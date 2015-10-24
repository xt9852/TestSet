
#pragma once
#include <vector>
#include <string>

typedef std::vector<std::string>  VECTOR_STR;

class CStrConver
{
public:
    CStrConver(void);
    ~CStrConver(void);

private:
    static std::string  m_cstrHex;
    static __int64 m_nHexBit[16];

public:
    static bool GBK_UNICODE(const std::string &strGBK, char *pszUNICODE, int &nWCharLength);
    static bool UNICODE_GBK(const char *pszUNICODE, std::string &strGBK);
    static std::string GBK_UTF8(const std::string &strGBK);
    static std::string UTF8_GBK(const char *utf8);
    static std::string GBK_URL(const std::string &strGBK);
    static std::string URL_GBK(const char *url);
    static void StringReplace(std::string &strBig, const std::string strsrc, const std::string strdst);

    /**
     *\fn         Tokenize(const char *srcData, const char *tokenize, VECTOR_STR &data)
     *\brief      分割字符串,例如"***|***|**"一个串，变成一个数组
     *\param[in]  srcData    原字符串。
     *\param[in]  token      分格符。
     *\param[out] data       输出数组。
     */
    static void TokenizeData(const char *srcData, const char *tokenize, VECTOR_STR &data);

#ifdef UNICODE
    static bool BSTR_CHAR(const BSTR &bstrSrc, char *pszDst);
    static bool CHAR_BSTR(const char *pszSrc, BSTR &bstrDst);
    static bool CSTRING_BSTR(const string &strSrc, BSTR &bstrDst);
    static HRESULT TChar_WChar(TCHAR *ptszInput, WCHAR **ppwszOutput);
#endif // UNICODE

    static INT64 StrToHex(const std::string &strHex);

    static std::string ltrim(std::string &s);
    static std::string rtrim(std::string &s);
    static std::string trim(std::string s);
};
