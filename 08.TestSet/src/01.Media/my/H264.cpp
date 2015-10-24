
#include "StdAfx.h"
#include "H264.h"


#pragma comment(lib, "../10.thirdParty/lib/h264/avutil.lib")
#pragma comment(lib, "../10.thirdParty/lib/h264/avcodec.lib")
#pragma comment(lib, "../10.thirdParty/lib/h264/avformat.lib")


CH264::CH264()
    :cx_(0),
    cy_(0),
    m_pEncoder(NULL),
    m_pDecoder(NULL),
    m_pEncoder_c(NULL),
    m_pDecoder_c(NULL),
    m_pRgb_En_picture(NULL),
    m_pRgb_De_picture(NULL),
    m_pYuv_En_picture(NULL),
    m_pYuv_De_picture(NULL),
    m_bInit(false)
{
}

CH264::~CH264()
{
    uninit();
}

/**
 *\fn           int init(int cx, int cy)
 *\brief        初始化
 *\param[in]    int cx 宽
 *\param[in]    int cy 高
 *\return       int 0成功,其它失败
 */
int CH264::init(int cx, int cy)
{
    if (m_bInit) return E_H264_INITED;

    cx_ = cx;
    cy_ = cy;

    //初始化编码库
    avcodec_init();
    avcodec_register_all();

    //编解码器的初始化
    m_pEncoder = avcodec_find_encoder(CODEC_ID_H264); // 编码器
    if (!m_pEncoder) return E_H264_FIND_ENCODER;

    m_pDecoder = avcodec_find_decoder(CODEC_ID_H264); // 解码器
    if (!m_pDecoder) return E_H264_FIND_DECODER;

    m_pEncoder_c = avcodec_alloc_context();
    m_pDecoder_c = avcodec_alloc_context();

    m_pRgb_En_picture = avcodec_alloc_frame();
    m_pRgb_De_picture = avcodec_alloc_frame();
    m_pYuv_En_picture = avcodec_alloc_frame();
    m_pYuv_De_picture = avcodec_alloc_frame();

    m_pDecoder_c->width         = cx;
    m_pDecoder_c->height        = cy;
    m_pEncoder_c->width         = cx;
    m_pEncoder_c->height        = cy;
    m_pEncoder_c->time_base.den = 25;
    m_pEncoder_c->time_base.num = 1;
    m_pEncoder_c->gop_size      = 10; // emit one intra frame every ten frames
    m_pEncoder_c->max_b_frames  = 0;
    m_pEncoder_c->pix_fmt       = PIX_FMT_YUV420P;

    if (avcodec_open(m_pEncoder_c, m_pEncoder) < 0)
    {
        TRACE(_T("could not open encodec"));
        return E_H264_OPEN_ENCODER;
    }

    if (avcodec_open(m_pDecoder_c, m_pDecoder) < 0)
    {
        TRACE(_T("could not open decodec"));
        return E_H264_OPEN_DECODER;
    }

    m_nEncodeBufSize = 1024*1024;
    m_pbyEncodeBuf = (UCHAR*)malloc(m_nEncodeBufSize);

    m_pYuv_En_picture->data[0] = (UCHAR*)malloc(cx*cy*1.5); //size for YUV 420
    m_pYuv_En_picture->data[1] = m_pYuv_En_picture->data[0] + cx*cy;
    m_pYuv_En_picture->data[2] = m_pYuv_En_picture->data[1] + cx*cy / 4;
    m_pYuv_En_picture->linesize[0] = cx;
    m_pYuv_En_picture->linesize[1] = cx / 2;
    m_pYuv_En_picture->linesize[2] = cx / 2;

    m_pRgb_De_picture->data[0] = (UCHAR*)malloc(cx*cy*3); //size for YUV 420
    m_pRgb_De_picture->data[1] = 0;
    m_pRgb_De_picture->data[2] = 0;
    m_pRgb_De_picture->linesize[0] = (cx*3+3)&~3;
    m_pRgb_De_picture->linesize[1] = 0;
    m_pRgb_De_picture->linesize[2] = 0;

    m_bInit = true;
    return 0;
}

/**
 *\fn           void uninit()
 *\brief        返初始化
 *\return       void 无
 */
void CH264::uninit()
{
    if (!m_bInit) return;

    m_bInit = FALSE;

    if (m_pbyEncodeBuf) delete[] m_pbyEncodeBuf;
    if (m_pYuv_En_picture->data[0]) delete[] m_pYuv_En_picture->data[0];
    if (m_pRgb_De_picture->data[0]) delete[] m_pRgb_De_picture->data[0];

    avcodec_close(m_pEncoder_c);
    avcodec_close(m_pDecoder_c);

    av_free(m_pEncoder_c);
    av_free(m_pDecoder_c);
    av_free(m_pRgb_En_picture);
    av_free(m_pRgb_De_picture);
    av_free(m_pYuv_En_picture);
    av_free(m_pYuv_De_picture);

}

/*
 *\fn         BYTE* encode(BYTE *data, int &outLen)
 *\brief      H264编码
 *\param[in]  BYTE * data  视频数据
 *\param[out] int & outLen 编码后的数据长
 *\return     BYTE* 编码后的数据
 */
BYTE* CH264::encode(BYTE *data, int &outLen)
{
    if (!m_bInit) return NULL;

    int nRet = avpicture_fill((AVPicture*)m_pRgb_En_picture, data, PIX_FMT_RGB24, cx_, cy_);

    try
    {
        // 转换为YUV240
        if (img_convert((AVPicture*)m_pYuv_En_picture, m_pEncoder_c->pix_fmt,
            (AVPicture*)m_pRgb_En_picture, PIX_FMT_RGB24, cx_, cy_) < 0)
        {
            TRACE("转换YUV失败！\n");
            return NULL;
        }
    }
    catch (...)
    {
        TRACE("转换YUV失败！\n");
        return NULL;
    }

    outLen = avcodec_encode_video(m_pEncoder_c, m_pbyEncodeBuf, m_nEncodeBufSize, m_pYuv_En_picture);

    return m_pbyEncodeBuf;
}

/*
 *\fn         BYTE* decode(BYTE *data, int inLen, int &outLen)
 *\brief      H264解码
 *\param[in]  BYTE * data 编码后的数据
 *\param[in]  int inLen 编码后的数据长
 *\param[out] int & outLen 解码后的数据长
 *\return     BYTE* 0成功,其它失败
 */
BYTE* CH264::decode(BYTE *data, int inLen, int &outLen)
{
    try
    {
        int nRet = avcodec_decode_video(m_pDecoder_c,m_pYuv_De_picture, &outLen, data, inLen);

        if (-1 == nRet || 0 == nRet)
        {
            TRACE("解码失败！\n");
            return NULL;
        }

        // 转换从YUV到RGB
        if (img_convert((AVPicture*)m_pRgb_De_picture, PIX_FMT_RGB24, (AVPicture*)m_pYuv_De_picture, PIX_FMT_YUV420P, cx_, cy_) < 0)
        {
            TRACE("转换RGB失败！\n");
            return NULL;
        }

        return m_pRgb_De_picture->data[0];
    }
    catch(...)
    {
        TRACE("CH264::Decode %d\n", ::GetLastError());
        return NULL;
    }
}
