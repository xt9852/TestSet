#include "stdafx.h"
#include "FingerFeature.h"
#include "FingerImageProcess.h"


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
void flagMinutia(uint8 *image, int cx, int cy, PFEATURE end, PFEATURE fork)
{
    int i = 0;
    int x = 0;
    int y = 0;
    int r = 5;

    for (int i = 0; i < end->minutiaNum; i++)
    {
        for (int x = -r; x < r; x++)
        {
            *(image + end->minutia[i].y * cx + end->minutia[i].x - r * cx + x) = 1;
            *(image + end->minutia[i].y * cx + end->minutia[i].x + r * cx + x) = 1;
        }

        for (int y = -r; y < r; y++)
        {
            *(image + end->minutia[i].y * cx + end->minutia[i].x + y * cx - r) = 1;
            *(image + end->minutia[i].y * cx + end->minutia[i].x + y * cx + r) = 1;
        }
    }

    for (int i = 0; i < fork->minutiaNum; i++)
    {
        for (int x = -2*r; x < 2*r; x++)
        {
            *(image + fork->minutia[i].y * cx + fork->minutia[i].x - r * cx + x) = 2;
        }

        for (int y = r, x = 0; y > -r; y--, x++)
        {
            *(image + fork->minutia[i].y * cx + fork->minutia[i].x + y * cx - x) = 2;
            *(image + fork->minutia[i].y * cx + fork->minutia[i].x + y * cx + x) = 2;
        }
    }
}

/**
 *\fn           int GetJiajiao(int angle1, int angle2)
 *\brief        求两个角度的夹角(0 - 90)
 *\param[in]    int angle1 角度1
 *\param[in]    int angle2 角度2
 *\return       int 夹角
 */
int GetJiajiao(int angle1, int angle2)
{
    int a = abs(angle1-angle2);

    if (a > 90)
    {
        a = 180 - a;
    }

    return a;
}

/**
 *\fn           int getDistancePt(uint8 *end, uint8 **pt, int d, int cx, int cy)
 *\brief        在纹线上找到距离当前端点为d的点的地址
 *\param[in]    uint8 * end 当前端点的地址
 *\param[out]   uint8 * * pt 目的点的地址(如果在距离d内有端点或者叉点，则返回他们的邻点)
 *\param[in]    int d 距离（点数）
 *\param[in]    int cx 
 *\param[in]    int cy 
 *\return       int 0成功,其它失败
 */
int getDistancePt(uint8 *end, uint8 **pt, int d, int cx, int cy)
{
    int i = 0;
    int n = 0;
    int siteD8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1};
    uint8 *now = NULL;
    uint8 *last = NULL;
    uint8 *next = NULL;

    *pt = NULL;

    // 找到当前点周围的是黑点并且不是前驱点的黑点，保存到数组
    for (i = 0; i < 8; i++)
    {
        if (*(end + siteD8[i]) == 0)
        {
            now = end + siteD8[i];
            n++;
        }
    }

    if (n != 1) // 数目如果不是1则返回错误
    {
        return 1;
    }

    // 找到的黑点地址为now
    // 端点作为前驱点,地址保存到last
    last = end;

    // 循环找d次后继点
    for (i = 0; i < d; i++)
    {
        // 如果是叉点则跳出循环
        if (isFork(now, cx))
        {
            break;
        }

        // 成功找到下一个点则更改当前点和前驱点
        if (getNextPt(now, last, &next, cx, cy))
        {
            last = now;
            now = next;
        }
        else
        {
            break;
        }
    }

    // 如果找到的点为叉点,则返回其前驱点,否则返回当前点
    *pt = (isFork(now, cx)) ? last : now;

    return 0;
}

/**
 *\fn           int getPtX(uint8 *input, uint8 *pos, int cx)
 *\brief        根据地址得到当前点的横坐标
 *\param[in]    uint8 * input 图像开始
 *\param[in]    uint8 * pos 当前点地址
 *\param[in]    int cx 图像宽
 *\return       int 横坐标
 */
int getPtX(uint8 *input, uint8 *pos, int cx)
{
    return ((pos - input) % cx);
}

/**
 *\fn           int getPtY(uint8 *input, uint8 *pos, int cx)
 *\brief        根据地址得到当前点的纵坐标
 *\param[in]    uint8 * input 图像开始
 *\param[in]    uint8 * pos 当前点地址
 *\param[in]    int cx 图像宽
 *\return       int 纵坐标
 */
int getPtY(uint8 *input, uint8 *pos, int cx)
{
    return ((pos - input) % cx);
}

/**
 *\fn           int getAngleAbs(int angle1, int angle2)
 *\brief        求两个角度的夹角(0 - 360)(逆时针方向)
 *\param[in]    int angle1 角度一(0 - 360)
 *\param[in]    int angle2 角度二(0 - 360)
 *\return       int 夹角
 */
int getAngleAbs(int angle1, int angle2)
{
    int a = angle1 - angle2;

    if (a < 0)
    {
        a += 360;
    }

    return a;
}

/**
 *\fn           int getAngleRelative(int angle1, int angle2)
 *\brief        求两个角度的夹角(0 - 180)
 *\param[in]    int angle1 角度一(0 - 360)
 *\param[in]    int angle2 角度二(0 - 360)
 *\return       int 夹角
 */
int getAngleRelative(int angle1, int angle2)
{
    int a = abs(angle1 - angle2);

    return ((a > 180) ? (360 - a) : a);
}

/**
 *\fn           int getAngle(int x0, int y0, int x1, int y1)
 *\brief        两个点连线与x轴方向的角度
 *\param[in]    int x0 第一个点横坐标
 *\param[in]    int y0 第一个点纵坐标
 *\param[in]    int x1 第二个点横坐标
 *\param[in]    int y1 第二个点纵坐标
 *\return       int 角度
 */
int getAngle(int x0, int y0, int x1, int y1)
{
    double angle = atan2((double)(y1-y0), (double)(x1-x0));

    // 弧度转化到0 - 2*PI
    if (angle < 0)
    {
        angle += 2*PI;
    }

    // 弧度转化为角度
    return (int)(angle*EPI + 0.5);
}

/**
 *\fn           bool isNearEdge(int x, int y, int cx, int cy, int r, uint8 *orient_pt)
 *\brief        检测是否靠近边缘
 *\param[in]    int x 当前点x坐标
 *\param[in]    int y 当前点y坐标
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    int r 检测半径
 *\param[in]    uint8 * orient_pt 当前方向场点
 *\return       bool 是否靠近边缘
 */
bool isNearEdge(int x, int y, int cx, int cy, int r, uint8 *orient_pt)
{
    int i = 0;
    int j = 0;
    bool flag = true;

    for (i = -r; i <= r && flag; i++)
    {
        for (j = -r; j <= r && flag; j++)
        {
            if ((y+i)<0 || (y+i)>=cy || (x+j)<0 || (x+j)>=cx)
            {
                continue;
            }

            if (*(orient_pt + i*cx + x + j) == 255) // 方向场
            {
                flag = false;
                break;
            }
        }
    }

    return !flag;
}

/**
 *\fn           bool isSevereChange(uint8 *orient_pt, int *siteR5)
 *\brief        检查该点周围方向场是否变化剧烈,变化剧烈很可能是虚假点
 *\param[in]    uint8 * orient_pt 当前方向场点
 *\param[in]    int *siteR5 某点为圆心,半径为5的圆上所有点的地址偏移
 *\return       bool 是否变化剧烈
 */
bool isSevereChange(uint8 *orient_pt, int *siteR5)
{
    int i = 0;
    int sum = 0;

    for (i = 0; i < 28; i++)
    {
        sum += GetJiajiao(*(orient_pt+siteR5[(i+1)%28]), *(orient_pt+siteR5[i]));
    }

    return (sum > 96);
}

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
int getRawMinutia(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end, PFEATURE fork)
{
    int x = 0;
    int y = 0;
    int lineBegin = 0;
    bool flag = false;
    uint8 *curInput = NULL;
    uint8 *curOrient = NULL;

    // 某点为圆心，半径为5的圆上所有点的地址偏移
    int siteR5[28] =
    {
        -5, cx-5, 2*cx-5, 3*cx-4, 4*cx-3, 5*cx-2, 5*cx-1, 5*cx,
        5*cx+1, 5*cx+2, 4*cx+3, 3*cx+4, 2*cx+5, cx+5, 5, -cx+5,
        -2*cx+5, -3*cx+4, -4*cx+3, -5*cx+2, -5*cx+1, -5*cx,
        -5*cx-1, -5*cx-2, -4*cx-3, -3*cx-4, -2*cx-5, -cx-5
    };

    end->minutiaNum = 0;
    fork->minutiaNum = 0;

    for (y = 17; y < cy-17; y++)
    {
        lineBegin = y*cx;

        for (x = 17; x < cx-17; x++)
        {
            curInput  = input + lineBegin + x;
            curOrient = orient + lineBegin + x;

            // 不是黑点则不考虑
            if (*curInput != 0)
            {
                continue;
            }

            // 是叉点
            if (isFork(curInput, cx))
            {
                // 检查是否靠近边缘,靠近边缘则不考虑
                flag = isNearEdge(x, y, cx, cy, 16, (orient + lineBegin));

                if (!flag)
                {
                    // 检查该点周围方向场是否变化剧烈,变化剧烈则不考虑,因为很可能是虚假点
                    flag = isSevereChange(curOrient, siteR5);
                }

                // 达到所有要求则记录下来该点
                if (!flag)
                {
                    fork->minutia[fork->minutiaNum].type = MINUTIA_FORK;
                    fork->minutia[fork->minutiaNum].x = x;
                    fork->minutia[fork->minutiaNum].y = y;
                    fork->minutiaNum++;

                    // 如果总数已经超过允许最大数目，则返回错误
                    if (fork->minutiaNum >= MAXRAWminutiaNum)
                    {
                        fork->minutiaNum = 0;
                        return -1;
                    }
                }
            }
            else if (isEnd(curInput, cx)) // 是端点
            {
                flag = isNearEdge(x, y, cx, cy, 16, (orient + lineBegin));

                if (!flag)
                {
                    flag = isSevereChange(curOrient, siteR5);
                }

                if (!flag)
                {
                    end->minutia[end->minutiaNum].type = MINUTIA_END;
                    end->minutia[end->minutiaNum].x = x;
                    end->minutia[end->minutiaNum].y = y;
                    end->minutiaNum++;

                    if (end->minutiaNum >= MAXRAWminutiaNum)
                    {
                        end->minutiaNum = 0;
                        return -2;
                    }
                }
            }
        }
    }

    return 0;
}

/**
 *\fn           int filteMinutiaEnd(uint8 *input, int cx, int cy, int minDis, PFEATURE end)
 *\brief        过滤优化指纹端点特征
 *\param[in]    uint8 * input 指纹图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    int minDis 允许两个特征点间最近的距离
 *\param[in]    PFEATURE end 端点数据
 *\return       int 端点数量
 */
int filteMinutiaEnd(uint8 *input, int cx, int cy, int minDis, PFEATURE end)
{
    int i = 0;
    int j = 0;
    int d = 0;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int num = 0;
    int end_num = end->minutiaNum;
    int edge = 16; // 允许特征点靠近前景边缘的最近距离
    int angle1 = 0;
    int angle2 = 0;
    int angle3 = 0;
    int angle4 = 0;
    bool flag = false;
    uint8 *curPoint = NULL;
    uint8 *disPoint = NULL;

    for (i = 0; i < (end_num - 1); i++)
    {
        flag = false;

        for (j = i+1; j < end_num; j++)
        {
            x1 = end->minutia[i].x;
            y1 = end->minutia[i].y;
            x2 = end->minutia[j].x;
            y2 = end->minutia[j].y;

            // 求两个端点的距离,勾股定理
            d = (int)sqrt((double)((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));

            // 距离足够大则检查下一个端点
            if (d > edge && d > minDis)
            {
                continue;
            }

            // 距离太小，则将其坐标置为（0，0）
            if (d <= minDis)
            {
                end->minutia[j].x = 0;
                end->minutia[j].y = 0;
                flag = true;
                continue;
            }

            // 求第一个端点所在纹线的角度
            curPoint = input + y1*cx + x1;

            // 得到纹线上距离该点8个点的点
            if (getDistancePt(curPoint, &disPoint, 8, cx, cy) != 0)
            {
                break;
            }

            angle1 = getAngle(x1, y1, getPtX(input, disPoint, cx), getPtY(input, disPoint, cy));

            // 求第二个端点所在纹线的角度
            curPoint = input + y2*cx + x2;

            if (getDistancePt(curPoint, &disPoint, 8, cx, cy) != 0)
            {
                continue;
            }

            angle2 = getAngle(x2, y2, getPtX(input, disPoint, cx), getPtY(input, disPoint, cy));

            // 求两个角度间的距离
            angle3 = getAngleAbs(angle1, angle2);

            // 如果两个角度间成锐角，则不是虚假特征点
            if (angle3 > 270 || angle3 < 90)
            {
                continue;
            }

            // 求两个端点连线的角度
            angle3 = getAngle(x1, y1, x2, y2);

            // 求第一个端点纹线与连线的夹角
            angle3 = getAngleAbs(angle1, angle3);

            // 如果夹角较大则不是虚假点
            if (angle3 < 150 || angle3 > 210)
            {
                continue;
            }

            // 求第二个端点纹线与连线的夹角
            angle4 = getAngle(x2, y2, x1, y1);

            angle4 = getAngleAbs(angle2, angle4);

            // 如果夹角较大则不是虚假点
            if (angle4 < 150 || angle4 > 210)
            {
                continue;
            }

            // 否则表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
            end->minutia[j].x = 0;
            end->minutia[j].y = 0;
            flag = true;
        }

        if (flag)// 表示这两个点是同一条纹线上的断裂处的两个端点,坐标置原点
        {
            end->minutia[i].x = 0;
            end->minutia[i].y = 0;
        }
    }

    // 统计新的端点数目
    for (i = 0; i < end_num; i++)
    {
        if (end->minutia[i].x == 0 || end->minutia[i].y == 0)
        {
            continue;
        }

        curPoint = input + end->minutia[i].y*cx + end->minutia[i].x;

        // 得到纹线上距离该点8个点的点
        if (getDistancePt(curPoint, &disPoint, 8, cx, cy) != 0)
        {
            end->minutia[i].x = 0;
            end->minutia[i].y = 0;
            continue;
        }

        num++;
    }

    return num;
}

/**
 *\fn           int filteMinutiaFork(uint8 *input, int cx, int cy, int minDis, PFEATURE fork)
 *\brief        过滤优化指纹端点特征
 *\param[in]    uint8 * input 指纹图像数据
 *\param[in]    int cx 图像宽
 *\param[in]    int cy 图像高
 *\param[in]    int minDis 允许两个特征点间最近的距离
 *\param[in]    PFEATURE fork 叉点数据
 *\return       int 叉点数量
 */
int filteMinutiaFork(uint8 *input, int cx, int cy, int minDis, PFEATURE fork)
{
    int i = 0;
    int j = 0;
    int n = 0;
    int d = 0;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int num = 0;
    int fork_num = fork->minutiaNum;
    int siteU8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1}; // 某点周围8个点的地址偏移
    bool flag = false;
    uint8 *temp[9] = {0};
    uint8 *curPoint = NULL;

    for (i = 0; i < fork_num-1; i++)
    {
        flag = false;

        for (j = i+1; j < fork_num; j++)
        {
            x1 = fork->minutia[i].x;
            y1 = fork->minutia[i].y;
            x2 = fork->minutia[j].x;
            y2 = fork->minutia[j].y;

            d = sqrt((double)((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));

            if (d <= (minDis-2))
            {
                fork->minutia[j].x = 0;
                fork->minutia[j].y = 0;
                flag = true;
            }
        }

        if (flag)
        {
            fork->minutia[i].x = 0;
            fork->minutia[i].y = 0;
        }
    }

    // 统计新的真正的叉点
    for (i = 0; i < fork_num; i++)
    {
        if (fork->minutia[i].x == 0 || fork->minutia[i].y == 0)
        {
            continue;
        }

        curPoint = input + fork->minutia[i].y*cx + fork->minutia[i].x;

        temp[0] = curPoint;
        *temp[0] = 255; // 设置成白点

        // 检查是否真正叉点
        for (j = 0, n = 1; j < 8; j++)
        {
            if (*(curPoint + siteU8[j]) == 0) // 黑点
            {
                temp[n] = curPoint + siteU8[j];
                *temp[n] = 255;
                n++;
            }
        }

        for (j = 0; j < 4; j++)
        {
            *temp[j] = 0; // 设置成黑点
        }

        if (n != 4)
        {
            fork->minutia[i].x = 0;
            fork->minutia[i].y = 0;
            continue;
        }

        num++;
    }

    return num;
}

/*
 *\fn         void clearMinutia(PFEATURE data)
 *\brief      清空特征点
 *\param[in]  PFEATURE data 特征点数据
 *\return     void 0成功,其它失败
 */
void clearMinutia(PFEATURE data)
{
    int last = data->minutiaNum - 1;
    int j = last;
    int i = 0;

    for (i = 0; i < j; i++)
    {
        if (data->minutia[i].x != 0 && data->minutia[i].y != 0)
        {
            continue;
        }

        for (j = last; j > i; j--)
        {
            if (data->minutia[j].x == 0 || data->minutia[j].y == 0)
            {
                continue;
            }

            last = j - 1;
            data->minutia[i] = data->minutia[j];
            data->minutia[j].x = 0;
            data->minutia[j].y = 0;
            break;
        }
    }

    data->minutiaNum = i - (0 == data->minutia[i-1].x || 0 == data->minutia[i-1].y);
}

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
int filteMinutia(uint8 *input, int cx, int cy, PFEATURE end, PFEATURE fork)
{
    int i = 0;
    int j = 0;
    int last = 0;
    int count = 0;

    for (i = 7; i < (7+32); i++)
    {
        count = filteMinutiaEnd(input, cx, cy, i, end);

        if (count < MAXminutiaNum) break;
    }

    for (i = 7; i < (7+32); i++)
    {
        count = filteMinutiaFork(input, cx, cy, i, fork);

        if (count < MAXminutiaNum) break;
    }

    clearMinutia(end);
    clearMinutia(fork);

    return 0;
}

/*
 *\fn         void makeFeatureEnd(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end)
 *\brief      生成端点特征数据
 *\param[in]  uint8 * input 图像数据
 *\param[in]  uint8 * orient 方向场
 *\param[in]  int cx 图像宽
 *\param[in]  int cy 图像高
 *\param[in]  PFEATURE end 端点
 *\return     void 无
 */
void makeFeatureEnd(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end)
{
    int i = 0;
    int x = 0;
    int y = 0;
    int x1 = 0;
    int y1 = 0;
    int angle1 = 0;
    int angle2 = 0;
    int angle3 = 0;
    int trilen = 16;
    double a = 0;
    uint8 *curPoint = NULL;
    uint8 *disPoint = NULL;

    for (i = 0; i < end->minutiaNum; i++)
    {
        x = end->minutia[i].x;
        y = end->minutia[i].y;

        // 沿纹线找到第8个点
        curPoint = input + y*cx + x;

        if (getDistancePt(curPoint, &disPoint, 8, cx, cy) != 0)
        {
            continue;
        }

        // 求该点与端点连线的角度
        angle1 = getAngle(x, y, getPtX(input, disPoint, cx), getPtX(input, disPoint, cx));

        // 方向场
        angle2 = *(orient + y * cx + x);

        angle3 = getAngleAbs(angle1, angle2);

        // 如果成钝角，则表示该特征点方向与该点方向场方向相反
        // 如果成锐角，则表示该特征点方向与该点方向场方向相同
        if (angle3 > 90 && angle3 < 270)
        {
            angle2 += 180;
        }

        end->minutia[i].direction = angle2;

        a = angle2 / EPI + PI/4.0;
        x1 = x + (int)(trilen*cos(a)+ 0.5);
        y1 = y + (int)(trilen*sin(a)+ 0.5);
        end->minutia[i].triangle[0] = *(orient + y1*cx + x1);

        a += PI*2/3.0;
        x1 = x + (int)(trilen*cos(a)+ 0.5);
        y1 = y + (int)(trilen*sin(a)+ 0.5);
        end->minutia[i].triangle[1] = *(orient + y1*cx + x1);

        a += PI*2/3.0;
        x1 = x + (int)(trilen*cos(a)+ 0.5);
        y1 = y + (int)(trilen*sin(a)+ 0.5);
        end->minutia[i].triangle[2] = *(orient + y1*cx + x1);
    }
}

/*
 *\fn         void makeFeatureFork(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE fork)
 *\brief      生成叉点特征数据
 *\param[in]  uint8 * input 图像数据
 *\param[in]  uint8 * orient 方向场
 *\param[in]  int cx 图像宽
 *\param[in]  int cy 图像高
 *\param[in]  PFEATURE fork 叉点
 *\return     void 无
 */
void makeFeatureFork(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE fork)
{
    int i = 0;
    int j = 0;
    int n = 0;
    int x = 0;
    int y = 0;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int x3 = 0;
    int y3 = 0;
    int d0 = 0;
    int d1 = 0;
    int d2 = 0;
    int angle1 = 0;
    int angle2 = 0;
    int angle3 = 0;
    int trilen = 16;
    int siteU8[8] = {cx-1, cx, cx+1, 1, -cx+1, -cx, -cx-1, -1}; // 某点周围8个点的地址偏移
    uint8 *temp[9] = {0};
    uint8 *curPoint = NULL;
    uint8 *disPoint[8] = {0};
    double a = 0;

    for (i = 0; i < fork->minutiaNum; i++)
    {
        x = fork->minutia[i].x;
        y = fork->minutia[i].y;

        curPoint = input + y*cx + x;

        temp[0] = curPoint;
        *temp[0] = 255; // 设置成白点

        for (j = 0, n = 1; j < 8; j++)
        {
            if (*(curPoint + siteU8[j]) == 0) // 黑点
            {
                temp[n] = curPoint + siteU8[j];
                *temp[n] = 255; // 设置成白点
                n++;
            }
        }

        if (n != 4)
        {
            continue;
        }

        // 找到叉点三个方向纹线上距离为8的点
        for (j = 0; j < 3; j++)
        {
            getDistancePt(temp[j+1], &disPoint[j], 8, cx, cy);
        }

        for (j = 0; j < 4; j++)
        {
            *temp[j] = 0; // 设置成黑点
        }

        // 求该三个点两两间的距离
        x1 = getPtX(input, disPoint[0], cx);
        y1 = getPtY(input, disPoint[0], cx);
        x2 = getPtX(input, disPoint[1], cx);
        y2 = getPtY(input, disPoint[1], cx);
        x3 = getPtX(input, disPoint[2], cx);
        y3 = getPtY(input, disPoint[2], cx);

        d0 = sqrt((double)((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
        d1 = sqrt((double)((x1 - x3)*(x1 - x3) + (y1 - y3)*(y1 - y3)));
        d2 = sqrt((double)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));

        // 距离最短的边对应的是叉线方向
        if (d0 < d1 && d0 < d2)
        {
            angle1 = getAngle(x, y, (x2+x3)/2, (y2+y3)/2);
        }
        else if (d1 < d0 && d1 < d2)
        {
            angle1 = getAngle(x, y, (x1+x3)/2, (y1+y3)/2);
        }
        else
        {
            angle1 = getAngle(x, y, (x1+x2)/2, (y1+y2)/2);
        }

        // 求最短边中点与叉点连线的方向与该点方向场方向的夹角
        //angle1 = getAngle(x, y, (x11+x21)/2, (y11+y21)/2);

        angle2 = *(orient + y*cx + x);

        angle3 = getAngleAbs(angle1, angle2);

        // 如果成钝角，则表示该特征点方向与该点方向场方向相反
        // 如果成锐角，则表示该特征点方向与该点方向场方向相同
        if (angle3 > 90 && angle3 < 270)
        {
            angle2 += 180;
        }

        fork->minutia[i].direction = angle2;

        // 纪录以特征点为中心外接圆半径为trilen的正三角形三个顶点的方向
        a = angle2 / EPI + PI/4.0;
        x1 = x + (int)(trilen*cos(a)+ 0.5);
        y1 = y + (int)(trilen*sin(a)+ 0.5);
        fork->minutia[i].triangle[0] = *(orient + y1*cx + x1);

        a += PI*2/3.0;
        x1 = x + (int)(trilen*cos(a)+ 0.5);
        y1 = y + (int)(trilen*sin(a)+ 0.5);
        fork->minutia[i].triangle[1] = *(orient + y1*cx + x1);

        a += PI*2/3.0;
        x1 = x + (int)(trilen*cos(a)+ 0.5);
        y1 = y + (int)(trilen*sin(a)+ 0.5);
        fork->minutia[i].triangle[2] = *(orient + y1*cx + x1);
    }
}

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
void makeFeature(uint8 *input, uint8 *orient, int cx, int cy, PFEATURE end, PFEATURE fork)
{
    makeFeatureEnd(input, orient, cx, cy, end);
    makeFeatureFork(input, orient, cx, cy, fork);
}


/*
 *\fn         void align(PFEATURE feature, PFEATURE aligned, PMINUTIA featureCore, int rotation, int transx, int transy)
 *\brief      对齐
 *\param[in]  PFEATURE feature 特征数据
 *\param[in]  PFEATURE aligned 对齐后的特征数
 *\param[in]  PMINUTIA featureCore 坐标转换的中心特征点
 *\param[in]  int rotation 旋转角度
 *\param[in]  int transx 水平偏移
 *\param[in]  int transy 垂直偏移
 *\return     void 无
 */
void align(PFEATURE feature, PFEATURE aligned, PMINUTIA featureCore, int rotation, int transx, int transy)
{
    int i = 0;
    int x = 0;
    int y = 0;
    int cx = featureCore->x;        // 坐标转换的中心点坐标
    int cy = featureCore->y;        // 坐标转换的中心点坐标
    double rota = rotation / EPI;   // 旋转的弧度
    double sinv = sin(rota);;       // 旋转弧度的sin值
    double cosv = cos(rota);        // 旋转弧度的cos值

    // 复制整个结构信息
    *aligned = *feature;

    for (i = 0; i < feature->minutiaNum; i++)
    {
        x = feature->minutia[i].x;
        y = feature->minutia[i].y;

        //  坐标转换后的新坐标
        aligned->minutia[i].x = (int)(cx + cosv*(x-cx) - sinv*(y-cy) + transx + 0.5);
        aligned->minutia[i].y = (int)(cy + sinv*(x-cx) + cosv*(y-cy) + transy + 0.5);

        // 旋转后特征点的新方向
        aligned->minutia[i].direction = (feature->minutia[i].direction + rotation) % 360;
    }
}

// 为节省时间，短距离的两点间距离采用查表法
// DisTbl[m][n] = (int)(sqrt(m*m+n*n)+0.5)
int  DisTbl[10][10] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
    1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
    2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 
    3, 3, 3, 4, 5, 5, 6, 7, 8, 9, 
    4, 4, 4, 5, 5, 6, 7, 8, 8, 9, 
    5, 5, 5, 5, 6, 7, 7, 8, 9, 10, 
    6, 6, 6, 6, 7, 7, 8, 9, 10, 10, 
    7, 7, 7, 7, 8, 8, 9, 9, 10, 11, 
    8, 8, 8, 8, 8, 9, 10, 10, 11, 12, 
    9, 9, 9, 9, 9, 10, 10, 11, 12, 12
};

/*
 *\fn         void alignMatch(PFEATURE feature, PFEATURE templat, PMATCHRESULT matchResult, int matchMode)
 *\brief      两个坐标系对齐的指纹特征进行比对
 *\param[in]  PFEATURE feature 特征数据
 *\param[in]  PFEATURE templat 模板数据
 *\param[in]  PMATCHRESULT matchResult 比对结果
 *\param[in]  int matchMode 
 *\return     void 0成功,其它失败
 */
void alignMatch(PFEATURE feature, PFEATURE templat, PMATCHRESULT matchResult, int matchMode)
{
    int i = 0;
    int j = 0;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int s = 0;          // 相似度
    int dis = 0;        // 距离
    int angle = 0;      // 角度
    int score = 0;      // 总分
    int matchNum = 0;   // 匹配特征点数
    int num1 = feature->minutiaNum;  // 特征点数量
    int num2 = templat->minutiaNum;  // 模板特征点数量
    BYTE flagA[MAXminutiaNum] = {0}; // 标记feature中特征点是否已经有匹配对象
    BYTE flagT[MAXminutiaNum] = {0}; // 标记templat中特征点是否已经有匹配对象

    // 相同类型特征点的匹配分数
    for (i = 0; i < templat->minutiaNum; i++)
    {
        // 是否已有匹配对象
        if (flagT[i]) continue;

        for (j = 0; j < feature->minutiaNum; j++)
        {
            // 是否已有匹配对象
            if (flagA[j]) continue;

            // 特征点类型是否相同
            if (templat->minutia[i].type != feature->minutia[j].type) continue;

            // 特征点方向夹角
            angle = getAngleAbs(templat->minutia[i].direction, feature->minutia[j].direction);

            // 夹角>=10则不匹配
            if (angle >= 10) continue;

            x1 = templat->minutia[i].x;
            y1 = templat->minutia[i].y;
            x2 = feature->minutia[j].x;
            y2 = feature->minutia[j].y;

            // 水平距离>=10则不匹配
            if (abs(x1-x2) >= 10) continue;

            // 垂直距离>=10则不匹配
            if (abs(y1-y2) >= 10) continue;

            // 两特征点间的距离
            dis = DisTbl[abs(y1-y2)][abs(x1-x2)];

            // 距离>=10则不匹配
            if (dis >= 10) continue;

            // 对这两个特征点做标记，表示已经有匹配对象
            flagA[j] = 1;
            flagT[i] = 1;

            // 总分加上此两个特征点的匹配分数
            score += (10-angle);
            score += (10-dis);

            // 匹配特征点数加1
            matchNum++;

            // 如果是快速比对模式
            if (matchMode == MATCHMODE_FAST && matchNum >= 8)
            {
                // 计算相似度
                s = 4 * score * matchNum * MAXminutiaNum / ((num1+num2)*(num1+num2));

                if (s > 100)  // 相似度足够大则返回比对结果
                {
                    matchResult->matchNum = matchNum;
                    matchResult->rotation = 0;
                    matchResult->similarity = s;
                    matchResult->transX = 0;
                    matchResult->transY = 0;
                    return;
                }
            }
        }
    }

    if (matchMode != MATCHMODE_FAST)
    {
        // 由于图像处理的误差导致可能端点处理成叉点或叉点处理成端点，假设概率为50%，计算
        // 此种情况的分数
        for (i = 0; i < templat->minutiaNum; i++)
        {
            // 是否已有匹配对象
            if (flagT[i]) continue;

            for (j = 0; j < feature->minutiaNum; j++)
            {
                // 是否已有匹配对象
                if (flagA[j]) continue;

                // 是否类型不同
                if (templat->minutia[i].type == feature->minutia[j].type) continue;
                    
                // 特征点方向夹角
                angle = getAngleAbs(templat->minutia[i].direction, feature->minutia[j].direction);

                // 夹角>=10则不匹配
                if (angle >= 10) continue;
                    
                x1 = templat->minutia[i].x;
                y1 = templat->minutia[i].y;
                x2 = feature->minutia[j].x;
                y2 = feature->minutia[j].y;

                // 水平距离>=10则不匹配
                if (abs(x1-x2) >= 10) continue;
                    
                // 垂直距离>=10则不匹配
                if (abs(y1-y2) >= 10) continue;
                    
                // 两特征点间的距离
                dis = DisTbl[abs(y1-y2)][abs(x1-x2)];

                // 距离>=10则不匹配
                if (dis >= 10) continue;
                    
                // 对这两个特征点做标记，表示已经有匹配对象
                flagA[j] = 1;
                flagT[i] = 1;

                // 总分加上此两个特征点的匹配分数
                score += ((10-angle)/2);
                score += ((10-dis)/2);

                // 匹配特征点数加1
                matchNum++;
            }
        }
    }

    // 计算相似度，返回比对结果
    s = 4 * score * matchNum * MAXminutiaNum / ((num1+num2)*(num1+num2));

    matchResult->matchNum = matchNum;
    matchResult->rotation = 0;
    matchResult->similarity = s;
    matchResult->transX = 0;
    matchResult->transY = 0;
}

/*
 *\fn         int matchFeature(PFEATURE feature, PFEATURE templat, MATCHRESULT *matchResult, int matchMode)
 *\brief      比较特征数据
 *\param[in]  PFEATURE feature1 特征数据
 *\param[in]  PFEATURE templat 模板特征数据
 *\param[in]  MATCHRESULT * matchResult 比较结果
 *\param[in]  int matchMode 比较模式,默认阈值为50。相似度>=50则认为比对成功，否则比对失败
 *\return     bool 是否匹配
 */
bool matchFeature(PFEATURE feature, PFEATURE templat, MATCHRESULT *matchResult, int matchMode)
{
    int i = 0;
    int j = 0;
    int a1 = 0;
    int a2 = 0;
    int d1 = 0;
    int d2 = 0;
    int t11 = 0;
    int t12 = 0;
    int t13 = 0;
    int t21 = 0;
    int t22 = 0;
    int t23 = 0;
    int num = 0;
    int agate = 8;                  // 三角拓扑结构角度误差
    int rotation = 0;;              // 旋转角度
    int transx = 0;                 // 水平偏移
    int transy = 0;                 // 垂直偏移
    FEATURE alignFeature = {0};     // 对齐后的指纹特征
    MATCHRESULT max = {0};          // 相似度最大的比对结果
    MATCHRESULT result = {0};       // 比对结果

    // 对相同类型的指纹特征两两作为同一个指纹特征进行对齐比对
    for (i = 0; i < templat->minutiaNum; i++)
    {
        for (j = 0; j < feature->minutiaNum; j++)
        {
            // 不同类型则不比对
            if (feature->minutia[j].type != templat->minutia[i].type) continue;

            d1 = feature->minutia[j].direction;
            d2 = feature->minutia[i].direction;

            if (matchMode == MATCHMODE_FAST)
            {
                t11 = feature->minutia[j].triangle[0];
                t12 = feature->minutia[j].triangle[1];
                t13 = feature->minutia[j].triangle[2];
                t21 = feature->minutia[i].triangle[0];
                t22 = feature->minutia[i].triangle[1];
                t23 = feature->minutia[i].triangle[2];

                // 特征点三角拓扑结构比对，相似则进行配准
                if (t11 != 255 && t21 != 255)
                {
                    a1 = GetJiajiao(t11, d1 % 180);
                    a2 = GetJiajiao(t21, d2 % 180);

                    if (abs(a1-a2) > agate) continue;
                }

                if (t11 != 255 && t21 != 255 && t12 != 255 && t22 != 255)
                {
                    a1 = GetJiajiao(t11, t12);
                    a2 = GetJiajiao(t21, t22);

                    if(abs(a1-a2) > agate) continue;
                }

                if (t13 != 255 && t23 != 255 && t12 != 255 && t22 != 255)
                {
                    a1 = GetJiajiao(t12, t13);
                    a2 = GetJiajiao(t22, t23);

                    if(abs(a1-a2) > agate) continue;
                }

                if (t11 != 255 && t11 != 255 && t13 != 255 && t23 != 255)
                {
                    a1 = GetJiajiao(t11, t13);
                    a2 = GetJiajiao(t21, t23);

                    if(abs(a1-a2) > agate) continue;
                }
            }

            alignFeature.minutiaNum = 0;

            // 旋转角度
            rotation = getAngleAbs(feature->minutia[j].direction, templat->minutia[i].direction);

            // 位置偏移
            transx = (templat->minutia[i].x - feature->minutia[j].x);
            transy = (templat->minutia[i].y - feature->minutia[j].y);

            // 将feature与templat对齐
            align(feature, &alignFeature, &feature->minutia[j], rotation, transx, transy);

            // 将两个对齐的指纹特征进行比对
            alignMatch(&alignFeature, templat, &result, matchMode);

            // 如果比对结果比最好的比对结果更好，则更新alignMax
            if (result.similarity > max.similarity)
            {
                max.matchNum = result.matchNum;
                max.similarity = result.similarity;
                max.rotation = rotation;
                max.transX = transx;
                max.transY = transy;

                // 如果是快速比对模式，则相似度达到一定程度则退出
                if (matchMode == MATCHMODE_FAST && max.matchNum >= 8)
                {
                    if (max.similarity >100)
                    {
                        *matchResult = max;
                        return TRUE;
                    }
                }
            }
        }
    }

    // 最终比对结果
    *matchResult = max;

    // 如果匹配特征点数较少，则对比对结果相似度进行修正
    if (matchMode != MATCHMODE_FAST && matchResult->matchNum < 15)
    {
        matchResult->similarity = (int)(matchResult->similarity*sin(matchResult->matchNum*PI/30.0) + 0.5);
    }

    // 默认阈值为50。相似度>=50则认为比对成功，否则比对失败,
    // 一般情况下，在35以上即可认为相似, 为安全起见，最好在50-100
    return (matchResult->similarity > 50);
}

/*
int getOriChange(int angle1, int angle2, char flag)
{
    int  d;

    d = angle2 - angle1;
    if(flag >= 1)
    {
        if(d < 0)
        {
            d += 10;
        }

    }
    else if(flag <= -1)
    {
        if(d > 0)
        {
            d -= 10;
        }
    }

    return d;
}

static int D3[8][2] = 
{
    -1,-1, -1,0,  -1,1,  0,1,  1,1,  1,0,  1,-1,  0,-1
};

static int D5[12][2] = 
{
    -2,-1, -2,0,  -2,1, -1,2,  0,2,  1,2, 2,1,  2,0,  2,-1, 1,-2, 0,-2, -1,-2
};

static int D7[24][2] = 
{
    -3,-3, -3,-2, -3,-1, -3,0, -3,1, -3,2, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3, 3,3, 3,2, 3,1, 3,0,
    3,-1, 3,-2, 3,-3, 2,-3, 1,-3, 0,-3, -1,-3, -2,-3
};

// 得到奇异点特征点
int getSingularMinutia(BYTE *lpOrient, int Width, int Height, char flag, LPVOID feature)
{
    int    x, y, i;
    int    num;
    int    sum1, sum2;
    int    d;
    unsigned char *pOriMap;

    int    oriV;
    int    a1, a2;
    DBLPOINT  singuArr[30];

    int    value;
    double dis;
    bool   bFound = false;
    bool   fg = false;
    int    D3[8][2] = {
        -1,-1, -1,0,  -1,1,  0,1,  1,1,  1,0,  1,-1,  0,-1
    };
    int    D5[12][2] = {
        -2,-1, -2,0,  -2,1, -1,2,  0,2,  1,2, 2,1,  2,0,  2,-1, 1,-2, 0,-2, -1,-2
    };
    int    D7[24][2] = {
        -3,-3, -3,-2, -3,-1, -3,0, -3,1, -3,2, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3, 3,3, 3,2, 3,1, 3,0,
        3,-1, 3,-2, 3,-3, 2,-3, 1,-3, 0,-3, -1,-3, -2,-3
    };

    FEATURE *g_Feature = (FEATURE*)(feature);


    num = 0;

    memset(singuArr, 0, sizeof(singuArr));				//初始化奇异点数组，清零

    for(y = 3; y < Height-3; y++)
    {
        for(x = 3; x < Width-3; x++)					//遍历整幅图
        {
            pOriMap = lpOrient + y*Width + x;			//获得某点的方向场指针
            oriV = *pOriMap;							//获取某点的方向场的值

            if(oriV == 255)								//若是背景区域，则跳入下一个循环
            {
                continue;
            }

            fg = false;
            for(i = 0; i < 24; i++)
            {
                if(pOriMap[D7[i][1]*Width + D7[i][0]]==255)
                {
                    fg = true;
                    break;
                }
            }
            if(fg)
            {
                continue;
            }

            sum1 = 0;
            for(i = 0; i < 8; i++)
            {
                a1 = pOriMap[D3[i][1]*Width + D3[i][0]]/24;
                a2 = pOriMap[D3[(i+1)%8][1]*Width + D3[(i+1)%8][0]]/24;
                d = getOriChange(a1, a2, flag);

                if(abs(d) > 5)
                {
                    break;
                }

                sum1 += d;
            }
            sum2 = 0;
            for(i = 0; i < 12; i++)
            {
                a1 = pOriMap[D5[i][1]*Width + D5[i][0]]/24;
                a2 = pOriMap[D5[(i+1)%12][1]*Width + D5[(i+1)%12][0]]/24;
                d = getOriChange(a1, a2, flag);

                if(abs(d) > 5)
                {
                    break;
                }

                sum2 += d;
            }

            if(flag == -1)									//中心点
            {
                value = -10;
            }
            else if(flag == 1)								//三角点
            {
                value = 10;
            }
            if(sum2 == value && sum1 == value)
            {
                bFound = false;
                for(i = 0; i < num; i++)
                {
                    dis = sqrt((double)((x - singuArr[i].x)*(x - singuArr[i].x) +
                        (y - singuArr[i].y)*(y - singuArr[i].y)));
                    if(dis < 4)
                    {
                        singuArr[i].x = (singuArr[i].x + x)/2.0;
                        singuArr[i].y = (singuArr[i].y + y)/2.0;
                        bFound = true;
                        break;
                    }

                }
                if(!bFound)
                {
                    singuArr[num].x = x;
                    singuArr[num].y = y;
                    num++;
                    if(num >= MAX_SINGULARYNUM)				//若奇异点数量超过最大限制，则停止寻找奇异点
                    {
                        goto next;
                    }
                }

            }
        }
    }

next:

    int  trilen = 16;
    int N = 0;											//奇异点的个数
    for(i = 0; i < num; i++)								//将找到的奇异点存入输入数组
    {
        //lpArr[*lpNum + i].x = (long)singuArr[i].x;
        //lpArr[*lpNum + i].y = (long)singuArr[i].y;	

        int x = (long)singuArr[i].x;
        int y = (long)singuArr[i].y;

        //if (*(g_lpDivide + y * Width + x) == 255) continue;

        if (((x + 0.0) / Width < 0.1) || ((x + 0.0) / Width > 0.9)) 
            continue;

        if (((y + 0.0) / Height < 0.1 ) || ((y + 0.0) / Height > 0.9))
            continue;



        g_Feature->minutia[g_Feature->minutiaNum + N].x = x;
        g_Feature->minutia[g_Feature->minutiaNum + N].y = y;

        g_Feature->minutia[g_Feature->minutiaNum + N].type = (flag == -1) ? VF_MINUTIA_CORE : VF_MINUTIA_DELTA;				
        g_Feature->minutia[g_Feature->minutiaNum + N].direction = 0;				

        N++;
    }

    g_Feature->minutiaNum += N;

    return 0;
}

*/

