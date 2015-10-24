
#pragma once
#include <afxtempl.h>
#include "Common/KeyList.h"
//#include "Network/DefineClientContext.h"

typedef struct tagClientContext*  PCLIENT;
typedef struct tagPACKHEAD*       PPACK;
typedef struct _tagPackEx*        PPACKEX;
typedef struct _tagBlockEx*       PBLOCKEX;
class CPackQueue;
class CBuffPool;
class CAVPlay;

typedef struct _tagRECVINFO
{
    DWORD          dwWaitId;    // 顺序ID,希望接收到的帧ID
    DWORD          dwToPlayId;  // 顺序ID,已经发送到AVPlay的ID
    CKeyList       AVList;      // 音视频数据块
    //ADDR           Addr;        // 地址
	int		ip;
	short   port;
    PCLIENT pClient;
}RECVINFO, *PRECVINFO;

typedef CMap<DWORD, DWORD, PRECVINFO, PRECVINFO>    RECVINFO_MAP;
typedef CArray<PPACK, PPACK>                        PPACK_ARR;


/**
    将收到的数据组合成并将数据就发送给AVPlay,由其播放,
    音频和视频的ID是在一起顺序的
**/
class CAVRecv
{
public:
    CAVRecv();
    ~CAVRecv();

protected:
    DWORD           m_dwBit[32];    // 二进制位值
    DWORD           m_dwMTU;        // 最小传输单元
    WORD            m_wResendProto; // 重传协议号,音视频用同一个
    WORD            m_wTimes;       // 检测是否有丢包
    UINT            m_nAddrSize;    // IPV4地址结构大小
    UINT            m_nAddrSize6;   // IPV6地址结构大小
    BOOL            m_bIPV6;        // IPV6地址

    CAVPlay         *m_pAVPlay;     // 播放对象
    CPackQueue      *m_pQueueOut;   // 发送队列,用户发送重传请求
    CBuffPool       *m_pBigBuffPool;// 大的缓冲区
    CBuffPool       *m_pSubBuffPool;// 小的缓冲区

    RECVINFO_MAP    m_mapRecvAV;    // 接收到的音视频包
    PPACK_ARR       m_arrPack;      // 视频子包队列

    enum {AUDIO = 1, VIDEO, VIDEO_BIG};

protected:
    void MakeFrame(DWORD dwChanId, PRECVINFO pRecvInfo);
    void QuestResend(DWORD dwChanId, PRECVINFO pRecvInfo);
    void SendResend(DWORD dwChanId, DWORD dwId, PCLIENT pClient, UINT64 *pnIP, WORD wPort);

public:
    void Init(BOOL bIPV6, DWORD dwMTU, WORD wResendProto, CAVPlay *pAVPlay, 
              CPackQueue *pQueueOut, CBuffPool *pBigBuffPool, CBuffPool *pSubBuffPool);
    void AddRecver(DWORD dwChanId, PCLIENT pClient, UINT64 *pnIP, WORD wPort);
    void DelRecver(DWORD dwChanId);
    void RecvAV(PPACK pPack, WORD wType);
};