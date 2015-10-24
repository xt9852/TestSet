
#include "StdAfx.h"
#include "P2PProcessSendMsg.h"
#include "P2PProtocol.h"


namespace XT_P2P
{

	/**
	 *\fn         P2PProcessSendMsg()
	 *\brief      缺省构造函数。
	 */
	P2PProcessSendMsg::P2PProcessSendMsg()
        :sendQueue_(NULL),
        buffPool_(NULL),
        iocp_(NULL),
        running_(false)
	{
	}

	/**
	 *\fn         ~P2PProcessSendMsg()
	 *\brief      析构函数。
	 */
	P2PProcessSendMsg::~P2PProcessSendMsg()
	{
	}

    /**
     *\fn         int StartSend()
     *\brief      开始发送消息。
     *\param[in]  无。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PProcessSendMsg::Start()
    {
        if (running_) return -1;

        running_ = true;

        unsigned int threadID = 0;
        HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, SendThread, this, 0, &threadID);

        if ((NULL == thread) || (NULL == iocp_) && (NULL == buffPool_) || (NULL == sendQueue_))
        {
            running_ = false;
            return P2P_ERR_QUEUE_SEND_START;
        }

        return 0;
    }

    /**
     *\fn         int Stop()
     *\brief      停止。
     *\param[in]  无。
     *\return     无。
     */
    void P2PProcessSendMsg::Stop()
    {
        running_ = false;
    }

    /**
	 *\fn         SendThread(LPVOID data)
	 *\brief      发送线程,从输出队列中读到数据并投递写操作。
	 *\param[in]  data    线程参数。
	 *\return     是否成功
	 */
    unsigned P2PProcessSendMsg::SendThread(LPVOID param)
    {
        if (NULL == param) return P2P_ERR_QUEUE_SEND_THREAD_INPUT;

        P2PProcessSendMsg *pThis = reinterpret_cast<P2PProcessSendMsg*>(param);

        try
        {
            return pThis->SendThreadProc();
        }
        catch (...)
        {
            LOG(ERROR) << _T("P2PProcessRecvMsg::SendThread error:") << ::GetLastError();
            return P2P_ERR_QUEUE_SEND_THREAD_EXCEPT;
        }
    }

	/**
	 *\fn         SendThreadProc()
	 *\brief      发送线程处理函数。
	 *\return     是否成功
	 */
    unsigned P2PProcessSendMsg::SendThreadProc(void)
    {
        void  *client  = NULL;
        void  *buf     = NULL;
        int   len      = 0;
        int   ip       = {0};
        short port     = 0;
        short waitTime = 1;
        short times    = 0;

        while (running_)
        {
            if (sendQueue_->Get(&client, &buf, len, ip, port))
            {
                iocp_->SendData((XT_IOCP::CLIENT*)client, buf, len, ip, port);
                waitTime = 0;
            }
            else
            {
                ::Sleep(waitTime); // 如果不加它CPU将100%
                if (++times > 10000)
                {
                    times = 0;
                    waitTime = 1;
                }
            }
        }

        return 0;
    }
}