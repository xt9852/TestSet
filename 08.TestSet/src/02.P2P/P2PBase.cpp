
#include "StdAfx.h"
#include "P2PBase.h"


namespace XT_P2P
{

	/**
	 *\fn         P2PLayoutBase()
	 *\brief      缺省构造函数。
	 */
	P2PLayoutBase::P2PLayoutBase()
        :pre_(NULL),
        next_(NULL)
	{
	}

	/**
	 *\fn         ~P2PLayoutBase()
	 *\brief      析构函数。
	 */
	P2PLayoutBase::~P2PLayoutBase()
	{
	}

    /**
     *\fn         int send(P2PMsg *msg)
     *\brief      发送命令。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PLayoutBase::send(P2PMsg *msg)
    {
        if (NULL == next_ || NULL == msg) return -1;

        return next_->send(msg);
    }

    /**
     *\fn         int recv(P2PMsg *msg)
     *\brief      接收命令。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PLayoutBase::recv(P2PMsg *msg)
    {
        if (NULL == pre_ || NULL == msg) return -1;

        return pre_->recv(msg);
    }
}