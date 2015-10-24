#include "StdAfx.h"
#include "XTDialog.h"

CXTDialog::CXTDialog()
	:heigh_(20)
{
}

CXTDialog::CXTDialog(UINT nIDTemplate, CWnd* pParentWnd/* = NULL*/)
	:CDialog(nIDTemplate, pParentWnd),
	heigh_(20)
{
}


CXTDialog::~CXTDialog()
{
}

BEGIN_MESSAGE_MAP(CXTDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CXTDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	if (point.y < heigh_)
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnMouseMove(nFlags, point);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CXTDialog::OnPaint()
{
	if (IsIconic())
	{
		/*
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		*/
	}
	else
	{		
		//CDialog::OnPaint();
		CPaintDC dc(this);
		PaintWindowlessControls(&dc);

		if (NULL == dc_ || NULL == compDC_)	return;

		DrawDlg();
	}
}

BOOL CXTDialog::OnEraseBkgnd(CDC* pDC)
{
	//return CDialog::OnEraseBkgnd(pDC);
	return TRUE;
}

// 设置窗体，也可自己调用SetDlgRect,然后再设置XTDC

// cx		[IN] 窗体宽
// cy		[IN] 窗体高
// nId		[IN] 窗体图片ID
// pstrBmp	]IN] 窗体图片路径
// hDll		[IN] 从DLL中载入资源
void CXTDialog::InitBkgBmp(int cx, int cy, int cr, int id)
{
	SetDlgRect(cx, cy, cr);
	SetBkgBmp(id, NULL);
}

void CXTDialog::SetDlgRect(int cx, int cy, int cr)
{
	heigh_ = cy;
	
	RECT rcWnd;
	GetWindowRect(&rcWnd);
	MoveWindow(rcWnd.left, rcWnd.top, cx, cy);
	HRGN hRgn = CreateRoundRectRgn(0, 0, cx, cy, cr, cr);
	SetWindowRgn(hRgn, TRUE);
	CenterWindow();

	GetClientRect(&rcWnd);
	rectList_.push_back(rcWnd);
}

void CXTDialog::SetBkgBmp(int id, HMODULE module)
{
	dc_ = xtDC_.Init(module, m_hWnd);
	compDC_ = xtDC_.AddCompDC(0);
	imageDC_ = xtDC_.AddPngDC(0, id);
	
	int cx = 0;
	int cy = 0;
	xtDC_.GetBmpRect(0, cx, cy);

	BitBlt(compDC_, 0, 0, cx, cy, imageDC_, 0, 0, SRCCOPY);
}

CRect CXTDialog::OutputText(int x, int y, const char *text)
{
	if (NULL != text)
	{
		CRect rcText(x,y,0,0);
		DrawText(compDC_, text, strlen(text), &rcText, DT_CALCRECT);	// 计算文字的范围
		DrawText(compDC_, text, strlen(text), &rcText, DT_LEFT);
		BitBlt(dc_, x, y, rcText.Width(), rcText.Height(), compDC_, x, y, SRCCOPY);

		return rcText;
	}

	return CRect(0,0,0,0);
}

void CXTDialog::ClearText(CRect rcText, HDC bkgDC)
{
	BitBlt(compDC_, rcText.left, rcText.top, rcText.Width(), rcText.Height(), bkgDC, rcText.left, rcText.top, SRCCOPY);
}

void CXTDialog::DrawDlg()
{
	RECT_LIST::iterator iter = rectList_.begin();

	for (; iter != rectList_.end(); ++iter)
	{
		RECT rc = *iter;

		BitBlt(dc_, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
			compDC_, rc.left, rc.top, SRCCOPY);		
	}
}

void CXTDialog::DelRect(int x, int y, int cx, int cy)
{
	CRect rcDel(x, y, x + cx, y + cy);

	RECT_LIST tmpeRectList;

	RECT_LIST::iterator iter = rectList_.begin();

	for (; iter != rectList_.end(); ++iter)
	{
		UpdateRect(*iter, rcDel, &tmpeRectList);
	}

	rectList_.clear();

	rectList_ = tmpeRectList;
}

// 1,  rcDel在rcSrc左边
// 2,  rcDel在rcSrc左边中
// 3,  rcDel在rcSrc坚过
// 4,  rcDel在rcSrc中
// 5,  rcDel在rcSrc右边中
// 6,  rcDel在rcSrc右边

// 7,  rcDel在rcSrc上边
// 8,  rcDel在rcSrc上边中
// 9,  rcDel在rcSrc横过
// 10, rcDel在rcSrc中(同4)
// 11, rcDel在rcSrc下边中
// 12, rcDel在rcSrc下边

// 13, rcDel在rcSrc左上角
// 14, rcDel在rcSrc右上角
// 15, rcDel在rcSrc右下角
// 16, rcDel在rcSrc左下角

// 17, rcSrc在rcDel中
// 18, rcDel与rcSrc不相交

void CXTDialog::UpdateRect(CRect rcSrc, CRect rcDel, RECT_LIST *rectList)
{
	if (NULL == rectList) return;

	POINT ptSrcLeftTop		= {rcSrc.left,  rcSrc.top};
	POINT ptSrcRightTop		= {rcSrc.right, rcSrc.top};
	POINT ptSrcLeftBottom	= {rcSrc.left,  rcSrc.bottom};
	POINT ptSrcRightBottom	= {rcSrc.right, rcSrc.bottom};

	POINT ptDelLeftTop		= {rcDel.left,  rcDel.top};
	POINT ptDelRightTop		= {rcDel.right, rcDel.top};
	POINT ptDelLeftBottom	= {rcDel.left,  rcDel.bottom};
	POINT ptDelRightBottom	= {rcDel.right, rcDel.bottom};

	BOOL bDelOnSrcLeftTop		= rcDel.PtInRect(ptSrcLeftTop);
	BOOL bDelOnSrcRightTop		= rcDel.PtInRect(ptSrcRightTop);
	BOOL bDelOnSrcLeftBottom	= rcDel.PtInRect(ptSrcLeftBottom);
	BOOL bDelOnSrcRightBottom	= rcDel.PtInRect(ptSrcRightBottom);

	BOOL bSrcOnDelLeftTop		= rcSrc.PtInRect(ptDelLeftTop);
	BOOL bSrcOnDelRightTop		= rcSrc.PtInRect(ptDelRightTop);
	BOOL bSrcOnDelLeftBottom	= rcSrc.PtInRect(ptDelLeftBottom);
	BOOL bSrcOnDelRightBottom	= rcSrc.PtInRect(ptDelRightBottom);

	// 1,  rcDel在rcSrc左边
	if (bDelOnSrcLeftTop && bDelOnSrcLeftBottom && !bDelOnSrcRightTop && !bDelOnSrcRightBottom)
	{
		RECT rc = {rcDel.right, rcSrc.top, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc);
	}
	// 2,  rcDel在rcSrc左边中
	else if (bSrcOnDelLeftTop && bSrcOnDelLeftBottom && !bSrcOnDelRightTop && !bSrcOnDelRightBottom)
	{
		RECT rc1 = {rcSrc.left,  rcSrc.top,    rcSrc.right, rcDel.top};
		RECT rc2 = {rcDel.right, rcDel.top,    rcSrc.right, rcDel.bottom};
		RECT rc3 = {rcSrc.left,  rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
		rectList->push_back(rc3);
	}
	// 3,  rcDel在rcSrc坚过
	else if (!bDelOnSrcLeftTop && !bDelOnSrcLeftBottom && !bDelOnSrcRightTop && !bDelOnSrcRightBottom &&
		!bSrcOnDelLeftTop && !bSrcOnDelLeftBottom && !bSrcOnDelRightTop && !bSrcOnDelRightBottom &&
		rcDel.top < rcSrc.top && rcDel.bottom > rcSrc.bottom && rcDel.left > rcSrc.left && rcDel.right < rcDel.right)
	{
		RECT rc1 = {rcSrc.left,  rcSrc.top,    rcDel.left,  rcSrc.top};
		RECT rc2 = {rcDel.right, rcSrc.top,    rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
	}
	// 4,  rcDel在rcSrc中
	else if (bSrcOnDelLeftTop && bSrcOnDelLeftBottom && bSrcOnDelRightTop && bSrcOnDelRightBottom)
	{
		RECT rc1 = {rcSrc.left, rcSrc.top,    rcSrc.right, rcDel.top};
		RECT rc2 = {rcSrc.left, rcDel.top,    rcDel.left,  rcDel.bottom};
		RECT rc3 = {rcDel.right, rcDel.top,   rcSrc.right, rcDel.bottom};
		RECT rc4 = {rcSrc.left, rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
		rectList->push_back(rc3);
		rectList->push_back(rc4);
	}
	// 5,  rcDel在rcSrc右边中
	else if (!bSrcOnDelLeftTop && !bSrcOnDelLeftBottom && bSrcOnDelRightTop && bSrcOnDelRightBottom)
	{
		RECT rc1 = {rcSrc.left, rcSrc.top,    rcSrc.right, rcDel.top};
		RECT rc2 = {rcSrc.left, rcDel.top,    rcDel.left,  rcDel.bottom};
		RECT rc3 = {rcSrc.left, rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
		rectList->push_back(rc3);
	}
	// 6,  rcDel在rcSrc右边
	else if (!bDelOnSrcLeftTop && !bDelOnSrcLeftBottom && bDelOnSrcRightTop && bDelOnSrcRightBottom)
	{
		RECT rc = {rcSrc.left, rcSrc.top, rcDel.left, rcSrc.bottom};
		rectList->push_back(rc);
	}
	// 7,  rcDel在rcSrc上边
	else if (bDelOnSrcLeftTop && !bDelOnSrcLeftBottom && bDelOnSrcRightTop && !bDelOnSrcRightBottom)
	{
		RECT rc = {rcSrc.left, rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc);
	}
	// 8,  rcDel在rcSrc上边中
	else if (bSrcOnDelLeftTop && !bSrcOnDelLeftBottom && bSrcOnDelRightTop && !bSrcOnDelRightBottom)
	{
		RECT rc1 = {rcSrc.left,  rcSrc.top,    rcDel.left,  rcDel.bottom};
		RECT rc2 = {rcDel.right, rcSrc.top,    rcSrc.right, rcDel.bottom};
		RECT rc3 = {rcSrc.left,  rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
		rectList->push_back(rc3);
	}
	// 9,  rcDel在rcSrc横过
	else if (!bDelOnSrcLeftTop && !bDelOnSrcLeftBottom && !bDelOnSrcRightTop && !bDelOnSrcRightBottom &&
		!bSrcOnDelLeftTop && !bSrcOnDelLeftBottom && !bSrcOnDelRightTop && !bSrcOnDelRightBottom &&
		rcDel.top > rcSrc.top && rcDel.bottom < rcSrc.bottom && rcDel.left < rcSrc.left && rcDel.right > rcDel.right)
	{
		RECT rc1 = {rcSrc.left, rcSrc.top,    rcSrc.right, rcDel.top};
		RECT rc2 = {rcSrc.left, rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
	}
	// 11, rcDel在rcSrc下边中
	else if (!bSrcOnDelLeftTop && bSrcOnDelLeftBottom && !bSrcOnDelRightTop && bSrcOnDelRightBottom)
	{
		RECT rc1 = {rcSrc.left,  rcSrc.top,    rcSrc.right, rcDel.top};
		RECT rc2 = {rcSrc.left,  rcDel.bottom, rcDel.left,  rcSrc.bottom};
		RECT rc3 = {rcDel.right, rcDel.top,    rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
		rectList->push_back(rc3);
	}
	// 12, rcDel在rcSrc下边
	else if (!bDelOnSrcLeftTop && bDelOnSrcLeftBottom && !bDelOnSrcRightTop && bDelOnSrcRightBottom)
	{
		RECT rc = {rcSrc.left, rcSrc.top, rcSrc.right, rcDel.top};
		rectList->push_back(rc);
	}
	// 13, rcDel在rcSrc左上角
	else if (bDelOnSrcLeftTop && !bDelOnSrcLeftBottom && !bDelOnSrcRightTop && !bDelOnSrcRightBottom)
	{
		RECT rc1 = {rcDel.right, rcSrc.top,    rcSrc.right, rcDel.bottom};
		RECT rc2 = {rcSrc.left,  rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
	}
	// 14, rcDel在rcSrc右上角
	else if (!bDelOnSrcLeftTop && !bDelOnSrcLeftBottom && bDelOnSrcRightTop && !bDelOnSrcRightBottom)
	{
		RECT rc1 = {rcSrc.left, rcSrc.top,    rcDel.left,  rcDel.bottom};
		RECT rc2 = {rcSrc.left, rcDel.bottom, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
	}
	// 15, rcDel在rcSrc右下角
	else if (!bDelOnSrcLeftTop && !bDelOnSrcLeftBottom && !bDelOnSrcRightTop && bDelOnSrcRightBottom)
	{
		RECT rc1 = {rcSrc.left, rcSrc.top, rcSrc.right, rcDel.top};
		RECT rc2 = {rcSrc.left, rcDel.top, rcDel.left,  rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
	}
	// 16, rcDel在rcSrc左下角
	else if (!bDelOnSrcLeftTop && bDelOnSrcLeftBottom && !bDelOnSrcRightTop && !bDelOnSrcRightBottom)
	{
		RECT rc1 = {rcSrc.left,  rcSrc.top, rcSrc.right, rcDel.top};
		RECT rc2 = {rcDel.right, rcDel.top, rcSrc.right, rcSrc.bottom};
		rectList->push_back(rc1);
		rectList->push_back(rc2);
	}
	// 17, rcSrc在rcDel中
	else if (bDelOnSrcLeftTop && bDelOnSrcLeftBottom && bDelOnSrcRightTop && bDelOnSrcRightBottom)
	{
	}
	// 18, rcDel与rcSrc不相交
	else
	{
		rectList->push_back(rcSrc);
	}
}

