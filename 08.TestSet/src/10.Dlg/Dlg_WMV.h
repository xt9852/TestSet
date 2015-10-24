
#pragma once
#include "wmv/PlayWMV.h"
#include "wmv/NetWrite.h"
#include "resource.h"

class CDlg_WMV : public CDialog
{
    DECLARE_DYNAMIC(CDlg_WMV)

public:
    CDlg_WMV(CWnd* pParent = NULL);
    virtual ~CDlg_WMV();

    enum { IDD = IDD_DLG_WMV };

    CString		m_strFileName;
    CPlayWMV	m_PlayWmv;
    CNetWrite	m_StreamWmv;
    HANDLE		m_hThread;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);

    LRESULT GraphEvent(WPARAM,LPARAM);
    static unsigned __stdcall WMVStreamThread(LPVOID pParam);

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedWmvBtnOpen();
    afx_msg void OnBnClickedWmvBtnStart();
    afx_msg void OnBnClickedWmvBtnPause();
    afx_msg void OnBnClickedWmvBtnStop();
    afx_msg void OnBnClickedWmvBtnSound();
    afx_msg void OnBnClickedWmvBtnSize();
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedWmvBtnStream();
};
