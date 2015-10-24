// CallingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CallingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Base\ooasn1.h"
#include "Base\ootypes.h"
#include "Base\ooq931.h"
extern struct ooAppContext * myContext;

/////////////////////////////////////////////////////////////////////////////
// CCallingDlg dialog


CCallingDlg::CCallingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCallingDlg)
	m_strTip = _T("");
	//}}AFX_DATA_INIT
}


void CCallingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCallingDlg)
	DDX_Text(pDX, IDC_H323_CALLING_WAIT_TIP, m_strTip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCallingDlg, CDialog)
	//{{AFX_MSG_MAP(CCallingDlg)
	ON_BN_CLICKED(IDC_H323_CALLING_CANCELCALL, OnCancelCall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallingDlg message handlers

void CCallingDlg::ShowTip(LPCTSTR strTip)
{
	m_strTip.Format("正在等待 %s 的应答...",strTip);
	UpdateData(FALSE);
}

void CCallingDlg::OnCancelCall() 
{
	// TODO: Add your control notification handler code here
	ooSendReleaseComplete(myContext);
	CDialog::OnCancel();	
}
