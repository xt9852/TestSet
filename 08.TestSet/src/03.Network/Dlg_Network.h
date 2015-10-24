
#pragma once
// #include "11.Common/XmlConfig.h"
// #include "Srv/Srv_HTTP.h"
// #include "Srv/Srv_IOCP.h"
// #include "srv/Srv_RTSP.h"
// #include "Player/RealPlayer.h"


class CDlg_Network : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Network)

public:
    CDlg_Network(CWnd* pParent = NULL);
    virtual ~CDlg_Network();

    enum { IDD = IDD_3_NETWORK };

private:
//    bool UpdateFile(const char *file, CHttpConnection *http);

//     CXmlConfig          m_XmlCfg;
// 
//     XT_IOCP::CSrv_HTTP  m_SrvHTTP;
// 
//     XT_IOCP::CSrv_IOCP  m_SrvIOCP;
// 
//     XT_IOCP::CSrv_RTSP  m_SrvRTSP;
// 
//     CRealPlayer         m_Player;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButHttpServer();
    afx_msg void OnBnClickedButDown();
    afx_msg void OnBnClickedBtnPost();
    afx_msg void OnBnClickedBtnFtp();
    afx_msg void OnBnClickedBtnMongoose();
    afx_msg void OnBnClickedBtnWebservice();
    afx_msg void OnBnClickedBtnIocpServer();
    afx_msg void OnBnClickedBtnIocpClient();
    afx_msg void OnBnClickedBtnRtspServer();
    afx_msg void OnBnClickedBtnRtspClient();
};
