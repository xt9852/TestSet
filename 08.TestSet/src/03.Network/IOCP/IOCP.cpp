
#include "StdAfx.h"
#include "IOCP.h"
#include "BuffPool.h"
#include "PrePack.h"
#include "PackQueue.h"
#include <process.h>
#include <WS2tcpip.h> // freeaddrinfo


namespace XT_IOCP
{

	/**
	 *\fn         IOCP()
	 *\brief      默认构造函数。
	 */
	IOCP::IOCP(void)
		:running_(false),
		completionPort_(NULL),
		idelThread_(NULL),
		sendThread_(NULL),
		acceptEx_(NULL),
		acceptEventesCount_(0),
		inputQueue_(NULL),
		outputQueue_(NULL),
		buffPool_(NULL),
		buffSize_(0),
		postSocketCount_(0)
	{
		::InitializeCriticalSection(&csAccept_);
		::InitializeCriticalSection(&csRead_);
		::InitializeCriticalSection(&csWrite_);
		::InitializeCriticalSection(&csPostRead_);
		::InitializeCriticalSection(&csWork_);
		::InitializeCriticalSection(&csListenSocket_);

		// 初使化socket
		WSADATA wsd = {0};
		::WSAStartup(MAKEWORD(2, 2), &wsd);
	}

	/**
	 *\fn         ~IOCP()
	 *\brief      析构函数。
	 */
	IOCP::~IOCP(void)
	{
		Stop();

		if (NULL != completionPort_)
		{
			CloseHandle(completionPort_);
			completionPort_ = NULL;
		}

		::DeleteCriticalSection(&csAccept_);
		::DeleteCriticalSection(&csRead_);
		::DeleteCriticalSection(&csWrite_);
		::DeleteCriticalSection(&csPostRead_);
		::DeleteCriticalSection(&csWork_);
		::DeleteCriticalSection(&csListenSocket_);

		::WSACleanup();
	}

	/**
	 *\fn         Stop()
	 *\brief      停止。
	 *\return     是否成功
	 */
	bool IOCP::Stop(void)
	{
        running_ = false;

		EndAllThread();

		::EnterCriticalSection(&csListenSocket_);

		LISTEN_INFO_MAP::iterator iter = listenInfoMap_.begin();

		for (; iter != listenInfoMap_.end(); ++iter)
		{
			CloseHandle(iter->second.acceptEvent);
			CloseClient(iter->second.listenClient, NULL);			
		}

		listenInfoMap_.clear();

		::LeaveCriticalSection(&csListenSocket_);

		return true;
	}

	/**
	 *\fn         EndAllThread()
	 *\brief      结束工作线程(工作线程，发送线程，连接事件线程)。
	 */
	void IOCP::EndAllThread(void)
	{
		for (unsigned int i = 0; i < workThreadList_.size(); i++)
		{
			::PostQueuedCompletionStatus(completionPort_, 0, NULL, NULL);
		}

		workThreadList_.clear();

		::TerminateThread(idelThread_, IOCP_IDLE_THREAD_EXIT);
		::CloseHandle(idelThread_);
		idelThread_ = NULL;

		::TerminateThread(sendThread_, IOCP_SEND_THREAD_EXIT);
		::CloseHandle(sendThread_);
		sendThread_ = NULL;
	}

    /**
	 *\fn         GetTcpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr)
	 *\brief      得到TCP地址，主要是用于IPV6，也可用于IPV4。
	 *\param[in]  ip      IP地址。
	 *\param[in]  port    端口地址。
	 *\param[in]  ipv6    是否是IPV6。
	 *\param[out] addr    地址结构。
	 *\return     是否成功(0成功，其它失败)
	 */
	int IOCP::GetTcpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr)
	{
		char portStr[10] = "";
		sprintf(portStr, "%d", port);

		struct addrinfo info = {0};
		info.ai_family = ipv6?AF_INET6:AF_INET;
		info.ai_socktype = SOCK_STREAM;
		info.ai_protocol = IPPROTO_TCP;

		return getaddrinfo(ip, portStr, &info, addr);
	}

	/**
	 *\fn         GetUdpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr)
	 *\brief      得到UDP地址，主要是用于IPV6，也可用于IPV4。
	 *\param[in]  ip      IP地址。
	 *\param[in]  port    端口地址。
	 *\param[in]  ipv6    是否是IPV6。
	 *\param[out] addr    地址结构。
	 *\return     是否成功(0成功，其它失败)
	 */
	int IOCP::GetUdpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr)
	{
		char portStr[10] = "";
		sprintf(portStr, "%d", port);

		struct addrinfo info = {0};
		info.ai_family = ipv6?AF_INET6:AF_INET;
		info.ai_socktype = SOCK_DGRAM;
		info.ai_protocol = IPPROTO_UDP;

		return getaddrinfo(ip, portStr, &info, addr);
	}

    /**
	 *\fn         GetIpAddr(addrinfo *addr)
	 *\brief      得到IP地址。
	 *\param[in]  addr      地址地址。
	 *\return     IP地址。
	 */
    int IOCP::GetIpAddr(addrinfo *addr)
    {
        if (NULL == addr) return 0;

        return ((UCHAR)addr->ai_addr->sa_data[5] << 24) | 
            ((UCHAR)addr->ai_addr->sa_data[4] << 16) |
            ((UCHAR)addr->ai_addr->sa_data[3] << 8) |
            (UCHAR)addr->ai_addr->sa_data[2];
    }

    /**
	 *\fn         GetPort(addrinfo *addr)
	 *\brief      得到端口。
	 *\param[in]  addr      地址地址。
	 *\return     端口。
	 */
    int IOCP::GetPort(addrinfo *addr)
    {
        if (NULL == addr) return 0;

        return ((UCHAR)addr->ai_addr->sa_data[1] << 8) | (UCHAR)addr->ai_addr->sa_data[0];
    }

	/**
	 *\fn         Init(int cmdType, PackQueue *inputQueue, PackQueue *outputQueue, BuffPool *buffPool)
	 *\brief      初使化。
	 *\param[in]  cmdType      命令类型。
	 *\param[in]  inputQueue   输入队列。
	 *\param[in]  outputQueue  输出队列。
	 *\param[in]  buffPool     缓冲池。
	 *\return     是否成功
	 */
	int IOCP::Init(int cmdType, PackQueue *inputQueue, PackQueue *outputQueue, BuffPool *buffPool)
	{
		if (NULL == inputQueue || NULL == outputQueue || NULL == buffPool)
		{
			return IOCP_PARA_ERROR;
		}

		inputQueue_  = inputQueue;
		outputQueue_ = outputQueue;
		buffPool_    = buffPool;
		buffSize_    = buffPool->getSize();

#ifdef _DEBUG
		clientPool_.name_ = "clientPool_";
		operatePool_.name_ = "operatePool_";
#endif		

		if (!clientPool_.Init(cmdType, inputQueue, buffPool))
		{
			return IOCP_INIT_CLIENT_POOL_FAIL;
		}

		return InitIOCP();
	}

	/**
	 *\fn         InitIOCP()
	 *\brief      初使化完成端口。
	 *\return     是否成功(0成功，其它失败)
	 */
	int IOCP::InitIOCP()
	{
		if (running_)
		{
			return IOCP_CREATE_EXIT_EVENT_FAIL;
		}
        
        running_ = true;

		// 创建完成端口
		completionPort_ = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if (NULL == completionPort_)
		{
			return IOCP_CREATE_IOCP_FAIL;
		}

		// 取得系统中CPU的数目,创建CPU的数目*2+2个线程
		SYSTEM_INFO SysInfo = {0};
		::GetSystemInfo(&SysInfo);
		int cpuCount = SysInfo.dwNumberOfProcessors;
		int nWorkerThreadCount = 1;//SysInfo.dwNumberOfProcessors * 2 + 2;

		// 启动工作线程
		for (int i = 0; i < nWorkerThreadCount; i++) 
		{
			unsigned int threadID = 0;
			HANDLE workThread = (HANDLE)_beginthreadex(NULL, 0, WorkThread, this, 0, &threadID);
			if (NULL != workThread)
			{
				workThreadList_.push_back(workThread);
			}
		}

		// 创建工作线程不成功
		if (workThreadList_.size() <= 0)
		{
			return IOCP_CREATE_WORK_THREAD_FAIL;
		}

		// 启动发送线程(安全设置,栈大小使用默认的,线程函数,参数,标记,线程ID)
// 		unsigned int threadId = 0;
// 		sendThread_ = (HANDLE)_beginthreadex(NULL, 0, SendThread, this, 0, &threadId);
// 		if (NULL == sendThread_)
// 		{
//             running_ = false;
// 			this->EndAllThread();
// 			return IOCP_CREATE_SEND_THREAD_FAIL;
// 		}

		// 启动Idle线程(安全设置,栈大小使用默认的,线程函数,参数,标记,线程ID)
		unsigned int threadId = 0;
		idelThread_ = (HANDLE)_beginthreadex(NULL, 0, IdleThread, this, 0, &threadId);
		if (NULL == idelThread_)
		{
            running_ = false;
			this->EndAllThread();
			return IOCP_CREATE_IDLE_THREAD_FAIL;
		}

		return S_OK;
	}

	/**
	 *\fn         AddAccepEvent(int listenSocket)
	 *\brief      添加客户端句柄不足事件。
	 *\n		  将网络FD_ACCEPT事件注册到hAcceptEvent，
	 *\n		  这样当可用AcceptEx调用被耗尽的时候，就会触发FD_ACCEPT事件，
	 *\n		  然后IdleThread里的WaitForSingleObject就会成功返回，
	 *\n		  导致PostAcceptEx被调用，现次分配SOKCET
	 *\param[in]  listenSocket  监听句柄。
	 *\return     事件句柄
	 */
	HANDLE IOCP::AddAccepEvent(int listenSocket)
	{   
		HANDLE acceptEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		if (NULL == acceptEvent)
		{
			return NULL;
		}

		int ret = WSAEventSelect(listenSocket, acceptEvent, FD_ACCEPT);
		if (SOCKET_ERROR == ret)
		{
			CloseHandle(acceptEvent);
			return NULL;
		}

		return acceptEvent;
	}

	/**
	 *\fn         PostAcceptSocket(int listenSocket, PCLIENT listenClient)
	 *\brief      添加待绑定的客户端句柄,连续发出SOCKET_ADD_NUM个AcceptEx调用。
	 *\param[in]  listenSocket  监听句柄。
	 *\param[in]  listenClient  监听客户端对象。
	 *\return     是否成功(0成功，其它失败)
	 */
	int IOCP::PostAcceptSocket(int listenSocket, PCLIENT listenClient)
	{
		if (NULL == listenClient)
		{
			return IOCP_PARA_ERROR;
		}

		if (NULL == acceptEx_)
		{
			DWORD result = 0;
			GUID GUIDAcceptEx = WSAID_ACCEPTEX;

			// 获取微软SOCKET扩展函数指针，有一个就行
			int ret = WSAIoctl(listenSocket, 
				SIO_GET_EXTENSION_FUNCTION_POINTER, 
				&GUIDAcceptEx, 
				sizeof(GUIDAcceptEx),
				&acceptEx_, 
				sizeof(acceptEx_), 
				&result, 
				NULL, 
				NULL);

			if (SOCKET_ERROR == ret)
			{
				closesocket(listenSocket);
				return IOCP_GET_SOCK_ACCEPT_FAIL;
			}
		}

		int successCount = 0;

		for (int i = 0; i < SOCKET_ADD_NUM; i++)
		{
			SOCKET acceptSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
			if (INVALID_SOCKET == acceptSocket)
			{
				continue;
			}

			// 没有延时(较小的包组装为更大的帧然后再发送)
			int option = 1;
			int ret = setsockopt(acceptSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));
			if (SOCKET_ERROR == ret)
			{
				closesocket(acceptSocket);
				TRACE(_T("setsockopt error:%d\n"), ::GetLastError());
				continue;
			}

			// 设置缓冲区大小
			option = 1024*1024;
			ret = setsockopt(acceptSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&option, sizeof(option)); 
			if (SOCKET_ERROR == ret)
			{
				closesocket(acceptSocket);
				TRACE(_T("setsockopt error:%d\n"), ::GetLastError());
				continue;
			}
			
			// 将socket设置为非阻塞
			option = 1;
			ret = ioctlsocket(acceptSocket, FIONBIO, (u_long*)&option);
			if (SOCKET_ERROR == ret)
			{
				closesocket(acceptSocket);
				TRACE(_T("ioctlsocket error:%d\n"), ::GetLastError());
				continue;
			}

			POPERATE operation = operatePool_.Get();
			operation->sock    = acceptSocket;
			operation->type    = OP_ACCEPT;
			operation->buf.buf = (char*)buffPool_->Get(1);
			operation->buf.len = buffSize_;
			operation->udp     = false;
			operation->sent    = false;

			/*
			typedef
				BOOL
				(PASCAL FAR * LPFN_ACCEPTEX)(
				__in SOCKET sListenSocket,
				__in SOCKET sAcceptSocket,
				__in PVOID lpOutputBuffer,
				__in DWORD dwReceiveDataLength,
				__in DWORD dwLocalAddressLength,
				__in DWORD dwRemoteAddressLength,
				__out LPDWORD lpdwBytesReceived,
				__inout LPOVERLAPPED lpOverlapped
				);
			*/

			// 投递IoAccept,如果提供了第四个参数，则这个函数会一直等到收到第一块数据才会返回。   
			int bytes = 1;
			int addrSize = sizeof(SOCKADDR_IN) + 16;

			ret = acceptEx_(listenSocket, 
				operation->sock, 
				(void*)operation->buf.buf,
				operation->buf.len - addrSize * 2,	// 如果不减后面的删除Buff时会出错
				addrSize, 
				addrSize,							// 如果不加16会出122错误
				(DWORD*)&bytes, 
				&(operation->overlapped));

			if (FALSE == ret)
			{
				int error = ::WSAGetLastError();
				if (ERROR_IO_PENDING != error)
				{
					//g_ProFile.m_pLog->println(LOG_ERROR, _T("PostAcceptSocket Error:%d Socket:%d"), error, listenSocket);
					closesocket(acceptSocket);
					continue;
				}
			}

			successCount++;
		}

		postSocketCount_ += successCount;

		TRACE(_T("PostAcceptSocket all:%d\n"), postSocketCount_);
		return successCount;
	}

	/**
	 *\fn         SendThread(LPVOID data)
	 *\brief      发送线程,从输出队列中读到数据并投递写操作。
	 *\param[in]  data    线程参数。
	 *\return     是否成功
	 */
	unsigned IOCP::SendThread(LPVOID data)
	{
		if (NULL == data)
		{
			return IOCP_PARA_ERROR;
		}

		IOCP *pThis = reinterpret_cast<IOCP*>(data);

		try
		{
			return pThis->SendThreadProc();
		}
		catch (...)
		{
			//g_ProFile.m_pLog->println(LOG_EXCEPT, _T("SendThreadProc ErrorCode:%d"), ::GetLastError());
			return IOCP_SEND_THREAD_EXCEPT;
		}
	}

	/**
	 *\fn         SendThreadProc()
	 *\brief      发送线程处理函数。
	 *\return     是否成功
	 */
	unsigned IOCP::SendThreadProc(void)
	{
		PCLIENT client = NULL;
		void   *buf       = NULL;
		int   len   = 0;
		int     ip      = {0};
		short    port       = 0;
		short    waitTime   = 1;
		short    times      = 0;

		while (running_)
		{
			if (outputQueue_->Get((void**)&client, &buf, len, ip, port))
			{
				SendData(client, buf, len, ip, port);
				waitTime = 0;
			}
			else
			{
				::Sleep(waitTime); // 如果不加它CPU将100%
				if (++times > 10000)
				{
					times = 0;
					waitTime = 1;
				}
			}
		}

		return IOCP_SEND_THREAD_EXIT;
	}

	/**
	 *\fn         SendData(PQueueNode node)
	 *\brief      发送数据。
	 *\param[in]  node      队列节点。
	 *\return     是否成功
	 */
	bool IOCP::SendData(PQueueNode node)
	{
		bool ret = SendData((PCLIENT)node->client, 
			node->pack,
			node->len,
			node->ip,
			node->port);

		outputQueue_->FreeItem(node);

		return ret;
	}

	/**
	 *\fn         SendData(PQueueNode node)
	 *\brief      发送TCP数据。
	 *\param[in]  client   客户端。
	 *\param[in]  buf      数据。
	 *\param[in]  len      数据长。
	 *\return     是否成功
	 */
	bool IOCP::SendData(PCLIENT client, void *buf, int len)
	{
		// 锁定，发送成功后再解锁
		POPERATE operate = operatePool_.Get();
		operate->sock    = client->sock;
		operate->type    = OP_WRITE;
		operate->buf.buf = (char*)buf;
		operate->buf.len = len;
		operate->udp     = false;
		operate->sent    = false;

		::PostQueuedCompletionStatus(completionPort_, 0, (DWORD)client, &(operate->overlapped));
		return true;
	}

	/**
	 *\fn         SendData(PQueueNode node)
	 *\brief      发送UDP数据。
	 *\param[in]  client   客户端。
	 *\param[in]  buf      数据。
	 *\param[in]  len      数据长。
	 *\param[in]  ip       IP地址。
	 *\param[in]  port     端口地址。
	 *\return     是否成功
	 */
	bool IOCP::SendData(PCLIENT client, void *buf, int len, int ip, unsigned short port)
	{
		// 锁定，发送成功后再解锁
		POPERATE operate = operatePool_.Get();
		operate->sock    = client->sock;
		operate->type    = OP_WRITE;
		operate->buf.buf = (char*)buf;
		operate->buf.len = len;
		operate->udp     = (0 != ip);
		operate->sent    = false;
		operate->setIp(ip);
		operate->setPort(port);

		::PostQueuedCompletionStatus(completionPort_, 0, (DWORD)client, &(operate->overlapped));
		return true;
	}

	/**
	 *\fn         IdleThread(LPVOID data)
	 *\brief      等待线程,守护hAcceptEvent网络事件，当有FD_ACCEPT时触发，
	 *\n		  说明待绑定的客户端已经用尽，需再投递。
	 *\param[in]  data    线程参数。
	 *\return     是否成功
	 */
	unsigned IOCP::IdleThread(LPVOID data)
	{
		if (NULL == data)  return 1;

		IOCP* pThis = reinterpret_cast<IOCP*>(data);

		try
		{
			return pThis->IdleThreadProc();
		}
		catch (...)
		{
			//g_ProFile.m_pLog->println(LOG_EXCEPT, _T("IdleThreadProc ErrorCode:%d"), ::GetLastError());
			return IOCP_IDLE_THREAD_EXCEPT;
		}
	}

	/**
	 *\fn         IdleThreadProc()
	 *\brief      等待线程处理函数。
	 *\return     是否成功
	 */
	unsigned IOCP::IdleThreadProc(void)
	{
		while (running_)
		{
			if (0 == acceptEventesCount_)
			{
				Sleep(100);
				continue;
			}

			DWORD ret = ::WaitForMultipleObjects(acceptEventesCount_, acceptEventes_, false, 10000); // 10秒

			switch (ret)
			{
			case WAIT_FAILED:
				{
					//g_ProFile.m_pLog->println(LOG_INFO, _T("IdleThreadProc WaitForMultipleObjects Err:%d\n"), ::GetLastError());
					continue;
				}
			case WAIT_TIMEOUT:  // 超时检测一下其它线程是否还在运行
				{
					DWORD code = 0;
					if (!GetExitCodeThread(idelThread_, &code) || (code != STILL_ACTIVE))
					{
						//g_ProFile.m_pLog->println(LOG_INFO, _T("IdelThread dead:%d ExitCode:%d"), idelThread_, code);
					}

					code = 0;
					if (!GetExitCodeThread(sendThread_, &code) || (code != STILL_ACTIVE))
					{
						//g_ProFile.m_pLog->println(LOG_INFO, _T("SendThread dead:%d ExitCode:%d"), sendThread_, code);
					}
					break;
				}
			default:
				{
					int index = ret - WAIT_OBJECT_0;
					this->PostAcceptSocket(listenInfoMap_[index].listenSocket, listenInfoMap_[index].listenClient);

					// 同时检测其他的事件
					while (index < acceptEventesCount_)
					{
						ret = WaitForMultipleObjects(acceptEventesCount_ - index, &acceptEventes_[index], false, 0);
						
						switch (ret)
						{
						case WAIT_FAILED:
							{
								continue;
							}
						case WAIT_TIMEOUT:
							{
								index = acceptEventesCount_; // 退出检测,因为没有被触发的对象了.
								break;
							}
						default:
							{
								index = ret - WAIT_OBJECT_0;
								PostAcceptSocket(listenInfoMap_[index].listenSocket, listenInfoMap_[index].listenClient);
							}
							break;
						}
					}
					break;
				}
			}
		}

		return IOCP_IDLE_THREAD_EXIT;
	}

	/**
	 *\fn         WorkThread(LPVOID data)
	 *\brief      工作线程。
	 *\param[in]  data    线程参数。
	 *\return     是否成功
	 */
	unsigned IOCP::WorkThread(LPVOID data)
	{
		if (NULL == data)  return IOCP_THREAD_PARA_ERROR;

		IOCP* pThis = reinterpret_cast<IOCP*>(data);

		try
		{
			return pThis->WorkThreadProc();
		}
		catch (...)
		{
			//g_ProFile.m_pLog->println(LOG_EXCEPT, _T("CIOCP::WorkThread ErrorCode:%d"), ::GetLastError());
			return IOCP_WORK_THREAD_EXCEPT;
		}
	}

	/**
	 *\fn         WorkThreadProc()
	 *\brief      工作线程处理函数。
	 *\return     是否成功
	 */
	unsigned IOCP::WorkThreadProc(void)
	{
		BOOL        ret     = 0;
		DWORD       size    = 0;
		DWORD       error   = 0;
		POPERATE    operate = NULL;
		PCLIENT     client  = NULL;

		while (running_)
		{
			ret = ::GetQueuedCompletionStatus(completionPort_, &size, (PULONG_PTR)&client, (LPOVERLAPPED*)&operate, INFINITE);

			if (!ret)          // 操作不成功
			{
				error = ::WSAGetLastError();

				if (64 == error)
				{
					CloseClient(client, operate);
				}

				// 64    指定的网络名不再可用
				// 234   表示有数据还没有接受完。应该再次调用WSARecv
				// 995   由于线程退出或应用程序请求，已放弃 I/O 操作
				// 998   内存分配访问无效
				// 10014 WSARecv 投递缓冲区要对齐不然就10014
				// 10035 无法立即完成一个非阻挡性套接字操作
				// 10038 在一个非套接字上尝试了一个操作
				// 10054 远程主机强迫关闭了一个现有的连接
				// 10061 由于目标机器积极拒绝，无法连接
				TRACE(_T("IOCP Error:%d 0x%x 0x%x\n"), error, client, operate);
			}
			else if (NULL != client && NULL != operate)
			{
				switch (operate->type)
				{
				case OP_WRITE:          // 发送数据
					{
						OPWrite(client, operate);
						break;
					}
                case OP_WRITE_FINISH:   // 发送完成
                    {
                        OPWriteFinish(client, operate);
                        break;
                    }
				case OP_READ:           // 接收数据
					{
						if (!OPRead(size, client, operate))
							continue;
						else
							PostReadOperate(client, operate);
						break;
					}
				case OP_ACCEPT:         // 在收到数据后才会触发(TCP)
					{
						if (0 != size)
						{
							PCLIENT newClient = OPAccept(client, operate);

							if (NULL == newClient) continue;

							if (!OPRead(size, newClient, operate)) continue;

							if (!PostReadOperate(newClient, operate)) continue;
						}
						else     // 直接关闭此客户端，不必向上层通知(没有数据,也没连接成功)
						{
							CloseClient(NULL, operate);
							TRACE(_T("OP_Accept: close\n"));
						}
						break;
					}
				default:
					break;
				}
			}
			else                // 当客户信息和完成信息都是空时（自己投递的）退出此线程
			{
				TRACE(_T("CIOCP.WorkThreadProc Quit\n"));
				break;
			}
		}
		return IOCP_WORK_THREAD_EXIT;
	}

	/**
	*\fn         OPAccept(PCLIENT client, POPERATE operate)
	*\brief      绑定操作,绑定连接的客户端。
	*\param[in]  client  监听句柄的客户端对象(client->socket为监听socket)。
	*\param[in]  operate 操作对象(operate->socket为客户端socket)。
	*\return     连接的客户端对象
	*/
	PCLIENT IOCP::OPAccept(PCLIENT client, POPERATE operate)
	{
		//::EnterCriticalSection(&csAccept_);

		// 建立关联
		int ret = setsockopt(operate->sock, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char*)&(client->sock), sizeof(client->sock));
		if (SOCKET_ERROR == ret)    // 当用户链接成功但没有发送数据时(超时),会执行此函数
		{
			closesocket(operate->sock);
			operatePool_.FreeItem(operate);
			//::LeaveCriticalSection(&csAccept_);
			return NULL;
		}

		PCLIENT newClient = clientPool_.Get(operate->sock);
		if (NULL == newClient)
		{
			//g_ProFile.m_pLog->println(LOG_ERROR, _T("Accept GetClient error"));
			closesocket(operate->sock);
			operatePool_.FreeItem(operate);
			//::LeaveCriticalSection(&csAccept_);
			return NULL;
		}

		// 将新建的套接字关联到完成端口
		ret = (int)CreateIoCompletionPort((HANDLE)newClient->sock, completionPort_, (DWORD_PTR)newClient, 0);
		if (NULL == ret)
		{
			CloseClient(newClient, operate);
			//::LeaveCriticalSection(&csAccept_);
			return NULL;
		}

		//::LeaveCriticalSection(&csAccept_);
		return newClient;
	}

	/**
	 *\fn         OPRead(int size, PCLIENT client, POPERATE operate)
	 *\brief      读操作。
	 *\param[in]  size    数据长。
	 *\param[in]  client  客户端对象。
	 *\param[in]  operate 操作对象。
	 *\return     是否成功
	 */
	bool IOCP::OPRead(int size, PCLIENT client, POPERATE operate)
	{
		//::EnterCriticalSection(&csRead_);

		if (0 == size)       // 向上层通知客端已关闭(TCP)
		{
			TRACE(_T("IOCP recv null data Error:%d\n"), ::GetLastError());
			CloseClient(client, operate);
			//::LeaveCriticalSection(&csRead_);
			return false;
		}

		if (!operate->udp) // TCP包
		{
			client->prePack->Add(client, size, operate->buf.buf);
		}
		else // UDP包
		{
			inputQueue_->Add(client, operate->buf.buf, size, operate->getIp(), operate->getPort());

            //static int a = 0;
            //TRACE("%d\n", a++);
		}

		operate->buf.buf = (char*)buffPool_->Get(1);
		operate->buf.len = buffSize_;

		//::LeaveCriticalSection(&csRead_);
		return true;
	}

	/**
	 *\fn         OPWrite(PCLIENT client, POPERATE operate)
	 *\brief      写操作。
	 *\param[in]  client  客户端对象。
	 *\param[in]  operate 操作对象。
	 *\return     是否成功
	 */
	bool IOCP::OPWrite(PCLIENT client, POPERATE operate)
	{
		//::EnterCriticalSection(&csWrite_);

		// 发送完成
// 		if (operate->sent)
// 		{
// 			operate->sent = false;
// 			operatePool_.FreeItem(operate);
// 			//::LeaveCriticalSection(&csWrite_);
// 			return true;
// 		}

SEND_BEGIN:
		int ret = 0;
		int sentLen = 0;
		int dataLen = operate->buf.len;
		int flags = MSG_PARTIAL;

        operate->type = OP_WRITE_FINISH; // 发送完成

		if (operate->udp) // UDP包
		{
            //static int b = 0;
            //TRACE("write %d\n", b++);

			ret = ::WSASendTo(client->sock, 
				&(operate->buf), 
				1, 
				(DWORD*)&sentLen, 
				0,//flags,
				(LPSOCKADDR)&(operate->remoteAddr), 
				sizeof(SOCKADDR_IN), 
				&(operate->overlapped),
				NULL);
		}
		else
		{
			ret = WSASend(client->sock, 
				&(operate->buf), 
				1, 
				(DWORD*)&sentLen, 
				flags, 
				&(operate->overlapped), 
				NULL);
		}

		if (SOCKET_ERROR == ret)
		{
			static int lockTimes = 0;

			int error = ::WSAGetLastError();
			if (10055 == error)// IOCP的内部队列耗尽(缓冲区)
			{
				Sleep(++lockTimes * 1000);
				goto SEND_BEGIN;
			}
			else if (error != WSA_IO_PENDING)
			{
				CloseClient(client, operate);
				//::LeaveCriticalSection(&csWrite_);
				return false;
			}

			lockTimes = 0;
		}
        else if (sentLen != dataLen)
		{
			if (operate->udp) // UDP包
			{
                OPWriteFinish(client, operate); // 回收

				TRACE(_T("IOCP delete UDP pack sent:%d data len:%d error:%d client:%d operate:%d\n"), 
                    sentLen, dataLen, ::WSAGetLastError(), client, operate);
			}
			else // TCP 包
			{
				operate->buf.len = dataLen - sentLen;
				memcpy(operate->buf.buf, operate->buf.buf + sentLen, dataLen - sentLen);
				goto SEND_BEGIN;
			}
		}
// 		else                         // 发送成功
// 		{
// 			buffPool_->Free(operate->buf.buf);
// 			operate->sent = true;
// 			operate->buf.len = 0;
// 			operate->buf.buf = NULL;
// 
//             TRACE(_T("IOCP UDP pack sent:%d data len:%d error:%d client:%d operate:%d\n"), 
//                 sentLen, dataLen, GetLastError(), client, operate);
// 		}

		//::LeaveCriticalSection(&csWrite_);
		return true;
	}

    /**
	 *\fn         OPWriteFinish(PCLIENT client, POPERATE operate)
	 *\brief      写完成操作。
	 *\param[in]  client  客户端对象。
	 *\param[in]  operate 操作对象。
	 *\return     是否成功
	 */
	bool IOCP::OPWriteFinish(PCLIENT client, POPERATE operate)
    {
        //static int c = 0;
        //TRACE("write finish %d\n", c++);

        buffPool_->Free(operate->buf.buf);
        operate->sent = true;
        operate->buf.len = 0;
        operate->buf.buf = NULL;
        operatePool_.FreeItem(operate);
        return true;
    }

	/**
	 *\fn         PostReadOperate(PCLIENT client, POPERATE operate)
	 *\brief      投递一个读操作,每当执行完读操作后就需要为原来的socket投递一个读操作
	 *\n		  准备接收下次的数据。
	 *\param[in]  client  客户端对象。
	 *\param[in]  operate 操作对象。
	 *\return     是否成功(0成功，其它失败)
	 */
	int IOCP::PostReadOperate(PCLIENT client, POPERATE operate)
	{   
		int ret= 0;
		int sentLen = 0;
		int flags = MSG_PARTIAL;

		//::EnterCriticalSection(&csPostRead_);

RECV_BEGIN:
		operate->type = OP_READ;

		if (operate->udp) // UDP包
		{
			ret = WSARecvFrom(operate->sock, 
				&(operate->buf), 
				1, 
				(DWORD*)&sentLen,
				(DWORD*)&flags, 
				(LPSOCKADDR)&(operate->remoteAddr), 
				&(operate->addrSize), 
				&(operate->overlapped),
				NULL);
		}
		else
		{
			ret = WSARecv(operate->sock, 
				&(operate->buf), 
				1, 
				(DWORD*)&sentLen, 
				(DWORD*)&flags, 
				&(operate->overlapped), 
				NULL);
		}

		if (SOCKET_ERROR == ret)
		{
			static int lockTimes = 0;

			int error = WSAGetLastError();

			if (error == 10055)// IOCP的内部队列耗尽(缓冲区)
			{
				::Sleep(++lockTimes * 1000);
				//g_ProFile.m_pLog->println(LOG_ERROR, _T("IOCP post recv operate error:10055, socket:%d, times:%d"), pOP->hSocket, m_nLockTimes);
				goto RECV_BEGIN;
			}
			else if (error != WSA_IO_PENDING)
			{
				CloseClient(client, operate);
				//g_ProFile.m_pLog->println(LOG_ERROR, _T("IOCP post recv operate Error:%d"), nError);
			}

			lockTimes = 0;

			ret = error;
		}

		//::LeaveCriticalSection(&csPostRead_);
		return ret;
	}

	/**
	 *\fn         CloseClient(PCLIENT client, POPERATE operate)
	 *\brief      关闭对象。
	 *\param[in]  client  客户端对象。
	 *\param[in]  operate 操作对象。
	 *\return     是否成功
	 */
	bool IOCP::CloseClient(PCLIENT client, POPERATE operate)
	{
		if (NULL != client)
		{			
			PPACK pack = (PPACK)buffPool_->Get(1);// 向上层报告客户端已经关闭
			pack->clear();
			pack->protoId = CLIENT_CLOSE_SOCKET;
			pack->dataLen = client->sock;

			inputQueue_->Add(NULL, pack, 0);

			closesocket(client->sock);
			clientPool_.FreeItem(client);		// 回收客户端对象
			client = NULL;
		}

		if (NULL != operate)
		{
			buffPool_->Free(operate->buf.buf);	// 回收内存
			operate->buf.buf = NULL;
			operate->buf.len = 0;

			operatePool_.FreeItem(operate);		// 回收操作对象
			operate = NULL;
		}

		return true;
	}

	/**
	 *\fn         ConnectTo(const char *ip, unsigned short port, PCLIENT *client)
	 *\brief      连接服务器。
	 *\param[in]  ip       IP地址。
	 *\param[in]  port     端口地址。
	 *\param[in]  client   客户端对象。
	 *\return     是否成功
	 */
	int IOCP::ConnectTo(const char *ip, unsigned short port, PCLIENT *client)
	{
		if (NULL == ip || NULL == client)
		{
			return IOCP_PARA_ERROR;
		}

		// 新建socket
		SOCKET connectSocket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (INVALID_SOCKET == connectSocket)
		{
			return IOCP_CREATE_SOCK_FAIL;
		}

		// 没有延时(较小的包组装为更大的帧然后再发送)
		int option = 1;
		int ret = setsockopt(connectSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(char)); // 没有延时
		if (SOCKET_ERROR == ret)
		{
			closesocket(connectSocket);
			return IOCP_SET_SOCK_FAIL;
		}

		// 设置缓冲区大小
		option = 1024*1024;
		ret = setsockopt(connectSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&option, sizeof(option)); 
		if (SOCKET_ERROR == ret)
		{
			closesocket(connectSocket);
			return IOCP_SET_SOCK_FAIL;
		}

		// 得到地址结构
		struct addrinfo *addr = NULL;
		ret = GetTcpAddr(ip, port, false, &addr);
		if (INVALID_SOCKET == ret)
		{
			closesocket(connectSocket);
			return IOCP_GET_SOCK_ADDR_FAIL;
		}

		// 连接到服务器
		ret = connect(connectSocket, addr->ai_addr, (int)addr->ai_addrlen);

		// 释放地址信息结构
		freeaddrinfo(addr);

		if (SOCKET_ERROR == ret)
		{
			closesocket(connectSocket);
			return IOCP_SOCKET_CONNECT_FAIL;
		}
		
		// 设置为非阻塞,如果放在connect前面调用connect会直接返回,因为是非阻塞的
		option = 1;
		ret = ioctlsocket(connectSocket, FIONBIO, (u_long*)&option);
		if (SOCKET_ERROR == ret)
		{
			closesocket(connectSocket);
			return IOCP_SET_SOCK_FAIL;
		}
		
		// 得到一个客户端数据结构
		PCLIENT connectClient = clientPool_.Get(connectSocket);
		if (NULL == connectClient)
		{
			closesocket(connectSocket);
			return IOCP_GET_CLIENT_DATA_FAIL;
		}

		// 得到一个操作数据结构
		POPERATE operate = operatePool_.Get();
		operate->sock    = connectSocket;
		operate->type    = OP_READ;
		operate->buf.buf = (char*)buffPool_->Get(1);
		operate->buf.len = buffSize_;
		operate->udp     = false;
		operate->sent    = false;
		
		// 投递读取操作
		ret = PostReadOperate(connectClient, operate);
		if (WSA_IO_PENDING != ret)
		{
			CloseClient(connectClient, NULL);
			return IOCP_POST_READ_OPERTE_FAIL;
		}
		
		// 将新建立的套接字关联到完成端口
		ret = (int)CreateIoCompletionPort((HANDLE)connectSocket, completionPort_, (DWORD_PTR)connectClient, 0);
		if (NULL == ret)
		{
			CloseClient(connectClient, NULL);
			return IOCP_SOCKET_INTO_IOCP_FAIL;
		}

		// 返回分配的客户端对象
		*client = connectClient;

		return S_OK;
	}

	/**
	 *\fn         AddTcpListen(const char *ip, unsigned short port, PCLIENT *client)
	 *\brief      添加TCP监听。
	 *\param[in]  ip       IP地址。
	 *\param[in]  port     端口地址。
	 *\param[in]  client   客户端对象。
	 *\return     是否成功
	 */
	int IOCP::AddTcpListen(const char *ip, unsigned short port, PCLIENT *client)
	{
		if (NULL == ip  || NULL == client)
		{
			return IOCP_PARA_ERROR;
		}

		// 新建socket
		SOCKET listenSocket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (INVALID_SOCKET == listenSocket)
		{
			return IOCP_CREATE_SOCK_FAIL;
		}

		// 得到地址信息结构
		struct addrinfo *addr = NULL;
		int ret = GetTcpAddr(ip, port, false, &addr);
		if (INVALID_SOCKET == ret)
		{
			closesocket(listenSocket);
			return IOCP_GET_SOCK_ADDR_FAIL;
		}

		// 绑定监听socket
		ret = bind(listenSocket, addr->ai_addr, addr->ai_addrlen);
		
		// 释放地址信息结构
		freeaddrinfo(addr);

		if (SOCKET_ERROR == ret)
		{
			closesocket(listenSocket);
			return IOCP_SOCKET_BIND_FAIL;
		}

		// 监听
		ret = listen(listenSocket, 100);
		if (SOCKET_ERROR == ret)
		{
			closesocket(listenSocket);
			return IOCP_SOCKET_LISTEN_FAIL;
		}

		// 得到一个客户端数据结构
		PCLIENT listenClient = clientPool_.Get(listenSocket);
		if (NULL == listenClient)
		{
			closesocket(listenSocket);
			return IOCP_GET_CLIENT_DATA_FAIL;
		}

		// 添加连接事件
		HANDLE acceptEvent = AddAccepEvent(listenSocket);
		if (NULL != acceptEvent)
		{
			LISTEN_INFO listenInfo = {0};
			listenInfo.acceptEvent = acceptEvent;
			listenInfo.listenClient = listenClient;
			listenInfo.listenSocket = listenSocket;
			listenInfoMap_[acceptEventesCount_] = listenInfo;
			acceptEventes_[acceptEventesCount_] = acceptEvent;
			acceptEventesCount_++;
		}
		else
		{
			CloseClient(listenClient, NULL);
			return IOCP_ADD_ACCEPT_EVENT_FAIL;
		}

		// 准备接收客户端的socket
		ret = PostAcceptSocket(listenSocket, listenClient);
		if (ret <= 0)
		{
			CloseClient(listenClient, NULL);
			return IOCP_POST_ACCEPT_SOCKET_FAIL;
		}
		
		// 将监听套接字listenSocket和已经建立的完成端口关联起来 
		ret = (int)CreateIoCompletionPort((HANDLE)listenSocket, completionPort_, (ULONG_PTR)listenClient, 0);
		if (NULL == ret)
		{
			CloseClient(listenClient, NULL);
			return IOCP_SOCKET_INTO_IOCP_FAIL;
		}

		// 返回分配的客户端对象
		*client = listenClient;

		return S_OK;
	}

	/**
	 *\fn         AddUdpListen(const char *ip, unsigned short port, PCLIENT *client)
	 *\brief      添加UDP监听。
	 *\param[in]  ip       IP地址。
	 *\param[in]  port     端口地址。
	 *\param[in]  client   客户端对象。
	 *\return     是否成功
	 */
	int IOCP::AddUdpListen(const char *ip, unsigned short port, PCLIENT *client)
	{
		if (NULL == ip || NULL == client)
		{
			return IOCP_PARA_ERROR;
		}

		// 新建socket
		SOCKET listenSocket = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (INVALID_SOCKET == listenSocket)
		{
			return IOCP_CREATE_SOCK_FAIL;
		}

		// 得到地址信息结构
		struct addrinfo *addr = NULL;
		int ret = GetUdpAddr(ip, port, false, &addr);
		if (INVALID_SOCKET == ret)
		{
			closesocket(listenSocket);
			return IOCP_GET_SOCK_ADDR_FAIL;
		}

		// 绑定监听socket
		ret = bind(listenSocket, addr->ai_addr, addr->ai_addrlen);

		if (SOCKET_ERROR == ret)
		{
			closesocket(listenSocket);
			TRACE(_T("bind error:%d\n"), ::GetLastError());
			return IOCP_SOCKET_BIND_FAIL;
		}

		// 得到一个数据结构
		PCLIENT listenClient = clientPool_.Get(listenSocket);
		if (NULL == listenClient)
		{
			closesocket(listenSocket);
			return IOCP_GET_CLIENT_DATA_FAIL;
		}

		// 得到一个操作数据结构
		POPERATE operate = operatePool_.Get();
		operate->sock    = listenSocket;
		operate->type    = OP_READ;
		operate->buf.buf = (char*)buffPool_->Get(1);
		operate->buf.len = buffSize_;
		operate->udp     = true;
		operate->sent    = false;
        operate->setIp(GetPort(addr));
        operate->setPort(GetIpAddr(addr));

        // 释放地址信息结构
		freeaddrinfo(addr);

		// 投递读取操作
		ret = PostReadOperate(listenClient, operate);
		if (WSA_IO_PENDING != ret)
		{
			CloseClient(listenClient, operate);
			return IOCP_POST_READ_OPERTE_FAIL;
		}
		
		// 将监听套接字listenSocket和已经建立的完成端口关联起来 
		ret = (int)CreateIoCompletionPort((HANDLE)listenSocket, completionPort_, (ULONG_PTR)listenClient, 0);
		if (NULL == ret)
		{
			CloseClient(listenClient, operate);
			return IOCP_SOCKET_INTO_IOCP_FAIL;
		}

		// 返回分配的客户端对象
		*client = listenClient;

		return S_OK;
	}

	/*
	// 地址重用
	BOOL bFlag = TRUE;
	nResult = ::setsockopt(hUdpListenSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&bFlag, sizeof(bFlag));  
	if (SOCKET_ERROR == nResult)  
	{ 
	TRACE("setsockopt() SO_REUSEADDR failed, Err: %d\n",WSAGetLastError());
	closesocket(hUdpListenSocket);
	return IOCP_SET_SOCK_FAIL;
	}

	// 将socket设置为非阻塞,test
	u_long argp = 1;
	nResult = ioctlsocket(hUdpListenSocket, FIONBIO, &argp);

	// 设置发送缓冲区的大小   
	DWORD maxBytes = 0;   
	setsockopt(hUdpListenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&maxBytes, sizeof(maxBytes));

	// 获取允许的最大接收缓冲区大小   
	int maxSend = sizeof(int);   
	getsockopt(hUdpListenSocket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char*)&maxBytes, &maxSend);

	// 设置接收缓冲区的大小   
	setsockopt(hUdpListenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&maxBytes, sizeof(maxBytes));

	// 使用nt的IOCTL 防止在WIN2000下对方没有打开端口的情况下
	// 出现错误(WSAECONNRESET)10054
	DWORD bytes = 0;
	BOOL inBuffer = FALSE;
	int ret = ::WSAIoctl(listenSocket, SIO_UDP_CONNRESET, &inBuffer, sizeof(inBuffer), NULL, 0, &bytes, NULL, NULL);
	if (SOCKET_ERROR == ret)
	{
	TRACE("AddUdpListen WSAIoctl() SIO_UDP_CONNRESET failed, Err: %d\n", WSAGetLastError());
	closesocket(listenSocket);
	return IOCP_SET_SOCK_FAIL;
	}
	*/
}