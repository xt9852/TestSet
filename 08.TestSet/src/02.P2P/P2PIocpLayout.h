
#pragma once
#include "P2PBase.h"
#include "03.Network/IOCP/IOCP.h"

namespace XT_P2P
{
    /**
     *\class  P2PIocpLayout
     *\brief  该类主要是P2P的IOCP完成端口数据收发层
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PIocpLayout : public P2PLayoutBase
    {
    public:
        /**
         *\fn         P2PIocpLayout()
         *\brief      缺省构造函数。
         */
        P2PIocpLayout();

        /**
         *\fn         ~P2PIocpLayout()
         *\brief      析构函数。
         */
        ~P2PIocpLayout();

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
        XT_IOCP::IOCP iocp_; // 完成端口

    protected:
        /**
         *\fn         int Init(P2PMsg *msg)
         *\brief      初始化完成端口。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int Init(P2PMsg *msg);

        /**
         *\fn         int Stop()
         *\brief      初始化。
         *\param[in]  无。
         *\return     是否成功,0成功,其它失败。
         */
        int Stop();

        /**
         *\fn         int AddListen(P2PMsg *msg)
         *\brief      在本地添加一个监听(本地UDP监听)。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int AddListen(P2PMsg *msg);

        /**
         *\fn         int getLayoutDataInfo(P2PMsg *msg)
         *\brief      得到本层的数据。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int getLayoutDataInfo(P2PMsg *msg);
    };

}