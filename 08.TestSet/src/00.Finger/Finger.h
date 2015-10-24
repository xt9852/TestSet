
#pragma once
#include "FingerFeature.h"


class FingerIdentify
{
public:
    FingerIdentify();
    ~FingerIdentify();

public:
    const char *path_;      /*文件路径*/

protected:
    int cx_;                /*图像宽*/
    int cy_;                /*图像高*/
    uint8 *data_;           /*图像数据*/
    uint8 *thin_clear_;     /*图像细化整理后数据*/
    uint8 *orient_smooth_;  /*图像平滑后的方向场数据*/

    FEATURE end_;           /*端点特征*/
    FEATURE fork_;          /*叉点特征*/

    BITMAPFILEHEADER bfh_;  /*BMP文件头*/
    BITMAPINFOHEADER bih_;  /*BMP文件信息头*/

public:
    /**
     *\fn           int loadBitmap(const char *filename)
     *\brief        载入图像文件
     *\param[in]    const char * filename 文件名
     *\return       int 0成功,其它失败
     */
    int loadBitmap(const char *filename);

    /**
     *\fn           int preprocess()
     *\brief        图像预处理
     *\return       int 0成功,其它失败
     */
    int preprocess();

    /**
     *\fn           int getFeature(PFEATURE feature)
     *\brief        得特征数据
     *\param[in]    PFEATURE feature 特征数据
     *\return       int 0成功,其它失败
     */
    int getFeature(PFEATURE feature);

    /**
     *\fn           bool match(PFEATURE feature1, PFEATURE feature2)
     *\brief        比较
     *\param[in]    PFEATURE feature1 特征数据1
     *\param[in]    PFEATURE feature2 特征数据2
     *\return       int 相似度,默认阈值为50。相似度>=50则认为比对成功，否则比对失败
     */
    int match(PFEATURE feature1, PFEATURE feature2);
};
