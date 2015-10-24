// AtlEdit.h : Declaration of the CAtlEdit
//
// This is a part of the Active Template Library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#pragma once
#include "resource.h"       // main symbols
#include "AddInVSEx.h"
#include "AddinWnd.h"

#pragma warning ( disable : 4244 )

/////////////////////////////////////////////////////////////////////////////
// CAtlEdit
class CAtlEdit :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CAtlEdit, &CLSID_CAtlEdit>,
    public IDispatchImpl<IAtlEdit, &IID_IAtlEdit, &LIBID_AddinVSExLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public CComControl<CAtlEdit>,
    public IProvideClassInfoImpl<&CLSID_CAtlEdit, &LIBID_AddinVSExLib>,
    public IPersistStreamInitImpl<CAtlEdit>,
    public IPersistStorageImpl<CAtlEdit>,
    public IQuickActivateImpl<CAtlEdit>,
    public IOleControlImpl<CAtlEdit>,
    public IOleObjectImpl<CAtlEdit>,
    public IOleInPlaceActiveObjectImpl<CAtlEdit>,
    public IViewObjectExImpl<CAtlEdit>,
    public IOleInPlaceObjectWindowlessImpl<CAtlEdit>,
    public IDataObjectImpl<CAtlEdit>,
    public ISpecifyPropertyPagesImpl<CAtlEdit>
{
public:
    CAtlEdit();
    ~CAtlEdit();

public:
    CAddinWnd addinWnd_; // 插件窗体

DECLARE_REGISTRY_RESOURCEID(IDR_AtlEdit)


BEGIN_COM_MAP(CAtlEdit)
    COM_INTERFACE_ENTRY(IAtlEdit)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
    COM_INTERFACE_ENTRY_IMPL(IOleControl)
    COM_INTERFACE_ENTRY_IMPL(IOleObject)
    COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
    COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
    COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
    COM_INTERFACE_ENTRY2(IPersist,IPersistStreamInit)
    COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
    COM_INTERFACE_ENTRY_IMPL(IDataObject)
    COM_INTERFACE_ENTRY(IProvideClassInfo)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CAtlEdit)
    PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CAtlEdit)
    MESSAGE_HANDLER(WM_CREATE,              OnCreate)
    MESSAGE_HANDLER(WM_DESTROY,             OnDestroy)
    MESSAGE_HANDLER(WM_MOUSEMOVE,           OnMouseMove)
    MESSAGE_HANDLER(WM_LBUTTONDOWN,         OnMouseDown)
    MESSAGE_HANDLER(WM_LBUTTONUP,           OnMouseUp)
    NOTIFY_CODE_HANDLER(TVN_SELCHANGED,     OnTreeClk);
    NOTIFY_CODE_HANDLER(TVN_ENDLABELEDIT,   OnTreeRename);
    NOTIFY_CODE_HANDLER(NM_DBLCLK,          OnListOpen);
    NOTIFY_CODE_HANDLER(NM_RDBLCLK,         OnListAdd);
    NOTIFY_CODE_HANDLER(LVN_COLUMNCLICK,    OnListSort)
    NOTIFY_CODE_HANDLER(LVN_BEGINDRAG,      OnListBegingDrag)
    NOTIFY_CODE_HANDLER(LVN_ENDLABELEDIT,   OnListRename)
ALT_MSG_MAP(1) // server
    MESSAGE_HANDLER(WM_MOUSEWHEEL,          OnComboMouseWheel)
    MESSAGE_HANDLER(WM_COMMAND,             OnComboServerCommand)
ALT_MSG_MAP(2) // connect
    MESSAGE_HANDLER(WM_MOUSEWHEEL,          OnComboMouseWheel)
    MESSAGE_HANDLER(WM_COMMAND,             OnComboConnectCommand)
ALT_MSG_MAP(3) // terminal
    MESSAGE_HANDLER(WM_SETFOCUS,            OnEditSetFocus)
    MESSAGE_HANDLER(WM_KILLFOCUS,           OnEditKillFocus)
    MESSAGE_HANDLER(WM_SIZE,                OnEditSize) // 收不到
    MESSAGE_HANDLER(WM_PAINT,               OnEditPaint)
    MESSAGE_HANDLER(WM_ERASEBKGND,          OnEditEraseBkgnd)
    MESSAGE_HANDLER(WM_CHAR,                OnEditChar)
    MESSAGE_HANDLER(WM_KEYDOWN,             OnEditKeyDown)
    MESSAGE_HANDLER(WM_VSCROLL,             OnEditVScroll)
    MESSAGE_HANDLER(WM_MOUSEWHEEL,          OnEditMouseWheel)
    MESSAGE_HANDLER(WM_RBUTTONUP,           OnEditRButtonUp) // 收不到
ALT_MSG_MAP(4) // tree
    MESSAGE_HANDLER(WM_KEYDOWN,             OnTreeKeyDown)
ALT_MSG_MAP(5) // list
    MESSAGE_HANDLER(WM_KEYDOWN,             OnListDel)
    MESSAGE_HANDLER(WM_DROPFILES,           OnListDropFiles) // 收不到
ALT_MSG_MAP(6) // path
END_MSG_MAP()

public:
    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnMouseUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnMouseDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);

    LRESULT OnComboServerCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnComboConnectCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnComboMouseWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);

    LRESULT OnEditSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditChar(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnEditKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnEditVScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditRButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    LRESULT OnTreeClk(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnTreeRename(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnTreeKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    LRESULT OnListAdd(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnListDel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnListRename(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnListOpen(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnListSort(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnListBegingDrag(WPARAM /*wParam*/, NMHDR* pNMHDR, BOOL& /*bHandled*/);
    LRESULT OnListDropFiles(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    STDMETHOD(setParam)(int id, const char *param);
    STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip);
};

OBJECT_ENTRY_AUTO(__uuidof(CAtlEdit), CAtlEdit)
