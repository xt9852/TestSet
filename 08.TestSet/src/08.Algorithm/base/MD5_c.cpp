/**********************************************************
***
*
** CopyRight ( C ) Technology Co. Ltd.
*
** SourceFile:   MD5.cpp
*
** Module:   MD5
*
** Author&Date:
*
** Reversion:
*
** Description:
*
** Inheritance:
*
**********************************************************/

#include "stdafx.h"
#include "MD5_c.h"
#include <io.h>



CMD5c::CMD5c()
{
}

CMD5c::~CMD5c()
{
}

// 得到一个十六进制的字符串,如(1FA3F9D23B55A2D0)
// pcResult		[OUT]
// pcSourceBuff [IN]
void CMD5c::GetStrMD5(CHAR *pcResult,const CHAR *pcSourceBuff,INT iSourceBuffLen)
{
	if( NULL == pcResult || NULL == pcSourceBuff )
		return;

	unsigned char MD5[ 50 ] = {""};

	GetMD5_128( (CHAR*)MD5, pcSourceBuff, iSourceBuffLen);

	static unsigned char base16Chars[17] = "0123456789ABCDEF";

	for( unsigned int i = 0; i < 16; i++)
	{
		int a = MD5[i] >> 4;

		pcResult[2*i] = base16Chars[MD5[i] >> 4];
		pcResult[2*i+1] = base16Chars[MD5[i] & 0x0f];
	}
}

void CMD5c::GetMD5_128(CHAR *pcResult,INT iFileID,INT iFileOff,INT iFileLen)
{
	if (iFileLen==0)
		memset(pcResult,'\0',16);
	else
	{
		MD5_CTX context;
		INT len = 1024;
		INT readByte;
		UCHAR buffer[1024], digest[16];
		MD5Init (&context);
		lseek(iFileID,iFileOff,SEEK_SET);
		INT i=0;
		while(iFileLen > len)
		{
			lseek(iFileID,len*i+iFileOff,SEEK_SET);
			readByte = read(iFileID,buffer,len);
			MD5Update (&context, buffer, readByte);
			iFileLen-=len;
			++i;
		}
		lseek(iFileID,len*i+iFileOff,SEEK_SET);
		readByte = read(iFileID,buffer,iFileLen);
		MD5Update (&context, buffer, readByte);
		MD5Final (digest, &context);
		memcpy(pcResult,(CHAR *)digest,16);
	}
}

void CMD5c::GetMD5_128(CHAR *pcResult,const CHAR *pcSourceBuff,INT iSourceBuffLen)
{
	if (iSourceBuffLen==0)
		memset(pcResult,'\0',16);
	else
	{
		MD5_CTX context;
		UCHAR digest[16];
		INT len = 1024;
		MD5Init (&context);
		MD5Update (&context, (UCHAR*)pcSourceBuff, iSourceBuffLen);
		MD5Final (digest, &context);
		memcpy(pcResult,(CHAR *)digest,16);
	}
}

bool CMD5c::VerifyMD5_128(const CHAR *pcVerifyBuff,INT iFileID,INT iFileOff,INT iFileLen)
{
	if (iFileLen==0) return(true);
	CHAR acBuff[16];
	GetMD5_128(acBuff,iFileID,iFileOff,iFileLen);
	if (memcmp(pcVerifyBuff,acBuff,16))
		return(false);
	return(true);
}

bool CMD5c::VerifyMD5_128(const CHAR *pcVerifyBuff,const CHAR *pcSourceBuff,INT iSourceBuffLen)
{
	if (iSourceBuffLen==0) return(true);
	CHAR acBuff[16];
	GetMD5_128(acBuff,pcSourceBuff,iSourceBuffLen);
	if (memcmp(pcVerifyBuff,acBuff,16))
		return(false);
	return(true);
}

// MD5内部实现函数
void CMD5c::MD5Init(MD5_CTX *context)
{
	context->count[0] = context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

void CMD5c::MD5Update(MD5_CTX *context, UCHAR *input,UINT inputLen)
{
	UINT i, index, partLen;

	index = (UINT)((context->count[0] >> 3) & 0x3F);

	if ((context->count[0] += ((MD5_UINT4)inputLen << 3)) < ((MD5_UINT4)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((MD5_UINT4)inputLen >> 29);

	partLen = 64 - index;

	if (inputLen >= partLen)
	{
		MD5_memcpy((MD5_POINTER)&context->buffer[index], (MD5_POINTER)input, partLen);
		MD5Transform (context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform (context->state, &input[i]);

		index = 0;
	}
	else
		i = 0;

	MD5_memcpy((MD5_POINTER)&context->buffer[index], (MD5_POINTER)&input[i],inputLen-i);
}

void CMD5c::MD5Final(UCHAR digest[16], MD5_CTX *context)
{
	UCHAR bits[8];
	UINT index, padLen;

	Encode (bits, context->count, 8);

	index = (UINT)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update (context,(UCHAR*) PADDING, padLen);

	MD5Update (context, bits, 8);
	Encode (digest, context->state, 16);

	MD5_memset ((MD5_POINTER)context, 0, sizeof (*context));
}

void CMD5c::MD5Transform(MD5_UINT4 state[4],UCHAR block[64])
{
	INT i=0;

	MD5_UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

	Decode (x, block, 64);

	//Round 1
	FF (a, b, c, d, x[ 0], MD5_S11, 0xd76aa478); // 1
	FF (d, a, b, c, x[ 1], MD5_S12, 0xe8c7b756); // 2
	FF (c, d, a, b, x[ 2], MD5_S13, 0x242070db); // 3
	FF (b, c, d, a, x[ 3], MD5_S14, 0xc1bdceee); // 4
	FF (a, b, c, d, x[ 4], MD5_S11, 0xf57c0faf); // 5
	FF (d, a, b, c, x[ 5], MD5_S12, 0x4787c62a); // 6
	FF (c, d, a, b, x[ 6], MD5_S13, 0xa8304613); // 7
	FF (b, c, d, a, x[ 7], MD5_S14, 0xfd469501); // 8
	FF (a, b, c, d, x[ 8], MD5_S11, 0x698098d8); // 9
	FF (d, a, b, c, x[ 9], MD5_S12, 0x8b44f7af); // 10
	FF (c, d, a, b, x[10], MD5_S13, 0xffff5bb1); // 11
	FF (b, c, d, a, x[11], MD5_S14, 0x895cd7be); // 12
	FF (a, b, c, d, x[12], MD5_S11, 0x6b901122); // 13
	FF (d, a, b, c, x[13], MD5_S12, 0xfd987193); // 14
	FF (c, d, a, b, x[14], MD5_S13, 0xa679438e); // 15
	FF (b, c, d, a, x[15], MD5_S14, 0x49b40821); // 16

	//Round 2
	GG (a, b, c, d, x[ 1], MD5_S21, 0xf61e2562); // 17
	GG (d, a, b, c, x[ 6], MD5_S22, 0xc040b340); // 18
	GG (c, d, a, b, x[11], MD5_S23, 0x265e5a51); // 19
	GG (b, c, d, a, x[ 0], MD5_S24, 0xe9b6c7aa); // 20
	GG (a, b, c, d, x[ 5], MD5_S21, 0xd62f105d); // 21
	GG (d, a, b, c, x[10], MD5_S22,  0x2441453); // 22
	GG (c, d, a, b, x[15], MD5_S23, 0xd8a1e681); // 23
	GG (b, c, d, a, x[ 4], MD5_S24, 0xe7d3fbc8); // 24
	GG (a, b, c, d, x[ 9], MD5_S21, 0x21e1cde6); // 25
	GG (d, a, b, c, x[14], MD5_S22, 0xc33707d6); // 26
	GG (c, d, a, b, x[ 3], MD5_S23, 0xf4d50d87); // 27
	GG (b, c, d, a, x[ 8], MD5_S24, 0x455a14ed); // 28
	GG (a, b, c, d, x[13], MD5_S21, 0xa9e3e905); // 29
	GG (d, a, b, c, x[ 2], MD5_S22, 0xfcefa3f8); // 30
	GG (c, d, a, b, x[ 7], MD5_S23, 0x676f02d9); // 31
	GG (b, c, d, a, x[12], MD5_S24, 0x8d2a4c8a); // 32

	//Round 3
	HH (a, b, c, d, x[ 5], MD5_S31, 0xfffa3942); // 33
	HH (d, a, b, c, x[ 8], MD5_S32, 0x8771f681); // 34
	HH (c, d, a, b, x[11], MD5_S33, 0x6d9d6122); // 35
	HH (b, c, d, a, x[14], MD5_S34, 0xfde5380c); // 36
	HH (a, b, c, d, x[ 1], MD5_S31, 0xa4beea44); // 37
	HH (d, a, b, c, x[ 4], MD5_S32, 0x4bdecfa9); // 38
	HH (c, d, a, b, x[ 7], MD5_S33, 0xf6bb4b60); // 39
	HH (b, c, d, a, x[10], MD5_S34, 0xbebfbc70); // 40
	HH (a, b, c, d, x[13], MD5_S31, 0x289b7ec6); // 41
	HH (d, a, b, c, x[ 0], MD5_S32, 0xeaa127fa); // 42
	HH (c, d, a, b, x[ 3], MD5_S33, 0xd4ef3085); // 43
	HH (b, c, d, a, x[ 6], MD5_S34,  0x4881d05); // 44
	HH (a, b, c, d, x[ 9], MD5_S31, 0xd9d4d039); // 45
	HH (d, a, b, c, x[12], MD5_S32, 0xe6db99e5); // 46
	HH (c, d, a, b, x[15], MD5_S33, 0x1fa27cf8); // 47
	HH (b, c, d, a, x[ 2], MD5_S34, 0xc4ac5665); // 48

	//Round 4
	II (a, b, c, d, x[ 0], MD5_S41, 0xf4292244); // 49
	II (d, a, b, c, x[ 7], MD5_S42, 0x432aff97); // 50
	II (c, d, a, b, x[14], MD5_S43, 0xab9423a7); // 51
	II (b, c, d, a, x[ 5], MD5_S44, 0xfc93a039); // 52
	II (a, b, c, d, x[12], MD5_S41, 0x655b59c3); // 53
	II (d, a, b, c, x[ 3], MD5_S42, 0x8f0ccc92); // 54
	II (c, d, a, b, x[10], MD5_S43, 0xffeff47d); // 55
	II (b, c, d, a, x[ 1], MD5_S44, 0x85845dd1); // 56
	II (a, b, c, d, x[ 8], MD5_S41, 0x6fa87e4f); // 57
	II (d, a, b, c, x[15], MD5_S42, 0xfe2ce6e0); // 58
	II (c, d, a, b, x[ 6], MD5_S43, 0xa3014314); // 59
	II (b, c, d, a, x[13], MD5_S44, 0x4e0811a1); // 60
	II (a, b, c, d, x[ 4], MD5_S41, 0xf7537e82); // 61
	II (d, a, b, c, x[11], MD5_S42, 0xbd3af235); // 62
	II (c, d, a, b, x[ 2], MD5_S43, 0x2ad7d2bb); // 63
	II (b, c, d, a, x[ 9], MD5_S44, 0xeb86d391); // 64

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	MD5_memset((MD5_POINTER)x, 0, sizeof (x));
}

void CMD5c::Encode(UCHAR *output,MD5_UINT4 *input,UINT len)
{
	UINT i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
	{
		output[j] = (UCHAR)(input[i] & 0xff);
		output[j+1] = (UCHAR)((input[i] >> 8) & 0xff);
		output[j+2] = (UCHAR)((input[i] >> 16) & 0xff);
		output[j+3] = (UCHAR)((input[i] >> 24) & 0xff);
	}
}

void CMD5c::Decode(MD5_UINT4 *output,UCHAR *input,UINT len)
{
	UINT i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((MD5_UINT4)input[j]) | (((MD5_UINT4)input[j+1]) << 8) |
		(((MD5_UINT4)input[j+2]) << 16) | (((MD5_UINT4)input[j+3]) << 24);
}

void CMD5c::MD5_memcpy(MD5_POINTER output,MD5_POINTER input,UINT len)
{
	UINT i;

	for (i = 0; i < len; i++)
		output[i] = input[i];
}

void CMD5c::MD5_memset(MD5_POINTER output,INT value,UINT len)
{
	UINT i;

	for (i = 0; i < len; i++)
		((CHAR *)output)[i] = (CHAR)value;
}

