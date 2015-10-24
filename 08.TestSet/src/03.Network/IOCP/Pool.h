
#pragma once
#include <map>
#include <list>
#include <string>

#define WIN32_LEAN_AND_MEAN	// 去除winsock.h包含
#include <Windows.h>


namespace XT_IOCP
{

	typedef std::map<void*, long>	MAP_ADDR_NUM;

	typedef std::list<void*>		LIST_VOID;


	/**
	 *\class  Pool
	 *\brief  该类主要是池类的基类
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	class Pool
	{
	public:
		/**
		 *\fn         Pool()
		 *\brief      缺省构造函数。
	     */
		Pool();

		/**
		 *\fn         Pool(int addCount)
		 *\brief      构造函数。
	     */
		Pool(int addCount);

		/**
		 *\fn         ~Pool()
		 *\brief      析构函数。
	     */
		~Pool();

	public:
		CRITICAL_SECTION	csUsed_;	// 临界区
		MAP_ADDR_NUM		allData_;	// 所有的单元
		MAP_ADDR_NUM		freeData_;	// 空闲的单元
		int					addCount_;	// 每次添加的数据

#ifdef _DEBUG
		std::string			name_;		// 类对象名
#endif

	public:
		/**
		 *\fn         GetItem()
		 *\brief      得到一个单元。
		 *\return     单元指针。
		 */
		void* GetItem();

		/**
		 *\fn         FreeItem(void *data)
		 *\brief      释放一个单元。
		 *\param[in]  data 数据指针。
		 *\return     释放是否成功。
		 */
		bool  FreeItem(void *data);

		/**
		 *\fn         NewItem()
		 *\brief      new一个单元,纯虚函数。
		 *\return     单元指针。
		 */
		virtual void* NewItem() = 0;

		/**
		 *\fn         DeleteItem()
		 *\brief      删除一个单元,纯虚函数。
		 *\param[in]  data 数据指针。
		 *\return     单元指针。
		 */
		virtual void DeleteItem(void *data) = 0;

		/**
		 *\fn         DeleteAll()
		 *\brief      删除所有的数据。
		 *\return     是否成功。
		 */
		bool  DeleteAll();

		/**
		 *\fn         GetNumber(unsigned long &allCount, unsigned long &freeCount)
		 *\brief      得到总数和剩余数量。
		 *\param[out] allCount  总数。
		 *\param[out] freeCount 剩余数。
		 */
		void  GetNumber(unsigned long &allCount, unsigned long &freeCount);
		
		/**
		 *\fn         setAddCount(int addCount)
		 *\brief      得到一次new几个单元。
		 *\param[in]  addCount 数量。
		 */
		void  setAddCount(int addCount) { addCount_ = addCount; }
	};

}