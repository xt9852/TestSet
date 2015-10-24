

#include "stdafx.h"
#include "VideoCapture.h"

#pragma comment(lib,"vfw32")

/*
 *\fn         void YUV2_RGB(BYTE *yuv, BYTE *rgb, UINT cx, UINT cy)
 *\brief      将yuv2转成rgb,并将图像水平翻转
 *\param[in]  BYTE * yuv yuv格式数据
 *\param[out] BYTE * rgb rgb格式数据
 *\param[in]  UINT cx 图像宽
 *\param[in]  UINT cy 图像高
 *\return     void 无
 */
void YUV2_RGB(BYTE *yuv, BYTE *rgb, UINT cx, UINT cy)
{
    BYTE *pos = NULL;
    long x = 0, y = 0;
    long R = 0, G = 0, B = 0;
    long Y0 = 0, U = 0, Y1 = 0, V = 0;

    for (y = cy - 1; y >= 0; y--)
    {
        for (x = 0; x < cx; x += 2)
        {
            pos = yuv + (y * cx + x) * 2;

            Y0 = *pos;
            U  = *(pos+1);
            Y1 = *(pos+2);
            V  = *(pos+3);

            R  = 1.164383 * (Y0 - 16) + 1.596027 * (V - 128);
            G  = 1.164383 * (Y0 - 16) - 0.812968 * (V - 128) - 0.391762 * (U - 128);
            B  = 1.164383 * (Y0 - 16) + 2.017232 * (U - 128);

            if (R < 0)   R = 0;
            if (R > 255) R = 255;
            if (G < 0)   G = 0;
            if (G > 255) G = 255;
            if (B < 0)   B = 0;
            if (B > 255) B = 255;

            *rgb++ = (BYTE)B;
            *rgb++ = (BYTE)G;
            *rgb++ = (BYTE)R;

            R  = 1.164383 * (Y1 - 16) + 1.596027 * (V - 128);
            G  = 1.164383 * (Y1 - 16) - 0.812968 * (V - 128) - 0.391762 * (U - 128);
            B  = 1.164383 * (Y1 - 16) + 2.017232 * (U - 128);

            if (R < 0)   R = 0;
            if (R > 255) R = 255;
            if (G < 0)   G = 0;
            if (G > 255) G = 255;
            if (B < 0)   B = 0;
            if (B > 255) B = 255;

            *rgb++ = (BYTE)B;
            *rgb++ = (BYTE)G;
            *rgb++ = (BYTE)R;
        }
    }
}

/**
 *\fn           LRESULT CALLBACK OnCaptureVideo(HWND wnd, LPVIDEOHDR lphdr)
 *\brief        设备回调
 *\param[in]    HWND wnd 用户自定义数据
 *\param[in]    LPVIDEOHDR lphdr 视频数据
 *\return       LRESULT CALLBACK 0成功,其它失败
 */
LRESULT CALLBACK OnCaptureVideo(HWND wnd, LPVIDEOHDR lphdr)
{
    try
    {
        VideoCapture *pThis = (VideoCapture*)capGetUserData(wnd);

        if (NULL != pThis && !pThis->isStop())
        {
            FRAMEINFO frame = {0};
            frame.len = lphdr->dwBytesUsed;
            frame.data = lphdr->lpData;
            pThis->send(&frame);
        }
    }
    catch(...)
    {
        TRACE(_T("VideoCapture.OnCaptureVideo Error %d\n"), ::GetLastError());
        return FALSE;
    }

    return TRUE;
}


VideoCapture::VideoCapture()
    :wndCap_(NULL),
    isStop_(FALSE)
{
    buf_ = new BYTE[1024*1024];
    memset(&bmpInfo_, 0, sizeof(bmpInfo_));
}

VideoCapture::~VideoCapture()
{
    delete[] buf_;
    uninit();
}

/**
 *\fn           int init(int cx, int cy)
 *\brief        初始化视频捕获
 *\param[in]    int cx 宽
 *\param[in]    int cy 高
 *\return       int 0成功,其它失败
 */
int VideoCapture::init(int cx, int cy)
{
    int index = 0;
    TCHAR devName[100] = _T("");
    TCHAR devVersion[100] = _T("");

    if (NULL != wndCap_)
    {
        return E_VC_INITED;
    }

    wndCap_ = capCreateCaptureWindow(_T("Capture"), WS_POPUP, 0, 0, 1, 1, 0, 0);

    if (NULL == wndCap_)
    {
        return E_VC_CREATECAPTURE;
    }

    //stopCapture();

    // 设置回调参数
    capSetUserData(wndCap_, this);

    // 设置回调函数
    capSetCallbackOnVideoStream(wndCap_, OnCaptureVideo);

    // 得到设置信息
    capGetDriverDescription(index, devName, sizeof(devName)/sizeof(devName[0]), 
        devVersion, sizeof(devVersion)/sizeof(devVersion[0]));

    // 连接设备
    if (!capDriverConnect(wndCap_, index))
    {
        TRACE("%s capDriverConnect=%d\n", __FUNCTION__, GetLastError());
        return E_VC_DRIVERCONNECT;
    }

    // 设置参数
    if (0 != setCaptureParam(cx, cy))
    {
        capDriverDisconnect(wndCap_);
        return E_VC_SETCAPTUREPARAM;
    }

    return 0;
}

/**
 *\fn           int setCaptureParam(int cx, int cy)
 *\brief        设置参数
 *\param[in]    int cx 宽
 *\param[in]    int cy 高
 *\return       int 0成功,其它失败
 */
int VideoCapture::setCaptureParam(int cx, int cy)
{
    CAPTUREPARMS capParms = {0};

    capCaptureGetSetup(wndCap_, &capParms, sizeof(capParms));

    capParms.wStepCaptureAverageFrames = 100;
    capParms.dwRequestMicroSecPerFrame = 1000000/6;// 每秒6帧;
    capParms.fAbortLeftMouse = FALSE;
    capParms.fAbortRightMouse = FALSE;
    capParms.fYield = TRUE;
    capParms.fCaptureAudio = FALSE;
    capParms.wPercentDropForError = 50;

    if (!capCaptureSetSetup(wndCap_, &capParms, sizeof(capParms)))
    {
        return E_VC_SETCAPTUREPARAM;
    }

    capGetVideoFormat(wndCap_, &bmpInfo_, sizeof(BITMAPINFO));

    bmpInfo_.bmiHeader.biWidth = cx;
    bmpInfo_.bmiHeader.biHeight = cy;
    bmpInfo_.bmiHeader.biBitCount = 16;
    bmpInfo_.bmiHeader.biSizeImage = cx * cy * 2;
    bmpInfo_.bmiHeader.biCompression = 844715353; // YUV2

    if (!capSetVideoFormat(wndCap_, &bmpInfo_.bmiHeader, sizeof(BITMAPINFOHEADER)))
    {
        return E_VC_SETCAPTUREPARAM;
    }

    return 0;
}

/**
 *\fn           void Uninit()
 *\brief        返初始化
 *\return       void 无
 */
void VideoCapture::uninit()
{
    if (NULL == wndCap_) return;

    stopCapture();

    Sleep(300);

    // 设置回调
    capSetCallbackOnVideoStream(wndCap_, NULL);

    Sleep(300);

    capDriverDisconnect(wndCap_);

    wndCap_ = NULL;
}

/**
 *\fn           int startCapture()
 *\brief        开始捕获视频
 *\return       int 0成功,其它失败
 */
int VideoCapture::startCapture()
{
    if (capCaptureSequenceNoFile(wndCap_) == FALSE)
    {
        return E_VC_STARTCAPTURE;
    }

    isStop_ = false;

    return 0;
}

/**
 *\fn           int stopCapture()
 *\brief        停止捕获视频
 *\return       int 0成功,其它失败
 */
int VideoCapture::stopCapture()
{
    capCaptureStop(wndCap_);
    capCaptureAbort(wndCap_);

    isStop_ = true;

    return 0;
}

/**
 *\fn           int send(void *data)
 *\brief        发送数据
 *\param[in]    void * data 视频数据
 *\return       int 0成功,其它失败
 */
int VideoCapture::send(void *data)
{
    FRAMEINFO out = {0};
    PFRAMEINFO frame = (PFRAMEINFO)data;

    if (NULL == frame || NULL == frame->data || 0 == frame->len) return E_VC_PARAM_NULL;

    out.data = buf_;
    out.len = bmpInfo_.bmiHeader.biWidth * bmpInfo_.bmiHeader.biHeight * 3;

    //saveBmp(".\\VideoCapture.bmp", getBmpInfoHeader(), (LPBYTE)frame->data);

    YUV2_RGB((BYTE*)frame->data, (BYTE*)out.data, bmpInfo_.bmiHeader.biWidth, bmpInfo_.bmiHeader.biHeight);

    return MeidaLayout::send(&out);
}

/**
 *\fn           BITMAPINFOHEADER* getBmpInfoHeader()
 *\brief        得到位图信息
 *\return       BITMAPINFOHEADER* 位图信息
 */
BITMAPINFOHEADER* VideoCapture::getBmpInfoHeader()
{
    return &(bmpInfo_.bmiHeader);
}



/**
 *\fn           int saveBmp(LPCSTR fileName, BITMAPINFOHEADER *bitInfo, LPBYTE data)
 *\brief        保存bmp图像
 *\param[in]    LPCSTR fileName 文件名
 *\param[in]    BITMAPINFOHEADER * bitInfo 图片信息
 *\param[in]    LPBYTE data 图片数据
 *\return       int 0成功,其它失败
 */
int VideoCapture::saveBmp(LPCSTR fileName, BITMAPINFOHEADER *bitInfo, LPBYTE data)
{
    if (NULL == fileName || NULL == bitInfo || NULL == data) return E_VC_PARAM_NULL;

    BITMAPINFOHEADER bmih = *bitInfo;
    bmih.biBitCount = 24;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = 3 * bmih.biHeight * bmih.biWidth;

    BITMAPFILEHEADER bmfh = {0};
    bmfh.bfType = 0x4D42;   // "BM"
    bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bmfh.bfSize = bmfh.bfOffBits + bitInfo->biSizeImage;

    BYTE *buf = new BYTE[bmih.biSizeImage];

    // vfw得到的是yuv2的,将其转为RGB
    YUV2_RGB(data, buf, bmih.biWidth, bmih.biHeight);

    FILE *file = fopen(fileName, "w+b");

    if (NULL == file)
    {
        delete[] buf;
        return E_VC_OPENFILE;
    }

    fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), file);
    fwrite(&bmih, 1, sizeof(BITMAPINFOHEADER), file);
    fwrite(buf, 1, bmih.biSizeImage, file);
    fclose(file);
    delete[] buf;
    return 0;
}





