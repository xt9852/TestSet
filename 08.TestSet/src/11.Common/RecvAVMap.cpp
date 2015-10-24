
#include "stdafx.h"
#include "Common\RecvAVMap.h"
#include "Dlg\Dlg_NAT.h"
#include "Srv\Srv_NAT.h"

CRecvAVMap::CRecvAVMap()
{
    InitializeCriticalSection(&m_csUsedAudio);
    InitializeCriticalSection(&m_csUsedVideo);

    m_UserMap.InitHashTable(20);
    m_hExit = CreateEvent(NULL, TRUE, FALSE, NULL);

    m_pSrvNat = NULL;
    m_pDlg = NULL;
    m_pBuffPool = NULL;
    m_hPlayThread = NULL;

    m_hdc = NULL;
    m_hdib = NULL;
    m_pbmpheader = NULL;

    m_ptVideo[0].x = 190;
    m_ptVideo[0].y = 250;
    m_ptVideo[1].x = 370;
    m_ptVideo[1].y = 250;
    m_ptVideo[2].x = 550;
    m_ptVideo[2].y = 250;

    for (int i = 0; i < USER_COUNT; i++)
    {
        m_bUsed[i] = false;
    }
}

CRecvAVMap::~CRecvAVMap()
{
    Uninit();

    DeleteCriticalSection(&m_csUsedAudio);
    DeleteCriticalSection(&m_csUsedVideo);
}

bool CRecvAVMap::Init(CSrv_NAT* pSrvNat, CDlg_NAT* pDlg, CBuffPool* pBuffPool)
{
    if (NULL == pSrvNat || NULL == pDlg || NULL == pBuffPool) return false;

    m_pSrvNat = pSrvNat;
    m_pDlg = pDlg;
    m_pBuffPool = pBuffPool;

    m_hdc = m_pDlg->m_hdc;
    m_hdib = m_pDlg->m_hdib;
    m_pbmpheader= m_pDlg->m_pbmpheader;

    UINT nThreadId = 0;
    m_hPlayThread = (HANDLE)_beginthreadex(NULL, 0, PlayThread, (void*)this, 0, &nThreadId);

    return true;
}

void CRecvAVMap::Uninit(void)
{
    if (NULL != m_hExit) SetEvent(m_hExit);


    //--------------------------------------------------------------------------

    POSITION pos = m_UserMap.GetStartPosition();
    while (NULL != pos)
    {
        CAvInfo* pAvInfo = NULL;
        DWORD dwKey = 0;
        m_UserMap.GetNextAssoc(pos, dwKey, pAvInfo);

        if (NULL != pAvInfo)
        {
            pAvInfo->AudioList.DelAll();
            pAvInfo->VideoList.DelAll();
            pAvInfo->h264.UninitH264();
            m_bUsed[pAvInfo->wLocId] = false;

            delete pAvInfo;
        }       
    }

    m_UserMap.RemoveAll();

    //--------------------------------------------------------------------------


    DWORD nCode = 0;
    for (int nAttempt = 10 ; nAttempt > 0 ; nAttempt--)
    {       
        if (m_hPlayThread != NULL)
        {
            if (!GetExitCodeThread(m_hPlayThread, &nCode) || nCode != STILL_ACTIVE)
            {
                CloseHandle(m_hPlayThread);
                m_hPlayThread = NULL;
            }
        }

        Sleep(50);
    }

    if (NULL != m_hPlayThread)
    {
        TerminateThread(m_hPlayThread, 0);
        g_ProFile.m_Log.println(_T("WARNING: Terminating CRecvAVMap.PlayThread."));
        CloseHandle(m_hPlayThread);
        m_hPlayThread = NULL;
    }

    if (NULL != m_hExit) CloseHandle(m_hExit);
    m_hExit = NULL;
}

CAvInfo* CRecvAVMap::FineUser(DWORD dwUserId)
{
    CAvInfo* pAvInfo = NULL;
    m_UserMap.Lookup(dwUserId, pAvInfo);

    if (NULL == pAvInfo)
    {
        CAvInfo* pAvNewInfo = AddUser(dwUserId);

        if (NULL == pAvNewInfo)
            return NULL;
        else
            return pAvNewInfo;
    }

    return pAvInfo;
}

CAvInfo* CRecvAVMap::AddUser(DWORD dwUserId)
{
    if (m_UserMap.GetSize() >= USER_COUNT) return NULL;

    for (WORD i = 0; i < USER_COUNT; i++)
    {
        if (!m_bUsed[i])
        {
            m_bUsed[i] = true;
            break;
        }
    }

    if (i >= USER_COUNT) return NULL;

    CAvInfo* pAvInfo = new CAvInfo;
    pAvInfo->AudioList.Init(m_pBuffPool, 50);
    pAvInfo->VideoList.Init(m_pBuffPool, 50);
    pAvInfo->dwUserId = dwUserId;
    pAvInfo->wLocId = i;
    pAvInfo->dwWantAudioId = 0;
    pAvInfo->dwWantVideoId = 0;
    pAvInfo->dwPlayAudioId = 0;
    pAvInfo->dwPlayVideoId = 0;
    pAvInfo->wTempSubNum = 0;
    pAvInfo->lLocX = m_ptVideo[i].x;
    pAvInfo->lLocY = m_ptVideo[i].y;
    pAvInfo->hdc = m_hdc;
    pAvInfo->hdib = m_hdib;
    pAvInfo->pbmpheader = m_pbmpheader;
    pAvInfo->h264.InitH264();

    m_UserMap.SetAt(dwUserId, pAvInfo);

    return pAvInfo;
}

BOOL CRecvAVMap::DelUser(DWORD dwUserId)
{
    CAvInfo* pAvInfo = NULL;
    m_UserMap.Lookup(dwUserId, pAvInfo);

    if (NULL != pAvInfo)
    {
        pAvInfo->AudioList.DelAll();
        pAvInfo->VideoList.DelAll();
        pAvInfo->h264.UninitH264();
        m_bUsed[pAvInfo->wLocId] = false;

        delete pAvInfo;
    }

    return m_UserMap.RemoveKey(dwUserId);
}

// 计算校验码
WORD CRecvAVMap::GetCheckNum(PPACK pPack)
{
    WORD wCheckSum = 0;
    DWORD dwCount    = pPack->dwDataLen;
    BYTE* pBuffer  = (BYTE*)&(pPack->szData[0]);

    for(DWORD dwLoop = 0; dwLoop < dwCount; dwLoop++)
        wCheckSum += (pBuffer[dwLoop] << 1);

    return wCheckSum;
}

WORD CRecvAVMap::GetCheckNum(LPBYTE byData, INT nDataLen)
{
    WORD wCheckSum = 0;
    for(WORD wLoop = 0; wLoop < nDataLen; wLoop++)
        wCheckSum += (byData[wLoop]<<1);

    return wCheckSum;
}

bool CRecvAVMap::AddAudioData(PPACK pPack)
{
    /*  if (GetHeaderOfCheckNum(pPack) != pPack->wCheckSum)
    {
    TRACE(_T("Audio CheckNum Error\n"));
    g_ProFile.m_Log.println(_T("Audio CheckNum Error %d"), pPack->dwId);
    m_pSvrNat->U_RequestResend(pPack->dwAckId, pPack->dwId, TYPE_AUDIO);
    m_pBuffPool->Free(pPack);
    return false;
    }
    */
    //if (pPack->wCheckSum == 123) TRACE("A+%d\n", pPack->dwId);

    try
    {
        CAvInfo* pAvInfo = FineUser(pPack->dwAckId);
        if (NULL != pAvInfo)
        {
            DWORD dwPlayAudioId = pAvInfo->GetPlayAudioId();

            if (pPack->dwId == pAvInfo->dwWantAudioId)  // 接收到正确的包
            {
                if (pPack->dwId == dwPlayAudioId)
                {
                    m_pDlg->ShowAudio(pAvInfo->wLocId, pPack->dwId, (LPBYTE)&(pPack->szData[0]), 60);
                    m_pBuffPool->Free(pPack);
                    pAvInfo->AdcPlayAudioId();
                }
                else
                    pAvInfo->AudioList.AddTail(pPack->dwId, (LPBYTE)pPack);

                pAvInfo->dwWantAudioId++;
            }
            else if (0 == pAvInfo->dwWantAudioId)               // 后来的用户数据不是从第一个开始传的
            {
                pAvInfo->AudioList.AddTail(pPack->dwId, (LPBYTE)pPack);
                pAvInfo->SetPlayAudioId(pAvInfo->dwWantAudioId);
                pAvInfo->dwWantAudioId = pPack->dwId + 1;
            }
            else if (pPack->dwId > pAvInfo->dwWantAudioId)  // 丢包啦
            {
                pAvInfo->AudioList.AddTail(pPack->dwId, (LPBYTE)pPack);

                for (DWORD i = pAvInfo->dwWantAudioId; i < pPack->dwId; i++)
                {
                    TRACE("lose A %d\n", i);
                    LPBYTE pbyAudio = (LPBYTE)pAvInfo->AudioList.GetNode(i);
                    if (NULL == pbyAudio)
                        m_pSrvNat->U_RequestResend(pPack->dwAckId, i, TYPE_AUDIO);
                }

                pAvInfo->dwWantAudioId = pPack->dwId + 1;
            }
            else if (pPack->dwId >= dwPlayAudioId)  // 重传来的包
            {
                pAvInfo->AudioList.AddTail(pPack->dwId, (LPBYTE)pPack);
            }
            else
            {
                TRACE("< dwPlayAudio Id %d %d %d\n", pPack->dwId, dwPlayAudioId, pAvInfo->dwWantAudioId);
                m_pBuffPool->Free(pPack);
            }
            return true;
        }
        else
        {
            TRACE("No This User\n");
            m_pBuffPool->Free(pPack);
        }
    }
    catch(...)
    {
        TRACE("Add Audio Error %d", ::GetLastError());
    }

    return false;
}


bool CRecvAVMap::AddVideoData(PPACK pPack)
{
    /*  if (GetHeaderOfCheckNum(pPack) != pPack->wCheckSum)
    {
    TRACE(_T("Video CheckNum Error\n"));
    g_ProFile.m_Log.println(_T("Video CheckNum Error %d"), pPack->dwId);
    m_pSvrNat->U_RequestResend(pPack->dwAckId, pPack->dwId, TYPE_VIDEO);
    m_pBufferPool->Free(pPack);
    return false;
    }
    */
    //if (pPack->wCheckSum == 123) TRACE("V+%d\n", pPack->dwId);

    try
    {
        PSUBPACKINFO pNewVideoInfo = (PSUBPACKINFO)&(pPack->szData[0]);
        int nNewVideoLen = pPack->dwDataLen - sizeof(SUBPACKINFO) + 1;

        CAvInfo* pAvInfo = FineUser(pPack->dwAckId);
        if (NULL != pAvInfo)
        {
            DWORD dwPlayVideoId = pAvInfo->GetPlayVideoId();

            if (pPack->dwId == pAvInfo->dwWantVideoId)      // 接收到想要的包
            {
                if (pNewVideoInfo->dwVideoId == dwPlayVideoId)  // 同一帧视频包
                {
                    if (pNewVideoInfo->ucSubPackNum == 1)       // 单一包
                    {
                        pAvInfo->ShowVideo((BYTE*)&(pNewVideoInfo->ucData[0]), nNewVideoLen);

                        m_pBuffPool->Free(pPack);
                        pAvInfo->AdcPlayVideoId();
                    }
                    else
                        pAvInfo->VideoList.AddTail(pPack->dwId, (LPBYTE)pPack);

                }
                else
                    pAvInfo->VideoList.AddTail(pPack->dwId, (LPBYTE)pPack);

                pAvInfo->dwWantVideoId++;
            }
            else if (0 == pAvInfo->dwWantVideoId)               // 后来的用户数据不是从第一个开始传的
            {
                pAvInfo->VideoList.AddTail(pPack->dwId, (LPBYTE)pPack);
                pAvInfo->SetPlayVideoId(pAvInfo->dwWantVideoId);
                pAvInfo->dwWantVideoId = pPack->dwId + 1;
            }
            else if (pPack->dwId > pAvInfo->dwWantVideoId)  // 丢包啦
            {
                pAvInfo->VideoList.AddTail(pPack->dwId, (BYTE*)pPack);

                for (DWORD i = pAvInfo->dwWantVideoId; i < pPack->dwId; i++)
                {
                    TRACE("lose V %d\n", i);
                    LPBYTE pbyVideo = (LPBYTE)pAvInfo->VideoList.GetNode(i);
                    if (NULL == pbyVideo)
                        m_pSrvNat->U_RequestResend(pPack->dwAckId, i, TYPE_VIDEO);
                }

                pAvInfo->dwWantVideoId = pPack->dwId + 1;
            }
            else if (pPack->dwId >= dwPlayVideoId)          // 重传来的包
            {
                pAvInfo->VideoList.AddTail(pPack->dwId, (BYTE*)pPack);
            }
            else
            {
                TRACE("< dwPlayVideoId %d %d %d\n", pPack->dwId, dwPlayVideoId, pAvInfo->dwWantVideoId);
                m_pBuffPool->Free(pPack);
            }
            return true;
        }
        else
        {
            TRACE("No This User\n");
            m_pBuffPool->Free(pPack);
        }
    }
    catch(...)
    {
        TRACE("Add Video Error %d", ::GetLastError());
    }

    return false;
}

// 播放线程
unsigned CRecvAVMap::PlayThread(LPVOID pParam)
{
    if( NULL == pParam ) return -1;

    CRecvAVMap *pThis = reinterpret_cast<CRecvAVMap*>(pParam);

    try
    {
        pThis->PlayThreadRun();
    }
    catch(...)
    {
        TRACE("PlayThread ErrorCode:%d\n",::GetLastError());
        g_ProFile.m_Log.println(_T("PlayThread ErrorCode:%d"), ::GetLastError());
    }
    return 0;
}

bool CRecvAVMap::PlayThreadRun(void)
{
    while (NULL != m_hExit)
    {
        if (WaitForSingleObject(m_hExit, 20) == WAIT_OBJECT_0)
            break;

        DWORD dwUserId = 0;
        CAvInfo *pAvInfo = NULL;

        POSITION ps = m_UserMap.GetStartPosition();
        while (NULL != ps)
        {
            m_UserMap.GetNextAssoc(ps, dwUserId, pAvInfo);

            if (NULL == pAvInfo) continue;

            DWORD dwPlayAudioId = pAvInfo->GetPlayAudioId();
            DWORD dwPlayVideoId = pAvInfo->GetPlayVideoId();

            try
            {
                //---------------------------------------------------------------------
                // 播放音频
                PPACK pPackAudio = (PPACK)pAvInfo->AudioList.GetNode(dwPlayAudioId);
                if (NULL != pPackAudio)
                {
                    if (pPackAudio->dwId == dwPlayAudioId)
                    {
                        m_pDlg->ShowAudio(pAvInfo->wLocId, pPackAudio->dwId, (LPBYTE)&(pPackAudio->szData[0]), 60);
                        pAvInfo->AudioList.DelNode(pPackAudio->dwId);
                        m_pBuffPool->Free(pPackAudio);
                        pAvInfo->AdcPlayAudioId();
                    }
                }
                else if (pAvInfo->AudioList.GetCount() > 20)
                {
                    for (DWORD i = 0; i < 10; i++)
                    {
                        PPACK pPackDel = (PPACK)pAvInfo->AudioList.GetHead();//.GetNode(dwPlayAudioId + i);
                        if (NULL != pPackDel)
                        {
                            if (pPackDel->dwId <= dwPlayAudioId)
                            {
                                TRACE("Del A %d \n", pPackDel->dwId);
                                pAvInfo->AudioList.DelNode(pPackDel->dwId);
                                m_pBuffPool->Free(pPackDel);
                            }
                            else
                            {
                                TRACE("AudioList Count %d\nSet PlayAudioId %d %d\n", pAvInfo->AudioList.EnumAll(), dwPlayAudioId, pPackDel->dwId);
                                pAvInfo->SetPlayAudioId(pPackDel->dwId);
                                break;
                            }
                        }
                    }
                }// end audio

                //-----------------------------------------------------------------------
                // 播放视频
                PPACK pPackVideo = (PPACK)pAvInfo->VideoList.GetNode(dwPlayVideoId);
                if (NULL != pPackVideo)
                {
                    PSUBPACKINFO pVideoInfo = (PSUBPACKINFO)&(pPackVideo->szData[0]);
                    int nVideoLen = pPackVideo->dwDataLen - sizeof(SUBPACKINFO) + 1;

                    if (pVideoInfo->ucSubPackNum == 1)  // 单一包
                    {
                        pAvInfo->ShowVideo((BYTE*)&(pVideoInfo->ucData[0]), nVideoLen);
                        pAvInfo->VideoList.DelNode(pPackVideo->dwId);
                        m_pBuffPool->Free(pPackVideo);
                        pAvInfo->AdcPlayVideoId();
                    }
                    else    // 子包
                    {
                        int nLastVideoLen = 0;

                        for (WORD dwSubId = pAvInfo->wTempSubNum; dwSubId < pVideoInfo->ucSubPackNum; dwSubId++)    // 拼子包
                        {
                            PPACK pPackLast = (PPACK)pAvInfo->VideoList.GetNode(dwPlayVideoId + dwSubId);
                            if (NULL != pPackLast)
                            {
                                PSUBPACKINFO pLastVideo = (PSUBPACKINFO)&(pPackLast->szData[0]);
                                nLastVideoLen = pPackLast->dwDataLen - sizeof(SUBPACKINFO) + 1;

                                pAvInfo->pbyTempBuf[pLastVideo->ucSubPackId] = (LPBYTE)pPackLast;
                                pAvInfo->wTempSubNum++;

                                memcpy(&(pAvInfo->ucVideo[pLastVideo->ucSubPackId * MY_MTU]), &(pLastVideo->ucData[0]), nLastVideoLen);
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (pAvInfo->wTempSubNum == pVideoInfo->ucSubPackNum)   // 播放视频
                        {
                            WORD wSumLen = (pVideoInfo->ucSubPackNum - 1) * MY_MTU + nLastVideoLen;

                            WORD wCheckNum = GetCheckNum((LPBYTE)&(pAvInfo->ucVideo[0]), wSumLen);

                            if (pPackVideo->wCheckSum == wCheckNum)
                            {
                                pAvInfo->ShowVideo((BYTE*)&(pAvInfo->ucVideo[0]), wSumLen);
                            }
                            else
                            {
                                TRACE("V check num error\n");
                            }

                            for (WORD i = 0; i < pVideoInfo->ucSubPackNum;i++)
                            {
                                pAvInfo->VideoList.DelNode(dwPlayVideoId + i);
                                m_pBuffPool->Free(pAvInfo->pbyTempBuf[i]);
                            }

                            pAvInfo->wTempSubNum = 0;
                            pAvInfo->AddPlayVideoId(pVideoInfo->ucSubPackNum);
                        }
                    }
                }
                else if (pAvInfo->VideoList.GetCount() > 20)
                {
                    for (DWORD i = 0; i < 10; i++)
                    {
                        PPACK pPackDel = (PPACK)pAvInfo->VideoList.GetHead();//.GetNode(dwPlayVideoId + i);
                        if (NULL != pPackDel)
                        {
                            PSUBPACKINFO pVideoInfo = (PSUBPACKINFO)&(pPackDel->szData[0]);
                            if (pVideoInfo->dwVideoId <= dwPlayVideoId)
                            {
                                TRACE("Del V %d \n", pVideoInfo->dwVideoId);
                                pAvInfo->VideoList.DelNode(pVideoInfo->dwVideoId);
                                m_pBuffPool->Free(pPackDel);
                            }
                            else
                            {
                                TRACE("VideoList Count %d\nSet PlayVideoId %d %d\n", pAvInfo->VideoList.EnumAll(), dwPlayVideoId, pVideoInfo->dwVideoId);
                                pAvInfo->SetPlayVideoId(pVideoInfo->dwVideoId);
                                break;
                            }
                        }
                    }
                }// video
            }
            catch(...)
            {
                TRACE("PlayThread Error %d\n", ::GetLastError());
            }
        }// end while m_UserMap
    }// end while totail

    return true;
}