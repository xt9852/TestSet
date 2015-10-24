
#pragma once
#include <afxtempl.h>
#include <vfw.h>
#include "AV/G729.h"
#include "AV/H264.h"
#include "AV/WaveOut.h"
#include "AV/PackHead.h"
#include "Common/KeyList.h"


typedef struct tagPACKHEAD* PPACK;
class CPackQueue;
class CBuffPool;

typedef CArray<PPACK, PPACK>    PPACK_ARRAY;

enum { PLAY, PAUSE, STOP, FORWARD, BACKWARD };

typedef struct _tagPLAYINFO
{
    HANDLE              hPlayThread;    // 播放线程
    DWORD               dwChannId;      // 这路音视频的ID
    DWORD               dwLastTime;     // 上一次播放的时间
    BOOL                bPlay;          // 是否在播放
    BOOL                bSaveAV;        // 保存AV文件
    BOOL                bSaveImage;     // 保存一帧视频
    BOOL                bShowBigVideo;  // 显示大的视频

    INT                 x;              // 视频显示的位置
    INT                 y;
    INT                 x1;             // 大视频显示位置
    INT                 y1;
    INT                 cx;             // 大视频宽高
    INT                 cy;
    HDC                 hDC;            // 显示的DC
    HDRAWDIB            hDib;
    BITMAPINFOHEADER    *pBmpHeader;    // 位图的信息
    CH264               H264;           // H264解码

    CKeyList            AVList;         // 音视频完整数据包,索引为时间

    PPACK_ARRAY         AVArray;        // 用于播放文件
    BYTE                ePlayType;      // 播放暂停/停止/快进/快退

    DWORD               dwCreateTime;   // 创建文件时的时间
    CFile               File;           // 保存的文件
    CString             strFile;        // 文件名
    HWND                hWnd;           // 视频显示窗体,用于发送播放完消息

}PLAYINFO, *PPLAYINFO;

typedef CMap<DWORD, DWORD, PPLAYINFO, PPLAYINFO>    PLAYINFO_MAP;
typedef CList<PPLAYINFO, PPLAYINFO>                 PLAYINFO_LIST;


class CAVPlay;

typedef struct _tagTHREADPARM
{
    CAVPlay *pThis;
    DWORD    dwId;
    HWND     hWnd;
}THREADPARM, *PTHREADPARM;


/**
    播放AV数据,音频和视频是在一起的,此时的ID为播的时间
**/
class CAVPlay
{
public:
    CAVPlay();
    ~CAVPlay();

protected:
    CRITICAL_SECTION    m_csPlay;           // 播放临界区
    HANDLE		        m_hExit;            // 退出事件

    CBuffPool           *m_pBigBuffPool;    // 大的缓冲区
    CBuffPool           *m_pSubBuffPool;    // 小的缓冲区
    
    PLAYINFO_MAP        m_mapPlayAV;        // 已经接收到的数据
    PLAYINFO_LIST       m_lstFree;          // 空闲的

    CG729               m_G729;             // 音频G729编解码,不同通道的音频可用同一个
    CWaveOut			m_WaveOut;          // 音频的播放
    char                m_szAudio[16000];   // 音频数据的缓冲区

    enum {AUDIO = 1, VIDEO, VIDEO_BIG};

protected:
    void NewPlayer(PPLAYINFO *ppPlayInfo, DWORD dwChanId, LPCSTR strFile, HDC hDC, HWND hWnd, int x, int y,
        BOOL bShowBigVideo, int x1, int y1, int cx, int cy);
    void DelPlayer(PPLAYINFO pPlayInfo, BOOL bDel);
    void SaveAV(BYTE byType, CFile *pFile, WORD wSleep, PBYTE pbyData, WORD wLen);
    void SaveBmp(PPLAYINFO pPlayInfo, PBYTE pbyData);
    void Destory(void);    
    void ProcessPlayAV(DWORD dwAVId);
    void ProcessPreFile(DWORD dwAVId);
    void ProcessPlayFile(DWORD dwAVId);
    
    static unsigned __stdcall PlayAVThread(void* pParam);
    static unsigned __stdcall PlayFileThread(void* pParam);

public:
    void  Init(CBuffPool *pBigBuffPool, CBuffPool *pSubBuffPool);
    void  AddPlayer(DWORD dwChanId, HDC hDC, int x, int y, BOOL bShowBigVideo, int x1, int y1, int cx, int cy);
    void  AddPlayer(DWORD dwChanId, LPCSTR strFile, HWND hWnd, int x, int y, BOOL bShowBigVideo, int x1, int y1, int cx, int cy);
    void  DelPlayer(DWORD dwChanId);
    void  SetPlayFile(DWORD dwChanId, BYTE ePlayType);
    void  StartSaveFile(DWORD dwChanId, LPCSTR strFile);
    DWORD StopSaveFile(DWORD dwChanId);
    void  SaveImage(DWORD dwChanId, LPCSTR strFile);
    void  StartShowBigVideo(DWORD dwChanId);
    void  StopShowBigVideo(DWORD dwChanId);
    BOOL  AddAV(DWORD dwChanId, PPACK pFrame);
};