
#include "StdAfx.h"
#include "strconver.h"
#include <comutil.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm> // find_if
#include <cctype>  // isspace
#include <atlchecked.h> // strupr_s


#if defined( WIN32 ) || defined( _WIN32 )
# include <windows.h>
#endif


std::string CStrConver::m_cstrHex("0123456789abcdef");

__int64 CStrConver::m_nHexBit[16] =
{
    0x0000000000000001,
    0x0000000000000010,
    0x0000000000000100,
    0x0000000000001000,
    0x0000000000010000,
    0x0000000000100000,
    0x0000000001000000,
    0x0000000010000000,
    0x0000000100000000,
    0x0000001000000000,
    0x0000010000000000,
    0x0000100000000000,
    0x0001000000000000,
    0x0010000000000000,
    0x0100000000000000,
    0x1000000000000000,
};


CStrConver::CStrConver(void)
{
}

CStrConver::~CStrConver(void)
{
}

// strGBK	    [IN]
// pszUNICODE	[OUT]
// nWCharLength	[OUT]
bool CStrConver::GBK_UNICODE(const std::string &strGBK, char *pszUNICODE, int &nWCharLength)
{
    if (NULL == pszUNICODE) return false;

    int len = ::MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);    // 计算字符长

    char *szUNICODE = new char[len * 2 + 2];
    memset(szUNICODE, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, (LPWSTR)szUNICODE, len);	// 转成UNICODE

    nWCharLength = len *2 + 2;
    memcpy(pszUNICODE, szUNICODE, nWCharLength);

    delete[] szUNICODE;

    return true;
}

// pszUNICODE	[IN]
// nWCharLength	[IN]
// strGBK	    [OUT]
bool CStrConver::UNICODE_GBK(const char *pszUNICODE, std::string &strGBK)
{
    if (NULL == pszUNICODE) return false;

    int len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pszUNICODE, -1, NULL, 0, NULL, NULL); // 计算字符长

    char *szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pszUNICODE, -1, szGBK, len, NULL,NULL);        // 转成GBK

    strGBK = szGBK;
    delete[] szGBK;

    return true;
}

std::string CStrConver::GBK_UTF8(const std::string &strGBK)
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);                  // 计算字符长
    unsigned short * wszUNICODE = new unsigned short[len + 1];
    memset(wszUNICODE, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0,  strGBK.c_str(), -1, (LPWSTR)wszUNICODE, len);           // 转成UNICODE

    len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUNICODE, -1, NULL, 0, NULL, NULL);    // 计算字符长
    char *szUtf8 = new char[len + 1];
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUNICODE, -1, szUtf8, len, NULL, NULL);     // 转成UTF8

    std::string strUtf8 = szUtf8;

    delete[] szUtf8;
    delete[] wszUNICODE;

    return strUtf8;
}

std::string CStrConver::UTF8_GBK(const char *utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);						// 计算字符长

    short *unicode = new short[len + 1];
    memset(unicode, 0, len * 2 + 2);

    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, (LPWSTR)unicode, len);					// 转成UNICODE

    len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)unicode, -1, NULL, 0, NULL, NULL);  // 计算字符长

    char *gbk = new char[len + 1];
    memset(gbk, 0, len + 1);

    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)unicode, -1, gbk, len, NULL,NULL);		// 转成GBK

    std::string strGBK = gbk;

    delete[] gbk;
    delete[] unicode;

    return strGBK;
}

std::string CStrConver::URL_GBK(const char *url)
{
    int index = 0;
    char hex[3] = {""};
    std::string gbk;
	std::string urlStr(url);	// 转成大写

    while (true)
    {
        index = urlStr.find("%");

        if (-1 != index)
        {
            if (0 != index)	// 前面有字符，则保存
            {
                gbk += urlStr.substr(0, index);
                urlStr.erase(0, index);
            }

            // 处理%后的字符
            hex[0] = (char)m_cstrHex.find(urlStr.at(1));
            hex[0] = (hex[0] << 4) | (char)m_cstrHex.find(urlStr.at(2));

            gbk += hex;
            urlStr.erase(0, 3);
        }
        else
        {
            if (0 != urlStr.length())
			{
                gbk += urlStr;
			}

            break;
        }
    }

    return gbk;
}


std::string CStrConver::GBK_URL(const std::string &strGBK)
{
    std::string strURL;
    char szTemp[10] = "";

    for (unsigned int i = 0; i < strGBK.length(); i++)
    {
        TCHAR a = strGBK.at( i );

        if ((a >= '0' && a <= '9') || (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '\\' || a == ':' || a == '.')
        {
            sprintf_s(szTemp, "%c", a);
            strURL += szTemp;
        }
        else
        {
            sprintf_s(szTemp, "%%%X", (BYTE)a);
            strURL += szTemp;
        }
    }

    return strURL;
}

#ifdef UNICODE
// _bstr_t	 是c++对bstr的封装
//  CComBSTR 是ATL对bstr的封装
bool CStrConver::BSTR_CHAR(const BSTR &bstrSrc, char *pszDst)
{
    if (NULL == pszDst) return false;

    const char *pstr = _com_util::ConvertBSTRToString(bstrSrc);

	strcpy(pszDst, pstr);

	delete[] pstr;

    return true;
}

bool CStrConver::CHAR_BSTR(const char *pszSrc, BSTR &bstrDst)
{
    if (NULL == pszSrc) return false;

    bstrDst = _bstr_t(pszSrc);

    return true;
}

// 用完需释放 SysFreeString(bstrDst);
bool CStrConver::CSTRING_BSTR(const std::string &strSrc, BSTR &bstrDst)
{
    bstrDst = ::SysAllocString(strSrc);
    return true;
}

// T2W,A2W
HRESULT CStrConver::TChar_WChar(TCHAR * ptszInput, WCHAR ** ppwszOutput)
{
    int cchOutput = 0;

    if (NULL == ptszInput || NULL == ppwszOutput)
    {
        return (E_INVALIDARG);
    }

    //
    // Get the size needed for the output buffer.
    //
#ifdef UNICODE
    cchOutput = wcslen(ptszInput) + 1;
#else //UNICODE
    cchOutput = MultiByteToWideChar(CP_ACP, 0, ptszInput, -1, NULL, 0);
    if (0 == cchOutput)
    {
        return (HRESULT_FROM_WIN32(GetLastError()));
    }
#endif// UNICODE

    // Allocate the buffer.
    *ppwszOutput = new WCHAR[cchOutput];
    if (NULL == *ppwszOutput)
    {
        return (E_OUTOFMEMORY);
    }

    // Convert the input string. 

#ifdef UNICODE
    wcsncpy(*ppwszOutput, ptszInput, cchOutput);
#else //UNICODE
    if (0 == MultiByteToWideChar(CP_ACP, 0, ptszInput, -1, *ppwszOutput, cchOutput))
    {
        if (*ppwszOutput)
        {
            delete *ppwszOutput;
            *ppwszOutput = NULL;
        }

        return (HRESULT_FROM_WIN32(GetLastError()));
    }        
#endif// UNICODE
    return (S_OK);
}
#endif // UNICODE

__int64 CStrConver::StrToHex(const std::string &strHex)
{
    __int64 nData = 0;
#pragma warning(disable:4996)    
    std::string strHexUp = strupr((char*)strHex.c_str());
#pragma warning(default:4996)
    int nStrLen = strHexUp.length();
    int nBegin = strHexUp.find("0X");
    nBegin =  (-1 == nBegin) ? 0 : nBegin + 2;

    if (nStrLen > 0)
    {
        int j = 0;
        for (int i = nStrLen -1; i >= nBegin; i--)
        {
            if (strHex[i] >= 'A' && strHex[i] <= 'F')
                nData += (strHex[i] - 'A' + 10) * m_nHexBit[j];
            else if (strHex[i] >= '0' && strHex[i] <= '9')
                nData += (strHex[i] - '0') * m_nHexBit[j];
            else
                return 0;
            j++;
        }
    }

    return nData;
}


//#include <istream>	// getline
#include <sstream>


/**
 *\fn         Tokenize(const char *srcData, const char *tokenize, VECTOR_STR &data)
 *\brief      分割字符串,例如"***|***|**"一个串，变成一个数组
 *\param[in]  srcData	原字符串。
 *\param[in]  token		分格符。
 *\param[out] data		输出数组。
 */
void CStrConver::TokenizeData(const char *srcData, const char *tokenize, VECTOR_STR &data)
{
    if (NULL == srcData) return;
/*
    std::stringstream src(srcData);
    std::string param;

    while (getline(src, param, tokenize))
    {
        data.push_back(param);
    }
*/
	char *content = NULL;
	char temp[MAX_PATH*10] = "";
	strcpy_s(temp, srcData);

	char *token = strtok_s(temp, tokenize, &content);

	while (token != NULL)
	{
		data.push_back(token);
		token = (char*)strtok_s(NULL, tokenize, &content);
	}
	
}

// 字符串替换
// strBig [IN] 源字符串
// strsrc [IN] 被替换的串
// strdst [IN] 替换为的串
void CStrConver::StringReplace(std::string &strBig, const std::string strsrc, const std::string strdst)
{
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();
    std::string::size_type dstlen = strdst.size();
    while((pos = strBig.find(strsrc, pos)) != std::string::npos)
    {
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}

std::string CStrConver::ltrim(std::string &s)
{ 
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace)))); 
	return s; 
} 

// trim from end 
std::string CStrConver::rtrim(std::string &s)
{ 
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end()); 
	return s; 
} 

std::string CStrConver::trim(std::string s)
{
#pragma warning(disable:4239)
	return ltrim(rtrim(s));
#pragma warning(default:4239)
} 

