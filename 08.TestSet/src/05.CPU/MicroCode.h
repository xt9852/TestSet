
#pragma once
#include <map>
#include <string>


// 寄存器
enum {AX,BX,CX,DX,CS,DS,SS,ES,BP,SP,IP,T1,AT,DRH,DRL,MSW,IR,MEM,    // 真正的寄存器
DRH_DRL,CS_IP,SS_SP,DS_T1,CS_T1,REG_COUNT}; // 主要是为了计算用

// ALU操作
enum {ALU_NULL,SEL_IR,ALU_OUTPUT_0,INC,DEC,ADD,SUB,NOT,AND,OR,XOR,SAR,SAL,JA,JAE,JB,JBE,JG,JGE,JL,JLE,JE,JNE,JC,JNC,CMP,JMP};

// 总线
enum {IBUS=0, OBUS, ABUS, ATBUS};

// 寄存器操作
enum {REG_READ=0/*读*/,  REG_NONE_READ=1/*不读*/};
enum {REG_WRITE=1/*写*/, REG_NONE_WRITE=0/*不写*/};

// 总线操作
enum {BUS_CE=0/*片选*/, BUS_NONE_CE=1/*不选取*/};
enum {BUS_TO=0/*输出到总线*/, BUS_FROM=1/*从总线读取*/};

// 内存操作
enum {MEM_READ=0/*读*/,  MEM_NONE_READ=0/*不读*/};
enum {MEM_WRITE=0/*写*/, MEM_NONE_WRITE=0/*不写*/};


typedef struct _tagMICROCODE_ITEM MICROCODE_ITEM;

typedef std::map<std::string, unsigned int>     MAP_STR_UINT;
typedef std::map<unsigned int, std::string>     MAP_UINT_STR;
typedef std::map<unsigned int, MICROCODE_ITEM*> MAP_UINT_MICROCOE;

typedef union _tagREG_OPER_ITEM
{
    struct
    {
        unsigned char byValue;
    };

    struct
    {
        unsigned char bRegRead:1;   // 寄存器读操作(0)
        unsigned char bRegWrite:1;  // 寄存器写操作(1)
        unsigned char bIBusCE:1;    // 内部总线片选
        unsigned char bIBusFrom:1;  // 内部总线,从总线读数据
        unsigned char bOBusCE:1;    // 外部总线片选
        unsigned char bOBusFrom:1;  // 外部总线,从总线读数据
        unsigned char bABusCE:1;    // 地址总线片选
        unsigned char bABusFrom:1;  // 地址总线,从总线读数据
    };

    _tagREG_OPER_ITEM()
    {
        bRegRead  = REG_NONE_READ;
        bRegWrite = REG_NONE_WRITE;
        bIBusCE   = BUS_NONE_CE;
        bIBusFrom = BUS_TO;
        bOBusCE   = BUS_NONE_CE;
        bOBusFrom = BUS_TO;
        bABusCE   = BUS_NONE_CE;
        bABusFrom = BUS_TO;
    }

}REG_OPER_ITEM;

typedef union _tagALU_OPER_ITEM
{
    struct
    {
        unsigned char byValue;
    };

    struct
    {
        unsigned char bSelIR:1;     // 选择IR寄存器
        unsigned char bCn:1;        // 74181Cn针脚
        unsigned char bM:1;         // 74181M针脚
        unsigned char bS0:1;        // 74181S0针脚
        unsigned char bS1:1;        // 74181S1针脚
        unsigned char bS2:1;        // 74181S2针脚
        unsigned char bS3:1;        // 74181S3针脚
    };

    _tagALU_OPER_ITEM()
    {
        byValue = 0;                // 只要不写入AT寄存器就可能了
    }

}ALU_OPER_ITEM;

typedef union _tagMEM_OPER_ITEM
{
    struct
    {
        unsigned char byValue;
    };

    struct
    {
        unsigned char bRead:1;      // 内存读操作
        unsigned char bWrite:1;     // 内存写操作
    };

    _tagMEM_OPER_ITEM()
    {
        bRead = MEM_NONE_READ;
        bWrite = MEM_NONE_WRITE;
    }

}MEM_OPER_ITEM;

typedef union _tagADDR_ITEM
{
    struct
    {
        unsigned char byLow;    // 微指令地址(低8位)
        unsigned char byHigh;   // 微指令地址(高8位)
    };

    struct
    {
        unsigned short wAddr:12;    // 微指令地址
    };

    _tagADDR_ITEM()
    {
        byLow = 0;
        byHigh = 0;
    }

}ADDR_ITEM;

typedef struct _tagMICROCODE_ITEM
{
    ADDR_ITEM       Addr;
    ADDR_ITEM       NextAddr;
    REG_OPER_ITEM   Reg[REG_COUNT];
    MEM_OPER_ITEM   Mem;
    ALU_OPER_ITEM   ALU;

}MICROCODE_ITEM;



class CMicroCode
{
public:
    CMicroCode(void);
    ~CMicroCode(void);

protected:
    MAP_UINT_STR m_mapAsm;  // 汇编

    MAP_STR_UINT m_mapReg;  // 寄存器(名字->编号)
    MAP_STR_UINT m_mapBus;  // 总线
    MAP_STR_UINT m_mapALU;  // ALU操作

    MAP_UINT_MICROCOE m_mapMicroCode;

    bool ParseMicroCode(const char *pszMicroCode,
        const char *pszAddr,
        const char *pszNextAddr,
        MICROCODE_ITEM &Item);

    bool ParseItem(const char *pszItem, MICROCODE_ITEM &Item);

    bool ParseRegMemOper(const std::string &strLeft, const std::string &strRight, MICROCODE_ITEM &Item);

    bool ParseALUOper(const char *pszOper, MICROCODE_ITEM &Item);

    bool SetBusOper(REG_OPER_ITEM &Reg, int nBusType, bool bLeftIsBus);

    void SetRegOper(REG_OPER_ITEM &Reg, bool bRead);

    void SetMemOper(MEM_OPER_ITEM &Mem, bool bRead);

public:
	bool Init(const char *pszFileName);
    bool LoadMicroCode(const char *pszFileName);
    bool SaveMicroCode(const char *pszPath, const char *pszName);
    MICROCODE_ITEM* GetMicroCode(WORD wAddr);
    MAP_UINT_STR* GetMapAsm(void) { return &m_mapAsm; }
};