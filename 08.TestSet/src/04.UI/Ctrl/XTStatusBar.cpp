// XTStatusBar.cpp : 实现文件
//

#include "stdafx.h"
#include "XTStatusBar.h"
#include ".\xtstatusbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXTStatusBar

IMPLEMENT_DYNAMIC(CXTStatusBar, CStatusBar)
CXTStatusBar::CXTStatusBar()
	:m_wHeight(20),
	m_wFillType(0),
	m_wColorType(0),
	m_wColorCount(0),
	m_hBackground(NULL),
	m_hCompDC(NULL),
	m_hBmpDC(NULL),
	m_hFont(NULL)
{
}

CXTStatusBar::~CXTStatusBar()
{
}


BEGIN_MESSAGE_MAP(CXTStatusBar, CStatusBar)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CXTStatusBar::Init(LPCTSTR pstrIniFile)
{
	if (NULL == pstrIniFile) return FALSE;

	try
	{
		TCHAR tszTemp[MAX_PATH] = {_T("")};

		m_wHeight = ::GetPrivateProfileInt(_T("StatusBar"), _T("Height"), 25, pstrIniFile);		

		UINT nHeight	= ::GetPrivateProfileInt(_T("StatusBar"), _T("FontHeight"),    20, pstrIniFile);
		UINT nWidth		= ::GetPrivateProfileInt(_T("StatusBar"), _T("FontWidth"),     20, pstrIniFile);
		BOOL bBold		= ::GetPrivateProfileInt(_T("StatusBar"), _T("FontBold"),       0, pstrIniFile);
		BOOL bItalic	= ::GetPrivateProfileInt(_T("StatusBar"), _T("FontItalic"),	   0, pstrIniFile);
		BOOL bUnderline	= ::GetPrivateProfileInt(_T("StatusBar"), _T("FontUnderline"),  0, pstrIniFile);
		BOOL bStrikeOut	= ::GetPrivateProfileInt(_T("StatusBar"), _T("FontStrikeOut"),  0, pstrIniFile);

		::GetPrivateProfileString(_T("StatusBar"), _T("FontName"), _T("宋休"), tszTemp, sizeof(tszTemp), pstrIniFile);
		m_hFont = ::CreateFont(nHeight,	// nHeight 高度
			nWidth,						// nWidth 宽度
			0,							// nEscapement 文本行逆时针旋转角度 
			0,							// nOrientation 字体角度
			bBold ? FW_BOLD : FW_NORMAL,// nWeight 字体粗细程度 
			bItalic,					// bItalic 斜体
			bUnderline,					// bUnderline 下划线
			bStrikeOut,					// cStrikeOut 删除线
			DEFAULT_CHARSET,			// nCharSet 
			OUT_DEFAULT_PRECIS,			// nOutPrecision 
			CLIP_DEFAULT_PRECIS,		// nClipPrecision 
			DEFAULT_QUALITY,			// nQuality 
			DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily 
			tszTemp);
		
		::GetPrivateProfileString(_T("StatusBar"), _T("FontColor"), _T("0,0,0"), tszTemp, sizeof(tszTemp), pstrIniFile);
		this->GetColor(tszTemp, &m_clFontColor);
		
		m_xtDC.Init(NULL, this->GetSafeHwnd(), true);
		
		m_wFillType	= ::GetPrivateProfileInt(_T("StatusBar"), _T("FillType"),  0, pstrIniFile);
		if (0 == m_wFillType)
		{
			::GetPrivateProfileString(_T("StatusBar"), _T("BackgroundFile"), _T(""), tszTemp, sizeof(tszTemp), pstrIniFile);
			m_hBackground = (HBITMAP)::LoadImage(NULL, tszTemp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			m_xtDC.SetBKG(m_hBackground, ::GetSystemMetrics(SM_CXSCREEN), m_wHeight);
		}
		else if (1 == m_wFillType)
		{
			::GetPrivateProfileString(_T("StatusBar"), _T("Color"), _T(""), tszTemp, sizeof(tszTemp), pstrIniFile);
			this->GetColor(tszTemp, &m_clBackColor[0]);
			m_xtDC.CreateCompDC(::GetSystemMetrics(SM_CXSCREEN), m_wHeight);
		}
		else
		{
			::GetPrivateProfileString(_T("StatusBar"), _T("Color"), _T(""), tszTemp, sizeof(tszTemp), pstrIniFile);
			m_wColorCount = this->GetColorGroup(tszTemp);
			m_wColorType = ::GetPrivateProfileInt(_T("StatusBar"), _T("ColorType"),  0, pstrIniFile);
			m_xtDC.CreateCompDC(::GetSystemMetrics(SM_CXSCREEN), m_wHeight);
		}

		m_hDC     = m_xtDC.GetHDC(0);
		m_hCompDC = m_xtDC.GetHDC(1);
		m_hBmpDC  = m_xtDC.GetHDC(2);
		
		::SetTextColor(m_hCompDC, RGB(m_clFontColor.red, m_clFontColor.green, m_clFontColor.blue));		

		this->InitBackground();

		return TRUE;
	}
	catch (...)
	{
		TRACE(_T("CXTStatusBar::Init Error:%d"), ::GetLastError());
	}

	return FALSE;
}

void CXTStatusBar::GetColor(LPCTSTR pstrRGB, RGBCOLOR *pRGB)
{
	CString strRGB(pstrRGB);
	int nPos = 0;

	for (int i = 0; i < 3; i++)
	{
		CString strValue = strRGB.Tokenize(_T(","), nPos);
		if (-1 == nPos) break;

		if (0 == i) pRGB->red = _ttoi(strValue);
		else if (1 == i) pRGB->green = _ttoi(strValue);
		else pRGB->blue = _ttoi(strValue);
	}
}

WORD CXTStatusBar::GetColorGroup(LPCTSTR pstrGroupRGB)
{
	CString strGroupRGB(pstrGroupRGB);

	int nPos = 0;
	int i = 0;

	for (; i < 20; i++)
	{
		CString strRGB = strGroupRGB.Tokenize(_T("|"), nPos);

		if (-1 == nPos) break;

		this->GetColor(strRGB, &m_clBackColor[i]);
	}

	return i;
}

void CXTStatusBar::InitBackground(void)
{
	//GetWindowRect(m_Rect);

	int nWidth = m_Rect.Width();

	if (0 == m_wFillType)		// 位图
	{
		::StretchBlt(m_hCompDC, 0, 0, nWidth, m_wHeight, m_hBmpDC, 0, 0, 1, m_wHeight, SRCCOPY);
	}
	else if (1 == m_wFillType)	// 单色
	{
		HBRUSH hBrFill = ::CreateSolidBrush(RGB(m_clBackColor[0].red,m_clBackColor[0].green, m_clBackColor[0].blue));
		::FillRect(m_hCompDC, CRect(0, 0, nWidth, m_wHeight), hBrFill);
		::DeleteObject(hBrFill);
	}
	else						// 渐变色
	{
		int nInter = m_wColorType ? (m_wHeight / (m_wColorCount - 1)) : (nWidth / (m_wColorCount - 1));

		TRIVERTEX *pVert = new TRIVERTEX[m_wColorCount];
		if (NULL != pVert)
		{
			for (int i = 0; i < m_wColorCount; i++)
			{
				pVert[i].x = m_wColorType ? (i%2 ? nWidth+10 : 0) : (i==m_wColorCount-1? nWidth+10 : i*nInter);
				pVert[i].y = m_wColorType ? (i==m_wColorCount-1? m_wHeight : i*nInter) : (i%2 ? m_wHeight:0);
				pVert[i].Red   = m_clBackColor[i].red * 256;
				pVert[i].Green = m_clBackColor[i].green * 256;
				pVert[i].Blue  = m_clBackColor[i].blue * 256;
				pVert[i].Alpha = 0;
			}
		}

		GRADIENT_RECT *pGrad = new GRADIENT_RECT[m_wColorCount - 1];
		if (NULL != pGrad)
		{
			for (int i = 0; i < m_wColorCount - 1; i++)
			{
				pGrad[i].UpperLeft = i;
				pGrad[i].LowerRight = i + 1;
			}
		}

		::GradientFill(m_hCompDC, pVert, m_wColorCount, pGrad, m_wColorCount - 1, m_wColorType);

		if (NULL != pVert) delete pVert;
		if (NULL != pGrad) delete pGrad;
	}

	HFONT hOldFont = (HFONT)::SelectObject(m_hCompDC, m_hFont);	

	UINT nId     = 0;
	UINT nStyle  = 0;
	int  nPaneCX = 0;
	int  nPosX   = 0;
	CString strText;	

	for (int i = 0; i < m_nCount; i++)
	{
		this->GetPaneInfo(i, nId, nStyle, nPaneCX);
		strText = this->GetPaneText(i);
		if (0 == nStyle)
		::TextOut(m_hCompDC, nPosX, 3, strText, strText.GetLength());
		nPosX += nPaneCX;
	}

	::SelectObject(m_hCompDC, hOldFont);
}

void CXTStatusBar::SetPaneWidth(int nIndex, int nWidth)
{
	UINT nId     = 0;
	UINT nStyle  = 0;
	int  nOldWidth = 0;

	GetPaneInfo(nIndex, nId, nStyle, nOldWidth);
	SetPaneInfo(nIndex, nId, nStyle, nWidth);
}

void CXTStatusBar::OnPaint()
{
	CPaintDC dc(this);
	//CClientDC dc(this) ;

	this->InitBackground();
	::BitBlt(m_hDC, 0, 0, m_Rect.Width(), m_wHeight, m_hCompDC, 0, 0, SRCCOPY);	

	::Arc(m_hDC, 0, 0, 20, 19, 0, 10, 10, 20);
	::Arc(m_hDC, m_Rect.right - 20, 0, m_Rect.right, 19, m_Rect.right - 11, 20, m_Rect.right, 10);
}

void CXTStatusBar::OnSize(UINT nType, int cx, int cy)
{
	CStatusBar::OnSize(nType, cx, cy);
	GetClientRect(m_Rect);
}
