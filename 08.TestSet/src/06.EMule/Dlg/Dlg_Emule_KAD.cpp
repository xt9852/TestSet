// Dlg_Emule_KAD.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_Emule_KAD.h"
//#include "emule\kademlia\kademlia\Kademlia.h"


// IP地址到物理地址类准备好
/*extern*/ UINT WM_IP2COUNTRY_NOTIFY;


IMPLEMENT_DYNAMIC(CDlg_Emule_KAD, CDialog)
CDlg_Emule_KAD::CDlg_Emule_KAD(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Emule_KAD::IDD, pParent)
{
}

CDlg_Emule_KAD::~CDlg_Emule_KAD()
{
}

void CDlg_Emule_KAD::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

//     DDX_Control(pDX, IDC_EMULE_KAD_CONTACTLIST, m_ContactListCtrl);
//     DDX_Control(pDX, IDC_EMULE_KAD_SECRET_MSG, m_SearchListCtrl);
//     DDX_Control(pDX, IDC_EMULE_KAD_KAD_HISTOGRAM, m_HistogramCtrl);
}


BEGIN_MESSAGE_MAP(CDlg_Emule_KAD, CDialog)
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_REGISTERED_MESSAGE(WM_IP2COUNTRY_NOTIFY, OnIp2CountryNotify)
    ON_BN_CLICKED(IDC_EMULE_KAD_BOOTSTRAPBUTTON, OnBnClickedBootstrapbutton)
	ON_BN_CLICKED(IDC_EMULE_KAD_STOP, OnBnClickedKadStop)
END_MESSAGE_MAP()


BOOL CDlg_Emule_KAD::OnInitDialog()
{
    CDialog::OnInitDialog();

    //-------------------------------------------------------------------------

//     m_IP2Country.SetOwner(this->GetSafeHwnd());
// 
//     GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPBUTTON)->EnableWindow(FALSE);
// 
//     GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPIP)->SetWindowText(_T("211.100.28.61"));
//     GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPPORT)->SetWindowText(_T("5154"));
// 
//     GetDlgItem(IDC_EMULE_KAD_KADICO1)->ShowWindow(SW_HIDE);
//     GetDlgItem(IDC_EMULE_KAD_KADICO2)->ShowWindow(SW_HIDE);
// 
//     GetDlgItem(IDC_EMULE_KAD_MYIP)->SetWindowText(g_ProFile.m_strIP);
//     GetDlgItem(IDC_EMULE_KAD_MYTCPPORT)->SetWindowText(_T("4501"));
//     GetDlgItem(IDC_EMULE_KAD_MYUDPPORT)->SetWindowText(_T("4501"));
// 
//     m_ContactListCtrl.Init();
//     m_SearchListCtrl.Init();
// 
//     m_ContactListCtrl.SetImageList(m_IP2Country.GetFlagImageList(), g_ProFile.GetImageList());
//     m_SearchListCtrl.ApplyImageList(g_ProFile.GetImageList()->m_hImageList);
// 
//     Kademlia::CKademlia::m_strCofigPath = g_ProFile.m_strCurPath + _T("\\res\\eMule\\");

    return TRUE;
}

void CDlg_Emule_KAD::OnBnClickedBootstrapbutton()
{/*
    CString strIP;
    uint16 nPort = 0;

    CString strMyIp;
    uint16 nMyTcpPort = 0;
    uint16 nMyUdpPort = 0;

    if (!IsDlgButtonChecked(IDC_EMULE_KAD_RADCLIENTS))
    {
        GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPIP)->GetWindowText(strIP);
        strIP.Trim();

        int iPos;
        if ((iPos = strIP.Find(_T(':'))) != -1)
        {
            GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPPORT)->SetWindowText(strIP.Mid(iPos+1));
            strIP = strIP.Left(iPos);
            GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPIP)->SetWindowText(strIP);
        }

        CString strPort;
        GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPPORT)->GetWindowText(strPort);
        strPort.Trim();
        nPort = (uint16)_ttoi(strPort);

        GetDlgItem(IDC_EMULE_KAD_MYIP)->GetWindowText(strMyIp);
        strMyIp.Trim();

        GetDlgItem(IDC_EMULE_KAD_MYTCPPORT)->GetWindowText(strPort);
        strPort.Trim();
        nMyTcpPort = (uint16)_ttoi(strPort);

        GetDlgItem(IDC_EMULE_KAD_MYUDPPORT)->GetWindowText(strPort);
        strPort.Trim();
        nMyUdpPort = (uint16)_ttoi(strPort);
    }

    if (!Kademlia::CKademlia::IsRunning())
    {
        if (Kademlia::CKademlia::Start(&m_ContactListCtrl,
            &m_SearchListCtrl,
            &m_HistogramCtrl,
            &m_IP2Country,
            (LPCTSTR)strMyIp,
            nMyTcpPort,
            nMyUdpPort))

        this->SetTimer(0, 1000, NULL);
    }
    if (!strIP.IsEmpty() && nPort)
    {
        Kademlia::CKademlia::Bootstrap(strIP, nPort, true);
    }*/
}

void CDlg_Emule_KAD::OnTimer(UINT nIDEvent)
{/*
    int nContactCount = Kademlia::CKademlia::GetListCtrl()->GetItemCount();
    int nSearchCount = Kademlia::CKademlia::GetSearchListCtrl()->GetItemCount();

    CString strText;
    strText.Format(_T("Contacts (%d)"), nContactCount);
    this->GetDlgItem(IDC_EMULE_KAD_KADCONTACTLAB)->SetWindowText(strText);

    strText.Format(_T("Current Searches (%d)"), nSearchCount);
    this->GetDlgItem(IDC_EMULE_KAD_KADSEARCHLAB)->SetWindowText(strText);

    m_HistogramCtrl.Localize();

    if (Kademlia::CKademlia::IsRunning())
    {
        Kademlia::CKademlia::Process();
        if( Kademlia::CKademlia::GetPrefs()->HasLostConnection())
        {
            Kademlia::CKademlia::Stop();
            TRACE(_T("Kademlia::CKademlia::Stop\n"));
        }
    }
	*/
    CDialog::OnTimer(nIDEvent);
}


void CDlg_Emule_KAD::OnDestroy()
{
	this->OnBnClickedKadStop();
/*
    m_ContactListCtrl.DeleteAllItems();
    m_ContactListCtrl.ShowWindow(SW_HIDE);
    m_ContactListCtrl.DestroyWindow();

    m_SearchListCtrl.DeleteAllItems();
    m_SearchListCtrl.ShowWindow(SW_HIDE);
    m_SearchListCtrl.DestroyWindow();

    m_HistogramCtrl.ShowWindow(SW_HIDE);
    m_HistogramCtrl.DestroyWindow();
	*/
    CDialog::OnDestroy();
}

long CDlg_Emule_KAD::OnIp2CountryNotify(WPARAM wParam, LPARAM lParam)
{/*
    if (100 == wParam)
    {
        GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPBUTTON)->SetWindowText(_T("BootStrap"));
        GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPBUTTON)->EnableWindow();
    }
    else
    {
        CString strText;
        strText.Format(_T("IpToCountry %d%%"), wParam*2);
        GetDlgItem(IDC_EMULE_KAD_BOOTSTRAPBUTTON)->SetWindowText(strText);
    }*/
    return 0;
}


void CDlg_Emule_KAD::OnBnClickedKadStop()
{
	this->KillTimer(0);
	//if (Kademlia::CKademlia::IsRunning()) Kademlia::CKademlia::Stop();
}
