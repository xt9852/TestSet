
#pragma once

#include "XTRichEdit.h"
#include "afxhtml.h"

//#include <boost/regex.hpp>
//using namespace boost;
enum {FILE_GIF = 1, FILE_JPG, FILE_BMP, FILE_DOC};

class CXTHtmlCtrl : public CHtmlView
{
	DECLARE_DYNCREATE(CXTHtmlCtrl)

public:
	CXTHtmlCtrl();
	virtual ~CXTHtmlCtrl();

	HWND	m_hParentWnd;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
    virtual void PostNcDestroy();

    DECLARE_MESSAGE_MAP()
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnDestroy();

public:
    BOOL CreateFromCtrl(UINT nID, CWnd* pParent);
	BOOL CreateFromCtrl(CRect rcCtrl, CWnd* pParent);
	void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, 
		CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
};


