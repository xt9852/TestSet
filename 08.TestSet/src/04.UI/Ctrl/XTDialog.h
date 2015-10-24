#pragma once
#include "XTUI.h"
#include "XTDC.h"
#include <list>

typedef std::list<RECT> RECT_LIST;


class CXTDialog : public CDialog, public CXTUI
{
public:
	CXTDialog(void);
	CXTDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	~CXTDialog(void);

protected:
	CXTDC xtDC_; // 双缓冲DC

	int	heigh_;	 // 标题栏高

	RECT_LIST rectList_;	// 需要画图的位置

public:
	void InitBkgBmp(int cx, int cy, int cr, int id);
	void SetDlgRect(int cx, int cy, int cr);
	void SetBkgBmp(int id, HMODULE module);

	CRect OutputText(int x, int y, const char *text);
	void ClearText(CRect rcText, HDC bkgDC);
	void DrawDlg(void);	

public:
	void SetTitleHeigh(int heigh) { heigh_ = heigh; }
	void AddCtrl(CXTUI *pCtrl, bool bNoDraw = false);
	void DelRect(int x, int y, int cx, int cy);
	void UpdateRect(CRect src, CRect del, RECT_LIST *list);
	void ResetImage(void);

public:
	DECLARE_MESSAGE_MAP()
	virtual void OnOK() {};
	afx_msg void OnPaint();	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
