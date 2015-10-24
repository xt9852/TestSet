// XTButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XTButton.h"
#include "XTDC.h"


IMPLEMENT_DYNAMIC(CXTButton, CWnd)
CXTButton::CXTButton()
{
	toolTip_.m_hWnd = NULL;
}

CXTButton::~CXTButton()
{
	if (toolTip_.m_hWnd != NULL && toolTip_.GetToolCount() > 0)
	{
		toolTip_.DelTool(this, 1);
	}
}

BEGIN_MESSAGE_MAP(CXTButton, CWnd)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE()	
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
	ON_WM_MOVE()
END_MESSAGE_MAP()

void CXTButton::PreSubclassWindow() 
{
	ModifyStyle(0, BS_OWNERDRAW);
	CWnd::PreSubclassWindow();
}

LRESULT CXTButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (IsWindowEnabled())
	{
		DrawImage(DLGDC, OK);
	}

	return 0;
}

void CXTButton::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT stTRACKMOUSEEVENT = {0};
	stTRACKMOUSEEVENT.cbSize    =  sizeof(TRACKMOUSEEVENT);
	stTRACKMOUSEEVENT.hwndTrack = m_hWnd;
	stTRACKMOUSEEVENT.dwFlags   = TME_LEAVE;
	_TrackMouseEvent(&stTRACKMOUSEEVENT);

	DrawImage(DLGDC, (nFlags == MK_LBUTTON) ? MOUSE_DOWN : MOUSE_ON);

	CWnd::OnMouseMove(nFlags, point);
}

BOOL CXTButton::PreTranslateMessage(MSG* pMsg)
{
	if(NULL != toolTip_.m_hWnd)
	{
		toolTip_.RelayEvent(pMsg);
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CXTButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	DrawImage(DLGDC, MOUSE_DOWN);
	CWnd::OnLButtonDown(nFlags, point);
}

void CXTButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	DrawImage(DLGDC, OK);
	CWnd::OnLButtonUp(nFlags, point);
}

void CXTButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
}

void CXTButton::DrawImage(UINT nObject, UINT nState/* = OK*/)
{
	if (NULL == xtDC_) return;

	switch (nObject)
	{
	case DLGDC:
		BitBlt(dc_, x_, y_, cx_, cy_, imageDC_, sx_ + nState * cx_, sy_, SRCCOPY);
		break;
	case COMPDC:
		BitBlt(compDC_, x_, y_, cx_, cy_, imageDC_, sx_ + nState * cx_, sy_, SRCCOPY);
		break;
	case COMPTODLG:
		BitBlt(dc_, x_, y_, cx_, cy_, compDC_, x_, y_, SRCCOPY);
		break;
    case CLEAR:
        BitBlt(dc_, x_, y_, cx_, cy_, imageDC_, x_, y_, SRCCOPY);
        BitBlt(compDC_, x_, y_, cx_, cy_, imageDC_, x_, y_, SRCCOPY);
        break;
	default:
		break;
	}
}

BOOL CXTButton::OnEraseBkgnd(CDC* pDC)
{
	// Don't draw back ground
	//return CButton::OnEraseBkgnd(pDC);
	return TRUE;
}

void CXTButton::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable(bEnable);

	DrawImage(COMPDC, bEnable?OK:DISABLE);
	DrawImage(COMPTODLG);
}

/**
	Init button
	All param is input

	x,  y			left top point position
	cx, cy			button width height
	sx, sy			button image left top point position in pix file
	pxtDC			double buff DC
	lpszToolTipText	button text info
	bCheckBox		is CheckBox
	bIsCheckBoxTrue	is checked(if is CheckBox)
*/
bool CXTButton::Initial(int x, int y,
						int cx, int cy,
						int sx, int sy,
						CXTDC *xtDC,
						const char *text)
{
	if (xtDC == NULL || text == NULL) return false;

	x_  = x;
	y_  = y;
	cx_ = cx;
	cy_ = cy;
	sx_ = sx;
	sy_ = sy;

	xtDC_    = xtDC;
	dc_      = xtDC_->GetHDC(WNDDC, 0);
	compDC_  = xtDC_->GetHDC(COMPDC, 0);
	imageDC_ = xtDC_->GetHDC(IMAGEDC, 0);

	MoveWindow(x, y, cx, cy, 0);	
	DrawImage(COMPDC, OK);
	DrawImage(COMPTODLG);

	// set button text info
	if (toolTip_.m_hWnd == NULL)
		toolTip_.Create(this);

	if (toolTip_.GetToolCount() > 0)
		toolTip_.DelTool(this, 1);

	if (!toolTip_.AddTool(this, text))
		return false;

	toolTip_.Activate(TRUE);

	return true;
}

// -1主要用于当DC中的图片更改时刷新CXTButton的图片
void CXTButton::ResetImage(int sx, int sy)
{
	if (-1 != sx) sx_ = sx;
	if (-1 != sy) sy_ = sy;

	imageDC_ = xtDC_->GetCurImageDC();

	DrawImage(DLGDC,  OK);
	DrawImage(COMPDC, OK);
}

void CXTButton::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CWnd::OnShowWindow(bShow, nStatus);

    if (bShow)
    {
        DrawImage(DLGDC,  OK);
        DrawImage(COMPDC, OK);
    }
    else
    {
        DrawImage(CLEAR);
    }
}

void CXTButton::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);

	x_ = x;
	y_ = y;

	DrawImage(DLGDC,  OK);
	DrawImage(COMPDC, OK);
}