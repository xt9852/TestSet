// src\Dlg\Dlg_Skin_Dlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "src\Dlg\Dlg_Skin_Dlg2.h"
#include ".\dlg_skin_dlg2.h"


// CDlg_Skin_Dlg2 对话框

IMPLEMENT_DYNAMIC(CDlg_Skin_Dlg2, CDialog)

CDlg_Skin_Dlg2::CDlg_Skin_Dlg2(CWnd* pParent /*=NULL*/)
    : CXTDialog(CDlg_Skin_Dlg2::IDD, pParent)
{	
}

CDlg_Skin_Dlg2::~CDlg_Skin_Dlg2()
{
}

void CDlg_Skin_Dlg2::DoDataExchange(CDataExchange* pDX)
{
    CXTDialog::DoDataExchange(pDX);

    //服务器界面按钮
    DDX_Control(pDX,IDC_HA_BT_TITLE_MONEY,	m_btnMoney);
    DDX_Control(pDX,IDC_HA_BT_TITLE_SHOP,	m_btnShop);
    DDX_Control(pDX,IDC_HA_BT_TITLE_WEB,	m_btnWeb);
    DDX_Control(pDX,IDC_HA_BT_TITLE_FORUM,	m_btnForum);
    DDX_Control(pDX,IDC_HA_BT_TITLE_SET,	m_btnSet);
    DDX_Control(pDX,IDC_HA_BT_TITLE_EXIT,	m_btnExit);
    DDX_Control(pDX,IDC_HA_BT_TITLE_MIN,	m_btnTitleMin);
    DDX_Control(pDX,IDC_HA_BT_TITLE_MAX,	m_btnTitleMax);
    DDX_Control(pDX,IDC_HA_BT_TITLE_CLOSE,  m_btnTitleClose);
    DDX_Control(pDX,IDC_HA_BT_BACK,			m_btnBack);
    DDX_Control(pDX,IDC_HA_BT_GO,			m_btnGo);
    DDX_Control(pDX,IDC_HA_BT_REFRESH,		m_btnRefresh);
    DDX_Control(pDX,IDC_HA_BT_STOP,			m_btnStop);
    DDX_Control(pDX,IDC_HA_BT_HOME,			m_btnHome);
    DDX_Control(pDX,IDC_HA_BT_HELP,			m_btnHelp);
    DDX_Control(pDX,IDC_HA_BT_PLAYTHING,	m_btnPlaything);
    DDX_Control(pDX,IDC_HA_BT_ADD,			m_btnAdd);
    DDX_Control(pDX,IDC_HA_BT_FIND,			m_btnFind);
    DDX_Control(pDX,IDC_HA_BT_TEACH,		m_btnTeach);
    DDX_Control(pDX,IDC_HA_BT_CUSTOMER_SERVER,m_btnCustomerserver);
    DDX_Control(pDX,IDC_HA_BT_SET,			m_btnSetRoom);
    DDX_Control(pDX,IDC_HA_BT_EXIT,			m_btnExitRoom);
    DDX_Control(pDX,IDC_HA_BT_SEND,			m_btnSend);
    DDX_Control(pDX,IDC_HA_BT_SEND_SHAPE,	m_btnSendShape);
    DDX_Control(pDX,IDC_HA_BT_TEXT_SET,		m_btnSetText);
    DDX_Control(pDX,IDC_HA_COMBO_MESSAGE,	m_cbbInput);
    DDX_Control(pDX,IDC_HA_LIST_USER,		m_lstUser);
    DDX_Control(pDX,IDC_HA_TREE_SERVER,		m_treRoom);	
}


BEGIN_MESSAGE_MAP(CDlg_Skin_Dlg2, CXTDialog)
    ON_WM_MOUSEMOVE()
    //ON_WM_PAINT()
    ON_BN_CLICKED(IDC_HA_BT_TITLE_CLOSE,	OnBnClickedHaBtTitleClose)
    ON_BN_CLICKED(IDC_HA_BT_TITLE_EXIT,		OnBnClickedHaBtTitleClose)
    ON_BN_CLICKED(IDC_HA_BT_TITLE_MONEY,	OnBnClickedHaBtTitleMoney)
    ON_BN_CLICKED(IDC_HA_BT_TITLE_SHOP,		OnBnClickedHaBtTitleShop)
END_MESSAGE_MAP()


BOOL CDlg_Skin_Dlg2::OnInitDialog()
{
    CXTDialog::OnInitDialog();

	InitBkgBmp(1025, 769, 15, IDB_UI_PNG_HALL_RED);
	xtDC_.AddPngDC(1, IDB_UI_PNG_HALL_BLUE);

    m_btnTitleMin.Initial(962, 4, 16, 16, 503, 906, &xtDC_, "最小化");
    m_btnTitleMax.Initial(978, 4, 16, 16, 552, 906, &xtDC_, "最大化");
    m_btnTitleClose.Initial(994, 4, 16, 16, 601, 906, &xtDC_, "关闭");

    m_btnMoney.Initial(400, 16, 60, 56, 0, 770, &xtDC_, "游戏币");
    m_btnShop.Initial(500, 16, 60, 56, 181, 770, &xtDC_, "游戏商城");
    m_btnWeb.Initial(600, 16, 60, 56, 362, 770, &xtDC_, "主页");
    m_btnForum.Initial(700, 16, 60, 56, 543, 770, &xtDC_, "论谈");
    m_btnSet.Initial(800, 16, 60, 56, 724, 770, &xtDC_, "设置");
    m_btnExit.Initial(900, 16, 60, 56, 0, 828, &xtDC_, "退出");

// 	m_btnBack.Initial(310, 138, 21, 21, 597, 828, &xtDC_, "后退");
// 	m_btnGo.Initial(337, 138, 21, 21, 661, 828, &xtDC_, "前进");
// 	m_btnRefresh.Initial(364, 138, 21, 21, 725, 828, &xtDC_, "刷新");
// 	m_btnStop.Initial(391, 138, 21, 21, 789, 828, &xtDC_, "停止");
// 	m_btnHome.Initial(418, 138, 21, 21, 853, 828, &xtDC_, "主页");

    m_btnPlaything.Initial(310, 138, 59, 18, 0, 886, &xtDC_, "道具");
    m_btnAdd.Initial(375, 138, 59, 18, 178, 886, &xtDC_, "加入");
    m_btnFind.Initial(440, 138, 59, 18, 356, 886, &xtDC_, "查找");
    m_btnTeach.Initial(505, 138, 59, 18, 534, 886, &xtDC_, "教学");
    m_btnCustomerserver.Initial(570, 138, 59, 18, 712, 886, &xtDC_, "客服");
    m_btnSetRoom.Initial(635, 138, 59, 18, 0, 906, &xtDC_, "设置");
    m_btnExitRoom.Initial(700, 138, 59, 18, 178, 906, &xtDC_, "退出");
    m_btnHelp.Initial(920, 138, 75, 21, 0, 926, &xtDC_, "帮助");

    m_btnSend.Initial(210, 716, 16, 16, 356, 906, &xtDC_, "发送");
    m_btnSendShape.Initial(232, 716, 16, 16, 405, 906, &xtDC_, "发送图形");
    m_btnSetText.Initial(255, 716, 16, 16, 454, 906, &xtDC_, "文本设置");

    m_cbbInput.Initial(9, 714, 200, 100, 650, 906, &xtDC_);
    m_cbbInput.AddString("大家好很高兴见到各位！");
    m_cbbInput.AddString("快点吧，我等得花儿都要谢了！");
    m_cbbInput.AddString("@_@");
    m_cbbInput.AddString("*_*");
    m_cbbInput.AddString("*?*");

    CString strHeads("用户ID,80;用户昵称,110;房间,30;坐位,30;积分,30;局数,30;级别,30;金币,50;");
    m_lstUser.Initial(9, 112, 270, 215, 181, 828, &xtDC_, strHeads);

	char id[10] = "";
	for (int i = 0; i < 100; i++)
	{
		sprintf(id, "%d", i);
		m_lstUser.InsertItem(0, id);
	}

    m_treRoom.MoveWindow(9, 355, 269, 350);
    m_treRoom.SetImageList(g_ProFile.getImageList(), TVSIL_NORMAL);

    HTREEITEM Node[2];
    Node[0] = m_treRoom.AddNode(TVI_ROOT, "杀人游戏", 1000, 0);	
    Node[1] = m_treRoom.AddNode(Node[0], "东北区", 1100, 1);
    m_treRoom.AddNode(Node[0], "华北区", 1200, 1);
    m_treRoom.AddNode(Node[0], "华中区", 1300, 1);
    m_treRoom.AddNode(Node[1], "房间1（高手）", 1101, 2);
    m_treRoom.AddNode(Node[1], "房间2（新手）", 1101, 3);
    m_treRoom.AddNode(Node[1], "房间3（普通）", 1101, 4);
    m_treRoom.Expand(Node[0], TVE_EXPAND);

    GetDlgItem(IDC_HA_BT_LABEL_0)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_HA_BT_LABEL_1)->ShowWindow(SW_HIDE);

	CRect rcInput;
	m_cbbInput.GetWindowRect(&rcInput);

	DelRect(9, 112, 270, 215);
	DelRect(9, 355, 269, 350);
	DelRect(9, 714, 200, 21);

    return TRUE;
}

void CDlg_Skin_Dlg2::SetSkin(int nImage)
{
	CRect rc;
	GetClientRect(&rc);

    imageDC_ = xtDC_.SelectImageDC(nImage);
	BitBlt(compDC_, 0, 0, rc.Width(), rc.Height(), imageDC_, 0, 0, SRCCOPY);	

    m_btnTitleMin.ResetImage();
    m_btnTitleMax.ResetImage();
    m_btnTitleClose.ResetImage();

    m_btnMoney.ResetImage();
    m_btnShop.ResetImage();
    m_btnWeb.ResetImage();
    m_btnForum.ResetImage();
    m_btnSet.ResetImage();
    m_btnExit.ResetImage();
    
    //m_btnBack.ResetImage();
    //m_btnGo.ResetImage();
    //m_btnRefresh.ResetImage();
    //m_btnStop.ResetImage();
    //m_btnHome.ResetImage();

    m_btnPlaything.ResetImage();
    m_btnAdd.ResetImage();
    m_btnFind.ResetImage();
    m_btnTeach.ResetImage();
    m_btnCustomerserver.ResetImage();
    m_btnSetRoom.ResetImage();
    m_btnExitRoom.ResetImage();
    m_btnHelp.ResetImage();

    m_btnSend.ResetImage();
    m_btnSendShape.ResetImage();
    m_btnSetText.ResetImage();

    m_cbbInput.ResetImage();
    m_lstUser.ResetImage();

    OnPaint();
}

void CDlg_Skin_Dlg2::OnBnClickedHaBtTitleClose()
{
    OnCancel();
}

void CDlg_Skin_Dlg2::OnBnClickedHaBtTitleMoney()
{
    SetSkin(1);
}

void CDlg_Skin_Dlg2::OnBnClickedHaBtTitleShop()
{
    SetSkin(0);
}
