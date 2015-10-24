
#include "stdafx.h"
#include "WebServiceCtrl.h"
#include "WeatherWebServiceSoap.nsmap"
#include "11.Common/StrConver.h"
#include <string>


#define WEBSERVICE_URL "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx?wsdl"


/**
 *\fn         WebServiceCtrl()
 *\brief      缺省构造函数。
 */
WebServiceCtrl::WebServiceCtrl()
{
}

/**
 *\fn         WebServiceCtrl()
 *\brief      缺省构造函数。
 */
WebServiceCtrl::~WebServiceCtrl()
{
}

/**
 *\fn         getWeatherbyCityName(const char *city)
 *\brief      通过城市名得到天气。
 *\param[in]  city 城市名。
 */
void WebServiceCtrl::getWeatherbyCityName(const char *city)
{
	_ns1__getWeatherbyCityName cityName;
	_ns1__getWeatherbyCityNameResponse cityNameResponse;

	CStrConver strConver;

	std::string cityUtf8 = strConver.GBK_UTF8(city);

	cityName.theCityName = (char*)cityUtf8.c_str();

	struct soap soap;
	soap_init(&soap);

	soap_set_mode(&soap, SOAP_C_UTFSTRING);

	int retValue = soap_call___ns1__getWeatherbyCityName(&soap, WEBSERVICE_URL, NULL, &cityName, &cityNameResponse);

	soap_cleanup(&soap);

	if (retValue == 0)
	{
		std::string info;
		for (int i = 0; i < cityNameResponse.getWeatherbyCityNameResult->__sizestring; i++)
		{
			info += strConver.UTF8_GBK(cityNameResponse.getWeatherbyCityNameResult->string[i]) + "\n";
		}

		MessageBox(NULL, info.c_str(), city, MB_OK);
	}
    else
    {
        char info[128] = "";
        _snprintf_s(info, sizeof(info)-1, "错误:%d", retValue);
        MessageBox(NULL, info, "错误", MB_OK);
    }
}