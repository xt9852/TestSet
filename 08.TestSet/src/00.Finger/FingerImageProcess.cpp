#include "stdafx.h"
#include "FingerImageProcess.h"
#include <math.h>


// 根据方向场生成12个方向的索引,
// 在这12个方向上取7个点,每个点的相对位置
static const int g_DDSite[12][7][2] =
{
    -3, 0,  -2, 0,  -1, 0,   0, 0,   1, 0,   2, 0,   3, 0,
    -3,-1,  -2,-1,  -1, 0,   0, 0,   1, 0,   2, 1,   3, 1,
    -3,-2,  -2,-1,  -1,-1,   0, 0,   1, 1,   2, 1,   3, 2,
    -3,-3,  -2,-2,  -1,-1,   0, 0,   1, 1,   2, 2,   3, 3,
    -2,-3,  -1,-2,  -1,-1,   0, 0,   1, 1,   1, 2,   2, 3,
    -1,-3,  -1,-2,   0,-1,   0, 0,   0, 1,   1, 2,   1, 3,
     0,-3,   0,-2,   0,-1,   0, 0,   0, 1,   0, 2,   0, 3,
    -1, 3,  -1, 2,   0, 1,   0, 0,   0,-1,   1,-2,   1,-3,
    -2, 3,  -1, 2,  -1, 1,   0, 0,   1,-1,   1,-2,   2,-3,
    -3, 3,  -2, 2,  -1, 1,   0, 0,   1,-1,   2,-2,   3,-3,
    -3, 2,  -2, 1,  -1, 1,   0, 0,   1,-1,   2,-1,   3,-2,
    -3, 1,  -2, 1,  -1, 0,   0, 0,   1, 0,   2,-1,   3,-1
};

/**
 *\fn           void zoomout(uint8 *input, uint8 *output, int cx, int cy)
 *\brief        图像缩小为原来的1/4
 *\param[in]    uint8 * input 输入原图像数据
 *\param[in]    uint8 * output 缩小后的图像数据
 *\param[in]    int cx 原图宽
 *\param[in]    int cy 原图高
 *\return       void 无
 */
void zoomout(uint8 *input, uint8 *output, int cx, int cy)
{
    int x = 0;
    int y = 0;
    int sum = 0;
    int temp1 = 0;
    int temp2 = 0;
    int SiteD8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1};
    uint8 *src = NULL;
    uint8 *dst = NULL;

    // 边缘部分
    temp2 = cx / 2;
    for (y = 0; y < cy; y += 2)
    {
        src = input + y*cx;
        dst = output + (y/2)*temp2;
        *dst = *src;

        src = input + y*cx + cx - 1;
        dst = output + (y/2)*temp2 + (temp2 - 1);
        *dst = *src;
    }

    temp1 = (cy-1)*cx;
    temp2 = (cy/2-1)*(cx/2);
    for (x = 0; x < cx; x += 2)
    {
        src = input + x;
        dst = output + x/2;
        *dst = *src;

        src = input + x + temp1;
        dst = output + x/2 + temp2;
        *dst = *src;
    }

    // 非边缘部分用高斯模板提取低频信息
    for (y = 2; y < cy-2; y += 2)
    {
        for (x = 2; x < cx-2; x += 2)
        {
            src = input + y*cx + x;
            dst = output + (y/2)*(cx/2) + x/2;

            // 高斯模板
            // 1 2 1
            // 2 4 2
            // 1 2 1
            sum = *src*4 + *(src + SiteD8[0]) +
                *(src + SiteD8[1])*2 + *(src + SiteD8[2]) +
                *(src + SiteD8[3])*2 + *(src + SiteD8[4]) +
                *(src + SiteD8[5])*2 + *(src + SiteD8[6]) +
                *(src + SiteD8[7])*2;

            *dst = (uint8)(sum >> 4);
        }
    }
}

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
void getGradsFromZoomout(uint8* input, uint8* output, int cx, int cy, long r)
{
    long x = 0;
    long y = 0;
    long i = 0;
    long j = 0;
    long vx = 0;
    long vy = 0;
    long lvx = 0;
    long lvy = 0;;

    uint8 *src = NULL; // 原数据
    uint8 *dst = NULL; // 目录数据

    int grad = 0;       // 梯度
    int gradSum = 0;    // 梯度和
    int gradNum = 0;    // 梯度计数

    for (y = 0; y < cy / 2; y++)
    {
        for (x = 0; x < cx / 2; x++)
        {
            lvx = 0;
            lvy = 0;
            gradNum = 0;
            gradSum = 0;

            for (i = -r; i <= r; i++) // 为提高速度，步长为2
            {
                if ((y+i) < 1 || (y+i) >= (cy/2-1)) continue;

                for (j = -r; j <= r; j++) // 为提高速度，步长为2
                {
                    if ((x+j) < 1 || (x+j) >= (cx/2-1)) continue;

                    src = input + (y+i)*(cx/2) + x+j;

                    // 求x方向偏导
                    // -1 0 1
                    // -2 0 2
                    // -1 0 1
                    vx = *(src + cx/2 + 1) - *(src + cx/2 - 1) +
                        *(src + 1)*2 - *(src - 1)*2 +
                        *(src - cx/2 + 1) - *(src - cx/2 - 1);

                    // 求y方向偏导
                    // -1 -2 -1
                    //  0  0  0
                    //  1  2 -1
                    vy = *(src + cx/2 - 1) - *(src - cx/2 - 1) +
                        *(src + cx/2)*2 - *(src - cx/2)*2 +
                        *(src + cx/2 + 1) - *(src - cx/2 + 1);

                    gradSum += (abs(vx)+abs(vy));
                    gradNum++;
                }
            }

            if (gradNum == 0) gradNum = 1;

            grad = gradSum / gradNum;

            if (grad > 255) grad = 255;

            dst = output + 2*y*cx + 2*x;

            *(dst) = (uint8)grad;
            *(dst + 1) = (uint8)grad;
            *(dst + cx) = (uint8)grad;
            *(dst + cx + 1) = (uint8)grad;
        }
    }
}

void getGrads(uint8* input, uint8* output, int cx, int cy, long r)
{
}

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
void getOrientFromZoomout(uint8 *input, uint8* output, int cx, int cy, long r)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    long vx = 0;
    long vy = 0;
    long lvx = 0;
    long lvy = 0;
    long num = 0;
    long angle = 0;
    double fAngle = 0.0;
    uint8 *src = NULL;
    uint8 *dst = NULL;

    for (y = 0; y < cy / 2; y++)
    {
        for (x = 0; x < cx / 2; x++)
        {
            lvx = 0;
            lvy = 0;
            num = 0;

            for (i = -r; i <= r; i++) // 为提高速度，步长为2
            {
                if ((y+i) < 1 || (y+i) >= (cy/2-1)) continue;

                for (j = -r; j <= r; j++) // 为提高速度，步长为2
                {
                    if ((x+j) < 1 || (x+j) >= (cx/2-1)) continue;

                    src = input + (y+i)*(cx/2) + x+j;

                    //求x方向偏导
                    // -1 0 1
                    // -2 0 2
                    // -1 0 1
                    vx = *(src + cx/2 + 1) - *(src + cx/2 - 1) +
                        *(src + 1)*2 - *(src - 1)*2 +
                        *(src - cx/2 + 1) - *(src - cx/2 - 1);

                    //求y方向偏导
                    // -1 -2 -1
                    //  0  0  0
                    //  1  2 -1
                    vy = *(src + cx/2 - 1) - *(src - cx/2 - 1) +
                        *(src + cx/2)*2 - *(src - cx/2)*2 +
                        *(src + cx/2 + 1) - *(src - cx/2 + 1);

                    lvx += vx * vy * 2;//sin(2sita)
                    lvy += vx*vx - vy*vy;//cos(2sita)
                    num++;
                }
            }

            if (num == 0) num = 1;

            // 求弧度(-pi - pi)
            fAngle = atan2((double)lvy, (double)lvx);

            // 变换到(0 - 2*pi)
            if(fAngle < 0) fAngle += 2*PI;

            // 由弧度转成角度,求纹线角度
            angle = (long)(fAngle*EPI*0.5 + 0.5);

            // 因为采用sobel算子，所以角度偏转了度，所以要旋转求得的角度
            angle -= 135;

            // 角度变换到（-180）
            if(angle <= 0) angle += 180;

            angle = 180-angle;

            // 最终纹线角度
            dst = output + 2 * y * cx + 2 * x;

            *(dst) = (uint8)angle;
            *(dst + 1) = (uint8)angle;
            *(dst + cx) = (uint8)angle;
            *(dst + cx + 1) = (uint8)angle;
        }
    }
}

void getOrient(uint8 *input, uint8* output, int cx, int cy, long r)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    long vx = 0;
    long vy = 0;
    long lvx = 0;
    long lvy = 0;
    long num = 0;
    long angle = 0;
    double fAngle = 0.0;
    uint8 *src = NULL;
    uint8 *dst = NULL;

    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            lvx = 0;
            lvy = 0;
            num = 0;

            for (i = -r; i <= r; i++)
            {
                if ((y+i) < 1 || (y+i) >= (cy-1)) continue;

                for (j = -r; j <= r; j++)
                {
                    if ((x+j) < 1 || (x+j) >= (cx-1)) continue;

                    src = input + (y+i)*cx + x+j;

                    //求x方向偏导
                    // -1 0 1
                    // -2 0 2
                    // -1 0 1
                    vx = *(src + cx + 1) - *(src + cx - 1) +
                        *(src + 1)*2 - *(src - 1)*2 +
                        *(src - cx + 1) - *(src - cx - 1);

                    //求y方向偏导
                    // -1 -2 -1
                    //  0  0  0
                    //  1  2 -1
                    vy = *(src + cx - 1) - *(src - cx - 1) +
                        *(src + cx)*2 - *(src - cx)*2 +
                        *(src + cx + 1) - *(src - cx + 1);

                    lvx += vx * vy * 2;//sin(2sita)
                    lvy += vx*vx - vy*vy;//cos(2sita)
                    num++;
                }
            }

            if (num == 0) num = 1;

            // 求弧度(-pi - pi)
            fAngle = atan2((double)lvy, (double)lvx);

            // 变换到(0 - 2*pi)
            if(fAngle < 0) fAngle += 2*PI;

            // 由弧度转成角度,求纹线角度
            angle = (long)(fAngle*EPI*0.5 + 0.5);

            // 因为采用sobel算子，所以角度偏转了度，所以要旋转求得的角度
            angle -= 135;

            // 角度变换到（-180）
            if(angle <= 0) angle += 180;

            angle = 180-angle;

            // 最终纹线角度
            dst = output + y * cx + x;

            *(dst) = (uint8)angle;
//             *(dst + 1) = (uint8)angle;
//             *(dst + cx) = (uint8)angle;
//             *(dst + cx + 1) = (uint8)angle;
        }
    }
}

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
int getBackgroundTemplate(uint8 *input, uint8 *output, int r, int threshold, int cx, int cy)
{
    int x = 0;
    int y = 0;
    int num = 0;
    int lineBegin= 0;
    uint8 *src = NULL;

    // 对方向场幅值图像进行高度平滑滤波
    smooth(input, output, cx, cy, r, 2);

    // 图像边缘均设置为背景

    num = cx - 1;

    for (y = 0; y < cy; y++)
    {
        src = output + y*cx;

        *(src) = 255;
        *(src + num) = 255;
    }

    num = (cy-1)*cx;

    for (x = 0; x < cx; x++)
    {
        src = output + x;

        *(src) = 255;
        *(src + num) = 255;
    }

    num = 0;
    lineBegin = cx;

    for (y = 1; y < cy-1; y++)
    {
        for (x = 1; x < cx-1; x++)
        {
            src = output + lineBegin + x;

            // 根据幅值与阈值大小判断是否为背景区域
            if (*src < threshold)
            {
                *src = 0;
            }
            else
            {
                *src = 255;
                num++;
            }
        }

        lineBegin += cx;
    }

    // 如果前景区域面积小于总面积的十分之一，则表示前景区域太小，返回错误
    return ((num < (cx * cy / 10)) ? 1 : 0);
}

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
void clearBackground(uint8 *input, uint8 *output, uint8* mask, int cx, int cy)
{
    int x = 0;
    int y = 0;
    int pos = 0;
    int lineBegin = 0;

    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            pos = lineBegin + x;

            // 如果是背景区域，则置该点为白点
            if (*(mask + pos) == 0)
            {
                *(output + pos) = 255;
            }
            else
            {
                *(output + pos) = *(input + pos);
            }
        }

        lineBegin += cx;
    }
}

/**
 *\fn           void equalize(uint8 *input, uint8 *output, int cx, int cy)
 *\brief        图像均衡
 *\param[in]    uint8 * input 输入原图像数据
 *\param[out]   uint8 * output 均衡后的图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void equalize(uint8 *input, uint8 *output, int cx, int cy)
{
    // 灰度计数表
    int lCount[256] = {0};

    // 灰度映射表
    uint8 bMap[256] = {0};

    // 指向源图像的指针
    uint8* src = NULL;
    uint8* dst = NULL;

    // 临时变量
    int lTemp = 0;
    int lineBegin = 0;

    // 循环变量
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;

    // 计算各个灰度值的计数
    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            src = input + lTemp + x;

            // 计数加1
            lCount[*(src)]++;
        }

        lineBegin += cx;
    }

    // 计算灰度映射表
    for (i = 0; i < 256; i++)
    {
        // 初始为0
        lTemp = 0;

        for (j = 0; j <= i; j++)
        {
            lTemp += lCount[j];
        }

        // 计算对应的新灰度值
        bMap[i] = (uint8)(lTemp * 255 / cy / cx);
    }

    lineBegin = 0;

    // 计算新的图像
    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            src = input + lineBegin + x;
            dst = output + lineBegin + x;

            // 计算新的灰度值
            *dst = bMap[*src];
        }

        lineBegin += cx;
    }
}

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
int getGaussWindowSize(double sigma)
{
    return (int)(1 + 2 * ceil(3 * sigma));
}

/**
 *\fn           void makeGauss(double sigma, int nWindowSize, double *output)
 *\brief        生成高斯模板
 *\param[in]    double sigma 高斯函数的标准差
 *\param[in]    int nWindowSize 窗口大小
 *\param[out]   double * output 高斯模板
 *\return       void 无
 */
void makeGauss(double sigma, int nWindowSize, double *output)
{
    // 数组的中心点
    int nCenter = nWindowSize / 2;

    // 数组的某一点到中心点的距离
    double dDis = 0.0;

    // 中间变量
    double dSum = 0.0;
    double dValue = 0.0;

    // 临时变量
    int i = 0;

    // 根据一维高斯函数生成模板
    for (i = 0; i < nWindowSize; i++)
    {
        dDis = (double)(i - nCenter);
        dValue = exp(-(1/2)*dDis*dDis/(sigma*sigma)) / (sqrt(2 * PI) * sigma);
        output[i] = dValue;
        dSum += dValue;
    }

    // 归一化
    for (i = 0; i < nWindowSize; i++)
    {
        output[i] /= dSum;
    }
}

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
void gaussSmooth(uint8 *input, uint8 *output, int cx, int cy, double sigma)
{
    // 高斯滤波器的数组长度
    int nWindowSize = getGaussWindowSize(sigma);

    // 窗口长度的1/2
    int nHalfLen = nWindowSize / 2;

    // 一维高斯数据滤波器
    double *pdKernel = new double[nWindowSize];

    // 高斯系数与图像数据的点乘
    double dDotMul = 0.0;

    // 高斯滤波系数的总和
    double dWeightSum = 0.0;

    // 中间变量
    double *pdTmp = new double[cx*cy];

    // 临时变量
    int x = 0;
    int y = 0;
    int i = 0;

    // 产生一维高斯数据滤波器
    makeGauss(sigma, nWindowSize, pdKernel);

    // x方向进行滤波
    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            dDotMul = 0;
            dWeightSum = 0;

            for (i = (-nHalfLen); i <= nHalfLen; i++)
            {
                // 判断是否在图像外部
                if ((x+i) < 0 || (x+i) >= cx) continue;

                dDotMul += (double)input[y*cx + (x+i)] * pdKernel[nHalfLen+i];
                dWeightSum += pdKernel[nHalfLen+i];
            }

            pdTmp[y*cx + x] = dDotMul/dWeightSum;
        }
    }

    // y方向进行滤波
    for (x = 0; x < cx; x++)
    {
        for (y = 0; y < cy; y++)
        {
            dDotMul = 0;
            dWeightSum = 0;

            for (i = (-nHalfLen); i <= nHalfLen; i++)
            {
                // 判断是否在图像外部
                if ((y+i) < 0 || (y+i) >= cy) continue;
                
                dDotMul += (double)pdTmp[(y+i)*cx + x] * pdKernel[nHalfLen+i];
                dWeightSum += pdKernel[nHalfLen+i];
            }

            output[y*cx + x] = (BYTE)(int)(dDotMul / dWeightSum);
        }
    }

    // 释放内存
    delete[] pdKernel;
    pdKernel = NULL;

    delete[] pdTmp;
    pdTmp = NULL;
}

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
void smooth(uint8 *input, uint8 *output, int cx, int cy, int r, int d)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    int sum = 0;
    int num = 0;
    uint8 *src = NULL;
    uint8 *dst = NULL;

    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            sum = 0;
            num = 0;
            src = input + y*cx + x;
            dst = output + y*cx + x;

            for (i = -r; i <= r; i += d)
            {
                if ((y+i) < 0 || (y+i) >= cy) continue;

                for (j = -r; j <= r; j += d)
                {
                    if ((x+j) < 0 || (x+j) >= cx) continue;

                    sum += *(src + i*cx + j);
                    num++;
                }
            }

            *dst = (uint8)(sum/num);
        }
    }
}

/**
 *\fn           int DDIndex(int angle)
 *\brief        将灰度值向量化成12个方向值
 *\param[in]    int angle 角度 （0 - 180）
 *\return       int 12个方向值(0-11)
 */
int DDIndex(int angle)
{
    if (angle >= 173 || angle < 8)
    {
        return 0;
    }
    else
    {
        return ((angle-8)/15 + 1);
    }
}

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
void orientEnhance(uint8 *input, uint8 *output, uint8 *orient, int cx, int cy)
{
    int Hw[7] = {1, 1, 1, 1, 1, 1, 1}; // 纹线方向上进行平滑滤波的平滑滤波器
    int Vw[7] = {-3, -1, 3, 9, 3, -1, -3}; // 纹线方向的垂直方向上进行锐化滤波的锐化滤波器
    uint8 *src = NULL;
    uint8 *dst = NULL;
    int x = 0;
    int y = 0;
    int i = 0;
    int d = 0;
    int sum = 0;
    int hsum = 0;
    int vsum = 0;
    int lineBegin = 0;
    uint8 *temp = new uint8[cx * cy];

    // 纹线方向上进行平滑滤波
    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            sum = 0;
            hsum = 0;
            src = input + lineBegin + x;
            d = DDIndex(*(orient + lineBegin + x)); // 纹线方向的索引

            for (i = 0; i < 7; i++)
            {
                if (y+g_DDSite[d][i][1] < 0 || y+g_DDSite[d][i][1] >= cy ||
                    x+g_DDSite[d][i][0] < 0 || x+g_DDSite[d][i][0] >= cx)
                {
                    continue;
                }

                sum += Hw[i] * (*(src + g_DDSite[d][i][1]*cx + g_DDSite[d][i][0]));
                hsum += Hw[i];
            }

            if (hsum != 0)
            {
                *(temp + lineBegin + x) = (uint8)(sum / hsum);
            }
            else
            {
                *(temp + lineBegin + x) = 255;
            }
        }

        lineBegin += cx;
    }

    // 纹线方向的垂直方向上进行锐化滤波
    lineBegin = 0;
    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            sum = 0;
            vsum = 0;
            src = temp + lineBegin + x;
            d = (DDIndex(*(orient + lineBegin + x))+6) % 12; // 纹线方向的垂直方向的索引

            for (i = 0; i < 7; i++)
            {
                if (y+g_DDSite[d][i][1] < 0 || y+g_DDSite[d][i][1] >= cy ||
                    x+g_DDSite[d][i][0] < 0 || x+g_DDSite[d][i][0] >= cx)
                {
                    continue;
                }

                sum += Vw[i] * (*(src + g_DDSite[d][i][1]*cx + g_DDSite[d][i][0]));
                vsum += Vw[i];
            }

            if (vsum > 0)
            {
                sum /= vsum;

                if (sum > 255)
                {
                    *(output + lineBegin + x) = 255;
                }
                else if (sum < 0)
                {
                    *(output + lineBegin + x) = 0;
                }
                else
                {
                    *(output + lineBegin + x) = (uint8)sum;
                }
            }
            else
            {
                *(output + lineBegin + x) = 255;
            }
        }

        lineBegin += cx;
    }

    delete[] temp;
}

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
void binary(uint8 *input, uint8 *output, uint8 *orient, int cx, int cy)
{
    int Hw[7] = {2, 2, 3, 4, 3, 2, 2}; // 纹线方向上的7个点的权值
    int Vw[7] = {1, 1, 1, 1, 1, 1, 1}; // 纹线方向的垂直方向上的7个点的权值
    int hsum = 0;   // 纹线方向上的7个点的加权和
    int vsum = 0;   // 纹线方向的垂直方向上的7个点的加权和
    int Hv = 0;     // 纹线方向上的7个点的加权平均值
    int Vv = 0;     // 纹线方向的垂直方向上的7个点的加权平均值
    uint8  *src = NULL; // 指纹图像像素点指针
    uint8  *dst = NULL; // 纹线方向指针
    int x = 0;
    int y = 0;
    int i = 0;
    int d = 0;
    int sum = 0;
    int lineBegin = 0;

    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            src = input + lineBegin + x;

            // 如果该点非常黑，则在临时缓冲区内置该点为黑点，值为0
            if (*src < 4)
            {
                *(output + lineBegin + x) = 0;
                continue;
            }

            // 计算方向索引（量化为12个方向）
            d = DDIndex(*(orient + lineBegin + x));

            // 计算当前点在纹线方向上的加权平均值
            sum = 0;
            hsum = 0;

            for (i = 0; i < 7; i++)
            {
                // 坐标是否越界
                if (y+g_DDSite[d][i][1] < 0 || y+g_DDSite[d][i][1] >= cy ||
                    x+g_DDSite[d][i][0] < 0 || x+g_DDSite[d][i][0] >= cx)
                {
                    continue;
                }

                sum += Hw[i] * (*(src + g_DDSite[d][i][1]*cx + g_DDSite[d][i][0]));
                hsum += Hw[i];
            }

            Hv = (hsum != 0) ? (sum / hsum) : 255;

            // 纹线方向的垂直方向的索引
            d = (d+6)%12;

            // 计算当前点在纹线方向的垂直方向上的加权平均值
            sum = 0;
            vsum = 0;

            for (i = 0; i < 7; i++)
            {
                if (y+g_DDSite[d][i][1] < 0 || y+g_DDSite[d][i][1] >= cy ||
                    x+g_DDSite[d][i][0] < 0 || x+g_DDSite[d][i][0] >= cx)
                {
                    continue;
                }

                sum += Vw[i] * (*(src + g_DDSite[d][i][1]*cx + g_DDSite[d][i][0]));
                vsum += Vw[i];
            }

            Vv = (vsum != 0) ? (sum / vsum) : 255;

            dst = output + lineBegin + x;

            // 纹线方向上加权平均值较小则置当前点为黑点,较大则置当前点为白点
            *dst = (Hv < Vv) ? 0 : 255;
        }

        lineBegin += cx;
    }
}

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
void binaryClear(uint8 *input, uint8 *output, uint8 *mask, int cx, int cy)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int n = 0;
    int num = 0;
    int lineBegin = 0;
    bool working = true;
    uint8 *src = NULL;
    uint8 *dst = NULL;

    // 某点周围8个点的地址偏移
    int SiteD8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1};

    // 初始化临时缓冲区
    memset(output, 0xFF, cx*cy);

    // 循环处理直到处理完毕或者处理次数超过8
    while (working && n < 8)
    {
        n++;
        working = false;
        lineBegin = cx;

        for (y = 1; y < cy-1; y++)
        {
            for (x = 1; x < cx-1; x++)
            {
                // 背景的点不处理
                if ((NULL != mask) && (*(mask + lineBegin + x) == 0)) continue;

                // 统计当前点周围与它相同类型点的个数
                num = 0;
                src = input + lineBegin + x;

                for (i = 0; i < 8; i++)
                {
                    if (*(src+SiteD8[i]) == *src)
                    {
                        num++;
                    }
                }

                // 相同点个数小于二则改变当前点类型
                dst = output + lineBegin + x;

                if (num < 2)
                {
                    *dst = 255 - *src;
                    working = true;
                }
                else
                {
                    *dst = *src;
                }
            }

            lineBegin += cx;
        }
    }
}

/**
 *\fn           void thin(uint8 *input, uint8 *output, int cx, int cy)
 *\brief        图像细化
 *\param[in]    uint8 * input 输入原图像数据
 *\param[in]    uint8 * output 输出细化后的图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\return       void 无
 */
void thin(uint8 *input, uint8 *output, int cx, int cy)
{
    uint8 eraseTable[256] =
    {
        0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
        1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
        0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
        1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
        1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
        1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,1,
        0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
        0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
        1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
        0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
        1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
        1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
        1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
        1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,0,
        1,1,0,0,1,1,1,0,             1,1,0,0,1,0,0,0
    };

    int     x = 0;
    int     y = 0;
    int     num = 0;
    int     lineBegin = cx;
    bool    finished = false;
    uint8   nw,n,ne,w,e,sw,s,se;
    uint8   *src = NULL;
    uint8   *dst = NULL;
    uint8   *buffer = new uint8[cx*cy];

    memcpy(buffer, input, cx*cy);
    memcpy(output, input, cx*cy);

    while (!finished) // 还没有结束
    {
        // 结束标志置成假
        finished = true;
        lineBegin = 0;

        // 先进行水平方向的细化
        for (y = 1; y < (cy-1); y++) //注意为防止越界，y的范围从1到高度-2
        {
            for (x = 1; x < (cx-1); ) // 注意为防止越界，x的范围从1到宽度-2
            {
                src = buffer + lineBegin + x;
                dst = output + lineBegin + x;

                if (*src == 0) // 是黑点才做处理
                {
                    w = *(src - 1); // 左邻点
                    e = *(src + 1); // 右邻点

                    if ((w == 255)|| (e == 255)) // 左右两个邻居中至少有一个是白点才处理
                    {
                        nw = *(src+cx-1); // 左上邻点
                        n  = *(src+cx);   // 上邻点
                        ne = *(src+cx+1); // 右上邻点
                        sw = *(src-cx-1); // 左下邻点
                        s  = *(src-cx);   // 下邻点
                        se = *(src-cx+1); // 右下邻点

                        // 计算索引
                        num = nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+
                            sw/255*32+s/255*64+se/255*128;

                        if (eraseTable[num] == 1) // 经查表，可以删除
                        {
                            *src = 255; // 在原图缓冲区中将该黑点删除
                            *dst = 255; // 结果图中该黑点也删除
                            finished = false; // 有改动，结束标志置成假
                            x++; // 水平方向跳过一个象素
                        }
                    }
                }

                x++; // 扫描下一个象素
            }

            lineBegin += cx;
        }

        lineBegin = 0;

        // 再进行垂直方向的细化
        for (x = 1; x < (cx-1); x++)
        {
            for (y = 1; y < (cy-1);)
            {
                src = buffer + lineBegin + x;
                dst = output + lineBegin + x;

                if (*src == 0) // 是黑点才做处理
                {
                    n = *(src + cx); // 下邻点
                    s = *(src - cx); // 上邻点

                    if ((n == 255) || (s == 255)) // 如果上下两个邻居中至少有一个是白点才处理
                    {
                        nw = *(src+cx-1); // 左上邻点
                        ne = *(src+cx+1); // 右上邻点
                        w  = *(src-1);    // 左邻点
                        e  = *(src+1);    // 右邻点
                        sw = *(src-cx-1); // 左下邻点
                        se = *(src-cx+1); // 右下邻点

                        // 计算索引
                        num = nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+
                            sw/255*32+s/255*64+se/255*128;

                        if (eraseTable[num] == 1) // 经查表，可以删除
                        {
                            *src = 255; // 在原图缓冲区中将该黑点删除
                            *dst = 255; // 结果图中该黑点也删除
                            finished = false;   // 有改动，结束标志置成假
                            y++;                // 垂直方向跳过一个象素
                        }
                    }
                }

                y++; // 扫描下一行象素
            }

            lineBegin += cy;
        }
    }

    delete[] buffer;
}

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
void thinClear(uint8 *input, uint8 *output, int cx, int cy, int len)
{
    int SiteD8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1};
    int x = 0;
    int y = 0;
    int i = 0;
    int n = 0;
    int lineBegin = 0;
    uint8 *linePt[25] = {0}; // 纹线各个点
    uint8 *temp[8] = {0}; // 某点的邻点
    uint8 *pt = NULL;
    uint8 *last = NULL;
    uint8 *next = NULL;
    uint8 *src = NULL;

    memcpy(output, input, cx*cy);

    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cx; x++)
        {
            src = output + lineBegin + x;

            if (*src != 0) continue;

            n = 0;
            linePt[0] = src;

            // 统计当前点的周围黑点个数
            for (i = 0; i < 8; i++)
            {
                pt = src + SiteD8[i];

                if (*pt == 0)
                {
                    temp[n] = pt;
                    n++;
                }
            }

            // 黑点个数为零，表示当前点是孤点，置为白色
            if (n == 0)
            {
                *src = 255;
                continue;
            }
            else if (n == 1) // 黑点个数为1，表示为端点
            {
                n = 0;
                last = src;
                pt = temp[0];

                // 沿纹线跟踪len个点
                for (i = 0; i < len; i++)
                {
                    // 如果遇到叉点则跳出循环
                    if (isFork(pt, cx))
                    {
                        break;
                    }

                    n++;
                    linePt[n] = pt;

                    if (getNextPt(pt, last, &next, cx, cy))
                    {
                        last = pt;
                        pt = next;
                    }
                    else // 如果遇到异常跳出循环
                    {
                        break;
                    }
                }

                // 纹线较短，表示为短棒或者是毛刺
                if (n < len)
                {
                    for(i = 0; i <= n; i++)
                    {
                        *linePt[i] = 255;
                    }
                }
            }
        }

        lineBegin += cx;
    }
}

/**
 *\fn           bool isEnd(uint8 *input, int cx)
 *\brief        判断当前点是否为端点
 *\param[in]    uint8 * input 当前点
 *\param[in]    int cx 图像宽
 *\return       bool 是否为端点
 */
bool isEnd(uint8 *input, int cx)
{
    int i = 0;
    int sum = 0;
    int siteD8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1};// 某点周围8个点的地址偏移

    // 8个点所有相邻两个点的差的绝对值的和如果为2*255则为端点
    for(i = 0; i < 8; i++)
    {
        sum += abs(*(input + siteD8[(i+1)%8]) - *(input + siteD8[i]));
    }

    return (sum == 255*2);
}

/**
 *\fn           bool isFork(uint8 *input, int cx)
 *\brief        当前点是否为叉点
 *\param[in]    uint8 * input 当前点数据
 *\param[in]    int cx 图像宽
 *\return       bool 是否为叉点
 */
bool isFork(uint8 *input, int cx)
{
    int i = 0;
    int sum = 0;
    int siteD8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1}; // 某点周围8个点的地址偏移

    // 8个点所有相邻两个点的差的绝对值的和如果为6*255则为叉点
    for (i = 0; i < 8; i++)
    {
        sum += abs(*(input + siteD8[(i+1)%8]) - *(input + siteD8[i]));
    }

    return (sum == 255*6);
}

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
bool getNextPt(uint8 *pt, uint8 *last, uint8 **next, int cx, int cy)
{
    int siteD8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1};
    int i = 0;
    int n = 0;
    uint8 *src = NULL;
    uint8 *temp[8] = {0}; // 某点周围8个点的地址

    *next = NULL;

    // 找到当前点周围的是黑点并且不是前驱点的黑点，保存到数组
    for (i = 0; i < 8; i++)
    {
        src = pt + siteD8[i];

        if (*src == 0 && src != last)
        {
            temp[n] = src;
            n++;
        }
    }

    if (n == 1) // 找到了一个，则其为后继点
    {
        *next = temp[0];
        return true;
    }

    // 没有找到其他黑点则表示没有后继点
    // 或找到多个点则返回错误
    return false;
}

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
int loadBitmap(const char *filename, uint8 *data, BITMAPFILEHEADER *bfh, BITMAPINFOHEADER *bih, int *cx, int *cy)
{
    if (NULL == filename || NULL == bfh || NULL == bih || NULL == cx || NULL == cy) return -1;

    // 打开文件
    FILE *fp = fopen(filename, "rb");

    if (NULL == fp) return -2;

    // 读文件头
    fread((void*)bfh, sizeof(BITMAPFILEHEADER), 1, fp);
    fread((void*)bih, sizeof(BITMAPINFOHEADER), 1, fp);

    // 检查是否为BMP文件
    if (bfh->bfType != 19778)
    {
        fclose(fp);
        return -3;
    }

    // 检查是否为256色灰度图像
    if (bih->biBitCount != 8 && bih->biClrUsed != 256)
    {
        fclose(fp);
        return -4;
    }

    // 得到图像大小
    *cx = bih->biWidth;
    *cy = bih->biHeight;

    // 得到一行的字节数,4个字节对齐
    int lineBytes = (bih->biWidth + 3) / 4 * 4;

    // 缓冲区指针不为空则读取图像数据到缓冲区
    if (NULL == data)
    {
        fclose(fp);
        return -5;
    }

    // 按行读取，每行只读取cx个字节
    for (int i = 0; i < bih->biHeight; i++)
    {
        fseek(fp, 1078+lineBytes*i, SEEK_SET);
        fread((void*)(data+i*bih->biWidth), 1, bih->biWidth, fp);
    }

    fclose(fp);

    return 0;
}

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
    int cx, int cy, bool color)
{
    if (NULL == filename || NULL == data || NULL == bfh || NULL == bih || NULL == cx || NULL == cy) return -1;

    // 得到一行的字节数,4个字节对齐
    int lineBytes = (cx + 3) / 4 * 4;

    // 文件头
    BITMAPFILEHEADER bfh_temp = *bfh;
    BITMAPINFOHEADER bih_temp = *bih;
    bfh_temp.bfSize = lineBytes * cy + 1078;
    bih_temp.biWidth = cx;
    bih_temp.biHeight = cy;
    bih_temp.biSizeImage = lineBytes * cy;

    // 构造调色板数据
    uint8 palatte[1024];
    for(int i = 0; i < 256; i++)
    {
        if (1 == i && color)
        {
            palatte[i*4]   =(unsigned char)255;
            palatte[i*4+1] =(unsigned char)0;
            palatte[i*4+2] =(unsigned char)0;
            palatte[i*4+3] =0;
        }
        else if (2 == i && color)
        {
            palatte[i*4]   =(unsigned char)0;
            palatte[i*4+1] =(unsigned char)255;
            palatte[i*4+2] =(unsigned char)0;
            palatte[i*4+3] =0;
        }
        else if (3 == i && color)
        {
            palatte[i*4]   =(unsigned char)0;
            palatte[i*4+1] =(unsigned char)0;
            palatte[i*4+2] =(unsigned char)255;
            palatte[i*4+3] =0;
        }
        else
        {
            palatte[i*4]   =(unsigned char)i;
            palatte[i*4+1] =(unsigned char)i;
            palatte[i*4+2] =(unsigned char)i;
            palatte[i*4+3] =0;
        }
    }

    // 打开文件
    FILE *fp = fopen(filename, "wb");

    if (NULL == fp) return -2;

    // 写文件头
    fwrite((void*)&bfh_temp, sizeof(bfh_temp), 1, fp);
    fwrite((void*)&bih_temp, sizeof(bih_temp), 1, fp);
    fwrite((void*)&palatte,  sizeof(palatte),  1, fp);

    // 按行读取，每行lineBytes个字节
    for (int i = 0; i < cy; i++)
    {
        fwrite((void*)(data+i*cx), 1, lineBytes, fp);
    }

    fclose(fp);

    return 0;
}
