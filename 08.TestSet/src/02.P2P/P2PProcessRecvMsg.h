
#pragma once
#include "P2PBase.h"
#include "P2PDataInfo.h"
#include "03.Network/IOCP/Srv.h"

namespace XT_P2P
{
    class P2PLayoutBase;

    /**
     *\class  P2PProcessRecvMsg
     *\brief  该类主要是P2P协议接收处理(可做流量限制)
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PProcessRecvMsg
    {
    public:
        /**
         *\fn         P2PProcessRecvMsg()
         *\brief      缺省构造函数。
         */
        P2PProcessRecvMsg();

        /**
         *\fn         ~P2PProcessRecvMsg()
         *\brief      析构函数。
         */
        ~P2PProcessRecvMsg();

    public:
        XT_IOCP::PackQueue *recvQueue_;
        XT_IOCP::BuffPool  *buffPool_;
        P2PLayoutBase      *pre_;
        P2PDataInfo        dataInfo_;
        bool               running_;

    public:
        /**
		 *\fn         void setRecvQueue(XT_IOCP::PackQueue *recvQueue)
		 *\brief      设置接收队列
		 *\param[in]  recvQueue	    接收队列指针。
         *\return     无。
		 */
        void setRecvQueue(XT_IOCP::PackQueue *recvQueue) { recvQueue_ = recvQueue; }

        /**
		 *\fn         setBuffPool(XT_IOCP::BuffPool *buffPool)
		 *\brief      设置内存池
		 *\param[in]  buffPool	    内存池指针。
         *\return     无。
		 */
        void setBuffPool(XT_IOCP::BuffPool *buffPool) { buffPool_ = buffPool; }

        /**
		 *\fn         setPre(P2PLayoutBase *pre)
		 *\brief      设置接收对象
		 *\param[in]  buffPool	    内存池指针。
         *\return     无。
		 */
        void setPre(P2PLayoutBase *pre) { pre_ = pre; }

        /**
         *\fn         int Start()
         *\brief      开始处理消息。
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
		 *\fn         RecvThreadFunc()
		 *\brief      实现处理函数。
		 *\return     是否成功(0成功，其它失败)
		 */
		int RecvThreadFunc();
		
		/**
		 *\fn         ProcessPackThread(void *pParam)
		 *\brief      处理线程。
		 *\param[in]  param  线程参数。
		 *\return     是否成功(0成功，其它失败)
		 */
		static unsigned __stdcall RecvThread(void *param);

        /**
		 *\fn         ProcessPack(void *client, void *buf, int len, int ip, short port)
		 *\brief      处理数据包
		 *\param[in]  client	客户端对象。
		 *\param[in]  buf		数据。
		 *\param[in]  len		数据长。
		 *\param[in]  ip		对方IP(UDP)。
		 *\param[in]  port		对方端口(UDP)。
		 */
		void ProcessPack(void *client, void *buf, int len, int ip, short port);
    };

}