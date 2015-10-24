#pragma once

#include "11.Common\SystemTray.h"

enum
{
    DLG_FINGER,         // 指纹识别
    DLG_MEDIA,          // 多媒体
    DLG_P2P,            // P2P软件升级
    DLG_NETWORK,        // 网络
    DLG_UI,             // 界面
    DLG_CPU,            // 虚拟CPU
    DLG_EMULE,          // 电驴
    DLG_DATABASE,       // 数据库
    DLG_ALGORITHM,      // 算法
    DLG_ALL,            // 结束标记
};


class CDlg_Main : public CDialog
{

public:
    CDlg_Main(CWnd* pParent = NULL);
    enum { IDD = IDD_MAIN };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

private:
    CComboBox           comboMain_;        // 下拉框
    CSystemTray         sysTray_;          // 任务栏图标

    CDialog             *curDlg_;         // 存当前显示的窗体
    CDialog             *dlg_[DLG_ALL];   // 所有窗体

protected:
    HICON m_hIcon;
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

    void SetTransparent(BYTE byTrans);
    CDialog* NewDlg(int nIndex, int &nID);

public:
    LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
    afx_msg void OnDestroy();
    afx_msg void OnMenuShow();
    afx_msg void OnMenuExit();
    afx_msg void OnMenuAutorun();
    afx_msg void OnMenuCloseMin();
    afx_msg void OnSelchangeComboMain();
    afx_msg void OnBnClickedMainBtnCreate();
};
