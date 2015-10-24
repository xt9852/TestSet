
#include "stdafx.h"
#include "XTOutBarEdit.h"
#include "XTOutBarCtrl.h"


extern UINT WM_OUTBAR_NOTIFY;


CXTOuBarEdit::CXTOuBarEdit()
{
	m_bEscapeKey = FALSE;
	m_nIndex = -1;
	m_msgSend = NM_OB_ONGROUPENDEDIT;
	m_bNoDown = false;
}

CXTOuBarEdit::~CXTOuBarEdit()
{
}


BEGIN_MESSAGE_MAP(CXTOuBarEdit, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CXTOuBarEdit::OnKillFocus(CWnd* pNewWnd) 
{
	PostMessage(WM_CLOSE, 0, 0);
	if (!m_bEscapeKey)
	{
		GetWindowText(m_strText);
		if (m_strText != _T("")) GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, m_msgSend, (LPARAM)this);
	}
}

BOOL CXTOuBarEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->wParam == VK_RETURN)
	{
		PostMessage(WM_CLOSE, 0, 0);
		return TRUE;
	}
	else if (pMsg->wParam == VK_ESCAPE)
	{
		PostMessage(WM_CLOSE, 0, 0);
		return m_bEscapeKey = TRUE;
	}
	
	return CEdit::PreTranslateMessage(pMsg);
}

void CXTOuBarEdit::PostNcDestroy() 
{
	CEdit::PostNcDestroy();
	delete this;
}

int CXTOuBarEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SendMessage(WM_SETFONT,(WPARAM) GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(TRUE,0));
	return 0;
}

void CXTOuBarEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (m_msgSend == NM_OB_ONGROUPENDEDIT)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	if (nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if (nChar == VK_ESCAPE) m_bEscapeKey = TRUE;
		GetParent()->SetFocus();
		return;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	CString str;
	CRect rect, parentrect;
	GetClientRect(&rect);
	GetParent()->GetClientRect(&parentrect);
	ClientToScreen(&rect);
	GetParent()->ScreenToClient(&rect);
	GetWindowText(str);
	CWindowDC dc(this);
	CFont *pFont = GetParent()->GetFont();
	CFont *pFontDC = dc.SelectObject(pFont);
	CRect szrc(rect);
	szrc.bottom = szrc.top;

	if (m_bNoDown == true)
	{
		dc.DrawText(str, szrc, DT_CALCRECT);
		if (szrc.right >= parentrect.right - 1) rect.right = parentrect.right - 1;
		else rect.right = szrc.right;
		MoveWindow(&rect);
		return;
	}

	dc.DrawText(str, szrc, DT_WORDBREAK|DT_CENTER|DT_CALCRECT);
	dc.SelectObject(pFontDC);
	CSize size = szrc.Size();

	if (size.cx > rect.Width())
	{
		if (size.cx + rect.left < parentrect.right) rect.right = rect.left + size.cx;
		else rect.right = parentrect.right;
		MoveWindow(&rect);
	}
	else if (size.cy > rect.Height())
	{
		if (size.cy + rect.bottom < parentrect.bottom) rect.bottom = rect.top + size.cy;
		else rect.bottom = parentrect.bottom;
		MoveWindow(&rect);
	}
}
