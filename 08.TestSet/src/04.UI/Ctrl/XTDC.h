
/**
双缓冲DC，主要有三个DC，一个窗体DC，一个兼容DC（载有一个兼容位图），载有背影图片的DC
*/

#pragma once
#include "../PNG.h"
#include <map>

typedef struct _tagXTDC
{
    HDC     dc;
    HGDIOBJ image;
    HGDIOBJ oldImage;
    void    *data;

    _tagXTDC::_tagXTDC()
    {
        dc = NULL;
        image = NULL;
        oldImage = NULL;
        data = NULL;
    }

}XTDC, *PXTDC;

typedef std::map<int, XTDC> XTDCMAP;

enum { WNDDC, COMPDC, IMAGEDC };

/**
*\class  CXTDC
*\brief  该类双缓冲DC，主要有三个DC，一个窗体DC，一个兼容DC（载有一个兼容位图），载有背影图片的DC
*\date   2012-06-25
*\author 张海涛
*\par    Revision History:
*/
class CXTDC
{
public:
    CXTDC();
    ~CXTDC();

private:
    HMODULE module_;        // DLL模块句柄（包含图片）
    HWND    wnd_;           // 窗体
    XTDCMAP compDcMap_;     // 兼容DC
    XTDCMAP imageDcMap_;    // 图像DC

public:
    HDC     dc_;            // 显示DC
    HDC     curCompDC_;     // 当前兼容DC
    HDC     curImageDC_;    // 当前图像DC

public:
    /**
     *\fn           HDC Init(HMODULE module, HWND wnd, bool windowDC)
     *\brief        初始化DC
     *\param[in]    HMODULE module 模块句柄,如果为空,则加载本程序的资源,
     *\             也可module = LoadLibrary("****.dll");从DLL中加载资源
     *\param[in]    HWND wnd 窗体句柄
     *\param[in]    bool windowDC 是否使用winddowDC
     *\return       HDC 0成功,其它失败
     */
    HDC Init(HMODULE module, HWND hwnd, bool bWindowDC = false);

    /**
     *\fn           HDC AddCompDC(int id)
     *\brief        添加兼容DC
     *\param[in]    int id 兼容DCID
     *\return       兼容DC句柄
     */
    HDC AddCompDC(int id = 0);

    /**
     *\fn           HDC AddBmpDC(int id, int bmpId)
     *\brief        添加BMP图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    int bmpId 资源ID
     *\return       BMP图像DC句柄
     */
    HDC AddBmpDC(int id, int bmpId);

    /**
     *\fn           HDC AddBmpDC(int id, const char *filename)
     *\brief        从文件添加BMP图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    const char * filename BMP图片路径
     *\return       BMP图像DC句柄
     */
    HDC AddBmpDC(int id, const char *filename);

    /**
     *\fn           HDC AddPngDC(int id, int pngId)
     *\brief        添加PNG图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    int pngId 资源ID
     *\return       PNG图像DC句柄
     */
    HDC AddPngDC(int id, int pngId);

    /**
     *\fn           HDC AddPngDC(int id, const char *filename)
     *\brief        添加PNG图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    const char * filename PNG图片路径
     *\return       PNG图像DC句柄
     */
    HDC AddPngDC(int id, const char *filename);

    /**
     *\fn           HDC AddGifDC(int id, int gifId)
     *\brief        添加GIF图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    int gifId 资源ID
     *\return       GIF图像DC句柄
     */
    HDC AddGifDC(int id, int gifId);

    /**
     *\fn           HDC AddGifDC(int id, const char *filename)
     *\brief        添加GIF图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    const char * filename GIF图片路径
     *\return       GIF图像DC句柄
     */
    HDC AddGifDC(int id, const char *filename);

    /**
     *\fn           HDC AddImageDC(int id, int resId)
     *\brief        添加JPG图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    int resId 资源ID
     *\return       JPG图像DC句柄
     */
    HDC AddImageDC(int id, int resId);

    /**
     *\fn           HDC AddImageDC(int id, const char *filename)
     *\brief        添加JPG图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    const char * filename JPG图片路径
     *\return       JPG图像DC句柄
     */
    HDC AddImageDC(int id, const char *filename);

    /**
     *\fn           HDC AddNullDC(int id, int cx, int cy)
     *\brief        添加空的图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    int cx 图像宽
     *\param[in]    int cy 图像高
     *\return       图像DC句柄
     */
    HDC AddNullDC(int id, int cx, int cy);

    /**
     *\fn           HDC AddNullDC(int id, BITMAPINFO *bmi)
     *\brief        添加空的图像DC
     *\param[in]    int id 图像DC序号
     *\param[in]    BITMAPINFO * bmi 图像信息
     *\return       图像DC句柄
     */
    HDC AddNullDC(int id, BITMAPINFO *bmi);

    /**
     *\fn           HDC GetHDC(int type, int id)
     *\brief        得到DC
     *\param[in]    int type DC类型:WNDDC, COMPDC, IMAGEDC
     *\param[in]    int id DC序号
     *\return       HDC 0成功,其它失败
     */
    HDC GetHDC(int type, int id);

    /**
     *\fn           HDC GetCurImageDC()
     *\brief        得到当前的图像DC
     *\return       当前的图像DC
     */
    HDC GetCurImageDC() { return curImageDC_; }

    /**
     *\fn           HDC SelectImageDC(int id)
     *\brief        选取图像ID
     *\param[in]    int id 图像DC序号
     *\return       图像DC句柄
     */
    HDC SelectImageDC(int id);

    /**
     *\fn           bool GetBmpRect(int id, int &cx, int &cy)
     *\brief        得到BMP图像DC的宽高
     *\param[in]    int id 图像DC的序号
     *\param[out]   int & cx 宽
     *\param[out]   int & cy 高
     *\return       bool 是否成功
     */
    bool GetBmpRect(int id, int &cx, int &cy);

    /**
     *\fn           void DeleteDC(int type, int id)
     *\brief        
     *\param[in]    int type DC类型:WNDDC, COMPDC, IMAGEDC
     *\param[in]    int id DC序号
     *\return       void 无
     */
    void DeleteDC(int type, int id);

    /**
     *\fn           void Release()
     *\brief        释放全部DC
     *\return       void 无
     */
    void Release();

    /**
     *\fn           void* LoadRes(int resId, const char *type)
     *\brief        加载资源
     *\param[in]    int resId 资源ID
     *\param[in]    const char * type 资源类型
     *\return       void* 资源数据
     */
    void* LoadRes(int resId, const char *type);
};
