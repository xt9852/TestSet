#pragma once


/**
 *\class  PackID
 *\brief  数据包ID
 *\date   2012-07-17
 *\author 张海涛
 *\par    Revision History:
 */
class PackID
{
public:
	/**
	 *\fn         Pool()
	 *\brief      缺省构造函数。
	 */
	PackID() {}

	/**
	 *\fn         Pool()
	 *\brief      缺省构造函数。
	 */
	~PackID() {}

private:
	unsigned int id_;
	CRITICAL_SECTION csUsed_;

public:
	unsigned int getPackId() { return ++id_; }
};
