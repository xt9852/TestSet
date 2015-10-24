#pragma once
#include "08.Algorithm/base/XTXml.h"

typedef std::list<std::string> STRING_LIST;

class CTestSetConfig
{
public:
    CTestSetConfig();
    ~CTestSetConfig();

protected:
    XT_XML::xml             xml_;
    XT_XML::TiXmlElementEx  *setNode_;
    XT_XML::TiXmlElementEx  *glogNode_;
    XT_XML::TiXmlElementEx  *updateNode_;
    XT_XML::TiXmlElementExs updateFiles_;
    XT_XML::TiXmlElementEx  *skinNode_;
    XT_XML::TiXmlElementExs skinDir_;

public:
    bool OpenFile(LPCTSTR filename);
    bool GetCloseToMin();

    int GetUpdateNum();
    LPCTSTR GetUpdateSrv();
    LPCTSTR GetUpdateFile(UINT num);

    LPCTSTR GetCurrentSkinName();
    STRING_LIST GetSkinList();

    LPCTSTR GetGlogInfoFilename();
    LPCTSTR GetGlogErrorFilename();
    LPCTSTR GetGlogWarningFilename();
};