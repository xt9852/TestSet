
#pragma once
#include "resource.h"
#include "Common/ShellContextMenu.h"

class CDlg_Other : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Other)

public:
    CDlg_Other(CWnd* pParent = NULL);
    virtual ~CDlg_Other();

    enum { IDD = IDD_DLG_OTHER };

    int func(int x);

    int m_nHotKeyID;

	HANDLE m_hInWrite;
	HANDLE m_hInRead; // in相对于被调用的程序
	HANDLE m_hOutRead;
	HANDLE m_hOutWrite;

	/**
	 *\fn         WorkThread()
	 *\brief      线程函数。
	 *\param[in]  param 线程参数。
	 *\return     线程退出码。
	 */
	static unsigned __stdcall WorkThread(void* param);

	/**
	 *\fn         WorkThreadProc()
	 *\brief      线程函数。
	 */
	void WorkThreadProc();

    void SetTransparent(BYTE byTrans);

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
public:
    afx_msg LONG OnHotKey(WPARAM wParam,LPARAM lParam);
    afx_msg void OnBnClickedOtherBtnOpen(); 
    afx_msg void OnBnClickedOtherBtnOSbit();
    afx_msg void OnBnClickedOtherBtnDisk();
    afx_msg void OnBnClickedOtherBtnCp();
    afx_msg void OnBnClickedOtherBtnDmp();
    afx_msg void OnBnClickedOtherBtnAsm();
    afx_msg void OnBnClickedOtherBtnAsmC();
    afx_msg void OnBnClickedOtherBtnPrint();
    afx_msg void OnBnClickedOtherBtnCompile();
    afx_msg void OnBnClickedOtherBtnLoaddll();
    afx_msg void OnBnClickedOtherBtnGuid();
    afx_msg void OnBnClickedOtherBtnDesktop();
    afx_msg void OnBnClickedOtherBtnProcess();
	afx_msg void OnBnClickedOtherBtnHotkey();
	afx_msg void OnBnClickedOtherBtnVfunc();
	afx_msg void OnBnClickedOtherBtnPipe();
	afx_msg void OnBnClickedOtherBtnPipe2();
    afx_msg void OnBnClickedOtherBtnScript();
    afx_msg void OnBnClickedOtherBtnNtfs();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedOtherBtnBsdiff();
    afx_msg void OnBnClickedOtherBtnLua();
};
