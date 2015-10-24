#pragma once

#include "MediaLayout.h"
#include <vfw.h>

enum
{
    E_VP_PARAM_NULL = 2000, /*参数为空*/
    E_VP_INITED,            /*已经初始化*/
    E_VP_CREATECAPTURE,     /*创建捕获失败*/
    E_VP_DRIVERCONNECT,     /*连接设备失败*/
    E_VP_SETCAPTUREPARAM,   /*设置参数失败*/
    E_VP_STARTCAPTURE,      /*开始捕获失败*/
    E_VP_OPENFILE,          /*打开文件失败*/
};

//播放视频
class VideoPlay : public MeidaLayout
{
public:
    VideoPlay();
    virtual ~VideoPlay();

protected:
    int x_;
    int y_;
    HDC dc_;
    HDRAWDIB drawDib_;
    BITMAPINFOHEADER bmpInfo_;

public:

    /**
     *\fn           int init(int cx, int cy, HDC dc, LPBITMAPINFOHEADER bmpInfo)
     *\brief        初始化
     *\param[in]    int x 横坐标
     *\param[in]    int y 纵坐标
     *\param[in]    int cx 宽
     *\param[in]    int cy 高
     *\param[in]    HDC dc DC句柄
     *\param[in]    LPBITMAPINFOHEADER bmpInfo 图像信息
     *\return       int 0成功,其它失败
     */
    int init(int x, int y, HDC dc, LPBITMAPINFOHEADER bmpInfo);

    /**
     *\fn           void uninit()
     *\brief        返初始化
     *\return       void 无
     */
    void uninit();

    /**
     *\fn           int send(void *data)
     *\brief        播放视频
     *\param[in]    void * data 视频数据
     *\return       int 0成功,其它失败
     */
    int send(void *data);

    /**
     *\fn           int recv(void *data)
     *\brief        播放视频
     *\param[in]    void * data 视频数据
     *\return       int 0成功,其它失败
     */
    int recv(void *data);
};
