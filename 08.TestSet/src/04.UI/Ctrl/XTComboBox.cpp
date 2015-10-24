
#include "stdafx.h"
#include "XTDC.h"
#include "XTComboBox.h"
#include ".\xtcombobox.h"

#define CB_STATE_NORMAL     0
#define CB_STATE_HOTTRACK   1
#define CB_STATE_PRESSED    2
#define CB_STATE_DISABLE    3


UINT WM_COMBOBOX_SEL = RegisterWindowMessage(_T("WM_COMBOBOX_SEL"));	// combobax 控件当前选择的行


CXTComboBox::CXTComboBox()
	:m_bMouseTracking(FALSE),
	m_clrBkg(RGB(187,223,246)),
	m_clr3DHilight(RGB(133,228,255)),
	m_clr3DShadow(RGB(207,222,234)),
	m_clr3DFace(RGB(78,160,209)),
	m_hbrBkg(NULL),
	m_bDisableAC(FALSE),
	m_bFlatLook(TRUE),
	m_bLBtnDown(FALSE),
	m_bPainted(FALSE),
	m_bHasFocus(FALSE),
	m_bAutoComp(FALSE),
	m_bClicked(FALSE)
{
	m_hbrDisabled  = (HBRUSH)CreateSolidBrush(RGB(0,255,255));
	m_hbrHighlight = (HBRUSH)CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
	m_cxHThumb = ::GetSystemMetrics(SM_CXHTHUMB);
	
	LOGFONT lf  = {0};
	lf.lfHeight = 15;
	m_Font.CreateFontIndirect(&lf);	
}

CXTComboBox::~CXTComboBox()
{
	if (NULL != m_memDC.GetSafeHdc())
	{
		m_memDC.DeleteDC();
		m_memBmp.DeleteObject();
	}
}

IMPLEMENT_DYNAMIC(CXTComboBox, CComboBox)
BEGIN_MESSAGE_MAP(CXTComboBox, CComboBox)
	ON_WM_PAINT()
	
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnCbnSelchange)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


bool CXTComboBox::Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *xtDC)
{
	if (NULL == xtDC) return false;

	sx_ = sx;
	sy_ = sy;
	xtDC_ = xtDC;
	imageDC_ = xtDC_->GetHDC(IMAGEDC, 0);

	MoveWindow(x, y, cx, cy);
	SetImage();

	return true;
}

void CXTComboBox::OnCbnSelchange()
{
	int nCurSel = GetCurSel();

	CWnd *pWnd = GetParent();
	if (NULL != pWnd)
		::SendMessage(pWnd->GetSafeHwnd(), WM_COMBOBOX_SEL, (WPARAM)GetSafeHwnd(), nCurSel);
}

// 子类化 
void CXTComboBox::PreSubclassWindow()
{ 
	this->ModifyStyleEx(WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME | WS_EX_STATICEDGE, 0, SWP_FRAMECHANGED);
	CComboBox::PreSubclassWindow();
}

// 设置尺寸 
void CXTComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{ 
	lpMeasureItemStruct->itemHeight = 12;
}

// 自绘
void CXTComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	if (!IsWindowEnabled())
	{
		DrawItemText(lpDIS, m_hbrDisabled);
		return;
	}

	// Selected
	if ((lpDIS->itemState & ODS_SELECTED) 
		&& (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		DrawItemText(lpDIS, m_hbrHighlight);
		return;
	}

	// De-Selected
	if (!(lpDIS->itemState & ODS_SELECTED) 
		&& (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		DrawItemText(lpDIS, m_hbrBkg);
	}

	// Focus
	if (lpDIS->itemAction & ODA_FOCUS) 
		::DrawFocusRect(lpDIS->hDC, &lpDIS->rcItem);
}

void CXTComboBox::DrawItemText(LPDRAWITEMSTRUCT lpDIS, HBRUSH bBrush)
{
	if (lpDIS->itemID != -1)
	{
		::FillRect(lpDIS->hDC, &lpDIS->rcItem, bBrush);

		CString strItem;
		GetLBText(lpDIS->itemID, strItem);
		int nOldMod = ::SetBkMode(lpDIS->hDC, TRANSPARENT);
		::DrawText(lpDIS->hDC, strItem, strItem.GetLength(), &(lpDIS->rcItem), DT_SINGLELINE);
		::SetBkMode(lpDIS->hDC, nOldMod);
	}
}

void CXTComboBox::DrawCombo(CDC* pDC, STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
}

void CXTComboBox::OnPaint()
{
	if (NULL == xtDC_) return;

	CPaintDC dc(this);

	int nSel = 0;

	if (m_bClicked)
		nSel = 2;
	else if (this->PointInRect())
		nSel = 1;
	
	dc.BitBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), &m_memDC, 0, m_rcClient.Height() * nSel, SRCCOPY);
}

void CXTComboBox::SetImage(void)
{
	if (NULL == xtDC_) return;

	if (NULL != m_memDC.GetSafeHdc())
	{
		m_memDC.DeleteDC();
		m_memBmp.DeleteObject();
	}	

	CPaintDC dc(this);

	GetClientRect(&m_rcClient);

	m_memBmp.CreateCompatibleBitmap(&dc, m_rcClient.Width(), m_rcClient.Height()*3);
	
	m_memDC.CreateCompatibleDC(&dc);
	m_memDC.SetMapMode(dc.GetMapMode());
	m_memDC.SelectObject(&m_memBmp);

	CRect rcItem(m_rcClient);
	m_memDC.Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
	rcItem.DeflateRect(1,1);
	m_memDC.Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
	rcItem.DeflateRect(1,1);
	m_memDC.Draw3dRect(rcItem, m_clr3DShadow, m_clr3DShadow);
	rcItem.left = rcItem.right - 15 - 2;
	m_memDC.Draw3dRect(rcItem, m_clr3DShadow, m_clr3DShadow);

	m_rcItem = rcItem;

	rcItem.left = m_rcClient.left;
	rcItem.right = m_rcClient.right;
	rcItem.top  = m_rcClient.top + m_rcClient.Height();
	rcItem.bottom = rcItem.top + m_rcClient.Height();

	m_memDC.Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
	rcItem.DeflateRect(1,1);
	m_memDC.Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
	rcItem.DeflateRect(1,1);
	m_memDC.Draw3dRect(rcItem, m_clr3DShadow, m_clr3DShadow);
	rcItem.left = rcItem.right - 15 - 2;
	m_memDC.Draw3dRect(rcItem, m_clr3DShadow, m_clr3DShadow);

	rcItem.left = m_rcClient.left;
	rcItem.right = m_rcClient.right;
	rcItem.top  = m_rcClient.top + m_rcClient.Height() * 2;
	rcItem.bottom = rcItem.top + m_rcClient.Height();

	m_memDC.Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
	rcItem.DeflateRect(1,1);
	m_memDC.Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
	rcItem.DeflateRect(1,1);
	m_memDC.Draw3dRect(rcItem, m_clr3DShadow, m_clr3DShadow);
	rcItem.left = rcItem.right - 15 - 2;
	m_memDC.Draw3dRect(rcItem, m_clr3DShadow, m_clr3DShadow);

	::BitBlt(m_memDC.GetSafeHdc(), m_rcClient.right-15-3, 3, 15, 15, imageDC_, sx_, sy_, SRCCOPY);
	::BitBlt(m_memDC.GetSafeHdc(), m_rcClient.right-15-3, 3 + m_rcClient.Height(), 15, 15, imageDC_, sx_+15, sy_, SRCCOPY);
	::BitBlt(m_memDC.GetSafeHdc(), m_rcClient.right-15-3, 3 + m_rcClient.Height() * 2, 15, 15, imageDC_, sx_+15*2, sy_, SRCCOPY);
}

void CXTComboBox::ResetImage(int sx, int sy)
{
	if (-1 != sx) sx_ = sx;
	if (-1 != sy) sy_ = sy;

	imageDC_ = xtDC_->curImageDC_;

	SetImage();
	Invalidate();
}

void CXTComboBox::SetBkgColor(COLORREF clrBkg)
{
	m_clrBkg = clrBkg;
	DeleteObject(m_hbrBkg);
	m_hbrBkg = (HBRUSH)CreateSolidBrush(m_clrBkg);
	Invalidate();
}

HBRUSH CXTComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	if (NULL != m_hbrBkg)
		return m_hbrBkg;
	else
		return hbr;
}

void CXTComboBox::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT stTRACKMOUSEEVENT = {0};
	stTRACKMOUSEEVENT.cbSize    =  sizeof(TRACKMOUSEEVENT);
	stTRACKMOUSEEVENT.hwndTrack = m_hWnd;
	stTRACKMOUSEEVENT.dwFlags   = TME_LEAVE;
	_TrackMouseEvent(&stTRACKMOUSEEVENT);

	InvalidateRect(&m_rcItem);

	__super::OnMouseMove(nFlags, point);
}

LRESULT CXTComboBox::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bClicked = FALSE;
	InvalidateRect(&m_rcItem);
	return 0;
}

void CXTComboBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (PointInRectClick()) m_bClicked = TRUE;

	__super::OnLButtonDown(nFlags, point);
}

void CXTComboBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bClicked = FALSE;

	__super::OnLButtonUp(nFlags, point);
}
