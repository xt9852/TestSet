// WMPPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "WMPPlayer.h"


// CWMPPlayer

IMPLEMENT_DYNAMIC(CWMPPlayer, CPlayer)
BEGIN_MESSAGE_MAP(CWMPPlayer, CPlayer)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

CWMPPlayer::CWMPPlayer()
{
	m_pView		=	NULL;
	m_pPlayer	=	NULL;
	m_pControls	=	NULL;
	m_pSettings	=	NULL;
	m_pCurrentMedia	=	NULL;
	m_pNetwork	=	NULL;
	
	m_nType = MEDIAPLAYER;
}

CWMPPlayer::~CWMPPlayer()
{
}

void CWMPPlayer::SetSource(LPCTSTR sURL)
{
	CString sSource = sURL;
	m_pPlayer->put_URL( sSource.AllocSysString() );
}

void CWMPPlayer::GetSource(CString& sSource)
{
	BSTR bsURL;
	m_pPlayer->get_URL( &bsURL );
	sSource = bsURL;
}

void CWMPPlayer::Play()
{
	if ( m_pControls == NULL )	m_pPlayer->get_controls( &m_pControls );
	if ( m_pControls == NULL )	return;

	m_pControls->play();
}

void CWMPPlayer::Stop()
{
	if ( m_pControls == NULL )	m_pPlayer->get_controls( &m_pControls );
	if ( m_pControls == NULL )	return;

	m_pControls->stop();
}

void CWMPPlayer::Pause()
{
	if ( m_pControls == NULL )	m_pPlayer->get_controls( &m_pControls );
	if ( m_pControls == NULL )	return;

	m_pControls->pause();
}

LONG CWMPPlayer::GetPosition()
{
	double nPosition = 0;
	m_pControls->get_currentPosition( &nPosition );
	return (LONG)( nPosition * ONESECOND );
}

LONG CWMPPlayer::GetLength()
{
	double nDuration = 0;
	if ( m_pCurrentMedia == NULL )	m_pPlayer->get_currentMedia( &m_pCurrentMedia );
	if ( m_pCurrentMedia != NULL )	m_pCurrentMedia->get_duration( &nDuration );
	else	nDuration = 0;
	return (LONG)( nDuration * ONESECOND );
}

MediaState CWMPPlayer::GetPlayState()
{
	MediaState nReState = smsNull;
	WMPPlayState nState = wmppsUndefined;

	m_pPlayer->get_playState( &nState );

	switch( nState ) {
	case wmppsUndefined      :
		nReState = smsNull;
		break;
	case wmppsStopped        :
		nReState = smsStopped;
		break;
	case wmppsPaused         :
		nReState = smsPaused;
		break;
	case wmppsPlaying        :
		nReState = smsPlaying;
		break;
	case wmppsScanForward    :
		nReState = smsSeeking;
		break;
	case wmppsScanReverse    :
		nReState = smsSeeking;
		break;
	case wmppsBuffering      :
		nReState = smsBuffering;
		break;
	case wmppsWaiting        :
		nReState = smsContacting;
		break;
	case wmppsMediaEnded     :
		nReState = smsStopped;
		break;
	case wmppsTransitioning  :
		nReState = smsContacting;
		break;
	case wmppsReady          :
		nReState = smsStopped;
		break;
	case wmppsReconnecting   :
		nReState = smsContacting;
		break;
	default:
		break;
	}

	return nReState;
}

void CWMPPlayer::SetPosition( LONG nPosition )
{
	double nDuration = 0;
	if ( m_pCurrentMedia == NULL )	m_pPlayer->get_currentMedia( &m_pCurrentMedia );
	if ( m_pCurrentMedia != NULL )	m_pCurrentMedia->get_duration( &nDuration );
	else	return;
	
	nPosition /= ONESECOND;
	if ( nPosition > (LONG)nDuration || nPosition < 0 )	return;

	if ( m_pControls == NULL )	m_pPlayer->get_controls( &m_pControls );
	if ( m_pControls == NULL )	return;

	m_pControls->put_currentPosition( (double)nPosition );
}

LONG CWMPPlayer::GetBuffering()
{
	LONG nBufferPer = 0;
	WMPPlayState nState = wmppsUndefined;
	m_pPlayer->get_playState( &nState );

	if ( nState != wmppsBuffering )	nBufferPer = 0;
	else
	{
		if ( m_pNetwork == NULL )	m_pPlayer->get_network( &m_pNetwork );
		if ( m_pNetwork == NULL )	nBufferPer = 0;
		else
		{
			m_pNetwork->get_bufferingProgress( &nBufferPer );
		}
	}
	return nBufferPer;
}

void CWMPPlayer::SetMute(BOOL bMute)
{
	VARIANT_BOOL vbMute = bMute ? VARIANT_TRUE : VARIANT_FALSE;

	if ( m_pSettings == NULL )	m_pPlayer->get_settings( &m_pSettings );
	if ( m_pSettings == NULL )	return;

	m_pSettings->put_mute( vbMute );
}

BOOL CWMPPlayer::GetMute()
{
	VARIANT_BOOL vbMute = VARIANT_FALSE;

	if ( m_pSettings == NULL )	m_pPlayer->get_settings( &m_pSettings );
	if ( m_pSettings == NULL )	return vbMute == VARIANT_TRUE;
	m_pSettings->get_mute( &vbMute );

	return vbMute == VARIANT_TRUE;
}

void CWMPPlayer::SetVolume( LONG nVolume )
{
	if ( m_pSettings == NULL )	m_pPlayer->get_settings( &m_pSettings );
	if ( m_pSettings == NULL )	return;

	m_pSettings->put_volume( nVolume );
}

LONG CWMPPlayer::GetVolume()
{
	LONG nVolume = 0;

	if ( m_pSettings == NULL )	m_pPlayer->get_settings( &m_pSettings );
	if ( m_pSettings == NULL )	return nVolume;
	m_pSettings->get_volume( &nVolume );

	return nVolume;
}

void CWMPPlayer::OnDestroy()
{
	CWnd::OnDestroy();
	
	Stop();
	m_pPlayer	=	NULL;
	m_pControls	=	NULL;
	m_pSettings	=	NULL;
	m_pCurrentMedia	=	NULL;
	m_pNetwork	=	NULL;

	if ( m_pView != NULL )
	{
		delete m_pView;
		m_pView	= NULL;
	}
}

int CWMPPlayer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPlayer::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);

	CComPtr<IAxWinHostWindow>	spHost;
	CComPtr<IObjectWithSite>    spHostObject;
	HRESULT                     hr;
	RECT                        rectWMP={rect.left,rect.top,rect.right,rect.bottom};

	// Get an simple container to contain WMP OCX
	AtlAxWinInit();
	m_pView = new CAxWindow();
	hr = m_pView? S_OK : E_OUTOFMEMORY;

	if(SUCCEEDED(hr))
	{
		m_pView->Create(m_hWnd, rectWMP, NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN);
		hr = ::IsWindow(m_pView->m_hWnd)? S_OK : E_FAIL;
	}

	if(SUCCEEDED(hr))
	{
		hr = m_pView->QueryHost(IID_IObjectWithSite, (void **)&spHostObject);
		hr = spHostObject.p? hr : E_FAIL;
	}

	if(SUCCEEDED(hr))
	{
		hr = m_pView->QueryHost(&spHost);
		hr = spHost.p? hr : E_FAIL;
	}

	// Create WMP control using its CLSID
	if(SUCCEEDED(hr))
	{
		hr = spHost->CreateControl(CComBSTR(L"{6BF52A52-394A-11d3-B153-00C04F79FAA6}"), m_pView->m_hWnd, 0);
	}

	if(SUCCEEDED(hr))
	{
		hr = m_pView->QueryControl(&m_pPlayer);
		hr = m_pPlayer.p? hr : E_FAIL;
	}

	//Get Points
	if(SUCCEEDED(hr))
	{
		m_pPlayer->get_settings( &m_pSettings );
		m_pPlayer->get_currentMedia( &m_pCurrentMedia );
		m_pPlayer->get_controls( &m_pControls );
		m_pPlayer->get_network( &m_pNetwork );
	}

	//Settings
	if(SUCCEEDED(hr))
	{
		BSTR sUIMode = ::SysAllocString( L"none" );
		m_pPlayer->put_uiMode( sUIMode );
		::SysFreeString( sUIMode );

		m_pSettings->put_autoStart( VARIANT_FALSE );
	}

	if( ! SUCCEEDED(hr) )
	{
		if ( m_pView != NULL )
		{
			delete m_pView;
			m_pView = NULL;
		}
	}

	return 0;
}

void CWMPPlayer::OnSize(UINT nType, int cx, int cy)
{
	CRect rect;
	GetClientRect( &rect );

   // ScreenToClient(&rect);
	if ( m_pView != NULL )
	{
		m_pView->MoveWindow( &rect );
	}
}
