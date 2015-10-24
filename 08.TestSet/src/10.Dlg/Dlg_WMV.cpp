
#include "stdafx.h"
#include "Dlg_WMV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern UINT WM_GRAPHNOTIFY;


IMPLEMENT_DYNAMIC(CDlg_WMV, CDialog)
CDlg_WMV::CDlg_WMV(CWnd* pParent /*=NULL*/)
    : CDialog(CDlg_WMV::IDD, pParent),
    m_hThread(NULL)
{
}

CDlg_WMV::~CDlg_WMV()
{
}

void CDlg_WMV::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_WMV, CDialog)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_WMV_BTN_OPEN, OnBnClickedWmvBtnOpen)
    ON_BN_CLICKED(IDC_WMV_BTN_START, OnBnClickedWmvBtnStart)
    ON_BN_CLICKED(IDC_WMV_BTN_PAUSE, OnBnClickedWmvBtnPause)
    ON_BN_CLICKED(IDC_WMV_BTN_STOP, OnBnClickedWmvBtnStop)
    ON_BN_CLICKED(IDC_WMV_BTN_SOUND, OnBnClickedWmvBtnSound)
    ON_BN_CLICKED(IDC_WMV_BTN_SIZE, OnBnClickedWmvBtnSize)	
    ON_BN_CLICKED(IDC_WMV_BTN_STREAM, OnBnClickedWmvBtnStream)
    ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, GraphEvent)
END_MESSAGE_MAP()


BOOL CDlg_WMV::OnInitDialog()
{
    CDialog::OnInitDialog();

    GetDlgItem(IDC_WMV_EDIT)->SetWindowText(_T("8080"));

    //---------------------------------------------------------

    return TRUE;
}

void CDlg_WMV::OnBnClickedWmvBtnOpen()
{
    CFileDialog FileDlg(TRUE, NULL, NULL, NULL, FILE_FILTER_TEXT);

    if(FileDlg.DoModal()==IDOK)
    {
        m_strFileName = FileDlg.GetPathName();
    }
}

void CDlg_WMV::OnBnClickedWmvBtnStart()
{
    m_PlayWmv.PlayMovieInWindow(this->GetSafeHwnd(), (LPTSTR)(LPCTSTR)m_strFileName);
}

void CDlg_WMV::OnBnClickedWmvBtnPause()
{
    m_PlayWmv.PauseClip();
}

void CDlg_WMV::OnBnClickedWmvBtnStop()
{
    m_PlayWmv.StopClip();
}

void CDlg_WMV::OnBnClickedWmvBtnSound()
{
    m_PlayWmv.ToggleMute();
}

void CDlg_WMV::OnBnClickedWmvBtnSize()
{
    m_PlayWmv.SetSize(50, 50, 300, 300);
}

LRESULT CDlg_WMV::GraphEvent(WPARAM,LPARAM)
{
    m_PlayWmv.HandleGraphEvent();
    return 0;
}

void CDlg_WMV::OnDestroy()
{
    m_PlayWmv.CloseClip();

    //----------------------------------------------------------------------

    m_StreamWmv.Release();
    if (m_hThread != NULL )
    {
        int i = 10;
        for (; i > 0; i--)
        {
            DWORD nCode;
            if (!GetExitCodeThread(m_hThread, &nCode)) break;
            if (nCode != STILL_ACTIVE) break;
            Sleep(0);
        }

        if (i == 0)
        {
            TerminateThread(m_hThread, 0);
            TRACE(_T("WARNING: Terminating WMVStreamThread.\n"));
            Sleep(0);
        }

        CloseHandle(m_hThread);
    }
    //----------------------------------------------------------------------

    CDialog::OnDestroy();
}

HRESULT ConvertTCharToWChar(TCHAR *ptszInput, WCHAR **ppwszOutput)
{
    int cchOutput = 0;

    if (NULL == ptszInput || NULL == ppwszOutput)
    {
        return (E_INVALIDARG);
    }

    //
    // Get the size needed for the output buffer.
    //
#ifdef UNICODE
    cchOutput = wcslen(ptszInput) + 1;
#else //UNICODE
    cchOutput = MultiByteToWideChar(CP_ACP, 0, ptszInput, -1, NULL, 0);
    if (0 == cchOutput)
    {
        return (HRESULT_FROM_WIN32(GetLastError()));
    }
#endif// UNICODE

    // Allocate the buffer.
    *ppwszOutput = new WCHAR[cchOutput];
    if (NULL == *ppwszOutput)
    {
        return (E_OUTOFMEMORY);
    }

    // Convert the input string. 

#ifdef UNICODE
    wcsncpy(*ppwszOutput, ptszInput, cchOutput);
#else //UNICODE
    if (0 == MultiByteToWideChar(CP_ACP, 0, ptszInput, -1, *ppwszOutput, cchOutput))
    {
        if (*ppwszOutput)
        {
            delete *ppwszOutput;
            *ppwszOutput = NULL;
        }

        return (HRESULT_FROM_WIN32(GetLastError()));
    }        
#endif// UNICODE

    return (S_OK);
}


void CDlg_WMV::OnBnClickedWmvBtnStream()
{
    if (NULL != m_hThread)
        TerminateThread(m_hThread, 0);

    UINT nThreadID = 0;
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, WMVStreamThread, (void*)this, 0, &nThreadID);
}

unsigned CDlg_WMV::WMVStreamThread(LPVOID pParam)
{
    CDlg_WMV *pthis = (CDlg_WMV*)pParam;

    CString strPort;
    pthis->GetDlgItem(IDC_WMV_EDIT)->GetWindowText(strPort);

    HRESULT hr = S_OK;
    WCHAR *pwszFile = NULL;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    do
    {
        hr = ConvertTCharToWChar((LPSTR)(LPCTSTR)pthis->m_strFileName, &pwszFile);
        if (FAILED(hr))
            break;

        // Initialize our helper object.
        hr = pthis->m_StreamWmv.Init();
        if (FAILED(hr))
            break;

        // Configure the helper object with the port number, file name, maximum
        // number of clients, and server URL.
        hr = pthis->m_StreamWmv.Configure(_ttoi(strPort), pwszFile, 10, NULL);
        if (FAILED(hr))
            break;

        // Write all of the samples to the network.
        hr = pthis->m_StreamWmv.WritetoNet();
        if (FAILED(hr))
            break;
    }
    while(FALSE);


    TRACE(_T("WMVStreamThread exit\n"));
    return 0;
}
