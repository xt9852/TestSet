
#include "stdafx.h"
#include "resource.h"
#include "Dlg_P2P.h"
#include "P2PProtocol.h"
#include "P2PFileOperator.h"

#define TESTSET_PROJECT_ID  100
#define OLD_VERSION         "1.0.0.1"
#define NEW_VERSION         "1.0.0.2"

IMPLEMENT_DYNAMIC(CDlg_P2P, CDialog)
CDlg_P2P::CDlg_P2P(CWnd* pParent /*=NULL*/)
    :CDialog(CDlg_P2P::IDD, pParent),
    getTaskTime_(0)
{
    fileListMd5_[0] = _T('\0');
}

CDlg_P2P::~CDlg_P2P()
{
}

void CDlg_P2P::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_P2P_TAB,         tabCtrl_);
    DDX_Control(pDX, IDC_P2P_LIST_FILE,   fileCtrl_);
    DDX_Control(pDX, IDC_P2P_LIST_TASK,   taskCtrl_);
    DDX_Control(pDX, IDC_P2P_LIST_PEER,   peerCtrl_);
    DDX_Control(pDX, IDC_P2P_LIST_LAYOUT, layoutCtrl_);
}

BEGIN_MESSAGE_MAP(CDlg_P2P, CDialog)
    ON_WM_TIMER()
    ON_NOTIFY(TCN_SELCHANGE, IDC_P2P_TAB,   &CDlg_P2P::OnTcnSelchangeP2pTab)
    ON_BN_CLICKED(IDC_P2P_BTN_SERVER,       &CDlg_P2P::OnBnClickedP2pBtnServer)
    ON_BN_CLICKED(IDC_P2P_BTN_CLIENT,       &CDlg_P2P::OnBnClickedP2pBtnClient)
    ON_BN_CLICKED(IDC_P2P_BTN_LIST,         &CDlg_P2P::OnBnClickedP2pBtnList)
END_MESSAGE_MAP()

BOOL CDlg_P2P::OnInitDialog()
{
    CDialog::OnInitDialog();

    GetDlgItem(IDC_P2P_IPADDRESS)->SetWindowText(g_ProFile.getIp(0));
    GetDlgItem(IDC_P2P_EDIT_PORT)->SetWindowText("8080");
    GetDlgItem(IDC_P2P_EDIT_NEW_VERSION)->SetWindowText(NEW_VERSION);
    GetDlgItem(IDC_P2P_EDIT_OLD_VERSION)->SetWindowText(OLD_VERSION);

    CRect rc;
    GetClientRect(&rc);

    int bottom = rc.bottom;
    rc.bottom = rc.top + 20;

    tabCtrl_.InsertItem(0, _T("file"));
    tabCtrl_.InsertItem(1, _T("task"));
    tabCtrl_.InsertItem(2, _T("peer"));
    tabCtrl_.InsertItem(3, _T("layout"));
    tabCtrl_.MoveWindow(rc);

    rc.top += 25;
    rc.bottom = bottom - 20;

    fileCtrl_.MoveWindow(&rc);
    fileCtrl_.SetExtendedStyle(fileCtrl_.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    fileCtrl_.InsertColumn(0, "md5",        0, 100);
    fileCtrl_.InsertColumn(1, "name",       0, 100);
    fileCtrl_.InsertColumn(3, "size",       0, 70);
    fileCtrl_.InsertColumn(4, "7zMd5",      0, 100);
    fileCtrl_.InsertColumn(5, "7zSize",     0, 70);

    taskCtrl_.MoveWindow(&rc);
    taskCtrl_.SetExtendedStyle(taskCtrl_.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    taskCtrl_.InsertColumn(0, "md5",        0, 50);
    taskCtrl_.InsertColumn(1, "path",       0, 100);
    taskCtrl_.InsertColumn(2, "state",      0, 70);
    taskCtrl_.InsertColumn(3, "size",       0, 70);
    taskCtrl_.InsertColumn(4, "finishSize", 0, 70);
    taskCtrl_.InsertColumn(5, "progress",   0, 50);

    taskCtrl_.InsertColumn(6, "upCount",    0, 50);
    taskCtrl_.InsertColumn(7, "upSize",     0, 50);
    taskCtrl_.InsertColumn(8, "downCount",  0, 50);
    taskCtrl_.InsertColumn(9, "downSize",   0, 50);

    taskCtrl_.InsertColumn(10, "fistRecvTime", 0, 70);
    taskCtrl_.InsertColumn(11, "lastRecvTime", 0, 70);
    taskCtrl_.InsertColumn(12, "fistSendTime", 0, 70);
    taskCtrl_.InsertColumn(13, "lastSendTime", 0, 70);

    taskCtrl_.InsertColumn(14, "downSpeed(K/S)", 0, 70);
    taskCtrl_.InsertColumn(15, "upSpeed(K/S)",   0, 70);

    peerCtrl_.MoveWindow(&rc);
    peerCtrl_.SetExtendedStyle(peerCtrl_.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    peerCtrl_.InsertColumn(0, "id",        0, 25);
    peerCtrl_.InsertColumn(1, "wanIp",     0, 105);
    peerCtrl_.InsertColumn(2, "wanPort",   0, 45);
    peerCtrl_.InsertColumn(3, "lanIp",     0, 105);
    peerCtrl_.InsertColumn(4, "lanPort",   0, 45);
    peerCtrl_.InsertColumn(5, "state",     0, 70);
    peerCtrl_.InsertColumn(6, "upCount",   0, 70);
    peerCtrl_.InsertColumn(7, "upSize",    0, 70);
    peerCtrl_.InsertColumn(8, "downCount", 0, 70);
    peerCtrl_.InsertColumn(9, "downSize",  0, 70);
    peerCtrl_.ShowWindow(SW_HIDE);

    layoutCtrl_.MoveWindow(&rc);
    layoutCtrl_.SetExtendedStyle(taskCtrl_.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    layoutCtrl_.InsertColumn(0, "name",      0, 50);
    layoutCtrl_.InsertColumn(1, "upCount",   0, 70);
    layoutCtrl_.InsertColumn(2, "upSize",    0, 70);
    layoutCtrl_.InsertColumn(3, "downCount", 0, 70);
    layoutCtrl_.InsertColumn(4, "downSize",  0, 70);
    layoutCtrl_.ShowWindow(SW_HIDE);

    layoutCtrl_.InsertItem(0, "task", 0);
    layoutCtrl_.SetItemText(0, 1, "0");
    layoutCtrl_.SetItemText(0, 2, "0");
    layoutCtrl_.SetItemText(0, 3, "0");
    layoutCtrl_.SetItemText(0, 4, "0");

    layoutCtrl_.InsertItem(1, "peer", 0);
    layoutCtrl_.SetItemText(1, 1, "0");
    layoutCtrl_.SetItemText(1, 2, "0");
    layoutCtrl_.SetItemText(1, 3, "0");
    layoutCtrl_.SetItemText(1, 4, "0");

    layoutCtrl_.InsertItem(2, "queue", 0);
    layoutCtrl_.SetItemText(2, 1, "0");
    layoutCtrl_.SetItemText(2, 2, "0");
    layoutCtrl_.SetItemText(2, 3, "0");
    layoutCtrl_.SetItemText(2, 4, "0");

    layoutCtrl_.InsertItem(3, "iocp", 0);
    layoutCtrl_.SetItemText(3, 1, "0");
    layoutCtrl_.SetItemText(3, 2, "0");
    layoutCtrl_.SetItemText(3, 3, "0");
    layoutCtrl_.SetItemText(3, 4, "0");
    layoutCtrl_.SetItemText(3, 4, "0");

    return TRUE;
}

#include "P2PFileOperator.h"

void CDlg_P2P::OnBnClickedP2pBtnServer()
{
    CString strIP;
    CString strPort;
    CString strPath;
    CString strSubDir;
    CString strFilelist;
    CString strFilelist7z;

    GetDlgItem(IDC_P2P_IPADDRESS)->GetWindowText(strIP);
    GetDlgItem(IDC_P2P_EDIT_PORT)->GetWindowText(strPort);
    GetDlgItem(IDC_P2P_EDIT_NEW_VERSION)->GetWindowText(strSubDir); // 只为测试实际运行时,应为程序所在目录

    strPath.Format("%s\\%s", g_ProFile.getPath(), strSubDir);
    strFilelist.Format("%s\\fileList.xml", strPath);
    strFilelist7z.Format("%s_7z\\fileList.xml.7z", strPath);

    DeleteFile(strFilelist);

    int ret = app_.Start(strPath, strIP, strPort);

    if (0 != ret) return;

    XT_P2P::P2PFileOperator fileOper;
    fileOper.UncompareZip7(strPath, strFilelist7z, strPath); // 只为测试
    app_.addUploadTaskList(strPath); // 只为测试

    GetDlgItem(IDC_P2P_BTN_CLIENT)->EnableWindow(TRUE);
    GetDlgItem(IDC_P2P_BTN_SERVER)->EnableWindow(FALSE);
}

void CDlg_P2P::OnBnClickedP2pBtnClient()
{
    CString strIP;
    CString strPort;
    CString strPath;

    GetDlgItem(IDC_P2P_IPADDRESS)->GetWindowText(strIP);
    GetDlgItem(IDC_P2P_EDIT_PORT)->GetWindowText(strPort);
    //GetDlgItem(IDC_P2P_EDIT_ADDR)->GetWindowText(strPath);

    app_.run(TESTSET_PROJECT_ID, strPath, strIP, strPort);
}

void CDlg_P2P::OnTcnSelchangeP2pTab(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;

    int showFile = SW_HIDE;
    int showTask = SW_HIDE;
    int showPeer = SW_HIDE;
    int showLayout = SW_HIDE;

    switch (tabCtrl_.GetCurSel())
    {
    case 0:
        {
            showFile = SW_SHOW;
            break;
        }
    case 1:
        {
            showTask = SW_SHOW;
            break;
        }
    case 2:
        {
            showPeer = SW_SHOW;
            break;
        }
    case 3:
        {
            showLayout = SW_SHOW;
            break;
        }
    }

    fileCtrl_.ShowWindow(showFile);
    taskCtrl_.ShowWindow(showTask);
    peerCtrl_.ShowWindow(showPeer);
    layoutCtrl_.ShowWindow(showLayout);
}

void CDlg_P2P::OnTimer(UINT_PTR nIDEvent)
{
    __super::OnTimer(nIDEvent);

    if (1000 != nIDEvent) return;

    UINT nowTime = GetTickCount();

    if (nowTime > getTaskTime_)
    {
        getTaskTime_ = nowTime + 2000;
        GetTaskInfo();
        GetPeerInfo();
        GetLayoutInfo();
    }
}

void CDlg_P2P::GetTaskInfo()
{
    XT_P2P::P2P_DATA_PTR_LIST dataList;
    XT_P2P::P2PInsideMsg getDataInfo;
    getDataInfo.setGetTaskInfo(XT_P2P::P2P_TASK_DATA_INFO, &dataList);

    //if (0 != enginer_.send(&getDataInfo)) return;

    XT_P2P::P2P_DATA_PTR_LIST::const_iterator iter = dataList.begin();

    for (; iter != dataList.end(); ++iter)
    {
        XT_P2P::P2PTaskDataInfo *dataInfo = (XT_P2P::P2PTaskDataInfo*)*iter;

        TCHAR temp[MAX_PATH] = _T("");

        LVFINDINFO info;
        info.flags = LVFI_PARTIAL|LVFI_STRING;
        info.psz = dataInfo->getMd5();

        int index = taskCtrl_.FindItem(&info);

        taskCtrl_.SetRedraw(FALSE);

        if (-1 == index) // 没找到
        {
            index = taskCtrl_.InsertItem(taskCtrl_.GetItemCount(), dataInfo->getMd5(), 0);

            taskCtrl_.SetItemText(index, 1, dataInfo->getFilename());

            _stprintf_s(temp, ARRAYSIZE(temp), _T("%I64d"), dataInfo->getFileSize());
            taskCtrl_.SetItemText(index, 3, temp);
        }
        
        taskCtrl_.SetItemText(index, 2, dataInfo->getStateStr());

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%I64d"), dataInfo->getFinishSize());
        taskCtrl_.SetItemText(index, 4, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%0.2f"), (float)dataInfo->getFinishSize() / dataInfo->getFileSize() * 100.0);
        taskCtrl_.SetItemText(index, 5, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getSendPackCount());
        taskCtrl_.SetItemText(index, 6, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getSendPackSize());
        taskCtrl_.SetItemText(index, 7, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getRecvPackCount());
        taskCtrl_.SetItemText(index, 8, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getRecvPackSize());
        taskCtrl_.SetItemText(index, 9, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getFirstRecvTime());
        taskCtrl_.SetItemText(index, 10, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getLastRecvTime());
        taskCtrl_.SetItemText(index, 11, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getFirstSendTime());
        taskCtrl_.SetItemText(index, 12, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getLastSendTime());
        taskCtrl_.SetItemText(index, 13, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%0.2f"), dataInfo->getRecvSpeed());
        taskCtrl_.SetItemText(index, 14, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%0.2f"), dataInfo->getSendSpeed());
        taskCtrl_.SetItemText(index, 15, temp);

        taskCtrl_.SetRedraw(TRUE);
    }

    dataList.clear();
}

void CDlg_P2P::GetPeerInfo()
{
    XT_P2P::P2P_DATA_PTR_LIST dataList;
    XT_P2P::P2PInsideMsg getDataInfo;
    getDataInfo.setGetPeerInfo(XT_P2P::P2P_PEER_DATA_INFO, &dataList);

    //if (0 != enginer_.send(&getDataInfo)) return;

    XT_P2P::P2P_DATA_PTR_LIST::const_iterator iter = dataList.begin();

    for (; iter != dataList.end(); ++iter)
    {
        XT_P2P::P2PPeerDataInfo *dataInfo = (XT_P2P::P2PPeerDataInfo*)*iter;

        TCHAR temp[MAX_PATH] = _T("");

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getId());

        LVFINDINFO info;
        info.flags = LVFI_PARTIAL|LVFI_STRING;
        info.psz = temp;

        int index = peerCtrl_.FindItem(&info);

        peerCtrl_.SetRedraw(FALSE);

        if (-1 == index) // 没找到
        {
            index = peerCtrl_.InsertItem(taskCtrl_.GetItemCount(), temp, 0);

            UINT ip = dataInfo->getWanIp();
            peerCtrl_.SetItemText(index, 1, inet_ntoa(*(in_addr*)&ip));

            _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), ntohs(dataInfo->getWanPort()));
            peerCtrl_.SetItemText(index, 2, temp);

            ip = dataInfo->getLanIp();
            peerCtrl_.SetItemText(index, 3, inet_ntoa(*(in_addr*)&ip));

            _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), ntohs(dataInfo->getLanPort()));
            peerCtrl_.SetItemText(index, 4, temp);
        }

        peerCtrl_.SetItemText(index, 5, dataInfo->getStateStr());

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getSendPackCount());
        peerCtrl_.SetItemText(index, 6, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getSendPackSize());
        peerCtrl_.SetItemText(index, 7, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getRecvPackCount());
        peerCtrl_.SetItemText(index, 8, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getRecvPackSize());
        peerCtrl_.SetItemText(index, 9, temp);

        peerCtrl_.SetRedraw(TRUE);
    }

    dataList.clear();
}

void CDlg_P2P::GetLayoutInfo()
{
    XT_P2P::P2P_DATA_PTR_LIST dataList;
    XT_P2P::P2PInsideMsg getDataInfo;
    getDataInfo.setGetLayoutInfo(XT_P2P::P2P_LAYOUT_DATA_INFO, &dataList);

    //if (0 != enginer_.send(&getDataInfo)) return;

    XT_P2P::P2P_DATA_PTR_LIST::const_iterator iter = dataList.begin();

    for (int i = 0; iter != dataList.end(); ++iter, i++)
    {
        XT_P2P::P2PDataInfo *dataInfo = (XT_P2P::P2PDataInfo*)*iter;

        LPCTSTR name = _T("");
        switch (i)
        {
        case 0: name = _T("task");  break;
        case 1: name = _T("peer");  break;
        case 2: name = _T("queue"); break;
        case 3: name = _T("iocp");  break;
        }

        TCHAR temp[MAX_PATH] = _T("");

        LVFINDINFO info;
        info.flags = LVFI_PARTIAL|LVFI_STRING;
        info.psz = name;

        int index = layoutCtrl_.FindItem(&info);

        if (-1 == index) continue;

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getRecvPackCount());
        layoutCtrl_.SetItemText(index, 1, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getRecvPackSize());
        layoutCtrl_.SetItemText(index, 2, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getSendPackCount());
        layoutCtrl_.SetItemText(index, 3, temp);

        _stprintf_s(temp, ARRAYSIZE(temp), _T("%d"), dataInfo->getSendPackSize());
        layoutCtrl_.SetItemText(index, 4, temp);

        layoutCtrl_.SetRedraw(TRUE);
    }

    dataList.clear();
}

typedef std::list<std::string> STRING_LIST;

#include "Zip/7z.h"

void CDlg_P2P::OnBnClickedP2pBtnList()
{
    CString newVerson;
    CString oldVerson;
    GetDlgItem(IDC_P2P_EDIT_NEW_VERSION)->GetWindowText(newVerson);
    GetDlgItem(IDC_P2P_EDIT_OLD_VERSION)->GetWindowText(oldVerson);

    STRING_LIST list;
    list.push_back(_T("/config.xml"));

    XT_P2P::P2PFileOperator fileOper;
    fileOper.CreateFileList(TESTSET_PROJECT_ID, g_ProFile.getPath(), newVerson, oldVerson, list);
}
