
#include "stdafx.h"
#include "Dlg_WMEncode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CDlg_WMEncode, CDialog)
CDlg_WMEncode::CDlg_WMEncode(CWnd* pParent /*=NULL*/)
    : CDialog(CDlg_WMEncode::IDD, pParent)
{
}

CDlg_WMEncode::~CDlg_WMEncode()
{
}

void CDlg_WMEncode::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_WMENCODE_EDIT_VIDEO_FILE, m_edVideoFile);
    DDX_Control(pDX, IDC_WMENCODE_EDIT_AUDIO_FILE, m_edAudioFile);
    DDX_Control(pDX, IDC_WMENCODE_AUDIO_DEV, m_cbbAudioDev);
    DDX_Control(pDX, IDC_WMENCODE_VIDEO_DEV, m_cbbVideoDev);
    DDX_Control(pDX, IDC_WMENCODE_PROFILE, m_cbbProfile);
}


BEGIN_MESSAGE_MAP(CDlg_WMEncode, CDialog)
    ON_BN_CLICKED(IDC_WMENCODE_BTN_CAPTURE_PARAM, OnBtnCaptureParam)
    ON_BN_CLICKED(IDC_WMENCODE_BTN_START_CAPTURE, OnBtnStartCapture)
    ON_BN_CLICKED(IDC_WMENCODE_BTN_SAVE_PROFILE, OnBtnSaveProfile)
END_MESSAGE_MAP()

BOOL CDlg_WMEncode::OnInitDialog()
{
    CDialog::OnInitDialog();

    //-------------------------------------------------------------------
    m_edAudioFile.SetWindowText(_T("F:\\music\\1.wav"));
    m_edVideoFile.SetWindowText(_T("F:\\music\\123.asf"));

    GetDlgItem(IDC_WMENCODE_EDIT_OUTPUT_FILE)->SetWindowText(_T("output.wmv"));
    GetDlgItem(IDC_WMENCODE_EDIT_PORT)->SetWindowText(_T("6600"));

    m_WMEncode.Init(&m_cbbAudioDev,
                    &m_cbbVideoDev,
                    &m_cbbProfile,
                    GetDlgItem(IDC_WMENCODE_PREVIEW)->GetSafeHwnd(),
                    GetDlgItem(IDC_WMENCODE_POSTVIEW)->GetSafeHwnd());

    m_WMEncode.GetParam();

    return TRUE;
}

void CDlg_WMEncode::OnBtnCaptureParam() 
{
    m_WMEncode.GetParam();
}

void CDlg_WMEncode::OnBtnStartCapture() 
{
    CString strVideoDevName;
    CString strAudioDevName;
    CString strVideoFile;
    CString strAudioFile;
    CString strOutFileName;
    CString strPort;

    m_cbbVideoDev.GetWindowText(strVideoDevName);
    if (strVideoDevName == _T(""))
    {
        AfxMessageBox(_T("未选择视频设备"));
        return;
    }

    m_cbbAudioDev.GetWindowText(strAudioDevName);
    if (strAudioDevName == _T(""))
    {
        AfxMessageBox(_T("未选择音频设备"));
        return;
    }

    m_edVideoFile.GetWindowText(strVideoFile);
    m_edAudioFile.GetWindowText(strAudioFile);

    GetDlgItem(IDC_WMENCODE_EDIT_OUTPUT_FILE)->GetWindowText(strOutFileName);
    GetDlgItem(IDC_WMENCODE_EDIT_PORT)->GetWindowText(strPort);

    m_WMEncode.StartCaption(strVideoDevName,
        strAudioDevName,
        m_cbbProfile.GetCurSel(),
        _ttoi(strPort),
        strVideoFile,
        strAudioFile,
        strOutFileName
        );

}

void CDlg_WMEncode::OnBtnSaveProfile() 
{
}


