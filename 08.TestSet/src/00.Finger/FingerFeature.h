
#pragma once

typedef unsigned char uint8;


#define MAXminutiaNum       60  // 最大特征点数
#define MAXRAWminutiaNum    100 // 包含虚假特征点的初始特征点最大数目

#define MINUTIA_END         1   // 端点
#define MINUTIA_FORK        2   // 叉点

#define MATCHMODE_FAST      1   // 快速比较

// 特征点结构
typedef struct tagMinutiae
{
    int x;                      // 横坐标
    int y;                      // 纵坐标
    int direction;              // 方向
    int triangle[3];            // 特征点为中心外接圆半径为定值的正三角形三个顶点的方向
    int type;                   // 类型

} MINUTIA, *PMINUTIA;

// 指纹特征(模板)结构
typedef struct tagFeature
{
    int     minutiaNum;             // 特征点数
    MINUTIA minutia[MAXminutiaNum]; // 特征点数组

} FEATURE, *PFEATURE;

typedef struct tagMatchResult
{
    int    similarity;              // 相似度
    int    rotation;                // 旋转角度
    int    transX;                  // 水平偏移
    int    transY;                  // 垂直偏移
    int    matchNum;                // 匹配特征点数

} MATCHRESULT, *PMATCHRESULT;


/*
 *\fn         int getRawMinutia(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end, PFEATURE fork)
 *\brief      得到原始特征点
 *\param[in]  uint8 * input 图像数据
 *\param[in]  uint8 * orient 方向场
 *\param[in]  int cx 图像宽
 *\param[in]  int cy 图像高
 *\param[in]  PFEATURE end 端点
 *\param[in]  PFEATURE fork 叉点
 *\return     int 0成功,其它失败
 */
int getRawMinutia(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end, PFEATURE fork);

/*
 *\fn         int filteMinutia(uint8 *input, int cx, int cy, PFEATURE end, PFEATURE fork)
 *\brief      过滤特征点
 *\param[in]  uint8 * input 图像数据
 *\param[in]  int cx 图像宽
 *\param[in]  int cy 图像高
 *\param[in]  PFEATURE end 端点
 *\param[in]  PFEATURE fork 叉点
 *\return     int 0成功,其它失败
 */
int filteMinutia(uint8 *input, int cx, int cy, PFEATURE end, PFEATURE fork);

/*
 *\fn         void makeFeature(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end, PFEATURE fork)
 *\brief      生成特征数据
 *\param[in]  uint8 * input 图像数据
 *\param[in]  uint8 * orient 方向场
 *\param[in]  int cx 图像宽
 *\param[in]  int cy 图像高
 *\param[in]  PFEATURE end 端点
 *\param[in]  PFEATURE fork 叉点
 *\return     void 0成功,其它失败
 */
void makeFeature(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end, PFEATURE fork);

/*
 *\fn         int matchFeature(PFEATURE feature, PFEATURE templat, MATCHRESULT *matchResult, int matchMode)
 *\brief      比较特征数据
 *\param[in]  PFEATURE feature1 特征数据
 *\param[in]  PFEATURE templat 模板特征数据
 *\param[in]  MATCHRESULT * matchResult 比较结果
 *\param[in]  int matchMode 比较模式,默认阈值为50。相似度>=50则认为比对成功，否则比对失败
 *\return     bool 是否匹配
 */
bool matchFeature(PFEATURE feature, PFEATURE templat, MATCHRESULT *matchResult, int matchMode);

/**
 *\fn           void flagMinutia(uint8 *image, int cx, int cy, PFEATURE end, PFEATURE fork)
 *\brief        标记特征点
 *\param[in]    uint8 * image 图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    PFEATURE end 端点
 *\param[in]    PFEATURE fork 叉点
 *\return       void 无
 */
void flagMinutia(uint8 *image, int cx, int cy, PFEATURE end, PFEATURE fork);
