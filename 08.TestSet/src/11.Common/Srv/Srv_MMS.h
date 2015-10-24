
#pragma once
#include "Network/Srv.h"

namespace XT_IOCP
{

	typedef struct _tagMMS_CMD
	{
		DWORD	dwFlag1;		// 0x00000001
		DWORD	dwFlag2;		// 0xb00bface
		DWORD	dwDataLen;		// "MMS "后数据长
		DWORD	dwFlag3;		// "MMS "
		DWORD	dwAlign1;		// 以8字节对齐
		DWORD	dwSeqNum;		// 序号
		UINT64	uTimeStamp;		// 时间戳
		DWORD	dwAlign2;		// 以8字节对齐
		USHORT	sCmdNum;		// 命令号
		USHORT	sDirect;		// 发送方向,0x03指明客户端发往服务器,0x04指明服务器发往客户端
		char	szData[1];		// 消息内容
	}MMS_HEAD,*PMMS_HEAD;

	class CSrv_MMS : public CSrv
	{
	public:
		CSrv_MMS(void);
		~CSrv_MMS(void);

	private:    
		HANDLE   m_hRtspStreamThread;
		PCLIENT  m_pClient;

		void ProcessPack(PCLIENT pClient, DWORD dwDataLen, PVOID pvBuf, UINT64 nIP[2], WORD wPort);

		void SetU32(BYTE **pBuf, DWORD dwValue);
		void SetStr(BYTE **pBuf, LPCSTR szStr);

	public:
		int Start(LPCTSTR pszIP, const int nPort);
		int Connect(LPCTSTR pszIP, const int nPort);
		int Login(void);
	};
}