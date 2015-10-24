#include "stdafx.h"
#include <afxpriv.h>
#include "resource.h"
#include "XTToolBar.h"


IMPLEMENT_DYNCREATE(CXTToolbar,CToolBar)

bool CXTToolbar::m_bRegistered = false;
UINT CXTToolbar::m_nIDClipFormat = 0;

CXTToolbar::CXTToolbar()
    :CToolBar(),
    m_bEnable(false),
    m_bIsDraging(false),
    m_bDragedOutside(false),
    m_nIDResource(0L)
{
    CXTToolbar::RegisterMyFormat();
}

void CXTToolbar::RegisterMyFormat()
{
    if (!CXTToolbar::m_bRegistered)
    {
        CXTToolbar::m_nIDClipFormat = RegisterClipboardFormat(CXTToolbar::GetClipboardFormatName());
        CXTToolbar::m_bRegistered = true;
    }
}

BOOL CXTToolbar::LoadToolBar(UINT nIDResource)
{
    m_nIDResource = nIDResource;  // salva l'ID della bitmap da caricare..

    BOOL bRtnCode;
    if ((bRtnCode = CToolBar::LoadToolBar(nIDResource)))
        LoadCustomToolbarState();

    return bRtnCode;
}

BOOL  CXTToolbar::LoadToolBar(LPCTSTR lpszResource)
{
    m_strResource = lpszResource ;

    BOOL bRtnCode;
    if ((bRtnCode = CToolBar::LoadToolBar(lpszResource)))
        LoadCustomToolbarState();

    return bRtnCode;
}

void CXTToolbar::SaveCustomToolbarState()
{
    // Hello boys NOT IMPLEMENTED...
}

void CXTToolbar::LoadCustomToolbarState()
{
    // Hello boys NOT IMPLEMENTED...
}
// 
// from bartool.cpp
//
void CXTToolbarCmdUI::Enable(BOOL bOn)
{
    m_bEnableChanged = TRUE;
    CXTToolbar* pToolBar = (CXTToolbar*)m_pOther;
    ASSERT(pToolBar != NULL);
    ASSERT_KINDOF(CXTToolbar, pToolBar);
    ASSERT(m_nIndex < m_nIndexMax);

    UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) & ~TBBS_DISABLED;
    if (!bOn)
    {
        nNewStyle |= TBBS_DISABLED;
        // WINBUG: If a button is currently pressed and then is disabled
        // COMCTL32.DLL does not unpress the button, even after the mouse
        // button goes up!  We work around this bug by forcing TBBS_PRESSED
        // off when a button is disabled.
        nNewStyle &= ~TBBS_PRESSED;
    }
    //	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
    pToolBar->SetButtonStyle(m_nIndex, nNewStyle);

    if (m_pToolBarButton && m_pToolBarButton->GetWindowCtrl())
    {
        if (!bOn && (::GetFocus() == m_pToolBarButton->GetWindowCtrl()->m_hWnd))
            m_pOther->GetParent()->GetNextDlgTabItem(m_pOther)->SetFocus();
        m_pToolBarButton->EnableControl(bOn);
    }
}

void CXTToolbarCmdUI::SetCheck(int nCheck)
{
    ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
    CXTToolbar* pToolBar = (CXTToolbar*)m_pOther;
    ASSERT(pToolBar != NULL);
    ASSERT_KINDOF(CXTToolbar, pToolBar);
    ASSERT(m_nIndex < m_nIndexMax);

    UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
        ~(TBBS_CHECKED | TBBS_INDETERMINATE);
    if (nCheck == 1)
        nNewStyle |= TBBS_CHECKED;
    else if (nCheck == 2)
        nNewStyle |= TBBS_INDETERMINATE;
    ASSERT(!(nNewStyle & TBBS_SEPARATOR));
    pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);
}

void CXTToolbarCmdUI::SetText(LPCTSTR lpszText)
{
    ASSERT (lpszText != NULL);

    CXTToolbar* pToolBar = (CXTToolbar*)m_pOther;
    ASSERT(pToolBar != NULL);
    ASSERT_KINDOF(CXTToolbar, pToolBar);
    ASSERT(m_nIndex < m_nIndexMax);

    if (m_pToolBarButton && m_pToolBarButton->GetWindowCtrl())
    {
        CString strNewText(lpszText);
        int index = strNewText.Find (_T('\t'));
        if( index != -1 ) strNewText = strNewText.Left( index );
        m_pToolBarButton->SetButtonText( strNewText );
    }
}

void CXTToolbar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
    if( m_bEnable ) return;

    CXTToolbarCmdUI state;
    state.m_pOther         = this;
    state.m_pToolBarButton = NULL;
    state.m_nIndexMax      = (UINT)GetToolBarCtrl().GetButtonCount();

    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
    {
        // get buttons state
        TBBUTTON button;
        GetToolBarCtrl().GetButton(state.m_nIndex, &button);
        state.m_nID             = button.idCommand;
        state.m_pToolBarButton  = ( button.idCommand ?
            FindButton( button.idCommand) :	(CToolBarButton*)NULL );

        // ignore separators
        if (state.m_pToolBarButton || !(button.fsStyle & TBSTYLE_SEP))
        {
            // allow reflections
            if (CWnd::OnCmdMsg(0,
                MAKELONG((int)CN_UPDATE_COMMAND_UI, WM_COMMAND+WM_REFLECT_BASE),
                &state, NULL))
                continue;

            // allow the toolbar itself to have update handlers
            if (CWnd::OnCmdMsg(state.m_nID, CN_UPDATE_COMMAND_UI, &state, NULL))
                continue;

            // allow the owner to process the update
            state.DoUpdate(pTarget,bDisableIfNoHndler);
        }
    }
    // update the dialog controls added to the toolbar
    UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

void CXTToolbar::EnableCustomization(bool bEnable)
{
    //
    // Enable or disable child's...
    //
    m_bEnable=bEnable;
    m_ctrlList.EnableCtrl((BOOL)!bEnable);
}

BEGIN_MESSAGE_MAP(CXTToolbar,CToolBar)
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_MESSAGE(WM_INITIALUPDATE, OnInitialUpdate)
    //ON_NOTIFY_REFLECT(TBN_DROPDOWN, OnToolbarDropDown)
END_MESSAGE_MAP()

void CXTToolbar::OnToolbarDropDown(NMTOOLBAR* pnmtb, LRESULT *plr)
{
    if( pnmtb != NULL ) m_ctrlList.OnToolbarDropDown(this,pnmtb,plr);
}

int CXTToolbar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if( CToolBar::OnCreate(lpCreateStruct) == -1) return -1;
    m_dropTarget.Register(this);  // register drop target
    return 0;                     
}

LRESULT CXTToolbar::OnInitialUpdate(WPARAM wParam,LPARAM lParam)
{
    OnCreateControls();
    m_ctrlList.CreateControl(this);
    return 0;
}

void CXTToolbar::OnLButtonDown(UINT nFlags, CPoint pt)
{
    if (m_bEnable)
    {
        int nHit,nIndex;
        TBBUTTON tbSource;

        if ((nHit = OnPointHitTest(pt,nIndex)) != -1 && GetToolBarCtrl().GetButton(nIndex, &tbSource))
        {
            //
            // Ok. Try to Drag...
            //
            CToolBarButton* pButton=NULL;
            if (tbSource.idCommand && (pButton=m_ctrlList.FindIndex(tbSource.idCommand)))
                pButton->OnPrepareDrag(this);

            COleDataSource srcItem;
            CSharedFile    globFile;
            CArchive       ar(&globFile,CArchive::store);
            CXTToolbarDragItem dragItem(m_nIDResource, nIndex,	tbSource, pButton);

            dragItem.Serialize(ar);         
            ar.Close();
            srcItem.CacheGlobalData(CXTToolbar::m_nIDClipFormat, globFile.Detach());

            CRect rcDrag(0,0,m_sizeButton.cx,m_sizeButton.cy);
            //
            // Start Drag & Drop :
            //
            m_bIsDraging      = true ;
            m_bDragedOutside  = false;
            //
            if (srcItem.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE,&rcDrag) == DROPEFFECT_NONE)
            {
                if (m_bDragedOutside)
                {
                    //
                    // Button is draged outside toolbar delete it...
                    //
                    if (pButton == NULL || !pButton->IsLocked())
                    {
                        GetToolBarCtrl().DeleteButton(nIndex);
                        if (pButton) m_ctrlList.Destroy(pButton);
                        AdjustChildWindowsPosition();
                    }
                }
            }
            m_bIsDraging = false;
        }
    }else
        CToolBar::OnLButtonDown(nFlags,pt);
}

DROPEFFECT CXTToolbar::OnInsideDragging(COleDataObject* pDataObject,DWORD dwKeyState, CPoint point)
{
    m_bDragedOutside=false;

    return (!pDataObject->IsDataAvailable(CXTToolbar::m_nIDClipFormat) ? DROPEFFECT_NONE :
    (m_bIsDraging ? DROPEFFECT_MOVE : DROPEFFECT_COPY));
}

DROPEFFECT CXTToolbar::OnDragEnter(COleDataObject* pDataObject,DWORD dwKeyState, CPoint point)
{
    return OnInsideDragging(pDataObject,dwKeyState,point);
}

DROPEFFECT CXTToolbar::OnDragScroll(DWORD dwKeyState,CPoint point)
{
    //  DROPEFFECT dropeffect=DROPEFFECT_SCROLL;
    //    if( !m_bIsDraging ){
    //  DROPEFFECT_NONE   The data object cannot be dropped in this window.
    //  DROPEFFECT_LINK for MK_CONTROL | MK_SHIFT  ?
    //      Creates a linkage between the object and its server.
    //  DROPEFFECT_COPY for MK_CONTROL   Creates a copy of the dropped object.
    //  DROPEFFECT_MOVE for MK_ALT  ?
    //      Creates a copy of the dropped object and delete the original object.
    //  DROPEFFECT_SCROLL   Indicates that a drag scroll operation is about to occur or is occurring in the target view. 
    //
    return (m_bIsDraging ? DROPEFFECT_MOVE : DROPEFFECT_COPY);
}

DROPEFFECT CXTToolbar::OnDragOver(COleDataObject* pDataObject,DWORD dwKeyState, CPoint point)
{
    return OnInsideDragging(pDataObject,dwKeyState,point);
}

void CXTToolbar::OnDragLeave()
{
    m_bDragedOutside = true;
}

BOOL CXTToolbar::OnDrop(COleDataObject* pDataObject,DROPEFFECT dropEffect, CPoint pt)
{
    BOOL  bRtnCode = FALSE;

    if (pDataObject->IsDataAvailable(CXTToolbar::m_nIDClipFormat))
    {
        bRtnCode = TRUE;
        TRY
        {
            HGLOBAL hGlob = pDataObject->GetGlobalData(CXTToolbar::m_nIDClipFormat);

            if (hGlob != NULL)
            {
                CSharedFile globFile;
                CXTToolbarDragItem dragItem;
                globFile.SetHandle(hGlob,FALSE);
                CArchive ar(&globFile,CArchive::load);
                dragItem.Serialize(ar);
                ar.Close();
                Transfer(dropEffect,pt,dragItem);
            }
        }
        CATCH(CException,e)
        {
            TRACE(_T("OnDrop error %d"), ::GetLastError());
        }END_CATCH;
    }
    return bRtnCode;
}

DROPEFFECT CXTToolbar::OnDropEx(COleDataObject* pDataObject,DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point)
{
    return (DROPEFFECT)-1;  // not implemented
}

int CXTToolbar::OnPointHitTest(CPoint point,int &index) const
{
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
    //
    // now hit test against CToolBar buttons
    //
    int nButtons = GetToolBarCtrl().GetButtonCount();
    int nHit  = -1;

    for (int i = 0; i < nButtons; i++)
    {
        CRect rect;
        if (GetToolBarCtrl().GetItemRect(i,&rect))
        {
            ++rect.bottom;
            ++rect.right;
            TBBUTTON button;

            if (rect.PtInRect(point) && GetToolBarCtrl().GetButton(i,&button))
            {
                //
                //   skip  !(button.fsStyle & TBSTYLE_SEP))
                //
                if (button.fsStyle & TBSTYLE_SEP)
                    nHit = 0;
                else
                    nHit = button.idCommand;

                index = i;
                break;
            }
        }
    }
    return nHit;
}

void CXTToolbar::DumpLayout()
{
#ifdef xxx
    int      nButtons = GetToolBarCtrl().GetButtonCount();
    CRect    rc;
    TBBUTTON tb;
    CWnd*    pWnd;
    for (int i = 0; i < nButtons ; i++)
    {
        GetToolBarCtrl().GetButton(i, &tb);
        GetToolBarCtrl().GetItemRect(i, &rc);
        pWnd = NULL;
        if (tb.idCommand) pWnd = GetDescendantWindow(tb.idCommand);
    }
#endif
}

void CXTToolbar::AdjustChildWindowsPosition()
{
    int nButtons = GetToolBarCtrl().GetButtonCount();
    TBBUTTON tb;
    CRect rect;
    //
    // first step remove double separators...
    //
    for (int i = 0; i < nButtons; i++)
    {
        GetToolBarCtrl().GetButton(i, &tb);
        if (!tb.idCommand && (tb.fsStyle & TBBS_SEPARATOR))
        {
            TBBUTTON tbNext;
            for (int j=i+1; j < nButtons; )
            {
                GetToolBarCtrl().GetButton(j, &tbNext);
                if (tb.idCommand == tbNext.idCommand && (tbNext.fsStyle & TBBS_SEPARATOR))
                {
                    GetToolBarCtrl().DeleteButton(j);
                    nButtons = GetToolBarCtrl().GetButtonCount();
                }
                else
                    break;
            }
        }
    }
    //
    // Adjust child's windows size & position
    //
    nButtons = GetToolBarCtrl().GetButtonCount();
    CToolBarButton* pButton;
    for (int i = 0; i < nButtons; i++)
    {
        GetToolBarCtrl().GetButton(i, &tb);
        if (tb.idCommand && (pButton=m_ctrlList.FindIndex(tb.idCommand)))
        {
            pButton->SetIndex(i);
            pButton->OnFinishDrag(this);
        }
    }
    //
    // Remove last button if separator...
    //
    if (nButtons > 1)
    {
        GetToolBarCtrl().GetButton(nButtons-1, &tb);
        if (!tb.idCommand && ( tb.fsStyle & TBBS_SEPARATOR))
            GetToolBarCtrl().DeleteButton(nButtons-1); // remove last separator..
    }

    DumpLayout();
    AdjustToolbarSize();
}

void CXTToolbar::CreateDropControl(CXTToolbarDragItem &item,int nIndex)
{
    item.m_pButton->SetIndex(nIndex);
    item.m_pButton->CreateControl(this);
    item.m_pButton->EnableControl(FALSE);
    m_ctrlList.Add(item.m_pButton);
    item.m_pButton = NULL;
}

void CXTToolbar::Transfer(DROPEFFECT dropEffect,CPoint pt,CXTToolbarDragItem &item)
{
    if( !item.m_bOnlyDrop ) return;

    int nButtonCount= GetToolBarCtrl().GetButtonCount(),
        nCommand = -1,
        nIndex   = -1;

    if (nButtonCount)
        nCommand = OnPointHitTest(pt,nIndex);
    else
        nIndex   = 0;     // Empty toolbar

    if (!nIndex && !item.m_tbButton.idCommand )
        return;   // no separator's at first place !

    if (!nButtonCount || (nCommand > -1 && nIndex > -1))
    {
        DumpLayout();
        TBBUTTON tbSource;
        item.CopyTBButton(item.m_tbButton,tbSource);

        if( dropEffect & DROPEFFECT_MOVE )
        {
            if( nIndex != item.m_nIndex )
            {
                GetToolBarCtrl().DeleteButton(item.m_nIndex);
                if( item.m_pButton )
                {
                    CToolBarButton*   pButton=m_ctrlList.FindIndex( item.m_pButton->GetCmdID() );
                    if (pButton) m_ctrlList.Destroy( pButton );
                }
                GetToolBarCtrl().InsertButton(nIndex,&tbSource);
                if (item.m_pButton) CreateDropControl(item,nIndex);

                AdjustChildWindowsPosition();
            }
        }
        else
        {
            if (dropEffect & DROPEFFECT_COPY)
            {
                if (!tbSource.idCommand && (tbSource.fsStyle & TBSTYLE_SEP))
                {
                    tbSource.idCommand =0;
                    //
                    // Simply insert a separator...
                    //
                    GetToolBarCtrl().InsertButton(nIndex,&tbSource);
                    AdjustChildWindowsPosition();
                }
                else
                {
                    //
                    // Se il comando non e' gia presente nella toolbar...
                    //
                    if (CommandToIndex(tbSource.idCommand) == -1)
                    {
                        //
                        // Fix Bitmap ID
                        //
                        tbSource.dwData=item.m_nBitmapID;
                        //
                        // Update bitmap
                        //
                        if (UpdateBitmap(item.m_nBitmapID,tbSource.idCommand,tbSource.iBitmap))
                        {
                            //
                            // Insert new button...
                            //
                            GetToolBarCtrl().InsertButton(nIndex,&tbSource);

                            if( item.m_pButton )
                                CreateDropControl(item,nIndex);

                            AdjustChildWindowsPosition();
                        }
                    }
                }
            }
        }
    }
}


BOOL CXTToolbar::UpdateBitmap(DWORD nNewBitmap,int nCommandID,int &nIndex)
{
    BOOL  bRtnCode=FALSE;
    //
    // Carica la bitmap del nuovo comando...    
    //
    CBitmap  bmpSource;
    BITMAP   bitmapSource;
    CBitmap* pbmpCurrent=CBitmap::FromHandle(m_hbmImageWell);
    BITMAP   bitmapCurrent;
    //
    if (pbmpCurrent)
    {
        if (pbmpCurrent->GetBitmap(&bitmapCurrent))
        {
            if (bmpSource.LoadBitmap(nNewBitmap))
            {
                if (bmpSource.GetBitmap(&bitmapSource))
                {
                    //
                    // Quanti comandi ci sono effettivamente nella bitmap ?
                    //
                    int nCount = bitmapCurrent.bmWidth / m_sizeImage.cx;
                    //
                    // find corrent index in source bitmap...
                    //
                    FindCorrectIndex(nNewBitmap,nCommandID,nIndex);
                    //
                    // ok copy...
                    //
                    CDC      dcDest;
                    CDC      dcSource;
                    CBitmap  bitOff;
                    //
                    dcDest.CreateCompatibleDC(NULL);
                    dcSource.CreateCompatibleDC(NULL);
                    //
                    bitOff.CreateBitmap( bitmapCurrent.bmWidth+m_sizeImage.cx,
                        bitmapCurrent.bmHeight ,
                        bitmapCurrent.bmPlanes,
                        bitmapCurrent.bmBitsPixel,
                        NULL );
                    //         
                    CBitmap* pOldDestBitmap =dcDest.SelectObject(&bitOff) ;
                    CBitmap* pOldSrcBitmap  =dcSource.SelectObject(pbmpCurrent);
                    //
                    // Copy current
                    //
                    dcDest.BitBlt(0,0,bitmapCurrent.bmWidth,bitmapCurrent.bmHeight,
                        &dcSource,0,0,SRCCOPY);
                    //
                    // Append last ....
                    //
                    dcSource.SelectObject(&bmpSource);
                    dcDest.BitBlt(bitmapCurrent.bmWidth,0,
                        bitmapCurrent.bmWidth+m_sizeImage.cx,
                        bitmapCurrent.bmHeight,
                        &dcSource,nIndex*m_sizeImage.cx,0,SRCCOPY);
                    //
                    dcDest.SelectObject(pOldDestBitmap);
                    dcSource.SelectObject(pOldSrcBitmap);
                    //
                    SetBitmap((HBITMAP)bitOff.Detach());
                    //
                    nIndex   = nCount;
                    bRtnCode = TRUE;
                }
            }
        }
    }
    return bRtnCode;
}

struct CToolBarData
{
    WORD wVersion;
    WORD wWidth;
    WORD wHeight;
    WORD wItemCount;
    //WORD aItems[wItemCount]

    WORD* items()
    { return (WORD*)(this+1); }
};

void CXTToolbar::FindCorrectIndex(DWORD nToolbarID,int nCommandID,int &nIndex)
{
    HINSTANCE   hInst = AfxFindResourceHandle((LPCTSTR)nToolbarID, RT_TOOLBAR);
#pragma warning(disable : 4312)
    HRSRC       hRsrc = ::FindResource(hInst,(LPCTSTR)nToolbarID, RT_TOOLBAR);
#pragma warning(disable : 4312)
    if (hRsrc == NULL) return;

    HGLOBAL     hGlobal = LoadResource(hInst, hRsrc);
    if (hGlobal == NULL) return;

    CToolBarData*  pData = (CToolBarData*)LockResource(hGlobal);
    if (pData == NULL) return;

    ASSERT(pData->wVersion == 1);

    int   iCommand;
    int   nTabs=0;
    for (int i=0  ; i < pData->wItemCount ; i++)
    {
        if (pData->items()[i])
        {
            iCommand =(int)pData->items()[i];
            if( iCommand == nCommandID )
            {
                nIndex=i-nTabs;
                break;
            }
        }
        else
        {
            nTabs++;
        }
    }
    UnlockResource(hGlobal);
    FreeResource(hGlobal);
}

void CXTToolbar::AdjustToolbarSize()
{
    Invalidate();
    GetParentFrame()->RecalcLayout();
}
//
void CXTToolbar::AddButton(CToolBarButton* pUserButton)
{
    if(pUserButton && pUserButton->GetCmdID())
    {
        //
        CToolBarButton*   pButton=m_ctrlList.FindIndex(pUserButton->GetCmdID());
        if (pButton) m_ctrlList.Destroy(pButton);
        //
        if( pUserButton->GetIndex() < 0 )
        {
            int   index = CommandToIndex( pUserButton->GetCmdID() );
            if (index < 0)
                pUserButton->SetIndex( GetToolBarCtrl().GetButtonCount() );
        }
        //
        if (GetSafeHwnd()) pUserButton->CreateControl(this);
        //
        m_ctrlList.Add(pUserButton);
    }
}

CToolBarButton* CXTToolbar::CreateButton(int    commandID,
                                         int    index    , // = -1 , // lo cerca...
                                         UINT   nBitmapID, // = 0  , // bitmap ID ( 0 is native...)
                                         int    nImage   , // = -1 ,
                                         UINT   nMenuID  ) // = 0
{
    CToolBarButton*   pButton=m_ctrlList.FindIndex(commandID);
    //
    if (pButton) m_ctrlList.Destroy(pButton);
    if (commandID && index < 0) index=CommandToIndex(commandID);
    //
    pButton  = new CToolBarButton(commandID,index,nBitmapID,nImage);
    //
    if (nMenuID) pButton->SetMenuID(nMenuID);
    //
    if (GetSafeHwnd()) pButton->CreateControl(this);
    //
    m_ctrlList.Add(pButton);
    //      
    return pButton;
}

CToolBarEditButton*  CXTToolbar::CreateEdit(int  commandID ,  // command id
                                            int  index     ,  // = -1   ,  // lo cerca...
                                            int  width     ,  // =50             ,  //
                                            LONG style     )  // =ES_AUTOHSCROLL )
{
    CToolBarButton*   pButton=m_ctrlList.FindIndex(commandID);
    //
    if (pButton) m_ctrlList.Destroy(pButton);
    if (commandID && index < 0) index=CommandToIndex(commandID);
    //
    CToolBarEditButton*  pEdit=new CToolBarEditButton(commandID,index,width,style);
    //
    if (GetSafeHwnd()) pEdit->CreateControl(this);
    //
    m_ctrlList.Add(pEdit);
    //      
    return pEdit;
}

CToolBarComboBoxButton* CXTToolbar::CreateCombo(int  commandID,
                                                int  index , //= -1     ,  // index on toolbar...
                                                int  width , //= 50     ,
                                                int  height, // = 120   ,
                                                LONG style ) // = CBS_DROPDOWNLIST | WS_VSCROLL);
{
    CToolBarButton*   pButton=m_ctrlList.FindIndex(commandID);
    //
    if (pButton) m_ctrlList.Destroy(pButton);
    if (commandID && index < 0) index=CommandToIndex(commandID);
    //
    CToolBarComboBoxButton* pCombo=new CToolBarComboBoxButton(commandID,index,width,height,style);
    //
    if (GetSafeHwnd()) pCombo->CreateControl(this);
    //
    m_ctrlList.Add(pCombo);
    //      
    return pCombo;
}

CToolBarProgressButton* CXTToolbar::CreateProgress(int  commandID,
                                                   int  index    , // = -1 
                                                   int  iWidth   , // = 0  
                                                   int  nLower   , // = 0  
                                                   int  nUpper   , // = 100
                                                   int  nStep    ) // = 1
{
    CToolBarButton*   pButton=m_ctrlList.FindIndex(commandID);
    //
    if (pButton) m_ctrlList.Destroy(pButton);
    if (commandID && index < 0) index=CommandToIndex(commandID);
    //
    CToolBarProgressButton* pProgress=new CToolBarProgressButton(commandID,index,iWidth,nLower,nUpper,nStep);
    //
    if (GetSafeHwnd()) pProgress->CreateControl(this);
    //
    m_ctrlList.Add(pProgress);
    //      
    return pProgress;
}
//
////////////
//
void  CXTToolbarDragItem::CopyTBButton(TBBUTTON tbSource,TBBUTTON &tbDest)
{
    tbDest.iBitmap  =tbSource.iBitmap  ; 
    tbDest.idCommand=tbSource.idCommand;
    tbDest.fsState  =tbSource.fsState  ;  
    tbDest.fsStyle  =tbSource.fsStyle  ; 
    tbDest.dwData   =tbSource.dwData   ; 
    tbDest.iString  =tbSource.iString  ;
}

void  CXTToolbarDragItem::Serialize(CArchive &ar)
{
    if (ar.IsStoring())
    {
        ar << m_bIsBetweenToolbars ;
        ar << m_nBitmapID          ;
        ar << m_nIndex             ;
        ar << m_tbButton.iBitmap   ;
        ar << m_tbButton.idCommand ;
        ar << m_tbButton.fsState   ;
        ar << m_tbButton.fsStyle   ;
        ar << (DWORD)m_tbButton.dwData;
        ar << (INT)m_tbButton.iString;
        ar << m_pButton            ;
    }
    else
    {
        ar >> m_bIsBetweenToolbars ;
        ar >> m_nBitmapID          ;
        ar >> m_nIndex             ;
        ar >> m_tbButton.iBitmap   ;
        ar >> m_tbButton.idCommand ;
        ar >> m_tbButton.fsState   ;
        ar >> m_tbButton.fsStyle   ;
        ar >> m_tbButton.dwData    ;
        ar >> m_tbButton.iString   ;
        ar >> m_pButton            ;
    }
}
//
//////////////////
//
DROPEFFECT CXTOleDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,DWORD dwKeyState, CPoint point)
{
    ASSERT_VALID(this);
    ASSERT_VALID(pWnd);
    //
    return (DROPEFFECT)(!pWnd->IsKindOf(RUNTIME_CLASS(CXTToolbar)) ? DROPEFFECT_NONE :
    ((CXTToolbar*)pWnd)->OnDragEnter(pDataObject, dwKeyState, point));
}

DROPEFFECT CXTOleDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,DWORD dwKeyState, CPoint point)
{
    ASSERT_VALID(this);
    ASSERT_VALID(pWnd);
    //
    return (DROPEFFECT)(!pWnd->IsKindOf(RUNTIME_CLASS(CXTToolbar)) ? DROPEFFECT_NONE :
    ((CXTToolbar*)pWnd)->OnDragOver(pDataObject, dwKeyState, point));
}

BOOL CXTOleDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,DROPEFFECT dropEffect, CPoint point)
{
    ASSERT_VALID(this);
    ASSERT_VALID(pWnd);
    //
    return (BOOL)(!pWnd->IsKindOf(RUNTIME_CLASS(CXTToolbar)) ? FALSE :
    ((CXTToolbar*)pWnd)->OnDrop(pDataObject, dropEffect, point) );
}

DROPEFFECT CXTOleDropTarget::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
                                      DROPEFFECT dropEffect, DROPEFFECT dropEffectList, CPoint point)
{
    ASSERT_VALID(this);
    ASSERT_VALID(pWnd);
    //
    return (DROPEFFECT)(!pWnd->IsKindOf(RUNTIME_CLASS(CXTToolbar)) ?
        (-1) : ((CXTToolbar*)pWnd)->OnDropEx(pDataObject, dropEffect, dropEffectList, point)); // not implemented
}

void CXTOleDropTarget::OnDragLeave(CWnd* pWnd)
{
    ASSERT_VALID(this);
    ASSERT_VALID(pWnd);
    //
    if (pWnd->IsKindOf(RUNTIME_CLASS(CXTToolbar)))
        ((CXTToolbar*)pWnd)->OnDragLeave();
}

DROPEFFECT CXTOleDropTarget::OnDragScroll(CWnd* pWnd, DWORD dwKeyState,CPoint point)
{
    ASSERT_VALID(this);
    ASSERT_VALID(pWnd);
    //
    return (DROPEFFECT)(!pWnd->IsKindOf(RUNTIME_CLASS(CXTToolbar)) ? DROPEFFECT_NONE :
    ((CXTToolbar*)pWnd)->OnDragScroll(dwKeyState, point));
}

