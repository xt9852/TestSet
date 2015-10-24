/*************************************************
 * VS Addin
 * Copyright (C) XT. Co., Ltd.
 * File name:       TerminalWnd.h
 * Author:          zht
 * Version:         1.0.0
 * Date:            2014.9.4
 * Description:     VS插件的终端窗体定义
*************************************************/

#pragma once
#include "SubWnd.h"
#include "Terminal.h"

extern "C"
{
#include "ssh2/ssh2.h"
#include "ssh2/direct_tcpip.h"
};

class CTerminalWnd  : public CSubWnd
{
public:
    CTerminalWnd();
    ~CTerminalWnd();

private:
    bool setSshSize_;           // 是否设置ssh的大小

    int accumDelta_;            // 鼠标滚动使用
    int deltaPerLine_;          // 鼠标滚动使用

    my_ssh_param ssh_param_;    // SSH参数

    CTerminal term_;            // 端终处理

    CContainedWindow edit_;     // EDIT控件

public:
    /**
     *\fn           void create(CMessageMap *map, int msgMapId, HWND wnd, RECT *rc)
     *\brief        创建窗体
     *\param[in]    CMessageMap * map 消息循环
     *\param[in]    int msgMapId 消息循环ID
     *\param[in]    HWND wnd 主窗体
     *\param[in]    RECT * rc 窗体位置
     *\return       void 无
     */
    void create(CMessageMap *map, int msgMapId, HWND wnd, RECT *rc);

    /**
     *\fn           void destroy()
     *\brief        释放窗本
     *\return       void 无
     */
    void destroy();

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
     *\fn           void setTermRect()
     *\brief        设置终端大小
     *\return       void 无
     */
    void setTermRect();

    /**
     *\fn           void setSShParam(const char *host, unsigned short port, 
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
    void setSShParam(const char *host, unsigned short port, 
        const char *username, const char *password, void *param);

    /**
     *\fn           void runSSh()
     *\brief        运行SSH
     *\return       void 无
     */
    void runSSh();

    /**
     *\fn           void setFocus(bool focus)
     *\brief        设置焦点
     *\param[in]    bool focus 是否有焦点
     *\return       void 无
     */
    void setFocus(bool focus);

    /**
     *\fn           void paint()
     *\brief        画图
     *\return       void 无
     */
    void paint();

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
     *\fn           void output(const char *text, int textLen)
     *\brief        输出文字
     *\param[in]    const char * text 文字
     *\param[in]    int textLen 文字长
     *\return       void 无
     */
    void output(const char *text, int textLen);
};


