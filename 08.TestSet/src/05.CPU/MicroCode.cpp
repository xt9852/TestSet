
#include "StdAfx.h"
#include "MicroCode.h"
#include "11.Common\StrConver.h"


CMicroCode::CMicroCode()
{
}

CMicroCode::~CMicroCode()
{
    for (MAP_UINT_MICROCOE::iterator iter = m_mapMicroCode.begin(); 
        iter !=  m_mapMicroCode.end(); ++iter)
    {
        delete iter->second;
    }

    m_mapMicroCode.empty();
}

bool CMicroCode::Init(const char *pszFileName)
{
    m_mapReg["AX"]       = AX;
    m_mapReg["BX"]       = BX;
    m_mapReg["CX"]       = CX;
    m_mapReg["DX"]       = DX;
    m_mapReg["CS"]       = CS;
    m_mapReg["DS"]       = DS;
    m_mapReg["SS"]       = SS;
    m_mapReg["ES"]       = ES;
    m_mapReg["BP"]       = BP;
    m_mapReg["SP"]       = SP;
    m_mapReg["IP"]       = IP;
    m_mapReg["IR"]       = IR;
    m_mapReg["T1"]       = T1;
    m_mapReg["AT"]       = AT;
    m_mapReg["DRH"]      = DRH;
    m_mapReg["DRL"]      = DRL;
    m_mapReg["MSW"]      = MSW;
    m_mapReg["MEM"]      = MEM;
    m_mapReg["CS:IP"]    = CS_IP;
    m_mapReg["SS:SP"]    = SS_SP;
    m_mapReg["DS:T1"]    = DS_T1;
    m_mapReg["CS:T1"]    = CS_T1;
    m_mapReg["DRH_DRL"]  = DRH_DRL;

    m_mapBus["IBus"]     = IBUS;
    m_mapBus["OBus"]     = OBUS;
    m_mapBus["ABus"]     = ABUS;
    m_mapBus["ATBus"]    = ATBUS;

    m_mapALU[""]         = ALU_NULL;
    m_mapALU["OUTPUT_0"] = ALU_OUTPUT_0;
    m_mapALU["++"]       = INC;
    m_mapALU["--"]       = DEC;
    m_mapALU["ADD"]      = ADD;
    m_mapALU["SUB"]      = SUB;
    m_mapALU["NOT"]      = NOT;
    m_mapALU["AND"]      = AND;
    m_mapALU["OR"]       = OR;
    m_mapALU["XOR"]      = XOR;
    m_mapALU["SAR"]      = SAR;
    m_mapALU["SAL"]      = SAL;
    m_mapALU["JA"]       = JA;
    m_mapALU["JAE"]      = JAE;
    m_mapALU["JB"]       = JB;
    m_mapALU["JBE"]      = JBE;
    m_mapALU["JG"]       = JG;
    m_mapALU["JGE"]      = JGE;
    m_mapALU["JL"]       = JL;
    m_mapALU["JLE"]      = JLE;
    m_mapALU["JE"]       = JE;
    m_mapALU["JNE"]      = JNE;
    m_mapALU["JC"]       = JC;
    m_mapALU["JNC"]      = JNC;
    m_mapALU["CMP"]      = CMP;
    m_mapALU["JMP"]      = JMP;
    m_mapALU["SEL_IR"]   = SEL_IR;

    m_mapAsm[0x00] = "NOP";
    m_mapAsm[0x01] = "IN";
    m_mapAsm[0x02] = "OUT";
    m_mapAsm[0x03] = "LAXF";
    m_mapAsm[0x04] = "SAXF";
    m_mapAsm[0x05] = "CALL ES:";
    m_mapAsm[0x06] = "RET";

    m_mapAsm[0x07] = "PUSH AX";
    m_mapAsm[0x08] = "PUSH BX";
    m_mapAsm[0x09] = "PUSH CX";
    m_mapAsm[0x0A] = "PUSH DX";
    m_mapAsm[0x0B] = "PUSH CS";
    m_mapAsm[0x0C] = "PUSH DS";
    m_mapAsm[0x0D] = "PUSH SS";
    m_mapAsm[0x0E] = "PUSH ES";
    m_mapAsm[0x0F] = "PUSH BP";
    m_mapAsm[0x10] = "PUSH SP";
    m_mapAsm[0x11] = "PUSH IP";
    m_mapAsm[0x12] = "PUSH MSW";

    m_mapAsm[0x13] = "POP AX";
    m_mapAsm[0x14] = "POP BX";
    m_mapAsm[0x15] = "POP CX";
    m_mapAsm[0x16] = "POP DX";
    m_mapAsm[0x17] = "POP CS";
    m_mapAsm[0x18] = "POP DS";
    m_mapAsm[0x19] = "POP SS";
    m_mapAsm[0x1A] = "POP ES";
    m_mapAsm[0x1B] = "POP BP";
    m_mapAsm[0x1C] = "POP SP";
    m_mapAsm[0x1D] = "POP IP";
    m_mapAsm[0x1E] = "POP MSW";

    m_mapAsm[0x1F] = "CMP AX,BX";
    m_mapAsm[0x20] = "CMP AX,CX";
    m_mapAsm[0x21] = "CMP AX,DX";
    m_mapAsm[0x22] = "CMP BX,AX";
    m_mapAsm[0x23] = "CMP BX,CX";
    m_mapAsm[0x24] = "CMP BX,DX";
    m_mapAsm[0x25] = "CMP CX,AX";
    m_mapAsm[0x26] = "CMP CX,BX";
    m_mapAsm[0x27] = "CMP CX,DX";
    m_mapAsm[0x28] = "CMP DX,AX";
    m_mapAsm[0x29] = "CMP DX,BX";
    m_mapAsm[0x2A] = "CMP DX,CX";

    m_mapAsm[0x2B] = "JMP ES:";
    m_mapAsm[0x2C] = "JA  ES:";
    m_mapAsm[0x2D] = "JAE ES:";
    m_mapAsm[0x2E] = "JB  ES:";
    m_mapAsm[0x2F] = "JBE ES:";
    m_mapAsm[0x30] = "JG  ES:";
    m_mapAsm[0x31] = "JGE ES:";
    m_mapAsm[0x32] = "JL  ES:";
    m_mapAsm[0x33] = "JLE ES:";
    m_mapAsm[0x34] = "JE  ES:";
    m_mapAsm[0x35] = "JNE ES:";
    m_mapAsm[0x36] = "JC  ES:";
    m_mapAsm[0x37] = "JNC ES:";

    m_mapAsm[0x38] = "MOV AX,BX";
    m_mapAsm[0x39] = "MOV AX,CX";
    m_mapAsm[0x3A] = "MOV AX,DX";
    m_mapAsm[0x3B] = "MOV BX,AX";
    m_mapAsm[0x3C] = "MOV BX,CX";
    m_mapAsm[0x3D] = "MOV BX,DX";
    m_mapAsm[0x3E] = "MOV CX,AX";
    m_mapAsm[0x3F] = "MOV CX,BX";
    m_mapAsm[0x40] = "MOV CX,DX";
    m_mapAsm[0x41] = "MOV DX,AX";
    m_mapAsm[0x42] = "MOV DX,BX";
    m_mapAsm[0x43] = "MOV DX,CX";
    m_mapAsm[0x44] = "MOV CS,DS";
    m_mapAsm[0x45] = "MOV CS,SS";
    m_mapAsm[0x46] = "MOV CS,ES";
    m_mapAsm[0x47] = "MOV DS,CS";
    m_mapAsm[0x48] = "MOV DS,SS";
    m_mapAsm[0x49] = "MOV DS,ES";
    m_mapAsm[0x4A] = "MOV SS,CS";
    m_mapAsm[0x4B] = "MOV SS,DS";
    m_mapAsm[0x4C] = "MOV SS,ES";
    m_mapAsm[0x4D] = "MOV ES,CS";
    m_mapAsm[0x4E] = "MOV ES,DS";
    m_mapAsm[0x4F] = "MOV ES,SS";
    m_mapAsm[0x50] = "MOV BP,SP";
    m_mapAsm[0x51] = "MOV SP,BP";
    m_mapAsm[0x52] = "MOV AX,CS";
    m_mapAsm[0x53] = "MOV AX,DS";
    m_mapAsm[0x54] = "MOV AX,SS";
    m_mapAsm[0x55] = "MOV AX,ES";
    m_mapAsm[0x56] = "MOV AX,BP";
    m_mapAsm[0x57] = "MOV AX,SP";
    m_mapAsm[0x58] = "MOV BX,CS";
    m_mapAsm[0x59] = "MOV BX,DS";
    m_mapAsm[0x5A] = "MOV BX,SS";
    m_mapAsm[0x5B] = "MOV BX,ES";
    m_mapAsm[0x5C] = "MOV BX,BP";
    m_mapAsm[0x5D] = "MOV BX,SP";
    m_mapAsm[0x5E] = "MOV CS,AX";
    m_mapAsm[0x5F] = "MOV DS,AX";
    m_mapAsm[0x60] = "MOV SS,AX";
    m_mapAsm[0x61] = "MOV ES,AX";
    m_mapAsm[0x62] = "MOV BP,AX";
    m_mapAsm[0x63] = "MOV SP,AX";
    m_mapAsm[0x64] = "MOV CS,BX";
    m_mapAsm[0x65] = "MOV DS,BX";
    m_mapAsm[0x66] = "MOV SS,BX";
    m_mapAsm[0x67] = "MOV ES,BX";
    m_mapAsm[0x68] = "MOV BP,BX";
    m_mapAsm[0x69] = "MOV SP,BX";
    m_mapAsm[0x6A] = "MOV AX,DS:[BX]";
    m_mapAsm[0x6B] = "MOV AX,DS:[CX]";
    m_mapAsm[0x6C] = "MOV AX,DS:[DX]";
    m_mapAsm[0x6D] = "MOV BX,DS:[AX]";
    m_mapAsm[0x6E] = "MOV BX,DS:[CX]";
    m_mapAsm[0x6F] = "MOV BX,DS:[DX]";
    m_mapAsm[0x70] = "MOV CX,DS:[AX]";
    m_mapAsm[0x71] = "MOV CX,DS:[BX]";
    m_mapAsm[0x72] = "MOV CX,DS:[DX]";
    m_mapAsm[0x73] = "MOV DX,DS:[AX]";
    m_mapAsm[0x74] = "MOV DX,DS:[BX]";
    m_mapAsm[0x75] = "MOV DX,DS:[CX]";
    m_mapAsm[0x76] = "MOV DS:[AX],BX";
    m_mapAsm[0x77] = "MOV DS:[AX],CX";
    m_mapAsm[0x78] = "MOV DS:[AX],DX";
    m_mapAsm[0x79] = "MOV DS:[BX],AX";
    m_mapAsm[0x7A] = "MOV DS:[BX],CX";
    m_mapAsm[0x7B] = "MOV DS:[BX],DX";
    m_mapAsm[0x7C] = "MOV DS:[CX],AX";
    m_mapAsm[0x7D] = "MOV DS:[CX],BX";
    m_mapAsm[0x7E] = "MOV DS:[CX],DX";
    m_mapAsm[0x7F] = "MOV DS:[DX],AX";
    m_mapAsm[0x80] = "MOV DS:[DX],BX";
    m_mapAsm[0x81] = "MOV DS:[DX],CX";
    m_mapAsm[0x82] = "MOV AX,";
    m_mapAsm[0x83] = "MOV BX,";
    m_mapAsm[0x84] = "MOV CX,";
    m_mapAsm[0x85] = "MOV DX,";
    m_mapAsm[0x86] = "AND AX,BX";
    m_mapAsm[0x87] = "AND AX,CX";
    m_mapAsm[0x88] = "AND AX,DX";
    m_mapAsm[0x89] = "AND BX,AX";
    m_mapAsm[0x8A] = "AND BX,CX";
    m_mapAsm[0x8B] = "AND BX,DX";
    m_mapAsm[0x8C] = "AND CX,AX";
    m_mapAsm[0x8D] = "AND CX,BX";
    m_mapAsm[0x8E] = "AND CX,DX";
    m_mapAsm[0x8F] = "AND DX,AX";
    m_mapAsm[0x90] = "AND DX,BX";
    m_mapAsm[0x91] = "AND DX,CX";
    m_mapAsm[0x92] = "OR AX,BX";
    m_mapAsm[0x93] = "OR AX,CX";
    m_mapAsm[0x94] = "OR AX,DX";
    m_mapAsm[0x95] = "OR BX,AX";
    m_mapAsm[0x96] = "OR BX,CX";
    m_mapAsm[0x97] = "OR BX,DX";
    m_mapAsm[0x98] = "OR CX,AX";
    m_mapAsm[0x99] = "OR CX,BX";
    m_mapAsm[0x9A] = "OR CX,DX";
    m_mapAsm[0x9B] = "OR DX,AX";
    m_mapAsm[0x9C] = "OR DX,BX";
    m_mapAsm[0x9D] = "OR DX,CX";
    m_mapAsm[0x9E] = "XOR AX,AX";
    m_mapAsm[0x9F] = "XOR AX,BX";
    m_mapAsm[0xA0] = "XOR AX,CX";
    m_mapAsm[0xA1] = "XOR AX,DX";
    m_mapAsm[0xA2] = "XOR BX,AX";
    m_mapAsm[0xA3] = "XOR BX,BX";
    m_mapAsm[0xA4] = "XOR BX,CX";
    m_mapAsm[0xA5] = "XOR BX,DX";
    m_mapAsm[0xA6] = "XOR CX,AX";
    m_mapAsm[0xA7] = "XOR CX,BX";
    m_mapAsm[0xA8] = "XOR CX,CX";
    m_mapAsm[0xA9] = "XOR CX,DX";
    m_mapAsm[0xAA] = "XOR DX,AX";
    m_mapAsm[0xAB] = "XOR DX,BX";
    m_mapAsm[0xAC] = "XOR DX,CX";
    m_mapAsm[0xAD] = "XOR DX,DX";
    m_mapAsm[0xAE] = "NOT AX";
    m_mapAsm[0xAF] = "NOT BX";
    m_mapAsm[0xB0] = "NOT CX";
    m_mapAsm[0xB1] = "NOT DX";
    m_mapAsm[0xB2] = "SAL AX,CX";
    m_mapAsm[0xB3] = "SAL BX,CX";
    m_mapAsm[0xB4] = "SAL DX,CX";
    m_mapAsm[0xB5] = "SAR AX,CX";
    m_mapAsm[0xB6] = "SAR BX,CX";
    m_mapAsm[0xB7] = "SAR DX,CX";
    m_mapAsm[0xB8] = "ADD AX,AX";
    m_mapAsm[0xB9] = "ADD AX,BX";
    m_mapAsm[0xBA] = "ADD AX,CX";
    m_mapAsm[0xBB] = "ADD AX,DX";
    m_mapAsm[0xBC] = "ADD BX,AX";
    m_mapAsm[0xBD] = "ADD BX,BX";
    m_mapAsm[0xBE] = "ADD BX,CX";
    m_mapAsm[0xBF] = "ADD BX,DX";
    m_mapAsm[0xC0] = "ADD CX,AX";
    m_mapAsm[0xC1] = "ADD CX,BX";
    m_mapAsm[0xC2] = "ADD CX,CX";
    m_mapAsm[0xC3] = "ADD CX,DX";
    m_mapAsm[0xC4] = "ADD DX,AX";
    m_mapAsm[0xC5] = "ADD DX,BX";
    m_mapAsm[0xC6] = "ADD DX,CX";
    m_mapAsm[0xC7] = "ADD DX,DX";
    m_mapAsm[0xC8] = "ADD BP,AX";
    m_mapAsm[0xC9] = "ADD BP,BX";
    m_mapAsm[0xCA] = "ADD BP,CX";
    m_mapAsm[0xCB] = "ADD BP,DX";
    m_mapAsm[0xCC] = "ADD SP,AX";
    m_mapAsm[0xCD] = "ADD SP,BX";
    m_mapAsm[0xCE] = "ADD SP,CX";
    m_mapAsm[0xCF] = "ADD SP,DX";
    m_mapAsm[0xD0] = "SUB AX,AX";
    m_mapAsm[0xD1] = "SUB AX,BX";
    m_mapAsm[0xD2] = "SUB AX,CX";
    m_mapAsm[0xD3] = "SUB AX,DX";
    m_mapAsm[0xD4] = "SUB BX,AX";
    m_mapAsm[0xD5] = "SUB BX,BX";
    m_mapAsm[0xD6] = "SUB BX,CX";
    m_mapAsm[0xD7] = "SUB BX,DX";
    m_mapAsm[0xD8] = "SUB CX,AX";
    m_mapAsm[0xD9] = "SUB CX,BX";
    m_mapAsm[0xDA] = "SUB CX,CX";
    m_mapAsm[0xDB] = "SUB CX,DX";
    m_mapAsm[0xDC] = "SUB DX,AX";
    m_mapAsm[0xDD] = "SUB DX,BX";
    m_mapAsm[0xDE] = "SUB DX,CX";
    m_mapAsm[0xDF] = "SUB DX,DX";
    m_mapAsm[0xE0] = "SUB BP,AX";
    m_mapAsm[0xE1] = "SUB BP,BX";
    m_mapAsm[0xE2] = "SUB BP,CX";
    m_mapAsm[0xE3] = "SUB BP,DX";
    m_mapAsm[0xE4] = "SUB SP,AX";
    m_mapAsm[0xE5] = "SUB SP,BX";
    m_mapAsm[0xE6] = "SUB SP,CX";
    m_mapAsm[0xE7] = "SUB SP,DX";
    m_mapAsm[0xE8] = "NOP";
    m_mapAsm[0xE9] = "NOP";
    m_mapAsm[0xEA] = "NOP";
    m_mapAsm[0xEB] = "NOP";
    m_mapAsm[0xEC] = "NOP";
    m_mapAsm[0xED] = "NOP";
    m_mapAsm[0xEE] = "NOP";
    m_mapAsm[0xEF] = "NOP";
    m_mapAsm[0xF0] = "NOP";
    m_mapAsm[0xF1] = "NOP";
    m_mapAsm[0xF2] = "NOP";
    m_mapAsm[0xF3] = "NOP";
    m_mapAsm[0xF4] = "NOP";
    m_mapAsm[0xF5] = "NOP";
    m_mapAsm[0xF6] = "NOP";
    m_mapAsm[0xF7] = "NOP";
    m_mapAsm[0xF8] = "NOP";
    m_mapAsm[0xF9] = "NOP";
    m_mapAsm[0xFA] = "NOP";
    m_mapAsm[0xFB] = "NOP";
    m_mapAsm[0xFC] = "NOP";
    m_mapAsm[0xFD] = "NOP";
    m_mapAsm[0xFE] = "NOP";
    m_mapAsm[0xFF] = "NOP";

    if (NULL == pszFileName) return false;

    return LoadMicroCode(pszFileName);
}

// 得到微代码
MICROCODE_ITEM* CMicroCode::GetMicroCode(WORD wAddr)
{
	if (wAddr >= 0x200) return 0;

	return m_mapMicroCode[wAddr];
}

bool CMicroCode::SaveMicroCode(const char *pszPath, const char *pszName)
{
    char szFileName[200] = "";
    sprintf(szFileName, "%s\\%s.bin", pszPath, pszName);

    FILE *pFile = fopen(szFileName, "wb");

    if (NULL == pFile) return false;

    bool bAdd = false;
    bool bExit = false;
    unsigned char szZero = 0;
    MAP_STR_UINT::iterator iter1 = m_mapReg.find(pszName);

    unsigned int nCount = m_mapMicroCode.size();
    for (unsigned int i = 0; i < 0x2000; i++)
    {
        if (0x1FFE == i)
        {
            i = 0xFFE;
            bAdd = true;
        }
        else if (0x1FFF == i)
        {
            i = 0xFFF;
            bExit = true;
        }

        MICROCODE_ITEM *pItem = m_mapMicroCode[i];

        if (NULL != pItem)
        {
            if (iter1 != m_mapReg.end())
            {
                fwrite(&(pItem->Reg[iter1->second]), 1, 1, pFile);
            }
            else if (0 == strcmp("NextAddrLow", pszName))
            {
                fwrite(&(pItem->NextAddr.byLow), 1, 1, pFile);
            }
            else if (0 == strcmp("NextAddrHigh", pszName))
            {
                fwrite(&(pItem->NextAddr.byHigh), 1, 1, pFile);
                long nPos = ftell(pFile);
                TRACE("i=%d Pos=%d\n", i, nPos);
            }
            else if (0 == strcmp("Mem", pszName))
            {
                fwrite(&(pItem->Mem.byValue), 1, 1, pFile);
            }
            else if (0 == strcmp("ALU", pszName))
            {
                fwrite(&(pItem->ALU.byValue), 1, 1, pFile);
            }
            else
            {
                TRACE("Don't find %s\n", pszName);
                fwrite(&szZero, 1, 1, pFile);
            }
        }
        else
        {
            fwrite(&szZero, 1, 1, pFile);
        }

        if ((0xFFE == i) && (bAdd))
        {
            i = 0x1FFE;
        }
        else if (bExit)
        {
            break;
        }
    }

    fclose(pFile);
    return true;
}

bool CMicroCode::LoadMicroCode(const char *pszFileName)
{
    FILE *pFile = fopen(pszFileName, "rb");

    if (NULL == pFile) return false;

    char szAddr[10] = "";
    char szNextAddr[10] = "";
    char szMicroCode[200] = "";

    while(-1 != fscanf(pFile, "%s\t%s\t%s", szMicroCode, szAddr, szNextAddr))
    {
        TRACE("%s\t%s\t%s\n", szMicroCode, szAddr, szNextAddr);
        
        MICROCODE_ITEM *pItem = new MICROCODE_ITEM;

        if (ParseMicroCode(szMicroCode, szAddr, szNextAddr, *pItem))
        {
            m_mapMicroCode[pItem->Addr.wAddr] = pItem;
        }
        else
        {
            delete pItem;
        }
    }

    fclose(pFile);
    return true;
}

// 解析微代码
// pszMicroCode [IN]  微代码字符串
// pszAddr      [IN]  代码地址
// pszNextAddr  [IN]  下一条微代码的地址
// Item         [OUT] 微代码数据
bool CMicroCode::ParseMicroCode(const char *pszMicroCode, 
                                const char *pszAddr, 
                                const char *pszNextAddr,
                                MICROCODE_ITEM &Item)
{

    if ((NULL == pszMicroCode) || (NULL == pszAddr) || (NULL == pszNextAddr))
    {
        return false;
    }
    
    if (0 == strcmp("0xFFF", pszAddr))
    {
        TRACE("ALU:%s\n", pszAddr);
    }

    Item.Addr.wAddr = CStrConver::StrToHex(pszAddr);
    Item.NextAddr.wAddr = CStrConver::StrToHex(pszNextAddr);

    VECTOR_STR vecParam;
    CStrConver::TokenizeData(pszMicroCode, ",", vecParam);

    for (unsigned int i = 0; i < vecParam.size(); i++)
    {
        ParseItem(vecParam[i].c_str(), Item);
    }

    return true;
}

// 解析微代码的子代码
// pszItem [IN]  子微代码
// Item    [OUT] 微代码数据
bool CMicroCode::ParseItem(const char *pszItem, MICROCODE_ITEM &Item)
{
    if (NULL == pszItem) return false;

    TRACE("%s ", pszItem);

    std::string strItem(pszItem);

    int nIndex = strItem.find("<-");
    if (-1 != nIndex)   // 有总线操作
    {
        std::string strLeft = strItem.substr(0, nIndex);
        std::string strRight = strItem.substr(nIndex+2);
        
        return ParseRegMemOper(strLeft, strRight, Item);
    }
    else
    {
        return ParseALUOper(pszItem, Item);
    }
}

// 总线操作
// strLeft  [IN]  左操作符
// strRight [IN]  右操作符
// Item     [OUT] 微代码数据
bool CMicroCode::ParseRegMemOper(const std::string &strLeft, const std::string &strRight, MICROCODE_ITEM &Item)
{
    MAP_STR_UINT::iterator iter1 = m_mapReg.find(strLeft);
    MAP_STR_UINT::iterator iter2 = m_mapBus.find(strRight);
    MAP_STR_UINT::iterator iter3 = m_mapReg.find(strRight);
    MAP_STR_UINT::iterator iter4 = m_mapBus.find(strLeft);

    bool bLeftIsBus = true;
    std::string strBus;
    std::string strReg;

    if ((iter1 != m_mapReg.end()) && (iter2 != m_mapBus.end()))
    {
        bLeftIsBus = false;
        strReg = strLeft;
        strBus = strRight;
    }
    else if ((iter3 != m_mapReg.end()) && (iter4 != m_mapBus.end()))
    {
        strReg = strRight;
        strBus = strLeft;
    }
    else
    {
        LOG(INFO) << "总线操作" << strLeft << strRight << "位置或名称不正确";
        return false;
    }

    int nBusType = m_mapBus[strBus];
    int nRegType = m_mapReg[strReg];

    TRACE("Reg:%d Bus:%d\n", nRegType, nBusType);

    switch (nRegType)
    {
    case DRH_DRL:
        {
            SetRegOper(Item.Reg[DRH], bLeftIsBus);
            SetRegOper(Item.Reg[DRL], bLeftIsBus);
            SetBusOper(Item.Reg[DRH], nBusType, bLeftIsBus);
            SetBusOper(Item.Reg[DRL], nBusType, bLeftIsBus);
            break;
        }
    case CS_IP:
        {
            SetRegOper(Item.Reg[CS], bLeftIsBus);
            SetRegOper(Item.Reg[IP], bLeftIsBus);
            SetBusOper(Item.Reg[CS], nBusType, bLeftIsBus);
            SetBusOper(Item.Reg[IP], nBusType, bLeftIsBus);
            break;
        }
    case SS_SP:
        {
            SetRegOper(Item.Reg[SS], bLeftIsBus);
            SetRegOper(Item.Reg[SP], bLeftIsBus);
            SetBusOper(Item.Reg[SS], nBusType, bLeftIsBus);
            SetBusOper(Item.Reg[SP], nBusType, bLeftIsBus);
            break;
        }
    case DS_T1:
        {
            SetRegOper(Item.Reg[DS], bLeftIsBus);
            SetRegOper(Item.Reg[T1], bLeftIsBus);
            SetBusOper(Item.Reg[DS], nBusType, bLeftIsBus);
            SetBusOper(Item.Reg[T1], nBusType, bLeftIsBus);
            break;
        }
    case CS_T1:
        {
            SetRegOper(Item.Reg[CS], bLeftIsBus);
            SetRegOper(Item.Reg[T1], bLeftIsBus);
            SetBusOper(Item.Reg[CS], nBusType, bLeftIsBus);
            SetBusOper(Item.Reg[T1], nBusType, bLeftIsBus);
            break;
        }
    default:
        {
            if (MEM == nRegType)    // 是内存MEM时
            {
                SetMemOper(Item.Mem, bLeftIsBus);
            }
            else
            {
                SetRegOper(Item.Reg[nRegType], bLeftIsBus);
            }

            SetBusOper(Item.Reg[nRegType], nBusType, bLeftIsBus);
            break;
        }
    }

    return true;
}

// 设备总线操作
// Reg        [IN] 寄存器
// nBusType   [IN] 总线类型
// bLeftIsBus [IN] 左测是总线
bool CMicroCode::SetBusOper(REG_OPER_ITEM &Reg, int nBusType, bool bLeftIsBus)
{
    switch (nBusType)
    {
    case IBUS:
        {
            Reg.bIBusCE = BUS_CE;
            Reg.bIBusFrom = bLeftIsBus ? BUS_TO : BUS_FROM;
            break;
        }
    case OBUS:
        {
            Reg.bOBusCE = BUS_CE;
            Reg.bOBusFrom = bLeftIsBus ? BUS_TO : BUS_FROM;
            break;
        }
    case ABUS:
    case ATBUS:
        {
            Reg.bABusCE = BUS_CE;
            Reg.bABusFrom = bLeftIsBus ? BUS_TO : BUS_FROM;
            break;
        }
    default:
        {
            TRACE("总线类型错误 %d\n", nBusType);
            return false;
        }
    }

    return true;
}

// 寄存器总线操作
// Reg   [IN] 寄存器
// bRead [IN] 读操作
void CMicroCode::SetRegOper(REG_OPER_ITEM &Reg, bool bRead)
{
    if (bRead)
    {
        Reg.bRegRead = REG_READ;
    }
    else
    {
        Reg.bRegWrite = REG_WRITE;
    }
}

// 内存操作
// Mem   [IN] 内存
// bRead [IN] 读操作
void CMicroCode::SetMemOper(MEM_OPER_ITEM &Mem, bool bRead)
{
    if (bRead)
    {
        Mem.bRead = MEM_READ;
    }
    else
    {
        Mem.bWrite = MEM_WRITE;
    }
}

// ALU操作
// pszOper [IN] 操作符
// Item    [OUT] 微代码数据
// ALU操作,INC自加1,DEC自减1
// 功能     输入S3 S2 S1 S0 M Cn
// ~A(A非)      L  L  L  L  H *
// A&B(A与B)    H  L  H  H  H *
// A|B(A或B)    H  H  H  L  H *
// A^B(A异或B)  L  H  H  L  H *
// A++          L  L  L  L  L L
// A--          H  H  H  H  L H
// A+B(A加B)    H  L  L  H  L L(A+B+1) H(A+B)
// A-B(A减B)    L  H  H  L  L L(A-B-1) H(A-B)
// 全0          L  L  H  H  H *
bool CMicroCode::ParseALUOper(const char *pszOper, MICROCODE_ITEM &Item)
{
    MAP_STR_UINT::iterator iter1 = m_mapALU.find(pszOper);

    if (iter1 == m_mapALU.end())
    {
        LOG(INFO) << "ALU操作名称不正确" << pszOper;
        return false;
    }
    
    TRACE("ALU:%d\n", iter1->second);

    switch (iter1->second)
    {
    case JMP:
        {
            break;
        }
    case SEL_IR:
        {
            Item.ALU.bSelIR = 1;
            break;
        }
    case ALU_OUTPUT_0:
        {
            Item.ALU.bS3 = 0;
            Item.ALU.bS2 = 0;
            Item.ALU.bS1 = 1;
            Item.ALU.bS0 = 1;
            Item.ALU.bM  = 0;
            Item.ALU.bCn = 0;
            break;
        }
    case INC:
        {
            Item.ALU.bS3 = 0;
            Item.ALU.bS2 = 0;
            Item.ALU.bS1 = 0;
            Item.ALU.bS0 = 0;
            Item.ALU.bM  = 0;
            Item.ALU.bCn = 0;
            break;
        }
    case DEC:
        {
            Item.ALU.bS3 = 1;
            Item.ALU.bS2 = 1;
            Item.ALU.bS1 = 1;
            Item.ALU.bS0 = 1;
            Item.ALU.bM  = 0;
            Item.ALU.bCn = 1;
            break;
        }
    case ADD:
        {
            Item.ALU.bS3 = 1;
            Item.ALU.bS2 = 0;
            Item.ALU.bS1 = 0;
            Item.ALU.bS0 = 1;
            Item.ALU.bM  = 0;
            Item.ALU.bCn = 1;
            break;
        }
    case SUB:
        {
            Item.ALU.bS3 = 1;
            Item.ALU.bS2 = 1;
            Item.ALU.bS1 = 1;
            Item.ALU.bS0 = 1;
            Item.ALU.bM  = 0;
            Item.ALU.bCn = 1;
            break;
        }
    case NOT:
        {
            Item.ALU.bS3 = 0;
            Item.ALU.bS2 = 0;
            Item.ALU.bS1 = 0;
            Item.ALU.bS0 = 0;
            Item.ALU.bM  = 1;
            Item.ALU.bCn = 0;
            break;
        }
    case AND:
        {
            Item.ALU.bS3 = 1;
            Item.ALU.bS2 = 0;
            Item.ALU.bS1 = 1;
            Item.ALU.bS0 = 1;
            Item.ALU.bM  = 1;
            Item.ALU.bCn = 0;
            break;
        }
    case OR:
        {
            Item.ALU.bS3 = 1;
            Item.ALU.bS2 = 1;
            Item.ALU.bS1 = 1;
            Item.ALU.bS0 = 0;
            Item.ALU.bM  = 1;
            Item.ALU.bCn = 0;
            break;
        }
    case XOR:
        {
            Item.ALU.bS3 = 0;
            Item.ALU.bS2 = 1;
            Item.ALU.bS1 = 1;
            Item.ALU.bS0 = 0;
            Item.ALU.bM  = 1;
            Item.ALU.bCn = 0;
            break;
        }
    default:break;
    }

    return true;
}