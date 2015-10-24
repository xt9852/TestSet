/////////////////////////////////////////////////////////////////////////////
// CCBEx window
#pragma once


//#include "EditEx.h"
//#include "listBoxEx.h"


class CCBEx : public CComboBox
{
// Construction
public:
 CCBEx();
    int m_nWidthDropBt;
 int m_nWidthDropList;
 CEdit m_editEx;
 CComboBox m_lbEx;
    void Init(CListBox *pLB);
// Attributes
public:

// Operations
public:

// Overrides
 // ClassWizard generated virtual function overrides
 //{{AFX_VIRTUAL(CCBEx)
 public:
 virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
 virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
 protected:
 virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
 //}}AFX_VIRTUAL

// Implementation
public:
 virtual ~CCBEx();

 // Generated message map functions
protected:
 //{{AFX_MSG(CCBEx)
 afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
 afx_msg void OnPaint();
 afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
 afx_msg void OnDestroy();
 afx_msg void OnDropdown();
 afx_msg void OnCloseup();
 afx_msg void OnMouseMove(UINT nFlags, CPoint point);
 //}}AFX_MSG

 DECLARE_MESSAGE_MAP()
};