
#include "StdAfx.h"
#include "srv_rtsp.h"

namespace XT_IOCP
{

	CSrv_RTSP::CSrv_RTSP()
		:m_wRTSP_ResponseSeq(3),
		m_nRTSP_TreamCount(0),
		m_tRTSP_LastSendPacket(0),
		m_tRTSP_LogicalPos(0),
		m_dwRTSP_PushDataTime(0),
		m_bFlag(TRUE),
		m_bRTSP_SendData(FALSE),
		m_pRTSP_rmParser(NULL),
		client_(NULL),
		m_hRtspStreamThread(NULL)
	{
		m_nRTSP_TreamSeq[0] = 0;
		m_nRTSP_TreamSeq[1] = 0;
		m_nRTSP_TreamSeq[2] = 0;
		m_nRTSP_TreamSeq[3] = 0;
		m_nRTSP_TreamSeq[4] = 0;

		headers_["OPTIONS"] = "";
		headers_["CSeq"] = "";
		headers_["User-Agent"] = "";
		headers_["DESCRIBE"] = "";
		headers_["Session"] = "";
		headers_["Content-base"] = "";
		headers_["Content-type"] = "";
		headers_["Content-length"] = "";
	}

	CSrv_RTSP::~CSrv_RTSP()
	{
		StopThread(m_hRtspStreamThread);
	}

	int CSrv_RTSP::Start(const char *ip, unsigned short port, const char *root)
	{
		root_ = root;

		if (0 != CSrv::Start(CMD_TYPE_HTTP, 1024*10)) return -1;

		PCLIENT client = NULL;

		return iocp_.AddTcpListen(ip, port, &client);
	}

	void CSrv_RTSP::ProcessPack(void *client, void *buf, int len, int ip, short port)
	{
		PPACK pack = (PPACK)buf;
		char *bufData = (char*)buf;		
		PCLIENT pClient = (PCLIENT)client;

		if (pack->protoId == CLIENT_CLOSE_SOCKET)
		{
			TRACE("CSrv_RTSP::ProcessPack default\n");
			buffPool_.Free(pack);
			return;
		}

		bufData[len] = '\0';
		cmd_ += bufData;

		if (cmd_.rfind("\r\n\r\n") == -1) // 还没结束
		{
			buffPool_.Free(buf);
			return;
		}
		
		Sleep(100);

		LOG(INFO) << cmd_;

		bufData = (char*)cmd_.c_str();
		len = cmd_.length();

		ParseRequstHead(bufData, len);

		if (0 == strncmp(bufData, "OPTION", 6))
		{
			ProcessOPTION(pClient, bufData, len);
			cmd_ = "";
		}
		else if (0 == strncmp(cmd_.c_str(), "DESCRIBE", 8))
		{
			ProcessDESCRIBE(pClient, bufData, len);
			cmd_ = "";
		}
		else if (0 == strncmp(cmd_.c_str(), "SETUP", 5))
		{
			ProcessSETUP(pClient, bufData, len);
			cmd_ = "";
		}
		else if (0 == strncmp(bufData, "SET_PARAMETER", 13))
		{
			ProcessSETPARAMETER(pClient, bufData, len);
			cmd_ = "";
		}
		else if (0 == strncmp(bufData, "PLAY", 4))
		{
			ProcessPLAY(pClient, bufData, len);
			cmd_ = "";
		}
		else if (0 == strncmp(bufData, "PAUSE", 5))
		{
			ProcessPAUSE(pClient, bufData, len);
			cmd_ = "";
		}
		else if (0 == strncmp(bufData, "TEARDOWN", 8))
		{
			TRACE("client exit\n");
			cmd_ = "";
		}
		else
		{
			LOG(ERROR) << "--------------------------------RTSP_IN_CMD ERROR";
			TRACE("RTSP_IN_CMD ERROR\n%s\n", bufData);
		}
	}

	/**
	 *\fn         ParseRequstHead(const char *data, int len)
	 *\brief      解析请求头
	 *\param[in]  data		数据。
	 *\param[in]  len		数据长。
	 *\return     命令类型
	 */
	std::string CSrv_RTSP::ParseRequstHead(const char *data, int len)
	{
		VECTOR_STR headerNodes;
		CStrConver::TokenizeData(data, "\r\n", headerNodes);

		std::string cmd;
		std::string header;
		std::string content;

		for (unsigned int i = 0; i < headerNodes.size(); i++)
		{
			GetHeadContent(headerNodes[i].c_str(), header, content);

			headers_[header] = content;

			TRACE(_T("Head:%s Value:%s\n"), header.c_str(), content.c_str());
		}

		return cmd;
	}

	/**
	 *\fn         GetHeadContent(const char *data, std::string &head, std::string &content)
	 *\brief      得到头部信息内容。
	 *\param[in]  data		头部文本。
	 *\param[out] head		头节点名称。
	 *\param[out] content	头节点内容。
	 */
	void CSrv_RTSP::GetHeadContent(const char *data, std::string &head, std::string &content)
	{
		std::string dataStr(data);

		int index = dataStr.find(":");

		if (index != -1)
		{
			char name[MAX_PATH] = "";
			strncpy(name, data, index);

			head = name;
			content = &data[index + 1];

			return;
		}

		// 可能是GET或POST
		index = dataStr.find(" ");

		if (index != -1)
		{
			char name[MAX_PATH] = "";
			strncpy(name, data, index);

			head = name;
			content = &data[index + 1];

			index = content.find(" ");
			if (index != -1)
			{
				content.erase(index, content.length());
			}

			index = content.find(" ");
			if (index != -1)
			{
				content.erase(index, content.length());
			}
		}
		else    // POST的标记,例:-----------------------------7db1f467094c
		{
			head = data;
		}
	}

	unsigned CSrv_RTSP::RtspStreamThread(LPVOID param)
	{
		if (NULL == param) return -1;

		CSrv_RTSP *pthis = reinterpret_cast<CSrv_RTSP*>(param);
		ULONG lDataLen = 0;

		pthis->m_tRTSP_LastSendPacket = GetTickCount() - 1000 * 20;

		while (pthis->running_)
		{
			if (pthis->m_bRTSP_SendData)
			{
				DWORD tNow = GetTickCount();

				if ((tNow - pthis->m_tRTSP_LastSendPacket) > 1000)
				{
					pthis->m_tRTSP_LogicalPos += (tNow - pthis->m_tRTSP_LastSendPacket);

					while (true)
					{
#pragma warning(disable : 4244)
						int nFrameCount = pthis->m_pRTSP_rmParser->GetPacketCounts(pthis->m_dwRTSP_PushDataTime);

						if (pthis->m_pRTSP_rmParser->SeekIndex(pthis->m_dwRTSP_PushDataTime))
#pragma warning(default : 4244)
						{
							for (int i = 0; i < nFrameCount; i++)//一秒内有多个包
							{
								lDataLen = 0;
								PVOID pvBuf = pthis->buffPool_.Get(1);
								lDataLen = pthis->m_pRTSP_rmParser->GetNextFrame((PUCHAR)pvBuf);
								if (lDataLen > 0)
								{
#ifdef RTSP_DATA_LOG
									MD5 md5;
									memset(&md5, 0, sizeof(md5));
									pthis->m_MD5.Reset();
									pthis->m_MD5.Add(pBuf, lDataLen);
									pthis->m_MD5.GetHash(&md5);

									pBuf[ lDataLen - 1 ] = '\0';
									g_ProFile.m_pLog->println(_T("RTSP_OUT_DATA\n L:M:%X%X%X%X"), lDataLen, md5.w[0], md5.w[1], md5.w[2], md5.w[3]);
#endif

									pthis->outputQueue_.Add(pthis->client_, pvBuf, lDataLen);
								}
							}

							TRACE("Send %d\n", pthis->m_dwRTSP_PushDataTime);
							pthis->m_dwRTSP_PushDataTime++;
						}

						// 判断是否可以停止发送了
						if (pthis->m_dwRTSP_PushDataTime >= pthis->m_tRTSP_LogicalPos / 1000) break;
					}

					pthis->m_tRTSP_LastSendPacket = tNow;
				}
				else
                {
					::Sleep(1000*10);
                }

			}
			else
            {
				::Sleep(100);
            }
		}

		LOG(INFO) << "Exit RtspStreamThread";

        return 0;
	}



	void CSrv_RTSP::ProcessOPTION(PCLIENT client, const char *buf, int len)
	{
		/* 客户端vlc2.0.3发来的
		OPTIONS rtsp://192.168.0.1:8080/细细的红线HD中英双字.rmvb RTSP/1.0
		CSeq: 2
		User-Agent: LibVLC/2.0.3 (LIVE555 Streaming Media v2011.12.23)
		*/

		/*
		OPTIONS rtsp://192.168.0.1:8080 RTSP/1.0
		CSeq: 1
		User-Agent: RealMedia Player Version 6.0.9.1235 (linux-2.0-libc6-i386-gcc2.95)
		ClientChallenge: 9e26d33f2984236010ef6253fb1887f7
		PlayerStarttime: [28/03/2003:22:50:23 00:00]
		CompanyID: KnKV4M4I/B2FjJ1TToLycw==
		GUID: 00000000-0000-0000-0000-000000000000
		RegionData: 0
		ClientID: Linux_2.4_6.0.9.1235_play32_RN01_EN_586
		*/

		char *data = (char*)buffPool_.Get(1);
		
		sprintf(data, "RTSP/1.0 200 OK\r\n\
CSeq: %s\r\nSession: 2\r\n\
Server: Helix Server Version 9.0.8.1427 (linux-2.2-libc6-i586-server) (RealServer compatible)\r\n\
Public: OPTIONS, DESCRIBE, ANNOUNCE, PLAY, SETUP, GET_PARAMETER, SET_PARAMETER, TEARDOWN\r\n\
RealChallenge1: d12f6756d0027a12ee0afbfd64a5cedd\r\n\r\n",
headers_["CSeq"].c_str());

		LOG(INFO) << "--------------------------------RTSP_OUT_CMD:" << data;

		outputQueue_.Add(client, data, strlen(data));

		client_ = client;

		TRACE("OPTION\n");
	}

	void CSrv_RTSP::ProcessDESCRIBE(PCLIENT client, const char *buf, int len)
	{
		/*
		DESCRIBE rtsp://192.168.0.1:8080/缁嗙粏鐨勭孩绾縃D涓嫳鍙屽瓧.rmvb RTSP/1.0
		Cseq: 3
		Session: 2
		Accept: application/sdp
		Bandwidth: 10485800
		GUID: 00000000-0000-0000-0000-000000000000
		RegionData: 0
		ClientID: Linux_2.4_6.0.9.1235_play32_RN01_EN_586
		SupportsMaximumASMBandwidth: 1
		Language: en-US
		Require: com.real.retain-entity-for-setup
		*/

		/*
		DESCRIBE rtsp://192.168.0.1:8080/缁嗙粏鐨勭孩绾縃D涓嫳鍙屽瓧.rmvb RTSP/1.0
		CSeq: 3
		User-Agent: LibVLC/2.0.3 (LIVE555 Streaming Media v2011.12.23)
		Accept: application/sdp
		*/

		std::string cmd(buf);
		int index1 = cmd.find("/", 16); // 跳过"DESCRIBE rtsp://"
		int index2 = cmd.find(" RTSP/1.0");

		if ((-1 != index1) && (-1 != index2))
		{
			std::string url = cmd.substr(8, index2-8);
			std::string filename = cmd.substr(index1+1, index2-index1-1);

			std::string file = strConver_.URL_GBK(filename.c_str());
			file = root_ + "\\" + strConver_.UTF8_GBK(file.c_str());

			m_pRTSP_rmParser = new RmParser(file.c_str());
			m_pRTSP_rmParser->Initial();
			std::string sdp = m_pRTSP_rmParser->GetSDP();

			int len = sdp.length();

			if (sdp.length() <= 0)
			{
				::MessageBox(NULL, "没有找到文件!", "错误", MB_OK);
			}

			char *data = (char*)buffPool_.Get(1);

			sprintf(data, "RTSP/1.0 200 OK\r\n\
CSeq: %s\r\n\
Session: 2\r\n\
Content-base: %s\r\n\
Content-type: application/sdp\r\n\
Content-length: %d\r\n\r\n\
%s\r\n", 
headers_["CSeq"].c_str(),
url.c_str(),
sdp.length(),
sdp.c_str());

			LOG(INFO) << "--------------------------------RTSP_OUT_CMD:" << data;

			outputQueue_.Add(client, data, strlen(data));

			TRACE("DESCRIBE\n");
		}
	}


	void CSrv_RTSP::ProcessSETUP(PCLIENT client, const char *buf, int len)
	{
		m_strRTSP_SETUP.Format("RTSP/1.0 200 OK\r\nCSeq: \r\nDate: Thu, 15 Dec 2005 03:00:04 GMT\r\nSession: 2\r\n",
							   m_wRTSP_ResponseSeq++);
		
		// RealChallenge3: d67b8f21bf272fd5020e9fbb08428cfa4f213d09,sdr=abcdabcd\r\n
        // Transport: x-real-rdt/tcp;interleaved=0\r\n\r\n");

		CString strCmd(buf);
		int nAt1 = strCmd.Find(_T("rtsp://"));
		if (-1 != nAt1)
		{
			int nAt2 = strCmd.Find(_T(" RTSP/1.0"));
			if (-1 != nAt2)
			{
				m_strRTSP_TreamURL[m_nRTSP_TreamCount++] = strCmd.Mid(nAt1, nAt2 - nAt1);
			}
		}

		if (m_bFlag)
		{
			m_strRTSP_SETUP.AppendFormat("RealChallenge3: d67b8f21bf272fd5020e9fbb08428cfa4f213d09,sdr=abcdabcd\r\n\
										 Transport: x-real-rdt/tcp;interleaved=0\r\n\r\n");
			m_bFlag = FALSE;
		}
		else
		{
			m_strRTSP_SETUP.AppendFormat("Transport: x-real-rdt/tcp;interleaved=1\r\n\r\n");
		}

		char *data = (char*)buffPool_.Get(1);
		strcpy(data, (LPCSTR)m_strRTSP_SETUP);

#ifdef RTSP_CMD_LOG
		LOG(INFO) << "--------------------------------RTSP_OUT_CMD:" << data;
#endif

		outputQueue_.Add(client, data, m_strRTSP_SETUP.GetLength());

		TRACE("SETUP\n");
	}

	void CSrv_RTSP::ProcessSETPARAMETER(PCLIENT client, const char *buf, int len)
	{
		m_strRTSP_SET_PARAMETER.Format("RTSP/1.0 200 OK\r\nCSeq: %d\r\nSession: 2\r\n\r\n", m_wRTSP_ResponseSeq++);

		char *pszBuf = (char*)buffPool_.Get(1);
		strcpy(pszBuf, (LPCSTR)m_strRTSP_SET_PARAMETER);

#ifdef RTSP_CMD_LOG
		pszBuf[m_strRTSP_SET_PARAMETER.GetLength() - 1] = '\0';
		LOG(INFO) << "--------------------------------RTSP_OUT_CMD:" << pszBuf;
#endif

		outputQueue_.Add(client, pszBuf, m_strRTSP_SET_PARAMETER.GetLength());

		TRACE("SET_PARAMETER\n");

		//return;

		::Sleep(500);

		CString strCmd((char*)buf, len);
		int nAt = strCmd.Find(_T("\r\n\r\n"));

		if (nAt < strCmd.GetLength() - 5)
		{
			ProcessPLAY(client, buf, len);
		}
	}


	void CSrv_RTSP::ProcessPLAY(PCLIENT client, const char *buf, int len)
	{
		m_strRTSP_PLAY.Format("RTSP/1.0 200 OK\r\nCSeq: %d\r\nRTP-Info: ", m_wRTSP_ResponseSeq++);

		for (int i = 0; i < m_nRTSP_TreamCount; i++)
		{
			m_strRTSP_PLAY.AppendFormat("url=%s;seq=0;rtptime=0,", m_strRTSP_TreamURL[i].GetBuffer());
		}

		m_strRTSP_PLAY.Delete(m_strRTSP_PLAY.GetLength() - 1);
		m_strRTSP_PLAY.AppendFormat(_T("\r\n\r\n"));

		char *data = (char*)buffPool_.Get(1);
		strcpy(data, (LPCSTR)m_strRTSP_PLAY);

#ifdef RTSP_CMD_LOG
		LOG(INFO) << "--------------------------------RTSP_OUT_CMD:" << data;
#endif

		outputQueue_.Add(client, data, m_strRTSP_PLAY.GetLength());

		m_bRTSP_SendData = TRUE;

		UINT nThreadID = 0;
		m_hRtspStreamThread = (HANDLE)_beginthreadex(NULL, 0, RtspStreamThread, (void*)this, 0, &nThreadID);

		TRACE("PLAY\n");
	}

	void CSrv_RTSP::ProcessPAUSE(PCLIENT client, const char *buf, int len)
	{
		m_strRTSP_PAUSE.Format("RTSP/1.0 200 OK\r\nCSeq: %d\r\n\r\n", m_wRTSP_ResponseSeq++);

		char *data = (char*)buffPool_.Get(1);
		strcpy(data, (LPCSTR)m_strRTSP_PAUSE);

#ifdef RTSP_CMD_LOG
		LOG(INFO) << "--------------------------------RTSP_OUT_CMD:" << data;
#endif
		outputQueue_.Add(client, data, m_strRTSP_PAUSE.GetLength());

		m_bRTSP_SendData = FALSE;

		TRACE("PAUSE\n");
	}

}