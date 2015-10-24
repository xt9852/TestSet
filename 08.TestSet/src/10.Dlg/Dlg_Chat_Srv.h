
#pragma once
#include "resource.h"
#include "Srv/Srv_Chat.h"

class CDlg_Chat_Clt;

typedef CArray<CDlg_Chat_Clt*, CDlg_Chat_Clt*> CLIENT_ARRAY;

class CDlg_Chat_Srv : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Chat_Srv)

public:
    CDlg_Chat_Srv(CWnd* pParent = NULL);
    virtual ~CDlg_Chat_Srv();

    enum { IDD = IDD_DLG_CHAT_SRV };

private:
    CSrv_Chat		m_Server;
    BOOL			m_bRun;
    DWORD			m_dwLast;

    CButton         m_btnStart;

    CLIENT_ARRAY    m_arrClient;

protected:
    virtual BOOL OnInitDialog();	
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT nIDEvent);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedStart();
    afx_msg void OnBnClickedTest();
    afx_msg void OnBnClickedClient();
};
