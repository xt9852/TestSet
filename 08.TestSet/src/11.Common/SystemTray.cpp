
   
#include "stdafx.h"
#include "SystemTray.h"


IMPLEMENT_DYNAMIC(CSystemTray, CWnd)

UINT CSystemTray::m_nIDEvent = 4567;

void CSystemTray::ShowMenu(BOOL ShowMenuFlag)
{
    //根据参数不同设置是否具有菜单
    m_tnd.uID    = (ShowMenuFlag?uIDtemp:0);
}

BOOL CSystemTray::Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID)
{
    // 这个可以用于95以上的扳本
    VERIFY(m_bEnabled = ( GetVersion() & 0xff ) >= 4);
    if (!m_bEnabled) return FALSE;
    //保证windows通知消息是有效的
    //VERIFY(m_bEnabled = (pParent && ::IsWindow(pParent->GetSafeHwnd())));
    //if (!m_bEnabled) return FALSE;
    
    // 保证没有冲突
    ASSERT(uCallbackMessage >= WM_USER);
    // 托盘的提示信息不能超过64个字符
    ASSERT(_tcslen(szToolTip) <= 64);

    // 创造一个隐型的窗体
    CWnd::CreateEx(0, AfxRegisterWndClass(0), _T(""), WS_POPUP, 0,0,10,10, NULL, 0);

    // 初始化 NOTIFYICONDATA structure
    m_tnd.cbSize = sizeof(NOTIFYICONDATA);
    m_tnd.hWnd   = pParent->GetSafeHwnd()? pParent->GetSafeHwnd() : m_hWnd;
    m_tnd.uID    = uID;
    uIDtemp      = uID;
    m_tnd.hIcon  = icon;
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_tnd.uCallbackMessage = uCallbackMessage;
    _tcscpy(m_tnd.szTip, szToolTip);

    // 设置托盘的图标
    VERIFY(m_bEnabled = Shell_NotifyIcon(NIM_ADD, &m_tnd));
    return m_bEnabled;
}

CSystemTray::CSystemTray()
{
    //一开始就执行initialise（）函数
    Initialise();
}

CSystemTray::CSystemTray(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID)
{
    Initialise();
    Create(pParent, uCallbackMessage, szToolTip, icon, uID);
}

void CSystemTray::Initialise()
{
    memset(&m_tnd, 0, sizeof(m_tnd));
    m_bEnabled   = FALSE;
    m_bHidden    = FALSE;
    m_uIDTimer   = 0;
    m_hSavedIcon = NULL;
    m_DefaultMenuItemID = 0;
    m_DefaultMenuItemByPos = TRUE;

    m_pImageList = NULL;
}

CSystemTray::~CSystemTray()
{
    RemoveIcon();
    m_IconList.RemoveAll();
    DestroyWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray icon manipulation

void CSystemTray::MoveToRight()
{
    HideIcon();
    ShowIcon();
}

void CSystemTray::RemoveIcon()
{
    if (!m_bEnabled) return;

    m_tnd.uFlags = 0;
    Shell_NotifyIcon(NIM_DELETE, &m_tnd);
    m_bEnabled = FALSE;
}

void CSystemTray::HideIcon()
{
    if (m_bEnabled && !m_bHidden) {
        m_tnd.uFlags = NIF_ICON;
        Shell_NotifyIcon (NIM_DELETE, &m_tnd);
        m_bHidden = TRUE;
    }
}

void CSystemTray::ShowIcon()
{
    if (m_bEnabled && m_bHidden) {
        m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        Shell_NotifyIcon(NIM_ADD, &m_tnd);
        m_bHidden = FALSE;
    }
}

BOOL CSystemTray::SetIcon(HICON hIcon)
{
    if (!m_bEnabled) return FALSE;

    ::DestroyIcon(m_tnd.hIcon);

    m_tnd.uFlags = NIF_ICON;
    m_tnd.hIcon = hIcon;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

BOOL CSystemTray::SetIcon(LPCTSTR lpszIconName)
{
    HICON hIcon = AfxGetApp()->LoadIcon(lpszIconName);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetIcon(UINT nIDResource)
{
    HICON hIcon = AfxGetApp()->LoadIcon(nIDResource);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetStandardIcon(LPCTSTR lpIconName)
{
    HICON hIcon = LoadIcon(NULL, lpIconName);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetStandardIcon(UINT nIDResource)
{
    HICON hIcon = LoadIcon(NULL, MAKEINTRESOURCE(nIDResource));

    return SetIcon(hIcon);
}
 
HICON CSystemTray::GetIcon() const
{
    return (m_bEnabled)? m_tnd.hIcon : NULL;
}

BOOL CSystemTray::SetIconList(UINT uFirstIconID, UINT uLastIconID) 
{
    if (uFirstIconID > uLastIconID)
    {
        return FALSE;
    }

    UINT uIconArraySize = uLastIconID - uFirstIconID + 1;
    const CWinApp * pApp = AfxGetApp();
    ASSERT(pApp != 0);

    m_IconList.RemoveAll();

    try
    {
        for (UINT i = uFirstIconID; i <= uLastIconID; i++)
        {
            m_IconList.Add(pApp->LoadIcon(i));
        }
    }
    catch (CMemoryException *e)
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

BOOL CSystemTray::SetIconList(HICON* pHIconList, UINT nNumIcons)
{
    m_IconList.RemoveAll();

    try
    {
        for (UINT i = 0; i <= nNumIcons; i++)
        {
            m_IconList.Add(pHIconList[i]);
        }
    }
    catch (CMemoryException *e)
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

BOOL CSystemTray::SetImageList(CImageList *pImageList)
{
    if (NULL == pImageList) return FALSE;

    m_pImageList = pImageList;

    return TRUE;
}

BOOL CSystemTray::Animate(UINT nDelayMilliSeconds, int nNumSeconds /*=-1*/)
{
    StopAnimation();

    m_nCurrentIcon = 0;
    m_StartTime = COleDateTime::GetCurrentTime();
    m_nAnimationPeriod = nNumSeconds;
    m_hSavedIcon = GetIcon();

    // Setup a timer for the animation
    m_uIDTimer = SetTimer(m_nIDEvent, nDelayMilliSeconds, NULL);

    return (m_uIDTimer != 0);
}

BOOL CSystemTray::StepAnimation()
{
    HICON hTempIcon = NULL;

    if (NULL != m_pImageList)
    {
        m_nCurrentIcon++;

        if (m_nCurrentIcon >= m_pImageList->GetImageCount())
            m_nCurrentIcon = 0;

        hTempIcon = m_pImageList->ExtractIcon(m_nCurrentIcon);
    }
    else
    {
        if (!m_IconList.GetSize())
            return false;

        m_nCurrentIcon++;

        if (m_nCurrentIcon >= m_IconList.GetSize())
            m_nCurrentIcon = 0;

        hTempIcon = m_IconList[m_nCurrentIcon];
    }

    return SetIcon(hTempIcon);
}

BOOL CSystemTray::StopAnimation()
{
    BOOL bResult = FALSE;

    if (m_uIDTimer)
    {
        bResult = KillTimer(m_uIDTimer);
    }

    m_uIDTimer = 0;

    if (m_hSavedIcon)
    {
        SetIcon(m_hSavedIcon);
    }

    m_hSavedIcon = NULL;

    return bResult;
}


/////////////////////////////////////////////////////////////////////////////
// CSystemTray 工具提示文本控制部分

BOOL CSystemTray::SetTooltipText(LPCTSTR pszTip)
{
    if (!m_bEnabled) return FALSE;

    m_tnd.uFlags = NIF_TIP;
    _tcscpy(m_tnd.szTip, pszTip);

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

BOOL CSystemTray::SetTooltipText(UINT nID)
{
    CString strText;
    VERIFY(strText.LoadString(nID));

    return SetTooltipText(strText);
}

CString CSystemTray::GetTooltipText() const
{
    CString strText;

    if (m_bEnabled)
        strText = m_tnd.szTip;

    return strText;
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray notification window stuff

BOOL CSystemTray::SetNotificationWnd(CWnd* pWnd)
{
    if (!m_bEnabled) return FALSE;

    // Make sure Notification window is valid
    ASSERT(pWnd && ::IsWindow(pWnd->GetSafeHwnd()));

    m_tnd.hWnd = pWnd->GetSafeHwnd();
    m_tnd.uFlags = 0;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

CWnd* CSystemTray::GetNotificationWnd() const
{
    return CWnd::FromHandle(m_tnd.hWnd);
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray 菜单部分

BOOL CSystemTray::SetMenuDefaultItem(UINT uItem, BOOL bByPos)
{
    if ((m_DefaultMenuItemID == uItem) && (m_DefaultMenuItemByPos == bByPos)) 
        return TRUE;

    m_DefaultMenuItemID = uItem;
    m_DefaultMenuItemByPos = bByPos;

    CMenu menu, *pSubMenu;

    if (!menu.LoadMenu(m_tnd.uID)) return FALSE;

    if (!(pSubMenu = menu.GetSubMenu(0))) return FALSE;

    ::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

    return TRUE;
}

void CSystemTray::GetMenuDefaultItem(UINT& uItem, BOOL& bByPos)
{
    uItem = m_DefaultMenuItemID;
    bByPos = m_DefaultMenuItemByPos;
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray message handlers

BEGIN_MESSAGE_MAP(CSystemTray, CWnd)
    //{{AFX_MSG_MAP(CSystemTray)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSystemTray::OnTimer(UINT nIDEvent) 
{
    ASSERT(nIDEvent == m_nIDEvent);

    COleDateTime CurrentTime = COleDateTime::GetCurrentTime();
    COleDateTimeSpan period = CurrentTime - m_StartTime;

    if (m_nAnimationPeriod > 0 && m_nAnimationPeriod < period.GetTotalSeconds())
    {
        StopAnimation();
        return;
    }

    StepAnimation();
}

LRESULT CSystemTray::OnTrayNotification(UINT wParam, LONG lParam) 
{
    //Return quickly if its not for this tray icon
    if (wParam != m_tnd.uID)
        return 0L;

    CMenu menu, *pSubMenu;
    CWnd* pTarget = AfxGetMainWnd();

    // Clicking with right button brings up a context menu
    if (LOWORD(lParam) == WM_RBUTTONUP)
    {    
        if (!menu.LoadMenu(m_tnd.uID)) return 0;
        if (!(pSubMenu = menu.GetSubMenu(0))) return 0;

        // Make chosen menu item the default (bold font)
        ::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

        // Display and track the popup menu
        CPoint pos;
        GetCursorPos(&pos);

        pTarget->SetForegroundWindow();
        ::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, pTarget->GetSafeHwnd(), NULL);

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
        pTarget->PostMessage(WM_NULL, 0, 0);

        menu.DestroyMenu();
    } 
    else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
    {
        // double click received, the default action is to execute default menu item
        pTarget->SetForegroundWindow();  

        UINT uItem;
        if (m_DefaultMenuItemByPos)
        {
            if (!menu.LoadMenu(m_tnd.uID)) return 0;
            if (!(pSubMenu = menu.GetSubMenu(0))) return 0;
            uItem = pSubMenu->GetMenuItemID(m_DefaultMenuItemID);
        }
        else
            uItem = m_DefaultMenuItemID;
        
        pTarget->SendMessage(WM_COMMAND, uItem, 0);

        menu.DestroyMenu();
    }

    return 1;
}

LRESULT CSystemTray::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if (message == m_tnd.uCallbackMessage)
        return OnTrayNotification(wParam, lParam);

    return CWnd::WindowProc(message, wParam, lParam);
}

