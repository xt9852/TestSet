
#include "StdAfx.h"
#include "P2PTaskLayout.h"
#include "P2PProtocol.h"
#include "P2PDataInfo.h"
#include "03.Network/IOCP/BuffPool.h"
#include "03.Network/IOCP/PrePack.h"

#ifdef _DEBUG
#include "03.Network/IOCP/ClientPool.h"
#endif // _DEBUG


namespace XT_P2P
{

	/**
	 *\fn         P2PTaskLayout()
	 *\brief      缺省构造函数。
	 */
    P2PTaskLayout::P2PTaskLayout()
        :buffPool_(NULL),
        rootPath_(NULL)
    {
    }

	/**
	 *\fn         ~P2PTaskLayout()
	 *\brief      析构函数。
	 */
	P2PTaskLayout::~P2PTaskLayout()
	{
        Stop();
	}

    /**
     *\fn         int send(P2PMsg *msg)
     *\brief      发送命令。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::send(P2PMsg *msg)
    {
        if (NULL == next_ || NULL == msg) return P2P_ERR_TASK_SEND_INPUT;

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
        case P2P_TASK_ADD_UPLOAD:
            {
                return addUploadTask(msg);
            }
        case P2P_TASK_ADD_DOWNLOAD:
            {
                return addDownloadTask(msg);
            }
        case P2P_TASK_DATA_INFO:
            {
                return getTaskDataInfo(msg);
            }
        case P2P_LAYOUT_DATA_INFO:
            {
                return getLayoutDataInfo(msg);
            }
        case P2P_TASK_PROC_UPLOAD:
            {
                return procTaskUpload(msg);
            }
        case P2P_TASK_PROC_DOWNLOAD:
            {
                return procTaskDownload(msg);
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
    int P2PTaskLayout::recv(P2PMsg *msg)
    {
        if (NULL == msg) return P2P_ERR_TASK_RECV_INPUT;

        P2PInsideMsg *recvMsg = (P2PInsideMsg*)msg;

        addRecvPack(recvMsg->getRecvDataLen());

        switch (msg->id_)
        {
        case P2P_GET_DATA_REQ:
            {
                return recvDownloadReq(msg);
            }
        case P2P_GET_DATA_RSP:
            {
                return recvDownloadRsp(msg);
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
    int P2PTaskLayout::Init(P2PMsg *msg)
    {
        if (NULL == msg) return P2P_ERR_PEER_SEND_INPUT;

        P2PInsideMsg *init = (P2PInsideMsg*)msg;
        rootPath_ = init->getRootPath();        
        buffPool_ = (XT_IOCP::BuffPool*)init->getBuffPool();

        return next_->send(msg);
    }

    /**
     *\fn         int Stop()
     *\brief      初始化。
     *\param[in]  无。
     *\return     无。
     */
    void P2PTaskLayout::Stop()
    {
        P2PTaskMap::iterator iter = uploadTaskMap_.begin();

        for (; iter != uploadTaskMap_.end(); ++iter)
        {
            P2PTask *task = iter->second;
            task->Free();
            delete task;
        }

        uploadTaskMap_.clear();

        iter = downloadTaskMap_.begin();

        for (; iter != downloadTaskMap_.end(); ++iter)
        {
            P2PTask *task = iter->second;
            task->Free();
            delete task;
        }

        downloadTaskMap_.clear();
    }

    /**
     *\fn         int addUploadTask(P2PMsg *msg)
     *\brief      处理添加上传任务命令。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::addUploadTask(P2PMsg *msg)
    {
        P2PInsideMsg *uploadTask = (P2PInsideMsg*)msg;

        UINT64 size = uploadTask->getUploadSize();
        LPCTSTR md5 = uploadTask->getUploadMd5();
        LPCTSTR filename = uploadTask->getUploadFilename();

        P2PTaskMap::iterator iter = uploadTaskMap_.find(md5);

        if (iter != uploadTaskMap_.end()) return P2P_ERR_TASK_HAD;

        P2PTask *task = new P2PTask;
        int ret = task->setUpload(md5, size, filename);

        if (0 != ret)
        {
            task->Free();
            delete task;
            return ret;
        }

        uploadTaskMap_[md5] = task;
        TRACE("P2PTaskLayout::addUploadTask md5:%s size:%I64u name:%s\n", md5, size, filename);
        return 0;
    }

    /**
     *\fn         int addDownloadTask(P2PMsg *msg)
     *\brief      处理添加下载任务命令。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::addDownloadTask(P2PMsg *msg)
    {
        P2PInsideMsg *downloadTask = (P2PInsideMsg*)msg;

        UINT64 size = downloadTask->getDownloadSize();
        LPCTSTR md5 = downloadTask->getDownloadMd5();
        LPCTSTR filename = downloadTask->getDownloadFilename();

        P2PTaskMap::iterator iter = downloadTaskMap_.find(md5);

        if (iter != downloadTaskMap_.end()) return P2P_ERR_TASK_HAD;

        TCHAR filePath[MAX_PATH] = _T("");
        _stprintf_s(filePath, ARRAYSIZE(filePath), _T("%s\\%s"), rootPath_, filename);

        P2PTask *task = new P2PTask;
        int ret = task->setDownload(md5, size, filePath);

        if (0 != ret)
        {
            task->Free();
            delete task;
            return ret;
        }

        downloadTaskMap_[md5] = task;
        TRACE("P2PTaskLayout::addDownloadTask md5:%s size:%I64u name:%s\n", md5, size, filename);
        return 0;
    }

    /**
     *\fn         int recvDownloadReq(P2PMsg *msg)
     *\brief      收到Peer请求下载文件。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::recvDownloadReq(P2PMsg *msg)
    {
        P2PInsideMsg *downloadReq = (P2PInsideMsg*)msg;

        // 接收到的数据
        UINT ip = downloadReq->getRecvIp();
        USHORT port = downloadReq->getRecvPort();
        UINT dataLen = downloadReq->getRecvDataLen();
        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)downloadReq->getRecvPack();

        if (NULL == pack) return P2P_ERR_TASK_DONOT_HAVE;

        // 请求的数据结构
        P2PGetDataReq *req = (P2PGetDataReq*)pack->getData();
        GET_DATA_INFO *reqInfo = &(req->position_);

#ifdef _DEBUG

        XT_IOCP::CLIENT *client = (XT_IOCP::CLIENT*)downloadReq->getRecvClient();

        struct sockaddr_in localAddr;
        int addrLen = sizeof(localAddr);
        getsockname(client->sock, (struct sockaddr *)&localAddr, &addrLen);

        TRACE("P2PTaskLayout::recvDownloadReq<-%s:%d<-%s:%d md5:%s count:%d\n", 
            inet_ntoa(localAddr.sin_addr), ntohs(localAddr.sin_port),
            inet_ntoa(*(in_addr*)&ip), ntohs(port), 
            req->md5_, req->questCount_);

        for (int i = 0; i < req->questCount_; i++)
        {
            TRACE("-->begin:%I64d size:%d\n", reqInfo[i].begin_, reqInfo[i].size_);
        }
#endif // _DEBUG

        P2PTaskMap::iterator iter = uploadTaskMap_.find(req->md5_);

        if (iter == uploadTaskMap_.end()) // 没有此任务
        {
            buffPool_->Free(pack);
            return P2P_ERR_TASK_DONOT_HAVE;
        }

        // 任务接收统计
        P2PTask *task = iter->second;
        task->addRecvPack(dataLen);

        USHORT count = req->speed_ + req->speed_ * 0.2;

        // 发送应答数据
        for (int i = 0; i < req->questCount_; i++, reqInfo++)
        {
            UINT packCount = reqInfo->size_ / K(1);
            UINT remain = reqInfo->size_ % K(1);

            if (0 != remain)
            {
                packCount++;
            }
            else
            {
                remain = K(1);
            }

            for (UINT j = 0; j < packCount && count > 0; i++, count--)
            {
                XT_IOCP::PACK *pack = (XT_IOCP::PACK*)buffPool_->Get(1);

                UINT dataSize = (j != packCount-1) ? K(1) : remain;
                UINT headSize = sizeof(P2PGetDataRsp);
                UINT64 pos = reqInfo->begin_ + (j * K(1));

                // 数据头
                P2PGetDataRsp rspData(req->md5_, pos, dataSize, j, packCount, pack, ip, port);

                // 数据包
                BYTE *buff = pack->getData();
                pack->clear(P2P_GET_DATA_RSP);
                pack->setData(0, &rspData, headSize);
                pack->dataLen += task->GetData(pos, dataSize, &buff[headSize]);

//                 TRACE("P2PTaskLayout::sendDownloadRsp->%s:%d md5:%s begin:%I64d size:%d packId:%d packCount:%d\n", 
//                     inet_ntoa(*(in_addr*)&ip), ntohs(port),
//                     rspData.md5_, rspData.begin_, rspData.size_, rspData.packId_, rspData.packCount_);

                // 任务发送统计
                task->addSendPack(pack->getPackLen());
                next_->send((P2PMsg*)pack->getData());
            }
        }

        buffPool_->Free(pack);
        return 0;
    }

    /**
     *\fn         int recvDownloadRsp(P2PMsg *msg)
     *\brief      收到Peer响应的数据。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::recvDownloadRsp(P2PMsg *msg)
    {
        P2PInsideMsg *downloadRsp = (P2PInsideMsg*)msg;

        // 接收到的数据
        UINT ip = downloadRsp->getRecvIp();
        USHORT port = downloadRsp->getRecvPort();
        UINT dataLen = downloadRsp->getRecvDataLen();
        XT_IOCP::PACK *pack = (XT_IOCP::PACK*)downloadRsp->getRecvPack();

        if (NULL == pack) P2P_ERR_TASK_DONOT_HAVE;

        // 应答的数据结构
        P2PGetDataRsp *rsp = (P2PGetDataRsp*)pack->getData();

// #ifdef _DEBUG
// 
//         XT_IOCP::CLIENT *client = (XT_IOCP::CLIENT*)downloadRsp->getRecvClient();
// 
//         struct sockaddr_in localAddr;
//         int addrLen = sizeof(localAddr);
//         getsockname(client->sock, (struct sockaddr *)&localAddr, &addrLen);
// 
//         TRACE("P2PTaskLayout::recvDownloadRsp<-%s:%d<-%s:%d md5:%s begin:%I64d size:%d packId:%d packCount:%d\n", 
//             inet_ntoa(localAddr.sin_addr), ntohs(localAddr.sin_port),
//             inet_ntoa(*(in_addr*)&ip), ntohs(port), 
//             rsp->md5_, rsp->begin_, rsp->size_, rsp->packId_, rsp->packCount_);
// 
// #endif // _DEBUG

        P2PTaskMap::iterator iter = downloadTaskMap_.find(rsp->md5_);

        if (iter == downloadTaskMap_.end()) return P2P_ERR_TASK_DONOT_HAVE;

        P2PTask *task = iter->second;
        task->addRecvPack(dataLen); // 任务接收统计

        // 返回0表示全部接收完成
        if (0 == task->SaveData(rsp->begin_, rsp->size_, (void*)&rsp[1]))
        {
            // 向上层通知下载完成
            P2PInsideMsg *downloadRet = (P2PInsideMsg*)buffPool_->Get(1);
            downloadRet->setResult(0, task->getMd5(), task->getFileSize());
            pre_->recv(downloadRet);
        }

        buffPool_->Free(pack);
        return 0;
    }

    /**
     *\fn         int getTaskDataInfo(P2PMsg *msg)
     *\brief      得到任务统计的数据。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::getTaskDataInfo(P2PMsg *msg)
    {
        P2PInsideMsg *dataInfo = (P2PInsideMsg*)msg;

        P2P_DATA_PTR_LIST *dataList = (P2P_DATA_PTR_LIST*)dataInfo->getTaskList();

        P2PTaskMap::const_iterator iter = downloadTaskMap_.begin();

        for (; iter != downloadTaskMap_.end(); ++iter)
        {
            P2PTask *task = iter->second;

            dataList->push_back(task->getDataInfo());
        }

        return 0;
    }

    /**
     *\fn         int getLayoutDataInfo(P2PMsg *msg)
     *\brief      得到本层的数据。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::getLayoutDataInfo(P2PMsg *msg)
    {
        P2PInsideMsg *dataInfo = (P2PInsideMsg*)msg;

        P2P_DATA_PTR_LIST *dataList = (P2P_DATA_PTR_LIST*)dataInfo->getLayoutList();

        dataList->push_front(getDataInfo());

        return next_->send(msg);
    }

    /**
     *\fn         int procTaskUpload(P2PMsg *msg)
     *\brief      处理任务上传。
     *\n          1分名检查一次，如果5分钟没有接接收请求下载数据，则关闭文件释放内存,
     *\n          状态置为等待上传
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::procTaskUpload(P2PMsg *msg)
    {
        P2PTaskMap::iterator iter = uploadTaskMap_.begin();

        for(; iter != uploadTaskMap_.end(); ++iter)
        {
            iter->second->procUpload();
        }

        return 0;
    }

    /**
     *\fn         int procTaskDownload(P2PMsg *msg)
     *\brief      处理任务下载。
     *\param[in]  msg           命令包。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTaskLayout::procTaskDownload(P2PMsg *msg)
    {
        if (downloadTaskMap_.size() <= 0) return -1;

        P2PInsideMsg *reqDownload = (P2PInsideMsg*)msg;

        P2P_PEER_REQ_MAP peerReqMap;

        P2PInsideMsg getPeer;

        getPeer.setGetPeerInfo(P2P_PEER_GET_CONNECTED_PEER, &peerReqMap);

        int ret = next_->send(&getPeer);

        if (peerReqMap.size() == 0)
        {
            getPeer.getPeerList();

            return next_->send(&getPeer);
        }

        P2PTaskMap::iterator iter = downloadTaskMap_.begin();

        for(; iter != downloadTaskMap_.end(); ++iter)
        {
            iter->second->procDownload(&peerReqMap);
        }

        reqDownload->setReqList((void*)&peerReqMap);
        reqDownload->setId(P2P_GET_DATA_REQ);
        return next_->send(reqDownload);
    }
}

