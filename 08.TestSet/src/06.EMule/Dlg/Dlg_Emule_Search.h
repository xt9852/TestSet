
#pragma once
//#include "eMule/UI/SearchListCtrl.h"


class CDlg_Emule_Search : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Emule_Search)

public:
    CDlg_Emule_Search(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_Emule_Search();

    enum { IDD = IDD_DLG_EMULE_SEARCH };

private:

    //CSearchListCtrl searchlistctrl;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedSearchBtnStart();
};
