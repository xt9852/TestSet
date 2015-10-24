
#pragma once


namespace XT_P2P
{
    #define K(n)            (n*1024)
    #define M(n)            (K(n)*1024)
    #define G(n)            (M(n)*1024)

    #define MILLISECOND(n)  (n)             // 毫秒
    #define SECOND(n)       (n*1000)        // 秒
    #define MINUTE(n)       (SECOND(n)*60)  // 分钟
    #define HOUR(n)         (MINUTE(n)*60)  // 小时
    #define DAY(n)          (HOUR(n)*24)    // 天

    // 错误号
    enum
    {
        P2P_ERR_TASK_SEND_INPUT = -1999,    // 任务层发送数据错误
        P2P_ERR_TASK_RECV_INPUT,            // 任务层接收数据错误
        P2P_ERR_TASK_OPEN_FILE,             // 任务层打开文件错误
        P2P_ERR_TASK_READ_FILE,             // 任务层读取文件错误
        P2P_ERR_TASK_DONOT_HAVE,            // 任务层任务不存在
        P2P_ERR_TASK_HAD,                   // 任务层任务已经存在

        P2P_ERR_PEER_SEND_INPUT = -2999,    // 客户端层发送数据错误
        P2P_ERR_PEER_RECV_INPUT,            // 客户端层接收数据错误
        P2P_ERR_PEER_DONT_CONNECT,          // 与此客户端未连通

        P2P_ERR_QUEUE_SEND_INPUT = -3999,   // 队列层发送数据错误
        P2P_ERR_QUEUE_RECV_INPUT,           // 队列层接收数据错误
        P2P_ERR_QUEUE_SEND_START,           // 队列层启动发送线程错误
        P2P_ERR_QUEUE_RECV_START,           // 队列层启动接收线程错误
        P2P_ERR_QUEUE_SEND_THREAD_INPUT,    // 队列层发送线程参数错误
        P2P_ERR_QUEUE_RECV_THREAD_INPUT,    // 队列层接收线程参数错误
        P2P_ERR_QUEUE_SEND_THREAD_EXCEPT,   // 队列层发送线程异常
        P2P_ERR_QUEUE_RECV_THREAD_EXCEPT,   // 队列层接收线程异常

        P2P_ERR_IOCP_SEND_INPUT = -4999,    // 完成端口层发送数据错误
        P2P_ERR_IOCP_RECV_INPUT,            // 完成端口层接收数据错误
        P2P_ERR_IOCP_INIT_INPUT,            // 完成端口层初使化参数错误
        P2P_ERR_IOCP_ADD_PEER_INPUT,        // 完成端口层添加客户端时参数错误

        P2P_ERR_MSG_DISCARDED = -5000,      // 未知的消息
    };

    // 内部协议
    enum
    {
        P2P_INIT = 5000,                    // 初使化P2P
        P2P_STOP,                           // 停止P2P
        P2P_GET_QUEUE,                      // 得到队列层队列指针
        P2P_ADD_LISTEN,                     // 添加监听端口
        P2P_LAYOUT_DATA_INFO,               // 得到各层数据

        P2P_PEER_ADD_PEER_LIST,             // 客户端添加PEER列表
        P2P_PEER_GET_CONNECTED_PEER,        // 得到已经连通的客户端
        P2P_PEER_DATA_INFO,                 // 得到客户端
        P2P_PEER_HELLO,                     // 客户端打洞，心跳

        P2P_TASK_ADD_UPLOAD,                // 添加上传任务
        P2P_TASK_ADD_DOWNLOAD,              // 添加下载任务
        P2P_TASK_PROC_UPLOAD,               // 处理上传任务
        P2P_TASK_PROC_DOWNLOAD,             // 处理下载任务

        P2P_TASK_DOWNLOAD_RET,              // 下载成功0，其它失败
        P2P_TASK_DATA_INFO,                 // 查询任务统计数据
    };

    // 外部协议
    enum
    {
        P2P_GET_VERSION_REQ = 1000,         // 请求最新的文件列表信息
        P2P_GET_VERSION_RSP,                // 应答文件列表信息

        P2P_GET_PEER_LIST_REQ,              // 请求Peer列表,得到文件MD5,文件大小
        P2P_GET_PEER_LIST_RSP,              // 应答客户列表

        P2P_HELLO_REQ,                      // 打洞请求
        P2P_HELLO_RSP,                      // 打洞应答

        P2P_GET_DATA_REQ,                   // 请求下载数据
        P2P_GET_DATA_RSP,                   // 应答下载数据
    };

    /**
     *\class  P2PMsg
     *\brief  该类主要是P2P协议命令基础类
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PMsg
    {
    public:
        UINT id_;   // 协议ID
        UINT size_; // 协议大小

        P2PMsg()
            :id_(0),
            size_(0)
        {
        }

        P2PMsg(int id)
            :id_(id),
            size_(0)
        {
        }
    };

    /**
     *\class  P2PInsideMsg
     *\brief  该类主要是P2P内部协议
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PInsideMsg : public P2PMsg
    {
    public:
        void   *param_[10];
        TCHAR  str50_[50];
        UINT64 int64_[2];

        P2PInsideMsg(int id)
        {
            id_ = id;
            size_ = 4;
            str50_[0] = _T('\0');
            memset(param_, 0, sizeof(void*)*10);
            memset(int64_, 0, sizeof(UINT64)*2);
        }

        P2PInsideMsg()
        {
            size_ = 0;
            str50_[0] = _T('\0');
            memset(param_, 0, sizeof(void*)*10);
            memset(int64_, 0, sizeof(UINT64)*2);
        }

        void setId(UINT id)
        {
            id_ = id;
        }

        // 初使化
        void setInit(int cmdType, void *buffPool, LPCTSTR rootPath)
        {
            id_ = P2P_INIT;
            size_ = 4 + sizeof(void*)*5;
            param_[2] = (void*)cmdType;
            param_[3] = buffPool;
            param_[4] = (void*)rootPath;
        }
        
        void setQueue(void *sendQueue, void *recvQueue)
        {
            param_[0] = sendQueue;
            param_[1] = recvQueue;
        }
        
        void setIocp(void *iocp) { param_[5] = (void*)iocp; }

        // 添加监听端口
        void setListen(LPCTSTR ip, USHORT port)
        {
            id_ = P2P_ADD_LISTEN;
            size_ = 4 + sizeof(void*)*2+sizeof(TCHAR)*_tcslen(ip);
            _tcscpy_s(str50_, ARRAYSIZE(str50_), ip);
            setListenPort(port);
        }

        void setListenPort(USHORT port)
        {
            param_[0] = (void*)port;
        }

        void setListenClient(void *client)
        {
            param_[1] = client;
        }

        // 添加上传任务
        void setAddUpload(LPCTSTR md5, UINT64 size, LPCTSTR filename)
        {
            id_ = P2P_TASK_ADD_UPLOAD;
            size_ = 4 + sizeof(UINT64) + sizeof(void*)*2;
            int64_[0] = size;
            param_[0] = (void*)md5;
            param_[1] = (void*)filename;
        }

        // 添加下载任务
        void setAddDownload(LPCTSTR md5, UINT64 size, LPCTSTR filename)
        {
            id_ = P2P_TASK_ADD_DOWNLOAD;
            size_ = 4 + sizeof(UINT64) + sizeof(void*)*2;
            int64_[0] = size;
            param_[0] = (void*)md5;
            param_[1] = (void*)filename;
        }

        // 接收数据
        void setRecvMsg(int id, void *pack, int size, void *client, int ip, int port)
        {
            id_ = id;
            size_ = 4 + sizeof(void*)*5;
            param_[0] = (void*)ip;
            param_[1] = (void*)port;
            param_[2] = (void*)pack;
            param_[3] = (void*)client;
            param_[4] = (void*)size;
        }

        // 任务下载的结果,由P2P引擎向应用层发送
        void setResult(int ret, LPCTSTR md5, UINT64 fileSize)
        {
            id_ = P2P_TASK_DOWNLOAD_RET;
            size_ = sizeof(void*)*2+sizeof(TCHAR)*_tcslen(md5);
            param_[0] = (void*)ret;
            param_[1] = (void*)fileSize;
            _tcscpy_s(str50_, ARRAYSIZE(str50_), md5);
        }

        // 得到统计信息
        void setGetFileInfo(int id, void *dataList)
        {
            id_ = id;
            size_ = 4 + sizeof(void*);
            param_[0] = (void*)dataList;
        }

        // 得到统计信息
        void setGetTaskInfo(int id, void *dataList)
        {
            id_ = id;
            size_ = 4 + sizeof(void*);
            param_[1] = (void*)dataList;
        }

        // 得到统计信息
        void setGetPeerInfo(int id, void *dataList)
        {
            id_ = id;
            size_ = 4 + sizeof(void*);
            param_[2] = (void*)dataList;
        }

        // 得到统计信息
        void setGetLayoutInfo(int id, void *dataList)
        {
            id_ = id;
            size_ = 4 + sizeof(void*);
            param_[3] = (void*)dataList;
        }

        // 设置请求列表
        void setReqList(void *list)
        {
            id_ = P2P_TASK_PROC_DOWNLOAD;
            size_ = 4 + sizeof(void*);
            param_[0] = list;
        }

        int     getCmdType() { return (int)param_[2]; }
        void*   getIocp() { return param_[5]; }
        void*   getBuffPool() { return param_[3]; }
        void*   getSendQueue() { return param_[0]; }
        void*   getRecvQueue() { return param_[1]; }
        LPCTSTR getRootPath() { return (LPCTSTR)param_[4]; }

        LPCTSTR getListenIp() { return str50_; }
        USHORT  getListenPort() { return (USHORT)param_[0]; }
        void*   getListenClient() { return param_[1]; }

        UINT64  getUploadSize() { return (UINT64)int64_[0]; }
        LPCTSTR getUploadMd5() { return (LPCTSTR)param_[0]; }        
        LPCTSTR getUploadFilename() { return (LPCTSTR)param_[1]; }

        UINT64  getDownloadSize() { return (UINT64)int64_[0]; }
        LPCTSTR getDownloadMd5() { return (LPCTSTR)param_[0]; }        
        LPCTSTR getDownloadFilename() { return (LPCTSTR)param_[1]; }

        UINT    getRecvIp() { return (UINT)param_[0]; }
        USHORT  getRecvPort() { return (USHORT)param_[1]; }
        void*   getRecvPack() { return param_[2]; }
        void*   getRecvClient() { return param_[3]; }
        UINT    getRecvDataLen() { return (UINT)param_[4]; }

        UINT    getResultId() { return (UINT)param_[0]; }
        UINT    getResultSize() { return (UINT)param_[1]; }
        LPCTSTR getResultMd5() { return str50_; }

        void*   getFileList() { return param_[0]; }
        void*   getTaskList() { return param_[1]; }
        void*   getPeerList() { return param_[2]; }
        void*   getLayoutList() { return param_[3]; }

        void*   getReqList() { return param_[0]; }
    };

    /**
     *\class  P2PGetVersionReq
     *\brief  该类主要是P2P外部协议,请求最新的文件列表信息
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PGetVersionReq : public P2PMsg
    {
    public:
        UINT projectId_;    // 工程ID
        LPCTSTR ip_;        // IP地址
        USHORT  port_;      // 端口

        P2PGetVersionReq(UINT projectId, LPCTSTR ip, USHORT port)
            :P2PMsg(P2P_GET_VERSION_REQ)
        {
            projectId_ = projectId;
            ip_ = ip;
            port_ = port;
        }
    };

    class P2PGetVersionRsp : public P2PMsg
    {
    public:
        TCHAR md5_[33];     // 文件列表md5串
        UINT  size_;        // 文件列表大小

        P2PGetVersionRsp(LPCTSTR md5, UINT size)
            :P2PMsg(P2P_GET_VERSION_RSP)
        {
            setData(md5, size);
        }

        void setData(LPCTSTR md5, UINT size)
        {
            id_ = P2P_GET_VERSION_RSP;
            _tcscpy_s(md5_, ARRAYSIZE(md5_), md5);
            size_ = size;
        }
    };

    /**
     *\class  P2PGetPeerListReq
     *\brief  该类主要是P2P外部协议,请求客户端列表
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PGetPeerListReq : public P2PMsg
    {
    public:
        LPCTSTR ip_;       // IP地址
        USHORT  port_;     // 端口

        P2PGetPeerListReq(LPCTSTR ip, USHORT port)
            :P2PMsg(P2P_GET_PEER_LIST_REQ)
        {
            ip_ = ip;
            port_ = port;
        }
    };

    typedef struct _tagP2PAddr
    {
        UINT    wanIp_;     // 公网IP
        USHORT  wanPort_;   // 公网端口
        UINT    lanIp_;     // 内网IP
        USHORT  lanPort_;   // 内网端口

        _tagP2PAddr()
            :wanIp_(0),
            wanPort_(0),
            lanIp_(0),
            lanPort_(0)
        {
        }

    }P2P_ADDR, *PP2P_ADDR;

    /**
     *\class  P2PGetPeerListRsp
     *\brief  该类主要是P2P外部协议,应答客户端列表
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PGetPeerListRsp : public P2PMsg
    {
    public:
        UINT    myWanIp_;         // 用户外网IP
        USHORT  myWanPort_;       // 用户外网端口
        BYTE    peerCount_;       // 用户数量

        P2PGetPeerListRsp()
            :P2PMsg(P2P_GET_PEER_LIST_RSP),
            myWanIp_(0),
            myWanPort_(0),
            peerCount_(0)
        {
        }

        void setData(UINT wanIp, USHORT wanPort, BYTE peerCount)
        {
            myWanIp_ = wanIp;
            myWanPort_ = wanPort;
            peerCount_ = peerCount;
        }
    };

    /**
     *\struct  _tagGetDataInfo
     *\brief  该类主要是P2P外部协议,得到数据请求,请求的位置和请求的数据长
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    typedef struct _tagGetDataInfo
    {
        UINT64 begin_;  // 文件开始位置
        UINT   size_;   // 数据大小

    }GET_DATA_INFO;

    /**
     *\class  P2PGetDataRsp
     *\brief  该类主要是P2P外部协议,得到数据请求
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PGetDataReq : public P2PMsg
    {
    public:
        char            md5_[33];       // 文件MD5
        BYTE            questCount_;    // 请求数量
        USHORT          speed_;         // 当前接收的速度(K/S)
        GET_DATA_INFO   position_;      // 请求的位置和数量(有questCount_个)

        P2PGetDataReq(LPCTSTR md5, UINT64 begin, UINT size, USHORT speed)
            :P2PMsg(P2P_GET_DATA_REQ)
        {
            setData(md5, begin, size, speed);
        }

        void setData(LPCTSTR md5, UINT64 begin, UINT size, USHORT speed)
        {
            id_ = P2P_GET_DATA_REQ;
          
            USES_CONVERSION;
            strcpy_s(md5_, ARRAYSIZE(md5_), T2A((LPTSTR)md5));

            speed_ = speed;
            questCount_ = 1;
            position_.begin_ = begin;
            position_.size_  = size;
        }

        void addReq(UINT64 begin, UINT size)
        {
            GET_DATA_INFO *req = &position_;

            for (int i = 0; i < questCount_; i++, req++);

            questCount_++;
            req->begin_ = begin;
            req->size_ = size;
        }
    };

    /**
     *\class  P2PGetDataRsp
     *\brief  该类主要是P2P外部协议,得到数据应答
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PGetDataRsp : public P2PMsg
    {
    public:
        char   md5_[33];   // 文件MD5
        UINT   packCount_; // 返回的一组数据包个数
        UINT   packId_;    // 当前包在这组中的位置
        UINT64 begin_;     // 文件开始位置
        UINT   size_;      // 数据大小
        void   *pack_;     // 数据包
        UINT   ip_;        // ip地址
        USHORT port_;      // 端口地址

        P2PGetDataRsp(LPCTSTR md5, UINT64 begin, UINT size, 
            UINT packId, UINT packCount, void *pack, UINT ip, USHORT port)
            :P2PMsg(P2P_GET_DATA_RSP)
        {
            setData(md5, begin, size, packId, packCount, pack, ip, port);
        }

        void setData(LPCTSTR md5, UINT64 begin, UINT size, 
            UINT packId, UINT packCount, void *pack, UINT ip, USHORT port)
        {
            id_ = P2P_GET_DATA_RSP;
            begin_ = begin;
            size_ = size;
            pack_ = pack;
            packId_ = packId;
            packCount_ = packCount;
            ip_ = ip;
            port_ = port;

            USES_CONVERSION;
            strcpy_s(md5_, ARRAYSIZE(md5_), T2A((LPTSTR)md5));
        }
    };
}