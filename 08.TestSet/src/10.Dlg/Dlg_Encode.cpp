// Dlg_Encode.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_Encode.h"
#include ".\dlg_encode.h"


// CDlg_DB 对话框

IMPLEMENT_DYNAMIC(CDlg_Encode, CDialog)
CDlg_Encode::CDlg_Encode(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Encode::IDD, pParent)
{
}

CDlg_Encode::~CDlg_Encode()
{
    m_pEncoder->Release();
}

void CDlg_Encode::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ENCODE_PROPSHELLCTRL, m_PropShell);
}


BEGIN_MESSAGE_MAP(CDlg_Encode, CDialog)
    ON_BN_CLICKED(IDC_ENCODE_CONFIGURE, OnBnClickedEncodeConfigure)
    ON_BN_CLICKED(IDC_ENCODE_START, OnBnClickedEncodeStart)
    ON_BN_CLICKED(IDC_ENCODE_STOP, OnBnClickedEncodeStop)
END_MESSAGE_MAP()


BOOL CDlg_Encode::OnInitDialog()
{
    CDialog::OnInitDialog();

    //-----------------------------------------------------------------

    IUnknown* pMainPage;
    IMSPropShell* pPropShell;

    m_PropShell.GetControlUnknown()->QueryInterface(IID_IMSPropShell, (void**)&pPropShell);
    HRESULT hr = CoCreateInstance(CLSID_WMEncMonMainPage, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pMainPage);
    HRESULT hr1 = CoCreateInstance(CLSID_WMEncoder, NULL, CLSCTX_INPROC_SERVER, IID_IWMEncoder, (void**)&m_pEncoder);

    pPropShell->AddObject(m_pEncoder);
    pPropShell->AddPage(pMainPage);

    pMainPage->Release();
    pPropShell->Release();

    //-----------------------------------------------------------------

    return TRUE;
}

void CDlg_Encode::OnBnClickedEncodeConfigure()
{
    CDlg_Encode_Cfg ConfigDlg;
    ConfigDlg.SetEncoder(m_pEncoder);
    ConfigDlg.DoModal();
}

void CDlg_Encode::OnBnClickedEncodeStart()
{
    m_pEncoder->Start();
}

void CDlg_Encode::OnBnClickedEncodeStop()
{
    WMENC_ENCODER_STATE EncoderState;
    m_pEncoder->get_RunState(&EncoderState);
    //TCHAR szBuffer[64];
    //wsprintf( szBuffer, _T("%d"), EncoderState ); 
    //AfxMessageBox(szBuffer);
    if ((EncoderState==WMENC_ENCODER_RUNNING)||(EncoderState==WMENC_ENCODER_PAUSED))
    {		
        m_pEncoder->Stop();	
    }
}

