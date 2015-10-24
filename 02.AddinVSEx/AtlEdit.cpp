// AtlEdit.cpp : Implementation of CAtlEdit
//
// This is a part of the Active Template Library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "stdafx.h"
#include "AtlEdit.h"

/**
 *\fn        STDMETHODIMP SetObjectRects(LPCRECT prcPos,LPCRECT prcClip)
 *\brief     设置窗体大小
 *\param[in] LPCRECT prcPos 
 *\param[in] LPCRECT prcClip 
 *\return    STDMETHODIMP 0成功,其它失败
 */
STDMETHODIMP CAtlEdit::SetObjectRects(LPCRECT prcPos,LPCRECT prcClip)
{
    IOleInPlaceObjectWindowlessImpl<CAtlEdit>::SetObjectRects(prcPos, prcClip);

    addinWnd_.resizeWnd(prcPos->right - prcPos->left, prcPos->bottom - prcPos->top);

    return S_OK;
}

/**
 *\fn        STDMETHODIMP setParam(int id, const char *param)
 *\brief     由Addin调用设置参数
 *\param[in] int id 接口ID
 *\param[in] const char * param 接口参数
 *\return    STDMETHODIMP 0成功,其它失败
 */
STDMETHODIMP CAtlEdit::setParam(int id, const char *param)
{
    switch (id)
    {
    case 0: // 退出
        {
            addinWnd_.destroy();
            break;
        }
    default:
        {
            addinWnd_.setParam(id, (void*)param);
            break;
        }
    }

    return S_OK;
}

CAtlEdit::CAtlEdit()
{
    m_bWindowOnly = TRUE;
}

CAtlEdit::~CAtlEdit()
{
}

LRESULT CAtlEdit::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
#if (_WIN32_IE >= 0x0300)
    INITCOMMONCONTROLSEX iccx;
    iccx.dwSize = sizeof(iccx);
    iccx.dwICC = ICC_USEREX_CLASSES;
    ::InitCommonControlsEx(&iccx);
#else
    ::InitCommonControls();
#endif

    addinWnd_.create(ATL::_pModule->GetModuleInstance(), this, m_hWnd,
        IDB_BITMAP_ICON, IDC_CURSOR_DRAG_HZ, IDC_CURSOR_COPY);

    return 0;
}

LRESULT CAtlEdit::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    addinWnd_.destroy();
    return 0;
}

LRESULT CAtlEdit::OnMouseUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    short x = (lParam & 0x0000FFFF);
    short y = (lParam & 0xFFFF0000) >> 16;
    addinWnd_.mouseMove(x, y, MOUSE_UP);
    return 0;
}

LRESULT CAtlEdit::OnMouseDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    short x = (lParam & 0x0000FFFF);
    short y = (lParam & 0xFFFF0000) >> 16;
    addinWnd_.mouseMove(x, y, MOUSE_DOWN);
    return 0;
}

LRESULT CAtlEdit::OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    short x = (lParam & 0x0000FFFF);
    short y = (lParam & 0xFFFF0000) >> 16;

    addinWnd_.mouseMove(x, y, wParam);

    return 0;
}

LRESULT CAtlEdit::OnComboServerCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
    bHandled = FALSE;

    if (HIWORD(wParam) != CBN_SELCHANGE)
    {
        return 0;
    }

    addinWnd_.connectServer();

    return S_OK;
}

LRESULT CAtlEdit::OnComboConnectCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
    bHandled = FALSE;

    if (HIWORD(wParam) != CBN_SELCHANGE)
    {
        return S_OK;
    }

    addinWnd_.showServer();

    return S_OK;
}

LRESULT CAtlEdit::OnComboMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // 禁止鼠标滚动
    return S_OK;
}

LRESULT CAtlEdit::OnEditSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    addinWnd_.setFocus(true);
    return S_OK;
}

LRESULT CAtlEdit::OnEditKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    addinWnd_.setFocus(false);
    return S_OK;
};

LRESULT CAtlEdit::OnEditSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CAtlEdit::OnEditPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    addinWnd_.onPaint();
    return 0;
}

LRESULT CAtlEdit::OnEditEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CAtlEdit::OnEditChar(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    addinWnd_.onChar(wParam, lParam);
    return 0;
}

LRESULT CAtlEdit::OnEditKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    addinWnd_.onKeyDown(wParam);
    return 0;
}

LRESULT CAtlEdit::OnEditVScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    addinWnd_.scroll(LOWORD(wParam), HIWORD(wParam));
    return 0;
}

LRESULT CAtlEdit::OnEditMouseWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    addinWnd_.mouseWheel(HIWORD(wParam));
    return 0;
}

LRESULT CAtlEdit::OnEditRButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CAtlEdit::OnTreeRename(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/)
{
    return addinWnd_.renameDir(((NMTVDISPINFO*)pNMHDR)->item.pszText); // TRUE保存数据
}

LRESULT CAtlEdit::OnTreeClk(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/)
{
    addinWnd_.updateFileList(pNMHDR->hwndFrom, ((NM_TREEVIEW*)pNMHDR)->itemNew.hItem);
    return 0;
}

LRESULT CAtlEdit::OnTreeKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    if (46 == wParam) // del
    {
        addinWnd_.deleteSelectDir();
    }

    return 0;
}

LRESULT CAtlEdit::OnListAdd(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/)
{
    addinWnd_.addFile(pNMHDR->hwndFrom);
    return 0;
}

LRESULT CAtlEdit::OnListDel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    if (46 == wParam) // del
    {
        addinWnd_.deleteSelectFile();
    }

    return 0;
}

LRESULT CAtlEdit::OnListRename(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/)
{
    NMLVDISPINFO* p = (NMLVDISPINFO*)pNMHDR;
    return addinWnd_.renameFile(p->item.iItem, p->item.iSubItem, p->item.pszText); // TRUE保存数据
}

LRESULT CAtlEdit::OnListOpen(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/)
{
    addinWnd_.openFile(pNMHDR->hwndFrom, ((NM_LISTVIEW*)pNMHDR)->iItem);
    return 0;
}

LRESULT CAtlEdit::OnListSort(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/)
{
    addinWnd_.sortList(((NM_LISTVIEW*)pNMHDR)->iSubItem);
    return 0;
}

LRESULT CAtlEdit::OnListBegingDrag(WPARAM /*wParam*/, NMHDR* /*pNMHDR*/, BOOL& /*bHandled*/)
{
    addinWnd_.startDragFile();
    return 0;
}

LRESULT CAtlEdit::OnListDropFiles(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}
