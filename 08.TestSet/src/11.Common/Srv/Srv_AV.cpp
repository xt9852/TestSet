
#include "StdAfx.h"
#include "Srv_AV.h"
//#include "Dlg/Dlg_AV.h"

namespace XT_IOCP
{

#define OP_UDP_AUDIO   0x0430
#define OP_UDP_VIDEO   0x0431
#define OP_UDP_RESEND  0x0432


	void CSrv_AV::StartTest(void)
	{
// 		UINT64 nIP[2] = {inet_addr(g_ProFile.m_strIP), 0};
// 		m_AVProcess.AddShow(m_pDlg->GetDC()->GetSafeHdc(), 10, 80);
// 		m_AVProcess.AddSender(TRUE, TRUE, m_pUdpCC, g_ProFile.m_strIP, 3303);
// 		m_AVProcess.AddRecver(m_dwAVChannId, m_pUdpCC, nIP, htons(3303),
// 			m_pDlg->GetDC()->GetSafeHdc(), 190, 80);
// 		m_AVProcess.Start(TRUE, TRUE);
	}

	void CSrv_AV::StopTest(void)
	{
// 		m_AVProcess.DelShow(m_pDlg->GetDC()->GetSafeHdc());
// 		m_AVProcess.Stop(TRUE, TRUE);
// 		m_AVProcess.DelRecver(m_dwAVChannId);
// 		m_AVProcess.DelSender(TRUE, TRUE, m_pUdpCC, g_ProFile.m_strIP, 3303);
	}

	CSrv_AV::CSrv_AV(void)
		:m_pDlg(NULL),
		m_dwAVChannId(0)   
	{
	}

	CSrv_AV::~CSrv_AV(void)
	{
	}

	int CSrv_AV::Init(CDlg_AV *pDlg)
	{
// 		m_pDlg = pDlg;
// 		m_dwAVChannId = ::GetTickCount();
// 
// 		CSrv::Init(CMD_TYPE_MYSELF, 1020, TRUE);
// 
// 		m_AVProcess.Init(m_bIPV6, m_dwAVChannId, 1000-sizeof(_tagBlockEx),
// 			OP_UDP_AUDIO, OP_UDP_VIDEO, OP_UDP_RESEND, &m_QueueOut, &m_BuffPool);

		return 0;
	}

	int CSrv_AV::Start()
	{
		CSrv::Start(CMD_TYPE_MYSELF, 2000);

		PCLIENT client = NULL;

		if (0 != iocp_.AddUdpListen(g_ProFile.getIp(0), 3303, &client)) return -80;

		return 0;
	}

	void CSrv_AV::ProcessPack(void *client, void *buf, int len, int ip, short port)
	{
		PPACK pPack = (PPACK)buf;

		if (pPack->getPackLen() != len) return;

		switch (pPack->protoId)
		{
		case CLIENT_CLOSE_SOCKET:   // SOCKET断开连接,pPack->dataLen为SOCKET值
			{
				TRACE(_T("CLIENT_CLOSE_SOCKET SOCKET:%d\n"), pPack->dataLen);
				buffPool_.Free(pPack);
				break;
			}
		case OP_UDP_AUDIO:
			{
				//m_AVProcess.m_AVRecv.RecvAV(pPack, AUDIO);
				break;
			}
		case OP_UDP_VIDEO:
			{
				//m_AVProcess.m_AVRecv.RecvAV(pPack, VIDEO);
				break;
			}
		case OP_UDP_RESEND:
			{
				//m_AVProcess.m_AVSend.ResendAV(client, pPack->dataLen, ip, port);
				buffPool_.Free(pPack);
				break;
			}
		default:
			TRACE(_T("Pack Error %x\n"), pPack->protoId);
			buffPool_.Free(pPack);
		}
	}

}