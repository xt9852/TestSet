
#pragma once
#include "Pool.h"


namespace XT_IOCP
{

	/**
	 *\struct tagBuffHead
	 *\brief  内存块信息头
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	typedef struct tagBuffHead
	{
		short usedCount;    // 使用次数

	}BUFFHEAD,*PBUFFHEAD;

	/**
	 *\class  BuffPool
	 *\brief  该类主要是内存池类
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	class BuffPool : public Pool
	{
	public:
		/**
		 *\fn         BuffPool()
		 *\brief      缺省构造函数。
	     */
		BuffPool();

		/**
		 *\fn         BuffPool(int size)
		 *\brief      缺省构造函数。
		 *\param[in]  size 内存块大小。
	     */
		BuffPool(int size);

		/**
		 *\fn         ~BuffPool()
		 *\brief      析构函数。
	     */
		~BuffPool();

	private:
		unsigned long buffSize_;	// 缓冲区大小

		/**
		 *\fn         NewItem()
		 *\brief      new一个内存块,纯虚函数。
		 *\return     内存块指针。
		 */
		virtual void* NewItem();

		/**
		 *\fn         DeleteItem()
		 *\brief      删除一个单元,纯虚函数。
		 *\param[in]  data 数据指针。
		 *\return     单元指针。
		 */
		void DeleteItem(void *data);

	public:
		/**
		 *\fn         Get(unsigned short times)
		 *\brief      得到一个单元。
		 *\param[in]  times 内存块使用次数。
		 *\return     内存块指针。
		 */
		void* Get(unsigned short times);

		/**
		 *\fn         Free(void *buff)
		 *\brief      回收一块内存。
		 *\param[in]  buff 数据指针。
		 *\return     释放是否成功。
		 */
		bool Free(void *buff);
		
		/**
		 *\fn         SetTimes(void *buff, unsigned short newTimes = 1)
		 *\brief      重新设置内存块被使用次数。
		 *\param[in]  buff 数据指针。
		 *\param[in]  newTimes 新的使用次数。
		 *\return     释放是否成功。
		 */
		bool SetTimes(void *buff, unsigned short newTimes);
		
		/**
		 *\fn         setSize(unsigned long size)
		 *\brief      设置内存块大小。
		 *\param[in]  size 内存块大小。
		 *\return     是否成功。
		 */
		void setSize(unsigned long size) { buffSize_ = size; }
		
		/**
		 *\fn         getSize()
		 *\brief      得到内存块大小。
		 *\param[in]  size 数据指针。
		 *\return     内存块大小。
		 */
		unsigned long getSize() { return buffSize_; }
	};
}