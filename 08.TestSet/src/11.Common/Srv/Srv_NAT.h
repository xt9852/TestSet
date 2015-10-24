
#pragma once

#include <list>
#include "Network\Srv.h"
#include "Network\PackId.h"
#include "Network\ResendQueue.h"
#include "Common\AVList.h"
#include "Common\RecvAVMap.h"

#define SVR_IP          _T("211.100.28.61")
#define SVR_PORT        6000
#define MY_MTU          1400

#include <map>


// 协议号（两字节长）
// PT_发送者_接收者
// U-用户， S-服务器
// 登录登录器就起到了开启本方的网关,就可以想要通信方进行通信
// 此过程是双向的同时进行

#define PT_U_S_LOGON_SERVER_REQUEST 0x1000  // 用户登录服务器，带有私网IP,Port,UserID,RoomNum

#define PT_S_U_IN_ROOM_USER         0x1010  // 房间内已有的人，带有用户信息
#define PT_S_U_INTO_ROOM_USER       0x1011  // 新进入房间的人，带有用户信息

#define PT_U_S_IN_ROOM_ACK          0x1020  // 应答 PT_S_U_IN_ROOM_USER 消息
#define PT_U_S_INTO_ROOM_ACK        0x1021  // 应答 PT_S_U_INTO_ROOM_USER 消息

#define PT_S_U_OUT_ROOM_USER        0x1032  // 用户退出，带有用户ID
#define PT_U_S_OUT_ROOM_USER        0x1033  // 用户退出，带有用户ID

#define PT_U_U_HELLO_REQUEST        0x1040  // 穿网测试
#define PT_U_U_HELLO_ANSWER         0x1041  // 穿网应答

#define PT_S_U_HEART_REQUEST        0x1050  // 心跳，带有用户ID
#define PT_U_S_HEART_ANSWER         0x1051  // 心跳，带有用户ID

#define PT_ACK_MSG                  0x1060  // 应答消息

#define PT_U_U_TEXT                 0x1070  // 文本信息
#define PT_U_S_VIDEO                0x1071  // 视频信息
#define PT_S_U_VIDEO                0x1072  // 视频信息
#define PT_U_U_VIDEO                0x1073  // 视频信息
#define PT_U_S_AUDIO                0x1074  // 音频信息
#define PT_S_U_AUDIO                0x1075  // 音频信息
#define PT_U_U_AUDIO                0x1076  // 音频信息

#define PT_U_S_RESEND               0x1080  // 通过服务器转发
#define PT_S_U_RESEND               0x1081  // 通过服务器转发
#define PT_U_U_RESEND               0x1082  // 通过服务器转发

enum
{
    UNCOMMUNICATION,
    COMMUNICING,
    COMMUNICED,
    IN_LAN
};

enum
{
    TYPE_AUDIO,
    TYPE_VIDEO,
    TYPE_COMMAND
};

typedef struct _tagUserInfo
{
    ULONG       lPublicIp;      // 公网IP
    WORD        wPublicPort;        // 公网端口
    ULONG       lPrivateIp;     // 私网IP
    WORD        wPrivatePort;       // 私网端口
    DWORD       dwAckTime;      // 心跳应答时间
    DWORD       dwUserId;       // 用户ID
    WORD        wRoomNum;       // 房间号   
    BYTE        byCommState;        // 通信状态 0-末直通 1-测试中 2-已直通

}USER_INFO,*PUSER_INFO;


typedef std::map<DWORD, USER_INFO> USER_MAP;    // 用户ID为索引
typedef std::map<WORD, USER_MAP>   ROOM_MAP;    // 房间号为索引
typedef std::pair<USER_MAP::iterator, bool> USER_MAP_INSERT;
typedef std::pair<ROOM_MAP::iterator, bool> ROOM_MAP_INSERT;

// 登录信息，用于登陆服务器
typedef struct _tagLogonInfo
{
    DWORD       dwUserId;       // 用户ID
    WORD        wRoomNum;       // 房间号
    ULONG       lPrivateIp;     // 私网IP
    WORD        wPrivatePort;   // 私网端口

}LOGON_INFO,*PLOGON_INFO;

// 用户ID房间号
typedef struct _tagUserId_RoomNum
{
    DWORD       dwUserId;       // 用户ID
    WORD        wRoomNum;       // 房间号

}USERID_ROOMNUM,*PUSERID_ROOMNUM;

// 视频应用包
typedef struct _tagSubPackInfo
{
    DWORD       dwVideoId;      // 视频ID
    WORD        wRoomNum;       // 房间号
    UCHAR       ucSubPackNum;   // 子包数量
    UCHAR       ucSubPackId;    // 子包ID
    UCHAR       ucData[1];      // 数据

}SUBPACKINFO,*PSUBPACKINFO;

// 重传应用包
typedef struct _tagResendPack
{
    WORD        wRoomNum;       // 房间号
    DWORD       dwRecvUserId;   // 接收者用户ID
    DWORD       dwPackId;       // 重传的消息ID
    WORD        wPackType;      // 重传类型

}RESENDPACK,*PRESENDPACK;



class CDlg_NAT;

class CSrv_NAT : public CSrv
{
public:
    CSrv_NAT(void);
    ~CSrv_NAT(void);

private:
    CRITICAL_SECTION m_csCheckNum;      // 临界区
    CResendQueue    m_ResendQueue;      // 用于消息的重发（当没有收到确认包）
    CPackID         m_PackId;           // 用于得到包ID
    CDlg_NAT*       m_pDlg;             // 窗体
    CListCtrl*      m_pList;            // 列表

    ROOM_MAP        m_RoomMap;          // 房间MAP(服务器用)
    USER_MAP        m_UserMap;          // 用户MAP(客户端用)    
    HANDLE          m_hLockRoomMap;     // 锁定房间MAP
    HANDLE          m_hLockUserMap;     // 锁定用户MAP
    HANDLE          m_hCommThread;      // 穿网,客户端心跳线程
    HANDLE          m_hSvrHeartBeatThread;  // 服务心跳检测线程 

    CLIENTCONTEXT   *m_pMyUdpCC;        // UDP客户端
    ULONG           m_lMyPubIp;         // 自己的公网IP（网络字节顺序）
    WORD            m_wMyPubPort;       // 自己的公网端口（网络字节顺序）
    ULONG           m_lMyPriIp;         // 自己的私网IP（网络字节顺序）
    WORD            m_wMyPriPort;       // 自己的私网端口（网络字节顺序）
    ULONG           m_lServerIp;        // 服务器的IP（网络字节顺序）
    WORD            m_wServerPort;      // 服务器的端口（网络字节顺序）
    DWORD           m_dwMyId;           // 用户ID
    WORD            m_wMyRoomNum;       // 用户房间号

    DWORD           m_dwAudioId;        // 音频ID
    DWORD           m_dwVideoId;        // 视频ID
    CAVList         m_AudioList;        // 已经发送的音频数据
    CAVList         m_VideoList;        // 已经发送的视频数据

    void Lock(HANDLE hOject);
    void UnLock(HANDLE hOject);
    bool AddList(DWORD dwUserId, DWORD dwPubIP, WORD wPubPort, DWORD dwPriIP, WORD wPriPort, LPCTSTR pszInfo);
    BOOL ModList(DWORD dwUserId, WORD wCol, LPCTSTR pszInfo);
    bool S_Broadcast(WORD wRoom, WORD wTimes, PPACK pPack);
    bool S_Transmit(WORD wRoom, DWORD dwUserId, WORD wTimes, PPACK pPack);
    bool S_NotfiyUserOutRoom(DWORD dwUserId, WORD wRoomNum, USER_MAP* pUserMap);
    bool PSU_ShowText(DWORD dwIP, WORD wPort, PPACK pPack);

    // 服务器处理(PS)
    bool PS_UserLogonServer(DWORD dwIP, WORD wPort, PPACK pPack);
    bool PS_UserIntoRoomAck(DWORD dwIP, WORD wPort, PPACK pPack);
    bool PS_NotfiyUserOutRoom(PPACK pPack);
    bool PS_HeartBeatAnswer(PPACK pPack);
    bool PS_BroadcastVideo(PPACK pPack);
    bool PS_BroadcastAudio(PPACK pPack);
    bool PS_Resend(PPACK pPack);

    // 客户端处理(PU)
    bool PU_UserIntoRoom(DWORD dwIP, WORD wPort, PPACK pPack);
    bool PU_UserOutRoom(DWORD dwIP, WORD wPort, PPACK pPack);
    bool PU_HelloRequest(DWORD dwIP, WORD wPort, PPACK pPack);
    bool PU_HelloAnswer(DWORD dwIP, WORD wPort, PPACK pPack);
    bool PU_Resend(PPACK pPack);

public: 
    CRecvAVMap m_RecvMap;       // 接收其它用户发来的音视频
    BYTE Init(LPCTSTR pszIp, const WORD wPort, BOOL bSrv, CDlg_NAT *pDlg);
    WORD GetCheckNum(LPBYTE byData, DWORD dwDataLen);
    void ProcessPack(PCLIENTCONTEXT pClient, DWORD dwIP, WORD wPort, DWORD dwDataLen, PBYTE pbyBuf);
    static unsigned __stdcall CommThread(LPVOID pParam);
    static unsigned __stdcall SvrHeartBeatThread(LPVOID pParam);

    // 客户端应用
    bool U_LogonServer(LPCTSTR pszIp, WORD wPort, UINT nUserId, WORD wRoomNum);
    bool U_RequestOutRoom(void);
    bool U_SendText(LPCTSTR pszIp, WORD wPort, LPCSTR pszText);
    bool U_SendVideo(DWORD dwUserId, WORD wProtoNum, BYTE *pbyVideo, WORD wDataLen);
    bool U_SendAudio(DWORD dwUserId, WORD wProtoNum, UCHAR *pAudio, int nDataLen);
    bool U_RequestResend(DWORD dwUserId, DWORD dwPackId, WORD wType);
};
