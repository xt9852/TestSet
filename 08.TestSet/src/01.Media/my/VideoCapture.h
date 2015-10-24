#pragma once

#include "MediaLayout.h"
#include <vfw.h>

#define IMAGE_WIDTH     176
#define IMAGE_HEIGHT    144

enum
{
    E_VC_PARAM_NULL = 1000, /*参数为空*/
    E_VC_INITED,            /*已经初始化*/
    E_VC_CREATECAPTURE,     /*创建捕获失败*/
    E_VC_DRIVERCONNECT,     /*连接设备失败*/
    E_VC_SETCAPTUREPARAM,   /*设置参数失败*/
    E_VC_STARTCAPTURE,      /*开始捕获失败*/
    E_VC_OPENFILE,          /*打开文件失败*/
};


//捕获视频
class VideoCapture : public MeidaLayout
{
public:
    VideoCapture();
    virtual ~VideoCapture();

private:
    BYTE *buf_;
    bool isStop_;
    HWND wndCap_;
    BITMAPINFO bmpInfo_;

public:
    /**
     *\fn           int init(int cx, int cy)
     *\brief        初始化视频捕获
     *\param[in]    int cx 宽
     *\param[in]    int cy 高
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
     *\fn           int startCapture()
     *\brief        开始捕获视频
     *\return       int 0成功,其它失败
     */
    int startCapture();

    /**
     *\fn           int stopCapture()
     *\brief        停止捕获视频
     *\return       int 0成功,其它失败
     */
    int stopCapture();

    /**
     *\fn           bool isStop()
     *\brief        是否已经停止
     *\return       bool true停止
     */
    bool isStop() { return isStop_; }

    /**
     *\fn           int send(void *data)
     *\brief        发送数据
     *\param[in]    void * data 视频数据
     *\return       int 0成功,其它失败
     */
    int send(void *data);

    /**
     *\fn           BITMAPINFOHEADER* getBmpInfoHeader()
     *\brief        得到位图信息
     *\return       BITMAPINFOHEADER* 位图信息
     */
    BITMAPINFOHEADER* getBmpInfoHeader();

    /**
     *\fn           int saveBmp(LPCSTR fileName, BITMAPINFOHEADER *bitInfo, LPBYTE data)
     *\brief        保存bmp图像
     *\param[in]    LPCSTR fileName 文件名
     *\param[in]    BITMAPINFOHEADER * bitInfo 图片信息
     *\param[in]    LPBYTE data 图片数据
     *\return       int 0成功,其它失败
     */
    int saveBmp(LPCSTR fileName, BITMAPINFOHEADER *bitInfo, LPBYTE data);

private:
    /**
     *\fn           int setCaptureParam(int cx, int cy)
     *\brief        设置参数
     *\param[in]    int cx 宽
     *\param[in]    int cy 高
     *\return       int 0成功,其它失败
     */
    int setCaptureParam(int cx, int cy);

    /**
     *\fn           LRESULT CALLBACK OnCaptureVideo(HWND wnd, LPVIDEOHDR lphdr)
     *\brief        设备回调
     *\param[in]    HWND wnd 用户自定义数据
     *\param[in]    LPVIDEOHDR lphdr 视频数据
     *\return       LRESULT CALLBACK 0成功,其它失败
     */
    friend LRESULT CALLBACK OnCaptureVideo(HWND wnd, LPVIDEOHDR lphdr);
};
