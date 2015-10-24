
/**
消息已经发送出去，等待此消息的确认（每个消息都有必须有确认，主要应用在UDP传输中）
如果没有得到此消息的确认则在 CHECK_TIMEOUT 秒后重新发送此消息
如果重发了 SEND_TIMES 次仍没有得到此消息的确认则将其删除
*/

#pragma once

#define RESEND_TIME     2000    // 毫秒超时
#define MAX_SEND_TIMES  5       // 发送次数

typedef struct tagClientContext *PCLIENT;
class CBufferPool;
class CSrv;

typedef struct tagAckPack
{
    DWORD   dwUserId;   // 用户ID
    DWORD   dwPackId;   // 包ID 
    DWORD   dwDataLen;  // 数据长
    DWORD   dwNextTime; // 下次发送时间
    WORD    wSendTimes; // 已经发送的次数
    WORD    wProtoNum;  // 协议号
    ADDR    Addr;       // 地址
    PCLIENT pClient;    // 发送对象
    PPACK   pData;      // 数据包

}ACKPACK,*PACKPACK;


//消息ID为索引
typedef CMap<DWORD, DWORD&, ACKPACK, ACKPACK> CWAITACKMAP;

class CResendQueue
{
public: 
    CResendQueue();
    ~CResendQueue();

    CRITICAL_SECTION    m_csUsedFlag;
    CWAITACKMAP         m_mapAckPack;
    CBuffPool           *m_pBuffPool;
    CSrv                *m_pSrv;

    int  Init(CSrv *pSrv, CBuffPool *pBuffPool);
    void UnInit(void);

    BOOL Add(DWORD dwUserId, DWORD dwPackId, PPACK pPack, PCLIENT pClient, ADDR &Addr);
    BOOL Add(DWORD dwUserId, DWORD dwPackId, PPACK pPack, PCLIENT pClient, UINT64 *pnIP, WORD wPort);
    BOOL Del(DWORD dwPackId);
    BOOL Del(DWORD dwUserId, WORD wProtoNum);
    static unsigned __stdcall CheckPackThread(LPVOID pParam);   // 包处理线程

protected:
    void CheckPack();
    HANDLE  m_hExit;    // 杀死线程句柄
    HANDLE  m_hThread;  // 等待消息处理线程
    BOOL    m_bInit;    // 是否初使化
};
