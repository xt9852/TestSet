// XTProgress.cpp : 实现文件
//

#include "stdafx.h"
#include "XTBackForth.h"
#include "XTDC.h"
#include "process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


enum{ WM_EXIT = 0x100, WM_SUCCESS = 0x200 };
UINT WM_PROGRESS_OK = RegisterWindowMessage(_T("WM_PROGRESS_OK"));


CXTBackForth::CXTBackForth()
	:m_hDC(NULL),
	m_hCompDC(NULL),
	m_hBmpDC(NULL),
	m_hWnd(NULL),
	m_nThreadId(0)
{	
}

CXTBackForth::~CXTBackForth()
{
}

// all param in
// nAllItemCount 整个进度条上小块的数量
// nItemCount    行走的小块数量
// nItemcx       小块宽
// nItemcy       小块高
// nInterval     块间隔
bool CXTBackForth::Initial(int x, int y, int nAllItemCount, int nItemCount, int nItemcx, int nItemcy, int nInterval,
						   int sx, int sy, CXTDC *pDBuffDC)
{
	if (pDBuffDC == NULL) return false;

	m_hDC  = pDBuffDC->GetHDC(WNDDC, 0);
	m_hCompDC = pDBuffDC->GetHDC(COMPDC, 0);
	m_hBmpDC  = pDBuffDC->GetHDC(IMAGEDC, 0);

	m_ItemSz.cx     = nItemcx;
	m_ItemSz.cy     = nItemcy;
	m_Pt.x          = x;
	m_Pt.y          = y;
	m_SrcLeftPt.x   = sx;
	m_SrcLeftPt.y   = sy;
	m_SrcMedPt.x    = m_SrcLeftPt.x + m_ItemSz.cx + nInterval;
	m_SrcMedPt.y    = sy;
	m_SrcRightPt.x  = m_SrcMedPt.x + m_ItemSz.cx + nInterval;
	m_SrcRightPt.y  = sy;

	m_BckLeftPt.x   = m_SrcRightPt.x + m_ItemSz.cx + nInterval;
	m_BckLeftPt.y   = sy;
	m_BckMedPt.x    = m_BckLeftPt.x + m_ItemSz.cx + nInterval;
	m_BckMedPt.y    = sy;
	m_BckRightPt.x  = m_BckMedPt.x + m_ItemSz.cx + nInterval;
	m_BckRightPt.y  = sy;
	
	m_nAllItemCount = nAllItemCount;
	m_nItemCount    = nItemCount;
	m_nInterval     = nInterval;

	m_nCurLeftPos   = 0;
	m_bToRight      = true;

	for (int i = 0; i < m_nAllItemCount; i++)
		ResetItem(i);

	return true;
}

bool CXTBackForth::Start(void)
{
	if (0 == m_nThreadId)
	{
		m_nCurLeftPos = 0;
		m_bToRight = true;
		m_bLeftOk  = false;
		m_bRightOk = false;

		for (int i = 0; i < m_nAllItemCount; i++)
			ResetItem(i);

		SetItem(0, LEFT);
		SetItem(m_nItemCount - 1, RIGHT);
		for (int i = 1; i < m_nItemCount - 1; i++)
			SetItem(i, MED);

		if (0 != m_nThreadId) return false;

		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, DrawProgressThread, this, 0, &m_nThreadId);	
		if (NULL == hThread)
		{
			TRACE(" CXTProgressBackForth::Start _beginthreadex Error\n");
			return false;
		}
	}

	return true;	
}
void CXTBackForth::Stop(void)
{
	PostThreadMessage(m_nThreadId, WM_EXIT, NULL, NULL);
}
void CXTBackForth::Success(void)
{
	PostThreadMessage(m_nThreadId, WM_SUCCESS, NULL, NULL);	
}

void CXTBackForth::SetItem(int nItemId, int nItemType)
{
	switch (nItemType)
	{
	case LEFT:
		{
			::BitBlt(m_hCompDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_SrcLeftPt.x, m_SrcLeftPt.y, SRCCOPY);
			::BitBlt(m_hDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_SrcLeftPt.x, m_SrcLeftPt.y, SRCCOPY);
			break;
		}
	case RIGHT:
		{
			::BitBlt(m_hCompDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_SrcRightPt.x, m_SrcRightPt.y, SRCCOPY);
			::BitBlt(m_hDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_SrcRightPt.x, m_SrcRightPt.y, SRCCOPY);
			break;
		}
	default:
		{
			::BitBlt(m_hCompDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_SrcMedPt.x, m_SrcMedPt.y, SRCCOPY);
			::BitBlt(m_hDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_SrcMedPt.x, m_SrcMedPt.y, SRCCOPY);
			break;
		}
	}
}

void CXTBackForth::ResetItem(int nItemId)
{
	if (0 == nItemId)
	{
		::BitBlt(m_hCompDC, m_Pt.x, m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_BckLeftPt.x, m_BckLeftPt.y, SRCCOPY);
		::BitBlt(m_hDC, m_Pt.x, m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_BckLeftPt.x, m_BckLeftPt.y, SRCCOPY);
	}
	else if ((m_nAllItemCount - 1) == nItemId)
	{
		::BitBlt(m_hCompDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_BckRightPt.x, m_BckRightPt.y, SRCCOPY);
		::BitBlt(m_hDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_BckRightPt.x, m_BckRightPt.y, SRCCOPY);
	}
	else
	{
		::BitBlt(m_hCompDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_BckMedPt.x, m_BckMedPt.y, SRCCOPY);
		::BitBlt(m_hDC, m_Pt.x + nItemId * (m_ItemSz.cx + m_nInterval), m_Pt.y, m_ItemSz.cx, m_ItemSz.cy, m_hBmpDC, m_BckMedPt.x, m_BckMedPt.y, SRCCOPY);
	}
}


void CXTBackForth::DrawDefaultImage(void)
{	
	if (m_bToRight)
	{
		int nLastPos = m_nCurLeftPos - 1;
		if (nLastPos >= 0)
			ResetItem(nLastPos);
		
		SetItem(m_nCurLeftPos, LEFT);
		SetItem(m_nCurLeftPos + m_nItemCount - 2, MED);
		SetItem(m_nCurLeftPos + m_nItemCount - 1, RIGHT);

		if ((++m_nCurLeftPos) > (m_nAllItemCount - m_nItemCount))
		{
			m_nCurLeftPos--;
			m_bToRight = false;
		}
	}
	else
	{
		int nLastPos = m_nCurLeftPos + m_nItemCount;
		if (nLastPos < m_nAllItemCount)
			ResetItem(nLastPos);

		SetItem(m_nCurLeftPos, LEFT);
		SetItem(m_nCurLeftPos + 1, MED);
		SetItem(m_nCurLeftPos + m_nItemCount - 1, RIGHT);

		if ((--m_nCurLeftPos) < 0)
		{
			m_nCurLeftPos = 0;
			m_bToRight = true;
		}
	}

	m_nCurRightPos = m_nCurLeftPos + m_nItemCount - 1;
}

void CXTBackForth::DrawSuccessImage(void)
{
	while (true) 
	{
		SetItem(m_nCurLeftPos, LEFT);
		SetItem(m_nCurLeftPos + 1, MED);

		SetItem(m_nCurRightPos, RIGHT);
		SetItem(m_nCurRightPos - 1, MED);


		if ((--m_nCurLeftPos) < 0)
		{
			m_nCurLeftPos = 0;
			m_bLeftOk = true;
		}

		if ((++m_nCurRightPos) >= m_nAllItemCount)
		{
			m_nCurRightPos = m_nAllItemCount - 1;
			m_bRightOk = true;
		}

		if (m_bLeftOk && m_bRightOk) break;

		::Sleep(100);
	}

	::SendMessage(m_hWnd, WM_PROGRESS_OK, NULL, NULL);
}

// 绘进度条线程
unsigned CXTBackForth::DrawProgressThread(LPVOID pthis)
{
	CXTBackForth *pThis = (CXTBackForth*)pthis;

	MSG WndMsg = {0};

	while (true)
	{
		::PeekMessage(&WndMsg, NULL, 0, 0, PM_REMOVE);
		switch (WndMsg.message)
		{		
		case WM_SUCCESS: pThis->DrawSuccessImage();
		case WM_EXIT:
			pThis->m_nThreadId = 0;
			return 0;
		default:
			{
				pThis->DrawDefaultImage();
				break;
			}
		}
		::Sleep(100);
	}
	return 0;
}
