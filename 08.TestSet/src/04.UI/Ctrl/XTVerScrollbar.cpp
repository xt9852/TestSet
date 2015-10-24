
#include "stdafx.h"
#include "XTVerScrollbar.h"
#include "XTDC.h"
#include <math.h>


/* x为滚动条的中间部分的长度

nLimit = nMax - rect.Width()


x                             rect.Width()
-------------------------- = --------------
rect.Width() - 16 * 2 - x       nLimit

*/


CXTVerScrollbar::CXTVerScrollbar()
	:list_(NULL),
	thumbPos_(15),
	thumbLen_(0),
	curPart_(NOT),
	lastPart_(NOT)
{
	memset(&thumb_, 0, sizeof(thumb_));
	memset(&upArraw_, 0, sizeof(upArraw_));
	memset(&downArraw_, 0, sizeof(downArraw_));
	memset(&lastDown_, 0, sizeof(lastDown_));
}

CXTVerScrollbar::~CXTVerScrollbar()
{
}

BEGIN_MESSAGE_MAP(CXTVerScrollbar, CWnd)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

void CXTVerScrollbar::PreSubclassWindow() 
{
    ModifyStyle(0, BS_OWNERDRAW);
    CWnd::PreSubclassWindow();
}

LRESULT CXTVerScrollbar::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
    DrawImage(DLGDC, OK, lastPart_);
    lastPart_ = NOT;
    return 0; 
}

void CXTVerScrollbar::OnMouseMove(UINT nFlags, CPoint point) 
{
    //SetCapture();

    // 跟踪鼠标离开事件
    TRACKMOUSEEVENT stTRACKMOUSEEVENT = {0};
    stTRACKMOUSEEVENT.cbSize =  sizeof(stTRACKMOUSEEVENT);
    stTRACKMOUSEEVENT.dwFlags = TME_LEAVE;
	stTRACKMOUSEEVENT.hwndTrack = m_hWnd;
    
    _TrackMouseEvent(&stTRACKMOUSEEVENT);

    UINT state = (nFlags == MK_LBUTTON) ? MOUSE_DOWN : MOUSE_ON;

    point.x = x_;
    point.y += y_;

    curPart_ = NOT;

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

        if (nFlags == MK_LBUTTON)
        {			
            int nMoved = point.y - lastDown_.y;

            if (0 != nMoved)
            {
                lastDown_ = point;

				CRect rc(0,0,0,0);
				list_->GetItemRect(0, &rc, LVIR_BOUNDS);

                int	limit = list_->GetScrollLimit(SB_VERT);
                int moved = (int)ceil(((double)limit * rc.Height() * nMoved) / (cy_ - 15 * 2 - thumbLen_));

                CSize size;
                size.cx = 0;
                size.cy = moved;
                list_->Scroll(size);

                UpdateThumbPosition();
            }
            goto end;
        }
    }

    if (curPart_ == NOT && lastPart_ != NOT)
    {
        DrawImage(DLGDC, OK, lastPart_);			// 恢复成正常
        lastPart_ = NOT;
    }
    else if (curPart_ != NOT && lastPart_ == NOT)
    {
        DrawImage(DLGDC, state, curPart_);	// 现在所在的区域高亮
        lastPart_ = curPart_;
    }
    else if (curPart_ != NOT && lastPart_ != NOT && curPart_ != lastPart_)
    {
        DrawImage(DLGDC, state, curPart_);
        DrawImage(DLGDC, OK, lastPart_);
        lastPart_ = curPart_;
    }

end:
    CWnd::OnMouseMove(nFlags, point);
}

void CXTVerScrollbar::OnLButtonDown(UINT nFlags, CPoint point) 
{
    point.x += x_;
    point.y += y_;

    if (upArraw_.PtInRect(point))
    {
        curPart_ = UPARRAW;
        ScrollUp();
        SetTimer(1, 50, NULL);
    }
    else if (downArraw_.PtInRect(point))
    {
        curPart_ = DOWNARRAW;
        ScrollDown();
        SetTimer(1, 50, NULL);
    }
    else if (thumb_.PtInRect(point))
    {	
        curPart_ = THUMB;
        lastDown_ = point;
    }
    else if (point.y < (y_ + thumbPos_))
    {
        curPart_ = UPARRAW;
        PageUp();
        SetTimer(2, 50, NULL);
    }
    else if (point.y > (y_ + thumbPos_ + thumbLen_))
    {
        curPart_ = DOWNARRAW;
        PageDown();
        SetTimer(2, 50, NULL);
    }

    CWnd::OnLButtonDown(nFlags, point);
}

void CXTVerScrollbar::OnLButtonUp(UINT nFlags, CPoint point) 
{
    ReleaseCapture();

    DrawImage(DLGDC, OK, lastPart_);

    curPart_ = NOT;
	lastPart_ = NOT;    

    KillTimer(1);
    KillTimer(2);

    CWnd::OnLButtonUp(nFlags, point);
}

void CXTVerScrollbar::OnTimer(UINT nIDEvent) 
{
    if (1 == nIDEvent)
    {
        if (DOWNARRAW == curPart_)
            ScrollDown();
        else if (UPARRAW == curPart_)
            ScrollUp();
    }
    else if (2 == nIDEvent)
    {
        if (DOWNARRAW == curPart_)
            PageDown();
        else if (UPARRAW == curPart_)
            PageUp();
    }

    CWnd::OnTimer(nIDEvent);
}

BOOL CXTVerScrollbar::OnEraseBkgnd(CDC* pDC)
{
    //不绘背景
    //return CButton::OnEraseBkgnd(pDC);
    return TRUE;
}

void CXTVerScrollbar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)//不加此函数会出问题
{
	DrawImage(DLGDC, 0, 0);
	DrawImage(COMPDC, 0, 0);
}

//绘图
//uObject:[IN]为0在m_hDC上绘，为1在m_hDC和m_hCompDC绘(只在初始化时绘)
//uState:[IN]为0绘平常状态，1绘鼠标在上面，2绘鼠标按下
//uPart:[IN]为0绘上箭头，为1下箭头，为2中间部分，为3
void CXTVerScrollbar::DrawImage(int obj, int state, int part)
{
	HDC dc = (DLGDC == obj)?dc_:compDC_;

	switch(part)
	{
	case UPARRAW://上箭头
		{				
			BitBlt(dc, x_, y_, 15, 15, imageDC_, sx_ + state * 15, sy_, SRCCOPY);
			break;
		}
	case DOWNARRAW://下箭头
		{
			BitBlt(dc,  x_, y_ + cy_ - 15, 15, 15, imageDC_, sx_ + state * 15, sy_ + 36, SRCCOPY);
			break;
		}
	case THUMB:
		{
			if (thumbLen_ >= 20)
			{
				//中间部分.上
				BitBlt(dc, x_, y_ + thumbPos_, 15, 5, imageDC_, sx_ + state * 15, sy_ + 15, SRCCOPY);
				//中间部分.背景
				StretchBlt(dc, x_, y_ + thumbPos_ + 5, 15, thumbLen_ - 10, imageDC_, sx_ + state * 15, sy_ + 19, 15, 1, SRCCOPY);
				//中间部分.中
				BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_/2 - 5, 15, 10, imageDC_, sx_ + state * 15, sy_ + 20, SRCCOPY);
				//中间部分.上
				BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_ - 5, 15, 5, imageDC_, sx_ + state * 15, sy_ + 30, SRCCOPY);		
			}
			else  if (thumbLen_ >= 15)
			{
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_, 15, 5, imageDC_, sx_ + state * 15, sy_ + 15, SRCCOPY);
				//中间部分.背景
				::StretchBlt(dc, x_, y_ + thumbPos_ + 5, 15, thumbLen_ - 10, imageDC_, sx_ + state * 15, sy_ + 19, 15, 1, SRCCOPY);
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_ - 5, 15, 5, imageDC_, sx_ + state * 15, sy_ + 30, SRCCOPY);		
			}
			else if (thumbLen_ >= 5)
			{
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_, 15, 3, imageDC_, sx_ + state * 15, sy_ + 15, SRCCOPY);
				//中间部分.上
				::BitBlt(dc, x_, y_ + thumbPos_ + 3, 15, 3, imageDC_, sx_ + state * 15, sy_ + 33, SRCCOPY);		
			}

			break;
		}			
	case THUMB_BKG:
		{
			//中间部分.上
			::BitBlt(dc, x_, y_ + thumbPos_, 15, 5, imageDC_, sx_ + state * 15, sy_ + 15, SRCCOPY);
			//中间部分.背景
			::StretchBlt(dc, x_, y_ + thumbPos_ + 5, 15, thumbLen_ - 10, imageDC_, sx_ + state * 15, sy_ + 19, 15, 1, SRCCOPY);
			//中间部分.中
			::BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_/2 - 5, 15, 10, imageDC_, sx_ + state * 15, sy_ + 20, SRCCOPY);
			//中间部分.上
			::BitBlt(dc, x_, y_ + thumbPos_ + thumbLen_ - 5, 15, 5, imageDC_, sx_ + state * 15, sy_ + 30, SRCCOPY);
			//背景.上
			::StretchBlt(dc, x_, y_ + 15, 15, thumbPos_ - 15, imageDC_, sx_ + state * 15, sy_ + 35, 15, 1, SRCCOPY);
			//背景.下			
			::StretchBlt(dc, x_ , y_ + thumbPos_ + thumbLen_, 15, y_ + cy_ - 15 - y_ - thumbPos_ - thumbLen_, imageDC_, 
				sx_ + state * 15, sy_ + 35, 15, 1, SRCCOPY);
			break;
		}
	default:
		break;
	}
}

void CXTVerScrollbar::ScrollUp()
{
    list_->SendMessage(WM_VSCROLL, MAKELONG(SB_LINEUP,0), NULL);
    UpdateThumbPosition();
}

void CXTVerScrollbar::ScrollDown()
{
    list_->SendMessage(WM_VSCROLL, MAKELONG(SB_LINEDOWN,0), NULL);
    UpdateThumbPosition();
}

void CXTVerScrollbar::PageDown()
{
    list_->SendMessage(WM_VSCROLL, MAKELONG(SB_PAGEDOWN,0), NULL);
    UpdateThumbPosition();
}

void CXTVerScrollbar::PageUp()
{
    list_->SendMessage(WM_VSCROLL, MAKELONG(SB_PAGEUP,0), NULL);
    UpdateThumbPosition();
}

void CXTVerScrollbar::UpdateThumbPosition()
{
	int pos = list_->GetScrollPos(SB_VERT);	// 当前位置行数
	int limit = list_->GetScrollLimit(SB_VERT);	// 实际需要滚动的长度 = 实际宽度(Max) - 滚动条长

	if (0 != limit)
	{
		thumbLen_ = (int)ceil((double)cy_ * (cy_ - 15*2) / double(cy_ + limit));
		if (thumbLen_ < 5) thumbLen_ = 5;
		thumbPos_ = 15 + (int)ceil((double)pos * (cy_ - 15*2 - thumbLen_) / limit);
	}
	else
	{
		thumbLen_ = 0;
	}

	//中间部分
	thumb_.left   = x_;
	thumb_.top	  = y_ + thumbPos_;
	thumb_.right  = x_ + cx_;
	thumb_.bottom = y_ + thumbPos_ + thumbLen_;

	DrawImage(DLGDC, 0, UPARRAW);
	DrawImage(DLGDC, 0, DOWNARRAW);
	DrawImage(DLGDC, 0, THUMB_BKG);
	DrawImage(COMPDC, 0, UPARRAW);
	DrawImage(COMPDC, 0, DOWNARRAW);
	DrawImage(COMPDC, 0, THUMB_BKG);
}

bool CXTVerScrollbar::Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *xtDC)
{
    if (NULL == xtDC) return false;

    xtDC_ = xtDC;

	dc_      = xtDC_->GetHDC(WNDDC, 0);
	compDC_  = xtDC_->GetHDC(COMPDC, 0);
	imageDC_ = xtDC_->GetHDC(IMAGEDC, 0);

    // 自己
    x_  = x;
    y_  = y;
    cx_ = cx;
    cy_ = cy;
	
	// 图片位置
    sx_ = sx;
    sy_ = sy;

    // 向上箭头
    upArraw_.left	 = x_;
    upArraw_.top	 = y_;
    upArraw_.right	 = x_ + cx_;
    upArraw_.bottom	 = y_ + 15;

    // 向下箭头
	downArraw_.left	  = x_;
	downArraw_.top	  = y_ + cy_ - 15;
	downArraw_.right  = x_ + cx_;
	downArraw_.bottom = y_ + cy_;

    // 中间部分
    thumb_.left		  = x_;
    thumb_.top		  = y_ + thumbPos_;
    thumb_.right	  = x_ + cx_;
    thumb_.bottom	  = y_ + thumbPos_ + thumbLen_;

	return true;
}

void CXTVerScrollbar::ResetImage(int sx, int sy)
{
    if (-1 != sx) sx_ = sx;
    if (-1 != sy) sy_ = sy;

	imageDC_ = xtDC_->curImageDC_;

	UpdateThumbPosition();
}

void CXTVerScrollbar::LimitThumbPosition()
{
    CRect rc;
    GetClientRect(&rc);

    if ((thumbPos_ + thumbLen_) > (rc.bottom - 15))
        thumbPos_ = rc.bottom - 15 - thumbLen_;

    if (thumbPos_ < (rc.top + 15))
        thumbPos_ = rc.top + 15;
}
