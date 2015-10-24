
#pragma once
#include "XTUI.h"

class CXTDC;

class CXTComboBox : public CComboBox, public CXTUI
{
	DECLARE_DYNAMIC(CXTComboBox)

public:
	CXTComboBox();
	virtual ~CXTComboBox();

private:
	BOOL		m_bMouseTracking;

	COLORREF	m_clrBkg;
	HBRUSH		m_hbrBkg;
	HBRUSH      m_hbrDisabled;
	HBRUSH      m_hbrHighlight;
	CFont		m_Font;

	CDC			m_memDC;
	CBitmap		m_memBmp;

	CRect		m_rcClient;
	CRect		m_rcItem;
	BOOL		m_bClicked;

	// enum used to determine the state the combo box should be
	enum STATE { NORMAL = 1, RAISED = 2, PRESSED = 3 };

	int      m_cxHThumb;     // Size of the drop arrow for the combo box.
	BOOL     m_bLBtnDown;    // TRUE if left mouse button is pressed
	BOOL     m_bPainted;     // used during paint operations
	BOOL     m_bHasFocus;    // TRUE if control has focus
	BOOL     m_bAutoComp;    // Used by Autocompleting.
	BOOL     m_bFlatLook;    // TRUE if the control is flat.
	BOOL     m_bDisableAC;   // TRUE when auto complete is disabled internally.
	COLORREF m_clr3DHilight; // System color for ::GetSysColor(COLOR_3DHILIGHT).
	COLORREF m_clr3DShadow;  // System color for ::GetSysColor(COLOR_3DSHADOW).
	COLORREF m_clr3DFace;    // System color for ::GetSysColor(COLOR_3DFACE).

public:

	// -> Input:   bDisable - TRUE to disable flat appearance.
	// -> Remarks: This member function will disable the flat look for the combo box.
	void DisableFlatLook(BOOL bDisable);

	// -> Input:   bEnable - TRUE to enable auto completion; otherwise FALSE.
	// -> Remarks: This member function enables or disables auto completion.
	virtual void EnableAutoCompletion(BOOL bEnable=TRUE);

	// -> Returns: TRUE if the mouse is over the combo box; otherwise FALSE.
	// -> Remarks: This member function determines if the mouse is within the controls rect.
	virtual BOOL PointInRect();

	virtual BOOL PointInRectClick();

	// -> Input:   pDC            - Points to the current device context.
	//             eState         - Current state of the combo box, either NORMAL, RAISED, or PRESSED.
	//             clrTopLeft     - RGB color value for top left 3D borders.
	//             clrBottomRight - RGB color value for bottom right 3D borders.
	//             
	// -> Remarks: This member function is called by the combo box whenever a paint 
	//             operation should occur.
	virtual void DrawCombo(CDC* pDC, STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight);

public:
	bool Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *xtDC);
	void ResetImage(int sx = -1, int sy = -1);
	void SetImage(void);
	void SetBkgColor(COLORREF clrBkg);

protected:
	void DrawItemText(LPDRAWITEMSTRUCT lpDIS, HBRUSH bBrush);
	virtual void PreSubclassWindow(void);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT   lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

AFX_INLINE void CXTComboBox::DisableFlatLook(BOOL bDisable) {
	m_bFlatLook = !bDisable;
}
AFX_INLINE void CXTComboBox::EnableAutoCompletion(BOOL bEnable/*=TRUE*/) {
	ASSERT(::IsWindow(m_hWnd)); m_bAutoComp = bEnable;
}
AFX_INLINE BOOL CXTComboBox::PointInRect() {
	ASSERT(::IsWindow(m_hWnd)); CPoint pt; GetCursorPos(&pt); CRect rcItem; GetWindowRect(&rcItem); return rcItem.PtInRect(pt);
}

AFX_INLINE BOOL CXTComboBox::PointInRectClick()
{
	ASSERT(::IsWindow(m_hWnd));
	CPoint pt;
	GetCursorPos(&pt);
	CRect rcItem;
	GetWindowRect(&rcItem);
	rcItem.left = rcItem.right - 17;
	return rcItem.PtInRect(pt);
}
