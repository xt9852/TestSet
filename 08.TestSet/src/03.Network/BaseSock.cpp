
#include "../stdafx.h"
#include "BaseSock.h"


CBaseSock::CBaseSock()
{
	WSADATA  wsaData;
	memset( &wsaData, 0, sizeof( wsaData ));
	WSAStartup( MAKEWORD( 2, 0 ), &wsaData );

	m_pInQueue     = NULL;
	m_pOutQueue    = NULL;
	m_pBufferPool  = NULL;
	m_BaseSock     = INVALID_SOCKET;
	m_nPort        = 0;
	m_bIsConnected = false;
	m_bCloseSocket = false;

	m_szIp[0]      = '\0';
	m_szHeadBuf[0] = '\0';

	InitializeCriticalSection( &m_CriSection );
}

CBaseSock::~CBaseSock(void)
{
	SetEvent( m_hExit );
	DeleteCriticalSection( &m_CriSection );
}

//设置两面个队列的指针
bool CBaseSock::Init( CMsgQueue *pInQueue, CMsgQueue *pOutQueue, CBufferPool *pBufferPool )
{
	if( NULL == pInQueue || NULL == pOutQueue || NULL == pBufferPool )
		return false;

	m_pInQueue    = pInQueue;
	m_pOutQueue   = pOutQueue;
	m_pBufferPool = pBufferPool;

	m_hExit = CreateEvent( NULL, FALSE, FALSE, NULL );
	
	return true;
}

bool CBaseSock::SetIpAndPort( char *pszIp, int nPort )
{
	if( NULL != pszIp && nPort > 1024 && nPort < 65535 )
	{
		strcpy( m_szIp, pszIp );
		m_nPort = nPort;

		return true;
	}
	else
		return false;
}

bool CBaseSock::ConnectAndRun( void )
{
	UINT   nThreadID   = 0;
	HANDLE hThread = NULL;
	
	if( this->ConnectOther())
	{
		hThread = (HANDLE)_beginthreadex( NULL, 0, RecvThreadProc, (void*)this, 0, &nThreadID );
		CloseHandle( hThread );
	}
	else
		return false;

	nThreadID   = 0;
	hThread = (HANDLE)_beginthreadex( NULL, 0, SendThreadProc, (void*)this, 0, &nThreadID );
	CloseHandle( hThread );

	m_bCloseSocket = false;

	return true;
}

bool CBaseSock::ConnectOther()    //连接其他机器
{
	sockaddr_in addr;
	memset( &addr, 0, sizeof( addr ));

	addr.sin_family      = AF_INET;
	addr.sin_port        = htons( m_nPort );
	addr.sin_addr.s_addr = inet_addr( m_szIp );

	m_BaseSock = socket( AF_INET, SOCK_STREAM, 0 );
	int ret = connect( m_BaseSock,( const sockaddr *)&addr, sizeof( addr ));	
	
	if( ret == SOCKET_ERROR)
	{
		CloseBaseSock();
		return false;
	}
	if( ret == 0 )
	{
		m_bIsConnected = true;
		return true;
	}

	return false;
}

bool CBaseSock::WaitForRecv( void )
{
	while( m_BaseSock != INVALID_SOCKET )
	{
		int nDataLen = 0, nProtocolCode = 0;

		if( ! RecvPackHead( &nDataLen, &nProtocolCode ))   //接收包头
			break;

		BYTE *pbyDataBuf = NULL;

		if( nDataLen != 0 )
		{
			if( nDataLen > PACK_DATA_MAX_LEN )
			{
				pbyDataBuf = m_pBufferPool->GetBuffer( nDataLen );
				ASSERT( NULL != pbyDataBuf );

				char szText[ 100 ] = {""};
				sprintf( szText, "分配一个包大于5000: %d", nDataLen );
				WriteLogEx( szText );
			}
			else
			{
				//分配缓冲区,由工作线程回收
				pbyDataBuf = m_pBufferPool->GetBuffer();
				ASSERT( NULL != pbyDataBuf );
			}

			if( nDataLen > 5000  )
				nDataLen = nDataLen;

			if( ! RecvPackData( nDataLen, (char*)pbyDataBuf ))     //接收包体
			{
				m_pBufferPool->MoveToFreeBuffer( pbyDataBuf );
				WriteLogEx( "接收数据部分不成功" );
			}
			else
			{
				m_pInQueue->AddMessage( nProtocolCode, pbyDataBuf, nDataLen );
			}
		}
	}

	return false;
}
bool CBaseSock::RecvPackHead( int *pnDataLen, int *pnProtocolCode )
{
	UINT nPackHead = 0;

	fd_set readSet;
	timeval tv;
	memset( &tv, 0, sizeof( tv ));
	tv.tv_sec  = 5;
	int sumLen = 0;

	memset( m_szHeadBuf, 0, PACK_HEAD_LEN );

	while( m_BaseSock != INVALID_SOCKET )
	{
		FD_ZERO( &readSet );
		FD_SET( m_BaseSock, &readSet ); 
		int ret = select( 0, &readSet, NULL, NULL, &tv );

		if( ( ret == SOCKET_ERROR ) || ( m_BaseSock == INVALID_SOCKET )) break;
		
		if( ( ret == 0 ) || ( ! FD_ISSET( m_BaseSock, &readSet ))) continue;

		int len = recv( m_BaseSock, m_szHeadBuf + sumLen, ( PACK_HEAD_LEN - sumLen ) , 0);

		if( len <= 0 )
			break;
		
		sumLen += len;

		if( sumLen == PACK_HEAD_LEN ) 
		{
			memcpy( (void*)&nPackHead,     (void*)m_szHeadBuf, PACK_FLAG_LEN );
			memcpy( (void*)pnDataLen,      (void*)&m_szHeadBuf[ PACK_FLAG_LEN ], PACK_DATA_LEN );
			memcpy( (void*)pnProtocolCode, (void*)&m_szHeadBuf[ PACK_FLAG_LEN + PACK_DATA_LEN ], PACK_PROT_LEN );

			if( PACK_FALG == nPackHead )
				return true;
			else
			{
				WriteLogEx("不是包头标记");
			}
		}
		else  	
			continue;
	}
	return false;
}
bool CBaseSock::RecvPackData( int nDataLen, char *pszDataBuf )
{
	if( NULL == pszDataBuf )
		return false;

	fd_set readSet;
	timeval tv;
	memset( &tv, 0, sizeof( tv ));
	tv.tv_sec  = 5;
	int sumLen = 0;

	memset( pszDataBuf, 0, nDataLen );

	while( m_BaseSock != INVALID_SOCKET )
	{
		FD_ZERO( &readSet );
		FD_SET( m_BaseSock, &readSet ); 
		int ret = select( 0, &readSet, NULL, NULL, &tv );

		if( ( ret == SOCKET_ERROR ) || ( m_BaseSock == INVALID_SOCKET )) break;
		if( ( ret == 0 ) || ( ! FD_ISSET( m_BaseSock, &readSet )))		continue;

		int len = recv( m_BaseSock, pszDataBuf + sumLen, ( nDataLen - sumLen ) , 0 );

		if( len <= 0 )
		{
			m_bIsConnected = false;
			break;
		}
				
		sumLen = sumLen + len;

		if( sumLen < nDataLen ) 
		    continue;
		else
			return true;
	}
	return false;
}

unsigned CBaseSock::RecvThreadProc( LPVOID pParam )
{
	if( NULL == pParam )
		return -1;

	CBaseSock *pthis = reinterpret_cast<CBaseSock*>( pParam );

	if( ! pthis->WaitForRecv())
	{
		if( ! pthis->m_bCloseSocket )
			pthis->m_pInQueue->AddMessage( TO_UP_SOCKET_CLOSE, NULL, 0 );

		//MessageBox( NULL, _T("与游戏服务器的连接已断开!"), _T("错误"), MB_OK );
	}

	return 0;
}

unsigned CBaseSock::SendThreadProc( LPVOID pParam )
{
	if( NULL == pParam )
		return -1;

	CBaseSock *pthis = reinterpret_cast<CBaseSock*>( pParam );

	char *pszBuffer   = NULL;
	char **ppszBuffer = &pszBuffer;	
	DWORD dwDataLen   = 0;
	DWORD dwProtoNum  = 0;

	try
	{
		while( true )
		{
			if( WaitForSingleObject( pthis->m_hExit, 1 ) == WAIT_OBJECT_0 )
				return 0;

			if( pthis->m_pOutQueue->HasQueueElement())
			{
				long count = pthis->m_pOutQueue->GetMsgCount();

				pszBuffer  = NULL;
				dwProtoNum = 0;
				dwDataLen  = 0;

				if( pthis->m_pOutQueue->GetMessageEx( dwProtoNum, ppszBuffer, dwDataLen ))
				{
					pthis->SendDataEx( dwProtoNum, (char*)pszBuffer, dwDataLen );					
					pthis->m_pBufferPool->MoveToFreeBuffer( (BYTE*)pszBuffer );//发送成功后回收Buffer
				}
			}
		}
	}
	catch(...)
	{
		char szText[ 100 ] = {""};
		sprintf( szText, "CBaseSock::SendThreadProc ErrorCode:%d", ::GetLastError());
		WriteLogEx( szText );
	}

	return 0;
}

bool CBaseSock::SendDataEx(int nProtocolCode, char *pBuff, unsigned int nDataLength )
{
	if( ! m_bIsConnected || NULL == pBuff )
		return false;

	EnterCriticalSection( &m_CriSection );  //同步
	
	int  nSumLength = nDataLength + PACK_HEAD_LEN; //nBufLength可以为0，只发送四个字节数据，两个字节是长度(长度为0),两个字节是协议号

	if( nSumLength > PACK_DATA_MAX_LEN )
	{
		char szText[100] = {""};
		sprintf( szText, "BaseSock SendDataEx > 5000: %d", nDataLength );
		WriteLogEx( szText );

		LeaveCriticalSection(&m_CriSection);
		return false;
	}

	UINT nPackHead = PACK_FALG;

	memcpy( pBuff,								  (void*)&nPackHead,     PACK_FLAG_LEN );
	memcpy( pBuff + PACK_FLAG_LEN,				  (void*)&nDataLength,   PACK_DATA_LEN );
	memcpy( pBuff + PACK_FLAG_LEN + PACK_DATA_LEN,(void*)&nProtocolCode, PACK_PROT_LEN );

	fd_set writeSet;
	struct timeval timeout;
	memset( &timeout, 0, sizeof( timeout ));
	timeout.tv_sec = 5;

	int sumSendlength = 0;
	
	while( m_BaseSock != INVALID_SOCKET )
	{	
		FD_ZERO( &writeSet );
		FD_SET( m_BaseSock, &writeSet ); 
		int ret = select( 0, NULL, &writeSet, NULL, &timeout );

		if( ( ret == SOCKET_ERROR ) || ( m_BaseSock == INVALID_SOCKET )) break;
		
		if( ( ret == 0 ) || ( ! FD_ISSET( m_BaseSock, &writeSet ))) continue;

		int sendlength = send( m_BaseSock, pBuff + sumSendlength, nSumLength - sumSendlength, 0 );

		if( sendlength == 0) continue;
		if( sendlength < 0 )
		{
			m_bIsConnected = false;
			m_BaseSock = INVALID_SOCKET;
			break;
		}

		sumSendlength += sendlength;
		 
		if( nSumLength - sumSendlength > 0 )
		{
			continue;
		}
		else
		{
			LeaveCriticalSection(&m_CriSection);
			return true;
		}
	}

	LeaveCriticalSection(&m_CriSection);
	return false;		
}

void CBaseSock::BufConstrue( TCHAR *pBuf, size_t leng, int i, TCHAR *pBeforBuf, TCHAR *pAfterBuf )
{

	TCHAR *ptemp;
    ptemp = (TCHAR *)_tcschr( pBuf, i );
	if( ( ptemp - pBuf ) >= leng )
		ptemp =NULL;

    if( ptemp )
	{
		_tcsncpy( pBeforBuf, pBuf, ptemp - pBuf );
		if( pAfterBuf != NULL )
			_tcsncpy( pAfterBuf, ptemp + 1, leng - ( ptemp - pBuf + 1 ));
	}
	else
		_tcsncpy( pBeforBuf, pBuf, leng );
}

void  CBaseSock::CloseBaseSock()
{
	m_bIsConnected = false;
	m_bCloseSocket = true;

	SetEvent( m_hExit );

	if( m_BaseSock != INVALID_SOCKET )
	{
		closesocket( m_BaseSock );
		m_BaseSock = INVALID_SOCKET;
	}
}