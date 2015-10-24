
#include "StdAfx.h"
#include "XTBarCtrl.h"
#include "XTDC.h"

/* 例如:
if (!m_tabbar.Init(this, WS_CHILD|WS_VISIBLE|CBRS_NOALIGN, 123456, 56, NULL, IDB_TOOLBAR_BUTTON)) return -1;
m_tabbar.EnableDocking(CBRS_ALIGN_ANY);
m_tabbar.SetBarStyle(m_tabbar.GetBarStyle() | CBRS_TOOLTIPS);
DockControlBar(&m_tabbar, AFX_IDW_DOCKBAR_TOP);


m_tabbar.AddButton(123, SY_BUTTON, 20, 3, 57, 50, 0,  55, _T("测试Tip字符串1"));
m_tabbar.AddButton(124, SY_BUTTON, 10, 3, 57, 50, 0, 105, _T("测试Tip字符串2"));
m_tabbar.AddButton(125, SY_BUTTON, 20, 3, 57, 50, 0, 155, _T("测试Tip字符串3"));

m_tabbar.CheckButtonPos();
*/


IMPLEMENT_DYNAMIC(CXTBarCtrl, CControlBar)
BEGIN_MESSAGE_MAP(CXTBarCtrl, CControlBar)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()


CXTBarCtrl::CXTBarCtrl()
	:m_pLastHoverItem(NULL),
	m_pLastClickItem(NULL),
	m_wSreenWidth(0),
	m_wWndHeight(0),
	m_bNewedDC(TRUE),
	m_pxtDC(NULL),
	m_hWndDC(NULL),
	m_hCompDC(NULL),
	m_hBmpDC(NULL)	
{
}

CXTBarCtrl::~CXTBarCtrl()
{
	int nCount = (int)m_ItemList.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		delete (BARITEM*)m_ItemList[i];
	}

	if (m_bNewedDC)
		delete m_pxtDC;
}


BOOL CXTBarCtrl::Init(CWnd* pParentWnd,
						   DWORD dwStyle,
						   UINT nID,
						   WORD wWndHeight, 
						   CXTDC *pxtDC, 
						   LPCTSTR strBmpFile)
{
	CRect rc(0, 0, 0, 0);
	rc.bottom = rc.top + wWndHeight;
	rc.right = rc.left + ::GetSystemMetrics(SM_CXSCREEN);

	dwStyle |= WS_CHILD;
	if (!CWnd::Create( NULL, NULL, dwStyle, rc, pParentWnd, nID, NULL ))
		return FALSE;

	//------------------------------------------------------------------------
	if (NULL == pxtDC)
	{
		m_pxtDC = new CXTDC();

		ASSERT(NULL != m_pxtDC);
		m_bNewedDC = TRUE;

		m_pxtDC->Init(NULL, this->GetSafeHwnd());
		m_pxtDC->SetBmpBKG(strBmpFile, 1);	
	}
	else
	{
		m_pxtDC = pxtDC;
	}

	m_hWndDC = m_pxtDC->GetHDC(0);
	m_hCompDC= m_pxtDC->GetHDC(1);
	m_hBmpDC = m_pxtDC->GetHDC(2);
	m_wWndHeight = wWndHeight;
	m_wSreenWidth = ::GetSystemMetrics(SM_CXSCREEN);

	return TRUE;
}

BOOL CXTBarCtrl::Init(CWnd* pParentWnd,
						   DWORD dwStyle,
						   UINT nID,
						   WORD wWndHeight, 
						   CXTDC *pxtDC, 
						   UINT nBmpId)
{
	CRect rc(0, 0, 0, 0);
	rc.bottom = rc.top + wWndHeight;
	rc.right = rc.left + ::GetSystemMetrics(SM_CXSCREEN);

	dwStyle |= WS_CHILD;
	if (!CWnd::Create( NULL, NULL, dwStyle, rc, pParentWnd, nID, NULL ))
		return FALSE;

	//------------------------------------------------------------------------
	if (NULL == pxtDC)
	{
		m_pxtDC = new CXTDC();

		ASSERT(NULL != m_pxtDC);
		m_bNewedDC = TRUE;

		m_pxtDC->Init(NULL, this->GetSafeHwnd());
		m_pxtDC->SetBmpBKG(nBmpId, 1);
	}
	else
	{
		m_pxtDC = pxtDC;
	}

	m_hCompDC= m_pxtDC->GetHDC(1);
	m_hBmpDC = m_pxtDC->GetHDC(2);
	m_wWndHeight = wWndHeight;
	m_wSreenWidth = ::GetSystemMetrics(SM_CXSCREEN);

	return TRUE;
}

BOOL CXTBarCtrl::AddButton(UINT nId, 
								WORD wType, 
								WORD wOffsetX, 
								WORD wY,
								WORD wWidth, 
								WORD wHeight, 
								WORD wSrcX, 
								WORD wSrcY, 
								LPCTSTR strTip, 
								CMenu *pMenu /*= NULL*/)
{
	BARITEM *pItem = new BARITEM;

	ASSERT(NULL != pItem);

	pItem->nId = nId;
	pItem->wType = wType;
	pItem->wOffsetX = wOffsetX;
	pItem->wY = wY;
	pItem->wWidth = wWidth;
	pItem->wHeight = wHeight;
	pItem->wSrcX = wSrcX;
	pItem->wSrcY = wSrcY;

	if (BT_DROPDOWN == wType)
		pItem->pMenu = pMenu;

	if (NULL != strTip)
		_tcscpy(pItem->tszTip, strTip);

	m_ItemList.Add(pItem);

	return TRUE;
}

void CXTBarCtrl::RedrawButton(void)
{
	WORD wCurX = 0;
	CRect rc;
	GetWindowRect(&rc);

	// 画背景
	::StretchBlt(m_hCompDC, 0, 0, m_wSreenWidth, m_wWndHeight, m_hBmpDC, 0, 0, 1, m_wWndHeight, SRCCOPY);


	// 重新计计算位置，得画按钮
	int nCount = (int)m_ItemList.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		BARITEM* pItem = (BARITEM*)m_ItemList[i];

		if (NULL != pItem && pItem->bShow)
		{
			wCurX += pItem->wOffsetX;
			pItem->wX = wCurX;
			wCurX += pItem->wWidth;
						
			//---------------------------------------------
			WORD wSrcX = pItem->wSrcX;

			if (!pItem->bEnable)
			{
				wSrcX += 3 * pItem->wWidth;
			}				
			else if (pItem->bCheck)
			{
				wSrcX += 2 * pItem->wWidth;
			}

			::BitBlt(m_hCompDC, pItem->wX, pItem->wY, 
				pItem->wWidth, pItem->wHeight, m_hBmpDC, 
				wSrcX, pItem->wSrcY, SRCCOPY);

			::BitBlt(m_hWndDC, pItem->wX, pItem->wY, 
				pItem->wWidth, pItem->wHeight, m_hBmpDC, 
				wSrcX, pItem->wSrcY, SRCCOPY);
		}
	}
}

void CXTBarCtrl::SetShow(WORD wButtonId, BOOL bShow)
{
	BARITEM* pItem = (BARITEM*)m_ItemList[wButtonId];

	if (NULL != pItem)
	{
		pItem->bShow = bShow;

		RedrawButton();
	}
}
void CXTBarCtrl::SetEnable(WORD wButtonId, BOOL bEnable)
{
	BARITEM* pItem = (BARITEM*)m_ItemList[wButtonId];

	if (NULL != pItem)
	{
		pItem->bEnable = bEnable;

		this->DrawButton(m_hWndDC, pItem, bEnable ? DR_ENABLE : DR_UNABLE);
		this->DrawButton(m_hCompDC, pItem, bEnable ? DR_ENABLE : DR_UNABLE);
	}
}
void CXTBarCtrl::SetCheck(WORD wButtonId, BOOL bCheck)
{
	BARITEM* pItem = (BARITEM*)m_ItemList[wButtonId];

	if (NULL != pItem && BT_CHECK == pItem->wType)
	{
		pItem->bCheck = bCheck;

		this->DrawButton(m_hWndDC, pItem, bCheck ? DR_CHECK : DR_UNCHECK);
		this->DrawButton(m_hCompDC, pItem, bCheck ? DR_CHECK : DR_UNCHECK);
	}
}

void CXTBarCtrl::DrawButton(HDC hDC, BARITEM *pItem, WORD wType)
{
	WORD wSrcX = pItem->wSrcX;

	switch (wType)
	{
	case DR_HOVER:
		{
			wSrcX += pItem->wWidth;
			break;
		}
	case DR_CLICK:
	case DR_CHECK:
		{
			wSrcX += pItem->wWidth * 2;
			break;
		}
	case DR_UNABLE:
		{
			wSrcX += pItem->wWidth * 3;
			break;
		}

	case DR_OK:
	case DR_ENABLE:
	case DR_UNCHECK:
	default:
		break;
	}

	::BitBlt(hDC, pItem->wX, pItem->wY, pItem->wWidth, pItem->wHeight,
		m_hBmpDC, wSrcX, pItem->wSrcY, SRCCOPY);
}

int CXTBarCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1) return -1;

	m_dwStyle |= CBRS_BORDER_3D;
	SetTimer( 1, 250, NULL );
	return 0;
}

// 虚函数，设置按钮的Enable
void CXTBarCtrl::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
}

// 虚函数,控制大小
CSize CXTBarCtrl::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CRect rcBackground;
	CSize size(32, m_wWndHeight);

	if (CWnd* pParent = GetOwner())
	{
		CRect rc;
		pParent->GetWindowRect(&rc);

		if (rc.Width() > 32)
			size.cx = rc.Width() + 2;
	}
	
	return size;
}

// 查找鼠标位于哪个按钮上
BARITEM* CXTBarCtrl::HitTest(const CPoint& point) const
{
	LONG x = point.x;
	LONG y = point.y;

	int nCount = (int)m_ItemList.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		BARITEM* pItem = (BARITEM*)m_ItemList[i];

		if (NULL != pItem && pItem->bShow)
		{
			if (x > pItem->wX && x < pItem->wX + pItem->wWidth
				&& y > pItem->wY && y < pItem->wY + pItem->wHeight)

				return pItem;
		}
	}
	
	return NULL;
}

// 虚函数，设置按钮的Tip
int CXTBarCtrl::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	BARITEM* pItem = HitTest(point);
	
	if (NULL == pItem) return -1;
	if (NULL == pTI) return 1;
	
	pTI->uFlags		= 0;
	pTI->hwnd		= GetSafeHwnd();
	pTI->uId		= pItem->nId;
	pTI->rect.left	= pItem->wX;
	pTI->rect.top   = pItem->wY;
	pTI->rect.right = pItem->wX + pItem->wWidth;
	pTI->rect.bottom= pItem->wY + pItem->wHeight; 

	pTI->lpszText = _tcsdup(pItem->tszTip);

	return (int)(pTI->uId);
}

// 画按钮
void CXTBarCtrl::DoPaint(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	
	if (NULL == m_hWndDC) m_hWndDC = pDC->GetSafeHdc();

	::BitBlt(m_hWndDC, 0, 0, m_wSreenWidth, m_wWndHeight, m_hCompDC, 0, 0, SRCCOPY);
}

// 设置鼠标指针
BOOL CXTBarCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest == HTCLIENT)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (BARITEM* pItem = HitTest(point))
		{
			if (pItem->bEnable)
			{
				//SetCursor(::LoadCursor(AfxGetResourceHandle(), IDC_ARROW));
				return TRUE;
			}
		}
	}
	
	return CControlBar::OnSetCursor( pWnd, nHitTest, message );
}

void CXTBarCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT stTRACKMOUSEEVENT = {0};
	stTRACKMOUSEEVENT.cbSize    = sizeof(TRACKMOUSEEVENT);
	stTRACKMOUSEEVENT.hwndTrack = m_hWnd;
	stTRACKMOUSEEVENT.dwFlags   = TME_LEAVE;
	_TrackMouseEvent(&stTRACKMOUSEEVENT);

	//----------------------------------------------------
	
	BARITEM* pItem = HitTest(point);

	if (NULL != pItem && NULL == m_pLastHoverItem)		// 鼠标第一次在一个按钮
	{
		if (pItem->bEnable)
		{
			if (BT_CHECK == pItem->wType)				// Check按钮
				this->DrawButton(m_hWndDC, pItem, pItem->bCheck ? DR_UNCHECK : DR_CHECK);
			else
				this->DrawButton(m_hWndDC, pItem, DR_HOVER);
			
			m_pLastHoverItem = pItem;
		}
	}
	else if (NULL == pItem && NULL != m_pLastHoverItem)	// 鼠标离开了上一个按钮
	{
		if (m_pLastHoverItem->bEnable)
		{
			if (BT_CHECK == m_pLastHoverItem->wType)	// Check按钮
				this->DrawButton(m_hWndDC, m_pLastHoverItem, m_pLastHoverItem->bCheck ? DR_CHECK : DR_UNCHECK);
			else
				this->DrawButton(m_hWndDC, m_pLastHoverItem, DR_OK);

			m_pLastHoverItem = NULL;
		}
	}
	else if (NULL != pItem && pItem != m_pLastHoverItem)// 鼠标由一个按钮直接移动到另一个按钮上
	{
		if (m_pLastHoverItem->bEnable)
		{
			if (BT_CHECK == m_pLastHoverItem->wType)	// Check按钮
				this->DrawButton(m_hWndDC, m_pLastHoverItem, m_pLastHoverItem->bCheck ? DR_CHECK : DR_UNCHECK);
			else
				this->DrawButton(m_hWndDC, m_pLastHoverItem, DR_OK);
		}

		if (pItem->bEnable)
		{
			if (BT_CHECK == pItem->wType)				// Check按钮
				this->DrawButton(m_hWndDC, pItem, pItem->bCheck ? DR_UNCHECK : DR_CHECK);
			else
				this->DrawButton(m_hWndDC, pItem, DR_HOVER);
		}
		m_pLastHoverItem = pItem;
	}
}

LRESULT CXTBarCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (NULL != m_pLastHoverItem)
	{
		if (m_pLastHoverItem->bEnable)
		{
			if (BT_CHECK == m_pLastHoverItem->wType)	// Check按钮
				this->DrawButton(m_hWndDC, m_pLastHoverItem, m_pLastHoverItem->bCheck ? DR_CHECK : DR_UNCHECK);
			else
				this->DrawButton(m_hWndDC, m_pLastHoverItem, DR_OK);
		}

		m_pLastHoverItem = NULL;
	}
	return   0;   
}

void CXTBarCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	BARITEM* pItem = HitTest(point);
	if (NULL != pItem)
	{
		this->SendMessage(WM_COMMAND, pItem->nId);

		if (pItem->bEnable)
		{
			if (BT_CHECK == pItem->wType)				// Check按钮
			{
				pItem->bCheck = !pItem->bCheck;

				this->DrawButton(m_hWndDC, pItem, pItem->bCheck ? DR_CHECK : DR_UNCHECK);
				this->DrawButton(m_hCompDC, pItem, pItem->bCheck ? DR_CHECK : DR_UNCHECK);
			}
			else
			{
				this->DrawButton(m_hWndDC, pItem, DR_CLICK);
				m_pLastClickItem = pItem;
			}
		}
	}
	else
	{
		CControlBar::OnLButtonDown(nFlags, point);
	}
}

void CXTBarCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (NULL != m_pLastClickItem && m_pLastClickItem->bEnable)
	{
		if (BT_CHECK != m_pLastClickItem->wType)				// Check按钮
		{
			this->DrawButton(m_hWndDC, m_pLastClickItem, DR_OK);
			m_pLastClickItem = NULL;
		}
	}

	CControlBar::OnLButtonUp(nFlags, point);
}

void CXTBarCtrl::OnSize(UINT nType, int cx, int cy)
{
	CControlBar::OnSize(nType, cx, cy);
}

