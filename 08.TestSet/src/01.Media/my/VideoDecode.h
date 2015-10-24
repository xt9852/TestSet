#pragma once

#include "MediaLayout.h"
#include "H264.h"

enum
{
    E_VD_PARAM_NULL = 4000, /*参数为空*/
    E_VD_DECODE_FAIL,       /*解码失败*/
};

/**
 H264解码
**/
class VideoDecode : public MeidaLayout
{
public:
    VideoDecode();
    ~VideoDecode();

protected:
    BYTE *buf_;     // 缓冲区
    CH264 H264_;    // 视频H264编解码

public:
    /**
     *\fn           int init()
     *\brief        初始化
     *\return       int 0成功,其它失败
     */
    int init(int cx, int cy);

    /**
     *\fn           void uninit()
     *\brief        返初始化
     *\return       void 无
     */
    void uninit();

    /**
     *\fn           int send(void *data)
     *\brief        发送数据
     *\param[in]    void * data 视频数据
     *\return       int 0成功,其它失败
     */
    int send(void *data);

    /**
     *\fn           int recv(void *data)
     *\brief        接收数据
     *\param[in]    void * data 视频数据
     *\return       int 0成功,其它失败
     */
    int recv(void *data);
};