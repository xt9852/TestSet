/*

将SVN的bin目录中的SciLexer.dll改名为SciLexerTrue.dll
将本代码生成的dll,复制到bin目录中
将config.xml复制到bin目录中

config.xml内容如下:

<?xml version="1.0" encoding="GB2312" ?>
<XmlRoot>
  <!-- is_check是事检测BOM, need_bom是否需要BOM, type只检测此类型的文件-->
  <check_bom is_check="1" need_bom="0" type=".h|.c|.cpp">
    <!-- 当is_check为1时,表示不需要检测的文件 -->
    <!-- 当is_check为0时,表示需要检测的文件 -->
    <exclude name="odbc.c" />
  </check_bom>

  <commit>
    <!-- 不需要提交的文件 -->
    <exclude name="lim_mq_queue.h" />
    <exclude name="lim_statistics_info.h" />
    <exclude name="lim_statistics_info.c" />
    <exclude name="lim_service.h" />
    <exclude name="lim_serverutil.c" />
    <exclude name="lim_jvm.c" />
    <exclude name="odbc.c" />
    <exclude name="utility.c" />
    <exclude name="mem_chunk.h" />
    <exclude name="mem_chunk.c" />
    <exclude name="check_event.c" />
    <exclude name="garbagecollector.h" />
    <exclude name="TestSet.vs2010.sln" />
  </commit>
</XmlRoot>

*/

#include "stdafx.h"
#include "08.Algorithm/Base/MD5.h"
#include "08.Algorithm/Base/XTXml.h"
#include "07.Database/CppSQLite3.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <process.h>
#include <CommCtrl.h>
#include <psapi.h> // GetModuleBaseName

#define WM_SHOW_MSG (WM_USER + 123)
#define WM_EXIT     (WM_USER + 124)

class ScintillaWin;

typedef HRESULT (*Scintilla_DirectFunction_true)(ScintillaWin *sci, UINT iMessage, WPARAM wParam, LPARAM lParam);

typedef std::list<std::string> STRING_LIST;

XT_XML::xml g_xml;

HWND g_lhHook     = NULL; // 钩子句柄
HWND g_hCommitWnd = NULL; // 提交窗体句柄
HWND g_hOkButton  = NULL; // OK按钮句柄
UINT g_hShowMsgThreadId = 0;
std::string g_errorInfo;
bool g_exit = false;

//--------------------------------------------------------------------------------

HMODULE g_scilexer_dll_module = NULL; // SciLexer.dll模块句柄
Scintilla_DirectFunction_true g_scilexer_dll_fun = NULL; // SciLexer.dll的Scintilla_DirectFunction的函数指针

extern "C" __declspec(dllexport) 
HRESULT __stdcall Scintilla_DirectFunction(ScintillaWin *sci, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    if (NULL == g_scilexer_dll_fun) return -1;

    return g_scilexer_dll_fun(sci, iMessage, wParam, lParam);
}

//--------------------------------------------------------------------------------

// 查找子窗体回调函数
BOOL CALLBACK EnumChildWindowCallBack(HWND hWnd, LPARAM lParam)
{
    DWORD dwPid = 0;

    DWORD threadId = GetWindowThreadProcessId(hWnd, &dwPid); // 获得找到窗口所属的进程

    if (dwPid == lParam) // 判断是否是目标进程的窗口
    {
        char className[MAX_PATH] = "";
        char windowName[MAX_PATH] = "";

        GetClassName(hWnd, className, sizeof(className));
        GetWindowText(hWnd, windowName, sizeof(windowName));

        if (0 == strcmp(className, "SysListView32"))
        {
            g_hCommitWnd = hWnd;
        }
        else if (0 == strcmp(className, "Button") && 0 == strcmp(windowName, "&OK"))//Cancel
        {
            g_hOkButton = hWnd;
        }

        if (NULL != g_hCommitWnd && NULL != g_hOkButton)
        {
            return FALSE;
        }

        EnumChildWindows(hWnd, EnumChildWindowCallBack, lParam);    // 递归查找子窗口
    }

    return TRUE;
}

// 查找窗体回调函数
BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)  
{
    DWORD dwPid = 0;

    GetWindowThreadProcessId(hWnd, &dwPid); // 获得找到窗口所属的进程

    if (dwPid == lParam) // 判断是否是目标进程的窗口
    {
        EnumChildWindows(hWnd, EnumChildWindowCallBack, lParam);    // 继续查找子窗口
    }

    return TRUE;
}

//--------------------------------------------------------------------------------

typedef std::vector<std::string>  VECTOR_STR;

void TokenizeData(const char *srcData, const char *tokenize, VECTOR_STR &data)
{
    if (NULL == srcData) return;

    char *content = NULL;
    char temp[MAX_PATH*10] = "";
    strcpy_s(temp, srcData);

    char *token = strtok_s(temp, tokenize, &content);

    while (token != NULL)
    {
        data.push_back(token);
        token = (char*)strtok_s(NULL, tokenize, &content);
    }
}

/**
 *\fn        void GetConfigPath(char *path, int maxSize)
 *\brief     得到配置文件路径
 *\param[in] char * path 路径
 *\param[in] int maxSize 路径缓冲区大小
 *\return    void 0成功,其它失败
 */
void GetConfigPath(char *path, int maxSize)
{
    if (NULL == path || maxSize < 0) return;

    GetModuleFileName(NULL, path, maxSize);

    char *end = strrchr(path, '\\');

    if (NULL != end)
    {
        *end = '\0';
    }

    strcat_s(path, maxSize, "\\config.xml");
}

/**
 *\fn        void GetSvnRoot(const char *path, char *root, int maxSize)
 *\brief     得到SVN根路径
 *\param[in] const char * path 当前路径
 *\param[out]char * root SVN根路径
 *\param[in] int maxSize 最大长度
 *\return    void 0成功,其它失败
 */
void GetSvnRoot(const char *path, char *root, int maxSize)
{
    if (NULL == path || NULL == root || maxSize < 0) return;

    char temp[1024] = "";

    VECTOR_STR vectorStr;
    TokenizeData(path, "\\", vectorStr);

    for (UINT i = 0; i < vectorStr.size(); i++)
    {
        strcpy_s(temp, vectorStr[0].c_str());

        for (UINT j = 1; j <= i; j++)
        {
            strcat_s(temp, "\\");
            strcat_s(temp, vectorStr[j].c_str());
        }

        strcat_s(temp, "\\.svn\\wc.db");

        if (_access(temp, 0) == 0)
        {
            strncpy_s(root, maxSize, temp, strstr(temp, "\\.svn\\wc.db") - temp);
            return;
        }
    }
}

/**
 *\fn        int getSvnFileMd5(const char *svnRoot, const char *filename, char *md5, int maxSize)
 *\brief     得到SVN保存的上次的文件MD5
 *\param[in] const char * svnRoot SVN根路径
 *\param[in] const char * filename 
 *\param[in] char * md5 
 *\param[in] int maxSize 
 *\return    int 0成功,其它失败
 */
int getSvnFileMd5(const char *svnRoot, const char *filename, char *md5, int maxSize)
{
    if (NULL == svnRoot || NULL == filename || NULL == md5 || maxSize <= 0) return -1;

    char temp[1024] = "";
    char local[1024] = "";

    CppSQLite3DB db;

    _snprintf_s(temp, sizeof(temp)-1, "%s\\.svn/wc.db", svnRoot);

    db.open(temp);

    strcpy_s(local, filename);

    for (UINT i = 0; i < strlen(local); i++)
    {
        if ('\\' == local[i]) local[i] = '/';
    }

    _snprintf_s(temp, sizeof(temp)-1, "SELECT checksum FROM nodes WHERE local_relpath like '%s';", 
        &local[strlen(svnRoot)+1]);

    CppSQLite3Query q = db.execQuery(temp);

    if (!q.eof())
    {
        strncpy_s(temp, q.fieldValue(0), sizeof(temp)-1);
    }

    q.finalize();

    db.close();

    //--------------------------------------

    VECTOR_STR vectorStr;
    TokenizeData(temp, "$", vectorStr);

    if (vectorStr.size() <= 1)
    {
        return -2;
    }

    _snprintf_s(temp, sizeof(temp)-1, "%s\\.svn\\pristine\\%c%c\\%s.svn-base", 
        svnRoot, vectorStr[1].c_str()[0], vectorStr[1].c_str()[1], vectorStr[1].c_str());

    FILE *file = NULL;

    fopen_s(&file, temp, "rb");

    if (NULL == file) return -3;

    fseek(file, 0, SEEK_END);

    int len = ftell(file);
    char *buf = new char[len+10];

    fseek(file, 0, SEEK_SET);
    fread(buf, 1, len, file);
    fclose(file);

    CMD5 md;
    std::string str = md.getHashStr(buf, len);
    strcpy_s(md5, 33, str.c_str());

    delete buf;

    return 0;
}

/**
 *\fn        void GetCurrentPath(HWND wnd, char *path, int maxSize)
 *\brief     得到当前路径
 *\param[in] HWND wnd 窗体句柄
 *\param[out] char * path 路径
 *\param[in] int maxSize 路径缓冲区大小
 *\return    void 0成功,其它失败
 */
void GetCurrentPath(HWND wnd, char *path, int maxSize)
{
    if (NULL == path || maxSize < 0) return;

    GetWindowText(GetParent(wnd), path, maxSize);

    char *end = strchr(path, ' ');

    if (NULL != end)
    {
        *end = '\0';
    }
}

/**
 *\fn        int GetConfigData(const char *configFile, bool &checkBom, bool &needBom, 
                               STRING_LIST &checkTypeList, STRING_LIST &checkExcludeList, 
                               STRING_LIST &commitExcludeList)
 *\brief     提到配置文件数据
 *\param[in] const char * configFile 配置文件名
 *\param[in] bool & checkBom 否检查BOM
 *\param[in] bool & needBom 需要有BOM
 *\param[in] STRING_LIST & checkTypeList 检查文件类型类型列表
 *\param[in] STRING_LIST & checkExcludeList 检查BOM排除文件列表
 *\param[in] STRING_LIST & commitExcludeList 提交排除文件列表
 *\return    int 0成功,其它失败
 */
int GetConfigData(const char *configFile, 
    bool &checkBom, 
    bool &needBom,
    STRING_LIST &checkTypeList,
    STRING_LIST &checkExcludeList,
    STRING_LIST &commitExcludeList)
{
    checkBom = false;
    checkTypeList.clear();
    checkExcludeList.clear();
    commitExcludeList.clear();

    const char *value = NULL;
    XT_XML::TiXmlElementEx *checkNode; // 检测节点
    XT_XML::TiXmlElementEx *commitNode; // 提交节点
    XT_XML::TiXmlElementExs checkExcludeFile; // 检测的排除节点
    XT_XML::TiXmlElementExs commitExcludeFile; // 提交的排除节点

    if (!g_xml.LoadFile(configFile))
    {
        MessageBox(NULL, "得到配置文件错误", "错误", MB_OK);
        return -1;
    }

    checkNode = g_xml.GetRoot()->SelectSingleNode("check_bom");
    commitNode = g_xml.GetRoot()->SelectSingleNode("commit");

    if (NULL != checkNode)
    {
        value = checkNode->Attribute("is_check");

        if (NULL != value)
        {
            checkBom = (0 == strcmp(value, "1"));
        }

        value = checkNode->Attribute("need_bom");

        if (NULL != value)
        {
            needBom = (0 == strcmp(value, "1"));
        }

        value = checkNode->Attribute("type");

        if (NULL != value)
        {
            char temp[MAX_PATH*10] = "";
            strcpy_s(temp, value);

            char *content = NULL;
            char *token = strtok_s(temp, "|", &content);

            while (token != NULL)
            {
                checkTypeList.push_back(token);
                token = (char*)strtok_s(NULL, "|", &content);
            }
        }

        checkExcludeFile = checkNode->SelectNodes("exclude");

        for (int i = 0; i < checkExcludeFile.getCount(); i++)
        {
            value = checkExcludeFile[i]->Attribute("name");

            if (NULL != value)
            {
                checkExcludeList.push_back(value);
            }
        }
    }

    if (NULL != commitNode)
    {
        commitExcludeFile = commitNode->SelectNodes("exclude");

        for (int i = 0; i < commitExcludeFile.getCount(); i++)
        {
            value = commitExcludeFile[i]->Attribute("name");

            if (NULL != value)
            {
                commitExcludeList.push_back(value);
            }
        }
    }

    return 0;
}

/**
 *\fn        int GetFileCount(HWND wnd)
 *\brief     得到文件数量
 *\param[in] HWND wnd 窗体句柄
 *\return    int 0成功,其它失败
 */
int GetFileCount(HWND wnd)
{
    return (int)SendMessage(wnd, LVM_GETITEMCOUNT, 0, 0L);
}

/**
 *\fn        BOOL GetCheckState(HWND wnd, int nIndex)
 *\brief     设置列表是否为选中
 *\param[in] HWND wnd 窗体句柄
 *\param[in] int nIndex 序号
 *\return    BOOL 0成功,其它失败
 */
BOOL GetCheckState(HWND wnd, int nIndex)
{
    UINT uRet = (UINT)::SendMessage(wnd, LVM_GETITEMSTATE, nIndex, LVIS_STATEIMAGEMASK);
    return (uRet >> 12) - 1;
}

/**
 *\fn        void GetFileList(HWND wnd, STRING_LIST &list)
 *\brief     得到需要提交的文件列表
 *\param[in] HWND wnd 窗体句柄
 *\param[in] STRING_LIST & list 文件列表
 *\return    void 0成功,其它失败
 */
void GetFileList(HWND wnd, STRING_LIST &list)
{
    char name[1024] = "";
    LVITEM lvi = { 0 };
    int count = (int)SendMessage(wnd, LVM_GETITEMCOUNT, 0, 0L);

    for (int i = 0; i < count; i++)
    {
        if (GetCheckState(wnd, i))
        {
            ListView_GetItemText(wnd, i, 0, name, sizeof(name));

            list.push_back(name);
        }
    }
}

/**
 *\fn        void UnSelectFile(HWND wnd, const char *filename)
 *\brief     取消文件选中
 *\param[in] HWND wnd 窗体句柄
 *\param[in] const char * filename 文件名
 *\return    void 0成功,其它失败
 */
void UnSelectFile(HWND wnd, const char *filename)
{
    char name[1024] = "";
    LVITEM lvi = { 0 };
    int count = (int)SendMessage(wnd, LVM_GETITEMCOUNT, 0, 0L);

    for (int i = 0; i < count; i++)
    {
        if (GetCheckState(wnd, i))
        {
            ListView_GetItemText(wnd, i, 0, name, sizeof(name));

            if (0 == strcmp(filename, name))
            {
                ListView_SetCheckState(wnd, i, false);
                break;
            }
        }
    }
}

/**
 *\fn        bool isExcludeFile(const char *filename, STRING_LIST &excludeList)
 *\brief     此文件是否在排除列表中
 *\param[in] const char * filename 文件名
 *\param[in] STRING_LIST & excludeList 排除列表中
 *\return    bool 0成功,其它失败
 */
bool isExcludeFile(const char *filename, STRING_LIST &excludeList)
{
    if (filename == NULL) return false;

    STRING_LIST::const_iterator iter = excludeList.begin();

    for (; iter != excludeList.end(); ++iter)
    {
        const char *have = strstr(filename, iter->c_str());

        if (NULL != have)
        {
            return true;
        }
    }

    return false;
}

/**
 *\fn        bool isBom(const char *filename)
 *\brief     检查文件是否有BOM
 *\param[in] const char * filename 文件名
 *\return    bool true有,false无
 */
bool isBom(const char *filename)
{
    if (filename == NULL) return false;

    unsigned char buff[10] = "";

    FILE *file = NULL;

    fopen_s(&file, filename, "rb");

    if (NULL != file)
    {
        fread(buff, 1, 3, file);
        fclose(file);
    }

    return (buff[0] == 0xEF && buff[1] == 0xBB && buff[2] == 0xBF);
}

/**
 *\fn        void setBom(const char *filename, bool set, char *md5)
 *\brief     设置utf8的BOM
 *\param[in] const char * filename 文件名
 *\param[in] bool set 是否设置
 *\param[out]char * md5 文件MD5
 *\return    void 0成功,其它失败
 */
void setBom(const char *filename, bool set, char *md5)
{
    if (filename == NULL) return;

    int len = 0;
    char *buf = NULL;
    unsigned char bom[10] = {0xEF, 0xBB, 0xBF};

    FILE *file = NULL;

    fopen_s(&file, filename, "rb");

    if (NULL != file)
    {
        fseek(file, 0, SEEK_END);

        len = ftell(file);
        buf = new char[len+10];

        fseek(file, set?0:3, SEEK_SET);
        len = fread(buf, 1, len-(set?0:3), file);
        fclose(file);
    }

    file = NULL;

    fopen_s(&file, filename, "w+b");

    CMD5 md;
    md.Reset();

    if (NULL != file)
    {
        if (set)
        {
            fwrite(bom, 1, 3, file);
            md.Add(bom, 3);
        }

        fwrite(buf, 1, len, file);
        md.Add(buf, len);

        fclose(file);
        md.Finish();
    }

    if (NULL != md5)
    {
        std::string str = md.getHashStr();
        strcpy_s(md5, 33, str.c_str());
    }

    if (NULL != buf)
    {
        free(buf);
    }
}

/**
 *\fn        bool checkFileBom(const char *filename, bool needBom, 
                               STRING_LIST &checkTypeList, STRING_LIST &checkExcludeList)
 *\brief     检测文件BOM
 *\param[in] const char * filename 文件名
 *\param[in] needBom 是否需要BOM
 *\param[in] STRING_LIST & checkTypeList 检测类型列表
 *\param[in] STRING_LIST & checkExcludeList 排除的文件
 *\return    bool 是否成功
 */
bool checkFileBom(const char *filename, bool needBom, 
    STRING_LIST &checkTypeList, STRING_LIST &checkExcludeList)
{
    if (filename == NULL) return false;

    bool needCheck = false;
    const char *end = strrchr(filename, '.');

    if (NULL != end)
    {
        STRING_LIST::const_iterator iter = checkTypeList.begin();

        for (; iter != checkTypeList.end(); ++iter)
        {
            const char *file_end = strrchr(iter->c_str(), '.');

            if (0 == strcmp(file_end, end))
            {
                needCheck = true;
                break;
            }
        }
    }

    // 需要检测,不在排除列表中,并且不是Bom
    if (needCheck && !isExcludeFile(filename, checkExcludeList) && (needBom != isBom(filename)))
    {
        return false;
    }

    return true;
}

/**
 *\fn        int processCommit()
 *\brief     处理提交
 *\return    int 0成功,其它失败
 */
int processCommit()
{
    char cfgPath[1024] = "";
    char curPath[1024] = "";
    char svnRoot[1024] = "";
    char filename[1024] = "";
    char temp[1024] = "";
    int fileCount = 0;
    bool checkBom = false;
    bool needBom = false;
    STRING_LIST checkTypeList;
    STRING_LIST checkExcludeList;
    STRING_LIST commitExcludeList;
    STRING_LIST fileList;

    g_errorInfo = "";

    fileCount = GetFileCount(g_hCommitWnd);

    if (fileCount <= 0)
    {
        return 0;
    }

    GetConfigPath(cfgPath, sizeof(cfgPath)-1);
    GetCurrentPath(g_hCommitWnd, curPath, sizeof(curPath)-1);
    GetConfigData(cfgPath, checkBom, needBom, checkTypeList, checkExcludeList, commitExcludeList);
    GetFileList(g_hCommitWnd, fileList);
    GetSvnRoot(curPath, svnRoot, sizeof(svnRoot)-1);

    STRING_LIST::iterator preIter;
    STRING_LIST::iterator fileIter = fileList.begin();

    for (; fileIter != fileList.end(); ++fileIter)
    {
        if (isExcludeFile(fileIter->c_str(), commitExcludeList))
        {
            UnSelectFile(g_hCommitWnd, fileIter->c_str());

            _snprintf_s(temp, sizeof(temp)-1,"不需要提交 %s\n", fileIter->c_str());
            g_errorInfo += temp;

            *fileIter = "";
        }
    }

    if (checkBom)
    {
        char curMd5[33] = "";
        char lastMd5[33] = "";

        STRING_LIST::const_iterator fileIter = fileList.begin();

        for (; fileIter != fileList.end(); ++fileIter)
        {
            if (*fileIter == "") continue;

            _snprintf_s(filename, sizeof(filename)-1, "%s/%s", curPath, fileIter->c_str());

            if (!checkFileBom(filename, needBom, checkTypeList, checkExcludeList))
            {
                setBom(filename, needBom, curMd5);

                _snprintf_s(temp, sizeof(temp)-1, "%s需要签名 %s\n", !needBom?"不":"", fileIter->c_str());
                g_errorInfo += temp;

                getSvnFileMd5(svnRoot, filename, lastMd5, sizeof(lastMd5)-1);

                if (0 == _stricmp(curMd5, lastMd5))
                {
                    UnSelectFile(g_hCommitWnd, fileIter->c_str());
                }
            }
        }
    }

    if (0 != strcmp(g_errorInfo.c_str(), ""))
    {
        PostThreadMessage(g_hShowMsgThreadId, WM_SHOW_MSG, NULL, NULL);
        return 1;
    }

    return 0;
}

//--------------------------------------------------------------------------------

static unsigned __stdcall show_message_thread(void * pParam)
{
    MSG msg = {0};

    while (!g_exit)
    {
        if (!GetMessage(&msg, 0, 0, 0)) continue;

        switch (msg.message)
        {
        case WM_SHOW_MSG:
            {
                MessageBox(NULL, g_errorInfo.c_str(), "错误", MB_OK);
                break;
            }
        case WM_EXIT:
            {
                return 0;
            }
        }
    }

    return 0;
}

// 鼠标事件回调
LRESULT WINAPI MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx((HHOOK)g_lhHook, nCode, wParam, lParam);
    }

    if (NULL == g_hOkButton)
    {
        EnumWindows(EnumWindowCallBack, GetCurrentProcessId());
    }

    if (NULL == g_hOkButton)
    {
        MessageBox(NULL, "没有找到按钮句柄", "错误", MB_OK);
    }

    if (NULL == g_hCommitWnd)
    {
        MessageBox(NULL, "没有找到窗体句柄", "错误", MB_OK);
    }

    int ret = 0;
    LPMOUSEHOOKSTRUCT pMouseHook = (MOUSEHOOKSTRUCT FAR *) lParam;

    if (wParam == WM_LBUTTONDOWN && g_hOkButton == pMouseHook->hwnd)
    {
        ret = processCommit();
    }

    if (1 == ret)
    {
        return 1; // 返回一个非零的值表示我们已经将鼠标消息处理了，系统不会再将鼠标消息向下传递了
    }

    // 继续传递消息, 1-消息不传递,0-消息继续传递
    return CallNextHookEx((HHOOK)g_lhHook, nCode, wParam, lParam);
}

// 设置鼠标消息钩子
void StartHook()
{
    g_lhHook = (HWND)SetWindowsHookEx(WH_MOUSE, MouseProc, g_scilexer_dll_module, GetCurrentThreadId());

    if (NULL == g_lhHook)
    {
        MessageBox(NULL, "Hook不成功", "错误", MB_OK);
    }
}

// 取消钩子
void StopHook()
{
    UnhookWindowsHookEx((HHOOK)g_lhHook);
}

#pragma comment (lib,"Psapi.lib") // GetModuleBaseName

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
            g_scilexer_dll_module = LoadLibrary("SciLexerTrue.dll");

            if (NULL != g_scilexer_dll_module)
            {
                g_scilexer_dll_fun = (Scintilla_DirectFunction_true)GetProcAddress(g_scilexer_dll_module, 
                    "Scintilla_DirectFunction");

                char text[128] = "";
                GetModuleBaseName(GetCurrentProcess(), NULL, text, sizeof(text));

                if (0 == strcmp(text, "TortoiseProc.exe"))
                {
                    StartHook();
                }
            }

            if (0 == g_hShowMsgThreadId)
            {
                //_beginthreadex(NULL, 0, &show_message_thread, NULL, 0, &g_hShowMsgThreadId);
            }

            break;
        }
    case DLL_PROCESS_DETACH:
        {
            if (NULL != g_scilexer_dll_module)
            {
                StopHook();
                FreeLibrary(g_scilexer_dll_module);
            }

            if (0 != g_hShowMsgThreadId)
            {
                g_exit = true;
                PostThreadMessage(g_hShowMsgThreadId, WM_EXIT, NULL, NULL);
            }

            break;
        }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        {
            break;
        }
    }

    return TRUE;
}

