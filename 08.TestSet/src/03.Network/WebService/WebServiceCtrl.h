
#ifndef TESTSET_WEBSERVICE_H_
#define TESTSET_WEBSERVICE_H_

#pragma once


/**
 *\class  WebServiceCtrl
 *\brief  该类主要WebService控制
 *\date   2012-06-25
 *\author 张海涛
 *\par    Revision History:
 */
class WebServiceCtrl
{
public:
	/**
	 *\fn         WebServiceCtrl()
	 *\brief      缺省构造函数。
     */
	WebServiceCtrl(void);

	/**
	 *\fn         WebServiceCtrl()
	 *\brief      析构函数。
     */
	~WebServiceCtrl(void);

	/**
	 *\fn         getWeatherbyCityName(const char *city)
	 *\brief      通过城市名得到天气。
	 *\param[in]  city 城市名。
	 */
	void getWeatherbyCityName(const char *city);

};

#endif // TESTSET_WEBSERVICE_H_

