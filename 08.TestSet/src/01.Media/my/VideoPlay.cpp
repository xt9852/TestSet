
#include "stdafx.h"
#include "VideoPlay.h"

VideoPlay::VideoPlay()
    :x_(0),
    y_(0),
    dc_(NULL),
    drawDib_(NULL)
{
}

VideoPlay::~VideoPlay()
{

}

/**
 *\fn           int init(int cx, int cy, HDC dc, LPBITMAPINFOHEADER bmpInfo)
 *\brief        初始化
 *\param[in]    int x 横坐标
 *\param[in]    int y 纵坐标
 *\param[in]    HDC dc DC句柄
 *\param[in]    LPBITMAPINFOHEADER bmpInfo 图像信息
 *\return       int 0成功,其它失败
 */
int VideoPlay::init(int x, int y, HDC dc, LPBITMAPINFOHEADER bmpInfo)
{
    if (NULL == dc) return E_VP_PARAM_NULL;
    if (NULL != drawDib_) return E_VP_INITED;

    x_ = x;
    y_ = y;
    dc_ = dc;
    bmpInfo_ = *bmpInfo;
    bmpInfo_.biBitCount = 24;
    bmpInfo_.biCompression = BI_RGB;
    bmpInfo_.biSizeImage = bmpInfo_.biWidth * bmpInfo_.biHeight * 3;

    drawDib_ = DrawDibOpen();

    return !::DrawDibBegin(drawDib_, dc, -1, -1, &bmpInfo_, bmpInfo_.biWidth, bmpInfo_.biHeight, 0);
}

/**
 *\fn           void uninit()
 *\brief        返初始化
 *\return       void 无
 */
void VideoPlay::uninit()
{
    ::DrawDibClose(drawDib_);
}

/**
 *\fn           int send(void *data)
 *\brief        播放视频
 *\param[in]    void * data 视频数据
 *\return       int 0成功,其它失败
 */
int VideoPlay::send(void *data)
{
    PFRAMEINFO frame = (PFRAMEINFO)data;

    if (NULL == frame || NULL == frame->data || 0 == frame->len) return E_VP_PARAM_NULL;

    DrawDibDraw(drawDib_, dc_, x_, y_, -1, -1, &bmpInfo_, frame->data, 
        0, 0, bmpInfo_.biWidth, bmpInfo_.biHeight, DDF_SAME_DRAW);

    MeidaLayout::send(data);

    return 0;
}

/**
 *\fn           int recv(void *data)
 *\brief        播放视频
 *\param[in]    void * data 视频数据
 *\return       int 0成功,其它失败
 */
int VideoPlay::recv(void *data)
{
    PFRAMEINFO frame = (PFRAMEINFO)data;

    if (NULL == frame || NULL == frame->data || 0 == frame->len) return E_VP_PARAM_NULL;

    DrawDibDraw(drawDib_, dc_, x_, y_, -1, -1, &bmpInfo_, frame->data, 
        0, 0, bmpInfo_.biWidth, bmpInfo_.biHeight, DDF_SAME_DRAW);

    MeidaLayout::recv(data);

    return 0;
}
