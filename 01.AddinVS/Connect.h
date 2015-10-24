// Connect.h : CConnect 的声明

#pragma once
#include "resource.h"       // 主符号
#include "AddinVSEx_i.c"
#include "AddinVSEx.h"
#include "src/SshConfig.h"
#include <map>
#include <string>

extern "C"
{
#include "03.Network/ssh2/ssh2.h"
#include "03.Network/ssh2/sftp.h"
};

typedef struct tagProjectSftp
{
    int serverPort;
    char serverAddr[256];
    char username[256];
    char password[256];
    char remotePath[1024];

    int portMappingCount;

    my_ssh_param ssh_param;

}ProjectSftpData, *PProjectSftpData;

typedef std::map<std::string, std::string> STR_STR_MAP;
typedef std::map<int, PProjectSftpData> INT_SSH_MAP;


class CAddinProcess;

using namespace AddInDesignerObjects;
using namespace EnvDTE;
using namespace EnvDTE80;
using namespace Microsoft_VisualStudio_CommandBars;


// 文档事件回调
class CDocumentEventsSink: public IDispEventImpl<1, 
    CDocumentEventsSink, 
    &__uuidof(EnvDTE::_dispDocumentEvents), 
    &EnvDTE::LIBID_EnvDTE, 
    8, 
    0>
{
public:
    CDocumentEventsSink()
    {
    }

    BEGIN_SINK_MAP(CDocumentEventsSink)
        SINK_ENTRY_EX(1, __uuidof(EnvDTE::_dispDocumentEvents), 1, OnDocumentSaved) //1-已经保存,2-关闭 ,3-正在打开,4-已经打开
    END_SINK_MAP()

public:
    STDMETHOD(OnDocumentSaved)(EnvDTE::Document *document);
};



/// <summary>用于实现外接程序的对象。</summary>
/// <seealso class='IDTExtensibility2' />
class ATL_NO_VTABLE CConnect : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CConnect, &CLSID_Connect>,
    public IDispatchImpl<IDTCommandTarget, &IID_IDTCommandTarget, &LIBID_EnvDTE, 7, 0>,
    public IDispatchImpl<_IDTExtensibility2, &IID__IDTExtensibility2, &LIBID_AddInDesignerObjects, 1, 0>
{
public:
    /// <summary>实现外接程序对象的构造函数。请将您的初始化代码置于此方法内。</summary>
    CConnect();
    ~CConnect();

    DECLARE_REGISTRY_RESOURCEID(IDR_ADDIN)
    DECLARE_NOT_AGGREGATABLE(CConnect)

    BEGIN_COM_MAP(CConnect)
        COM_INTERFACE_ENTRY(IDTExtensibility2)
        COM_INTERFACE_ENTRY(IDTCommandTarget)
        COM_INTERFACE_ENTRY2(IDispatch, IDTExtensibility2)
    END_COM_MAP()



    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease() 
    {
    }

public:
    //IDTExtensibility2 的具体实现:

    /// <summary>实现 IDTExtensibility2 接口的 OnConnection 方法。接收正在加载外接程序的通知。</summary>
    /// <param term='application'>宿主应用程序的根对象。</param>
    /// <param term='connectMode'>描述外接程序的加载方式。</param>
    /// <param term='addInInst'>表示此外接程序的对象。</param>
    /// <seealso class='IDTExtensibility2' />
    STDMETHOD(OnConnection)(IDispatch * Application, ext_ConnectMode ConnectMode, IDispatch *AddInInst, SAFEARRAY **custom);

    /// <summary>实现 IDTExtensibility2 接口的 OnDisconnection 方法。接收正在卸载外接程序的通知。</summary>
    /// <param term='disconnectMode'>描述外接程序的卸载方式。</param>
    /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
    /// <seealso class='IDTExtensibility2' />
    STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY **custom );

    /// <summary>实现 IDTExtensibility2 接口的 OnAddInsUpdate 方法。当外接程序集合已发生更改时接收通知。</summary>
    /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
    /// <seealso class='IDTExtensibility2' />	
    STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom );

    /// <summary>实现 IDTExtensibility2 接口的 OnStartupComplete 方法。接收宿主应用程序已完成加载的通知。</summary>
    /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
    /// <seealso class='IDTExtensibility2' />
    STDMETHOD(OnStartupComplete)(SAFEARRAY **custom );

    /// <summary>实现 IDTExtensibility2 接口的 OnBeginShutdown 方法。接收正在卸载宿主应用程序的通知。</summary>
    /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
    /// <seealso class='IDTExtensibility2' />
    STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom );

    //IDTCommandTarget 的具体实现:

    /// <summary>实现 IDTCommandTarget 接口的 QueryStatus 方法。此方法在更新该命令的可用性时调用</summary>
    /// <param term='commandName'>要确定其状态的命令的名称。</param>
    /// <param term='neededText'>该命令所需的文本。</param>
    /// <param term='status'>该命令在用户界面中的状态。</param>
    /// <param term='commandText'>neededText 参数所要求的文本。</param>
    /// <seealso class='Exec' />
    STDMETHOD(QueryStatus)(BSTR CmdName, vsCommandStatusTextWanted NeededText, vsCommandStatus *StatusOption, VARIANT *CommandText);

    /// <summary>实现 IDTCommandTarget 接口的 Exec 方法。此方法在调用该命令时调用。</summary>
    /// <param term='commandName'>要执行的命令的名称。</param>
    /// <param term='executeOption'>描述该命令应如何运行。</param>
    /// <param term='varIn'>从调用方传递到命令处理程序的参数。</param>
    /// <param term='varOut'>从命令处理程序传递到调用方的参数。</param>
    /// <param term='handled'>通知调用方此命令是否已被处理。</param>
    /// <seealso class='Exec' />
    STDMETHOD(Exec)(BSTR CmdName, vsCommandExecOption ExecuteOption, VARIANT *VariantIn, VARIANT *VariantOut, VARIANT_BOOL *Handled);

private:
    CComPtr<DTE2>       m_pDTE;
    CComPtr<AddIn>      m_pAddInInstance;
    CComPtr<Window>     m_pToolWindow;
    CAddinProcess      *m_pAddinProcess;
    CDocumentEventsSink m_objDocumentEvents;

    Config              m_Config;           // 配置文件
    INT_SSH_MAP         sftpParam_;         // SFTP参数

public:
    /**
     *\fn        void OnUploadFile()
     *\brief     上传文件
     *\return    void 无
     */
    void OnUploadFile();

    /**
     *\fn        void OnDownloadFile()
     *\brief     下载文件
     *\return    void 无
     */
    void OnDownloadFile();

    /**
     *\fn        void OnShowWindow()
     *\brief     显示命令窗体
     *\return    void 无
     */
    void OnShowWindow();

    /**
     *\fn        void OnAddFileBom()
     *\brief     添加文件BOM
     *\return    void 无
     */
    void OnAddFileBom();

    /**
     *\fn        void OnDelFileBom()
     *\brief     删除文件BOM
     *\return    void 无
     */
    void OnDelFileBom();

    /**
     *\fn        bool isFileBom(const char *filename)
     *\brief     得到是否有BOM标记
     *\param[in] const char * filename 文件名
     *\return    是否有BOM标记
     */
    bool isFileBom(const char *filename);

    /**
     *\fn        void setFileBom(const char *filename, bool set)
     *\brief     设置BOM标记
     *\param[in] const char * filename 文件名
     *\param[in] bool set 是否有BOM标记
     *\return    void 0成功,其它失败
     */
    void setFileBom(const char *filename, bool set);

    /**
     *\fn        PProjectSftpData runSftp()
     *\brief     运行sftp
     *\return    PProjectSftpData sftp数据
     */
    PProjectSftpData runSftp();

    /**
     *\fn         GetSelectFile(STR_STR_MAP &files)
     *\brief      得到选中的文件。
     *\param[out] files 选中的文件。
     */
    void GetSelectFile(STR_STR_MAP &files);

    /**
     *\fn         GetConfigPath()
     *\brief      得到通过项目文件路径,得到配置文件路径。
     *\return     配置文件路径
     */
    std::string GetConfigPath();
};

OBJECT_ENTRY_AUTO(__uuidof(Connect), CConnect)
