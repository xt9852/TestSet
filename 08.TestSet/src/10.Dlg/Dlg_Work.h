#pragma once
#include "resource.h"
//#include "Chat/chat_serverDlg.h"
//#include "Chat/chat_clientDlg.h"

class CDlg_Work : public CDialog
{
	DECLARE_DYNAMIC(CDlg_Work)

public:
	CDlg_Work(CWnd* pParent = NULL);
	virtual ~CDlg_Work();

	enum { IDD = IDD_DLG_WORK };

//     Cchat_serverDlg *m_pChatSrv;
//     Cchat_clientDlg *m_pChatClt1;
//     Cchat_clientDlg *m_pChatClt2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
public:
    afx_msg void OnBnClickedWorkBtnChatsrv();
    afx_msg void OnBnClickedWorkBtnChatclt();
};
