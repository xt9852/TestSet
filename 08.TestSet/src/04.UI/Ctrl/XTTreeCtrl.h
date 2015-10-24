
#pragma once

class CXTTreeCtrl : public CTreeCtrl
{
    DECLARE_DYNAMIC(CXTTreeCtrl)

public:
    CXTTreeCtrl(void);
    virtual ~CXTTreeCtrl();

protected:
    DECLARE_MESSAGE_MAP()
    CImageList	m_ImageList;
    HTREEITEM   m_hRoot;

    HTREEITEM   FindNode(HTREEITEM hItem, LPCTSTR sName, DWORD dwData);

public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

    bool		SetImage(UINT uImageId, UINT uImageCount);

    HTREEITEM	AddNode(HTREEITEM hParent, CString sName, DWORD dwData, DWORD dwIcon);
    void        DelNode(DWORD dwData);

    HTREEITEM   GetNode(DWORD dwData);
    HTREEITEM   GetNode(LPCTSTR sName);
    BOOL        SetNode(HTREEITEM hItem, LPCTSTR sParam, ...);

};


