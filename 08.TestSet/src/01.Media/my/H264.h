
#pragma once
#include "H264\avcodec.h"
#include "H264\swscale.h"

// 需要引用库avcodec.lib,avformat.lib,avutil.lib
// 应用时要用avcodec.dll,avutil.dll

enum
{
    E_H264_PARAM_NULL = 1000, /*参数为空*/
    E_H264_INITED,            /*已经初始化*/
    E_H264_FIND_ENCODER,
    E_H264_FIND_DECODER,
    E_H264_OPEN_ENCODER,
    E_H264_OPEN_DECODER,
};

class CH264
{
private:
    int cx_;
    int cy_;

    AVCodec *m_pEncoder;
    AVCodec *m_pDecoder;
    
    AVCodecContext *m_pEncoder_c;
    AVCodecContext *m_pDecoder_c;

    AVFrame *m_pRgb_En_picture;
    AVFrame *m_pRgb_De_picture;
    AVFrame *m_pYuv_En_picture;
    AVFrame *m_pYuv_De_picture;

    UCHAR *m_pbyEncodeBuf;
    int m_nEncodeBufSize;
    bool m_bInit;

public:
    CH264();
    ~CH264();

public:
    /**
     *\fn           int init(int cx, int cy)
     *\brief        初始化
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

    /*                         s
     *\fn         BYTE* encode(BYTE *data, int &outLen)
     *\brief      H264编码
     *\param[in]  BYTE * data  视频数据
     *\param[out] int & outLen 编码后的数据长
     *\return     BYTE* 编码后的数据
     */
    BYTE* encode(BYTE *data, int &outLen);
    
    /*
     *\fn         BYTE* decode(BYTE *data, int inLen, int &outLen)
     *\brief      H264解码
     *\param[in]  BYTE * data 编码后的数据
     *\param[in]  int inLen 编码后的数据长
     *\param[out] int & outLen 解码后的数据长
     *\return     BYTE* 0成功,其它失败
     */
    BYTE* decode(BYTE *data, int inLen, int &outLen);
};
