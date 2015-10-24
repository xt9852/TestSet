
/**
    CMenu expand class, it can use icon,bitmap or color

    For change menu item with sub menu height then in it's parent class process WM_MEASUREITEM window message, example:

    为了能改变带有MF_POPUP属性(带有子菜单)的菜单条的高度,需在其父窗口中响应WM_MEASUREITEM消息,例如:在CMainFrame中处理

    void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
    {
        if (!CXTMenu::OnMeasureItem(GetCurrentMessage()))
        {
            CFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
        }
    }
*/

#pragma once
#include "afxtempl.h"

#define MIT_ICON     1
#define MIT_COLOR    2
#define MIT_XP       3

class CMenuItem
{
public:
    CMenuItem(int nId, int nWidth, int nHeight, int nImageIndex = -1)
    {
        m_nId     = nId;        
        m_nWidth  = nWidth;
        m_nHeight = nHeight;
        m_nImageIndex = nImageIndex;
        memset(m_tszText, 0, sizeof(m_tszText));
        memset(m_tszHotkey, 0, sizeof(m_tszHotkey));
    }
public:
    TCHAR   m_tszText[128];     // message text 
    TCHAR   m_tszHotkey[128];   // hot key text
    int     m_nImageIndex;      // picture index in image list or rgb value
    int     m_nWidth;
    int     m_nHeight;
    int     m_nId;
};


class CXTMenu : public CMenu
{
public:
    CXTMenu();
    ~CXTMenu();

public:
    void SetMenuType(UINT nType);
    void SetMenuWidth(DWORD width);
    void SetMenuHeight(DWORD height);
    void ModifyMenuText(DWORD dwId, LPCTSTR psName);    
    void SetParam(CImageList *pImageList, DWORD dwWidth, DWORD dwHeight, UINT nMenuType);
    BOOL AppendMenu(UINT nFlags, UINT nIdItem = 0, LPCTSTR pstrItem = NULL, INT nImageIndex = -1);

protected:
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
    virtual BOOL EraseBkgnd(HWND hWnd,HDC hDC);
    void DrawXPMenu(LPDRAWITEMSTRUCT lpDIS);
    void DrawColorMenu(LPDRAWITEMSTRUCT lpDIS);
    void DrawIconMenu(LPDRAWITEMSTRUCT lpDIS);
    void DrawCheckMark(CDC* pDC, int x, int y, COLORREF color);

protected:
    UINT        m_nType;
    DWORD       m_Width;
    DWORD       m_Height;
    CTypedPtrList<CPtrList,CMenuItem *> m_MenuList;
    CImageList  *m_pImageList;

public:
    COLORREF    m_SelColor;
    int         m_curSel;

public:
    static void   EnableHook(BOOL bEnable);
    static BOOL   OnMeasureItem(const MSG* pMsg);
    static CMenu* FindPopupMenuFromIDData(HMENU hMenu, UINT nID, ULONG_PTR pData);
    static CMenu* FindPopupMenuFromIDData(CMenu* pMenu, UINT nID, ULONG_PTR pData);

protected:
    static HHOOK    m_hMsgHook;
    static LPCTSTR  wpnOldProc;
    
    static LRESULT  CALLBACK MsgHook(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT  CALLBACK MenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);      
};

