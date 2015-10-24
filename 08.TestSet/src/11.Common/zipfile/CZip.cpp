
#include "stdafx.h"
#include "CZip.h"
#include "zip.h"
#include "unzip.h"


CZip::CZip(void)
{
}

CZip::~CZip(void)
{
}

// pszIn       [IN]  要压缩的数据
// nInDataLen  [IN]  要压缩的数据长
// ppszOut     [OUT] 压缩后数据
// nOutDataLen [OUT] 压缩后数据长
bool CZip::Compress(char *pszIn, UINT nInDataLen, char **ppszOut, UINT &nOutDataLen)
{
    HZIP hz = CreateZip(m_szBuf, BUFF_SIZE, 0);                                 // 压缩文件,CreateZip(L"simple1.zip",0);

    if (ZR_OK == ZipAdd(hz, _T("pack"), pszIn, nInDataLen))						// 压缩
    {
        if (ZR_OK == ZipGetMemory(hz, (void**)ppszOut, (ULONG*)&nOutDataLen))	// 得到压缩后的数据
        {
            CloseZip(hz);
            return true;
        }
    }

    CloseZip(hz);
    return false;
}

// pszIn       [IN]     压缩的数据
// nInDataLen  [IN]     压缩的数据长
// ppszOut     [IN/OUT] 解压缩后的数据(缓冲区不能为空)
// nOutDataLen [IN/OUT] 解压缩后的数据长(缓冲区长)
bool CZip::UnCompress(char *pszIn, UINT nInDataLen, char *pszOut, UINT &nOutDataLen)
{
	if (NULL == pszOut) return false;

    int i = 0;
    ZIPENTRY ze = {0};
    HZIP hz = OpenZip(pszIn, nInDataLen, 0);

    if (ZR_OK == FindZipItem(hz, _T("pack"), true, &i, &ze))
    {
        if (ZR_OK == UnzipItem(hz, i, pszOut, nOutDataLen)) // 解压
        {
            nOutDataLen = ze.unc_size;
            CloseZip(hz);
            return true;
        }
    }

    CloseZip(hz);
    return false;
}
