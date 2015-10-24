// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XTTabCtrl.h"



IMPLEMENT_DYNAMIC(CXTTabCtrl, CTabCtrl)
CXTTabCtrl::CXTTabCtrl()
{
	m_hbrFill.CreateSolidBrush(RGB(182,224,249));
	m_hbrEdge.CreateSolidBrush(RGB(57,160,198));
	m_hbrSelFill.CreateSolidBrush(RGB(255,255,255));
	m_hbrSelEdge.CreateSolidBrush(RGB(17,119,147));
}

CXTTabCtrl::~CXTTabCtrl()
{
	m_hbrFill.DeleteObject();
	m_hbrEdge.DeleteObject();
	m_hbrSelFill.DeleteObject();
	m_hbrSelEdge.DeleteObject();
}

BEGIN_MESSAGE_MAP(CXTTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CXTTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UNUSED_ALWAYS(lpDrawItemStruct);
}

void CXTTabCtrl::DrawButtonItem(CPaintDC &dc, 
									   RECT &rc, 
									   UINT nID,
									   INT nImageId, 
									   LPCTSTR strText, 
									   BOOL bSelected)
{
	CRgn ItemRgn1;
	CRgn ItemRgn2;
	ItemRgn1.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 10, 10);	
	ItemRgn2.CreateRectRgn(rc.left, rc.top + 5, rc.right, rc.bottom);
	ItemRgn1.CombineRgn(&ItemRgn1, &ItemRgn2, RGN_OR);

	if (bSelected)
	{
		dc.FillRgn(&ItemRgn1, &m_hbrSelFill);
		dc.FrameRgn(&ItemRgn1, &m_hbrSelEdge, 1, 1);
	}
	else
	{
		dc.FillRgn(&ItemRgn1, &m_hbrFill);
		dc.FrameRgn(&ItemRgn1, &m_hbrEdge, 1, 1);
	}

	if (-1 != nImageId)
	{
		dc.TextOut(rc.left + (nID ? 17 : 25), rc.top + (bSelected? 6: 5), strText, (int)_tcslen(strText));

		CImageList* piml = GetImageList();
		if (piml && piml->m_hImageList)
		{
			piml->Draw(&dc, nImageId, CPoint(rc.left + (nID? 1: 5), rc.top + 3), ILD_NORMAL);
		}
	}
	else
	{
		dc.DrawText(strText, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
}

BOOL CXTTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect rect; 
	this->GetClientRect(rect); 

	pDC->FillSolidRect(&rect, RGB(215, 239, 251));
	return TRUE;
}

void CXTTabCtrl::OnPaint()
{
	CPaintDC dc(this);

	dc.SelectObject(GetFont());
	dc.SetBkMode(TRANSPARENT);

	RECT rcItem = {0};	
	int nTab = GetItemCount();
	int nSel = GetCurSel();

	if (!nTab) return;

	for (int i = 0; i < nTab; i++)
	{
		TCHAR tszText[100] = {_T("")};
		TCITEM tci = {0};
		tci.mask        = TCIF_TEXT | TCIF_IMAGE;
		tci.pszText     = tszText;
		tci.cchTextMax  =  sizeof(tszText)/sizeof(tszText[0]);
	
		GetItem(i, &tci);
		GetItemRect(i, &rcItem);

		if (i != nSel)
		{
			rcItem.bottom += 2;	
			DrawButtonItem(dc, rcItem, i, tci.iImage, tszText);
		}
		else
		{
			rcItem.top -= 2;
			rcItem.bottom += 2;			
			DrawButtonItem(dc, rcItem, i, tci.iImage, tszText, TRUE);
		}
	}
}
