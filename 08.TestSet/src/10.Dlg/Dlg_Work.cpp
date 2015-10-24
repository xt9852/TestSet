
#include "stdafx.h"
#include "Dlg_Work.h"


IMPLEMENT_DYNAMIC(CDlg_Work, CDialog)
CDlg_Work::CDlg_Work(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Work::IDD, pParent)//,
//     m_pChatSrv(NULL),
//     m_pChatClt1(NULL),
//     m_pChatClt2(NULL)
{
}

CDlg_Work::~CDlg_Work()
{
//     if (NULL != m_pChatSrv)
//     {
//         m_pChatSrv->CloseWindow();
//         m_pChatSrv->DestroyWindow();
//         delete m_pChatSrv;
//     }
// 
//     if (NULL != m_pChatClt1)
//     {
//         m_pChatClt1->CloseWindow();
//         m_pChatClt1->DestroyWindow();
//         delete m_pChatClt1;
//     }
// 
//     if (NULL != m_pChatClt2)
//     {
//         m_pChatClt2->CloseWindow();
//         m_pChatClt2->DestroyWindow();
//         delete m_pChatClt2;
//     }
}

void CDlg_Work::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlg_Work, CDialog)
    ON_WM_PAINT() 
    ON_BN_CLICKED(IDC_WORK_BTN_CHATSRV, OnBnClickedWorkBtnChatsrv)
    ON_BN_CLICKED(IDC_WORK_BTN_CHATCLT, OnBnClickedWorkBtnChatclt)
END_MESSAGE_MAP()

BOOL CDlg_Work::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}


void CDlg_Work::OnPaint() 
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
        //dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

void CDlg_Work::OnBnClickedWorkBtnChatsrv()
{
//     if (NULL == m_pChatSrv)
//     {
//         m_pChatSrv = new Cchat_serverDlg;
//         m_pChatSrv->Create(IDD_DLG_CHAT_SRV);        
//     }
//     m_pChatSrv->ShowWindow(SW_SHOW);
}

void CDlg_Work::OnBnClickedWorkBtnChatclt()
{
//     if (NULL == m_pChatClt1)
//     {
//         m_pChatClt1 = new Cchat_clientDlg;
//         m_pChatClt1->Create(IDD_DLG_CHAT_CLT);
//     }
//     
//     m_pChatClt1->ShowWindow(SW_SHOW);
// 
//     if (NULL == m_pChatClt2)
//     {
//         m_pChatClt2 = new Cchat_clientDlg;
//         m_pChatClt2->Create(IDD_DLG_CHAT_CLT);
//     }
// 
//     m_pChatClt2->ShowWindow(SW_SHOW);
}
