
#include "StdAfx.h"
#include "Memory.h"


CMemory::CMemory()
:m_pbyMem(NULL),
m_dwMemSize(0),
m_dwIconPos(0),
m_pShowData(NULL)
{
}

CMemory::~CMemory()
{
    if (NULL != m_pbyMem) delete[] m_pbyMem;
}

bool CMemory::Init(unsigned long dwMemSize, CShowData *pShowData)
{
    if ((0 == dwMemSize) || (NULL == pShowData)) return false;

    m_dwMemSize = dwMemSize;
    m_pShowData = pShowData;

    SetMemSize(dwMemSize);

    SetRandData();

    //-------------------------------------

    m_pbyMem[0x10001] = 0x1E;
    m_pbyMem[0x10002] = 0x34;
    m_pbyMem[0x10003] = 0x12;

    m_pbyMem[0x10004] = 0x06;
    m_pbyMem[0x10005] = 0x07;
    m_pbyMem[0x10006] = 0x08;
    m_pbyMem[0x10007] = 0x09;
    m_pbyMem[0x10008] = 0x0a;
    m_pbyMem[0x10009] = 0x0b;
    m_pbyMem[0x1000a] = 0x0c;
    m_pbyMem[0x1000b] = 0x0d;
    m_pbyMem[0x1000c] = 0x0e;
    m_pbyMem[0x1000d] = 0x0f;
    m_pbyMem[0x1000e] = 0x10;
    m_pbyMem[0x1000f] = 0x11;	// push msw
    m_pbyMem[0x10010] = 0x40;	// MSW<-AH
    m_pbyMem[0x10011] = 0x1d;	// pop msw
    m_pbyMem[0x10012] = 0x12;
    m_pbyMem[0x10013] = 0x13;
    m_pbyMem[0x10014] = 0x14;
    m_pbyMem[0x10015] = 0x15;
    m_pbyMem[0x10016] = 0x16;
    m_pbyMem[0x10017] = 0x17;
    m_pbyMem[0x10018] = 0x18;
    m_pbyMem[0x10019] = 0x19;
    m_pbyMem[0x1001a] = 0x1a;
    m_pbyMem[0x1001b] = 0x1b;
    m_pbyMem[0x1001c] = 0x1c;
    m_pbyMem[0x1001d] = 0x1d;

    m_pbyMem[0x41234] = 0x1f;

    //-------------------------------------

    return true;
}

void CMemory::LoadData(const char *pszFileName, unsigned long dwPos)
{
    if (NULL == pszFileName) return;

    FILE *pFile = fopen(pszFileName, "r");
    if (NULL != pFile)
    {
        unsigned long nFileLen = fseek(pFile, 0, SEEK_END);

        if (nFileLen > m_dwMemSize)
        {
            fread(m_pbyMem, nFileLen, 1, pFile);
        }
        else
        {
            fread(m_pbyMem, m_dwMemSize, 1, pFile);
        }

        fclose(pFile);
    }
}

void CMemory::SetRandData(void)
{
    for (DWORD i = 0; i < m_dwMemSize - 1; i++)
    {
        m_pbyMem[i] = rand() % 256;
    }
}

void CMemory::SetMemSize(unsigned long dwMemSize)
{
    if (NULL != m_pbyMem) delete[] m_pbyMem;

    m_pbyMem = new unsigned char[dwMemSize];
    ASSERT(m_pbyMem);

    m_dwMemSize = dwMemSize;
}

bool CMemory::Read(unsigned long dwPos, unsigned char &byData)
{
    if (dwPos >= m_dwMemSize) return false;

    byData = m_pbyMem[dwPos];
    return true;
}

bool CMemory::Read(unsigned long dwPos, unsigned char *pszMem, unsigned long dwToReadLen, unsigned long dwReadLen)
{
    if (dwPos >= m_dwMemSize) return false;

    if ((dwPos + dwToReadLen) >= m_dwMemSize)
    {
        unsigned long dwLen = m_dwMemSize - dwPos;
        memcpy(pszMem, &m_pbyMem[dwPos], dwLen);
        dwReadLen = dwLen;
    }
    else
    {
        memcpy(pszMem, &m_pbyMem[dwPos], dwToReadLen);
        dwReadLen = dwToReadLen;
    }

    return true;
}

bool CMemory::Write(unsigned long dwPos, unsigned char byData)
{
    if (dwPos >= m_dwMemSize) return false;

    m_pbyMem[dwPos] = byData;
    return true;
}

bool CMemory::Write(unsigned long dwPos, unsigned char *pszMem, unsigned long dwToWriteLen, unsigned long dwWriteLen)
{
    if (dwPos >= m_dwMemSize) return false;

    if ((dwPos + dwToWriteLen) >= m_dwMemSize)
    {
        DWORD dwLen = m_dwMemSize - dwPos;
        memcpy(&m_pbyMem[dwPos], pszMem, dwLen);
        dwWriteLen = dwLen;
    }
    else
    {
        memcpy(&m_pbyMem[dwPos], pszMem, dwToWriteLen);
        dwWriteLen = dwToWriteLen;
    }

    return true;
}

