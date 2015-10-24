
#include "stdafx.h"
#include "XTTitleBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXTTitleBar::CXTTitleBar()
	:m_wTitleHeight(25),
	m_wFillType(0),
	m_wColorType(0),
	m_wColorCount(0),
	m_wLastButton(0),
	m_bWndChang(false),
	m_hWnd(NULL),
	m_hBackground(NULL),
	m_hCompDC(NULL),
	m_hBmpDC(NULL),
	m_hFont(NULL)
{
	memset(m_clBackColor,		0, sizeof(m_clBackColor));
	memset(&m_szIcon,			0, sizeof(m_szIcon));
	memset(&m_ptSrcMinButton,	0, sizeof(m_ptSrcMinButton));
	memset(&m_ptSrcMaxButton,	0, sizeof(m_ptSrcMaxButton));
	memset(&m_ptSrcResumeButton,0, sizeof(m_ptSrcResumeButton));
	memset(&m_ptSrcCloseButton, 0, sizeof(m_ptSrcCloseButton));
	memset(&m_szMinButton,		0, sizeof(m_szMinButton));
	memset(&m_szMaxButton,		0, sizeof(m_szMaxButton));
	memset(&m_szResumeButton,	0, sizeof(m_szResumeButton));
	memset(&m_szCloseButton,	0, sizeof(m_szCloseButton));
}

CXTTitleBar::~CXTTitleBar()
{
	if (NULL != m_hFont)
		::DeleteObject(m_hFont);

	if (NULL != m_hBackground)
		::DeleteObject(m_hBackground);
}

BOOL CXTTitleBar::Init(HWND hWnd, HICON hIcon, LPCTSTR pstrIniFile)
{
	if (NULL == pstrIniFile) return FALSE;

	try
	{
		TCHAR tszTemp[MAX_PATH] = {_T("")};
		
		m_wTitleHeight = ::GetPrivateProfileInt(_T("TitleBar"), _T("Height"), 25, pstrIniFile);		
		m_szIcon.cx    = ::GetPrivateProfileInt(_T("TitleBar"), _T("IconCX"), 16, pstrIniFile);
		m_szIcon.cy    = ::GetPrivateProfileInt(_T("TitleBar"), _T("IconCY"), 16, pstrIniFile);

		m_ptSrcMinButton.x = ::GetPrivateProfileInt(_T("TitleBar"), _T("MinButtonBmpX"), 0, pstrIniFile);
		m_ptSrcMinButton.y = ::GetPrivateProfileInt(_T("TitleBar"), _T("MinButtonBmpY"), 0, pstrIniFile);
		m_szMinButton.cx   = ::GetPrivateProfileInt(_T("TitleBar"), _T("MinButtonCX"),  16, pstrIniFile);
		m_szMinButton.cy   = ::GetPrivateProfileInt(_T("TitleBar"), _T("MinButtonCY"),  16, pstrIniFile);

		m_ptSrcMaxButton.x = ::GetPrivateProfileInt(_T("TitleBar"), _T("MaxButtonBmpX"), 0, pstrIniFile);
		m_ptSrcMaxButton.y = ::GetPrivateProfileInt(_T("TitleBar"), _T("MaxButtonBmpY"), 0, pstrIniFile);
		m_szMaxButton.cx   = ::GetPrivateProfileInt(_T("TitleBar"), _T("MaxButtonCX"),  16, pstrIniFile);
		m_szMaxButton.cy   = ::GetPrivateProfileInt(_T("TitleBar"), _T("MaxButtonCY"),  16, pstrIniFile);

		m_ptSrcResumeButton.x = ::GetPrivateProfileInt(_T("TitleBar"), _T("ResumeButtonBmpX"), 0, pstrIniFile);
		m_ptSrcResumeButton.y = ::GetPrivateProfileInt(_T("TitleBar"), _T("ResumeButtonBmpY"), 0, pstrIniFile);
		m_szResumeButton.cx   = ::GetPrivateProfileInt(_T("TitleBar"), _T("ResumeButtonCX"),  16, pstrIniFile);
		m_szResumeButton.cy   = ::GetPrivateProfileInt(_T("TitleBar"), _T("ResumeButtonCY"),  16, pstrIniFile);

		m_ptSrcCloseButton.x  = ::GetPrivateProfileInt(_T("TitleBar"), _T("CloseButtonBmpX"), 0, pstrIniFile);
		m_ptSrcCloseButton.y  = ::GetPrivateProfileInt(_T("TitleBar"), _T("CloseButtonBmpY"), 0, pstrIniFile);
		m_szCloseButton.cx    = ::GetPrivateProfileInt(_T("TitleBar"), _T("CloseButtonCX"),  16, pstrIniFile);
		m_szCloseButton.cy    = ::GetPrivateProfileInt(_T("TitleBar"), _T("CloseButtonCY"),  16, pstrIniFile);
		
		UINT nHeight	= ::GetPrivateProfileInt(_T("TitleBar"), _T("FontHeight"),    20, pstrIniFile);
		UINT nWidth		= ::GetPrivateProfileInt(_T("TitleBar"), _T("FontWidth"),     20, pstrIniFile);
		BOOL bBold		= ::GetPrivateProfileInt(_T("TitleBar"), _T("FontBold"),       0, pstrIniFile);
		BOOL bItalic	= ::GetPrivateProfileInt(_T("TitleBar"), _T("FontItalic"),	   0, pstrIniFile);
		BOOL bUnderline	= ::GetPrivateProfileInt(_T("TitleBar"), _T("FontUnderline"),  0, pstrIniFile);
		BOOL bStrikeOut	= ::GetPrivateProfileInt(_T("TitleBar"), _T("FontStrikeOut"),  0, pstrIniFile);
		
		::GetPrivateProfileString(_T("TitleBar"), _T("ButtonFile"), _T(""), tszTemp, sizeof(tszTemp), pstrIniFile);
		m_xtDC.Init(NULL, hWnd, true);
		m_xtDC.SetBmpBKG(tszTemp, ::GetSystemMetrics(SM_CXSCREEN), m_wTitleHeight);
		m_hDC     = m_xtDC.GetHDC(0);
		m_hCompDC = m_xtDC.GetHDC(1);
		m_hBmpDC  = m_xtDC.GetHDC(2);
		m_hIcon   = hIcon;
		m_hWnd    = hWnd;
		
		::GetPrivateProfileString(_T("TitleBar"), _T("FontName"), _T("宋休"), tszTemp, sizeof(tszTemp), pstrIniFile);
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

		::GetPrivateProfileString(_T("TitleBar"), _T("FontColor"), _T("0,0,0"), tszTemp, sizeof(tszTemp), pstrIniFile);
		this->GetColor(tszTemp, &m_clFontColor);
		::SetTextColor(m_hCompDC, RGB(m_clFontColor.red, m_clFontColor.green, m_clFontColor.blue));

		m_wFillType	= ::GetPrivateProfileInt(_T("TitleBar"), _T("FillType"),  0, pstrIniFile);
		if (0 == m_wFillType)
		{
			::GetPrivateProfileString(_T("TitleBar"), _T("BackgroundFile"), _T(""), tszTemp, sizeof(tszTemp), pstrIniFile);
			m_hBackground = (HBITMAP)::LoadImage(NULL, tszTemp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		else if (1 == m_wFillType)
		{
			::GetPrivateProfileString(_T("TitleBar"), _T("Color"), _T(""), tszTemp, sizeof(tszTemp), pstrIniFile);
			this->GetColor(tszTemp, &m_clBackColor[0]);
		}
		else
		{
			::GetPrivateProfileString(_T("TitleBar"), _T("Color"), _T(""), tszTemp, sizeof(tszTemp), pstrIniFile);
			m_wColorCount = this->GetColorGroup(tszTemp);
			m_wColorType = ::GetPrivateProfileInt(_T("TitleBar"), _T("ColorType"),  0, pstrIniFile);
		}

		this->InitBackground();

		return TRUE;
	}
	catch (...)
	{
		TRACE(_T("CTitleBar::Init Error:%d"), ::GetLastError());
	}

	return FALSE;
}

void CXTTitleBar::GetColor(LPCTSTR pstrRGB, RGBCOLOR *pRGB)
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

WORD CXTTitleBar::GetColorGroup(LPCTSTR pstrGroupRGB)
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

void CXTTitleBar::InitBackground(RECT *pRect/*= NULL*/)
{
	if (NULL == pRect)
	{
		::GetWindowRect(m_hWnd, m_rcTitleBar);
	}
	else
	{
		m_rcTitleBar.left = pRect->left;
		m_rcTitleBar.top = pRect->top;
		m_rcTitleBar.right = pRect->right;
		m_rcTitleBar.bottom = pRect->bottom;
	}

	int nWidth = m_rcTitleBar.Width();

	if (0 == m_wFillType)		// 位图
	{
		HBITMAP hOldBmp = (HBITMAP)::SelectObject(m_hBmpDC, m_hBackground);		
		::StretchBlt(m_hCompDC, 0, 0, nWidth, m_wTitleHeight, m_hBmpDC, 0, 0, 1, m_wTitleHeight, SRCCOPY);
		::SelectObject(m_hBmpDC, hOldBmp);
	}
	else if (1 == m_wFillType)	// 单色
	{
		HBRUSH hBrFill = ::CreateSolidBrush(RGB(m_clBackColor[0].red,m_clBackColor[0].green, m_clBackColor[0].blue));
		::FillRect(m_hCompDC, CRect(0, 0, nWidth, m_wTitleHeight), hBrFill);
		::DeleteObject(hBrFill);
	}
	else						// 渐变色 m_wColorType 0为横向渐变，1为纵向渐变
	{
		int nInter = m_wColorType ? (m_wTitleHeight / (m_wColorCount - 1)) : (nWidth / (m_wColorCount - 1));
		
		TRIVERTEX *pVert = new TRIVERTEX[m_wColorCount];
		if (NULL != pVert)
		{
			for (int i = 0; i < m_wColorCount; i++)
			{
				pVert[i].x = m_wColorType ? (i%2 ? nWidth+10 : 0) : (i==m_wColorCount-1? nWidth+10 : i*nInter);
				pVert[i].y = m_wColorType ? (i==m_wColorCount-1? m_wTitleHeight : i*nInter) : (i%2 ? m_wTitleHeight:0);
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

	CString strTitle;
	::GetWindowText(m_hWnd, strTitle.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strTitle.ReleaseBuffer();

	HFONT hOldFont = (HFONT)::SelectObject(m_hCompDC, m_hFont);	
	::TextOut(m_hCompDC, 25, 3, strTitle, strTitle.GetLength());
	::SelectObject(m_hCompDC, hOldFont);

	::DrawIconEx(m_hCompDC, 3, 3, m_hIcon, m_szIcon.cx, m_szIcon.cy, 0, NULL, DI_NORMAL);

	m_rcCloseButton.left = nWidth - m_szCloseButton.cx - 5;
	m_rcCloseButton.top = 3;
	m_rcCloseButton.right = m_rcCloseButton.left + m_szCloseButton.cx;
	m_rcCloseButton.bottom = m_rcCloseButton.top + m_szCloseButton.cy;
	
	m_rcResumeButton.left = m_rcCloseButton.left - m_szResumeButton.cx - 2;
	m_rcResumeButton.top = 3;
	m_rcResumeButton.right = m_rcResumeButton.left + m_szResumeButton.cx;
	m_rcResumeButton.bottom = m_rcResumeButton.top + m_szResumeButton.cy;
	
	m_rcMaxButton.left = m_rcCloseButton.left - m_szMaxButton.cx - 2;
	m_rcMaxButton.top = 3;
	m_rcMaxButton.right = m_rcMaxButton.left + m_szMaxButton.cx;
	m_rcMaxButton.bottom = m_rcMaxButton.top + m_szMaxButton.cy;

	m_rcMinButton.left = (::IsZoomed(m_hWnd) ? m_rcResumeButton.left: m_rcMaxButton.left) - m_szMinButton.cx - 2;

	m_rcMinButton.top = 3;
	m_rcMinButton.right = m_rcMinButton.left + m_szMinButton.cx;
	m_rcMinButton.bottom = m_rcMinButton.top + m_szMinButton.cy;
	
	DrawButton(COMPDC, m_rcMinButton, m_ptSrcMinButton, OK);
	DrawButton(COMPDC, m_rcCloseButton, m_ptSrcCloseButton, OK);	

	if (::IsZoomed(m_hWnd))
		DrawButton(COMPDC, m_rcResumeButton, m_ptSrcResumeButton, OK);
	else
		DrawButton(COMPDC, m_rcMaxButton, m_ptSrcMaxButton, OK);
}

void CXTTitleBar::DrawButton(int nType, CRect &Rect, POINT &ps, int nStat)
{
	::BitBlt(DLGDC == nType? m_hDC : m_hCompDC, Rect.left, Rect.top, Rect.Width(), Rect.Height(), m_hBmpDC,
		ps.x + Rect.Width() * nStat, ps.y, SRCCOPY);
}

// 直接替换基类应用
BOOL CXTTitleBar::OnNcActivate(void)
{
	this->OnNcPaint();
	return TRUE;
}

// 直接替换基类应用
void CXTTitleBar::OnNcCalcSize(NCCALCSIZE_PARAMS* lpncsp)
{
	lpncsp->rgrc[0].left +=1;
	lpncsp->rgrc[0].right -=1;
	lpncsp->rgrc[0].top += m_wTitleHeight;
	lpncsp->rgrc[0].bottom -= 1;

	this->InitBackground(&(lpncsp->rgrc[0]));
/*
	int nWidth = lpncsp->rgrc[0].right - lpncsp->rgrc[0].left + 3;
	int nHeigth = lpncsp->rgrc[0].bottom - lpncsp->rgrc[0].top + 28;
	HRGN hRgn = ::CreateRoundRectRgn(0, 0, nWidth, nHeigth, 20, 20);
	::SetWindowRgn(m_hWnd, hRgn, TRUE);
*/
}

// 直接替换基类应用
void CXTTitleBar::OnNcPaint(void)
{
	::GetWindowRect(m_hWnd, m_rcTitleBar);

	::BitBlt(m_hDC, 0, 0, m_rcTitleBar.Width(), m_wTitleHeight, m_hCompDC, 0 ,0, SRCCOPY);

	CRect Rect;
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = m_rcTitleBar.Width();
	Rect.bottom = m_rcTitleBar.Height();

	POINT ps = {0};
	::MoveToEx(m_hDC, Rect.left, Rect.top, &ps);
	::LineTo(m_hDC, Rect.right - 1, Rect.top);
	::LineTo(m_hDC, Rect.right - 1, Rect.bottom - 1);
	::LineTo(m_hDC, Rect.left, Rect.bottom - 1);
	::LineTo(m_hDC, Rect.left, Rect.top);

	::Arc(m_hDC, Rect.left, Rect.top, Rect.left + 20, Rect.top + 20, Rect.left + 10, Rect.top, Rect.left, Rect.top + 10);
	::Arc(m_hDC, Rect.right - 20, Rect.top, Rect.right, Rect.top + 20, Rect.right, Rect.top + 10, Rect.right - 10, Rect.top);
}

// 直接替换基类应用
UINT CXTTitleBar::OnNcHitTest(CPoint point)
{
	::GetWindowRect(m_hWnd, m_rcTitleBar);

	point.x -= m_rcTitleBar.left;
	point.y -= m_rcTitleBar.top;

	if (m_rcMinButton.PtInRect(point))
		return MINBUTTON;
	else if (m_rcCloseButton.PtInRect(point))
		return CLOSEBUTTON;
	else if (::IsZoomed(m_hWnd))
	{
		if (m_rcResumeButton.PtInRect(point))
			return RESUMEBUTTON;
	}
	else if (m_rcMaxButton.PtInRect(point))
		return MAXBUTTON;

	return HTCAPTION;
}

// 直接替换基类应用
void CXTTitleBar::OnNcMouseMove(UINT nHitTest)
{
	if (NULL != m_wLastButton && m_wLastButton != nHitTest && !m_bWndChang)
	{
		switch (m_wLastButton)
		{
		case MINBUTTON:
			DrawButton(DLGDC, m_rcMinButton, m_ptSrcMinButton, OK);
			break;
		case MAXBUTTON:
			DrawButton(DLGDC, m_rcMaxButton, m_ptSrcMaxButton, OK);
			break;
		case RESUMEBUTTON:
			DrawButton(DLGDC, m_rcResumeButton, m_ptSrcResumeButton, OK);
			break;
		case CLOSEBUTTON:
			DrawButton(DLGDC, m_rcCloseButton, m_ptSrcCloseButton, OK);
			break;
		default:
			break;
		}
	}

	m_bWndChang = false;

	switch (nHitTest)
	{
	case MINBUTTON:
		DrawButton(DLGDC, m_rcMinButton, m_ptSrcMinButton, MOUSE_ON);
		m_wLastButton = MINBUTTON;
		break;
	case MAXBUTTON:
		DrawButton(DLGDC, m_rcMaxButton, m_ptSrcMaxButton, MOUSE_ON);
		m_wLastButton = MAXBUTTON;
		break;
	case RESUMEBUTTON:
		DrawButton(DLGDC, m_rcResumeButton, m_ptSrcResumeButton, MOUSE_ON);
		m_wLastButton = RESUMEBUTTON;
		break;
	case CLOSEBUTTON:
		DrawButton(DLGDC, m_rcCloseButton, m_ptSrcCloseButton, MOUSE_ON);
		m_wLastButton = CLOSEBUTTON;
		break;
	default:
		m_wLastButton = NULL;
		break;
	}
}

// 加在基类应用之前,如果直接替换就不能移动窗体
void CXTTitleBar::OnNcLButtonDown(UINT nHitTest)
{
	switch (nHitTest)
	{
	case MINBUTTON:
		DrawButton(DLGDC, m_rcMinButton, m_ptSrcMinButton, MOUSE_DOWN);
		break;
	case MAXBUTTON:
		DrawButton(DLGDC, m_rcMaxButton, m_ptSrcMaxButton, MOUSE_DOWN);
		break;
	case RESUMEBUTTON:
		DrawButton(DLGDC, m_rcResumeButton, m_ptSrcResumeButton, MOUSE_DOWN);
		break;
	case CLOSEBUTTON:
		DrawButton(DLGDC, m_rcCloseButton, m_ptSrcCloseButton, MOUSE_DOWN);
		break;
	default:
		break;
	}
}

// 直接替换基类应用
void CXTTitleBar::OnNcLButtonUp(UINT nHitTest)
{
	switch (nHitTest)
	{
	case MINBUTTON:
		::ShowWindow(m_hWnd, SW_MINIMIZE);
		break;
	case MAXBUTTON:
		::ShowWindow(m_hWnd, SW_MAXIMIZE);
		m_bWndChang = true;
		break;
	case RESUMEBUTTON:
		::ShowWindow(m_hWnd, SW_RESTORE);
		m_bWndChang = true;
		break;
	case CLOSEBUTTON:
		::PostMessage(m_hWnd, WM_CLOSE, NULL, NULL);
		break;
	default:
		m_wLastButton = NULL;
		break;
	}
}

