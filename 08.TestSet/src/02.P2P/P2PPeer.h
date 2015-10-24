
#pragma once
#include "P2PProtocol.h"
#include "P2PDataInfo.h"
#include "03.Network/IOCP/PackQueue.h"
#include "03.Network/IOCP/PrePack.h"
#include <map>
#include <list>

namespace XT_P2P
{
    class P2PPeer;

    typedef std::map<std::string, P2PPeer*> P2P_PEER_MAP;
    typedef std::list<P2PPeer*>             P2P_PEER_LIST;
    typedef std::list<P2P_ADDR>             P2P_PEER_ADDR_LIST;

    /**
     *\class  P2PPeer
     *\brief  该类主要是P2P的Peer
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PPeer
    {
    public:
        P2PPeer();
        ~P2PPeer();

    private:
        void                *client_;       // 客户端对象
        UINT                clientIndex_;   // 客户端对象索引
        XT_IOCP::BuffPool   *buffPool_;     // 内存池
        XT_IOCP::PackQueue  *sendQueue_;    // 发送队列
        P2PPeerDataInfo     dataInfo_;      // 统计数据信息

    public:
        void*     getClient() { return client_; }
        UINT      getClientIndex() { return clientIndex_; }
        UINT      getLastRecvTime() { return dataInfo_.getLastRecvTime(); }
        USHORT    getRecvSpeed() { return dataInfo_.getRecvSpeed(); }
        UINT      getId() { return dataInfo_.getId(); }
        UINT      getState() { return dataInfo_.getState(); }
        UINT      getWanIp() { return dataInfo_.getWanIp(); }
        UINT      getLanIp() { return dataInfo_.getLanIp(); }
        USHORT    getWanPort() { return dataInfo_.getWanPort(); }
        USHORT    getLanPort() { return dataInfo_.getLanPort(); }
        P2P_ADDR* getAddr() { return dataInfo_.getAddr(); }
        P2PPeerDataInfo* getData() { return &dataInfo_; }

        void setClient(void *client) { client_ = client; }
        void setClientIndex(UINT index) { clientIndex_ = index; }
        void setSendQueue(XT_IOCP::PackQueue *queue) { sendQueue_ = queue; }
        void setId(UINT id) { dataInfo_.setId(id); }
        void setState(UINT state) { dataInfo_.setState(state); }
        void setAddr(P2P_ADDR *addr) { dataInfo_.setAddr(addr); }
        void setLanIp(UINT ip) { dataInfo_.setLanIp(ip); }
        void setWanIp(UINT ip) { dataInfo_.setWanIp(ip); }
        void setLanPort(USHORT port) { dataInfo_.setLanPort(port); }
        void setWanPort(USHORT port) { dataInfo_.setWanPort(port); }
        void addRecvPack(UINT size) { dataInfo_.addRecvPack(size); }
        void addSendPack(UINT size) { dataInfo_.addSendPack(size); }

        /**
         *\fn         int send(XT_IOCP::PACK *pack)
         *\brief      发送命令
         *\param[in]  pack  要发送的数据包。
         *\return     0成功，其它失败
         */
        int send(XT_IOCP::PACK *pack);

        /**
         *\fn         int send(XT_IOCP::PACK *pack, UINT ip, USHORT port)
         *\brief      发送命令
         *\param[in]  pack  要发送的数据包。
         *\param[in]  ip    要发送到的IP地址。
         *\param[in]  port  要发送到的端口地址。
         *\return     0成功，其它失败
         */
        int send(XT_IOCP::PACK *pack, UINT ip, USHORT port);

        /**
         *\fn         int sendReq(LPCTSTR md5, UINT64 begin, UINT size)
         *\brief      发送请求下载数据命令
         *\param[in]  md5   请求的文件。
         *\param[in]  begin 请求数据的位置。
         *\param[in]  size  请求数据的大小。
         *\return     0成功，其它失败
         */
        int sendReq(LPCTSTR md5, UINT64 begin, UINT size);
    };
}