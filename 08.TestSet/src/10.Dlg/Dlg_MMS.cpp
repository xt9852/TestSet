// Dlg_MMS.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_MMS.h"
#include ".\dlg_mms.h"


// CDlg_MMS 对话框

IMPLEMENT_DYNAMIC(CDlg_MMS, CDialog)
CDlg_MMS::CDlg_MMS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_MMS::IDD, pParent)
{
}

CDlg_MMS::~CDlg_MMS()
{
}

void CDlg_MMS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_MMS, CDialog)
	ON_BN_CLICKED(IDC_MMS_BUT_START_SERVER, OnBnClickedButStartServer)
	ON_BN_CLICKED(IDC_MMS_BUT_START_CLIENT, OnBnClickedButStartClient)
END_MESSAGE_MAP()


BOOL CDlg_MMS::OnInitDialog()
{
	CDialog::OnInitDialog();

	//--------------------------------------------------------------

	// mms://220.194.63.17/cebeijing8


	GetDlgItem(IDC_MMS_IPADDRESS1)->SetWindowText(g_ProFile.m_strIP);
	GetDlgItem(IDC_MMS_EDIT_PORT)->SetWindowText(_T("1755"));
	GetDlgItem(IDC_MMS_EDIT)->SetWindowText(_T("cebeijing8"));				// MMS协议的虚拟路径，客户请求的文件名

	GetDlgItem(IDC_MMS_BUT_START_CLIENT)->EnableWindow(FALSE);

	//--------------------------------------------------------------	

	return TRUE;
}

void CDlg_MMS::OnBnClickedButStartServer()
{
	CString strIP;
	CString strPort;

	GetDlgItem(IDC_MMS_IPADDRESS1)->GetWindowText(strIP);
	GetDlgItem(IDC_MMS_EDIT_PORT)->GetWindowText(strPort);
	
	BYTE byRet = m_SrvMMS.Start(strIP, _ttoi(strPort));
	if (0 == byRet)
	{
		GetDlgItem(IDC_MMS_BUT_START_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMS_BUT_START_CLIENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_MMS_IPADDRESS1)->SetWindowText(_T("220.194.63.17"));
	}
	else
	{
		CString msg;
		msg.Format(_T("Init IOCP Error\nErrorCode:%d"), byRet);
		MessageBox(msg);
	}
}

void CDlg_MMS::OnBnClickedButStartClient()
{
	CString strIP;
	CString strPort;
	CString strTemp;

	GetDlgItem(IDC_MMS_IPADDRESS1)->GetWindowText(strIP);
	GetDlgItem(IDC_MMS_EDIT_PORT)->GetWindowText(strPort);
	GetDlgItem(IDC_MMS_EDIT)->GetWindowText(strTemp);

	AfxEnableControlContainer();
	if (m_MediaPlayer.Create(NULL, _T("TestPlayer"), WS_CHILD, CRect(10, 60, 410, 460), this, -1))
	{
		if (NULL != m_MediaPlayer.m_pView)
		{
			m_MediaPlayer.ShowWindow(SW_SHOW);
			m_MediaPlayer.SetSource(strTemp);
			m_MediaPlayer.Play();
		}		
	}	

	return;

	BYTE byRet = m_SrvMMS.Connect(strIP, _ttoi(strPort));
	if (0 == byRet)
	{
		GetDlgItem(IDC_MMS_BUT_START_CLIENT)->EnableWindow(FALSE);
		m_SrvMMS.Login();
	}
	else
	{
		CString msg;
		msg.Format(_T("Connect MMS Server Error\nErrorCode:%d"), byRet);
		MessageBox(msg);
	}
}
