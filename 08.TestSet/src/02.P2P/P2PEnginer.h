
#pragma once
#include "P2PTaskLayout.h"
#include "03.Network/IOCP/BuffPool.h"
#include "03.Network/IOCP/PackQueue.h"


namespace XT_P2P
{
    class P2PLayoutBase;

    /**
     *\class  P2PEnginer
     *\brief  该类主要是P2P引擎
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PEnginer : public P2PLayoutBase
    {
    public:
        /**
         *\fn         P2PEnginer()
         *\brief      缺省构造函数。
         */
        P2PEnginer();

        /**
         *\fn         ~P2PEnginer()
         *\brief      析构函数。
         */
        ~P2PEnginer();

    protected:
        CRITICAL_SECTION    csUsed_;	            // 临界区

        XT_IOCP::BuffPool   *buffPool_;             // 缓冲池

        XT_IOCP::PackQueue  *appQueue_;             // 应用队列

        P2PLayoutBase       *layoutList_;           // 顶层

        TCHAR               rootPath_[MAX_PATH];    // 文件根路径
        UINT                procUploadTaskTime_;    // 处理上传任务时间
        UINT                procDownloadTaskTime_;  // 处理下载任务时间
        UINT                procPeerConnection_;    // 处理客户端连通

        TCHAR               fileListMd5_[MAX_PATH]; // 文件列表md5
        UINT                fileListSize_;          // 文件列表大小

    public:
        /**
         *\fn         int recv(P2PMsg *msg)
         *\brief      接收命令。
         *\param[in]  msg           命令包。
         *\return     是否成功,0成功,其它失败。
         */
        virtual int recv(P2PMsg *msg);

        /**
         *\fn         int recvVersionInfoReq(P2PMsg *msg)
         *\brief      处理请求得到版本信息
         *\param[in]  P2PMsg * msg
         *\return     函数返回值
         */
        int recvVersionInfoReq(P2PMsg *msg);

        /**
         *\fn         int recvVersionInfoRsp(P2PMsg *msg)
         *\brief      处理应答得到版本信息
         *\param[in]  P2PMsg * msg
         *\return     函数返回值
         */
        int recvVersionInfoRsp(P2PMsg *msg);

    public:
        /**
         *\fn         int init(XT_IOCP::BuffPool *buffPool, XT_IOCP::PackQueue *appQueue, LPCTSTR rootPath)
         *\brief      初始化P2P引擎。
         *\param[in]  buffPool      缓冲池指针。
         *\param[in]  appQueue      应用队列指针。
         *\param[in]  rootPath      文件根路径。
         *\return     是否成功,0成功,其它失败。
         */
        int init(XT_IOCP::BuffPool *buffPool, XT_IOCP::PackQueue *appQueue, LPCTSTR rootPath);

        /**
         *\fn         void stop()
         *\brief      停止。
         *\param[in]  无。
         *\return     无。
         */
        void stop();

        /**
         *\fn         int addListen(LPCTSTR ip, USHORT port)
         *\brief      添加一个本地监听。
         *\param[in]  ip            IP地址。
         *\param[in]  port          端口号。
         *\return     是否成功,0成功,其它失败。
         */
        int addListen(LPCTSTR ip, USHORT port);

        /**
         *\fn         int setVersionInfo(LPCTSTR md5, UINT size)
         *\brief      设置版本信息(文件列表信息)
         *\param[in]  LPCTSTR md5   文件列表md5串
         *\param[in]  UINT size     文件列表大小
         *\return     是否成功,0成功,其它失败。
         */
        int setVersionInfo(LPCTSTR md5, UINT size);

        /**
         *\fn         getVersionInfo(UINT projectId, LPCTSTR ip, int port)
         *\brief      得到最新的文件列表信息(md5,大小)。
         *\param[in]  projectId     工程ID。
         *\param[in]  ip            服务器IP地址。
         *\param[in]  port          服务器端口号。
         *\return     是否成功,0成功,其它失败。
         */
        int getVersionInfo(UINT projectId, LPCTSTR ip, USHORT port);

        /**
         *\fn         getPeerListInfo(LPCTSTR ip, int port)
         *\brief      得到Peer列表信息(md5,大小)。
         *\param[in]  ip            服务器IP地址。
         *\param[in]  port          服务器端口号。
         *\return     是否成功,0成功,其它失败。
         */
        int getPeerListInfo(LPCTSTR ip, USHORT port);

        /**
         *\fn         int addUploadTask(LPCTSTR md5, UINT64 size, LPCTSTR filename)
         *\brief      添加一个上传任务。
         *\param[in]  md5           要上传的文件的MD5码(小写32个字符长)。
         *\param[in]  size          要上传的文件的大小(单位为字节)。
         *\param[in]  filename      将上传的文件存放的相对文件名。
         *\return     是否成功,0成功,其它失败。
         */
        int addUploadTask(LPCTSTR md5, UINT64 size, LPCTSTR filename);

        /**
         *\fn         int addDownloadTask(LPCTSTR md5, UINT64 size, LPCTSTR filename)
         *\brief      添加一个下载任务。
         *\param[in]  md5           要下载的文件的MD5码(小写32个字符长)。
         *\param[in]  size          要下载的文件的大小(单位为字节)。
         *\param[in]  fullFilename  将下载的文件存放的相对文件名。
         *\return     是否成功,0成功,其它失败。
         */
        int addDownloadTask(LPCTSTR md5, UINT64 size, LPCTSTR filename);

        /**
         *\fn         void RunBackgroundThread()
         *\brief      执行后台线程。
         *\return     无
         */
        void RunBackgroundThread();

        /**
         *\fn         static unsigned __stdcall BackgroundThread(void *param)
         *\brief      后台线程主要是初始化设置，反馈窗体。
         *\return     无
         */
        static unsigned __stdcall BackgroundThread(void *param);

        /**
         *\fn         void BackgroundThreadFun()
         *\brief      后台线程主函数。
         *\return     无
         */
        void BackgroundThreadFun();
    };

}