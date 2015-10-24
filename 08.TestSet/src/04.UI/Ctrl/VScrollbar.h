
#pragma once

#include "XTUI.h"


#define WM_MOVEUP   ( WM_USER + 1000 )
#define WM_MOVEDOWN ( WM_USER + 1001 )

//class CProgressDlg;

class CXTDC;

class CVScrollBar : public CWnd, CXTUI
{
	DECLARE_DYNAMIC(CVScrollBar)

public:
	CVScrollBar();
	virtual ~CVScrollBar();

private:	
	int		thumbPos_;
	int		thumbLen_;
	
	int		lineNum_;	// 行数
	float	interval_;	// 每次移动的距离(单位像素)
	bool	inBar_;

	CRect	thumb_;
	CRect	upArraw_;
	CRect	downArraw_;	

	enum{ DLGDC, COMPDC, DLG_COMP_DC };
	enum{ OK, MOUSE_ON, MOUSE_DOWN };
	enum{ UPARRAW, DOWNARRAW, THUMB, THUMB_BKG, NOT }
	curPart_, lastPart_;//按下或鼠路过哪一部分

protected:
	DECLARE_MESSAGE_MAP()
	//{{AFX_VIRTUAL(CVScrollBar)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUALpublic:

public:
	bool Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *pxtDC);
	bool SetLineNum(int nLineNum);
	bool SetDlgPtr(CWnd *wnd);
	bool MoveTo(int nSubBallId);
	void ResetImage(int sx = -1, int sy = -1);

private:
	void DrawImage(int obj, int state, int part);
	void PageUp(int nLineNum);
	void PageDown(int nLineNum);
	void ScrollUp(int nLineNum);
	void ScrollDown(int nLineNum);	
	void LimitThumbPosition(void);
	void UpdateThumbPosition(int nInterval);
	void SetThumbTop(UINT nThumbTop);	

public:
	LRESULT  OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);		
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnMove(int x, int y);
	afx_msg void OnTimer(UINT nIDEvent);
};


