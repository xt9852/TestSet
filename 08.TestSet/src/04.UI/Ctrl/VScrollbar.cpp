// VScrollBar.cpp : 实现文件
//

#include "stdafx.h"
#include "VScrollBar.h"
#include "XTDC.h"

// CVScrollBar

IMPLEMENT_DYNAMIC(CVScrollBar, CButton)
CVScrollBar::CVScrollBar()
{
	thumb_ = CRect(0,0,0,0);
	upArraw_ = CRect(0,0,0,0);
	downArraw_ = CRect(0,0,0,0);
	
	curPart_  = NOT;
	lastPart_ = NOT;
	inBar_    = false;
	thumbPos_ = 15;
	thumbLen_ = 20;
	interval_ = 0.0f;
	lineNum_  = 0;
}

CVScrollBar::~CVScrollBar()
{
}


BEGIN_MESSAGE_MAP(CVScrollBar, CWnd)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_MOUSEMOVE()	
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()	
	ON_WM_MOVE()
END_MESSAGE_MAP()


void CVScrollBar::PreSubclassWindow() 
{
	ModifyStyle(0, BS_OWNERDRAW);
	CWnd::PreSubclassWindow();
}

LRESULT CVScrollBar::OnMouseLeave(WPARAM   wParam,   LPARAM   lParam)
{
	inBar_ = false;
	DrawImage(DLGDC, OK, lastPart_);
	lastPart_ = NOT;
	return 0;   
}

void CVScrollBar::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT stTRACKMOUSEEVENT = {0};
	stTRACKMOUSEEVENT.cbSize =  sizeof(stTRACKMOUSEEVENT);
	stTRACKMOUSEEVENT.dwFlags = TME_LEAVE;	
	stTRACKMOUSEEVENT.hwndTrack = m_hWnd;
	
	_TrackMouseEvent(&stTRACKMOUSEEVENT);

	UINT state = (nFlags == MK_LBUTTON) ? MOUSE_DOWN : MOUSE_ON;

	curPart_ = NOT;
	
	point.x += x_;
	point.y += y_;

	if (!inBar_)
	{
		m_Point  = point;
		inBar_ = true;
	}

	if (upArraw_.PtInRect(point))
	{
		curPart_ = UPARRAW;
	}
	else if (downArraw_.PtInRect(point))
	{
		curPart_ = DOWNARRAW;
	}
	else if (thumb_.PtInRect(point))
	{
		curPart_ = THUMB;

		if (nFlags == MK_LBUTTON)//移动//////////////////////////////
		{
			if ((float)point.y > (float)(m_Point.y + m_fInterval))
			{
				int nLineNum = (int)((point.y - m_Point.y) / m_fInterval);
				m_Point = point;
				PageDown( nLineNum );
			}
			else if ((float)point.y < (float)(m_Point.y - m_fInterval))
			{
				int nLineNum = (int)((m_Point.y - point.y) / m_fInterval);
				m_Point = point;
				PageUp(nLineNum);
			}

			DrawImage(DLGDC, MOUSE_DOWN, THUMB_BKG);
			goto end;
		}
	}
	
	if (curPart_ == NOT && lastPart_ != NOT)
	{
		DrawImage(DLGDC, OK, lastPart_);
		lastPart_ = NOT;
	}
	else if (curPart_ != NOT && lastPart_ == NOT)
	{
		DrawImage(DLGDC, state, curPart_);
		lastPart_ = curPart_;
	}
	else if (curPart_ != NOT && lastPart_ != NOT && curPart_ != lastPart_)
	{
		DrawImage(DLGDC, state, curPart_);
		DrawImage(DLGDC, OK, lastPart_);
		lastPart_ = curPart_;
	}

end:
	CButton::OnMouseMove(nFlags, point);
}

void CVScrollBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();

	point.x += x_;
	point.y += y_;

	if (upArraw_.PtInRect(point))
	{
		lastPart_ = UPARRAW;
		ScrollUp(1);
		DrawImage(DLGDC, MOUSE_DOWN, lastPart_);
	}
	else if (downArraw_.PtInRect(point))
	{
		lastPart_ = DOWNARRAW;
		ScrollDown(1);
		DrawImage(DLGDC, MOUSE_DOWN, lastPart_);
	}
	else if (thumb_.PtInRect(point))
	{
		lastPart_ = THUMB;
		DrawImage(DLGDC, MOUSE_DOWN, lastPart_);
	}
	else if (point.y < (m_Rect.top + thumbPos_))
	{
		PageUp(5);
	}
	else if (point.y > ( m_Rect.top + thumbPos_ + thumbLen_))
	{
		PageDown(5);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CVScrollBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	DrawImage(DLGDC, OK, lastPart_);

	curPart_ = NOT;
	lastPart_ = NOT;

	KillTimer(1);
	KillTimer(2);

	CWnd::OnLButtonUp(nFlags, point);
}

void CVScrollBar::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		if(DOWNARRAW == curPart_)
			ScrollDown(5);
		if(UPARRAW == curPart_)
			ScrollUp(5);
	}
	else if (nIDEvent == 2)
	{
		if (DOWNARRAW == curPart_)
		{
			KillTimer(2);
			SetTimer(1, 50, NULL);
		}
		if (UPARRAW == curPart_)
		{
			KillTimer(2);
			SetTimer(1, 50, NULL);
		}
	}

	CWnd::OnTimer(nIDEvent);
}

void CVScrollBar::PageUp(int nLineNum)
{
	if (0 == nLineNum) return;

	CWnd *pParent = this->GetParent();
	pParent->PostMessage(WM_MOVEUP, -1*nLineNum, 0);
	UpdateThumbPosition((int)(-1*nLineNum*interval_));
}
void CVScrollBar::PageDown(int nLineNum)
{
	if (0 == nLineNum) return;

	CWnd *pParent = this->GetParent();
	pParent->PostMessage(WM_MOVEDOWN, nLineNum, 0);
	UpdateThumbPosition((int)(nLineNum*interval_));
}
void CVScrollBar::ScrollUp(int nLineNum)
{
	if (0 == nLineNum) return;

	CWnd *pParent = this->GetParent();
	pParent->PostMessage(WM_MOVEUP, -1*nLineNum, 0);	
	UpdateThumbPosition((int)(-1*nLineNum*interval_));
}
void CVScrollBar::ScrollDown(int nLineNum)
{
	if (0 == nLineNum) return;

	CWnd *pParent = this->GetParent();
	pParent->PostMessage(WM_MOVEDOWN, nLineNum, 0);	
	UpdateThumbPosition((int)(nLineNum*interval_));
}

void CVScrollBar::UpdateThumbPosition(int nInterval)
{
	thumbPos_ += nInterval;
	
	LimitThumbPosition();

	thumb_.left   = m_Rect.left;
	thumb_.top    = m_Rect.top + thumbPos_;
	thumb_.right  = m_Rect.right;
	thumb_.bottom = m_Rect.top + thumbPos_ + thumbLen_;
}

void CVScrollBar::LimitThumbPosition(void)
{
	if (thumbPos_ > (m_Rect.Height() - 15 - thumbLen_))
	{
		thumbPos_ = m_Rect.Height() - 15 - thumbLen_;
	}

	if (thumbPos_ < 15)
	{
		thumbPos_ = 15;
	}
}

BOOL CVScrollBar::OnEraseBkgnd(CDC* pDC)
{
	//return CButton::OnEraseBkgnd(pDC);
	return TRUE;
}

void CVScrollBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	DrawImage(DLG_COMP_DC);
}

//绘图
//uObject:[IN]为0在m_hDC上绘，为1在m_hDC和m_hCompDC绘(只在初始化时绘)
//uState:[IN]为0绘平常状态，1绘鼠标在上面，2绘鼠标按下
//uPart:[IN]为0绘上箭头，为1下箭头，为2中间部分，为3
void CVScrollBar::DrawImage(int obj, int state, int part)
{
	HDC dc = (DLGDC == obj)?dc_:compDC_;

// 	if (DLGDC == uObject)
// 	{
		switch(uPart)
		{
		case UPARRAW://上箭头
			{				
				::BitBlt(dc, x_, y_, 15, 15, imageDC_, sx_ + state * 15, sy_ + 0, SRCCOPY);
				break;
			}
		case DOWNARRAW://下箭头
			{
				::BitBlt(dc, x_, m_Rect.bottom - 15, 15, 15, imageDC_, m_SrcPt.x + state * 15, sy_ + 36, SRCCOPY);
				break;
			}
		case THUMB:
			{
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_, 15, 5, imageDC_, m_SrcPt.x + state * 15, sy_ + 15, SRCCOPY);
				//中间部分.背景
				::StretchBlt(dc, x_, y_ + thumbPos_ + 5, 15, thumbLen_ - 10, imageDC_, m_SrcPt.x + state * 15, sy_ + 19, 15, 1, SRCCOPY);
				//中间部分.中
				::BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_/2 - 5, 15, 10, imageDC_, m_SrcPt.x + state * 15, sy_ + 20, SRCCOPY);
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_ - 5, 15, 5, imageDC_, m_SrcPt.x + state * 15, sy_ + 30, SRCCOPY);		
				break;
			}			
		case THUMB_BKG:
			{
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_, 15, 5, imageDC_, m_SrcPt.x + state * 15, sy_ + 15, SRCCOPY);
				//中间部分.背景
				::StretchBlt(dc, x_, y_ + thumbPos_ + 5, 15, thumbLen_ - 10, imageDC_, m_SrcPt.x + state * 15, sy_ + 19, 15, 1, SRCCOPY);
				//中间部分.中
				::BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_/2 - 5, 15, 10, imageDC_, m_SrcPt.x + state * 15, sy_ + 20, SRCCOPY);
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_ - 5, 15, 5, imageDC_, m_SrcPt.x + state * 15, sy_ + 30, SRCCOPY);
				//背景.上
				::StretchBlt(dc, x_, y_ + 15, 15, thumbPos_ - 15, imageDC_, m_SrcPt.x + state * 15, sy_ + 35, 15, 1, SRCCOPY);
				//背景.下			
				::StretchBlt(dc,  x_ , y_ + thumbPos_ + thumbLen_, 
					15, m_Rect.bottom - 15 - y_ - thumbPos_ - thumbLen_, imageDC_, m_SrcPt.x + state * 15, sy_ + 35, 15, 1, SRCCOPY);

				break;
			}
		default:
			break;
		}
	/*}
	else
	{
		//上箭头
		::BitBlt(m_hCompDC, m_Rect.left , m_Rect.top, 15, 15, imageDC_, m_SrcPt.x + 0, sy_ + 0, SRCCOPY);
		::BitBlt(dc, m_Rect.left , m_Rect.top, 15, 15, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 0, SRCCOPY);
		//中间部分.上
		::BitBlt(m_hCompDC, m_Rect.left, m_Rect.top + m_nThumbPoint, 15, 5, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 15, SRCCOPY);
		::BitBlt(dc, m_Rect.left, m_Rect.top + m_nThumbPoint, 15, 5, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 15, SRCCOPY);
		//中间部分.背景
		::StretchBlt(m_hCompDC, m_Rect.left , m_Rect.top + m_nThumbPoint + 5, 15, m_nThumbLength - 10, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 19, 15, 1, SRCCOPY );
		::StretchBlt(dc, m_Rect.left , m_Rect.top + m_nThumbPoint + 5, 15, m_nThumbLength - 10, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 19, 15, 1, SRCCOPY );
		//中间部分.中
		::BitBlt(m_hCompDC, m_Rect.left, m_Rect.top + m_nThumbPoint + m_nThumbLength/2 - 5, 15, 10, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 20, SRCCOPY);
		::BitBlt(dc, m_Rect.left, m_Rect.top + m_nThumbPoint + m_nThumbLength/2 - 5, 15, 10, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 20, SRCCOPY);
		//中间部分.上
		::BitBlt(m_hCompDC, m_Rect.left, m_Rect.top + m_nThumbPoint + m_nThumbLength - 5, 15, 5, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 30, SRCCOPY);
		::BitBlt(dc, m_Rect.left, m_Rect.top + m_nThumbPoint + m_nThumbLength - 5, 15, 5, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 30, SRCCOPY);		
		//下箭头
		::BitBlt(m_hCompDC, m_Rect.left, m_Rect.bottom - 15, 15, 15, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 36, SRCCOPY);
		::BitBlt(dc, m_Rect.left, m_Rect.bottom - 15, 15, 15, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 36, SRCCOPY);
		//背景.上
		::StretchBlt(m_hCompDC, m_Rect.left, m_Rect.top + 15, 15, m_nThumbPoint - 15, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 35, 15, 1, SRCCOPY );
		::StretchBlt(dc, m_Rect.left, m_Rect.top + 15, 15, m_nThumbPoint - 15, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 35, 15, 1, SRCCOPY );
		//背景.下
		::StretchBlt(m_hCompDC, m_Rect.left, m_Rect.top + m_nThumbPoint + m_nThumbLength, 
			15, m_Rect.bottom - 15 - m_Rect.top - m_nThumbPoint - m_nThumbLength, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 35, 15, 1, SRCCOPY );
		::StretchBlt(dc, m_Rect.left, m_Rect.top + m_nThumbPoint + m_nThumbLength, 
			15, m_Rect.bottom - 15 - m_Rect.top - m_nThumbPoint - m_nThumbLength, m_hImageDC, m_SrcPt.x + 0, m_SrcPt.y + 35, 15, 1, SRCCOPY );

	}*/
}

void CVScrollBar::OnMove(int x, int y)
{
	CButton::OnMove(x, y);

	m_Rect.left = x;
	m_Rect.top	= y;
}

void CVScrollBar::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	m_Rect.right  = m_Rect.left + cx;
	m_Rect.bottom = m_Rect.top	+ cy;

	//向上箭头
	upArraw_.left		= m_Rect.left;
	upArraw_.top		= m_Rect.top;
	upArraw_.right		= m_Rect.right;
	upArraw_.bottom	= m_Rect.top + 15;
	//向下箭头
	downArraw_.left	= m_Rect.left;
	downArraw_.top		= m_Rect.bottom - 15;
	downArraw_.right	= m_Rect.right;
	downArraw_.bottom	= m_Rect.bottom;
	//中间部分
	thumb_.left		= m_Rect.left;
	thumb_.top			= m_Rect.top + m_nThumbPoint;
	thumb_.right		= m_Rect.right;
	thumb_.bottom		= m_Rect.top + m_nThumbPoint + m_nThumbLength;
}

void CVScrollBar::SetThumbTop(UINT nThumbTop)
{
	if (nThumbTop >= 15 && (m_nThumbPoint + m_nThumbLength) < (m_Rect.Height() - 15))
		m_nThumbPoint = nThumbTop;
}

bool CVScrollBar::Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *pxtDC)
{
	if (NULL == pxtDC) return false;

	m_SrcPt.x				= sx;
	m_SrcPt.y				= sy;
	// 自己
	m_Rect.left				= x;
	m_Rect.top				= y;
	m_Rect.right			= x + cx;
	m_Rect.bottom			= y + cy;
	// 向上箭头
	m_UpArrawRect.left		= m_Rect.left;
	m_UpArrawRect.top		= m_Rect.top;
	m_UpArrawRect.right		= m_Rect.right;
	m_UpArrawRect.bottom	= m_Rect.top + 15;
	// 向下箭头
	m_DownArrawRect.left	= m_Rect.left;
	m_DownArrawRect.top		= m_Rect.bottom - 15;
	m_DownArrawRect.right	= m_Rect.right;
	m_DownArrawRect.bottom	= m_Rect.bottom;
	// 中间部分
	m_ThumbRect.left		= m_Rect.left;
	m_ThumbRect.top			= m_Rect.top + m_nThumbPoint;
	m_ThumbRect.right		= m_Rect.right;
	m_ThumbRect.bottom		= m_Rect.top + m_nThumbPoint + m_nThumbLength;

	this->MoveWindow(x, y, cx, cy, 0);

	return true;
}

void CVScrollBar::ResetImage(int sx, int sy)
{
	if (-1 != sx) m_SrcPt.x = sx;
	if (-1 != sy) m_SrcPt.y = sy;

	DrawImage(DLG_COMP_DC);
}

bool CVScrollBar::SetLineNum(int nLineNum)
{
	if (nLineNum < 0) return false;

	if (nLineNum < m_Rect.Height() - 50)
		m_fInterval = 1.0f;
	else
		m_fInterval = (m_Rect.Height() - 50) / (float)nLineNum;

	m_nLineNum     = nLineNum;
	m_nThumbLength = m_Rect.Height() - 30 - (int)(m_nLineNum * m_fInterval);

	m_ThumbRect.bottom = m_Rect.top + m_nThumbPoint + m_nThumbLength;		

	DrawImage(DLG_COMP_DC);

	return true;
}

bool CVScrollBar::MoveTo(int nMoveLine)
{
	if (0 == nMoveLine) return false;

	UpdateThumbPosition(nMoveLine);
	DrawImage(DLGDC, MOUSE_DOWN, THUMB_BKG);
	return true;
}

/*
// wParam [IN] > 0 下移，< 0上移
LRESULT CProgressDlg::PageMove(WPARAM wParam, LPARAM lParam)
{
	int nLineNum = (int)wParam;
	int nOldFirstId = m_nFirstBallId;

	if (nLineNum < 0 && m_nFirstBallId > 0)	// 向上
	{
		nLineNum *= -1;

		m_nFirstBallId -= nLineNum * COL_BALL_NUM;
		if (m_nFirstBallId < 0)
		{
			m_nFirstBallId = 0;

			nOldFirstId -= m_nFirstBallId;
			nLineNum = nOldFirstId / COL_BALL_NUM;
		}

		if (nLineNum < LINE_BALL_NUM)
		{
			::BitBlt(dc,     m_ptFirstBall.x, m_ptFirstBall.y + m_szBall.cy * nLineNum, m_szBall.cx * COL_BALL_NUM, m_szBall.cy * (LINE_BALL_NUM - nLineNum), m_hCompDC, m_ptFirstBall.x, m_ptFirstBall.y, SRCCOPY);
			::BitBlt(m_hCompDC, m_ptFirstBall.x, m_ptFirstBall.y + m_szBall.cy * nLineNum, m_szBall.cx * COL_BALL_NUM, m_szBall.cy * (LINE_BALL_NUM - nLineNum), m_hCompDC, m_ptFirstBall.x, m_ptFirstBall.y, SRCCOPY);
		}

		for (int i = 0; i < nLineNum * COL_BALL_NUM; i++)
			DrawBall(m_nFirstBallId + i, 1, m_BallMap[m_nFirstBallId + i]);
	}
	else if (nLineNum > 0 && m_nFirstBallId < m_nMaxFirstBallId) // 向下
	{
		m_nFirstBallId += nLineNum * COL_BALL_NUM;
		if (m_nFirstBallId > m_nMaxFirstBallId)
		{
			m_nFirstBallId = m_nMaxFirstBallId;

			nOldFirstId = m_nFirstBallId - nOldFirstId;
			nLineNum = nOldFirstId / COL_BALL_NUM;
		}

		if (nLineNum < LINE_BALL_NUM)
		{
			::BitBlt(dc,     m_ptFirstBall.x, m_ptFirstBall.y, m_szBall.cx * COL_BALL_NUM, m_szBall.cy * ( LINE_BALL_NUM - nLineNum ), m_hCompDC, m_ptFirstBall.x, m_ptFirstBall.y + m_szBall.cy * nLineNum, SRCCOPY);
			::BitBlt(m_hCompDC, m_ptFirstBall.x, m_ptFirstBall.y, m_szBall.cx * COL_BALL_NUM, m_szBall.cy * ( LINE_BALL_NUM - nLineNum ), m_hCompDC, m_ptFirstBall.x, m_ptFirstBall.y + m_szBall.cy * nLineNum, SRCCOPY);
		}

		int nIndex = m_nFirstBallId + (LINE_BALL_NUM - nLineNum) * COL_BALL_NUM;
		for (int i = 0; i < nLineNum * COL_BALL_NUM; i++)
			DrawBall(nIndex + i, 1, m_BallMap[ nIndex + i]);
	}
	else 
		return false;

	return true;
}
*/
