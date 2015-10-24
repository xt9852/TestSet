
#pragma once
#include "XTUI.h"
#include "XTHeaderCtrl.h"
#include "XTHorScrollbar.h"
#include "XTVerScrollbar.h"


class CXTDC;

class CXTListCtrl : public CListCtrl, public CXTUI
{

public:
	CXTListCtrl();
	virtual ~CXTListCtrl();

	CXTHeaderCtrl	m_XTHeaderCtrl;
	CXTVerScrollbar	m_XTVerScrollbar;
	CXTHorScrollbar	m_XTHorScrollbar;

	CXTDC			*m_pxtDC;

	COLORREF		m_clrFgHi;
	COLORREF		m_clrBgHi;
	COLORREF		m_clrBkg;
	CFont			m_Font;
	int				m_nScrollbarWidth;
	bool			m_bInitHead;

	bool Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *pDBuffDC, const CString& strHeads);
	void MyShowWindow(int cmd);
	void MyMoveWindow(int x,int y,int cx,int cy);
	void MyInvalidate(void);
	void ResetImage(int sx = -1, int sy = -1);

protected:
	bool InitHead(const CString& strHeads);
	bool SetHead(const CString& strHeads);
	void EnableHighlighting(HWND hWnd, int row, bool bHighlight);
	bool IsRowSelected(HWND hWnd, int row);
	bool IsRowHighlighted(HWND hWnd, int row);

	virtual void PreSubclassWindow();
	//virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnCustomDrawList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	DECLARE_MESSAGE_MAP()
};
