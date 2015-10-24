// LHP 2004-4-29

#pragma once

#include <afxole.h>

// 拖动类型
#define DRAGTYPE_NONE			0
#define DRAGTYPE_FILE			1		// 文件

class COleDropTargetEx: public COleDropTarget
{
    DECLARE_DYNAMIC(COleDropTargetEx)
    DECLARE_INTERFACE_MAP()
    DECLARE_MESSAGE_MAP()

public:
    COleDropTargetEx();
    virtual ~COleDropTargetEx();

protected:
    LPDROPTARGET m_pIEDropTarget;

public:
    void SetIEDropTarget(LPDROPTARGET pDropTarget);
    void ReleaseIEDropTarget();

public:
    BEGIN_INTERFACE_PART(DropTargetEx, IDropTarget)
        INIT_INTERFACE_PART(COleDropTargetEx, DropTargetEx)
        STDMETHOD(DragEnter)(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
        STDMETHOD(DragOver)(DWORD, POINTL, LPDWORD);
        STDMETHOD(DragLeave)();
        STDMETHOD(Drop)(LPDATAOBJECT, DWORD, POINTL pt, LPDWORD);
    END_INTERFACE_PART(DropTargetEx)
};
