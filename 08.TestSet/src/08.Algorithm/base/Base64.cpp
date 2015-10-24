
#include "stdafx.h"
#include "Base64.h"


/**
 *\fn         CMD5()
 *\brief      缺省构造函数。
 */
CBase64::CBase64()
{	
}


/**
 *\fn         CMD5()
 *\brief      析构函数。
 */
CBase64::~CBase64()
{
}

/**
 *\fn         getBase64(const char *data, int len)
 *\brief      得到BASE65串。
 *\param[in]  data  数据。
 *\param[in]  len   数据长。
 *\return     BASE65串
 */
std::string CBase64::getBase64(const char *data, int len)
{
	int times = len / 3;
	int remain = len % 3;
	int endPos = len - remain;
	int tail = remain ? (3-remain) : 0;
	int pos = times * 4;
	int outputLen = len / 3 * 4 + 10;

	char *output = new char[outputLen];
	memset(output, 0, outputLen);

	ToBase64 *item = (ToBase64*)data;

	for (int i = 0; i < times; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			output[i*4 + j] = BASE64_ALPHABET[item->get(j)];
		}

		item++;
	}

	ToBase64 end = {0};
	memcpy(&end, &data[endPos], remain);

	for (int i = 0; i < remain + 1; i++)
	{
		output[pos + i] = BASE64_ALPHABET[end.get(i)];
	}

	for (int i = 0; i < tail; i++)
	{
		output[pos + remain + 1 + i] = 0x3d; // '='
	}

	std::string base64 = output;

	delete[] output;

	return base64;
}

/**
 *\fn         getStrFromBase64(const char *base64, char *output, int outputSize)
 *\brief      从BASE65串得到原字符串。
 *\param[in]  base64        BASE64字符串数据。
 *\param[out] output        输出数据缓冲。
 *\param[out] outputSize    输出数据缓冲区大小。
 *\return     是否成功,小于0失败,大于0为原数据长
 */
int CBase64::getStrFromBase64(const char *base64, char *output, int outputSize)
{
    int len = strlen(base64);

    if (outputSize < len) return -1;

	char *input = new char[len+1];
    memset(input, 0, len+1);

    for (int i = 0, j = 0; i < len; i++)
    {
        if (0x0a == base64[i])
        {
            continue;
        }
        else
        {
            input[j] = base64[i];
            j++;
        }
    }

	len = strlen(input);

	for (int i = 0; i < len; i++)
	{
		if ((input[i] >= 'A') && (input[i] <= 'Z'))
		{
			input[i] -= 'A';			
		}
		else if ((input[i] >= 'a') && (input[i] <= 'z'))
		{
			input[i] -= 71;
		}
		else if ((input[i] >= '0') && (input[i] <= '9'))
		{
			input[i] += 4;
		}
		else if (input[i] == '+')
		{
			input[i] = 62;
		}
		else if (input[i] == '/')
		{
			input[i] = 63;
		}
		else if (input[i] == 0x3d) // '='
		{
			input[i] = 0;
		}
	}
	
	int times = len / 4;
	memset(output, 0, len);

	FromBase64 *item = (FromBase64*)input;

	for (int i = 0; i < times; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			output[i*3 + j] = item->get(j);
		}

		item++;
	}

	delete[] input;

	return times * 3;
}