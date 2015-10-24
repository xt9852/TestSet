
#pragma once
#include "P2PBase.h"
#include "P2PProcessSendMsg.h"
#include "P2PProcessRecvMsg.h"
#include "03.Network/IOCP/PackQueue.h"


namespace XT_P2P
{
    /**
     *\class  P2PQueueLayout
     *\brief  该类主要是P2P的队列缓冲层
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PQueueLayout : public P2PLayoutBase
    {
    public:
        /**
         *\fn         P2PQueueLayout()
         *\brief      缺省构造函数。
         */
        P2PQueueLayout();

        /**
         *\fn         ~P2PQueueLayout()
         *\brief      析构函数。
         */
        ~P2PQueueLayout();

    public:
        /**
         *\fn         int send(P2PMsg *msg)
         *\brief      发送命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        virtual int send(P2PMsg *msg);

        /**
         *\fn         int recv(P2PMsg *msg)
         *\brief      接收命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        virtual int recv(P2PMsg *msg);

    protected:
        XT_IOCP::PackQueue recvQueue_;   // 接收队列
        XT_IOCP::PackQueue sendQueue_;   // 发送队列
        P2PProcessRecvMsg  recvMsgProc_; // 接收消息处理器
        P2PProcessSendMsg  sendMsgProc_; // 发成消息处理器
        
        /**
         *\fn         int init(P2PMsg *msg)
         *\brief      处理初始化命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int Init(P2PMsg *msg);

        /**
         *\fn         int Stop()
         *\brief      初始化。
         *\param[in]  无。
         *\return     无。
         */
        void Stop();

        /**
         *\fn         int getLayoutDataInfo(P2PMsg *msg)
         *\brief      得到本层的数据。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int getLayoutDataInfo(P2PMsg *msg);
    };
}