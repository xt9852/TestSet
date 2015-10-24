
/**
 在其调用窗体或框架中需要响应消息:
 WM_NCPAINT, WM_NCACTIVATE, WM_NCMOUSEMOVE, WM_NCLBUTTONUP
 WM_NCLBUTTONDOWN, WM_NCCALCSIZE
 不执行 WM_NCACTIVATE 消息基类处理函数,直接返回 TRUE
 不执行 WM_NCCALCSIZE 消息基类处理函数,直接赋值
*/

#pragma once
#include <Icm.h>
#include "XTDC.h"

class CXTTitleBar
{
public:
	CXTTitleBar();
	virtual ~CXTTitleBar();

private:
	WORD		m_wTitleHeight;
	WORD		m_wFillType;
	WORD		m_wColorType;		// 如果是渐变色,则为渐变类型(0横向, 1竖向)
	WORD		m_wColorCount;
	RGBCOLOR	m_clBackColor[20];

	WORD		m_wLastButton;
	bool		m_bWndChang;

	HICON		m_hIcon;
	HBITMAP		m_hBackground;
	HWND		m_hWnd;	
	CXTDC		m_xtDC;
	HDC			m_hDC;
	HDC			m_hCompDC;
	HDC			m_hBmpDC;
	HFONT		m_hFont;
	RGBCOLOR	m_clFontColor;

	SIZE		m_szIcon;
	POINT		m_ptSrcMinButton;	// 最小化按钮图片在文件中的位置
	POINT		m_ptSrcMaxButton;
	POINT		m_ptSrcResumeButton;// 恢复按钮
	POINT		m_ptSrcCloseButton;
	SIZE		m_szMinButton;
	SIZE		m_szMaxButton;
	SIZE		m_szResumeButton;
	SIZE		m_szCloseButton;
	CRect		m_rcMinButton;		// 按钮的实际位置	
	CRect		m_rcMaxButton;
	CRect		m_rcResumeButton;
	CRect		m_rcCloseButton;
	CRect		m_rcTitleBar;

	enum{ DLGDC, COMPDC };
	enum{ OK, MOUSE_ON, MOUSE_DOWN };
	enum{ MINBUTTON = 10000, MAXBUTTON, RESUMEBUTTON, CLOSEBUTTON};

	void GetColor(LPCTSTR pstrRGB, RGBCOLOR *pRGB);
	WORD GetColorGroup(LPCTSTR pstrGroupRGB);
	void InitBackground(RECT *pRect = NULL);
	void DrawButton(int nType, CRect &Rect, POINT &ps, int nStat);

public:
	BOOL Init(HWND hWnd, HICON hIcon, LPCTSTR pstrIniFile);

	BOOL OnNcActivate(void);
	void OnNcCalcSize(NCCALCSIZE_PARAMS* lpncsp);
	void OnNcPaint(void);
	UINT OnNcHitTest(CPoint point);
	void OnNcMouseMove(UINT nHitTest);
	void OnNcLButtonDown(UINT nHitTest);
	void OnNcLButtonUp(UINT nHitTest);
};
