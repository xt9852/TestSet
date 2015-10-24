#pragma once
#include "UI/Ctrl/XTDialog.h"
#include "UI/Ctrl/XTDC.h"
#include "UI/Ctrl/XTEdit.h"
#include "UI/Ctrl/XTButton.h"
#include "UI/Ctrl/XTCheckBox.h"
#include "UI/Ctrl/XTComboBox.h"
#include "UI/Ctrl/XTProgress.h"
#include "UI/Ctrl/XTBackForth.h"

#include "UI/Ctrl/XTFlatComboBox.h"

// CDlg_Skin_Dlg1 对话框

class CDlg_Skin_Dlg1 : public CXTDialog
{
	DECLARE_DYNAMIC(CDlg_Skin_Dlg1)

public:
	CDlg_Skin_Dlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Skin_Dlg1();

// 对话框数据
	enum { IDD = IDD_DLG_UI_LO };

private:
	
	CXTButton		m_btnExit;
	CXTButton		m_btnLogin;
	CXTButton		m_btnCancel;
	CXTButton		m_btnRegister;
	CXTButton		m_btnCLean;
	CXTButton		m_btnKeyBoard;
	CXTCheckBox		m_btnSavePassword;
	CXTCheckBox		m_btnAutoLogin;
	CXTComboBox		m_ComboBoxServer;
	CXTComboBox		m_ComboBoxUser;
	CXTEdit			m_editPass;
	CXTProgress		m_Progress;
	CXTBackForth	m_ProgressEx;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoBtRegister();
	afx_msg void OnBnClickedLoBtClean();
	afx_msg void OnBnClickedLoBtKeyboard();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLoBtExit();
	afx_msg void OnBnClickedLoBtSavePassword();
	afx_msg void OnBnClickedLoBtAutoLogin();
};
