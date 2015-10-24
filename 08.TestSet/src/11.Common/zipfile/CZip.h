
#pragma once

enum { BUFF_SIZE = 204800 };

class CZip
{
public:
    CZip(void);
    ~CZip(void);

protected:
    char m_szBuf[BUFF_SIZE];

public:
    bool Compress(char *pszIn, UINT nInDataLen, char **ppszOut, UINT &nOutDataLen);
    bool UnCompress(char *pszIn, UINT nInDataLen, char *pszOut, UINT &nOutDataLen);
};

