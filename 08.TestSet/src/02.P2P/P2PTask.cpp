
#include "StdAfx.h"
#include "P2PTask.h"
#include "P2PProtocol.h"
#include "P2PFileOperator.h"

namespace XT_P2P
{
    P2PTask::P2PTask()
        :sectionCount_(0),
        file_(NULL),
        fileMap_(NULL),
        fileSeek_(0),
        buffSize_(0),
        buff_(NULL)
    {
    }

    P2PTask::~P2PTask()
    {
        Free();
    }

    /**
     *\fn         int OpenFile(bool read, UINT64 begin);
     *\brief      打开文件。
     *\param[in]  read          打开文件。
     *\param[in]  begin         映射开始位置。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTask::OpenFile(bool read, UINT64 begin)
    {
        DWORD openAttrib  = read ? OPEN_EXISTING : OPEN_ALWAYS;
        DWORD acceAttrib  = read ? GENERIC_READ  : (GENERIC_READ|GENERIC_WRITE);
        DWORD pageProtect = read ? PAGE_READONLY : PAGE_READWRITE;

begin_create:

        // 创建文件对象
        file_ = CreateFile(dataInfo_.getFilename(), acceAttrib, FILE_SHARE_READ, NULL, openAttrib, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == file_)
        {
            if (GetLastError() == ERROR_PATH_NOT_FOUND) // 系统找不到指定的路径
            {
                P2PFileOperator fileOper;
                fileOper.MakeDirectory(dataInfo_.getFilename());
                goto begin_create;
            }

            TRACE("创建文件对象失败,错误代码:%d\r\n", GetLastError());
            return -2;
        }

        UINT64 fileSize = dataInfo_.getFileSize();
        long highOffset = (fileSize >> 32);
        long lowOffset  = (fileSize & 0xFFFFFFFF);

        if (!read)
        {
            int ret = SetFilePointer(file_, lowOffset, &highOffset, FILE_BEGIN); // 设置文件大小
            if (HFILE_ERROR == ret)
            {
                return -3;
            }
        }

        // 创建文件映射对象
        fileMap_ = CreateFileMapping(file_, NULL, pageProtect, highOffset, lowOffset, NULL);

        if (NULL == fileMap_)
        {
            TRACE("创建文件映射对象失败,错误代码:%d\r\n", GetLastError());
            return -4;
        }

        // 映射视图
        return MoveView(read, begin);
    }

    /**
     *\fn         int MoveView(bool read, UINT64 begin);
     *\brief      移动映射位置。
     *\param[in]  read          打开文件。
     *\param[in]  begin         映射开始位置。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTask::MoveView(bool read, UINT64 begin)
    {
        DWORD viewAccess  = read ? FILE_MAP_READ : FILE_MAP_WRITE;

        fileSeek_ = begin / M(1) * M(1); // 1M对齐

        UINT64 fileSize = dataInfo_.getFileSize();
        buffSize_ = ((fileSize - fileSeek_) > M(1)) ? M(1) : (fileSize - fileSeek_); // 按系统分配粒度(xp-64k)对齐

        // 映射视图
        buff_ = (LPBYTE)MapViewOfFile(fileMap_, viewAccess, (fileSeek_ >> 32), (fileSeek_ & 0xFFFFFFFF), buffSize_);

        if (NULL == buff_)
        {
            TRACE("映射文件映射失败,错误代码:%d\r\n", GetLastError());
            return -5;
        }

        return 0;
    }

    /**
     *\fn         void Free()
     *\brief      释放数据。
     *\param[in]  无。
     *\return     无。
     */
    void P2PTask::Free()
    {
        if (NULL != fileMap_)
        {
            UnmapViewOfFile(fileMap_); // 撤消文件映像
            CloseHandle(fileMap_);
            fileMap_ = NULL;
        }

        if (NULL != file_)
        {
            CloseHandle(file_); // 关闭文件
            file_ = NULL;
        }

        sectionInfo_.clear();
        unreqSectionList_.clear();
        unrecvSectionList_.clear();

        buff_ = NULL;
        fileSeek_ = 0;
    }

    /**
     *\fn         setUpload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename)
     *\brief      设置上传。
     *\param[in]  md5           文件Md5。
     *\param[in]  fileSize      文件大小。
     *\param[in]  filename      文件全路径名。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTask::setUpload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename)
    {
        if (NULL == md5 || NULL == filename || NULL != file_) return -1;

        dataInfo_.setMd5(md5);
        dataInfo_.setFilname(filename);
        dataInfo_.setFileSize(fileSize);
        dataInfo_.setState(TASK_STATE_WAIT_UPLOAD);

        return 0;
    }

    /**
     *\fn         int GetData(UINT64 begin, UINT size, void *buff)
     *\brief      保存数据。
     *\param[in]  begin         开始位置。
     *\param[in]  size          数据大小。
     *\param[in]  buff          数据。
     *\return     小于0失败,其它读取的数据长。
     */
    int P2PTask::GetData(UINT64 begin, UINT size, void *buff)
    {
        if (NULL == buff || begin >= dataInfo_.getFileSize()) return -1;

        if (NULL == file_)
        {
            OpenFile(true, begin);
            dataInfo_.setState(TASK_STATE_UPLOADING);
        }
        else if (begin < fileSeek_ || begin >= (fileSeek_ + buffSize_)) // 不在映射中
        {
            MoveView(true, begin);
        }

        if (NULL == buff_) return -2;

        UINT64 pos = begin - fileSeek_;
        
        if ((begin + size) >= dataInfo_.getFileSize()) size = dataInfo_.getFileSize() - begin;

        memcpy(buff, &buff_[pos], size);

        return size;
    }

    /**
     *\fn         setDownload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename)
     *\brief      设置下载。
     *\param[in]  md5           文件Md5。
     *\param[in]  fileSize      文件大小。
     *\param[in]  filename      文件全路径名。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTask::setDownload(LPCTSTR md5, UINT64 fileSize, LPCTSTR filename)
    {
        if (NULL == md5 || NULL == filename || NULL != file_) return -1;

        sectionCount_ = fileSize / SECTION_SIZE;
        sectionCount_ += (fileSize % SECTION_SIZE) ? 1 : 0;

        unreqSectionList_.clear();
        unrecvSectionList_.clear();

        for (UINT i = 0; i < sectionCount_; i++)
        {
            unreqSectionList_.push_back(i);
            unrecvSectionList_.push_back(i);
        }

        dataInfo_.setMd5(md5);
        dataInfo_.setFilname(filename);
        dataInfo_.setFileSize(fileSize);
        dataInfo_.setState(TASK_STATE_WAIT_DOWNLOAD);

        return 0;
    }

    /**
     *\fn         int SaveData(UINT64 begin, UINT size, void *buff)
     *\brief      保存数据。
     *\param[in]  begin         开始位置。
     *\param[in]  size          数据大小。
     *\param[in]  fileSize      文件总大小。
     *\param[in]  buff          数据。
     *\return     是否成功,0成功,其它失败。
     */
    int P2PTask::SaveData(UINT64 begin, UINT size, void *buff)
    {
        if (NULL == buff || begin >= dataInfo_.getFileSize() || 0 == size) return -1;

        if (NULL == file_)
        {
            OpenFile(false, begin);
            dataInfo_.setState(TASK_STATE_DOWNLOADING);
        }
        else if (begin < fileSeek_ || begin >= (fileSeek_ + buffSize_)) // 不在映射中
        {
            MoveView(false, begin);
        }

        if (NULL == buff_) return -2;

        int sectionBegin = begin / SECTION_SIZE * SECTION_SIZE;

        P2P_SECTION_LIST::iterator iter = sectionInfo_.begin();

        for (; iter != sectionInfo_.end(); ++iter)
        {
            TASK_SECTION &section = *iter;

            if (section.sectionBegin_ == sectionBegin)
            {
                UINT index = (begin - sectionBegin) / K(1);

                if (!section.recvPackBit_[index])
                {
                    dataInfo_.addFinishSize(1024);
                    section.recvPackCount_++;
                    section.recvPackBit_.set(index);
                    memcpy((void*)&buff_[begin - fileSeek_], buff, size);

                    if (section.recvPackCount_ == section.packCount_)
                    {
                        // 删除未接收到的区段,并添加新的区段
                        bool delSection = false;
                        bool newSection = false;
                        UINT finishId = section.sectionBegin_ / SECTION_SIZE;
                        P2P_UINT_LIST::iterator delItem;
                        P2P_UINT_LIST::iterator unrecvItem = unrecvSectionList_.begin();

                        for (; unrecvItem != unrecvSectionList_.end(); ++unrecvItem)
                        {
                            UINT unrecvId = *unrecvItem;

                            if (finishId == unrecvId)
                            {
                                delItem = unrecvItem;
                                delSection = true;
                            }
                            else if (!newSection)
                            {
                                if (unrecvId == (sectionCount_ - 1)) // 最后一块
                                {
                                    int a = section.recvPackBit_.count();
                                    section.sectionBegin_ = unrecvId * SECTION_SIZE;
                                    section.sectionSize_ = getFileSize() - section.sectionBegin_;
                                    section.packCount_ = (section.sectionSize_ / K(1)) + ((section.sectionSize_ % K(1))?1:0);
                                    section.recvPackBit_.reset();
                                    section.recvPackCount_ = 0;
                                    newSection = true;
                                }
                                else
                                {
                                    section.sectionBegin_ = unrecvId * SECTION_SIZE;
                                    section.sectionSize_ = SECTION_SIZE;
                                    section.packCount_ = SECTION_SIZE / K(1);
                                    section.recvPackBit_.reset();
                                    section.recvPackCount_ = 0;
                                    newSection = true;
                                }

                                break;
                            }

                            if (delSection && newSection) break;
                        }

                        if (delSection) unrecvSectionList_.erase(delItem);
                    }
                }
            }
        }

        if (unrecvSectionList_.size() != 0) return size;

        // 已经接收完
        Free();
        dataInfo_.setState(TASK_STATE_DOWNLOADED);
        return 0;
    }

    /**
     *\fn         int procUpload()
     *\brief      处理上传达室任务,5分钟没有接收请求则关闭文件，释放内存
     *\return     无
     */
    int P2PTask::procUpload()
    {
        if (((GetTickCount() - dataInfo_.getLastRecvTime()) > MINUTE(5)) && // 5分钟
            (dataInfo_.getState() == TASK_STATE_UPLOADING))
        {
            Free(); // 关闭文件，释放内存
            dataInfo_.setState(TASK_STATE_WAIT_UPLOAD);
        }

        return 0;
    }

    /**
     *\fn         int procDownload(P2P_PEER_REQ_MAP *peerReqMap)
     *\brief      处理下载任务
     *\param[in]  peerIdReqMap 客户端ID到请求列表
     *\return     无
     */
    int P2PTask::procDownload(P2P_PEER_REQ_MAP *peerReqMap)
    {
        if ((GetTickCount() - dataInfo_.getLastRecvTime()) < SECOND(5) || 
            getState() == TASK_STATE_DOWNLOADED) return -1;

        int sectionCount = sectionInfo_.size();
        int peerCount = peerReqMap->size();

        if (peerCount > sectionCount)
        {
            for (int i = 0; i < (peerCount - sectionCount); i++)
            {
                P2P_UINT_LIST::iterator iter = unreqSectionList_.begin();

                if (iter == unreqSectionList_.end()) break;

                UINT id = *iter;

                TASK_SECTION section;
                section.sectionBegin_ = id * SECTION_SIZE;
                section.sectionSize_ = (id == (sectionCount_-1))?(getFileSize()-id*SECTION_SIZE):SECTION_SIZE;
                section.packCount_ = ceil((float)section.sectionSize_ / K(1));

                sectionInfo_.push_back(section);

                unreqSectionList_.erase(iter);
            }
        }

        P2P_SECTION_LIST::iterator sectionIter = sectionInfo_.begin();
        P2P_PEER_REQ_MAP::iterator peeriter = peerReqMap->begin();

        for (; sectionIter != sectionInfo_.end() && peeriter != peerReqMap->end(); ++sectionIter, ++peeriter)
        {
            TASK_SECTION &section = *sectionIter;
            P2P_REQ_DATA_LIST &reqList = peeriter->second;

            UINT64 size = 0;
            REQ_DATA_INFO req;
            req.md5_ = getMd5();
            
            for (int i = 0; i < section.packCount_; i++)
            {
                if (!section.recvPackBit_[i])
                {
                    if (0 == size)
                    {
                        size = K(1);
                        req.begin_ = section.sectionBegin_ + i * K(1);
                    }
                    else
                    {
                        size += (i == (section.packCount_-1))?(section.sectionSize_-i*K(1)):K(1);
                    }
                }
                else if (0 != size)
                {
                    req.size_ = size;
                    reqList.push_back(req);
                    size = 0;

                    TRACE(_T("req begin:%I64u, size:%u\n"), req.begin_, req.size_);
                }
            }

            if (0 != size)
            {
                req.size_ = size;
                reqList.push_back(req);
                TRACE(_T("req begin:%I64u, size:%u\n"), req.begin_, req.size_);
            }
        }

        addSendPack(sizeof(REQ_DATA_INFO));
        TRACE(_T("------------------\n"));
        return 0;
    }
}