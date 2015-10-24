// Dlg_MyCPU.cpp : implementation file
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_CPU.h"
#include "11.Common/StrConver.h"



IMPLEMENT_DYNAMIC(CDlg_CPU, CDialog)
CDlg_CPU::CDlg_CPU(CWnd* pParent /*=NULL*/)
    :CDialog(CDlg_CPU::IDD, pParent),
    m_nTabShowItem(0),
    m_pmapAsm(NULL),
    m_pszMem(NULL)
{
}

CDlg_CPU::~CDlg_CPU()
{
}

void CDlg_CPU::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CPU_TAB,           m_tabSel);
    DDX_Control(pDX, IDC_CPU_LIST_UNASM,    m_lstUnasm);
    DDX_Control(pDX, IDC_CPU_LIST_MEMORY,   m_lstMemory);
    DDX_Control(pDX, IDC_CPU_LIST_REGISTER, m_lstRegister);
}


BEGIN_MESSAGE_MAP(CDlg_CPU, CDialog)
    ON_BN_CLICKED(IDC_CPU_BTN_RUN,            OnBnClickedCpuRun)
    ON_BN_CLICKED(IDC_CPU_BTN_PAUSE,          OnBnClickedCpuPause)
    ON_BN_CLICKED(IDC_CPU_BTN_SINGLESTEP,     OnBnClickedCpuSinglestep)
    ON_BN_CLICKED(IDC_CPU_BTN_MICROCODESTEP,  OnBnClickedCpuMicrocodestep)
    ON_BN_CLICKED(IDC_CPU_BTN_MADEMICROCODE,  OnBnClickedCpuBtnMadeCode)
    ON_BN_CLICKED(IDC_CPU_BTN_LOAD,           OnBnClickedCpuLoad)
    ON_BN_CLICKED(IDC_CPU_BTN_SAVE,           OnBnClickedCpuSave)
    ON_NOTIFY(TCN_SELCHANGE, IDC_CPU_TAB,     OnTcnSelchangeTab)
END_MESSAGE_MAP()


BOOL CDlg_CPU::OnInitDialog()
{
    CDialog::OnInitDialog();

    GetDlgItem(IDC_CPU_EDIT_BEGIN)->SetWindowText("0x10000");
    GetDlgItem(IDC_CPU_EDIT_LEN)->SetWindowText("0x200");

    m_tabSel.InsertItem(0, "Unasm");
    m_tabSel.InsertItem(1, "Memory");

    m_lstUnasm.SetExtendedStyle(m_lstUnasm.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    m_lstUnasm.SetImageList(g_ProFile.getImageList(), LVSIL_SMALL);
    m_lstUnasm.InsertColumn(0, "",        0, 20);
    m_lstUnasm.InsertColumn(1, "Address", 0, 70);
    m_lstUnasm.InsertColumn(2, "Code",    0, 60);
    m_lstUnasm.InsertColumn(3, "Asm",     0, 120);
    m_lstUnasm.MoveWindow(15, 80, 300, 370);

    m_lstMemory.SetExtendedStyle(m_lstMemory.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    m_lstMemory.InsertColumn(0, "Address",0, 70);
    m_lstMemory.InsertColumn(1, "Code",   2, 300);
    m_lstMemory.InsertColumn(2, "Ascii",  2, 180);
    m_lstMemory.MoveWindow(15, 80, 600, 370);
    m_lstMemory.ShowWindow(SW_HIDE);

    m_lstRegister.SetExtendedStyle(m_lstUnasm.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    m_lstRegister.InsertColumn(0, "Reg",   0, 80);
    m_lstRegister.InsertColumn(1, "Value", 2, 120);
    m_lstRegister.InsertItem(0, "AX");
    m_lstRegister.InsertItem(1, "BX");
    m_lstRegister.InsertItem(2, "CX");
    m_lstRegister.InsertItem(3, "DX");
    m_lstRegister.InsertItem(4, "CS");
    m_lstRegister.InsertItem(5, "DS");
    m_lstRegister.InsertItem(6, "SS");
    m_lstRegister.InsertItem(7, "ES");
    m_lstRegister.InsertItem(8, "BP");
    m_lstRegister.InsertItem(9, "SP");
    m_lstRegister.InsertItem(10, "IP");
    m_lstRegister.InsertItem(11, "MSW");
    m_lstRegister.InsertItem(12, "IR");
    m_lstRegister.InsertItem(13, "T1");
    m_lstRegister.InsertItem(14, "AT");
    m_lstRegister.InsertItem(15, "DRH");
    m_lstRegister.InsertItem(16, "DRL");
    m_lstRegister.InsertItem(17, "IBUS");
    m_lstRegister.InsertItem(18, "OBUS");
    m_lstRegister.InsertItem(19, "ABUS");
    m_lstRegister.InsertItem(20, "MicroCodeAddr");
    m_lstRegister.InsertItem(21, "MicroCode");

    m_ShowData.Init(&m_lstUnasm, &m_lstMemory, &m_lstRegister);

    m_CPUEmulator.Init(&m_ShowData, "E:\\TestSet\\Environment\\cpu\\Doc\\Î¢´úÂë.txt");
    m_CPUEmulator.Reset();

    m_pmapAsm = m_CPUEmulator.GetMapAsm();
    m_pszMem = m_CPUEmulator.GetMemPtr();

    OnBnClickedCpuLoad();

    return TRUE;
}

void CDlg_CPU::OnBnClickedCpuRun()
{
    m_CPUEmulator.Run();
}

void CDlg_CPU::OnBnClickedCpuPause()
{
    m_CPUEmulator.Pause();
}

void CDlg_CPU::OnBnClickedCpuSinglestep()
{
    m_CPUEmulator.SingleStep();
}

void CDlg_CPU::OnBnClickedCpuMicrocodestep()
{
    m_CPUEmulator.SingleMicroCode();
}

void CDlg_CPU::TabShow(int nItem, int nCmdShow)
{
    if (m_nTabShowItem != nItem)
    {
        switch(m_nTabShowItem)
        {
        case 0:
            {
                m_lstUnasm.ShowWindow(SW_HIDE);
                m_lstRegister.ShowWindow(SW_HIDE);
                GetDlgItem(IDC_CPU_BTN_RUN)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_CPU_BTN_PAUSE)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_CPU_BTN_SINGLESTEP)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_CPU_BTN_MICROCODESTEP)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_CPU_BTN_MADEMICROCODE)->ShowWindow(SW_HIDE);
                break;
            }
        case 1:
            {
                m_lstMemory.ShowWindow(SW_HIDE);
                break;
            }
        }

        switch(nItem)
        {
        case 0:
            {
                m_lstUnasm.ShowWindow(SW_SHOW);
                m_lstRegister.ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CPU_BTN_RUN)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CPU_BTN_PAUSE)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CPU_BTN_SINGLESTEP)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CPU_BTN_MICROCODESTEP)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CPU_BTN_MADEMICROCODE)->ShowWindow(SW_SHOW);
                break;
            }
        case 1:
            {
                m_lstMemory.ShowWindow(SW_SHOW);
                break;
            }
        }

        m_nTabShowItem = nItem;
    }
}

void CDlg_CPU::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;

    int nItemId = m_tabSel.GetCurSel();

    switch(nItemId)
    {
    case 0:
        {
            TabShow(1, SW_HIDE);
            TabShow(0, SW_SHOW);
            break;
        }
    case 1:
        {
            TabShow(0, SW_HIDE);
            TabShow(1, SW_SHOW);
            break;
        }
    }
}

void CDlg_CPU::OnBnClickedCpuBtnMadeCode()
{
}

void CDlg_CPU::OnBnClickedCpuLoad()
{
    CString strBegin;
    CString strLen;
    GetDlgItem(IDC_CPU_EDIT_BEGIN)->GetWindowText(strBegin);
    GetDlgItem(IDC_CPU_EDIT_LEN)->GetWindowText(strLen);

    DWORD dwBegin = (DWORD)CStrConver::StrToHex(strBegin.GetString());
    DWORD dwLen = (DWORD)CStrConver::StrToHex(strLen.GetString());

    int nItemId = m_tabSel.GetCurSel();
    if (0 == nItemId)
    {
        m_ShowData.UpdateUnasm(m_pszMem, m_pmapAsm, dwBegin, dwLen);
    }
    else
    {
        m_ShowData.UpdateMemory(m_pszMem, dwBegin, dwLen);
    }
}

void CDlg_CPU::OnBnClickedCpuSave()
{
    char *pszPath = "E:\\TestSet\\Environment\\cpu\\Proteus";
    m_CPUEmulator.SaveMicroCode(pszPath, "AX");
    m_CPUEmulator.SaveMicroCode(pszPath, "BX");
    m_CPUEmulator.SaveMicroCode(pszPath, "CX");
    m_CPUEmulator.SaveMicroCode(pszPath, "DX");
    m_CPUEmulator.SaveMicroCode(pszPath, "CS");
    m_CPUEmulator.SaveMicroCode(pszPath, "DS");
    m_CPUEmulator.SaveMicroCode(pszPath, "SS");
    m_CPUEmulator.SaveMicroCode(pszPath, "ES");
    m_CPUEmulator.SaveMicroCode(pszPath, "BP");
    m_CPUEmulator.SaveMicroCode(pszPath, "SP");
    m_CPUEmulator.SaveMicroCode(pszPath, "IP");
    m_CPUEmulator.SaveMicroCode(pszPath, "T1");
    m_CPUEmulator.SaveMicroCode(pszPath, "AT");
    m_CPUEmulator.SaveMicroCode(pszPath, "DRH");
    m_CPUEmulator.SaveMicroCode(pszPath, "DRL");
    m_CPUEmulator.SaveMicroCode(pszPath, "MSW");
    m_CPUEmulator.SaveMicroCode(pszPath, "IR");
    m_CPUEmulator.SaveMicroCode(pszPath, "MEM");
    m_CPUEmulator.SaveMicroCode(pszPath, "ALU");
    m_CPUEmulator.SaveMicroCode(pszPath, "NextAddrLow");
    m_CPUEmulator.SaveMicroCode(pszPath, "NextAddrHigh");
}
