
#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_Main.h"
#include "00.Finger/Dlg_Finger.h"
#include "01.Media/my/Dlg_Media.h"
#include "02.P2P/Dlg_P2P.h"
#include "03.Network/Dlg_Network.h"
// #include "Dlg_UI.h"
#include "05.CPU/Dlg_CPU.h"
#include "06.EMule/Dlg/Dlg_Emule.h"
#include "07.Database/Dlg_DB.h"
// #include "Dlg_DataStruct.h"
#include "11.Common/mdump.h"

// 用于检测内存泄漏,Visual Leak Detector
// #include "vld/vld.h"
// #pragma comment(lib, "../10.thirdParty/lib/vld/vld32.lib")

#ifdef _DEBUG
#pragma comment(lib, "../10.thirdParty/lib/glog/libglogd.lib")
#else
#pragma comment(lib, "../10.thirdParty/lib/glog/libglog.lib")
#endif

// 异常时生成dmp文件
extern CMiniDumper g_theCrashDumper;

// 任务栏图标的消息
UINT WM_MY_NOTIFYICON = RegisterWindowMessage(_T("WM_MY_NOTIFYICON"));

// 更改本exe文件结构,添加1个区段,此区段内所有定义的变量都是共享的
// 设置名为Shared的数据段属性。
// /SECTION就表示为这是一个数据区间，R——Read读，W——Write写，S——Share共享。
#pragma data_seg("Shared")
volatile LONG g_lApplicationInstances = 0;
char szString[MAX_PATH] = "Shared string";
#pragma data_seg()

#pragma comment(linker, "/Section:Shared,RWS") 


CDlg_Main::CDlg_Main(CWnd* pParent /*=NULL*/)
    : CDialog(CDlg_Main::IDD, pParent),
    curDlg_(NULL)
{
    m_hIcon = AfxGetApp()->LoadIcon("CONTACT0");

    memset(dlg_, 0, sizeof(dlg_));
}

void CDlg_Main::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MAIN_COMBO, comboMain_);
}

BEGIN_MESSAGE_MAP(CDlg_Main, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
    ON_WM_CLOSE()
    ON_COMMAND(ID_MAIN_MENU_SHOW,               OnMenuShow)
    ON_COMMAND(ID_MAIN_MENU_EXIT,               OnMenuExit)
    ON_COMMAND(ID_MAIN_MENU_AUTORUN,            OnMenuAutorun)
    ON_COMMAND(ID_MAIN_MENU_CLOSE_MIN,          OnMenuCloseMin)
    ON_BN_CLICKED(IDC_MAIN_BTN_CREATE,          OnBnClickedMainBtnCreate)
    ON_CBN_SELCHANGE(IDC_MAIN_COMBO,            OnSelchangeComboMain)
    ON_REGISTERED_MESSAGE(WM_MY_NOTIFYICON,     OnNotifyIcon)
END_MESSAGE_MAP()


BOOL CDlg_Main::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    //-------------------------------------------------------------------------

    CoInitialize(NULL);
    AfxInitRichEdit();

    // 初使化Google日志库
    google::InitGoogleLogging("");

    // 全局的参数
    LIST_STR list;
    list.push_back("CONTACT0");
    list.push_back("CONTACT1");
    list.push_back("CONTACT2");
    list.push_back("CONTACT3");
    list.push_back("CONTACT4");

    g_ProFile.Init(list);
    g_theCrashDumper.Enable("TestSet", true);

    //-------------------------------------------------------------------------

    // 任务栏小图标
    sysTray_.Create(NULL, WM_MY_NOTIFYICON, "测试集", NULL, IDR_MAIN_MENU);
    sysTray_.SetImageList(g_ProFile.getImageList());
    sysTray_.Animate(500);

    //-------------------------------------------------------------------------

    comboMain_.InsertString(DLG_FINGER,     "指纹识别");
    comboMain_.InsertString(DLG_MEDIA,      "多媒体");
    comboMain_.InsertString(DLG_P2P,        "P2P软件升级");
    comboMain_.InsertString(DLG_NETWORK,    "网络");
    comboMain_.InsertString(DLG_UI,         "界面");
    comboMain_.InsertString(DLG_CPU,        "虚拟CPU");
    comboMain_.InsertString(DLG_EMULE,      "电驴");
    comboMain_.InsertString(DLG_DATABASE,   "数据库");
    comboMain_.InsertString(DLG_ALGORITHM,  "算法");
    comboMain_.SetCurSel(0);

    return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CDlg_Main::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CDlg_Main::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// 小图标的消息
LRESULT CDlg_Main::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
    switch(lParam)
    {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        {
            this->ShowWindow(IsWindowVisible()?SW_HIDE:SW_SHOW);
        }
        break;
    }
    return 0;
}

// 注消窗体
void CDlg_Main::OnDestroy()
{
    for (int i = 0; i < DLG_ALL; i++)
    {
        if (NULL != dlg_[i])
        {
            dlg_[i]->DestroyWindow();
            delete dlg_[i];
        }
    }

    sysTray_.DestroyWindow();

    CDialog::OnDestroy();
}

// 切换当前显示的窗体
void CDlg_Main::OnSelchangeComboMain()
{
    int nIndex = comboMain_.GetCurSel();

    if (NULL != curDlg_)
    {
        curDlg_->ShowWindow(SW_HIDE);
    }

    if (NULL == dlg_[nIndex])
    {
        return;
    }

    dlg_[nIndex]->ShowWindow(SW_SHOW);

    curDlg_ = dlg_[nIndex];
}

// 按钮创建窗体
void CDlg_Main::OnBnClickedMainBtnCreate()
{
    CRect rcWnd;
    this->GetClientRect(&rcWnd);
    rcWnd.top += 50;

    int nIndex = comboMain_.GetCurSel();

    if (NULL != curDlg_)
    {
        curDlg_->ShowWindow(SW_HIDE);
    }

    if (NULL == dlg_[nIndex])
    {
        int nID = 0;
        curDlg_ = NewDlg(nIndex, nID);
        curDlg_->Create(nID, this);
        curDlg_->MoveWindow(rcWnd);
    }
    else
    {
        curDlg_ = dlg_[nIndex];
    }

    curDlg_->ShowWindow(SW_SHOW);
}

// 创建窗体内存
// nIndex [IN]  序号
// nID    [OUT] 窗体资源ID
CDialog* CDlg_Main::NewDlg(int nIndex, int &nID)
{
    if ((nIndex < 0) || (nIndex >= DLG_ALL)) return NULL;

    switch(nIndex)
    {
    case DLG_FINGER:
        {
            dlg_[nIndex] = new CDlg_Finger;
            nID = CDlg_Finger::IDD;
            break;
        }
    case DLG_MEDIA:
        {
            dlg_[nIndex] = new CDlg_Media;
            nID = CDlg_Media::IDD;
            break;
        }
    case DLG_P2P:
        {
            dlg_[nIndex] = new CDlg_P2P;
            nID = CDlg_P2P::IDD;
            break;
        }
    case DLG_NETWORK:
        {
            dlg_[nIndex] = new CDlg_Network;
            nID = CDlg_Network::IDD;
            break;
        }
//     case DLG_UI:
//         {
//             dlg_[nIndex] = new CDlg_UI;
//             nID = CDlg_UI::IDD;
//             break;
//         }
    case DLG_CPU:
        {
            dlg_[nIndex] = new CDlg_CPU;
            nID = CDlg_CPU::IDD;
            break;
        }
//     case DLG_EMULE:
//         {
//             dlg_[nIndex] = new CDlg_Emule;
//             nID = CDlg_Emule::IDD;
//             break;
//         }
    case DLG_DATABASE:
        {
            dlg_[nIndex] = new CDlg_DB;
            nID = CDlg_DB::IDD;
            break;
        }
//     case DLG_ALGORITHM:
//         {
//             dlg_[nIndex] = new CDlg_Algorithm;
//             nID = CDlg_Algorithm::IDD;
//             break;
//         }
    }

    return dlg_[nIndex];
}

// 菜单，显示或隐藏窗体
void CDlg_Main::OnMenuShow()
{
    this->ShowWindow(IsWindowVisible()?SW_HIDE:SW_SHOW);
}

// 菜单，退出
void CDlg_Main::OnMenuExit()
{
    OnOK();
}

// 菜单，开机自动运行
void CDlg_Main::OnMenuAutorun()
{
}

// 菜单，最小化到任务栏
void CDlg_Main::OnMenuCloseMin()
{
}

