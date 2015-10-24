#pragma once

#include "resource.h"/*
#include "Srv\Srv_NAT.h"
#include "H264\H264.h"
#include "Common\VideoCapture.h"
#include "Sound\WaveIn.h"
#include "Sound\WaveOut.h"
#include "Sound\DirectSound1.h"


typedef struct _tagVideoInfo
{
    LONG    lLocX;	// 视频窗口x
    LONG    lLocY;	// 视频窗口y
    CH264	h264;	// H264压缩
}VIDEOINFO, *PVIDEOIFNO;
*/

// CDlg_NAT 对话框

class CDlg_NAT : public CDialog//, public CWaveIn, public CVideoCapture
{
    DECLARE_DYNAMIC(CDlg_NAT)

public:
    CDlg_NAT(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_NAT();

    // 对话框数据
    enum { IDD = IDD_DLG_NAT };

private:
//	CSrv_NAT	        m_SrvNAT;		    // 服务类	
    DWORD		        m_dwCurSelUserId;	// 当前列表选择的用户ID
    bool		        m_bToServer;		// 向服务器发数据
    CButton		        m_ccbIsServer;		// 选定按钮"server"
/*
    CH264		        m_h264;			    // 只用于压缩自己的视频	
    CWaveOut	        m_WaveOut;		    // 音频
    CDirectSound	    m_DS;
*/
public:
    CListCtrl	        m_lstUser;		    // 列表控件	
/*
    HDC		            m_hdc;			    // 用于显示视频
    HDRAWDIB	        m_hdib;
    BITMAPINFOHEADER*	m_pbmpheader;
*/
    BOOL InitVideo(void);
    BOOL InitH264(void);
    void UninitH264(void);
    void ShowAudio(int nId, DWORD dwAudioId, LPBYTE pbyData, int nLen);
 //   virtual void ProcAudio(char *pszData, DWORD dwLen);
 //   virtual void ProcVideo(LPBYTE pbyData,int nLen);

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLvnItemchangedNatList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDestroy();

    afx_msg void OnBnClickedButStartServer();
    afx_msg void OnBnClickedButStartClient();
    afx_msg void OnBnClickedNatButSendText();	
    afx_msg void OnBnClickedNatButToClient();	
    afx_msg void OnBnClickedNatButToServer();
};
