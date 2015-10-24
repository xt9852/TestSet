#pragma once
#include "Base/XTXml.h"

namespace XT_P2P
{
    typedef struct _tagFileInfo
    {
        enum
        {
            UPDATE_NULL = 0,    // 无更新
            UPDATE_PATCH,       // 更新补丁文件
            UPDATE_FILE,        // 更新整个文件
        };
    
        enum
        {
            PATCH_NULL = 0,     // 无补丁
            PATCH_COURGETTE,    // courgette补丁
            PATCH_BSDIFF,       // bsdiff补丁
        };
    
        TCHAR name[MAX_PATH];   // 文件相对路径名
        TCHAR size[20];         // 文件大小
        TCHAR md5[33];          // 文件md5串
        TCHAR zip7Size[20];     // 7z压缩后的文件大小
        TCHAR zip7Md5[33];      // 7z压缩后的文件md5串
        TCHAR patchSize[20];    // 补丁文件大小
        TCHAR patchMd5[33];     // 补丁文件md5串
        TCHAR patch7zSize[20];  // 7z压缩后的补丁文件大小
        TCHAR patch7zMd5[33];   // 7z压缩后的补丁文件md5串
        TCHAR oldSize[20];      // 旧文件大小
        TCHAR oldMd5[33];       // 旧文件md5串
        BYTE  patchType;        // 补丁类型:0-无补丁,1-courgette补丁,2-bsdiff补丁
        BYTE  updateType;       // 更新类型:0-无更新,1-更新补丁文件,2-更新整个文件
        bool  exclude;          // 是否排除此文件
    
    }FileInfo;
    
    typedef std::list<FileInfo> FILE_INFO_LIST;
    typedef std::list<std::string> STRING_LIST;
    
    class P2PFileOperator
    {
    public:
        P2PFileOperator();
        ~P2PFileOperator();
    
    protected:
        FILE_INFO_LIST localFileList_;  // 本地已有文件信息
        FILE_INFO_LIST oldFileList_;    // 旧的文件列表xml的文件信息
        FILE_INFO_LIST newFileList_;    // 新的文件列表xml的文件信息
    
        XT_XML::xml    xml_;            // xml文件解析
    
    public:
        /**
         *\fn         DWORD runProcess(LPCTSTR cmd, LPCTSTR path)
         *\brief      运行程序
         *\param[in]  LPCTSTR cmd   命令可带参数
         *\param[in]  LPCTSTR path  命令执行的默认路径
         *\return     程序退出码
         */
        int runProcess(LPCTSTR cmd, LPCTSTR path);

        /**
         *\fn         bool getFile(FILE_INFO_LIST &fileList, LPCTSTR name, FileInfo &file)
         *\brief      得到文件的信息
         *\param[in]  FILE_INFO_LIST & fileList 文件列表
         *\param[in]  LPCTSTR name              文件名
         *\param[in]  FileInfo & file           文件信息
         *\return     是否成功
         */
        bool getFile(FILE_INFO_LIST &fileList, LPCTSTR name, FileInfo &file);
        
        /**
         *\fn         void deleteFileInList(FILE_INFO_LIST &fileList, LPCTSTR name)
         *\brief      从文件列表中删除文件
         *\param[in]  FILE_INFO_LIST & fileList 文件列表
         *\param[in]  LPCTSTR name              文件名
         *\return     无
         */
        void deleteFileInList(FILE_INFO_LIST &fileList, LPCTSTR name);
    
        /**
         *\fn         GetFiles(LPCTSTR root, LPCTSTR path, FILE_INFO_LIST &files)
         *\brief      查找文件，包含子目录。
         *\param[in]  root	根目录。
         *\param[in]  path	相对目录。
         *\param[out] files	文件。
         *\return     是否成功
         */
        bool GetFiles(LPCTSTR root, LPCTSTR path, FILE_INFO_LIST &files);
    
        /**
         *\fn         GetFilesMd5(LPCTSTR rootPath, FILE_INFO_LIST &files)
         *\brief      计算文件md5。
         *\param[in]  rootPath	文件根路径。
         *\param[out] files	文件。
         *\return     是否成功
         */
        bool GetFilesMd5(LPCTSTR rootPath, FILE_INFO_LIST &files);
    
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
        bool GetFileMd5(LPCTSTR filename, LPTSTR size, UINT sizeBuffLen, LPTSTR md5, UINT md5BuffLen);
        
        /**
         *\fn         int CreateFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, LPCTSTR oldVersion, STRING_LIST &excludeFileList)
         *\brief      生成新的文件列表
         *\param[in]  UINT projectId                工程ID
         *\param[in]  LPCTSTR rootPath              根文件路径
         *\param[in]  LPCTSTR newVersion            新的版本号
         *\param[in]  LPCTSTR oldVersion            旧的版本号
         *\param[in]  STRING_LIST & excludeFileList 要排除的文件列表
         *\return     0成功,其它失败
         */
        int CreateFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, LPCTSTR oldVersion, STRING_LIST &excludeFileList);

        /**
         *\fn         int OpenFileList(LPCTSTR xml, UINT projectId, FILE_INFO_LIST &fileList)
         *\brief      解析文件列表
         *\param[in]  LPCTSTR xml               xml文件名
         *\param[in]  UINT projectId            工程ID
         *\param[in]  FILE_INFO_LIST & fileList 文件列表
         *\return     0成功,其它失败
         */
        int OpenFileList(LPCTSTR xml, UINT projectId, FILE_INFO_LIST &fileList);

        /**
         *\fn         bool CompareFile(FILE_INFO_LIST &oldFileList, FILE_INFO_LIST &newFileList)
         *\brief      比较文件，以便生成补丁文件
         *\param[in]  FILE_INFO_LIST & oldFileList 旧文件列表
         *\param[in]  FILE_INFO_LIST & newFileList 新文件列表
         *\return     是否有不同的
         */
        bool CompareFile(FILE_INFO_LIST &oldFileList, FILE_INFO_LIST &newFileList);
    
        /**
         *\fn         int CreatePatch(LPCTSTR rootPath, LPCTSTR oldVersion, LPCTSTR newVersion, FILE_INFO_PTR_LIST &fileList)
         *\brief      生成补丁文件
         *\param[in]  LPCTSTR rootPath          根路径
         *\param[in]  LPCTSTR oldVersion        旧的版本号
         *\param[in]  LPCTSTR newVersion        新的版本号
         *\param[in]  FILE_INFO_LIST & fileList 文件列表     
         *\return     0成功,其它失败
         */
        int CreatePatch(LPCTSTR rootPath, LPCTSTR oldVersion, LPCTSTR newVersion, FILE_INFO_LIST &fileList);
    
        /**
         *\fn         int CreateZip7(LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
         *\brief      生成7zip压缩文件
         *\param[in]  LPCTSTR rootPath          根路径
         *\param[in]  LPCTSTR newVersion        新版本号
         *\param[in]  FILE_INFO_LIST & fileList 文件列表
         *\return     0成功,其它失败
         */
        int CreateZip7(LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList);

        /*
         *\fn         int CreateZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR filename)
         *\brief      生成7zip压缩文件
         *\param[in]  LPCTSTR rootPath 根路径
         *\param[in]  LPCTSTR zip7 7z文件名
         *\param[in]  LPCTSTR filename 文件名
         *\return     int 0成功,其它失败
         */
        int CreateZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR filename);

        /*
         *\fn         int UncompareZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR outPath)
         *\brief      解压7zip文件
         *\param[in]  LPCTSTR rootPath 根路径
         *\param[in]  LPCTSTR zip7 文件名
         *\param[in]  LPCTSTR outPath 输出路径
         *\return     int 0成功,其它失败
         */
        int UncompareZip7(LPCTSTR rootPath, LPCTSTR zip7, LPCTSTR outPath);

        /*
         *\fn         bool canCourgette(LPCTSTR filename)
         *\brief      是否能使用courgette
         *\param[in]  LPCTSTR filename 文件名
         *\return     bool 是否能使用courgette
         */
        bool canCourgette(LPCTSTR filename);

        /**
         *\fn         int ExcludeFile(FILE_INFO_LIST &fileList, STRING_LIST &excludeFileList)
         *\brief      排队文件
         *\param[in]  FILE_INFO_LIST & fileList 文件列表
         *\param[in]  STRING_LIST & excludeFileList 需要排除的文件列表
         *\return     0成功,其它失败
         */
        int ExcludeFile(FILE_INFO_LIST &fileList, STRING_LIST &excludeFileList);
    
        /**
         *\fn         int CreateXmlFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList)
         *\brief      生成文件列表xml
         *\param[in]  UINT projectId            工程ID
         *\param[in]  LPCTSTR rootPath          根路径
         *\param[in]  LPCTSTR newVersion        新版本号
         *\param[in]  FILE_INFO_LIST & fileList 文件列表
         *\return     0成功,其它失败
         */
        int CreateXmlFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, FILE_INFO_LIST &fileList);
    
        /**
         *\fn         int GetFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, LPCTSTR oldVersion, STRING_LIST &excludeFileList)
         *\brief      生成新的文件列表
         *\param[in]  UINT projectId                工程ID
         *\param[in]  LPCTSTR rootPath              根文件路径
         *\param[in]  LPCTSTR newVersion            新的版本号
         *\param[in]  LPCTSTR oldVersion            旧的版本号
         *\param[in]  STRING_LIST & excludeFileList 要排除的文件列表
         *\return     0成功,其它失败
         */
        int GetFileList(UINT projectId, LPCTSTR rootPath, LPCTSTR newVersion, LPCTSTR oldVersion, STRING_LIST &excludeFileList);

        /**
         *\fn         int GetUpdateList(LPCTSTR rootPath, LPCTSTR newXml, LPCTSTR oldXml, FILE_INFO_LIST &updateList)
         *\brief      得到需列新的文件列表
         *\param[in]  LPCTSTR rootPath              根文件路径
         *\param[in]  LPCTSTR newXml                新的文件列表xml
         *\param[in]  LPCTSTR oldXml                旧的文件列表xml  
         *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件
         *\return     函数返回值
         */
        int GetUpdateList(LPCTSTR rootPath, LPCTSTR newXml, LPCTSTR oldXml, FILE_INFO_LIST &updateList);

        /**
         *\fn         int CheckLocalFile(LPCTSTR rootPath, LPCTSTR oldXml, FILE_INFO_LIST &updateList)
         *\brief      校验本地文件是否正确
         *\param[in]  LPCTSTR rootPath              文件根目录
         *\param[in]  LPCTSTR oldXml                文件列表
         *\param[in]  FILE_INFO_LIST & updateList   需要更新的文件
         *\return     是否成功,0成功,其它失败
         */
        int CheckLocalFile(LPCTSTR rootPath, LPCTSTR oldXml, FILE_INFO_LIST &updateList);

        /**
         *\fn         TokenizeData(LPCTSTR srcData, LPCTSTR tokenize, VECTOR_STR &data)
         *\brief      分割字符串,例如"***|***|**"一个串，变成一个数组
         *\param[in]  srcData	原字符串。
         *\param[in]  token		分格符。
         *\param[out] data		输出数组。
         */
        void TokenizeData(LPCTSTR srcData, LPCTSTR tokenize, VECTOR_STR &data);

        /**
         *\fn         void MakeDirectory(LPCTSTR path)
         *\brief      创建多级目录
         *\param[in]  LPCTSTR path 路径
         *\return     无
         */
        void MakeDirectory(LPCTSTR path);
    };
}