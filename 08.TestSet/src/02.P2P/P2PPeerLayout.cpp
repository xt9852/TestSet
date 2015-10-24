
#include "StdAfx.h"
#include "P2PPeerLayout.h"
#include "08.Algorithm/base/XTXml.h"
#include "03.Network/IOCP/BuffPool.h"
#include "03.Network/IOCP/ClientPool.h"


namespace XT_P2P
{
	/**
	 *\fn         P2PPeerLayout()
	 *\brief      缺省构造函数。
	 */
    P2PPeerLayout::P2PPeerLayout()
        :buffPool_(NULL),
        sendQueue_(NULL),
        peerId_(0)
    {
        memset(client_, 0, sizeof(void*)*P2P_CLIENT_COUNT);
        memset(peerCountUseClient_, 0, sizeof(UINT)*P2P_CLIENT_COUNT);
	}

	/**
	 *\fn         ~P2PPeerLayout()
	 *\brief      析构函数。
	 */
	P2PPeerLayout::~P2PPeerLayout()
	{
        Stop();
	}

    /**
     *\fn         int send(P2PMsg *msg)
     *\brief      发送命令。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::send(P2PMsg *msg)
    {
        if (NULL == msg || NULL == next_) return P2P_ERR_PEER_SEND_INPUT;

        addSendPack(msg->size_);

        switch (msg->id_)
        {
        case P2P_INIT:
            {
                return Init(msg);
            }
        case P2P_STOP:
            {
                Stop();
                return next_->send(msg);
            }
        case P2P_ADD_LISTEN:
            {
                return AddListen(msg);
            }
        case P2P_GET_VERSION_REQ:
            {
                return sendVersionReq(msg);
            }
        case P2P_GET_VERSION_RSP:
            {
                return sendVersionRsp(msg);
            }
        case P2P_GET_PEER_LIST_REQ:
            {
                return sendGetPeerListReq(msg);
            }
        case P2P_PEER_HELLO:
            {
                return sendHelloReq(msg);
            }
        case P2P_PEER_GET_CONNECTED_PEER:
            {
                return getConnectedPeer(msg);
            }
        case P2P_PEER_DATA_INFO:
            {
                return getPeerData(msg);
            }
        case P2P_LAYOUT_DATA_INFO:
            {
                return getLayoutDataInfo(msg);
            }
        case P2P_GET_DATA_REQ:
            {
                return sendDownloadReq(msg);
            }
        case P2P_GET_DATA_RSP:
            {
                return sendDownloadRsp(msg);
            }
        default:
            {
                return next_->send(msg);
            }
        }
    }

    /**
     *\fn         int recv(P2PMsg *msg)
     *\brief      接收命令。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::recv(P2PMsg *msg)
    {
        if (NULL == pre_ || NULL == msg) return P2P_ERR_PEER_RECV_INPUT;

        addRecvPack(msg->size_);

        switch (msg->id_)
        {
        case P2P_GET_PEER_LIST_REQ:
            {
                return recvGetPeerListReq(msg);
            }
        case P2P_GET_PEER_LIST_RSP:
            {
                return recvGetPeerListRsp(msg);
            }
        case P2P_HELLO_REQ:
            {
                return recvHelloReq(msg);
            }
        case P2P_HELLO_RSP:
            {
                return recvHelloRsp(msg);
            }
        default:
            {
                return pre_->recv(msg);
            }
        }
    }

    /**
     *\fn         int Init(P2PMsg *msg)
     *\brief      初始化。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::Init(P2PMsg *msg)
    {
        if (NULL == msg) return P2P_ERR_PEER_SEND_INPUT;

        int ret = next_->send(msg);

        if (0 != ret) return ret;

        P2PInsideMsg *init = (P2PInsideMsg*)msg;

        buffPool_ = (XT_IOCP::BuffPool*)init->getBuffPool();
        sendQueue_ = (XT_IOCP::PackQueue*)init->getSendQueue();

        return 0;
    }

    /**
     *\fn         int Stop()
     *\brief      初始化。
     *\param[in]  无。
     *\return     无。
     */
    void P2PPeerLayout::Stop()
    {
        P2P_PEER_LIST::iterator iter = usedPeerList_.begin();
        for (; iter != usedPeerList_.end(); ++iter)
        {
            P2PPeer *peer = *iter;
            delete peer;
        }

        usedPeerList_.clear();

        iter = freePeerList_.begin();
        for (; iter != freePeerList_.end(); ++iter)
        {
            P2PPeer *peer = *iter;
            delete peer;
        }

        freePeerList_.clear();
    }

    /**
     *\fn         int AddListen(P2PMsg *msg)
     *\brief      在本地添加一个监听(本地UDP监听)。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::AddListen(P2PMsg *msg)
    {
        P2PInsideMsg *addPeer = (P2PInsideMsg*)msg;

        for (int i = 0; i < P2P_CLIENT_COUNT; )
        {
            int ret = next_->send(addPeer);

            addPeer->setListenPort(addPeer->getListenPort() + 1);

            if (0 != ret) continue;

            if (0 == myAddr_.lanIp_)
            {
                myAddr_.lanIp_ = inet_addr(addPeer->getListenIp());
                myAddr_.lanPort_ = htons(addPeer->getListenPort());
                myAddr_.wanIp_ = inet_addr(addPeer->getListenIp());
                myAddr_.wanPort_ = htons(addPeer->getListenPort());
            }

            i++;

            client_[i-1] = addPeer->getListenClient();
        }

        return 0;
    }

    /**
     *\fn         int getConnectedPeer(P2PMsg *msg)
     *\brief      得已经连通的客户端。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::getConnectedPeer(P2PMsg *msg)
    {
        P2PInsideMsg *getPeer = (P2PInsideMsg*)msg;

        P2P_PEER_REQ_MAP *peerMap = (P2P_PEER_REQ_MAP*)getPeer->getPeerList();

        P2P_REQ_DATA_LIST reqList;

        P2P_PEER_LIST::iterator iter = usedPeerList_.begin();
        for (; iter != usedPeerList_.end(); ++iter)
        {
            P2PPeer *peer = *iter;

            if (peer->getState() == PEER_STATE_LAN_CONNECTED || 
                peer->getState() == PEER_STATE_WAN_CONNECTED)
            {
                (*peerMap)[peer] = reqList;
            }
        }

        return 0;
    }

    /**
     *\fn         int getPeerData(P2PMsg *msg)
     *\brief      得到客户端信息。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::getPeerData(P2PMsg *msg)
    {
        P2PInsideMsg *getPeer = (P2PInsideMsg*)msg;

        P2P_DATA_PTR_LIST *peerList = (P2P_DATA_PTR_LIST*)getPeer->getPeerList();

        P2P_PEER_LIST::iterator iter = usedPeerList_.begin();
        for (; iter != usedPeerList_.end(); ++iter)
        {
            P2PPeer *peer = *iter;

            peerList->push_back(peer->getData());
        }

        return 0;
    }

    /**
     *\fn         int getLayoutDataInfo(P2PMsg *msg)
     *\brief      得到本层的数据。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::getLayoutDataInfo(P2PMsg *msg)
    {
        P2PInsideMsg *dataInfo = (P2PInsideMsg*)msg;

        P2P_DATA_PTR_LIST *dataList = (P2P_DATA_PTR_LIST*)dataInfo->getLayoutList();

        dataList->push_back(getDataInfo());

        return next_->send(msg);
    }

    /**
     *\fn         int SendData(XT_IOCP::PACK *pack, UINT ip, USHORT port)
     *\brief      发送数据。
     *\param[in]  pack          数据包。
     *\param[in]  ip            要发送到的IP地址。
     *\param[in]  port          要发送到的端口地址。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::SendData(XT_IOCP::PACK *pack, UINT ip, USHORT port)
    {
        if (NULL == pack || NULL == sendQueue_) return -1;

        sendQueue_->Add(client_[0], pack, pack->getPackLen(), ip, port);

        addSendPack(pack->getPackLen());

        return 0;
    }

    /**
     *\fn         int sendVersionReq(P2PMsg *msg)
     *\brief      向服务器请求最新的文件列表信息。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::sendVersionReq(P2PMsg *msg)
    {
        P2PGetVersionReq *req = (P2PGetVersionReq*)msg;

        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)buffPool_->Get(1);

        pack->clear(P2P_GET_VERSION_REQ);

        pack->setData(0, &(req->projectId_), sizeof(req->projectId_));

        SendData(pack, inet_addr(req->ip_), htons(req->port_));

        addSendPack(pack->getPackLen());

        TRACE("P2PPeerLayout::sendVersionReq->%s:%d\n", req->ip_, req->port_);

        return 0;
    }

    /**
     *\fn         int sendVersionRsp(P2PMsg *msg)
     *\brief      向客户端发送最新的文件列表信息。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::sendVersionRsp(P2PMsg *msg)
    {
        P2PInsideMsg *rsp = (P2PInsideMsg*)msg;

        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)rsp->getRecvPack();

        SendData(pack, rsp->getRecvIp(), rsp->getRecvPort());

        addSendPack(pack->getPackLen());

#ifdef _DEBUG
        UINT ip = rsp->getRecvIp();
        USHORT port = rsp->getRecvPort();

        TRACE("P2PPeerLayout::sendVersionRsp->%s:%d\n", 
            inet_ntoa(*(in_addr*)&ip), ntohs(port));
#endif // _DEBUG

        return 0;
    }

    /**
     *\fn         int sendGetPeerListReq(P2PMsg *msg)
     *\brief      向服务器请求Peer列表。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::sendGetPeerListReq(P2PMsg *msg)
    {
        P2PGetPeerListReq *req = (P2PGetPeerListReq*)msg;

        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)buffPool_->Get(1);
        pack->clear(P2P_GET_PEER_LIST_REQ);

        SendData(pack, inet_addr(req->ip_), htons(req->port_));

        addSendPack(pack->getPackLen());

        TRACE("P2PPeerLayout::sendGetPeerListReq->%s:%d\n", req->ip_, req->port_);

        return 0;
    }

    /**
     *\fn         int recvGetPeerListReq(P2PMsg *msg)
     *\brief      服务器接收请求Peer列表。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::recvGetPeerListReq(P2PMsg *msg)
    {
        P2PInsideMsg *req = (P2PInsideMsg*)msg;
        buffPool_->Free(req->getRecvPack());

        // 客户端外网地址
        struct sockaddr_in clientAddr;
        int addrLen = sizeof(clientAddr);

        XT_IOCP::PCLIENT client = (XT_IOCP::PCLIENT)req->getRecvClient();
        getsockname(client->sock, (struct sockaddr *)&clientAddr, &addrLen);

        // 发送应答
        UINT peerCountInPack = (K(1) - sizeof(P2PGetPeerListRsp)) / sizeof(P2P_ADDR);
        UINT peerCount = peerListInfo_.getPeerCount();
        P2P_ADDR *data = (P2P_ADDR*)peerListInfo_.getBuff();

        for (int i = peerCount; i > 0; i -= peerCountInPack)
        {
            XT_IOCP::PACK *pack = (XT_IOCP::PACK*)buffPool_->Get(1);
            pack->clear(P2P_GET_PEER_LIST_RSP);
 
            P2PGetPeerListRsp *rsp = (P2PGetPeerListRsp*)pack->getData();
            rsp->setData(clientAddr.sin_addr.S_un.S_addr, clientAddr.sin_port, 
                (i > peerCountInPack ? peerCountInPack : i));

            P2P_ADDR *addr = (P2P_ADDR*)&rsp[1];
            memcpy(addr, &data[i-1], sizeof(P2P_ADDR) * rsp->peerCount_);

            pack->dataLen = sizeof(P2PGetPeerListRsp) + sizeof(P2P_ADDR) * rsp->peerCount_;
            SendData(pack, req->getRecvIp(), req->getRecvPort());
        }

        return 0;
    }

    /**
     *\fn         int recvGetPeerListRsp(P2PMsg *msg)
     *\brief      向服务器请求Peer列表应答。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::recvGetPeerListRsp(P2PMsg *msg)
    {
        P2PInsideMsg *rsp = (P2PInsideMsg*)msg;

        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)rsp->getRecvPack();
        P2PGetPeerListRsp *data = (P2PGetPeerListRsp*)pack->getData();
        P2P_ADDR *addr = (P2P_ADDR*)&data[1];

        // 自己的外网IP，端口
        myAddr_.wanIp_ = data->myWanIp_;
        myAddr_.wanPort_ = data->myWanPort_;

        // 得到的用户
        for (int i = 0; i < data->peerCount_; i++)
        {
            P2P_PEER_LIST::iterator iter = usedPeerList_.begin();
            for (; iter != usedPeerList_.end(); ++iter)
            {
                P2PPeer *peer = *iter;

                int ret = memcmp(&addr[i], peer->getAddr(), sizeof(P2P_ADDR));
                if (0 == ret) // 已存在
                {
                    break;
                }
                else if (ret < 0) // 插入一个新的,小于iterm
                {
                    P2PPeer *newPeer = createPeer(&addr[i]);

                    usedPeerList_.insert(iter, newPeer);
                }
            }

            // 插入一个新的,最大
            if (iter == usedPeerList_.end())
            {
                P2PPeer *newPeer = createPeer(&addr[i]);

                usedPeerList_.push_back(newPeer);
            }

            // 开始打洞
            sendHelloReq(msg);
        }

        buffPool_->Free(rsp->getRecvPack());
        return 0;
    }

    /**
     *\fn         P2PPeer* createPeer(P2P_ADDR *addr)
     *\brief      创建一个客户端对象。
     *\param[in]  addr          客户端地址。
     *\return     客户端。
     */
    P2PPeer* P2PPeerLayout::createPeer(P2P_ADDR *addr)
    {
        UINT index = peerCountUseClient_[0];

        for (int i = 1; i < P2P_CLIENT_COUNT; i++)
        {
            if (index < peerCountUseClient_[i])
            {
                index = peerCountUseClient_[i];
            }
        }

        peerCountUseClient_[index]++;

        P2PPeer *newPeer = new P2PPeer;
        newPeer->setId(peerId_++);
        newPeer->setAddr(addr);
        newPeer->setClient(client_[index]);
        newPeer->setClientIndex(index);
        newPeer->setSendQueue(sendQueue_);
        newPeer->addRecvPack(0);

#ifdef _DEBUG
        TRACE("AddPeer wan:%s:%d lan:%s:%d\n", 
            inet_ntoa(*(in_addr*)&(addr->wanIp_)), ntohs(addr->wanPort_),
            inet_ntoa(*(in_addr*)&(addr->lanIp_)), ntohs(addr->lanPort_));
#endif // _DEBUG

        return newPeer;
    }

    /**
     *\fn         int sendHelloReq(P2PMsg *msg)
     *\brief      客户端连通。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::sendHelloReq(P2PMsg *msg)
    {
        P2P_PEER_LIST::iterator iter = usedPeerList_.begin();

        for (; iter != usedPeerList_.end(); ++iter)
        {
            P2PPeer *peer = *iter;

            // 10秒还没有接收到数据可以客户端已经下线
            if ((GetTickCount() - peer->getLastRecvTime()) > SECOND(5))
            {
                TRACE(_T("peer %d timeout\n"), peer->getId());
                peer->setState(PEER_STATE_BREAK);
            }
            else
            {
                XT_IOCP::PACK *pack = (XT_IOCP::PACK*)buffPool_->Get(2);
                pack->clear(P2P_HELLO_REQ);
                pack->setData(0, &myAddr_, sizeof(P2P_ADDR));

                P2P_ADDR *addr = peer->getAddr();

                peer->send(pack, addr->lanIp_, addr->lanPort_);
                peer->send(pack, addr->wanIp_, addr->wanPort_);

                addRecvPack(pack->getPackLen());
                addRecvPack(pack->getPackLen());

// #ifdef _DEBUG
//                 TRACE("peer %d send hello to wan:%s:%d lan:%s:%d\n", peer->getId(),
//                     inet_ntoa(*(in_addr*)&(addr->wanIp_)), ntohs(addr->wanPort_),
//                     inet_ntoa(*(in_addr*)&(addr->lanIp_)), ntohs(addr->lanPort_));
// #endif // _DEBUG
            }
        }

        return 0;
    }

    /**
     *\fn         int recvHelloReq(P2PMsg *msg)
     *\brief      收到打洞请求。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::recvHelloReq(P2PMsg *msg)
    {
        P2PInsideMsg *helloReq = (P2PInsideMsg*)msg;

        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)helloReq->getRecvPack();

        P2P_ADDR *sendPeerAddr = (P2P_ADDR*)pack->getData();

        P2P_PEER_LIST::iterator iter = usedPeerList_.begin();
        for (; iter != usedPeerList_.end(); ++iter)
        {
            P2PPeer *peer = *iter;

            bool inLan = (helloReq->getRecvIp() == peer->getLanIp());
            bool inWan = (helloReq->getRecvIp() == peer->getWanIp());

            if (inLan || inWan)
            {
                peer->addRecvPack(pack->getPackLen());
                peer->setState(inLan?PEER_STATE_LAN_RECVED:PEER_STATE_WAN_RECVED);
                break;
            }
        }

        // 发送应答
        pack->protoId = P2P_HELLO_RSP;
        SendData(pack, helloReq->getRecvIp(), helloReq->getRecvPort());
        return 0;
    }

    /**
     *\fn         int recvHelloRsp(P2PMsg *msg)
     *\brief      收到打洞应答。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::recvHelloRsp(P2PMsg *msg)
    {
        P2PInsideMsg *helloRsp = (P2PInsideMsg*)msg;

        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)helloRsp->getRecvPack();

        P2P_ADDR *sendPeerAddr = (P2P_ADDR*)pack->getData();

        P2P_PEER_LIST::iterator iter = usedPeerList_.begin();
        for (; iter != usedPeerList_.end(); ++iter)
        {
            P2PPeer *peer = *iter;

            bool inLan = (helloRsp->getRecvIp() == peer->getLanIp());
            bool inWan = (helloRsp->getRecvIp() == peer->getWanIp());

            if (inLan || inWan)
            {
                peer->addRecvPack(pack->getPackLen());
                peer->setState(inLan?PEER_STATE_LAN_CONNECTED:PEER_STATE_WAN_CONNECTED);
            }
        }

        buffPool_->Free(pack);
        return 0;
    }

    /**
     *\fn         int sendDownloadReq(P2PMsg *msg)
     *\brief      向Peer请求下载文件(一次最大1M)。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::sendDownloadReq(P2PMsg *msg)
    {
        P2PInsideMsg *req = (P2PInsideMsg*)msg;

        P2P_PEER_REQ_MAP *peerReqMap = (P2P_PEER_REQ_MAP*)req->getReqList();

        P2P_PEER_REQ_MAP::const_iterator iterMap = peerReqMap->begin();

        for (; iterMap != peerReqMap->end(); ++iterMap)
        {
            P2PPeer *peer = (P2PPeer*)iterMap->first;
            P2P_REQ_DATA_LIST reqList = iterMap->second;

            XT_IOCP::PACK *pack = NULL;
            P2PGetDataReq *req = NULL;
            GET_DATA_INFO *reqItem = NULL;
            UINT maxReqCount = (buffPool_->getSize() - sizeof(P2PGetDataReq)) / sizeof(GET_DATA_INFO) + 1;

            P2P_REQ_DATA_LIST::const_iterator iterList = reqList.begin();

            for (; iterList != reqList.end(); ++iterList)
            {
                REQ_DATA_INFO reqData = *iterList;
begin:
                if (NULL == pack)
                {
                    pack = (XT_IOCP::PACK*)buffPool_->Get(1);
                    pack->clear(P2P_GET_DATA_REQ);
                    pack->dataLen = sizeof(P2PGetDataReq);

                    req = (P2PGetDataReq*)pack->getData();
                    _tcscpy_s(req->md5_, ARRAYSIZE(req->md5_), reqData.md5_);
                    req->speed_ = (0 == peer->getRecvSpeed()) ? 500 : peer->getRecvSpeed();
                    req->questCount_ = 1;                    
                    req->position_.begin_ = reqData.begin_;
                    req->position_.size_ = reqData.size_;

                    reqItem = &(req->position_);
                    reqItem++;
                }
                else if (0 == _tcscmp(req->md5_, reqData.md5_))
                {
                    if (req->questCount_ < maxReqCount)
                    {
                        req->questCount_++;
                        reqItem->begin_ = reqData.begin_;
                        reqItem->size_ = reqData.size_;
                        reqItem++;
                    }
                    else
                    {
                        pack->dataLen = (req->questCount_-1) * sizeof(GET_DATA_INFO) + sizeof(P2PGetDataReq);
                        peer->send(pack);
                        addSendPack(pack->dataLen);
                        pack = NULL;
                        goto begin;
                    }
                }
                else
                {
                    pack->dataLen = (req->questCount_-1) * sizeof(GET_DATA_INFO) + sizeof(P2PGetDataReq);
                    peer->send(pack);
                    addSendPack(pack->dataLen);
                    pack = NULL;
                    goto begin;
                }
            }

            if (NULL != pack)
            {
                pack->dataLen = (req->questCount_-1) * sizeof(GET_DATA_INFO) + sizeof(P2PGetDataReq);
                peer->send(pack);
                addSendPack(pack->dataLen);
                pack = NULL;
            }
        }

        return 0;
    }

    /**
     *\fn         int sendDownloadRsp(P2PMsg *msg)
     *\brief      发送客户端请求的数据。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PPeerLayout::sendDownloadRsp(P2PMsg *msg)
    {
        P2PGetDataRsp *rsp = (P2PGetDataRsp*)msg;

        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)rsp->pack_;

        SendData(pack, rsp->ip_, rsp->port_);

        addSendPack(pack->getPackLen());

        return 0;
    }
}