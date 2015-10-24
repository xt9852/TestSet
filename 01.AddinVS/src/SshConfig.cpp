#include "stdafx.h"
#include "SshConfig.h"


Config::Config()
    :load_(false),
    tempPath_(NULL)
{
}

Config::~Config()
{
}

/**
 *\fn        int openFile(const char *filename)
 *\brief     打开配置文件
 *\param[in] const char * filename 配置文件名
 *\return    int 0成功,其它失败
 */
int Config::openFile(const char *filename)
{
    if (NULL == filename) return false;

    FILE *file = NULL;

    fopen_s(&file, filename, "rb");
    load_ = file_.LoadFile(file);
    //load_ = file_.LoadFile(filename); 内部fseek出错

    if (load_)
    {
        servers_ = file_.GetRoot()->SelectNodes("server");
        projects_ = file_.GetRoot()->SelectNodes("project");

        XT_XML::TiXmlElementEx *temp = file_.GetRoot()->SelectSingleNode("temp");

        tempPath_ = (NULL != temp) ? temp->Attribute("path") : "./temp";

        for (int i = 0; i < projects_.getCount(); i++)
        {
            ProjectInfo info;
            info.remotePath = projects_[i]->Attribute("remotePath");
            projects_[i]->Attribute("serverId", &info.serverId);

            projectInfo_[projects_[i]->Attribute("name")] = info;
        }
    }

    fclose(file);

    return load_;
}

/**
 *\fn        const char* getRemotePath(const char *projectname)
 *\brief     得到项目所在的远程地址
 *\param[in] const char * projectname 项目名
 *\return    const char* 远程地址
 */
const char* Config::getRemotePath(const char *projectname)
{
    if (NULL == projectname) return NULL;

    ProjectInfoMap::const_iterator iter = projectInfo_.find(projectname);

    if (iter != projectInfo_.end())
    {
        return iter->second.remotePath.c_str();
    }

    return NULL;
}

/**
 *\fn        int getServerId(const char *projectname)
 *\brief     得到项所在的服务器ID
 *\param[in] const char * projectname 项目名
 *\return    int -1失败,其它服务器ID
 */
int Config::getServerId(const char *projectname)
{
    if (NULL == projectname) return -1;

    ProjectInfoMap::const_iterator iter = projectInfo_.find(projectname);

    if (iter != projectInfo_.end())
    {
        return iter->second.serverId;
    }

    return -1;
}

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
int Config::getServerParam(int index, char *addr, int &port, 
    char *username, char *password, int &portMappingCount)
{
    if (NULL == addr || index >= servers_.getCount()) return -1;

    servers_[index]->Attribute("port", (int*)&port);
    strcpy_s(addr,     32, servers_[index]->Attribute("addr"));
    strcpy_s(username, 32, servers_[index]->Attribute("username"));
    strcpy_s(password, 32, servers_[index]->Attribute("password"));

    portMappingCount = servers_[index]->SelectNodes("port").getCount();

    return 0;
}

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
int Config::getServerPortMap(int serverIndex, int portIndexint, int &type, int &local, int &remote)
{
    XT_XML::TiXmlElementExs ports;

    if (serverIndex < 0 || serverIndex >= servers_.getCount()) return -1;

    ports = servers_[serverIndex]->SelectNodes("port");

    if (portIndexint < 0 || portIndexint >= ports.getCount()) return -2;

    ports[portIndexint]->Attribute("type", (int*)&type);
    ports[portIndexint]->Attribute("local", (int*)&local);
    ports[portIndexint]->Attribute("remote", (int*)&remote);

    return 0;
}

