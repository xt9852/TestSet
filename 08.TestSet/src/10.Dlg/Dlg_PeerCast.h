
#pragma once
#include "Peercast\common\peercast.h"
#include "Peercast\common\channel.h"
#include "Peercast\common\servent.h"
#include "Peercast\common\servmgr.h"
#include "Peercast\win32\wsys.h"


class MyPeercastInst : public PeercastInstance
{
public:
    virtual Sys* APICALL createSys();
};

class MyPeercastApp : public PeercastApplication
{
public:
    MyPeercastApp()
    {
        char szLogName[MAX_PATH] = {_T("")};
        strcpy(szLogName, (LPCSTR)(LPCTSTR)g_ProFile.m_strCurPath);
        strcat(szLogName, _T("\\res\\peercast\\Peercast.log"));
        logFile.openWriteReplace(szLogName);
    }

    virtual const char* APICALL getPath();

    virtual const char* APICALL getIniFilename();
    virtual const char* APICALL getClientTypeOS();
    virtual void APICALL printLog(LogBuffer::TYPE t, const char *str);

    virtual void APICALL updateSettings();
    virtual void APICALL notifyMessage(ServMgr::NOTIFY_TYPE, const char *);

    virtual void APICALL channelStart(ChanInfo *);
    virtual void APICALL channelStop(ChanInfo *);
    virtual void APICALL channelUpdate(ChanInfo *);

    FileStream	logFile;

};


//-------------------------------------------------------------------------------

class CDlg_PeerCast : public CDialog
{
    DECLARE_DYNAMIC(CDlg_PeerCast)

public:
    CDlg_PeerCast(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_PeerCast();

    // 对话框数据
    enum { IDD = IDD_DLG_PEERCAST };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedPeercastBut();
};
