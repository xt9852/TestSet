// Dlg_PeerCast.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "Dlg_PeerCast.h"
#include ".\dlg_peercast.h"

class NOTIFYICONDATA2
{
public:
    DWORD cbSize;			// DWORD
    HWND hWnd;				// HWND
    UINT uID;				// UINT
    UINT uFlags;			// UINT
    UINT uCallbackMessage;	// UINT
    HICON hIcon;			// HICON
    char szTip[128];		// char[128]
    DWORD dwState;			// DWORD
    DWORD dwStateMask;		// DWORD
    char szInfo[256];		// char[256]
    UINT uTimeoutOrVersion; // UINT
    char szInfoTitle[64];	// char[64]
    DWORD dwInfoFlags;		// DWORD
    //GUID guidItem; > IE 6
};

NOTIFYICONDATA2 trayIcon;

char pasfHead[16384];
int  asflen = 0;
unsigned int streampos = 0;

static int currNotify=0;
static String trackTitle;
static String channelComment;

const char *pRootDir = "D:\\";
HWND mainWnd = NULL;

String iniFileName;
String exePath;
GnuID  lastPlayID;

static HMENU trayMenu,ltrayMenu;
bool   showGUI = true;
bool   allowMulti = false;
bool   killMe = false;
bool   allowTrayMenu = true;
int	   seenNewVersionTime = 0;
HICON  icon1,icon2;
ChanInfo chanInfo;
bool   chanInfoIsRelayed;

void   clearChannelPopup();
void   channelPopup(const char *title, const char *msg);


Sys * APICALL MyPeercastInst::createSys()
{
    return new WSys(mainWnd);
}


//--------------------------------------

const char * APICALL MyPeercastApp::getIniFilename()
{
    return iniFileName.cstr();
}

const char *APICALL MyPeercastApp::getClientTypeOS() 
{
    return PCX_OS_WIN32;
}

const char * APICALL MyPeercastApp::getPath()
{
    return exePath.cstr();
}

void APICALL MyPeercastApp::channelStop(ChanInfo *info)
{
    if (info->id.isSame(lastPlayID))
    {
        lastPlayID.clear();
        clearChannelPopup();
    }
}

void APICALL MyPeercastApp::updateSettings()
{
    //	setControls(true);
}

void APICALL MyPeercastApp ::printLog(LogBuffer::TYPE t, const char *str)
{
    //	ADDLOG(str,logID,true,NULL,t);
    if (logFile.isOpen())
    {
        logFile.writeLine(str);
        logFile.flush();
    }
}

void APICALL MyPeercastApp::channelStart(ChanInfo *info)
{
    lastPlayID = info->id;
    clearChannelPopup();
}

void APICALL MyPeercastApp::channelUpdate(ChanInfo *info)
{
    if (lastPlayID.isSet() && info && info->id.isSame(lastPlayID))
    {
        String tmp;
        tmp.append(info->track.artist);
        tmp.append(" ");
        tmp.append(info->track.title);

        if (!tmp.isSame(trackTitle))
        {
            if (ServMgr::NT_TRACKINFO & peercastInst->getNotifyMask())
            {
                trackTitle=tmp;
                clearChannelPopup();
                channelPopup(info->name.cstr(),trackTitle.cstr());
            }
        }
        else if (!info->comment.isSame(channelComment))
        {
            if (ServMgr::NT_BROADCASTERS & peercastInst->getNotifyMask())
            {
                channelComment = info->comment;
                clearChannelPopup();
                channelPopup(info->name.cstr(),channelComment.cstr());
            }
        }
    }
}

void APICALL MyPeercastApp::notifyMessage(ServMgr::NOTIFY_TYPE type, const char *msg)
{
    currNotify = type;

    if (type == ServMgr::NT_UPGRADE)
    {
        trayIcon.uFlags = NIF_ICON;
        trayIcon.hIcon = icon2;
    }
    else
    {
        trayIcon.uFlags = NIF_ICON;
        trayIcon.hIcon = icon1;
    }

    const char *title="";

    switch(type)
    {
    case ServMgr::NT_UPGRADE:
        title = "Upgrade alert";
        break;
    case ServMgr::NT_PEERCAST:
        title = "Message from PeerCast:";
        break;
    }
    if (type & peercastInst->getNotifyMask())
    {
        trayIcon.uFlags |= 16;
        trayIcon.uTimeoutOrVersion = 10000;
        strncpy(trayIcon.szInfo,msg,sizeof(trayIcon.szInfo)-1);
        strncpy(trayIcon.szInfoTitle,title,sizeof(trayIcon.szInfoTitle)-1);
        Shell_NotifyIcon(NIM_MODIFY, (NOTIFYICONDATA*)&trayIcon);
    }
}

void clearChannelPopup()
{
    trayIcon.uFlags = NIF_ICON|16;
    trayIcon.uTimeoutOrVersion = 10000;
    strncpy(trayIcon.szInfo,"",sizeof(trayIcon.szInfo)-1);
    strncpy(trayIcon.szInfoTitle,"",sizeof(trayIcon.szInfoTitle)-1);
    Shell_NotifyIcon(NIM_MODIFY, (NOTIFYICONDATA*)&trayIcon);
}

void channelPopup(const char *title, const char *msg)
{
    String both;

    both.append(msg);
    both.append(" (");
    both.append(title);
    both.append(")");

    trayIcon.uFlags = NIF_ICON|NIF_TIP;
    strncpy(trayIcon.szTip, both.cstr(),sizeof(trayIcon.szTip)-1);
    trayIcon.szTip[sizeof(trayIcon.szTip)-1]=0;

    trayIcon.uFlags |= 16;
    trayIcon.uTimeoutOrVersion = 10000;
    strncpy(trayIcon.szInfo,msg,sizeof(trayIcon.szInfo)-1);
    strncpy(trayIcon.szInfoTitle,title,sizeof(trayIcon.szInfoTitle)-1);

    Shell_NotifyIcon(NIM_MODIFY, (NOTIFYICONDATA*)&trayIcon);
}

/*
void SendAllUserAsfHead(char *pcData,WORD wLength)
{
USERSTRLIST ul;
USERONLINEINFO uoli;
g_Process.m_pUserOnlineInfo->GetUserList(ul);
POSITION pos = ul.GetHeadPosition();
while(pos)
{
ZeroMemory(&uoli,sizeof(USERONLINEINFO));
CString dwUserId = ul.GetNext(pos);

g_Process.m_pUserOnlineInfo->GetOnlineUserInfoById(dwUserId,uoli);
COMMHEAD chAddress;
memcpy(&chAddress.pcIP[0],&uoli.pcIPV6Ip[0],160);
chAddress.usPort = htons(uoli.saiPublic.sin_port);
g_Process.SendAsfHead(uoli.dwUserId,&chAddress);

}
}


void SendAllUserData(char *pcData,WORD wLength,DWORD dwPos)
{
USERSTRLIST ul;
USERONLINEINFO uoli;
g_Process.m_pUserOnlineInfo->GetUserList(ul);
POSITION pos = ul.GetHeadPosition();
while(pos)
{
ZeroMemory(&uoli,sizeof(USERONLINEINFO));
CString dwUserId = ul.GetNext(pos);

g_Process.m_pUserOnlineInfo->GetOnlineUserInfoById(dwUserId,uoli);
COMMHEAD chAddress;
memcpy(&chAddress.pcIP[0],&uoli.pcIPV6Ip[0],160);
chAddress.usPort = htons(uoli.saiPublic.sin_port);
g_Process.SendAsfData(uoli.dwUserId,pcData,wLength,&chAddress,dwPos);

}
}

*/
//----------------------------------------------------------------------------------------

IMPLEMENT_DYNAMIC(CDlg_PeerCast, CDialog)
CDlg_PeerCast::CDlg_PeerCast(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_PeerCast::IDD, pParent)
{
}

CDlg_PeerCast::~CDlg_PeerCast()
{
}

void CDlg_PeerCast::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_PeerCast, CDialog)
    ON_BN_CLICKED(IDC_PEERCAST_BUT, OnBnClickedPeercastBut)
END_MESSAGE_MAP()


void CDlg_PeerCast::OnBnClickedPeercastBut()
{
    CString strIniFile(g_ProFile.m_strCurPath + _T("\\res\\peercast\\peercast.ini"));
    CString strPath(g_ProFile.m_strCurPath + _T("\\res\\peercast\\"));

    iniFileName.set(strIniFile);
    exePath.set(strPath);

    peercastInst = new MyPeercastInst();
    peercastApp = new MyPeercastApp();

    peercastInst->init();

    GetDlgItem(IDC_PEERCAST_BUT)->EnableWindow(FALSE);
}
