
#include "stdafx.h"
#include "XTEdit.h"
#include ".\xtedit.h"


UINT WM_EDIT_RETURN  = RegisterWindowMessage(_T("WM_EDIT_RETURN"));


IMPLEMENT_DYNAMIC(CXTEdit, CEdit)
CXTEdit::CXTEdit()
{
	m_clrBkg = RGB(187,223,246);
	m_hBrush = (HBRUSH)CreateSolidBrush(m_clrBkg);
}

CXTEdit::~CXTEdit()
{
}


BEGIN_MESSAGE_MAP(CXTEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


void CXTEdit::PreSubclassWindow(void)
{
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	CEdit::PreSubclassWindow();
}

BOOL CXTEdit::PreTranslateMessage(MSG *pMsg)
{
	if ((WM_KEYDOWN == pMsg->message) && (VK_RETURN == pMsg->wParam))
	{
		GetOwner()->PostMessage(WM_EDIT_RETURN, this->GetDlgCtrlID(), NULL);
		return TRUE;
	}

	return CEdit::PreTranslateMessage(pMsg);
}

HBRUSH CXTEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);
	return m_hBrush;
}

void CXTEdit::SetBkgColor(COLORREF clrBkg)
{
	m_clrBkg = clrBkg;
	::DeleteObject(m_hBrush);
	m_hBrush = (HBRUSH)CreateSolidBrush(m_clrBkg);
	this->Invalidate();
}
