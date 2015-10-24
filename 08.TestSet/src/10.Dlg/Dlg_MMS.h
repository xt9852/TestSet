#pragma once

#include "Srv\Srv_MMS.h"
#include "Player\WMPPlayer.h"

// CDlg_MMS 对话框

class CDlg_MMS : public CDialog
{
	DECLARE_DYNAMIC(CDlg_MMS)

public:
	CDlg_MMS(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_MMS();

// 对话框数据
	enum { IDD = IDD_DLG_MMS };

private:
	XT_IOCP::CSrv_MMS	m_SrvMMS;
	CWMPPlayer	m_MediaPlayer;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButStartServer();
	afx_msg void OnBnClickedButStartClient();
};
