#include "StdAfx.h"
#include "cpu.h"
#include "11.Common/StrConver.h"


CCPU::CCPU(void)
    :m_eCurStat(PAUSE),
    m_bExit(false),
    m_hSingleStep(NULL),
    m_hWorkThread(NULL),
    m_pShowData(NULL)
{
    m_hSingleStep = ::CreateEvent(NULL, FALSE, FALSE, NULL);

    UINT nThreadID = 0;
    m_hWorkThread = (HANDLE)_beginthreadex(NULL, 0, WorkThread, (void*)this, 0, &nThreadID);
}

CCPU::~CCPU(void)
{
    m_bExit = true;

    // 关闭线程
    if (m_hWorkThread != NULL)
    {
        int i = 10;
        for (; i > 0 ; i--)
        {
            DWORD nCode;
            if (!GetExitCodeThread(m_hWorkThread, &nCode)) break;
            if (nCode != STILL_ACTIVE) break;
            Sleep(50);
        }

        if (i == 0)
        {
            TerminateThread(m_hWorkThread, 0);
            LOG(INFO) << "WARNING: Terminating CCPUEmulator.WorkThread Thread.";
            Sleep(50);
        }

        CloseHandle(m_hWorkThread);
    }
}

bool CCPU::Init(CShowData *pShowData, const char *pszFileName)
{
	if ((NULL == pShowData) || (NULL == pszFileName)) return false;

	m_pShowData = pShowData;

	if (m_MicroCode.Init(pszFileName) && m_Mem.Init(0x100000, pShowData))
		return true;
	else
		return false;
}

bool CCPU::SaveMicroCode(const char *pszPath, const char *pszName)
{
    return m_MicroCode.SaveMicroCode(pszPath, pszName);
}

void CCPU::Reset(void)
{
    for (int i = 0; i < REG_COUNT; i++)
    {
        m_Reg[i].wValue = 0;
    }

    for (int i = 0; i < ABUS; i++)
    {
        m_Bus[i].dwValue = 0;
    }

	m_wMicroCodeAddr = 0;
}

void CCPU::Run(void)
{
    m_eCurStat = RUN;
    ::SetEvent(m_hSingleStep);
}

void CCPU::Pause(void)
{
    m_eCurStat = PAUSE;
}

void CCPU::SingleStep(void)
{
    m_eCurStat = SINGLESTEP;
    ::SetEvent(m_hSingleStep);
}

void CCPU::SingleMicroCode(void)
{
}

unsigned CCPU::WorkThread(LPVOID pParam)
{
    if (NULL == pParam) return -1;

    CCPU *pthis = reinterpret_cast<CCPU*>(pParam);

    try
    {
        while (!pthis->m_bExit)
        {
            if (PAUSE == pthis->m_eCurStat)
            {
                ::Sleep(100);
            }
            else if (SINGLESTEP == pthis->m_eCurStat)
            {
                ::WaitForSingleObject(pthis->m_hSingleStep, INFINITE);
                ::ResetEvent(pthis->m_hSingleStep);

                pthis->ProcessSingleStep();
            }
            else
            {
                pthis->ProcessSingleStep();
            }
        }
    }
    catch(...)
    {
        MessageBox(NULL, "CCPU::WorkThread Error", "", MB_OK);
        LOG(ERROR) << "CCPU::WorkThread ErrorCode:" << GetLastError();
    }

    return 0;
}

void CCPU::ProcessSingleStep(void)
{/*
	if (m_bSelIR)
	{
		m_wMicroCodeAddr = m_IR.byValue;// << 4 | 0x01;	// 从IR取微代码地址,只有取指指令 Get1 执行
	}
	else if (m_bJmp)
	{
		m_wMicroCodeAddr++;
	}
	else
	{
		m_wMicroCodeAddr = m_CurMicroCode.NextAddr;
	}

	m_CurMicroCode.n64Value = m_MicroCode.GetMicroCode(m_wMicroCodeAddr);

	if (0 != m_CurMicroCode.n64Value)
    {
        if ((m_wMicroCodeAddr >= 0x120 && m_wMicroCodeAddr <= 0x1d0)    // POP
            || (m_wMicroCodeAddr >= 0x1F0 && m_wMicroCodeAddr <= 0x1F3) // RET
            || (m_wMicroCodeAddr >= 0x2E0 && m_wMicroCodeAddr <= 0x310) // Condition JMP
            )
        {
            this->ProcessMicroCodeALU(m_CurMicroCode.AluOperater);
            this->ProcessMicroCodeReg(m_CurMicroCode.Reg1, m_CurMicroCode.Reg1RW, m_CurMicroCode.Reg1To);
            this->ProcessMicroCodeReg(m_CurMicroCode.Reg2, m_CurMicroCode.Reg2RW, m_CurMicroCode.Reg2To);
            this->ProcessMicroCodeReg(m_CurMicroCode.Reg3, m_CurMicroCode.Reg3RW, m_CurMicroCode.Reg3To);
            this->ProcessMicroCodeRegMemory();
        }
        else
        {
            this->ProcessMicroCodeReg(m_CurMicroCode.Reg1, m_CurMicroCode.Reg1RW, m_CurMicroCode.Reg1To);
            this->ProcessMicroCodeReg(m_CurMicroCode.Reg2, m_CurMicroCode.Reg2RW, m_CurMicroCode.Reg2To);
            this->ProcessMicroCodeReg(m_CurMicroCode.Reg3, m_CurMicroCode.Reg3RW, m_CurMicroCode.Reg3To);
            this->ProcessMicroCodeRegMemory();
            this->ProcessMicroCodeALU(m_CurMicroCode.AluOperater);
        }
    }
    else
    {
        TRACE(_T("Don't have this %d micro code\n"), m_wMicroCodeAddr);
    }*/
}

void CCPU::ProcessMicroCodeRegMemory(void)
{/*
    if ((0x000 == m_wMicroCodeAddr)
        || (m_wMicroCodeAddr >= 0x120 && m_wMicroCodeAddr <= 0x1D0)	// POP R
        || (m_wMicroCodeAddr >= 0x1E5 && m_wMicroCodeAddr <= 0x1F3)	// CALL ES:IMM16,RET
        || (m_wMicroCodeAddr >= 0x2E2 && m_wMicroCodeAddr <= 0x3A1)	// Condition JMP
        || (m_wMicroCodeAddr >= 0x6D1 && m_wMicroCodeAddr <= 0x882)	// MOV
        )
    {
        this->ProcessMicroCodeMemory(m_CurMicroCode.MemoryTo, m_CurMicroCode.MemoryRW);
        this->ProcessMicroCodeReg(m_CurMicroCode.Reg3, m_CurMicroCode.Reg3RW, m_CurMicroCode.Reg3To);
    }
    else
    {
        this->ProcessMicroCodeReg(m_CurMicroCode.Reg3, m_CurMicroCode.Reg3RW, m_CurMicroCode.Reg3To);
        this->ProcessMicroCodeMemory(m_CurMicroCode.MemoryTo, m_CurMicroCode.MemoryRW);
    }*/
}

// 处理各个寄存器的存取
void CCPU::ProcessMicroCodeReg(unsigned char byRegId, unsigned char byRegRW, unsigned char byRegTo)
{/*
    switch(byRegId)
    {
    case 0: break;
    case AH: ProcessMicroCodeRegEx(&m_AH, byRegRW, byRegTo); break;
    case AL: ProcessMicroCodeRegEx(&m_AL, byRegRW, byRegTo); break;
	case BH: ProcessMicroCodeRegEx(&m_BH, byRegRW, byRegTo); break;
	case BL: ProcessMicroCodeRegEx(&m_BL, byRegRW, byRegTo); break;
	case CH: ProcessMicroCodeRegEx(&m_CH, byRegRW, byRegTo); break;
	case CL: ProcessMicroCodeRegEx(&m_CL, byRegRW, byRegTo); break;
	case DH: ProcessMicroCodeRegEx(&m_DH, byRegRW, byRegTo); break;
	case DL: ProcessMicroCodeRegEx(&m_DL, byRegRW, byRegTo); break;
    case CS: ProcessMicroCodeRegEx(&m_CS, byRegRW, byRegTo); break;
    case SS: ProcessMicroCodeRegEx(&m_SS, byRegRW, byRegTo); break;
    case DS: ProcessMicroCodeRegEx(&m_DS, byRegRW, byRegTo); break;
    case ES: ProcessMicroCodeRegEx(&m_ES, byRegRW, byRegTo); break;
    case BP: ProcessMicroCodeRegEx(&m_BP, byRegRW, byRegTo); break;
    case SP: ProcessMicroCodeRegEx(&m_SP, byRegRW, byRegTo); break;
    case IP: ProcessMicroCodeRegEx(&m_IP, byRegRW, byRegTo); break;
    case IR: ProcessMicroCodeRegEx(&m_IR, byRegRW, byRegTo); break;
    case FR: ProcessMicroCodeRegEx(&m_FR, byRegRW, byRegTo); break;
	case T1: ProcessMicroCodeRegEx(&m_T1, byRegRW, byRegTo); break;
	case T2: ProcessMicroCodeRegEx(&m_T2, byRegRW, byRegTo); break;
    default: MessageBox(NULL, _T("没有这个REG"), _T("Error"), MB_OK); break;
    }*/
}

// 16位寄存器操作
void CCPU::ProcessMicroCodeRegEx(REG16 *pReg, unsigned char byRegRW, unsigned char byRegTo)
{/*
	if (R == byRegRW)	// 0读,1写
	{
		switch(byRegTo)	// 0-IDBus,1-ODBus,2-ABus
		{
		case I: m_IDBus16.wValue = pReg->wValue; break;
		case O: m_ODBus16.wValue = pReg->wValue; break;
		case A:
			{
				if (pReg == &m_CS || pReg == &m_DS || pReg == &m_SS || pReg == &m_ES)
				{
					m_ABus32.wHigh = pReg->wValue;
				}
				else if (pReg == &m_BP || pReg == &m_SP || pReg == &m_IP || pReg == &m_T1 || pReg == &m_T2)
				{
					m_ABus32.wLow = pReg->wValue;
				}
				else
				{
					MessageBox(NULL, _T("与 ABus 相连接对象错误"), _T("Error"), MB_OK);
				}

				break;
			}
		default: MessageBox(NULL, _T("与 REG 相连接对象错误"), _T("Error"), MB_OK); break;
		}
	}
	else	// 写
	{
		switch(byRegTo)	// 0-IDBus,1-ODBus,2-ABus
		{
		case I: pReg->wValue = m_IDBus16.wValue; break;
		case O: pReg->wValue = m_ODBus16.wValue; break;
		case A: MessageBox(NULL, _T("不能从地址总线上读数据,只能向地址总线上写数据"), _T("Error"), MB_OK);break;
		default: MessageBox(NULL, _T("与 REG 相连接对象错误"), _T("Error"), MB_OK); break;
		}
	}*/
}

// 8位寄存器操作
void CCPU::ProcessMicroCodeRegEx(REG8 *pReg, unsigned char byRegRW, unsigned char byRegTo)
{/*
	if (R == byRegRW)	// 0读,1写
	{
		switch(byRegTo)	// 0-IDBus,1-ODBus,2-ABus
		{
		case I:
			{
				if (pReg == &m_AH || pReg == &m_BH || pReg == &m_CH || pReg == &m_DH)
				{
					m_IDBus16.byHigh = pReg->byValue;
				}
				else if (pReg == &m_AL || pReg == &m_BL || pReg == &m_CL || pReg == &m_DL)
				{
					m_IDBus16.byLow = pReg->byValue;
				}

				break;
			}
		case O:
			{
				if (pReg == &m_AH || pReg == &m_BH || pReg == &m_CH || pReg == &m_DH)
				{
					m_ODBus16.byHigh = pReg->byValue;
				}
				else if (pReg == &m_AL || pReg == &m_BL || pReg == &m_CL || pReg == &m_DL)
				{
					m_ODBus16.byLow = pReg->byValue;
				}

				break;
			}
		case A:
			{
				if (pReg == &m_AH || pReg == &m_BH || pReg == &m_CH || pReg == &m_DH)
				{
					m_ABus32.byLow2 = pReg->byValue;
				}
				else if (pReg == &m_AL || pReg == &m_BL || pReg == &m_CL || pReg == &m_DL)
				{
					m_ABus32.byLow1 = pReg->byValue;
				}

				break;
			}
		default: MessageBox(NULL, _T("与 REG 相连接对象错误"), _T("Error"), MB_OK); break;
		}
	}
	else	// 写
	{
		switch(byRegTo)	// 0-IDBus,1-ODBus,2-ABus
		{
		case I:
			{
				if (pReg == &m_AH || pReg == &m_BH || pReg == &m_CH || pReg == &m_DH)
				{
					pReg->byValue = m_IDBus16.byHigh;
				}
				else if (pReg == &m_AL || pReg == &m_BL || pReg == &m_CL || pReg == &m_DL)
				{
					pReg->byValue = m_IDBus16.byLow;
				}

				break;
			}
		case O:
			{
				if (pReg == &m_AH || pReg == &m_BH || pReg == &m_CH || pReg == &m_DH)
				{
					pReg->byValue = m_ODBus16.byHigh;
				}
				else if (pReg == &m_AL || pReg == &m_BL || pReg == &m_CL || pReg == &m_DL)
				{
					pReg->byValue = m_ODBus16.byLow;
				}

				break;
			}
		case A: MessageBox(NULL, _T("不能从地址总线上读数据,只能向地址总线上写数据"), _T("Error"), MB_OK);break;
		default: MessageBox(NULL, _T("与 REG 相连接对象错误"), _T("Error"), MB_OK); break;
		}
	}*/
}

// byMemoryRW: 0无操作,1读,2写
// byMemoryTo: 0与低8位,1与高8位
void CCPU::ProcessMicroCodeMemory(unsigned char byMemoryTo, unsigned char byMemoryRW)
{/*
	switch(byMemoryRW)
	{
	case 0: break;
	case MR:
		{
			if (MH == byMemoryTo)
				m_Mem.Read(m_ABus32.dwValue, m_ODBus16.byHigh);
			else
				m_Mem.Read(m_ABus32.dwValue, m_ODBus16.byLow);
			break;
		}
	case MW:
		{
			if (MH == byMemoryTo)
				m_Mem.Write(m_ABus32.dwValue, m_ODBus16.byHigh);
			else
				m_Mem.Write(m_ABus32.dwValue, m_ODBus16.byLow);
			break;
		}
	default:
		MessageBox(NULL, _T("与内存相连接的对象错误"), _T("Error"), MB_OK);
		break;
	}*/
}

/*
标志位:

无符号:
CF = 1			    A < B
CF = 1 或 ZF = 1	A <= B
CF = 0			    A >= B
CF = 0 且 ZF = 0	A > B

有符号:
当 OF = 0 时
SF = 0 且 ZF = 0	A > B
SF = 0 或 ZF = 1	A >= B
SF = 1 且 ZF = 0	A < B
SF = 1 或 ZF = 1	A <= B

当 OF = 1 时
SF = 1			    A > B
SF = 0			    A < B

*/
void CCPU::ProcessMicroCodeALU(unsigned char byALUOp)
{/*
	m_bJmp = false;
	m_bSelIR = false;

	int nNum1 = m_IDBus16.wValue;
	int nNum2 = m_ODBus16.wValue;
	int nNum3 = 0;

	switch(byALUOp)
	{
	case 0: break;
	case ADD: m_T1.wValue = nNum1 + nNum2;		ProcessMicroCodeSetMSW();	break;
	case SUB: m_T1.wValue = nNum1 - nNum2;		ProcessMicroCodeSetMSW();	break;
	case INC: m_T1.wValue = nNum1 + 1;			ProcessMicroCodeSetMSW();	break;
	case DEC: m_T1.wValue = nNum1 - 1;			ProcessMicroCodeSetMSW();	break;
	case A2:  m_T1.wValue = nNum1 + 2;			ProcessMicroCodeSetMSW();	break;
	case S2:  m_T1.wValue = nNum1 - 2;			ProcessMicroCodeSetMSW();	break;
	case A3:  m_T1.wValue = nNum1 + 3;			ProcessMicroCodeSetMSW();	break;
	case MUL: m_T1.wValue = nNum1 * nNum2;		ProcessMicroCodeSetMSW();	break;
	case DIV: m_T1.wValue = nNum1 / nNum2;		ProcessMicroCodeSetMSW();	break;
	case AND: m_T1.wValue = nNum1 & nNum2;		ProcessMicroCodeSetMSW();	break;
	case OR:  m_T1.wValue = nNum1 | nNum2;		ProcessMicroCodeSetMSW();	break;
	case XOR: m_T1.wValue = nNum1 ^ nNum2;		ProcessMicroCodeSetMSW();	break;
	case NOT: m_T1.wValue = ~nNum1;				ProcessMicroCodeSetMSW();	break;
	case SAR: m_T1.wValue = nNum1 >> nNum2;		ProcessMicroCodeSetMSW();	break;
	case SAL: m_T1.wValue = nNum1 << nNum2;		ProcessMicroCodeSetMSW();	break;
	case JA:  if (!m_FR.bCarry && !m_FR.bZero)	m_bJmp = true;				break;
	case JAE: if (!m_FR.bCarry)					m_bJmp = true;				break;
	case JB:  if (m_FR.bCarry)					m_bJmp = true;				break;
	case JBE: if (m_FR.bCarry || m_FR.bZero)	m_bJmp = true;				break;
	case JE:  if (m_FR.bZero)					m_bJmp = true;				break;
	case JNE: if (!m_FR.bZero)					m_bJmp = true;				break;
	case JC:  if (m_FR.bCarry)					m_bJmp = true;				break;
	case JNC: if (!m_FR.bCarry)					m_bJmp = true;				break;
	case SI: m_bSelIR = true; break;
	default: MessageBox(NULL, _T("ALU操作码错误"), _T("Error"), MB_OK);	break;
	}*/
}

void CCPU::ProcessMicroCodeSetMSW(void)
{
	if (m_Reg[AT].wValue & 0x0100)
		m_Reg[MSW].byHigh.bCarry = true;
	else
		m_Reg[MSW].byHigh.bCarry = true;

	if (m_Reg[AT].wValue >= 32757 && m_Reg[AT].wValue <= -32768)
		m_Reg[MSW].byHigh.bOver = true;
	else
		m_Reg[MSW].byHigh.bOver = true;

	if (m_Reg[AT].wValue & 0x0080)
		m_Reg[MSW].byHigh.bSign = true;
	else
		m_Reg[MSW].byHigh.bSign = false;

	if (m_Reg[AT].wValue == 0)
		m_Reg[MSW].byHigh.bZero = true;
	else
		m_Reg[MSW].byHigh.bZero = false;

}