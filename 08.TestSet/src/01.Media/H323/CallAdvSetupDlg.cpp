// CallAdvSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CallAdvSetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCallAdvSetupDlg dialog


CCallAdvSetupDlg::CCallAdvSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallAdvSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCallAdvSetupDlg)
	m_bViaGK = FALSE;
	m_bName = FALSE;
	m_bNumber = FALSE;
	m_strName = _T("");
	m_strNumber = _T("");
	m_strGatekeeper = _T("");
	//}}AFX_DATA_INIT
	m_bViaGW = TRUE;
}


void CCallAdvSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCallAdvSetupDlg)
	DDX_Check(pDX, IDC_H323_SETUP_CALL_BY_GK, m_bViaGK);
	DDX_Check(pDX, IDC_H323_SETUP_CALL_BY_NAME, m_bName);
	DDX_Check(pDX, IDC_H323_SETUP_CALL_BY_NUMBER, m_bNumber);
	DDX_Text(pDX, IDC_H323_SETUP_CALLED_NAME, m_strName);
	DDX_Text(pDX, IDC_H323_SETUP_CALLED_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_H323_SETUP_GK_ADDR, m_strGatekeeper);
	//}}AFX_DATA_MAP
	DDX_Check(pDX,IDC_H323_SETUP_CALL_VIA_GW,m_bViaGW);
	DDX_Text(pDX,IDC_H323_SETUP_GATEWAY_ADDRESS,m_strGateway);
}


BEGIN_MESSAGE_MAP(CCallAdvSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CCallAdvSetupDlg)
	ON_BN_CLICKED(IDC_H323_SETUP_CALL_BY_GK, OnCallByGk)
	ON_BN_CLICKED(IDC_H323_SETUP_CALL_BY_NAME, OnCallByName)
	ON_BN_CLICKED(IDC_H323_SETUP_CALL_BY_NUMBER, OnCallByNumber)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_H323_SETUP_CALL_VIA_GW,OnCallViaGW)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallAdvSetupDlg message handlers

void CCallAdvSetupDlg::OnCallByGk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CWnd *pGkAddr,*pByName,*pByNo,*pName,*pNo,*pViaGW,*pGW;
	pGkAddr = GetDlgItem(IDC_H323_SETUP_GK_ADDR);
	pByName = GetDlgItem(IDC_H323_SETUP_CALL_BY_NAME);
	pName = GetDlgItem(IDC_H323_SETUP_CALLED_NAME);
	pByNo = GetDlgItem(IDC_H323_SETUP_CALL_BY_NUMBER);
	pNo = GetDlgItem(IDC_H323_SETUP_CALLED_NUMBER);
	pViaGW = GetDlgItem(IDC_H323_SETUP_CALL_VIA_GW);
	pGW = GetDlgItem(IDC_H323_SETUP_GATEWAY_ADDRESS);

	if(m_bViaGK == FALSE)
	{
		pGkAddr->EnableWindow(FALSE);
		pByName->EnableWindow(FALSE);
		pName->EnableWindow(FALSE);
		pByNo->EnableWindow(FALSE);
		pNo->EnableWindow(FALSE);
		pViaGW->EnableWindow(TRUE);
		OnCallViaGW();
	}
	else
	{
		pGkAddr->EnableWindow(TRUE);
		pByName->EnableWindow(TRUE);
		pByNo->EnableWindow(TRUE);
		pViaGW->EnableWindow(FALSE);
		pGW->EnableWindow(FALSE);
		OnCallByName();
		OnCallByNumber();
	}
}

void CCallAdvSetupDlg::OnCallByName() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CWnd * 	pName = GetDlgItem(IDC_H323_SETUP_CALLED_NAME);
	if(m_bName == TRUE)
		pName->EnableWindow(TRUE);
	else
		pName->EnableWindow(FALSE);
}

void CCallAdvSetupDlg::OnCallByNumber() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CWnd * 	pNo = GetDlgItem(IDC_H323_SETUP_CALLED_NUMBER);
	if(m_bNumber == TRUE)
		pNo->EnableWindow(TRUE);
	else
		pNo->EnableWindow(FALSE);	
}

void CCallAdvSetupDlg::OnCallViaGW()
{
	UpdateData(TRUE);
	CWnd *pGateway = GetDlgItem(IDC_H323_SETUP_GATEWAY_ADDRESS);
	pGateway->EnableWindow(m_bViaGW);
}

BOOL CCallAdvSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *pGkAddr,*pByName,*pName,*pByNo,*pNo,*pByGW,*pGW;
	pGkAddr = GetDlgItem(IDC_H323_SETUP_GK_ADDR);
	pByName = GetDlgItem(IDC_H323_SETUP_CALL_BY_NAME);
	pName = GetDlgItem(IDC_H323_SETUP_CALLED_NAME);
	pByNo = GetDlgItem(IDC_H323_SETUP_CALL_BY_NUMBER);
	pNo = GetDlgItem(IDC_H323_SETUP_CALLED_NUMBER);
	pByGW = GetDlgItem(IDC_H323_SETUP_CALL_VIA_GW);
	pGW = GetDlgItem(IDC_H323_SETUP_GATEWAY_ADDRESS);

	pGkAddr->EnableWindow(m_bViaGK);
	pByName->EnableWindow(m_bViaGK);
	pName->EnableWindow(m_bName);
	pByNo->EnableWindow(m_bViaGK);
	pNo->EnableWindow(m_bNumber);
	pByGW->EnableWindow(!m_bViaGK);
	pGW->EnableWindow(m_bViaGW && !m_bViaGK);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCallAdvSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_bViaGK)
	{
		if(m_strGatekeeper.IsEmpty())
		{
			AfxMessageBox("请您键入一个有效的网守服务器地址");
			return;
		}

		if(!m_bName && !m_bNumber)
		{
			AfxMessageBox("您选择了使用网关守卫但没有指定用什么信息登录网关守卫");
			return;
		}

		if(m_bName)
		{
			if(m_strName.IsEmpty())
			{
				AfxMessageBox("您键入了一个无效的账户名，请检查后重新键入");
				return;
			}
		}

		if(m_bNumber)
		{
			if(m_strNumber.IsEmpty())
			{
				AfxMessageBox("呼叫号码不能为空，请重新键入");
				return;
			}
			int nCount = m_strNumber.GetLength();
			TCHAR ch;
			for(int i = 0; i < nCount; i++)
			{
				ch = m_strNumber.GetAt(i);
				if((ch < '0' && ch != '*' && ch != '#') || ch > '9')
				{
					AfxMessageBox("您键入了无效的号码，请检查后重新键入");
					return;
				}
			}
		}
	}

	CDialog::OnOK();
}
