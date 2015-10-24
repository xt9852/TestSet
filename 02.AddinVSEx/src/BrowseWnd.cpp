/*************************************************
 * VS Addin
 * Copyright (C) XT. Co., Ltd.
 * File name:       BrowseWnd.cpp
 * Author:          zht
 * Version:         1.0.0
 * Date:            2014.9.4
 * Description:     VS插件的浏览窗体实现
****************************************F*********/

#include "stdafx.h"
#include "BrowseWnd.h"
#include "11.Common\StrConver.h"
#include <io.h>
#include <ShlObj.h>

CBrowseWnd* CBrowseWnd::cur_ = NULL; // 当前显示的浏览器

/**
 *\fn           void saveFileCallback(void *param, const char *filename)
 *\brief        保存文件时VS回调
 *\param[in]    void * param 自定时参数
 *\param[in]    const char * filename 文件名
 *\return       void 无
 */
void saveFileCallback(void * /*param*/, const char *filename)
{
    CBrowseWnd::cur_->uploadFile(filename);
}

/**
 *\fn        int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
 *\brief     列表排序比较回调函数
 *\param[in] LPARAM lParam1 itemId1
 *\param[in] LPARAM lParam2 itemId2
 *\param[in] LPARAM lParamSort subitemId
 *\return    int CALLBACK 0成功,其它失败
 */
int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    if (NULL == CBrowseWnd::cur_) return 0;

    return CBrowseWnd::cur_->sortList(lParam1, lParam2, lParamSort);
}


CBrowseWnd::CBrowseWnd()
    :x_(0),
    y_(0),
    wndWidth_(0),
    wndHeight_(0),
    treeWidth_(0),
    dragWnd_(false),
    dragFile_(false),
    processExpand_(false),
    tempPath_(NULL),
    open_file_cb_(NULL),
    output_text_cb_(NULL),
    wnd_(NULL),
    hImageList_(NULL),
    hCursorDragWnd_(NULL),
    hCursorDragFile_(NULL)
{
    type_ = SUB_TYPE_BROWSE;
    memset(&ssh_param_, 0, sizeof(ssh_param_));
}

CBrowseWnd::~CBrowseWnd()
{
    destroy();

    mapExtImage_.clear();
    mapLocalRemoteFile.clear();
}

/**
 *\fn           void create(CMessageMap *map, int msgMapId, HWND wnd, RECT *rc, 
 *\                         int treeWidth, HIMAGELIST imageList, 
 *\                         HCURSOR dragWnd, HCURSOR dragFile)
 *\brief        创建窗窗体
 *\param[in]    CMessageMap * map 消息循环
 *\param[in]    int msgMapId 消息循环ID
 *\param[in]    HWND wnd 主窗体
 *\param[in]    RECT * rc 位置
 *\param[in]    int treeWidth 树控件宽
 *\param[in]    HIMAGELIST imageList 图片列表
 *\param[in]    HCURSOR dragWnd 拖动窗体光标
 *\param[in]    HCURSOR dragFile 拖动文件光标
 *\return       void 无
 */
void CBrowseWnd::create(CMessageMap *map, int msgMapId, HWND wnd, RECT *rc, 
    int treeWidth, HIMAGELIST imageList, HCURSOR dragWnd, HCURSOR dragFile)
{
    x_ = rc->left;
    y_ = rc->top;
    wnd_ = wnd;
    wndWidth_ = rc->right - rc->left;
    wndHeight_ = rc->bottom - rc->top;
    treeWidth_ = treeWidth;
    hImageList_ = imageList;
    hCursorDragWnd_ = dragWnd;
    hCursorDragFile_ = dragFile;

    // 树控件
    tree_.m_pObject = map;
    tree_.m_dwMsgMapID = msgMapId++;
    tree_.m_lpszClassName = WC_TREEVIEW;

    RECT wndRc = *rc;
    wndRc.left   = rc->left;
    wndRc.right  = rc->left + treeWidth_;
    wndRc.top    = rc->top;
    wndRc.bottom = rc->bottom - 20 - S_MB;

    tree_.Create(wnd, wndRc, _T(""), WS_VISIBLE | WS_CHILD | TVS_LINESATROOT | 
        TVS_HASLINES | TVS_EDITLABELS | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, 
        WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES);

    tree_.SendMessage(TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)imageList);

    // 列表控件
    wndRc.left   = rc->left + treeWidth_ + S_ML;
    wndRc.right  = rc->right;
    wndRc.top    = rc->top;
    wndRc.bottom = rc->bottom - 20 -S_MB;

    list_.m_pObject = map;
    list_.m_dwMsgMapID = msgMapId++;
    list_.m_lpszClassName = WC_LISTVIEW;

    list_.Create(wnd, wndRc, _T(""), WS_VISIBLE | WS_CHILD | LVS_EDITLABELS |
        LVS_REPORT | LVS_SHOWSELALWAYS, 
        WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES);

    DWORD dwStyle = list_.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) | 
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

    list_.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
    list_.SendMessage(LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)imageList);

    // 列表控件头列
    LV_COLUMN colmn = {0};
    colmn.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM; // 风格
    colmn.cx = 310;
    colmn.pszText = _T("name");
    list_.SendMessage(LVM_INSERTCOLUMN, 0, (LPARAM)&colmn);

    colmn.cx = 80;
    colmn.pszText = _T("size");
    list_.SendMessage(LVM_INSERTCOLUMN, 1, (LPARAM)&colmn);

    colmn.cx = 90;
    colmn.pszText = _T("date");
    list_.SendMessage(LVM_INSERTCOLUMN, 2, (LPARAM)&colmn);

    colmn.cx = 65;
    colmn.pszText = _T("mode");
    list_.SendMessage(LVM_INSERTCOLUMN, 3, (LPARAM)&colmn);

    colmn.cx = 40;
    colmn.pszText = _T("user");
    list_.SendMessage(LVM_INSERTCOLUMN, 4, (LPARAM)&colmn);

    colmn.cx = 50;
    colmn.pszText = _T("group");
    list_.SendMessage(LVM_INSERTCOLUMN, 5, (LPARAM)&colmn);

    // 路径
    wndRc.left   = rc->left;
    wndRc.right  = rc->right;
    wndRc.top    = rc->bottom - 20;
    wndRc.bottom = rc->bottom;

    path_.m_pObject = map;
    path_.m_dwMsgMapID = msgMapId++;
    path_.m_lpszClassName = WC_EDIT;

    path_.Create(wnd, wndRc, _T(""), WS_VISIBLE | WS_CHILD | ES_READONLY, WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES);
    path_.SetFont(list_.GetFont());

    CBrowseWnd::cur_ = this;
}

/**
 *\fn           void destroy()
 *\brief        释放窗本
 *\return       void 无
 */
void CBrowseWnd::destroy()
{
    if (tree_.IsWindow())
    {
        tree_.DestroyWindow();
    }

    if (list_.IsWindow())
    {
        list_.DestroyWindow();
    }

    if (path_.IsWindow())
    {
        path_.DestroyWindow();
    }

    ssh_param_.exit = TRUE;
}

/**
 *\fn           void showWindow(int cmd)
 *\brief        显示窗本
 *\param[in]    int cmd 命令SW_SHOW显示,SW_HIDE隐藏
 *\return       void 无
 */
void CBrowseWnd::showWindow(int cmd)
{
    tree_.ShowWindow(cmd);
    list_.ShowWindow(cmd);
    path_.ShowWindow(cmd);

    if (SW_SHOW == cmd)
    {
        CBrowseWnd::cur_ = this;
    }
}

/**
 *\fn           void setWndRect(int x, int y, int cx, int cy)
 *\brief        设置 窗体位置
 *\param[in]    int x x轴位置
 *\param[in]    int y y轴位置
 *\param[in]    int cx 宽
 *\param[in]    int cy 高
 *\return       void 无
 */
void CBrowseWnd::setWndRect(int x, int y, int cx, int cy)
{
    x_ = x;
    y_ = y;
    wndWidth_ = cx;
    wndHeight_ = cy;

    if (treeWidth_ <= 0 || treeWidth_ >= cx)
    {
        treeWidth_ = cx / 2;
    }

    tree_.SetWindowPos(NULL, x, y, treeWidth_, cy - 20 - S_MB, SWP_NOZORDER | SWP_NOACTIVATE);
    list_.SetWindowPos(NULL, x + treeWidth_ + S_ML, y, cx - treeWidth_ - S_MB, cy - 20 - S_MB, SWP_NOZORDER | SWP_NOACTIVATE);
    path_.SetWindowPos(NULL, x, y + cy - 20, cx, 20, SWP_NOZORDER | SWP_NOACTIVATE);
}

/**
 *\fn           bool inDragWndRect(int x, int y)
 *\brief        在拖动窗体区域
 *\param[in]    int x 鼠标位置
 *\param[in]    int y 鼠标位置
 *\return       bool false不在,true在
 */
bool CBrowseWnd::inDragWndRect(int x, int y)
{
    return (x <= (x_ + treeWidth_ + S_ML) && 
        x >= (x_ + treeWidth_) && 
        y <= (y_ + wndHeight_ - S_MB) && 
        y >= (y_));
}

/**
 *\fn           void mouseMove(int x, int y, int type)
 *\brief        鼠标移动
 *\param[in]    int x X位置
 *\param[in]    int y Y位置
 *\param[in]    int type 0-正常,1-鼠标按下,2-鼠标抬起
 *\return       void 无
 */
void CBrowseWnd::mouseMove(int x, int y, int type)
{
    switch (type)
    {
    case MOUSE_NORMAL:
        {
            if (inDragWndRect(x, y) && !dragFile_ && !dragWnd_)
            {
                SetCursor(hCursorDragWnd_);
            }

            break;
        }
    case MOUSE_DOWN:
        {
            if (inDragWndRect(x, y) && !dragFile_ && !dragWnd_)
            {
                dragWnd_ = true;
                SetCapture(wnd_);
            }

            if (dragWnd_)
            {
                SetCursor(hCursorDragWnd_);
            }
            else if (dragFile_)
            {
                SetCursor(hCursorDragFile_);
            }

            break;
        }
    case MOUSE_UP:
        {
            if (dragWnd_)
            {
                treeWidth_ = x - x_;
                setWndRect(x_, y_, wndWidth_, wndHeight_);
                ReleaseCapture();
                dragWnd_ = false;
            }

            if (dragFile_)
            {
                dragFile(x, y);
                ReleaseCapture();
                dragFile_ = false;
            }

            break;
        }
    }
}

/**
 *\fn           void setParam(int id, void *data)
 *\brief        设置参数
 *\param[in]    int id 序号
 *\param[in]    void * data 数据
 *\return       void 无
 */
void CBrowseWnd::setParam(int id, void *data)
{
    switch (id)
    {
    case 0:
        {
            tempPath_ = (const char *)data;
            break;
        }
    case 1:
        {
            open_file_cb_ = (ssh_recv_data_callback)data;
            break;
        }
    case 2:
        {
            output_text_cb_ = (ssh_recv_data_callback)data;
            break;
        }
    }
}

/**
 *\fn           void setSftpParam(const char *host, unsigned short port, 
 *\                               const char *username, const char *password, 
 *\                               void *param)
 *\brief        设置SFTP的参数
 *\param[in]    const char * host 
 *\param[in]    unsigned short port 
 *\param[in]    const char * username 
 *\param[in]    const char * password 
 *\param[in]    void * param 
 *\return       void 0成功,其它失败
 */
void CBrowseWnd::setSftpParam(const char *host, unsigned short port, const char *username, const char *password, void *param)
{
    ssh_param_.type = SSH_TYPE_SFTP;
    ssh_param_.recv_cb = NULL; // printf_data_cb
    ssh_param_.param = param;
    ssh_param_.server_addr = host;
    ssh_param_.server_port = port;
    ssh_param_.username = username;
    ssh_param_.password = password;
}

/**
 *\fn           void runSftp(const char *path)
 *\brief        运行SFTP客户端
 *\param[in]    const char * path 
 *\return       void 无
 */
void CBrowseWnd::runSftp(const char *path)
{
    _beginthread(sftp_thread_func, 0, &ssh_param_);

    // 等待连接完成
    for (int i = 0; i < 100; i++)
    {
        if (NULL != ssh_param_.channel) break;
        Sleep(100);
    }

    if (NULL == path) return;

    HTREEITEM item = createItem(path);

    updateFileList(item);

    processExpand_ = true;
}

/**
 *\fn           void sortList(int id)
 *\brief        列表排序
 *\param[in]    int id 列ID
 *\return       void 无
 */
void CBrowseWnd::sortList(int id)
{
    list_.SendMessage(LVM_SORTITEMSEX, (WPARAM)id, (LPARAM)CompareFunc);
}

/**
 *\fn           int sortList(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
 *\brief        列表排序
 *\param[in]    LPARAM lParam1 参数1
 *\param[in]    LPARAM lParam2 参数2
 *\param[in]    LPARAM lParamSort 排序参数
 *\return       int 0成功,其它失败
 */
int CBrowseWnd::sortList(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    int ret = 0;
    char buf1[50];
    char buf2[50];

    ListView_GetItemText(list_.m_hWnd, lParam1, lParamSort, buf1, 50);
    ListView_GetItemText(list_.m_hWnd, lParam2, lParamSort, buf2, 50);

    if (true) // down
    {
        ret = lstrcmp(buf1, buf2);
    }
    else
    {
        ret = -lstrcmp(buf1, buf2);
    }

    return ret;
}

/**
 *\fn           int addListItem(const char *filename, const char *size, 
                                const char *month, const char *day, const char *time, 
                                const char *mod, const char *user, const char *group, 
                                void *param, bool isLink)
 *\brief        添加列表
 *\param[in]    const char * filename 文件名
 *\param[in]    const char * size 大小
 *\param[in]    const char * month 月
 *\param[in]    const char * day 天
 *\param[in]    const char * time 时间
 *\param[in]    const char * mod 属性
 *\param[in]    const char * user 用户
 *\param[in]    const char * group 组
 *\param[in]    void * param 数据
 *\param[in]    bool isLink 是否是连接
 *\return       int 0成功,其它失败
 */
int CBrowseWnd::addListItem(const char *filename, const char *size, 
    const char *month, const char *day, const char *time,
    const char *mod, const char *user, const char *group,
    void *param, bool isLink)
{
    LV_ITEM lvis = {0};
    lvis.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM; // 文字
    lvis.cchTextMax = 200; // 文字长度
    lvis.iItem = 0;
    lvis.iSubItem = 0;
    lvis.lParam = (LPARAM)param;

    lvis.iImage = getFileExtId(isLink ? ".lnk" : filename);
    lvis.iSubItem = 0;
    lvis.pszText = (LPTSTR)filename;// 文件名
    list_.SendMessage(LVM_INSERTITEM, 0, (LPARAM)&lvis);

    lvis.iSubItem = 1;
    lvis.pszText = (LPTSTR)size;    // 大小
    list_.SendMessage(LVM_SETITEMTEXT, 0, (LPARAM)&lvis);

    char date[64] = "";
    sprintf_s(date, "%s %s %s", month, day, time);

    lvis.iSubItem = 2;
    lvis.pszText = (LPTSTR)date;    // 时间
    list_.SendMessage(LVM_SETITEMTEXT, 0, (LPARAM)&lvis);

    lvis.iSubItem = 3;
    lvis.pszText = (LPTSTR)mod;     // 权限
    list_.SendMessage(LVM_SETITEMTEXT, 0, (LPARAM)&lvis);

    lvis.iSubItem = 4;
    lvis.pszText = (LPTSTR)user;    // 用户
    list_.SendMessage(LVM_SETITEMTEXT, 0, (LPARAM)&lvis);

    lvis.iSubItem = 5;
    lvis.pszText = (LPTSTR)group;   // 组
    list_.SendMessage(LVM_SETITEMTEXT, 0, (LPARAM)&lvis);

    return 0;
}

/**
 *\fn        int updateFileList(HTREEITEM hItem)
 *\brief     更新该节点的文件列表
 *\param[in] HTREEITEM hItem 树节点
 *\return    int 0成功,其它失败
 */
int CBrowseWnd::updateFileList(HTREEITEM hItem)
{
    if (NULL == hItem || 1 == (int)hItem) return -1;

    // 连接已断开,重连
    if (ssh_param_.exit)
    {
        _beginthread(sftp_thread_func, 0, &ssh_param_);
        return 0;
    }

    // 得到当前路径
    char path[1024] = "";
    getPath(hItem, path); // 得到路径

    // 目录连接
    if (isLink(hItem))
    {
        list_.SetFocus();
        sftp_get_link_path(&ssh_param_, path, path, sizeof(path)-1);
        hItem = createItem(path);
    }

    // 得到子树
    mapStrHtreeitem map;
    getSubtree(hItem, map);

    // 设置路径
    path_.SetWindowText(path);

    // 得到文件列表
    char *dir = new char[1024*1024];
    int ret = sftp_get_dir(&ssh_param_, path, dir, 1024*1024);

    if (0 != ret)
    {
        ssh_param_.exit = TRUE;
        map.clear();
        delete[] dir;
        return ret;
    }

    // 不刷新窗体
    tree_.SetRedraw(FALSE);
    list_.SetRedraw(FALSE);
    list_.SendMessage(LVM_DELETEALLITEMS, 0, 0);

    char line[1024];
    char filename[1024];

    for (int i = 0; 0 != dir[i]; )
    {
        strncpy_s(line, &dir[i+1], dir[i]);
        line[dir[i]] = '\0';

        VECTOR_STR data;
        CStrConver::TokenizeData(line, " ", data);

        if (data.size() < 9) continue;

        // 文件名
        strcpy_s(filename, sizeof(filename)-1, data[8].c_str());

        for (UINT j = 9; j < data.size(); j++) // 可能文件名中包含空格,再重新组成完整文件名
        {
            strcat_s(filename, " ");
            strcat_s(filename, data[j].c_str());
        }

        // 目录或连接
        bool isDir = ('d' == data[0].c_str()[0]);
        bool isLink = ('l' == data[0].c_str()[0]);
        bool isDirLnk = false;

        if (isLink)
        {
            char src[1024];
            sprintf_s(src, "%s%s", path, filename);

            char des[1024];
            isDirLnk = (1 == sftp_get_link_path(&ssh_param_, src, des, sizeof(des)-1));
        }

        if (isDir || isDirLnk)
        {
            mapStrHtreeitem::iterator iter = map.find(filename);

            if (map.end() == iter)
            {
                addTreeItem(hItem, filename, isLink);
            }
            else
            {
                map.erase(filename);
            }
        }
        else // 文件
        {
            addListItem(filename, data[4].c_str(), 
                data[5].c_str(), data[6].c_str(), data[7].c_str(), 
                &data[0][1], data[2].c_str(), data[3].c_str(), 
                hItem, isLink);
        }

        i += dir[i] + 1;
    }

    delete[] dir;

    // 删除多余的子节点
    for (mapStrHtreeitem::iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        tree_.SendMessage(TVM_DELETEITEM, 0, (LPARAM)iter->second);
    }

    tree_.SendMessage(TVM_EXPAND, TVE_EXPAND, (LPARAM)hItem);
    tree_.SendMessage(TVM_SELECTITEM, TVGN_CARET, (LPARAM)hItem);
    list_.SendMessage(LVM_SORTITEMSEX, 0, (LPARAM)CompareFunc);

    tree_.SetRedraw(TRUE);
    list_.SetRedraw(TRUE);

    return 0;
}

/**
 *\fn           int uploadFile(const char *filename)
 *\brief        上传文件
 *\param[in]    const char * filename 文件名
 *\return       int 0成功,其它失败
 */
int CBrowseWnd::uploadFile(const char *filename)
{
    mapStrStr::const_iterator item = mapLocalRemoteFile.find(filename);

    if (item == mapLocalRemoteFile.end()) return -1;

    return sftp_upload_file(&ssh_param_, filename, item->second.c_str());
}

/**
 *\fn           bool isLink(HTREEITEM hItem)
 *\brief        该节点是否是连接
 *\param[in]    HTREEITEM hItem 树节点
 *\return       bool 是否是连接
 */
bool CBrowseWnd::isLink(HTREEITEM hItem)
{
    TV_ITEM item = {0};
    item.hItem = hItem;
    item.mask = LVIF_IMAGE; // 文字

    TreeView_GetItem(tree_.m_hWnd, &item);

    return (2 == item.iImage || 3 == item.iImage);
}

/**
 *\fn           HTREEITEM addTreeItem(HTREEITEM hParent, const char *text, bool link)
 *\brief        添加节点
 *\param[in]    HTREEITEM hParent 父节点
 *\param[in]    const char * text 节点名称
 *\param[in]    bool link 是否是连接
 *\return       HTREEITEM 新节点
 */
HTREEITEM CBrowseWnd::addTreeItem(HTREEITEM hParent, const char *text, bool link)
{
    if (NULL == text) return NULL;

    TVINSERTSTRUCT tvis = { 0 };
    tvis.hParent = hParent;
    tvis.hInsertAfter = NULL;
    tvis.item.mask = TVIF_TEXT | TVIF_IMAGE |TVIF_PARAM | TVIF_SELECTEDIMAGE;
    tvis.item.pszText = (LPSTR)text;
    tvis.item.lParam = (LPARAM)hParent;
    tvis.item.state = TVIS_EXPANDED;
    tvis.item.stateMask = 0;

    if (link)
    {
        tvis.item.iImage = 2;
        tvis.item.iSelectedImage = 3;
    }
    else if ('.' == text[0])
    {
        tvis.item.iImage = 4;
        tvis.item.iSelectedImage = 5;
    }
    else
    {
        tvis.item.iImage = 0;
        tvis.item.iSelectedImage = 1;
    }

    HTREEITEM hItem = (HTREEITEM)tree_.SendMessage(TVM_INSERTITEM, 0, (LPARAM)&tvis);

    tree_.SendMessage(TVM_SORTCHILDREN, 0, (LPARAM)hParent);

    return hItem;
}

/**
 *\fn           HTREEITEM findTreeItem(HTREEITEM hParent, const char *text)
 *\brief        查找节点
 *\param[in]    HTREEITEM hParent 父节点
 *\param[in]    const char * text 节点名称
 *\return       HTREEITEM 节点
 */
HTREEITEM CBrowseWnd::findTreeItem(HTREEITEM hParent, const char *text)
{
    if (NULL == text) return NULL;

    char name[128] = "";

    TVITEM item = {0};
    item.mask = TVIF_TEXT;
    item.pszText = name;
    item.cchTextMax = sizeof(name)-1;

    HTREEITEM hChild = (HTREEITEM)tree_.SendMessage(TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hParent);

    while (NULL != hChild)
    {
        item.hItem = hChild;
        tree_.SendMessage(TVM_GETITEM, 0, (LPARAM)&item);

        if (0 == strcmp(name, text))
        {
            return hChild;
        }

        hChild = (HTREEITEM)tree_.SendMessage(TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hChild);
    }

    return NULL;
}

/**
 *\fn           HTREEITEM createItem(const char *path)
 *\brief        创建并得到树节点
 *\param[in]    const char * path 路径
 *\return       HTREEITEM 0成功,其它失败
 */
HTREEITEM CBrowseWnd::createItem(const char *path)
{
    VECTOR_STR vectorStr;
    CStrConver::TokenizeData(path, "/", vectorStr);

    HTREEITEM hItem = TreeView_GetRoot(tree_.m_hWnd);

    if (NULL == hItem)
    {
        hItem = addTreeItem(NULL, "/", false); // 根节点
    }

    HTREEITEM hChild = NULL;

    for (UINT i = 0; i < vectorStr.size(); i++)
    {
        hChild = findTreeItem(hItem, vectorStr[i].c_str());

        if (NULL == hChild)
        {
            hChild = addTreeItem(hItem, vectorStr[i].c_str(), false);
        }

        tree_.SendMessage(TVM_EXPAND, TVE_EXPAND, (LPARAM)hItem);

        hItem = hChild;
    }

    return hItem;
}

/**
 *\fn        int getPath(HTREEITEM hItem, char *path)
 *\brief     得到该节点的路径
 *\param[in] HTREEITEM hItem 树节点
 *\param[in] char * path 路径
 *\return    int 0成功,其它失败
 */
int CBrowseWnd::getPath(HTREEITEM hItem, char *path)
{
    if (NULL == hItem || NULL == path) return -1;

    char text[1024] = "";
    TV_ITEM item = {0};
    item.hItem = hItem;
    item.mask = LVIF_TEXT | LVIF_PARAM; // 文字
    item.pszText = text;
    item.cchTextMax = sizeof(text);

    TreeView_GetItem(tree_.m_hWnd, &item);

    if ('/' == text[0])
    {
        text[0] = 0;
    }

    strcat_s(text, "/");
    strcat_s(text, path);
    strcpy_s(path, 1023, text);

    if (NULL == item.lParam) return 0;

    return getPath((HTREEITEM)item.lParam, path);
}

/**
 *\fn        int getSubtree(HTREEITEM hItem, mapStrHtreeitem &map)
 *\brief     得到该节点的所有子节点
 *\param[in] HTREEITEM hItem 节点
 *\param[in] mapStrHtreeitem & map 子节点,名称->节点句柄
 *\return    int 0成功,其它失败
 */
int CBrowseWnd::getSubtree(HTREEITEM hItem, mapStrHtreeitem &map)
{
    map.clear();

    char text[128] = "";
    TVITEM item = { 0 };
    item.mask = TVIF_TEXT;
    item.pszText = text;
    item.cchTextMax = sizeof(text);

    HTREEITEM child = (HTREEITEM)tree_.SendMessage(TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hItem);

    while (NULL != child)
    {
        item.hItem = child;
        tree_.SendMessage(TVM_GETITEM, 0, (LPARAM)&item);

        map[text] = child;

        child = (HTREEITEM)tree_.SendMessage(TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)child);
    }

    return 0;
}

/**
 *\fn        const char * getFileExt(const char *filename)
 *\brief     得到文件扩展名
 *\param[in] const char * filename 文件名
 *\return    const char * 扩展名
 */
const char * CBrowseWnd::getFileExt(const char *filename)
{
    if (NULL == filename) return "";

    for (int i = strlen(filename); i >= 0; --i)
    {
        if ('.' == filename[i])
        {
            return &filename[i+1];
        }
    }

    return "";
}

/**
 *\fn           int getFileExtId(const char *filename)
 *\brief        得到文件扩展名ID
 *\param[in]    const char * filename 文件名
 *\return       int 扩展名ID
 */
int CBrowseWnd::getFileExtId(const char *filename)
{
    int id = 0;
    const char *ext = getFileExt(filename);

    mapStrInt::iterator iter = mapExtImage_.find(ext);

    if (iter == mapExtImage_.end())
    {
        SHFILEINFO info = {0};
        SHGetFileInfo(filename, 0, &info, sizeof(info), SHGFI_ICON | SHGFI_USEFILEATTRIBUTES );

        id = ImageList_AddIcon(hImageList_, info.hIcon);

        mapExtImage_[ext] = id;
    }
    else
    {
        id = iter->second;
    }

    return id;
}

/**
 *\fn           void startDragFile()
 *\brief        开始施动文件
 *\return       void 无
 */
void CBrowseWnd::startDragFile()
{
    dragFile_ = true;
    SetCapture(wnd_);
}

/**
 *\fn           void dragFile(int x, int y)
 *\brief        拖动文件
 *\param[in]    int x 鼠标位置
 *\param[in]    int y 鼠标位置
 *\return       void 无
 */
void CBrowseWnd::dragFile(int x, int y)
{
    POINT pt = {x, y};
    ::ClientToScreen(wnd_, &pt);

    HWND wnd = ::WindowFromPoint(pt); // 得到鼠标所在的窗体

    char path[1024] = "";
    ::GetWindowText(wnd, path, sizeof(path)-1);

    if (0 == strcmp("FolderView", path)) // 桌面
    {
        SHGetSpecialFolderPath(NULL, path, CSIDL_DESKTOPDIRECTORY, FALSE);
    }
    else // 资源管理器
    {
        wnd = ::GetParent(wnd); // SHELLDLL_DefView
        wnd = ::GetParent(wnd); // CtrlNotifySink
        wnd = ::GetParent(wnd); // DirectUIHWND
        wnd = ::GetParent(wnd); // DUIViewWndClassName
        wnd = ::GetParent(wnd); // ShellTabWindowClass
        wnd = ::GetParent(wnd); // CabinetWClass
        wnd = ::FindWindowEx(wnd, NULL, "WorkerW", NULL);
        wnd = ::FindWindowEx(wnd, NULL, "ReBarWindow32", NULL);
        wnd = ::FindWindowEx(wnd, NULL, "Address Band Root", NULL);
        wnd = ::FindWindowEx(wnd, NULL, "msctls_progress32", NULL);
        wnd = ::FindWindowEx(wnd, NULL, "Breadcrumb Parent", NULL);
        wnd = ::FindWindowEx(wnd, NULL, "ToolbarWindow32", NULL);

        ::GetWindowText(wnd, path, sizeof(path)-1); // 地址: D:\360Downloads
    }

    // 没有找到窗体
    if (path[0] == '\0') return;

    int i = 0;
    int itemId = -1;
    int count = ListView_GetSelectedCount(list_.m_hWnd);

    for (i = 0; i < count; i++)
    {
        itemId = ListView_GetNextItem(list_.m_hWnd, itemId, LVNI_SELECTED);

        LV_ITEM item = {0};
        char filename[256] = "";
        item.iItem = itemId;
        item.mask = LVIF_TEXT | LVIF_PARAM; // 文字
        item.pszText = filename;
        item.cchTextMax = sizeof(filename);

        ListView_GetItem(list_.m_hWnd, &item);

        char remotePath[1024] = "";
        getPath((HTREEITEM)item.lParam, remotePath);

        char localPath[1024] = "";
        strcpy_s(localPath, strstr(path, "\\") - 2);

        strcat_s(localPath, sizeof(path), "\\");
        strcat_s(localPath, sizeof(path), filename);
        strcat_s(remotePath, sizeof(path), filename);

        sftp_download_file(&ssh_param_, localPath, remotePath);
    }
}

#define NEW_FILE_NAME "new file"

/**
 *\fn           void addFile()
 *\brief        添加一个新文件
 *\return       void 无
 */
void CBrowseWnd::addFile()
{
    int fileId = 0;
    int count = ListView_GetItemCount(list_.m_hWnd);
    char filename[256] = "";

    for (int i = 0; i < count; i++)
    {
        ListView_GetItemText(list_.m_hWnd, i, 0, filename, sizeof(filename)-1);

        if (NULL != strstr(filename, NEW_FILE_NAME))
        {
            if (atoi(&filename[strlen(NEW_FILE_NAME)]) >= fileId)
            {
                fileId = atoi(&filename[strlen(NEW_FILE_NAME)]) + 1;
            }
        }
    }

    sprintf_s(filename, NEW_FILE_NAME"%d", fileId);

    char path[1024] = "";
    GetCurrentDirectory(MAX_PATH, path);

    int len = strlen(path);
    sprintf_s(&path[len], sizeof(path)-len-1, "\\%s\\%s", tempPath_, filename);

    char localPath[1024] = "";
    PathCanonicalize(localPath, path);

    char remotePath[1024] = "";
    path_.GetWindowText(remotePath, sizeof(remotePath)-1);
    strcat_s(remotePath, filename);

    if (!PathFileExists(tempPath_))
    {
        ::CreateDirectory(tempPath_, NULL);
    }

    FILE *file = NULL;
    fopen_s(&file, localPath, "w+");
    fwrite(filename, 1, strlen(filename), file);
    fclose(file);

    int ret = sftp_upload_file(&ssh_param_, localPath, remotePath);

    if (0 != ret) return;

    updateFileList(TreeView_GetSelection(tree_.m_hWnd));
}

/**
 *\fn           void openFile(int id)
 *\brief        打开文件
 *\param[in]    int id 列表ID
 *\return       void 0成功,其它失败
 */
void CBrowseWnd::openFile(int id)
{
    LV_ITEM item = {0};
    char text[100] = "";
    item.iItem = id;
    item.mask = LVIF_TEXT | LVIF_PARAM; // 文字
    item.pszText = text;
    item.cchTextMax = sizeof(text);

    ListView_GetItem(list_.m_hWnd, &item);

    if (NULL == item.lParam) return;

    if (!PathFileExists(tempPath_))
    {
        ::CreateDirectory(tempPath_, NULL);
    }

    char localPath[1024] = "";
    _snprintf_s(localPath, sizeof(localPath)-1, "%s\\%s", tempPath_, text);

    char remotePath[1024] = "";
    getPath((HTREEITEM)item.lParam, remotePath);

    strcat_s(remotePath, "/");
    strcat_s(remotePath, text);

    int ret = sftp_download_file(&ssh_param_, localPath, remotePath);

    if (0 != ret) return;

    open_file_cb_(NULL, localPath, strlen(localPath));

    mapLocalRemoteFile[localPath] = remotePath;
}

/**
 *\fn           BOOL renameDir(const char *name)
 *\brief        重命名
 *\param[in]    const char *name 新名字
 *\return       BOOL TRUE成功,其它失败
 */
BOOL CBrowseWnd::renameDir(const char *name)
{
    if (NULL == name) return FALSE;

    char oldPath[1024] = "";
    path_.GetWindowText(oldPath, sizeof(oldPath)-1);

    char newPath[1024] = "";

    for (int i = strlen(oldPath) - 2; i >=0; i--)
    {
        if ('/' == oldPath[i])
        {
            strncpy_s(newPath, oldPath, i+1);
            break;
        }
    }

    strcat_s(newPath, name);

    if (0 == strcmp(oldPath, newPath))
    {
        return TRUE;
    }

    BOOL ret = (0 == sftp_rename(&ssh_param_, oldPath, newPath));

    if (ret)
    {
        path_.SetWindowText(newPath);
    }

    return ret;
}

/**
 *\fn           BOOL renameFile(int item, int subItem, const char *name)
 *\brief        重命名
 *\param[in]    int item 列表节点ID
 *\param[in]    int subItem 列表子节点ID
 *\param[in]    const char * name 新名字
 *\return       BOOL 0成功,其它失败
 */
BOOL CBrowseWnd::renameFile(int item, int subItem, const char *name)
{
    if (item < 0 || 0 != subItem || NULL == name) return FALSE;

    char oldPath[1024] = "";
    path_.GetWindowText(oldPath, sizeof(oldPath)-1);

    char newPath[1024] = "";
    sprintf_s(newPath, "%s%s", oldPath, name);

    int len = strlen(oldPath);
    ListView_GetItemText(list_.m_hWnd, item, subItem, &oldPath[len], sizeof(oldPath)-len-1);

    if (0 == strcmp(oldPath, newPath))
    {
        return TRUE;
    }

    return (0 == sftp_rename(&ssh_param_, oldPath, newPath));
}

/**
 *\fn           BOOL deleteSelectDir()
 *\brief        删除当前选中目录
 *\return       BOOL TRUE成功,其它失败
 */
BOOL CBrowseWnd::deleteSelectDir()
{
    char path[1024] = "";
    path_.GetWindowText(path, sizeof(path)-1);

    BOOL ret (0 == sftp_rm_dir(&ssh_param_, path));

    if (ret)
    {
        HTREEITEM item = TreeView_GetSelection(tree_.m_hWnd);

        TreeView_DeleteItem(tree_.m_hWnd, item);
    }

    return ret;
}

/**
 *\fn           BOOL deleteSelectFile()
 *\brief        删除当前选中文件
 *\return       BOOL TRUE成功,其它失败
 */
BOOL CBrowseWnd::deleteSelectFile()
{
    if (ListView_GetSelectedCount(list_.m_hWnd) <= 0 ||
        IDYES != MessageBox(NULL, "您确认要删除当前选中的文件吗?", "信息", MB_ICONQUESTION|MB_YESNO))
    {
        return FALSE;
    }

    char path[1024] = "";
    path_.GetWindowText(path, sizeof(path)-1);

    int index = -1;
    char name[128] = "";

    char filename[1024] = "";

    while (true)
    {
        index = ListView_GetNextItem(list_.m_hWnd, index, LVNI_SELECTED);

        if (index >= 0)
        {
            ListView_GetItemText(list_.m_hWnd, index, 0, name, sizeof(name)-1);

            sprintf_s(filename, "%s%s", path, name);

            if (0 == sftp_rm(&ssh_param_, filename))
            {
                ListView_DeleteItem(list_.m_hWnd, index);
                index--;
            }
        }
        else
        {
            break;
        }
    }

    return TRUE;
}
