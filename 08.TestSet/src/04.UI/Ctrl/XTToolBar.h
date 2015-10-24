#ifndef _XTTOOLBAR_
#define _XTTOOLBAR_

#pragma once
#include <afxole.h>
#include "XTToolBarButton.h"


class CXTOleDropTarget : public COleDropTarget
{
public:
    CXTOleDropTarget()
        :COleDropTarget()
    {}

    virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
    virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
    virtual void OnDragLeave(CWnd* pWnd);
    virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);

public:
    virtual ~CXTOleDropTarget() {}
};

class CXTToolbarDragItem : public CObject
{
public:
    CXTToolbarDragItem()  // Only drop...
    {
        m_bOnlyDrop = TRUE;
        m_pButton   = NULL;
    }
    CXTToolbarDragItem(int nBitmapID,
        int	nIndex,
        TBBUTTON &tbButton,
        CToolBarButton* pButton = NULL)
    {
        m_bIsBetweenToolbars = TRUE;
        m_nBitmapID  = (tbButton.dwData ? (int)tbButton.dwData : nBitmapID);
        m_bOnlyDrop  = FALSE;
        m_nIndex     = nIndex;
        m_pButton    = pButton;

        CopyTBButton(tbButton,m_tbButton);
    }

    virtual void Serialize(CArchive &ar);

public:
    BOOL     IsBetweenToolbar()   const { return m_bIsBetweenToolbars; }
    void     CopyTBButton(TBBUTTON tbSource,TBBUTTON &tbDest);

    BOOL     m_bIsBetweenToolbars;  // Drag & Drop fra toolbar ?
    int      m_nBitmapID;
    BOOL     m_bOnlyDrop;
    int      m_nIndex;
    TBBUTTON m_tbButton;

    CToolBarButton* m_pButton;
};


class CXTToolbar : public CToolBar
{
    DECLARE_DYNCREATE(CXTToolbar)
public:
    CXTToolbar();
    virtual  ~CXTToolbar() { m_ctrlList.Destroy(); }

public:
    static UINT GetClipboardFormat() { RegisterMyFormat(); return CXTToolbar::m_nIDClipFormat; }
    static LPCTSTR GetClipboardFormatName() { return _T("CXTToolbarFormat"); }

    void EnableCustomization(bool bEnable);
    //virtual void OnAddControls(CTbDlg &dlg) {}
    bool IsOnCustomization() const { return m_bEnable; }

public:

    CToolBarButton* CreateButton(int commandID,
        int  index = -1,    // lo cerca...
        UINT nBitmapID = 0, // bitmap ID ( 0 is native...)
        int  nImage  = -1 ,
        UINT nMenuID = 0);

    CToolBarEditButton* CreateEdit(int commandID,     // command id
        int index = -1,    // lo cerca...
        int width = 50,    //
        LONG style = ES_AUTOHSCROLL );

    CToolBarComboBoxButton* CreateCombo(int commandID, // command id
        int  index = -1,   // index on toolbar...
        int  width = 50,
        int  height = 120,
        LONG style = CBS_DROPDOWNLIST | WS_VSCROLL);

    CToolBarProgressButton* CreateProgress(int commandID,
        int index = -1,
        int iWidth = 0,
        int nLower = 0,
        int nUpper = 100,
        int nStep = 1);
    //
    // Toolbar take ownership and destroy....
    //
    void AddButton(CToolBarButton* pButton);

    CToolBarButton* FindButton(UINT nCmdID)
    {
        return (nCmdID ? m_ctrlList.FindIndex(nCmdID) : (CToolBarButton*)NULL);
    }

public:
    BOOL LoadToolBar(UINT nIDResource);
    BOOL LoadToolBar(LPCTSTR lpszResource);

    void SaveCustomToolbarState();
    void LoadCustomToolbarState();

public:
    virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState, CPoint point);
    virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState, CPoint point);
    virtual BOOL       OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect, CPoint point);
    virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
    virtual void       OnDragLeave();
    virtual DROPEFFECT OnDragScroll(DWORD dwKeyState,CPoint point);

    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

protected:
    DROPEFFECT OnInsideDragging(COleDataObject* pDataObject,DWORD dwKeyState, CPoint point);
    void Transfer(DROPEFFECT dropEffect,CPoint pt,CXTToolbarDragItem &item);
    BOOL UpdateBitmap(DWORD nNewBitmap,int nCommandID,int &nIndex);
    void FindCorrectIndex(DWORD nBitmapID,int nCommandID,int &nIndex);
    void AdjustToolbarSize();
    static void RegisterMyFormat();

protected:
    CXTOleDropTarget m_dropTarget;
    bool m_bDragedOutside;
    bool m_bEnable;
    bool m_bIsDraging;
    UINT m_nIDResource;
    CString m_strResource;
    //
    static bool m_bRegistered;
    static UINT m_nIDClipFormat;

protected:
    //
    // Toolbar item position
    //
    int   OnPointHitTest(CPoint point,int &index) const;

protected:
    virtual BOOL OnCreateControls() { return TRUE; }

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg LRESULT OnInitialUpdate(WPARAM wParam,LPARAM lParam);
    afx_msg void OnToolbarDropDown(NMTOOLBAR* pnmh, LRESULT* plRes);
    DECLARE_MESSAGE_MAP()
private:
    void DumpLayout();      
    void AdjustChildWindowsPosition();
    void CreateDropControl(CXTToolbarDragItem &item,int nIndex);

    CToolBarButtonList m_ctrlList;
};


class CXTToolbarCmdUI : public CCmdUI        // class private to this file !
{
public: // re-implementations only
    virtual void Enable(BOOL bOn);
    virtual void SetCheck(int nCheck);
    virtual void SetText(LPCTSTR lpszText);
public:
    CToolBarButton*   m_pToolBarButton  ;
};

#define _XTTOOLBAR_
#endif
