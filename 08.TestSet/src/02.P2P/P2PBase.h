
#pragma once
#include "P2PDataInfo.h"


namespace XT_P2P
{
    class P2PMsg;

    /**
     *\class  P2PBase
     *\brief  该类主要是P2P层基础类
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PLayoutBase
    {
    public:
        /**
         *\fn         P2PLayoutBase()
         *\brief      缺省构造函数。
         */
        P2PLayoutBase();

        /**
         *\fn         ~P2PLayoutBase()
         *\brief      析构函数。
         */
        ~P2PLayoutBase();

    protected:
        P2PLayoutBase *pre_;        // 上一个节点
        P2PLayoutBase *next_;       // 下一个节点
        P2PDataInfo   dataInfo_;    // 统计数据信息

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

        /**
         *\fn         void setPre(P2PLayoutBase *layout)
         *\brief      设置上一层节点。
         *\param[in]  layout        层节点。
         *\return     无。
         */
        void setPre(P2PLayoutBase *layout) { pre_ = layout; }

        /**
         *\fn         void setNext(P2PLayoutBase *layout)
         *\brief      设置下一层节点。
         *\param[in]  layout        层节点。
         *\return     无。
         */
        void setNext(P2PLayoutBase *layout) { next_ = layout; }

        /**
         *\fn         P2PLayoutBase* getPre()
         *\brief      得到上一层节点。
         *\param[in]  无。
         *\return     上一层节点指针。
         */
        P2PLayoutBase* getPre() { return pre_; }

        /**
         *\fn         P2PLayoutBase* getNext()
         *\brief      得到下一层节点。
         *\param[in]  无。
         *\return     下一层节点指针。
         */
        P2PLayoutBase* getNext() { return next_; }

        /**
         *\fn         void addRecvPack(UINT size)
         *\brief      设置接收到的数据长。
         *\param[in]  size          数据长。
         *\return     无。
         */
        void addRecvPack(UINT size) { dataInfo_.addRecvPack(size); }

        /**
         *\fn         void addSendPack(UINT size)
         *\brief      设置发送的数据长。
         *\param[in]  size          数据长。
         *\return     无。
         */
        void addSendPack(UINT size) { dataInfo_.addSendPack(size); }

        /**
         *\fn         P2PDataInfo* getDataInfo()
         *\brief      得到统计数据。
         *\param[in]  无。
         *\return     统计数据。
         */
        P2PDataInfo* getDataInfo() { return &dataInfo_; }
    };

}