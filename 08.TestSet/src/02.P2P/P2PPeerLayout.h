
#pragma once
#include "P2PBase.h"
#include "P2PPeer.h"
#include "P2PPeerList.h"


namespace XT_P2P
{
#define P2P_CLIENT_COUNT    10

    /**
     *\class  P2PPeerLayout
     *\brief  该类主要是P2P的Peer组层
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PPeerLayout : public P2PLayoutBase
    {
    public:
        /**
         *\fn         P2PPeerLayout()
         *\brief      缺省构造函数。
         */
        P2PPeerLayout();

        /**
         *\fn         ~P2PPeerLayout()
         *\brief      析构函数。
         */
        ~P2PPeerLayout();

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
        P2P_PEER_LIST       usedPeerList_;      // 在线的用户
        P2P_PEER_LIST       freePeerList_;      // 已经下线的用户
        UINT                peerCountUseClient_[P2P_CLIENT_COUNT];
        void                *client_[P2P_CLIENT_COUNT];
        P2P_ADDR            myAddr_;            // 我的地址
        P2PPeerList         peerListInfo_;      // 服务器管理已经完成下载的用户
        UINT                peerId_;            // 客户端ID

        XT_IOCP::BuffPool   *buffPool_;         // 内存池
        XT_IOCP::PackQueue  *sendQueue_;        // 发送队列

    protected:
        /**
         *\fn         int Init(P2PMsg *msg)
         *\brief      初始化。
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
         *\fn         P2PPeer* createPeer(P2P_ADDR *addr)
         *\brief      创建一个客户端对象。
         *\param[in]  addr          客户端地址。
         *\return     客户端。
         */
        P2PPeer* createPeer(P2P_ADDR *addr);

        /**
         *\fn         int AddListen(P2PMsg *msg)
         *\brief      在本地添加一个监听(本地UDP监听)。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int AddListen(P2PMsg *msg);

        /**
         *\fn         int getConnectedPeer(P2PMsg *msg)
         *\brief      得已经连通的客户端。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int getConnectedPeer(P2PMsg *msg);

        /**
         *\fn         int getPeerData(P2PMsg *msg)
         *\brief      得到客户端信息。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int getPeerData(P2PMsg *msg);

        /**
         *\fn         int getLayoutDataInfo(P2PMsg *msg)
         *\brief      得到本层的数据。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int getLayoutDataInfo(P2PMsg *msg);

        /**
         *\fn         int SendData(XT_IOCP::PACK *pack, UINT ip, USHORT port)
         *\brief      发送数据。
         *\param[in]  pack          数据包。
         *\param[in]  ip            要发送到的IP地址。
         *\param[in]  port          要发送到的端口地址。
         *\return     是否成功,0成功,其它失败。
         */
        int SendData(XT_IOCP::PACK *pack, UINT ip, USHORT port);

        /**
         *\fn         int sendVersionReq(P2PMsg *msg)
         *\brief      向服务器请求最新的文件列表信息。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int sendVersionReq(P2PMsg *msg);

        /**
         *\fn         int sendVersionRsp(P2PMsg *msg)
         *\brief      向客户端发送最新的文件列表信息。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int sendVersionRsp(P2PMsg *msg);

        /**
         *\fn         int sendGetPeerListReq(P2PMsg *msg)
         *\brief      向服务器请求Peer列表。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int sendGetPeerListReq(P2PMsg *msg);

        /**
         *\fn         int recvGetPeerListReq(P2PMsg *msg)
         *\brief      服务器接收请求Peer列表。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int recvGetPeerListReq(P2PMsg *msg);

        /**
         *\fn         int recvGetPeerListRsp(P2PMsg *msg)
         *\brief      向服务器请求Peer列表应答。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int recvGetPeerListRsp(P2PMsg *msg);

        /**
         *\fn         int sendHelloReq(P2PMsg *msg)
         *\brief      客户端连通。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int sendHelloReq(P2PMsg *msg);

        /**
         *\fn         int recvHelloReq(P2PMsg *msg)
         *\brief      收到打洞请求。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int recvHelloReq(P2PMsg *msg);

        /**
         *\fn         int recvHelloRsp(P2PMsg *msg)
         *\brief      收到打洞应答。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int recvHelloRsp(P2PMsg *msg);

        /**
         *\fn         int sendDownloadReq(P2PMsg *msg)
         *\brief      向Peer请求下载文件(一次最大1M)。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int sendDownloadReq(P2PMsg *msg);

        /**
         *\fn         int sendDownloadRsp(P2PMsg *msg)
         *\brief      发送客户端请求的数据。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int sendDownloadRsp(P2PMsg *msg);
    };

}