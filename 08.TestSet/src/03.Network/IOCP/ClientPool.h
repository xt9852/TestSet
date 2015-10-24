
#pragma once
#include "Pool.h"


namespace XT_IOCP
{

	class BuffPool;
	class PackQueue;
	class PrePack;

	/**
	 *\struct tagClientContext
	 *\brief  客户端信息
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	typedef struct tagClientContext
	{
		int sock;			// socket名柄
		PrePack *prePack;	// 预处理包
        void *data;         // 用户自定义数据

	}CLIENT,*PCLIENT;

	/**
	 *\class  ClientPool
	 *\brief  该类主要是客户端对象池类
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	class ClientPool : public Pool
	{
	public:
		/**
		 *\fn         ClientPool()
		 *\brief      缺省构造函数。
	     */
		ClientPool();

		/**
		 *\fn         ~ClientPool()
		 *\brief      析构函数。
	     */
		~ClientPool();

	private:
		int			cmdType_;	// 命令类型
		PackQueue	*inQueue_;	// 数据包输入队列
		BuffPool	*buffPool_;	// 内存池
		
		/**
		 *\fn         NewItem()
		 *\brief      new一个客户端对象,纯虚函数。
		 *\return     客户端对象指针。
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
		 *\fn         Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool)
		 *\brief      初使化客户端对象池。
		 *\param[in]  cmdType  命令类型。
		 *\param[in]  inQueue  数据包输入队列。
		 *\param[in]  buffPool 内存池。
		 *\return     是否成功
		 */
		bool Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool);

		/**
		 *\fn         Get(int sock)
		 *\brief      从池中取得一个客户端对象。
		 *\param[in]  sock  客户端socket句柄。
		 *\return     客户端对象指针。
		 */
		PCLIENT Get(int sock);
	};
}
