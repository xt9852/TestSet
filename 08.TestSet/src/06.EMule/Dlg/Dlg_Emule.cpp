// Dlg_Emule.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "Dlg_Emule.h"


// CDlg_Emule 对话框

IMPLEMENT_DYNAMIC(CDlg_Emule, CDialog)
CDlg_Emule::CDlg_Emule(CWnd* pParent /*=NULL*/)
    :CDialog(CDlg_Emule::IDD, pParent),
    m_pLastDlg(NULL)
{
}

CDlg_Emule::~CDlg_Emule()
{
}

void CDlg_Emule::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EMULE_TAB1, m_Tab);	
}


BEGIN_MESSAGE_MAP(CDlg_Emule, CDialog)
    ON_BN_CLICKED(IDC_EMULE_BUT_PING, OnBnClickedEmuleButPing)
    ON_NOTIFY(TCN_SELCHANGE, IDC_EMULE_TAB1, OnTcnSelchangeEmuleTab1)
END_MESSAGE_MAP()

BOOL CDlg_Emule::OnInitDialog()
{
    CDialog::OnInitDialog();

    //-------------------------------------------------------------------------

    GetDlgItem(IDC_EMULE_EDIT_IP)->SetWindowText(_T("211.100.28.61"));
    GetDlgItem(IDC_EMULE_EDIT_PORT)->SetWindowText(_T("5144"));

    // 设置TAB控件
    m_Tab.InsertItem(0, _T("KAD"));
    m_Tab.InsertItem(1, _T("Server"));
    m_Tab.InsertItem(2, _T("Search"));

    CRect rcRect;
    this->GetParent()->GetClientRect(&rcRect);
    rcRect.top += 35;
    this->MoveWindow(&rcRect);

    m_DlgKAD.Create(IDD_DLG_EMULE_KAD, this);
    m_DlgKAD.MoveWindow(rcRect);
    m_DlgKAD.ShowWindow(SW_SHOW);
    m_pLastDlg = &m_DlgKAD;

    m_DlgSearch.Create(IDD_DLG_EMULE_SEARCH, this);
    m_DlgSearch.MoveWindow(rcRect);
    m_DlgSearch.ShowWindow(SW_HIDE);

    return TRUE;
}

void CDlg_Emule::OnBnClickedEmuleButPing()
{
    CString strIP;
    GetDlgItem(IDC_EMULE_EDIT_PORT)->GetWindowText(strIP);

    UINT nAddr = inet_addr(strIP);

    PingStatus Status = m_Ping.Ping(nAddr, 64, true);
    DWORD dwTick = ::GetTickCount();

    if (Status.success)
    {
        CString msg;
        msg.Format(_T("Ping IP: %s,TTL:%d,Time:%f ms"), (LPCTSTR)strIP, Status.ttl, Status.delay);
        MessageBox(msg);
    }
}

void CDlg_Emule::OnTcnSelchangeEmuleTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;

    //-------------------------------------------

    int nSel = m_Tab.GetCurSel();

    if (NULL != m_pLastDlg)
        m_pLastDlg->ShowWindow(SW_HIDE);

    switch (nSel)
    {
    case 0:
        {
            m_DlgKAD.ShowWindow(SW_SHOW);
            m_pLastDlg = &m_DlgKAD;
            break;
        }
/*	case 1:
        {
            m_DlgServer.ShowWindow(SW_SHOW);
            m_pLastDlg = &m_DlgServer;
            break;
        }
*/	case 2:
        {
            m_DlgSearch.ShowWindow(SW_SHOW);
            m_pLastDlg = &m_DlgSearch;
            break;
        }
    default: break;
    }
}

