

DWORD BinTo64(const BYTE* pInBuf, DWORD len, char* pOutBuf);
DWORD BinToURL64(const BYTE* pInBuf, DWORD len, char* pOutBuf);
DWORD BinFrom64(const char* pInBuf, DWORD len, BYTE* pOutBuf);
void printbuf(unsigned char* pBuf, int len);