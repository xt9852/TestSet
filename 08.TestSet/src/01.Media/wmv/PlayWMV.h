
/*
	播放wmv,wma,asf文件
	需要引用strmiids.lib,quartz.lib,winmm.lib,WMVCORE.lib(SDK)这四个库
*/


#pragma once

#include <strmif.h>
#include <control.h>
#include <uuids.h>
#include <evcode.h>

#define VOLUME_FULL     0L
#define VOLUME_SILENCE  -10000L

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
	TEXT("Windows Media Files (*.asf; *.wma; *.wmv) |*.asf;*.wma;*.wmv|All Files (*.*) |*.*||")

enum PLAYSTATE {Stopped, Paused, Running, Init};

//
// Macros
//
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

#define JIF(x) if (FAILED(hr=(x))) \
{Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

#define LIF(x) if (FAILED(hr=(x))) \
{Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr);}

#ifndef NUMELMS
#define NUMELMS(aa) (sizeof(aa)/sizeof((aa)[0]))
#endif


class CPlayWMV
{

public:
	CPlayWMV();
	~CPlayWMV();

private:
	HWND			m_hWnd;				// 显示画面的窗体
	BOOL			m_bAudioOnly;
	BOOL			m_bFullscreen;
	LONG			m_lVolume;
	PLAYSTATE		m_nPlayState;
	RECT			m_Rect;

	// DirectShow interfaces
	IGraphBuilder	*m_pGB;
	IMediaControl	*m_pMC;
	IMediaEventEx	*m_pME;
	IVideoWindow	*m_pVW;
	IBasicAudio		*m_pBA;
	IBasicVideo		*m_pBV;
	IMediaSeeking	*m_pMS;

	void Msg(TCHAR *szFormat, ...);
	void CheckVisibility(void);
	void CloseInterfaces(void);	

public:
	HRESULT PlayMovieInWindow(HWND hWnd, LPTSTR szFile);
	void PauseClip(void);
	void StopClip(void);
	void CloseClip(void);
	HRESULT ToggleMute(void);
	HRESULT ToggleFullScreen(void);
	HRESULT HandleGraphEvent(void);
	HRESULT SetSize(int nLeft, int nTop, int nRight, int nBottom);
};












