
#include "stdafx.h"
#include "VideoEncode.h"

VideoEncode::VideoEncode()
{
    buf_ = new BYTE[1024*1024];
}

VideoEncode::~VideoEncode()
{
    delete[] buf_;
}

/**
 *\fn           int init(int cx, int cy)
 *\brief        初始化
 *\param[in]    int cx 宽
 *\param[in]    int cy 高
 *\return       int 0成功,其它失败
 */
int VideoEncode::init(int cx, int cy)
{
    return H264_.init(cx, cy);
}

/**
 *\fn           void uninit()
 *\brief        返初始化
 *\return       void 无
 */
void VideoEncode::uninit()
{
    H264_.uninit();
}

/**
 *\fn           int send(void *data)
 *\brief        发送数据
 *\param[in]    void * data 视频数据
 *\return       int 0成功,其它失败
 */
int VideoEncode::send(void *data)
{
    FRAMEINFO out = {0};
    PFRAMEINFO frame = (PFRAMEINFO)data;

    if (NULL == frame || NULL == frame->data || 0 == frame->len) return E_VE_PARAM_NULL;

    out.data = H264_.encode((BYTE*)frame->data, out.len);

    if (NULL == out.data) return E_VE_ENCODE_FAIL;

    return MeidaLayout::send(&out);
}

/**
 *\fn           int recv(void *data)
 *\brief        接收数据
 *\param[in]    void * data 视频数据
 *\return       int 0成功,其它失败
 */
int VideoEncode::recv(void *data)
{
    FRAMEINFO out = {0};
    PFRAMEINFO frame = (PFRAMEINFO)data;

    if (NULL == frame || NULL == frame->data || 0 == frame->len) return E_VE_PARAM_NULL;

    out.data = H264_.encode((BYTE*)frame->data, out.len);

    if (NULL == out.data) return E_VE_ENCODE_FAIL;

    return MeidaLayout::recv(&out);
}