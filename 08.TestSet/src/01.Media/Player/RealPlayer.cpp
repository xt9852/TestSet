// RealPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "RealPlayer.h"


UINT WM_FULLSCREEN = RegisterWindowMessage(_T("WM_FULLSCREEN"));	// 全屏


IMPLEMENT_DYNAMIC(CRealPlayer, CPlayer)
BEGIN_MESSAGE_MAP(CRealPlayer, CPlayer)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

CRealPlayer::CRealPlayer()
{
	m_nType = REALPLAYER;
	m_nBufferingLength = 0;
}

CRealPlayer::~CRealPlayer()
{
}

BOOL CRealPlayer::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
			const RECT& rect, CWnd* pParentWnd, UINT nID, 
			CCreateContext* pContext)
{ 
	BOOL bRet = CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);

	if (bRet)
	{
		SetControls(_T("ImageWindow"));
		SetNoLogo(TRUE);
		SetEnableContextMenu(FALSE);
		SetImageStatus(FALSE);
		SetWantErrors(FALSE);
		SetCenter(TRUE);
		SetMaintainAspect(TRUE);
		SetAutoStart(FALSE);
	}

	return bRet;
}

void CRealPlayer::OnDestroy()
{
	CWnd::OnDestroy();

	DoStop();
}

LONG CRealPlayer::GetVolume()
{
	short result;
	InvokeHelper(0xe2, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return (LONG)result;
}

void CRealPlayer::SetVolume(LONG nVol)
{
	short nVol1 = (short)nVol;
	static BYTE parms[] = VTS_I2 ;
	InvokeHelper(0xe3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nVol1);
}

BOOL CRealPlayer::GetMute()
{
	BOOL result;
	InvokeHelper(0xe4, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CRealPlayer::SetMute(BOOL bMute)
{
	static BYTE parms[] = VTS_BOOL ;
	InvokeHelper(0xe5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bMute);
}

void CRealPlayer::SetSource(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR ;
	InvokeHelper(0xd7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lpszNewValue);
}

void CRealPlayer::GetSource(CString& sSource)
{
	CString result;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	sSource = result;
}

void CRealPlayer::SetPosition(LONG lPosition)
{
	static BYTE parms[] = VTS_I4 ;
	InvokeHelper(0x10d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lPosition);
}

LONG CRealPlayer::GetPosition()
{
	long result;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

LONG CRealPlayer::GetLength()
{
	long result;
	InvokeHelper(0x105, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CRealPlayer::Play()
{
	DoPlay();
}

void CRealPlayer::Pause()
{
	DoPause();
}

void CRealPlayer::Stop()
{
	DoStop();
}

MediaState CRealPlayer::GetPlayState()
{
	long result;
	InvokeHelper(0x104, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);

	MediaState nState = (MediaState)result;
	if (nState != smsBuffering)	m_nBufferingLength = 0;
	return (MediaState)result;
}

LONG CRealPlayer::GetBuffering()
{
	LONG nElapsed = GetBufferingTimeElapsed();
	if (nElapsed > m_nBufferingLength)
		m_nBufferingLength = nElapsed;
	if (m_nBufferingLength <= 0 || nElapsed <= 0)	return 0;
	return (LONG)((float)((m_nBufferingLength - nElapsed) * 100) / m_nBufferingLength);
}

BOOL CRealPlayer::PreTranslateMessage( MSG* pMsg )
{
	if (!(pMsg->message == WM_RBUTTONDOWN || pMsg->message == WM_RBUTTONUP || pMsg->message == WM_MOUSEMOVE || 
		pMsg->message == WM_RBUTTONDBLCLK ))
	{
		if (pMsg->message == WM_LBUTTONDOWN)//DBLCLK 
		{
			GetParent()->PostMessage(WM_FULLSCREEN, 0, 0);
			return TRUE;
		}
		return CWnd::PreTranslateMessage(pMsg);
	}
	else
	{
		if (pMsg->message == WM_RBUTTONDOWN)
		{
			POINT point;
			::GetCursorPos(&point);
			GetParent()->PostMessage(WM_CONTEXTMENU, point.x, point.y);
			return TRUE;
		}
		return TRUE;
	}	
}






