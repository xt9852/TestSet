// HtmlCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XTHtmlCtrl.h"


UINT WM_HTML_CLICK = ::RegisterWindowMessage(_T("WM_HTML_CLICK"));


IMPLEMENT_DYNCREATE(CXTHtmlCtrl, CHtmlView)
CXTHtmlCtrl::CXTHtmlCtrl()
	:m_hParentWnd(NULL)
{
}

CXTHtmlCtrl::~CXTHtmlCtrl()
{
}

void CXTHtmlCtrl::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXTHtmlCtrl, CHtmlView)
	ON_WM_DESTROY()
    ON_WM_SIZE()
END_MESSAGE_MAP()



#ifdef _DEBUG
void CXTHtmlCtrl::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CXTHtmlCtrl::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif


int CXTHtmlCtrl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	//return CHtmlView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CXTHtmlCtrl::OnBeforeNavigate2(LPCTSTR lpszURL,
									DWORD nFlags,
									LPCTSTR lpszTargetFrameName,
									CByteArray& baPostedData,
									LPCTSTR lpszHeaders,
									BOOL* pbCancel) 
{
	if (NULL == lpszURL) return;

/*	regex expression("^http://gif([0-9]\{4\})/");

	cmatch what;
	string msg;
	CString strFileName(m_strPath);

	if (regex_match(lpszURL, what, expression))
	{
		*pbCancel = TRUE;
		this->ShowWindow(SW_HIDE);

		msg = what[1].str();

		strFileName += _T("\\GIF\\");
		strFileName += _T(msg.c_str());
		strFileName += _T(".gif");
		
		m_pTextInput->InsertFace(strFileName);
		m_pTextInput->Invalidate();

		if (NULL != m_pTextInfo)
			m_pTextInfo->ShowWindow(SW_SHOW);
	}
*/
		
	CString strUrl(lpszURL);
	int nIndex = strUrl.Find(_T("image://"));
	if (-1 != nIndex)
	{
		*pbCancel = TRUE;

		CString strFileName = strUrl.Mid(nIndex + 8, strUrl.GetLength() - 8 - 1);
		CString strExName = strFileName.Right(3);

		int nType = 0;
		if (strExName.CompareNoCase(_T("gif")) == 0)
			nType = FILE_GIF;
		else if (strExName.CompareNoCase(_T("jpg")) == 0)
			nType = FILE_JPG;
		else if (strExName.CompareNoCase(_T("bmp")) == 0)
			nType = FILE_BMP;

		::SendMessage(m_hParentWnd, WM_HTML_CLICK, (WPARAM)(LPCTSTR)strFileName, (LPARAM)nType);
	}

	return;
}

void CXTHtmlCtrl::PostNcDestroy()
{
	//CHtmlView::PostNcDestroy();
}

void CXTHtmlCtrl::OnDestroy()
{
	//CHtmlView::OnDestroy();
	CWnd::OnDestroy();
}

BOOL CXTHtmlCtrl::CreateFromCtrl(UINT nID, CWnd* pParent)
{
	m_hParentWnd = pParent->GetSafeHwnd();
	
	if (!pParent || !m_hParentWnd) return FALSE;

	CWnd *pCtrl = pParent->GetDlgItem(nID);
	if (!pCtrl)	return FALSE;

	CRect rcCtrl;
	pCtrl->GetWindowRect(rcCtrl);
	pParent->ScreenToClient(rcCtrl);
	UINT style = ::GetWindowLong(pCtrl->GetSafeHwnd(), GWL_STYLE);
	pCtrl->DestroyWindow();

	return Create(NULL, NULL, style | WS_CHILD | WS_VISIBLE, rcCtrl, pParent, nID, NULL);
}

BOOL CXTHtmlCtrl::CreateFromCtrl(CRect rcCtrl, CWnd* pParent)
{
	if (!pParent || !pParent->GetSafeHwnd())
		return FALSE;

	return Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rcCtrl, pParent, 0, NULL);
}

void CXTHtmlCtrl::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);
    if (::IsWindow(m_wndBrowser.m_hWnd))
    {
        CRect rect;
        GetClientRect(rect); // 就这一句与CHtmlView的不同
        ::AdjustWindowRectEx(rect, GetStyle(), FALSE, WS_EX_CLIENTEDGE);
        m_wndBrowser.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER); 
    }
}

