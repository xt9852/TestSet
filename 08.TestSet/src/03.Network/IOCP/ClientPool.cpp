#include "StdAfx.h"
#include "ClientPool.h"
#include "PrePack.h"


namespace XT_IOCP
{
	/**
	 *\fn         ClientPool()
	 *\brief      缺省构造函数。
	 */
	ClientPool::ClientPool(void)
		:Pool(10),
		buffPool_(NULL),
		inQueue_(NULL),
		cmdType_(CMD_TYPE_MYSELF)
	{
	}

	/**
	 *\fn         ~ClientPool()
	 *\brief      析构函数。
	 */
	ClientPool::~ClientPool(void)
	{
		DeleteAll();
	}

	/**
	 *\fn         NewItem()
	 *\brief      new一个客户端对象,纯虚函数。
	 *\return     内存块指针。
	 */
	void* ClientPool::NewItem()
	{
		PCLIENT client = new CLIENT[addCount_];

		client->sock = 0;
        client->data = NULL;
		client->prePack = new PrePack;
		client->prePack->Init(cmdType_, inQueue_, buffPool_);

		return client;
	}

	/**
	 *\fn         DeleteItem()
	 *\brief      删除一个单元,纯虚函数。
	 *\param[in]  data 数据指针。
	 *\return     单元指针。
	 */
	void ClientPool::DeleteItem(void *data)
	{
		PCLIENT client = (PCLIENT)data;
		delete client->prePack;
		delete client;
	}

	/**
	 *\fn         Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool)
	 *\brief      初使化客户端对象池。
	 *\param[in]  cmdType  命令类型。
	 *\param[in]  inQueue  数据包输入队列。
	 *\param[in]  buffPool 内存池。
	 *\return     是否成功
	 */
	bool ClientPool::Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool)
	{
		if (NULL == inQueue || NULL == buffPool) return false;

		EnterCriticalSection(&csUsed_);
		cmdType_ = cmdType;
		inQueue_ = inQueue;
		buffPool_ = buffPool;    
		LeaveCriticalSection(&csUsed_);

		return true;
	}

	/**
	 *\fn         Get(int sock)
	 *\brief      从池中取得一个客户端对象。
	 *\param[in]  sock  客户端socket句柄。
	 *\return     客户端对象指针。
	 */
	PCLIENT ClientPool::Get(int sock)
	{
		PCLIENT client = (PCLIENT)GetItem();

		client->sock = sock;

		return client;
	}
}