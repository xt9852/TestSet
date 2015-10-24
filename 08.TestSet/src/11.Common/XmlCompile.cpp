#include "stdafx.h"
#include "XmlCompile.h"
#include "../../resource.h"


CXmlCompile::CXmlCompile()
:m_bLoadFile(FALSE)
{
    // C/C++
    m_arTnan[0].Add(_T("AdditionalIncludeDirectories|AdditionalUsingDirectories|DebugInformationFormat|SuppressStartupBanner|WarningLevel|Detect64BitPortabilityProblems|WarnAsError|UseUnicodeResponseFiles"));
    m_arTnan[0].Add(_T("Optimization|InlineFunctionExpansion|EnableIntrinsicFunctions|FavorSizeOrSpeed|OmitFramePointers|EnableFiberSafeOptimizations|WholeProgramOptimization"));
    m_arTnan[0].Add(_T("PreprocessorDefinitions|IgnoreStandardIncludePath|GeneratePreprocessedFile|KeepComments"));
    m_arTnan[0].Add(_T("StringPooling|MinimalRebuild|ExceptionHandling|SmallerTypeCheck|BasicRuntimeChecks|RuntimeLibrary|StructMemberAlignment|BufferSecurityCheck|EnableFunctionLevelLinking|EnableEnhancedInstructionSet|FloatingPointModel|FloatingPointExceptions"));
    m_arTnan[0].Add(_T("DisableLanguageExtensions|DefaultCharIsUnsigned|TreatWChar_tAsBuiltInType|ForceConformanceInForLoopScope|RuntimeTypeInfo|OpenMP"));
    m_arTnan[0].Add(_T("UsePrecompiledHeader|PrecompiledHeaderThrough|PrecompiledHeaderFile"));
    m_arTnan[0].Add(_T("ExpandAttributedSource|AssemblerOutput|AssemblerListingLocation|ObjectFile|ProgramDataBaseFileName|GenerateXMLDocumentationFiles|XMLDocumentationFileName"));
    m_arTnan[0].Add(_T("BrowseInformation|BrowseInformationFile"));
    m_arTnan[0].Add(_T("CallingConvention|CompileAs|DisableSpecificWarnings|ForcedIncludeFiles|ForcedUsingFiles|ShowIncludes|UndefinePreprocessorDefinitions|UndefineAllPreprocessorDefinitions|UseFullPaths|OmitDefaultLibName|ErrorReporting"));
    m_arTnan[0].Add(_T("AdditionalOptions"));
    // 链接器
    m_arTnan[1].Add(_T("OutputFile|ShowProgress|Version|LinkIncremental|SuppressStartupBanner|IgnoreImportLibrary|RegisterOutput|AdditionalLibraryDirectories|LinkLibraryDependencies|UseLibraryDependencyInputs|UseUnicodeResponseFiles"));
    m_arTnan[1].Add(_T("AdditionalDependencies|IgnoreAllDefaultLibraries|IgnoreDefaultLibraryNames|ModuleDefinitionFile|AddModuleNamesToAssembly|EmbedManagedResourceFile|ForceSymbolReferences|DelayLoadDLLs|AssemblyLinkResource"));
    m_arTnan[1].Add(_T("GenerateManifest|ManifestFile|AdditionalManifestDependencies|AllowIsolation"));
    m_arTnan[1].Add(_T("GenerateDebugInformation|ProgramDatabaseFile|StripPrivateSymbols|GenerateMapFile|MapFileName|MapExports|AssemblyDebug"));
    m_arTnan[1].Add(_T("SubSystem|HeapReserveSize|HeapCommitSize|StackReserveSize|StackCommitSize|LargeAddressAware|TerminalServerAware|SwapRunFromCD|SwapRunFromNet|Driver"));
    m_arTnan[1].Add(_T("OptimizeReferences|EnableCOMDATFolding|OptimizeForWindows98|FunctionOrder|ProfileGuidedDatabase|LinkTimeCodeGeneration"));
    m_arTnan[1].Add(_T("MidlCommandFile|IgnoreEmbeddedIDL|MergedIDLBaseFileName|TypeLibraryFile|TypeLibraryResourceID"));
    m_arTnan[1].Add(_T("EntryPointSymbol|ResourceOnlyDLL|SetChecksum|BaseAddress|FixedBaseAddress|TurnOffAssemblyGeneration|SupportUnloadOfDelayLoadedDLL|ImportLibrary|MergeSections|TargetMachine|Profile|CLRThreadAttribute|CLRImageType|KeyFile|KeyContainer|DelaySign|ErrorReporting|CLRUnmanagedCodeCheck"));
    m_arTnan[1].Add(_T("AdditionalOptions"));
    // 清单工具
    m_arTnan[2].Add(_T("SuppressStartupBanner|VerboseOutput|AssemblyIdentity|UseUnicodeResponseFiles|UseFAT32Workaround"));
    m_arTnan[2].Add(_T("AdditionalManifestFiles|InputResourceManifests|EmbedManifest|OutputManifestFile|ManifestResourceFile|GenerateCatalogFiles|DependencyInformationFile"));
    m_arTnan[2].Add(_T("TypeLibraryFile|RegistrarScriptFile|ComponentFileName|ReplacementsFile"));
    m_arTnan[2].Add(_T("UpdateFileHashes|UpdateFileHashesSearchPath"));
    m_arTnan[2].Add(_T("AdditionalOptions"));
    // 资源
    m_arTnan[3].Add(_T("PreprocessorDefinitions|Culture|AdditionalIncludeDirectories|IgnoreStandardIncludePath|ShowProgress|ResourceOutputFileName"));
    m_arTnan[3].Add(_T("AdditionalOptions"));
    // XML文档生成
    m_arTnan[4].Add(_T("SuppressStartupBanner|ValidateIntelliSense|AdditionalDocumentFiles|OutputDocumentFile||UseUnicodeResponseFiles"));
    m_arTnan[4].Add(_T("AdditionalOptions"));
    // 浏览信息
    m_arTnan[5].Add(_T("SuppressStartupBanner|OutputFile"));
    m_arTnan[5].Add(_T("AdditionalOptions"));
    // 预生成事件
    m_arTnan[6].Add(_T("CommandLine|Description|ExcludedFromBuild"));
    // 预链接事件
    m_arTnan[7].Add(_T("CommandLine|Description|ExcludedFromBuild"));
    // 生成后事件
    m_arTnan[8].Add(_T("CommandLine|Description|ExcludedFromBuild"));
    // 自定义生成步骤
    m_arTnan[9].Add(_T("CommandLine|Description|Outputs|AdditionalDependencies"));
    // WEB部署
    m_arTnan[10].Add(_T("VirtualDirectoryName|ApplicationMappings|ApplicationProtection|ExcludedFromBuild|RelativePath|AdditionalFiles|UnloadBeforeCopy|RegisterOutput"));

    CString strProjAttrib = _T("ProjectType|Version|Name|ProjectGUID|RootNamespace|Keyword|TargetFrameworkVersion|AssemblyReferenceSearchPaths");
    CString strCfgAttrib = _T("OutputDirectory|IntermediateDirectory|DeleteExtensionsOnClean|BuildLogFile|ConfigurationType|UseOfMFC|UseOfATL|ATLMinimizesCRunTimeLibraryUsage|CharacterSet|ManagedExtensions|WholeProgramOptimization");
    CString strToolName = _T("VCCLCompilerTool|VCLinkerTool|VCManifestTool|VCResourceCompilerTool|VCXDCMakeTool|VCBscMakeTool|VCPreBuildEventTool|VCPreLinkEventTool|VCPostBuildEventTool|VCCustomBuildTool|VCWebDeploymentTool");

    this->CStringToArray(strProjAttrib, m_arPnan);
    this->CStringToArray(strCfgAttrib, m_arCnan);
    this->CStringToArray(strToolName, m_arToolName);
    m_arMap.SetSize(m_arToolName.GetCount());

    //------------------------------------------------------------------------------------------------

    HINSTANCE hInstance  = AfxGetResourceHandle();
    HRSRC hResCompile = ::FindResource(hInstance, MAKEINTRESOURCE(IDR_COMPILE_XML_COMPILE), _T("XML"));
    char *pszData = (char*)LoadResource(hInstance, (HRSRC)hResCompile); // 在资源的后面加了'\0'

    if (m_xmlCompile.LoadXml(pszData))
    {
        m_CpRoot = m_xmlCompile.GetRoot();
        m_CpNameSpace = m_CpRoot.SelectSingleNode(_T("NameSpace"));
        m_CpConfig = m_CpRoot.SelectSingleNode(_T("Configurations//Configuration"));
        m_CpGlobal = m_CpRoot.SelectSingleNode(_T("Globals//Global"));

        int nIndex = 0;
        m_CpAttrib[nIndex++] = m_CpNameSpace.SelectNodes(_T("Attribute"));          // 0
        m_CpAttrib[nIndex++] = m_CpRoot.SelectNodes(_T("Attribute"));               // 1
        m_CpAttrib[nIndex++] = m_CpConfig.SelectNodes(_T("Attribute"));             // 2

        CXmlNode TempNode = m_CpConfig.SelectSingleNode(_T("VCCLCompilerTool"));    // 3
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Common//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Optimization//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Preprocessor//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Build//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Language//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Precompiled//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Output//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Browse//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Advanced//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("CommandLine//Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCLinkerTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Common//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Input//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Manifest//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Debug//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("System//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Optimize//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("EmbeddedIDL//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Advanced//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("CommandLine//Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCManifestTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Common//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("InputOutput//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("COM//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Advanced//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("CommandLine//Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCResourceCompilerTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Common//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("CommandLine//Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCXDCMakeTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Common//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("CommandLine//Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCBscMakeTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Common//Attribute"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("CommandLine//Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCPreBuildEventTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCPreLinkEventTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCPostBuildEventTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCCustomBuildTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Attribute"));

        TempNode = m_CpConfig.SelectSingleNode(_T("VCWebDeploymentTool"));
        m_CpAttrib[nIndex++] = TempNode.SelectNodes(_T("Attribute"));

        TRACE(_T("加载XML资源成功\n"));
    }
    else
    {
        TRACE(_T("加载XML资源不成功(%d)\n"), ::GetLastError());
    }
}

CXmlCompile::~CXmlCompile()
{
}

// 打开VC项目文件*.vcproj
// strFileName [IN] 文件名
BOOL CXmlCompile::OpenVcProj(CString &strFileName)
{
    m_xmlVcProj.Close();

    if (m_xmlVcProj.Open(strFileName))
    {
        m_strPathFile = strFileName;
        m_VpRoot = m_xmlVcProj.GetRoot();
        m_VpPlatform = m_VpRoot.SelectNodes(_T("Platforms//Platform"));
        m_VpConfig = m_VpRoot.SelectNodes(_T("Configurations//Configuration"));
        m_VpGlobal = m_VpRoot.SelectSingleNode(_T("Globals//Global"));

        //----------------------------------------------------------------------------------------------
        // set platform node name

        CStringArray arTemp;
        CString strTemp = m_CpAttrib[0][(LONG)0]->GetAttribute(_T("XmlValue"));   // 平台名

        this->GetPlatforms(m_arPfName);

        for (int i = 0; i < m_arPfName.GetCount(); i++)
        {
            strTemp += _T("|") + m_arPfName[i];
        }

        m_CpAttrib[0][(LONG)0]->SetAttribute(_T("XmlValue"), strTemp);    // 写入新的平台名

        //----------------------------------------------------------------------------------------------
        // set config node name

        strTemp = m_CpAttrib[0][1]->GetAttribute(_T("XmlValue"));   // 配置名

        this->GetConfigs(m_arCfgName, FALSE);

        for (int i = 0; i < m_arCfgName.GetCount(); i++)
        {
            strTemp += _T("|") + m_arCfgName[i];
        }

        m_CpAttrib[0][1]->SetAttribute(_T("XmlValue"), strTemp);    // 写入新配置名

        //----------------------------------------------------------------------------------------------
        // set project node attribute value

        for (int i = 0; i < m_arPnan.GetCount(); i++)
        {
            strTemp = this->GetRootAttribValue(m_arPnan[i]);
            if (_T("") == strTemp) strTemp = _T(" ");

            strTemp = m_CpAttrib[1][i]->GetAttribute(_T("XmlValue")) + _T("|") + strTemp;
            m_CpAttrib[1][i]->SetAttribute(_T("XmlValue"), strTemp);
        }

        //----------------------------------------------------------------------------------------------

        for (int i = 0; i < m_VpConfig.GetCount(); i++)
        {
            this->GetTools(i);  // get tool nodes

            //----------------------------------------------------------------------------------------------

            //TRACE(_T("ConfigIndex:%d NodeCount:%d StrCount:%d\n"), i, m_CpAttrib[2].GetCount(), m_arCnan.GetCount());

            for (int j = 0; j < m_arCnan.GetCount(); j++)
            {
                strTemp = this->GetConfigAttribValue(i, m_arCnan[j]);
                if (_T("") == strTemp) strTemp = _T(" ");

                strTemp = m_CpAttrib[2][j]->GetAttribute(_T("XmlValue")) + _T("|") + strTemp;
                m_CpAttrib[2][j]->SetAttribute(_T("XmlValue"), strTemp);
            }

            // set tool nodes attribute values

            int nIndex = 0;
            for (int j = 0; j < m_arToolName.GetCount(); j++)
            {
                for (int k = 0; k < m_arTnan[j].GetCount(); k++)
                {
                    this->CStringToArray(m_arTnan[j][k], arTemp);

                    //TRACE(_T("ToolIndex:%d SubIndex:%d NodeCount:%d StrCount:%d\n"),
                    //    j, k,
                    //    m_CpAttrib[3+nIndex+k].GetCount(),
                    //    arTemp.GetCount());

                    for (int l = 0; l < arTemp.GetCount(); l++)
                    {
                        strTemp = this->GetToolAttribValue(j, arTemp[l]);
                        if (_T("") == strTemp) strTemp = _T(" ");

                        strTemp = m_CpAttrib[3+nIndex+k][l]->GetAttribute(_T("XmlValue")) + _T("|") + strTemp;
                        m_CpAttrib[3+nIndex+k][l]->SetAttribute(_T("XmlValue"), strTemp);
                        
                        // TRACE(_T("->%d %s=%s %s\n"), l,
                        // m_CpAttrib[3+nIndex+k][l]->GetAttribute(_T("XmlName")),
                        // strTemp,
                        // m_CpAttrib[3+nIndex+k][l]->GetAttribute(_T("Select")));
                    }
                }

                nIndex += (int)m_arTnan[j].GetCount();
                //TRACE(_T("nIndex:%d\n"), nIndex);
            }
        }

        //----------------------------------------------------------------------------------------------

        m_CpGlobal.SetAttribute(_T("Value"), m_VpGlobal.GetAttribute(_T("Value")));

        //----------------------------------------------------------------------------------------------

        m_xmlVcProj.Close();

        //----------------------------------------------------------------------------------------------
        m_xmlCompile.Save(_T("out.xml"));
        //----------------------------------------------------------------------------------------------
 
        m_bLoadFile = TRUE;
    }
    else
    {
        m_bLoadFile = FALSE;
    }

    return m_bLoadFile;
}

// 创建VCPROJ文件
BOOL CXmlCompile::CreateVcProj(CString &strFileName)
{
    m_xmlVcProj.Close();

    CString strXML = _T("<?xml version=\"1.0\" encoding=\"gb2312\"?>\
<VisualStudioProject>\
<Platforms/>\
<ToolFiles/>\
<Configurations/>\
<References/>\
<Files/>\
<Globals>\
    <Global Name=\"RESOURCE_FILE\" Value=\"\" />\
</Globals>\
</VisualStudioProject>");

    if (m_xmlVcProj.LoadXml(strXML))
    {
        CStringArray arPlatform;
        CStringArray arAttrib;
        CStringArray arTemp;
        CString strTemp;

        m_VpRoot = m_xmlVcProj.GetRoot();
        m_VpPlatform = m_VpRoot.SelectNodes(_T("Platforms"));
        m_VpConfig = m_VpRoot.SelectNodes(_T("Configurations"));
        m_VpGlobal = m_VpRoot.SelectSingleNode(_T("Globals//Global"));

        //---------------------------------------------------------------

        strTemp = m_CpAttrib[0][(LONG)0]->GetAttribute(_T("XmlValue"), strTemp);    // 平台名
        this->CStringToArray(strTemp, arPlatform);

        strTemp = m_CpAttrib[0][(LONG)1]->GetAttribute(_T("XmlValue"), strTemp);    // 配置名
        this->CStringToArray(strTemp, arTemp);

        for (int i = 1; i < arPlatform.GetCount(); i++)
        {
            m_VpPlatform[(LONG)0]->NewChild(_T("Platform"))->SetAttribute(_T("Name"), arPlatform[i]);   // 设置平台

            for (int j = 1; j < arTemp.GetCount(); j++)
            {
                CXmlNode NewCfg = m_VpConfig[(LONG)0]->NewChild(_T("Configuration"));
                NewCfg.SetAttribute(_T("Name"), arTemp[j]+_T("|")+arPlatform[i]);

                for (int k = 0; k < m_arToolName.GetCount(); k++)
                {
                    NewCfg.NewChild(_T("Tool"))->SetAttribute(_T("Name"), m_arToolName[k]);
                }
            }
        }

        m_VpPlatform = m_VpRoot.SelectNodes(_T("Platforms//Platform"));
        m_VpConfig = m_VpRoot.SelectNodes(_T("Configurations//Configuration"));

        //---------------------------------------------------------------

        for (int i = 0; i < m_arPnan.GetCount(); i++)
        {
            strTemp = m_CpAttrib[1][i]->GetAttribute(_T("XmlValue"));
            this->CStringToArray(strTemp, arTemp);

            if (_T(" ") != arTemp[m_bLoadFile])
            {
                m_VpRoot.SetAttribute(m_arPnan[i], arTemp[m_bLoadFile]);
            }
        }

        //---------------------------------------------------------------

        for (int i = 0; i < m_VpConfig.GetCount(); i++)
        {
            for (int j = 0; j < m_arCnan.GetCount(); j++)   // 配置属性
            {
                strTemp = m_CpAttrib[2][j]->GetAttribute(_T("XmlValue"));
                this->CStringToArray(strTemp, arTemp);

                if (_T(" ") != arTemp[i+m_bLoadFile])
                {
                    m_VpConfig[i]->SetAttribute(m_arCnan[j], arTemp[i+m_bLoadFile]);
                }
            }

            this->GetTools(i);

            int nIndex = 0;

            for (int j = 0; j < m_arToolName.GetCount(); j++)
            {
                for (int k = 0; k < m_arTnan[j].GetCount(); k++)    // 工具属性
                {
                    this->CStringToArray(m_arTnan[j][k], arAttrib);

                    //TRACE(_T("ToolIndex:%d SubIndex:%d NodeCount:%d StrCount:%d\n"),
                    //    j, k,
                    //    m_CpAttrib[3+nIndex+k].GetCount(),
                    //    arAttrib.GetCount());

                    for (int l = 0; l < arAttrib.GetCount(); l++)
                    {
                        strTemp = m_CpAttrib[3+nIndex+k][l]->GetAttribute(_T("XmlValue"));
                        this->CStringToArray(strTemp, arTemp);

                        if (_T(" ") != arTemp[i+1])
                        {
                            m_VpTool[j]->SetAttribute(arAttrib[l], arTemp[i+m_bLoadFile]);
                        }
                        // TRACE(_T("->%d %s=%s\n"), l, m_CpAttrib[3+nIndex+k][l]->GetAttribute(_T("XmlName")), strTemp);
                    }
                }

                nIndex += (int)m_arTnan[j].GetCount();
                //TRACE(_T("nIndex:%d\n"), nIndex);
            }
        }

        //---------------------------------------------------------------

        m_VpGlobal.SetAttribute(_T("Value"), m_CpGlobal.GetAttribute(_T("Value")));

        m_xmlVcProj.Save(strFileName);
    }
    else
    {
        TRACE(_T("加载XML资源不成功(%d)\n"), ::GetLastError());
    }

    return FALSE;
}

// 保存VCPROJ文件
BOOL CXmlCompile::SaveVcProj(CString &strFileName)
{
    return m_xmlVcProj.Save(m_strPathFile);
}

// 创建MAKE文件
BOOL CXmlCompile::CreateMakeFile(CString &strFileName, int nCfg)
{
    // /Od /I "./src" /I "./" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_MBCS" /Gm /EHsc /RTC1 /MTd /Zc:wchar_t /Yu"stdafx.h" /Fp"Debug/TestSet.pch" /Fo"Debug/" /Fd"Debug/vc70.pdb" /W3 /c /Wp64 /ZI /TP
    // /Od /I "./src" /I "./" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_MBCS" /Gm /EHsc /RTC1 /MTd /Zc:wchar_t /Fo"Debug/" /Fd"Debug/vc70.pdb" /W3 /c /Wp64 /ZI /TC

    /*
    int i = nCfg;

    m_VpConfig[i]

    for (int j = 0; j < m_arCnan.GetCount(); j++)
    {
        strTemp = m_CpAttrib[2][j]->GetAttribute(_T("XmlValue"));
        this->CStringToArray(strTemp, arTemp);

        if (_T(" ") != arTemp[i+1])
        {
            m_VpConfig[i]->SetAttribute(m_arCnan[j], arTemp[i+1]);
        }
    }

    this->GetTools(i);

    int nIndex = 0;

    for (int j = 0; j < m_arToolName.GetCount(); j++)
    {
        for (int k = 0; k < m_arTnan[j].GetCount(); k++)
        {
            this->CStringToArray(m_arTnan[j][k], arAttrib);

            //TRACE(_T("ToolIndex:%d SubIndex:%d NodeCount:%d StrCount:%d\n"),
            //    j, k,
            //    m_CpAttrib[3+nIndex+k].GetCount(),
            //    arAttrib.GetCount());

            for (int l = 0; l < arAttrib.GetCount(); l++)
            {
                strTemp = m_CpAttrib[3+nIndex+k][l]->GetAttribute(_T("XmlValue"));
                this->CStringToArray(strTemp, arTemp);

                if (_T(" ") != arTemp[i+1])
                {
                    m_VpTool[j]->SetAttribute(arAttrib[l], arTemp[i+1]);
                }
                // TRACE(_T("->%d %s=%s\n"), l, m_CpAttrib[3+nIndex+k][l]->GetAttribute(_T("XmlName")), strTemp);
            }
        }

        nIndex += (int)m_arTnan[j].GetCount();
        //TRACE(_T("nIndex:%d\n"), nIndex);
    }
*/

    return TRUE;
}

int CXmlCompile::CreateBatFile(void)
{
    return 0;
}

// 得到这一页中的属性个数
int CXmlCompile::GetAttribCount(int nPage)
{
    return m_CpAttrib[nPage].GetCount();
}

// 得到Name属性
CString CXmlCompile::GetName(int nPage, int nIndex)
{
    return m_CpAttrib[nPage][nIndex]->GetAttribute(_T("Name"));
}

// 得到Select属性
CString CXmlCompile::GetSelect(int nPage, int nIndex)
{
    return m_CpAttrib[nPage][nIndex]->GetAttribute(_T("Select"));
}

// 得到Explain属性
CString CXmlCompile::GetExplain(int nPage, int nIndex)
{
    return m_CpAttrib[nPage][nIndex]->GetAttribute(_T("Explain"));
}

// 得到XmlName属性
CString CXmlCompile::GetXmlName(int nPage, int nIndex)
{
    return m_CpAttrib[nPage][nIndex]->GetAttribute(_T("XmlName"));
}

// 得到XmlValue属性
CString CXmlCompile::GetXmlValue(int nPage, int nIndex)
{
    return m_CpAttrib[nPage][nIndex]->GetAttribute(_T("XmlValue"));
}

// 得到XmlValue属性
void CXmlCompile::SetXmlValue(int nPage, int nIndex, CString strValue)
{
    m_CpAttrib[nPage][nIndex]->SetAttribute(_T("XmlValue"), strValue);
}

// 从"***|***|**"一个串，变成一个数组
// strData [IN]  输入串
// arrData [OUT] 输出数组
void CXmlCompile::CStringToArray(CString &strData, CStringArray &arrData)
{
    int nStart = 0;

    arrData.RemoveAll();

    for (int i = 0; nStart != -1; i++)
    {
        CString strItem = strData.Tokenize(_T("|"), nStart);

        if (-1 != nStart)
        {
            arrData.Add(strItem);
            //TRACE(_T("%d %s\n"), i, strItem);
        }
    }

    //TRACE(_T("count:%d\n"), arrData.GetCount());
}

// 得到根属性值
// ptAttrib [IN] 属性名
CString CXmlCompile::GetRootAttribValue(LPCTSTR ptAttrib)
{
    return m_VpRoot.GetAttribute(ptAttrib);
}

// 得到配置节点属性值
// nConfigIndex [IN] 配置序号
// ptAttrib     [IN] 属性名
CString CXmlCompile::GetConfigAttribValue(int nConfigIndex, LPCTSTR ptAttrib)
{
    return m_VpConfig[nConfigIndex]->GetAttribute(ptAttrib);
}

// 得到Tool节点属性值
// nNodeIndex [IN] Tool节点序号
// ptAttrib   [IN] 属性名
CString CXmlCompile::GetToolAttribValue(int nToolIndex, LPCTSTR ptAttrib)
{
    return m_VpTool[m_arMap[nToolIndex]]->GetAttribute(ptAttrib);
}

// 得到平台名
void CXmlCompile::GetPlatforms(CStringArray &saPlatforms)
{
    saPlatforms.RemoveAll();

    for (int i = 0; i < m_VpPlatform.GetCount(); i++)
    {
        saPlatforms.Add(m_VpPlatform[i]->GetAttribute(_T("Name")));
    }
}

// 得到配置名
void CXmlCompile::GetConfigs(CStringArray &saConfigs, BOOL bFull)
{
    BOOL bFind = FALSE;
    CString strTemp;

    saConfigs.RemoveAll();

    for (int i = 0; i < m_VpConfig.GetCount(); i++)
    {
        strTemp = m_VpConfig[i]->GetAttribute(_T("Name"));

        if (!bFull)
        {
            int nIndex = strTemp.Find(_T("|"));
            if (-1 != nIndex)
            {
                strTemp.Delete(nIndex, strTemp.GetLength());
            }

            bFind = FALSE;
            int nCount = (int)saConfigs.GetCount();
            for (int i = 0; i < nCount; i++)
            {
                if (0 == saConfigs[i].Compare(strTemp))
                {
                    bFind = TRUE;
                    break;
                }
            }

            if (!bFind)
            {
                saConfigs.Add(strTemp);
            }
        }
        else
        {
            saConfigs.Add(strTemp);
        }
    }
}

// 得到Tool节点
void CXmlCompile::GetTools(int nConfigIndex)
{
    CString strValue;
    m_VpTool = m_VpConfig[nConfigIndex]->SelectNodes(_T("Tool"));

    for (int i = 0; i < m_arToolName.GetCount(); i++)
    {
        for (int j = 0; j < m_VpTool.GetCount(); j++)
        {
            if (m_VpTool[j]->GetAttribute(_T("Name")) == m_arToolName[i])
            {
                m_arMap[i] = j;
                //TRACE(_T("ToolMap %d->%d\n"), i, j);
                break;
            }
        }
    }
}