// LHP 2004-4-29

#include "stdafx.h"
#include "OleDropTargetEx.h"


//IMPLEMENT_DYNAMIC(CMyOleDropTarget, COleDropTarget)	// 不能在静态MFC中编译
IMPLEMENT_DYNAMIC(COleDropTargetEx,   CCmdTarget)

BEGIN_MESSAGE_MAP(COleDropTargetEx, COleDropTarget)
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(COleDropTargetEx, COleDropTarget)
    INTERFACE_PART(COleDropTargetEx, IID_IDropTarget, DropTargetEx)
END_INTERFACE_MAP()

COleDropTargetEx::COleDropTargetEx()
{
    m_pIEDropTarget = NULL;
}

COleDropTargetEx::~COleDropTargetEx()
{
    ReleaseIEDropTarget();
}

void COleDropTargetEx::SetIEDropTarget(LPDROPTARGET pDropTarget)
{
    if(m_pIEDropTarget)
        ReleaseIEDropTarget();
    m_pIEDropTarget = pDropTarget;
    m_pIEDropTarget->AddRef();
}

void COleDropTargetEx::ReleaseIEDropTarget()
{
    if(!m_pIEDropTarget)
        return;
    m_pIEDropTarget->Release();
    m_pIEDropTarget = NULL;
}

STDMETHODIMP_(ULONG) COleDropTargetEx::XDropTargetEx::AddRef()
{
    METHOD_PROLOGUE_EX_(COleDropTargetEx, DropTargetEx)
        return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) COleDropTargetEx::XDropTargetEx::Release()
{
    METHOD_PROLOGUE_EX_(COleDropTargetEx, DropTargetEx)
        return pThis->ExternalRelease();
}

STDMETHODIMP COleDropTargetEx::XDropTargetEx::QueryInterface(
    REFIID iid, LPVOID* ppvObj)
{
    METHOD_PROLOGUE_EX_(COleDropTargetEx, DropTargetEx)
        return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP COleDropTargetEx::XDropTargetEx::DragEnter(THIS_ LPDATAOBJECT lpDataObject,
                                                        DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{
    METHOD_PROLOGUE_EX(COleDropTargetEx, DropTargetEx)
        ASSERT_VALID(pThis);

    if(pThis->m_pIEDropTarget)
        pThis->m_pIEDropTarget->DragEnter(lpDataObject, dwKeyState, pt, pdwEffect);
    return pThis->m_xDropTarget.DragEnter(lpDataObject, dwKeyState, pt, pdwEffect);
}

STDMETHODIMP COleDropTargetEx::XDropTargetEx::DragOver(THIS_ DWORD dwKeyState,
                                                       POINTL pt, LPDWORD pdwEffect)
{
    METHOD_PROLOGUE_EX(COleDropTargetEx, DropTargetEx)
        ASSERT_VALID(pThis);

    if(pThis->m_pIEDropTarget)
        pThis->m_pIEDropTarget->DragOver(dwKeyState, pt, pdwEffect);
    return pThis->m_xDropTarget.DragOver(dwKeyState, pt, pdwEffect);
}

STDMETHODIMP COleDropTargetEx::XDropTargetEx::DragLeave(THIS)
{
    METHOD_PROLOGUE_EX(COleDropTargetEx, DropTargetEx)
        ASSERT_VALID(pThis);

    if(pThis->m_pIEDropTarget)
        pThis->m_pIEDropTarget->DragLeave();
    return pThis->m_xDropTarget.DragLeave();
}

STDMETHODIMP COleDropTargetEx::XDropTargetEx::Drop(THIS_ LPDATAOBJECT lpDataObject,
                                                   DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{
    METHOD_PROLOGUE_EX(COleDropTargetEx, DropTargetEx)
        ASSERT_VALID(pThis);

    if(pThis->m_pIEDropTarget)
        pThis->m_pIEDropTarget->Drop(lpDataObject, dwKeyState, pt, pdwEffect);
    return pThis->m_xDropTarget.Drop(lpDataObject, dwKeyState, pt, pdwEffect);
}