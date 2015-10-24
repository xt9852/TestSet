
#pragma once
// #include "emule\UI\KadContactListCtrl.h"
// #include "emule\UI\KadSearchListCtrl.h"
// #include "emule\UI\KadContactHistogramCtrl.h"
// #include "emule\XTIP2Country.h"



class CDlg_Emule_KAD : public CDialog
{
	DECLARE_DYNAMIC(CDlg_Emule_KAD)

public:
	CDlg_Emule_KAD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Emule_KAD();

	enum { IDD = IDD_DLG_EMULE_KAD };

private:
// 	CKadContactListCtrl         m_ContactListCtrl;
// 	CKadSearchListCtrl          m_SearchListCtrl;
// 	CKadContactHistogramCtrl    m_HistogramCtrl;
// 	CXTIP2Country               m_IP2Country;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg long OnIp2CountryNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBootstrapbutton();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedKadStop();
};
