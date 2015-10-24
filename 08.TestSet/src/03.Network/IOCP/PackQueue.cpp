
#include "stdafx.h"
#include "PackQueue.h"


namespace XT_IOCP
{

	/**
	 *\fn         PackQueue()
	 *\brief      缺省构造函数。
	 */
	PackQueue::PackQueue()
		:Pool(100),
		used_(false)
	{
	}

	/**
	 *\fn         ~PackQueue()
	 *\brief      析构函数。
	 */
	PackQueue::~PackQueue()
	{
		DeleteAll();
	}

	/**
	 *\fn         LockQueue()
	 *\brief      锁定队列。
	 */
	void PackQueue::LockQueue()
	{
		EnterCriticalSection(&csUsed_);
	}

	/**
	 *\fn         UnLockQueue()
	 *\brief      解锁队列。
	 */
	void PackQueue::UnLockQueue()
	{
		LeaveCriticalSection(&csUsed_);
	}

	/**
	 *\fn         NewItem()
	 *\brief      new一个内存块,纯虚函数。
	 *\return     内存块指针。
	 */
	void* PackQueue::NewItem()
	{
		return new QueueNode;
	}

	/**
	 *\fn         DeleteItem()
	 *\brief      删除一个单元,纯虚函数。
	 *\param[in]  data 数据指针。
	 *\return     单元指针。
	 */
	void PackQueue::DeleteItem(void *data)
	{
		delete data;
	}

	/**
	 *\fn         Add(PQUEUE_NODE node)
	 *\brief      包入队。
	 *\param[in]  data 数据指针。
	 */
	void PackQueue::Add(PQueueNode node)
	{
		if (!used_) return;

		LockQueue();

		busyNodeList_.push_back(node);

		UnLockQueue();
	}
	
	/**
	 *\fn         Add(void *client, int len, void *buf)
	 *\brief      TCP包入队。
	 *\param[in]  client 客户端对象。
	 *\param[in]  buf    数据指针。
	 *\param[in]  len    数据长度。
	 */
	void PackQueue::Add(void *client, void *buf, int len)
	{
		if (!used_) return;

		LockQueue();

		PQueueNode node = (PQueueNode)GetItem();
		node->client	= client;
		node->pack		= buf;
		node->len		= len;
		node->ip		= 0;
		node->port      = 0;

		busyNodeList_.push_back(node);

		UnLockQueue();
	}

	/**
	 *\fn         Add(void *client, void *buf, int len, PSOCKADDR_IN addr)
	 *\brief      UDP包入队。
	 *\param[in]  client 客户端对象。
	 *\param[in]  buf    数据指针。
	 *\param[in]  len    数据长度。	 
	 *\param[in]  addr   对方地址。
	 */
	void PackQueue::Add(void *client, void *buf, int len, PSOCKADDR_IN addr)
	{
		if (!used_) return;

		LockQueue();

		PQueueNode node = (PQueueNode)GetItem();
		node->client    = client;
		node->pack      = buf;
		node->len       = len;
		node->ip		= addr->sin_addr.S_un.S_addr;
		node->port      = addr->sin_port;

		busyNodeList_.push_back(node);

		UnLockQueue();
	}
	
	/**
	 *\fn         Add(void *client, void *buf, int len, int ip, short port)
	 *\brief      UDP包入队。
	 *\param[in]  client 客户端对象。
	 *\param[in]  buf    数据指针。
	 *\param[in]  len    数据长度。	 
	 *\param[in]  ip     对方IP地址。
	 *\param[in]  port   对方端口。
	 */
	void PackQueue::Add(void *client, void *buf, int len, int ip, short port)
	{
		if (!used_) return;

		LockQueue();

		PQueueNode node = (PQueueNode)GetItem();
		node->client	= client;
		node->pack		= buf;
		node->len		= len;
		node->ip		= ip;
		node->port		= port;

		busyNodeList_.push_back(node);

		UnLockQueue();
	}

	/**
	 *\fn         Get(PQUEUE_NODE *node)
	 *\brief      包出队。
	 *\param[OUT] node 数据指针的指针。
	 */
	bool PackQueue::Get(PQueueNode *node)
	{
		LockQueue();

		bool ret = false;

		if (!busyNodeList_.empty())
		{
			LIST_VOID::iterator iter = busyNodeList_.begin();

			if (iter != busyNodeList_.end())
			{
				PQueueNode node = (PQueueNode)*iter;

				busyNodeList_.erase(iter);

				ret = true;
			}
		}

		UnLockQueue();

		return ret;
	}

	/**
	*\fn         Get(void **client, void **buf, int &len)
	*\brief      TCP包出队。
	*\param[OUT] client 客户对象指针的指针。
	*\param[OUT] buf    数据指针的指针。
	*\param[OUT] len    数据长。	
	*/
	bool PackQueue::Get(void **client, void **buf, int &len)
	{
		LockQueue();

		bool ret = false;

		if (!busyNodeList_.empty())
		{
			LIST_VOID::iterator iter = busyNodeList_.begin();

			if (iter != busyNodeList_.end())
			{
				PQueueNode node = (PQueueNode)*iter;
				len     = node->len;
				*buf    = node->pack;
				*client = node->client;

				FreeItem(node);
				
				busyNodeList_.erase(iter);

				ret = true;
			}
		}

		UnLockQueue();

		return ret;
	}

	/**
	 *\fn         Get(void **client, void **buf, int &len, PSOCKADDR_IN addr)
	 *\brief      UDP包出队。
	 *\param[OUT] client 客户对象指针的指针。
	 *\param[OUT] buf    数据指针的指针。
	 *\param[OUT] len    数据长。	 
	 *\param[OUT] addr   对方地址。
	 */
	bool PackQueue::Get(void **client, void **buf, int &len, PSOCKADDR_IN addr)
	{
		LockQueue();

		bool ret = false;

		if (!busyNodeList_.empty())
		{
			LIST_VOID::iterator iter = busyNodeList_.begin();

			if (iter != busyNodeList_.end())
			{
				PQueueNode node            = (PQueueNode)*iter;
				len                        = node->len;
				*buf                       = node->pack;
				*client                    = node->client;
				addr->sin_addr.S_un.S_addr = node->ip;
				addr->sin_port             = node->port;

				FreeItem(node);

				busyNodeList_.erase(iter);

				ret = true;
			}
		}

		UnLockQueue();

		return ret;
	}

	/**
	 *\fn         Get(void **client, void **buf, int &len, int &ip, short &port)
	 *\brief      UDP包出队。
	 *\param[OUT] client 客户对象指针的指针。
	 *\param[OUT] buf    数据指针的指针。
	 *\param[OUT] len    数据长。	 
	 *\param[OUT] ip     对方IP地址。
	 *\param[OUT] port   对方端口。
	 */
	bool PackQueue::Get(void **client, void **buf, int &len, int &ip, short &port)
	{
		LockQueue();

		bool ret = false;

		if (!busyNodeList_.empty())
		{
			LIST_VOID::iterator iter = busyNodeList_.begin();

			if (iter != busyNodeList_.end())
			{
				PQueueNode node = (PQueueNode)*iter;
				len     = node->len;
				*buf    = node->pack;
				*client = node->client;
				ip      = node->ip;
				port    = node->port;

				FreeItem(node);

				busyNodeList_.erase(iter);

				ret = true;
			}
		}

		UnLockQueue();

		return ret;
	}
}