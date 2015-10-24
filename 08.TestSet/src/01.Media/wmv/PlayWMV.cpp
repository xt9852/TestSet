
#include "stdafx.h"
#include "PlayWMV.h"

#pragma comment(lib,"../lib/wmv/strmiids.lib")	// VS2003×Ô´øµÄ
#pragma comment(lib,"../lib/wmv/WMVCORE.lib")


UINT WM_GRAPHNOTIFY = RegisterWindowMessage(_T("WM_GRAPHNOTIFY"));


CPlayWMV::CPlayWMV()
    :m_hWnd(NULL),
    m_bAudioOnly(FALSE),
    m_bFullscreen(FALSE),
    m_lVolume(VOLUME_FULL),
    m_nPlayState(Stopped),
    m_pGB(NULL),
    m_pMC(NULL),
    m_pME(NULL),
    m_pVW(NULL),
    m_pBA(NULL),
    m_pBV(NULL),
    m_pMS(NULL)
{
    m_Rect.left = 50;
    m_Rect.top = 50;
    m_Rect.right = 150;
    m_Rect.bottom = 150;
}
CPlayWMV::~CPlayWMV()
{}

HRESULT CPlayWMV::PlayMovieInWindow(HWND hWnd, LPTSTR szFile)
{
    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        Msg(TEXT("CoInitialize Failed!\r\n"));
        return 0;
    }

    USES_CONVERSION;
    WCHAR wFile[MAX_PATH];
    HRESULT hr;

    // Check input string
    if (!szFile)
        return E_POINTER;

    m_hWnd = hWnd;

    // Clear open dialog remnants before calling RenderFile()
    UpdateWindow(m_hWnd);

    // Convert filename to wide character string
    wcsncpy(wFile, T2W(szFile), NUMELMS(wFile)-1);
    wFile[MAX_PATH-1] = 0;

    // Get the interface for DirectShow's GraphBuilder
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
        IID_IGraphBuilder, (void **)&m_pGB));

    // Get the media event interface before building the graph
    JIF(m_pGB->QueryInterface(IID_IMediaEventEx, (void **)&m_pME));

    // Have the graph builder construct the appropriate graph automatically
    JIF(m_pGB->RenderFile(wFile, NULL));

    if (SUCCEEDED(hr))
    {
        // QueryInterface for DirectShow interfaces
        JIF(m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC));
        JIF(m_pGB->QueryInterface(IID_IMediaSeeking, (void **)&m_pMS));

        // Query for video interfaces, which may not be relevant for audio files
        JIF(m_pGB->QueryInterface(IID_IVideoWindow, (void **)&m_pVW));
        JIF(m_pGB->QueryInterface(IID_IBasicVideo,  (void **)&m_pBV));

        // Query for audio interfaces, which may not be relevant for video-only files
        JIF(m_pGB->QueryInterface(IID_IBasicAudio, (void **)&m_pBA));

        // Have the graph signal event via window callbacks for performance
        JIF(m_pME->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0));

        // Is this an audio-only file (no video component)?
        CheckVisibility();

        if (!m_bAudioOnly)
        {
            // Setup the video window
            JIF(m_pVW->put_Owner((OAHWND)m_hWnd));
            JIF(m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN));
            JIF(m_pVW->SetWindowPosition(m_Rect.left, 
                m_Rect.top, m_Rect.right, m_Rect.bottom));
        }
        else
        {
            // Initialize the default player window and enable playback menu items
            // that don't involve manipulating video size
            //JIF(InitPlayerWindow());
            /*
            BOOL bRet = SetWindowPos(m_hWnd, NULL, 0, 0,
            DEFAULT_AUDIO_WIDTH,
            DEFAULT_AUDIO_HEIGHT,
            SWP_NOMOVE | SWP_NOOWNERZORDER);
            */
        }

        // Complete window initialization
        //ShowWindow(m_hWnd, SW_SHOWNORMAL);
        //UpdateWindow(m_hWnd);
        //SetForegroundWindow(m_hWnd);
        m_bFullscreen = FALSE;

        // Run the graph to play the media file
        JIF(m_pMC->Run());

        m_nPlayState = Running;

        SetFocus(m_hWnd);
    }

    return hr;
}


void CPlayWMV::CheckVisibility(void)
{
    long lVisible;
    HRESULT hr;

    if ((!m_pVW) || (!m_pBV))
    {
        // Audio-only files have no video interfaces.  This might also
        // be a file whose video component uses an unknown video codec.
        m_bAudioOnly = TRUE;
        return;
    }
    else
    {
        // Clear the global flag
        m_bAudioOnly = FALSE;
    }

    hr = m_pVW->get_Visible(&lVisible);
    if (FAILED(hr))
    {
        // If this is an audio-only clip, get_Visible() won't work.
        if (hr == E_NOINTERFACE)
        {
            m_bAudioOnly = TRUE;
        }
        else
        {
            Msg(TEXT("Failed(%08lx) in pVW->get_Visible()!\r\n"), hr);
        }
    }
}

void CPlayWMV::PauseClip(void)
{
    if (!m_pMC)
        return;

    if((m_nPlayState == Paused) || (m_nPlayState == Stopped))
    {
        if (SUCCEEDED(m_pMC->Run()))
            m_nPlayState = Running;
    }
    else
    {
        if (SUCCEEDED(m_pMC->Pause()))
            m_nPlayState = Paused;
    }
}

void CPlayWMV::StopClip(void)
{
    HRESULT hr;

    if ((!m_pMC) || (!m_pMS))
        return;

    // Stop and reset position to beginning
    if((m_nPlayState == Paused) || (m_nPlayState == Running))
    {
        hr = m_pMC->Stop();
        m_nPlayState = Stopped;

        // Seek to the beginning
        LONGLONG pos = 0;
        hr = m_pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning,
            NULL, AM_SEEKING_NoPositioning);

        // Display the first frame to indicate the reset condition
        hr = m_pMC->Pause();
    }
}

void CPlayWMV::CloseClip()
{
    HRESULT hr;

    // Stop media playback
    if (m_pMC)
        hr =m_pMC->Stop();

    // Clear global flags
    m_nPlayState = Stopped;
    m_bAudioOnly = TRUE;
    m_bFullscreen = FALSE;

    // Free DirectShow interfaces
    CloseInterfaces();

    // No current media state
    m_nPlayState = Init;

    // Reset the player window
    InvalidateRect(m_hWnd, &m_Rect, TRUE);
}

void CPlayWMV::CloseInterfaces(void)
{
    HRESULT hr;

    // Relinquish ownership (IMPORTANT!) after hiding video window
    if (m_pVW)
    {
        hr = m_pVW->put_Visible(0);
        hr = m_pVW->put_Owner(NULL);
    }

    // Disable event callbacks
    if (m_pME)
        hr = m_pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

    // Release and zero DirectShow interfaces
    SAFE_RELEASE(m_pME);
    SAFE_RELEASE(m_pMS);
    SAFE_RELEASE(m_pMC);
    SAFE_RELEASE(m_pBA);
    SAFE_RELEASE(m_pBV);
    SAFE_RELEASE(m_pVW);
    SAFE_RELEASE(m_pGB);
}


void CPlayWMV::Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    // Display a message box with the formatted string
    MessageBox(NULL, szBuffer, TEXT("DSPlay Sample"), MB_OK);
}

HRESULT CPlayWMV::ToggleMute(void)
{
    HRESULT hr = S_OK;

    if ((!m_pGB) || (!m_pBA))
        return S_OK;

    // Read current volume
    hr = m_pBA->get_Volume(&m_lVolume);
    if (hr == E_NOTIMPL)
    {
        // Fail quietly if this is a video-only media file
        return S_OK;
    }
    else if (FAILED(hr))
    {
        Msg(TEXT("Failed to read audio volume!  hr=0x%x\r\n"), hr);
        return hr;
    }

    // Switch volume levels
    if (m_lVolume == VOLUME_FULL)
        m_lVolume = VOLUME_SILENCE;
    else
        m_lVolume = VOLUME_FULL;

    // Set new volume
    JIF(m_pBA->put_Volume(m_lVolume));

    //  UpdateMainTitle();
    return hr;
}


HRESULT CPlayWMV::ToggleFullScreen(void)
{
    HRESULT hr = S_OK;
    LONG lMode = 0;
    static HWND hDrain = 0;

    // Don't bother with full-screen for audio-only files
    if ((m_bAudioOnly) || (!m_pVW))
        return S_OK;

    // Read current state
    JIF(m_pVW->get_FullScreenMode(&lMode));

    if (lMode == 0)  /* OAFALSE */
    {
        // Save current message drain
        LIF(m_pVW->get_MessageDrain((OAHWND *) &hDrain));

        // Set message drain to application main window
        LIF(m_pVW->put_MessageDrain((OAHWND) m_hWnd));

        // Switch to full-screen mode
        lMode = -1;  /* OATRUE */
        JIF(m_pVW->put_FullScreenMode(lMode));
        m_bFullscreen = TRUE;
    }
    else
    {
        // Switch back to windowed mode
        lMode = 0;  /* OAFALSE */
        JIF(m_pVW->put_FullScreenMode(lMode));

        // Undo change of message drain
        LIF(m_pVW->put_MessageDrain((OAHWND) hDrain));

        // Reset video window
        LIF(m_pVW->SetWindowForeground(-1));

        // Reclaim keyboard focus for player application
        UpdateWindow(m_hWnd);
        SetForegroundWindow(m_hWnd);
        SetFocus(m_hWnd);
        m_bFullscreen = FALSE;
    }

    return hr;
}

HRESULT CPlayWMV::HandleGraphEvent(void)
{
    LONG evCode = 0, evParam1 = 0, evParam2 = 0;
    HRESULT hr = S_OK;

    // Make sure that we don't access the media event interface
    // after it has already been released.
    if (!m_pME)
        return S_OK;

    // Process all queued events
    while(SUCCEEDED(m_pME->GetEvent(&evCode, (LONG_PTR *)&evParam1, (LONG_PTR *)&evParam2, 0)))
    {
        // If this is the end of the clip, reset to beginning
        if(EC_COMPLETE == evCode)
        {
            LONGLONG pos = 0;

            // Reset to first frame of movie
            hr = m_pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                NULL, AM_SEEKING_NoPositioning);
            if (FAILED(hr))
            {
                // If seeking failed, just stop and restart to reset playback
                if (FAILED(hr = m_pMC->Stop()))
                {
                    Msg(TEXT("Failed(0x%08lx) to stop media clip!\r\n"), hr);
                    break;
                }

                if (FAILED(hr = m_pMC->Run()))
                {
                    Msg(TEXT("Failed(0x%08lx) to reset media clip!\r\n"), hr);
                    break;
                }
            }
        }
        else if(EC_ERRORABORT == evCode)
        {
            Msg(TEXT("Playback error (EC_ERRORABORT - 0x%08lx). Aborting...\r\n"), evParam1);

            if (FAILED(hr = m_pMC->Stop()))
                Msg(TEXT("Failed(0x%08lx) to stop media clip!\r\n"), hr);

            hr = (HRESULT)evParam1;
            break;
        }
    }

    // Free memory associated with callback
    if( FAILED(m_pME->FreeEventParams(evCode, evParam1, evParam2)) )
    {
        CloseClip();
    }

    return hr;
}

HRESULT CPlayWMV::SetSize(int nLeft, int nTop, int nRight, int nBottom)
{
    HRESULT hr = S_OK;

    m_Rect.left = nLeft;
    m_Rect.top = nTop;
    m_Rect.right = nRight;
    m_Rect.bottom = nBottom;

    JIF(m_pVW->SetWindowPosition(m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom));

    return hr;
}

