// src\Dlg\Dlg_Skin_Dlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_Skin_Dlg1.h"


// CDlg_Skin_Dlg1 对话框

IMPLEMENT_DYNAMIC(CDlg_Skin_Dlg1, CDialog)
CDlg_Skin_Dlg1::CDlg_Skin_Dlg1(CWnd* pParent /*=NULL*/)
	:CXTDialog(CDlg_Skin_Dlg1::IDD, pParent)
{	
}

CDlg_Skin_Dlg1::~CDlg_Skin_Dlg1()
{
}

void CDlg_Skin_Dlg1::DoDataExchange(CDataExchange* pDX)
{
	CXTDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LO_BT_EXIT,				m_btnExit);
	DDX_Control(pDX,IDOK,						m_btnLogin);
	DDX_Control(pDX,IDCANCEL,					m_btnCancel);
	DDX_Control(pDX,IDC_LO_BT_REGISTER,			m_btnRegister);
	DDX_Control(pDX,IDC_LO_BT_CLEAN,			m_btnCLean);
	DDX_Control(pDX,IDC_LO_BT_KEYBOARD,			m_btnKeyBoard);
	DDX_Control(pDX,IDC_LO_BT_SAVE_PASSWORD,	m_btnSavePassword);
	DDX_Control(pDX,IDC_LO_BT_AUTO_LOGIN,		m_btnAutoLogin);
	DDX_Control(pDX,IDC_LO_COMBO_SELECT_USER,	m_ComboBoxUser);
	DDX_Control(pDX,IDC_LO_COMBO_MANAGE_SERVER,	m_ComboBoxServer);
	DDX_Control(pDX,IDC_LO_EDIT_INPUT_PASSWORD, m_editPass);
}


BEGIN_MESSAGE_MAP(CDlg_Skin_Dlg1, CXTDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK,							OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,						OnBnClickedLoBtExit)
	ON_BN_CLICKED(IDC_LO_BT_EXIT,				OnBnClickedLoBtExit)
	ON_BN_CLICKED(IDC_LO_BT_CLEAN,				OnBnClickedLoBtClean)
	ON_BN_CLICKED(IDC_LO_BT_REGISTER,			OnBnClickedLoBtRegister)
	ON_BN_CLICKED(IDC_LO_BT_KEYBOARD,			OnBnClickedLoBtKeyboard)
	ON_BN_CLICKED(IDC_LO_BT_AUTO_LOGIN,			OnBnClickedLoBtAutoLogin)
	ON_BN_CLICKED(IDC_LO_BT_SAVE_PASSWORD,		OnBnClickedLoBtSavePassword)
END_MESSAGE_MAP()

BOOL CDlg_Skin_Dlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitBkgBmp(306+1, 236+1, 15, IDB_UI_PNG_LOGIN);

	m_btnExit.Initial(       283,   3,  18,  18,   0, 243, &xtDC_, "退出");
	m_btnLogin.Initial(      149, 209,  68,  18,   0, 295, &xtDC_, "登录");
	m_btnCancel.Initial(     223, 209,  68,  18,   0, 315, &xtDC_, "退出");
	m_btnRegister.Initial(   218, 107,  68,  18,   0, 335, &xtDC_, "注册用户");
	m_btnCLean.Initial(      218, 134,  68,  18,   0, 355, &xtDC_, "清除用户");
	m_btnKeyBoard.Initial(   218, 160,  68,  18,   0, 375, &xtDC_, "软键盘");
	m_btnSavePassword.Initial(60, 184,  63,  11,   0, 269, &xtDC_, "记住密码");
	m_btnAutoLogin.Initial(  145, 184,  63,  11,   0, 282, &xtDC_, "自动登录");
	m_ComboBoxServer.Initial( 93, 104, 116, 100,  56, 243, &xtDC_);
	m_ComboBoxUser.Initial(   93, 131, 116, 100,  56, 243, &xtDC_);
	m_editPass.MoveWindow(    94, 158, 114,  21);
	m_Progress.Initial(       10, 210, 120,  15, 102, 243, &xtDC_);
	m_ProgressEx.Initial(      9,  91,  17,   6,  16,   6, 1, 0, 236, &xtDC_);
	m_ProgressEx.SetDlgWnd(this->GetSafeHwnd());

	this->DelRect(93, 104, 116, 21);
	this->DelRect(93, 132, 116, 21);
	this->DelRect(94, 158, 114, 21);

	this->SetTimer(0, 1000, NULL);

	//----------------------------------------------------

	//m_ComboBoxUser.EnableAutoCompletion();
	
	for (int i = 0; i < 10; i++)
	{
		CString str;
		str.Format(_T("你好 ABC %d"), i);
		m_ComboBoxServer.InsertString(i, str);
		m_ComboBoxUser.InsertString(i, str);
	}

	//----------------------------------------------------

	return TRUE;
}

//绘登录窗体上的动画
void CDlg_Skin_Dlg1::OnTimer(UINT nIDEvent)
{
	//现在背景DC中装入的是登录的动画

	static int nCount = 0;

	if (++nCount %= 101)
		m_Progress.DrawImage(nCount, "你好啊!");

	static bool bShowOne = false;

	if (bShowOne)
	{
		::BitBlt(dc_, 6, 29, 294, 56, imageDC_, 6, 29, SRCCOPY);
		::BitBlt(compDC_, 6, 29, 294, 56, imageDC_, 6, 29, SRCCOPY);
		bShowOne = false;
	}
	else
	{
		::BitBlt(dc_, 6, 29, 294, 56, imageDC_, 0, 395, SRCCOPY);
		::BitBlt(compDC_, 6, 29, 294, 56, imageDC_, 0, 395, SRCCOPY);
		bShowOne = true;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlg_Skin_Dlg1::OnBnClickedLoBtRegister()
{
	m_ProgressEx.Success();
}

void CDlg_Skin_Dlg1::OnBnClickedLoBtClean()
{
	m_editPass.SetWindowText(_T(""));
}

void CDlg_Skin_Dlg1::OnBnClickedLoBtKeyboard()
{
	BOOL bEnable = m_btnRegister.IsWindowEnabled();
	m_btnRegister.EnableWindow(!bEnable);
}

void CDlg_Skin_Dlg1::OnBnClickedOk()
{
	m_ProgressEx.Start();
}

void CDlg_Skin_Dlg1::OnBnClickedLoBtExit()
{
	m_ProgressEx.Stop();
	OnCancel();
}

void CDlg_Skin_Dlg1::OnBnClickedLoBtSavePassword()
{
}

void CDlg_Skin_Dlg1::OnBnClickedLoBtAutoLogin()
{
}
