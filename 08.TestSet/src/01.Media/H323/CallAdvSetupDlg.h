#if !defined(AFX_CALLADVSETUPDLG_H__C89D1835_8F3C_4587_A22D_4C95059A768D__INCLUDED_)
#define AFX_CALLADVSETUPDLG_H__C89D1835_8F3C_4587_A22D_4C95059A768D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CallAdvSetupDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CCallAdvSetupDlg dialog

class CCallAdvSetupDlg : public CDialog
{
// Construction
public:
	CCallAdvSetupDlg(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(CCallAdvSetupDlg)
	enum { IDD = IDD_DLG_H323_ADVANCED_SETUP };
	BOOL	m_bViaGK;
	BOOL	m_bName;
	BOOL	m_bNumber;
	CString	m_strName;
	CString	m_strNumber;
	CString	m_strGatekeeper;
	//}}AFX_DATA
	BOOL	m_bViaGW;
	CString m_strGateway;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCallAdvSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCallAdvSetupDlg)
	afx_msg void OnCallByGk();
	afx_msg void OnCallByName();
	afx_msg void OnCallByNumber();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnCallViaGW();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALLADVSETUPDLG_H__C89D1835_8F3C_4587_A22D_4C95059A768D__INCLUDED_)
