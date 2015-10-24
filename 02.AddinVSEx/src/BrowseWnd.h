/*************************************************
 * VS Addin
 * Copyright (C) XT. Co., Ltd.
 * File name:       BrowseWnd.h
 * Author:          zht
 * Version:         1.0.0
 * Date:            2014.9.4
 * Description:     VS插件的浏览窗体定义
*************************************************/

#pragma once
#include "SubWnd.h"
#include <map>
#include <string>

extern "C"
{
#include "ssh2/ssh2.h"
#include "ssh2/sftp.h"
#include "ssh2/direct_tcpip.h"
};

#define S_ML 5  // 树与列表控件中间保留
#define S_MB 5  // 树与路径控件中间保留

typedef std::map<std::string, int>              mapStrInt;
typedef std::map<std::string, std::string>      mapStrStr;
typedef std::map<std::string, HTREEITEM>        mapStrHtreeitem;

class CBrowseWnd : public CSubWnd
{
public:
    CBrowseWnd();
    ~CBrowseWnd();

private:
    int x_;                                 // 窗体位置
    int y_;                                 // 窗体位置
    int wndWidth_;                          // 窗体宽
    int wndHeight_;                         // 窗体高
    int treeWidth_;                         // 树控件宽

    bool dragWnd_;                          // 是否正在拖动控件
    bool dragFile_;                         // 是否正在拖动文件
    bool processExpand_;                    // 是否处理treeview展开消息

    ssh_recv_data_callback open_file_cb_;   // 在VS中打开文件回调
    ssh_recv_data_callback output_text_cb_; // 在状态栏显示信息

    my_ssh_param ssh_param_;                // SSH参数

    const char *tempPath_;                  // 临地目录
    mapStrInt mapExtImage_;                 // "文件类型"->hImageList_中的ID
    mapStrStr mapLocalRemoteFile;           // 本地文件到远程文件

private:
    HWND wnd_;                              // 主窗体
    HIMAGELIST hImageList_;                 // 图标列表
    HCURSOR hCursorDragWnd_;                // 拖动窗体时光标
    HCURSOR hCursorDragFile_;               // 拖动文件时光标

    CContainedWindow tree_;                 // 树型控件
    CContainedWindow list_;                 // 列表控件
    CContainedWindow path_;                 // EDIT控件,当前路径

public:
    static CBrowseWnd *cur_;                // 当前显示的

public:
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
    void create(CMessageMap *map, int msgMapId, HWND wnd, RECT *rc, 
        int treeWidth, HIMAGELIST imageList, HCURSOR dragWnd, HCURSOR dragFile);

    /**
     *\fn           void destroy()
     *\brief        释放窗本
     *\return       void 无
     */
    void destroy();

    /**
     *\fn           bool isTree(HWND wnd)
     *\brief        是否是树控件
     *\param[in]    HWND wnd 窗体
     *\return       bool 
     */
    bool isTree(HWND wnd) { return (wnd == tree_.m_hWnd); }

    /**
     *\fn           bool isList(HWND wnd)
     *\brief        是否是列表控件
     *\param[in]    HWND wnd 窗体
     *\return       bool 
     */
    bool isList(HWND wnd) { return (wnd == list_.m_hWnd); }

    /**
     *\fn           bool inDragWndRect(int x, int y)
     *\brief        在拖动窗体区域
     *\param[in]    int x 鼠标位置
     *\param[in]    int y 鼠标位置
     *\return       bool false不在,true在
     */
    bool inDragWndRect(int x, int y);

    /**
     *\fn           void showWindow(int cmd)
     *\brief        显示窗本
     *\param[in]    int cmd 命令SW_SHOW显示,SW_HIDE隐藏
     *\return       void 无
     */
    void showWindow(int cmd);

    /**
     *\fn           void setWndRect(int x, int y, int cx, int cy)
     *\brief        设置 窗体位置
     *\param[in]    int x x轴位置
     *\param[in]    int y y轴位置
     *\param[in]    int cx 宽
     *\param[in]    int cy 高
     *\return       void 无
     */
    void setWndRect(int x, int y, int cx, int cy);

    /**
     *\fn           void mouseMove(int x, int y, int type)
     *\brief        鼠标移动
     *\param[in]    int x X位置
     *\param[in]    int y Y位置
     *\param[in]    int type 0-正常,1-鼠标按下,2-鼠标抬起
     *\return       void 无
     */
    void mouseMove(int x, int y, int type);

    /**
     *\fn           void startDragFile()
     *\brief        开始施动文件
     *\return       void 无
     */
    void startDragFile();

    /**
     *\fn           void dragFile(int x, int y)
     *\brief        拖动文件
     *\param[in]    int x 鼠标位置
     *\param[in]    int y 鼠标位置
     *\return       void 无
     */
    void dragFile(int x, int y);

    /**
     *\fn           void setParam(int id, void *data)
     *\brief        设置参数
     *\param[in]    int id 序号
     *\param[in]    void * data 数据
     *\return       void 无
     */
    void setParam(int id, void *data);

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
    void setSftpParam(const char *host, unsigned short port, 
        const char *username, const char *password, void *param);

    /**
     *\fn           void runSftp(const char *path)
     *\brief        运行SFTP客户端
     *\param[in]    const char * path 
     *\return       void 无
     */
    void runSftp(const char *path);

    /**
     *\fn        int updateFileList(HTREEITEM hItem)
     *\brief     更新该节点的文件列表
     *\param[in] HTREEITEM hItem 树节点
     *\return    int 0成功,其它失败
     */
    int updateFileList(HTREEITEM hItem);

    /**
     *\fn           void sortList(int id)
     *\brief        列表排序
     *\param[in]    int id 列ID
     *\return       void 无
     */
    void sortList(int id);

    /**
     *\fn           int sortList(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
     *\brief        列表排序
     *\param[in]    LPARAM lParam1 参数1
     *\param[in]    LPARAM lParam2 参数2
     *\param[in]    LPARAM lParamSort 排序参数
     *\return       int 0成功,其它失败
     */
    int sortList(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

    /**
     *\fn           int uploadFile(const char *filename)
     *\brief        上传文件
     *\param[in]    const char * filename 文件名
     *\return       int 0成功,其它失败
     */
    int uploadFile(const char *filename);

    /**
     *\fn           bool isLink(HTREEITEM hItem)
     *\brief        该节点是否是连接
     *\param[in]    HTREEITEM hItem 树节点
     *\return       bool 是否是连接
     */
    bool isLink(HTREEITEM hItem);

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
    int addListItem(const char *filename, const char *size, 
        const char *month, const char *day, const char *time,
        const char *mod, const char *user, const char *group,
        void *param, bool isLink);

    /**
     *\fn           HTREEITEM addTreeItem(HTREEITEM hParent, const char *text, bool link)
     *\brief        添加节点
     *\param[in]    HTREEITEM hParent 父节点
     *\param[in]    const char * text 节点名称
     *\param[in]    bool link 是否是连接
     *\return       HTREEITEM 新节点
     */
    HTREEITEM addTreeItem(HTREEITEM hParent, const char *text, bool link);

    /**
     *\fn           HTREEITEM findTreeItem(HTREEITEM hParent, const char *text)
     *\brief        查找节点
     *\param[in]    HTREEITEM hParent 父节点
     *\param[in]    const char * text 节点名称
     *\return       HTREEITEM 节点
     */
    HTREEITEM findTreeItem(HTREEITEM hParent, const char *text);

    /**
     *\fn           HTREEITEM createItem(const char *path)
     *\brief        创建并得到树节点
     *\param[in]    const char * path 路径
     *\return       HTREEITEM 0成功,其它失败
     */
    HTREEITEM createItem(const char *path);

    /**
     *\fn        int getPath(HTREEITEM hItem, char *path)
     *\brief     得到该节点的路径
     *\param[in] HTREEITEM hItem 树节点
     *\param[in] char * path 路径
     *\return    int 0成功,其它失败
     */
    int getPath(HTREEITEM hItem, char *path);

    /**
     *\fn        int getSubtree(HTREEITEM hItem, mapStrHtreeitem &map)
     *\brief     得到该节点的所有子节点
     *\param[in] HTREEITEM hItem 节点
     *\param[in] mapStrHtreeitem & map 子节点,名称->节点句柄
     *\return    int 0成功,其它失败
     */
    int getSubtree(HTREEITEM hItem, mapStrHtreeitem &map);

    /**
     *\fn           const char* getFileExt(const char *filename)
     *\brief        得到文件的扩展名
     *\param[in]    const char * filename 文件名
     *\return       const char* 扩展名
     */
    const char* getFileExt(const char *filename);

    /**
     *\fn           int getFileExtId(const char *filename)
     *\brief        得到文件扩展名ID
     *\param[in]    const char * filename 文件名
     *\return       int 扩展名ID
     */
    int getFileExtId(const char *filename);

    /**
     *\fn           void addFile()
     *\brief        添加一个新文件
     *\return       void 无
     */
    void addFile();

    /**
     *\fn           void openFile(int id)
     *\brief        打开文件
     *\param[in]    int id 列表ID
     *\return       void 0成功,其它失败
     */
    void openFile(int id);

    /**
     *\fn           BOOL renameDir(const char *name)
     *\brief        重命名
     *\param[in]    const char *name 新名字
     *\return       BOOL TRUE成功,其它失败
     */
    BOOL renameDir(const char *name);

    /**
     *\fn           BOOL renameFile(int item, int subItem, const char *name)
     *\brief        重命名
     *\param[in]    int item 列表节点ID
     *\param[in]    int subItem 列表子节点ID
     *\param[in]    const char * name 新名字
     *\return       BOOL 0成功,其它失败
     */
    BOOL renameFile(int item, int subItem, const char *name);

    /**
     *\fn           BOOL deleteSelectDir()
     *\brief        删除当前选中目录
     *\return       BOOL TRUE成功,其它失败
     */
    BOOL deleteSelectDir();

    /**
     *\fn           BOOL deleteSelectFile()
     *\brief        删除当前选中文件
     *\return       BOOL TRUE成功,其它失败
     */
    BOOL deleteSelectFile();
};


