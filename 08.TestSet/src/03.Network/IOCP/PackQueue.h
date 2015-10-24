
#pragma once
#include "Pool.h"
#include <WinSock2.h> // PSOCKADDR_IN


namespace XT_IOCP
{

	/**
	 *\struct tagQUEUE_NODE
	 *\brief  队列节点
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	typedef struct tagQueueNode
	{
		int		len;		// 包长度
		void	*pack;		// 包内容
		void	*client;	// 客户端对象
		long	ip;			// UDP地址IP
		short	port;		// UDP地址端口
		
	}QueueNode, *PQueueNode;

	/**
	 *\class  PackQueue
	 *\brief  该类主要是数据包队列
	 *\	      由底层的网传输类，将消息入队，再由上层的消息处理类处理，起到缓冲和分层的使用
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	class PackQueue : public Pool
	{
	public:
		/**
		 *\fn         PackQueue()
		 *\brief      缺省构造函数。
	     */
		PackQueue();

		/**
		 *\fn         ~PackQueue()
		 *\brief      析构函数。
	     */
		~PackQueue();

	private:
		LIST_VOID	busyNodeList_;	// 在队列里的包
		bool		used_;			// 使用标记

		/**
		 *\fn         LockQueue()
		 *\brief      锁定队列。
	     */
		void  LockQueue();

		/**
		 *\fn         UnLockQueue()
		 *\brief      解锁队列。
	     */
		void  UnLockQueue();

		/**
		 *\fn         NewItem()
		 *\brief      new一个单元,纯虚函数。
		 *\return     单元指针。
		 */
		virtual void* NewItem();

		/**
		 *\fn         DeleteItem()
		 *\brief      删除一个单元,纯虚函数。
		 *\param[in]  data 数据指针。
		 *\return     单元指针。
		 */
		virtual void DeleteItem(void *data);

	public:
		/**
		 *\fn         Add(PQUEUE_NODE node)
		 *\brief      包入队。
		 *\param[in]  data 数据指针。
		 */
		void Add(PQueueNode node);

		/**
		 *\fn         Add(void *client, void *buf, int len)
		 *\brief      TCP包入队。
		 *\param[in]  client 客户端对象。
		 *\param[in]  len    数据长度。
		 *\param[in]  buf    数据指针。
		 */
		void Add(void *client, void *buf, int len);
		
		/**
		 *\fn         Add(void *client, void *buf, int len, PSOCKADDR_IN addr)
		 *\brief      UDP包入队。
		 *\param[in]  client 客户端对象。
		 *\param[in]  buf    数据指针。
		 *\param[in]  len    数据长度。		 
		 *\param[in]  addr   对方地址。
		 */
		void Add(void *client, void *buf, int len, PSOCKADDR_IN addr);

		/**
		 *\fn         Add(void *client, void *buf, int len, int ip, short port)
		 *\brief      UDP包入队。
		 *\param[in]  client 客户端对象。
		 *\param[in]  buf    数据指针。
		 *\param[in]  len    数据长度。		 
		 *\param[in]  ip     对方IP地址。
		 *\param[in]  port   对方端口。
		 */
		void Add(void *client, void *buf, int len, int ip, short port);

		/**
		 *\fn         Get(PQUEUE_NODE *node)
		 *\brief      包出队。
		 *\param[OUT] node 数据指针的指针。
		 */
		bool Get(PQueueNode *node);

		/**
		 *\fn         Get(void **client, void **buf, int &len)
		 *\brief      TCP包出队。
		 *\param[OUT] client 客户对象指针的指针。
		 *\param[OUT] buf    数据指针的指针。
		 *\param[OUT] len    数据长。		 
		 */
		bool Get(void **client, void **buf, int &len);

		/**
		 *\fn         Get(void **client, void **buf, int &len)
		 *\brief      UDP包出队。
		 *\param[OUT] client 客户对象指针的指针。
		 *\param[OUT] buf    数据指针的指针。
		 *\param[OUT] len    数据长。		 
		 *\param[OUT] addr   对方地址。
		 */
		bool Get(void **client, void **buf, int &len, PSOCKADDR_IN addr);

		/**
		 *\fn         Get(void **client, void **buf, int &len, int &ip, short &port)
		 *\brief      UDP包出队。
		 *\param[OUT] client 客户对象指针的指针。
		 *\param[OUT] buf    数据指针的指针。
		 *\param[OUT] len    数据长。		 
		 *\param[OUT] ip     对方IP地址。
		 *\param[OUT] port   对方端口。
		 */
		bool Get(void **client, void **buf, int &len, int &ip, short &port);

		/**
		 *\fn         Start()
		 *\brief      开始工作。
		 */
		void Start() { used_ = true; }

		/**
		 *\fn         Stop()
		 *\brief      停止工作。
		 */
		void Stop() { used_ = false; }
	};

}