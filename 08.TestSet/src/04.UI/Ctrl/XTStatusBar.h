
#pragma once
#include <Icm.h>
#include "XTDC.h"


class CXTStatusBar : public CStatusBar
{
	DECLARE_DYNAMIC(CXTStatusBar)

public:
	CXTStatusBar();
	virtual ~CXTStatusBar();

private:
	WORD		m_wHeight;
	WORD		m_wFillType;
	WORD		m_wColorType;		// 如果是渐变色,则为渐变类型(0横向, 1竖向)
	WORD		m_wColorCount;
	RGBCOLOR	m_clBackColor[20];
	
	CXTDC		m_xtDC;
	HDC			m_hDC;
	HDC			m_hCompDC;
	HDC			m_hBmpDC;
	HFONT		m_hFont;
	RGBCOLOR	m_clFontColor;
	HBITMAP		m_hBackground;

	CRect		m_Rect;

	void		GetColor(LPCTSTR pstrRGB, RGBCOLOR *pRGB);
	WORD		GetColorGroup(LPCTSTR pstrGroupRGB);
	void		InitBackground(void);

public:
	BOOL Init(LPCTSTR pstrIniFile);
	void SetPaneWidth(int nIndex, int nWidth);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


