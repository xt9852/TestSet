/*************************************************
 * VS Addin
 * Copyright (C) XT. Co., Ltd.
 * File name:       SubWnd.h
 * Author:          zht
 * Version:         1.0.0
 * Date:            2014.9.4
 * Description:     VS插件窗体基类实现
*************************************************/

#include "stdafx.h"
#include "SubWnd.h"

#define S_L 5   // 左边框保留
#define S_R 5   // 右边框保留
#define S_T 5   // 上边框保留
#define S_B 5   // 下边框保留
#define S_M 5   // 中间框保留

CAddinWnd::CAddinWnd()
    :hImageList_(NULL),
    hCursorDragWnd_(NULL),
    hCursorDragFile_(NULL),
    wnd_(NULL),
    config_(NULL),
    serverInfo_(NULL),
    serverCount_(0),
    wndWidth_(0),
    treeWidth_(0),
    wndHeight_(0),
    moveTree_(false),
    dragFile_(false)
{
    projectName_[0] = '\0';
}

CAddinWnd::~CAddinWnd()
{
    if (comboServer_.IsWindow())
    {
        comboServer_.DestroyWindow();
    }

    if (comboConnect_.IsWindow())
    {
        comboConnect_.DestroyWindow();
    }

    if (NULL != serverInfo_)
    {
        delete[] serverInfo_;
    }
}

int CAddinWnd::create(HINSTANCE instance, CMessageMap *map, HWND wnd, int icon, int cursorDrag, int cursorCopy)
{
    if (NULL == map) return -1;

    wnd_ = wnd;

    hCursorDragWnd_ = ::LoadCursor(instance, MAKEINTRESOURCE(cursorDrag));//IDC_CURSOR_DRAG_HZ
    hCursorDragFile_ = ::LoadCursor(instance, MAKEINTRESOURCE(cursorCopy));//IDC_CURSOR_COPY
    hImageList_ = ImageList_LoadImage(instance, MAKEINTRESOURCE(icon), //IDB_BITMAP_ICON
        16, 0, RGB(0,0,255), IMAGE_BITMAP, ILC_MIRROR);

    RECT rc = {0};
    comboServer_.m_pObject = map;
    comboServer_.m_dwMsgMapID = 1;
    comboServer_.m_lpszClassName = WC_COMBOBOX;
    comboServer_.Create(wnd, rc, _T(""), WS_VISIBLE|WS_CHILD|CBS_AUTOHSCROLL|CBS_DROPDOWNLIST|CBS_SORT);

    comboConnect_.m_pObject = map;
    comboConnect_.m_dwMsgMapID = 2;
    comboConnect_.m_lpszClassName = WC_COMBOBOX;
    comboConnect_.Create(wnd, rc, _T(""), WS_VISIBLE|WS_CHILD|CBS_AUTOHSCROLL|CBS_DROPDOWNLIST|CBS_SORT);

    return 0;
}

void CAddinWnd::resizeWnd(int cx, int cy, bool dragWnd)
{
    treeWidth_ = (cx - S_L - S_M - S_R) / 2;

    wndWidth_ = cx;
    wndHeight_ = cy;

    comboConnect_.SetWindowPos(NULL, S_L, S_T, treeWidth_, 280, SWP_NOZORDER | SWP_NOACTIVATE);
    comboServer_.SetWindowPos(NULL, S_L + treeWidth_ + S_M, S_T, treeWidth_, 280, SWP_NOZORDER | SWP_NOACTIVATE);
}

void CAddinWnd::mouseMove(int x, int y)
{
    // 在tree和list中线的坚线部分
    if (x >= (treeWidth_+5) && x <= (treeWidth_+10) && y >= 25 && y <= (wndHeight_-5))
    {
        ::SetCursor(hCursorDragWnd_);
    }
}

int CAddinWnd::addServer()
{
    char text[512] = {0};
    serverCount_ = config_->getServerCount();

    serverInfo_ = new ServerInfo[serverCount_];

    for (int i = 0; i < serverCount_; i++)
    {
        config_->getServerParam(i, serverInfo_[i].serverAddr, serverInfo_[i].serverPort, 
            serverInfo_[i].username, serverInfo_[i].password, serverInfo_[i].port_map_count);
    }

    comboServer_.SetRedraw(FALSE);

    int index = 0;

    for (int i = 0; i < serverCount_; i++)
    {
        _snprintf_s(text, sizeof(text)-1, "ssh://%s@%s:%d", serverInfo_[i].username, 
            serverInfo_[i].serverAddr, serverInfo_[i].serverPort);

        index = comboServer_.SendMessage(CB_ADDSTRING, 0, (LPARAM)text);
        comboServer_.SendMessage(CB_SETITEMDATA, index, (LPARAM)i);
    }

    for (int i = 0; i < serverCount_; i++)
    {
        _snprintf_s(text, sizeof(text)-1, "sftp://%s@%s:%d", serverInfo_[i].username, 
            serverInfo_[i].serverAddr, serverInfo_[i].serverPort);

        index = comboServer_.SendMessage(CB_ADDSTRING, 0, (LPARAM)text);
        comboServer_.SendMessage(CB_SETITEMDATA, index, (LPARAM)i);
    }

    comboServer_.SetRedraw(TRUE);

    return 0;
}

int CAddinWnd::connectServer()
{
    char text[512] = {0};
    int curSel = comboServer_.SendMessage(CB_GETCURSEL, 0, 0L);
    comboServer_.SendMessage(CB_GETLBTEXT, curSel, LPARAM(text));
    int serverId = comboServer_.SendMessage(CB_GETITEMDATA, curSel, NULL);

    int index = comboConnect_.SendMessage(CB_ADDSTRING, 0, (LPARAM)text);
    comboConnect_.SendMessage(CB_SETCURSEL, index, NULL);

    void *data = NULL;
    if (curSel > serverCount_)
    {
        addTerminal(serverId, &data);
    }
    else
    {
        addBrowse(serverId, &data);
    }

    comboConnect_.SendMessage(CB_SETITEMDATA, index, (LPARAM)data);

    return 0;
}

int CAddinWnd::showServer()
{
    int curSel = comboConnect_.SendMessage(CB_GETCURSEL, 0, 0L);
    char *text = (char*)comboConnect_.SendMessage(CB_GETITEMDATA, curSel, NULL);

    ATLTRACE2(text);
    ATLTRACE2("\n");

    return 0;
}

int CAddinWnd::addBrowse(int serverId, void **data)
{
    char *text = new char[128];
    sprintf_s(text, 127, "Browse_%d", serverId);

    *data = text;
    return 0;
}

int CAddinWnd::addTerminal(int serverId, void **data)
{
    char *text = new char[128];
    sprintf_s(text, 127, "Terminal_%d", serverId);

    *data = text;
    return 0;
}

