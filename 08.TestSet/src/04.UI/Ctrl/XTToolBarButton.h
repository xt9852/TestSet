#ifndef _TBBUTTON_
#define _TBBUTTON_

#pragma once

class CToolBarButton : public CObject
{
    DECLARE_SERIAL(CToolBarButton)
public:
    CToolBarButton()
    {
        Init();
    }
    CToolBarButton(int commandID, // command id     
        int  index,               // index on toolbar...
        UINT nBitmapID = 0,       // bitmap ID ( 0 is native...)
        int  nImage = -1)         // image index on bitmap...
    {
        Init();

        m_nCommandID = commandID;
        m_nIndex     = index;
        m_nBitmapID  = nBitmapID;
        m_iImage     = nImage;
    }
    virtual ~CToolBarButton()
    {}

    virtual void Serialize(CArchive &ar)
    {
        CObject::Serialize(ar);
        if (ar.IsStoring())
        {
            ar << m_nCommandID;  
            ar << m_nIndex;  
            ar << m_nBitmapID;  
            ar << m_iImage;  
            ar << m_nStyle;  
            ar << m_strBitmapFile;
            ar << m_rect;  
            ar << m_nMenuID;
            ar << m_bLocked;    // Removable button ?
        }
        else
        {
            ar >> m_nCommandID;  
            ar >> m_nIndex;  
            ar >> m_nBitmapID;  
            ar >> m_iImage;  
            ar >> m_nStyle;  
            ar >> m_strBitmapFile;
            ar >> m_rect;  
            ar >> m_nMenuID;
            ar >> m_bLocked;    // Removable button ?
        }
    }
public:
    void Set(const TBBUTTON &tbButton)
    {
        m_nCommandID = tbButton.idCommand;
        m_nIndex     = tbButton.iBitmap; 
        m_nStyle     = tbButton.fsStyle;   
    }

    void    SetCmdID(int nCommandID) { m_nCommandID = nCommandID; }
    void    SetIndex(int nIndex) { m_nIndex = nIndex; }
    void    SetBitmap(UINT nBitmapID) { m_nBitmapID = nBitmapID; m_strBitmapFile=_T(""); }
    void    SetImageIndex(int iImage) { m_iImage = iImage; }
    void    SetStyle(UINT nStyle) { m_nStyle = nStyle;}
    void    SetBitmap(LPCTSTR lpszFile) { m_strBitmapFile = lpszFile;  m_nBitmapID = 0; }
    void    SetRect(const CRect& rect) { m_rect = rect; }
    void    SetMenuID(UINT nMenuID) { m_nMenuID = nMenuID; }
    void    SetLocked(BOOL bLocked) { m_bLocked = bLocked; }

    int     GetCmdID() const { return m_nCommandID; }
    int     GetIndex() const { return m_nIndex; }
    UINT    GetBitmap() const { return m_nBitmapID; }
    int     GetImageIndex() const { return m_iImage; }
    UINT    GetStyle() const { return m_nStyle; }
    LPCTSTR GetBitmapFile() const { return m_strBitmapFile; }
    void    GetRect(CRect& rect) const { rect = m_rect; }
    UINT    GetMenuID() const { return m_nMenuID; }
    BOOL    IsLocked() const { return m_bLocked; }

    int     GetWidth() const { return m_rect.Width(); }    

public:
    virtual BOOL  IsWndControl() const { return FALSE; }

    virtual BOOL  IsControl() const { return FALSE; }
    virtual CWnd* GetWindowCtrl() { return (CWnd*)NULL; }
    virtual void  EnableControl(BOOL bEnable) { CWnd* pWnd=GetWindowCtrl(); if( pWnd ) pWnd->EnableWindow(bEnable);  }
    virtual BOOL  CreateControl(CToolBar* pParent);
    virtual void  SetButtonText(LPCTSTR lpszText)  { CWnd* pWnd=GetWindowCtrl(); if( pWnd && lpszText ) pWnd->SetWindowText( lpszText ); }

    virtual BOOL  OnToolbarDropDown(CToolBar* pParent, NMTOOLBAR* pnmtb, LRESULT *plr);

    virtual void  OnPrepareDrag(CToolBar* pParent);
    virtual void  OnFinishDrag(CToolBar* pParent);

protected:
    void  SetStockFont(CWnd* pWnd,int iStockFont = DEFAULT_GUI_FONT);
    void  CheckAndCreateButton(CToolBar* pParent);
    void  Init()
    {
        m_nCommandID    = 0;      // command ID
        m_nIndex        = 0;      // index in toolbar
        m_nBitmapID     = 0;      // Bitmap ID
        m_iImage        = 0;      // index into bitmap
        m_nStyle        = 0;      // TBBS_ styles
        m_strBitmapFile = _T(""); // Button Text...
        m_rect.SetRectEmpty();
        m_bLocked = FALSE;        // Removable button ?
    }

protected:

    int      m_nCommandID;    // command ID
    int      m_nIndex;        // index in toolbar
    UINT     m_nBitmapID;     // Bitmap ID
    int		 m_iImage;        // index into bitmap
    UINT	 m_nStyle;        // TBBS_ styles
    UINT     m_nMenuID;       // Menu ID
    CString  m_strBitmapFile; // Button Text...
    CRect    m_rect;          // Button location
    BOOL     m_bLocked;       // Removable button ?
};


class CToolBarEditButton : public CToolBarButton
{
    DECLARE_SERIAL(CToolBarEditButton)
public:
    CToolBarEditButton()
    {
        m_width  = 0;
        m_dwStyle= ES_AUTOHSCROLL;
    }
    CToolBarEditButton(int commandID, // command id     
        int  index,                   // index on toolbar...
        int  width=50,
        LONG style=ES_AUTOHSCROLL )
        :CToolBarButton(commandID,index)
    {
        m_width  = width;
        m_dwStyle= style;
    }
    virtual ~CToolBarEditButton() {}

    virtual void Serialize(CArchive &ar)
    {
        CToolBarButton::Serialize(ar);
        if (ar.IsStoring())
        {
            ar << m_width;
            ar << m_dwStyle;
        }
        else
        {
            ar >> m_width;
            ar >> m_dwStyle;
        }
    }

public:
    virtual BOOL  IsWndControl() const { return TRUE; }
    virtual BOOL  IsControl() const { return (m_edit.m_hWnd != NULL); }
    virtual CWnd* GetWindowCtrl() { return (m_edit.m_hWnd ? (CWnd*)&m_edit : (CWnd*)NULL); }
    virtual BOOL  CreateControl(CToolBar* pParent);

    virtual void  OnPrepareDrag(CToolBar* pParent);
    virtual void  OnFinishDrag(CToolBar* pParent);

protected:

    CEdit m_edit;
    int   m_width;
    DWORD m_dwStyle;
};

class CToolBarComboBoxButton : public CToolBarButton
{
    DECLARE_SERIAL(CToolBarComboBoxButton)
public:
    CToolBarComboBoxButton()
    {
        m_size.cx  = 0;
        m_size.cy  = 22;
        m_dwStyle  = CBS_DROPDOWNLIST | WS_VSCROLL;
        m_cbCurSel = CB_ERR;
    }
    CToolBarComboBoxButton(int commandID, // command id     
        int  index,                       // index on toolbar...
        int  width = 50,
        int  height = 120,
        LONG style = CBS_DROPDOWNLIST | WS_VSCROLL)
        :CToolBarButton(commandID,index)
    {
        m_size.cx= width;
        m_size.cy= height;
        m_dwStyle= style;
    }
    virtual ~CToolBarComboBoxButton()
    { m_strArray.SetSize(0); }

    virtual void Serialize(CArchive &ar)
    {
        CToolBarButton::Serialize(ar);

        if (ar.IsStoring())
        {
            ar << m_size.cx;
            ar << m_size.cy;
            ar << m_dwStyle;
        }
        else
        {
            ar >> m_size.cx;
            ar >> m_size.cy;
            ar >> m_dwStyle;
        }
        m_strArray.Serialize(ar);
    }

    void ResetContent()
    {
        if (m_combo.GetSafeHwnd())
            m_combo.ResetContent();
        else
            m_strArray.SetSize(0);
    }
    void AddString(const CString& str)
    {
        if (m_combo.GetSafeHwnd())
            m_combo.AddString(str);
        else
            m_strArray.SetAt(m_strArray.GetSize(),str);
    }

public:
    virtual BOOL  IsWndControl() const { return TRUE; }
    virtual BOOL  IsControl() const { return (m_combo.m_hWnd != NULL); }
    virtual CWnd* GetWindowCtrl() { return (m_combo.m_hWnd ? (CWnd*)&m_combo : (CWnd*)NULL); }
    virtual BOOL  CreateControl(CToolBar* pParent);

    virtual void  OnPrepareDrag(CToolBar* pParent);
    virtual void  OnFinishDrag(CToolBar* pParent);

protected:
    CComboBox    m_combo;
    CSize        m_size;
    DWORD        m_dwStyle;
    CStringArray m_strArray;
    int          m_cbCurSel;
};


class CToolBarProgressButton : public CToolBarButton
{
    DECLARE_SERIAL(CToolBarProgressButton)
public:
    CToolBarProgressButton()
    {
        m_width  = 0;
        m_nLower = 0;
        m_nUpper = 100;
        m_nStep  = 1;
        m_dwStyle= 0L;
    }
    CToolBarProgressButton(int  commandID,	// command id     
        int  index,		                    // index on toolbar...
        int  width   = 0,
        int  nLower  = 0,
        int  nUpper  = 100,
        int  nStep   = 1,
        LONG style   = 0L)
        :CToolBarButton(commandID,index)
    {
        m_width  = width;
        m_nLower = nLower;
        m_nUpper = nUpper;
        m_nStep  = nStep;
        m_dwStyle= style;
    }
    virtual ~CToolBarProgressButton() {}

    virtual void Serialize(CArchive &ar)
    {
        CToolBarButton::Serialize(ar);
        if (ar.IsStoring())
        {
            ar << m_width;
            ar << m_nLower;
            ar << m_nUpper;
            ar << m_nStep;
            ar << m_dwStyle;
        }else
        {
            ar >> m_width;
            ar >> m_nLower;
            ar >> m_nUpper;
            ar >> m_nStep;
            ar >> m_dwStyle;
        }
    }

public:
    virtual BOOL  IsWndControl() const { return TRUE; }
    virtual BOOL  IsControl() const { return (m_wndProgress.m_hWnd != NULL); }
    virtual CWnd* GetWindowCtrl() { return (m_wndProgress.m_hWnd ? (CWnd*)&m_wndProgress : (CWnd*)NULL); }
    virtual BOOL  CreateControl(CToolBar* pParent);

    virtual void  OnPrepareDrag(CToolBar* pParent);
    virtual void  OnFinishDrag(CToolBar* pParent);

protected:
    CProgressCtrl m_wndProgress;
    int           m_width;
    int           m_nLower;
    int           m_nUpper;
    int           m_nStep;
    DWORD         m_dwStyle;
};


typedef CTypedPtrList<CObList,CToolBarButton*>  CToolBarButton_List;


class CToolBarButtonList
{
public:
    CToolBarButtonList() {}
    ~CToolBarButtonList() {}

    void  Serialize(CArchive &ar) { m_list.Serialize(ar); }

    BOOL IsEmpty() const { return m_list.IsEmpty(); }
    int  GetCount() const { return (int)m_list.GetCount(); }
    void Destroy() { while (!m_list.IsEmpty()) delete m_list.RemoveHead(); }
    void Add(CToolBarButton* pItem) { if (pItem) m_list.AddTail(pItem); }
    BOOL OnToolbarDropDown(CToolBar* pParent,NMTOOLBAR* pnmtb, LRESULT *plr)
    {
        BOOL bResult = FALSE;
        POSITION pos;
        for(CToolBarButton* pItem=GetFirst(pos) ; pItem ; pItem=GetNext(pos) )
            if ((bResult=pItem->OnToolbarDropDown(pParent,pnmtb,plr)) ) break;
        return bResult;
    }
    BOOL CreateControl(CToolBar* pParent)
    {
        BOOL bResult=TRUE;
        POSITION pos;
        for (CToolBarButton* pItem=GetFirst(pos) ; pItem; pItem=GetNext(pos))
            if (!(bResult=pItem->CreateControl(pParent))) break;
        return bResult;
    }
    void EnableCtrl(BOOL bEnable)
    {
        POSITION pos;
        for (CToolBarButton* pItem=GetFirst(pos); pItem; pItem=GetNext(pos))
            pItem->EnableControl(bEnable);
    }
    CToolBarButton* FindIndex(int nID) const
    {
        POSITION pos;
        CToolBarButton* pItem=GetFirst(pos);
        for (; pItem; pItem=GetNext(pos))
            if (pItem->GetCmdID() == nID) break;
        return pItem;
    }
    BOOL Remove(CToolBarButton* pObj) { POSITION pos=m_list.Find(pObj);   if( !pos ) return FALSE;   m_list.RemoveAt(pos);   return TRUE;   }
    void Destroy(CToolBarButton* pButton)
    {
        if (pButton)
        {
            Remove(pButton);
            CWnd* pWnd = pButton->GetWindowCtrl();
            if (pWnd) pWnd->DestroyWindow();
            delete pButton;
        }
    }
    void OnFinishDrag(CToolBar* pParent)
    {
        POSITION pos;
        for( CToolBarButton* pItem=GetFirst(pos) ; pItem ; pItem=GetNext(pos) )
            pItem->OnFinishDrag(pParent);
    }

    CToolBarButton* GetFirst(POSITION& pos) const {  pos = m_list.GetHeadPosition();  return GetNext(pos); }
    CToolBarButton* GetNext(POSITION& pos)  const {  return pos != NULL ? m_list.GetNext(pos) : (CToolBarButton*)NULL; }

    CToolBarButton_List m_list;
};

#define _TBBUTTON_
#endif
