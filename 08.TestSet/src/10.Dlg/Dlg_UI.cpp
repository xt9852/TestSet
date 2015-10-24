// src\Dlg\Dlg_Skin.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_UI.h"
#include "Dlg/Dlg_Skin_Dlg1.h"
#include "Dlg/Dlg_Skin_Dlg2.h"
#include "Dlg/Dlg_Skin_Dlg3.h"
#include "Dlg/TaskbarNotifier.h"
#include "Dlg/SCreenCluterDlg.h"
#include "UI/Ctrl/XTMessageBox.h"
#include <CommCtrl.h>


extern UINT WM_HTML_CLICK;

static UINT BASED_CODE indicators[] =
{
	ID_UI_STATBAR_INDICATOR_NISH,
};


IMPLEMENT_DYNAMIC(CDlg_UI, CDialog)
CDlg_UI::CDlg_UI(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_UI::IDD, pParent),
	m_pSkinDlg1(NULL),
	m_pSkinDlg2(NULL),
	m_pSkinDlg3(NULL),
	m_pSkinDlg4(NULL),
	m_bShowImage(FALSE),
	m_hGlobal(NULL),
	m_hBmp(NULL)
{
}

CDlg_UI::~CDlg_UI()
{
	if(NULL != m_pSkinDlg1)	delete m_pSkinDlg1;
	if(NULL != m_pSkinDlg2)	delete m_pSkinDlg2;
	if(NULL != m_pSkinDlg3)	delete m_pSkinDlg3;
	if(NULL != m_pSkinDlg4)	delete m_pSkinDlg4;

	if (NULL != m_hGlobal) GlobalFree(m_hGlobal);
	if (NULL != m_hBmp) DeleteObject(m_hBmp);
}

void CDlg_UI::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    
    DDX_Control(pDX, IDC_UI_CPU,		m_CPUStatus);
	DDX_Control(pDX, IDC_UI_RICHEDIT,	m_RichEdit);
	DDX_Control(pDX, IDC_UI_COLOR,		m_btnColor);
    DDX_ColorPicker(pDX, IDC_UI_COLOR,	m_rgbColor);
}

BEGIN_MESSAGE_MAP(CDlg_UI, CDialog)
    ON_WM_SIZE()
	ON_WM_ERASEBKGND()
    ON_WM_MOUSEMOVE()
    ON_WM_MBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()	
    ON_WM_MEASUREITEM()

    ON_BN_CLICKED(IDC_UI_BTN_LO,		OnBnClickedDlg1)
    ON_BN_CLICKED(IDC_UI_BTN_HA,		OnBnClickedDlg2)
    ON_BN_CLICKED(IDC_UI_BTN_GA,		OnBnClickedDlg3)
    ON_BN_CLICKED(IDC_UI_BTN_OK,		OnBnClickedDlg4)
    ON_BN_CLICKED(IDC_UI_BTN_SHOW,		OnBnClickedShowJpg)
    ON_BN_CLICKED(IDC_UI_BTN_SCREEN,	OnBnClickedScreenCap)
	ON_BN_CLICKED(IDC_UI_BTN_MESSAGEBOX,OnBnClickedMessageBox)
	ON_BN_CLICKED(IDC_UI_BTN_PNG,		OnBnClickedPng)
	ON_BN_CLICKED(IDC_UI_BTN_GIF,		OnBnClickedGif)   
	ON_BN_CLICKED(IDC_UI_BTN_JS,		OnBnClickedJS)

    ON_NOTIFY_EX(TTN_NEEDTEXT, 0,		OnToolTipText)
    ON_COMMAND(ID_UI_TOOLBAR_FILE_NEW,	OnToolBarCommand)
    ON_COMMAND(ID_UI_TOOLBAR_FILE_OPEN, OnToolBarCommand)
    ON_COMMAND(ID_UI_TOOLBAR_FILE_SAVE, OnToolBarCommand)
    ON_NOTIFY(LVN_GETDISPINFO, IDC_UI_LIST, OnLvnGetdispinfoUiList)
	
	ON_REGISTERED_MESSAGE(WM_HTML_CLICK, OnHtmlClick)

END_MESSAGE_MAP()



BOOL CDlg_UI::OnInitDialog()
{
    CDialog::OnInitDialog();

	// 加载DLL内的资源
// 	m_hResource = LoadLibrary(LPCTSTR("KitSource.dll"));
// 	if (NULL == m_hResource)
// 	{
// 		AfxMessageBox(_T("载入 KitSource.dll 错误!"));
// 
// 		return FALSE;
// 	}
// 	AfxSetResourceHandle(m_hResource);

    m_pSkinDlg1 = new CDlg_Skin_Dlg1();
    m_pSkinDlg1->Create(m_pSkinDlg1->IDD);
    m_pSkinDlg1->ShowWindow(SW_HIDE);

    m_pSkinDlg2 = new CDlg_Skin_Dlg2();
    m_pSkinDlg2->Create(m_pSkinDlg2->IDD);
    m_pSkinDlg2->ShowWindow(SW_HIDE);

    m_pSkinDlg3 = new CDlg_Skin_Dlg3();
    m_pSkinDlg3->Create(m_pSkinDlg3->IDD);
    m_pSkinDlg3->ShowWindow(SW_HIDE);

    m_pSkinDlg4 = new CTaskbarNotifier();
    m_pSkinDlg4->Create(this);
    m_pSkinDlg4->LoadConfiguration("CTaskbarNotifier");

	//---------------------------------------------------------------------------

    m_hDC = m_xtDC.Init(NULL, this->GetSafeHwnd());
    m_hCompDC = m_xtDC.AddCompDC();
    m_hBmpDC  = m_xtDC.AddPngDC(0, IDB_UI_PNG_HALL_RED);

    CImageList *pImageList = g_ProFile.getImageList();

    m_menuSubIcon.CreatePopupMenu();
    m_menuSubIcon.SetParam(pImageList, 20, 20, MIT_ICON);
    m_menuSubIcon.AppendMenu(MF_ENABLED, ID_FILE_OPEN, "", 0);
    m_menuSubIcon.AppendMenu(MF_ENABLED, ID_FILE_OPEN, "", 1);
    m_menuSubIcon.AppendMenu(MF_ENABLED, ID_FILE_OPEN, "", 2);
    m_menuSubIcon.AppendMenu(MF_ENABLED|MF_MENUBREAK,ID_FILE_OPEN, "", 3);
    m_menuSubIcon.AppendMenu(MF_ENABLED, ID_FILE_OPEN, "", 4);

    m_menuSubColor.CreatePopupMenu();
    m_menuSubColor.SetParam(pImageList, 32, 32, MIT_COLOR);
    m_menuSubColor.AppendMenu(MF_ENABLED, 0, "", 0xff0000);
    m_menuSubColor.AppendMenu(MF_ENABLED, 1, "", 0xffff00);
    m_menuSubColor.AppendMenu(MF_ENABLED, 2, "", 0x00ffff);

    m_menu.CreatePopupMenu();
    m_menu.SetParam(pImageList, 150, 20, MIT_XP);
    m_menu.AppendMenu(MF_ENABLED, ID_UI_TOOLBAR_FILE_NEW, "&New\tCtrl+N", 0);
    m_menu.AppendMenu(MF_ENABLED, ID_UI_TOOLBAR_FILE_OPEN, "&Open\tCtrl+O", 1);
    m_menu.AppendMenu(MF_ENABLED, ID_UI_TOOLBAR_FILE_CLOSE, "&Close", 2);
    m_menu.AppendMenu(MF_SEPARATOR, 0, "");
#pragma warning(disable : 4311)
    m_menu.AppendMenu(MF_POPUP, (UINT)m_menuSubIcon.m_hMenu, "Icon", 3);
    m_menu.AppendMenu(MF_POPUP, (UINT)m_menuSubColor.m_hMenu, "Color", 4);
#pragma warning(default : 4311)
    m_menu.EnableHook(TRUE);

    //---------------------------------------------------------------------------

    DWORD dwf = CXTOutBarCtrl::fDragItems|
		CXTOutBarCtrl::fEditGroups|
		CXTOutBarCtrl::fEditItems|
		CXTOutBarCtrl::fRemoveGroups|
        CXTOutBarCtrl::fRemoveItems|
		CXTOutBarCtrl::fAddGroups|
		CXTOutBarCtrl::fAnimation;

    if (!m_wndOutlookBar.Create(WS_CHILD|WS_VISIBLE, CRect(550,10,650,200), this, 102, dwf))
    {
        TRACE0("Failed to create outlook bar.");
        return -1;
    }

    int iFolder; // index of the added folder

    // set the image lists for the outlook bar.
    m_wndOutlookBar.SetImageList(g_ProFile.getImageList(), CXTOutBarCtrl::fLargeIcon);
    m_wndOutlookBar.SetImageList(g_ProFile.getImageList(), CXTOutBarCtrl::fSmallIcon);

    m_wndOutlookBar.SetAnimationTickCount(20);
    m_wndOutlookBar.SetAnimSelHighlight(200);

    // Add the first folder to the outlook bar.
    iFolder = m_wndOutlookBar.AddFolder("Shortcuts 1", 0);

    // Add items to the folder, syntax is folder, index, text, image, and item data.
    m_wndOutlookBar.InsertItem(iFolder, 1, "Item 1", 0, NULL);
    m_wndOutlookBar.InsertItem(iFolder, 2, "Item 2", 1, NULL);
    m_wndOutlookBar.InsertItem(iFolder, 3, "Item 3", 2, NULL);
    m_wndOutlookBar.InsertItem(iFolder, 4, "Item 4", 3, NULL);
    m_wndOutlookBar.InsertItem(iFolder, 5, "Item 5", 4, NULL);
    m_wndOutlookBar.InsertItem(iFolder, 6, "Item 6", 0, NULL);

    // Add the second folder to the outlook bar.
    iFolder = m_wndOutlookBar.AddFolder("Shortcuts 2", 1);

    // Add items to the folder, syntax is folder, index, text, image, and item data.
    m_wndOutlookBar.InsertItem(iFolder, 1, "Item 1", 0, NULL);
    m_wndOutlookBar.InsertItem(iFolder, 2, "Item 2", 1, NULL);

    // Select the first folder in the bar.
    m_wndOutlookBar.SetSelFolder(iFolder);

    m_wndOutlookBar.ShowWindow(SW_SHOW);

    //---------------------------------------------------------------------------

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CCS_NODIVIDER) ||
        !m_wndToolBar.LoadToolBar(IDR_UI_TOOLBAR))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;
    }

    m_wndToolBar.ShowWindow(SW_SHOW);

    pComboBox = m_wndToolBar.CreateCombo(ID_UI_TOOLBAR_BTN1, -1, 100);
    pEdit = m_wndToolBar.CreateEdit(ID_UI_TOOLBAR_BTN2, -1, 100);
    m_wndToolBar.CreateButton(ID_UI_TOOLBAR_BTN3, -1, 0, -1, IDR_MAIN_MENU);

    // add combobox item
    pComboBox->SetLocked(TRUE);
    if (pComboBox->GetWindowCtrl())
    {
        ((CComboBox*)pComboBox->GetWindowCtrl())->ResetContent();
        CString  str;
        for( int i=0 ; i < 10 ; i++ )
        {
            str.Format("%d",i);
            ((CComboBox*)pComboBox->GetWindowCtrl())->AddString(str);
        }

        ((CComboBox*)pComboBox->GetWindowCtrl())->SetCurSel(0);
    }

    ((CEdit*)pEdit->GetWindowCtrl())->SetWindowText("ToolBar Edit");

	//---------------------------------------------------------------------------

    m_StatusBar.Create(this);
    m_StatusBar.SetIndicators(indicators,1);
    m_StatusBar.SetPaneInfo(0, ID_UI_STATBAR_INDICATOR_NISH, SBPS_NORMAL, 100);

    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

    m_CPUStatus.MoveWindow(550, 220, 100, 100);
    m_CPUStatus.Init(1000);

// 	要向ListCtrl中插入大量的数据有三种方法：
// 	1，直接调用InsertItem()，插入10000条数据大约953毫秒
// 	2，在调用InsertItem()之前调用SetRedraw(FALSE)，在插入完数据后再调用 SetRedraw(TRUE)，插入10000条数据大约485毫秒
// 	3，不用调用InsertItem()，先调用SetItemCount(10000)，在其父窗体中处理LVN_GETDISPINFO消息，在消息处理函数内直接附值

// 	m_FastList.InsertColumn(0, "序号", LVCFMT_LEFT, 50);
// 	m_FastList.InsertColumn(1, "值", LVCFMT_LEFT, 50);
// 	m_FastList.SetItemCount(10000);

	std::string strPath;

	for (int i = 0; i < 5; i++)
	{
		m_pKeyFile[i] = NULL;
	}

	m_RichEdit.MoveWindow(290, 70, 250, 370);

	m_RichEdit.Init();

	m_RichEdit.AddLink("\nwww.google.com\n", NULL);
	m_RichEdit.AddText("\nWriteKeyText\n");

	m_pKeyFile[0] = m_RichEdit.AddTransFile("TestSet.exe", (UINT64)10*1024*1024*1024, 
		"res\\Contact0.ico", "开始", NULL);

	m_RichEdit.SetTransFile(m_pKeyFile[0], "", 1, (UINT64)6*1024*1024*1024);
	m_RichEdit.AddText("\n");
	m_RichEdit.AddText("\n");

	m_pKeyFile[1] = m_RichEdit.AddTransFile("TestSet.rc2", 1000, "", "开始", NULL);
	m_RichEdit.AddText("\n");

	strPath = g_ProFile.getPath() + std::string("\\res\\image\\001.gif");
	m_RichEdit.AddGif(strPath.c_str(), NULL);
	m_RichEdit.AddText("\n");

	strPath = g_ProFile.getPath() + std::string("\\res\\image\\001.jpg");
	m_pKeyFile[2] = m_RichEdit.AddImage(strPath.c_str(), NULL);
	m_RichEdit.AddText("\n");
/*
	strPath = g_ProFile.getPath() + std::string("\\res\\image\\Contact4.ico");
	m_RichEdit.AddImage(strPath.c_str(), NULL);
	m_RichEdit.AddText("\n");

	strPath = g_ProFile.getPath() + std::string("\\res\\image\\1002.gif");
	m_pKeyFile[3] = m_RichEdit.AddGif(strPath.c_str(), NULL);
	m_RichEdit.AddText("\n");

	strPath = g_ProFile.getPath() + std::string("\\res\\image\\003.jpg");
	m_RichEdit.SetImage(m_pKeyFile[2], strPath.c_str());

	strPath = g_ProFile.getPath() + std::string("\\res\\image\\1001.gif");
	m_RichEdit.SetGif(m_pKeyFile[2], strPath.c_str());
*/
	//--------------------------------------------------------------
	// 网页

	strPath = g_ProFile.getPath();
	strPath += "\\res\\htm\\Demo.htm";

	// 创建浏览器
	GetDlgItem(IDC_UI_HTML)->MoveWindow(10, 70, 260, 370);
	m_Browser.CreateFromStatic(IDC_UI_HTML, this);
	m_Browser.Navigate2(strPath.c_str(),NULL,NULL);

	SetTimer(1, 200, NULL);

    return TRUE;
}

void CDlg_UI::OnTimer(UINT nIDEvent)
{
	static int a = 0;
	m_RichEdit.SetTransFile(m_pKeyFile[1], _T(""), 1, a++);
	CDialog::OnTimer(nIDEvent);
}

LRESULT CDlg_UI::OnHtmlClick(WPARAM wParam, LPARAM lParam)
{
	std::string strFileName = g_ProFile.getPath();
	strFileName += "\\res\\";
	strFileName += (LPCTSTR)wParam;

	switch ((int)lParam)
	{
	case FILE_GIF:
		{
			KEY_AREA *pKey = m_RichEdit.AddGif(strFileName.c_str(), NULL);
			break;
		}
	case FILE_JPG:
	case FILE_BMP:
		{
			KEY_AREA *pKey = m_RichEdit.AddImage(strFileName.c_str(), NULL);
			break;
		}
	default:
		break;
	}
	m_RichEdit.AddText("\n");
	return 0;
}

void CDlg_UI::OnBnClickedGif()
{
	CString strFilePath;
	CString strFileName;

	CFileDialog FileDlg(TRUE, NULL, NULL, NULL, "GIF *.gif|*.gif||");
	FileDlg.m_ofn.lpstrInitialDir = g_ProFile.getPath();   

	if (FileDlg.DoModal()==IDOK)
	{
		strFileName = FileDlg.GetFileName();
		m_gif.Load((LPCTSTR)strFileName);

		UINT nCount = m_gif.getFrameCount();

		CString strFrameNum;
		GetDlgItem(IDC_UI_EDIT)->GetWindowText(strFrameNum);
		UINT nFrameNum = _ttoi((LPCTSTR)strFrameNum);

		CString strText;
		strText.Format("帧号太大(0~%d)", nCount - 1);
		if (nFrameNum >= nCount)
		{
			MessageBox(strText);
		}
		else
		{
			CString strName;
			strName.Format("%s_%d.bmp", strFileName, nFrameNum);
			m_gif.SaveBmp(strName, nFrameNum);

			m_BmpInfo.bmWidth = m_gif.getWidth();
			m_BmpInfo.bmHeight = m_gif.getHeight();

			m_bShowImage = m_gif.Draw(m_hCompDC, 0, 0, nFrameNum);
		}
	}
}

void CDlg_UI::OnBnClickedJS()
{
	m_Browser.CallJScript("ShowTime");
}

BOOL CDlg_UI::OnEraseBkgnd(CDC* pDC)
{
	if (m_bShowImage)
	{
		::BitBlt(m_hDC, 550, 330, m_BmpInfo.bmWidth, m_BmpInfo.bmHeight, m_hCompDC, 0, 0, SRCCOPY);
	}
	
	return TRUE;
}

void CDlg_UI::OnBnClickedDlg1()
{
    m_pSkinDlg1->ShowWindow(SW_SHOW);
}

void CDlg_UI::OnBnClickedDlg2()
{
    m_pSkinDlg2->ShowWindow(SW_SHOW);
}

void CDlg_UI::OnBnClickedDlg3()
{
    m_pSkinDlg3->ShowWindow(SW_SHOW);
}

void CDlg_UI::OnBnClickedDlg4()
{
    m_pSkinDlg4->Show("TaskbarNotifier", 4, "www.emule.com");
}

BOOL CDlg_UI::SetJpg(LPCTSTR pFileName, HGLOBAL &hGlobal, HBITMAP &hBmp)
{
    CFile file;
    if (!file.Open(pFileName, CFile::modeRead))
        return FALSE;

    long lResSize =(long)file.GetLength();

    hGlobal = GlobalAlloc(GMEM_MOVEABLE, lResSize);
    if (NULL == hGlobal)
        return false;

    // 锁定内存
    LPVOID pvData = GlobalLock(hGlobal);
    if (NULL == pvData)
        return false;

    // 读文件
    file.Read(pvData, lResSize);

    file.Close();

    // 解锁
    GlobalUnlock(hGlobal);

    // 建立IStream
    LPSTREAM pstm = NULL;
    HRESULT  hr   = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);

    if (!SUCCEEDED(hr) && NULL == pstm)
        return false;

    // 建立IPicture   
    LPPICTURE gpPicture;
    hr = ::OleLoadPicture(pstm, lResSize, FALSE, IID_IPicture, (LPVOID*)&gpPicture);

    if (!SUCCEEDED(hr) && NULL == gpPicture)
        return false;

    // 释放lSrcSize
    pstm->Release();

    OLE_HANDLE m_picHandle;
    gpPicture->get_Handle(&m_picHandle);

#pragma warning(disable : 4312)
    hBmp = (HBITMAP)m_picHandle;
#pragma warning(disable : 4312)

    return true;
}

void CDlg_UI::OnBnClickedShowJpg()
{
    CString strFileName = g_ProFile.getPath();

	strFileName += "\\res\\image\\001.jpg";

    SetJpg(strFileName, m_hGlobal, m_hBmp);

	::GetObject(m_hBmp, sizeof(m_BmpInfo), &m_BmpInfo);	// 得到位图信息

	::SelectObject(m_hBmpDC, m_hBmp);
	::BitBlt(m_hCompDC, 0, 0, m_BmpInfo.bmWidth, m_BmpInfo.bmHeight, m_hBmpDC, 0, 0, SRCCOPY);
	::BitBlt(m_hDC, 550, 330, m_BmpInfo.bmWidth, m_BmpInfo.bmHeight, m_hCompDC, 0, 0, SRCCOPY);

    m_bShowImage = TRUE;
}

void CDlg_UI::OnMouseMove(UINT nFlags, CPoint point)
{
    CString s;
    s.Format("X=%d Y=%d", point.x, point.y);
    m_StatusBar.SetPaneText(0, s);

    CDialog::OnMouseMove(nFlags, point);
}

void CDlg_UI::OnBnClickedScreenCap()
{
    CSCreenCluterDlg dlg;
    if (IDOK == dlg.DoModal())
    {
        CString strTemp;
        strTemp.AppendFormat("%s\\%d.jpg", g_ProFile.getPath(), GetTickCount());
        dlg.m_imgResult.Save(strTemp);

        CString strText("已存为 ");
        strText += strTemp;

        MessageBox(strText);
    }
}

void CDlg_UI::OnRButtonDown(UINT nFlags, CPoint point)
{
    CRect rect;
    this->GetWindowRect(&rect);
    point.x += rect.left;
    point.y += rect.top;

    m_menu.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);

    CDialog::OnRButtonDown(nFlags, point);
}

BOOL CDlg_UI::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
    ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

    // UNICODE消息
    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

    CString strTipText;
    UINT nID = (UINT)(pNMHDR->idFrom);

    if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
        pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
    {
        // idFrom为工具条的HWND 
#pragma warning(disable : 4312)
        nID = ::GetDlgCtrlID((HWND)nID);
#pragma warning(default : 4312)
    }

    if (nID != 0) //不为分隔符
    {
        strTipText.LoadString(nID);
        strTipText = strTipText.Mid(strTipText.Find('\n',0)+1);

#ifndef _UNICODE
        if (pNMHDR->code == TTN_NEEDTEXTA)
            lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
        else
            _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
#else
        if (pNMHDR->code == TTN_NEEDTEXTA)
            _wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
        else
            lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
#endif

        *pResult = 0;

        // 使工具条提示窗口在最上面
        ::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,SWP_NOACTIVATE|
            SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER); 
        return TRUE;
    }
    return TRUE;
}

void CDlg_UI::OnToolBarCommand()
{
    CString strText;
    CString strComboBox;
    CString strEdit;

    pComboBox->GetWindowCtrl()->GetWindowText(strComboBox);
    pEdit->GetWindowCtrl()->GetWindowText(strEdit);

    strText = strComboBox + _T("\n") + strEdit;

    MessageBox(strText);
}

void CDlg_UI::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if (IsWindow(m_StatusBar.m_hWnd))
        m_StatusBar.MoveWindow(0, cy - 20, cx, 20);
}

void CDlg_UI::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    if (!CXTMenu::OnMeasureItem(GetCurrentMessage()))
        CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CDlg_UI::OnLvnGetdispinfoUiList(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
    *pResult = 0;

    if (pDispInfo->item.mask & LVIF_TEXT)
        sprintf(pDispInfo->item.pszText, "%d-%d", pDispInfo->item.iItem, pDispInfo->item.iSubItem);

}

void CDlg_UI::OnBnClickedMessageBox()
{
	XTMessageBox("大家好\n\n(0_0)","信息",MB_ICONEXCLAMATION|MB_CANCELTRYCONTINUE);
}

#include "UI/PNG.h"
void CDlg_UI::OnBnClickedPng()
{
	CPNG png;
	//png.Load("D:\\OpenCode\\png\\gold_huangjia_02.png");
	HMODULE module = (HMODULE)ATL::_pModule->GetModuleInstance();
	png.Load(module, IDB_UI_PNG_HALL_RED);
	png.SaveBmp("new.bmp");

	m_bShowImage = png.Draw(m_hCompDC, 0, 0);
	m_BmpInfo.bmWidth = png.getWidth();
	m_BmpInfo.bmHeight = png.getHeight();	
}
