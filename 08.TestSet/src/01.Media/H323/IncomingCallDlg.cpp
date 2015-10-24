// IncomingCallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IncomingCallDlg.h"
#include "H323MsgHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern struct ooAppContext *myContext;
/////////////////////////////////////////////////////////////////////////////
// CIncomingCallDlg dialog
CIncomingCallDlg::CIncomingCallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIncomingCallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIncomingCallDlg)
	m_strTip = _T("");
	//}}AFX_DATA_INIT
	m_hIcons[0] = ::LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_EMULE_BMP_UP));
	m_hIcons[1] = ::LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_EMULE_BMP_DOWN));
	m_iIndex = 0;
}


void CIncomingCallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIncomingCallDlg)
	DDX_Control(pDX, IDC_H323_INCOMING_CALL_INDICATOR, m_cIndicator);
	DDX_Text(pDX, IDC_H323_INCOMING_CALL_TIP, m_strTip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIncomingCallDlg, CDialog)
	//{{AFX_MSG_MAP(CIncomingCallDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIncomingCallDlg message handlers

void CIncomingCallDlg::ShowTip(LPCTSTR strTip)
{
	m_strTip.Format("侦听到来自 %s 的呼叫",strTip);
	UpdateData(FALSE);
}

void CIncomingCallDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_iIndex)
		m_iIndex = 1;
	else
		m_iIndex = 0;

	m_cIndicator.SetIcon(m_hIcons[m_iIndex]);
	
	CDialog::OnTimer(nIDEvent);
}

void CIncomingCallDlg::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(2004);
	SetEvent(CH323MsgHandler::hRespondEvent);
	CH323MsgHandler::bAcceptCall = TRUE;
	
	CDialog::OnOK();
}

void CIncomingCallDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	KillTimer(2004);
	SetEvent(CH323MsgHandler::hRespondEvent);
	CH323MsgHandler::bAcceptCall = FALSE;

	CDialog::OnCancel();
}
