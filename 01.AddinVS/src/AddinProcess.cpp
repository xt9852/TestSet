
#include "stdafx.h"
#include "AddinProcess.h"


// m_pDTE->ExecuteCommand(CComBSTR(L"Edit.Copy"),CComBSTR(L""));

// CommandBar -> CommandBarControls -> CommandBarControls
// 命令条        菜单                  菜单项

CAddinProcess::CAddinProcess()
    :m_bInit(false)
{
}


CAddinProcess::~CAddinProcess()
{
}

/**
 *\fn           int Init(CComPtr<DTE2> pDTE, CComPtr<AddIn> pAddInInstance, CAddInModule *pAtlModule)
 *\brief        初使化插件
 *\param[in]    CComPtr<DTE2> pDTE VS开发环境指针
 *\param[in]    CComPtr<AddIn> pAddInInstance 实例指针
 *\param[in]    CAddInModule * pAtlModule 模块指针
 *\return       int 0成功,其它失败
 */
int CAddinProcess::Init(CComPtr<DTE2> pDTE, CComPtr<AddIn> pAddInInstance, CAddInModule *pAtlModule)
{
    if (!m_bInit)
    {
        CComPtr<IDispatch> pDisp;

        m_pDTE = pDTE;
        m_pAddInInstance = pAddInInstance;
        m_pAtlModule = pAtlModule;

        m_pDTE->get_Solution(&m_pSolution);
        m_pDTE->get_Documents(&m_pDocs);
        m_pDTE->get_Windows(&m_pWindows);
        m_pDTE->get_Commands(&m_pCommands);
        m_pDTE->get_ItemOperations(&m_pOperations);
        m_pDTE->get_SelectedItems(&m_pSelectedItems);
        m_pDTE->get_StatusBar(&m_pStatusBar);
        m_pDTE->get_Events(&m_pEvents);
        m_pDTE->get_CommandBars(&pDisp);

        m_pEvents->get_DocumentEvents(NULL, &m_pDocEvents);

        m_pSolution->get_Projects(&m_pProjects);

        m_pCommandBars = pDisp;

        m_pCommands2 = m_pCommands;

        if ((NULL == m_pDTE) || 
            (NULL == m_pAddInInstance) || 
            (NULL == m_pAtlModule) || 
            (NULL == m_pDocs) || 
            (NULL == m_pOperations) || 
            (NULL == m_pWindows) || 
            (NULL == m_pCommandBars))
        {
            return -1;
        }

        m_bInit = true;
    }

    return 0;
}

/**
 *\fn           std::string BstrToStr(BSTR bstr)
 *\brief        将BSTR转成GBGB2312
 *\param[in]    BSTR bstr 
 *\return       std::string
 */
std::string CAddinProcess::BstrToStr(BSTR bstr)
{
    char *pszStr = _com_util::ConvertBSTRToString(bstr);
    std::string str = pszStr;
    delete pszStr;

    return str;
}

/**
 *\fn           std::string CLSIDToProgID(const char *clsid)
 *\brief        将CLSID转成类名,CLSID例:{2D7E0F8F-3215-11D0-BF28-0000E8D0D146}
 *\param[in]    const char * clsid 
 *\return       std::string 类名
 */
std::string CAddinProcess::CLSIDToProgID(const char *clsid)
{
    if (NULL == clsid) return "";

    USES_CONVERSION;
    CLSID clsid_data = {0};
    OLECHAR clsid_wstr[100] = {0};
    LPOLESTR prog_id = NULL;

    wcscpy(clsid_wstr, CT2OLE(clsid));

    HRESULT hr = CLSIDFromString(clsid_wstr, &clsid_data);

    if (FAILED(hr)) return "";

    hr = ProgIDFromCLSID(clsid_data, &prog_id);

    if (FAILED(hr)) return "";

    LPCTSTR lpstr =  OLE2CT(prog_id);

    std::string out(lpstr);

    IMalloc * pMalloc = NULL;

    hr = ::CoGetMalloc(1, &pMalloc);   // 取得 IMalloc

    if (SUCCEEDED(hr))
    {
        pMalloc->Free(prog_id);        // 释放ProgID内存
        pMalloc->Release();            // 释放IMalloc
    }

    return out;
}

/**
 *\fn           HRESULT GetActiveWnd(Window **ppWnd)
 *\brief        得到当前的窗体
 *\param[out]    Window * * ppWnd 窗体
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetActiveWnd(Window **ppWnd)
{
    return m_pDTE->get_ActiveWindow(ppWnd);
}

/**
 *\fn           HRESULT GetActiveDoc(Document **ppDoc)
 *\brief        得到当前的文档
 *\param[out]   Document * * ppDoc 文档
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetActiveDoc(Document **ppDoc)
{
    return m_pDTE->get_ActiveDocument(ppDoc);
}

/**
 *\fn           std::string GetSolutionFilename()
 *\brief        得到解决方案名称
 *\return       std::string 解决方案名称
 */
std::string CAddinProcess::GetSolutionFilename()
{
    BSTR bstrName;
    m_pSolution->get_FullName(&bstrName);

    return BstrToStr(bstrName);
}

/**
 *\fn           HRESULT GetWndSelection(Window *pWnd, TextSelection **ppSelection)
 *\brief        得到窗体的选择区
 *\n            执行完此函数应该加一句 pTextSel = pDisp;
 *\n            CComPtr<TextSelection> pTextSel;
 *\param[in]    Window * pWnd 
 *\param[in]    TextSelection * * ppSelection 
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetWndSelection(Window *pWnd, TextSelection **ppSelection)
{
    if (NULL == pWnd) return E_INVALIDARG;

    CComPtr<Document> pDoc;
    HRESULT hr = pWnd->get_Document(&pDoc);

    if (NULL == pDoc) return E_INVALIDARG;

    CComPtr<IDispatch> pDisp;
    hr = pDoc->get_Selection(&pDisp);

    if (FAILED(hr)) return E_INVALIDARG;

    CComPtr<TextSelection> pTextSel;
    pTextSel = pDisp;

    *ppSelection = pTextSel;

    return hr;
}

/**
 *\fn           HRESULT GetDoc(unsigned int nIndex, Document **pDoc)
 *\brief        到到文档
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   Document * * pDoc 文档指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetDoc(unsigned int nIndex, Document **pDoc)
{
    unsigned long nCount = 0;

    HRESULT hr = m_pDocs->get_Count((long*)&nCount);

    if (FAILED(hr) || (nIndex > nCount)) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;      // 指明整型数据
    varIndex.lVal = nIndex;   // 赋值

    return m_pDocs->Item(varIndex, pDoc);
}

/**
 *\fn           std::string GetSolutionPath()
 *\brief        得到解决方案所在路径
 *\return       std::string 解决方案所在路径
 */
std::string CAddinProcess::GetSolutionPath()
{
    std::string path = GetSolutionFilename();
    path.erase(path.rfind("\\"), 1000);
    return path;
}

/**
 *\fn           HRESULT GetCurProject(Project **ppProject)
 *\brief        得到当前项目
 *\param[in]    Project * * ppProject 项目指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCurProject(Project **ppProject)
{
    CComPtr<SelectedItem> selectItem;
    HRESULT hr = GetSelectedItem(1, &selectItem);

    if (SUCCEEDED(hr) && selectItem != NULL)
    {
        CComPtr<ProjectItem> item;
        hr = selectItem->get_ProjectItem(&item);

        if (SUCCEEDED(hr) && item != NULL)
        {
            hr = item->get_ContainingProject(ppProject);
        }
    }

    return hr;
}

/**
 *\fn           std::string GetCurProjectName()
 *\brief        得到当前项目名称
 *\return       std::string 项目名称
 */
std::string CAddinProcess::GetCurProjectName()
{
    std::string path;
    CComPtr<Project> project;
    HRESULT hr = GetCurProject(&project);

    if (SUCCEEDED(hr) && project != NULL)
    {
        BSTR name;
        project->get_Name(&name);
        path = BstrToStr(name);
    }

    return path;
}

/**
 *\fn           std::string GetCurProjectPath()
 *\brief        得到当前项目路径
 *\return       std::string 项目路径
 */
std::string CAddinProcess::GetCurProjectPath()
{
    std::string path;
    CComPtr<Project> project;
    HRESULT hr = GetCurProject(&project);

    if (SUCCEEDED(hr) && project != NULL)
    {
        BSTR name;
        project->get_FullName(&name);
        path = BstrToStr(name);
        path.erase(path.rfind("\\"), 1000);
    }

    return path;
}

/**
 *\fn           std::string GetCommandBarControlName(CommandBarControl *pControl)
 *\brief        得到菜单名称
 *\param[in]    CommandBarControl * pControl 菜单指针
 *\return       std::string 菜单名称
 */
std::string  CAddinProcess::GetCommandBarControlName(CommandBarControl *pControl)
{
    BSTR bname;

    pControl->get_Caption(&bname);

    return BstrToStr(bname);
}

/**
 *\fn           HRESULT GetProject(unsigned int nIndex, Project **ppProject)
 *\brief        得到项目
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   Project * * ppProject 项目指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetProject(unsigned int nIndex, Project **ppProject)
{
    unsigned long nCount = 0;

    HRESULT hr = m_pProjects->get_Count((long*)&nCount);

    if (FAILED(hr) || (nIndex > nCount)) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;    // 指明整型数据
    varIndex.lVal = nIndex; // 赋值

    return m_pProjects->Item(varIndex, ppProject);
}

/**
 *\fn           HRESULT GetProjectItem(Project *pProject, unsigned int nIndex, ProjectItem **ppProjectItem)
 *\brief        得到项目Item
 *\param[in]    Project * pProject 项目指针
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   ProjectItem * * ppProjectItem Item指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetProjectItem(Project *pProject, unsigned int nIndex, ProjectItem **ppProjectItem)
{
    if (NULL == pProject) return E_INVALIDARG;

    CComPtr<ProjectItems> pProjectItems;
    HRESULT hr = pProject->get_ProjectItems(&pProjectItems);

    if (NULL == pProjectItems) return E_INVALIDARG;

    unsigned long nCount = 0;
    hr = pProjectItems->get_Count((long*)&nCount);

    if (nIndex > nCount) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;    // 指明整型数据
    varIndex.lVal = nIndex; // 赋值

    return pProjectItems->Item(varIndex, ppProjectItem);
}

/**
 *\fn           HRESULT GetSubProjectItem(ProjectItem *pProjectItem, unsigned int nIndex, ProjectItem **ppProjectItem)
 *\brief        得到子项目Item
 *\param[in]    ProjectItem * pProjectItem 项目Item
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   ProjectItem * * ppProjectItem 子项目Item
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetSubProjectItem(ProjectItem *pProjectItem, unsigned int nIndex, ProjectItem **ppProjectItem)
{
    if (NULL == pProjectItem) return E_INVALIDARG;

    CComPtr<ProjectItems> pProjectItems;
    HRESULT hr = pProjectItem->get_ProjectItems(&pProjectItems);

    if (NULL == pProjectItems) return E_INVALIDARG;

    unsigned long nCount = 0;
    hr = pProjectItems->get_Count((long*)&nCount);

    if (nIndex > nCount) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;    // 指明整型数据
    varIndex.lVal = nIndex; // 赋值

    return pProjectItems->Item(varIndex, ppProjectItem);
}

/**
 *\fn           std::string GetProjectItemName(ProjectItem *pProjectItem)
 *\brief        得到项目Item名字
 *\param[in]    ProjectItem * pProjectItem 项目Item
 *\return       std::string 项目Item名字
 */
std::string CAddinProcess::GetProjectItemName(ProjectItem *pProjectItem)
{
    if (NULL == pProjectItem) return _T("");

    BSTR bstrName;
    pProjectItem->get_Name(&bstrName);

    return BstrToStr(bstrName);
}

/**
 *\fn           HRESULT GetProjectProperty(Project *pProject, unsigned int nIndex, Property **ppProperty)
 *\brief        得到项目的属性
 *\param[in]    Project * pProject 项目指针
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   Property * * ppProperty 项目属性指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetProjectProperty(Project *pProject, unsigned int nIndex, Property **ppProperty)
{
    if (NULL == pProject) return E_INVALIDARG;

    CComPtr<Properties> pProperties;
    HRESULT hr = pProject->get_Properties(&pProperties);

    if (NULL == pProperties) return E_INVALIDARG;

    unsigned long nCount = 0;
    hr = pProperties->get_Count((long*)&nCount);

    if (nIndex > nCount) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;    // 指明整型数据
    varIndex.lVal = nIndex; // 赋值

    return pProperties->Item(varIndex, ppProperty);
}

/**
 *\fn           HRESULT GetProjectItemProperty(ProjectItem *pProjectItem, unsigned int nIndex, Property **ppProperty)
 *\brief        得到项目Item的属性
 *\param[in]    ProjectItem * pProjectItem 项目Item
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   Property * * ppProperty 属性
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetProjectItemProperty(ProjectItem *pProjectItem, unsigned int nIndex, Property **ppProperty)
{
    if (NULL == pProjectItem) return E_INVALIDARG;

    CComPtr<Properties> pProperties;
    HRESULT hr = pProjectItem->get_Properties(&pProperties);

    if (NULL == pProperties) return E_INVALIDARG;

    unsigned long nCount = 0;
    hr = pProperties->get_Count((long*)&nCount);

    if (nIndex > nCount) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;    // 指明整型数据
    varIndex.lVal = nIndex; // 赋值

    return pProperties->Item(varIndex, ppProperty);
}

/**
 *\fn           HRESULT GetProjectItemProperty(ProjectItem *pProjectItem, const char *name, Property **ppProperty)
 *\brief        得到项目Item的属性,通过名称查找
 *\param[in]    ProjectItem * pProjectItem 项目Item
 *\param[in]    const char * name 名称
 *\param[out]   Property * * ppProperty 属性
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetProjectItemProperty(ProjectItem *pProjectItem, const char *name, Property **ppProperty)
{
    if (NULL == pProjectItem) return E_INVALIDARG;

    CComPtr<Properties> pProperties;
    HRESULT hr = pProjectItem->get_Properties(&pProperties);

    if (NULL == pProperties) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_BSTR;
    varIndex.bstrVal = _com_util::ConvertStringToBSTR(name);

    return pProperties->Item(varIndex, ppProperty);
}

/**
 *\fn           std::string GetPropertyName(Property *pProperty)
 *\brief        得到属性名称
 *\param[in]    Property * pProperty 属性
 *\return       std::string 属性名称
 */
std::string CAddinProcess::GetPropertyName(Property *pProperty)
{
    if (NULL == pProperty) return _T("");

    BSTR bstrName;
    pProperty->get_Name(&bstrName);

    return BstrToStr(bstrName);
}

/**
 *\fn           std::string GetPropertyValue(Property *pProperty)
 *\brief        得到属性值
 *\param[in]    Property * pProperty 属性
 *\return       std::string 属性值
 */
std::string CAddinProcess::GetPropertyValue(Property *pProperty)
{
    if (NULL == pProperty) return _T("");

    VARIANT varIndex;
    VariantInit(&varIndex);
    pProperty->get_Value(&varIndex);

    if (varIndex.vt == VT_BSTR)
    {
        return BstrToStr(varIndex.bstrVal);
    }
    else
    {
        return _T("");
    }
}

/**
 *\fn           HRESULT GetSelectedItem(unsigned int nIndex, SelectedItem **ppSelectedItem)
 *\brief        得到选中的文件
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   SelectedItem * * ppSelectedItem 选中的文件
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetSelectedItem(unsigned int nIndex, SelectedItem **ppSelectedItem)
{
    unsigned long nCount = 0;
    m_pSelectedItems->get_Count((long*)&nCount);

    if (nIndex > nCount) return E_INVALIDARG;

    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;
    varIndex.lVal = nIndex;

    return m_pSelectedItems->Item(varIndex, ppSelectedItem);
}

/**
 *\fn           HRESULT OpenSolution(const char *pszFileName)
 *\brief        打开一个解决方案
 *\param[in]    const char * pszFileName 解决方案文件名
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::OpenSolution(const char *pszFileName)
{
    if (NULL == pszFileName) return E_INVALIDARG;

    return m_pSolution->Open(CComBSTR(pszFileName));
}

/**
 *\fn           HRESULT OpenFile(const char *pszFileName, Window **ppWin)
 *\brief        打开一个文件
 *\param[in]    const char * pszFileName 文件名
 *\param[out]   Window * * ppWin 窗体
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::OpenFile(const char *pszFileName, Window **ppWin)
{
    if (NULL == pszFileName) return E_INVALIDARG;

    return m_pOperations->OpenFile(CComBSTR(pszFileName),CComBSTR(vsViewKindTextView), ppWin);
}

// 打开工具窗体
/**
 *\fn           HRESULT OpenToolWindow(const char *pszWindowName, const char *pszWindowID, int nBmpId, Window **ppWindow)
 *\brief        打开工具窗体
 *\param[in]    const char * pszWindowName 窗体名称
 *\param[in]    const char * pszWindowID 窗体CLSID
 *\param[in]    int nBmpId 图片
 *\param[out]   Window * * ppWindow 窗体
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::OpenToolWindow(const char *pszWindowName, const char *pszWindowID, int nBmpId, Window **ppWindow)
{
    if (NULL == pszWindowName || NULL == pszWindowID) return E_INVALIDARG;

    CComVariant varBitmap;
    varBitmap.vt = VT_INT;
    varBitmap.intVal = 0;

#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
    varBitmap.intVal = (INT)LoadBitmap(m_pAtlModule->GetResourceInstance(), (LPCSTR)nBmpId);
#pragma warning( default : 4311 )
#pragma warning( default : 4312 )

    std::string pszProgID = CLSIDToProgID(pszWindowID);

    CComPtr<IDispatch> pProgrammableObject;

    HRESULT hr = m_pWindows->CreateToolWindow(m_pAddInInstance, 
        CComBSTR(pszProgID.c_str()),
        CComBSTR(pszWindowName),
        CComBSTR(pszWindowID),
        &pProgrammableObject,
        ppWindow);

    if (NULL == *ppWindow) return E_INVALIDARG;

    hr = (*ppWindow)->SetTabPicture(varBitmap);
    hr = (*ppWindow)->put_Visible(VARIANT_TRUE);

    return hr;
}

/**
 *\fn           HRESULT OutputString(const char *pszCaption, const char *pszText)
 *\brief        向输出窗体输出文字
 *\param[in]    const char * pszCaption 标题
 *\param[in]    const char * pszText 内容
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::OutputString(const char *pszCaption, const char *pszText)
{
    if (NULL == pszCaption || NULL == pszText) return E_INVALIDARG;

    CComPtr<Window> pWindow;
    HRESULT hr = m_pWindows->Item(CComVariant(EnvDTE::vsWindowKindOutput), &pWindow);

    if (NULL == pWindow) return E_INVALIDARG;

    CComPtr<IDispatch> pDisp;
    CComQIPtr<OutputWindow> pOutputWindow;
    hr = pWindow->get_Object(&pDisp);
    pOutputWindow = pDisp;

    if (NULL == pOutputWindow) return E_INVALIDARG;

    CComPtr<OutputWindowPanes> pOutputWindowPanes;
    hr = pOutputWindow->get_OutputWindowPanes(&pOutputWindowPanes);

    if (NULL == pOutputWindowPanes) return E_INVALIDARG;

    long nCount = 0;
    hr = pOutputWindowPanes->get_Count(&nCount);

    CComPtr<OutputWindowPane> pOutputWindowPane;

    int i = 1;
    for (; i <= nCount; i++)
    {
        VARIANT varIndex;
        VariantInit(&varIndex);
        varIndex.vt = VT_I4;
        varIndex.lVal = i;

        CComPtr<OutputWindowPane> pPane;
        hr = pOutputWindowPanes->Item(varIndex, &pPane);

        if (NULL == pPane) continue;

        BSTR bstrName;
        pPane->get_Name(&bstrName);

        std::string name = BstrToStr(bstrName);

        if (0 == strcmp(name.c_str(), pszCaption))
        {
            pOutputWindowPane = pPane;
            break;
        }
    }

    if (i > nCount)
    {
        hr = pOutputWindowPanes->Add(CComBSTR(pszCaption), &pOutputWindowPane);
    }

    hr = pOutputWindowPane->OutputString(CComBSTR(pszText));

    return hr;
}

/**
 *\fn           HRESULT OutputString(const char *pszText)
 *\brief        向状态栏输出文字
 *\param[in]    const char * pszText 内容
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::OutputString(const char *pszText)
{
    if (NULL == pszText) return E_INVALIDARG;

    return m_pStatusBar->put_Text(CComBSTR(pszText));
}

/**
 *\fn           HRESULT GetCommandBar(unsigned int nIndex, CommandBar **ppCommandBar)
 *\brief        得到命令条
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   CommandBar * * ppCommandBar 命令条
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommandBar(unsigned int nIndex, CommandBar **ppCommandBar)
{
    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;
    varIndex.lVal = nIndex;

    return m_pCommandBars->get_Item(varIndex, ppCommandBar);
}

/**
 *\fn           HRESULT GetCommandBar(const char *pszName, CommandBar **ppCommandBar)
 *\brief        得到命令条
 *\param[in]    const char * pszName 命令条名称
 *\param[out]   CommandBar * * ppCommandBar 命令条
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommandBar(const char *pszName, CommandBar **ppCommandBar)
{
    return m_pCommandBars->get_Item(CComVariant(pszName), ppCommandBar);
}

/**
 *\fn           HRESULT GetCommandBarControls(unsigned int nIndex, CommandBarControls **ppCommandBarControls)
 *\brief        得到菜单
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   CommandBarControls * * ppCommandBarControls 菜单
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommandBarControls(unsigned int nIndex, CommandBarControls **ppCommandBarControls)
{
    CComPtr<CommandBar> pCommandBar;
    HRESULT hr = GetCommandBar(nIndex, &pCommandBar);

    if (SUCCEEDED(hr))
    {
        hr = pCommandBar->get_Controls(ppCommandBarControls);
    }

    return hr;
}

/**
 *\fn           HRESULT GetCommandBarControls(const char *pszName, CommandBarControls **ppCommandBarControls)
 *\brief        得到菜单
 *\param[in]    const char * pszName 命令条名称(菜单名)
 *\param[out]   CommandBarControls * * ppCommandBarControls 菜单
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommandBarControls(const char *pszName, CommandBarControls **ppCommandBarControls)
{
    CComPtr<CommandBar> pCommandBar;
    HRESULT hr = GetCommandBar(pszName, &pCommandBar);

    if (SUCCEEDED(hr))
    {
        hr = pCommandBar->get_Controls(ppCommandBarControls);
    }

    return hr;
}

/**
 *\fn           HRESULT GetCommandBarControls(CommandBar *pCommandBar, CommandBarControls **ppCommandBarControls)
 *\brief        得到菜单
 *\param[in]    CommandBar * pCommandBar 命令条
 *\param[out]   CommandBarControls * * ppCommandBarControls 菜单
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommandBarControls(CommandBar *pCommandBar, CommandBarControls **ppCommandBarControls)
{
    return pCommandBar->get_Controls(ppCommandBarControls);
}

/**
 *\fn           HRESULT GetCommandBarControl(const char *pszName, unsigned int nIndex, CommandBarControl **ppControl)
 *\brief        得到菜单项
 *\param[in]    const char * pszName 菜单名
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   CommandBarControl * * ppControl 菜单项
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommandBarControl(const char *pszName, unsigned int nIndex, CommandBarControl **ppControl)
{
    CComPtr<CommandBarControls> pControls;

    HRESULT hr = GetCommandBarControls(pszName, &pControls);

    if (SUCCEEDED(hr))
    {
        hr = GetCommandBarControl(pControls, nIndex, ppControl);
    }

    return hr;
}

/**
 *\fn           HRESULT GetCommandBarControl(CommandBarControls *pControls, unsigned int nIndex, CommandBarControl **ppControl)
 *\brief        得到菜单项
 *\param[in]    CommandBarControls * pControls 菜单
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   CommandBarControl * * ppControl 菜单项
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommandBarControl(CommandBarControls *pControls, unsigned int nIndex, CommandBarControl **ppControl)
{
    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;
    varIndex.lVal = nIndex;

    return pControls->get_Item(varIndex, ppControl);
}

/**
 *\fn           HRESULT GetCommand(unsigned int nIndex, Command **ppCommand)
 *\brief        得到命令
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   Command * * ppCommand 命令指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommand(unsigned int nIndex, Command **ppCommand)
{
    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;
    varIndex.lVal = nIndex;

    return m_pCommands2->Item(varIndex, 1, ppCommand);
}

/**
 *\fn           HRESULT GetCommand(const char *pszName, Command **ppCommand)
 *\brief        得到命令
 *\param[in]    const char * pszName 命令名称
 *\param[out]   Command * * ppCommand 命令指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetCommand(const char *pszName, Command **ppCommand)
{
    return m_pCommands2->Item(CComVariant(pszName), 1, ppCommand);
}

/**
 *\fn           HRESULT GetWindow(const char *pszName, Window **ppWindow)
 *\brief        得到窗体
 *\param[in]    const char * pszName 窗体名称
 *\param[out]   Window * * ppWindow 窗体
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetWindow(const char *pszName, Window **ppWindow)
{
    return m_pWindows->Item(CComVariant(pszName), ppWindow);
}

/**
 *\fn           HRESULT GetWindow(unsigned int nIndex, Window **ppWindow)
 *\brief        得到窗体
 *\param[in]    unsigned int nIndex 序号
 *\param[out]   Window * * ppWindow 窗体
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetWindow(unsigned int nIndex, Window **ppWindow)
{
    VARIANT varIndex;
    VariantInit(&varIndex);
    varIndex.vt = VT_I4;
    varIndex.lVal = nIndex;

    return m_pWindows->Item(varIndex, ppWindow);
}

/**
 *\fn           HRESULT GetAllCommandBar(LIST_STR &lstCommandBar)
 *\brief        得到所有命令栏
 *\param[out]   LIST_STR & lstCommandBar 
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetAllCommandBar(LIST_STR &lstCommandBar)
{
    int nCount = 0;

    BSTR bstrName;

    CComPtr<CommandBar> pCommandBar;

    HRESULT hr = m_pCommandBars->get_Count(&nCount);

    for (int i = 1; i <= nCount; i++)
    {
        pCommandBar = NULL;

        hr = GetCommandBar(i, &pCommandBar);

        if (NULL == pCommandBar) continue;

        hr = pCommandBar->get_Name(&bstrName);

        std::string name = BstrToStr(bstrName);

        lstCommandBar.push_back(name);

        AtlTrace("%d %s\n", i, name.c_str());
    }

    return hr;
}

/**
 *\fn           HRESULT GetAllCommand(LIST_STR &lstCommand)
 *\brief        得到所有命令
 *\param[out]   LIST_STR & lstCommand 
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetAllCommand(LIST_STR &lstCommand)
{
    long nCount = 0;

    BSTR bstrName;

    CComPtr<Command> pCommand;

    HRESULT hr = m_pCommands2->get_Count((long*)&nCount);

    for (int i = 1; i <= nCount; i++)
    {
        pCommand = NULL;

        hr = GetCommand(i, &pCommand);

        if (NULL == pCommand) continue;

        pCommand->get_Name(&bstrName);

        std::string name = BstrToStr(bstrName);

        lstCommand.push_back(name);

        AtlTrace("%d %s\n", i, name.c_str());
    }

    return hr;
}

/**
 *\fn           HRESULT GetAllWindow(LIST_STR &lstWindow)
 *\brief        得到所有窗体
 *\param[out]   LIST_STR & lstWindow 
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetAllWindow(LIST_STR &lstWindow)
{
    long nCount = 0;

    BSTR bstrName;

    CComPtr<Window> pWindow;

    HRESULT hr = m_pWindows->get_Count((long*)&nCount);

    for (int i = 1; i <= nCount; i++)
    {
        pWindow = NULL;

        hr = GetWindow(i, &pWindow);

        if (FAILED(hr)) continue;

        pWindow->get_Caption(&bstrName);

        std::string name = BstrToStr(bstrName);

        lstWindow.push_back(name);

        AtlTrace("%d %s\n", i, name.c_str());
    }

    return hr;
}

/**
 *\fn           HRESULT GetAllControl(CommandBarControls *pControls, LIST_STR &lstControl)
 *\brief        得到菜单的所有菜单项
 *\param[in]    CommandBarControls * pControls 
 *\param[in]    LIST_STR & lstControl 
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetAllControl(CommandBarControls *pControls, LIST_STR &lstControl)
{
    if (NULL == pControls) return E_INVALIDARG;

    int nCount = 0;
    HRESULT hr = pControls->get_Count(&nCount);

    for (int i = 1; i <= nCount; i++)
    {
        CComPtr<CommandBarControl> pControl; // 菜单Item

        VARIANT varIndex;
        VariantInit(&varIndex);
        varIndex.vt = VT_I4;
        varIndex.lVal = i;
        hr = pControls->get_Item(varIndex, &pControl);

        if (NULL == pControl) continue;

        BSTR bstrName;
        hr = pControl->get_Caption(&bstrName);

        std::string name = BstrToStr(bstrName);

        lstControl.push_back(name);

        AtlTrace("Control: %d %s\n", i, name.c_str());

        /*
        // 得到子菜单
        long nc = 0;
        hr = pControl->get_accChildCount(&nc);

        for (int j = 1; j <= nc; j++)
        {
        VARIANT varIndex;
        VariantInit(&varIndex);
        varIndex.vt = VT_I4;
        varIndex.lVal = j;
        BSTR bstrName1;
        hr = pControl->get_accName(varIndex, &bstrName1);

        CComPtr<IDispatch> pDisp;
        hr = pControl->get_accChild(varIndex, &pDisp);

        CComPtr<CommandBarControl> pSubControl;
        pSubControl = pDisp;

        if (NULL != pSubControl)
        {
        hr = pSubControl->get_Caption(&bstrName1);
        std::string name = BstrToStr(bstrName1);
        AtlTrace("Control:Child %d %s\n", i, name.c_str());
        }
        }
        */
    }

    return hr;
}

/**
 *\fn           std::string GetText(Document *pDoc, int nLineNum)
 *\brief        得到一行文本
 *\param[in]    Document * pDoc 文档
 *\param[in]    int nLineNum 行号
 *\return       std::string 内容
 */
std::string CAddinProcess::GetText(Document *pDoc, int nLineNum)
{
    if (NULL == pDoc) return "";

    CComPtr<IDispatch> pDisp;    
    HRESULT hr = pDoc->get_Selection(&pDisp);

    CComPtr<TextSelection> pTextSel;
    pTextSel = pDisp;

    if (NULL == pTextSel) return "";

    hr = pTextSel->GotoLine(nLineNum, true);

    BSTR bstrText;

    hr = pTextSel->get_Text(&bstrText);

    hr = pTextSel->GotoLine(nLineNum, false);

    std::string text = BstrToStr(bstrText);

    return text;
}

/**
 *\fn           HRESULT InsertText(Document *pDoc, int nLineNum, const char *pszText)
 *\brief        插入一行文本
 *\param[in]    Document * pDoc 文档
 *\param[in]    int nLineNum 行号
 *\param[in]    const char * pszText 内容
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::InsertText(Document *pDoc, int nLineNum, const char *pszText)
{
    CComPtr<IDispatch> pDisp;
    HRESULT hr = pDoc->get_Selection(&pDisp);

    CComPtr<TextSelection> pTextSel;
    pTextSel = pDisp;

    if (NULL == pTextSel) return E_INVALIDARG;

    hr = pTextSel->GotoLine(nLineNum, false);

    return pTextSel->Insert(CComBSTR(pszText), 1);

    //pTextSel->put_Text(CComBSTR(pszText));

    //CComPtr<TextPoint> pStartTextPoint;
    //hr = pTextSel->get_Start(&StartTextPoint);

    //CComPtr<EditPoint> pStratEditPoint;
    //hr = pStartTextPoint->CreateEditPoint(&pStratEditPoint);

    //CComPtr<Window> pNewWindow;
    //hr = pDoc1->NewWindow(&pNewWindow);
}

/**
 *\fn           HRESULT AddCommand(const char *pszName, const char *pszButtonText, 
                                   const char *pszTooltip, int nBmp, Command **ppCommand)
 *\brief        添加命令,类型AddinVS.Connect.command_upload_file
 *\param[in]    const char * pszName 命令名称
 *\param[in]    const char * pszButtonText 按钮名称
 *\param[in]    const char * pszTooltip 工具栏提示信息
 *\param[in]    int nBmp 显示的图标
 *\param[out]   Command * * ppCommand 命令指针
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::AddCommand(const char *pszName, 
    const char *pszButtonText, 
    const char *pszTooltip, 
    int nBmp, 
    Command **ppCommand)
{
    if ((NULL == pszName)
        || (NULL == pszButtonText)
        || (NULL == pszTooltip))
        return E_INVALIDARG;

    return m_pCommands2->AddNamedCommand2(m_pAddInInstance, 
        CComBSTR(pszName), 
        CComBSTR(pszButtonText), 
        CComBSTR(pszTooltip), 
        VARIANT_TRUE, 
        CComVariant(nBmp), 
        NULL, 
        vsCommandStatusSupported+vsCommandStatusEnabled, 
        vsCommandStylePictAndText, 
        vsCommandControlTypeButton, 
        ppCommand);
}

/**
 *\fn           HRESULT SetCommandName(int commandBarControlsIndex, const char *commandName, const char *newName)
 *\brief        设置菜单名称
 *\param[in]    int commandBarControlsIndex 
 *\param[in]    const char * commandName 
 *\param[in]    const char * newName 
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::SetCommandName(int commandBarControlsIndex, const char *commandName, const char *newName)
{
    if (NULL == commandName || NULL == newName) return E_INVALIDARG;

    CComPtr<CommandBarControls> pCommandBarControls;
    HRESULT hr = GetCommandBarControls(43, &pCommandBarControls);

    if (SUCCEEDED(hr))
    {
        int count = 0;
        pCommandBarControls->get_Count(&count);

        for (int i = 0; i < count; i++)
        {
            VARIANT varIndex;
            VariantInit(&varIndex);
            varIndex.vt = VT_I4;
            varIndex.lVal = i;

            CComPtr<CommandBarControl> pCommandBarControl;

            hr = pCommandBarControls->get_Item(varIndex, &pCommandBarControl);

            if (SUCCEEDED(hr))
            {
                BSTR bname;

                pCommandBarControl->get_Caption(&bname);

                std::string name = BstrToStr(bname);

                if (0 == strcmp(name.c_str(), commandName))
                {
                    hr = pCommandBarControl->put_Caption(CComBSTR(newName));

                    if (SUCCEEDED(hr))
                    {
                        ATLTRACE("put_Caption ok\n");
                    }

                    break;
                }
            }
        }
    }

    return S_OK;
}

HRESULT CAddinProcess::DeleteCommand(int commandBarControlsIndex, const char *commandName)
{
    if (commandBarControlsIndex < 0 || NULL == commandName) return E_INVALIDARG;

    CComPtr<CommandBarControls> pCommandBarControls;
    HRESULT hr = GetCommandBarControls(commandBarControlsIndex, &pCommandBarControls);

    if (SUCCEEDED(hr))
    {
        int count = 0;
        pCommandBarControls->get_Count(&count);

        for (int i = 0; i < count; i++)
        {
            VARIANT varIndex;
            VariantInit(&varIndex);
            varIndex.vt = VT_I4;
            varIndex.lVal = i;

            CComPtr<CommandBarControl> pCommandBarControl;

            hr = pCommandBarControls->get_Item(varIndex, &pCommandBarControl);

            if (SUCCEEDED(hr))
            {
                BSTR bname;
                pCommandBarControl->get_Caption(&bname);

                std::string name = BstrToStr(bname);

                if (0 == strcmp(name.c_str(), commandName))
                {
                    pCommandBarControl->Delete();
                    break;
                }
            }
        }
    }

    return S_OK;
}

/**
 *\fn           HRESULT AddCommandBar(const char *pszName, CommandBar *pParent, int pos, IDispatch **ppCommandBar)
 *\brief        添加命令集
 *\param[in]    const char * pszName 名称
 *\param[in]    CommandBar * pParent 父命令集
 *\param[in]    int pos 位置
 *\param[out]   IDispatch * * ppCommandBar 命令集
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::AddCommandBar(const char *pszName, CommandBar *pParent, int pos, IDispatch **ppCommandBar)
{
    return m_pCommands2->AddCommandBar(CComBSTR(pszName), 
        vsCommandBarTypeMenu, 
        pParent, 
        pos,
        ppCommandBar);
}

void CAddinProcess::Test(void)
{
    //HRESULT hr = this->OpenSolution("D:\\OpenCode\\TestSet\\AddinEdit\\AddinEdit.sln");

    CComPtr<Project> pProject;

    for (int j = 1; SUCCEEDED(GetProject(j, &pProject)); j++, pProject = NULL)
    {
        CComPtr<ProjectItem> pProjectItem;
        for (int i = 1; SUCCEEDED(this->GetProjectItem(pProject, i, &pProjectItem)); i++, pProjectItem = NULL)
        {
            std::string strName = this->GetProjectItemName(pProjectItem);

            AtlTrace("---------------------------------------------\n");
            AtlTrace("ProjectItem:%d %s\n", i, strName.c_str());

            CComPtr<Property> pProperty;
            for (int j = 1; SUCCEEDED(this->GetProjectItemProperty(pProjectItem, j, &pProperty)); j++, pProperty = NULL)
            {
                std::string strName = this->GetPropertyName(pProperty);
                std::string strValue = this->GetPropertyValue(pProperty);

                if (_T("") != strValue)
                {
                    AtlTrace("ProjectItem_Property:%d %s=%s\n", j, strName.c_str(), strValue.c_str());
                }
                else
                {
                    AtlTrace("ProjectItem_Property:%d %s\n", j, strName.c_str());
                }
            }

            //CComPtr<ProjectItems> pProjectItems;
            //pProjectItem->get_ProjectItems(&pProjectItems);

            //CComPtr<ProjectItem> pItem;
            //hr = pProjectItems->AddFromFile(CComBSTR("test.txt"), &pItem);

            CComPtr<ProjectItem> pSubProjectItem;
            for (int j = 1; SUCCEEDED(this->GetSubProjectItem(pProjectItem, j, &pSubProjectItem)); j++, pSubProjectItem = NULL)
            {
                std::string strName = this->GetProjectItemName(pSubProjectItem);
                AtlTrace("SubProjectItem:%d %s\n", j, strName.c_str());

                CComPtr<Property> pProperty;
                for (int j = 1; SUCCEEDED(this->GetProjectItemProperty(pSubProjectItem, j, &pProperty)); j++, pProperty = NULL)
                {
                    std::string strName = this->GetPropertyName(pProperty);
                    std::string strValue = this->GetPropertyValue(pProperty);

                    if (_T("") != strValue)
                    {
                        AtlTrace("SubProjectItem_Property:%d %s=%s\n", j, strName.c_str(), strValue.c_str());
                    }
                    else
                    {
                        AtlTrace("SubProjectItem_Property:%d %s\n", j, strName.c_str());
                    }
                }
            }
        }

        AtlTrace("---------------------------------------------\n");
        CComPtr<Property> pProperty;
        for (int i = 1; SUCCEEDED(this->GetProjectProperty(pProject, i, &pProperty)); i++, pProperty = NULL)
        {
            std::string strName = this->GetPropertyName(pProperty);
            std::string strValue = this->GetPropertyValue(pProperty);

            if (_T("") != strValue)
            {
                AtlTrace("Project_Property:%d %s=%s\n", i, strName.c_str(), strValue.c_str());
            }
            else
            {
                AtlTrace("Project_Property:%d %s\n", i, strName.c_str());
            }
        }
    }
}