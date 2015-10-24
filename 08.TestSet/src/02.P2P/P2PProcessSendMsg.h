
#pragma once
#include "P2PBase.h"
#include "P2PDataInfo.h"
#include "03.Network/IOCP/Srv.h"

namespace XT_P2P
{
    class P2PLayoutBase;

    /**
     *\class  P2PProcessSendMsg
     *\brief  该类主要是P2P协议发送处理(可做流量限制)
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PProcessSendMsg
    {
    public:
        /**
         *\fn         P2PProcessSendMsg()
         *\brief      缺省构造函数。
         */
        P2PProcessSendMsg();

        /**
         *\fn         ~P2PProcessSendMsg()
         *\brief      析构函数。
         */
        ~P2PProcessSendMsg();

    public:
        XT_IOCP::PackQueue *sendQueue_;
        XT_IOCP::BuffPool  *buffPool_;
        XT_IOCP::IOCP      *iocp_;
        P2PDataInfo        dataInfo_;
        bool               running_;

    public:
        /**
		 *\fn         void setSendQueue(XT_IOCP::PackQueue *sendQueue)
		 *\brief      设置发送队列
		 *\param[in]  sendQueue	    发送队列指针。
         *\return     无。
		 */
        void setSendQueue(XT_IOCP::PackQueue *sendQueue) { sendQueue_ = sendQueue; }

        /**
		 *\fn         setBuffPool(XT_IOCP::BuffPool *buffPool)
		 *\brief      设置内存池
		 *\param[in]  buffPool	    内存池指针。
         *\return     无。
		 */
        void setBuffPool(XT_IOCP::BuffPool *buffPool) { buffPool_ = buffPool; }

        /**
		 *\fn         setIocp(XT_IOCP::IOCP *iocp)
		 *\brief      设置接收数据的对象
		 *\param[in]  iocp	        完成端口指针。
         *\return     无。
		 */
        void setIocp(XT_IOCP::IOCP *iocp) { iocp_ = iocp; }

        /**
         *\fn         int Start()
         *\brief      开始发送消息。
         *\param[in]  无。
         *\return     是否成功,0成功,其它失败。
         */
        int Start();

        /**
         *\fn         int Stop()
         *\brief      停止。
         *\param[in]  无。
         *\return     无。
         */
        void Stop();

        /**
		 *\fn         SendThread(LPVOID data)
		 *\brief      发送线程,从输出队列中读到数据并投递写操作。
		 *\param[in]  data    线程参数。
		 *\return     是否成功
		 */
		static unsigned __stdcall SendThread(LPVOID data);

        /**
		 *\fn         SendThreadProc()
		 *\brief      发送线程处理函数。
		 *\return     是否成功
		 */
		unsigned SendThreadProc();
    };

}