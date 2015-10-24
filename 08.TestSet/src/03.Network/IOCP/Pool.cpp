
#include "StdAfx.h"
#include "Pool.h"


namespace XT_IOCP
{

	/**
	 *\fn         Pool()
	 *\brief      缺省构造函数。
	 */
	Pool::Pool(void)
		:addCount_(1)
	{
		InitializeCriticalSection(&csUsed_);
	}

	/**
	 *\fn         Pool(int addCount)
	 *\brief      构造函数。
	 */
	Pool::Pool(int addCount)
	{
		addCount_ = addCount;
		InitializeCriticalSection(&csUsed_);
	}

	/**
	 *\fn         ~Pool()
	 *\brief      析构函数。
	 */
	Pool::~Pool(void)
	{
		DeleteCriticalSection(&csUsed_);
	}

	/**
	 *\fn         GetItem(void *buff)
	 *\brief      得到一个单元。
	 *\return     单元指针。
	 */
	void* Pool::GetItem()
	{
		void *buff = NULL;

		EnterCriticalSection(&csUsed_);

BEGIN:
		if (!freeData_.empty())
		{
			MAP_ADDR_NUM::iterator iter = freeData_.begin();

			buff = iter->first;

			freeData_.erase(iter);

#ifdef _DEBUG_POOL
			TRACE("%s Get addr:%x free:%d\n", name_.c_str(), buff, freeData_.size());
#endif
		}
		else
		{
			for (int i = 0; i < addCount_; i++)
			{
				buff = NewItem();
				allData_[buff] = 0;
				freeData_[buff] = 0;

#ifdef _DEBUG_POOL
				unsigned long all = 0;
				unsigned long free = 0;

				GetNumber(all, free);

				TRACE("%s new i=%d buf:%x all:%d free:%d\n", name_.c_str(), i, buff, all, free);
#endif
			}

			goto BEGIN;
		}

		LeaveCriticalSection(&csUsed_);
		return buff;
	}

	/**
	 *\fn         FreeItem(void *buff)
	 *\brief      释放一个单元。
	 *\param[in]  data 数据指针。
	 *\return     释放是否成功。
	 */
	bool Pool::FreeItem(void *buff)
	{
		if (NULL == buff) return false;

		EnterCriticalSection(&csUsed_);

#ifdef _DEBUG_POOL

		unsigned long all = 0;
		unsigned long free = 0;

		this->GetNumber(all, free);

		TRACE("%s Free all:%d free:%d----\n", name_.c_str(), all, free);

		MAP_ADDR_NUM::iterator iter = allData_.find(buff);

		if (iter != allData_.end())
		{
			TRACE("%s all buf:%x used:%d\n", name_.c_str(), buff, iter->second);
		}
		else
		{
			TRACE("%s all Don't find buf:%x\n", name_.c_str(), buff, all, free);
		}

		iter = freeData_.find(buff);

		if (iter != freeData_.end())
		{
			TRACE("%s free buf:%x used:%d\n", name_.c_str(), buff, iter->second);
		}
		else
		{
			TRACE("%s free Don't find buf:%x\n", name_.c_str(), buff);
		}
#endif

		freeData_[buff] = 0;

#ifdef _DEBUG_POOL
		this->GetNumber(all, free);
		TRACE("%s Free now all:%d free:%d\n", name_.c_str(), all, free);
#endif

		LeaveCriticalSection(&csUsed_);
		return false;
	}

	/**
	 *\fn         DeleteAll()
	 *\brief      删除所有的数据。
	 *\return     是否成功。
	 */
	bool Pool::DeleteAll()
	{
		try
		{
			EnterCriticalSection(&csUsed_);

#ifdef _DEBUG_POOL
			unsigned long all = 0;
			unsigned long free = 0;

			this->GetNumber(all, free);

			TRACE("%s DeleteAll all:%d free:%d\n", name_.c_str(), all, free);
#endif

			void *buff = NULL;
			
			while (!allData_.empty())
			{
				MAP_ADDR_NUM::iterator iter = allData_.begin();

				if (iter != allData_.end())
				{
					buff = iter->first;

#ifdef _DEBUG_POOL
					MAP_ADDR_NUM::iterator iterMap = allData_.find(buff);

					if (iterMap != allData_.end())
					{
						TRACE(" buf:%x size:%d\n", buff, allData_.size());
					}
					else
					{
						TRACE(" Don't find buf:%x\n", buff);
					}
#endif

					allData_.erase(iter);
					
					DeleteItem(buff);
				}	
			}

			LeaveCriticalSection(&csUsed_);
		}
		catch (...)
		{
			LeaveCriticalSection(&csUsed_);
			TRACE("DeleteAll error %d\n", ::GetLastError());
			return false;
		}

		return true;
	}

	/**
	 *\fn         GetNumber(unsigned long &allCount, unsigned long &freeCount)
	 *\brief      得到总数和剩余数量。
	 *\param[out] allCount  总数。
	 *\param[out] freeCount 剩余数。
	 */
	void Pool::GetNumber(unsigned long &allCount, unsigned long &freeCount)
	{
		EnterCriticalSection(&csUsed_);
		allCount = allData_.size();
		freeCount = freeData_.size();
		LeaveCriticalSection(&csUsed_);
	}

}