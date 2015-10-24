#ifndef		__WMPPLAYER_H__
#define		__WMPPLAYER_H__

#pragma once
#include <atlwin.h>
#include "Player.h"
#include "wmp.h"


// 在Win2000系统下，如果用系统自带的MediaPlayer需要用
// wmvcore.dll,wmasf.dll,wmidex.dll,drmclien.dll,msdmo.dll,gdiplus.d


// 工程要用动态连接到ATL
class CWMPPlayer : public CPlayer
{
	DECLARE_DYNAMIC(CWMPPlayer)

public:
	CWMPPlayer();
	virtual ~CWMPPlayer();

	void		SetSource(LPCTSTR sURL);
	void		GetSource(CString& sSource);
	void		Play();
	void		Pause();
	void		Stop();
	LONG		GetPosition();
	LONG		GetLength();
	MediaState	GetPlayState();
	void		SetPosition( LONG nPosition );
	void		SetMute(BOOL bMute);
	BOOL		GetMute();
	void		SetVolume( LONG nVolume );
	LONG		GetVolume();
	LONG		GetBuffering();

	void SetControls(LPCTSTR lpszNewValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lpszNewValue);
	}
	long GetPacketsLate()
	{
		long result;
		InvokeHelper(0xf1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

public:
	// IE control to hold WMP OCX
	CAxWindow*						m_pView;

protected:
	// Player
	CComPtr<IWMPPlayer4>            m_pPlayer;
	// Player Settings
	CComPtr<IWMPSettings>			m_pSettings;
	// CurrentMedia
	CComPtr<IWMPMedia>				m_pCurrentMedia;
	// Player Control
	CComPtr<IWMPControls>			m_pControls;
	// Player Network
	CComPtr<IWMPNetwork>			m_pNetwork;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#endif//__WMPPLAYER_H__
