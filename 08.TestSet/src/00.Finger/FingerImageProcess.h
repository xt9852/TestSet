
#pragma once

typedef unsigned char uint8;

#define PI  3.141593
#define EPI 57.29578

/*
 *\fn         int loadBitmap(const char *filename, uint8 *data, BITMAPFILEHEADER *bfh, BITMAPINFOHEADER *bih, int *cx, int *cy)
 *\brief      载入图像文件
 *\param[in]  const char * filename 文件名
 *\param[out] uint8 * data 文件数据
 *\param[out] BITMAPFILEHEADER * bfh 图像文件头
 *\param[out] BITMAPINFOHEADER * bih 图像登信息头
 *\param[out] int * cx 图像高
 *\param[out] int * cy 图像高
 *\return     int 0成功,其它失败
 */
int loadBitmap(const char *filename, uint8 *data, BITMAPFILEHEADER *bfh, BITMAPINFOHEADER *bih, int *cx, int *cy);

/**
 *\fn           int saveBitmap(const char *filename, const uint8 *data, BITMAPFILEHEADER *bfh, BITMAPINFOHEADER *bih, 
                               int cx, int cy, bool color)
 *\brief        保存图像文件
 *\param[in]    const char * filename 文件名
 *\param[in]    const uint8 * data 数据
 *\param[in]    BITMAPFILEHEADER * bfh 图像文件头
 *\param[in]    BITMAPINFOHEADER * bih 图像登信息头
 *\param[in]    int cy 图像高
 *\param[in]    int cy 图像高
 *\param[in]    int color 是否是彩色的
 *\return       int 0成功,其它失败
 */
int saveBitmap(const char *filename, const uint8 *data, BITMAPFILEHEADER *bfh, BITMAPINFOHEADER *bih, 
    int cx, int cy, bool color);

/**
 *\fn           void zoomout(uint8 *input, uint8 *output, int cx, int cy)
 *\brief        图像缩小为原来的1/4
 *\param[in]    uint8 * input 输入原图像数据
 *\param[in]    uint8 * output 缩小后的图像数据
 *\param[in]    int cx 原图宽
 *\param[in]    int cy 原图高
 *\return       void 无
 */
void zoomout(uint8 *input, uint8 *output, int cx, int cy);

/**
 *\fn           void getGrads(uint8* input, uint8* output, int cx, int cy, long r)
 *\brief        得到梯度场
 *\param[in]    uint8 * input 输入数据,其为原图的1/4图像
 *\param[out]   uint8 * output 输出数据,梯度场
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    long r 半径长
 *\return       void 无
 */
void getGrads(uint8* input, uint8* output, int cx, int cy, long r);
void getGradsFromZoomout(uint8* input, uint8* output, int cx, int cy, long r);
/**
 *\fn           void getOrient(uint8* input, uint8* output, int cx, int cy, long r)
 *\brief        得到方向场
 *\param[in]    uint8 * input 输入数据,其为原图的1/4图像
 *\param[out]   uint8 * output 输出数据,梯度场
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    long r 半径长
 *\return       void 无
 */
void getOrient(uint8 *input, uint8* output, int cx, int cy, long r);
void getOrientFromZoomout(uint8 *input, uint8* output, int cx, int cy, long r);

/**
 *\fn           int getBackgroundTemplate(uint8 *input, uint8 *output, int r, int threshold, int cx, int cy)
 *\brief        生成背景模板
 *\param[in]    uint8 * input 输入原图像数据
 *\param[in]    uint8 * output 背景模板:255为背景,0为前景
 *\param[in]    int r 对幅值图像高度平滑滤波的滤波器半径
 *\param[in]    int threshold 分割的阈值
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       int 0成功,其它失败
 */
int getBackgroundTemplate(uint8 *input, uint8 *output, int r, int threshold, int cx, int cy);

/**
 *\fn           void clearBackground(uint8 *input, uint8 *output, uint8* mask, int cx, int cy)
 *\brief        清除背景
 *\param[in]    uint8 * input 输入原图像
 *\param[out]   uint8 * output 清除背景图像
 *\param[in]    uint8 * mask 背景模板
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void clearBackground(uint8 *input, uint8 *output, uint8* mask, int cx, int cy);

/**
 *\fn           void equalize(uint8 *input, uint8 *output, int cx, int cy)
 *\brief        图像均衡
 *\param[in]    uint8 * input 输入原图像数据
 *\param[out]   uint8 * output 均衡后的图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void equalize(uint8 *input, uint8 *output, int cx, int cy);

/**
 *\fn           int getGaussWindowSize(double sigma)
 *\brief        得到一维高斯模板窗口大小
 *\n            这个函数可以生成一个一维的高斯函数的数字数据，理论上高斯数据的长度应
 *\n            该是无限长的，但是为了计算的简单和速度，实际的高斯数据只能是有限长的
 *\n            数组长度，根据概率论的知识，选取[-3*sigma, 3*sigma]以内的数据。
 *\n            这些数据会覆盖绝大部分的滤波系数
 *\param[in]    double sigma 高斯函数的标准差
 *\return       int 高斯模板窗口大小
 */
int getGaussWindowSize(double sigma);

/**
 *\fn           void makeGauss(double sigma, int nWindowSize, double *output)
 *\brief        生成高斯模板
 *\param[in]    double sigma 高斯函数的标准差
 *\param[in]    int nWindowSize 窗口大小
 *\param[out]   double * output 高斯模板
 *\return       void 无
 */
void makeGauss(double sigma, int nWindowSize, double *output);

/**
 *\fn           void gaussSmooth(uint8 *input, uint8 *output, int cx, int cy, double sigma)
 *\brief        高斯平滑
 *\param[in]    uint8 * input 输入数据原图
 *\param[out]   uint8 * output 输出数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    double sigma 高斯函数的标准差
 *\return       void 无
 */
void gaussSmooth(uint8 *input, uint8 *output, int cx, int cy, double sigma);

/**
 *\fn           void smooth(uint8 *input, uint8 *output, int cx, int cy, int r, int d)
 *\brief        均值平滑滤波
 *\param[in]    uint8 * input 要平滑的图像数据缓冲区
 *\param[out]    uint8 * output 平滑后的图像数据缓冲区
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    int r 平滑滤波器半径
 *\param[in]    int d 平滑滤波器步长
 *\return       void 无
 */
void smooth(uint8 *input, uint8 *output, int cx, int cy, int r, int d);

/**
 *\fn           int DDIndex(int angle)
 *\brief        将灰度值向量化成12个方向值
 *\param[in]    int angle 角度 （0 - 180）
 *\return       int 12个方向值(0-11)
 */
int DDIndex(int angle);

/**
 *\fn           void orientEnhance(uint8 *input, uint8 *output, uint8 *orient, int cx, int cy)
 *\brief        通过方向场增强图像
 *\param[in]    uint8 * input 输入原图像数据
 *\param[out]   uint8 * output 输出增强后的图像数据
 *\param[in]    uint8 * orient 方向场数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void orientEnhance(uint8 *input, uint8 *output, uint8 *orient, int cx, int cy);

/**
 *\fn           void binary(uint8 *input, uint8 *output, uint8 *orient, int cx, int cy)
 *\brief        二值化图像
 *\param[in]    uint8 * input 输入原图像数据
 *\param[out]   uint8 * output 输出二值化后的图像数据
 *\param[in]    uint8 * orient 输入方向场数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void binary(uint8 *input, uint8 *output, uint8 *orient, int cx, int cy);

/**
 *\fn           void binaryClear(uint8 *input, uint8 *output, uint8 *mask, int cx, int cy)
 *\brief        对二值化指纹图像进行去噪声,去掉孤立点
 *\param[in]    uint8 * input 输入原图像数据
 *\param[in]    uint8 * output 输出去噪声后图像数据
 *\param[in]    uint8 * mask 背景模板
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void binaryClear(uint8 *input, uint8 *output, uint8 *mask, int cx, int cy);

/**
 *\fn           void thin(uint8 *input, uint8 *output, int cx, int cy)
 *\brief        图像细化
 *\param[in]    uint8 * input 输入原图像数据
 *\param[in]    uint8 * output 输出细化后的图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void thin(uint8 *input, uint8 *output, int cx, int cy);

/**
 *\fn           void thinClear(uint8 *input, uint8 *output, int cx, int cy, int len)
 *\brief        清除细化图像中短棒和毛刺
 *\param[in]    uint8 * input 输入原图像数据
 *\param[in]    uint8 * output 输出整理后的图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    int len 短棒和毛刺的最大长度
 *\return       void 无
 */
void thinClear(uint8 *input, uint8 *output, int cx, int cy, int len);

/**
 *\fn           bool isEnd(uint8 *input, int cx)
 *\brief        判断当前点是否为端点
 *\param[in]    uint8 * input 当前点
 *\param[in]    int cx 图像宽
 *\return       bool 是否为端点
 */
bool isEnd(uint8 *input, int cx);

/**
 *\fn           bool isFork(uint8 *input, int cx)
 *\brief        某点是否为叉点
 *\param[in]    uint8 * input 某点
 *\param[in]    int cx 图像宽
 *\return       bool 是否为叉点
 */
bool isFork(uint8 *input, int cx);

/**
 *\fn           int getNextPt(uint8 *pt, uint8 *last, uint8 **next, int cx, int cy)
 *\brief        得到纹线的下一个点
 *\param[in]    uint8 * pt 当前点的地址
 *\param[in]    uint8 * last 前驱点的地址
 *\param[in]    uint8 * * next 下一个点的地址的指针
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       bool 是否找到后继点
 */
bool getNextPt(uint8 *pt, uint8 *last, uint8 **next, int cx, int cy);
