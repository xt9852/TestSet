// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainFrm.h"
#include <time.h>

#pragma comment(lib, "dulib.lib")   // 界面库


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    return FALSE;
}

CMainFrame::CMainFrame()
    :wndManager_(NULL)
{
    currentPath_[0] = _T('\0');
    srand((unsigned)time(0));
}

CMainFrame::~CMainFrame()
{
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);
    SetMenu(NULL);

    GetCurrentPath();

    LoadSkin();

    return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    // unregister message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);
    bHandled = FALSE;
    return 1;
}

LRESULT CMainFrame::OnDirectUINotify(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    duBEGIN_MESSAGE_MAP(CMainFrame, wParam, lParam)
        duON_MESSAGE(windows_min,   DUM_BTNCLICK, &CMainFrame::OnMinClick)
        duON_MESSAGE(windows_close, DUM_BTNCLICK, &CMainFrame::OnCloseClick)
    duEND_MESSAGE_MAP()
    return 0;
}

LRESULT CMainFrame::OnMinClick(duPlugin * /*pPlugin*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    ShowWindow(SW_SHOWMINIMIZED);
    InvalidateRect(NULL,TRUE);
    return 0;
}

LRESULT CMainFrame::OnCloseClick(duPlugin * /*pPlugin*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    PostMessage(WM_CLOSE, NULL, NULL);
    return 0;
}

/**
 *\fn         GetCurrentPath()
 *\brief      得到程序的当前路径。
 *\return     无。
 */
void CMainFrame::GetCurrentPath()
{
    TCHAR path[MAX_PATH+1] = _T("");
    GetModuleFileName(GetModuleHandle(NULL), path, MAX_PATH);
    PathRemoveFileSpec(path);
    _tcscpy_s(currentPath_, MAX_PATH, path);
}

/**
 *\fn         LoadSkin()
 *\brief      加载DirectUI皮肤。
 *\return     是否成功,0成功，其它失败
 */
int CMainFrame::LoadSkin()
{
    TCHAR path[MAX_PATH+1] = _T("");
    _stprintf_s(path, MAX_PATH, _T("%s\\skin\\DefaultSkin\\FileUpdate\\FileUpdateSkin.zip"), currentPath_);

    wndManager_ = LoadStyleZipW(path);
    if (NULL == wndManager_)
    {
        TCHAR info[MAX_PATH + 1] = _T("");
        _stprintf_s(info, sizeof(info)/sizeof(info[0]), _T("加载界面库失败,%s"), path);
        MessageBox(info);
        return -1;
    }

    ATLTRACE(_T("加载界面库成功,%s"), path);

    WindowManager_Attach(wndManager_, m_hWnd, _T("Update_Window"));

    duHeaderCtrl *pHeaderCtrl = (duHeaderCtrl *)GetPluginByName(m_hWnd, _T("headerctrl_0"));
    pHeaderCtrl->InsertItem(0, _T("文件名称"), FALSE, 280, NULL);
    pHeaderCtrl->InsertItem(1, _T("速度"),     FALSE,  75, NULL);
    pHeaderCtrl->InsertItem(2, _T("下载进度"), FALSE, 150, NULL);

    duListCtrl *listCtrl = (duListCtrl*)GetPluginByName(m_hWnd, _T("listctrl_0"));

    TCHAR name1[MAX_PATH + 1] = _T("");
    TCHAR name2[MAX_PATH + 1] = _T("");
    TCHAR name3[MAX_PATH + 1] = _T("");
    TCHAR info1[MAX_PATH + 1] = _T("");
    TCHAR info2[MAX_PATH + 1] = _T("");

    for (int i = 0; i < 10; i++)
    {
        int pos = rand() % 101;
        _stprintf_s(info1, sizeof(info1) / sizeof(info1[0]), _T("%d%%"), pos);
        _stprintf_s(info2, sizeof(info2) / sizeof(info2[0]), _T("%dKB/S"), rand());
        _stprintf_s(name1, sizeof(name1) / sizeof(name1[0]), _T("software_download_%d"), i);
        _stprintf_s(name2, sizeof(name2) / sizeof(name2[0]), _T("file_download_progress_%d"), i);
        _stprintf_s(name3, sizeof(name3) / sizeof(name3[0]), _T("file_download_progress_rate_%d"), i);

        duLayout *pLayout = (duLayout*)listCtrl->InsertLine(0, _T("listctrl_0_template_"));

        if (NULL == pLayout)
        {
            continue;
        }

        duStatic *stat = (duStatic*)pLayout->GetPluginByName(name1);

        if (NULL == stat)
        {
            continue;
        }

        stat->SetText(info2);

        duProgress *progress = (duProgress*)pLayout->GetPluginByName(name2);

        if (NULL == progress)
        {
            continue;
        }

        progress->SetPos(rand() % 101);

        stat = (duStatic*)pLayout->GetPluginByName(name3);

        if (NULL == stat)
        {
            continue;
        }

        stat->SetText(info1);
    }

    return 0;
}