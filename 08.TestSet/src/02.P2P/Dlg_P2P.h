#pragma once
#include "P2PFileUpdateApp.h"

typedef std::list<std::string> LIST_STR;

class CDlg_P2P: public CDialog
{
    DECLARE_DYNAMIC(CDlg_P2P)

public:
    CDlg_P2P(CWnd* pParent = NULL); // 标准构造函数
    virtual ~CDlg_P2P();

    // 对话框数据
    enum{ IDD = IDD_2_P2P };

private:
    CTabCtrl  tabCtrl_;
    CListCtrl fileCtrl_;
    CListCtrl taskCtrl_;
    CListCtrl peerCtrl_;
    CListCtrl layoutCtrl_;

    TCHAR     fileListMd5_[MAX_PATH]; // fileList.xml md5 string

    UINT      getTaskTime_;

    XT_P2P::P2PFileUpdateApp    app_;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

    void GetTaskInfo();
    void GetPeerInfo();
    void GetLayoutInfo();

public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnTcnSelchangeP2pTab(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedP2pBtnServer();
    afx_msg void OnBnClickedP2pBtnClient();
    afx_msg void OnBnClickedP2pBtnList();
};
