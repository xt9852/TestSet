/**********************************************************
***
*
** CopyRight ( C ) Technology Co. Ltd.
*
** SourceFile:   MD5.h
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
#ifndef C_MD5_H
#define C_MD5_H

#pragma once

#define MD 5

#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif


//add
typedef unsigned      char    UINT8;
typedef unsigned      int     UINT32;

typedef  UINT32               UINT;
typedef  UINT8                UCHAR;
typedef  char				  CHAR;
typedef  int				  INT;


typedef UCHAR *MD5_POINTER;
typedef UINT MD5_UINT4;

#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif

#define MD5_S11 7
#define MD5_S12 12
#define MD5_S13 17
#define MD5_S14 22
#define MD5_S21 5
#define MD5_S22 9
#define MD5_S23 14
#define MD5_S24 20
#define MD5_S31 4
#define MD5_S32 11
#define MD5_S33 16
#define MD5_S34 23
#define MD5_S41 6
#define MD5_S42 10
#define MD5_S43 15
#define MD5_S44 21

CHAR* MDString PROTO_LIST ((CHAR *));
CHAR* MDFile PROTO_LIST ((CHAR *));
CHAR* hmac_md5(CHAR* text, CHAR* key);
typedef struct
  {
  MD5_UINT4 state[4];   // state (ABCD)
  MD5_UINT4 count[2];   // number of bits, modulo 2^64 (lsb first)
  UCHAR buffer[64];     // input buffer
  } MD5_CTX;

static UCHAR PADDING[64] =
  {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, ac) \
  { \
  (a) += F ((b), (c), (d)) + (x) + (MD5_UINT4)(ac); \
  (a) = ROTATE_LEFT ((a), (s)); \
  (a) += (b); \
  }

#define GG(a, b, c, d, x, s, ac) \
  { \
  (a) += G ((b), (c), (d)) + (x) + (MD5_UINT4)(ac); \
  (a) = ROTATE_LEFT ((a), (s)); \
  (a) += (b); \
  }

#define HH(a, b, c, d, x, s, ac) \
  { \
  (a) += H ((b), (c), (d)) + (x) + (MD5_UINT4)(ac); \
  (a) = ROTATE_LEFT ((a), (s)); \
  (a) += (b); \
  }

#define II(a, b, c, d, x, s, ac) \
  { \
  (a) += I ((b), (c), (d)) + (x) + (MD5_UINT4)(ac); \
  (a) = ROTATE_LEFT ((a), (s)); \
  (a) += (b); \
  }

//------------------
class CMD5c
{
public:
	CMD5c();
	~CMD5c();

	void GetStrMD5(CHAR *pcResult,const CHAR *pcSourceBuff,INT iSourceBuffLen);
	void GetMD5_128(CHAR *pcResult,INT iFileID,INT iFileOff,INT iFileLen);
	void GetMD5_128(CHAR *pcResult,const CHAR *pcSourceBuff,INT iSourceBuffLen);
	bool VerifyMD5_128(const CHAR *pcVerifyBuff,INT iFileID,INT iFileOff,INT iFileLen);
	bool VerifyMD5_128(const CHAR *pcVerifyBuff,const CHAR *pcSourceBuff,INT iSourceBuffLen);

private:
	UCHAR digest[16];

	void MD5Init (MD5_CTX *context);
	void MD5Update(MD5_CTX *context, UCHAR *input,UINT inputLen);
	void MD5Transform  (MD5_UINT4 [4], UCHAR [64]) ;
	void Encode(UCHAR *, MD5_UINT4 *, UINT);
	void Decode (MD5_UINT4 *, UCHAR *, UINT);
	void MD5_memcpy(MD5_POINTER, MD5_POINTER, UINT);
	void MD5_memset(MD5_POINTER, INT, UINT);
	void MD5Final (UCHAR digest[16], MD5_CTX *context);
};


#endif//C_MD5_H
