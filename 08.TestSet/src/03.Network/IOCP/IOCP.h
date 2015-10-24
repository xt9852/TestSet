
#pragma once
#include "ClientPool.h"
#include "OperatePool.h"
#include <set>
#include <list>
#include <winsock2.h>
#include <mswsock.h> // LPFN_ACCEPTEX
#pragma comment(lib,"ws2_32.lib")


namespace XT_IOCP
{

#define MAX_THREAD_COUNT    50      // 最大线程数量
#define MAX_LISTEN_COUNT    100     // 最大监听数量
#define SOCKET_ADD_NUM      100     // 一次添加SOCKET的数量
#define CLIENT_CLOSE_SOCKET 0xFFFF  // IOCP通知上层客户端壮志凌云了SOCKET

	/**
	 *\struct tagListenInfo
	 *\brief  监听对象数据结构
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类
	 */
	typedef struct tagListenInfo
	{
		SOCKET  listenSocket;
		HANDLE  acceptEvent;
		PCLIENT listenClient;

	}LISTEN_INFO, *PLISTEN_INFO;


	typedef std::list<HANDLE>			WORK_THREAD_LIST;
	typedef std::map<int, LISTEN_INFO>	LISTEN_INFO_MAP;
	typedef struct tagQueueNode			*PQueueNode;	

	/**
	完成端口，需先Initialize(),然后再AddTcpListen()或AddUdpListen()

	1-  不要为每个小数据包发送一个IOCP请求,这样很容易耗尽IOCP的内部队列.....从而产生10055错误.
	2-  不要试图在发送出IOCP请求之后,收到完成通知之前修改请求中使用的数据缓冲的内容,因为在这段时间,系统可能会来读取这些缓冲.
	3-  为了避免内存拷贝,可以尝试关闭SOCKET的发送和接收缓冲区,不过代价是,你需要更多的接收请求POST到一个数据流量比较大的SOCKET,
	从而保证系统一直可以找到BUFFER来收取到来的数据.
	4-  在发出多个接收请求的时候,如果你的WORKTHREAD不止一个,一定要使用一些手段来保证接收完成的数据按照发送接收请求的顺序处理,否则,
	你会遇到数据包用混乱的顺序排列在你的处理队列里.....
	5-  说起工作线程, 最好要根据MS的建议, 开 CPU个数*2+2 个, 如果你不了解IOCP的工作原理的话. 
	6-  IOCP的工作线程是系统优化和调度的, 自己就不需要进行额外的工作了.如果您自信您的智慧和经验超过MS的工程师, 那你还需要IOCP么....
	7-  发出一个Send请求之后，就不需要再去检测是否发送完整，因为iocp会帮你做这件事情，有些人说iocp没有做这件事情，这和iocp的高效能是相悖的，
	并且我做过的无数次测试表明，Iocp要么断开连接，要么就帮你把每个发送请求都发送完整。
	8-  出现数据错乱的时候，不要慌，要从多线程的角度检查你的解析和发送数据包的代码，看看是不是有顺序上的问题。
	9-  当遇到奇怪的内存问题时，逐渐的减少工作线程的数量，可以帮你更快的锁定问题发生的潜在位置。
	10- 同样是遇到内存问题时，请先去检查你的客户端在服务器端内部映射对象的释放是否有问题。而且要小心的编写iocp完成失败的处理代码，
	防止引用一个错误的内部映射对象的地址。
	11- overlapped对象一定要保存在持久的位置，并且不到操作完成（不管成功还是失败）不要释放，否则可能会引发各种奇怪的问题。
	12- IOCP的所有工作都是在获取完成状态的那个函数内部进行调度和完成的，所以除了注意工作线程的数量之外，还要注意，
	尽量保持足够多的工作线程处在获取完成状态的那个等待里面，这样做就需要减少工作线程的负担，确保工作线程内部要处理费时的工作。
	（我的建议是工作线程和逻辑线程彻底区分开）
	13- overlapped对象要为每次的send和recv操作都准备一个全新的，不能图方便重复利用。
	14- 尽量保持send和recv的缓冲的大小是系统页面大小的倍数，因为系统发送或者接收数据的时候，会锁用户内存的，
	比页面小的缓冲会浪费掉整个一个页面。（作为第一条的补充，建议把小包合并成大包发送）
	**/

	enum
	{
		IOCP_THREAD_PARA_ERROR  = 1000, // 线程输入参数不正确
		IOCP_SEND_THREAD_EXIT,          // 发送线程正常退出
		IOCP_IDLE_THREAD_EXIT,          // 检测线程正常退出
		IOCP_WORK_THREAD_EXIT,          // 工作线程正常退出
		IOCP_CORECE_THREAD_EXIT,        // 强近关闭线程

		IOCP_PARA_ERROR         = -1999,// 输入参数不正确
		IOCP_INIT_CLIENT_POOL_FAIL,     // 初使化客户端池失败    
		IOCP_SET_SOCK_FAIL,             // 设置SOCKET失败
		IOCP_GET_SOCK_ADDR_FAIL,        // 得到SOCKET地址失败
		IOCP_GET_SOCK_ACCEPT_FAIL,      // 得到SOCKET扩展函数指针失败
		IOCP_GET_CLIENT_DATA_FAIL,      // 得到客户端结构失败
		IOCP_ADD_ACCEPT_EVENT_FAIL,     // 添加ACCEPT事件失败
		IOCP_POST_READ_OPERTE_FAIL,     // 添加读取操作失败
		IOCP_POST_ACCEPT_SOCKET_FAIL,   // 添加读取操作失败
		IOCP_SOCKET_LISTEN_OUT,         // 监听SOCKET数量太多    
		IOCP_SOCKET_BIND_FAIL,          // SCOKET绑定失败
		IOCP_SOCKET_LISTEN_FAIL,        // SCOKET监听失败
		IOCP_SOCKET_CONNECT_FAIL,       // SCOKET连接失败
		IOCP_SOCKET_INTO_IOCP_FAIL,     // SCOKET关连到IOCP失败
		IOCP_CREATE_EXIT_EVENT_FAIL,    // 创建退出事件失败
		IOCP_CREATE_IOCP_FAIL,          // 创建完成端口失败
		IOCP_CREATE_SOCK_FAIL,          // 创建SOCKET失败
		IOCP_CREATE_WORK_THREAD_FAIL,   // 创建工作线程失败
		IOCP_CREATE_SEND_THREAD_FAIL,   // 创建发送线程失败
		IOCP_CREATE_IDLE_THREAD_FAIL,   // 创建检测线程失败
		IOCP_SEND_THREAD_EXCEPT,        // 发送线程异常退出
		IOCP_IDLE_THREAD_EXCEPT,        // 检测线程异常退出
		IOCP_WORK_THREAD_EXCEPT,        // 工作线程异彩常退出

	};

	class PackQueue;

	/**
	 *\class  IOCP
	 *\brief  完成端口类
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类。
	 */
	class IOCP
	{
	public:
		/**
		 *\fn         IOCP()
		 *\brief      默认构造函数。
		 */
		IOCP(void);

		/**
		 *\fn         ~IOCP()
		 *\brief      析构函数。
		 */
		~IOCP(void);

	private:
		CRITICAL_SECTION    csAccept_;		
		CRITICAL_SECTION    csRead_;
		CRITICAL_SECTION    csWrite_;
		CRITICAL_SECTION    csPostRead_;
		CRITICAL_SECTION    csWork_;
		CRITICAL_SECTION    csListenSocket_;

		bool                running_;		    // 是否正在运行
		HANDLE              completionPort_;	// 完成端口句柄
		HANDLE              idelThread_;		// 接收网络事件,并监视其它线程
		HANDLE              sendThread_;		// 发送包线程

		LPFN_ACCEPTEX       acceptEx_;			// 完成端口绑听函数

		WORK_THREAD_LIST	workThreadList_;    // 工作线程HANDLE
		LISTEN_INFO_MAP     listenInfoMap_;		// 监听SOCKET信息
		HANDLE              acceptEventes_[MAX_LISTEN_COUNT];
		int                 acceptEventesCount_;// 事件数量

		PackQueue          *inputQueue_;		// 已接收包队列
		PackQueue          *outputQueue_;		// 待发送包队列
		BuffPool           *buffPool_;			// 内存池
		ClientPool          clientPool_;		// 用户结构池
		OperatePool         operatePool_;		// 操作结构池

		int					buffSize_;			// 缓冲区大小
		int					postSocketCount_;	// 已经投递的socket数量

	protected:
		/**
		 *\fn         InitIOCP()
		 *\brief      初使化完成端口。
		 *\return     是否成功(0成功，其它失败)
		 */
		int InitIOCP();		

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
		HANDLE AddAccepEvent(int listenSocket);

		/**
		 *\fn         PostAcceptSocket(int listenSocket, PCLIENT listenClient)
		 *\brief      添加待绑定的客户端句柄,连续发出SOCKET_ADD_NUM个AcceptEx调用。
		 *\param[in]  listenSocket  监听句柄。
		 *\param[in]  listenClient  监听客户端对象。
		 *\return     是否成功(0成功，其它失败)
		 */
		int PostAcceptSocket(int listenSocket, PCLIENT listenClient);

		/**
		 *\fn         PostReadOperate(PCLIENT client, POPERATE operate)
		 *\brief      投递一个读操作,每当执行完读操作后就需要为原来的socket投递一个读操作，
		 *\n		  准备接收下次的数据。
		 *\param[in]  client  客户端对象。
		 *\param[in]  operate 操作对象。
		 *\return     是否成功(0成功，其它失败)
		 */
		int PostReadOperate(PCLIENT client, POPERATE operate);

		/**
		 *\fn         GetTcpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr)
		 *\brief      得到TCP地址，主要是用于IPV6，也可用于IPV4。
		 *\param[in]  ip      IP地址。
		 *\param[in]  port    端口地址。
		 *\param[in]  ipv6    是否是IPV6。
		 *\param[out] addr    地址结构。
		 *\return     是否成功(0成功，其它失败)
		 */
		int GetTcpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr);

		/**
		 *\fn         GetUdpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr)
		 *\brief      得到UDP地址，主要是用于IPV6，也可用于IPV4。
		 *\param[in]  ip      IP地址。
		 *\param[in]  port    端口地址。
		 *\param[in]  ipv6    是否是IPV6。
		 *\param[out] addr    地址结构。
		 *\return     是否成功(0成功，其它失败)
		 */
		int GetUdpAddr(const char *ip, unsigned short port, bool ipv6, PADDRINFOA *addr);

        /**
	     *\fn         GetIpAddr(addrinfo *addr)
	     *\brief      得到IP地址。
	     *\param[in]  addr      地址地址。
	     *\return     IP地址。
	     */
        int GetIpAddr(addrinfo *addr);

        /**
	     *\fn         GetPort(addrinfo *addr)
	     *\brief      得到端口。
	     *\param[in]  addr      地址地址。
	     *\return     端口。
	     */
        int GetPort(addrinfo *addr);
		
		/**
		 *\fn         EndAllThread()
		 *\brief      结束工作线程(工作线程，发送线程，连接事件线程)。
		 */
		void EndAllThread();

	protected:
		/**
		 *\fn         OPAccept(PCLIENT client, POPERATE operate)
		 *\brief      绑定操作,绑定连接的客户端。
		 *\param[in]  client  监听句柄的客户端对象(client->socket为监听socket)。
		 *\param[in]  operate 操作对象(operate->socket为客户端socket)。
		 *\return     连接的客户端对象
		 */
		PCLIENT OPAccept(PCLIENT client, POPERATE operate);

		/**
		 *\fn         OPRead(int size, PCLIENT client, POPERATE operate)
		 *\brief      读操作。
		 *\param[in]  size    数据长。
		 *\param[in]  client  客户端对象。
		 *\param[in]  operate 操作对象。
		 *\return     是否成功
		 */
		bool OPRead(int size, PCLIENT client, POPERATE operate);

		/**
		 *\fn         OPWrite(PCLIENT client, POPERATE operate)
		 *\brief      写操作。
		 *\param[in]  client  客户端对象。
		 *\param[in]  operate 操作对象。
		 *\return     是否成功
		 */
		bool OPWrite(PCLIENT client, POPERATE operate);

        /**
		 *\fn         OPWriteFinish(PCLIENT client, POPERATE operate)
		 *\brief      写完成操作。
		 *\param[in]  client  客户端对象。
		 *\param[in]  operate 操作对象。
		 *\return     是否成功
		 */
		bool OPWriteFinish(PCLIENT client, POPERATE operate);

		/**
		 *\fn         WorkThreadProc()
		 *\brief      工作线程处理函数。
		 *\return     是否成功
		 */
		unsigned WorkThreadProc();

		/**
		 *\fn         SendThreadProc()
		 *\brief      发送线程处理函数。
		 *\return     是否成功
		 */
		unsigned SendThreadProc();

		/**
		 *\fn         IdleThreadProc()
		 *\brief      等待线程处理函数。
		 *\return     是否成功
		 */
		unsigned IdleThreadProc();

		/**
		 *\fn         WorkThread(LPVOID data)
		 *\brief      工作线程。
		 *\param[in]  data    线程参数。
		 *\return     是否成功
		 */
		static unsigned __stdcall WorkThread(LPVOID data);

		/**
		 *\fn         SendThread(LPVOID data)
		 *\brief      发送线程,从输出队列中读到数据并投递写操作。
		 *\param[in]  data    线程参数。
		 *\return     是否成功
		 */
		static unsigned __stdcall SendThread(LPVOID data);

		/**
		 *\fn         IdleThread(LPVOID data)
		 *\brief      等待线程,守护hAcceptEvent网络事件，当有FD_ACCEPT时触发，
		 *\n		  说明待绑定的客户端已经用尽，需再投递。
		 *\param[in]  data    线程参数。
		 *\return     是否成功
		 */
		static unsigned __stdcall IdleThread(LPVOID data);

	public:
		/**
		 *\fn         Init(int cmdType, PackQueue *inputQueue, PackQueue *outputQueue, BuffPool *buffPool)
		 *\brief      初使化。
		 *\param[in]  cmdType      命令类型。
		 *\param[in]  inputQueue   输入队列。
		 *\param[in]  outputQueue  输出队列。
		 *\param[in]  buffPool     缓冲池。
		 *\return     是否成功
		 */
		int     Init(int cmdType, PackQueue *inputQueue, PackQueue *outputQueue, BuffPool *buffPool);

		/**
		 *\fn         Stop()
		 *\brief      停止。
		 *\return     是否成功
		 */
		bool    Stop();

		/**
		 *\fn         SendData(PQueueNode node)
		 *\brief      发送数据。
		 *\param[in]  node      队列节点。
		 *\return     是否成功
		 */
		bool    SendData(PQueueNode node);

		/**
		 *\fn         SendData(PQueueNode node)
		 *\brief      发送TCP数据。
		 *\param[in]  client   客户端。
		 *\param[in]  buf      数据。
		 *\param[in]  len      数据长。
		 *\return     是否成功
		 */
		bool    SendData(PCLIENT client, void *buf, int len);

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
		bool    SendData(PCLIENT client, void *buf, int len, int ip, unsigned short port);

		/**
		 *\fn         ConnectTo(const char *ip, unsigned short port, PCLIENT *client)
		 *\brief      连接服务器。
		 *\param[in]  ip       IP地址。
		 *\param[in]  port     端口地址。
		 *\param[in]  client   客户端对象。
		 *\return     是否成功
		 */
		int     ConnectTo(const char *ip, unsigned short port, PCLIENT *client);

		/**
		 *\fn         AddTcpListen(const char *ip, unsigned short port, PCLIENT *client)
		 *\brief      添加TCP监听。
		 *\param[in]  ip       IP地址。
		 *\param[in]  port     端口地址。
		 *\param[in]  client   客户端对象。
		 *\return     是否成功
		 */
		int     AddTcpListen(const char *ip, unsigned short port, PCLIENT *client);

		/**
		 *\fn         AddUdpListen(const char *ip, unsigned short port, PCLIENT *client)
		 *\brief      添加UDP监听。
		 *\param[in]  ip       IP地址。
		 *\param[in]  port     端口地址。
		 *\param[in]  client   客户端对象。
		 *\return     是否成功
		 */
		int     AddUdpListen(const char *ip, unsigned short port, PCLIENT *client);
		
		/**
		 *\fn         CloseClient(PCLIENT client, POPERATE operate)
		 *\brief      关闭对象。
		 *\param[in]  client  客户端对象。
		 *\param[in]  operate 操作对象。
		 *\return     是否成功
		 */
		bool    CloseClient(PCLIENT client, POPERATE operate);
	};
}