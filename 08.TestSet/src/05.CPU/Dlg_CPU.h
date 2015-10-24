#pragma once
#include "CPU.h"
#include "ShowData.h"

class CDlg_CPU : public CDialog
{
    DECLARE_DYNAMIC(CDlg_CPU)

public:
    CDlg_CPU(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlg_CPU();

    // Dialog Data
    enum { IDD = IDD_DLG_3_CPU };

private:
    CTabCtrl  m_tabSel;
    CListCtrl m_lstUnasm;
    CListCtrl m_lstMemory;
    CListCtrl m_lstRegister;

    CCPU      m_CPUEmulator;
    CShowData m_ShowData;

    MAP_UINT_STR *m_pmapAsm;
    unsigned char *m_pszMem;

    int  m_nTabShowItem;
    void TabShow(int nItem, int nCmdShow);

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedCpuRun();
    afx_msg void OnBnClickedCpuPause();
    afx_msg void OnBnClickedCpuSinglestep();
    afx_msg void OnBnClickedCpuMicrocodestep();
    afx_msg void OnBnClickedCpuBtnMadeCode();
    afx_msg void OnBnClickedCpuLoad();
    afx_msg void OnBnClickedCpuSave();
};
