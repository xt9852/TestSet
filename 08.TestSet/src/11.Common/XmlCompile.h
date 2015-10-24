#pragma once
//#include "common/CXml/Xml.h"
//using namespace JWXml;


enum
{
    NAME,
    EXPLAIN,
    SELECT,
    XMLNAME,
    XMLDEFAULTVALUE,
};

typedef CArray<int, int> CARRAY_INT;

class CXmlCompile
{
public:
    CXmlCompile();
    ~CXmlCompile(void);

protected:
    CXml            m_xmlCompile;
    CXml            m_xmlVcProj;
    CString         m_strPathFile;

    CStringArray    m_arPfName;     // 平台名
    CStringArray    m_arCfgName;    // 配置名

    CStringArray    m_arPnan;       // vcproj project node attrib name
    CStringArray    m_arCnan;       // vcproj config nodes attrib name
    CStringArray    m_arTnan[12];   // vcproj tool nodes attrib name
    CStringArray    m_arToolName;   // vcproj tool nodes name
    CARRAY_INT      m_arMap;        // compile tool node name index to vcproj tool node name index

    CXmlNode        m_CpRoot;       // compile xml root node
    CXmlNode        m_CpNameSpace;
    CXmlNode        m_CpConfig;
    CXmlNode        m_CpGlobal;
    CXmlNodes       m_CpAttrib[40];
    BOOL            m_bLoadFile;

    CXmlNode        m_VpRoot;       // my open xml(vcproj) root node
    CXmlNodes       m_VpPlatform;
    CXmlNodes       m_VpConfig;
    CXmlNodes       m_VpTool;
    CXmlNode        m_VpGlobal;

public:
    BOOL OpenVcProj(CString &strFileName);
    BOOL SaveVcProj(CString &strFileName);
    BOOL CreateVcProj(CString &strFileName);    
    BOOL CreateMakeFile(CString &strFileName, int nCfg);
    BOOL CreateBatFile(void);

    // compile xml attribute
    CString GetName(int nPage, int nIndex);
    CString GetSelect(int nPage, int nIndex);
    CString GetExplain(int nPage, int nIndex);
    CString GetXmlName(int nPage, int nIndex);
    CString GetXmlValue(int nPage, int nIndex);
    void SetXmlValue(int nPage, int nIndex, CString strValue);
    int GetAttribCount(int nPage);

    //------------------------------------------------------------------------- 

    void GetTools(int nConfigIndex);    
    void GetPlatforms(CStringArray &saPlatforms);
    void GetConfigs(CStringArray &saConfigs, BOOL bFull);  
    CString GetRootAttribValue(LPCTSTR ptAttrib);
    CString GetToolAttribValue(int nToolIndex, LPCTSTR ptAttrib);
    CString GetConfigAttribValue(int nConfigIndex, LPCTSTR ptAttrib);

    //------------------------------------------------------------------------- 

    void CStringToArray(CString &strData, CStringArray &arrData);
};