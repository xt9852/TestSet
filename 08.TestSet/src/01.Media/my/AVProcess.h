
#pragma once
#include "Network/BuffPool.h"
#include "AVCapt.h"
#include "AVSend.h"
#include "AVRecv.h"
#include "AVPlay.h"


namespace XT_IOCP
{

	class CAVProcess
	{
	public:
		CAVProcess();
		~CAVProcess();

	public:
		BuffPool       m_BigBuffPool;  // 用于播放H264的缓冲区可能比较大
		CAVPlay         m_AVPlay;
		CAVRecv         m_AVRecv;
		CAVSend         m_AVSend;
		CAVCapt         m_AVCapture;
		BOOL            m_bIPV6;

	public:
		void Init(BOOL bIPV6, DWORD dwChanId, DWORD dwMTU,
			WORD  wAudioProto, WORD wVideoProto, WORD wResendProto,
			PackQueue *pQueueOut, BuffPool *pSubBuffPool);

		void AddShow(HDC hDC, int x, int y);
		void DelShow(HDC hDC);

		void AddRecver(DWORD dwChannId, PCLIENT pClient, UINT64 *pnIP, WORD wPort, HDC hDC, int x, int y,
			BOOL bShowBigVideo = FALSE, int x1 = 0, int y1 = 0, int cx = 0, int cy = 0);
		void AddPlayer(DWORD dwChannId, LPCSTR strFile, HWND hWnd, int x, int y,
			BOOL bShowBigVideo = FALSE, int x1 = 0, int y1 = 0, int cx = 0, int cy = 0);
		void AddSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, LPCTSTR strIP, WORD wPort);
		void AddSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, UINT64 *pnIP, WORD wPort);  

		void DelRecver(DWORD dwChannId);
		void DelPlayer(DWORD dwChannId);
		void DelSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, LPCTSTR strIP, WORD wPort);
		void DelSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, UINT64 *pnIP, WORD wPort);

		void Start(BOOL bAudio, BOOL bVideo);
		void Stop(BOOL bAudio, BOOL bVideo);

		void  StartSaveFile(DWORD dwChanId, LPCSTR strFile);
		DWORD StopSaveFile(DWORD dwChanId);
		void  SaveImage(DWORD dwChanId, LPCSTR strFile);

		void StartBigVideo(DWORD dwChanId);
		void StopBigVideo(DWORD dwChanId);

		void StartSaveMyFile(LPCTSTR psFile);
		void StopSaveMyFile(void);

		void SetPlay(DWORD dwChanId, BYTE ePlayType);

		void AddAV(PPACK pPack, WORD wType);
		void ResendAV(PCLIENT pClient, DWORD dwId, UINT64 *pnIP, WORD wPort);

		bool GetAddrUdp(LPCTSTR sIP, WORD wPort, addrinfo **ppAddInfo);

		WORD GetVideoSenderCount(void);
	};
}