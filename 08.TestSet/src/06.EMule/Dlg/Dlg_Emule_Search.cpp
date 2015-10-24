// Dlg_Emule_Search.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_Emule_Search.h"
// #include "emule\kademlia\kademlia\Kademlia.h"
// #include "eMule\kademlia\kademlia\SearchManager.h"

// CDlg_Emule_KAD 对话框

IMPLEMENT_DYNAMIC(CDlg_Emule_Search, CDialog)
CDlg_Emule_Search::CDlg_Emule_Search(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Emule_Search::IDD, pParent)
{
}

CDlg_Emule_Search::~CDlg_Emule_Search()
{
}

void CDlg_Emule_Search::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    /*
    DDX_Control(pDX, IDC_KAD_CONTACTLIST, m_ContactListCtrl);
    DDX_Control(pDX, IDC_KAD_SECRET_MSG, m_SearchListCtrl);
    DDX_Control(pDX, IDC_KAD_KAD_HISTOGRAM, m_HistogramCtrl);
    */
}


BEGIN_MESSAGE_MAP(CDlg_Emule_Search, CDialog)
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_EMULE_SEARCH_BTN_START, OnBnClickedSearchBtnStart)
END_MESSAGE_MAP()


BOOL CDlg_Emule_Search::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;
}
/*
void CDlg_Emule_Search::OnBnClickedBootstrapbutton()
{
CString strIP;
uint16 nPort = 0;

CString strMyIp;
uint16 nMyTcpPort = 0;
uint16 nMyUdpPort = 0;

if (!IsDlgButtonChecked(IDC_KAD_RADCLIENTS))
{
GetDlgItem(IDC_KAD_BOOTSTRAPIP)->GetWindowText(strIP);
strIP.Trim();

int iPos;
if ((iPos = strIP.Find(_T(':'))) != -1)
{
GetDlgItem(IDC_KAD_BOOTSTRAPPORT)->SetWindowText(strIP.Mid(iPos+1));
strIP = strIP.Left(iPos);
GetDlgItem(IDC_KAD_BOOTSTRAPIP)->SetWindowText(strIP);
}

CString strPort;
GetDlgItem(IDC_KAD_BOOTSTRAPPORT)->GetWindowText(strPort);
strPort.Trim();
nPort = (uint16)_ttoi(strPort);

GetDlgItem(IDC_KAD_MYIP)->GetWindowText(strMyIp);
strMyIp.Trim();

GetDlgItem(IDC_KAD_MYTCPPORT)->GetWindowText(strPort);
strPort.Trim();
nMyTcpPort = (uint16)_ttoi(strPort);

GetDlgItem(IDC_KAD_MYUDPPORT)->GetWindowText(strPort);
strPort.Trim();
nMyUdpPort = (uint16)_ttoi(strPort);
}

if (!Kademlia::CKademlia::IsRunning())
{
Kademlia::CKademlia::Start(&m_ContactListCtrl,
&m_SearchListCtrl,
&m_HistogramCtrl,
&m_IP2Country,
(LPCTSTR)strMyIp,
nMyTcpPort,
nMyUdpPort);

this->SetTimer(0, 1000, NULL);
}
if (!strIP.IsEmpty() && nPort)
{
Kademlia::CKademlia::Bootstrap(strIP, nPort, true);
}
}
*/
void CDlg_Emule_Search::OnTimer(UINT nIDEvent)
{
    /*	int nContactCount = Kademlia::CKademlia::GetListCtrl()->GetItemCount();
    int nSearchCount = Kademlia::CKademlia::GetSearchListCtrl()->GetItemCount();

    CString strText;
    strText.Format(_T("Contacts (%d)"), nContactCount);
    this->GetDlgItem(IDC_KAD_KADCONTACTLAB)->SetWindowText(strText);

    strText.Format(_T("Current Searches (%d)"), nSearchCount);
    this->GetDlgItem(IDC_KAD_KADSEARCHLAB)->SetWindowText(strText);

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

    */	CDialog::OnTimer(nIDEvent);
}


void CDlg_Emule_Search::OnDestroy()
{
    /*	Kademlia::CKademlia::Stop();

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
/*
long CDlg_Emule_KAD::OnIp2CountryNotify(WPARAM wParam, LPARAM lParam)
{
if (100 == wParam)
{
GetDlgItem(IDC_KAD_BOOTSTRAPBUTTON)->SetWindowText(_T("BootStrap"));
GetDlgItem(IDC_KAD_BOOTSTRAPBUTTON)->EnableWindow();
}
else
{
CString strText;
strText.Format(_T("IpToCountry %d%%"), wParam);
GetDlgItem(IDC_KAD_BOOTSTRAPBUTTON)->SetWindowText(strText);
}
return 0;
}
*/

void CDlg_Emule_Search::OnBnClickedSearchBtnStart()
{
    /*	SSearchParams* pParams = new SSearchParams;
    pParams->strExpression = this->GetDlgItem(IDC_SEARCH_FILTER)->GetWindowText();
    pParams->eType = (ESearchType)m_ctlMethod.GetCurSel();
    pParams->strFileType = strFileType;
    pParams->strMinSize = strMinSize;
    pParams->ullMinSize = ullMinSize;
    pParams->strMaxSize = strMaxSize;
    pParams->ullMaxSize = ullMaxSize;
    pParams->uAvailability = uAvailability;
    pParams->strExtension = strExtension;
    //pParams->bMatchKeywords = IsDlgButtonChecked(IDC_MATCH_KEYWORDS)!=0;
    pParams->uComplete = uComplete;
    pParams->strCodec = strCodec;
    pParams->ulMinBitrate = ulMinBitrate;
    pParams->ulMinLength = ulMinLength;
    if ((m_ctlOpts.GetItemData(orTitle) & 1) == 0)
    {
    pParams->strTitle = m_ctlOpts.GetItemText(orTitle, 1);
    pParams->strTitle.Trim();
    }
    if ((m_ctlOpts.GetItemData(orAlbum) & 1) == 0)
    {
    pParams->strAlbum = m_ctlOpts.GetItemText(orAlbum, 1);
    pParams->strAlbum.Trim();
    }
    if ((m_ctlOpts.GetItemData(orArtist) & 1) == 0)
    {
    pParams->strArtist = m_ctlOpts.GetItemText(orArtist, 1);
    pParams->strArtist.Trim();
    }
    pParams->bUnicode = bUnicode;

    CSafeMemFile data(100);
    if (!GetSearchPacket(&data, pParams, true, NULL)// || (!pParams->strBooleanExpr.IsEmpty() && data.GetLength() == 0)/)
    return false;

    LPBYTE pSearchTermsData = NULL;
    UINT uSearchTermsSize = (UINT)data.GetLength();
    if (uSearchTermsSize){
    pSearchTermsData = new BYTE[uSearchTermsSize];
    data.SeekToBegin();
    data.Read(pSearchTermsData, uSearchTermsSize);
    }
    */
/*
    if (!Kademlia::CKademlia::IsRunning()) return;

    CString strKeyword;
    GetDlgItem(IDC_EMULE_SEARCH_FILTER)->GetWindowText(strKeyword);
    try
    {
        Kademlia::CSearchManager::PrepareFindKeywords(true, strKeyword, 0, NULL);
    }
    catch (CString strException)
    {
        TRACE(_T("PrepareFindKeywords Error:%d\n"), ::GetLastError());
    }*/
}
