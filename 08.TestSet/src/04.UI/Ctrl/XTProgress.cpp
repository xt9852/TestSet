// XTProgress.cpp : 实现文件
//

#include "stdafx.h"
#include "XTProgress.h"
#include "XTDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXTProgress::CXTProgress()
    :m_hDC(NULL),
    m_hCompDC(NULL),
    m_hBmpDC(NULL),
    m_hFont(NULL),
    m_clFont(0),
    m_nMax(100)
{
    m_Sz.cx = 0;
    m_Sz.cy = 0;
    m_Pt.x = 0;
    m_Pt.y = 0;
    m_SrcPt.x = 0;
    m_SrcPt.y = 0;
}

CXTProgress::~CXTProgress()
{
}

bool CXTProgress::Initial(LPCTSTR strIniFile)
{
    return true;
}

bool CXTProgress::Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *pDBuffDC)
{
    if (pDBuffDC == NULL) return false;

    m_hDC	  = pDBuffDC->GetHDC(WNDDC, 0);
    m_hCompDC = pDBuffDC->GetHDC(COMPDC, 0);
    m_hBmpDC  = pDBuffDC->GetHDC(IMAGEDC, 0);

    m_hFont = ::CreateFont(12,		// nHeight 高度
        8,							// nWidth 宽度
        0,							// nEscapement 文本行逆时针旋转角度 
        0,							// nOrientation 字体角度
        FW_NORMAL,					// nWeight 字体粗细程度 
        0,							// bItalic 斜体
        0,							// bUnderline 下划线
        0,							// cStrikeOut 删除线
        DEFAULT_CHARSET,			// nCharSet 
        OUT_DEFAULT_PRECIS,			// nOutPrecision 
        CLIP_DEFAULT_PRECIS,		// nClipPrecision 
        DEFAULT_QUALITY,			// nQuality 
        DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily 
        _T("宋体"));

    ::SelectObject(m_hCompDC, m_hFont);
    ::SetTextColor(m_hCompDC, m_clFont);

    m_Sz.cx   = cx;
    m_Sz.cy   = cy;
    m_Pt.x    = x;
    m_Pt.y    = y;
    m_SrcPt.x = sx;
    m_SrcPt.y = sy;

    DrawImage(0, _T(""));
    return true;
}

bool CXTProgress::SetParam(UINT nMax)
{
    m_nMax = nMax;

    DrawImage(0);
    return true;
}

void CXTProgress::DrawImage(UINT nProgress, LPCTSTR strMessage/* = NULL*/)
{
    RECT rcText = {m_Pt.x, m_Pt.y, m_Pt.x + m_Sz.cx, m_Pt.y + m_Sz.cy};

    // draw background header
    ::BitBlt(m_hCompDC, m_Pt.x, m_Pt.y, 3, m_Sz.cy, m_hBmpDC, m_SrcPt.x, m_SrcPt.y, SRCCOPY);
    // draw background ender
    ::BitBlt(m_hCompDC, m_Pt.x + m_Sz.cx - 3, m_Pt.y, 3, m_Sz.cy, m_hBmpDC, m_SrcPt.x + 7, m_SrcPt.y, SRCCOPY);
    // draw background middle
    ::StretchBlt(m_hCompDC, m_Pt.x + 3, m_Pt.y, m_Sz.cx - 6, m_Sz.cy, m_hBmpDC, m_SrcPt.x + 2, m_SrcPt.y, 1, m_Sz.cy, SRCCOPY);

    // draw progress
    if (nProgress > 0 && nProgress <= m_nMax)
    {
        float fProgress = (float)nProgress / m_nMax;
        int nProgressLen = (int)(fProgress * (m_Sz.cx - 6));
        ::StretchBlt(m_hCompDC, m_Pt.x + 3, m_Pt.y, nProgressLen, m_Sz.cy, m_hBmpDC, m_SrcPt.x + 3, m_SrcPt.y, 1, m_Sz.cy, SRCCOPY);

        CString strProgress(_T("0.00%%"));
        strProgress.Format(_T("%.2f%%"), fProgress * 100);
        ::DrawText(m_hCompDC, strProgress, strProgress.GetLength(), &rcText, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_WORD_ELLIPSIS);
    }
    else if (NULL != strMessage)
    {
        ::DrawText(m_hCompDC, strMessage, (int)_tcslen(strMessage), &rcText, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_WORD_ELLIPSIS);
    }

    // draw to dlg from Compatible dc
    ::BitBlt(m_hDC, m_Pt.x, m_Pt.y, m_Sz.cx, m_Sz.cy, m_hCompDC, m_Pt.x, m_Pt.y, SRCCOPY);
}

