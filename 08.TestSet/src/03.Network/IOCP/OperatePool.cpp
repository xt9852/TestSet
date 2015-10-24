
#include "StdAfx.h"
#include "OperatePool.h"


namespace XT_IOCP
{

	/**
	 *\fn         OperatePool()
	 *\brief      缺省构造函数。
	 */
	OperatePool::OperatePool(void)
		:Pool(100)
	{
	}

	/**
	 *\fn         ~OperatePool()
	 *\brief      析构函数。
	 */
	OperatePool::~OperatePool(void)
	{
		DeleteAll();
	}

	/**
	 *\fn         NewItem()
	 *\brief      new一个单元,纯虚函数。
	 *\return     单元指针。
	 */
	void* OperatePool::NewItem()
	{
		POPERATE operate = new OPERATE;
		return operate;
	}

	/**
	 *\fn         DeleteItem()
	 *\brief      删除一个单元,纯虚函数。
	 *\param[in]  data 数据指针。
	 *\return     单元指针。
	 */
	void OperatePool::DeleteItem(void *data)
	{
		delete data;
	}

	/**
	 *\fn         Get()
	 *\brief      从池中取得一个操作对象。
	 *\return     操作对象指针。
	 */
	POPERATE OperatePool::Get()
	{
		POPERATE operate = (POPERATE)GetItem();
		return operate;
	}
}
