
#include "stdafx.h"
#include "BigMatch.h"

enum
{
    BIG_MATCH_SIG,
    BIG_MATCH_POW,
    BIG_MATCH_HEAD,
};

BigMatch::BigMatch()
{

}

BigMatch::~BigMatch()
{

}

/**
 *\fn        VECTOR_INT strToVector(const char *num)
 *\brief     将字符串转换成数组
 *\param[in] const char * num 字符串
 *\return    VECTOR_INT 数组
 */
VECTOR_INT BigMatch::strToVector(const char *num)
{
    VECTOR_INT ret;

    if (NULL == num) return ret;

    int temp = 0;
    int numLen = strlen(num);

    ret.push_back(num[0] == '-'); // 正负号
    ret.push_back(0); // 位记数

    for (int i = ret[BIG_MATCH_SIG]; i < numLen; i++)
    {
        if ('.' == num[i])
        {
            ret[BIG_MATCH_POW] = i - numLen + 1;
            continue;
        }

        temp = num[i] - '0';

        if (temp < 0 || temp > 9) break;

        ret.push_back(temp);
    }

    return ret;
}

/**
 *\fn        int vectorToStr(const VECTOR_INT &num, char *result, int resultLen)
 *\brief     将数组转换成字符串
 *\param[in] const VECTOR_INT & num 
 *\param[in] char * result 字符串数组
 *\param[in] int resultLen 字符串缓冲区长
 *\return    int 0成功,其它失败
 */
int BigMatch::vectorToStr(const VECTOR_INT &num, char *result, int resultLen)
{
    if (NULL == result || resultLen < num.size()) return -1;

    char temp[10] = "";
    int len = num.size();

    strcpy(result, (num[BIG_MATCH_SIG] ? "-" : ""));

    for (int i = BIG_MATCH_HEAD; i < len; i++)
    {
        if (num[BIG_MATCH_POW] == (i - len))
        {
            strcat(result, ".");
        }

        itoa(num[i], temp, sizeof(temp));

        strcat(result, temp);
    }

    for (int i = strlen(result) - 1; i >= 0; i--)
    {
        if (result[i] == '0')
        {
            result[i] = '\0';
        }
        else
        {
            break;
        }
    }

    return 0;
}

/**
 *\fn        VECTOR_INT arrayNumber(const VECTOR_INT &num)
 *\brief     整理数组实现进位借位操作
 *\param[in] const VECTOR_INT & num 数组
 *\return    VECTOR_INT 整理后数组
 */
VECTOR_INT BigMatch::arrayNumber(const VECTOR_INT &num)
{
    VECTOR_INT ret = num;

    for (int i = ret.size() - 1; i >= BIG_MATCH_HEAD; i--)
    {
        if (ret[i] >= 10)
        {
            if (i == BIG_MATCH_HEAD) // 最高位,大于10向前进位,新建个节点
            {
                VECTOR_INT::iterator iter = ret.begin();
                iter += BIG_MATCH_HEAD;
                ret.insert(iter, 0);
            }
            
            ret[i-1] += ret[i] / 10; // 向前进位
            ret[i] %= 10;
        }
    }

    return ret;
}

/**
 *\fn        VECTOR_INT add(const VECTOR_INT &num1, const VECTOR_INT &num2)
 *\brief     组数相加
 *\param[in] const VECTOR_INT & num1 数组1
 *\param[in] const VECTOR_INT & num2 数组2
 *\return    VECTOR_INT 相加后的结果数组
 */
VECTOR_INT BigMatch::add(const VECTOR_INT &num1, const VECTOR_INT &num2)
{
    VECTOR_INT n1 = num1;
    VECTOR_INT n2 = num2;

    int move = (n1[BIG_MATCH_POW] != n2[BIG_MATCH_POW]) ? (n1[BIG_MATCH_POW] - n2[BIG_MATCH_POW]) : 0;

    if (move > 0)
    {
        n1[BIG_MATCH_POW] = n2[BIG_MATCH_POW];

        for (int i = 0; i < move; i++)
        {
            n1.push_back(0);
        }
    }
    else if (move < 0)
    {
        n2[BIG_MATCH_POW] = n1[BIG_MATCH_POW];

        for (int i = 0; i > move; i--)
        {
            n2.push_back(0);
        }

        move = -move;
    }

    int n1Len = n1.size();
    int n2Len = n2.size();
    int subLen = n1Len - n2Len;

    if (subLen < 0)
    {
        VECTOR_INT temp;
        temp = n1;
        n1 = n2;
        n2 = temp;

        n1Len = n1.size();
        n2Len = n2.size();
        subLen = n1Len - n2Len;
    }
    
    VECTOR_INT ret;
    ret.push_back(n1[BIG_MATCH_SIG]);
    ret.push_back(n1[BIG_MATCH_POW]);

    for (int i = BIG_MATCH_HEAD; i < n1Len; i++)
    {
        if ((i - subLen) > BIG_MATCH_POW)
        {
            // TRACE("n1[%d]=%d n2[%d]=%d\n", i, n1[i], i - subLen, n2[i - subLen]); 

            ret.push_back(n1[i] + n2[i - subLen]);
        }
        else
        {
            ret.push_back(n1[i]);
        }
    }
    
    return arrayNumber(ret);
}

/**
 *\fn        VECTOR_INT add(const VECTOR_INT &num1, const VECTOR_INT &num2)
 *\brief     组数相减
 *\param[in] const VECTOR_INT & num1 数组1
 *\param[in] const VECTOR_INT & num2 数组2
 *\return    VECTOR_INT 相减后的结果数组
 */
VECTOR_INT BigMatch::sub(const VECTOR_INT &num1, const VECTOR_INT &num2)
{
    VECTOR_INT n1 = num1;
    VECTOR_INT n2 = num2;

    int move = (n1[BIG_MATCH_POW] != n2[BIG_MATCH_POW]) ? (n1[BIG_MATCH_POW] - n2[BIG_MATCH_POW]) : 0;

    if (move > 0)
    {
        n1[BIG_MATCH_POW] = n2[BIG_MATCH_POW];

        for (int i = 0; i < move; i++)
        {
            n1.push_back(0);
        }
    }
    else if (move < 0)
    {
        n2[BIG_MATCH_POW] = n1[BIG_MATCH_POW];

        for (int i = 0; i > move; i--)
        {
            n2.push_back(0);
        }

        move = -move;
    }

    int n1Len = n1.size();
    int n2Len = n2.size();
    int subLen = n1Len - n2Len;
    bool sig = false; // 正数

    if (subLen < 0)
    {
        VECTOR_INT temp;
        temp = n1;
        n1 = n2;
        n2 = temp;

        n1Len = n1.size();
        n2Len = n2.size();
        subLen = n1Len - n2Len;
        sig = true; // 负数
    }

    VECTOR_INT ret;
    ret.push_back(sig);
    ret.push_back(n1[BIG_MATCH_POW]);

    for (int i = n1Len - 1; i >= BIG_MATCH_HEAD; i--)
    {
        if ((i - subLen) >= BIG_MATCH_HEAD)
        {
            // TRACE("n1[%d]=%d n2[%d]=%d -> ", i, n1[i], i - subLen, n2[i - subLen]); 

            if ((n1[i] - n2[i - subLen]) < 0)
            {
                if ((i-1) >= 1) n1[i-1]--;
                n1[i] += 10;
            }

            // TRACE("n1[%d]=%d n2[%d]=%d %d\n ", i, n1[i], i - subLen, n2[i - subLen], n1[i] - n2[i - subLen]);

            ret.push_back(n1[i] - n2[i - subLen]);
        }
        else
        {
            ret.push_back(n1[i]);
        }
    }

    for (int i = 0; i < (n1Len - BIG_MATCH_HEAD)  / 2; i++)
    {
        subLen = ret[i + BIG_MATCH_HEAD];
        ret[i + BIG_MATCH_HEAD] = ret[n1Len - i - 1];
        ret[n1Len - i - 1] = subLen;
    }
    
    return arrayNumber(ret);
}

/**
 *\fn        VECTOR_INT mul(const VECTOR_INT &num1, const VECTOR_INT &num2)
 *\brief     组数相乘
 *\param[in] const VECTOR_INT & num1 数组1
 *\param[in] const VECTOR_INT & num2 数组2
 *\return    VECTOR_INT 相乘后的结果数组
 */
VECTOR_INT BigMatch::mul(const VECTOR_INT &num1, const VECTOR_INT &num2)
{
    VECTOR_INT n1 = num1;
    VECTOR_INT n2 = num2;

    if (n1[BIG_MATCH_SIG] == n2[BIG_MATCH_SIG])
    {
        if (n1[BIG_MATCH_SIG])
        {
            n1[BIG_MATCH_SIG] = FALSE;
            n2[BIG_MATCH_SIG] = FALSE;
        }
    }
    else
    {
        n1[BIG_MATCH_SIG] = TRUE;
        n2[BIG_MATCH_SIG] = FALSE;
    }

    VECTOR_INT temp;
    VECTOR_INT ret;
    ret.push_back(n1[BIG_MATCH_SIG]);
    ret.push_back(0);

    for (int i = num2.size() - 1; i >= BIG_MATCH_HEAD; i--)
    {
        temp = mul(n1, n2[i]);
        temp[BIG_MATCH_POW] += (n2.size() - 1 - i);
        ret = add(ret, temp);
    }
    
    ret[BIG_MATCH_POW] = n1[BIG_MATCH_POW] + n2[BIG_MATCH_POW];

    return arrayNumber(ret);
}

/**
 *\fn        VECTOR_INT div(const VECTOR_INT &num1, const VECTOR_INT &num2)
 *\brief     组数相除
 *\param[in] const VECTOR_INT & num1 数组1
 *\param[in] const VECTOR_INT & num2 数组2
 *\return    VECTOR_INT 相除后的结果数组
 */
VECTOR_INT BigMatch::div(const VECTOR_INT &num1, const VECTOR_INT &num2)
{
    VECTOR_INT temp;
    VECTOR_INT ret;
    ret.push_back(num1[BIG_MATCH_SIG]);
    ret.push_back(num1[BIG_MATCH_POW]);

    for (int i = BIG_MATCH_HEAD; i < num2.size(); i++)
    {
        temp = mul(num1, num2[i]);
        temp[BIG_MATCH_POW]++;
        ret = add(ret, temp);
    }

    return arrayNumber(ret);
}

/**
 *\fn        VECTOR_INT mul(const VECTOR_INT &num1, int num2)
 *\brief     组数相乘
 *\param[in] const VECTOR_INT & num1 数组1
 *\param[in] int num2 数据
 *\return    VECTOR_INT 相乘后的结果数组
 */
VECTOR_INT BigMatch::mul(const VECTOR_INT &num1, int num2)
{
    VECTOR_INT ret = num1;
    ret[BIG_MATCH_SIG] = FALSE;

    for (int i = BIG_MATCH_HEAD; i < num1.size(); i++)
    {
        ret[i] *= num2;
    }

    return arrayNumber(ret);
}

/**
 *\fn        bool equ(const char *number1, const char *number2)
 *\brief     是否相等
 *\param[in] const char * number1 数字1
 *\param[in] const char * number2 数字2
 *\return    bool 是否相等
 */
bool BigMatch::equ(const char *number1, const char *number2)
{
    return false;
}

/**
 *\fn        int add(const char *number1, const char *number2, char *result, int resultLen)
 *\brief     字符串型数字相加
 *\param[in] const char * number1 数字1
 *\param[in] const char * number2 数字2
 *\param[in] char * result 相加后的数字
 *\param[in] int resultLen 相加后的数字缓冲区长
 *\return    int 0成功,其它失败
 */
int BigMatch::add(const char *number1, const char *number2, char *result, int resultLen)
{
    if (NULL == number1 || NULL == number2 || NULL == result || resultLen <= strlen(number1)) return -1;

    VECTOR_INT num1 = strToVector(number1);
    VECTOR_INT num2 = strToVector(number2);
    VECTOR_INT num3;

    if (num1[BIG_MATCH_SIG] == num2[BIG_MATCH_SIG])
    {
        num3 = add(num1, num2);
    }
    else if(num1[BIG_MATCH_SIG] < num2[BIG_MATCH_SIG])
    {
        num2[BIG_MATCH_SIG] = FALSE;
        num3 = sub(num1, num2);
    }
    else
    {
        num1[BIG_MATCH_SIG] = FALSE;
        num3 = sub(num2, num1);
    }

    return vectorToStr(num3, result, resultLen);
}

/**
 *\fn        int add(const char *number1, const char *number2, char *result, int resultLen)
 *\brief     字符串型数字相减
 *\param[in] const char * number1 数字1
 *\param[in] const char * number2 数字2
 *\param[in] char * result 相减后的数字
 *\param[in] int resultLen 相减后的数字缓冲区长
 *\return    int 0成功,其它失败
 */
int BigMatch::sub(const char *number1, const char *number2, char *result, int resultLen)
{
    if (NULL == number1 || NULL == number2 || NULL == result || resultLen <= strlen(number1)) return -1;

    VECTOR_INT num1 = strToVector(number1);
    VECTOR_INT num2 = strToVector(number2);
    VECTOR_INT num3;

    if (num1[BIG_MATCH_SIG] == num2[BIG_MATCH_SIG])
    {
        if (!num1[BIG_MATCH_SIG])
        {
            num3 = sub(num1, num2);
        }
        else
        {
            num2[BIG_MATCH_SIG] = FALSE;
            num3 = sub(num2, num1);
        }
    }
    else
    {
        num2[BIG_MATCH_SIG] = (num1[BIG_MATCH_SIG] > num2[BIG_MATCH_SIG]);
        num3 = add(num1, num2);
    }

    return vectorToStr(num3, result, resultLen);
}

/**
 *\fn        int mul(const char *number1, const char *number2, char *result, int resultLen)
 *\brief     字符串型数字相乘
 *\param[in] const char * number1 数字1
 *\param[in] const char * number2 数字2
 *\param[in] char * result 相乘后的数字
 *\param[in] int resultLen 相乘后的数字缓冲区长
 *\return    int 0成功,其它失败
 */
int BigMatch::mul(const char *number1, const char *number2, char *result, int resultLen)
{
    if (NULL == number1 || NULL == number2 || NULL == result || resultLen <= (strlen(number1) + strlen(number2))) return -1;

    VECTOR_INT num1 = strToVector(number1);
    VECTOR_INT num2 = strToVector(number2);
    VECTOR_INT num3 = mul(num1, num2);
    return vectorToStr(num3, result, resultLen);
}

/**
 *\fn        int div(const char *number1, const char *number2, char *result, int resultLen)
 *\brief     字符串型数字相除
 *\param[in] const char * number1 数字1
 *\param[in] const char * number2 数字2
 *\param[in] char * result 相除后的数字
 *\param[in] int resultLen 相除后的数字缓冲区长
 *\return    int 0成功,其它失败
 */
int BigMatch::div(const char *number1, const char *number2, char *result, int resultLen)
{
    if (NULL == number1 || NULL == number2 || NULL == result || resultLen <= strlen(number1)) return -1;

    VECTOR_INT num1 = strToVector(number1);
    VECTOR_INT num2 = strToVector(number2);
    VECTOR_INT num3;
    return vectorToStr(num3, result, resultLen);
}

/**
 *\fn        int mod(const char *number1, const char *number2, char *result, int resultLen)
 *\brief     字符串型数字取余
 *\param[in] const char * number1 数字1
 *\param[in] const char * number2 数字2
 *\param[in] char * result 相除后的数字
 *\param[in] int resultLen 相除后的数字缓冲区长
 *\return    int 0成功,其它失败
 */
int BigMatch::mod(const char *number1, const char *number2, char *result, int resultLen)
{
    VECTOR_INT num1 = strToVector(number1);
    VECTOR_INT num2 = strToVector(number2);
    VECTOR_INT num3;
    return vectorToStr(num3, result, resultLen);
}