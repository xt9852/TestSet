#if !defined(AFX_INCOMINGCALLDLG_H__67A72ACE_DD94_4DAA_9562_95602D6F0727__INCLUDED_)
#define AFX_INCOMINGCALLDLG_H__67A72ACE_DD94_4DAA_9562_95602D6F0727__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IncomingCallDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CIncomingCallDlg dialog

class CIncomingCallDlg : public CDialog
{
// Construction
public:
	void ShowTip(LPCTSTR strTip);
	CIncomingCallDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIncomingCallDlg)
	enum { IDD = IDD_DLG_H323_INCOMING_CALL };
	CStatic	m_cIndicator;
	CString	m_strTip;
	//}}AFX_DATA
	HICON m_hIcons[2];
	int m_iIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncomingCallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIncomingCallDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCOMINGCALLDLG_H__67A72ACE_DD94_4DAA_9562_95602D6F0727__INCLUDED_)
