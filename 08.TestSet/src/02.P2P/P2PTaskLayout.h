
#pragma once
#include "P2PBase.h"
#include "P2PTask.h"
#include "03.Network/IOCP/BuffPool.h"
#include "08.Algorithm/base/XTXml.h"
#include <map>
#include <list>


namespace XT_P2P
{
    class P2PTask;

    typedef std::map<std::string, P2PTask*> P2PTaskMap;

    /**
     *\class  P2PTaskLayout
     *\brief  该类主要是P2P任务层
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PTaskLayout : public P2PLayoutBase
    {
    public:
        /**
         *\fn         P2PTaskLayout()
         *\brief      缺省构造函数。
         */
        P2PTaskLayout();

        /**
         *\fn         ~P2PTaskLayout()
         *\brief      析构函数。
         */
        ~P2PTaskLayout();

    public:
        /**
         *\fn         int send(P2PMsg *msg)
         *\brief      发送命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int send(P2PMsg *msg);

        /**
         *\fn         int recv(P2PMsg *msg)
         *\brief      接收命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int recv(P2PMsg *msg);

    private:
        P2PTaskMap          uploadTaskMap_;     // 上传任务
        P2PTaskMap          downloadTaskMap_;   // 下载任务

        void                *commandClient_;    // 命令socket
        XT_IOCP::BuffPool   *buffPool_;         // 内存池

        XT_XML::xml         peerListXml;        // PEER列表XML

        LPCTSTR             rootPath_;          // 文件根路径

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
         *\fn         int addUploadTask(P2PMsg *msg)
         *\brief      处理添加上传任务命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int addUploadTask(P2PMsg *msg);

        /**
         *\fn         int addDownloadTask(P2PMsg *msg)
         *\brief      处理添加下载任务命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int addDownloadTask(P2PMsg *msg);

        /**
         *\fn         int recvDownloadReq(P2PMsg *msg)
         *\brief      收到Peer请求下载文件。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int recvDownloadReq(P2PMsg *msg);

        /**
         *\fn         int recvDownloadRsp(P2PMsg *msg)
         *\brief      收到Peer响应的数据。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int recvDownloadRsp(P2PMsg *msg);

        /**
         *\fn         int getTaskDataInfo(P2PMsg *msg)
         *\brief      得到任务统计的数据。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int getTaskDataInfo(P2PMsg *msg);

        /**
         *\fn         int getLayoutDataInfo(P2PMsg *msg)
         *\brief      得到本层的数据。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int getLayoutDataInfo(P2PMsg *msg);

        /**
         *\fn         int procTaskUpload(P2PMsg *msg)
         *\brief      处理任务上传。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int procTaskUpload(P2PMsg *msg);

        /**
         *\fn         int procTaskDownload(P2PMsg *msg)
         *\brief      处理任务下载。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        int procTaskDownload(P2PMsg *msg);
    };

}