// H323Dlg.h : header file
//

#if !defined(AFX_H323DLG_H__29FCA6C7_8590_461B_B60D_CF02C9F5A909__INCLUDED_)
#define AFX_H323DLG_H__29FCA6C7_8590_461B_B60D_CF02C9F5A909__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "H323\CallingDlg.h"
#include "H323\IncomingCallDlg.h"

struct Q931Message;
int HandleCommand();


#define WM_USER_INCOMINGCALL	WM_USER + 1001
#define WM_USER_RECVRCF			WM_USER + 1002
#define WM_USER_RECVACF			WM_USER	+ 1004
#define WM_USER_RECVCONNECT		WM_USER + 1005
#define WM_USER_SENDCONNECT		WM_USER + 1006
#define WM_USER_RECVReleaseComplete WM_USER+1007
/////////////////////////////////////////////////////////////////////////////
// CH323Dlg dialog

class CDlg_H323 : public CDialog
{
// Construction
public:
	CDlg_H323(CWnd* pParent = NULL);			// standard constructor
	virtual ~CDlg_H323();// standard deconstructor

	void CallSetup();
	void RegistrationRequest();
	void AdmissionRequest();
	void DisengageRequest();
	void UnregistrationRequest();
	BOOL IsAutoAnswer();
	BOOL DoNotBother();

	BOOL m_bAsCaller;	//TRUE: Ö÷½Ð FALSE: ±»½Ð
	BOOL m_bRegistered;
// Dialog Data
	//{{AFX_DATA(CH323Dlg)
	enum { IDD = IDD_DLG_H323 };
	CListCtrl	m_cParties;
	CString	m_strCalled;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CH323Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL m_bAutoAnswer;
	BOOL m_bDoNotBother;

	//tony add 2004/11/24
	BOOL m_bViaGK;
	CString m_strGatekeeper;
	BOOL m_bName;
	CString m_strName;
	BOOL m_bNumber;
	CString m_strNumber;
	BOOL m_bViaGW;
	CString m_strGateway;
	int m_nDestStrType;	//ºô½Ð×Ö´®ÀàÐÍ 0: IPµØÖ· 1: ºÅÂë 2: ÕËºÅ

	CCallingDlg *m_pCallingDlg;
	CIncomingCallDlg *m_pInCallDlg;

	int Listen();
	// Generated message map functions
	//{{AFX_MSG(CH323Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMakecall();
	afx_msg void OnHangup();
	afx_msg void OnClose();
	afx_msg void OnCallAdvanceSetup();
	afx_msg void OnDonotBother();
	afx_msg void OnAutoAnswer();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

// XT-20110328
// 	afx_msg void OnIncomingCall(WPARAM wParam,LPARAM lParam);
// 	afx_msg void OnRecvRCF(WPARAM wParam,LPARAM lParam);
// 	afx_msg void OnRecvACF(WPARAM wParam,LPARAM lParam);
// 	afx_msg void OnRecvConnect(WPARAM wParam,LPARAM lParam);
// 	afx_msg void OnSendConnect(WPARAM wParam,LPARAM lParam);
// 	afx_msg void OnRecvReleaseComplete(WPARAM wParam,LPARAM lParam);

    // XT+20110328
    LRESULT OnIncomingCall(WPARAM wParam,LPARAM lParam);
    LRESULT OnRecvRCF(WPARAM wParam,LPARAM lParam);
    LRESULT OnRecvACF(WPARAM wParam,LPARAM lParam);
    LRESULT OnRecvConnect(WPARAM wParam,LPARAM lParam);
    LRESULT OnSendConnect(WPARAM wParam,LPARAM lParam);
    LRESULT OnRecvReleaseComplete(WPARAM wParam,LPARAM lParam);
private:
	HANDLE m_hMonitorThread;
	void SaveIpAddr();
	void SaveAdvSetup();
	void Loadini();
	int WhatTypeIsDestStr(CString strCalled);
	void PopupCallingDlg();
	void CloseCallingDlg();
	void AddParty(LPCTSTR strName);

	CImageList m_Imgs;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_H323DLG_H__29FCA6C7_8590_461B_B60D_CF02C9F5A909__INCLUDED_)
