#ifndef		__PLAYER_H__
#define		__PLAYER_H__

#pragma once

typedef enum
{
	smsNull = -1,
	smsStopped,smsContacting,smsBuffering,smsPlaying,smsPaused,smsSeeking
} MediaState;

enum
{
	UNKOWNPLAYER = 0,
	REALPLAYER,
	MEDIAPLAYER
};

#define ONESECOND	1000

class CPlayer : public CWnd
{
	DECLARE_DYNAMIC(CPlayer)

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void		SetSource(LPCTSTR sURL) = 0;
	virtual void		Play() = 0;
	virtual void		Pause() = 0;
	virtual void		Stop() = 0;
	virtual LONG		GetPosition() = 0;
	virtual LONG		GetLength() = 0;
	virtual MediaState	GetPlayState() = 0;
	virtual void		SetPosition( LONG nPosition ) = 0;
	virtual void		SetMute(BOOL bMute) = 0;
	virtual BOOL		GetMute() = 0;
	virtual void		SetVolume( LONG nVolume ) = 0;
	virtual LONG		GetVolume() = 0;
	virtual LONG		GetBuffering() = 0;
    virtual	void SetControls(LPCTSTR lpszNewValue) =0;
	
protected:
	int			m_nType;

protected:
	DECLARE_MESSAGE_MAP()
};
#endif//__PLAYER_H__