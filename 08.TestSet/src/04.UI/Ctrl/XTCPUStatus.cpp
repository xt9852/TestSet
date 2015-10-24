// CPUStatus.cpp : 实现文件
//

#include "stdafx.h"
#include "XTCPUStatus.h"
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCPUStatus

IMPLEMENT_DYNAMIC(CXTCPUStatus, CStatic)
CXTCPUStatus::CXTCPUStatus()
	:m_hDC(NULL),
	m_hCompDC(NULL),
	m_hPen(NULL),
	m_hPenLine(NULL),
	m_hPenBlack(NULL),
	m_hBrush(NULL),
	m_pPoint(NULL),
	m_nCPU(0),
	m_nCountX(0),
	m_nCountY(0),
	m_nLastX(1),
	m_nInter(0.0f)
{
	m_hPen = ::CreatePen(PS_SOLID, 1, RGB(0,128,64));
	m_hPenLine = ::CreatePen(PS_SOLID, 1, RGB(0,255,0));
	m_hPenBlack = ::CreatePen(PS_SOLID, 1, RGB(0,0,0));
	m_hBrush = ::CreateSolidBrush(RGB(0,0,0));
}

CXTCPUStatus::~CXTCPUStatus()
{
	if (NULL != m_pPoint)
		delete[] m_pPoint;

	::DeleteObject(m_hPen);
	::DeleteObject(m_hBrush);
}


BEGIN_MESSAGE_MAP(CXTCPUStatus, CStatic)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CXTCPUStatus::Init(int nInterval)
{
	GetClientRect(&m_rItem);

	m_nCountX = (UINT)ceil((m_rItem.right - m_rItem.left) / 3.0f);
	m_nCountY = (UINT)ceil((m_rItem.bottom - m_rItem.top) / 3.0f);
	m_nCompDC.cx = m_nCountX * 3 + 1;
	m_nCompDC.cy = m_nCountY * 3;
	m_nInter = m_rItem.bottom / 100.0f;

	m_pPoint = new POINT[m_nCountX];

	//----------------------------------------------------
	m_hDC = m_xtDC.Init(NULL, this->GetSafeHwnd());
	m_hCompDC = m_xtDC.AddNullDC(0, m_nCompDC.cx, m_nCompDC.cy);
	
	::FillRect(m_hCompDC, CRect(0,0,m_nCompDC.cx, m_nCompDC.cy), m_hBrush);
	::SelectObject(m_hCompDC, m_hPen);
	::SelectObject(m_hCompDC, m_hBrush);
	::SetTextColor(m_hDC, RGB(0,255,0));
	::SetBkMode(m_hDC, TRANSPARENT);

	POINT ptTemp = {0};

	for (UINT i = 1; i <= m_nCountY; i++)
	{
		m_pPoint[i - 1].y = m_rItem.bottom - 1;
		::MoveToEx(m_hCompDC, 0, i * CPU_GRID_CY, &ptTemp);
		::LineTo(m_hCompDC, m_nCompDC.cx, i * CPU_GRID_CY);
	}
	
	for (UINT i = 1; i <= m_nCountX; i++)
	{
		m_pPoint[i - 1].x = i * 3;
		::MoveToEx(m_hCompDC, i * CPU_GRID_CX, 0, &ptTemp);
		::LineTo(m_hCompDC, i * CPU_GRID_CX, m_rItem.bottom);
	}

	//----------------------------------------------------
	m_cpuUsage.SetRefreshInterval(1000);
	SetTimer(0, 1000, NULL);
}

void CXTCPUStatus::OnTimer(UINT nIDEvent)
{
	POINT ptTemp = {0};
	m_nCPU = m_cpuUsage.GetCpuUsage();

	for (UINT i = 0; i < m_nCountX; i++)
	{
		if (i == m_nCountX - 1)
			m_pPoint[i].y = m_rItem.bottom - (LONG)ceil(m_nCPU * m_nInter);
		else
			m_pPoint[i].y = m_pPoint[i + 1].y;
	}

	// move
	::BitBlt(m_hCompDC, 0, 0, m_nCompDC.cx, m_nCompDC.cy, m_hCompDC, 3, 0, SRCCOPY);
	::SelectObject(m_hCompDC, m_hPenBlack);
	::Rectangle(m_hCompDC, m_nCompDC.cx - 3, 0, m_nCompDC.cx, m_nCompDC.cy);
	::SelectObject(m_hCompDC, m_hPen);

	// hor line
	for (UINT i = 1; i <= m_nCountY; i++)
	{
		::MoveToEx(m_hCompDC, m_nCompDC.cx - 3, i * CPU_GRID_CY, &ptTemp);
		::LineTo(m_hCompDC, m_nCompDC.cx, i * CPU_GRID_CY);
	}

	// ver line
	m_nLastX += 3;
	if (m_nLastX > CPU_GRID_CX)
	{
		m_nLastX %= CPU_GRID_CX;

		::MoveToEx(m_hCompDC, m_nCompDC.cx - m_nLastX, 0, &ptTemp);
		::LineTo(m_hCompDC, m_nCompDC.cx - m_nLastX, m_nCompDC.cy);
	}

	// cir line
	::SelectObject(m_hCompDC, m_hPenLine);
	::MoveToEx(m_hCompDC, m_pPoint[m_nCountX-2].x, m_pPoint[m_nCountX-2].y, &ptTemp);
	::LineTo(m_hCompDC, m_pPoint[m_nCountX-1].x, m_pPoint[m_nCountX-1].y);

	// copy to dlg
	::BitBlt(m_hDC, 0, 0, m_rItem.right, m_rItem.bottom, m_hCompDC, 0, 0, SRCCOPY);
	CString strText;
	strText.Format(_T("CPU:使用率%d%%"), m_nCPU);
	::TextOut(m_hDC, 0, 0, strText, strText.GetLength());

	CStatic::OnTimer(nIDEvent);
}

BOOL CXTCPUStatus::OnEraseBkgnd(CDC* pDC)
{
	//return CStatic::OnEraseBkgnd(pDC);
	return TRUE;
}

void CXTCPUStatus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	::BitBlt(m_hDC, 0, 0, m_rItem.right, m_rItem.bottom, m_hCompDC, 0, 0, SRCCOPY);
	CString strText;
	strText.Format(_T("CPU:使用率%d%%"), m_nCPU);
	::TextOut(m_hDC, 0, 0, strText, strText.GetLength());
}
