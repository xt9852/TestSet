
#pragma once

class CShowData;

class CMemory
{
public:
    CMemory(void);
    ~CMemory(void);

    bool Init(unsigned long dwMemSize, CShowData *pShowData);

    void LoadData(const char *szFileName, unsigned long dwPos);
    void SetRandData(void);

    void  SetMemSize(unsigned long dwMemSize);
    unsigned long GetMemSize(void) { return m_dwMemSize; }

    unsigned char* GetMemPtr(void) { return m_pbyMem; }

    bool Read(unsigned long dwPos, unsigned char &byData);
    bool Read(unsigned long dwPos, unsigned char *pszMem, unsigned long dwToReadLen, unsigned long dwReadLen);
    bool Write(unsigned long dwPos, unsigned char byData);
    bool Write(unsigned long dwPos, unsigned char *pszMem, unsigned long dwToWriteLen, unsigned long dwWriteLen);	

private:
    unsigned char *m_pbyMem;
    unsigned long m_dwMemSize;
    unsigned long m_dwIconPos;
    CShowData     *m_pShowData;
};