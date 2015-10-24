
#include "stdafx.h"
#include "AVRecv.h"
#include "AVPlay.h"
#include "Network/PackQueue.h"
#include "Network/BuffPool.h"
#include <math.h>


CAVRecv::CAVRecv()
    :m_dwMTU(1000),
    m_wResendProto(0),
    m_wTimes(0),
    m_nAddrSize(0),
    m_nAddrSize6(0),
    m_bIPV6(FALSE),
    m_pQueueOut(NULL),
    m_pBigBuffPool(NULL),
    m_pSubBuffPool(NULL)
{
    m_nAddrSize = sizeof(SOCKADDR_IN);
    m_nAddrSize6 = sizeof(SOCKADDR_IN6);

    for (int i = 0; i < 32; i++) m_dwBit[i] = (1<<i);
}

CAVRecv::~CAVRecv()
{
    DWORD     dwChanId  = 0;
    PRECVINFO pRecvInfo = NULL;

    POSITION ps = m_mapRecvAV.GetStartPosition();
    while (NULL != ps)
    {
        m_mapRecvAV.GetNextAssoc(ps, dwChanId, pRecvInfo);

        while (pRecvInfo->AVList.GetCount())
        {
            m_pSubBuffPool->Free(pRecvInfo->AVList.GetHead(TRUE));
        }

        delete pRecvInfo;
    }
    m_mapRecvAV.RemoveAll();
}

// bIPV6        [in] IPV6地址
// dwMTU        [in] 块数据大小
// wResendProto [in] 重发音频帧协议号
// pAVPlay      [in] AV播放
// pQueueOut    [in] 发送队列
// pBigBuffPool [in] 缓冲区这个缓冲区应该设置的比较大，用于音视频和CAVplay用同一个BuffPool
// pSubBuffPool [in] 和通信层用的是同一个BuffPool
void CAVRecv::Init(BOOL bIPV6, DWORD dwMTU, WORD wResendProto, CAVPlay *pAVPlay,
                   CPackQueue *pQueueOut,CBuffPool *pBigBuffPool, CBuffPool *pSubBuffPool)
{
    m_bIPV6        = bIPV6;
    m_dwMTU        = dwMTU;
    m_wResendProto = wResendProto;
    m_pAVPlay      = pAVPlay;
    m_pQueueOut    = pQueueOut;
    m_pBigBuffPool = pBigBuffPool;
    m_pSubBuffPool = pSubBuffPool;
}

void CAVRecv::AddRecver(DWORD dwChanId, PCLIENT pClient, UINT64 *pnIP, WORD wPort)
{
    PRECVINFO pRecvInfo = NULL;
    if (!m_mapRecvAV.Lookup(dwChanId, pRecvInfo))
    {
        pRecvInfo                = new RECVINFO;
        pRecvInfo->dwWaitId      = 0;
        pRecvInfo->dwToPlayId    = 0;
        pRecvInfo->pClient       = pClient;
        pRecvInfo->Addr.wPort    = wPort;
        pRecvInfo->Addr.Int64[0] = pnIP[0];
        pRecvInfo->Addr.Int64[1] = pnIP[1];
        m_mapRecvAV.SetAt(dwChanId, pRecvInfo);
    }
}

void CAVRecv::DelRecver(DWORD dwChanId)
{
    PRECVINFO pRecvInfo = NULL;
    if (m_mapRecvAV.Lookup(dwChanId, pRecvInfo))
    {
        m_mapRecvAV.RemoveKey(dwChanId);

        while (pRecvInfo->AVList.GetCount())
        {
            m_pSubBuffPool->Free(pRecvInfo->AVList.GetHead(TRUE));
        }

        pRecvInfo->AVList.DelAll();

        delete pRecvInfo;
    }
}

// 检查是否有丢包
void CAVRecv::QuestResend(DWORD dwChanId, PRECVINFO pRecvInfo)
{
    DWORD dwHead = pRecvInfo->dwToPlayId + 1;
    DWORD dwTail = pRecvInfo->dwWaitId - 1;

    if ((dwTail - dwHead) > 30)
    {
        for (DWORD i = dwHead; i < dwTail; i++)
        {
            pRecvInfo->dwToPlayId = i++;
            PPACK pBlock = (PPACK)pRecvInfo->AVList.DelNode(i); 
            if (NULL != pBlock)
            {                
                if (VIDEO == pBlock->wProtoNum)
                {
                    PBLOCKEX pBlockEx = (PBLOCKEX)pBlock->byData;
                    WORD j = 0;
                    for (; j < pBlockEx->wBlockCount - 1; j++)    // 删除这一帧数据
                        m_pSubBuffPool->Free(pRecvInfo->AVList.DelNode(i + j));

                    i += j - 1;
                }

                m_pSubBuffPool->Free(pBlock);
            }
        }
    }
    else if (++m_wTimes == 10)
    {
        m_wTimes = 0;

        for (DWORD i = dwHead; i < dwTail; i++)
        {
            if (NULL == (PPACK)pRecvInfo->AVList.GetNode(i))
            {
                SendResend(dwChanId, i, pRecvInfo->pClient, pRecvInfo->Addr.Int64, pRecvInfo->Addr.wPort);
                TRACE("Quest resend %d\n", i);
            }
        }
    }
}

// 发送重发请求包
void CAVRecv::SendResend(DWORD dwChanId, DWORD dwId, PCLIENT pClient, UINT64 *pnIP, WORD wPort)
{
    PPACK pError = (PPACK)m_pSubBuffPool->Get();
    pError->Clear();
    pError->wProtoNum = m_wResendProto;
    pError->dwAckId = dwChanId;
    pError->dwId = dwId;

    m_pQueueOut->Add(pClient, pError->GetPackLen(), pError, pnIP, wPort);
}

// 将视频帧组合
void CAVRecv::MakeFrame(DWORD dwChanId, PRECVINFO pRecvInfo)
{
    do
    {
        PPACK pBlock = (PPACK)pRecvInfo->AVList.GetNode(pRecvInfo->dwToPlayId+1);
        if (NULL != pBlock)
        {
            if (VIDEO == pBlock->wProtoNum)
            {
                PBLOCKEX pBlockEx = (PBLOCKEX)pBlock->byData;
                if (pBlockEx->wBlockCount > 1)
                {
                    PPACK pNode = NULL;
                    PBLOCKEX pNodeEx = NULL;
                    m_arrPack.RemoveAll();
                    m_arrPack.Add(pBlock);
                    
                    for (DWORD i = pBlock->dwId + 1; i < pBlock->dwId + pBlockEx->wBlockCount; i++)
                    {
                        pNode = (PPACK)pRecvInfo->AVList.GetNode(i);
                        if (NULL != pNode)
                        {
                            pNodeEx = (PBLOCKEX)pBlock->byData;
                            if (VIDEO != pNode->wProtoNum) return;
                            if (pNodeEx->dwTime != pBlockEx->dwTime) return;
                            m_arrPack.Add(pNode);
                        }
                        else
                        {
                            return;
                        }
                    }

                    PPACK pSub = NULL;
                    PBLOCKEX pSubEx = NULL;
                    DWORD dwDataLen = 0;
                    DWORD dwId = 0;
                    PPACK pFrame = (PPACK)m_pBigBuffPool->Get();
                    pFrame->Clear();

                    for (int i = 0; i < m_arrPack.GetCount(); i++)
                    {
                        pSub = m_arrPack[i];
                        pSubEx = (PBLOCKEX)pSub->byData;
                        if (pSub->dwId > dwId) dwId = pSub->dwId;
                        dwDataLen = pSub->dwDataLen - sizeof(BLOCKEX);
                        pFrame->dwDataLen += dwDataLen;
                        memcpy(&pFrame->byData[m_dwMTU*pSub->wSubId], ++pSubEx, dwDataLen);
                    }

                    WORD w = pFrame->GetCheckNum();
                    if (pFrame->GetCheckNum() == pBlockEx->wFrameCheck)
                    {
                        pRecvInfo->dwToPlayId = dwId;
                        pFrame->dwId = pBlockEx->dwTime;
                        pFrame->wProtoNum = VIDEO_BIG;
                        if (!m_pAVPlay->AddAV(dwChanId, pFrame)) m_pBigBuffPool->Free(pFrame);
                    }
                    else
                    {
                        m_pBigBuffPool->Free(pFrame);
                    }

                    for (int i = 0; i < m_arrPack.GetCount(); i++)
                        m_pSubBuffPool->Free(pRecvInfo->AVList.DelNode(m_arrPack[i]->dwId));
                }
                else
                {
                    pRecvInfo->AVList.DelNode(pBlock->dwId);
                    pRecvInfo->dwToPlayId = pBlock->dwId;
                    pBlock->dwId = pBlockEx->dwTime;
                    if (!m_pAVPlay->AddAV(dwChanId, pBlock)) m_pSubBuffPool->Free(pBlock);
                }
            }
            else
            {                
                pRecvInfo->AVList.DelNode(pBlock->dwId);
                pRecvInfo->dwToPlayId = pBlock->dwId;
                PPACKEX pBlockEx = (PPACKEX)pBlock->byData;
                pBlock->dwId = pBlockEx->dwTime;
                if (!m_pAVPlay->AddAV(dwChanId, pBlock)) m_pSubBuffPool->Free(pBlock);
            }
        }
        else
            return;

    } while(true);
}

// 添回音视频包数据
// pBlock    [in] 数据包
// wProtoNum [in] 音视频 AUDIO 或 VIDEO
void CAVRecv::RecvAV(PPACK pBlock, WORD wType)
{
    DWORD     dwChanId  = pBlock->dwAckId;
    PRECVINFO pRecvInfo = NULL;
    if (m_mapRecvAV.Lookup(dwChanId, pRecvInfo))
    {
        if ((pBlock->GetCheckNum() == pBlock->wCheckSum) && (pBlock->dwId > pRecvInfo->dwToPlayId))
        {
            pBlock->wProtoNum = wType;
            pRecvInfo->dwWaitId = pBlock->dwId + 1;
            pRecvInfo->AVList.AddTail(pBlock->dwId, pBlock);
            this->QuestResend(dwChanId, pRecvInfo);
            this->MakeFrame(dwChanId, pRecvInfo);
            return;
        }
    }
    
    m_pSubBuffPool->Free(pBlock);
}