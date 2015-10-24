
#pragma once

#include "Network/Srv.h"
#include "Common/StrConver.h"
#include "rm/RmParser.h"
#include <map>
#include <string>

#define RTSP_CMD_IN_LOG
#define RTSP_CMD_LOG
//#define RTSP_DATA_LOG

namespace XT_IOCP
{

	typedef struct tagClientContext *PCLIENT;

	typedef std::map<std::string, std::string>	MAP_STR_STR;

	class CSrv_RTSP : public CSrv
	{
	public:
		CSrv_RTSP();
		~CSrv_RTSP();

	private:
		CStrConver	strConver_;

		std::string	root_;

		HANDLE		m_hRtspStreamThread;

		//CString		m_strRTSP_OPTION;
		//CString		m_strRTSP_DESCRIBE;
		CString		m_strRTSP_SETUP;
		CString		m_strRTSP_SET_PARAMETER;
		CString		m_strRTSP_PLAY;
		CString		m_strRTSP_PAUSE;
		WORD		m_wRTSP_ResponseSeq;

		CString		m_strRTSP_TreamURL[5];
		WORD		m_nRTSP_TreamSeq[5];
		WORD		m_nRTSP_TreamCount;

		BOOL		m_bRTSP_SendData;
		DWORD		m_tRTSP_LastSendPacket;
		DWORD		m_tRTSP_LogicalPos;	
		DWORD		m_dwRTSP_PushDataTime;

		RmParser	*m_pRTSP_rmParser;

		bool		m_bFlag;
		PCLIENT		client_;

		std::string cmd_;

		MAP_STR_STR	headers_;			// «Î«ÛÕ∑

		static unsigned __stdcall RtspStreamThread(LPVOID param);

		void ProcessPack(void *client, void *buf, int len, int ip, short port);

		std::string ParseRequstHead(const char *data, int len);

		void GetHeadContent(const char *data, std::string &head, std::string &content);

		void ProcessOPTION(PCLIENT client, const char *buf, int len);
		void ProcessDESCRIBE(PCLIENT client, const char *buf, int len);
		void ProcessSETUP(PCLIENT client, const char *buf, int len);
		void ProcessSETPARAMETER(PCLIENT client, const char *buf, int len);
		void ProcessPLAY(PCLIENT client, const char *buf, int len);
		void ProcessPAUSE(PCLIENT client, const char *buf, int len);

	public:
		int Start(const char *ip, unsigned short port, const char *root);
	};

}