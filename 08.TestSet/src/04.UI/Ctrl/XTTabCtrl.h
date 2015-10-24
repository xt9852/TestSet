
#pragma once

class CXTTabCtrl : public CTabCtrl
{
    DECLARE_DYNAMIC(CXTTabCtrl)

public:
    CXTTabCtrl();
    virtual ~CXTTabCtrl();

protected:
    CBrush m_hbrFill;
    CBrush m_hbrEdge;
    CBrush m_hbrSelFill;
    CBrush m_hbrSelEdge;

    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    void DrawButtonItem(CPaintDC &dc, RECT &rc, UINT nID, INT nImageId, LPCTSTR strText, BOOL bSelected = FALSE);

    DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
};


