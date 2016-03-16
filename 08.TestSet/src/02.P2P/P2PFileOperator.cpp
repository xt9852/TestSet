#include "stdafx.h"
#include "P2PFileOperator.h"
#include "zip/7z.h"
#include "08.Algorithm/base/MD5.h"
#include "../courgette/courgette.h"

//#pragma comment(lib, "../10.thirdParty/lib/zip/7z.lib")
#ifdef _DEBUG
#pragma comment(lib, "../10.thirdParty/lib/courgette/courgetted.lib")
#else
#pragma comment(lib, "../10.thirdParty/lib/courgette/courgette.lib")
#endif


namespace XT_P2P
{
    P2PFileOperator::P2PFileOperator()
    {
    }

    P2PFileOperator::~P2PFileOperator()
    {
    }

    /**
     *\fn         DWORD runProcess(LPCTSTR cmd, LPCTSTR path)
     *\brief      运行程序
     *\param[in]  LPCTSTR cmd   命令可带参数
     *\param[in]  LPCTSTR path  命令执行的默认路径
     *\return     程序退出码
     */
    int P2PFileOperator::runProcess(LPCTSTR cmd, LPCTSTR path)
    {
        if (NULL == cmd || NULL == path) return -1;

        DWORD exitCode = 0;
        PROCESS_INFORMATION pi = {0};
        STARTUPINFO si = {0};
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;

        if (!CreateProcess(NULL, (LPTSTR)cmd, NULL, NULL, FALSE, CREATE_NEW_PROCESS_GROUP, NULL, path, &si, &pi)) return -2;

        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &exitCode);

        return exitCode;
    }

    /**
     *\fn         bool getFile(FILE_INFO_LIST &fileList, LPCTSTR name, FileInfo &file)
     *\brief      得到文件的信息
     *\param[in]  FILE_INFO_LIST & fileList 文件列表
     *\param[in]  LPCTSTR name              文件名
     *\param[in]  FileInfo & file           文件信息
     *\return     是否成功
     */
    bool P2PFileOperator::getFile(FILE_INFO_LIST &fileList, LPCTSTR name, FileInfo &file)
    {
        if (NULL == name) return false;

        FILE_INFO_LIST::const_iterator iter = fileList.begin();

        for (; iter != fileList.end(); ++iter)
        {
            if (0 == _tcscmp(name, iter->name))
            {
                file = *iter;
                return true;
            }
        }

        return false;
    }

    /**
     *\fn         void deleteFileInList(FILE_INFO_LIST &fileList, LPCTSTR name)
     *\brief      从文件列表中删除文件
     *\param[in]  FILE_INFO_LIST & fileList 文件列表
     *\param[in]  LPCTSTR name              文件名
     *\return     无
     */
    void P2PFileOperator::deleteFileInList(FILE_INFO_LIST &fileList, LPCTSTR name)
    {
        if (NULL == name) return;

        FILE_INFO_LIST::const_iterator iter = fileList.begin();

        for (; iter != fileList.end(); ++iter)
        {
            if (0 == _tcscmp(name, iter->name))
            {
                fileList.erase(iter);
                break;
            }
        }
    }

    /**
     *\fn         GetFiles(LPCTSTR root, LPCTSTR path, FILE_INFO_LIST &files)
     *\brief      查找文件，包含子目录。
     *\param[in]  root	根目录。
     *\param[in]  path	相对目录。
     *\param[out] files	文件。
     *\return     是否成功
     */
    bool P2PFileOperator::GetFiles(LPCTSTR root, LPCTSTR path, FILE_INFO_LIST &files)
    {
        if (NULL == root || NULL == path) return false;

        bool ret = true;
        bool finished = false;

        WIN32_FIND_DATA fileData = {0};

        TCHAR fullPath[MAX_PATH] = _T("");
        _stprintf_s(fullPath, "%s\\%s", root, path);

        if (!SetCurrentDirectory(fullPath)) return false;

        HANDLE search = FindFirstFile(_T("*.*"), &fileData);

        if (search == INVALID_HANDLE_VALUE)
        {
            ret = false;
        }

        while (!finished && ret)
        {
            if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)// 是文件
            {
                FileInfo fileInfo = {0};
                _stprintf_s(fileInfo.name, "%s%s", path, fileData.cFileName);
                files.push_back(fileInfo);
            }
            else if ((_tcscmp(fileData.cFileName, _T(".")) != 0) && (_tcscmp(fileData.cFileName, _T("..")) != 0))// 是目录
            {
                TCHAR shortPath[MAX_PATH] = _T(""); // 相对路径
                _stprintf_s(shortPath, "%s%s\\", path, fileData.cFileName);
                GetFiles(root, shortPath, files);  // 递归调用
            }

            if (!FindNextFile(search, &fileData))
            {
                if (GetLastError() == ERROR_NO_MORE_FILES)
                {
                    finished = true;
                }
                else
                {
                    ret = false;
                }
            }
        }

        FindClose(search);

        return ret;
    }

    /**
     *\fn         GetFilesMd5(LPCTSTR rootPath, FILE_INFO_LIST &files)
     *\brief      计算文件md5。
     *\param[in]  rootPath	文件根路径。
     *\param[out] files	文件。
     *\return     是否成功
     */
    bool P2PFileOperator::GetFilesMd5(LPCTSTR rootPath, FILE_INFO_LIST &files)
    {
        if (NULL == rootPath) return false;

        TCHAR  filename[MAX_PATH] = _T("");

        for (FILE_INFO_LIST::iterator iter = files.begin(); iter != files.end(); ++iter)
        {
            if (iter->exclude) continue;

            _stprintf_s(filename, ARRAYSIZE(filename), _T("%s\\%s"), rootPath, iter->name);

            GetFileMd5(filename, iter->size, ARRAYSIZE(iter->size), iter->md5, ARRAYSIZE(iter->md5));
        }

        return true;
    }

    /**
     *\fn         bool GetFileMd5(LPCTSTR filename, LPTSTR size, UINT sizeBuffLen, LPTSTR md5, UINT md5BuffLen)
     *\brief      计算文件md5
     *\param[in]  LPCTSTR filename  文件名
     *\param[in]  LPTSTR size       文件大小字符串
     *\param[in]  UINT sizeBuffLen  文件大小字符串缓冲区大小
     *\param[in]  LPTSTR md5        md5字符串
     *\param[in]  UINT md5BuffLen   md5字符串缓冲区大小
     *\return     是否成功
     */
    bool P2PFileOperator::GetFileMd5(LPCTSTR filename, LPTSTR size, UINT sizeBuffLen, 
        LPTSTR md5, UINT md5BuffLen)
    {
        if (NULL == filename || NULL == size || NULL == md5 || md5BuffLen < 32) return false;

        USES_CONVERSION;

        FILE *file = fopen(T2A((LPTSTR)filename), "rb");

        if (NULL == file) return false;

        int buffSize = 1024*1024*10;
        char *buff = new char[buffSize];
        CMD5 Md5;

        fseek(file, 0, SEEK_END);

        UINT64 len = 0;
        UINT64 fileSize = ftell(file);

        for (UINT64 i = 0; i < fileSize; i+=len)
        {
            fseek(file, i, SEEK_SET);

            len = fread(buff, 1, buffSize, file);

            Md5.Add(buff, len);
        }

        fclose(file);

        Md5.Finish();

        Md5.HashToChar(Md5.getHash(), md5, md5BuffLen);

        _stprintf_s(size, sizeBuffLen, _T("%I64u"), fileSize);

        delete buff;

        return true;
    }

    /**
     *\fn         int OpenFileList(LPCTSTR xml, UINT projectId, FILE_INFO_LIST &fileList)
     *\brief      解析文件列表
     *\param[in]  LPCTSTR xml               xml文件名
     *\param[in]  UINT projectId            工程ID
     *\param[in]  FILE_INFO_LIST & fileList 文件列表
     *\return     0成功,其它失败
     */
    int P2PFileOperator::OpenFileList(LPCTSTR xml, UINT projectId, FILE_INFO_LIST &fileList)
    {
        if (NULL == xml) return -1;

        USES_CONVERSION;

        if (!xml_.LoadFile(T2A((LPTSTR)xml))) return -2;

        XT_XML::TiXmlElementEx *version = xml_.GetRoot()->SelectSingleNode("version");

        if (NULL == version) return -3;

        version->Attribute("projectId", (int*)&projectId);

        XT_XML::TiXmlElementExs files = version->SelectNodes("file");

        for (int i = 0; i < files.getCount(); i++)
        {
            LPCSTR name        = files[i]->Attribute("name");
            LPCSTR size        = files[i]->Attribute("size");
            LPCSTR md5         = files[i]->Attribute("md5");
            LPCSTR zip7Size    = files[i]->Attribute("zip7Size");
            LPCSTR zip7Md5     = files[i]->Attribute("zip7Md5");
            LPCSTR patchSize   = files[i]->Attribute("patchSize");
            LPCSTR patchMd5    = files[i]->Attribute("patchMd5");
            LPCSTR patch7zSize = files[i]->Attribute("patch7zSize");
            LPCSTR patch7zMd5  = files[i]->Attribute("patch7zMd5");
            LPCSTR exclude     = files[i]->Attribute("exclude");

            FileInfo fileInfo = {0};

            if (NULL != name)
            {
                _tcscpy_s(fileInfo.name, ARRAYSIZE(fileInfo.name), A2T((LPSTR)name));
            }

            if (NULL != size)
            {
                _tcscpy_s(fileInfo.size, ARRAYSIZE(fileInfo.size), A2T((LPSTR)size));
            }

            if (NULL != md5)
            {
                _tcscpy_s(fileInfo.md5, ARRAYSIZE(fileInfo.md5), A2T((LPSTR)md5));
            }

            if (NULL != zip7Size)
            {
                _tcscpy_s(fileInfo.zip7Size, ARRAYSIZE(fileInfo.zip7Size), A2T((LPSTR)zip7Size));
            }

            if (NULL != zip7Md5)
            {
                _tcscpy_s(fileInfo.zip7Md5, ARRAYSIZE(fileInfo.zip7Md5), A2T((LPSTR)zip7Md5));
            }

            if (NULL != patchSize)
            {
                _tcscpy_s(fileInfo.patchSize, ARRAYSIZE(fileInfo.patchSize), A2T((LPSTR)patchSize));
            }

            if (NULL != patchMd5)
            {
                _tcscpy_s(fileInfo.patchMd5, ARRAYSIZE(fileInfo.patchMd5), A2T((LPSTR)patchMd5));
            }

            if (NULL != patch7zSize)
            {
                _tcscpy_s(fileInfo.patch7zSize, ARRAYSIZE(fileInfo.patch7zSize), A2T((LPSTR)patch7zSize));
            }

            if (NULL != patch7zMd5)
            {
                _tcscpy_s(fileInfo.patch7zMd5, ARRAYSIZE(fileInfo.patch7zMd5), A2T((LPSTR)patch7zMd5));
            }

            if (NULL != exclude)
            {
                fileInfo.exclude = true;
            }

            fileList.push_back(fileInfo);
        }

        return 0;
    }

    /**
     *\fn         bool CompareFile(FILE_INFO_LIST &oldFileList, FILE_INFO_LIST &newFileList)
     *\brief      比较文件，以便生成补丁文件
     *\param[in]  FILE_INFO_LIST & oldFileList 旧文件列表
     *\param[in]  FILE_INFO_LIST & newFileList 新文件列表
     *\return     是否有不同的
     */
    bool P2PFileOperator::CompareFile(FILE_INFO_LIST &oldFileList, FILE_INFO_LIST &newFileList)
    {
        bool ret = false;

        FILE_INFO_LIST::iterator newIter = newFileList.begin();
        for (; newIter != newFileList.end(); ++newIter)
        {
            FILE_INFO_LIST::const_iterator oldIter = oldFileList.begin();
            for (; oldIter != oldFileList.end(); ++oldIter)
            {
                if (0 == _tcscmp(newIter->name, oldIter->name))
                {
                    if (0 != _tcscmp(newIter->md5, oldIter->md5))
                    {
                        ret = true;
                        _tcscpy_s(newIter->oldMd5, ARRAYSIZE(newIter->oldMd5), oldIter->md5);
                        _tcscpy_s(newIter->oldSize, ARRAYSIZE(newIter->oldSize), oldIter->size);
                    }

                    break;
                }
            }
        }

        return ret;
    }

    /**
     *\fn         int CreatePatch(LPCTSTR rootPath, LPCTSTR oldVersion, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
     *\brief      生成补丁文件
     *\param[in]  LPCTSTR rootPath 根路径
     *\param[in]  LPCTSTR oldVersion 旧的版本号
     *\param[in]  LPCTSTR newVersion 新的版本号
     *\param[in]  FILE_INFO_LIST & fileList 文件列表
     *\return     0成功,其它失败
     */
    int P2PFileOperator::CreatePatch(LPCTSTR rootPath, LPCTSTR oldVersion, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
    {
        if (NULL == rootPath || NULL == oldVersion || NULL == newVersion) return -1;

        LPCTSTR subCmd = NULL;
        TCHAR newFilename[MAX_PATH] = _T("");
        TCHAR patch[MAX_PATH] = _T("");
        TCHAR cmd[MAX_PATH*5] = _T("");
        bool ret = false;

        FILE_INFO_LIST::iterator iter = fileList.begin();
        for (; iter != fileList.end(); ++iter)
        {
            if (0 != _tcscmp(iter->oldMd5, _T("")))
            {
                _stprintf_s(newFilename, ARRAYSIZE(newFilename), _T("%s\\%s\\%s"),
                    rootPath,
                    newVersion,
                    iter->name);

                ret = canCourgette(newFilename);

                subCmd = ret ? _T("-gen") : _T("-genbsdiff");

                iter->patchType = ret ? FileInfo::PATCH_COURGETTE : FileInfo::PATCH_BSDIFF;

                _stprintf_s(patch, ARRAYSIZE(patch), _T("%s\\%s_patch\\%s.%s.patch"),
                    rootPath,
                    newVersion,
                    iter->name,
                    &(subCmd[1]));

                TCHAR oldFile[MAX_PATH] = _T("");

                _stprintf_s(oldFile, ARRAYSIZE(oldFile), _T("%s\\%s\\%s"),
                    rootPath,
                    oldVersion,
                    iter->name);

                TCHAR newFile[MAX_PATH] = _T("");

                _stprintf_s(newFile, ARRAYSIZE(newFile), _T("%s\\%s\\%s"),
                    rootPath,
                    newVersion,
                    iter->name);

                const char* argv[5] = { "", T2A((LPTSTR)subCmd), T2A(oldFile), T2A(newFile), T2A(patch) };

                if (0 == courgette_main(5, argv)) // courtette -gen|-genbsdiff oldfile newfile patch
                {
                    GetFileMd5(patch, iter->patchSize, ARRAYSIZE(iter->patchSize), iter->patchMd5, ARRAYSIZE(iter->patchMd5));
                }
                else
                {
                    LOG(INFO) << _T("生成补丁文件错误: ") << cmd;
                }
            }
        }

        return 0;
    }

    /**
     *\fn         int CreateZip7(LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
     *\brief      生成7zip压缩文件
     *\param[in]  LPCTSTR rootPath          根路径
     *\param[in]  LPCTSTR newVersion        新版本号
     *\param[in]  FILE_INFO_LIST & fileList 文件列表
     *\return     0成功,其它失败
     */
    int P2PFileOperator::CreateZip7(LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
    {
        if (NULL == rootPath || NULL == newVersion) return -1;

        int exitCode = 0;
        TCHAR zip7[MAX_PATH] = _T("");
        TCHAR cmd[MAX_PATH*5] = _T("");
        TCHAR compressFilename[MAX_PATH] = _T("");

        _stprintf_s(zip7, ARRAYSIZE(zip7), _T("%s\\%s_7z"), rootPath, newVersion);

        ::CreateDirectory(zip7, NULL);

        FILE_INFO_LIST::iterator iter = fileList.begin();
        for (; iter != fileList.end(); ++iter)
        {
            _stprintf_s(zip7, ARRAYSIZE(zip7), _T("%s\\%s_7z\\%s.7z"),
                rootPath,
                newVersion,
                iter->name);

            _stprintf_s(compressFilename, ARRAYSIZE(compressFilename), _T("%s\\%s\\%s"), 
                rootPath,
                newVersion,
                iter->name);

            exitCode = CreateZip7(rootPath, zip7, compressFilename); // 压缩文件

            if (0 == exitCode)
            {
                GetFileMd5(zip7, iter->zip7Size, ARRAYSIZE(iter->zip7Size), iter->zip7Md5, ARRAYSIZE(iter->zip7Md5));
            }
            else
            {
                LOG(INFO) << _T("压缩文件错误: ") << cmd;
            }

            if (FileInfo::PATCH_NULL == iter->patchType) continue; // 没有有补丁

            _stprintf_s(zip7, ARRAYSIZE(zip7), _T("%s\\%s_patch\\%s.%s.patch.7z"),
                rootPath,
                newVersion,
                iter->name,
                ((FileInfo::PATCH_COURGETTE == iter->patchType) ? _T("gen") : _T("genbsdiff")));

            _stprintf_s(compressFilename, ARRAYSIZE(compressFilename), _T("%s\\%s_patch\\%s.%s.patch"), 
                rootPath,
                newVersion,
                iter->name,
                ((FileInfo::PATCH_COURGETTE == iter->patchType) ? _T("gen") : _T("genbsdiff")));

            exitCode = CreateZip7(rootPath, zip7, compressFilename); // 压缩补丁

            if (0 == exitCode)
            {
                GetFileMd5(zip7, iter->patch7zSize, ARRAYSIZE(iter->patch7zSize), iter->patch7zMd5, ARRAYSIZE(iter->patch7zMd5));
            }
            else
            {
                LOG(INFO) << _T("压缩补丁文件错误: ") << cmd;
            }
        }

        return 0;
    }

    /*
     *\fn         int CreateZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR filename)
     *\brief      生成7zip压缩文件
     *\param[in]  LPCTSTR rootPath 根路径
     *\param[in]  LPCTSTR zip7 7z文件名
     *\param[in]  LPCTSTR filename 文件名
     *\return     int 0成功,其它失败
     */
    int P2PFileOperator::CreateZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR filename)
    {
        TCHAR cmd[MAX_PATH*5];
        _stprintf_s(cmd, ARRAYSIZE(cmd), _T("%s\\7z.exe a \"%s\" \"%s\""), rootPath, zip7, filename);

        int ret = runProcess(cmd, rootPath); // 使用7z.exe压缩文件

        //int ret = create_7z(zip7, 1, filename);

        return ret;
    }

    /*
     *\fn         int UncompareZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR outPath)
     *\brief      解压7zip文件
     *\param[in]  LPCTSTR rootPath 根路径
     *\param[in]  LPCTSTR zip7 文件名
     *\param[in]  LPCTSTR outPath 输出路径
     *\return     int 0成功,其它失败
     */
    int P2PFileOperator::UncompareZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR outPath)
    {
#ifdef ZIP7_EXE
        TCHAR cmd[MAX_PATH*5] = _T("");

        _stprintf_s(cmd, ARRAYSIZE(cmd), _T("%s\\7z.exe x \"%s\" -o\"%s\""), rootPath, zip7, outPath);

        int ret = runProcess(cmd, rootPath); // 使用7z.exe压缩文件
#else

        int ret = 0;// exclude_7z(zip7, outPath); // 使用7z.lib压缩文件

#endif // ZIP7_EXE

        return ret;
    }

    /*
     *\fn         bool canCourgette(LPCTSTR filename)
     *\brief      是否能使用courgette
     *\param[in]  LPCTSTR filename 文件名
     *\return     bool 是否能使用courgette
     */
    bool P2PFileOperator::canCourgette(LPCTSTR filename)
    {
        if (NULL == filename) return false;

        const char* argv1[3] = { "", "-supported", T2A((LPTSTR)filename) };

        return (0 == courgette_main(3, argv1)); // courgette -supported newfile // 确定能否用courgette生成补丁
    }

    /**
     *\fn         int ExcludeFile(FILE_INFO_LIST &fileList, STRING_LIST &excludeFileList)
     *\brief      排队文件
     *\param[in]  FILE_INFO_LIST & fileList 文件列表
     *\param[in]  STRING_LIST & excludeFileList 需要排除的文件列表
     *\return     0成功,其它失败
     */
    int P2PFileOperator::ExcludeFile(FILE_INFO_LIST &fileList, STRING_LIST &excludeFileList)
    {
        STRING_LIST::const_iterator excludeIter = excludeFileList.begin();

        for (; excludeIter != excludeFileList.end(); ++excludeIter)
        {
            FILE_INFO_LIST::iterator fileIter = fileList.begin();

            for (; fileIter != fileList.end(); ++fileIter)
            {
                if (fileIter->name == *excludeIter)
                {
                    fileIter->exclude = true;
                }
            }
        }

        return 0;
    }

#define FTP_SERVER_IP   _T("172.109.1.78")
#define FTP_SERVER_PORT _T("8080")

    /**
     *\fn         int CreateXmlFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
     *\brief      生成文件列表xml
     *\param[in]  UINT projectId            工程ID
     *\param[in]  LPCTSTR rootPath          根路径
     *\param[in]  LPCTSTR newVersion        新版本号
     *\param[in]  FILE_INFO_LIST & fileList 文件列表
     *\return     0成功,其它失败
     */
    int P2PFileOperator::CreateXmlFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
    {
        if (NULL == rootPath || NULL == newVersion) return -1;

        TCHAR filename[MAX_PATH] = _T("");
        _stprintf_s(filename, ARRAYSIZE(filename), _T("%s\\%s\\fileList.xml"), rootPath, newVersion);

        FILE *file = NULL;
        fopen_s(&file, filename, "wb");

        if (NULL == file) return -1;

        CTime time = CTime::GetCurrentTime();

        TCHAR info[MAX_PATH*10] = _T("");
        _stprintf_s(info, ARRAYSIZE(info), _T("<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n")
            _T("<XmlRoot>\r\n")
            _T("    <!-- addr文件服务器地址,port文件服务器端口 -->\r\n")
            _T("    <server addr=\"%s\" port=\"%s\" />\r\n\r\n")
            _T("    <!-- name版本号,time发布时间,desc描述信息,path文件路径 -->\r\n")
            _T("    <version projectId=\"%d\" name=\"%s\" time=\"%s\" path=\"/TestSet/%s\" desc=\"正式版\" >\r\n\r\n")
            _T("        <!-- file文件列表,name文件相对路径名-->\r\n")
            _T("        <!-- size文件大小,md5文件校验码-->\r\n")
            _T("        <!-- zip7Size文件压缩后大小,zip7Md5文件压缩后校验码-->\r\n")
            _T("        <!-- patchSize补丁文件大小,patchMd5补丁文件校验码-->\r\n")
            _T("        <!-- patch7zSize补丁文件压缩后大小,patch7zMd5补丁文件压缩后校验码-->\r\n")
            _T("        <!-- oldSize旧文件大小,oldMd5旧文件校验码-->\r\n")
            _T("        <!-- exclude是否排除文件,如果排除则不下载更新,但无此文件时下载文件-->\r\n"),
            FTP_SERVER_IP, 
            FTP_SERVER_PORT, 
            projectId,
            newVersion, 
            time.Format(_T("%Y-%m-%d %H:%M:%S")),
            newVersion);

        fwrite(info, 1, _tcslen(info), file);

        TCHAR patch[MAX_PATH] = _T("");
        TCHAR exclude[MAX_PATH] = _T("");

        FILE_INFO_LIST::const_iterator iter = fileList.begin();
        for (;iter != fileList.end(); ++iter)
        {
            if (0 != _tcscmp(iter->patchMd5, _T("")))
            {
                _stprintf_s(patch, ARRAYSIZE(patch), _T(" patchSize=\"%s\" patchMd5=\"%s\"")
                    _T(" patch7zSize=\"%s\" patch7zMd5=\"%s\" oldSize=\"%s\" oldMd5=\"%s\""),
                    iter->patchSize,
                    iter->patchMd5,
                    iter->patch7zSize,
                    iter->patch7zMd5,
                    iter->oldSize,
                    iter->oldMd5);
            }
            else
            {
                patch[0] = _T('\0');
            }

            _tcscpy_s(exclude, ARRAYSIZE(exclude), iter->exclude ? _T(" exclude=\"true\"") : _T(""));

            _stprintf_s(info, ARRAYSIZE(info), _T("        <file name=\"%s\" size=\"%s\" md5=\"%s\" ")
                _T("zip7Size=\"%s\" zip7Md5=\"%s\"%s%s/>\r\n"),
                iter->name, 
                iter->size,
                iter->md5, 
                iter->zip7Size,
                iter->zip7Md5,
                exclude,
                patch);

            // 写入xml列表文件
            fwrite(info, 1, _tcslen(info), file);
        }

        _tcscpy_s(info, ARRAYSIZE(info), _T("    </version>\r\n</XmlRoot>"));
        fwrite(info, 1, _tcslen(info), file);

        fclose(file);

        return 0;
    }

    /**
     *\fn         int CreateFileList(UINT projectId, LPCTSTR rootPath, 
     LPCTSTR newVersion, LPCTSTR oldVersion, STRING_LIST &excludeFileList)
     *\brief      生成新的文件列表
     *\param[in]  UINT projectId                工程ID
     *\param[in]  LPCTSTR rootPath              根文件路径
     *\param[in]  LPCTSTR newVersion            新的版本号
     *\param[in]  LPCTSTR oldVersion            旧的版本号
     *\param[in]  STRING_LIST & excludeFileList 要排除的文件列表
     *\return     0成功,其它失败
     */
    int P2PFileOperator::CreateFileList(UINT projectId, LPCTSTR rootPath, 
        LPCTSTR newVersion, LPCTSTR oldVersion, STRING_LIST &excludeFileList)
    {
        if (NULL == rootPath || NULL == newVersion) return -1; // oldVersion可以为空

        int ret = 0;

        if (NULL != oldVersion && 0 != _tcscmp(oldVersion, _T("")))
        {
            TCHAR oldXml[MAX_PATH] = _T("");
            _stprintf_s(oldXml, ARRAYSIZE(oldXml), _T("%s\\%s\\fileList.xml"), rootPath, oldVersion);

            UINT oldProjectId = 0;
            OpenFileList(oldXml, oldProjectId, oldFileList_); // 从fileList.xml读文件信息
        }

        TCHAR newPath[MAX_PATH] = _T("");
        _stprintf_s(newPath, ARRAYSIZE(newPath), _T("%s\\%s"), rootPath, newVersion);

        if (GetFiles(newPath, _T(""), newFileList_)) // 得到文件列表
        {
            GetFilesMd5(newPath, newFileList_);
        }

        if (CompareFile(oldFileList_, newFileList_)) // 比较文件
        {
            CreatePatch(rootPath, oldVersion, newVersion, newFileList_);
        }

        CreateZip7(rootPath, newVersion, newFileList_);

        ExcludeFile(newFileList_, excludeFileList); // 排除无需要升级的文件

        CreateXmlFileList(projectId, rootPath, newVersion, newFileList_); // 生成fileList.xml

        TCHAR xml[MAX_PATH] = _T("");
        TCHAR zip7[MAX_PATH] = _T("");
        _stprintf_s(xml, ARRAYSIZE(xml), _T("%s\\%s\\fileList.xml"), rootPath, newVersion);
        _stprintf_s(zip7, ARRAYSIZE(zip7), _T("%s\\%s_7z\\fileList.xml.7z"), rootPath, newVersion);
        return CreateZip7(rootPath, zip7, xml); // 生成fileList.xml.7z
    }

    /**
     *\fn         int GetUpdateList(LPCTSTR rootPath, LPCTSTR newXml, LPCTSTR oldXml, FILE_INFO_LIST &updateList)
     *\brief      得到需列新的文件列表
     *\param[in]  LPCTSTR rootPath              根文件路径
     *\param[in]  LPCTSTR newXml                新的文件列表xml
     *\param[in]  LPCTSTR oldXml                旧的文件列表xml  
     *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件
     *\return     函数返回值
     */
    int P2PFileOperator::GetUpdateList(LPCTSTR rootPath, LPCTSTR newXml, LPCTSTR oldXml, FILE_INFO_LIST &updateList)
    {
        if (NULL == rootPath || NULL == newXml) return -1;

        UINT newProjectId = 0;
        UINT oldProjectId = 0;

        GetFiles(rootPath, _T(""), localFileList_); // 扫描 rootPath下的所有文件含子目录文件,计算md5,存入localFileList
        GetFilesMd5(rootPath, localFileList_);
        OpenFileList(newXml, newProjectId, newFileList_);   // 得到新的文件信息

        if (NULL != oldXml)
        {
            OpenFileList(oldXml, oldProjectId, oldFileList_);   // 得到旧的文件信息
        }

        for (FILE_INFO_LIST::const_iterator localFileIter = localFileList_.begin();
            localFileIter != localFileList_.end();
            ++localFileIter)
        {
            LPCTSTR localFileMd5 = localFileIter->md5;
            LPCTSTR localFileName = localFileIter->name;

            FileInfo oldFile = {0};
            FileInfo newFile = {0};

            bool sameOldFileMd5 = false;
            bool sameNewFileMd5 = false;

            bool inOldFileList = getFile(oldFileList_, localFileName, oldFile);  // 是否在旧的文件信息内
            bool inNewFileList = getFile(newFileList_, localFileName, newFile);  // 是否在新的文件信息内

            if (inOldFileList)
            {
                sameOldFileMd5 = (0 == _tcscmp(localFileMd5, oldFile.md5));
            }

            if (inNewFileList)
            {
                sameNewFileMd5 = (0 == _tcscmp(localFileMd5, newFile.md5));
            }

            // 在新的文件列表中,但不同于新的md5,则需下载补丁或整个新的文件
            if (inNewFileList && !sameNewFileMd5 && !newFile.exclude)
            {
                // 与旧文件的md5相同,下载补丁文件,
                // 否则下载整个的新文件,因为旧的文件已经被改了,这样就用不了补丁了
                newFile.updateType = sameOldFileMd5 ? FileInfo::UPDATE_PATCH : FileInfo::UPDATE_FILE;

                updateList.push_back(newFile);
            }

            if (inOldFileList)
            {
                deleteFileInList(oldFileList_, localFileName);
            }

            if (inNewFileList)
            {
                deleteFileInList(newFileList_, localFileName);
            }
        }

        if (newFileList_.size() > 0) // 新添加的文件
        {
            for (FILE_INFO_LIST::iterator iter = newFileList_.begin(); 
                iter != newFileList_.end();
                ++iter)
            {
                iter->updateType = FileInfo::UPDATE_FILE;
                updateList.push_back(*iter);
            }
        }

        oldFileList_.clear();
        newFileList_.clear();

        return (updateList.size() ? 0 : -2);
    }

    /**
     *\fn         int CheckLocalFile(LPCTSTR rootPath, LPCTSTR oldXml, FILE_INFO_LIST &updateList)
     *\brief      校验本地文件是否正确
     *\param[in]  LPCTSTR rootPath              文件根目录
     *\param[in]  LPCTSTR oldXml                文件列表
     *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件
     *\return     是否成功,0成功,其它失败
     */
    int P2PFileOperator::CheckLocalFile(LPCTSTR rootPath, LPCTSTR oldXml, FILE_INFO_LIST &updateList)
    {
        if (NULL == rootPath || NULL == oldXml) return -1;

        TCHAR md5[MAX_PATH] = _T("");
        TCHAR size[MAX_PATH] = _T("");
        TCHAR filename[MAX_PATH] = _T("");

        UINT projectId = 0;
        FILE_INFO_LIST fileList;

        OpenFileList(oldXml, projectId, fileList);     // 得到旧的文件信息

        FILE_INFO_LIST::iterator iter = fileList.begin();

        for (; iter != fileList.end(); ++iter)
        {
            _stprintf_s(filename, ARRAYSIZE(filename), _T("%s\\%s"), rootPath, iter->name);

            if (!GetFileMd5(filename, size, ARRAYSIZE(size), md5, ARRAYSIZE(md5)) ||
                (0 != _tcscmp(md5, iter->md5)) ||
                (0 != _tcscmp(size, iter->size)))
            {
                iter->updateType = FileInfo::UPDATE_FILE;

                updateList.push_back(*iter);
            }
        }

        return (updateList.size() ? 0 : -2);
    }

    /**
     *\fn         TokenizeData(LPCTSTR srcData, LPCTSTR tokenize, VECTOR_STR &data)
     *\brief      分割字符串,例如"***|***|**"一个串，变成一个数组
     *\param[in]  srcData	原字符串。
     *\param[in]  token		分格符。
     *\param[out] data		输出数组。
     */
    void P2PFileOperator::TokenizeData(LPCTSTR srcData, LPCTSTR tokenize, VECTOR_STR &data)
    {
        if (NULL == srcData || NULL == tokenize) return;

        UINT len = _tcslen(srcData) + 1;

        TCHAR *temp = new TCHAR[len];

        _tcscpy_s(temp, len, srcData);

        LPTSTR token = NULL;

        _tcstok_s(temp, tokenize, &token);

        while (token != NULL)
        {
            data.push_back(token);

            _tcstok_s(NULL, tokenize, &token);
        }
    }

    /**
     *\fn         void MakeDirectory(LPCTSTR path)
     *\brief      创建多级目录
     *\param[in]  LPCTSTR path 路径
     *\return     无
     */
    void P2PFileOperator::MakeDirectory(LPCTSTR path)
    {
        VECTOR_STR data;

        TokenizeData(path, _T("\\"), data);

        TCHAR temp[MAX_PATH] = _T("");

        for (UINT i = 0; i < (data.size() - 1); i++)
        {
            _tcscat_s(temp, ARRAYSIZE(temp), data[i].c_str());
            _tcscat_s(temp, ARRAYSIZE(temp), _T("\\"));
            CreateDirectory(temp, NULL);
        }
    }
}