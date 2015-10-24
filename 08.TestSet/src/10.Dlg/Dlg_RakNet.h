#pragma once


// CDlg_NakNet 对话框

class CDlg_RakNet : public CDialog
{
	DECLARE_DYNAMIC(CDlg_RakNet)

public:
	CDlg_RakNet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_RakNet();

// 对话框数据
	enum { IDD = IDD_DLG_RAKNET };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRaknetBtnRun();
};
