
#include "StdAfx.h"
#include "XTMenu.h"

CXTMenu::CXTMenu()
{
    m_Width  = 25;              // default menu width
    m_Height = 32;              // default menu height
    m_nType  = MIT_ICON;        // default menu type (Icon Menu)
}

CXTMenu::~CXTMenu()
{
    while (m_MenuList.GetCount())   // release all menu item
    {
        CMenuItem* pItem = m_MenuList.GetHead();
        delete pItem;
        m_MenuList.RemoveHead();
    }

}

// 设置参数,应用时先CreatePopupMenu,再SetParam,然后AppendMenu
void CXTMenu::SetParam(CImageList *pImageList, DWORD dwWidth, DWORD dwHeight, UINT nMenuType)
{
    m_Width = dwWidth - 12;
    m_Height = dwHeight;
    m_nType = nMenuType;
    m_pImageList = pImageList;
}

// nFlags       [IN] 状态标记,MF_ENABLED,MF_POPUP,MF_SEPARATOR,MF_MENUBREAK ...
// nIdItem      [IN] 菜单项的ID,用于ON_COMMAND或其它
// pstrItem     [IN] 菜单项名
// nImageIndex  [IN] 菜单项的图像ID,只能是16*16像素的
BOOL CXTMenu::AppendMenu(UINT nFlags, UINT nIdItem /*= 0*/, LPCTSTR pstrItem /*= NULL*/, INT nImageIndex/* = -1*/)
{
    CString strNewItem(pstrItem);

	CMenuItem* pItem = new CMenuItem(nIdItem, m_Width, m_Height, nImageIndex);
	m_MenuList.AddTail(pItem);

	if (NULL != pstrItem )
	{
		int nIndex = strNewItem.Find(_T("\t"));
		if (-1 != nIndex)
		{
			_tcsncpy(pItem->m_tszText, &pstrItem[1], nIndex - 1);
			_tcsncpy(pItem->m_tszHotkey, &pstrItem[nIndex+1], 127);
		}
		else
		{
			_tcsncpy(pItem->m_tszText, pstrItem, 127);
		}
	}

	nFlags |= MF_OWNERDRAW;

	return CMenu::AppendMenu(nFlags, nIdItem, (LPCTSTR)pItem);
}

void CXTMenu::SetMenuWidth(DWORD width)
{
    m_Width = width;
}

void CXTMenu::SetMenuHeight(DWORD height)
{
    m_Height = height;
}

void CXTMenu::SetMenuType(UINT nType)
{
    m_nType = nType;
}

void CXTMenu::ModifyMenuText(DWORD dwId, LPCTSTR psName)
{
    POSITION ps = m_MenuList.GetHeadPosition();
    while (NULL != ps)
    {
        CMenuItem* pItem = m_MenuList.GetNext(ps);

        if (pItem->m_nId == dwId)
            _tcscpy(pItem->m_tszText, psName);
    }
}

BOOL CXTMenu::EraseBkgnd(HWND hWnd, HDC hDC)
{
    CDC* pDC = CDC::FromHandle(hDC);
    CRect Rect;
    GetClientRect(hWnd, Rect);

    pDC->FillSolidRect(Rect,RGB(255,0,0));

    return TRUE;
}

void CXTMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
    UINT state = GetMenuState(lpMIS->itemID,MF_BYCOMMAND);

    CMenuItem* pItem = reinterpret_cast<CMenuItem *>(lpMIS->itemData);

    if (state & MF_SEPARATOR && _tcscmp(pItem->m_tszText, _T("")) == 0)     // item state is separator
    {
        lpMIS->itemWidth = pItem->m_nWidth;
        lpMIS->itemHeight = 3;
    }
    else                            // other item state
    {
        int temp = ::GetSystemMetrics(SM_CYMENU);
        
        lpMIS->itemWidth = pItem->m_nWidth;
        lpMIS->itemHeight = pItem->m_nHeight;       
    }
}

void CXTMenu::DrawColorMenu(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);

    CMenuItem* pItem = reinterpret_cast<CMenuItem *>(lpDIS->itemData);
    CRect rect(&lpDIS->rcItem); 

    if (lpDIS->itemAction & ODA_DRAWENTIRE)
    {
        // paint the brush and color item in requested
        pDC->FrameRect(rect, &CBrush(GetSysColor(COLOR_3DFACE)));
        rect.DeflateRect(3, 3, 3, 3);
        pDC->FrameRect(rect, &CBrush(RGB(128, 128, 128)));

        rect.DeflateRect(1,1,1,1);
        // draw a rectangle palette
        pDC->FillSolidRect(rect, (COLORREF)pItem->m_nImageIndex);
    }

    if ((lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & (ODA_SELECT|ODA_DRAWENTIRE)))
    {
        // item has been selected - raised frame
        pDC->DrawEdge(rect, EDGE_RAISED, BF_RECT);
        m_SelColor = (COLORREF) _ttol(pItem->m_tszText);
        m_curSel = lpDIS->itemID;
    }

    if (!(lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & ODA_SELECT))
    {
        // item has been de-selected -- remove frame
        CBrush br(GetSysColor(COLOR_3DFACE));
        pDC->FrameRect(rect, &br);
        rect.DeflateRect(1,1,1,1);
        pDC->FrameRect(rect, &br);
    }
}

void CXTMenu::DrawIconMenu(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);

    CMenuItem* pItem = reinterpret_cast<CMenuItem *>(lpDIS->itemData);
    CRect rect(&lpDIS->rcItem);
    
    UINT state = GetMenuState(lpDIS->itemID, MF_BYCOMMAND);
    if ((lpDIS->itemAction & ODA_DRAWENTIRE) 
        || (!(lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & ODA_SELECT)))
    {
        pDC->FillRect(rect, &CBrush(RGB(255, 255, 240)));

        if (NULL != m_pImageList)
        {
            // paint icon item in requested
            POINT pt = {rect.left + 2, rect.top + 2};
            m_pImageList->Draw(pDC, pItem->m_nImageIndex, pt, ILD_NORMAL | INDEXTOOVERLAYMASK(1));
        }

        // the menu state is separator - draw a color title
        if (state & MF_SEPARATOR)
        {
            for(int i = 0; i < rect.Width(); i++)
                pDC->FillRect(rect, &CBrush(RGB(216-i, 216-i, 235)));
        }
    }

    if ((lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
    {
        // item has been selected - draw hilite frame
        CBrush br(RGB(64, 64, 128));
        pDC->FrameRect(rect, &br);
        rect.DeflateRect(1, 1, 1, 1);
        pDC->FrameRect(rect, &br);
        m_curSel = lpDIS->itemID;   // get current selected 
    }
/*
    if (!(lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & ODA_SELECT))
    {
        // item has been de-selected - remove frame
        CBrush br(::GetSysColor(COLOR_3DFACE));
        pDC->FrameRect(rect, &br);
        rect.DeflateRect(1, 1, 1, 1);
        pDC->FrameRect(rect, &br);      
    }
*/
}
/*
void CXTMenu::DrawXPMenu(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);

    CMenuItem* pItem = reinterpret_cast<CMenuItem *>(lpDIS->itemData);
    CRect rectFull(&lpDIS->rcItem); 

    // get icon region and text region
    CRect rectIcon(rectFull.left, rectFull.top, rectFull.left + 20, rectFull.top + 20);
    CRect rectText(rectIcon.right, rectFull.top, rectFull.right, rectFull.bottom);

    UINT state = GetMenuState(lpDIS->itemID, MF_BYCOMMAND);

    if (lpDIS->itemAction & ODA_DRAWENTIRE)
    {
        // paint the brush and icon item in requested
        CRect rect;
        // paint item background 
        pDC->FillRect(rectFull, &CBrush(RGB(255, 255, 240)));
        pDC->FillRect(rectIcon, &CBrush(GetSysColor(COLOR_3DFACE)));

        if (state & MF_SEPARATOR)   // item is separator
        {   // draw a etched edge
            rect.CopyRect(rectText);
            rect.OffsetRect(0,3);
            pDC->DrawEdge(rect,EDGE_ETCHED,BF_TOP);
        }
            
        if (state & MFS_CHECKED) // item has been checked
        {
            // paint the frame and brush,then draw a check mark
            rect.CopyRect(rectIcon);
            rect.DeflateRect(1,1,1,1);
            pDC->FrameRect(rect,&CBrush(RGB(64,64,128)));

            rect.DeflateRect(1,1,1,1);
            pDC->FillRect(rect,&CBrush(RGB(216,216,235)));
            DrawCheckMark(pDC,rect.left+5,rect.top+5,RGB(64,64,128));
        }
        if (-1 != pItem->m_nImageIndex && NULL != m_pImageList) // item has bitmap
        {
            // draw a bitmap
            POINT pt = {rectIcon.left + 2, rectIcon.top + 2};
            SIZE sz = {16, 16};
            m_pImageList->DrawEx(pDC, pItem->m_nImageIndex, pt, sz,
                RGB(192, 192, 192), RGB(255,0,255),
                ILD_NORMAL | INDEXTOOVERLAYMASK(1));
        }

        // draw display text
        pDC->SetBkMode(TRANSPARENT);
        rect.CopyRect(rectText);
        rect.DeflateRect(2, 2, 2, 2);
        rect.OffsetRect(6, 2);
        if (state & MFS_DISABLED)   // item has been disabled
            pDC->SetTextColor(GetSysColor(COLOR_3DFACE));

        pDC->DrawText(pItem->m_tszText, (int)_tcslen(pItem->m_tszText), rect, DT_LEFT|DT_SINGLELINE);   
        
        if (0 == _tcscmp(pItem->m_tszHotkey,_T("")))
        {
            pDC->DrawText(pItem->m_tszHotkey,
                lstrlen(pItem->m_tszHotkey),
                CRect(rect.right - 60, rect.top, rect.right, rect.bottom), 
                DT_LEFT|DT_SINGLELINE);
        }
    }

    if ((lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
    {
        // item has been selected
        if( state & MFS_DISABLED )  
            return;                 // item has been disabled  
        CRect  rect;

        // item has bitmap - draw a raised edge
        if (!(state & MFS_CHECKED) && (pItem->m_nImageIndex != -1)) 
            pDC->DrawEdge(rectIcon,EDGE_RAISED,BF_RECT);

        // draw hilite frame
        rect.SetRect(rectText.left+2, rectText.top, rectText.right, rectText.bottom);
        pDC->FrameRect(rect, &CBrush(RGB(64, 64, 128)));
        // draw hilite brush
        rect.DeflateRect(1, 1, 1, 1);
        pDC->FillRect(rect, &CBrush(RGB(216, 216, 235)));
        // draw display text
        rect.CopyRect(rectText);
        rect.DeflateRect(2, 2, 2, 2);
        rect.OffsetRect(6, 2);

        pDC->SetBkMode(TRANSPARENT);
        pDC->DrawText(pItem->m_tszText, (int)_tcslen(pItem->m_tszText), rect, DT_LEFT|DT_SINGLELINE);

        if (0 == _tcscmp(pItem->m_tszHotkey,_T("")))
        {
            pDC->DrawText(pItem->m_tszHotkey,
                lstrlen(pItem->m_tszHotkey),
                CRect(rect.right - 60, rect.top, rect.right, rect.bottom), 
                DT_LEFT|DT_SINGLELINE);
        }

        m_curSel = lpDIS->itemID;   // get current selected
    }

    if (!(lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & ODA_SELECT))
    {
        // item has been de-selected
        CRect rect;
        rect.CopyRect(rectIcon);

        if (-1 != pItem->m_nImageIndex && NULL != m_pImageList)
        {
            // the item has bitmap - repaint icon region and bitmap
            pDC->FillRect(rect,&CBrush(::GetSysColor(COLOR_3DFACE)));

            POINT pt = {rectIcon.left + 2, rectIcon.top + 2};
            SIZE sz = {16, 16};
            m_pImageList->DrawEx(pDC, pItem->m_nImageIndex, pt, sz,
                RGB(192, 192, 192), RGB(255,0,255),
                ILD_NORMAL | INDEXTOOVERLAYMASK(1));
        }

        // draw display text
        pDC->FillRect(rectText,&CBrush(RGB(255,255,240)));
        rect.CopyRect(rectText);
        rect.DeflateRect(2,2,2,2);
        rect.OffsetRect(6,2);
        pDC->SetBkMode(TRANSPARENT);
        if( state & MFS_DISABLED ) // item has been disabled
            pDC->SetTextColor(GetSysColor(COLOR_3DFACE));

        pDC->DrawText(pItem->m_tszText, (int)_tcslen(pItem->m_tszText), rect, DT_LEFT|DT_SINGLELINE);
        if (0 == _tcscmp(pItem->m_tszHotkey,_T("")))
        {
            pDC->DrawText(pItem->m_tszHotkey,
                lstrlen(pItem->m_tszHotkey),
                CRect(rect.right - 60, rect.top, rect.right, rect.bottom), 
                DT_LEFT|DT_SINGLELINE);
        }
    }
}
*/
void CXTMenu::DrawXPMenu(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);
    CMenuItem* pItem = reinterpret_cast<CMenuItem *>(lpDIS->itemData);

    if (NULL == pItem) return;

    CRect rectFull(&lpDIS->rcItem);
    CRect rectText(rectFull.left + 18, rectFull.top, rectFull.right, rectFull.bottom);

    UINT state = GetMenuState(lpDIS->itemID, MF_BYCOMMAND);

    if ((lpDIS->itemAction & ODA_DRAWENTIRE) || (!(lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & ODA_SELECT)))
    {
        pDC->FillRect(rectFull, &CBrush(RGB(255, 255, 240)));

        if (state & MF_SEPARATOR)   // item is separator
        {
            rectFull.OffsetRect(0,1);
            pDC->DrawEdge(rectFull,EDGE_ETCHED,BF_TOP);
        }
        else if (state & MFS_CHECKED) // item has been checked
        {
            CRect rect(rectFull);
            rect.left = rectFull.left + 3;
            rect.top = rectFull.top + 3;
            rect.right = rect.left + 16;
            rect.bottom = rect.top + 16;
            pDC->FrameRect(rect,&CBrush(RGB(64,64,128)));

            rect.DeflateRect(1,1,1,1);
            pDC->FillRect(rect,&CBrush(RGB(216,216,235)));
            DrawCheckMark(pDC,rect.left+4,rect.top+4,RGB(64,64,128));
        }
        else if (-1 != pItem->m_nImageIndex && NULL != m_pImageList)
        {
            POINT pt = {rectFull.left + 3, rectFull.top + 3};
            SIZE sz = {16, 16};
            m_pImageList->Draw(pDC, pItem->m_nImageIndex, pt, ILD_NORMAL | INDEXTOOVERLAYMASK(1));
        }

        rectText.DeflateRect(2, 2, 2, 2);
        rectText.OffsetRect(6, 2);

        if (state & MFS_DISABLED)   // item has been disabled
            pDC->SetTextColor(GetSysColor(COLOR_3DFACE));
        
        pDC->SetBkMode(TRANSPARENT);
        pDC->DrawText(pItem->m_tszText, (int)_tcslen(pItem->m_tszText), rectText, DT_LEFT|DT_SINGLELINE|DT_WORD_ELLIPSIS);  

        if (0 != _tcscmp(pItem->m_tszHotkey,_T("")))
        {
            pDC->DrawText(pItem->m_tszHotkey,
                lstrlen(pItem->m_tszHotkey),
                CRect(rectText.right - 40, rectText.top, rectText.right, rectText.bottom), 
                DT_LEFT|DT_SINGLELINE|DT_WORD_ELLIPSIS);
        }
    }

    if ((lpDIS->itemState & ODS_SELECTED) && (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
    {
        if (state & MFS_DISABLED) return;

        pDC->FrameRect(rectFull, &CBrush(RGB(64, 64, 128)));

        rectFull.DeflateRect(1, 1, 1, 1);
        pDC->FillRect(rectFull, &CBrush(RGB(216, 216, 235)));

        if (state & MFS_CHECKED)
        {
            DrawCheckMark(pDC,rectFull.left+6,rectFull.top+6,RGB(64,64,128));
        }
        else if (-1 != pItem->m_nImageIndex && NULL != m_pImageList)
        {
            POINT pt = {rectFull.left + 1, rectFull.top + 1};
            SIZE sz = {16, 16};
            m_pImageList->Draw(pDC, pItem->m_nImageIndex, pt, ILD_NORMAL | INDEXTOOVERLAYMASK(1));
        }

        rectText.DeflateRect(2, 2, 2, 2);
        rectText.OffsetRect(6, 2);

        pDC->SetBkMode(TRANSPARENT);
        pDC->DrawText(pItem->m_tszText, (int)_tcslen(pItem->m_tszText), rectText, DT_LEFT|DT_SINGLELINE|DT_WORD_ELLIPSIS);

        if (0 != _tcscmp(pItem->m_tszHotkey,_T("")))
        {
            pDC->DrawText(pItem->m_tszHotkey,
                lstrlen(pItem->m_tszHotkey),
                CRect(rectText.right - 40, rectText.top, rectText.right, rectText.bottom), 
                DT_LEFT|DT_SINGLELINE|DT_WORD_ELLIPSIS);
        }

        m_curSel = lpDIS->itemID;   // get current selected
    }
}

void CXTMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    switch(m_nType)
    {
    case MIT_XP:
        DrawXPMenu(lpDIS);
        break;
    case MIT_ICON:
        DrawIconMenu(lpDIS);
        break;
    case MIT_COLOR:
        DrawColorMenu(lpDIS);
        break;
    }
}

// 画'对号'
void CXTMenu::DrawCheckMark(CDC* pDC,int x,int y,COLORREF color)
{
    CPen Pen;

    Pen.CreatePen(PS_SOLID,0,color);
    CPen *pOldPen = pDC->SelectObject(&Pen);
    
    pDC->MoveTo(x,y+2);
    pDC->LineTo(x,y+5);
    
    pDC->MoveTo(x+1,y+3);
    pDC->LineTo(x+1,y+6);
    
    pDC->MoveTo(x+2,y+4);
    pDC->LineTo(x+2,y+7);
    
    pDC->MoveTo(x+3,y+3);
    pDC->LineTo(x+3,y+6);
    
    pDC->MoveTo(x+4,y+2);
    pDC->LineTo(x+4,y+5);
    
    pDC->MoveTo(x+5,y+1);
    pDC->LineTo(x+5,y+4);
    
    pDC->MoveTo(x+6,y);
    pDC->LineTo(x+6,y+3);
    
    pDC->SelectObject(pOldPen);
    Pen.DeleteObject();
}

//----------------------------------------------------------------------------------------------------

BOOL CXTMenu::OnMeasureItem(const MSG* pMsg)
{
    if (pMsg->message == WM_MEASUREITEM)
    {
        LPMEASUREITEMSTRUCT lpMIS = (LPMEASUREITEMSTRUCT)pMsg->lParam;
        if (lpMIS->CtlType == ODT_MENU)
        {
            CMenu* pMenu=NULL;
            if (::IsMenu((HMENU)(UINT_PTR)(lpMIS->itemID)))
            {
                pMenu = CMenu::FromHandlePermanent((HMENU)(UINT_PTR)(lpMIS->itemID));
            }
            else
            {
                _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
                if (pThreadState->m_hTrackingWindow == pMsg->hwnd)
                {
                    // start from popup
                    pMenu = FindPopupMenuFromIDData(pThreadState->m_hTrackingMenu, lpMIS->itemID, lpMIS->itemData);
                }

                if (pMenu == NULL)
                {
                    // start from menubar
                    pMenu = FindPopupMenuFromIDData(::GetMenu(pMsg->hwnd), lpMIS->itemID, lpMIS->itemData);
                    if (pMenu == NULL)
                    {
                        // finaly start from system menu.
                        pMenu = FindPopupMenuFromIDData(::GetSystemMenu(pMsg->hwnd,FALSE), lpMIS->itemID, lpMIS->itemData);
                    }
                }
            }

            if (pMenu!=NULL)
            {
                pMenu->MeasureItem(lpMIS);
                return TRUE;
            }
        }
    }
    return FALSE;
}

CMenu* CXTMenu::FindPopupMenuFromIDData(HMENU hMenu, UINT nID, ULONG_PTR pData)
{
    if (::IsMenu(hMenu))
    {
        CMenu *pMenu = CMenu::FromHandlePermanent(hMenu);
        if(pMenu)
        {
            return FindPopupMenuFromIDData(pMenu,nID,pData);
        }
    }
    return NULL; 
}

CMenu* CXTMenu::FindPopupMenuFromIDData(CMenu* pMenu, UINT nID, ULONG_PTR pData)
{
    if (!pMenu || !IsMenu(pMenu->m_hMenu))
    {
        return NULL;
    }
    ASSERT_VALID(pMenu);
    // walk through all items, looking for ID match
    UINT nItems = pMenu->GetMenuItemCount();
    for (int iItem = 0; iItem < (int)nItems; iItem++)
    {
        CMenu* pPopup = pMenu->GetSubMenu(iItem);
        if (pPopup!=NULL)
        {
            // recurse to child popup
            pPopup = FindPopupMenuFromIDData(pPopup, nID, pData);
            // check popups on this popup
            if (pPopup != NULL)
            {
                return pPopup;
            }
        }
        else if (pMenu->GetMenuItemID(iItem) == nID)
        { 
            MENUITEMINFO MenuItemInfo = {0};
            MenuItemInfo.cbSize = sizeof(MenuItemInfo);
            MenuItemInfo.fMask = MIIM_DATA;

            if(pMenu->GetMenuItemInfo(iItem,&MenuItemInfo,TRUE))
            {
                if(MenuItemInfo.dwItemData==pData)
                {
                    // it is a normal item inside our popup
                    return pMenu;
                }
            }
        }
    }
    // not found
    return NULL;
}

//----------------------------------------------------------------------------------------------------

HHOOK   CXTMenu::m_hMsgHook = NULL;
LPCTSTR CXTMenu::wpnOldProc = _T("MenuOldWndProc");

void CXTMenu::EnableHook(BOOL bEnable)
{
    if (bEnable == (m_hMsgHook != NULL)) return;

    if (bEnable)
    {
        m_hMsgHook = SetWindowsHookEx(WH_CALLWNDPROC, MsgHook,
            AfxGetInstanceHandle(), GetCurrentThreadId());
    }
    else
    {
        UnhookWindowsHookEx(m_hMsgHook);
        m_hMsgHook = NULL;
    }
}

LRESULT CALLBACK CXTMenu::MsgHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    CWPSTRUCT* pCWP = (CWPSTRUCT*)lParam;

    while (nCode == HC_ACTION)
    {
        if (pCWP->message != WM_CREATE && pCWP->message != 0x01E2) break;

        TCHAR szClassName[16];
        int nClassName = GetClassName(pCWP->hwnd, szClassName, 16);
        if (nClassName != 6 || _tcscmp(szClassName, _T("#32768")) != 0) break;

        if (::GetProp(pCWP->hwnd, wpnOldProc) != NULL) break;

        HWND hWndFore = GetForegroundWindow();
        if (hWndFore != NULL && CWnd::FromHandlePermanent(hWndFore) == NULL) break;

        WNDPROC pWndProc = (WNDPROC)(LONG_PTR)::GetWindowLong(pCWP->hwnd, GWL_WNDPROC);
        if (pWndProc == NULL) break;
        ASSERT(pWndProc != MenuProc);

        if (!SetProp( pCWP->hwnd, wpnOldProc, pWndProc)) break;

        if (!SetWindowLong( pCWP->hwnd, GWL_WNDPROC, (DWORD)(DWORD_PTR)MenuProc))
        {
            ::RemoveProp(pCWP->hwnd, wpnOldProc);
            break;
        }

        //break;
    }

    return CallNextHookEx(CXTMenu::m_hMsgHook, nCode, wParam, lParam);
}

LRESULT CALLBACK CXTMenu::MenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WNDPROC pWndProc = (WNDPROC)::GetProp(hWnd, wpnOldProc);

    switch (uMsg)
    {
    case WM_WINDOWPOSCHANGING:
        {
            WINDOWPOS* pWndPos = (WINDOWPOS*)lParam;
            pWndPos->cx -= 4;
            pWndPos->cy -= 4;
            break;
        }       
    case WM_NCCALCSIZE:
        {
            NCCALCSIZE_PARAMS* pCalc = (NCCALCSIZE_PARAMS*)lParam;
            pCalc->rgrc[0].left++;
            pCalc->rgrc[0].top++;
            pCalc->rgrc[0].right--;
            pCalc->rgrc[0].bottom--;
            return 0;
        }       
    case WM_NCPAINT:
        {
            CWnd* pWnd = CWnd::FromHandle(hWnd);
            CWindowDC dc(pWnd);
            CRect rc;

            pWnd->GetWindowRect(&rc);
            rc.OffsetRect(-rc.left, -rc.top);
            dc.Draw3dRect(&rc, RGB(128,128,128), RGB(128,128,128));
            return 0;
        }       
    case WM_ERASEBKGND:
        {
            break;
        }       
    case WM_NCDESTROY:
        ::RemoveProp(hWnd, wpnOldProc);
        break;
    }

    return CallWindowProc(pWndProc, hWnd, uMsg, wParam, lParam);
}


