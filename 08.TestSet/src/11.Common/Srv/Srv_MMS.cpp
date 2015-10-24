#include "StdAfx.h"
#include ".\srv_mms.h"
#include "Common/StrConver.h"


namespace XT_IOCP
{

	CSrv_MMS::CSrv_MMS(void)
		:m_hRtspStreamThread(NULL),
		m_pClient(NULL)
	{
		//CSrv::Init(CMD_TYPE_MMS, 1024*4-4);
	}

	CSrv_MMS::~CSrv_MMS(void)
	{
		/*	if (m_hRtspStreamThread != NULL)
		{
		for (int nAttempt = 10 ; nAttempt > 0 ; nAttempt--)
		{
		DWORD nCode;
		if (!GetExitCodeThread( m_hRtspStreamThread, &nCode)) break;
		if (nCode != STILL_ACTIVE ) break;
		Sleep(100);
		}

		if (nAttempt == 0)
		{
		TerminateThread(m_hRtspStreamThread, 0);
		g_ProFile.m_pLog->println(_T("WARNING: Terminating CDlg_RTSP.RtspStream Thread."));
		Sleep(100);
		}

		CloseHandle(m_hRtspStreamThread);
		}
		*/
	}

	int CSrv_MMS::Start(LPCTSTR pszIP, const int nPort)
	{
		if (0 != CSrv::Start(CMD_TYPE_MMS, 4000)) return -1;

		PCLIENT	pvClient = NULL;

		return iocp_.AddTcpListen(pszIP, nPort, &pvClient);
	}

	int CSrv_MMS::Connect(LPCTSTR pszIP, const int nPort)
	{
		return iocp_.ConnectTo(pszIP, nPort, (PCLIENT*)&m_pClient);
	}

	int CSrv_MMS::Login(void)
	{
		/*	BYTE *pBuf = m_BuffPool.GetBuffer();
		BYTE *pPtr = pBuf;

		memset(pPtr, 0, 1024 * 4);

		// to server;Len=104
		// 包头
		SetU32(&pPtr, 0x00000001);	// 是客户端向服务器端发包的固定开头。以后你会看到每一个包都是如此开头的。4字节
		SetU32(&pPtr, 0xb00bface);	// 这也是固定不变的。通常被人称为“BOOB FACE”。他可能是一个版本号或者序列号。以后你会看到客户端和服务器端发出的每一个包都是如此开头的。4字节。	
		SetU32(&pPtr, 0x00000058);	// 表明在“协议类型(也就是接下来的4d 4d 53 20)”后面的所有数据的长度。4字节。	
		SetU32(&pPtr, 0x20534d4d);	// 表明协议类型，就是“MMS<space>”的ASCII码。4字节。	
		SetU32(&pPtr, 0x0000000b);	// Length until end of packet in 8 byte boundary lengths，Including own data field。4字节。	
		SetU32(&pPtr, 0x00000000);	// Sequence number。4字节。	
		SetU32(&pPtr, 0x00000000);	// 8字节。Double precision time stamp (see notes) used for network timing。	
		SetU32(&pPtr, 0x00000000);	
		SetU32(&pPtr, 0x00000009);	// Length until end of packet in 8 byte boundary lengths. Including own data field。4字节。		
		SetU32(&pPtr, 0x00030001);	// 指的是“Comm 2 bytes | Dir 2 bytes”。01 00是Command数值。03 00是Direction数值，这里的0x03指明客户端发往服务器。4字节。
		// 包体							
		SetU32(&pPtr, 0x0f0f0f0f);	// MMS协议标志1。
		SetU32(&pPtr, 0x0004000b);
		SetU32(&pPtr, 0x0003001c);
		SetStr(&pPtr, "NSPlayer/7.1.0.1956; ");
		*/

		PMMS_HEAD pHead = (PMMS_HEAD)buffPool_.Get(1);
		memset(pHead, 0, 104);

		pHead->dwFlag1	  = 0x01;
		pHead->dwFlag2	  = 0xb00bface;
		pHead->dwDataLen  = 0x58;
		pHead->dwFlag3	  = 0x20534d4d;
		pHead->dwAlign1	  = 0x0b;
		pHead->dwSeqNum	  = 0x00;
		pHead->uTimeStamp = 0x00;
		pHead->dwAlign2	  = 0x09;
		pHead->sCmdNum	  = 0x01;
		pHead->sDirect	  = 0x03;

		BYTE *pPtr = (BYTE*)pHead->szData;

		SetU32(&pPtr, 0xf0f0f0f0);
		SetU32(&pPtr, 0x0004000b);
		SetU32(&pPtr, 0x0003001c);

		int nWcharLen = 0;
		CStrConver::GBK_UNICODE("NSPlayer/7.1.0.1956; " , (char*)pPtr, nWcharLen);

		LOG(INFO) << "1TH OUT CMD";
		//g_ProFile.m_pLog->println((LPCTSTR)pHead, pHead->dwDataLen + 0x10);
		//g_ProFile.m_pLog->println(_T("\r\n"), 2);

		outputQueue_.Add(m_pClient, pHead, pHead->dwDataLen + 0x10);

		return 0;
	}

	void CSrv_MMS::SetU32(BYTE **pBuf, DWORD dwValue)
	{
		memcpy((void*)*pBuf, (const void *)&dwValue, 4);
		*pBuf += 4;
	}

	void CSrv_MMS::SetStr(BYTE **pBuf, LPCSTR szStr)
	{
		memcpy((void*)*pBuf, szStr, sizeof(szStr));
		*pBuf += sizeof(szStr);
	}

	void CSrv_MMS::ProcessPack(PCLIENT pClient, DWORD dwDataLen, PVOID pvBuf, UINT64 nIP[2], WORD wPort)
	{
		PMMS_HEAD pHead = (PMMS_HEAD)pvBuf;

		LOG(INFO) << "IN CMD:" << pHead;

		if (pHead->sDirect == 0x04)	// 从服务器发来的数据
		{
			switch (pHead->sCmdNum)
			{
			case 0x01:	// 发0x18
				{
					pHead->dwDataLen = 0x20;
					pHead->dwAlign1	 = pHead->dwDataLen / 8;
					pHead->dwAlign2	 = (pHead->dwDataLen-0x10) / 8;
					pHead->sDirect	 = 0x03;
					pHead->sCmdNum	 = 0x18;				
					pHead->dwSeqNum	 = 0x01;

					BYTE *pPtr = (BYTE*)pHead->szData;

					SetU32(&pPtr, 0xf0f0f0f1);
					SetU32(&pPtr, 0x0004000b);

					LOG(INFO) << "2TH OUT CMD";
					//g_ProFile.m_pLog->println((LPCTSTR)pHead, pHead->dwDataLen + 0x10);
					//g_ProFile.m_pLog->println(_T("\r\n"), 2);

					outputQueue_.Add(m_pClient, pHead, pHead->dwDataLen + 0x10);				
					break;
				}
			case 0x15:	// 发0x02
				{
					static int nTimes = 0;

					if (++nTimes == 3)
					{
						pHead->dwDataLen  = 0x60;
						pHead->dwAlign1	  = (pHead->dwDataLen) / 8;
						pHead->dwAlign2	  = (pHead->dwDataLen-0x10) / 8;
						pHead->uTimeStamp = 0x00;
						pHead->sDirect	  = 0x03;
						pHead->sCmdNum	  = 0x02;				
						pHead->dwSeqNum	  = 0x02;					

						BYTE *pPtr = (BYTE*)pHead->szData;

						memset(pPtr, 0, 200);

						SetU32(&pPtr, 0xf0f0f0f1);
						SetU32(&pPtr, 0xffffffff);
						SetU32(&pPtr, 0x00000000);
						SetU32(&pPtr, 0x00a00000);
						SetU32(&pPtr, 0x00000002);
						SetU32(&pPtr, 0x00000001);
						SetU32(&pPtr, 0x00000001);
						SetU32(&pPtr, 0x00008000);

						struct sockaddr_in svrAddr;
						int saLen = sizeof(svrAddr);
						getsockname(pClient->sock, (struct sockaddr*)&svrAddr, &saLen);

						CStringA strAddr;
						strAddr.Format("%s\\\\TCP\\%d", inet_ntoa(svrAddr.sin_addr), ntohs(svrAddr.sin_port));

						int nWcharLen = 0;
						CStrConver::GBK_UNICODE(strAddr.GetString(), (char*)pPtr, nWcharLen);
						pPtr++;
						CStrConver::GBK_UNICODE("000000000000000000000000" , (char*)pPtr, nWcharLen);

						LOG(INFO) << "3TH OUT CMD:" << pHead;
						//g_ProFile.m_pLog->Log((LPCTSTR)pHead, pHead->dwDataLen + 0x10);
						//g_ProFile.m_pLog->Log(_T("\r\n"), 2);

						outputQueue_.Add(m_pClient, pHead, pHead->dwDataLen + 0x10);
					}
					else
					{
						buffPool_.Free(pvBuf);
					}
					break;
				}
			case 0x02:
				{
					buffPool_.Free(pvBuf);
					LOG(INFO) << "IN CMD 0x02";
					break;
				}
			case 0x03:
				{
					buffPool_.Free(pvBuf);
					LOG(INFO) << "IN CMD 0x03";
					break;
				}		
			default:
				{
					buffPool_.Free(pvBuf);
					LOG(INFO) << "IN CMD ERROR";
					break;
				}
			}
		}
		else
		{
			buffPool_.Free(pvBuf);
			return;
		}

		return;
	}

}