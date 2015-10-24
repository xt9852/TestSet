
#include "StdAfx.h"
#include "BuffPool.h"



namespace XT_IOCP
{

	/**
	 *\fn         BuffPool()
	 *\brief      缺省构造函数。
	 */
	BuffPool::BuffPool(void)
		:Pool(50)
	{
		buffSize_ = 1024 - sizeof(BUFFHEAD);
	}

	/**
	 *\fn         BuffPool(int size)
	 *\brief      缺省构造函数。
	 *\param[in]  size 内存块大小。
	 */
	BuffPool::BuffPool(int size)
		:Pool(50)
	{
		buffSize_ = size;
	}
	
	/**
	 *\fn         ~BuffPool()
	 *\brief      析构函数。
	 */
	BuffPool::~BuffPool(void)
	{
		DeleteAll();
	}

	/**
	 *\fn         NewItem()
	 *\brief      new一个内存块,纯虚函数。
	 *\return     内存块指针。
	 */
	void* BuffPool::NewItem()
	{
		return new char[buffSize_ + sizeof(BUFFHEAD)];
	}

	/**
	 *\fn         DeleteItem()
	 *\brief      删除一个单元,纯虚函数。
	 *\param[in]  data 数据指针。
	 *\return     单元指针。
	 */
	void BuffPool::DeleteItem(void *data)
	{
		delete data;
	}

	/**
	 *\fn         Get(unsigned short times)
	 *\brief      得到一个单元。
	 *\param[in]  times 内存块使用次数。
	 *\return     内存块指针。
	 */
	PVOID BuffPool::Get(unsigned short times)
	{
		PBUFFHEAD buff = (PBUFFHEAD)GetItem();

		buff->usedCount = times;

		return ++buff; // 实际存放数据的位置
	}

	/**
	 *\fn         Free(void *buff)
	 *\brief      回收一块内存,将共享量减一，如果为一则移到空闲区。
	 *\param[in]  buff 数据指针。
	 *\return     释放是否成功。
	 */
	bool BuffPool::Free(void *buff)
	{
		if (NULL == buff) return false;

		PBUFFHEAD buffHead = (PBUFFHEAD)buff;
		buffHead--;    // 实际指向了new时的指针

		if (buffHead->usedCount > 1)
		{
			buffHead->usedCount--;
			return true;
		}
		else
		{
			return FreeItem(buffHead);
		}
	}

	/**
	 *\fn         SetTimes(void *buff, unsigned short newTimes = 1)
	 *\brief      重新设置内存块被使用次数。
	 *\param[in]  buff 数据指针。
	 *\param[in]  newTimes 新的使用次数。
	 *\return     释放是否成功。
	 */
	bool BuffPool::SetTimes(PVOID buff, unsigned short newTimes)
	{
		if (NULL == buff) return false;

		EnterCriticalSection(&csUsed_);

		PBUFFHEAD buffHead = (PBUFFHEAD)buff;

		(--buffHead)->usedCount = newTimes;

		LeaveCriticalSection(&csUsed_);

		return false;
	}
}