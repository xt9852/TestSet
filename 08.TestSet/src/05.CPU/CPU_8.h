#pragma once
#include "Memory.h"


// 8 bit
typedef union _tagREG8
{
	BYTE byValue;
	struct { bool bCarry; bool bOver; bool bSign; bool bZero; bool bInterrupt; };

}REG8;


// 16 bit
typedef union _tagADDR16
{
	WORD wValue;
	struct { BYTE byLow; BYTE byHigh; };

}ADDR16;

typedef struct _tagMicroCodeAddr12
{
	WORD w12Value:12;
}ADDR12;

#pragma warning(disable:4010)


typedef union _tagMICROCODE_8
{
	_int64 n64Value;
	struct { DWORD dw32Low; DWORD dw32High; };
	struct
	{
		// 要操作的寄存器(bit0~bit4)
		// 0-NULL,1-AX,2-BX,3-CX,4-DX,5-CS,6-DS,7-SS,8-ES,9-BP,10-SP,
		// 11-IP,12-IR,13-MSW,14-TR1,15-TR2
		DWORD Reg1:5;

		// REG读或写(0读,1写)(bit5)
		DWORD Reg1RW:1;

		// REG与谁通信(0-IDBus,1-ODBus,2-ABus)(bit6~bit7)
		DWORD Reg1To:2;

		// bit8~bit12
		DWORD Reg2:5;

		// bit13
		DWORD Reg2RW:1;

		// bit14~bit15
		DWORD Reg2To:2;

		// bit16~bit20
		DWORD Reg3:5;

		// bit21
		DWORD Reg3RW:1;

		// bit22~bit23
		DWORD Reg3To:2;

		// Memory读或写(0无操作,1读,2写)(bit24~bit25)
		DWORD MemoryRW:2;       

		// ALU的操作码(bit26~bit30)
		// 0-NULL,
		// 1-ADD,2-SUB,3-INC(自加1),4-DEC(自减1),5-MUL,6-DIV,
		// 7-AND,8-OR,9-XOR,10-NOT,
		// 11-SAR,12-SAL,
		// 13-JA,14-JAE,15-JB,16-JBE,17-JE,18-JNE,19-JC,20-JNC,
		// 21-SEL_IR(使用IR做为微代码地址，只有Get1使用),
		// 22-自加2,23-自减2,24-自加3
		DWORD AluOperater:5;

		// 下一条微代码地址(bit31~bit42)
		DWORD NextAddr:12;
	};
}MICROCODE_8;

#pragma warning(default:4010)


typedef CMap<WORD, WORD, MICROCODE_8, MICROCODE_8> MAP_MICROCODE_8;

class CCPU_8
{
public:
	CCPU_8(void);
	~CCPU_8(void);

protected:
	REG8       m_AX;
	REG8       m_BX;
	REG8       m_CX;
	REG8       m_DX;

	REG8       m_CS;
	REG8       m_SS;
	REG8       m_DS;
	REG8       m_ES;

	REG8       m_BP;
	REG8       m_SP;

	REG8       m_IP;
	REG8       m_IR;

	REG8       m_MSW;
	
	REG8       m_TR1;
	REG8       m_TR2;

	REG8       m_IDBus;			// Inside Data Bus
	REG8       m_ODBus;			// Outside Data Bus
	ADDR16     m_ABus;			// Address Bus

	ADDR12      m_MCAddr;		// MicroCode Address
	MICROCODE_8 m_MicroCode;    // MicroCode    

	CMemory     m_Mem;

	MAP_MICROCODE_8   m_mapMicroCode;

	enum {RUN, PAUSE, SINGLESTEP} m_eCurStat;
	enum {AX = 1, BX, CX, DX, CS, DS, SS, ES, BP, SP, IP, IR, MSW, TR1, TR2};
	enum {ADD = 1, SUB, INC, DEL, MUL, DIV, AND, OR, XOR, NOT, SAR, SAL, 
		JA, JAE, JB, JBE, JE, JNE, JC, JNC,
		SEL_IR,
		ADD2, SUB2, ADD3};

	bool		m_bSelIR;
	bool		m_bJmp;
	
	DWORD       m_dwLastListPoint;

	bool        m_bExit;
	HANDLE      m_hSingleStep;
	HANDLE      m_hWorkThread;
	static unsigned __stdcall WorkThread(LPVOID pParam);

private:
	CListCtrl   *m_plstUnasm;
	CListCtrl   *m_plstMemory;
	CListCtrl   *m_plstRegister;

public:
	bool Init(CListCtrl *plstUnasm, CListCtrl *plstMemory, CListCtrl *plstRegister);
	void Reset(void);
	void Run(void);
	void Pause(void);
	void SingleStep(void);
	void SingleMicroCode(void);
	void ProcessSingleStep(void);

	void ProcessMicroCodeRegMemory(void);   
	void ProcessMicroCodeReg(BYTE byRegId, BYTE byRegRW, BYTE byRegTo);
	void ProcessMicroCodeRegEx(REG8 *pReg, BYTE byRegRW, BYTE byRegTo);
	void ProcessMicroCodeMemory(BYTE byMemoryRW);   
	void ProcessMicroCodeALU(BYTE byALUOp);
	void ProcessMicroCodeSetMSW(void);

	void UpdateUnasm(DWORD dwPos, DWORD dwLen);
	void UpdateMemory(DWORD dwPos, DWORD dwLen);
	void UpdateUnasmIcon(void);
	void UpdateRegList(void);
};
