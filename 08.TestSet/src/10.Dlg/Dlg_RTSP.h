#pragma once

#include "Srv/Srv_RTSP.h"
#include "Player/RealPlayer.h"


class CDlg_RTSP : public CDialog
{
    DECLARE_DYNAMIC(CDlg_RTSP)

public:
    CDlg_RTSP(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_RTSP();

    // 对话框数据
    enum { IDD = IDD_DLG_RTSP };

private:
    XT_IOCP::CSrv_RTSP  m_SrvRTSP;

    static CRealPlayer	m_Player;
    BOOL			    m_bFullScreen;

    static HHOOK		m_hMsgHook;
    CMenu			    m_PopMenu;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

    LRESULT OnFullScreen(WPARAM wParam, LPARAM lParam);
    LRESULT OnContextMenu(WPARAM wParam, LPARAM lParam);
    static  LRESULT CALLBACK MsgHook(int nCode, WPARAM wParam, LPARAM lParam);
    static  LRESULT	CALLBACK MenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static unsigned __stdcall RtpThread(void* pParam);
public:
    afx_msg void OnDestroy();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedButStartServer();
    afx_msg void OnBnClickedButStartClient();    
    afx_msg void OnBnClickedRtspButRtpClient();
    afx_msg void OnBnClickedRtspButRtpServer();
};
