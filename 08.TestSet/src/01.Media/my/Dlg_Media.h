
#pragma once

#include "resource.h"
//#include "Srv/Srv_AV.h"
//#include "Media/MediaCapt.h"
//#include "SoundCtrl.h"
#include "VideoPlay.h"
#include "VideoCapture.h"
#include "VideoEncode.h"
#include "VideoDecode.h"

class CDlg_Media : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Media)

public:
    CDlg_Media(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_Media();

    enum { IDD = IDD_1_MEDIA };

private:
    CTabCtrl    tableCtrl_;

//     CSoundCtrl  m_SoundCtrl;    // 音频控制
     CSliderCtrl m_SoundSel;
// 
//     XT_IOCP::CSrv_AV m_SrvAV;
// 
// 	CMeidaCapt capture_;
// 
// 	BYTE		*m_pbyData;
// 	DWORD		m_dwDataLen;
// 	CBrush		m_hBrush;

    VideoPlay       videoPlay_;
    VideoPlay       videoPlay2_;
    VideoCapture    videoCature_;
    VideoEncode     videoEncode_;
    VideoDecode     videoDecode_;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedMediaBtnInit();
    afx_msg void OnBnClickedMediaBtnUninit();
    afx_msg void OnBnClickedStart();
    afx_msg void OnBnClickedStop();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
