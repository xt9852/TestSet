#include "stdafx.h"
#include "CCBEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCBEx

CCBEx *g_cbEx = NULL;
BOOL g_bInit = FALSE;
int g_nIndexIn = -1;
int g_nIndexInLast = -1;

CCBEx::CCBEx()
{
	m_nWidthDropBt = 100;
	m_nWidthDropList = 100;

}

CCBEx::~CCBEx()
{
}



BEGIN_MESSAGE_MAP(CCBEx, CComboBox)
	//{{AFX_MSG_MAP(CCBEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBEx message handlers
CBrush g_brushItem1(RGB(255, 0, 0));
CBrush g_brushItem2(RGB(255, 255, 0));
CBrush g_brushItem3(RGB(255, 0, 255));
CBrush g_brushItemSelected(RGB(0, 122, 122));

void CCBEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item

	HWND hWndParent = ::GetParent(lpDrawItemStruct->hwndItem);
	HDC hDC = ::GetDC(hWndParent);

	::DeleteDC(hDC);


	CRgn rgn;
	rgn.CreateEllipticRgn(lpDrawItemStruct->rcItem.left, 
		lpDrawItemStruct->rcItem.top, 
		lpDrawItemStruct->rcItem.right, 
		lpDrawItemStruct->rcItem.bottom);



	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CString sItem;

	if (-1 != lpDrawItemStruct->itemID)
		GetLBText(lpDrawItemStruct->itemID, sItem);
	CRect rcItem = lpDrawItemStruct->rcItem;
	if(g_nIndexIn != -1 && (int)lpDrawItemStruct->itemID == g_nIndexIn)
	{
		pDC->FillRgn(&rgn, &g_brushItemSelected);

	}
	else
	{
		switch(lpDrawItemStruct->itemID % 3)
		{
		case 0:
			pDC->FillRgn(&rgn, &g_brushItem1);
			break;
		case 1:
			pDC->FillRgn(&rgn, &g_brushItem2);
			break;
		case 2:
			pDC->FillRgn(&rgn, &g_brushItem3);
			break;
		}

	}



	pDC->SetBkMode(TRANSPARENT);

	pDC->SetTextColor(RGB(0, 0, 0));
	if((g_nIndexIn != -1) && (g_nIndexIn == (int)lpDrawItemStruct->itemID))
	{
		pDC->SetTextColor(RGB(255, 255, 255));
	}
	pDC->TextOut(rcItem.left + rcItem.Width() / 2 - 3, 
		rcItem.top + rcItem.Height() / 2 - 7,
		sItem);
	rgn.DeleteObject();
}
LONG wndproc = NULL;
LONG wndprocOld = NULL;

CBrush g_brushDropList(RGB(0, 255, 0));
LRESULT CALLBACK epassProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{


	if (uMsg == WM_CREATE)
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);

	}

	if(uMsg == WM_DESTROY) //0x0002
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_MOVE) //0x0003
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_SIZE) //0x0005
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_ACTIVATE) //0x0006
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_SETFOCUS) //0x0007
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_KILLFOCUS) //0x0008
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_PAINT)
	{
		//  TRACE("WM_PAINT\n");
		//  return TRUE;
		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_NCPAINT)
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}



	if(uMsg == WM_ERASEBKGND) //绘制背景，
	{
		CListBox *pLB = (CListBox*)CListBox::FromHandle(hwnd);
		CDC *pDC = CDC::FromHandle((HDC)wParam); 
		CRect rcLB;
		pLB->GetClientRect(rcLB);
		pDC->FillRect(rcLB, &g_brushDropList);
		return TRUE;
	}

	if(uMsg == WM_SHOWWINDOW) //0x0018
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_ACTIVATEAPP) //0x001c 
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_DRAWITEM)
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);

	}

	if(uMsg == WM_WINDOWPOSCHANGING) //0x0046 
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_WINDOWPOSCHANGED) //0x0047
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_STYLECHANGING) //0x007c
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_STYLECHANGED) //0x007d
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_NOTIFY) //0x007e
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}


	if(uMsg == WM_GETICON) //0x007f
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}


	if(uMsg == WM_NCDESTROY )//0x0082
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}


	if(uMsg == WM_NCCALCSIZE) //0x0083
	{

		//      LPNCCALCSIZE_PARAMS pNcCalcSizeParam = (LPNCCALCSIZE_PARAMS)lParam;
		//  pNcCalcSizeParam->rgrc[0].left -= 17;

		//  DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);  
		//  if(dwStyle & WM_VSCROLL)
		//  {
		//
		//  }
		//  else
		//  {
		//
		//   }

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_NCACTIVATE) //0x0086
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_GETDLGCODE) //0x0087
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_NCLBUTTONDOWN) //0x00a1
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}



	if(uMsg == 0x00af) //
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_KEYUP) //0x0101
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_SYSCOMMAND) //0x0101
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_COMMAND)
	{
		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_VSCROLL) //0x0115
	{

		//  CWnd *pWnd = CWnd::FromHandle(hwnd);
		//  CWnd *pParent = pWnd->GetParent();
		//  CRect rcClient;
		//   pWnd->GetClientRect(rcClient);
		//  pWnd->ClientToScreen(rcClient);
		//  pParent->ScreenToClient(rcClient);
		//  CWnd *pParentCB = g_cbEx->GetParent();
		//  pParentCB->ScreenToClient(rcClient);
		//   pParentCB->InvalidateRect(rcClient, TRUE);
		//  pParent->InvalidateRect(rcClient, TRUE);

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_HSCROLL)//0x1501
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_CTLCOLOREDIT)
	{
		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_CTLCOLORLISTBOX)
	{
		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_SETCURSEL) //0x0186
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_GETCURSEL) //0x0188
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}



	if(uMsg == LB_GETTEXT) //0x0189
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_GETTEXTLEN) //0x018a
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_GETCOUNT) //0x018b
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	} 
	if(uMsg == LB_SELECTSTRING) //0x018c
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	} 
	if(uMsg == LB_GETTOPINDEX) //0x018e
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}


	if(uMsg == LB_FINDSTRING) //0x018f
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_GETITEMRECT) //0x0198
	{


		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_SETCARETINDEX)//0x019e
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_SETTOPINDEX)//0x0197
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_GETITEMHEIGHT)//0x01a1
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == LB_FINDSTRINGEXACT)//0x01a2
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == 0x01ae)
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == 0x01af)
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_MOUSEMOVE)//0x0200
	{
		//  TRACE("WM_PRINT\n");
		CListBox *pLB = (CListBox*)CListBox::FromHandle(hwnd);
		int nIndexTop = pLB->GetTopIndex();
		//  TRACE("nIndexTop = %d\n", nIndexTop);
		POINT point;
		GetCursorPos(&point);

		CPoint pt(point.x, point.y);
		pLB->ScreenToClient(&pt);

		CRect rcClient;
		pLB->GetClientRect(rcClient);
		CRect rcItem;
		int nIndex = -1;
		for(int i = nIndexTop; i < pLB->GetCount();i++)
		{
			pLB->GetItemRect(i, rcItem);
			if(rcItem.PtInRect(pt))
			{
				nIndex = i;
				break;

			}

			if(rcItem.bottom > rcClient.bottom || rcItem.top < 0)
			{
				break;
			}

			if(pt.x < 0 || pt.y < 0 || pt.x > rcClient.right || pt.y > rcClient.bottom)
			{
				break;
			}

		}

		if(g_nIndexIn != nIndex)
		{

			g_nIndexInLast = g_nIndexIn;
			g_nIndexIn = nIndex;
			//   pLB->Invalidate();
			if(g_nIndexInLast != -1)
			{
				CRect rcItemLast;
				pLB->GetItemRect(g_nIndexInLast, rcItemLast);
				pLB->InvalidateRect(rcItemLast, TRUE);

			}
			TRACE("g_nIndexInLast = %d\n", g_nIndexInLast);


			if(g_nIndexIn != -1)
			{
				CRect rcItem;
				pLB->GetItemRect(g_nIndexIn, rcItem);
				pLB->InvalidateRect(rcItem, TRUE);

			}
			TRACE("nIndex = %d\n\n", nIndex);

		}




		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_LBUTTONDOWN)//0x0201
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_LBUTTONUP)//0x0202
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_MOUSEWHEEL) //0x020a
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}
	if(uMsg == WM_CAPTURECHANGED) //0x0215
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}


	if(uMsg == WM_IME_SETCONTEXT) //0x0281
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if(uMsg == WM_IME_NOTIFY) //0x0282
	{

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);
	}

	if (uMsg == WM_PRINT) //0x0317
	{

		//  TRACE("WM_PRINT\n");
		CListBox *pLB = (CListBox*)CListBox::FromHandle(hwnd);

		//移动窗口   
		if(g_cbEx != NULL)
		{

			CRect rect;
			pLB->GetWindowRect(&rect);

			CRect rcCB;
			g_cbEx->GetWindowRect(rcCB);
			rect.left = rcCB.left + 120;
			rect.right = rcCB.right + 20;
			rect.bottom = rcCB.bottom + 150;
			pLB->MoveWindow(&rect);
		}
		//注意每次ShowDropDown就发送该消息，
		//得把它转给WM_PAINT

		//设置窗口有效区域
		//  if(g_cbEx != NULL)
		//  {
		//      if(!g_bInit)
		//   {
		//                g_cbEx->Init(pLB);
		//    g_bInit = FALSE;
		//   }
		//  
		//   }

		//      pLB->ShowScrollBar(SB_VERT, TRUE);

		int nOp = 0;

		//
		if(lParam & PRF_CHECKVISIBLE)
		{
			//   nOp |= PRF_CHECKVISIBLE;
		}

		//背景重新绘制:WM_ERASEBKGND。
		if(lParam & PRF_ERASEBKGND)
		{
			nOp |= PRF_ERASEBKGND;
		}

		//滚动条等非客户区重新绘制。
		if(lParam & PRF_NONCLIENT)
		{
			nOp |= PRF_NONCLIENT;
		}

		//客户区重新绘制:WM_PRINTCLIENT。
		if(lParam & PRF_CLIENT)
		{
			nOp |= PRF_CLIENT;
		}

		//子窗口绘制，注意滚动条不属于自窗口它和ListBox并列。
		if(lParam & PRF_CHILDREN)
		{
			//   nOp |= PRF_CHILDREN;
		}

		//父窗口绘制。
		if(lParam & PRF_OWNED)
		{
			//   nOp |= PRF_OWNED; 
		}  

		//  pLB->Invalidate(TRUE);

		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,(LPARAM)nOp); 


	}

	if (uMsg == WM_PRINTCLIENT) //绘制Item
	{
		//     TRACE("WM_PRINTCLIENT!\n"); 
		return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam); 
		//  return TRUE;

	}

	TRACE("%08x,%04x,%d,%d\n", hwnd, uMsg, wParam, lParam);
	return CallWindowProc((WNDPROC)wndprocOld,hwnd,uMsg,wParam,lParam);;

}

HBRUSH CCBEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{



	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	if(wndprocOld != NULL)
	{
		return hbr;
	}
	CRect rcClient;
	this->GetClientRect(rcClient);
	switch(nCtlColor)
	{
	case CTLCOLOR_EDIT:
		{
			if(m_editEx.GetSafeHwnd() == NULL)
			{
				m_editEx.SubclassWindow(pWnd->m_hWnd);
			}
			CRect rect;
			pWnd->GetWindowRect(&rect);
			pWnd->MoveWindow(CRect(1, 21, rcClient.right - m_nWidthDropBt, rcClient.bottom - 21));

		}
		break;
	case CTLCOLOR_LISTBOX:
		{    
			this->ClientToScreen(rcClient);            
			CRect rect;
			pWnd->GetWindowRect(&rect);

			rect.left = 0; //rcClient.right - m_nWidthDropBt / 2 - m_nWidthDropList / 2;
			rect.right = 0; //rect.left + m_nWidthDropList;
			rect.top = 0; //rcClient.bottom;
			rect.bottom = 0; //rcClient.bottom + 150;
			pWnd->MoveWindow(&rect);

			if(wndprocOld == NULL)
			{

				wndprocOld = GetWindowLong(pWnd->m_hWnd, GWL_WNDPROC);
				SetWindowLong(pWnd->m_hWnd, GWL_WNDPROC, (long)epassProc);

				UINT nStyle = GetWindowLong(pWnd->m_hWnd, GWL_STYLE);
				nStyle &= ~WS_BORDER;
				SetWindowLong(pWnd->m_hWnd, GWL_STYLE, WS_CHILD | nStyle/*| WS_VISIBLE*/);

				SetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE, WS_CHILD | WS_EX_LEFTSCROLLBAR);


				g_cbEx = this;
				//    int iStyle = g_cbEx->GetStyle();
				//     g_cbEx->ModifyStyle(0, iStyle | LBS_NOTIFY);


			}   


		}
		break;
	}

	return hbr;
	// TODO: Change any attributes of the DC here

}
void CCBEx::Init(CListBox *pLB)
{
	DWORD dwStyle = GetWindowLong(pLB->m_hWnd, GWL_STYLE);

	int nWidScroll = 0;
	if(dwStyle & WM_VSCROLL)
	{
		nWidScroll = ::GetSystemMetrics(SM_CXVSCROLL);
	}

	CRect rcItem;
	CRgn rgnClient;
	rgnClient.CreateRectRgn(0, 0, 0, 0);
	CRgn rgnItem;
	for(int i = 0; i < pLB->GetCount(); i++)
	{
		pLB->GetItemRect(i, rcItem);
		rgnItem.CreateEllipticRgn(rcItem.left, rcItem.top, rcItem.right, rcItem.bottom);
		rgnClient.CombineRgn(&rgnClient, &rgnItem, RGN_OR);
		rgnItem.DeleteObject();

	}


	// CRect rcClient;
	// GetClientRect(rcClient);
	// rcClient.right = rcClient.left;
	//  rgnItem.CreateRectRgn(1, 1, rcClient.right, 99/*rcClient.bottom*/);
	//  rgnClient.CombineRgn(&rgnClient, &rgnItem, RGN_OR);
	//  rgnItem.DeleteObject();

	pLB->SetWindowRgn(rgnClient, FALSE);

	rgnClient.DeleteObject();
}


void CCBEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	// lpMeasureItemStruct->itemHeight = 100;
}

CBrush g_brushDropBt(RGB(0, 255, 0));
CPen g_penEdit(PS_SOLID, 2, RGB(0, 255, 0));

void CCBEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	this->GetClientRect(rcClient);
	CRect rcEdit = rcClient;
	rcEdit.right = rcClient.right - m_nWidthDropBt + 1;
	rcEdit.top += 20;
	rcEdit.bottom -= 20;
	CRgn rgnEdit;
	rgnEdit.CreateRectRgn(rcEdit.left, rcEdit.top, rcEdit.right, rcEdit.bottom);

	CPen *pOldPen = dc.SelectObject(&g_penEdit);
	dc.Rectangle(rcEdit);
	CRect rcBt = rcClient;
	rcBt.left = rcClient.right - m_nWidthDropBt + 1;
	CRgn rgn;
	rgn.CreateEllipticRgn(rcBt.left, rcBt.top, rcBt.right, rcBt.bottom);
	dc.FillRgn(&rgn, &g_brushDropBt);
	rgn.CombineRgn(&rgn, &rgnEdit, RGN_OR);
	this->SetWindowRgn(rgn, TRUE);

	dc.SelectObject(pOldPen);
	rgnEdit.DeleteObject();
	rgn.DeleteObject();


	// TODO: Add your message handler code here

	// Do not call CComboBox::OnPaint() for painting messages
}

void CCBEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// this->SetFocus();
	// this->SetCurSel(0); 

	if(wndprocOld == NULL)
	{
		ShowDropDown(TRUE);
		ShowDropDown(FALSE);
	}
	ShowDropDown(TRUE);

}

void CCBEx::OnDestroy() 
{

	if(m_editEx.GetSafeHwnd() != NULL)
	{

		m_editEx.UnsubclassWindow();
	}
	CComboBox::OnDestroy();

	// TODO: Add your message handler code here

}

LRESULT CCBEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	// if(message == WM_COMMAND)
	// {
	//  if(HIWORD(wParam) == LBN_SELCHANGE)
	//  {
	//
	//  }
	//  }
	return CComboBox::DefWindowProc(message, wParam, lParam);
}

void CCBEx::OnDropdown() 
{
	// TODO: Add your control notification handler code here 
}

void CCBEx::OnCloseup() 
{

	// TODO: Add your control notification handler code here 
}

void CCBEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnMouseMove(nFlags, point);
}
