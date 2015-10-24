
#pragma once
#include <string>


const static char BASE64_ALPHABET[64] =
{ 
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', //   0 -   9 
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', //  10 -  19 
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', //  20 -  29 
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', //  30 -  39 
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', //  40 -  49 
	'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', //  50 -  59 
	'8', '9', '+', '/'								  //  60 -  63 
};


/**
 *\class  CBase64
 *\brief  该类主要用于计算Base64校验值
 *\date   2012-06-25
 *\author 张海涛
 *\par    Revision History:
 */
class CBase64 
{ 
public:
	/**
	 *\fn         CBase64()
	 *\brief      缺省构造函数。
	 */
	CBase64();

	/**
	 *\fn         ~CBase64()
	 *\brief      析构函数。
	 */
	~CBase64();
	

	struct ToBase64i
	{
		BYTE i[3];
	};

	struct ToBase64o
	{
		BYTE o0 : 2;
		BYTE o1 : 6;
		BYTE o2 : 4;
		BYTE o3 : 4;
		BYTE o4 : 6;
		BYTE o5 : 2;
	};

	typedef union
	{
		ToBase64i i;
		ToBase64o o;

		BYTE get(int i)
		{
			switch(i)
			{
			case 0: return o.o1;
			case 1: return o.o0 << 4 | o.o3;
			case 2: return o.o2 << 2 | o.o5;
			case 3: return o.o4;
			}

			return 0;
		}

	}ToBase64;

	struct FromBase64i
	{
		BYTE i[4];
	};

	struct FromBase64o
	{
		BYTE o0 : 6;
		BYTE o1 : 2;
		BYTE o2 : 4;
		BYTE o3 : 2;
		BYTE o4 : 2;
		BYTE o5 : 2;
		BYTE o6 : 4;
		BYTE o7 : 2;
		BYTE o8 : 6;
		BYTE o9 : 2;
	};

	typedef union
	{
		FromBase64i i;
		FromBase64o o;

		BYTE get(int i)
		{
			switch(i)
			{
			case 0: return o.o0 << 2 | o.o3;
			case 1: return o.o2 << 4 | o.o6;
			case 2: return o.o5 << 6 | o.o8;
			}

			return 0;
		}

	}FromBase64;


	/**
	 *\fn         getBase64(const char *data, int len)
	 *\brief      得到BASE65串。
	 *\param[in]  data  数据。
     *\param[in]  len   数据长。
	 *\return     BASE65串
	 */
	std::string getBase64(const char *data, int len);

	/**
     *\fn         getStrFromBase64(const char *base64, char *output, int outputSize)
     *\brief      从BASE65串得到原字符串。
     *\param[in]  base64        BASE64字符串数据。
     *\param[out] output        输出数据缓冲。
     *\param[out] outputSize    输出数据缓冲区大小。
     *\return     是否成功,小于0失败,大于0为原数据长
     */
    int getStrFromBase64(const char *base64, char *output, int outputSize);
};