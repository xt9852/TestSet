
#ifndef DESKDEPLOY_COMPUTERINFO_H_
#define DESKDEPLOY_COMPUTERINFO_H_

#pragma once
#include <vector>
#include <string>

typedef std::vector<std::string> VECTOR_STR;


/**
 *\class  ComputerInfo
 *\brief  该类主要得到本机IP和MAC地址
 *\date   2012-06-25
 *\author 张海涛
 *\par    Revision History:
 */
class ComputerInfo
{
public:
	/**
	 *\fn         ComputerInfo()
	 *\brief      缺省构造函数。
     */
	ComputerInfo();

	/**
	 *\fn         ~ComputerInfo()
	 *\brief      析构函数。
	 */
	~ComputerInfo();

	/**
	 *\fn         getIpCount()
	 *\brief      设置XP系统自启动。
	 *\return     返回本机IP地址数量。
	 */
	int getIpCount() { return ipAddr_.size(); }

	/**
	 *\fn         getIpStr()
	 *\brief      得到IP地址。
	 *\param[in]  data		序号。
	 *\return     返回本机IP地址串。
	 */
	const char * getIpStr(int id) { return ipAddr_[id].c_str(); }

	/**
	 *\fn         getMacStr()
	 *\brief      得到MAC地址。
	 *\param[in]  data		序号。
	 *\return     返回本机MAC地址串。
	 */
	const char * getMacStr(int id) { return macAddr_[id].c_str(); }

	/**
	 *\fn         GetComputerName()
	 *\brief      设置Win7系统自启动。
	 *\return     返回本机MAC地址串。
	 */
	const char * getComputerName() { return computerName_.c_str(); }

	/**
	 *\fn         Init()
	 *\brief      初使化。
	 */
	void Init();

	/**
	*\fn         GetUpSpeed()
	*\brief      得到本机网卡上行速度
	*\return     本机网卡上行速度
	*/
	int GetUpSpeed();

	/**
	*\fn         GetDownSpeed()
	*\brief      得到本机网卡下行速度
	*\return     本机网卡下行速度
	*/
	int GetDownSpeed();

private:
	/**
	*\fn         GetUpBytes()
	*\brief      得到本机网卡上行字节数
	*\return     本机网卡上行字节数
	*/
	int GetUpBytes();

	/**
	*\fn         GetDownBytes()
	*\brief      得到本机网卡下行字节数
	*\return     本机网卡下行字节数
	*/
	int GetDownBytes();

	VECTOR_STR ipAddr_;
	VECTOR_STR macAddr_;
	std::string computerName_;

	int upBytes_;
	int downBytes_;
	int upTick_;
	int downTick_;
};



#endif // DESKDEPLOY_COMPUTERINFO_H_