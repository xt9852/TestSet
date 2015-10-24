#pragma once
#include "MicroCode.h"
#include "Memory.h"


// 8 bit
typedef union _tagREG8
{
	unsigned char byValue;
	struct { bool bCarry; bool bOver; bool bSign; bool bZero; bool bInterrupt; };

    void SetCarry(bool bSet)
    {
        if (bSet)
        {
            byValue |= 0x01;
        }
        else
        {
            byValue &= 0xFE;
        }
    };

    void SetOver(bool bSet)
    {
        if (bSet)
        {
            byValue |= 0x02;
        }
        else
        {
            byValue &= 0xFD;
        }
    };

    void SetSign(bool bSet)
    {
        if (bSet)
        {
            byValue |= 0x04;
        }
        else
        {
            byValue &= 0xFB;
        }
    };

    void SetZero(bool bSet)
    {
        if (bSet)
        {
            byValue |= 0x08;
        }
        else
        {
            byValue &= 0xF7;
        }
    };
    void SetInterrupt(bool bSet)
    {
        if (bSet)
        {
            byValue |= 0x10;
        }
        else
        {
            byValue &= 0xEF;
        }
    };

    bool GetCarry(void)     { return (byValue & 0x01)?true:false; }
    bool GetOver(void)      { return (byValue & 0x02)?true:false; }
    bool GetSign(void)      { return (byValue & 0x04)?true:false; }
    bool GetZero(void)      { return (byValue & 0x08)?true:false; }
    bool GetInterrupt(void) { return (byValue & 0x10)?true:false; }

}REG8;

// 16 bit
typedef union _tagREG16
{
	unsigned short wValue;
    struct { REG8 byLow; REG8 byHigh; };

}REG16;

// 32 bit
typedef union _tagADDR32
{
	unsigned long dwValue;
	struct { REG16 wLow; REG16 wHigh; };

}ADDR32;


class CCPU
{
public:
	CCPU(void);
	~CCPU(void);

protected:
	REG16       m_Reg[REG_COUNT];
	ADDR32      m_Bus[ABUS];		// Inside Data Bus, Outside Data Bus, Address Bus

	WORD		m_wMicroCodeAddr;	// Current MicroCode Address

	CMicroCode  m_MicroCode;		// MicroCode Set

	CMemory     m_Mem;

	unsigned long m_dwLastListPoint;

	enum {RUN, PAUSE, SINGLESTEP} m_eCurStat;

	bool		m_bSelIR;
	bool		m_bJmp;

	bool        m_bExit;
	HANDLE      m_hSingleStep;
	HANDLE      m_hWorkThread;
	static unsigned __stdcall WorkThread(LPVOID pParam);

protected:
    CShowData   *m_pShowData;
    
    void ProcessMicroCodeRegMemory(void);
    void ProcessMicroCodeReg(unsigned char byRegId, unsigned char byRegRW, unsigned char byRegTo);
    void ProcessMicroCodeRegEx(REG8 *pReg, unsigned char byRegRW, unsigned char byRegTo);
    void ProcessMicroCodeRegEx(REG16 *pReg, unsigned char byRegRW, unsigned char byRegTo);
    void ProcessMicroCodeMemory(unsigned char byMemoryTo,unsigned char byMemoryRW);   
    void ProcessMicroCodeALU(unsigned char byALUOp);
    void ProcessMicroCodeSetMSW(void);

public:
	bool Init(CShowData *pShowData, const char *pszFileName);
	void Reset(void);
	void Run(void);
	void Pause(void);
	void SingleStep(void);
	void SingleMicroCode(void);
	void ProcessSingleStep(void);
    bool SaveMicroCode(const char *pszPath, const char *pszName);

    MAP_UINT_STR* GetMapAsm(void) { return m_MicroCode.GetMapAsm(); }
    unsigned char* GetMemPtr(void) { return m_Mem.GetMemPtr(); }
};
