
#pragma once
#include "P2PDataInfo.h"
#include "Base/MD5.h"
#include <list>
#include <bitset>

namespace XT_P2P
{

#define SECTION_SIZE    M(1)

    typedef std::list<UINT>     P2P_UINT_LIST;
    typedef std::bitset<1024>   P2P_RECV_PACK;

    typedef struct _tagSection
    {
        UINT64          sectionBegin_;      // 当前区段开始
        UINT            sectionSize_;       // 当前区段大小
        USHORT          packCount_;         // 需要接收的包个数(sectionSize_ / K(1))上取整
        USHORT          recvPackCount_;     // 已经接收到的包个数
        P2P_RECV_PACK   recvPackBit_;       // 已经接收到的包

        UINT            lastSendTime_;      // 最后一次发送请求的时间
        UINT            lastRecvTime_;      // 最后一次接收数据的时间

        _tagSection()
            :sectionBegin_(0),
            sectionSize_(0),
            packCount_(0),
            recvPackCount_(0),
            lastSendTime_(0),
            lastRecvTime_(0)
        {
        }

    }TASK_SECTION, *PTASK_SECTION;

    typedef std::list<TASK_SECTION> P2P_SECTION_LIST;

    /**
     *\class  P2PTask
     *\brief  该类主要是P2P的任务
     *\date   2012-12-26
     *\author 张海涛
     *\par    Revision History:
     */
    class P2PTask
    {
    public:
        P2PTask();
        ~P2PTask();

    private:
        UINT                sectionCount_;          // 区段个数
        P2P_UINT_LIST       unreqSectionList_;      // 还没有请求数据的区段
        P2P_UINT_LIST       unrecvSectionList_;     // 还没有接收完数据的区段
        P2P_SECTION_LIST    sectionInfo_;           // 区段信息

        HANDLE              file_;                  // 文件句柄
        HANDLE              fileMap_;               // 文件映射对象
        UINT64              fileSeek_;              // 文件的当前位置
        UINT                buffSize_;              // 缓冲区大小
        BYTE                *buff_;                 // 缓冲区

        P2PTaskDataInfo     dataInfo_;              // 统计数据
        CMD5                md5_;                   // MD5

    protected:
        /**
         *\fn         int OpenFile(bool read, UINT64 begin);
         *\brief      打开文件。
         *\param[in]  read          打开文件。
         *\param[in]  begin         映射开始位置。
         *\return     是否成功,0成功,其它失败。
         */
        int OpenFile(bool read, UINT64 begin);

        /**
         *\fn         int MoveView(bool read, UINT64 begin);
         *\brief      移动映射位置。
         *\param[in]  read          打开文件。
         *\param[in]  begin         映射开始位置。
         *\return     是否成功,0成功,其它失败。
         */
        int MoveView(bool read, UINT64 begin);

    public:
        LPCTSTR getMd5() { return dataInfo_.getMd5(); }
        UINT64  getFileSize() { return dataInfo_.getFileSize(); }

        UINT getState() { return dataInfo_.getState(); }
        void setState(UINT state) { dataInfo_.setState(state); }
        P2PTaskDataInfo* getDataInfo() { return &dataInfo_; }

        void addRecvPack(int size) { dataInfo_.addRecvPack(size); }
        void addSendPack(int size) { dataInfo_.addSendPack(size); }

        /**
         *\fn         void Free()
         *\brief      释放数据。
         *\param[in]  无。
         *\return     无。
         */
        void Free();

        /**
         *\fn         setUpload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename)
         *\brief      设置上传。
         *\param[in]  md5           文件Md5。
         *\param[in]  fileSize      文件大小。
         *\param[in]  filename      文件全路径名。
         *\return     是否成功,0成功,其它失败。
         */
        int setUpload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename);

        /**
         *\fn         setDownload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename)
         *\brief      设置下载。
         *\param[in]  md5           文件Md5。
         *\param[in]  fileSize      文件大小。
         *\param[in]  filename      文件全路径名。
         *\return     是否成功,0成功,其它失败。
         */
        int setDownload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename);

        /**
         *\fn         int GetData(UINT64 begin, UINT size, void *buff)
         *\brief      保存数据。
         *\param[in]  begin         开始位置。
         *\param[in]  size          数据大小。
         *\param[in]  buff          数据。
         *\return     是否成功,0成功,其它失败。
         */
        int GetData(UINT64 begin, UINT size, void *buff);

        /**
         *\fn         int SaveData(UINT64 begin, UINT size, void *buff)
         *\brief      保存数据。
         *\param[in]  begin         开始位置。
         *\param[in]  size          数据大小。
         *\param[in]  buff          数据。
         *\return     是否成功,0成功,其它失败。
         */
        int SaveData(UINT64 begin, UINT size, void *buff);

        /**
         *\fn         int procUpload()
         *\brief      处理上传任务,5分钟没有接收请求则关闭文件，释放内存
         *\return     无
         */
        int procUpload();

        /**
         *\fn         int procDownload(P2P_PEER_REQ_MAP *peerReqMap)
         *\brief      处理下载任务
         *\param[in]  peerIdReqMap 客户端ID到请求列表
         *\return     无
         */
        int procDownload(P2P_PEER_REQ_MAP *peerReqMap);
    };
}