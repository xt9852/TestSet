// Connect.cpp : CConnect 的具体实现
#include "stdafx.h"
#include "AddInVS.h"
#include "Connect.h"
#include "src/AddinProcess.h"
#include "11.Common/StrConver.h"
#include <TlHelp32.h>

#define CONFIG_FILENAME         "ssh_info.xml"
#define ADDIN_NAME              "我的插件"
#define UPLOAD_FILE             "command_upload_file"
#define DOWNLOAD_FILE           "command_download_file"
#define SHOW_WINDOW             "command_show_window"
#define ADD_FILE_BOM            "command_add_file_bom"
#define DEL_FILE_BOM            "command_del_file_bom"
#define COMMAND(x)              "AddinVS.Connect."##x


typedef void (*docSavedCallback)(void *param, const char *filename);

CAddinProcess *g_pAddinProcess = NULL;      // 插件处理

docSavedCallback g_SaveDocCallback = NULL;  // 保存文档回调

void *g_SaveDocParam = NULL;                // 保存文件回调的自定义参数

/**
 *\fn        STDMETHODIMP OnDocumentSaved(EnvDTE::Document *document)
 *\brief     保存文档事件事件处理
 *\param[in] EnvDTE::Document * document 文档
 *\return    STDMETHODIMP 0成功,其它失败
 */
STDMETHODIMP CDocumentEventsSink::OnDocumentSaved(EnvDTE::Document *document)
{
    BSTR bstrName = L"test";
    document->get_FullName(&bstrName);
    std::string name = g_pAddinProcess->BstrToStr(bstrName);

    ATLTRACE("CDocumentEventsSink::OnDocumentSaved %s\n", name.c_str());

    if (NULL != g_SaveDocCallback)
    {
        g_SaveDocCallback(g_SaveDocParam, name.c_str());
    }

    return 0;
}

/**
 *\fn        void setParam(int id, void *param)
 *\brief     设置参数
 *\param[in] int id 参数ID
 *\param[in] void * param 参数
 *\return    void 0成功,其它失败
 */
void setParam(int id, void *param)
{
    switch (id)
    {
    case 0:
        {
            g_SaveDocCallback = (docSavedCallback)param;
            break;
        }
    case 1:
        {
            g_SaveDocParam = param;
            break;
        }
    default:
        {
            ATLTRACE("setParam id error id:%d\n", id);
       break;
        }
    }
}


CConnect::CConnect()
    :m_pAddinProcess(NULL)
{
}

CConnect::~CConnect()
{
}

// CConnect
STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, ext_ConnectMode ConnectMode, 
    IDispatch *pAddInInst, SAFEARRAY ** /*自定义*/ )
{
    HRESULT hr = S_FALSE;

    pApplication->QueryInterface(__uuidof(DTE2), (LPVOID*)&m_pDTE);

    pAddInInst->QueryInterface(__uuidof(AddIn), (LPVOID*)&m_pAddInInstance);

    if (ConnectMode == ext_cm_AfterStartup) //5 == ext_cm_UISetup
    {
        if (m_pAddinProcess == NULL)
        {
            m_pAddinProcess = new CAddinProcess;
            g_pAddinProcess = m_pAddinProcess;
        }

        // 初使化
        int nRet = m_pAddinProcess->Init(m_pDTE, m_pAddInInstance, &_AtlModule);

        if (0 != nRet) return hr;

        // 文件保存事件关联
        hr = m_objDocumentEvents.DispEventAdvise(m_pAddinProcess->m_pDocEvents);

        if (FAILED(hr)) return hr;

        // 得到上传命令
        CComPtr<Command> pUploadCommand;
        hr = m_pAddinProcess->GetCommand(COMMAND(UPLOAD_FILE), &pUploadCommand);

        if (SUCCEEDED(hr))
        {
            return hr;
        }

        // 得到命令集
        CComPtr<CommandBar> addinCommandBar;
        hr = m_pAddinProcess->GetCommandBar(ADDIN_NAME, &addinCommandBar); // 比较慢

        if (FAILED(hr))
        {
            // 得到命令条
            CComPtr<CommandBar> pCommandBar;
            hr = m_pAddinProcess->GetCommandBar("Item", &pCommandBar);

            if (FAILED(hr)) return hr;

            // 我的插件子菜单
            CComPtr<IDispatch> pAddinCommandBar;
            hr = m_pAddinProcess->AddCommandBar(ADDIN_NAME, pCommandBar, 1, &pAddinCommandBar);
            addinCommandBar = pAddinCommandBar;
        }

        //CComPtr<Command> pUploadCommand;
        hr = m_pAddinProcess->GetCommand(COMMAND(UPLOAD_FILE), &pUploadCommand);

        if (FAILED(hr))
        {
            // 添加命令
            CComPtr<Command> pUploadCommand;
            hr = m_pAddinProcess->AddCommand(UPLOAD_FILE, 
                "上传(&U)", 
                "Upload files to server by sftp.", 
                59, 
                &pUploadCommand);
        }

        if (SUCCEEDED(hr))
        {
            CComPtr<IDispatch> pDisp;
            hr = pUploadCommand->AddControl(addinCommandBar, 1, &pDisp);// 添加一个菜单项
        }

        CComPtr<Command> pDownloadCommand;
        hr = m_pAddinProcess->GetCommand(COMMAND(DOWNLOAD_FILE), &pDownloadCommand);

        if (FAILED(hr))
        {
            // 添加命令
            CComPtr<Command> pDownloadCommand;
            hr = m_pAddinProcess->AddCommand(UPLOAD_FILE, 
                "下载(&D)", 
                "Download files to server by sftp.", 
                59, 
                &pDownloadCommand);
        }

        if (SUCCEEDED(hr))
        {
            CComPtr<IDispatch> pDisp;
            hr = pDownloadCommand->AddControl(addinCommandBar, 2, &pDisp);
        }

        CComPtr<Command> pShowCommand;
        hr = m_pAddinProcess->GetCommand(COMMAND(SHOW_WINDOW), &pShowCommand);

        if (FAILED(hr))
        {
            hr = m_pAddinProcess->AddCommand(SHOW_WINDOW, 
                "命令行窗体(&C)", 
                "Show command window.", 
                59, 
                &pShowCommand);
        }

        if (SUCCEEDED(hr))
        {
            CComPtr<IDispatch> pDisp;
            hr = pShowCommand->AddControl(addinCommandBar, 3, &pDisp);
        }

        CComPtr<Command> pAddBomCommand;
        hr = m_pAddinProcess->GetCommand(COMMAND(ADD_FILE_BOM), &pAddBomCommand);

        if (FAILED(hr))
        {
            hr = m_pAddinProcess->AddCommand(ADD_FILE_BOM, 
                "添加签名(&A)", 
                "Add file BOM.", 
                59, 
                &pAddBomCommand);
        }

        if (SUCCEEDED(hr))
        {
            CComPtr<IDispatch> pDisp;
            hr = pAddBomCommand->AddControl(addinCommandBar, 4, &pDisp);
        }

        CComPtr<Command> pDelBomCommand;
        hr = m_pAddinProcess->GetCommand(COMMAND(DEL_FILE_BOM), &pDelBomCommand);

        if (FAILED(hr))
        {
            hr = m_pAddinProcess->AddCommand(DEL_FILE_BOM, 
                "删除签名(&R)", 
                "Delete file BOM.", 
                59, 
                &pDelBomCommand);
        }

        if (SUCCEEDED(hr))
        {
            CComPtr<IDispatch> pDisp;
            hr = pDelBomCommand->AddControl(addinCommandBar, 5, &pDisp);
        }
    }

    return hr;
}

STDMETHODIMP CConnect::OnDisconnection(ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*自定义*/ )
{
    m_pDTE = NULL;
    m_pAddInInstance = NULL;
    return S_OK;
}

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*自定义*/ )
{
    return S_OK;
}

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*自定义*/ )
{
    return S_OK;
}

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*自定义*/ )
{
    if (NULL != m_pToolWindow)
    {
        CComPtr<IDispatch> pDisp;
        m_pToolWindow->get_Object(&pDisp);
        CComQIPtr<IAtlEdit> pAtlEdit = pDisp;
        pAtlEdit->setParam(0, NULL);
    }

    for (INT_SSH_MAP::iterator iter = sftpParam_.begin(); iter != sftpParam_.end(); ++iter)
    {
        PProjectSftpData data = iter->second;

        if (NULL != data->ssh_param.channel)
        {
            data->ssh_param.exit = 1;
        }
    }

    Sleep(2000);

    for (INT_SSH_MAP::iterator iter = sftpParam_.begin(); iter != sftpParam_.end(); ++iter)
    {
        PProjectSftpData data = iter->second;

        free(data);
    }

    return S_OK;
}

/**
 *\fn        STDMETHODIMP QueryStatus(BSTR bstrCmdName, vsCommandStatusTextWanted NeededText, 
                                      vsCommandStatus *pStatusOption, VARIANT *pvarCommandText)
 *\brief     设置菜单状态
 *\param[in] BSTR bstrCmdName 
 *\param[in] vsCommandStatusTextWanted NeededText 
 *\param[in] vsCommandStatus * pStatusOption 
 *\param[in] VARIANT * pvarCommandText 
 *\return    STDMETHODIMP 0成功,其它失败
 */
STDMETHODIMP CConnect::QueryStatus(BSTR bstrCmdName, 
    vsCommandStatusTextWanted NeededText, 
    vsCommandStatus *pStatusOption, 
    VARIANT *pvarCommandText)
{
    if (NeededText == vsCommandStatusTextWantedNone)
    {
        std::string name = m_pAddinProcess->BstrToStr(bstrCmdName);

        if (name == COMMAND(UPLOAD_FILE) ||
            name == COMMAND(DOWNLOAD_FILE) ||
            name == COMMAND(SHOW_WINDOW) ||
            name == COMMAND(ADD_FILE_BOM) ||
            name == COMMAND(DEL_FILE_BOM))
        {
            *pStatusOption = (vsCommandStatus)(vsCommandStatusEnabled+vsCommandStatusSupported);
        }
    }
    return S_OK;
}

/**
 *\fn        STDMETHODIMP Exec(BSTR bstrCmdName, vsCommandExecOption ExecuteOption, 
                               VARIANT *pvarVariantIn, VARIANT *pvarVariantOut, VARIANT_BOOL *pvbHandled)
 *\brief     执行命令
 *\param[in] BSTR bstrCmdName 
 *\param[in] vsCommandExecOption ExecuteOption 
 *\param[in] VARIANT * 
 *\param[in] VARIANT * 
 *\param[in] VARIANT_BOOL * pvbHandled 
 *\return    STDMETHODIMP 0成功,其它失败
 */
STDMETHODIMP CConnect::Exec(BSTR bstrCmdName, 
    vsCommandExecOption ExecuteOption, 
    VARIANT * /*pvarVariantIn*/, 
    VARIANT * /*pvarVariantOut*/, 
    VARIANT_BOOL *pvbHandled)
{
    if (m_pAddinProcess == NULL)
    {
        m_pAddinProcess = new CAddinProcess;
        g_pAddinProcess = m_pAddinProcess;

        m_pAddinProcess->Init(m_pDTE, m_pAddInInstance, &_AtlModule);
    }

    *pvbHandled = VARIANT_FALSE;
    if (ExecuteOption == vsCommandExecOptionDoDefault)
    {
        std::string name = m_pAddinProcess->BstrToStr(bstrCmdName);

        if (name == COMMAND(UPLOAD_FILE))
        {
            OnUploadFile();

            *pvbHandled = VARIANT_TRUE;
        }
        else if(name == COMMAND(DOWNLOAD_FILE))
        {
            OnDownloadFile();

            *pvbHandled = VARIANT_TRUE;
        }
        else if(name == COMMAND(SHOW_WINDOW))
        {
            OnShowWindow();

            *pvbHandled = VARIANT_TRUE;
        }
        else if(name == COMMAND(ADD_FILE_BOM))
        {
            OnAddFileBom();

            *pvbHandled = VARIANT_TRUE;
        }
        else if(name == COMMAND(DEL_FILE_BOM))
        {
            OnDelFileBom();

            *pvbHandled = VARIANT_TRUE;
        }
    }
    return S_OK;
}

/**
 *\fn         GetSelectFile(STR_STR_MAP &files)
 *\brief      得到选中的文件。
 *\param[out] files 选中的文件。
 */
void CConnect::GetSelectFile(STR_STR_MAP &files)
{
    for (int i = 1; true; i++)
    {
        CComPtr<SelectedItem> selectItem;
        HRESULT hr = m_pAddinProcess->GetSelectedItem(i, &selectItem);

        if (SUCCEEDED(hr) && selectItem != NULL)
        {
            std::string fullPath;     // 绝对路径
            std::string relativePath; // 相对路径

            CComPtr<ProjectItem> projectItem;
            hr = selectItem->get_ProjectItem(&projectItem);

            CComPtr<Property> property;
            hr = m_pAddinProcess->GetProjectItemProperty(projectItem, "FullPath", &property);
            if (SUCCEEDED(hr) && property != NULL)
            {
                fullPath = m_pAddinProcess->GetPropertyValue(property);
            }

            property = NULL;
            hr = m_pAddinProcess->GetProjectItemProperty(projectItem, "RelativePath", &property);
            if (SUCCEEDED(hr) && property != NULL)
            {
                relativePath = m_pAddinProcess->GetPropertyValue(property);

                int index = relativePath.rfind("\\");
                if (-1 != index)
                {
                    relativePath.erase(index, relativePath.length());
                    CStrConver::StringReplace(relativePath, "\\", "/");
                }
                else
                {
                    relativePath = "";
                }
            }

            files[fullPath] = relativePath;
        }
        else
        {
            break;
        }
    }
}

/**
 *\fn         GetConfigPath()
 *\brief      得到通过项目文件路径,得到配置文件路径。
 *\return     配置文件路径。
 */
std::string CConnect::GetConfigPath()
{
    return m_pAddinProcess->GetSolutionPath() + "\\" + CONFIG_FILENAME;
}

/**
 *\fn        int outputCallback(void *param, const char *data, int data_len)
 *\brief     向Output窗体的"我的插件"页,输出文字回调
 *\param[in] void * param sftp连接
 *\param[in] const char * data 数据
 *\param[in] int data_len 数据长
 *\return    int 0成功,其它失败
 */
int outputCallback(void *param, const char *data, int data_len)
{
    g_pAddinProcess->OutputString(data);
    g_pAddinProcess->OutputString(ADDIN_NAME, data);
    return 0;
}

/**
 *\fn        PProjectSftpData runSftp()
 *\brief     运行sftp
 *\return    PProjectSftpData sftp数据
 */
PProjectSftpData CConnect::runSftp()
{
    if (!m_Config.isLoad())
    {
        m_Config.openFile(GetConfigPath().c_str());
    }

    if (!m_Config.isLoad())
    {
        TCHAR info[MAX_PATH] = _T("");
        _stprintf_s(info, ARRAYSIZE(info), _T("配置文件%s不正确"), GetConfigPath().c_str());
        MessageBox(NULL, info, _T("错误"), MB_OK|MB_ICONSTOP);
        return NULL;
    }

    std::string projectName = m_pAddinProcess->GetCurProjectName();
    int serverId = m_Config.getServerId(projectName.c_str());

    if (-1 == serverId)
    {
        TCHAR info[MAX_PATH] = _T("");
        _stprintf_s(info, ARRAYSIZE(info), _T("配置文件中没有工程%s信息"), projectName.c_str());
        MessageBox(NULL, info, _T("错误"), MB_OK|MB_ICONSTOP);
        return NULL;
    }

    PProjectSftpData sshParam = NULL;
    INT_SSH_MAP::iterator iter = sftpParam_.find(serverId);

    if (iter == sftpParam_.end())
    {
        sshParam = new ProjectSftpData;
        memset(sshParam, 0, sizeof(ProjectSftpData));

        sshParam->ssh_param.type = SSH_TYPE_SFTP;
        sshParam->ssh_param.username = sshParam->username;
        sshParam->ssh_param.password = sshParam->password;
        sshParam->ssh_param.server_addr = sshParam->serverAddr;
        sshParam->ssh_param.recv_cb = outputCallback;

        strcpy(sshParam->remotePath, m_Config.getRemotePath(projectName.c_str()));

        m_Config.getServerParam(serverId, sshParam->serverAddr, sshParam->serverPort, 
            sshParam->username, sshParam->password, sshParam->portMappingCount);

        sshParam->ssh_param.server_port = sshParam->serverPort;

        sftpParam_[serverId] = sshParam;
    }
    else
    {
        sshParam = iter->second;
    }

    if (NULL == sshParam->ssh_param.channel)
    {
        _beginthread(sftp_thread_func, 0, &(sshParam->ssh_param));
    }

    for (int i = 0; i < 100; i++)
    {
        if (NULL != sshParam->ssh_param.channel) break;
        Sleep(100);
    }

    return sshParam;
}

/**
 *\fn        void OnUploadFile()
 *\brief     上传文件
 *\return    void 无
 */
void CConnect::OnUploadFile()
{
    PProjectSftpData sftpParam = runSftp();

    if (NULL == sftpParam) return;

    STR_STR_MAP files;
    GetSelectFile(files);

    STR_STR_MAP::iterator iter = files.begin();
    for (; iter != files.end(); ++iter)
    {
        std::string filename = iter->first;
        filename.erase(0, filename.rfind("\\")+1);

        std::string path = std::string(sftpParam->remotePath) + 
            "/" + iter->second + "/" + filename;

        sftp_upload_file(&(sftpParam->ssh_param), iter->first.c_str(), path.c_str());
    }
}

/**
 *\fn        void OnDownloadFile()
 *\brief     下载文件
 *\return    void 无
 */
void CConnect::OnDownloadFile()
{
    PProjectSftpData sftpParam = runSftp();

    if (NULL == sftpParam) return;

    STR_STR_MAP files;
    GetSelectFile(files);

    STR_STR_MAP::iterator iter = files.begin();
    for (; iter != files.end(); ++iter)
    {
        std::string filename = iter->first;
        filename.erase(0, filename.rfind("\\")+1);

        std::string path = std::string(sftpParam->remotePath) + 
            "/" + iter->second + "/" + filename;

        sftp_download_file(&(sftpParam->ssh_param), iter->first.c_str(), path.c_str());
    }
}

/**
 *\fn        int openFileCallback(void *param, const char *data, int data_len)
 *\brief     打开文件回调
 *\param[in] void * param sftp连接
 *\param[in] const char * data 文件名
 *\param[in] int data_len 文件名长
 *\return    int 0成功,其它失败
 */
int openFileCallback(void *param, const char *data, int data_len)
{
    CComPtr<Window> wnd;

    return g_pAddinProcess->OpenFile(data, &wnd);
}

/**
 *\fn        void OnShowWindow()
 *\brief     显示命令窗体
 *\return    void 无
 */
void CConnect::OnShowWindow()
{
    if (!m_Config.isLoad())
    {
        m_Config.openFile(GetConfigPath().c_str());
    }

    if (!m_Config.isLoad())
    {
        TCHAR info[MAX_PATH] = _T("");
        _stprintf_s(info, ARRAYSIZE(info), _T("配置文件%s不正确"), GetConfigPath().c_str());
        MessageBox(NULL, info, _T("错误"), MB_OK|MB_ICONSTOP);
        return;
    }

    if (m_pToolWindow == NULL)
    {
        HRESULT hr = m_pAddinProcess->OpenToolWindow("我的插件",
            "{2D7E0F8F-3215-11D0-BF28-0000E8D0D146}",
            IDB_BITMAP1,
            &m_pToolWindow);

        CComPtr<IDispatch> pDisp;
        m_pToolWindow->get_Object(&pDisp);
        CComQIPtr<IAtlEdit> pAtlEdit = pDisp;
        pAtlEdit->setParam(1, m_pAddinProcess->GetCurProjectName().c_str());
        pAtlEdit->setParam(2, (const char*)openFileCallback);
        pAtlEdit->setParam(3, (const char*)outputCallback);
        pAtlEdit->setParam(4, (const char*)&m_Config);
        pAtlEdit->setParam(5, (const char*)setParam);
    }
    else
    {
        m_pToolWindow->put_Visible(VARIANT_TRUE);
    }
}

/**
 *\fn        void OnAddFileBom()
 *\brief     添加文件BOM
 *\return    void 无
 */
void CConnect::OnAddFileBom()
{
    STR_STR_MAP files;
    GetSelectFile(files);

    STR_STR_MAP::iterator iter = files.begin();
    for (; iter != files.end(); ++iter)
    {
        if (!isFileBom(iter->first.c_str()))
        {
            setFileBom(iter->first.c_str(), true);
        }
        else
        {
            continue;
        }
    }
}

/**
 *\fn        void OnDelFileBom()
 *\brief     删除文件BOM
 *\return    void 无
 */
void CConnect::OnDelFileBom()
{
    STR_STR_MAP files;
    GetSelectFile(files);

    STR_STR_MAP::iterator iter = files.begin();
    for (; iter != files.end(); ++iter)
    {
        if (isFileBom(iter->first.c_str()))
        {
            setFileBom(iter->first.c_str(), false);
        }
        else
        {
            continue;
        }
    }
}

/**
 *\fn        bool isFileBom(const char *filename)
 *\brief     得到是否有BOM标记
 *\param[in] const char * filename 文件名
 *\return    是否有BOM标记
 */
bool CConnect::isFileBom(const char *filename)
{
    if (filename == NULL) return false;

    unsigned char buff[10] = "";
    FILE *file = fopen(filename, "rb");

    if (NULL != file)
    {
        fread(buff, 1, 3, file);
        fclose(file);
    }

    return (buff[0] == 0xEF && buff[1] == 0xBB && buff[2] == 0xBF);
}

/**
 *\fn        void setFileBom(const char *filename, bool set)
 *\brief     设置BOM标记
 *\param[in] const char * filename 文件名
 *\param[in] bool set 是否有BOM标记
 *\return    void 0成功,其它失败
 */
void CConnect::setFileBom(const char *filename, bool set)
{
    if (filename == NULL) return;

    int len = 0;
    char *buf = NULL;
    unsigned char bom[10] = {0xEF, 0xBB, 0xBF};
    FILE *file = fopen(filename, "rb");

    if (NULL != file)
    {
        fseek(file, 0, SEEK_END);

        len = ftell(file);
        buf = new char[len+10];

        fseek(file, set?0:3, SEEK_SET);
        len = fread(buf, 1, len-(set?0:3), file);
        fclose(file);
    }

    file = fopen(filename, "w+b");

    if (NULL != file)
    {
        if (set)
        {
            fwrite(bom, 1, 3, file);
        }

        fwrite(buf, 1, len, file);
        fclose(file);
    }

    if (NULL != buf)
    {
        free(buf);
    }
}
