
#ifndef TESTSET_MD5_H_
#define TESTSET_MD5_H_

#pragma once
#include <string>


typedef union
{
	BYTE	n[16];
	BYTE	b[16];
	DWORD	w[4];
}MD5, *PMD5;

/**
 *\class  CMD5
 *\brief  该类主要用于计算MD5校验值
 *\date   2012-06-25
 *\author 张海涛
 *\par    Revision History:
 */
class CMD5  
{
public:
	/**
	 *\fn         CMD5()
	 *\brief      缺省构造函数。
     */
	CMD5();

	/**
	 *\fn         ~CMD5()
	 *\brief      析构函数。
     */
	virtual ~CMD5();		// 不能删除virtual这占4个字节MD5_asm.asm预留了位置的
	
public:
	DWORD	m_nCount[2];	// 这三个变量不能移动顺序，和改变大小
	DWORD	m_nState[4];	// MD5_asm.asm会用到
	BYTE	m_pBuffer[64];

public:	
	/**
	 *\fn         Add(void *data, int len)
	 *\brief      添加要计算校验码的数据。
	 *\param[in]  data 数据。
	 *\param[in]  len  数据长。
	 */
	void Add(void *data, int len);

	/**
	 *\fn         Finish()
	 *\brief      完成。
	 */
	void Finish();

	/**
	 *\fn         Reset()
	 *\brief      重置。
	 */
	void Reset();

	/**
	 *\fn         GetHashStr(void *data, int len)
	 *\brief      计算校验码并返回校验码的字符串。
	 *\param[in]  data 数据。
	 *\param[in]  len  数据长。
	 *\return     校验码的字符串
	 */
	std::string	getHashStr(void *data, int len);

	/**
	 *\fn         HashToString(const MD5* hash)
	 *\brief      得到校验码的字符串。
	 *\param[in]  hash 校验码。
	 *\return     校验码的字符串
	 */
	std::string	HashToString(const MD5* hash);

    /**
     *\fn         HashToChar(const MD5* hash, LPTSTR md5, int md5BuffSize)
     *\brief      得到校验码的字符串。
     *\param[in]  hash          校验码。
     *\param[out] md5           校验码串。
     *\param[in]  md5BuffSize   校验码串缓冲区大小。
     *\return     校验码的字符串
     */
    bool HashToChar(const MD5* hash, LPTSTR md5, int md5BuffSize);
	
	/**
	 *\fn         getHash(void *data, int len)
	 *\brief      得校验码。
	 *\param[in]  data 数据。
	 *\param[in]  len  数据长。
	 *\return     校验码
	 */
	MD5* getHash(void *data, int len);

	/**
	 *\fn         getHash()
	 *\brief      得校验码。
	 *\return     校验码
	 */
	MD5* getHash() { return (MD5*)m_nState; }

    /**
     *\fn        std::string getHashStr()
     *\brief     得到校验码的字符串
     *\return    std::string 0成功,其它失败
     */
    std::string	getHashStr() { return HashToString(getHash()); }
};

#endif // TESTSET_MD5_H_