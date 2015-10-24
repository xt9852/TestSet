#include "stdafx.h"
#include <afxpriv.h>
#include "resource.h"
#include "XTToolBar.h"

IMPLEMENT_SERIAL(CToolBarButton        ,CObject       , 0)
IMPLEMENT_SERIAL(CToolBarEditButton    ,CToolBarButton, 0)
IMPLEMENT_SERIAL(CToolBarComboBoxButton,CToolBarButton, 0)
IMPLEMENT_SERIAL(CToolBarProgressButton,CToolBarButton, 0)

void CToolBarButton::SetStockFont(CWnd* pWnd,int iStockFont)
{
    HFONT hFont = (HFONT)GetStockObject(iStockFont);

    if (!hFont && iStockFont != DEFAULT_GUI_FONT)
        hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    if (hFont && pWnd) pWnd->SendMessage(WM_SETFONT,(WPARAM)hFont);
}

void CToolBarButton::CheckAndCreateButton(CToolBar* pParent)
{
    if (pParent)
    {
        if (m_nIndex < 0 && (m_nIndex=pParent->CommandToIndex(m_nCommandID)) < 0)
        {
            TBBUTTON tb;
            tb.iBitmap  = m_nIndex; 
            tb.idCommand= m_nCommandID;
            tb.fsState  = 0;
            tb.fsStyle  = m_nStyle; 
            tb.dwData   = 0;
            tb.iString  = 0;

            pParent->GetToolBarCtrl().InsertButton(pParent->GetToolBarCtrl().GetButtonCount(), &tb);

            m_nIndex = pParent->CommandToIndex(m_nCommandID);
        }
    }
}

BOOL CToolBarButton::CreateControl(CToolBar* pParent)
{
    if (!m_nMenuID || !m_nCommandID || IsWndControl()) return TRUE;

    pParent->SendMessage(TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_DRAWDDARROWS);

    CheckAndCreateButton(pParent);

    DWORD dwStyle  = pParent->GetButtonStyle(m_nIndex) | TBSTYLE_DROPDOWN;
    pParent->SetButtonStyle(m_nIndex , dwStyle);
    return TRUE;
}

BOOL CToolBarButton::OnToolbarDropDown(CToolBar* pParent,NMTOOLBAR* pnmtb, LRESULT *plr)
{
    BOOL  bResult=FALSE;
    //
    if (m_nMenuID        &&
        m_nCommandID     &&
        !IsWndControl()  &&
        pnmtb != NULL    &&
        pnmtb->iItem == m_nCommandID)
    {
        bResult  = TRUE;
        CMenu menu;
        if( menu.LoadMenu(m_nMenuID))
        {
            CMenu* pPopup = menu.GetSubMenu(0);
            if (pPopup)
            {
                CRect rc;
                pParent->SendMessage(TB_GETRECT,pnmtb->iItem,(LPARAM)&rc);
                pParent->ClientToScreen(&rc);
                pPopup->TrackPopupMenu(
                    TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
                    rc.left, rc.bottom,AfxGetMainWnd(),&rc );
            }
        }
    }
    return bResult;
}

void CToolBarButton::OnPrepareDrag(CToolBar* pParent)
{
    m_nStyle = pParent->GetButtonStyle(m_nIndex);
    pParent->GetToolBarCtrl().GetItemRect(m_nIndex,&m_rect);
}

void CToolBarButton::OnFinishDrag(CToolBar* pParent)
{
    CRect rect;
    pParent->GetToolBarCtrl().GetItemRect(m_nIndex,rect);
    if (m_nCommandID)
    {
        CWnd* pWnd = GetWindowCtrl();
        if (pWnd)
        {
            if (rect.Width() != m_rect.Width())
            {
                pParent->SetButtonInfo(m_nIndex, m_nCommandID, TBBS_SEPARATOR, m_rect.Width());
                pParent->GetToolBarCtrl().GetItemRect(m_nIndex,rect);
            }
            pWnd->SetWindowPos(NULL,
                rect.left, rect.top,
                rect.Width(), rect.Height(),
                SWP_NOZORDER|SWP_NOACTIVATE);
        }
    }
    m_rect = rect;
}

void CToolBarEditButton::OnPrepareDrag(CToolBar* pParent)
{
    CToolBarButton::OnPrepareDrag(pParent);
}

void CToolBarEditButton::OnFinishDrag(CToolBar* pParent)
{
    CToolBarButton::OnFinishDrag(pParent);
}

BOOL CToolBarEditButton::CreateControl(CToolBar* pToolBar)
{
    BOOL  bResult=FALSE;

    if (pToolBar != NULL)
    {
        CheckAndCreateButton(pToolBar);
        if (m_nIndex > -1 && !(bResult=IsControl()))
        {

            if (m_width)
                pToolBar->SetButtonInfo(m_nIndex,
                m_nCommandID,
                TBBS_SEPARATOR,
                m_width);

            pToolBar->GetItemRect(m_nIndex,&m_rect);

            if (m_edit.CreateEx(WS_EX_CLIENTEDGE,
                _T("EDIT"),	NULL,
                m_dwStyle | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                m_rect,	pToolBar,m_nCommandID))
            {
                SetStockFont(&m_edit);
                bResult = TRUE;
            }
        }
    }
    return bResult;
}

BOOL CToolBarComboBoxButton::CreateControl(CToolBar* pToolBar)
{
    BOOL  bResult=FALSE;
    //
    if (pToolBar != NULL)
    {
        CheckAndCreateButton(pToolBar);
        if (m_nIndex > -1 && !(bResult=IsControl()))
        {
            if (m_size.cx)
                pToolBar->SetButtonInfo(m_nIndex, m_nCommandID, TBBS_SEPARATOR, m_size.cx);

            pToolBar->GetItemRect(m_nIndex,&m_rect);

            if (m_size.cy)
                m_rect.bottom = m_rect.top + m_size.cy;

            if (m_combo.Create(m_dwStyle | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                m_rect, pToolBar, m_nCommandID))
            {
                SetStockFont(&m_combo);

                for (int i=0 ; i < m_strArray.GetSize() ; i++)
                    m_combo.AddString(m_strArray[i]);

                if (m_cbCurSel != CB_ERR)
                    m_combo.SetCurSel(m_cbCurSel);

                bResult  = TRUE;
            }
        }
    }
    return bResult;
}

void CToolBarComboBoxButton::OnPrepareDrag(CToolBar* pParent)
{
    CToolBarButton::OnPrepareDrag(pParent);
    if (m_combo.m_hWnd)
    {
        int count = m_combo.GetCount();

        m_strArray.SetSize(count);

        for (int i=0 ; i < count ; i++)
            m_combo.GetLBText(i,m_strArray[i]);

        m_cbCurSel  = m_combo.GetCurSel();
    }
}

void CToolBarComboBoxButton::OnFinishDrag(CToolBar* pParent)
{
    CToolBarButton::OnFinishDrag(pParent);
    if (m_combo.m_hWnd && m_nCommandID)
        m_combo.SetWindowPos(NULL, m_rect.left , m_rect.top,
        m_rect.Width(), m_rect.Height() + m_size.cy,
        SWP_NOZORDER|SWP_NOACTIVATE);
}

BOOL CToolBarProgressButton::CreateControl(CToolBar* pToolBar)
{
    BOOL bResult=FALSE;

    if (pToolBar != NULL)
    {
        CheckAndCreateButton(pToolBar);
        if (m_nIndex > -1 && !(bResult=IsControl()) )
        {
            if (m_width)
                pToolBar->SetButtonInfo(m_nIndex,
                m_nCommandID,
                TBBS_SEPARATOR,
                m_width);

            pToolBar->GetItemRect(m_nIndex,&m_rect);
            m_rect.InflateRect(-3,-1);

            if( m_wndProgress.Create(m_dwStyle | WS_CHILD | WS_VISIBLE,
                m_rect, pToolBar, m_nCommandID))
            {
                if (m_nUpper) m_wndProgress.SetRange(m_nLower, m_nUpper);
                if (m_nStep) m_wndProgress.SetStep(m_nStep);
                SetStockFont(&m_wndProgress);
                bResult  = TRUE;
            }
        }
    }
    return bResult;
}

void CToolBarProgressButton::OnPrepareDrag(CToolBar* pParent)
{
    CToolBarButton::OnPrepareDrag(pParent);
}

void CToolBarProgressButton::OnFinishDrag(CToolBar* pParent)
{
    CToolBarButton::OnFinishDrag(pParent);
}
