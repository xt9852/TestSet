// src\Dlg\Dlg_Skin.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_Encode_Cfg.h"
#include ".\dlg_encode_cfg.h"

// CDlg_Skin 对话框

IMPLEMENT_DYNAMIC(CDlg_Encode_Cfg, CDialog)
CDlg_Encode_Cfg::CDlg_Encode_Cfg(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Encode_Cfg::IDD, pParent)
{
}

CDlg_Encode_Cfg::~CDlg_Encode_Cfg()
{
}

void CDlg_Encode_Cfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ENCODE_PROPSHELLCTRLConfig, m_PropShellConfig);
}

BEGIN_MESSAGE_MAP(CDlg_Encode_Cfg, CDialog)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CDlg_Encode_Cfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    //----------------------------------------------------------------------

    try
    {
        IUnknown* pSourcesPage;
        IUnknown* pDescriptionPage;
        IUnknown* pAttributesPage;
        IUnknown* pEncodingPage;
        IUnknown* pOutputPage;	

        m_PropShellConfig.GetControlUnknown()->QueryInterface(IID_IMSPropShell,(void**)&pPropShell);
        HRESULT hrSrc=CoCreateInstance(CLSID_WMEncSourcesAltPage,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,(void**)&pSourcesPage);
        HRESULT hrDesc=CoCreateInstance(CLSID_WMEncDisplayInfoPage,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,(void**)&pDescriptionPage);
        HRESULT hrAttr=CoCreateInstance(CLSID_WMEncAttributesPage,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,(void**)&pAttributesPage);
        HRESULT hrEnc=CoCreateInstance(CLSID_WMEncProfilePage,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,(void**)&pEncodingPage);
        HRESULT hrOut=CoCreateInstance(CLSID_WMEncOutputPage,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,(void**)&pOutputPage);	

        pPropShell->AddObject(m_pEncoder);
        pPropShell->AddPage(pSourcesPage);
        pPropShell->AddPage(pDescriptionPage);
        pPropShell->AddPage(pAttributesPage);
        pPropShell->AddPage(pEncodingPage);
        pPropShell->AddPage(pOutputPage);	

        pSourcesPage->Release();
        pDescriptionPage->Release();
        pAttributesPage->Release();
        pEncodingPage->Release();
        pOutputPage->Release();
    }
    catch(...)
    {
        MessageBox(_T("Error"));
    }

    //----------------------------------------------------------------------

    return TRUE;
}

void CDlg_Encode_Cfg::SetEncoder(IWMEncoder* pEncoder)
{
    m_pEncoder = pEncoder;
}

void CDlg_Encode_Cfg::OnBnClickedOk()
{
    pPropShell->Apply();
    m_pEncoder->PrepareToEncode(TRUE);
    pPropShell->Release();

    OnOK();
}

void CDlg_Encode_Cfg::OnBnClickedCancel()
{
    pPropShell->Release();

    OnCancel();
}
