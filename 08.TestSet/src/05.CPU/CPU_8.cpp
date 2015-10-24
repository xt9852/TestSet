#include "StdAfx.h"
#include "cpu_8.h"
#include "Common/StrConver.h"


CCPU_8::CCPU_8(void)
    :m_eCurStat(PAUSE),
	m_bSelIR(true),
	m_bJmp(false),
    m_bExit(false),
    m_hSingleStep(NULL),
    m_hWorkThread(NULL),
    m_plstUnasm(NULL),
    m_plstMemory(NULL),
    m_plstRegister(NULL)
{
    m_hSingleStep = ::CreateEvent(NULL, FALSE, FALSE, NULL);

    UINT nThreadID = 0;
    m_hWorkThread = (HANDLE)_beginthreadex(NULL, 0, WorkThread, (void*)this, 0, &nThreadID);

    m_mapMicroCode.InitHashTable(501);
}

CCPU_8::~CCPU_8(void)
{
    m_bExit = true;

    // 关闭线程
    if (m_hWorkThread != NULL)
    {
        for (int nAttempt = 10 ; nAttempt > 0 ; nAttempt--)
        {
            DWORD nCode;
            if (!GetExitCodeThread(m_hWorkThread, &nCode)) break;
            if (nCode != STILL_ACTIVE) break;
            Sleep(50);
        }

        if (nAttempt == 0)
        {
            TerminateThread(m_hWorkThread, 0);
            g_ProFile.m_Log.println(_T("WARNING: Terminating CCPUEmulator.WorkThread Thread."));
            Sleep( 50);
        }

        CloseHandle(m_hWorkThread);
    }
}

bool CCPU_8::Init(CListCtrl *plstUnasm, CListCtrl *plstMemory, CListCtrl *plstRegister)
{
    if ((NULL == plstUnasm) || (NULL == plstMemory) || (NULL == plstRegister)) return false;

    m_plstRegister = plstRegister;

    return m_Mem.Init(0x100000, plstUnasm, plstMemory);
}

void CCPU_8::Reset(void)
{
    m_AX.byValue = 0xa1;
    m_BX.byValue = 0xb1;
    m_CX.byValue = 0xc1;
    m_DX.byValue = 0xd1;
    m_CS.byValue = 1;    
    m_DS.byValue = 2;
	m_SS.byValue = 3;
    m_ES.byValue = 4;
    m_BP.byValue = 0;
    m_SP.byValue = 0xff;
    m_IP.byValue = 1;
    m_IR.byValue = 0;
	m_MSW.byValue = 0;
    
    m_TR1.byValue = 0;
	m_TR2.byValue = 0;
    m_IDBus.byValue = 0;
    m_ODBus.byValue = 0;
    m_ABus.wValue = 0;

    m_MCAddr.w12Value = 0;
    m_MicroCode.n64Value = 0;

    //-----------------------------------------

    CStdioFile file;
    if (file.Open(g_ProFile.m_strCurPath + _T("\\res\\微代码.txt"), CFile::modeRead))
    {
        CString strLine;
        BOOL bExit = FALSE;

        do
        {
            if (bExit = file.ReadString(strLine))
            {
                MICROCODE_8 mc = {0};
                int nPos = 0;

                CString strAddr = strLine.Tokenize(_T("\t"), nPos);

                WORD wAddr = (WORD)CStrConver::StrToHex(strAddr);

                CString strMC = strLine.Mid(nPos);
                mc.n64Value = CStrConver::StrToHex(strMC);

                m_mapMicroCode.SetAt(wAddr, mc);

            }			
        } while(bExit);

        file.Close();
    }
}

void CCPU_8::Run(void)
{
    m_eCurStat = RUN;
    ::SetEvent(m_hSingleStep);
}

void CCPU_8::Pause(void)
{
    m_eCurStat = PAUSE;
    UpdateRegList();
}


void CCPU_8::SingleStep(void)
{
    m_eCurStat = SINGLESTEP;
    ::SetEvent(m_hSingleStep);
}


void CCPU_8::SingleMicroCode(void)
{
}


unsigned CCPU_8::WorkThread(LPVOID pParam)
{
    if (NULL == pParam) return -1;

    CCPU_8 *pthis = reinterpret_cast<CCPU_8*>(pParam);

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
                pthis->UpdateRegList();

                if (pthis->m_MCAddr.w12Value == 0x000)
                    pthis->UpdateUnasmIcon();
            }
            else
            {
                pthis->ProcessSingleStep();
            }
        }
    }
    catch(...)
    {
        MessageBox(NULL, _T("CCPU::WorkThread Error"), _T(""), MB_OK);
        g_ProFile.m_Log.println(_T("CCPU::WorkThread ErrorCode:%d"), ::GetLastError());
    }

    return 0;
}

void CCPU_8::ProcessSingleStep(void)
{
	if (m_bSelIR)
	{
		m_MCAddr.w12Value = m_IR.byValue << 4 | 0x01;	// 从IR取微代码地址,只有取指指令 Get1 执行
	}
	else if (m_bJmp)
	{
		m_MCAddr.w12Value++;
	}
	else
	{
		m_MCAddr.w12Value = m_MicroCode.NextAddr;
	}

	if (m_MCAddr.w12Value > 0x0FFF)
		m_MCAddr.w12Value = 0;

    if (m_mapMicroCode.Lookup(m_MCAddr.w12Value, m_MicroCode))
    {
        if ((m_MCAddr.w12Value >= 0x120 && m_MCAddr.w12Value <= 0x1d0)    // POP
            || (m_MCAddr.w12Value >= 0x1F0 && m_MCAddr.w12Value <= 0x1F3) // RET
            || (m_MCAddr.w12Value >= 0x2E0 && m_MCAddr.w12Value <= 0x310) // Condition JMP
            )
        {
            this->ProcessMicroCodeALU(m_MicroCode.AluOperater);

            this->ProcessMicroCodeReg(m_MicroCode.Reg1, m_MicroCode.Reg1RW, m_MicroCode.Reg1To);
            this->ProcessMicroCodeReg(m_MicroCode.Reg2, m_MicroCode.Reg2RW, m_MicroCode.Reg2To);
            this->ProcessMicroCodeReg(m_MicroCode.Reg3, m_MicroCode.Reg3RW, m_MicroCode.Reg3To);
            this->ProcessMicroCodeRegMemory();
        }
        else
        {
            this->ProcessMicroCodeReg(m_MicroCode.Reg1, m_MicroCode.Reg1RW, m_MicroCode.Reg1To);
            this->ProcessMicroCodeReg(m_MicroCode.Reg2, m_MicroCode.Reg2RW, m_MicroCode.Reg2To);
            this->ProcessMicroCodeReg(m_MicroCode.Reg3, m_MicroCode.Reg3RW, m_MicroCode.Reg3To);
            this->ProcessMicroCodeRegMemory();

            this->ProcessMicroCodeALU(m_MicroCode.AluOperater);
        }
    }
    else
    {
        TRACE(_T("Don't have this %d micro code\n"), m_MCAddr.w12Value);
    }
}

void CCPU_8::ProcessMicroCodeRegMemory(void)
{
    if ((0x000 == m_MCAddr.w12Value)
        || (m_MCAddr.w12Value >= 0x120 && m_MCAddr.w12Value <= 0x1D0)	// POP R
        || (m_MCAddr.w12Value >= 0x1E5 && m_MCAddr.w12Value <= 0x1F3)	// CALL ES:IMM16,RET
        || (m_MCAddr.w12Value >= 0x2E2 && m_MCAddr.w12Value <= 0x3A1)	// Condition JMP
        || (m_MCAddr.w12Value >= 0x6D1 && m_MCAddr.w12Value <= 0x882)	// MOV
        )
    {
        this->ProcessMicroCodeMemory(m_MicroCode.MemoryRW);
        this->ProcessMicroCodeReg(m_MicroCode.Reg3, m_MicroCode.Reg3RW, m_MicroCode.Reg3To);
    }
    else
    {
        this->ProcessMicroCodeReg(m_MicroCode.Reg3, m_MicroCode.Reg3RW, m_MicroCode.Reg3To);
        this->ProcessMicroCodeMemory(m_MicroCode.MemoryRW);
    }
}

// 处理各个寄存器的存取
void CCPU_8::ProcessMicroCodeReg(BYTE byRegId, BYTE byRegRW, BYTE byRegTo)
{
    switch(byRegId)
    {
    case 0: break;
    case AX: ProcessMicroCodeRegEx(&m_AX, byRegRW, byRegTo); break;
    case BX: ProcessMicroCodeRegEx(&m_BX, byRegRW, byRegTo); break;
    case CX: ProcessMicroCodeRegEx(&m_CX, byRegRW, byRegTo); break;
    case DX: ProcessMicroCodeRegEx(&m_DX, byRegRW, byRegTo); break;
    case CS: ProcessMicroCodeRegEx(&m_CS, byRegRW, byRegTo); break;
    case DS: ProcessMicroCodeRegEx(&m_DS, byRegRW, byRegTo); break;
	case SS: ProcessMicroCodeRegEx(&m_SS, byRegRW, byRegTo); break;    
    case ES: ProcessMicroCodeRegEx(&m_ES, byRegRW, byRegTo); break;
    case BP: ProcessMicroCodeRegEx(&m_BP, byRegRW, byRegTo); break;
    case SP: ProcessMicroCodeRegEx(&m_SP, byRegRW, byRegTo); break;
    case IP: ProcessMicroCodeRegEx(&m_IP, byRegRW, byRegTo); break;
    case IR: ProcessMicroCodeRegEx(&m_IR, byRegRW, byRegTo); break;	
    case MSW: ProcessMicroCodeRegEx(&m_MSW,byRegRW, byRegTo); break;
	case TR1: ProcessMicroCodeRegEx(&m_TR1, byRegRW, byRegTo); break;
	case TR2: ProcessMicroCodeRegEx(&m_TR2, byRegRW, byRegTo); break;    
    default: MessageBox(NULL, _T("没有这个REG"), _T("Error"), MB_OK); break;
    }
}


void CCPU_8::ProcessMicroCodeRegEx(REG8 *pReg, BYTE byRegRW, BYTE byRegTo)
{
	if (NULL == pReg) return;

	if (0 == byRegRW)	// 0读,1写
	{
		switch(byRegTo)	// 0-IDBus,1-ODBus,2-ABus
		{
		case 0:	m_IDBus.byValue = pReg->byValue;break;
		case 1:	m_ODBus.byValue = pReg->byValue;break;
		case 2:
			{
				if (pReg == &m_AX || pReg == &m_CS || pReg == &m_DX || pReg == &m_SS || pReg == &m_ES)
					m_ABus.byLow = pReg->byValue;
				else if (pReg == &m_BP || pReg == &m_SP || pReg == &m_IP || pReg == &m_TR2)
					m_ABus.byHigh = pReg->byValue;
				else
					MessageBox(NULL, _T("与 ABus 相连接对象错误"), _T("Error"), MB_OK);

				break;
			}
		default: MessageBox(NULL, _T("与 REG 相连接对象错误"), _T("Error"), MB_OK); break;
		}
	}
	else
	{
		switch(byRegTo)	// 0-IDBus,1-ODBus,2-ABus
		{
		case 0:	pReg->byValue = m_IDBus.byValue;break;
		case 1:	pReg->byValue = m_ODBus.byValue;break;
		case 2: MessageBox(NULL, _T("不能从地址总线上读数据,只能向地址总线上写数据"), _T("Error"), MB_OK);break;
		default: MessageBox(NULL, _T("与 REG 相连接对象错误"), _T("Error"), MB_OK); break;
		}
	}
}

// byMemoryRW: 0无操作,1读,2写
// byMemoryTo: 0与低8位,1与高8位
void CCPU_8::ProcessMicroCodeMemory(BYTE byMemoryRW)
{
	switch(byMemoryRW)
	{
	case 0: break;
	case 1:m_Mem.Read(m_ABus.wValue, m_ODBus.byValue);break;
	case 2:m_Mem.Write(m_ABus.wValue, m_ODBus.byValue);break;
	default:
		MessageBox(NULL, _T("与内存相连接的对象错误"), _T("Error"), MB_OK);
		break;
	}
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
void CCPU_8::ProcessMicroCodeALU(BYTE byALUOp)
{
	m_bJmp = false;
	m_bSelIR = false;

    int nNum1 = m_IDBus.byValue;
    int nNum2 = m_ODBus.byValue;
    int nNum3 = 0;

    switch(byALUOp)
    {
    case 0: break;
    case ADD:  m_TR1.byValue = nNum1 + nNum2;	ProcessMicroCodeSetMSW();	break;
    case SUB:  m_TR1.byValue = nNum1 - nNum2;	ProcessMicroCodeSetMSW();	break;
	case INC:  m_TR1.byValue = nNum1 + 1;		ProcessMicroCodeSetMSW();	break;
	case DEL:  m_TR1.byValue = nNum1 - 1;		ProcessMicroCodeSetMSW();	break;
	case ADD2: m_TR1.byValue = nNum1 + 2;		ProcessMicroCodeSetMSW();	break;
	case SUB2: m_TR1.byValue = nNum1 - 2;		ProcessMicroCodeSetMSW();	break;
	case ADD3: m_TR1.byValue = nNum1 + 3;		ProcessMicroCodeSetMSW();	break;
	case MUL:  m_TR1.byValue = nNum1 * nNum2;	ProcessMicroCodeSetMSW();	break;
    case DIV:  m_TR1.byValue = nNum1 / nNum2;	ProcessMicroCodeSetMSW();	break;
    case AND:  m_TR1.byValue = nNum1 & nNum2;	ProcessMicroCodeSetMSW();	break;
    case OR:   m_TR1.byValue = nNum1 | nNum2;	ProcessMicroCodeSetMSW();	break;
    case XOR:  m_TR1.byValue = nNum1 ^ nNum2;	ProcessMicroCodeSetMSW();	break;
    case NOT:  m_TR1.byValue = ~nNum1;			ProcessMicroCodeSetMSW();	break;
    case SAR:  m_TR1.byValue = nNum1 >> nNum2;	ProcessMicroCodeSetMSW();	break;
    case SAL:  m_TR1.byValue = nNum1 << nNum2;	ProcessMicroCodeSetMSW();	break;
    case JA:  if (!m_MSW.bCarry && !m_MSW.bZero)m_bJmp = true; break;
    case JAE: if (!m_MSW.bCarry)				m_bJmp = true; break;
    case JB:  if (m_MSW.bCarry)					m_bJmp = true; break;
    case JBE: if (m_MSW.bCarry || m_MSW.bZero)	m_bJmp = true; break;
	case JE:  if (m_MSW.bZero)					m_bJmp = true; break;
    case JNE: if (!m_MSW.bZero)					m_bJmp = true; break;
    case JC:  if (m_MSW.bCarry)					m_bJmp = true; break;
    case JNC: if (!m_MSW.bCarry)				m_bJmp = true; break;
	case SEL_IR: m_bSelIR = true; break;
	default: MessageBox(NULL, _T("ALU操作码错误"), _T("Error"), MB_OK);	break;
    }
}

void CCPU_8::ProcessMicroCodeSetMSW(void)
{
	if (m_TR1.byValue & 0x0100)
		m_MSW.bCarry = true;
	else
		m_MSW.bCarry = true;

	if (m_TR1.byValue >= 32757 && m_TR1.byValue <= -32768)
		m_MSW.bOver = true;
	else
		m_MSW.bOver = true;

	if (m_TR1.byValue & 0x0080)
		m_MSW.bSign = true;
	else
		m_MSW.bSign = false;

	if (m_TR1.byValue == 0)
		m_MSW.bZero = true;
	else
		m_MSW.bZero = false;

}

void CCPU_8::UpdateRegList(void)
{
    if (NULL == m_plstRegister) return;

    char szValue[50] = {_T("")};
    sprintf(szValue, _T("0x%04X"), m_AX.byValue);
    m_plstRegister->SetItemText(0, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_BX.byValue);
    m_plstRegister->SetItemText(1, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_CX.byValue);
    m_plstRegister->SetItemText(2, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_DX.byValue);
    m_plstRegister->SetItemText(3, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_CS.byValue);
    m_plstRegister->SetItemText(4, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_SS.byValue);
    m_plstRegister->SetItemText(5, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_DS.byValue);
    m_plstRegister->SetItemText(6, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_ES.byValue);
    m_plstRegister->SetItemText(7, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_BP.byValue);
    m_plstRegister->SetItemText(8, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_SP.byValue);
    m_plstRegister->SetItemText(9, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_IP.byValue);
    m_plstRegister->SetItemText(10, 1, szValue);
    sprintf(szValue, _T("0x%02X"), m_MSW.byValue);
    m_plstRegister->SetItemText(11, 1, szValue);
    sprintf(szValue, _T("0x%02X"), m_IR.byValue);
    m_plstRegister->SetItemText(12, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_TR1.byValue);
	//sprintf(szValue, _T("0x%04X"), m_TR2.byValue);
    m_plstRegister->SetItemText(13, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_IDBus.byValue);
    m_plstRegister->SetItemText(14, 1, szValue);
    sprintf(szValue, _T("0x%04X"), m_ODBus.byValue);
    m_plstRegister->SetItemText(15, 1, szValue);
    sprintf(szValue, _T("0x%08X"), m_ABus.wValue);
    m_plstRegister->SetItemText(16, 1, szValue);
    sprintf(szValue, _T("0x%03X"), m_MCAddr.w12Value);
    m_plstRegister->SetItemText(17, 1, szValue);
    sprintf(szValue, _T("0x%08X%08X"), m_MicroCode.dw32High, m_MicroCode.dw32Low);
    m_plstRegister->SetItemText(18, 1, szValue);
}

void CCPU_8::UpdateUnasm(DWORD dwPos, DWORD dwLen)
{
    m_Mem.UpdateUnasm(dwPos, dwLen);
}
void CCPU_8::UpdateMemory(DWORD dwPos, DWORD dwLen)
{
    m_Mem.UpdateMemory(dwPos, dwLen);
}
void CCPU_8::UpdateUnasmIcon(void)
{
    m_Mem.UpdateUnasmIcon(m_CS.byValue, m_IP.byValue);
}
