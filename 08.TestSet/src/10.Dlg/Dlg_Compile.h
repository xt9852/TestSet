#pragma once
#include "UI/Ctrl/XTTreeCtrl.h"


class CDlg_Compile : public CDialog
{
	DECLARE_DYNCREATE(CDlg_Compile)

public:
	CDlg_Compile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Compile();

	enum { IDD = IDD_DLG_COMPILE };

	CXTTreeCtrl m_treRoom;
    CComboBox   m_cbbConfig;

    CStatic     m_staInfo;
    CStatic     m_staName[18];
    CComboBox   m_cbbData[18];

    BOOL        m_bIsLoad;
    int         m_nTreePage;

    //CXmlCompile m_xmlComplie;

protected:
    void SelNewPage(int nNewPage);
    void SetComboData(int nIndex, CString strSelect, CString strValue, int nUse);
    void CleanComboData(int nIndex);
    void CleanConfig(void);
    
    CString GetProjectFileName(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
    LRESULT OnClickTree(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnSetfocusCompileCombo(UINT nIndex);
    afx_msg void OnBnClickedComplieBtnSave();
    afx_msg void OnBnClickedComplieBtnOpen();
    afx_msg void OnBnClickedComplieBtnCreate();
    afx_msg void OnBnClickedComplieBtnMake();
};
