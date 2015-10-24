
#pragma once
#include <atlbase.h>
#include <atlcom.h>
#include <string>
#include <list>

#pragma warning( disable : 4278 )
#pragma warning( disable : 4146 )
    //下面的 #import 基于其 LIBID 导入 IDTExtensibility2 接口
    #import "libid:AC0714F2-3D04-11D1-AE7D-00A0C90F26F4" version("1.0") lcid("0")  raw_interfaces_only named_guids

    //下面的 #import 基于其 LIBID 导入 VS 命令栏
    #import "libid:1CBA492E-7263-47BB-87FE-639000619B15" version("8.0") lcid("0") raw_interfaces_only named_guids

    //下面的 #import 基于其 LIBID 导入 DTE
    #import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("8.0") lcid("0") raw_interfaces_only named_guids

    //下面的 #import 基于其 LIBID 导入 DTE80
    #import "libid:1A31287A-4D7D-413e-8E32-3B374931BD89" version("8.0") lcid("0") raw_interfaces_only named_guids
#pragma warning( default : 4146 )
#pragma warning( default : 4278 )

using namespace AddInDesignerObjects;
using namespace EnvDTE;
using namespace EnvDTE80;
using namespace Microsoft_VisualStudio_CommandBars;

class CAddInModule;

typedef std::list<std::string> LIST_STR;

class CAddinProcess
{
public:
    CAddinProcess();
    ~CAddinProcess();

    int Init(CComPtr<DTE2> pDTE, CComPtr<AddIn> pAddInInstance, CAddInModule *pAtlModule);

    HRESULT OpenSolution(const char *pszFileName);

    HRESULT OpenFile(const char *pszFileName, Window **ppWin);

    HRESULT OpenToolWindow(const char *pszWindowName, const char *pszWindowID, int nBmpId, Window **ppWindow);

    HRESULT OutputString(const char *pszCaption, const char *pszText);

    HRESULT OutputString(const char *pszText);

    HRESULT GetActiveWnd(Window **ppWnd);

    HRESULT GetActiveDoc(Document **ppDoc);

    HRESULT GetDoc(unsigned int nIndex, Document **pDoc);

    HRESULT GetCurProject(Project **ppProject);

    HRESULT GetProject(unsigned int nIndex, Project **ppProject);

    HRESULT GetProjectItem(Project *pProject, unsigned int nIndex, ProjectItem **ppProjectItem);

    HRESULT GetSubProjectItem(ProjectItem *pProjectItem, unsigned int nIndex, ProjectItem **ppProjectItem);

    HRESULT GetProjectProperty(Project *pProject, unsigned int nIndex, Property **ppProperty);

    HRESULT GetProjectItemProperty(ProjectItem *pProjectItem, unsigned int nIndex, Property **ppProperty);

    HRESULT GetProjectItemProperty(ProjectItem *pProjectItem, const char *name, Property **ppProperty);

    HRESULT GetSelectedItem(unsigned int nIndex, SelectedItem **ppSelectedItem);

    HRESULT GetWndSelection(Window *pWnd, TextSelection **ppSelection);

    HRESULT GetCommandBar(unsigned int nIndex, CommandBar **ppCommandBar);

    HRESULT GetCommandBar(const char *pszName, CommandBar **ppCommandBar);

    HRESULT GetCommandBarControls(unsigned int nIndex, CommandBarControls **ppCommandBarControls);

    HRESULT GetCommandBarControls(const char *pszName, CommandBarControls **ppCommandBarControls);

    HRESULT GetCommandBarControls(CommandBar *pCommandBar, CommandBarControls **ppCommandBarControls);

    HRESULT GetCommandBarControl(CommandBarControls *pControls, unsigned int nIndex, CommandBarControl **ppControl);

    HRESULT GetCommandBarControl(const char *pszName, unsigned int nIndex, CommandBarControl **ppControl);

    HRESULT GetCommand(unsigned int nIndex, Command **ppCommand);

    HRESULT GetCommand(const char *pszName, Command **ppCommand);

    HRESULT GetWindow(const char *pszName, Window **ppWindow);

    HRESULT GetWindow(unsigned int nIndex, Window **ppWindow);

    HRESULT GetAllCommandBar(LIST_STR &lstCommandBar);

    HRESULT GetAllCommand(LIST_STR &lstCommand);

    HRESULT GetAllWindow(LIST_STR &lstWindow);

    HRESULT GetAllControl(CommandBarControls *pControls, LIST_STR &lstControl);

    std::string  GetText(Document *pDoc, int nLineNum);

    std::string  GetProjectItemName(ProjectItem *pProjectItem);

    std::string  GetPropertyName(Property *pProperty);

    std::string  GetPropertyValue(Property *pProperty);

    std::string  GetSolutionFilename();

    std::string  GetSolutionPath();

    std::string  GetCurProjectName();

    std::string  GetCurProjectPath();

    std::string  GetCommandBarControlName(CommandBarControl *pControl);

    HRESULT InsertText(Document *pDoc, int nLineNum, const char *pszText);

    HRESULT AddCommand(const char *pszName, const char *pszButtonText, const char *pszTooltip, int nBmp, Command **ppCommand);

    HRESULT SetCommandName(int commandBarControlsIndex, const char *commandName, const char *newName);

    HRESULT DeleteCommand(int commandBarControlsIndex, const char *pszName);

    HRESULT AddCommandBar(const char *pszName, CommandBar *pParent, int pos, IDispatch **ppCommandBar);

    bool getInit() { return m_bInit; }

    void Test(void);

    std::string BstrToStr(BSTR bstr);

    std::string CLSIDToProgID(const char *clsid);

//protected:
    bool                        m_bInit;
    CAddInModule                *m_pAtlModule;
    CComPtr<DTE2>               m_pDTE;
    CComPtr<AddIn>              m_pAddInInstance;

    CComPtr<ItemOperations>     m_pOperations;
    CComPtr<Documents>          m_pDocs;
    CComPtr<Windows>            m_pWindows;
    CComPtr<Commands>           m_pCommands;
    CComPtr<Commands2>          m_pCommands2;
    CComPtr<_CommandBars>       m_pCommandBars;
    CComQIPtr<_Solution>        m_pSolution;
    CComPtr<Projects>           m_pProjects;
    CComPtr<SelectedItems>      m_pSelectedItems;
    CComPtr<UIHierarchy>        m_pUIHierarchy;
    CComPtr<StatusBar>          m_pStatusBar;
    CComPtr<Events>             m_pEvents;
    CComPtr<_DocumentEvents>    m_pDocEvents;
};