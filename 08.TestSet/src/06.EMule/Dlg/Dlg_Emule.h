#pragma once

#include "03.Network\Pinger.h"
#include "Dlg_Emule_KAD.h"
#include "Dlg_Emule_Search.h"


// CDlg_Emule 对话框

class CDlg_Emule: public CDialog
{
    DECLARE_DYNAMIC(CDlg_Emule)

public:
    CDlg_Emule(CWnd* pParent = NULL); // 标准构造函数
    virtual ~CDlg_Emule();

    // 对话框数据
    enum{ IDD = IDD_DLG_EMULE };

private:
    Pinger              m_Ping;

    CTabCtrl            m_Tab;
    CDialog             *m_pLastDlg;    // 存上一次显示的窗体
    CDlg_Emule_KAD      m_DlgKAD;       // KAD窗体
    CDlg_Emule_Search   m_DlgSearch;    // 查询窗体


protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedEmuleButPing();
    afx_msg void OnTcnSelchangeEmuleTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
