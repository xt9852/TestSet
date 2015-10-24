/*************************************************
 * VS Addin
 * Copyright (C) XT. Co., Ltd.
 * File name:       AddinWnd.h
 * Author:          zht
 * Version:         1.0.0
 * Date:            2014.9.4
 * Description:     VS插件窗体定义
*************************************************/

#pragma once
#include "SubWnd.h"
#include "SshConfig.h"

extern "C"
{
#include "ssh2/ssh2.h"
};


typedef struct _tagServerInfo
{
    char username[128];
    char password[128];
    char serverAddr[128];
    int serverPort;
    int port_map_count;

    _tagServerInfo()
    {
        username[0] = 0;
        password[0] = 0;
        serverAddr[0] = 0;
        serverPort = 0;
        port_map_count = 0;
    }

}ServerInfo, *PServerInfo;


class CAddinWnd
{
public:
    CAddinWnd();
    ~CAddinWnd();

private:
    HIMAGELIST hImageList_;                     // 图像列表
    HCURSOR hCursorDragWnd_;                    // 拖动窗体时显示的光标
    HCURSOR hCursorDragFile_;                   // 拖动文件时显示的光标
    HFONT font_;                                // 字体

    HWND wnd_;                                  // 主窗体
    CMessageMap *msgMap_;                       // 消息循环

    CContainedWindow comboServer_;              // ComboBox控件,可连接的服务器
    CContainedWindow comboConnect_;             // ComboBox控件,当前已经连接的服务器

private:
    ssh_recv_data_callback open_file_cb_;       // 在VS中打开文件回调
    ssh_recv_data_callback output_text_cb_;     // 在状态栏显示信息

    char projectName_[128];                     // 项目名
    Config *config_;                            // 配置文件

    PServerInfo serverInfo_;                    // 服务器信息

    CSubWnd *connectServer_[100];               // 已经连接的服务器

    int serverCount_;                           // 服务器数量
    int showServerIndex_;                       // 当前显示的窗体
    int connectServerCount_;                    // 已经连接的服务器数量

    int wndWidth_;                              // 窗体宽
    int wndHeight_;                             // 窗体高
    int treeWidth_;                             // 树控件宽

public:
    /**
     *\fn           void setParam(int id, void *data)
     *\brief        设置参数
     *\param[in]    int id 序号
     *\param[in]    void * data 数据
     *\return       void 无
     */
    void setParam(int id, void *data);

    /**
     *\fn           int create(HINSTANCE instance, CMessageMap *map, HWND wnd, 
     *\                        int icon, int cursorDrag, int cursorCopy)
     *\brief        创建窗体
     *\param[in]    HINSTANCE instance 实例句柄
     *\param[in]    CMessageMap * map 消息循环
     *\param[in]    HWND wnd 主窗本
     *\param[in]    int icon 图标
     *\param[in]    int cursorDrag 拖动时图标
     *\param[in]    int cursorCopy 复制时图标
     *\return       int 0成功,其它失败
     */
    int create(HINSTANCE instance, CMessageMap *map, HWND wnd, 
        int icon, int cursorDrag, int cursorCopy);

    /**
     *\fn           void destroy()
     *\brief        释放窗体和资源
     *\return       void 无
     */
    void destroy();

    /**
     *\fn           void resizeWnd(int cx, int cy)
     *\brief        设置窗本大小
     *\param[in]    int cx 宽
     *\param[in]    int cy 高
     *\return       void 无
     */
    void resizeWnd(int cx, int cy);

    /**
     *\fn           void mouseMove(int x, int y, int type)
     *\brief        鼠标移动
     *\param[in]    int x X轴
     *\param[in]    int y Y轴
     *\param[in]    int type 0-正常,1-按下,2-抬起
     *\return       void 无
     */
    void mouseMove(int x, int y, int type);

    /**
     *\fn           int addServer()
     *\brief        添加服务器
     *\return       int 无
     */
    int addServer();

    /**
     *\fn           int connectServer()
     *\brief        连接服务器
     *\return       int 无
     */
    int connectServer();

    /**
     *\fn           int showServer()
     *\brief        显示服务器
     *\return       int 无
     */
    int showServer();

    /**
     *\fn           int addBrowse(int serverId, void **data)
     *\brief        添加浏览器
     *\param[in]    int serverId 服务器ID
     *\param[out]   void * * data 数据
     *\return       int 0成功,其它失败
     */
    int addBrowse(int serverId, void **data);

    /**
     *\fn           int addTerminal(int serverId, void **data)
     *\brief        添加终端
     *\param[in]    int serverId 服务器ID
     *\param[out]   void * * data 数据
     *\return       int 0成功,其它失败
     */
    int addTerminal(int serverId, void **data);

    /**
     *\fn           void setFocus(bool focus)
     *\brief        设置焦点
     *\param[in]    bool focus 是否有焦点
     *\return       void 无
     */
    void setFocus(bool focus);

    /**
     *\fn           void scroll(int type, int data)
     *\brief        滚动屏幕
     *\param[in]    int type 类型
     *\param[in]    int data 数值
     *\return       void 无
     */
    void scroll(int type, int data);

    /**
     *\fn           void mouseWheel(int data)
     *\brief        鼠标滑轮滚动
     *\param[in]    int data 数值
     *\return       void 无
     */
    void mouseWheel(int data);

    /**
     *\fn           void onChar(int key, int type)
     *\brief        输入一个字符
     *\param[in]    int key 字符
     *\param[in]    int type 数据
     *\return       void 无
     */
    void onChar(int key, int type);

    /**
     *\fn           void onChar(int key)
     *\brief        按下一个键
     *\param[in]    int key 键
     *\return       void 无
     */
    void onKeyDown(int key);

    /**
     *\fn           void onPaint()
     *\brief        画图
     *\return       void 无
     */
    void onPaint();

    /**
     *\fn           void sortList(int id)
     *\brief        列表排序
     *\param[in]    int id 列ID
     *\return       void 无
     */
    void sortList(int id);

    /**
     *\fn           void addFile(HWND wnd)
     *\brief        添加一个新文件
     *\param[in]    HWND wnd 窗本
     *\return       void 无
     */
    void addFile(HWND wnd);

    /**
     *\fn           void openFile(HWND wnd, int id)
     *\brief        打开文件窗体
     *\param[in]    HWND wnd
     *\param[in]    int id 行ID
     *\return       void 无
     */
    void openFile(HWND wnd, int id);

    /**
     *\fn           void startDragFile()
     *\brief        开始拖动文件
     *\return       void 无
     */
    void startDragFile();

    /**
     *\fn        int updateFileList(HWND wnd, HTREEITEM hItem)
     *\brief     更新该节点的文件列表
     *\param[in] HWND wnd 窗体
     *\param[in] HTREEITEM hItem 树节点
     *\return    int 0成功,其它失败
     */
    void updateFileList(HWND wnd, HTREEITEM item);

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
     *\return       BOOL TRUE成功,其它失败
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


