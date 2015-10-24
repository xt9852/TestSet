// XTCheckBox.cpp : 实现文件
//

#include "stdafx.h"
#include "XTCheckBox.h"
#include "XTDC.h"
#include ".\xtcheckbox.h"

IMPLEMENT_DYNAMIC(CXTCheckBox, CButton)
CXTCheckBox::CXTCheckBox()
	:m_hDlgDC(NULL),
	m_hCompDC(NULL),
	m_hBmpDC(NULL),
    m_bCheck(FALSE)
{
	m_Sz.cx = 0;
	m_Sz.cy = 0;
	m_Pt.x = 0;
	m_Pt.y = 0;
	m_SrcPt.x = 0;
	m_SrcPt.y = 0;
	m_ToolTip.m_hWnd = NULL;
}

CXTCheckBox::~CXTCheckBox()
{
	if (m_ToolTip.m_hWnd != NULL && m_ToolTip.GetToolCount() > 0)
	{
		m_ToolTip.DelTool(this, 1);
	}
}

BEGIN_MESSAGE_MAP(CXTCheckBox, CButton)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(BM_SETCHECK,	  OnSetCheck)
	ON_MESSAGE(BM_GETCHECK,	  OnGetCheck)
	ON_WM_MOUSEMOVE()	
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CXTCheckBox::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

LRESULT CXTCheckBox::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (!this->IsWindowEnabled()) return 0;

    if (m_bCheck)
		DrawImage(DLGDC, CHECK);
	else
		DrawImage(DLGDC, UNCHECK);

	return 0;
}

void CXTCheckBox::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT stTRACKMOUSEEVENT = {0};
	stTRACKMOUSEEVENT.cbSize    =  sizeof(TRACKMOUSEEVENT);
	stTRACKMOUSEEVENT.hwndTrack = m_hWnd;
	stTRACKMOUSEEVENT.dwFlags   = TME_LEAVE;
	_TrackMouseEvent(&stTRACKMOUSEEVENT);

	if (m_bCheck)
		DrawImage(DLGDC, CHECK_ON);
	else
		DrawImage(DLGDC, UNCHECK_ON);

	CButton::OnMouseMove(nFlags, point);
}

BOOL CXTCheckBox::PreTranslateMessage(MSG* pMsg)
{
	if(NULL != m_ToolTip.m_hWnd)
		m_ToolTip.RelayEvent(pMsg);

	return CButton::PreTranslateMessage(pMsg);
}

LRESULT CXTCheckBox::OnSetCheck(WPARAM wParam, LPARAM lParam)
{
	if (!this->IsWindowEnabled()) return 0;

    m_bCheck = (BOOL)wParam;

	if (wParam)
		DrawImage(COMPDC, CHECK_ON);
	else
		DrawImage(COMPDC, UNCHECK_ON);

	DrawImage(COMPTODLG);
	return 0;
}

LRESULT CXTCheckBox::OnGetCheck(WPARAM wParam, LPARAM lParam)
{
	return m_bCheck;
}

void CXTCheckBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    this->SetCheck(!m_bCheck);
	CButton::OnLButtonDown(nFlags, point);
}

void CXTCheckBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
}

void CXTCheckBox::DrawImage(UINT nObject, UINT nState)
{
	switch (nObject)
	{
	case DLGDC:
		::BitBlt(m_hDlgDC, m_Pt.x, m_Pt.y, m_Sz.cx, m_Sz.cy, m_hBmpDC, m_SrcPt.x + nState * m_Sz.cx, m_SrcPt.y, SRCCOPY);
		break;
	case COMPDC:
		::BitBlt(m_hCompDC, m_Pt.x, m_Pt.y, m_Sz.cx, m_Sz.cy, m_hBmpDC, m_SrcPt.x + nState * m_Sz.cx, m_SrcPt.y, SRCCOPY);
		break;
	case COMPTODLG:
		::BitBlt(m_hDlgDC, m_Pt.x, m_Pt.y, m_Sz.cx, m_Sz.cy, m_hCompDC, m_Pt.x, m_Pt.y, SRCCOPY);
		break;
    case CLEAR:
        ::BitBlt(m_hDlgDC, m_Pt.x, m_Pt.y, m_Sz.cx, m_Sz.cy, m_hBmpDC, m_Pt.x, m_Pt.y, SRCCOPY);
        ::BitBlt(m_hCompDC, m_Pt.x, m_Pt.y, m_Sz.cx, m_Sz.cy, m_hBmpDC, m_Pt.x, m_Pt.y, SRCCOPY);
        break;
	default:
		break;
	}
}

BOOL CXTCheckBox::OnEraseBkgnd(CDC* pDC)
{
	// Don't draw back ground
	//return CButton::OnEraseBkgnd(pDC);
	return TRUE;
}

void CXTCheckBox::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);

	int nState = 0;
	
	if (bEnable)
	{
		nState = GetCheck() ? CHECK : UNCHECK;
	}
	else
	{
		nState = GetCheck() ? CHECK_DISABLE : UNCHECK_DISABLE;
	}

	DrawImage(COMPDC, nState);
	DrawImage(COMPTODLG);
}

/**
	Init button
	All param is input

	x,  y			left top point position
	cx, cy			button width height
	sx, sy			button image left top point position in pix file
	pDBuffDC		double buff DC
	lpszToolTipText	button text info
	bCheckBox		is CheckBox
	bIsCheckBoxTrue	is checked(if is CheckBox)
*/
bool CXTCheckBox::Initial(int x, int y,
						int cx, int cy,
						int sx, int sy,
						CXTDC *pDBuffDC,
						LPCTSTR lpszToolTipText)
{
	if (pDBuffDC == NULL) return false;

	m_hDlgDC  = pDBuffDC->GetHDC(WNDDC, 0);
	m_hCompDC = pDBuffDC->GetHDC(COMPDC, 0);
	m_hBmpDC  = pDBuffDC->GetHDC(IMAGEDC, 0);

	m_Sz.cx   = cx;
	m_Sz.cy   = cy;
	m_Pt.x    = x;
	m_Pt.y    = y;
	m_SrcPt.x = sx;
	m_SrcPt.y = sy;

	MoveWindow(x, y, cx, cy, 0);	
	DrawImage(COMPDC, UNCHECK);
	DrawImage(COMPTODLG);

	// set button text info
	if (m_ToolTip.m_hWnd == NULL)
		m_ToolTip.Create(this);

	if (m_ToolTip.GetToolCount() > 0)
		m_ToolTip.DelTool(this, 1);

	if (!m_ToolTip.AddTool(this, lpszToolTipText))
		return false;

	m_ToolTip.Activate(TRUE);

	return true;
}

// -1主要用于当DC中的图片更改时刷新CXTCheckBox的图片
void CXTCheckBox::ResetImage(int sx, int sy)
{
	if (-1 != sx) m_SrcPt.x = sx;
	if (-1 != sy) m_SrcPt.y = sy;

	int nState = GetCheck() ? CHECK : UNCHECK;
	DrawImage(DLGDC,  nState);
	DrawImage(COMPDC, nState);
}


void CXTCheckBox::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CButton::OnShowWindow(bShow, nStatus);

    if (bShow)
    {
        int nState = GetCheck() ? CHECK : UNCHECK;

        DrawImage(DLGDC,  nState);
        DrawImage(COMPDC, nState);
    }
    else
    {
        DrawImage(CLEAR);
    }
}
