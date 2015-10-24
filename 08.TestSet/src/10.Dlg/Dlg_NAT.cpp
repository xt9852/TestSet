// Dlg_NAT.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_NAT.h"
#include ".\dlg_nat.h"


//------------------------------------------------
//HHOOK my_list::ms_hHookOldMenuCbtFilter;
//my_list *my_list::m_p;
//------------------------------------------------


IMPLEMENT_DYNAMIC(CDlg_NAT, CDialog)
CDlg_NAT::CDlg_NAT(CWnd* pParent /*=NULL*/)
    : CDialog(CDlg_NAT::IDD, pParent),
    /*m_hdib(NULL),
    m_hdc(NULL),
    m_pbmpheader(NULL),*/
    m_bToServer(false)
{
}

CDlg_NAT::~CDlg_NAT()
{
}

void CDlg_NAT::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_NAT_LIST1, m_lstUser);
    DDX_Control(pDX, IDC_NAT_CHECK1, m_ccbIsServer);
}

BEGIN_MESSAGE_MAP(CDlg_NAT, CDialog)
    ON_WM_DESTROY()
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_NAT_LIST1, OnLvnItemchangedNatList1)
    ON_BN_CLICKED(IDC_NAT_BUT_START_SERVER, OnBnClickedButStartServer)
    ON_BN_CLICKED(IDC_NAT_BUT_START_CLIENT, OnBnClickedButStartClient)
    ON_BN_CLICKED(IDC_NAT_BUT_SEND, OnBnClickedNatButSendText)	
    ON_BN_CLICKED(IDC_NAT_BUT_TO_CLIENT, OnBnClickedNatButToClient)
    ON_BN_CLICKED(IDC_NAT_BUT_TO_SERVER, OnBnClickedNatButToServer)
END_MESSAGE_MAP()

BOOL CDlg_NAT::OnInitDialog()
{
    CDialog::OnInitDialog();

    //--------------------------------------------------------------

    CRect rcRect;
    this->GetParent()->GetClientRect(&rcRect);
    rcRect.top += 50;
    this->MoveWindow(&rcRect);

    //--------------------------------------------------------------

    GetDlgItem(IDC_NAT_IPADDRESS1)->SetWindowText(g_ProFile.getIp(0));
    GetDlgItem(IDC_NAT_EDIT_PORT)->SetWindowText("60000");
    GetDlgItem(IDC_NAT_BUT_START_CLIENT)->EnableWindow(FALSE);
    m_ccbIsServer.SetCheck(1);

    //--------------------------------------------------------------

    m_lstUser.SetExtendedStyle(m_lstUser.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    m_lstUser.InsertColumn(0, "用户ID",   0, 70);
    m_lstUser.InsertColumn(1, "公网IP",   0, 110);
    m_lstUser.InsertColumn(2, "公网端口", 0, 50);
    m_lstUser.InsertColumn(3, "私网IP",   0, 110);
    m_lstUser.InsertColumn(4, "私网端口", 0, 50);
    m_lstUser.InsertColumn(5, "连通状态", 0, 70);

    //--------------------------------------------------------------
/*
    m_hdc = this->GetDC()->m_hDC;
    m_hdib = ::DrawDibOpen();;

    CVideoCapture::Init(m_hdc, m_hdib);
    m_pbmpheader = CVideoCapture::GetBmpInfoHeader();

    //--------------------------------------------------------------

    m_h264.InitH264();

    //--------------------------------------------------------------

    CWaveIn::StartRec();
    m_WaveOut.StartPlay();

    m_DS.InitDirectSound(this->m_hWnd);
*/
    //--------------------------------------------------------------

    return TRUE;
}
/*
// 视频回调函数
void CDlg_NAT::ProcVideo(LPBYTE pbyData,int nLen)
{
    if (this->m_isOver || pbyData == NULL) return;

    ::DrawDibDraw(m_hdib,m_hdc,10,250,-1,-1,m_pbmpheader,pbyData,0,0,IMAGE_WIDTH,IMAGE_HEIGHT,DDF_SAME_DRAW);

    BYTE *pEnCodeData = NULL;
    WORD wEnCodeDataLen = 0;

    pEnCodeData = m_h264.Encode(pbyData, nLen, wEnCodeDataLen);

    bool bOk = true;

    if (m_bToServer)
        bOk = m_SrvNAT.U_SendVideo(0, PT_U_S_VIDEO, pEnCodeData, wEnCodeDataLen);
    else if (0 != m_dwCurSelUserId)
        bOk = m_SrvNAT.U_SendVideo(m_dwCurSelUserId, PT_U_U_VIDEO, pEnCodeData, wEnCodeDataLen);
    else
        bOk = false;

    if (!bOk)
    {
        GetDlgItem(IDC_NAT_BUT_TO_SERVER)->EnableWindow(TRUE);
        GetDlgItem(IDC_NAT_BUT_TO_CLIENT)->EnableWindow(TRUE);

        CVideoCapture::StopCapture();
        CWaveIn::CloseRecord();

        m_bToServer = false;
    }
}

void CDlg_NAT::ProcAudio(char *pszData, DWORD dwLen)
{
    bool bOk = true;

    if (m_bToServer)
        bOk = m_SrvNAT.U_SendAudio(0, PT_U_S_AUDIO, (UCHAR*)pszData, dwLen);
    else if (0 != m_dwCurSelUserId)
        bOk = m_SrvNAT.U_SendAudio(m_dwCurSelUserId, PT_U_U_AUDIO, (UCHAR*)pszData, dwLen);
    else
        bOk = false;

    if (!bOk)
    {
        GetDlgItem(IDC_NAT_BUT_TO_SERVER)->EnableWindow(TRUE);
        GetDlgItem(IDC_NAT_BUT_TO_CLIENT)->EnableWindow(TRUE);

        CVideoCapture::StopCapture();
        CWaveIn::CloseRecord();

        m_bToServer = false;
    }
}*/

void CDlg_NAT::ShowAudio(int nId, DWORD dwAudioId, LPBYTE pbyData, int nLen)
{
 //   m_DS.Play(nId, dwAudioId, pbyData, nLen);
    //m_WaveOut.Play(nId, (char*)pbyData, nLen);
}

void CDlg_NAT::OnBnClickedButStartServer()
{
    CString strIP;
    CString strPort;

    GetDlgItem(IDC_NAT_IPADDRESS1)->GetWindowText(strIP);
    GetDlgItem(IDC_NAT_EDIT_PORT)->GetWindowText(strPort);

/*    BYTE byRet = m_SrvNAT.Init(strIP, _ttoi(strPort), m_ccbIsServer.GetCheck(), this);

    if (0 == byRet)
    {
        GetDlgItem(IDC_NAT_BUT_START_SERVER)->EnableWindow(FALSE);
        GetDlgItem(IDC_NAT_BUT_START_CLIENT)->EnableWindow(TRUE);

        m_ccbIsServer.SetCheck(0);
    }
    else
    {
        CString msg;
        msg.Format(_T("Init IOCP Error\nErrorCode:%d"), byRet);
        MessageBox(msg);
    }*/
}

void CDlg_NAT::OnBnClickedButStartClient()
{
    CString strIP;
    CString strPort;

    GetDlgItem(IDC_NAT_IPADDRESS1)->GetWindowText(strIP);
    GetDlgItem(IDC_NAT_EDIT_PORT)->GetWindowText(strPort);

 /*   if (m_SrvNAT.U_LogonServer(strIP, _ttoi(strPort), 100, 1))
    {
        GetDlgItem(IDC_NAT_BUT_START_CLIENT)->EnableWindow(FALSE);
    }
    else
    {
        MessageBox(_T("错误"));
    }*/
}

void CDlg_NAT::OnBnClickedNatButSendText()
{
    CString strIP;
    CString strPort;
    CString strText;

    GetDlgItem(IDC_NAT_IPADDRESS1)->GetWindowText(strIP);
    GetDlgItem(IDC_NAT_EDIT_PORT)->GetWindowText(strPort);
    GetDlgItem(IDC_NAT_EDIT_TEXT)->GetWindowText(strText);

 /*   if (!m_SrvNAT.U_SendText(strIP, _ttoi(strPort), strText))
    {
        MessageBox(_T("错误"));
    }*/
}

void CDlg_NAT::OnDestroy()
{
 /*   CVideoCapture::StopCapture();
    CWaveIn::StopRec();

    m_WaveOut.StopPlay();
*/
    CDialog::OnDestroy();	
}

void CDlg_NAT::OnBnClickedNatButToClient()
{
    GetDlgItem(IDC_NAT_BUT_TO_SERVER)->EnableWindow(FALSE);
    GetDlgItem(IDC_NAT_BUT_TO_CLIENT)->EnableWindow(FALSE);

 //   CVideoCapture::StartCapture();
 //   CWaveIn::OpenRecord();
}

void CDlg_NAT::OnBnClickedNatButToServer()
{
    GetDlgItem(IDC_NAT_BUT_TO_SERVER)->EnableWindow(FALSE);
    GetDlgItem(IDC_NAT_BUT_TO_CLIENT)->EnableWindow(FALSE);

    m_bToServer = true;

//    CVideoCapture::StartCapture();
//    CWaveIn::OpenRecord();
}

void CDlg_NAT::OnLvnItemchangedNatList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    *pResult = 0;

    CString strUserID = m_lstUser.GetItemText(pNMLV->iItem, 0);

    m_dwCurSelUserId = _ttoi(strUserID);
}

