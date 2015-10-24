
#ifndef _FILE_UPDATE_H_
#define _FILE_UPDATE_H_
#pragma once

#include <map>
#include <list>
#include <string>
#include "P2PApplication.h"
#include "P2PFileOperator.h"


namespace XT_P2P
{
    class P2PFileUpdateApp : public P2PApplication
    {
    public:
        P2PFileUpdateApp();
        ~P2PFileUpdateApp();

    protected:
        TCHAR           rootPath_[MAX_PATH];
        TCHAR           fileListMd5_[MAX_PATH]; // 当前的文件列表md5串
        UINT            fileListSize_;          // 当前的文件列表大小

        FILE_INFO_LIST  updateList_;            // 要更新的文件列表

        /**
         *\fn         int GetUpdateFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList)
         *\brief      得到需要更新的文件列表
         *\param[in]  LPCTSTR rootPath              根路径
         *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件列表
         *\return     是否成功,0成功,其它失败
         */
        int GetUpdateFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList);

        /**
         *\fn         int GetErrorFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList)
         *\brief      得到本地校验错误的文件列表
         *\param[in]  LPCTSTR rootPath              根路径
         *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件列表
         *\return     是否成功,0成功,其它失败
         */
        int GetErrorFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList);

        /**
         *\fn         int DownloadUpdateFile(FILE_INFO_LIST &updateList)
         *\brief      下载需要更新的文件
         *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件
         *\return     是否成功,0成功,其它失败
         */
        int DownloadUpdateFile(FILE_INFO_LIST &updateList);

    public:

        /**
         *\fn         bool haveUpdate()
         *\brief      是否有新版本需要更新
         *\return     是否有更新
         */
        bool haveUpdate() { return (0 != updateList_.size()); }

        /**
         *\fn         int decompressFilelist(LPCTSTR listList)
         *\brief      解压文件列表
         *\param[in]  LPCTSTR listList 文件列表名
         *\return     是否成功,0成功,其它失败
         */
        int decompressFilelist(LPCTSTR listList);

        /**
         *\fn         int addUploadTaskList(LPCTSTR rootPath)
         *\brief      添加上传任务
         *\param[in]  LPCTSTR rootPath 文件根目录
         *\return     是否成功,0成功,其它失败
         */
        int addUploadTaskList(LPCTSTR rootPath);

        /**
         *\fn         int run(UINT projectId, LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port)
         *\brief      运行p2p文件更新客户端
         *\param[in]  LPCTSTR projectId 工程ID
         *\param[in]  LPCTSTR rootPath  根目录(文件列表所在的目录)
         *\param[in]  LPCTSTR ip        服务器的IP地址
         *\param[in]  LPCTSTR port      服务器的端口地址
         *\return     是否成功
         */
        int run(UINT projectId, LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port);

        /**
	     *\fn         ProcessPack(void *client, void *buf, int len, int ip, short port)
	     *\brief      处理数据包。
	     *\param[in]  client  客户端。
	     *\param[in]  buf     数据。
	     *\param[in]  len     数据长。
	     *\param[in]  ip	  IP地址(UDP)。
	     *\param[in]  port    端口地址(UDP)。
	     */
	    void ProcessPack(void *client, void *buf, int len, int ip, short port);

        /**
         *\fn         void procGetVersion(LPCTSTR md5, UINT size)
         *\brief      处理得到文件列表信息消息
         *\param[in]  LPCTSTR md5   最新的文件列表的md5
         *\param[in]  UINT size     最新的文件列表的
         *\return     无
         */
        void procGetVersion(LPCTSTR md5, UINT size);

        /**
         *\fn         void procDownload(LPCTSTR md5, UINT size)
         *\brief      处理文件下载完成消息
         *\param[in]  LPCTSTR md5   下载完的文件的md5
         *\param[in]  UINT size     下载完的文件的大小
         *\return     无
         */
        void procDownload(LPCTSTR md5, UINT size);
    };

} // namespace XT_P2P

#endif // _FILE_UPDATE_H_