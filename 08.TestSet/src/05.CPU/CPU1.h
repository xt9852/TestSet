#pragma once
#include "Memory.h"

typedef union _tagREG
{
    WORD wValue;
    struct { BYTE byLow; BYTE byHigh; };
    struct { bool bCarry; bool bOver; bool bSign; bool bZero; bool bInterrupt; };

}REG16;


typedef union _tagADDR
{
    DWORD dwValue;
    struct { BYTE byLow1; BYTE byLow2; BYTE byHigh1; BYTE byHigh2;};

}ADDR32;

typedef struct _tagMicroCodeAddr
{
    WORD w12Value:12;
}ADDR12;

#pragma warning(disable:4010)


typedef union _tagMICROCODE
{
    _int64 n64Value;
    struct { DWORD dw32Low; DWORD dw32High; };
    struct
    {
		DWORD Reg1:5;           // 要操作的寄存器(bit0~bit4)
								// 0-NULL,1-AX,2-BX,3-CX,4-DX,5-CS,6-DS,7-SS,8-ES,9-BP,10-SP,
								// 11-IP,12-IR,13-MSW,14-TR1,15-TR2

        DWORD Reg1RW:1;         // REG读或写(0读,1写)                  bit5
        DWORD Reg1To:2;         // REG与谁通信(0-IDBus,1-ODBus,2-ABus) bit6~bit7

        DWORD Reg2:5;           //                                     bit8~bit12
        DWORD Reg2RW:1;         //                                     bit13
        DWORD Reg2To:2;         //                                     bit14~bit15

        DWORD Reg3:5;           //                                     bit16~bit20
        DWORD Reg3RW:1;         //                                     bit21
        DWORD Reg3To:2;         //                                     bit22~bit23

        DWORD MemoryRW:2;       // Memory读或写(0无操作,1读,2写)       bit24~bit25

        DWORD AluOperater:5;    // ALU的操作码(bit26~bit30)
								// 0-NULL,1-ADD,2-SUB,3-INC(自加1),4-DEC(自减1),5-MUL,6-DIV,
								// 7-AND,8-OR,9-XOR,10-NOT,11-SAR,12-SAL,
								// 14-JA,15-JAE,16-JB,17-JBE,22-JE,23-JNE,24-JC,25-JNC,
								// 26-SEL_IR(使用IR做为微代码，只有Get1使用),
								// 27-自加2,28-自减2,29-自加3

        DWORD NextAddr:12;      // 下一条微代码地址                     bit31~bit42
    };
}MICROCODE;

#pragma warning(default:4010)


typedef CMap<WORD, WORD, MICROCODE, MICROCODE> MAP_MICROCODE;

class CCPU
{
public:
    CCPU(void);
    ~CCPU(void);

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
    REG8       m_MSW;

    REG8       m_IR;
    REG8       m_TR;

    REG8       m_IDBus8;  // Inside Data Bus
    REG8       m_ODBus8;  // Outside Data Bus
    ADDR16     m_ABus16;  // Address Bus

    ADDR12      m_MCAddr; // MicroCode Address
    MICROCODE   m_MicroCode;    // MicroCode    

    CMemory     m_Mem;

    MAP_MICROCODE   m_mapMicroCode;

    DWORD       m_dwLastListPoint;


    enum {RUN, PAUSE, SINGLESTEP} m_eCurStat;
    enum {AX = 1, BX, CX, DX, CS, DS, SS, ES, BP, SP, IP, IR, MSW, TR1, TR2};
    enum {ADD = 1, SUB, INC, DEL, MUL, DIV, AND, OR, XOR, NOT, SAR, SAL, 
		JA, JAE, JB, JBE, JE, JNE, JC, JNC,
		SEL_IR,
		ADD2, SUB2, ADD3};

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
    void ProcessMicroCodeRegEx(REG16 *pReg, bool bHigh, BYTE byRegRW, BYTE byRegTo);
    void ProcessMicroCodeMemory(BYTE byCtrlBus, BYTE byMemoryTo,BYTE byMemoryRW);   
    bool ProcessMicroCodeALU(BYTE byALUOp);

    void UpdateUnasm(DWORD dwPos, DWORD dwLen);
    void UpdateMemory(DWORD dwPos, DWORD dwLen);
    void UpdateUnasmIcon(void);
    void UpdateRegList(void);
};
