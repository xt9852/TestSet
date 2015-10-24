#if !defined(AFX_CALLINGDLG_H__8F4559C5_5EAC_4917_8505_65088C1EC587__INCLUDED_)
#define AFX_CALLINGDLG_H__8F4559C5_5EAC_4917_8505_65088C1EC587__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CallingDlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CCallingDlg dialog

class CCallingDlg : public CDialog
{
// Construction
public:
	CCallingDlg(CWnd* pParent = NULL);   // standard constructor
	void ShowTip(LPCTSTR strTip);

// Dialog Data
	//{{AFX_DATA(CCallingDlg)
	enum { IDD = IDD_DLG_H323_CALLING };
	CString	m_strTip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCallingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCallingDlg)
	afx_msg void OnCancelCall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALLINGDLG_H__8F4559C5_5EAC_4917_8505_65088C1EC587__INCLUDED_)
