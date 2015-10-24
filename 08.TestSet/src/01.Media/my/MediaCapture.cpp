
#include "stdafx.h"
#include "AVCapt.h"
//#include "AVSend.h"


CAVCapt::CAVCapt()
    :m_bAudio(FALSE),
    m_bVideo(FALSE),
    m_hDib(NULL),
    m_pBmpHeader(NULL),
    m_pAVSend(NULL),
    m_bSaveFile(FALSE),
    m_dwLastTime(0)
{
}

CAVCapt::~CAVCapt()
{
    Destory();
}

void CAVCapt::Init(CAVSend *pAVSend)
{
    m_pAVSend = pAVSend;
    m_hDib = ::DrawDibOpen();

    m_pBmpHeader = CVideoCapture::Init(NULL, NULL);

    int nRet = m_H264.InitH264();
    if (0 != nRet)
    {
        CString strError;
        strError.Format(_T("³õÊ¹»¯²¶»ñH264Ê§°Ü %d"), nRet);
        AfxMessageBox(strError);
    }

    CWaveIn::StartRec();
}

void CAVCapt::AddShow(HDC hDC, int x, int y)
{
    ::DrawDibBegin(m_hDib, hDC, -1, -1, m_pBmpHeader, IMAGE_WIDTH, IMAGE_HEIGHT, 0);
    POINT pt = {x, y};
    m_mapHdc.insert(MAP_HDC::value_type(hDC, pt));
}

void CAVCapt::DelShow(HDC hDC)
{
    m_mapHdc.erase(hDC);
}

void CAVCapt::StartSaveFile(LPCTSTR psFile)
{
    if (!m_bSaveFile)
    {
        m_bSaveFile = m_File.Open(psFile, CFile::modeCreate | CFile::modeReadWrite);
        m_bSaveFile = TRUE;
    }
}

void CAVCapt::StopSaveFile(void)
{
    if (m_bSaveFile)
    {
        m_File.Close();
        m_bSaveFile = FALSE;
    }
}

void CAVCapt::Start(BOOL bAudio, BOOL bVideo)
{
    m_bAudio = bAudio;
    m_bVideo = bVideo;

    if (m_bVideo) CVideoCapture::StartCapture();
    if (m_bAudio) CWaveIn::OpenRecord();
}

void CAVCapt::Stop(BOOL bAudio, BOOL bVideo)
{
    m_bAudio = !bAudio;
    m_bVideo = !bVideo;

    if (!m_bVideo) CVideoCapture::StopCapture();
    if (!m_bAudio) CWaveIn::CloseRecord();
}

void CAVCapt::Destory(void)
{
    CVideoCapture::StopCapture();
    CWaveIn::StopRec();
    m_H264.UninitH264();    
    ::DrawDibClose(m_hDib);
}

void CAVCapt::ProcAudio(char *pszData, DWORD dwLen)
{
    int nOutLen = 0;
    m_G729.Encode(pszData, dwLen, m_szAudio, &nOutLen);

    if (m_bSaveFile)
    {
        if (0 == m_dwLastTime) m_dwLastTime = ::GetTickCount();

        FRAMEINFO FrameInfo = {0};
        FrameInfo.byType    = 1;
        FrameInfo.wSleep    = ::GetTickCount() - m_dwLastTime;
        FrameInfo.wLen      = nOutLen;
        m_File.Write(&FrameInfo, sizeof(FrameInfo));
        m_File.Write(m_szAudio, nOutLen);
    }

    //if (NULL != m_pAVSend) m_pAVSend->SendAudio((PBYTE)m_szAudio, nOutLen);
}

void CAVCapt::ProcVideo(LPBYTE pbyData, int nLen)
{
    if (this->m_isOver || pbyData == NULL) return;

    if (m_mapHdc.size() > 0)
    {
        HDC hDC = NULL;
        POINT pt = {0};
        MAP_HDC::iterator iter = m_mapHdc.begin();
        for(; iter != m_mapHdc.end(); ++iter)
        {
			hDC = iter->first;
			pt  = iter->second;
            ::DrawDibDraw(m_hDib,hDC,pt.x,pt.y,-1,-1,m_pBmpHeader,pbyData,0,0,IMAGE_WIDTH,IMAGE_HEIGHT,DDF_SAME_DRAW);
        }
    }

    int nEnDataLen = 0;
    BYTE *pEnData = m_H264.Encode(pbyData, nEnDataLen);

    if (m_bSaveFile)
    {
        if (0 == m_dwLastTime) m_dwLastTime = ::GetTickCount();

        FRAMEINFO FrameInfo = {0};
        FrameInfo.byType = 2;
        FrameInfo.wSleep = ::GetTickCount() - m_dwLastTime;
        FrameInfo.wLen   = nEnDataLen;
        m_File.Write(&FrameInfo, sizeof(FrameInfo));
        m_File.Write(pEnData, nEnDataLen);
    }

    //if (NULL != pEnData) m_pAVSend->SendVideo(pEnData, nEnDataLen);
}