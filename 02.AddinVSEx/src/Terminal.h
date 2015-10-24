
#pragma once
#include "04.UI/Ctrl/XTDC.h"

// 得到git提交的次数
// git rev-list --all | find /v "" /c

class CTerminal
{
public:
    CTerminal();
    ~CTerminal();

private:
    CXTDC               xtDC_;          // XTDC
    HDC                 wndDC_;         // 窗体DC
    HDC                 imageDC_;       // 图像DC
    HDC                 testDC_;        // 图像DC

    HFONT               font_;          // 字体
    COLORREF            color_[8];      // 颜色
    COLORREF            fgColor_;       // 当前文字颜色
    COLORREF            bgColor_;       // 当前背景颜色
    HPEN                fgPen_;         // 画笔
    HPEN                bgPen_;         // 画笔
    HWND                wnd_;           // 窗体句柄

    BITMAPINFO          *bmi_;          // BMP信息

    UINT                fontCx_;        // 字体宽(像素)
    UINT                fontCy_;        // 字体高
    UINT                wndCx_;         // 窗体宽
    UINT                wndCy_;         // 窗体高
    UINT                screenCx_;      // 屏幕宽
    UINT                screenCy_;      // 屏幕高
    UINT                imageDcCx_;     // 图像DC宽
    UINT                imageDcCy_;     // 图像DC屏幕高

    UINT                scrollPos_;     // 滚动条位置(字符行)
    UINT                scrollPageCx_;  // 滚动条页宽
    UINT                scrollPageCy_;  // 滚动条页高

    UINT                imageTopPos_;   // 图像DC开始位置,循环向下移动

    UINT                cursorX_;       // 当前光标位置X
    UINT                cursorY_;       // 当前光标位置Y
    UINT                saveCursorX_;   // 保存当前光标位置X
    UINT                saveCursorY_;   // 保存当前光标位置Y
    UINT                lastCursorY_;   // 保存当前光标位置Y

    static UINT         pid_;           // 显示光标的线程
    static CTerminal    *focusTerm_;    // 当前获得焦点的终端

    CRITICAL_SECTION    wndDrawlock_;   // 刷新窗体锁

public:
    /**
     *\fn           void showSursorThread(void* param)
     *\brief        显示光标线程
     *\param[in]    void * param 
     *\return       void 0成功,其它失败
     */
    static UINT __stdcall showSursorThread(void* param);

    /*
     *\fn         int Init(HWND hwnd)
     *\brief      初始化
     *\param[in]  HWND hwnd 窗体句柄
     *\return     int 0成功,其它失败
     */
    int Init(HWND hwnd);

    /**
     *\fn           void setFocus(bool focus)
     *\brief        设置焦点
     *\param[in]    bool focus 是否有焦点
     *\return       void 无
     */
    void setFocus(bool focus);

    /**
     *\fn           void getTermRect(int &cx, int &cy)
     *\brief        得到终端的横竖字符个数
     *\param[in]    int & cx 横向字符个数
     *\param[in]    int & cy 竖向字符个数
     *\return       void 无
     */
    void getTermRect(int &cx, int &cy) { cx = scrollPageCx_; cy = scrollPageCy_;}

    /*
     *\fn         void setWndRect(int cx, int cy)
     *\brief      设置窗体宽高
     *\param[in]  int cx 宽
     *\param[in]  int cy 高
     *\return     void 无
     */
    void setWndRect(int cx, int cy);

    /**
     *\fn           void scrollScreen(int type, int data)
     *\brief        垂直滚动
     *\param[in]    int type 类型
     *\param[in]    int data 数据
     *\return       void 0成功,其它失败
     */
    void scrollScreen(int type, int data);

    /*
     *\fn         void drawWndDc()
     *\brief      刷屏
     *\return     void 无
     */
    void drawWndDc();

    /**
     *\fn           void drawWndCursor(int x, int y, bool show)
     *\brief        显示光标
     *\param[in]    int x 光标x
     *\param[in]    int y 光标y
     *\param[in]    bool show 是否显示光标
     *\return       void 无
     */
    void drawWndCursor(int x, int y, bool show);

    /*
     *\fn         void clearScreen(int type)
     *\brief      清屏
     *\param[in]  int type 清空类型:0-从光标到屏幕底,1-屏幕到顶光标,2-全屏
     *\return     void 无
     */
    void clearScreen(int type);

    /**
     *\fn           void clearLineText(int type, int count)
     *\brief        清行
     *\param[in]    int type:0-从光标到行尾,1-行首到光标,2-全行
     *\param[in]    int count 字符数量
     *\return       void 无
     */
    void clearLineText(int type, int count);

    /**
     *\fn           void drawLineText(const char *text, int textLen, bool newLen)
     *\brief        刷新一行
     *\param[in]    const char * text 文字内容
     *\param[in]    int textLen 文字长
     *\param[in]    bool newLen 新行
     *\return       void 0成功,其它失败
     */
    void drawLineText(const char *text, int textLen, bool newLen, bool unicode);

    /*
     *\fn         int outputText((const char *text, int textLen)
     *\brief      输出文字
     *\param[in]  const char * text 文字内容
     *\param[in]  int textLen 文字长
     *\return     int 0成功,其它失败
     */
    int outputText(const char *text, int textLen);

    /**
     *\fn           int processCmd(const char *text)
     *\brief        处理命令
     *\param[in]    const char * text 命令字符
     *\return       int 0成功,其它失败
     */
    int processCmd(const char *text);

    /**
     *\fn           void moveCursor(UINT x, UINT y)
     *\brief        移动光标
     *\param[in]    UINT x 光标X轴位置
     *\param[in]    UINT y 光标Y轴位置
     *\return       void 无
     */
    void moveCursor(UINT x, UINT y);

    /**
     *\fn           void setColor(UINT count, UINT *data)
     *\brief        设置颜色
     *\param[in]    UINT count 数据个数
     *\param[in]    UINT * data 数据
     *\return       void 无
     */
    void setColor(UINT count, UINT *data);

    /**
     *\fn           UINT getCurPagePos()
     *\brief        得到当前页顶位置
     *\return       UINT 当前页页顶位置
     */
    UINT getCurPagePos();

    /**
     *\fn           UINT getTailPagePos()
     *\brief        得到尾页页顶位置
     *\return       UINT 尾页页顶位置
     */
    UINT getTailPagePos();

    /**
     *\fn           void setNewCmd()
     *\brief        标记新命令
     *\return       void 无
     */
    void setNewCmd() { lastCursorY_ = 0; }
};


