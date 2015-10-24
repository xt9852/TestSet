
#pragma once
#include "Media/VideoCapture.h"
#include "Media/WaveIn.h"
#include "Media/G729.h"
#include "Media/H264.h"
#include <map>

typedef std::map<HDC, POINT> MAP_HDC;


class CAVSend;


/**
    捕获音频和视频数据,然后由CAVSend发送给指定的用户
    音频:G729编码
    视频:H264编码
*/
class CMeidaCapt : public CWaveIn, public CVideoCapture
{
public:
    CMeidaCapt();
    ~CMeidaCapt();

protected:
    BOOL                m_bAudio;           // 获得单频
    BOOL                m_bVideo;           // 获得视频
    
    CG729               m_G729;             // 音频G729编解码
    CHAR                m_szAudio[1000];    // 音频缓冲区

    CH264               m_H264;             // 视频H264编解码

    MAP_HDC             m_mapHdc;           // 显示视频

    HDRAWDIB            m_hDib;
    BITMAPINFOHEADER    *m_pBmpHeader;      // 位图信息

    CAVSend             *m_pAVSend;         // 网络发送对象

    CFile               m_File;             // 保存的文件
    BOOL                m_bSaveFile;        // 是否保存文件
    DWORD               m_dwLastTime;       // 上一次时间

protected:
    void Destory(void);
    virtual void ProcAudio(char *pszData, DWORD dwLen);
    virtual void ProcVideo(LPBYTE pbyData, int nLen);

public:
    void Init(CAVSend *pAVSend);
    void Start(BOOL bAudio, BOOL bVideo);
    void Stop(BOOL bAudio, BOOL bVideo);
    void AddShow(HDC hDC, int x, int y);
    void DelShow(HDC hDC);
    void StartSaveFile(LPCTSTR psFile);
    void StopSaveFile(void);
};