#include "stdafx.h"
#include "TestSetConfig.h"

#ifdef DEBUG
#pragma comment(lib,"../10.thirdParty/lib/tinyxml/tinyxmld.lib")
#else
#pragma comment(lib,"../10.thirdParty/lib/tinyxml/tinyxml.lib")
#endif

CTestSetConfig::CTestSetConfig()
    :setNode_(NULL),
    glogNode_(NULL),
    updateNode_(NULL),
    skinNode_(NULL)
{
}

CTestSetConfig::~CTestSetConfig()
{
}

bool CTestSetConfig::OpenFile(LPCTSTR filename)
{
    USES_CONVERSION;

    bool bRet = xml_.LoadFile(T2A((LPTSTR)filename));

    if (bRet)
    {
        setNode_     = xml_.GetRoot()->SelectSingleNode("Set");
        glogNode_    = xml_.GetRoot()->SelectSingleNode("Log");
        updateNode_  = xml_.GetRoot()->SelectSingleNode("Update");
        updateFiles_ = xml_.GetRoot()->SelectNodes("Update\\File");
        skinNode_    = xml_.GetRoot()->SelectSingleNode("SkinSet");
        skinDir_     = xml_.GetRoot()->SelectNodes("SkinSet\\Skin");
    }

    return (bRet && 
        (NULL != setNode_) && 
        (NULL != glogNode_) && 
        (NULL != updateNode_) &&
        (NULL != skinNode_));
}

// 得到更新文件数
// dwNum [out]
int CTestSetConfig::GetUpdateNum()
{
    int num = 0;
    updateNode_->Attribute("count", &num);
    return num;
}

// 得到更新的服务器地址
// pszSrv [out] 地址
LPCTSTR CTestSetConfig::GetUpdateSrv()
{
    USES_CONVERSION;

    return A2T((LPSTR)updateNode_->Attribute("serverURL"));
}

// 得到更新的文件名
// dwNum   [in] ID
// pszFile [out] 文件名
LPCTSTR CTestSetConfig::GetUpdateFile(UINT num)
{
    if (num >= updateFiles_.getCount()) return NULL;

    USES_CONVERSION;

    return A2T((LPSTR)updateFiles_[num]->Attribute("name"));
}

// 当关闭时是否最小化
bool CTestSetConfig::GetCloseToMin()
{
    const char *value = setNode_->Attribute("CloseToMin");

    return (0 == strcmp(value, "1"))?true:false;
}

LPCTSTR CTestSetConfig::GetGlogInfoFilename()
{
    if (NULL == glogNode_) return NULL;

    return glogNode_->Attribute("GLOG_INFO");
}

LPCTSTR CTestSetConfig::GetGlogErrorFilename()
{
    if (NULL == glogNode_) return NULL;

    return glogNode_->Attribute("GLOG_ERROR");
}

LPCTSTR CTestSetConfig::GetGlogWarningFilename()
{
    if (NULL == glogNode_) return NULL;

    return glogNode_->Attribute("GLOG_WARNING");
}

LPCTSTR CTestSetConfig::GetCurrentSkinName()
{
    if (NULL == skinNode_) return NULL;

    return skinNode_->Attribute("current");
}

STRING_LIST CTestSetConfig::GetSkinList()
{
    STRING_LIST skinList;

    for (int i = 0; i < skinDir_.getCount(); i++)
    {
        skinList.push_back(skinDir_[i]->Attribute("name"));
    }

    return skinList;
}

