
#pragma once
#include "P2PProtocol.h"
#include <map>
#include <list>

namespace XT_P2P
{
    class P2PDataInfo;
    typedef std::list<P2PDataInfo*>             P2P_DATA_PTR_LIST;
    

    typedef struct _tagReqDataInfo
    {
        LPCTSTR md5_;   // 请求的文件
        UINT64  begin_; // 文件开始位置
        UINT    size_;  // 数据大小

    }REQ_DATA_INFO;
    
    typedef std::list<REQ_DATA_INFO>            P2P_REQ_DATA_LIST;
    typedef std::map<void*, P2P_REQ_DATA_LIST>  P2P_PEER_REQ_MAP;

    /**
     *\class  P2PDataInfo
     *\brief  该类主要是P2P统计信息
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PDataInfo
    {
    public:
        /**
         *\fn         P2PStatisticalInfo()
         *\brief      缺省构造函数。
         */
        P2PDataInfo();

        /**
         *\fn         ~P2PStatisticalInfo()
         *\brief      析构函数。
         */
        ~P2PDataInfo();

    protected:
        UINT recvPackSizeTemp_; // 一秒内接收到数据大小
        UINT sendPackSizeTemp_; // 一秒内发送的数据大小
        UINT lastRecvTimeTemp_; // 上秒接收到最后一个数据时间
        UINT lastSendTimeTemp_; // 上秒发送的最后一个数据时间

        UINT recvPackCount_;    // 接收到的包个数
        UINT recvPackSize_;     // 接收到的包总大小(字节)
        UINT sendPackCount_;    // 发送的包个数
        UINT sendPackSize_;     // 发送的包总大小(字节)

        UINT firstRecvTime_;    // 第一次接收数据时间
        UINT firstSendTime_;    // 第一次发送数据时间
        UINT lastRecvTime_;     // 最后一次接收数据时间
        UINT lastSendTime_;     // 最后一次发送数据时间

        float recvSpeed_;       // 发送的速度
        float sendSpeed_;       // 接收的速度

    public:
        /**
         *\fn         void addRecvPack(int size)
         *\brief      接收到一个数据包，用做统计数据
         *\param[in]  int size 接收到数据长
         *\return     无
         */
        void addRecvPack(int size);

        /**
         *\fn         void addSendPack(int size)
         *\brief      发送一个数据包，用做统计数据
         *\param[in]  int size 发送的数据长
         *\return     无
         */
        void addSendPack(int size);
        
        /**
         *\fn         float getRecvSpeed()
         *\brief      得到接收数据的速度
         *\return     接收数据的速度
         */
        float getRecvSpeed();

        /**
         *\fn         float getSendSpeed()
         *\brief      得到发送数据的速度
         *\return     发送数据的速度
         */
        float getSendSpeed();

        UINT getRecvPackCount() { return recvPackCount_; }
        UINT getRecvPackSize() { return recvPackSize_; }
        UINT getSendPackCount() { return sendPackCount_; }
        UINT getSendPackSize() { return sendPackSize_; }

        UINT getFirstRecvTime() { return firstRecvTime_; }
        UINT getFirstSendTime() { return firstSendTime_; }
        UINT getLastRecvTime() { return lastRecvTime_; }
        UINT getLastSendTime() { return lastSendTime_; }
    };

    enum
    {
        TASK_STATE_UNKNOW,          // 未知
        TASK_STATE_WAIT_DOWNLOAD,   // 等待下载
        TASK_STATE_SENDED_REQUEST,  // 已经发送了下载请求
        TASK_STATE_DOWNLOADING,     // 正在下载
        TASK_STATE_DOWNLOADED,      // 已经下载完成
        TASK_STATE_WAIT_UPLOAD,     // 等待上传
        TASK_STATE_UPLOADING,       // 正在上传
        TASK_STATE_UPLOADED,        // 已经上传完成
    };

    class P2PTaskDataInfo : public P2PDataInfo
    {
    public:
        P2PTaskDataInfo();
        ~P2PTaskDataInfo();

    protected:
        TCHAR   md5_[MAX_PATH];     // MD5
        TCHAR   filename_[MAX_PATH];// 文件名        
        UINT64  fileSize_;          // 文件大小
        UINT64  finishSize_;        // 下载大小
        UINT    state_;             // 当前状态

    public:
        void setMd5(LPCTSTR md5) { _tcscpy_s(md5_, ARRAYSIZE(md5_), md5); }
        void setFilname(LPCTSTR filename) { _tcscpy_s(filename_, ARRAYSIZE(filename_), filename); }
        void setState(UINT state) { state_ = state; }
        void setFileSize(UINT64 size) { fileSize_ = size; }
        void addFinishSize(UINT64 size) { finishSize_ += size; }

        LPCTSTR getMd5() { return md5_; }
        LPCTSTR getFilename() { return filename_; }
        UINT    getState() { return state_; }
        UINT64  getFileSize() { return fileSize_; }
        UINT64  getFinishSize() { return finishSize_; }
        
        LPCTSTR getStateStr();
    };

    enum
    {
        PEER_STATE_UNKNOW = 0,
        PEER_STATE_LAN_RECVED    = 1,   // 内网可接收数据
        PEER_STATE_LAN_SENDED    = 2,   // 内网可发送数据
        PEER_STATE_LAN_CONNECTED = 3,   // 内网已连通
        PEER_STATE_WAN_RECVED    = 4,   // 外网可接收数据
        PEER_STATE_WAN_SENDED    = 8,   // 外网可发送数据
        PEER_STATE_WAN_CONNECTED = 12,  // 外网已连通
        PEER_STATE_BREAK         = 16,  // 已经断网
    };

    class P2PPeerDataInfo : public P2PDataInfo
    {
    public:
        P2PPeerDataInfo();
        ~P2PPeerDataInfo();

    protected:
        UINT        id_;    // 客户端id
        UINT        state_; // 用户连通状态
        P2P_ADDR    addr_;  // 用户地址

    public:
        void setId(UINT id) { id_ = id; }
        UINT getId() { return id_; }

        void setState(UINT state) { state_ = state; }
        UINT getState() { return state_; }

        void setLanIp(UINT ip) { addr_.lanIp_ = ip; }
        void setWanIp(UINT ip) { addr_.wanIp_ = ip; }
        void setLanPort(USHORT port) { addr_.lanPort_ = port; }
        void setWanPort(USHORT port) { addr_.wanPort_ = port; }
        void setAddr(P2P_ADDR *addr) { addr_ = *addr; }

        UINT      getWanIp() { return addr_.wanIp_; }
        UINT      getLanIp() { return addr_.lanIp_; }
        USHORT    getWanPort() { return addr_.wanPort_; }
        USHORT    getLanPort() { return addr_.lanPort_; }
        P2P_ADDR* getAddr() { return &addr_; }
        LPCTSTR   getStateStr();
    };
}