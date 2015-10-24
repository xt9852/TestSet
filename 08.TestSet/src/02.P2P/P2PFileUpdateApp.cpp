
#include "stdafx.h"
#include "P2PFileUpdateApp.h"


namespace XT_P2P
{
    P2PFileUpdateApp::P2PFileUpdateApp()
        :fileListSize_(0)
    {
        rootPath_[0] = _T('\0');
        fileListMd5_[0] = _T('\0');
    }

    P2PFileUpdateApp::~P2PFileUpdateApp()
    {
    }

    /**
     *\fn         int run(UINT projectId, LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port)
     *\brief      运行p2p文件更新客户端
     *\param[in]  LPCTSTR projectId 工程ID
     *\param[in]  LPCTSTR rootPath  根目录(文件列表所在的目录)
     *\param[in]  LPCTSTR ip        服务器的IP地址
     *\param[in]  LPCTSTR port      服务器的端口地址
     *\return     是否成功
     */
    int P2PFileUpdateApp::run(UINT projectId, LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port)
    {
        if (NULL == rootPath || NULL == ip || NULL == port) return -1;

        _tcscpy_s(rootPath_, ARRAYSIZE(rootPath_), rootPath);

        TCHAR fileListXml[MAX_PATH] = _T("");

        _stprintf_s(fileListXml, ARRAYSIZE(fileListXml), _T("%s\\fileList.xml.7z"), rootPath);

        TCHAR fileListSize[MAX_PATH] = _T("");

        P2PFileOperator fileOper;

        if (!fileOper.GetFileMd5(fileListXml, fileListSize, ARRAYSIZE(fileListSize), 
            fileListMd5_, ARRAYSIZE(fileListMd5_))) return -2;

        fileListSize_ = _ttoi(fileListSize);

        return enginer_.getVersionInfo(projectId, ip, _ttoi(port));
    }

    /**
     *\fn         int decompressFilelist(LPCTSTR rootPath)
     *\brief      解压文件列表
     *\param[in]  LPCTSTR listList 文件根目录
     *\return     是否成功,0成功,其它失败
     */
    int P2PFileUpdateApp::decompressFilelist(LPCTSTR rootPath)
    {
        if (NULL == rootPath) return -1;

        TCHAR oldXml[MAX_PATH] = _T("");
        _stprintf_s(oldXml, ARRAYSIZE(oldXml), _T("%s\\fileList.xml"), rootPath);

        DeleteFile(oldXml);

        P2PFileOperator fileOper;

        return fileOper.UncompareZip7(rootPath, oldXml, rootPath);
    }

    /**
     *\fn         int addUploadTaskList(LPCTSTR rootPath)
     *\brief      添加上传任务
     *\param[in]  LPCTSTR rootPath 文件根目录
     *\return     是否成功,0成功,其它失败
     */
    int P2PFileUpdateApp::addUploadTaskList(LPCTSTR rootPath)
    {
        if (NULL == rootPath) return -1;

        // 解压文件
        TCHAR oldXml[MAX_PATH] = _T("");
        _stprintf_s(oldXml, ARRAYSIZE(oldXml), _T("%s\\fileList.xml"), rootPath);

        UINT projectId = 0;
        FILE_INFO_LIST listList;
        P2PFileOperator fileOper;

        if (0 != fileOper.OpenFileList(oldXml, projectId, listList)) return -3;

        TCHAR filename[MAX_PATH] = _T("");
        TCHAR patch[MAX_PATH] = _T("");
        FILE_INFO_LIST::const_iterator iter = listList.begin();

        for (; iter != listList.end(); ++iter)
        {
            _stprintf_s(filename, ARRAYSIZE(filename), _T("%s\\%s"), rootPath, iter->name);
            enginer_.addUploadTask(iter->md5, _ttoi64(iter->size), filename);

            _stprintf_s(filename, ARRAYSIZE(filename), _T("%s_7z\\%s.7z"), rootPath, iter->name);
            enginer_.addUploadTask(iter->zip7Md5, _ttoi64(iter->zip7Size), filename);

            if (0 != _tcscmp(iter->patchMd5, _T("")))
            {
                _stprintf_s(filename, ARRAYSIZE(filename), _T("%s\\%s"), rootPath, iter->name);
                _stprintf_s(patch, ARRAYSIZE(patch), _T("%s_patch\\%s.%s.patch"), 
                    rootPath, iter->name, fileOper.canCourgette(filename)?"gen":"genbsdiff");

                enginer_.addUploadTask(iter->patchMd5, _ttoi64(iter->patch7zSize), patch);
            }

            if (0 != _tcscmp(iter->patch7zMd5, _T("")))
            {
                _stprintf_s(filename, ARRAYSIZE(filename), _T("%s\\%s"), rootPath, iter->name);
                _stprintf_s(patch, ARRAYSIZE(patch), _T("%s_patch\\%s.%s.patch.7z"), 
                    rootPath, iter->name, fileOper.canCourgette(filename)?"gen":"genbsdiff");

                enginer_.addUploadTask(iter->patch7zMd5, _ttoi64(iter->patch7zSize), patch);
            }
        }

        TCHAR md5[MAX_PATH] = _T("");
        TCHAR size[MAX_PATH] = _T("");

        _tcscat_s(oldXml, ARRAYSIZE(oldXml), _T(".7z"));

        if (!fileOper.GetFileMd5(oldXml, size, ARRAYSIZE(size), md5, ARRAYSIZE(md5))) return -4;

        enginer_.addUploadTask(md5, _ttoi64(size), _T("/fileList.xml.7z"));

        enginer_.setVersionInfo(md5, _ttoi(size));

        return 0;
    }

    /**
     *\fn         int GetUpdateFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList)
     *\brief      得到需要更新的文件列表
     *\param[in]  LPCTSTR rootPath              根路径
     *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件列表
     *\return     是否成功,0成功,其它失败
     */
    int P2PFileUpdateApp::GetUpdateFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList)
    {
        if (NULL == rootPath) return -1;

        TCHAR oldXml[MAX_PATH] = _T("");
        TCHAR newXml[MAX_PATH] = _T("");

        _stprintf_s(oldXml, ARRAYSIZE(oldXml), _T("%s\\fileList.xml"), rootPath);
        _stprintf_s(newXml, ARRAYSIZE(newXml), _T("%s\\update\\fileList.xml"), rootPath);

        P2PFileOperator fileOper;

        return fileOper.GetUpdateList(rootPath, newXml, oldXml, updateList);
    }

    /**
     *\fn         int GetErrorFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList)
     *\brief      得到本地校验错误的文件列表
     *\param[in]  LPCTSTR rootPath              根路径
     *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件列表
     *\return     是否成功,0成功,其它失败
     */
    int P2PFileUpdateApp::GetErrorFileList(LPCTSTR rootPath, FILE_INFO_LIST &updateList)
    {
        if (NULL == rootPath) return -1;

        if (0 != decompressFilelist(rootPath)) return -2;

        TCHAR oldXml[MAX_PATH] = _T("");

        _stprintf_s(oldXml, ARRAYSIZE(oldXml), _T("%s\\fileList.xml"), rootPath);

        P2PFileOperator fileOper;

        return fileOper.CheckLocalFile(rootPath, oldXml, updateList);
    }

    /**
     *\fn         int DownloadUpdateFile(FILE_INFO_LIST &updateList)
     *\brief      下载需要更新的文件
     *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件
     *\return     是否成功,0成功,其它失败
     */
    int P2PFileUpdateApp::DownloadUpdateFile(FILE_INFO_LIST &updateList)
    {
        TCHAR filename[MAX_PATH] = _T("");

        FILE_INFO_LIST::const_iterator iter = updateList.begin();

        for (; iter != updateList.end(); ++iter)
        {
            if (FileInfo::UPDATE_NULL != iter->updateType)
            {
                _stprintf_s(filename, ARRAYSIZE(filename), _T("\\update\\%s"), iter->name);

                LPCTSTR md5 = (FileInfo::UPDATE_PATCH == iter->updateType) ? iter->patch7zMd5 : iter->zip7Md5;
                LPCTSTR size = (FileInfo::UPDATE_PATCH == iter->updateType) ? iter->patch7zSize : iter->zip7Size;

                enginer_.addDownloadTask(md5, _ttoi64(size), filename);
            }
        }

        return 0;
    }

    /**
	 *\fn         ProcessPack(void *client, void *buf, int len, int ip, short port)
	 *\brief      处理数据包。
	 *\param[in]  client  客户端。
	 *\param[in]  buf     数据。
	 *\param[in]  len     数据长。
	 *\param[in]  ip	  IP地址(UDP)。
	 *\param[in]  port    端口地址(UDP)。
	 */
    void P2PFileUpdateApp::ProcessPack(void *client, void *buf, int len, int ip, short port)
    {
        XT_P2P::P2PMsg *msg = (XT_P2P::P2PMsg*)buf;

        switch (msg->id_)
        {
        case XT_P2P::P2P_GET_VERSION_RSP:
            {
                XT_P2P::P2PGetVersionRsp *versionRsp = (XT_P2P::P2PGetVersionRsp*)buf;
                procGetVersion(versionRsp->md5_, versionRsp->size_);
                buffPool_.Free(buf);
                break;
            }
        case XT_P2P::P2P_TASK_DOWNLOAD_RET:
            {
                XT_P2P::P2PInsideMsg *downloadRet = (XT_P2P::P2PInsideMsg*)buf;
                procDownload(downloadRet->getResultMd5(), downloadRet->getResultSize());
                buffPool_.Free(buf);
                break;
            }
        default:
            {
                buffPool_.Free(buf);
                TRACE("CDlg_P2P::ProcessPack error\n");
                break;
            }
        }
    }

    /**
     *\fn         void procGetVersion(LPCTSTR md5, UINT size)
     *\brief      处理得到文件列表信息消息
     *\param[in]  LPCTSTR md5   最新的文件列表的md5
     *\param[in]  UINT size     最新的文件列表的
     *\return     无
     */
    void P2PFileUpdateApp::procGetVersion(LPCTSTR md5, UINT size)
    {
        if (NULL == md5) return;

        if (0 != _tcscmp(fileListMd5_, md5) || fileListSize_ != size)// 有版本更新,下载最新的文件列表
        {
            enginer_.addDownloadTask(md5, size, _T("update\\fileList.xml.7z"));
        }
        else // 无更新,开始准备上传文件
        {
            if (0 == GetErrorFileList(rootPath_, updateList_))
            {
                DownloadUpdateFile(updateList_);
            }
            else
            {
                addUploadTaskList(rootPath_);
            }
        }
    }

    /**
     *\fn         void procDownload(LPCTSTR md5, UINT size)
     *\brief      处理文件下载完成消息
     *\param[in]  LPCTSTR md5   下载完的文件的md5
     *\param[in]  UINT size     下载完的文件的大小
     *\return     无
     */
    void P2PFileUpdateApp::procDownload(LPCTSTR md5, UINT size)
    {
        if (NULL == md5) return;

        if (0 == _tcscmp(md5, fileListMd5_)) // 文件列表,fileList.xml
        {
            LOG(INFO) << "P2PFileUpdateApp::procDownload---------- downloaded fileList.xml " << md5 << "" << size;

            decompressFilelist(rootPath_);
            GetUpdateFileList(rootPath_, updateList_);
            DownloadUpdateFile(updateList_);
        }
        else
        {
            LOG(INFO) << "P2PFileUpdateApp::procDownload---------- " << md5 << "" << size;

            FILE_INFO_LIST::const_iterator iter = updateList_.begin();

            for (; iter != updateList_.end(); ++iter)
            {
                if (0 != _tcscmp(iter->md5, md5) || _ttoi64(iter->size) != size)
                {
                    updateList_.erase(iter);
                    break;
                }
            }

            if (updateList_.size() == 0) // 已经下载完成,通知主程序,有新的更新并替换文件
            {
                // to do replaceFile
            }
        }
    }

} // namespace XT_P2P
