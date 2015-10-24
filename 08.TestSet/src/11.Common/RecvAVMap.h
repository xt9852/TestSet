
#pragma once

#include <afxtempl.h>
#include <vfw.h>
#include "H264\H264.h"
#include "Network\PreparePack.h"
#include "Common\AVList.h"

#define USER_COUNT  3

class CAvInfo
{
public:
    CRITICAL_SECTION    m_csAvInfo;     // 临界区
    CRITICAL_SECTION    m_csAvPlayV;    // 临界区
    DWORD               dwUserId;       // 用户ID
    WORD                wLocId;         // 占用窗口号
    DWORD               dwWantVideoId;  // 希望接收的视频ID
    DWORD               dwWantAudioId;  // 希望接收的音频ID
    DWORD               dwPlayVideoId;  // 播放的视频ID
    DWORD               dwPlayAudioId;  // 播放的音频ID
    LONG                lLocX;          // 视频窗口x
    LONG                lLocY;          // 视频窗口y
    HDC                 hdc;            // HDC
    HDRAWDIB            hdib;           // 画位图
    BITMAPINFOHEADER*   pbmpheader;     // 位图信息
    CH264               h264;           // H264压缩
    UCHAR               ucVideo[80000]; // 完整的一帧视频缓冲
    WORD                wTempSubNum;    // 存的一个视频子包数量
    LPBYTE              pbyTempBuf[10]; // 视频缓冲区
    CAVList             AudioList;      // 接收到的音频
    CAVList             VideoList;      // 接收到的视频

    CAvInfo()
    {
        InitializeCriticalSection(&m_csAvInfo);
        InitializeCriticalSection(&m_csAvPlayV);
    }

    ~CAvInfo()
    {
        DeleteCriticalSection(&m_csAvInfo);
        DeleteCriticalSection(&m_csAvPlayV);
    }

    void ShowVideo(BYTE* pbyData, WORD wLen)
    {
        EnterCriticalSection(&m_csAvPlayV);

        BYTE *pDeCodeData = NULL;
        WORD wDeCodeDataLen = 0;

        pDeCodeData = h264.Decode(pbyData, wLen, wDeCodeDataLen);

        if (NULL != pDeCodeData)
            ::DrawDibDraw(hdib,hdc,lLocX,lLocY,-1,-1,pbmpheader,pDeCodeData,0,0,IMAGE_WIDTH,IMAGE_HEIGHT,DDF_SAME_DRAW);

        LeaveCriticalSection(&m_csAvPlayV);
    }

    DWORD GetPlayAudioId(void)
    {
        DWORD dwRetId = 0;
        EnterCriticalSection(&m_csAvInfo);
        dwRetId = dwPlayAudioId;
        LeaveCriticalSection(&m_csAvInfo);
        return dwRetId;
    }
    DWORD GetPlayVideoId(void)
    {
        DWORD dwRetId = 0;
        EnterCriticalSection(&m_csAvInfo);
        dwRetId = dwPlayVideoId;
        LeaveCriticalSection(&m_csAvInfo);
        return dwRetId;
    }
    void AdcPlayAudioId(void)
    {
        EnterCriticalSection(&m_csAvInfo);
        dwPlayAudioId++;
        LeaveCriticalSection(&m_csAvInfo);
    }   
    void AdcPlayVideoId(void)
    {
        EnterCriticalSection(&m_csAvInfo);
        dwPlayVideoId++;
        LeaveCriticalSection(&m_csAvInfo);
    }
    void AddPlayVideoId(DWORD dwNum)
    {
        EnterCriticalSection(&m_csAvInfo);
        dwPlayVideoId += dwNum;
        LeaveCriticalSection(&m_csAvInfo);
    }
    void SetPlayVideoId(DWORD dwNum)
    {
        EnterCriticalSection(&m_csAvInfo);
        dwPlayVideoId = dwNum;
        LeaveCriticalSection(&m_csAvInfo);
    }
    void SetPlayAudioId(DWORD dwNum)
    {
        EnterCriticalSection(&m_csAvInfo);
        dwPlayAudioId = dwNum;
        LeaveCriticalSection(&m_csAvInfo);
    }
};

typedef CMap<DWORD, DWORD&, CAvInfo*, CAvInfo*> CUserMap;

class CDlg_NAT;
class CSrv_NAT;

class CRecvAVMap
{
public: 
    CRecvAVMap();
    virtual ~CRecvAVMap();

private:
    CRITICAL_SECTION    m_csUsedAudio;
    CRITICAL_SECTION    m_csUsedVideo;
    HANDLE              m_hExit;
    HANDLE              m_hPlayThread;

    CSrv_NAT*           m_pSrvNat;
    CDlg_NAT*           m_pDlg;
    CBuffPool*          m_pBuffPool;

    HDC                 m_hdc;
    HDRAWDIB            m_hdib;
    BITMAPINFOHEADER*   m_pbmpheader;

    CUserMap            m_UserMap;
    CPoint              m_ptVideo[USER_COUNT];
    bool                m_bUsed[USER_COUNT];

    CAvInfo* FineUser(DWORD dwUserId);
    CAvInfo* AddUser(DWORD dwUserId);
    WORD GetCheckNum(PPACK pPack);
    WORD GetCheckNum(LPBYTE byData, INT nDataLen);

public:
    bool Init(CSrv_NAT* pSrvNat, CDlg_NAT* pDlg, CBuffPool* pBuffPool);
    void Uninit(void);
    bool AddVideoData(PPACK pPack);
    bool AddAudioData(PPACK pPack);
    BOOL DelUser(DWORD dwUserId);
    static unsigned __stdcall PlayThread(LPVOID pParam);
    bool PlayThreadRun(void);   
};
