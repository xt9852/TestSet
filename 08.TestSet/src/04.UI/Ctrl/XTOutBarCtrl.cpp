
#include "stdafx.h"
#include "XTOutBarCtrl.h"
#include "XTOutBarEdit.h"
#include ".\xtoutbarctrl.h"


UINT WM_OUTBAR_NOTIFY = RegisterWindowMessage(_T("WM_OUTBAR_NOTIFY"));


IMPLEMENT_DYNCREATE(CXTOutBarCtrl, CWnd)

CXTOutBarCtrl::CXTOutBarCtrl()
{
	m_crBackGroundColor = GetSysColor(COLOR_BACKGROUND);
	m_crBackGroundColor1 = GetSysColor(COLOR_BACKGROUND);
	
	m_crTextColor = 0;

	m_cr3dFace = RGB(157,179,202);//GetSysColor(COLOR_3DFACE);
	m_crLightBorder = GetSysColor(COLOR_3DLIGHT);
	m_crHilightBorder = GetSysColor(COLOR_3DHILIGHT);
	m_crShadowBorder = GetSysColor(COLOR_3DSHADOW);
	m_crDkShadowBorder = GetSysColor(COLOR_3DDKSHADOW);

	m_pBlackPen = new CPen(PS_SOLID, 1, RGB(0,0,0));

	m_nFolderHeight = 22;

	m_dwFlags = fDragItems|fEditGroups|fEditItems|fRemoveGroups|fRemoveItems|fAddGroups|fAnimation|fSelHighlight|fSmallIcon;

	m_nSelFolder = -1;

	m_nLastFolderHighlighted = -1;
	m_nLastSelectedFolder = -1;
	
	m_pLargeImageList = NULL;
	m_pSmallImageList = NULL;

	m_nFirstItem = 0;

	m_xSmallIconLabelOffset = 4;
	m_yLargeIconLabelOffset = 3;

	m_ySmallIconSpacing = 10;
	m_yLargeIconSpacing = 8;

	m_xLeftMargin = 5;
	m_yTopMargin = 5;

	m_bUpArrow = m_bDownArrow = false;

	m_hHandCursor = AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649));	// hand
	m_rcUpArrow = m_rcDownArrow = CRect(0,0,0,0);

	m_bUpPressed = m_bDownPressed = false;

	m_bLooping = false;

	m_nLastItemHighlighted = -1;
	m_bPressedHighlight = false;

	m_nLastDragItemDraw = -1;

	m_nAnimationTickCount = 10;

	m_hDragCursor = AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649));
	m_hNoDragCursor = AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);

	m_nLastSel = -1;
	m_nSelAnimCount = 0;

	m_nSelAnimTiming = 0;
}

CXTOutBarCtrl::~CXTOutBarCtrl()
{
	for (int i = 0; i < m_arFolder.GetSize(); i++)
	{
		if (m_arFolder.GetAt(i)) delete (CBarFolder*)m_arFolder.GetAt(i);
	}

	m_arFolder.RemoveAll();

	delete m_pBlackPen;
}


BEGIN_MESSAGE_MAP(CXTOutBarCtrl, CWnd)
    ON_WM_CREATE()
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_SETCURSOR()
    ON_WM_SIZE()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()
    ON_WM_DESTROY()    
    ON_REGISTERED_MESSAGE(WM_OUTBAR_NOTIFY,    OnEndLabelEdit)
/*    ON_COMMAND(ID_OUTBAR_LARGEICON,            OnOutBarLargeicon)
	ON_UPDATE_COMMAND_UI(ID_OUTBAR_LARGEICON,  OnUpdateOutBarLargeicon)
	ON_COMMAND(ID_OUTBAR_SMALLICON,            OnOutBarSmallicon)
	ON_UPDATE_COMMAND_UI(ID_OUTBAR_SMALLICON,  OnUpdateOutBarSmallicon)
	ON_COMMAND(ID_OUTBAR_REMOVEITEM,           OnOutBarRemoveitem)
	ON_UPDATE_COMMAND_UI(ID_OUTBAR_REMOVEITEM, OnUpdateOutBarRemoveitem)
	ON_COMMAND(ID_OUTBAR_RENAMEITEM,           OnOutBarRenameitem)
	ON_UPDATE_COMMAND_UI(ID_OUTBAR_RENAMEITEM, OnUpdateOutBarRenameitem)    
    ON_COMMAND(ID_OUTBAR_ADDGROUP,             OnOutBarAddGroup)
    ON_COMMAND(ID_OUTBAR_DELGROUP,             OnOutBarDelGroup)
    ON_COMMAND(ID_OUTBAR_RENAMEGROUP,          OnOutBarRenameGroup)
    ON_COMMAND(ID_OUTBAR_DELUSER,              OnDelUserFromFloder)
    ON_COMMAND(ID_OUTBAR_BROADFILE,            OnBroadFile)
    ON_COMMAND_RANGE(ID_OUTBAR_ADDUSER, ID_OUTBAR_ADDUSER+100, OnAddUserToFloder)
*/
END_MESSAGE_MAP()


void CXTOutBarCtrl::OnDestroy() 
{
    CWnd::OnDestroy();
}

long CXTOutBarCtrl::OnEndLabelEdit(WPARAM wParam, LPARAM lParam)
{
	if (wParam == NM_OB_ONGROUPENDEDIT)
	{
		CXTOuBarEdit *pEdit = (CXTOuBarEdit *)lParam;
		OUTBAR_INFO ob = {0};
		ob.nFolder = pEdit->m_nIndex;
		ob.pszText = (LPCTSTR)pEdit->m_strText;
        ob.nData   = this->GetFolderData(pEdit->m_nIndex);
		if (GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_OB_ONGROUPENDEDIT, (LPARAM) &ob))
		{
			SetFolderText(pEdit->m_nIndex, pEdit->m_strText);
			CRect rc;
			GetFolderRect(pEdit->m_nIndex, rc);
			InvalidateRect(rc, false);
		}
	}
	if (wParam == NM_OB_ONLABELENDEDIT)
	{
		CXTOuBarEdit *pEdit = (CXTOuBarEdit *)lParam;
        OUTBAR_INFO ob = {0};
		ob.nIndex  = pEdit->m_nIndex;
		ob.pszText = (LPCTSTR)pEdit->m_strText;
        ob.nData   = this->GetItemData(pEdit->m_nIndex);
		if (GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_OB_ONLABELENDEDIT, (LPARAM) &ob))
		{
			SetItemText(pEdit->m_nIndex, pEdit->m_strText);
			CRect rc;
			GetInsideRect(rc);
			InvalidateRect(rc, true);
		}
	}
	return 0;
}

void CXTOutBarCtrl::SetFolderText(const int nIndex, const char *pszText)
{
	if (nIndex < 0 || nIndex >= GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nIndex);
	if (NULL == pbf) return;

	if (pbf->m_pszName) 
	{
		delete [] pbf->m_pszName;
		pbf->m_pszName = NULL;
	}
	pbf->m_pszName = new char [lstrlen(pszText)+1];
	lstrcpy(pbf->m_pszName, pszText);
}

void CXTOutBarCtrl::SetFolderData(const int nIndex, DWORD dwData)
{
    if (nIndex < 0 || nIndex >= GetFolderCount()) return;

    CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nIndex);
    if (NULL == pbf) return;

    pbf->m_dwData = dwData;
}

void CXTOutBarCtrl::SetItemText(const int nIndex, const char *pszText)
{
	if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return;

	CBarItem *pi = (CBarItem*) pbf->m_arItems.GetAt(nIndex);
	if (pi->m_pszItem) 
	{
		delete [] pi->m_pszItem;
		pi->m_pszItem = NULL;
	}
	pi->m_pszItem = new char [lstrlen(pszText)+1];
	lstrcpy(pi->m_pszItem, pszText);
}

BOOL CXTOutBarCtrl::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, const DWORD dwFlag)
{
	m_dwFlags = dwFlag;
	if (!CWnd::CreateEx(WS_EX_STATICEDGE, NULL, NULL, dwStyle|WS_CHILD, rect, pParentWnd, nID))	return FALSE;

	SetSmallIconView(true);
/*
	m_menuItem.CreatePopupMenu();
	m_menuItem.SetParam(g_ProFile.GetImageList(), 100, 20, MIT_XP);
	m_menuItem.AppendMenu(MF_STRING, ID_OUTBAR_SMALLICON, STR_OUTBAR_SMALLICON, 1);
	m_menuItem.AppendMenu(MF_STRING, ID_OUTBAR_LARGEICON, STR_OUTBAR_LARGEICON, 2);

	if (m_dwFlags&fRemoveItems || m_dwFlags&fEditItems)
	{
		m_menuFolder.AppendMenu(MF_SEPARATOR);
		if (m_dwFlags&fEditItems)
			m_menuItem.AppendMenu(MF_STRING, ID_OUTBAR_RENAMEITEM, STR_OUTBAR_RENAMEITEM, 3);

		if (m_dwFlags&fRemoveItems)
			m_menuItem.AppendMenu(MF_STRING, ID_OUTBAR_REMOVEITEM, STR_OUTBAR_REMOVEITEM, 4);
	}


	m_mFolder.CreatePopupMenu();
	m_mFolder.SetParam(g_ProFile.GetImageList(), 100, 20, MIT_XP);
	m_mFolder.AppendMenu(MF_STRING, ID_OUTBAR_ADDGROUP,    STR_OUTBAR_ADDGROUP, 1);

    m_mFolder1.CreatePopupMenu();
    m_mFolder1.SetParam(g_ProFile.GetImageList(), 100, 20, MIT_XP);
    m_mFolder1.AppendMenu(MF_STRING, ID_OUTBAR_ADDGROUP,    STR_OUTBAR_ADDGROUP, 1);
    m_mFolder1.AppendMenu(MF_STRING, ID_OUTBAR_DELGROUP,    STR_OUTBAR_DELGROUP, 2);
    m_mFolder1.AppendMenu(MF_STRING, ID_OUTBAR_RENAMEGROUP, STR_OUTBAR_RENAMEGROUP, 3);

    m_mItem.CreatePopupMenu();
    m_mItem.SetParam(g_ProFile.GetImageList(), 150, 20, MIT_XP);

    m_mItem1.CreatePopupMenu();
    m_mItem1.SetParam(g_ProFile.GetImageList(), 120, 20, MIT_XP);
    m_mItem1.AppendMenu(MF_STRING, ID_OUTBAR_DELUSER, STR_OUTBAR_DELUSER, 3);
    m_mItem1.AppendMenu(MF_STRING, ID_OUTBAR_BROADFILE, STR_OUTBAR_BROADFILE, 4);
*/
	this->SetTimer(4, 200, NULL);

	return TRUE;
}

bool CXTOutBarCtrl::IsSmallIconView() const
{
	return m_dwFlags&fSmallIcon;
}

void CXTOutBarCtrl::SetSmallIconView(const bool bSet)
{
	m_nFirstItem = 0;

	if (bSet)
	{
		if (!IsSmallIconView()) 
		{
			m_dwFlags |= fSmallIcon;
			CRect rc;
			GetInsideRect(rc);
			InvalidateRect(rc, false);
		}
	}
	else
	{
		if (IsSmallIconView()) 
		{
			m_dwFlags &= ~fSmallIcon;
			CRect rc;
			GetInsideRect(rc);
			InvalidateRect(rc, false);
		}
	}
}

DWORD CXTOutBarCtrl::GetFlag() const
{
	return m_dwFlags;
}

void CXTOutBarCtrl::ModifyFlag(const DWORD &dwRemove, const DWORD &dwAdd, const UINT nRedraw)
{
	if (dwRemove)	m_dwFlags &= ~(dwRemove);
	if (dwAdd)		m_dwFlags |= dwAdd;

	if (GetSafeHwnd())
	{
		if (nRedraw != 0) SetWindowPos(0,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|nRedraw);
		else Invalidate();
	}
}

int CXTOutBarCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CXTOutBarCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		CPoint pt(GetMessagePos());
		ScreenToClient(&pt);

		CRect rc;
		GetClientRect(&rc);
		if (!(rc.PtInRect(pt)))
		{
			HighlightFolder(-1);
			HighlightItem(-1);
			KillTimer(1);
		}
	}
	else if (nIDEvent == 3 && m_nLastSel >= 0)
	{
		m_nSelAnimCount++;
		if (m_nSelAnimCount > 3) m_nSelAnimCount = -1;
		if (m_nSelAnimCount == 0)
			DrawAnimItem(-1, 1, m_nLastSel);
		if (m_nSelAnimCount == 1)
			DrawAnimItem(0, 0, m_nLastSel);
		if (m_nSelAnimCount == 2)
			DrawAnimItem(1, 1, m_nLastSel);
		if (m_nSelAnimCount == 3)
			DrawAnimItem(0, 0, m_nLastSel);
	}
	else if (nIDEvent == 4)
	{
		m_nSelAnimCount++;
		if (m_nSelAnimCount > 3) m_nSelAnimCount = -1;

		for (int i = 0; i < (int)m_arActiveItem.GetCount(); i++)
		{
			if (m_nSelAnimCount == 0)
				DrawActItem(-1, 1, m_arActiveItem[i].nFolder, m_arActiveItem[i].nIndex);
			if (m_nSelAnimCount == 1)
				DrawActItem(0, 0, m_arActiveItem[i].nFolder, m_arActiveItem[i].nIndex);
			if (m_nSelAnimCount == 2)
				DrawActItem(1, 1, m_arActiveItem[i].nFolder, m_arActiveItem[i].nIndex);
			if (m_nSelAnimCount == 3)
				DrawActItem(0, 0, m_arActiveItem[i].nFolder, m_arActiveItem[i].nIndex);
		}
	}

	CWnd::OnTimer(nIDEvent);
}

// 图标抖动
void CXTOutBarCtrl::DrawAnimItem(const int xoffset, const int yoffset, const int nIndex)
{
	CImageList *pImageList = GetFolderImageList(m_nSelFolder, IsSmallIconView());
	if (NULL == pImageList) return;

	CRect rc, irc;
	GetInsideRect(irc);
	GetItemRect(m_nSelFolder, m_nLastSel, rc);

	if (m_nLastSel >= m_nFirstItem && irc.bottom > rc.bottom && irc.top < rc.top)
	{
		if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return;

		CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
		if (NULL == pbf) return;

		if (nIndex < 0 || nIndex >= pbf->GetItemCount()) return;

		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
		if (NULL == pi) return;

		CClientDC dc(this);

		if (IsSmallIconView())
		{
			IMAGEINFO ii = {0};
			pImageList->GetImageInfo(pi->m_nImage, &ii);

			CSize szImage = CRect(ii.rcImage).Size();
			CPoint pt;
			pt.x = rc.left + 2;
			pt.y = rc.top + (rc.Height() - szImage.cy) / 2;
			CRect rcBck(pt.x-1, pt.y-1, pt.x + szImage.cx+2, pt.y + szImage.cy+2);

			dc.FillSolidRect(rcBck, m_crBackGroundColor);

			pt.x += xoffset;
			pt.y += yoffset;

			pImageList->Draw(&dc, pi->m_nImage, pt, ILD_NORMAL);
		}
		else
		{
			IMAGEINFO ImageInfo = {0};
			pImageList->GetImageInfo(pi->m_nImage, &ImageInfo);

			CSize szImage = CRect(ImageInfo.rcImage).Size();
			CPoint pt;
			pt.x = rc.left + (rc.Width() - szImage.cx) / 2;
			pt.y = rc.top;

			CRect rcBck(pt.x-1, pt.y-1, pt.x + szImage.cx+2, pt.y + szImage.cy+2);

			dc.FillSolidRect(rcBck, m_crBackGroundColor);

			pt.x += xoffset;
			pt.y += yoffset;

			pImageList->Draw(&dc, pi->m_nImage, pt, ILD_NORMAL);
		}
	}
}

// 图标抖动
void CXTOutBarCtrl::DrawActItem(const int xoffset, const int yoffset, 
                                const int nFolder, const int nIndex)
{
	if (nFolder != m_nSelFolder || GetFolderCount() < 1) return;

	CImageList *pImageList = GetFolderImageList(nFolder, IsSmallIconView());
	if (NULL == pImageList) return;

	CRect rc, irc;
	GetInsideRect(irc);
	GetItemRect(nFolder, nIndex, rc);

	if (irc.bottom > rc.bottom && irc.top < rc.top)
	{
		CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
		if (NULL == pbf) return;
 
		if (nIndex >= pbf->m_arItems.GetCount()) return;

		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
		if (NULL == pi) return;

		CClientDC dc(this);

		if (IsSmallIconView())
		{
			IMAGEINFO ii = {0};
			pImageList->GetImageInfo(pi->m_nImage, &ii);

			CSize szImage = CRect(ii.rcImage).Size();
			CPoint pt;
			pt.x = rc.left + 2;
			pt.y = rc.top + (rc.Height() - szImage.cy) / 2;

			CRect rcBck(pt.x-1, pt.y-1, pt.x + szImage.cx+2, pt.y + szImage.cy+2);

			dc.FillSolidRect(rcBck, m_crBackGroundColor);

			pt.x += xoffset;
			pt.y += yoffset;

			pImageList->Draw(&dc, pi->m_nImage, pt, ILD_NORMAL);
		}
		else
		{
			IMAGEINFO ii = {0};
			pImageList->GetImageInfo(pi->m_nImage, &ii);

			CSize szImage = CRect(ii.rcImage).Size();
			CPoint pt;
			pt.x = rc.left + (rc.Width() - szImage.cx) / 2;
			pt.y = rc.top;

			CRect rcBck(pt.x-1, pt.y-1, pt.x + szImage.cx+2, pt.y + szImage.cy+2);

			dc.FillSolidRect(rcBck, m_crBackGroundColor);

			pt.x += xoffset;
			pt.y += yoffset;

			pImageList->Draw(&dc, pi->m_nImage, pt, ILD_NORMAL);
		}
	}
}

void CXTOutBarCtrl::OnPaint() 
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CPaintDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap Bmp;
	Bmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	CBitmap *pOldBmp = memDC.SelectObject(&Bmp);
	CDC *pDC = &memDC;

	CRect rcInside;
	GetInsideRect(rcInside);
	if (!GetFolderChild()) 
	{		
		pDC->FillSolidRect(rcInside, m_crBackGroundColor);
	}

	int nCount = (int)m_arFolder.GetSize();
	CRect rcFolder;
	for (int i = 0; i < nCount; i++)
	{
		GetFolderRect(i, rcFolder);
		DrawFolder(pDC, i, rcFolder, false);
	}

	if (!GetFolderChild() && (m_nSelFolder >= 0))
	{
		int nFirst = 0, nLast = 0;
		GetVisibleRange(m_nSelFolder, nFirst, nLast);

		m_rcUpArrow.SetRect(0,0,GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CXVSCROLL));
		m_rcDownArrow = m_rcUpArrow;
		m_rcUpArrow.OffsetRect(rcInside.right - 5 - GetSystemMetrics(SM_CXVSCROLL), rcInside.top +5);
		m_rcDownArrow.OffsetRect(rcInside.right - 5 - GetSystemMetrics(SM_CXVSCROLL), rcInside.bottom - 5 - GetSystemMetrics(SM_CXVSCROLL));

		if (nFirst > 0)
		{
			if (m_bUpPressed) pDC->DrawFrameControl(m_rcUpArrow, DFC_SCROLL, DFCS_SCROLLUP|DFCS_PUSHED);
			else			  pDC->DrawFrameControl(m_rcUpArrow, DFC_SCROLL, DFCS_SCROLLUP);

			m_bUpArrow = true;
			pDC->ExcludeClipRect(m_rcUpArrow);
		}
		else m_bUpArrow = false;

		if (nLast < GetItemCount() - 1)
		{
			if (m_bDownPressed)	pDC->DrawFrameControl(m_rcDownArrow, DFC_SCROLL, DFCS_SCROLLDOWN|DFCS_PUSHED);
			else				pDC->DrawFrameControl(m_rcDownArrow, DFC_SCROLL, DFCS_SCROLLDOWN);

			m_bDownArrow = true;
			pDC->ExcludeClipRect(m_rcDownArrow);
		}
		else m_bDownArrow = false;

		PaintItems(pDC, m_nSelFolder, rcInside);
	}

	dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), &memDC, 0,0, SRCCOPY);

	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	Bmp.DeleteObject();

	if (m_nLastFolderHighlighted >= 0)
	{
		int i = m_nLastFolderHighlighted;
		m_nLastFolderHighlighted = -1;
		HighlightFolder(i);
	}
	if (m_nLastItemHighlighted >= 0)
	{
		int i = m_nLastItemHighlighted;
		m_nLastItemHighlighted = -1;
		HighlightItem(i, m_bPressedHighlight);
	}
}

BOOL CXTOutBarCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}

bool CXTOutBarCtrl::GetFolderRect(const int nIndex, CRect &rect) const
{
	int nCount = (int)m_arFolder.GetCount();

	if (nIndex < 0 || nIndex >= nCount) return false;

	CRect rc;
	GetClientRect(rc);
	if (nIndex > m_nSelFolder)
		rect.SetRect(rc.left, rc.bottom - ((nCount - nIndex)) * m_nFolderHeight, rc.right, 
						rc.bottom - (nCount - nIndex - 1) * m_nFolderHeight);
	else 
		rect.SetRect(rc.left, rc.top + nIndex * m_nFolderHeight - 1, rc.right, 
						rc.top + (1 + nIndex) * m_nFolderHeight - 1);

	return true;
}

void CXTOutBarCtrl::GetItemRect(const int nFolder, const int nIndex, CRect &rect)
{
	CRect rc;
	GetInsideRect(rc);
	int nTop = rc.top;
	CSize sz(0,0);
	int nOffsetY = 0;
	for (int i = 0; i < nIndex; i++)
	{
		sz = GetItemSize(nFolder, i, ircAll);
		nTop += sz.cy;

		if (IsSmallIconView()) 
		{
			nTop += m_ySmallIconSpacing; 
		}
		else 
		{
			nTop += m_yLargeIconSpacing;
		}
		if (i == m_nFirstItem - 1) nOffsetY = nTop - rc.top;
	}

	sz = GetItemSize(nFolder, nIndex, ircAll);
	rect.SetRect(rc.left, nTop, rc.left + sz.cx, nTop + sz.cy);

	rect.top -= nOffsetY;
	rect.bottom -= nOffsetY;

	rect.left += m_xLeftMargin;
	rect.top  += m_yTopMargin;
	rect.bottom += m_yTopMargin;

	if (!IsSmallIconView()) 
	{
		rect.left = rc.left;
		rect.right = rc.right;
	}
}

void CXTOutBarCtrl::DrawFolder(CDC *pDC, const int nIndex, CRect rect, const bool bSelected)
{
	CBarFolder *pbf = (CBarFolder*) m_arFolder.GetAt(nIndex);
	if (NULL == pbf) return;

	if (!bSelected)
	{
		CPen Pen(PS_SOLID, 1, m_crBackGroundColor1);
		CPen *pOldPen = pDC->SelectObject(&Pen);
		pDC->MoveTo(rect.left, rect.top);
		pDC->LineTo(rect.right, rect.top);
		pDC->SelectObject(pOldPen);

		rect.top++;

		pDC->Draw3dRect(rect, m_crHilightBorder, m_crBackGroundColor1);
		rect.InflateRect(-1,-1);
		
		pDC->FillSolidRect(rect, m_cr3dFace);

		int nOldBKMode = pDC->SetBkMode(TRANSPARENT);
		CFont *pOldFont = pDC->SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
		pDC->DrawText(CString(pbf->m_pszName), rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_WORD_ELLIPSIS);
		pDC->SetBkMode(nOldBKMode);
		pDC->SelectObject(pOldFont);
	}
	else
	{
		CPen Pen(PS_SOLID, 1, m_crBackGroundColor1);
		CPen *pOldPen = pDC->SelectObject(&Pen);
		pDC->MoveTo(rect.left+1, rect.top);
		pDC->LineTo(rect.right, rect.top);
		pDC->SelectObject(pOldPen);

		rect.top++;

		pDC->Draw3dRect(rect, m_crDkShadowBorder, m_crHilightBorder);
		rect.InflateRect(-1,-1);
		pDC->Draw3dRect(rect, m_crBackGroundColor1, m_cr3dFace);
		rect.InflateRect(-1,-1);

		pDC->FillSolidRect(rect, m_cr3dFace);

		int nOldBKMode = pDC->SetBkMode(TRANSPARENT);
		CFont *pOldFont = pDC->SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
		pDC->DrawText(CString(pbf->m_pszName), rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_WORD_ELLIPSIS);
		pDC->SetBkMode(nOldBKMode);
		pDC->SelectObject(pOldFont);
	}
}

int CXTOutBarCtrl::AddFolder(const char *pszName, const DWORD dwData)
{
	CBarFolder *pbf = new CBarFolder(pszName, dwData);
	ASSERT(pbf);
	m_arFolder.Add((void *)pbf);

	return (int)m_arFolder.GetSize() - 1;
}

CXTOutBarCtrl::CBarFolder::CBarFolder(const char *pszName, DWORD dwData)
{
	m_pszName = NULL;
	m_dwData = dwData;

	if (NULL == m_pszName)
	{
		m_pszName = new char[lstrlen(pszName)+1];
		ASSERT(m_pszName);
		lstrcpy(m_pszName, pszName);
	}
	m_pLargeImageList = NULL;
	m_pSmallImageList = NULL;
	m_pWndChild = NULL;
}

CXTOutBarCtrl::CBarFolder::~CBarFolder()
{
	if (m_pszName) delete [] m_pszName;
	for (int i = 0; i < m_arItems.GetSize(); i++)
		if (m_arItems.GetAt(i)) delete (CBarFolder*) m_arItems.GetAt(i);

	m_arItems.RemoveAll();
}

void CXTOutBarCtrl::GetInsideRect(CRect &rect) const
{
	GetClientRect(rect);
	if (m_arFolder.GetSize() > 0)
	{
		int nCount = (int)m_arFolder.GetCount();
		rect.top += m_nFolderHeight * (m_nSelFolder + 1) - 1;
		rect.bottom -= (nCount - m_nSelFolder - 1) * m_nFolderHeight;
		return;
	}
}

void CXTOutBarCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	int nIndex, nHit = HitTestEx(point, nIndex);

	if (nHit != htFolder && m_nLastFolderHighlighted >= 0) HighlightFolder(-1);
	if (nHit != htItem   && m_nLastItemHighlighted   >= 0) HighlightItem(-1);

	if (nHit == htFolder)
	{
		HighlightFolder(nIndex);
		SetTimer(1,100,NULL);
	}
	else if (nHit == htItem)
	{
		HighlightItem(nIndex);
		SetTimer(1,100,NULL);
	}

	CWnd::OnMouseMove(nFlags, point);
}

int CXTOutBarCtrl::HitTestEx(const CPoint &point, int &nIndex)
{
	if (m_nSelFolder < 0) return htNothing;

	if (m_bUpArrow && m_rcUpArrow.PtInRect(point)) return htUpScroll;
	if (m_bDownArrow && m_rcDownArrow.PtInRect(point)) return htDownScroll;

	CRect rc;
	int nCount = (int)m_arFolder.GetCount();
	
	for (int i = 0; i < nCount; i++)
	{
		GetFolderRect(i, rc);
    	if (rc.PtInRect(point)) 
		{
			nIndex = i;
			return htFolder;
		}
	}

	GetInsideRect(rc);
	CBarFolder *pbf = (CBarFolder*) m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return htNothing;

	nCount = pbf->GetItemCount();
	for (int i = m_nFirstItem; i < nCount; i++)
	{
		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(i);
		if (NULL == pi) continue;

		CRect rcItem;
		if (!IsSmallIconView()) 
		{
			GetIconRect(m_nSelFolder, i, rcItem);
			if (rcItem.PtInRect(point))
			{
				nIndex = i;
				return htItem;
			}
			else if (rcItem.top > rc.bottom) break;

			GetLabelRect(m_nSelFolder, i, rcItem);
			rcItem.top -= m_yLargeIconLabelOffset;

			if (rcItem.PtInRect(point))
			{
				nIndex = i;
				return htItem;
			}
			else if (rcItem.top > rc.bottom) break;
		}
		else
		{
			GetItemRect(m_nSelFolder, i, rcItem);
			if (rcItem.PtInRect(point))
			{
				nIndex = i;
				return htItem;
			}
			else if (rcItem.top > rc.bottom) break;
		}
	}
	return htNothing;
}

void CXTOutBarCtrl::HighlightFolder(const int nIndex)
{
	CWnd *pWnd = GetFocus();
	if (NULL != pWnd && this != pWnd && IsChild(pWnd)) return;

	if (m_nLastFolderHighlighted == nIndex) return;

	if (m_nLastFolderHighlighted >= 0)
	{
		CRect rc;
		if (GetFolderRect(m_nLastFolderHighlighted, rc))
		{
			CClientDC dc(this);
			CPen Pen(PS_SOLID, 1, m_crBackGroundColor1);//crShadowBorder);
			CPen *pOldPen = dc.SelectObject(&Pen);
			dc.MoveTo(rc.left, rc.bottom-1);
			dc.LineTo(rc.right-1, rc.bottom-1);
			dc.LineTo(rc.right-1, rc.top);
			CPen pn1(PS_SOLID, 1, m_cr3dFace);
			dc.SelectObject(&Pen);
			dc.MoveTo(rc.left+1, rc.bottom-2);
			dc.LineTo(rc.right-2, rc.bottom-2);
			dc.LineTo(rc.right-2, rc.top+1);
			dc.SelectObject(pOldPen);
		}
	}

	m_nLastFolderHighlighted = nIndex;
	if (m_nLastFolderHighlighted >= 0)
	{
		CRect rc;
		if (GetFolderRect(m_nLastFolderHighlighted, rc))
		{
			CClientDC dc(this);
			CPen Pen(PS_SOLID, 1, m_crDkShadowBorder);
			CPen *pOldPen = dc.SelectObject(&Pen);
			dc.MoveTo(rc.left, rc.bottom-1);
			dc.LineTo(rc.right-1, rc.bottom-1);
			dc.LineTo(rc.right-1, rc.top);
			CPen pn1(PS_SOLID, 1, m_crBackGroundColor1);
			dc.SelectObject(&Pen);
			dc.MoveTo(rc.left+1, rc.bottom-2);
			dc.LineTo(rc.right-2, rc.bottom-2);
			dc.LineTo(rc.right-2, rc.top+1);
			dc.SelectObject(pOldPen);
		}
	}
}

void CXTOutBarCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (GetFocus() != this) SetFocus();

	int nIndex, nHit = HitTestEx(point, nIndex);
	m_nLastDragItemDrawType = -1;

	CRect rcInside;
	GetInsideRect(rcInside);

	if (nHit == htFolder)
	{
		bool bHigh = true;
		CRect rc;
		GetFolderRect(nIndex, rc);

		if (::GetCapture() == NULL)
		{
			SetCapture();
			ASSERT(this == GetCapture());
			CClientDC dc(this);
			DrawFolder(&dc, nIndex, rc, true);
			AfxLockTempMaps();
			for (;;)
			{
				MSG msg;
				VERIFY(::GetMessage(&msg, NULL, 0, 0));

				if (CWnd::GetCapture() != this) break;

				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					{
						CPoint pt(msg.lParam);
						int nIndex1, nHit1 = HitTestEx(pt, nIndex1);
						if (nHit1 == htFolder && nIndex1 == nIndex)
						{
							if (!bHigh)
							{
								DrawFolder(&dc, nIndex, rc, true);
								bHigh = true;
							}
						}
						else
						{
							if (bHigh)
							{
								DrawFolder(&dc, nIndex, rc, false);
								bHigh = false;
							}
						}
					}
					break;

				case WM_LBUTTONUP:
					{
						if (bHigh)
						{
							DrawFolder(&dc, nIndex, rc, false);
							bHigh = false;
						}
						CPoint pt(msg.lParam);
						int nIndex2, nHit2 = HitTestEx(pt, nIndex2);
						if (nHit2 == htFolder && nIndex2 != m_nSelFolder)
							SetSelFolder(nIndex2);
					}

					goto ExitLoop2;

				case WM_KEYDOWN:	
					if (msg.wParam != VK_ESCAPE) 
						break;

				default:
					DispatchMessage(&msg);
					break;
				}
			}

		ExitLoop2:
			ReleaseCapture();
			AfxUnlockTempMaps(FALSE);
		}
		if (bHigh) InvalidateRect(rc, false);
	}
	else m_nLastSelectedFolder = -1;

	if (nHit == htItem)
	{
		m_nLastDragItemDraw = -1;
		bool bHigh = true, bDragging = false;
		CRect rc;
		GetItemRect(m_nSelFolder, nIndex, rc);

		HCURSOR hCursor = GetCursor();

		if (::GetCapture() == NULL)
		{
			SetCapture();
			ASSERT(this == GetCapture());
			CClientDC dc(this);
			HighlightItem(nIndex, true);
			AfxLockTempMaps();
			for (;;)
			{
				MSG msg;
				VERIFY(::GetMessage(&msg, NULL, 0, 0));

				if (CWnd::GetCapture() != this) break;

				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					{
						CPoint pt(msg.lParam);
						int nIndex3, nHit3 = HitTestEx(pt, nIndex3);
						if (bDragging)
						{
							if (nHit3 == htItem) 
							{
								DrawDragArrow(&dc, nIndex, nIndex3);
								SetCursor(m_hDragCursor);
								hCursor = m_hDragCursor;
							}
							else if (nHit3 == htFolder)
                            {
                                TRACE(_T("%d\n"), nIndex3);
                                SetCursor(m_hNoDragCursor);
                                hCursor = m_hNoDragCursor;
                                break;
                            }
                            else
							{
								CRect rcItem;
								GetItemRect(m_nSelFolder, GetItemCount() - 1, rcItem);
								if (pt.y > rcItem.bottom && pt.y < rcInside.bottom)
								{
									DrawDragArrow(&dc, nIndex, GetItemCount());
									SetCursor(m_hDragCursor);
									hCursor = m_hDragCursor;
								}
								else
								{
									DrawDragArrow(&dc, nIndex, -1);
									SetCursor(m_hNoDragCursor);
									hCursor = m_hNoDragCursor;
								}
							}
						}
						else
						{
							if (nHit3 == htItem && nIndex3 == nIndex)
							{
								if (!bHigh)
								{
									HighlightItem(nIndex, true);
									bHigh = true;
									m_bPressedHighlight = true;
								}
							}
							else 
							{
								if (nHit3 == htItem)
								{
									if (bHigh)
									{
										HighlightItem(nIndex, false);
										bHigh = false;
										m_bPressedHighlight = false;
									}
								}
								else
								{
									if (m_dwFlags&fDragItems)
									{
										HighlightItem(nIndex, true);
										bHigh = true;
										bDragging = true;

										SetCursor(m_hDragCursor);
										hCursor = m_hDragCursor;

										m_bPressedHighlight = true;
									}
								}
							}
						}
					}
					break;

				case WM_SETCURSOR:
					SetCursor(hCursor);
					break;

				case WM_LBUTTONUP:
					{
						if (bHigh)
						{
							HighlightItem(-1);
							bHigh = false;
						}
						CPoint pt(msg.lParam);
						int nIndex4, nHit4 = HitTestEx(pt, nIndex4);
						if (!bDragging)
						{
							if (nHit4 == htItem && nIndex4 == nIndex) 
							{
								if (m_nSelAnimTiming > 0 && nIndex != m_nLastSel && m_nLastSel >= 0)
								{
									DrawAnimItem(0, 0, m_nLastSel);
								}

								if (m_dwFlags&fSelHighlight && m_nLastSel >= 0)
								{
									CRect rc;
									GetIconRect(m_nSelFolder, m_nLastSel, rc);
									rc.InflateRect(1,1);
									InvalidateRect(rc);
								}

								m_nLastSel = nIndex;

								if (m_dwFlags&fSelHighlight && m_nLastSel >= 0)
								{
									CRect rc;
									GetIconRect(m_nSelFolder, m_nLastSel, rc);
									rc.InflateRect(1,1);
									InvalidateRect(rc);
								}

                                OUTBAR_INFO ob = {0};
                                ob.nFolder = m_nSelFolder;
                                ob.nIndex = nIndex4;
								GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_OB_ITEMCLICK, (LPARAM)&ob);
							}
						}
						else
						{
							if (nHit4 == htItem)
							{
                                if (nIndex4 != nIndex)
                                {
                                    OUTBAR_INFO ob = {0};
                                    ob.nDragFromFolder = m_nSelFolder;
                                    ob.nDragToFolder = m_nSelFolder;
                                    ob.nDragFrom = nIndex;
                                    ob.nDragTo = nIndex;
                                    if (GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_OB_DRAGITEM, (LPARAM)&ob))
                                    {
                                        CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
                                        if (NULL == pbf) return;
                                        CBarItem *piFrom = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
                                        if (NULL == piFrom) return;
                                        pbf->m_arItems.RemoveAt(nIndex);
                                        if (nIndex4 > nIndex) nIndex4--;
                                        pbf->m_arItems.InsertAt(nIndex4, piFrom);
                                    }
                                }
							}
							else if (nHit4 == htFolder)
                            {
                                //-------------------------------------------------------
                                // 只能在用户创建的组施到
                                if ((0 != nIndex4) && (1 != nIndex4))
                                {
                                    OUTBAR_INFO ob = {0};
                                    ob.nDragFromFolder = m_nSelFolder;
                                    ob.nDragToFolder = nIndex4;
                                    ob.nDragFrom = nIndex;
                                    ob.nDragTo = this->GetItemCount(nIndex4);
                                    if (GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_OB_DRAGITEM, (LPARAM)&ob))
                                    {
                                        CBarFolder *pbfFrom = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
                                        if (NULL == pbfFrom) return;
                                        CBarItem *piFrom = (CBarItem*)pbfFrom->m_arItems.GetAt(nIndex);
                                        if (NULL == piFrom) return;
                                        pbfFrom->m_arItems.RemoveAt(nIndex);
                                        CBarFolder *pbfTo = (CBarFolder*)m_arFolder.GetAt(nIndex4);
                                        if (NULL == pbfTo) return;
                                        pbfTo->m_arItems.Add((void *)piFrom);
                                    }
                                }
                            }
                            else
							{
								CRect rcItem;
								GetItemRect(m_nSelFolder, GetItemCount() - 1, rcItem);
								if (pt.y > rcItem.bottom && pt.y < rcInside.bottom)
								{
									OUTBAR_INFO ob = {0};
                                    ob.nDragFromFolder = m_nSelFolder;
                                    ob.nDragToFolder = m_nSelFolder;
                                    ob.nDragFrom = nIndex;
                                    ob.nDragTo = this->GetItemCount(m_nSelFolder) - 1;
									if (GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_OB_DRAGITEM, (LPARAM)&ob))
									{
										CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
										if (NULL == pbf) return;
										CBarItem *piFrom = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
										if (NULL == piFrom) return;
										pbf->m_arItems.RemoveAt(nIndex);
										pbf->m_arItems.Add((void *)piFrom);
									}
								}
							}
						}
					}

					goto ExitLoop4;

				default:
					DispatchMessage(&msg);
					break;
				}
			}

		ExitLoop4:
			ReleaseCapture();
			AfxUnlockTempMaps(FALSE);
			if (bDragging) 
			{
				Invalidate();
			}
		}
		m_bPressedHighlight = false;
		if (bHigh) InvalidateRect(rc, false);
	}
	else m_nLastItemHighlighted = -1;

	if (nHit == htDownScroll)
	{
		m_bLooping = true;
		bool bHigh = true;

		if (::GetCapture() == NULL)
		{
			SetCapture();
			ASSERT(this == GetCapture());
			CClientDC dc(this);
			
			dc.DrawFrameControl(m_rcDownArrow, DFC_SCROLL, DFCS_SCROLLDOWN|DFCS_PUSHED);
			
			SetTimer(2,300,NULL);
			AfxLockTempMaps();
			for (;;)
			{
				MSG msg;
				VERIFY(::GetMessage(&msg, NULL, 0, 0));

				if (CWnd::GetCapture() != this) break;

				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					{
						CPoint pt(msg.lParam);
						if (m_rcDownArrow.PtInRect(pt))
						{
							if (bHigh == false)
							{
								dc.DrawFrameControl(m_rcDownArrow, DFC_SCROLL, DFCS_SCROLLDOWN|DFCS_PUSHED);

								bHigh = true;
								m_bDownArrow = true;
								m_bDownPressed = true;
							}
						}
						else
						{
							if (bHigh == true)
							{
								dc.DrawFrameControl(m_rcDownArrow, DFC_SCROLL, DFCS_SCROLLDOWN);

								bHigh = false;
								m_bDownArrow = false;
								m_bDownPressed = false;
							}
						}
					}
					break;

				case WM_LBUTTONUP:
					{
						if (bHigh)
						{
							dc.DrawFrameControl(m_rcDownArrow, DFC_SCROLL, DFCS_SCROLLDOWN);
							bHigh = false;
						}
						m_bDownArrow = false;
						CPoint pt(msg.lParam);
						if (m_rcDownArrow.PtInRect(pt))
						{
							CRect itrc;
							GetItemRect(m_nSelFolder, GetItemCount() - 1, itrc);
							CRect crc;
							GetInsideRect(crc);
							if (itrc.bottom > crc.bottom)
							{
								m_nFirstItem ++;
								InvalidateRect(crc, true);
							}
						}
					}
					goto ExitLoop3;


				case WM_TIMER:
					{
						if (msg.wParam == 2)
						{
							if (bHigh)
							{
								CPoint pt(msg.pt);
								ScreenToClient(&pt);
								if (m_rcDownArrow.PtInRect(pt))
								{
									m_bDownPressed = true;
									CRect itrc;
									GetItemRect(m_nSelFolder, GetItemCount() - 1, itrc);
									CRect crc;
									GetInsideRect(crc);
									if (itrc.bottom > crc.bottom)
									{
										m_nFirstItem ++;
										InvalidateRect(crc, true);
									}
									else goto ExitLoop3;
								}
								else m_bDownPressed = false;
							}
						}
						break;
					}

				case WM_KEYDOWN:	
					if (msg.wParam != VK_ESCAPE) 
						break;

				default:
					DispatchMessage(&msg);
					break;
				}
			}

		ExitLoop3:
			KillTimer(2);
			ReleaseCapture();
			AfxUnlockTempMaps(FALSE);
			m_bLooping = false;
			m_bDownPressed = false;
			m_bDownArrow = false;
			CRect crc;
			GetInsideRect(crc);
			InvalidateRect(crc, true);
		}
	}

	if (nHit == htUpScroll)
	{
		m_bLooping = true;
		bool bHigh = true;

		if (::GetCapture() == NULL)
		{
			SetCapture();
			ASSERT(this == GetCapture());
			CClientDC dc(this);

			dc.DrawFrameControl(m_rcUpArrow, DFC_SCROLL, DFCS_SCROLLUP|DFCS_PUSHED);
			
			SetTimer(2,300,NULL);
			AfxLockTempMaps();
			for (;;)
			{
				MSG msg;
				VERIFY(::GetMessage(&msg, NULL, 0, 0));

				if (CWnd::GetCapture() != this) break;

				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					{
						CPoint pt(msg.lParam);
						if (m_rcUpArrow.PtInRect(pt))
						{
							if (bHigh == false)
							{
								dc.DrawFrameControl(m_rcUpArrow, DFC_SCROLL, DFCS_SCROLLUP|DFCS_PUSHED);

								bHigh = true;
								m_bUpArrow = true;
								m_bUpPressed = true;
							}
						}
						else
						{
							if (bHigh == true)
							{
								dc.DrawFrameControl(m_rcUpArrow, DFC_SCROLL, DFCS_SCROLLUP);

								bHigh = false;
								m_bUpArrow = false;
								m_bUpPressed = false;
							}
						}
					}
					break;

				case WM_LBUTTONUP:
					{
						if (bHigh)
						{
							dc.DrawFrameControl(m_rcUpArrow, DFC_SCROLL, DFCS_SCROLLUP);
							bHigh = false;
						}
						m_bUpArrow = false;
						CPoint pt(msg.lParam);
						if (m_rcUpArrow.PtInRect(pt))
						{
							if (m_nFirstItem > 0 ) 
							{
								m_nFirstItem --;
								CRect crc;
								GetInsideRect(crc);
								InvalidateRect(crc, true);
							}
						}
					}

					goto ExitLoop;

				case WM_TIMER:
					{
						if (msg.wParam == 2)
						{
							if (bHigh)
							{
								CPoint pt(msg.pt);
								ScreenToClient(&pt);
								if (m_rcUpArrow.PtInRect(pt))
								{
									m_bUpPressed = true;
									if (m_nFirstItem > 0) 
									{
										m_nFirstItem --;
										CRect crc;
										GetInsideRect(crc);
										InvalidateRect(crc, true);
									}
									else goto ExitLoop;
								}
								else m_bUpPressed = false;
							}
						}
						break;
					}
				case WM_KEYDOWN:	
					if (msg.wParam != VK_ESCAPE) break;

				default:
					DispatchMessage(&msg);
					break;
				}
			}

		ExitLoop:
			KillTimer(2);
			ReleaseCapture();
			AfxUnlockTempMaps(FALSE);
			m_bLooping = false;
			m_bUpPressed = false;
			m_bUpArrow = false;
			CRect crc;
			GetInsideRect(crc);
			InvalidateRect(crc, true);
		}
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CXTOutBarCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (GetFocus() != this) SetFocus();

	int nIndex, nHit = HitTestEx(point, nIndex);

	GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_OB_ITEMDBCLICK, this->GetItemData(nIndex));

	CWnd::OnLButtonDblClk(nFlags, point);
}


int CXTOutBarCtrl::InsertItem(const int nFolder, const int nIndex, const char *pszText, const int nImage, const DWORD dwData)
{
	if (nFolder < 0 || nFolder >= GetFolderCount()) return -1;

	CBarFolder *pbf = (CBarFolder *) m_arFolder.GetAt(nFolder);
	if (NULL == pbf) return -1;
	return pbf->InsertItem(nIndex, pszText, nImage, dwData);
}

int CXTOutBarCtrl::GetItemCount(int nIndex /*= -1*/) const
{
	if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return -1;

	if (-1 == nIndex) nIndex = m_nSelFolder;

	CBarFolder *pbf = (CBarFolder*) m_arFolder.GetAt(nIndex);
	if (NULL == pbf) return -1;
	return 	pbf->GetItemCount();
}

void CXTOutBarCtrl::SetSelFolder(const int nIndex, bool bAnimate/* = true*/)
{
	if (nIndex < 0 || nIndex >= GetFolderCount()) return;

	if (nIndex == m_nSelFolder) return;

	if (!bAnimate)
	{
		m_nSelFolder = nIndex;
		return;
	}

	CWnd *pWnd = GetFolderChild();
	if (pWnd) pWnd->ShowWindow(SW_HIDE);

	if (nIndex != m_nSelFolder)
	{
		if (m_dwFlags&fAnimation && m_nAnimationTickCount >= 0) AnimateFolderScroll(m_nSelFolder, nIndex);
	}

	m_nSelFolder = nIndex;
	m_nFirstItem = 0;
	m_nLastSel = -1;

	pWnd = GetFolderChild();
	if (pWnd)
	{
		CRect rc;
		GetInsideRect(rc);
		pWnd->MoveWindow(rc);
		pWnd->ShowWindow(SW_SHOW);
	}	

	//GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, NM_FOLDERCHANGE, (LPARAM)m_nSelFolder);

	Invalidate();
}
							
int CXTOutBarCtrl::GetFolderCount() const
{
	return (int)m_arFolder.GetSize();
}

int CXTOutBarCtrl::GetSelFolder() const
{
	return m_nSelFolder;
}

void CXTOutBarCtrl::RemoveFolder(const int nIndex)
{
	if (nIndex < 0 || nIndex >= GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nIndex);
	if (NULL == pbf) return;

	delete pbf;
	m_arFolder.RemoveAt(nIndex);
	if (m_nSelFolder >= nIndex) m_nSelFolder = nIndex - 1;
	if (m_nSelFolder < 0 && GetFolderCount() > 0) m_nSelFolder = 0;
	m_nLastFolderHighlighted = m_nSelFolder;
	Invalidate();
}

int CXTOutBarCtrl::CBarFolder::InsertItem(int nIndex, const char *pszText, const int nImage, const DWORD dwData)
{
	if (nIndex < 0 || nIndex >= GetItemCount()) nIndex = GetItemCount();

	CBarItem *pbf = new CBarItem(pszText, nImage, dwData);
	ASSERT(pbf);

	if (nIndex < GetItemCount()) 
		m_arItems.InsertAt(nIndex, (void*)pbf);
	else 
		m_arItems.Add((void*)pbf);

	return nIndex;
}

int CXTOutBarCtrl::GetCountPerPage() const
{
	return 0;
}

CImageList * CXTOutBarCtrl::SetImageList(CImageList *pImageList, int nImageList)
{
	CImageList *pOutImageList = NULL;
	if (nImageList == fSmallIcon)
	{
		pOutImageList = m_pSmallImageList;
		m_pSmallImageList = pImageList;
	}
	else if (nImageList == fLargeIcon)
	{
		pOutImageList = m_pLargeImageList;
		m_pLargeImageList = pImageList;
	}
	return pOutImageList;
}

CImageList * CXTOutBarCtrl::GetImageList(CImageList *pImageList, int nImageList)
{
	if (nImageList == fSmallIcon) return m_pSmallImageList;
	else if (nImageList == fLargeIcon) return m_pLargeImageList;
	return NULL;
}

CImageList * CXTOutBarCtrl::SetFolderImageList(const int nFolder, CImageList *pImageList, int nImageList)
{
	if (nFolder < 0 || nFolder >= GetFolderCount()) return NULL;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
	CImageList *pOutImage = NULL;
	if (nImageList == fSmallIcon)
	{
		pOutImage = pbf->m_pSmallImageList;
		pbf->m_pSmallImageList = pImageList;
	}
	else if (nImageList == fLargeIcon)
	{
		pOutImage = pbf->m_pLargeImageList;
		pbf->m_pLargeImageList = pImageList;
	}
	return pOutImage;
}


CXTOutBarCtrl::CBarItem::CBarItem(const char *pszName, const int nImage, DWORD dwData)
{
	if (NULL == pszName) return;

	m_pszItem = NULL;
	m_nImage = nImage;
	m_dwData = dwData;
	if (NULL == m_pszItem)
	{
		m_pszItem = new char[lstrlen(pszName)+1];
		ASSERT(m_pszItem);
		lstrcpy(m_pszItem, pszName);
	}
}

CXTOutBarCtrl::CBarItem::~CBarItem()
{
	if (m_pszItem) delete [] m_pszItem;
}

int CXTOutBarCtrl::CBarFolder::GetItemCount()
{
	return (int)m_arItems.GetSize();
}

void CXTOutBarCtrl::PaintItems(CDC *pDC, const int nFolder, CRect rc)
{
	if (nFolder < 0 || nFolder >= GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
	if (NULL == pbf) return;

	int nCount = pbf->GetItemCount();
	CRect rcInside;
	GetInsideRect(rcInside);
	int nSaveDC = pDC->SaveDC();
	CRgn itemRegion;
	itemRegion.CreateRectRgnIndirect(&rcInside);
	pDC->SelectClipRgn(&itemRegion);
	itemRegion.DeleteObject();

	for (int i = m_nFirstItem; i < nCount; i++)
	{
		CBarItem *pi = (CBarItem*) pbf->m_arItems.GetAt(i);
		if (NULL == pi) continue;
		CRect rcItem;
		GetItemRect(nFolder, i, rcItem);
        if (rcItem.top > rcInside.bottom) break;
		else DrawItem(pDC, nFolder, rcItem, i);
	}
	pDC->RestoreDC(nSaveDC);
}

void CXTOutBarCtrl::PaintItemsEx(CDC *pDC, const int nFolder, CRect rc)
{
    if (nFolder < 0 || nFolder >= GetFolderCount()) return;

    CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
    if (NULL == pbf) return;

    int nCount = pbf->GetItemCount();
    for (int i = m_nFirstItem; i < nCount; i++)
    {
        CBarItem *pi = (CBarItem*) pbf->m_arItems.GetAt(i);
        if (NULL == pi) continue;
        CRect rcItem;
        GetItemRect(nFolder, i, rcItem);
        rcItem.top -= nFolder*m_nFolderHeight;
        rcItem.bottom -= nFolder*m_nFolderHeight;
        if (rcItem.top > rc.bottom) break;
        else DrawItem(pDC, nFolder, rcItem, i);
    }
}

CSize CXTOutBarCtrl::GetItemSize(const int nFolder, const int nIndex, const int nType)
{
	if (nFolder < 0 || nFolder >= GetFolderCount()) return CSize(0, 0);

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
	if (NULL == pbf) return CSize(0, 0);

	if (nIndex < 0 || nIndex >= pbf->GetItemCount()) return CSize(0, 0);

	CBarItem * pi = (CBarItem *) pbf->m_arItems.GetAt(nIndex);

	CSize szImage(0,0);
	CSize szLabel(0,0);
	CSize szAll(0,0);

	if (pi->m_nImage >= 0)
	{
		if (nType != ircLabel)
		{
			CImageList *ImageList = GetFolderImageList(nFolder, IsSmallIconView());
			if (NULL == ImageList) return CSize(0, 0);

			IMAGEINFO ImageInfo = {0};
			ImageList->GetImageInfo(pi->m_nImage, &ImageInfo);
			szImage = CRect(ImageInfo.rcImage).Size();
		}
	}
	if (pi->m_pszItem)
	{
		if (nType != ircIcon)
		{
			CClientDC dc(this);
			CFont *pOldFont = (CFont*)dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
			if (IsSmallIconView())
			{
				szLabel = dc.GetTextExtent(pi->m_pszItem, lstrlen(pi->m_pszItem));
			}
			else
			{
				CRect rc;
				GetInsideRect(rc);
				rc.bottom = rc.top;
				dc.DrawText(pi->m_pszItem, lstrlen(pi->m_pszItem), rc, DT_CALCRECT|DT_CENTER|DT_WORDBREAK);
				szLabel = rc.Size();
			}
			dc.SelectObject(pOldFont);
		}
	}
	if (IsSmallIconView())
	{
		if (nType == ircIcon) szAll = szImage;
		else if (nType == ircLabel) szAll = szLabel;
		else if (nType == ircAll) szAll = CSize(szImage.cx + szLabel.cx + m_xSmallIconLabelOffset, szImage.cy > szLabel.cy ? szImage.cy : szLabel.cy);
	}
	else
	{
		if (nType == ircIcon) szAll = szImage;
		else if (nType == ircLabel) szAll = szLabel;
		else if (nType == ircAll)
		{
			szAll = CSize(szImage.cx > szLabel.cx ? szImage.cx : szLabel.cx, szLabel.cy + szImage.cy + m_yLargeIconLabelOffset + m_yLargeIconSpacing);
		}
	}
	return szAll;
}

CImageList * CXTOutBarCtrl::GetFolderImageList(const int nIndex, const bool bSmall) const
{
	if (nIndex < 0 || nIndex >= GetFolderCount()) return NULL;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nIndex);
	if (NULL == pbf) return NULL;
	if (bSmall)
	{
		if (pbf->m_pSmallImageList) return pbf->m_pSmallImageList;
		else return m_pSmallImageList;
	}
	if (pbf->m_pLargeImageList) return pbf->m_pLargeImageList;
	else return m_pLargeImageList;
}

void CXTOutBarCtrl::DrawItem(CDC *pDC, const int nFolder, CRect rc, const int nIndex, const bool bOnlyImage)
{
	if (nFolder < 0 || nFolder >= GetFolderCount()) return;

	CImageList *pImageList = GetFolderImageList(nFolder, IsSmallIconView());
	if (NULL == pImageList) return;
	
	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
	if (NULL == pbf) return;

	if (nIndex < 0 || nIndex >= pbf->GetItemCount()) return;
	CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
	if (NULL == pi) return;


	CFont *pOldFont = (CFont *) pDC->SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	COLORREF crOldText = pDC->SetTextColor(m_crTextColor);
	int nOldBKMode = pDC->SetBkMode(TRANSPARENT);

	if (IsSmallIconView())
	{
		IMAGEINFO ImageInfo = {0};
		pImageList->GetImageInfo(pi->m_nImage, &ImageInfo);
		CSize szImage = CRect(ImageInfo.rcImage).Size();
		CPoint pt;
		pt.x = rc.left + 2;
		pt.y = rc.top + (rc.Height() - szImage.cy) / 2;
		pImageList->Draw(pDC, pi->m_nImage, pt, ILD_NORMAL);

		if (!bOnlyImage)
		{
			rc.left += szImage.cx + m_xSmallIconLabelOffset;
			pDC->TextOut(rc.left, rc.top, CString(pi->m_pszItem));
		}
	}
	else
	{

		IMAGEINFO ImageInfo = {0};
		pImageList->GetImageInfo(pi->m_nImage, &ImageInfo);
		CSize szImage = CRect(ImageInfo.rcImage).Size();
		CPoint pt;
		pt.x = rc.left + (rc.Width() - szImage.cx) / 2;
		pt.y = rc.top;
		pImageList->Draw(pDC, pi->m_nImage, pt, ILD_NORMAL);
		if (!bOnlyImage)
		{
			rc.top += szImage.cy + m_yLargeIconLabelOffset;
			pDC->DrawText(pi->m_pszItem, lstrlen(pi->m_pszItem), rc, DT_CENTER|DT_WORDBREAK);
		}
	}
	
/*	if (dwFlags&fSelHighlight && iLastSel == index && iLastSel >= 0)
	{
		CRect rc;
		GetIconRect(iSelFolder, iLastSel, rc);
		rc.InflateRect(1,1);
		pDC->Draw3dRect(rc, crDkShadowBorder, cr3dFace);
	}
*/
	pDC->SetTextColor(crOldText);
	pDC->SelectObject(pOldFont);
	pDC->SetBkMode(nOldBKMode);
}
	

BOOL CXTOutBarCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	int nIndex, nHit = HitTestEx(pt, nIndex);
	if (nHit == htFolder)
	{
		SetCursor(m_hHandCursor);
		return true;
	}
		
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CXTOutBarCtrl::GetVisibleRange(const int nFolder, int &nFirst, int &nLast)
{
	nFirst = m_nFirstItem;
	CRect rcInside;
	GetInsideRect(rcInside);

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
	if (NULL == pbf) return;

	int nCount = pbf->GetItemCount();
	for (int i = m_nFirstItem; i < nCount; i++)
	{
		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(i);
		if (NULL == pi) continue;

		CRect rcItem;
		GetItemRect(nFolder, i, rcItem);
		if (rcItem.bottom > rcInside.bottom) 
		{
			nLast = i - 1;
			break;
		}
		else nLast = i;
	}
}

void CXTOutBarCtrl::OnSize(UINT nType, int cx, int cy) 
{
	m_bUpArrow = m_bDownArrow = false;

	CWnd::OnSize(nType, cx, cy);

	CRect rc;
	GetInsideRect(rc);
	int nCount = GetFolderCount();
	for (int i = 0; i < nCount; i++)
	{
		//CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(i);
		CWnd *pWnd = GetFolderChild(i);
		if (pWnd) pWnd->SetWindowPos(0, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
	}
}

void CXTOutBarCtrl::HighlightItem(const int nIndex, const bool bPressed)
{
	CWnd *pWnd = GetFocus();
	if (NULL != pWnd && this != pWnd && IsChild(pWnd)) return;

	static bool bOldPressed = false;
	if (m_nLastItemHighlighted == nIndex && bOldPressed == bPressed) return;

	bOldPressed = bPressed;

	CClientDC dc(this);

	CRect rcInside;
	GetInsideRect(rcInside);
	int nSaveDC = dc.SaveDC();
	CRgn itemRegion;
	itemRegion.CreateRectRgnIndirect(&rcInside);
	dc.SelectClipRgn(&itemRegion);
	itemRegion.DeleteObject();

	if (m_nLastItemHighlighted >= 0 && IsValidItem(m_nLastItemHighlighted))
	{
		CRect rc;
		GetIconRect(m_nSelFolder, m_nLastItemHighlighted, rc);
		rc.InflateRect(1,1);
		
		dc.Draw3dRect(rc, m_crBackGroundColor, m_crBackGroundColor);
	}
	if (m_nSelAnimTiming > 0 && nIndex == m_nLastSel)
	{
		m_nLastItemHighlighted = -1;
		return;
	}
	if (m_dwFlags&fSelHighlight && m_nLastSel == nIndex)
	{
		m_nLastItemHighlighted = -1;
		return;
	}

	m_nLastItemHighlighted = nIndex;
	if (m_nLastItemHighlighted >= 0 && IsValidItem(m_nLastItemHighlighted))
	{
		CRect rc;
		GetIconRect(m_nSelFolder, m_nLastItemHighlighted, rc);
		rc.InflateRect(1,1);
		if (bPressed)
		{
			dc.Draw3dRect(rc, m_crDkShadowBorder, m_cr3dFace);
		}
		else
		{
		    dc.Draw3dRect(rc, m_cr3dFace, m_crDkShadowBorder);
		}
  }
	dc.RestoreDC(nSaveDC);
}

void CXTOutBarCtrl::GetIconRect(const int nFolder, const int nIndex, CRect &rect)
{
	CRect rc;
	GetInsideRect(rc);
	int nTop = rc.top;
	CSize sz(0,0);
	int nOffsetY = 0;
	int nSpacing = IsSmallIconView() ? m_ySmallIconSpacing : m_yLargeIconSpacing;

	for (int i = 0; i < nIndex; i++)
	{
		sz = GetItemSize(nFolder, i, ircAll);
		nTop += sz.cy;
		nTop += nSpacing;
		if (i == m_nFirstItem - 1) nOffsetY = nTop - rc.top;
	}
	nTop += nSpacing;

	sz = GetItemSize(nFolder, nIndex, ircIcon);
	if (IsSmallIconView())
	{
		rect.SetRect(rc.left, nTop, rc.left + sz.cx, nTop + sz.cy);
		rect.left += m_xLeftMargin + 2;
		rect.right += m_xLeftMargin + 2;
		rect.top -= m_yTopMargin;
		rect.bottom -= m_yTopMargin;

		rect.top -= nOffsetY;
		rect.bottom -= nOffsetY;
	}
	else
	{
		rect.SetRect(rc.left + (rc.Width() - sz.cx)/2, nTop, rc.left + (rc.Width() - sz.cx)/2 + sz.cx, nTop + sz.cy);
		rect.top -= nOffsetY + 3;
		rect.bottom -= nOffsetY + 2;
	}
}

void CXTOutBarCtrl::GetLabelRect(const int nFolder, const int nIndex, CRect &rect)
{
	CRect rc;
	GetInsideRect(rc);
	int nTop = rc.top;
	CSize sz(0,0);
	int nOffsetY = 0;
	int nSpacing = IsSmallIconView() ? m_ySmallIconSpacing : m_yLargeIconSpacing;

	for (int i = 0; i < nIndex; i++)
	{
		sz = GetItemSize(nFolder, i, ircAll);
		nTop += sz.cy;
		nTop += nSpacing;
		if (i == m_nFirstItem - 1) nOffsetY = nTop - rc.top;
	}
	nTop += nSpacing;

	sz = GetItemSize(nFolder, nIndex, ircAll);

	CSize szLabel = GetItemSize(nFolder, nIndex, ircLabel);

	if (IsSmallIconView())
	{
		rect.SetRect(rc.left, nTop, rc.left + sz.cx, nTop + sz.cy);
		rect.left += m_xLeftMargin + 2;
		rect.right += m_xLeftMargin + 2;
		rect.top  += m_yTopMargin - 5;
		rect.bottom += m_yTopMargin - 5;
	}
	else
	{
		rect.SetRect(rc.left + (rc.Width() - sz.cx)/2, nTop, rc.left + (rc.Width() - sz.cx)/2 + sz.cx, nTop + sz.cy);
		rect.top -= nOffsetY + 3;
		rect.bottom -= nOffsetY + 2;

		rect.bottom -= m_yLargeIconSpacing;
		rect.top = rect.bottom - szLabel.cy;
	}
}


void CXTOutBarCtrl::StartGroupEdit(const int nIndex)
{
	CXTOuBarEdit *pEdit = new CXTOuBarEdit;
	pEdit->m_nIndex = nIndex;
	CRect rc;
	GetFolderRect(nIndex, rc);
	rc.InflateRect(-2,-2);
	pEdit->Create(WS_CHILD|WS_VISIBLE|ES_CENTER|ES_MULTILINE,rc,this,1);
	pEdit->m_msgSend = NM_OB_ONGROUPENDEDIT;
	pEdit->ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
	if (nIndex < 0 || nIndex > GetFolderCount()) return;
	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nIndex);
	if (NULL == pbf) return;
	pEdit->SetWindowText(pbf->m_pszName);
	pEdit->SetFocus();
}

void CXTOutBarCtrl::StartItemEdit(const int nIndex)
{
	if (m_nSelFolder < 0 || m_nSelFolder > GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return;

	if (nIndex < 0 || nIndex >= pbf->GetItemCount()) return;
	CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
	if (NULL == pi) return;

	CXTOuBarEdit *pEdit = new CXTOuBarEdit;
	pEdit->m_nIndex = nIndex;
	CRect rc, rcInside;
	GetLabelRect(m_nSelFolder, nIndex, rc);
	GetInsideRect(rcInside);
	
	DWORD dwFlag = WS_CHILD|WS_VISIBLE|WS_BORDER;

	if (!IsSmallIconView())
	{
		rc.left = rcInside.left + 5;
		rc.right = rcInside.right - 5;
		rc.bottom += 5;
		dwFlag |= ES_CENTER|ES_MULTILINE;
	}
	else 
	{
		CRect rcIcon;
		GetIconRect(m_nSelFolder, nIndex, rcIcon);
		dwFlag |= ES_AUTOHSCROLL;
		rc.OffsetRect(rcIcon.Width()+1, -6);
		pEdit->m_bNoDown = true;
	}

	pEdit->Create(dwFlag, rc, this, 1);
	pEdit->m_msgSend = NM_OB_ONLABELENDEDIT;
	
	pEdit->SetWindowText(pi->m_pszItem);
	pEdit->SetFocus();

}

void CXTOutBarCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_nHitInternal1 = HitTestEx(point, m_nHitInternal2);
/*
	CGfxPopupMenu cMenu;
	cMenu.CreatePopupMenu();

	cMenu.AppendMenu(MF_STRING, ID_OUTBAR_SMALLICON, _ID_GFX_SMALLICON);
	cMenu.AppendMenu(MF_STRING, ID_OUTBAR_LARGEICON, _ID_GFX_LARGEICON);

	if (m_iHitInternal1 == htItem)
	{
		if (m_dwFlags&fRemoveItems || m_dwFlags&fEditItems)
		{
			cMenu.AppendMenu(MF_SEPARATOR);
			if (m_dwFlags&fRemoveItems)
				cMenu.AppendMenu(MF_STRING, ID_OUTBAR_REMOVEITEM, _ID_GFX_REMOVEITEM);

			if (m_dwFlags&fEditItems)
				cMenu.AppendMenu(MF_STRING, ID_OUTBAR_RENAMEITEM, _ID_GFX_RENAMEITEM);
		}
	}
	else if (m_iHitInternal1 == htFolder)
	{
		if (m_dwFlags&fRemoveGroups || m_dwFlags&fEditGroups)
		{
			cMenu.AppendMenu(MF_SEPARATOR);

			if (m_dwFlags&fRemoveGroups)
				cMenu.AppendMenu(MF_STRING, ID_OUTBAR_REMOVEITEM, _ID_GFX_REMOVEITEM);

			if (m_dwFlags&fEditGroups)
				cMenu.AppendMenu(MF_STRING, ID_OUTBAR_RENAMEITEM, _ID_GFX_RENAMEITEM);
		}
	}
	
	//cMenu.LoadToolBarResource(IDR_MAINFRAME);
	cMenu.RemapMenu(&cMenu);
	cMenu.EnableMenuItems(&cMenu, this);

	CPoint pt(point);
	ClientToScreen(&pt);
	cMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);

	cMenu.DestroyMenu();

 
    CPoint pt(point);
    ClientToScreen(&pt);

    if (m_nHitInternal1 == htFolder)
    {
        if (0 == m_nHitInternal2)
            m_mFolder.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
        else
            m_mFolder1.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
    }
    else if (m_nHitInternal1 == htItem)
    {
        if (0 == m_nSelFolder)
            m_mItem.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
        else if (1 != GetFolderData(m_nSelFolder))
            m_mItem1.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
    }
*/
	CWnd::OnRButtonDown(nFlags, point);
}

/*
void CXTOutBarCtrl::OnOutBarLargeicon() 
{
	SetSmallIconView(false);
	Invalidate();	
}

void CXTOutBarCtrl::OnUpdateOutBarLargeicon(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSmallIconView());
}

void CXTOutBarCtrl::OnOutBarSmallicon() 
{
	SetSmallIconView(true);	
	Invalidate();
}

void CXTOutBarCtrl::OnUpdateOutBarSmallicon(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!IsSmallIconView());
}

void CXTOutBarCtrl::OnOutBarRemoveitem() 
{
	if (m_nHitInternal1 == htFolder)
	{
		RemoveFolder(m_nHitInternal2);
	}
	else if (m_nHitInternal1 == htItem)
	{
		RemoveItem(m_nSelFolder, m_nHitInternal2);
	}
}

void CXTOutBarCtrl::OnUpdateOutBarRemoveitem(CCmdUI* pCmdUI) 
{
		
}

void CXTOutBarCtrl::OnOutBarRenameitem() 
{
	if (m_nHitInternal1 == htFolder)
	{
		StartGroupEdit(m_nHitInternal2);
	}
	else if (m_nHitInternal1 == htItem)
	{
		StartItemEdit(m_nHitInternal2);
	}
}

void CXTOutBarCtrl::OnUpdateOutBarRenameitem(CCmdUI* pCmdUI) 
{
}
*/
void CXTOutBarCtrl::RemoveItem(const int nFolder, const int nIndex)
{
	if (nFolder < 0 || nFolder >= GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
	if (NULL == pbf) return;

	if (nIndex < 0 || nIndex >= pbf->GetItemCount()) return;
	if (IsValidItem(nIndex, nFolder))
	{
		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
		delete pi;

		pbf->m_arItems.RemoveAt(nIndex);
		CRect rc;
		GetInsideRect(rc);
		InvalidateRect(rc);
	}
}

bool CXTOutBarCtrl::IsValidItem(const int nIndex, const int nFolder/* = -1*/) const
{
	int nCurFolder = (nFolder == -1) ? m_nSelFolder : nFolder;

	if (nCurFolder < 0 || nCurFolder >= GetFolderCount()) return false;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nCurFolder);
	if (NULL == pbf) return false;
	return (nIndex >= 0 && nIndex < pbf->GetItemCount());
}

DWORD CXTOutBarCtrl::GetItemData(const int nIndex) const
{
	if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return 0;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return 0;
	if (IsValidItem(nIndex))
	{
		CBarItem *pi = (CBarItem*) pbf->m_arItems.GetAt(nIndex);
		if (NULL == pi) return 0;
		return pi->m_dwData;
	}
	return 0;
}

int CXTOutBarCtrl::GetItemImage(const int nIndex) const
{
	if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return -1;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return -1;
	if (IsValidItem(nIndex))
	{
		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
		if (NULL == pi) return -1;
		return pi->m_nImage;
	}
	return -1;
}

void CXTOutBarCtrl::SetItemData(const int nIndex, const DWORD dwData)
{
	if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return;
	if (IsValidItem(nIndex))
	{
		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
		if (NULL == pi) return;
		pi->m_dwData = dwData;
	}
}

void CXTOutBarCtrl::SetItemImage(const int nIndex, const int nImage)
{
	if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return;

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return;
	if (IsValidItem(nIndex))
	{
		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
		pi->m_nImage = nImage;
	}
}

void CXTOutBarCtrl::DrawDragArrow(CDC *pDC, const int nFrom, const int nTo)
{
	if (nTo == m_nLastDragItemDraw) return;
	CRect rc;
	if (m_nLastDragItemDraw >= 0)
	{
		GetDragItemRect(m_nLastDragItemDraw, rc);
		if (m_nLastDragItemDrawType == 0) rc.bottom = rc.top + 5;
		else if (m_nLastDragItemDrawType == 1) { rc.top -= 4; rc.bottom = rc.top + 9; }
		else if (m_nLastDragItemDrawType == 2) { rc.top -= 4; rc.bottom = rc.top + 5; }
		InvalidateRect(rc, true);
		UpdateWindow();
	}
	m_nLastDragItemDraw = nTo;

	if (m_nLastDragItemDraw >= 0)
	{
		m_nLastDragItemDrawType = GetDragItemRect(m_nLastDragItemDraw, rc);

		CPen *pOldPen = pDC->SelectObject(m_pBlackPen);

		pDC->MoveTo(rc.left, rc.top);
		pDC->LineTo(rc.right, rc.top);

		if (m_nLastDragItemDrawType != 2)
		{
			pDC->MoveTo(rc.left, rc.top+1);
			pDC->LineTo(rc.left + 7, rc.top+1);
			pDC->MoveTo(rc.left, rc.top+2);
			pDC->LineTo(rc.left + 5, rc.top+2);
			pDC->MoveTo(rc.left, rc.top+3);
			pDC->LineTo(rc.left + 3, rc.top+3);
			pDC->MoveTo(rc.left, rc.top+4);
			pDC->LineTo(rc.left + 1, rc.top+4);

			pDC->MoveTo(rc.right-1, rc.top+1);
			pDC->LineTo(rc.right - 7, rc.top+1);
			pDC->MoveTo(rc.right-1, rc.top+2);
			pDC->LineTo(rc.right - 5, rc.top+2);
			pDC->MoveTo(rc.right-1, rc.top+3);
			pDC->LineTo(rc.right - 3, rc.top+3);
		}
		if (m_nLastDragItemDrawType != 0)
		{
			pDC->MoveTo(rc.left, rc.top-1);
			pDC->LineTo(rc.left + 7, rc.top-1);
			pDC->MoveTo(rc.left, rc.top-2);
			pDC->LineTo(rc.left + 5, rc.top-2);
			pDC->MoveTo(rc.left, rc.top-3);
			pDC->LineTo(rc.left + 3, rc.top-3);
			pDC->MoveTo(rc.left, rc.top-4);
			pDC->LineTo(rc.left + 1, rc.top-4);

			pDC->MoveTo(rc.right-1, rc.top-1);
			pDC->LineTo(rc.right - 7, rc.top-1);
			pDC->MoveTo(rc.right-1, rc.top-2);
			pDC->LineTo(rc.right - 5, rc.top-2);
			pDC->MoveTo(rc.right-1, rc.top-3);
			pDC->LineTo(rc.right - 3, rc.top-3);
			pDC->MoveTo(rc.right-1, rc.top-4);
			pDC->LineTo(rc.right - 1, rc.top-4);
		}

		pDC->SelectObject(pOldPen);
	}
}

int CXTOutBarCtrl::GetDragItemRect(const int nIndex, CRect &rect)
{
	CRect rc, rcInside;
	GetInsideRect(rcInside);
	rcInside.InflateRect(-2, 0);

	GetItemRect(m_nSelFolder, nIndex < GetItemCount() ? nIndex : nIndex - 1, rc);
	int nLine = 0;
	if (nLine < GetItemCount())
	{
		nLine = rc.top - 4;
	}
	else
	{
		nLine = rc.bottom + 6;
	}
	int nTpe;
	if (nLine == 0)
	{
		rect.SetRect(rcInside.left, nLine + 2, rcInside.right, nLine + 7);
		nTpe = 0;
	}
	else if (nIndex < GetItemCount())
	{
		rect.SetRect(rcInside.left, nLine - 9, rcInside.right, nLine);
		nTpe = 1;
		if (IsSmallIconView()) 
		{
			rect.top += 8;
			rect.bottom += 8;
		}
	}
	else
	{
		rect.SetRect(rcInside.left, nLine, rcInside.right, nLine + 5);
		nTpe = 2;
	}
	return nTpe;
}


void CXTOutBarCtrl::AnimateFolderScroll(const int nFrom, const int nTo)
{
	if (nFrom < 0 || nFrom >= GetFolderCount()) return;
	if (nTo < 0 || nTo >= GetFolderCount()) return;

	CRect rcInside, rcInside1, rcFolder, rcFolder1;
	GetInsideRect(rcInside);
	rcInside1.SetRect(0,0,rcInside.Width(),rcInside.Height());
	GetFolderRect(nTo, rcFolder);
	rcFolder1 = rcFolder;

	CClientDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmpFrom, bmpTo;
	bmpFrom.CreateCompatibleBitmap(&dc, rcInside1.Width(), rcInside1.Height() + rcFolder.Height() * 2);
	bmpTo.CreateCompatibleBitmap(&dc, rcInside1.Width(), rcInside1.Height() + rcFolder.Height() * 2);
	CDC *pDC = &memDC;

	CWnd *pWnd1 = GetFolderChild(nFrom);
	CWnd *pWnd2 = GetFolderChild(nTo);

	CBitmap *pOldBmp = pDC->SelectObject(&bmpFrom);
	if (nTo > nFrom)
	{
		rcInside1.bottom += rcFolder.Height() * 2;
		pDC->FillSolidRect(rcInside1, m_crBackGroundColor);

		if (pWnd1) 
		{
			BOOL bPrev = pWnd1->ShowWindow(SW_SHOW);
			pWnd1->SendMessage(WM_ERASEBKGND, (WPARAM) pDC->GetSafeHdc(), (LPARAM)0);
			pWnd1->SendMessage(WM_PAINT, (WPARAM) pDC->GetSafeHdc(), (LPARAM)0);
			if (!bPrev) pWnd1->ShowWindow(SW_HIDE);
		}
		else PaintItemsEx(pDC, nFrom, rcInside1);

		pDC->SelectObject(&bmpTo);
		rcFolder.SetRect(0,0,rcFolder.Width(),rcFolder.Height());
		rcInside1.SetRect(0,rcFolder.Height(),rcInside.Width(), rcInside.Height()+rcFolder.Height() * 2);

		pDC->FillSolidRect(rcInside1, m_crBackGroundColor);

		if (pWnd2) 
		{
			CPoint ovpt = pDC->SetViewportOrg(0, rcFolder.Height());
			BOOL bPrev = pWnd2->ShowWindow(SW_SHOW);
			pWnd2->SendMessage(WM_ERASEBKGND, (WPARAM) pDC->GetSafeHdc(), (LPARAM) 0);
			pWnd2->SendMessage(WM_PAINT, (WPARAM) pDC->GetSafeHdc(), (LPARAM) 0);
			if (!bPrev) pWnd2->ShowWindow(SW_HIDE);
			pDC->SetViewportOrg(ovpt);
		}
        else PaintItems(pDC, nTo, rcInside1);
		DrawFolder(pDC, nTo, rcFolder, false);
	}
	else
	{
		rcFolder.SetRect(0,0,rcFolder.Width(),rcFolder.Height());
		rcInside1.top += rcFolder.Height();
		rcInside1.bottom += rcFolder.Height() * 2;

		pDC->FillSolidRect(rcInside1, m_crBackGroundColor);

		if (pWnd1) 
		{
			CPoint ovpt = pDC->SetViewportOrg(0, rcFolder.Height());
			BOOL bPrev = pWnd1->ShowWindow(SW_SHOW);
			pWnd1->SendMessage(WM_ERASEBKGND, (WPARAM) pDC->GetSafeHdc(), (LPARAM)0);
			pWnd1->SendMessage(WM_PAINT, (WPARAM) pDC->GetSafeHdc(), (LPARAM)0);
			if (!bPrev) pWnd1->ShowWindow(SW_HIDE);
			pDC->SetViewportOrg(ovpt);
		}
		else PaintItemsEx(pDC, nFrom, rcInside1);

		DrawFolder(pDC, nFrom, rcFolder, false);

		pDC->SelectObject(&bmpTo);
		rcInside1.SetRect(0,0,rcInside.Width(), rcInside.Height() + rcFolder.Height() * 2);

		pDC->FillSolidRect(rcInside1, m_crBackGroundColor);

		if (pWnd2) 
		{
			BOOL bPrev = pWnd2->ShowWindow(SW_SHOW);
			pWnd2->SendMessage(WM_ERASEBKGND, (WPARAM) pDC->GetSafeHdc(), (LPARAM) 0);
			pWnd2->SendMessage(WM_PAINT, (WPARAM) pDC->GetSafeHdc(), (LPARAM) 0);
			if (!bPrev) pWnd2->ShowWindow(SW_HIDE);
		}
		else PaintItemsEx(pDC, nTo, rcInside1);
	}

	if (nTo > nFrom)
	{
		CRect rcFrom, rcTo;
		GetFolderRect(nFrom, rcFrom);
		GetFolderRect(nTo, rcTo);
		int fh = rcFrom.Height();
		for (int y = rcTo.top - fh; y > rcFrom.bottom; y -= fh)
		{
			pDC->SelectObject(&bmpFrom);
			dc.BitBlt(rcInside.left, rcFrom.bottom + 1, rcInside.Width()+20, y - rcFrom.bottom - 1, pDC, 0,fh, SRCCOPY);
			pDC->SelectObject(&bmpTo);
			dc.BitBlt(rcInside.left, y, rcInside.Width(), rcInside.bottom - y + fh, pDC, 0,0, SRCCOPY);
			Sleep(m_nAnimationTickCount);
		}
	}
	else
	{
		CRect rcFrom, rcTo;
		GetFolderRect(nFrom, rcFrom);
		int fh = rcFrom.Height();
		rcTo.SetRect(rcInside.left, rcInside.bottom, rcInside.right, rcInside.bottom - fh);
		for (int y = rcFrom.top + 1; y < rcTo.top - fh; y += fh)
		{
			pDC->SelectObject(&bmpTo);
			dc.BitBlt(rcInside.left, rcFrom.top, rcInside.Width(), y - rcFrom.top - 1, pDC, 0, fh*2, SRCCOPY);
			pDC->SelectObject(&bmpFrom);
			dc.BitBlt(rcInside.left, y, rcInside.Width(), rcInside.bottom - y, pDC, 0,0, SRCCOPY);
			Sleep(m_nAnimationTickCount);
		}
	}

	pDC->SelectObject(pOldBmp);
}

CString CXTOutBarCtrl::GetItemText(const int nIndex)
{
	CString strText;
	
	if (m_nSelFolder < 0 || m_nSelFolder >= GetFolderCount()) return strText;	

	CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(m_nSelFolder);
	if (NULL == pbf) return strText;
	if (IsValidItem(nIndex))
	{
		CBarItem *pi = (CBarItem*)pbf->m_arItems.GetAt(nIndex);
		if (NULL == pi) return strText;
		if (pi->m_pszItem) strText = pi->m_pszItem;
	}
	return strText;
}

int CXTOutBarCtrl::AddFolderBar(const char * pszName, CWnd * pWndChild, const DWORD dwData)
{
	CBarFolder *pbf = new CBarFolder(pszName, dwData);
	ASSERT(pbf);
	pbf->m_pWndChild = pWndChild;

	m_arFolder.Add((void*)pbf);

	return (int)m_arFolder.GetSize() - 1;
}

CWnd * CXTOutBarCtrl::GetFolderChild(int nFolder)
{
	if (GetFolderCount() && (-1 != nFolder))
	{
		if (nFolder < 0) nFolder = m_nSelFolder;

		CBarFolder *pbf = (CBarFolder*)m_arFolder.GetAt(nFolder);
		if (NULL == pbf) return NULL;
		return pbf->m_pWndChild;
	}
	return NULL;
}

DWORD CXTOutBarCtrl::GetFolderData(int nFolder)
{
	if (nFolder < 0) nFolder = m_nSelFolder;
	CBarFolder *pbf = (CBarFolder*) m_arFolder.GetAt(nFolder);
	if (NULL == pbf) return 0;
	return pbf->m_dwData;
}

void CXTOutBarCtrl::SetAnimSelHighlight(const int nTime)
{
	if (nTime <= 0) KillTimer(3);
	else SetTimer(3, nTime, NULL);
	m_nSelAnimTiming = nTime;
}

void CXTOutBarCtrl::StartActiveItem(DWORD dwFolderIndex, DWORD dwUserIndex)
{
	for (int i = 0; i < (int)m_arActiveItem.GetCount(); i++)
	{
		if ((dwFolderIndex == m_arActiveItem[i].nFolder) &&
            (dwUserIndex == m_arActiveItem[i].nIndex)) return;
	}
    ACTITEM ActItem = { dwFolderIndex, dwUserIndex };
	m_arActiveItem.Add(ActItem);
}

void CXTOutBarCtrl::StopActiveItem(DWORD dwFolderIndex, DWORD dwUserIndex)
{
    for (int i = 0; i < (int)m_arActiveItem.GetCount(); i++)
    {
        if ((dwFolderIndex == m_arActiveItem[i].nFolder) &&
            (dwUserIndex == m_arActiveItem[i].nIndex))
            m_arActiveItem.RemoveAt(i);
    }
}
/*
void CXTOutBarCtrl::AddMenu(DWORD dwId, LPCTSTR psName)
{
    CString strText;
    strText.Format(_T("添加到\'%s\'(&A)"), psName);
    m_mItem.AppendMenu(MF_STRING, ID_OUTBAR_ADDUSER+dwId, strText, rand()%4);
}

void CXTOutBarCtrl::ModMenu(DWORD dwId, LPCTSTR psName)
{
    CString strText;
    strText.Format(_T("添加到\'%s\'(&A)"), psName);

    int count = m_mItem.GetMenuItemCount();
    for (int i = 0; i < count; i++)
    {
        if (m_mItem.GetMenuItemID(i) == ID_OUTBAR_ADDUSER + dwId)
            m_mItem.ModifyMenuText(ID_OUTBAR_ADDUSER + dwId, strText);
    }
}

void CXTOutBarCtrl::DelMenu(DWORD dwId)
{
    int count = m_mItem.GetMenuItemCount();
    for (int i = 0; i < count; i++)
    {
        if (m_mItem.GetMenuItemID(i) == ID_OUTBAR_ADDUSER + dwId)
            m_mItem.RemoveMenu(i, MF_BYPOSITION);
    }
}

void CXTOutBarCtrl::OnOutBarAddGroup()
{
    GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, ID_OUTBAR_ADDGROUP, this->GetFolderCount());
}

void CXTOutBarCtrl::OnOutBarDelGroup()
{
    GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, ID_OUTBAR_DELGROUP, m_nHitInternal2);
}

void CXTOutBarCtrl::OnOutBarRenameGroup()
{
    GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, ID_OUTBAR_RENAMEGROUP, m_nHitInternal2);
}

void CXTOutBarCtrl::OnAddUserToFloder(UINT nCmd)
{
    int *pnData = new int[2];
    pnData[0] = GetFolderData(nCmd-ID_OUTBAR_ADDUSER);
    pnData[1] = GetItemData(m_nHitInternal2);
    GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, ID_OUTBAR_ADDUSER, (LPARAM)pnData);
}

void CXTOutBarCtrl::OnDelUserFromFloder()
{
    int *pnData = new int[3];
    pnData[0] = GetFolderData(m_nSelFolder);
    pnData[1] = GetItemData(m_nHitInternal2);
    pnData[2] = m_nHitInternal2;
    GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, ID_OUTBAR_DELUSER, (LPARAM)pnData);
}

void CXTOutBarCtrl::OnBroadFile()
{
    int *pnData = new int[3];
    pnData[0] = GetFolderData(m_nSelFolder);
    pnData[1] = GetItemData(m_nHitInternal2);
    pnData[2] = m_nHitInternal2;
    GetOwner()->SendMessage(WM_OUTBAR_NOTIFY, ID_OUTBAR_BROADFILE, (LPARAM)pnData);
}
*/
