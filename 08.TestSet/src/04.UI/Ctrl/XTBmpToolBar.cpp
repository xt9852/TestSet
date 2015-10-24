
#include "StdAfx.h"
#include "XTBmpToolBar.h"
#include "XTDC.h"


IMPLEMENT_DYNAMIC(CXTBmpToolBar, CToolBar)
BEGIN_MESSAGE_MAP(CXTBmpToolBar, CToolBar)	
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


CXTBmpToolBar::CXTBmpToolBar()
	:m_pLastHoverItem(NULL),
	m_pLastClickItem(NULL),
	m_wSreenWidth(0),
	m_wWndHeight(50),
	m_nDropDownButtonX(0),
	m_nDropDownButtonY(0),
	m_nDropDownButtonCX(0),
	m_nDropDownButtonCY(0),
	m_nBackground(0),
	m_nBackgroundX(0),
	m_nBackgroundY(0),
	m_nBackgroundCX(0),
	m_nBackgroundCY(0),
	m_bNewedDC(TRUE),
	m_pxtDC(NULL),
	m_hWndDC(NULL),
	m_hCompDC(NULL),
	m_hBmpDC(NULL)
{
}

CXTBmpToolBar::~CXTBmpToolBar()
{
	int nCount = (int)m_ItemList.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		delete (BARITEM*)m_ItemList[i];
	}

	if (m_bNewedDC)
		delete m_pxtDC;
}

BOOL CXTBmpToolBar::Init(CWnd* pParentWnd, CXTDC *pxtDC, LPCTSTR strIniFile)
{
	CString strBmpFile;
	CString strButton;

	UINT nHeight   = ::GetPrivateProfileInt(_T("MainToolBar"), _T("Height"),   55, strIniFile);
	UINT nButtonCX = ::GetPrivateProfileInt(_T("MainToolBar"), _T("ButtonCX"), 51, strIniFile);
	UINT nButtonCY = ::GetPrivateProfileInt(_T("MainToolBar"), _T("ButtonCY"), 51, strIniFile);
	::GetPrivateProfileString(_T("MainToolBar"), _T("ButtonFile"), _T(""), 
		(LPTSTR)(LPCTSTR)strBmpFile.GetBufferSetLength(200), 200, strIniFile);
	::GetPrivateProfileString(_T("MainToolBar"), _T("ButtonCount"), _T(""), 
		(LPTSTR)(LPCTSTR)strButton.GetBufferSetLength(200), 200, strIniFile);

	m_nDropDownButtonX  = ::GetPrivateProfileInt(_T("MainToolBar"), _T("DropdownButtonX"), 11, strIniFile);
	m_nDropDownButtonY  = ::GetPrivateProfileInt(_T("MainToolBar"), _T("DropdownButtonY"),  0, strIniFile);
	m_nDropDownButtonCX = ::GetPrivateProfileInt(_T("MainToolBar"), _T("DropdownButtonCX"), 11, strIniFile);
	m_nDropDownButtonCY = ::GetPrivateProfileInt(_T("MainToolBar"), _T("DropdownButtonCY"), 49, strIniFile);

	m_nBackground = ::GetPrivateProfileInt(_T("MainToolBar"), _T("BackGround"), 0, strIniFile);

	if (1 == m_nBackground)
	{
		m_nBackgroundX  = ::GetPrivateProfileInt(_T("MainToolBar"), _T("BackgroundX"), 55, strIniFile);
		m_nBackgroundY  = ::GetPrivateProfileInt(_T("MainToolBar"), _T("BackgroundY"),  0, strIniFile);
		m_nBackgroundCX = ::GetPrivateProfileInt(_T("MainToolBar"), _T("BackgroundCX"), 149, strIniFile);
		m_nBackgroundCY = ::GetPrivateProfileInt(_T("MainToolBar"), _T("BackgroundCY"), 54, strIniFile);
	}

	//------------------------------------------------------------------------
	CRect rc(0, 0, 0, 0);
	rc.bottom = rc.top + nHeight;
	rc.right = rc.left + ::GetSystemMetrics(SM_CXSCREEN);

	SIZE szButton = {nButtonCX + 8, nButtonCY + 8};
	SIZE szImage = {nButtonCX, nButtonCY};
	this->SetSizes(szButton, szImage);
	this->SetHeight(nHeight);

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
	m_wWndHeight = nHeight;
	m_wSreenWidth = ::GetSystemMetrics(SM_CXSCREEN);

	//------------------------------------------------------------------------

	CString strButtonId;
	CString strButtonInfo;
	CString strTemp;
	int nCurPos1 = 0;
	int nCurPos2 = 0;
	int nStype = 0;	
	int nOffsetX = 0;
	int nOffsetY = 0;
	int nSrcX = 0;
	int nSrcY = 0;

	while (true)
	{
		strButtonId = strButton.Tokenize(_T(","), nCurPos1);
		
		if (nCurPos1 > strButton.GetLength())
			break;

		if (strButtonId.GetLength() > 0 )
		{
			::GetPrivateProfileString(_T("MainToolBar"), strButtonId, _T(""), (LPTSTR)(LPCTSTR)strButtonInfo.GetBufferSetLength(200), 200, strIniFile);

			if (strButtonInfo.GetLength() > 0)
			{
				nCurPos2 = 0;

				for (int i = 0 ; i < 6; i++)
				{
					strTemp = strButtonInfo.Tokenize(_T(","), nCurPos2);

					switch (i)
					{
					case 0: nStype = _ttoi(strTemp); break;
					case 1: nOffsetX = _ttoi(strTemp); break;
					case 2: nOffsetY = _ttoi(strTemp); break;
					case 3: nSrcX = _ttoi(strTemp); break;
					case 4: nSrcY = _ttoi(strTemp); break;
					case 5:						
						this->AddButton(_ttoi(strButtonId), nStype, nOffsetX, nOffsetY, nButtonCX, nButtonCY, nSrcX, nSrcY, strTemp);
						break;
					}
				}
			}
		}
	}

	this->RedrawButton();

	return TRUE;
}

/**
	add  button for toolbar
	all param input
param:
	nId		Button id for send WM_COMMAND used
	wType	Button style is BT_BUTTON,BT_CHECK,	or BT_DROPDOWN
	wY		Button left top point Y position units pixel
	wWidth	Button Width
	wHeight Button Height
	wSrcX	Button image left top point X position in Pix file
	wSrcX	Button image left top point Y position in Pix file
	strTip	Button text information
	pMenu	Button if has
return:
	TRUE	success
	FLASE	fail

*/

BOOL CXTBmpToolBar::AddButton(UINT nId,
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
	TBBUTTON button = {0};
	button.idCommand = nId;
	button.iBitmap = 0;
	button.iString = -1;
	button.fsState = TBSTATE_ENABLED;
	button.fsStyle = (nId != 0) ? TBSTYLE_BUTTON: TBSTYLE_SEP;

	if (DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
	{
		BARITEM *pItem = new BARITEM;
		ASSERT(NULL != pItem);

		pItem->nId = nId;
		pItem->wType = wType;
		pItem->wOffsetX = wOffsetX;
		pItem->wY = wY;
		pItem->wWidth = (nId != 0) ? wWidth: 3;
		pItem->wHeight = wHeight;
		pItem->wSrcX = wSrcX;
		pItem->wSrcY = wSrcY;

		if (BT_DROPDOWN == wType) pItem->pMenu = pMenu;
		if (NULL != strTip)	_tcscpy(pItem->tszTip, strTip);

		m_ItemList.Add(pItem);

		return TRUE;
	}

	return FALSE;	
}

void CXTBmpToolBar::RedrawButton(void)
{
	WORD wCurX = 0;
	CRect rc;
	GetWindowRect(&rc);

	int nSrcX = 0;
	int nSrcY = 0;
	int nWidth = 1;
	int nHeight = m_wWndHeight;	

	// 画背景
	if (1 == m_nBackground)
	{
		nSrcX = m_nBackgroundX;
		nSrcY = m_nBackgroundY;
		nWidth = m_nBackgroundCX;
		nHeight = m_nBackgroundCY;
	}

	::StretchBlt(m_hCompDC, 0, 0, m_wSreenWidth, m_wWndHeight, m_hBmpDC, nSrcX, nSrcY, nWidth, nHeight, SRCCOPY);
	
	// 重新计计算位置，得画按钮
	int nCount = (int)m_ItemList.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		UINT nStyle = this->GetButtonStyle(i);

		BARITEM* pItem = (BARITEM*)m_ItemList[i];
		ASSERT(NULL != pItem);

		if (nStyle & TBBS_CHECKED)
			pItem->bCheck = TRUE;
		else
			pItem->bCheck = FALSE;

		if (nStyle & TBBS_DISABLED)
			pItem->bEnable = FALSE;
		else
			pItem->bEnable = TRUE;

		if (nStyle & TBBS_HIDDEN)
			pItem->bShow = FALSE;
		else
			pItem->bShow = TRUE;

		if (pItem->bShow)
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
		}
	}

	::BitBlt(m_hWndDC, 0, 0, m_wSreenWidth, m_wWndHeight, m_hCompDC, 0, 0, SRCCOPY);
	TRACE(_T("RedrawButton\n"));
}

void CXTBmpToolBar::SetShow(WORD wButtonId, BOOL bShow)
{
	BARITEM* pItem = (BARITEM*)m_ItemList[wButtonId];

	if (NULL != pItem)
	{
		pItem->bShow = bShow;

		RedrawButton();
	}
}
void CXTBmpToolBar::SetEnable(WORD wButtonId, BOOL bEnable)
{
	BARITEM* pItem = (BARITEM*)m_ItemList[wButtonId];

	if (NULL != pItem)
	{
		pItem->bEnable = bEnable;

		this->DrawButton(m_hWndDC, pItem, bEnable ? DR_ENABLE : DR_UNABLE);
		this->DrawButton(m_hCompDC, pItem, bEnable ? DR_ENABLE : DR_UNABLE);
	}
}
void CXTBmpToolBar::SetCheck(WORD wButtonId, BOOL bCheck)
{
	BARITEM* pItem = (BARITEM*)m_ItemList[wButtonId];

	if (NULL != pItem)
	{
		pItem->bCheck = bCheck;

		this->DrawButton(m_hWndDC, pItem, bCheck ? DR_CHECK : DR_UNCHECK);
		this->DrawButton(m_hCompDC, pItem, bCheck ? DR_CHECK : DR_UNCHECK);
	}
}

void CXTBmpToolBar::DrawButton(HDC hDC, BARITEM *pItem, WORD wType)
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

// 虚函数，设置按钮的Enable
void CXTBmpToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CToolBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);

	int nCount = (int)m_ItemList.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		UINT nStyle = this->GetButtonStyle(i);

		BARITEM* pItem = (BARITEM*)m_ItemList[i];
		ASSERT(NULL != pItem);

		if (nStyle & TBBS_CHECKED)
		{
			pItem->bCheck = TRUE;
		}
		else
		{
			pItem->bCheck = FALSE;
		}

		if (nStyle & TBBS_DISABLED)
			pItem->bEnable = FALSE;
		else
			pItem->bEnable = TRUE;

		if (nStyle & TBBS_HIDDEN)
			pItem->bShow = FALSE;
		else
			pItem->bShow = TRUE;
		}
}

// 虚函数,控制大小
CSize CXTBmpToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CRect rcBackground;
	CSize size(32, m_wWndHeight + 4);

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
BARITEM* CXTBmpToolBar::HitTest(const CPoint& point) const
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
int CXTBmpToolBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
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
void CXTBmpToolBar::DoPaint(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	
	if (NULL == m_hWndDC) m_hWndDC = pDC->GetSafeHdc();

	::BitBlt(m_hWndDC, 0, 0, m_wSreenWidth, m_wWndHeight, m_hCompDC, 0, 0, SRCCOPY);
}

// 设置鼠标指针
BOOL CXTBmpToolBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
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
	
	return CToolBar::OnSetCursor( pWnd, nHitTest, message );
}

void CXTBmpToolBar::OnMouseMove(UINT nFlags, CPoint point)
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
			this->DrawButton(m_hWndDC, pItem, pItem->bCheck ? DR_CHECK : DR_HOVER);
			m_pLastHoverItem = pItem;
		}
	}
	else if (NULL == pItem && NULL != m_pLastHoverItem)	// 鼠标离开了上一个按钮
	{
		if (m_pLastHoverItem->bEnable)
		{
			this->DrawButton(m_hWndDC, m_pLastHoverItem, m_pLastHoverItem->bCheck ? DR_CHECK : DR_OK);
			m_pLastHoverItem = NULL;
		}
	}
	else if (NULL != pItem && pItem != m_pLastHoverItem)// 鼠标由一个按钮直接移动到另一个按钮上
	{
		if (m_pLastHoverItem->bEnable)
		{
			this->DrawButton(m_hWndDC, m_pLastHoverItem, m_pLastHoverItem->bCheck ? DR_CHECK : DR_OK);
		}

		if (pItem->bEnable)
		{
			this->DrawButton(m_hWndDC, pItem, pItem->bCheck ? DR_CHECK : DR_HOVER);
		}
		m_pLastHoverItem = pItem;
	}
}

LRESULT CXTBmpToolBar::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (NULL != m_pLastHoverItem)
	{
		if (m_pLastHoverItem->bEnable)
		{
			this->DrawButton(m_hWndDC, m_pLastHoverItem, m_pLastHoverItem->bCheck ? DR_CHECK : DR_OK);
		}

		m_pLastHoverItem = NULL;
	}
	return   0;   
}

void CXTBmpToolBar::OnLButtonDown(UINT nFlags, CPoint point)
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
		CToolBar::OnLButtonDown(nFlags, point);
	}
}

void CXTBmpToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (NULL != m_pLastClickItem && m_pLastClickItem->bEnable)
	{
		if (BT_CHECK != m_pLastClickItem->wType)				// Check按钮
		{
			this->DrawButton(m_hWndDC, m_pLastClickItem, DR_OK);
			m_pLastClickItem = NULL;
		}
	}

	CToolBar::OnLButtonUp(nFlags, point);
}

void CXTBmpToolBar::OnPaint()
{
	CPaintDC dc(this);

	this->RedrawButton();

	//if (NULL == m_hWndDC) m_hWndDC = dc.GetSafeHdc();
	//::BitBlt(m_hWndDC, 0, 0, m_wSreenWidth, m_wWndHeight, m_hCompDC, 0, 0, SRCCOPY);
}

