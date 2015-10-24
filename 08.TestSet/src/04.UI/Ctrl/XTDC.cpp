
#include "stdafx.h"
#include "XTDC.h"


CXTDC::CXTDC()
    :module_(NULL),
    wnd_(NULL),
    dc_(NULL),
    curCompDC_(NULL),
    curImageDC_(NULL)
{
}

CXTDC::~CXTDC()
{
    Release();
}

void CXTDC::Release()
{
    if (NULL != dc_)
    {
        ::ReleaseDC(wnd_, dc_);
        dc_ = NULL;
    }

    XTDCMAP::iterator iter = compDcMap_.begin();
    for (; iter != compDcMap_.end(); ++iter)
    {
        XTDC xtDC = (*iter).second;

        if (xtDC.dc && xtDC.oldImage)
        {
            SelectObject(xtDC.dc, xtDC.oldImage);
        }

        if (xtDC.dc)
        {
            ::DeleteDC(xtDC.dc);
        }

        if (xtDC.image)
        {
            DeleteObject(xtDC.image);
        }

        if (xtDC.data)
        {
            delete xtDC.data;
        }
    }

    compDcMap_.clear();

    iter = imageDcMap_.begin();
    for (; iter != imageDcMap_.end(); ++iter)
    {
        XTDC xtDC = (*iter).second;

        if (xtDC.dc && xtDC.oldImage)
        {
            SelectObject(xtDC.dc, xtDC.oldImage);
        }

        if (xtDC.dc)
        {
            ::DeleteDC(xtDC.dc);
        }

        if (xtDC.image)
        {
            DeleteObject(xtDC.image);
        }
    }
    imageDcMap_.clear();
}

#define IN_ATL

/**
 *\fn           HDC Init(HMODULE module, HWND wnd, bool windowDC)
 *\brief        初始化DC
 *\param[in]    HMODULE module 模块句柄,如果为空,则加载本程序的资源,
 *\             也可module = LoadLibrary("****.dll");从DLL中加载资源
 *\param[in]    HWND wnd 窗体句柄
 *\param[in]    bool windowDC 是否使用winddowDC
 *\return       HDC 0成功,其它失败
 */
HDC CXTDC::Init(HMODULE module, HWND wnd, bool windowDC/* = false*/)
{
    if (NULL == module)
    {
#ifdef IN_ATL
        module_ = (HMODULE)ATL::_pModule->GetModuleInstance();
#else
        module_ = AfxGetResourceHandle();
#endif
    }
    else
    {
        module_ = module;
    }

    wnd_ = wnd;

    dc_ = windowDC ? GetWindowDC(wnd) : GetDC(wnd);

    return dc_;
}

/**
 *\fn           HDC AddCompDC(int id)
 *\brief        添加兼容DC
 *\param[in]    int id 兼容DCID
 *\return       兼容DC句柄
 */
HDC CXTDC::AddCompDC(int id)
{
    DeleteDC(COMPDC, id);

    int width = GetDeviceCaps(dc_, HORZRES);
    int height = GetDeviceCaps(dc_, VERTRES);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(dc_);
    xtDC.image = CreateCompatibleBitmap(dc_, width, height);
    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);
    compDcMap_[id] = xtDC;

    SetBkMode(xtDC.dc, TRANSPARENT);

    return xtDC.dc;
}

/**
 *\fn           HDC AddBmpDC(int id, int bmpId)
 *\brief        添加BMP图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    int bmpId 资源ID
 *\return       BMP图像DC句柄
 */
HDC CXTDC::AddBmpDC(int id, int bmpId)
{
    DeleteDC(IMAGEDC, id);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = (HGDIOBJ)LoadImage(module_, MAKEINTRESOURCE(bmpId), IMAGE_BITMAP, 0, 0, 0);

    if (NULL == xtDC.image)
    {
        return NULL;
    }

    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);

    imageDcMap_[id] = xtDC;

    return xtDC.dc;
}

/**
 *\fn           HDC AddBmpDC(int id, const char *filename)
 *\brief        从文件添加BMP图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    const char * filename BMP图片路径
 *\return       BMP图像DC句柄
 */
HDC CXTDC::AddBmpDC(int id, const char *filename)
{
    DeleteDC(IMAGEDC, id);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = LoadImage(module_, filename, IMAGE_BITMAP, 0, 0, 0);

    if (NULL == xtDC.image)
    {
        return NULL;
    }

    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);

    imageDcMap_[id] = xtDC;

    return xtDC.dc;
}

/**
 *\fn           HDC AddPngDC(int id, int pngId)
 *\brief        添加PNG图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    int pngId 资源ID
 *\return       PNG图像DC句柄
 */
HDC CXTDC::AddPngDC(int id, int pngId)
{
    DeleteDC(IMAGEDC, id);

    CPNG *png = new CPNG; // PNG文件

    if (!png->Load(module_, pngId)) return false;

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = CreateCompatibleBitmap(dc_, png->getWidth(), png->getHeight());
    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);
    xtDC.data = png;

    png->Draw(xtDC.dc, 0, 0);

    imageDcMap_[id] = xtDC;

    return xtDC.dc;
}

/**
 *\fn           HDC AddPngDC(int id, const char *filename)
 *\brief        添加PNG图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    const char * filename PNG图片路径
 *\return       PNG图像DC句柄
 */
HDC CXTDC::AddPngDC(int /*id*/, const char * /*filename*/)
{
    return NULL;
}

/**
 *\fn           HDC AddGifDC(int id, int gifId)
 *\brief        添加GIF图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    int gifId 资源ID
 *\return       GIF图像DC句柄
 */
HDC CXTDC::AddGifDC(int /*id*/, int /*gifId*/)
{
    return NULL;
}

/**
 *\fn           HDC AddGifDC(int id, const char *filename)
 *\brief        添加GIF图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    const char * filename GIF图片路径
 *\return       GIF图像DC句柄
 */
HDC CXTDC::AddGifDC(int /*id*/, const char * /*filename*/)
{
    return NULL;
}

/**
 *\fn           HDC AddImageDC(int id, int resId)
 *\brief        添加JPG图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    int resId 资源ID
 *\return       JPG图像DC句柄
 */
HDC CXTDC::AddImageDC(int id, int resId)
{
    DeleteDC(IMAGEDC, id);

    HRSRC   res     = FindResource(module_, MAKEINTRESOURCE(resId), _T("jpg"));
    HGLOBAL resData = LoadResource(module_, (HRSRC)res);
    DWORD   resSize = SizeofResource(module_, (HRSRC)res);

    if (NULL == resData)
    {
        return NULL;
    }

    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, resSize);
    if (NULL == hGlobal)
    {
        return NULL;
    }

    LPVOID pvData = GlobalLock(hGlobal);// 锁定内存
    if (NULL == pvData)
    {
        FreeResource(resData);
        GlobalFree(hGlobal);
        return NULL;
    }

    LockResource(resData);              // 锁定资源
    memcpy(pvData, resData, resSize);   // 载入内存
    GlobalUnlock(hGlobal);              // 解锁内存
    FreeResource(resData);              // 释放资源

    CComPtr<IStream> spStream = NULL;
    HRESULT hr = ::CreateStreamOnHGlobal(hGlobal, TRUE, &spStream); // 建立IStream
    if (!SUCCEEDED(hr))
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    CComPtr<IPicture> spPicture;
    hr = OleLoadPicture(spStream, resSize, FALSE, IID_IPicture, (LPVOID*)&spPicture);   // 建立IPicture
    if (!SUCCEEDED(hr))
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    GlobalFree(hGlobal);

    OLE_HANDLE picHandle = NULL;
    spPicture->get_Handle(&picHandle);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = (HGDIOBJ)picHandle;
    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);

    imageDcMap_[id] = xtDC;

    return xtDC.dc;
}

/**
 *\fn           HDC AddImageDC(int id, const char *filename)
 *\brief        添加JPG图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    const char * filename JPG图片路径
 *\return       JPG图像DC句柄
 */
HDC CXTDC::AddImageDC(int id, const char *filename)
{
    DeleteDC(IMAGEDC, id);

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, &sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)	return NULL;

    DWORD dwFileSize = GetFileSize(hFile, NULL);

    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
    if (NULL == hGlobal) return false;

    LPVOID pvData = GlobalLock(hGlobal);// 锁定内存
    if (NULL == pvData)
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    DWORD dwReadLen = 0;
    if (!ReadFile(hFile, pvData, dwFileSize, &dwReadLen, NULL))
    {
        GlobalFree(hGlobal);
        CloseHandle(hFile);
        return false;
    }

    if (dwReadLen != dwFileSize)
    {
        GlobalFree(hGlobal);
        CloseHandle(hFile);
        return false;
    }

    GlobalUnlock(hGlobal);
    CloseHandle(hFile);

    CComPtr<IStream> spStream = NULL;
    HRESULT hr = ::CreateStreamOnHGlobal(hGlobal, TRUE, &spStream);// 建立IStream
    if (!SUCCEEDED(hr))
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    CComPtr<IPicture> spPicture;
    hr = OleLoadPicture(spStream, dwFileSize, FALSE, IID_IPicture, (LPVOID*)&spPicture);// 建立IPicture
    if (!SUCCEEDED(hr))
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    GlobalFree(hGlobal);

    OLE_HANDLE picHandle = NULL;
    spPicture->get_Handle(&picHandle);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = (HGDIOBJ)picHandle;
    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);

    imageDcMap_[id] = xtDC;

    return xtDC.dc;
}

/**
 *\fn           HDC AddNullDC(int id, int cx, int cy)
 *\brief        添加空的图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       图像DC句柄
 */
HDC CXTDC::AddNullDC(int id, int cx, int cy)
{
    DeleteDC(IMAGEDC, id);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = CreateCompatibleBitmap(dc_, cx, cy);
    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);

    imageDcMap_[id] = xtDC;

    FloodFill(xtDC.dc, 0, 0, RGB(0, 0, 0));

    return xtDC.dc;
}

/**
 *\fn           HDC AddNullDC(int id, BITMAPINFO *bmi)
 *\brief        添加空的图像DC
 *\param[in]    int id 图像DC序号
 *\param[in]    BITMAPINFO * bmi 图像信息
 *\return       图像DC句柄
 */
HDC CXTDC::AddNullDC(int id, BITMAPINFO *bmi)
{
    if (NULL == bmi) return NULL;

    DeleteDC(IMAGEDC, id);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = ::CreateDIBSection(xtDC.dc, bmi, DIB_RGB_COLORS, &xtDC.data, NULL, 0); // 系统会自己释放xtDC.data的
    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);

    imageDcMap_[id] = xtDC;

    return (NULL != xtDC.image) ? xtDC.dc : NULL;
}

/**
 *\fn           HDC SelectImageDC(int id)
 *\brief        选取图像ID
 *\param[in]    int id 图像DC序号
 *\return       图像DC句柄
 */
HDC CXTDC::SelectImageDC(int id)
{
    int cx = 0;
    int cy = 0;

    if (GetBmpRect(id, cx, cy))
    {
        curImageDC_ = GetHDC(IMAGEDC, id);
        ::BitBlt(curCompDC_, 0, 0, cx, cy, curImageDC_, 0, 0, SRCCOPY);		
        return curImageDC_;
    }

    return NULL;
}

/**
 *\fn           void DeleteDC(int type, int id)
 *\brief        
 *\param[in]    int type DC类型:WNDDC, COMPDC, IMAGEDC
 *\param[in]    int id DC序号
 *\return       void 无
 */
void CXTDC::DeleteDC(int type, int id)
{
    if (COMPDC == type)
    {
        XTDCMAP::iterator iter = compDcMap_.find(id);
        if (compDcMap_.end() != iter)
        {
            XTDC xtDC = (*iter).second;
            if (xtDC.dc && xtDC.oldImage)
            {
                SelectObject(xtDC.dc, xtDC.oldImage);
            }

            if (xtDC.dc)
            {
                ::DeleteDC(xtDC.dc);
            }

            xtDC.dc = NULL;
            xtDC.image = NULL;
            xtDC.oldImage = NULL;

            compDcMap_.erase(id);
        }
    }
    else
    {
        XTDCMAP::iterator iter = imageDcMap_.find(id);
        if (imageDcMap_.end() != iter)
        {
            XTDC xtDC = (*iter).second;
            if (xtDC.dc && xtDC.oldImage)
            {
                SelectObject(xtDC.dc, xtDC.oldImage);
            }

            if (xtDC.dc)
            {
                ::DeleteDC(xtDC.dc);
            }

            xtDC.dc = NULL;
            xtDC.image = NULL;
            xtDC.oldImage = NULL;

            imageDcMap_.erase(id);
        }
    }
}

/**
 *\fn           HDC GetHDC(int type, int id)
 *\brief        得到DC
 *\param[in]    int type DC类型:WNDDC, COMPDC, IMAGEDC
 *\param[in]    int id DC序号
 *\return       HDC 0成功,其它失败
 */
HDC CXTDC::GetHDC(int type, int id /*= 0*/)
{
    switch (type)
    {
    case WNDDC:
        {
            return dc_;
        }
    case COMPDC:
        {
            XTDCMAP::iterator iter = compDcMap_.find(id);
            if (compDcMap_.end() != iter)
            {
                return (*iter).second.dc;
            }
            break;
        }
    default:
        {
            XTDCMAP::iterator iter = imageDcMap_.find(id);
            if (imageDcMap_.end() != iter)
            {
                return (*iter).second.dc;
            }
            break;
        }
    }
    return NULL;
}

/**
 *\fn           bool GetBmpRect(int id, int &cx, int &cy)
 *\brief        得到BMP图像DC的宽高
 *\param[in]    int id 图像DC的序号
 *\param[out]   int & cx 宽
 *\param[out]   int & cy 高
 *\return       bool 是否成功
 */
bool CXTDC::GetBmpRect(int id, int &cx, int &cy)
{
    XTDCMAP::iterator iter = imageDcMap_.find(id);
    if (imageDcMap_.end() != iter)
    {
        BITMAP bmpInfo = {0};
        GetObject((*iter).second.image, sizeof(bmpInfo), &bmpInfo);	// 得到位图信息
        cx = bmpInfo.bmWidth;
        cy = bmpInfo.bmHeight;
        return true;
    }
    return false;
}

/**
 *\fn           void* LoadRes(int resId, const char *type)
 *\brief        加载资源
 *\param[in]    int resId 资源ID
 *\param[in]    const char * type 资源类型
 *\return       void* 资源数据
 */
void* CXTDC::LoadRes(int resId, const char *type)
{
    HRSRC   res     = FindResource(module_, MAKEINTRESOURCE(resId), type);
    HGLOBAL resData = LoadResource(module_, (HRSRC)res);
    DWORD   resSize = SizeofResource(module_, (HRSRC)res);

    if (NULL == resData)
    {
        return NULL;
    }

    void *data = new char[resSize];

    ::LockResource(resData);        // 锁定资源
    memcpy(data, resData, resSize); // 载入内存
    ::FreeResource(resData);        // 释放资源

    return data;
}