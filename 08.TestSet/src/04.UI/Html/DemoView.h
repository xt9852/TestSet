#pragma once

#include "HtmlViewEx.h"

class CDemoView : public CHtmlViewEx
{
    DECLARE_DYNCREATE(CDemoView)
    DECLARE_MESSAGE_MAP()
    DECLARE_DISPATCH_MAP() // 构建dispatch映射表以暴露方法或属性

public:
    CDemoView();
    virtual ~CDemoView();

protected:
    virtual void OnInitialUpdate();

    virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);

    virtual HRESULT OnShowCustomContextMenu(LPPOINT ppt, LPUNKNOWN pcmdtReserved,LPDISPATCH pdispReserved);

    void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName,
        CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);

protected:
    void WobbleWnd();// 抖动窗口
};
