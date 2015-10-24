
#include "stdafx.h"
#include "AVPlay.h"
#include "Network/PackQueue.h"
#include "Network/BuffPool.h"
#include "VideoCapture.h"
#include <process.h>

/*
线程    状态    退出码

播放    正常    400
播放    强闭    401
播放    异常    402
*/


UINT WM_STOP_PLAY = ::RegisterWindowMessage(_T("WM_STOP_PLAY"));


CAVPlay::CAVPlay()
    :m_hExit(NULL),
    m_pBigBuffPool(NULL),
    m_pSubBuffPool(NULL)
{
    m_hExit = CreateEvent(NULL, FALSE, FALSE, NULL);
    ::ResetEvent(m_hExit);
    ::InitializeCriticalSection(&m_csPlay);
}

CAVPlay::~CAVPlay()
{    
    Destory();
    ::DeleteCriticalSection(&m_csPlay);
}

void CAVPlay::Init(CBuffPool *pBigBuffPool, CBuffPool *pSubBuffPool)
{
    m_pBigBuffPool = pBigBuffPool;
    m_pSubBuffPool = pSubBuffPool;
    m_WaveOut.StartPlay(); 
}

void CAVPlay::Destory(void)
{
    ::SetEvent(m_hExit);
    ::CloseHandle(m_hExit);
    m_hExit = NULL;

    ::EnterCriticalSection(&m_csPlay);

    DWORD dwChanId = 0;
    PPLAYINFO pPlayInfo = NULL;
    POSITION ps = m_mapPlayAV.GetStartPosition();
    while (NULL != ps)
    {
        m_mapPlayAV.GetNextAssoc(ps, dwChanId, pPlayInfo);
        this->DelPlayer(pPlayInfo, TRUE);
    }

    while (m_lstFree.GetCount() > 0)
    {
        this->DelPlayer(m_lstFree.RemoveHead(), TRUE);
    }

    m_mapPlayAV.RemoveAll();
    m_WaveOut.StopPlay();

    ::LeaveCriticalSection(&m_csPlay);
}

// 新建对象
void CAVPlay::NewPlayer(PPLAYINFO *ppPlayInfo, 
                        DWORD dwChanId, 
                        LPCSTR strFile, 
                        HDC hDC,
                        HWND hWnd,
                        int x, int y,
                        BOOL bShowBigVideo,
                        int x1, int y1, int cx, int cy)
{
    if (m_lstFree.GetCount() > 0)
    {
        *ppPlayInfo = m_lstFree.RemoveHead();
    }
    else
    {
        *ppPlayInfo = new PLAYINFO;

        (*ppPlayInfo)->hDib = ::DrawDibOpen();
        if (0 != (*ppPlayInfo)->H264.InitH264()) AfxMessageBox(_T("初使化播放H264错误"));
    }
    
    (*ppPlayInfo)->hPlayThread = NULL;
    (*ppPlayInfo)->dwChannId   = dwChanId;
    (*ppPlayInfo)->ePlayType   = PLAY;
    (*ppPlayInfo)->dwLastTime  = 0;
    (*ppPlayInfo)->bPlay       = FALSE;
    (*ppPlayInfo)->bSaveAV     = FALSE;
    (*ppPlayInfo)->bSaveImage  = FALSE;
    (*ppPlayInfo)->bShowBigVideo = bShowBigVideo;
    (*ppPlayInfo)->x           = x;
    (*ppPlayInfo)->y           = y;
    (*ppPlayInfo)->x1          = x1;
    (*ppPlayInfo)->y1          = y1;
    (*ppPlayInfo)->cx          = cx;
    (*ppPlayInfo)->cy          = cy;
    (*ppPlayInfo)->hWnd        = hWnd;
    (*ppPlayInfo)->hDC         = hDC;
    (*ppPlayInfo)->strFile     = strFile;
    (*ppPlayInfo)->pBmpHeader  = CVideoCapture::GetInfo(hDC, (*ppPlayInfo)->hDib);

    if ((NULL != strFile) && (!(*ppPlayInfo)->File.Open(strFile, CFile::modeRead)))
        TRACE(_T("pPlayInfo->File.Open %s error:%d\n"), strFile, ::GetLastError());

    if (NULL == strFile)
    {
        UINT nThreadID = 0;
        PTHREADPARM pParm = new THREADPARM;
        pParm->pThis = this;
        pParm->dwId = dwChanId;
        pParm->hWnd = hWnd;
        (*ppPlayInfo)->hPlayThread = (HANDLE)_beginthreadex(NULL, 0, PlayAVThread, pParm, 0, &nThreadID);
    }
}

// 删除对象
void CAVPlay::DelPlayer(PPLAYINFO pPlayInfo, BOOL bDel)
{
    while (pPlayInfo->AVList.GetCount() > 0)
    {
        PPACK pFrame = (PPACK)pPlayInfo->AVList.GetHead(TRUE);
        if (NULL != pFrame)
        {
            if ((AUDIO == pFrame->wProtoNum) || (VIDEO == pFrame->wProtoNum))
                m_pSubBuffPool->Free(pFrame);
            else
                m_pBigBuffPool->Free(pFrame);
        }
    }
    pPlayInfo->AVList.DelAll();

    int nCount = pPlayInfo->AVArray.GetCount();
    for (int i = 0; i < nCount; i++)
    {
        PPACK pFrame = (PPACK)pPlayInfo->AVArray[i];
        if (NULL != pFrame)
        {
            if ((AUDIO == pFrame->wProtoNum) || (VIDEO == pFrame->wProtoNum))
                m_pSubBuffPool->Free(pFrame);
            else
                m_pBigBuffPool->Free(pFrame);
        }
    }
    pPlayInfo->AVArray.RemoveAll();

    // 关闭线程
    if (pPlayInfo->hPlayThread != NULL)
    {
        int i = 10;
        for (; i > 0; i--)
        {
            DWORD nCode;
            if (!GetExitCodeThread(pPlayInfo->hPlayThread, &nCode)) break;
            if (nCode != STILL_ACTIVE) break;
            Sleep(50);
        }

        if (i == 0)
        {
            TRACE(_T("WARNING: Terminating CAVPlay.PlayThread Thread.\n"));
            TerminateThread(pPlayInfo->hPlayThread, 401);
        }

        CloseHandle(pPlayInfo->hPlayThread);
        pPlayInfo->hPlayThread = NULL;
    }

    if (pPlayInfo->bSaveAV) pPlayInfo->File.Close();

    if (NULL != pPlayInfo->hWnd) ::ReleaseDC(pPlayInfo->hWnd, pPlayInfo->hDC);

    if (bDel)
    {
        pPlayInfo->H264.UninitH264();
        ::DrawDibClose(pPlayInfo->hDib);

        delete pPlayInfo;
    }
}

// 保存AV文件
void CAVPlay::SaveAV(BYTE byType, CFile *pFile, WORD wSleep, PBYTE pbyData, WORD wLen)
{
    FRAMEINFO FrameInfo = {0};
    FrameInfo.byType = byType;
    FrameInfo.wSleep = wSleep;
    FrameInfo.wLen   = wLen;

    if (NULL != pFile)
    {
        pFile->Write(&FrameInfo, sizeof(FrameInfo));
        pFile->Write(pbyData, wLen);
    }
}

// 保存居位图
void CAVPlay::SaveBmp(PPLAYINFO pPlayInfo, PBYTE pbyData)
{
    CVideoCapture::SaveBmp(pPlayInfo->strFile, pbyData);
    pPlayInfo->bSaveImage = FALSE;
}

// 添加播放对象
// dwChanId [in] 通道ID
// hDC      [in] 显示DC
// hDib     [in] 显示DIB
// x,y      [in] 视频显示的位置
void CAVPlay::AddPlayer(DWORD dwChanId, HDC hDC, int x, int y, 
                        BOOL bShowBigVideo, int x1, int y1, int cx, int cy)
{
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (!m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        this->NewPlayer(&pPlayInfo, dwChanId, NULL, hDC, NULL, x, y, bShowBigVideo, x1, y1, cx, cy);
        m_mapPlayAV.SetAt(dwChanId, pPlayInfo);
    }
    ::LeaveCriticalSection(&m_csPlay);
}

// 添加播放对象(直接播放一个文件)
// strFile  [in] 文件名
// hDC      [in] 显示DC
// hDib     [in] 显示DIB
// x,y      [in] 视频显示的位置
void CAVPlay::AddPlayer(DWORD dwChanId, LPCSTR strFile, HWND hWnd, int x, int y, 
                        BOOL bShowBigVideo, int x1, int y1, int cx, int cy)
{
    UINT nThreadID = 0;
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (!m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        this->NewPlayer(&pPlayInfo, dwChanId, strFile, ::GetDC(hWnd), hWnd, x, y, bShowBigVideo, x1, y1, cx, cy);
        m_mapPlayAV.SetAt(dwChanId, pPlayInfo);
    }

    PTHREADPARM pParm = new THREADPARM;
    pParm->pThis = this;
    pParm->dwId = dwChanId;
    pParm->hWnd = hWnd;

    pPlayInfo->hPlayThread = (HANDLE)_beginthreadex(NULL, 0, PlayFileThread, pParm, 0, &nThreadID);
    ::LeaveCriticalSection(&m_csPlay);
}

// 删除播放对象
// dwChanId [in] 通道ID
void CAVPlay::DelPlayer(DWORD dwChanId)
{
    UINT nThreadID = 0;
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        m_mapPlayAV.RemoveKey(dwChanId);
        m_lstFree.AddTail(pPlayInfo);

        this->DelPlayer(pPlayInfo, FALSE);
    }
    ::LeaveCriticalSection(&m_csPlay);
}

// 开始保存文件
void CAVPlay::StartSaveFile(DWORD dwChanId, LPCSTR strFile)
{
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        if (!pPlayInfo->bSaveAV)
        {
            try
            {
                if (pPlayInfo->File.Open(strFile, CFile::modeCreate|CFile::modeReadWrite))
                {
                    pPlayInfo->bSaveAV = TRUE;
                    pPlayInfo->dwCreateTime = ::GetTickCount();
                }
                else
                {
                    TRACE(_T("Open %s Fail %d\n"), strFile, ::GetLastError());
                    pPlayInfo->bSaveAV = FALSE;
                }
            }
            catch (...)
            {
                TRACE(_T("pPlayInfo->File.Open error:%d\n"), ::GetLastError());
            }
        }
    }
    ::LeaveCriticalSection(&m_csPlay);
}

// 停止保存文件
// dwChanId [in]  通道号
// 返回           文件时间长
DWORD CAVPlay::StopSaveFile(DWORD dwChanId)
{
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        pPlayInfo->bSaveAV = FALSE;

        CFileStatus FileStatus;
        pPlayInfo->File.GetStatus(FileStatus);
        pPlayInfo->File.Close();

        ::LeaveCriticalSection(&m_csPlay);
        return (::GetTickCount() - pPlayInfo->dwCreateTime);
    }
    ::LeaveCriticalSection(&m_csPlay);
    return 0;
}

// 设置播放
// dwChanId  [in] 通道号
// ePlayType [in] 播放类型(PLAY,PAUSE,STOP,FORWARD,BACKWARD)
void CAVPlay::SetPlayFile(DWORD dwChanId, BYTE ePlayType)
{
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        pPlayInfo->ePlayType = ePlayType;
    }
    ::LeaveCriticalSection(&m_csPlay);
}

// 保存一帧视频
void CAVPlay::SaveImage(DWORD dwChanId, LPCSTR strFile)
{
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        pPlayInfo->strFile.Format(_T("%s"), strFile);
        pPlayInfo->bSaveImage = TRUE;
    }
    ::LeaveCriticalSection(&m_csPlay);
}

// 显示大视频
void CAVPlay::StartShowBigVideo(DWORD dwChanId)
{
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        pPlayInfo->bShowBigVideo = TRUE;
    }
    ::LeaveCriticalSection(&m_csPlay);
}

// 停止显示大视频
void CAVPlay::StopShowBigVideo(DWORD dwChanId)
{
    PPLAYINFO pPlayInfo = NULL;
    ::EnterCriticalSection(&m_csPlay);
    if (m_mapPlayAV.Lookup(dwChanId, pPlayInfo))
    {
        pPlayInfo->bShowBigVideo = FALSE;
    }
    ::LeaveCriticalSection(&m_csPlay);
}

// 添加包数据
// dwChanId [in] 通道ID
// pFrame   [in] 数据包
BOOL CAVPlay::AddAV(DWORD dwChanId, PPACK pFrame)
{
    PPLAYINFO pPlayInfo = NULL;

    ::EnterCriticalSection(&m_csPlay);
    BOOL bRet = m_mapPlayAV.Lookup(dwChanId, pPlayInfo);
    ::LeaveCriticalSection(&m_csPlay);

    if (bRet) pPlayInfo->AVList.AddTail(pFrame->dwId, pFrame);

    return bRet;
}

// 播放视频
unsigned CAVPlay::PlayAVThread(void* pParam)
{
    if (NULL == pParam) return -1;

    PTHREADPARM pParm  = reinterpret_cast<PTHREADPARM>(pParam);
    HWND        hWnd   = pParm->hWnd;
    DWORD       dwAVId = pParm->dwId;
    CAVPlay     *pThis = pParm->pThis;
    delete      pParm;

    ::Sleep(100);

    pThis->ProcessPlayAV(dwAVId);

    return 0;
}

#define DRAWH264 pPlayInfo->hDib,pPlayInfo->hDC,pPlayInfo->x,pPlayInfo->y,\
    -1,-1,pPlayInfo->pBmpHeader,pbyData,\
    0,0,IMAGE_WIDTH,IMAGE_HEIGHT,DDF_SAME_DRAW

#define DRAWBIGH264 pPlayInfo->hDib,pPlayInfo->hDC,pPlayInfo->x1,pPlayInfo->y1,\
    pPlayInfo->cx,pPlayInfo->cy,pPlayInfo->pBmpHeader,pbyData,\
    0,0,IMAGE_WIDTH,IMAGE_HEIGHT,DDF_SAME_DRAW

// 播放视频流
void CAVPlay::ProcessPlayAV(DWORD dwAVId)
{
    try
    {
        int nDeLen = 0;
        int nPos = sizeof(BLOCKEX);
        BYTE *pbyData = NULL;

        DWORD dwTime = 0;
        PPLAYINFO pPlayInfo = NULL;
        if (!m_mapPlayAV.Lookup(dwAVId, pPlayInfo)) return;

        while (NULL != m_hExit)
        {
            PPACK pFrame = (PPACK)pPlayInfo->AVList.GetHead(TRUE);

            if (NULL != pFrame)
            {
                if (!pPlayInfo->bPlay)  // 不是连接播放
                {
                    dwTime = pFrame->dwId - pPlayInfo->dwLastTime;
                    pPlayInfo->bPlay = TRUE;
                    pPlayInfo->dwLastTime = pFrame->dwId;
                }
                else
                {
                    dwTime = (pFrame->dwId) - (pPlayInfo->dwLastTime);
                    if ((dwTime > 100) || (pPlayInfo->AVList.GetCount() > 10)) dwTime = 0;
                    ::Sleep(dwTime);
                    pPlayInfo->dwLastTime = pFrame->dwId;
                }

                if (VIDEO == pFrame->wProtoNum)
                {
                    nDeLen = 0;
                    pbyData = pPlayInfo->H264.Decode(&pFrame->byData[nPos], pFrame->dwDataLen-nPos, nDeLen);

                    ::DrawDibDraw(DRAWH264);                                    // 显示视频
                    if (pPlayInfo->bShowBigVideo) ::DrawDibDraw(DRAWBIGH264);   // 显示大个视频
                    if (pPlayInfo->bSaveImage)    SaveBmp(pPlayInfo, pbyData);  // 保存图片
                    if (pPlayInfo->bSaveAV)       SaveAV(VIDEO, &(pPlayInfo->File), dwTime, &pFrame->byData[nPos], pFrame->dwDataLen-nPos);// 保存文件

                    m_pSubBuffPool->Free(pFrame);
                }
                else if (VIDEO_BIG == pFrame->wProtoNum)
                {
                    pbyData = pPlayInfo->H264.Decode(pFrame->byData, pFrame->dwDataLen, nDeLen);

                    ::DrawDibDraw(DRAWH264);
                    if (pPlayInfo->bShowBigVideo) ::DrawDibDraw(DRAWBIGH264);
                    if (pPlayInfo->bSaveImage)    SaveBmp(pPlayInfo, pbyData);
                    if (pPlayInfo->bSaveAV)       SaveAV(VIDEO, &(pPlayInfo->File), dwTime, pFrame->byData, pFrame->dwDataLen);

                    m_pBigBuffPool->Free(pFrame);
                }
                else
                {
                    m_G729.Decode((char*)&(pFrame->byData[8]), pFrame->dwDataLen - 8, m_szAudio, &nDeLen);

                    m_WaveOut.Play(m_szAudio, nDeLen);
                    if (pPlayInfo->bSaveAV) SaveAV(AUDIO, &(pPlayInfo->File), dwTime, (PBYTE)&(pFrame->byData[8]), pFrame->dwDataLen-8);

                    m_pSubBuffPool->Free(pFrame);
                }
            }
            else
            {
                pPlayInfo->bPlay = FALSE;   // 无数据暂时停止播放
                ::Sleep(10);
            }
        }
    }
    catch(...)
    {
        TRACE(_T("ProcessPlayAV error:%d\n"), ::GetLastError());
    }
}

// 播放文件
unsigned CAVPlay::PlayFileThread(void* pParam)
{
    if (NULL == pParam) return -1;

    PTHREADPARM pParm  = reinterpret_cast<PTHREADPARM>(pParam);
    HWND        hWnd   = pParm->hWnd;
    DWORD       dwAVId = pParm->dwId;
    CAVPlay     *pThis = pParm->pThis;
    delete pParm;

    ::Sleep(100);

    pThis->ProcessPreFile(dwAVId);
    pThis->ProcessPlayFile(dwAVId);

    ::PostMessage(hWnd, WM_STOP_PLAY, dwAVId, NULL);
    TRACE(_T("PostMessage WM_STOP_PLAY\n"));

    return 400;
}

// 准备文件
void CAVPlay::ProcessPreFile(DWORD dwAVId)
{ 
    try
    {
        int nDeLen = 0;
        char szAudio[16000] = "";
        BYTE *pbyData = NULL;
        FRAMEINFO FrameInfo = {0};
        UINT nFrameSize = sizeof(FrameInfo);

        PPLAYINFO pPlayInfo = NULL;
        if (!m_mapPlayAV.Lookup(dwAVId, pPlayInfo)) return;

        if (pPlayInfo->AVArray.GetCount() > 0) return;   // 已经准备好了数据

        while (NULL != m_hExit)
        {
            if (pPlayInfo->File.Read(&FrameInfo, nFrameSize) == nFrameSize)
            {
                PPACK pFrame = NULL;

                if (FrameInfo.byType == VIDEO)
                {
                    pFrame = (PPACK)m_pBigBuffPool->Get();                    
                    pPlayInfo->File.Read(pFrame->byData, FrameInfo.wLen);
                    pbyData = pPlayInfo->H264.Decode(pFrame->byData, FrameInfo.wLen, nDeLen);
                    pFrame->wProtoNum = VIDEO_BIG;
                    pFrame->dwId      = FrameInfo.wSleep; // 间隔时间
                    
                    if (NULL != pbyData)
                    {
                        memcpy(pFrame->byData, pbyData, IMAGE_WIDTH*IMAGE_HEIGHT*3);
                        pPlayInfo->AVArray.Add(pFrame);
                    }
                    else
                    {
                        m_pBigBuffPool->Free(pFrame);
                    }
                }
                else
                {
                    pFrame = (PPACK)m_pSubBuffPool->Get();                    
                    pPlayInfo->File.Read(pFrame->byData, FrameInfo.wLen);
                    m_G729.Decode((char*)&(pFrame->byData), FrameInfo.wLen, szAudio, &nDeLen);
                    memcpy(pFrame->byData, szAudio, nDeLen);

                    pFrame->wProtoNum = AUDIO;
                    pFrame->dwDataLen = nDeLen;
                    pFrame->dwId      = FrameInfo.wSleep;
                    pPlayInfo->AVArray.Add(pFrame);
                }

                
            }
            else
            {
                pPlayInfo->File.Close();
                TRACE(_T("Close play file\n"));
                return;
            }
        }
    }
    catch (...)
    {
        TRACE(_T("ProcessFile error:%d\n"), ::GetLastError());
    }
    return;
}

// 播放文件视频流
void CAVPlay::ProcessPlayFile(DWORD dwAVId)
{
    try
    {
        int nDeLen = 0;
        BYTE *pbyData = NULL;

        DWORD dwTime = 0;
        PPLAYINFO pPlayInfo = NULL;
        if (!m_mapPlayAV.Lookup(dwAVId, pPlayInfo)) return;

        int nCulFrameId = 0;
        int nCount = pPlayInfo->AVArray.GetCount();

        pPlayInfo->ePlayType = PLAY;

        while ((NULL != m_hExit) && (nCount > 0))
        {
            PPACK pFrame = (PPACK)pPlayInfo->AVArray[nCulFrameId];

            switch (pPlayInfo->ePlayType)
            {
            case PLAY: nCulFrameId++; break;
            case PAUSE: break;
            case STOP: return;
            case FORWARD: nCulFrameId += 10; break;
            case BACKWARD: nCulFrameId -= 10; break;
            }

            ::Sleep(pFrame->dwId);
            if ((nCulFrameId < 0) || (nCulFrameId >= nCount)) return;

            if (NULL != pFrame)
            {
                if (VIDEO_BIG == pFrame->wProtoNum)
                {
                    pbyData = pFrame->byData;

                    ::DrawDibDraw(DRAWH264);
                    if (pPlayInfo->bShowBigVideo) ::DrawDibDraw(DRAWBIGH264);
                }
                else
                {
                    m_WaveOut.Play((char*)pFrame->byData, pFrame->dwDataLen);
                }
            }
        }
    }
    catch(...)
    {
        TRACE(_T("ProcessPlayFile error:%d\n"), ::GetLastError());
    }
}