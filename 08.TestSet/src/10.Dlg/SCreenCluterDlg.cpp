/********************************************************************
File Name:  SCreenCluterDlg.cpp
Created:	2008/05/22  22:5:2008    15:23
Author:		Alan Chen
Copy Right (C) Beijing CO-OPLAND Technology Ltd. 1999-2008 All
Right Reserved.

Desc:   	Full screen culter h file.
*********************************************************************/

#include "stdafx.h"
#include "SCreenCluterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSCreenCluterDlg 对话框

IMPLEMENT_DYNAMIC(CSCreenCluterDlg, CDialog)
CSCreenCluterDlg::CSCreenCluterDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSCreenCluterDlg::IDD, pParent),
    m_pDCScr(NULL),
    m_dwStage(NOT_SEL)

{
    m_ptHintPosition.x = 50;
    m_ptHintPosition.y = 150;
    m_strHintString = _T("选中需要截屏的区域后\n双击或者按回车完成选择!\n右健或者按下ESC取消截屏！");
}

CSCreenCluterDlg::~CSCreenCluterDlg()
{
    m_imgScr.ReleaseDC();
}

void CSCreenCluterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSCreenCluterDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CSCreenCluterDlg 消息处理程序

BOOL CSCreenCluterDlg::PreCreateWindow(CREATESTRUCT& cs)
{
    CRect rectDesktop;
    CWnd *pDesktopWnd = CWnd::GetDesktopWindow();
    pDesktopWnd->GetWindowRect(rectDesktop);

    cs.cx = rectDesktop.Width();
    cs.cy = rectDesktop.Height();

    return CDialog::PreCreateWindow(cs);
}

void CSCreenCluterDlg::PreInitDialog()
{
    CWnd *pDesktopWnd = CWnd::GetDesktopWindow();
    CDC *pDesktopDC = pDesktopWnd->GetDC();

    // Get screen 
    CRect rectDesktop;
    pDesktopWnd->GetWindowRect(rectDesktop);
    m_dwWidth = rectDesktop.Width();
    m_dwHeight = rectDesktop.Height();

    // Create back buffer
    m_imgScr.Create(m_dwWidth, m_dwHeight, pDesktopDC->GetDeviceCaps(BITSPIXEL));

    // Create back dc
    m_pDCScr = CDC::FromHandle( m_imgScr.GetDC());

    // Screen capture
    if (m_pDCScr)
        m_pDCScr->BitBlt(0, 0, m_dwWidth, m_dwHeight, pDesktopDC, 0, 0, SRCCOPY);

    CDialog::PreInitDialog();
}

BOOL CSCreenCluterDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Fullof screen
    SetWindowPos(&wndTop, 0, 0, m_dwWidth, m_dwHeight, SWP_SHOWWINDOW);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CSCreenCluterDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // Draw screen cap
    if (m_pDCScr)
        dc.BitBlt(0, 0, m_dwWidth, m_dwHeight, m_pDCScr, 0, 0, SRCCOPY);

    if (NOT_SEL != m_dwStage)
    {
        dc.Draw3dRect(m_ptStart.x, 
            m_ptStart.y, 
            m_ptEnd.x - m_ptStart.x, 
            m_ptEnd.y - m_ptStart.y,
            RGB(0, 255, 0), RGB(255, 0, 0));
    }

    CRect rect;
    dc.SetTextColor(RGB(0, 0, 0));
    dc.SetBkMode(TRANSPARENT);

    rect.left = m_ptHintPosition.x;
    rect.top = m_ptHintPosition.y;
    rect.right = m_dwWidth;
    rect.bottom = m_dwHeight;
    dc.DrawText(m_strHintString, rect, DT_LEFT);
}

void CSCreenCluterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    switch(m_dwStage)
    {
    case NOT_SEL:
        m_ptStart = point;
        m_ptEnd = point;
        m_dwStage = SEL_START;
        Invalidate(FALSE);
        break;
    case SEL_START:
        m_ptEnd = point;
        m_dwStage = SEL_END;
        Invalidate(FALSE);
        break;
    }

    CDialog::OnLButtonDown(nFlags, point);
}

void CSCreenCluterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    if (point.x < (INT)m_dwWidth / 2)
    {
        m_ptHintPosition.x = m_dwWidth - 200;
    }
    else
    {
        m_ptHintPosition.x = 50;
    }

    if (SEL_START == m_dwStage)
    {
        m_ptEnd = point;

        Invalidate(FALSE);
    }

    CDialog::OnMouseMove(nFlags, point);
}

void CSCreenCluterDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    if (SEL_END == m_dwStage)
        PostMessage(WM_COMMAND, IDOK);

    CDialog::OnLButtonDblClk(nFlags, point);
}

void CSCreenCluterDlg::OnOK()
{
    if (SEL_END != m_dwStage)
    {
        return;
    }

    // Save Result;
    CRect rectSRC;
    rectSRC.left = min(m_ptEnd.x, m_ptStart.x);
    rectSRC.top = min(m_ptEnd.y, m_ptStart.y);
    rectSRC.right = max(m_ptEnd.x, m_ptStart.x);
    rectSRC.bottom = max(m_ptEnd.y, m_ptStart.y);

    CRect rectDest;
    rectDest.left = 0;
    rectDest.top = 0;
    rectDest.right = rectSRC.Width();
    rectDest.bottom = rectSRC.Height();

    CPoint ptStartSrc;
    ptStartSrc.x = rectSRC.left;
    ptStartSrc.y = rectSRC.top;

    m_imgResult.Create(rectSRC.Width(),
        rectSRC.Height(),
        m_imgScr.GetBPP());
    m_imgScr.BitBlt(m_imgResult.GetDC(),
        rectDest,
        ptStartSrc, SRCCOPY);
    m_imgResult.ReleaseDC();

    CDialog::OnOK();
}
