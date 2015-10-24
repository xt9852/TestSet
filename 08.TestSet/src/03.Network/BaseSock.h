#ifndef _BASESOCK_H_
#define _BASESOCK_H_

#include <winsock2.h>
#include "process.h"
#include "Afxmt.h"

#include "BufferPool.h"
#include "..\..\PublicFiles\ProtocolDefine.h"
#include "MsgQueue.h"

#pragma comment(lib,"Ws2_32.lib")

#define		PACK_DATA_MAX_LEN	5000			// 包体的最大长度
#define		PACK_HEAD_LEN		8				// 包头长度
#define     PACK_FALG           123456789		// 包头标记
#define     PACK_FLAG_LEN		4
#define     PACK_DATA_LEN		2
#define     PACK_PROT_LEN		2

////////////////////////////////////////////////////////////////////////
class CBaseSock
{
public:
	CBaseSock();
	~CBaseSock(void);

private:
	SOCKET	m_BaseSock;
	char	m_szIp[20];
	int		m_nPort;
	char	m_szHeadBuf[ PACK_HEAD_LEN ];		// 接收协议头BUF
	char    m_szSendBuf[ PACK_DATA_MAX_LEN ];	// 发送缓冲

	CRITICAL_SECTION m_CriSection;
	CMsgQueue		 *m_pInQueue;
	CMsgQueue		 *m_pOutQueue;
	CBufferPool		 *m_pBufferPool;

	bool    m_bIsConnected;

public:
	HANDLE  m_hExit;
	bool    m_bCloseSocket;						// 自己主动关闭socket

	bool	Init( CMsgQueue *pInQueue, CMsgQueue *pOutQueue, CBufferPool *pBufferPool );
	bool	SetIpAndPort( char *pszIp,int nPort);
	bool    ConnectAndRun( void );

	static unsigned __stdcall SendThreadProc( LPVOID pParam );
	static unsigned __stdcall RecvThreadProc( LPVOID pParam );

	bool    ConnectOther();
	bool    WaitForRecv( void );

	bool	RecvPackHead( int *pnDataLen, int *pnProtocolCode );
	bool    RecvPackData( int nDataLen, char *pszDataBuf );

	bool	SendDataEx(int nProtocolCode,char * pBuff,unsigned int nDataLength);

	void	BufConstrue(TCHAR *pBuf,size_t leng ,int i,TCHAR *pBeforBuf,TCHAR *pAfterBuf);

	void    CloseBaseSock();
};

#endif