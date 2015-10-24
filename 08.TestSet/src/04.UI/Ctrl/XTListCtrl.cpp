// XTListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "XTListCtrl.h"
#include "MEMDC.H"
#include "XTDC.h"

CXTListCtrl::CXTListCtrl()
	:m_pxtDC(NULL),
	m_clrBgHi(RGB(115, 123, 165)),
	m_clrFgHi(RGB(229, 229, 229)),
	m_clrBkg(RGB(0xFF, 0xFF, 0xFF)),
	m_nScrollbarWidth(15),
	m_bInitHead(false)
{	
}

CXTListCtrl::~CXTListCtrl()
{
}

bool CXTListCtrl::Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *pxtDC, const CString& strHeads)
{
	if (NULL == pxtDC) return false;
	
	if (!this->InitHead(strHeads)) return false;

	m_pxtDC = pxtDC;

	x_ = x;
	y_ = y;
	cx_ = cx;
	cy_ = cy;	
	sx_ = sx;
	sy_ = sy;

	MyMoveWindow(x, y, cx, cy);

	m_XTHeaderCtrl.Initial(x, y, cx - 15 - 15, 18, sx + 98, sy, pxtDC);
	m_XTVerScrollbar.Initial(x + cx - 15, y, 15, cy, sx, sy, pxtDC);
	m_XTHorScrollbar.Initial(x, y + cy - 15, cx - 15, 15, sx + 46, sy, pxtDC);
	return true;
}

void CXTListCtrl::ResetImage(int sx, int sy)
{
	m_XTHeaderCtrl.ResetImage(sx, sy);
	m_XTVerScrollbar.ResetImage(sx, sy);
	m_XTHorScrollbar.ResetImage(sx, sy);
}

BEGIN_MESSAGE_MAP(CXTListCtrl, CListCtrl)
	ON_WM_NCCALCSIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDrawList)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()

void CXTListCtrl::PreSubclassWindow() 
{
	if (GetHeaderCtrl())
		m_XTHeaderCtrl.SubclassWindow(GetHeaderCtrl()->m_hWnd);

	CListCtrl::PreSubclassWindow();
}

void CXTListCtrl::OnCustomDrawList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	static bool bHighlighted = false;
	
    *pResult = CDRF_DODEFAULT;

    if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
        int iRow = (int)pLVCD->nmcd.dwItemSpec;
		bHighlighted = IsRowHighlighted(m_hWnd, iRow);
		if ( bHighlighted )
		{
			pLVCD->clrText   = m_clrFgHi; // Use my foreground hilite color
			pLVCD->clrTextBk = m_clrBgHi; // Use my background hilite color
			EnableHighlighting(m_hWnd, iRow, false);
		}
		
		*pResult = CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
	}
	else if (CDDS_ITEMPOSTPAINT == pLVCD->nmcd.dwDrawStage)
	{
		if (bHighlighted)
		{
			int  iRow = (int)pLVCD->nmcd.dwItemSpec;
			EnableHighlighting(m_hWnd, iRow, true);
		}
		*pResult = CDRF_DODEFAULT;
	}
}

void CXTListCtrl::EnableHighlighting(HWND hWnd, int row, bool bHighlight)
{
	ListView_SetItemState(hWnd, row, bHighlight? 0xff: 0, LVIS_SELECTED);
}

bool CXTListCtrl::IsRowSelected(HWND hWnd, int row)
{
	return (ListView_GetItemState(hWnd, row, LVIS_SELECTED) != 0);
}

bool CXTListCtrl::IsRowHighlighted(HWND hWnd, int row)
{
	return IsRowSelected(hWnd, row);
}

void CXTListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	//UpdateWindow();
	m_XTHeaderCtrl.Invalidate();
	m_XTHorScrollbar.UpdateThumbPosition();
	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

BOOL CXTListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	m_XTVerScrollbar.UpdateThumbPosition();
	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}

void CXTListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar == VK_UP)    ||
		(nChar == VK_DOWN)  ||
		(nChar == VK_PRIOR) ||
		(nChar == VK_NEXT)  ||
		(nChar == VK_HOME)  ||
		(nChar == VK_END))
		m_XTVerScrollbar.UpdateThumbPosition();
	else if ((nChar == VK_LEFT) || (nChar == VK_RIGHT))
		m_XTHorScrollbar.UpdateThumbPosition();

	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

bool CXTListCtrl::InitHead(const CString& strHeads)
{
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_HEADERDRAGDROP 
		| LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);//| LVS_EX_TRACKSELECT

	InitializeFlatSB(m_hWnd);
	FlatSB_EnableScrollBar(m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);

	CWnd* pParent = GetParent();

	m_XTVerScrollbar.Create(NULL, NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE|WS_GROUP, CRect(0,0,0,0), pParent, 0xfff);
	m_XTHorScrollbar.Create(NULL, NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE|WS_GROUP, CRect(0,0,0,0), pParent, 0xeee);
	m_XTVerScrollbar.list_ = this;
	m_XTHorScrollbar.list_ = this;

	SetBkColor(RGB(255, 85, 118));

	LOGFONT lf = {0};
	lf.lfHeight = 12;
	_tcscpy(lf.lfFaceName, _T("ËÎÌו"));
	m_Font.CreateFontIndirect(&lf);

	SetFont(&m_Font, TRUE);

	SetRedraw(FALSE);
	
	if (!SetHead(strHeads))
		return false;

	SetRedraw(TRUE);

	m_bInitHead = true;
	return true;
}

bool CXTListCtrl::SetHead(const CString& strHeads)
{
	int nNumColumns = 0;
	int nStart = 0;

	for (;;)
	{
		const int nComma = strHeads.Find(_T(','), nStart);

		if (nComma == -1) break;

		const CString strHeadTemp = strHeads.Mid(nStart, nComma - nStart);

		nStart = nComma + 1;

		int nSemiColon = strHeads.Find(_T(';'), nStart);

		if (nSemiColon == -1) nSemiColon = strHeads.GetLength();

		const int nWidth = _ttoi(strHeads.Mid(nStart, nSemiColon - nStart));

		nStart = nSemiColon + 1;

		if (InsertColumn(nNumColumns++, strHeadTemp, LVCFMT_LEFT, nWidth) == -1)
			return false;
	}

	return true;
}

BOOL CXTListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
	//return CListCtrl::OnEraseBkgnd(pDC);
}

void CXTListCtrl::OnPaint() 
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CMemeryDC memDC(&dc, rect);

	CRect headerRect;
	GetDlgItem(0)->GetWindowRect(&headerRect);
	ScreenToClient(&headerRect);
	dc.ExcludeClipRect(&headerRect);
	   
	CRect clip;
	memDC.GetClipBox(&clip);
	memDC.FillSolidRect(clip, m_clrBkg);
	   
	m_XTVerScrollbar.UpdateThumbPosition();
	m_XTHorScrollbar.UpdateThumbPosition();

	DefWindowProc(WM_PAINT, (WPARAM)memDC->m_hDC, (LPARAM)0);
	//DefWindowProc(WM_PAINT, (WPARAM)m_CompDC, (LPARAM)0);
}
/*
void CXTListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int nItemCount = m_XTHeaderCtrl.GetItemCount();
	int nWitdth = 0;

	CString strItemText;
	CRect rcRect(lpDrawItemStruct->rcItem);

	for (int i = 0; i < nItemCount; i++)
	{
		rcRect.right = rcRect.left + GetColumnWidth(i);

		strItemText = GetItemText(lpDrawItemStruct->itemID, i);

		::DrawText(lpDrawItemStruct->hDC, (LPSTR)(LPCSTR)strItemText, strlen((LPSTR)(LPCSTR)strItemText), &rcRect, DT_END_ELLIPSIS | DT_CENTER);// DT_RIGHT

		rcRect.left = rcRect.right;		
	}
}
*/

void CXTListCtrl::MyMoveWindow(int x, int y, int cx, int cy)
{
	MoveWindow(x, y, cx - 15, cy - 15);
	m_XTVerScrollbar.MoveWindow(x + cx - 15, y, 15, cy);
	m_XTHorScrollbar.MoveWindow(x, y + cy - 15, cx - 15, 15);
}
void CXTListCtrl::MyShowWindow(int cmd)
{
	ShowWindow(cmd);
	m_XTVerScrollbar.ShowWindow(cmd);
	m_XTHorScrollbar.ShowWindow(cmd);
}
void CXTListCtrl::MyInvalidate(void)
{
	Invalidate();
	m_XTVerScrollbar.Invalidate();
	m_XTHorScrollbar.Invalidate();
}

void CXTListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 50;
}