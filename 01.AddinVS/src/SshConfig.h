#pragma once
#include "08.Algorithm/base/XTXml.h"
#include <map>
#include <string>


typedef struct _tagProjectInfo
{
    int serverId;
    std::string remotePath;

}ProjectInfo;

typedef std::map<std::string, ProjectInfo> ProjectInfoMap;

typedef std::map<int, int> IntIntMap;

class Config
{
public:
    Config();
    ~Config();

protected:
    bool                    load_;          // 是否已经加载了数据
    ProjectInfoMap          projectInfo_;   // 项目信息
    const char              *tempPath_;     // 临时目录

    XT_XML::xml             file_;          // XML文件
    XT_XML::TiXmlElementExs projects_;      // XML项目节点
    XT_XML::TiXmlElementExs servers_;       // XML服务器节点

public:
    /**
     *\fn        int openFile(const char *filename)
     *\brief     打开配置文件
     *\param[in] const char * filename 配置文件名
     *\return    int 0成功,其它失败
     */
    int openFile(const char *filename);

    /**
     *\fn        bool isLoad()
     *\brief     是否已经加载配置文件
     *\return    bool 是否已经加载配置文件
     */
    bool isLoad() { return load_; }

    /**
     *\fn        const char getTempPath()
     *\brief     得到临时目录
     *\return    const char 0成功,其它失败
     */
    const char * getTempPath() { return tempPath_; }

    /**
     *\fn        int getServerCount()
     *\brief     得到服务器数量
     *\return    int 服务器数量
     */
    int getServerCount() { return servers_.getCount();}

    /**
     *\fn        int getServerParam(int index, char *addr, int &port, 
                                    char *username, char *password, int &portMappingCount)
     *\brief     得到服务器参数
     *\param[in] int index 服务器ID
     *\param[out]char * addr 服务器地址
     *\param[out]int & port 服务器端口号
     *\param[out]char * username 服务器用户名
     *\param[out]char * password 服务器用户密码
     *\param[out]int & portMappingCount 端口映射数量
     *\return    int 0成功,其它失败
     */
    int getServerParam(int index, char *addr, int &port, 
        char *username, char *password, int &portMappingCount);

    /**
     *\fn        int getServerPortMap(int serverIndex, int portIndexint, &type, int &local, int &remote)
     *\brief     得到映射的端口
     *\param[in] int serverIndex 服务器ID
     *\param[in] int portIndexint 端口ID
     *\param[in] int & type 映射类型:0-本地监听连远端,1-远端监听连本地
     *\param[in] int & local 本地端口
     *\param[in] int & remote 远端端口
     *\return    int 0成功,其它失败
     */
    int getServerPortMap(int serverIndex, int portIndexint, int &type, int &local, int &remote);

    /**
     *\fn        int getServerId(const char *projectname)
     *\brief     得到项所在的服务器ID
     *\param[in] const char * projectname 项目名
     *\return    int -1失败,其它服务器ID
     */
    int getServerId(const char *projectname);

    /**
     *\fn        const char* getRemotePath(const char *projectname)
     *\brief     得到项目所在的远程地址
     *\param[in] const char * projectname 项目名
     *\return    const char* 远程地址
     */
    const char* getRemotePath(const char *projectname);
};