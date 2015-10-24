/*************************************************
 * VS Addin
 * Copyright (C) XT. Co., Ltd.
 * File name:       SubWnd.h
 * Author:          zht
 * Version:         1.0.0
 * Date:            2014.9.4
 * Description:     VS插件窗体基类定义
*************************************************/

#pragma once

enum
{
    MOUSE_NORMAL,       /*鼠标正常*/
    MOUSE_DOWN,         /*鼠标按下*/
    MOUSE_UP,           /*鼠标抬起*/
};

enum
{
    SUB_TYPE_TERMINAL,  /*终端*/
    SUB_TYPE_BROWSE,    /*浏览器*/
};

class CSubWnd
{
public:
    CSubWnd() { type_ = 0; }
    ~CSubWnd() {}

public:
    int type_;

public:
    /**
     *\fn           void destroy()
     *\brief        释放窗体,和资源
     *\return       void 无
     */
    virtual void destroy() {}
    /**
     *\fn           void showWindow(int cmd)
     *\brief        显示窗体
     *\param[in]    int cmd TRUE-显示,FALSE-隐藏
     *\return       void 无
     */
    virtual void showWindow(int /*cmd*/) {}

    /**
     *\fn           void mouseMove(int x, int y, int type)
     *\brief        鼠标移动
     *\param[in]    int x X位置
     *\param[in]    int y Y位置
     *\param[in]    int type 0-正常,1-鼠标按下,2-鼠标抬起
     *\return       void 无
     */
    virtual void mouseMove(int /*x*/, int /*y*/, int /*type*/) {}

    /**
     *\fn           void setWndRect(int x, int y, int cx, int cy)
     *\brief        设置窗体大小位置
     *\param[in]    int x X位置
     *\param[in]    int y Y位置
     *\param[in]    int cx 宽
     *\param[in]    int cy 高
     *\return       void 无
     */
    virtual void setWndRect(int /*x*/, int /*y*/, int /*cx*/, int /*cy*/) {}
};


