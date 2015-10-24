
#pragma once
#include "4.Media/MediaLayout"
#include "4.Media/AudioCapture.h"
#include "4.Media/VideoCapture.h"
// #include <map>
// 
// typedef std::map<HDC, POINT> MAP_HDC;



/**
    ������Ƶ����Ƶ����,Ȼ����CAVSend���͸�ָ�����û�
    ��Ƶ:G729����
    ��Ƶ:H264����
*/
class CMeidaCapture : public MeidaLayout, public CAudioCapture, public CVideoCapture
{
public:
    CMeidaCapture();
    ~CMeidaCapture();

protected:
    BOOL                m_bAudio;           // ��õ�Ƶ
    BOOL                m_bVideo;           // �����Ƶ

    CG729               m_G729;             // ��ƵG729�����
    CHAR                m_szAudio[1000];    // ��Ƶ������

    CH264               m_H264;             // ��ƵH264�����

    MAP_HDC             m_mapHdc;           // ��ʾ��Ƶ

    HDRAWDIB            m_hDib;
    BITMAPINFOHEADER    *m_pBmpHeader;      // λͼ��Ϣ

    CAVSend             *m_pAVSend;         // ���緢�Ͷ���

    CFile               m_File;             // ������ļ�
    BOOL                m_bSaveFile;        // �Ƿ񱣴��ļ�
    DWORD               m_dwLastTime;       // ��һ��ʱ��

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