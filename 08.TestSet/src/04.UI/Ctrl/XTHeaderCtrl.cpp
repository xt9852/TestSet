// SkinHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "XTHeaderCtrl.h"
#include "XTDC.h"


CXTHeaderCtrl::CXTHeaderCtrl()
	:oldFont_(NULL)
{
}

CXTHeaderCtrl::~CXTHeaderCtrl()
{
}

bool CXTHeaderCtrl::Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *xtDC)
{
    if (NULL == xtDC) return false;

    x_	= x;
    y_	= y;	
	cx_	= cx;
	cy_	= cy;
	sx_	= sx;
	sy_	= sy;

	xtDC_ = xtDC;

	dc_ = xtDC_->GetHDC(WNDDC, 0);
	compDC_ = xtDC_->GetHDC(COMPDC, 0);
	imageDC_ = xtDC_->GetHDC(IMAGEDC, 0);

    LOGFONT lf = {0};
    lf.lfHeight = 12;
    _tcscpy(lf.lfFaceName, _T("宋体"));
    font_.CreateFontIndirect(&lf);

    return true;
}


BEGIN_MESSAGE_MAP(CXTHeaderCtrl, CHeaderCtrl)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_DESTROY()
END_MESSAGE_MAP()


void CXTHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
}

void CXTHeaderCtrl::OnPaint()
{
    CPaintDC dc(this);	// 系统的不能删除

    DrawImage(dc);
}

void CXTHeaderCtrl::DrawImage(CPaintDC &dc)
{
	int nWidth = 0;
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(0,0,0));
    oldFont_ = dc.SelectObject(&font_);

    CRect rect;
    int nItems = GetItemCount();
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_TOP |DT_CENTER | DT_END_ELLIPSIS;
	TCHAR buf[256] = {""};
	
	HD_ITEM hditem;
	hditem.mask       = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
	hditem.pszText    = buf;
	hditem.cchTextMax = sizeof(buf)-1;

	CRect rcWnd;
	GetWindowRect(&rcWnd);

	// 背景
	::StretchBlt(dc.m_hDC, 0, 0, rcWnd.Width(), cy_, imageDC_, sx_ + 2, sy_, 1, cy_, SRCCOPY);
	
	for (int i = 0; i < nItems; i++)
	{
		GetItem(i, &hditem);
		GetItemRect(i, &rect);

		// 背景
		// ::StretchBlt(dc.m_hDC, rect.left, 0, rect.Width(), m_Sz.cy, m_hImageDC, m_SrcPt.x + 2, m_SrcPt.y, 1, m_Sz.cy, SRCCOPY);

		// 分隔线
		::BitBlt(dc.m_hDC, rect.left, rect.top, 3, cy_, imageDC_, sx_, sy_, SRCCOPY);

		rect.top += 2;
		::DrawText(dc.m_hDC, (LPCTSTR)buf, (int)_tcslen(buf), &rect, uFormat);

		nWidth += rect.Width();
	}

	// 背景尾部
	if (nWidth < cx_)
		::StretchBlt(dc_, x_ + nWidth, y_, cx_ - nWidth + 15, cy_, imageDC_, sx_ + 2, sy_, 1, cy_, SRCCOPY);

    dc.SelectObject(oldFont_);
}

void CXTHeaderCtrl::ResetImage(int sx, int sy)
{
    if (-1 != sx) sx_ = sx;
    if (-1 != sy) sy_ = sy;

	imageDC_ = xtDC_->GetCurImageDC();

    Invalidate();
}

BOOL CXTHeaderCtrl::OnEraseBkgnd(CDC* pDC) 
{
    return TRUE;
}

void CXTHeaderCtrl::OnDestroy()
{
    CHeaderCtrl::OnDestroy();
}
