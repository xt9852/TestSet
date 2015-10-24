
#pragma once
#include <vector>


typedef std::vector<int> VECTOR_INT; // 第一个元素为正负号, 第一个元素为位记数(小数点的位置)

class BigMatch
{
public:
    BigMatch();
    ~BigMatch();

protected:    
    /**
     *\fn        VECTOR_INT strToVector(const char *num)
     *\brief     将字符串转换成数组
     *\param[in] const char * num 字符串
     *\return    VECTOR_INT 数组
     */
    VECTOR_INT strToVector(const char *num);

    /**
     *\fn        int vectorToStr(const VECTOR_INT &num, char *result, int resultLen)
     *\brief     将数组转换成字符串
     *\param[in] const VECTOR_INT & num 
     *\param[in] char * result 字符串数组
     *\param[in] int resultLen 字符串缓冲区长
     *\return    int 0成功,其它失败
     */
    int vectorToStr(const VECTOR_INT &num, char *result, int resultLen);

    /**
     *\fn        VECTOR_INT arrayNumber(const VECTOR_INT &num)
     *\brief     整理数组实现进位借位操作
     *\param[in] const VECTOR_INT & num 数组
     *\return    VECTOR_INT 整理后数组
     */
    VECTOR_INT arrayNumber(const VECTOR_INT &num);
    
    /**
     *\fn        VECTOR_INT add(const VECTOR_INT &num1, const VECTOR_INT &num2)
     *\brief     组数相加
     *\param[in] const VECTOR_INT & num1 数组1
     *\param[in] const VECTOR_INT & num2 数组2
     *\return    VECTOR_INT 相加后的结果数组
     */
    VECTOR_INT add(const VECTOR_INT &num1, const VECTOR_INT &num2);

    /**
     *\fn        VECTOR_INT add(const VECTOR_INT &num1, const VECTOR_INT &num2)
     *\brief     组数相减
     *\param[in] const VECTOR_INT & num1 数组1
     *\param[in] const VECTOR_INT & num2 数组2
     *\return    VECTOR_INT 相减后的结果数组
     */
    VECTOR_INT sub(const VECTOR_INT &num1, const VECTOR_INT &num2);

    /**
     *\fn        VECTOR_INT mul(const VECTOR_INT &num1, const VECTOR_INT &num2)
     *\brief     组数相乘
     *\param[in] const VECTOR_INT & num1 数组1
     *\param[in] const VECTOR_INT & num2 数组2
     *\return    VECTOR_INT 相乘后的结果数组
     */
    VECTOR_INT mul(const VECTOR_INT &num1, const VECTOR_INT &num2);

    /**
     *\fn        VECTOR_INT div(const VECTOR_INT &num1, const VECTOR_INT &num2)
     *\brief     组数相除
     *\param[in] const VECTOR_INT & num1 数组1
     *\param[in] const VECTOR_INT & num2 数组2
     *\return    VECTOR_INT 相除后的结果数组
     */
    VECTOR_INT div(const VECTOR_INT &num1, const VECTOR_INT &num2);

    /**
     *\fn        VECTOR_INT mul(const VECTOR_INT &num1, int num2)
     *\brief     组数相乘
     *\param[in] const VECTOR_INT & num1 数组1
     *\param[in] int num2 数据
     *\return    VECTOR_INT 相乘后的结果数组
     */
    VECTOR_INT mul(const VECTOR_INT &num1, int num2);

public:
    /**
     *\fn        int add(const char *number1, const char *number2, char *result, int resultLen)
     *\brief     字符串型数字相加
     *\param[in] const char * number1 数字1
     *\param[in] const char * number2 数字2
     *\param[in] char * result 相加后的数字
     *\param[in] int resultLen 相加后的数字缓冲区长
     *\return    int 0成功,其它失败
     */
    int add(const char *number1, const char *number2, char *result, int resultLen);

    /**
     *\fn        int add(const char *number1, const char *number2, char *result, int resultLen)
     *\brief     字符串型数字相减
     *\param[in] const char * number1 数字1
     *\param[in] const char * number2 数字2
     *\param[in] char * result 相减后的数字
     *\param[in] int resultLen 相减后的数字缓冲区长
     *\return    int 0成功,其它失败
     */
    int sub(const char *number1, const char *number2, char *result, int resultLen);

    /**
     *\fn        int mul(const char *number1, const char *number2, char *result, int resultLen)
     *\brief     字符串型数字相乘
     *\param[in] const char * number1 数字1
     *\param[in] const char * number2 数字2
     *\param[in] char * result 相乘后的数字
     *\param[in] int resultLen 相乘后的数字缓冲区长
     *\return    int 0成功,其它失败
     */
    int mul(const char *number1, const char *number2, char *result, int resultLen);

    /**
     *\fn        int div(const char *number1, const char *number2, char *result, int resultLen)
     *\brief     字符串型数字相除
     *\param[in] const char * number1 数字1
     *\param[in] const char * number2 数字2
     *\param[in] char * result 相除后的数字
     *\param[in] int resultLen 相除后的数字缓冲区长
     *\return    int 0成功,其它失败
     */
    int div(const char *number1, const char *number2, char *result, int resultLen);

    /**
     *\fn        int mod(const char *number1, const char *number2, char *result, int resultLen)
     *\brief     字符串型数字取余
     *\param[in] const char * number1 数字1
     *\param[in] const char * number2 数字2
     *\param[in] char * result 相除后的数字
     *\param[in] int resultLen 相除后的数字缓冲区长
     *\return    int 0成功,其它失败
     */
    int mod(const char *number1, const char *number2, char *result, int resultLen);

    /**
     *\fn        bool equ(const char *number1, const char *number2)
     *\brief     是否相等
     *\param[in] const char * number1 数字1
     *\param[in] const char * number2 数字2
     *\return    bool 是否相等
     */
    bool equ(const char *number1, const char *number2);

};