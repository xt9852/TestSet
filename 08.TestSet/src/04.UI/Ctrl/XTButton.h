
#pragma once
#include "XTUI.h"


class CXTButton : public CWnd, public CXTUI
{
	DECLARE_DYNAMIC(CXTButton)

public:
	CXTButton();
	virtual ~CXTButton();

private:
	CToolTipCtrl toolTip_;

	enum{ DLGDC, COMPDC, COMPTODLG, CLEAR};
	enum{ OK, MOUSE_ON, MOUSE_DOWN, DISABLE };

public:
	bool Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *xtDC, const char *text);
	void ResetImage(int sx = -1, int sy = -1);
	void DrawImage(UINT nObject, UINT nState = OK);
	
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);// 不加会出错，可能是设置了自绘属性，就必须有此函数，目前此函数为空
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()

public:
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	
	afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMove(int, int);
};


