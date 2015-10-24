
#include "stdafx.h"
#include "AVProcess.h"
#include <WS2tcpip.h>

namespace XT_IOCP
{

#define BUF_SIZE 76100

	CAVProcess::CAVProcess()
		:m_bIPV6(FALSE)
	{
	}

	CAVProcess::~CAVProcess()
	{
	}

	bool CAVProcess::GetAddrUdp(LPCTSTR sIP, WORD wPort, addrinfo **ppAddInfo)
	{
		CString sPort;
		sPort.Format("%d", wPort);

		struct addrinfo Info = {0};
		Info.ai_family = m_bIPV6?AF_INET6:AF_INET;
		Info.ai_socktype = SOCK_DGRAM;
		Info.ai_protocol = IPPROTO_UDP;

		if (getaddrinfo(sIP, sPort, &Info, ppAddInfo) == 0)
			return true;
		else
			return false;
	}

	void CAVProcess::Init(BOOL bIPV6, DWORD dwChanId, DWORD dwMTU,
		WORD  wAudioProto, WORD wVideoProto, WORD  wResendProto,
		PackQueue *pQueueOut, BuffPool *pSubBuffPool)
	{
		m_bIPV6 = bIPV6;

		m_BigBuffPool.SetSize(BUF_SIZE);
		m_AVSend.Init(bIPV6, dwChanId, dwMTU, BUF_SIZE, wAudioProto, wVideoProto, pQueueOut, pSubBuffPool);
		m_AVCapture.Init(&m_AVSend);
		m_AVPlay.Init(&m_BigBuffPool, pSubBuffPool);
		m_AVRecv.Init(bIPV6, dwMTU, wResendProto, &m_AVPlay, pQueueOut, &m_BigBuffPool, pSubBuffPool);
	}

	// 设置自己视频的位置
	void CAVProcess::AddShow(HDC hDC, int x, int y)
	{
		m_AVCapture.AddShow(hDC, x, y);
	}

	void CAVProcess::DelShow(HDC hDC)
	{
		m_AVCapture.DelShow(hDC);
	}

	// 添加一个接收者
	void CAVProcess::AddRecver(DWORD dwChannId, 
		PCLIENT pClient, UINT64 *pnIP, WORD wPort,
		HDC hDC, int x, int y, 
		BOOL bShowBigVideo, int x1, int y1, int cx, int cy)
	{
		m_AVPlay.AddPlayer(dwChannId, hDC, x, y, bShowBigVideo, x1, y1, cx, cy);
		m_AVRecv.AddRecver(dwChannId, pClient, pnIP, wPort);
	}

	// 添加一个播放,直接打开文件进行播放
	void CAVProcess::AddPlayer(DWORD dwChannId, LPCSTR strFile, HWND hWnd, int x, int y, 
		BOOL bShowBigVideo, int x1, int y1, int cx, int cy)
	{
		m_AVPlay.AddPlayer(dwChannId, strFile, hWnd, x, y, bShowBigVideo, x1, y1, cx, cy);
	}

	// 添加一个发送者
	void CAVProcess::AddSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, LPCTSTR strIP, WORD wPort)
	{
		struct addrinfo *pAddrInfo = NULL;
		if (GetAddrUdp(strIP, wPort, &pAddrInfo))
		{
			UINT64 nIP[2] = {0};
			WORD   wPort  = 0;

			if (m_bIPV6)
			{
				PSOCKADDR_IN6 pAddr6 = (PSOCKADDR_IN6)pAddrInfo->ai_addr;
				wPort = pAddr6->sin6_port;
				memcpy(&nIP, &pAddr6->sin6_addr, 16);
			}
			else
			{
				PSOCKADDR_IN pAddr = (PSOCKADDR_IN)pAddrInfo->ai_addr;
				wPort = pAddr->sin_port;
				nIP[0] = pAddr->sin_addr.S_un.S_addr;
			}

			if (bAudio) m_AVSend.AddAudioSend(pClient, nIP, wPort);
			if (bVideo) m_AVSend.AddVideoSend(pClient, nIP, wPort);

			freeaddrinfo(pAddrInfo);
		}
	}

	// 添加一个发送者
	// dwIP, wPort 网络字节顺序
	void CAVProcess::AddSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, UINT64 *pnIP, WORD wPort)
	{
		if (bAudio) m_AVSend.AddAudioSend(pClient, pnIP, wPort);
		if (bVideo) m_AVSend.AddVideoSend(pClient, pnIP, wPort);
	}

	// 删除接收者
	void CAVProcess::DelRecver(DWORD dwChannId)
	{
		m_AVRecv.DelRecver(dwChannId);
		m_AVPlay.DelPlayer(dwChannId);
	}

	// 删除播放
	void CAVProcess::DelPlayer(DWORD dwChannId)
	{
		m_AVPlay.DelPlayer(dwChannId);
	}

	// 删除发送者
	void CAVProcess::DelSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, LPCTSTR strIP, WORD wPort)
	{
		struct addrinfo *pAddrInfo = NULL;
		if (GetAddrUdp(strIP, wPort, &pAddrInfo))
		{
			UINT64 nIP[2] = {0};
			WORD   wPort  = 0;

			if (m_bIPV6)
			{
				PSOCKADDR_IN6 pAddr6 = (PSOCKADDR_IN6)pAddrInfo->ai_addr;
				wPort = pAddr6->sin6_port;
				memcpy(&nIP, &pAddr6->sin6_addr, 16);
			}
			else
			{
				PSOCKADDR_IN pAddr = (PSOCKADDR_IN)pAddrInfo->ai_addr;
				wPort = pAddr->sin_port;
				nIP[0] = pAddr->sin_addr.S_un.S_addr;
			}

			if (bAudio) m_AVSend.DelAudioSend(pClient, nIP, wPort);
			if (bVideo) m_AVSend.DelVideoSend(pClient, nIP, wPort);

			freeaddrinfo(pAddrInfo);
		}
	}

	// 删除发送者
	// dwIP, wPort 网络字节顺序
	void CAVProcess::DelSender(BOOL bAudio, BOOL bVideo, PCLIENT pClient, UINT64 *pnIP, WORD wPort)
	{
		if (bAudio) m_AVSend.DelAudioSend(pClient, pnIP, wPort);
		if (bVideo) m_AVSend.DelVideoSend(pClient, pnIP, wPort);
	}

	// 开始将音视频保存为文件
	void CAVProcess::StartSaveFile(DWORD dwChanId, LPCSTR strFile)
	{
		m_AVPlay.StartSaveFile(dwChanId, strFile);
	}

	// 停止将音视频保存为文件
	DWORD CAVProcess::StopSaveFile(DWORD dwChanId)
	{
		return m_AVPlay.StopSaveFile(dwChanId);
	}

	// 开始显示大视频
	void CAVProcess::StartBigVideo(DWORD dwChanId)
	{
		m_AVPlay.StartShowBigVideo(dwChanId);
	}

	// 停止显示大视频
	void CAVProcess::StopBigVideo(DWORD dwChanId)
	{
		m_AVPlay.StopShowBigVideo(dwChanId);
	}

	// 保存自己的视频
	void CAVProcess::StartSaveMyFile(LPCTSTR psFile)
	{
		m_AVCapture.StartSaveFile(psFile);
	}

	// 保存自己的视频
	void CAVProcess::StopSaveMyFile(void)
	{
		m_AVCapture.StopSaveFile();
	}

	// 设置播放
	// dwChanId  [in] 通道号
	// ePlayType [in] 播放类型(PLAY,PAUSE,STOP,FORWARD,BACKWARD)
	void CAVProcess::SetPlay(DWORD dwChanId, BYTE ePlayType)
	{
		m_AVPlay.SetPlayFile(dwChanId, ePlayType);
	}

	// 将视频帧保存成BMP文件
	void CAVProcess::SaveImage(DWORD dwChanId, LPCSTR strFile)
	{
		m_AVPlay.SaveImage(dwChanId, strFile);
	}

	// 开始捕获音视频
	void CAVProcess::Start(BOOL bAudio, BOOL bVideo)
	{
		m_AVCapture.Start(bAudio, bVideo);
	}

	// 停止捕获音视频
	void CAVProcess::Stop(BOOL bAudio, BOOL bVideo)
	{
		m_AVCapture.Stop(bAudio, bVideo);
	}

	// 收到音视频包
	void CAVProcess::AddAV(PPACK pPack, WORD wType)
	{
		m_AVRecv.RecvAV(pPack, wType);
	}

	// 重发音视频帧
	void CAVProcess::ResendAV(PCLIENT pClient, DWORD dwId, UINT64 *pnIP, WORD wPort)
	{
		m_AVSend.ResendAV(pClient, dwId, pnIP, wPort);
	}

	WORD CAVProcess::GetVideoSenderCount(void)
	{
		return m_AVSend.GetVideoCount();
	}
}