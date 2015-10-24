
#include "stdafx.h"
#include "Dlg_Chat_Clt.h"
#include "Dlg_Chat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern UINT WM_PROGRESS_OK;
extern UINT WM_OUTBAR_NOTIFY;
extern UINT WM_COMBOBOX_SEL;

extern UINT WM_AddFRIEND_FAIL;
extern UINT WM_DELFRIEND_FAIL;
extern UINT WM_SENDTEXT_FAIL;
extern UINT WM_NOFRIEND_TEXT;
extern UINT WM_DEL_CHATDLG;

#define DLG_WIDTH 200
#define DLG_HIGHT 600


IMPLEMENT_DYNAMIC(CDlg_Chat_Clt, CDialog)
CDlg_Chat_Clt::CDlg_Chat_Clt(CWnd* pParent /*=NULL*/)
    : CDialog(CDlg_Chat_Clt::IDD, pParent), 
    m_pUserInfoMap(NULL),
    m_pFriendIdArray(NULL),
    m_pLoginUserInfo(NULL),
    m_dwMyId(0),
    m_nOnlineFriends(0),
    m_bLoginDlg(true),
    m_bDlgMin(false)
{
}

CDlg_Chat_Clt::~CDlg_Chat_Clt()
{
}

void CDlg_Chat_Clt::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    
    DDX_Control(pDX,IDC_CHAT_BTN_MIN,               m_btnMin);
    DDX_Control(pDX,IDC_CHAT_BTN_EXIT,              m_btnExit);
    DDX_Control(pDX,IDC_CHAT_BTN_LOGIN,             m_btnLogin);    
    DDX_Control(pDX,IDC_CHAT_BTN_AUTO_LOGIN,        m_btnAutoLogin);
    DDX_Control(pDX,IDC_CHAT_BTN_SAVE_PASSWORD,     m_btnSavePass);
    DDX_Control(pDX,IDC_CHAT_COMBO_SELECT_USER,     m_ComboBoxUser);
    DDX_Control(pDX,IDC_CHAT_EDIT_INPUT_PASSWORD,   m_edPass);
}

BEGIN_MESSAGE_MAP(CDlg_Chat_Clt, CDialog)
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP 
    ON_BN_CLICKED(IDC_CHAT_BTN_MIN,                 OnBtnClickedMin)
    ON_BN_CLICKED(IDC_CHAT_BTN_EXIT,                OnBtnClickedExit)
    ON_BN_CLICKED(IDC_CHAT_BTN_LOGIN,               OnBtnClickedLogin)
    ON_BN_CLICKED(IDC_CHAT_BTN_AUTO_LOGIN,          OnBtnClickedBtAutoLogin)
    ON_BN_CLICKED(IDC_CHAT_BTN_SAVE_PASSWORD,       OnBtnClickedBtSavePassword)
    ON_REGISTERED_MESSAGE(WM_PROGRESS_OK,           OnProgressOk)
    ON_REGISTERED_MESSAGE(WM_COMBOBOX_SEL,          OnComboBoxSel)  
    ON_REGISTERED_MESSAGE(WM_OUTBAR_NOTIFY,         OnOutlookCtrl)
    ON_REGISTERED_MESSAGE(WM_AddFRIEND_FAIL,        OnAddFriendFail)
    ON_REGISTERED_MESSAGE(WM_DELFRIEND_FAIL,        OnDelFriendFail)
    ON_REGISTERED_MESSAGE(WM_SENDTEXT_FAIL,         OnSendTextFail)
    ON_REGISTERED_MESSAGE(WM_NOFRIEND_TEXT,         OnNoFriendText)
    ON_REGISTERED_MESSAGE(WM_DEL_CHATDLG,           OnDelChatDlg)
END_MESSAGE_MAP()


BOOL CDlg_Chat_Clt::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    //------------------------------------------------------------------------------
    BYTE byError = m_Client.Init(this);
    if (0 != byError)
    {
        CString strError(_T("初使化错误:"));
        strError.AppendFormat(_T("%d"), byError);
        MessageBox(strError);
        m_btnLogin.EnableWindow(FALSE);
    }

    byError = m_Client.Start();
    if (0 != byError)
    {
        CString strError(_T("运行错误:"));
        strError.AppendFormat(_T("%d"), byError);
        MessageBox(strError);
        m_btnLogin.EnableWindow(FALSE);
    }

    m_Client.SetDlgWnd(this->GetSafeHwnd());

    //------------------------------------------------------------------------------
    CRect rcWnd;
    this->GetWindowRect(&rcWnd);
    this->MoveWindow(rcWnd.left, rcWnd.top, DLG_WIDTH, DLG_HIGHT);
    HRGN hRgn = CreateRoundRectRgn(0, 0, DLG_WIDTH + 1, DLG_HIGHT + 1, 15, 15);
    this->SetWindowRgn(hRgn, TRUE);
    this->SetWindowText(_T("chat"));
    this->CenterWindow();

    //------------------------------------------------------------------------------
    m_hDC = m_xtDC.Init(NULL, this->m_hWnd);
    m_hCompDC = m_xtDC.AddCompDC();
    m_hBmpDC = m_xtDC.AddBmpDC(0, IDB_BMP_CHATCLTDLG);
    ::BitBlt(m_hCompDC, 0, 0, 200, 600, m_hBmpDC, 0, 0, SRCCOPY);

    //------------------------------------------------------------------------------
    m_btnMin.Initial(145, 10, 20, 20, 0, 600, &m_xtDC, _T("最小化"));
    m_btnExit.Initial(170, 10, 20, 20, 61, 600, &m_xtDC, _T("退出"));
    m_btnLogin.Initial(70, 500, 66, 18, 0, 621, &m_xtDC, _T("登录"));
    m_ComboBoxUser.Initial(20, 350, 160, 100, 122, 600, &m_xtDC);
    m_edPass.MoveWindow(20, 380, 160, 20);
    m_btnSavePass.Initial(20, 410, 63, 11, 0, 640, &m_xtDC, _T("保存密码"));
    m_btnAutoLogin.Initial(20, 440, 63, 11, 0, 651, &m_xtDC, _T("自动登录"));
    m_Progress.Initial(9, 320, 14, 4, 12, 6, 1, 168, 600, &m_xtDC);
    m_Progress.SetDlgWnd(this->GetSafeHwnd());

    //------------------------------------------------------------------------------
    if (!m_wndOutlookBar.Create(WS_CHILD|WS_VISIBLE, CRect(10,50,190,550), this, 100, CXTOutBarCtrl::fAnimation))
    {
        TRACE("Failed to create outlook bar.\n");
        return -1;
    }

    m_wndOutlookBar.SetImageList(g_ProFile.GetImageList(), CXTOutBarCtrl::fLargeIcon);
    m_wndOutlookBar.SetImageList(g_ProFile.GetImageList(), CXTOutBarCtrl::fSmallIcon);
    m_wndOutlookBar.SetAnimationTickCount(20);
    m_wndOutlookBar.AddFolder(_T("在线用户"), 0);
    m_wndOutlookBar.AddFolder(_T("我的好友"), 1);
    m_wndOutlookBar.SetSelFolder(1);
    m_wndOutlookBar.ShowWindow(SW_HIDE);

    //------------------------------------------------------------------------------
    WORD wSel = 0;
    if (m_Client.GetLoginUser(wSel, &m_pLoginUserInfo) && (NULL != m_pLoginUserInfo))
    {
        for (int i = 0; i < m_pLoginUserInfo->GetCount(); i += 3)
            m_ComboBoxUser.AddString((*m_pLoginUserInfo)[i]);
        
        m_ComboBoxUser.SetCurSel(wSel);

        if ((*m_pLoginUserInfo)[wSel*3+1].GetLength() > 0)
        {
            m_btnSavePass.SetCheck(1);
            m_edPass.SetWindowText((*m_pLoginUserInfo)[wSel*3+1]);
        }

        if ((*m_pLoginUserInfo)[wSel*3+2].Compare(_T("1")) == 0)
            m_btnAutoLogin.SetCheck(1);
    }

    return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CDlg_Chat_Clt::ShowLoginDlg(int nCmdShow)
{
    int nOtherCmdShow = (SW_SHOW == nCmdShow) ? SW_HIDE : SW_SHOW;

    m_bLoginDlg = (SW_SHOW == nCmdShow) ? true : false;

    m_btnLogin.ShowWindow(nCmdShow);
    m_btnSavePass.ShowWindow(nCmdShow);
    m_btnAutoLogin.ShowWindow(nCmdShow);
    m_ComboBoxUser.ShowWindow(nCmdShow);
    m_edPass.ShowWindow(nCmdShow);
    m_wndOutlookBar.ShowWindow(nOtherCmdShow);
}

void CDlg_Chat_Clt::OnPaint() 
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

        if (m_hDC == NULL || m_hCompDC == NULL) return;

        if (m_bLoginDlg)
        {
            ::BitBlt(m_hDC,   0,   0, 200, 350, m_hCompDC,   0,   0, SRCCOPY);
            ::BitBlt(m_hDC,   0, 400, 200, 200, m_hCompDC,   0, 400, SRCCOPY);
            ::BitBlt(m_hDC,   0, 350,  20,  50, m_hCompDC,   0, 350, SRCCOPY);
            ::BitBlt(m_hDC, 180, 350,  20,  50, m_hCompDC, 180, 350, SRCCOPY);
            ::BitBlt(m_hDC,  20, 370, 160,  10, m_hCompDC,  20, 370, SRCCOPY);
        }
        else
        {
            ::BitBlt(m_hDC,   0,   0, 200,  50, m_hCompDC,   0,   0, SRCCOPY);
            ::BitBlt(m_hDC,   0,  50,  10, 500, m_hCompDC,   0,  50, SRCCOPY);
            ::BitBlt(m_hDC, 190,  50,  10, 500, m_hCompDC, 190,  50, SRCCOPY);
            ::BitBlt(m_hDC,   0, 550, 200,  50, m_hCompDC,   0, 550, SRCCOPY);
        }
    }
}

//绘登录窗体上的动画
void CDlg_Chat_Clt::OnTimer(UINT nIDEvent)
{
    m_Client.ProcessNAT();
    CDialog::OnTimer(nIDEvent);
}

void CDlg_Chat_Clt::OnMouseMove(UINT nFlags, CPoint point)
{
    PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
    CDialog::OnMouseMove(nFlags, point);
}


//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CDlg_Chat_Clt::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CDlg_Chat_Clt::OnBtnClickedMin()
{
    ShowWindow(SW_MINIMIZE);
}

void CDlg_Chat_Clt::OnBtnClickedExit()
{
    m_Progress.Stop();
    OnCancel();
}

void CDlg_Chat_Clt::OnBtnClickedLogin()
{
#pragma warning(disable: 4800)
    bool bAutoLogin = (bool)m_btnAutoLogin.GetCheck();
    bool bSavePass = (bool)m_btnSavePass.GetCheck();
#pragma warning(default: 4800)
    
    CString strUserName;
    CString strPassword;

    m_ComboBoxUser.GetWindowText(strUserName);
    m_edPass.GetWindowText(strPassword);

    m_Client.SetUserInfo(strUserName, strPassword, bSavePass, bAutoLogin);

    int nRes = m_Client.Login();
    if (0 == nRes)
    {
        m_Progress.Start();
        m_btnLogin.EnableWindow(FALSE);
    }
    else
    {
        CString strText("Login Fail ");
        strText.AppendFormat(_T("%d"), nRes);
        MessageBox(strText);
    }
}

void CDlg_Chat_Clt::OnBtnClickedBtSavePassword()
{
    if (FALSE == m_btnSavePass.GetCheck() && TRUE == m_btnAutoLogin.GetCheck())
        m_btnAutoLogin.SetCheck(FALSE);
}

void CDlg_Chat_Clt::OnBtnClickedBtAutoLogin()
{
    if (TRUE == m_btnAutoLogin.GetCheck())
    {
        m_btnSavePass.SetCheck(TRUE);
    }
}

LRESULT CDlg_Chat_Clt::OnOutlookCtrl(WPARAM wParam, LPARAM lParam)
{
    if (NULL == m_pFriendIdArray) return -1;

    DWORD dwUserId = (DWORD)lParam;

    switch (wParam)
    {
    case ID_OUTBAR_ADDFRIEND:
        {
            m_Client.AddFriend(dwUserId);
            break;
        }
    case ID_OUTBAR_DELFRIEND:
        {
            m_Client.DelFriend(dwUserId);
            break;
        }
    case NM_OB_ITEMDBCLICK:
    case ID_OUTBAR_STARTCHAT:
        {
            if (NULL != m_pUserInfoMap)
            {
                USERINFO UserInfo = {0};
                if (m_pUserInfoMap->Lookup(dwUserId, UserInfo))
                {
                    if (NULL == UserInfo.pChatDlg)
                    {
                        UserInfo.pChatDlg = new CDlg_Chat;
                        ASSERT(UserInfo.pChatDlg);
                        UserInfo.pChatDlg->Create(IDD_DLG_CHAT, this);
                        UserInfo.pChatDlg->SetParam(&m_Client, dwUserId);
                        m_pUserInfoMap->SetAt(dwUserId, UserInfo);
                    }
                    
                    UserInfo.pChatDlg->ShowWindow(SW_SHOW);
                    this->StopActiveUserIcon(dwUserId);

                    if (NULL != UserInfo.pPackUserInfo)
                    {
                        CString strText;

                        for (DWORD i = 0; i < UserInfo.pPackUserInfo->dwDataLen; )
                        {
                            strText = _T("");
                            strText.Append((char*)&(UserInfo.pPackUserInfo->byData[i]), UserInfo.pPackUserInfo->dwDataLen);
                            strText.ReleaseBuffer();
                            int nLen = strText.GetLength();
                            i += nLen + 1;
                            if (nLen > 0)
                                UserInfo.pChatDlg->SetText(dwUserId, (LPCTSTR)strText);
                            else
                                break;
                        }

                        UserInfo.pPackUserInfo->dwDataLen = 0;
                        m_pUserInfoMap->SetAt(dwUserId, UserInfo);
                    }                   
                }
            }
            break;
        }
    default:break;
    }

    return 1;
}

LRESULT CDlg_Chat_Clt::OnProgressOk(WPARAM wParam, LPARAM lParam)
{
    ShowLoginDlg(SW_HIDE);
    return 0;
}

LRESULT CDlg_Chat_Clt::OnComboBoxSel(WPARAM wParam, LPARAM lParam)
{
    if (NULL == m_pLoginUserInfo) return -1;

    WORD wSel = (WORD)lParam;
    m_ComboBoxUser.SetCurSel(wSel);

    if ((*m_pLoginUserInfo)[wSel*3+1].GetLength() > 0)
    {
        m_btnSavePass.SetCheck(1);
        m_edPass.SetWindowText((*m_pLoginUserInfo)[wSel*3+1]);
    }
    else
    {
        m_btnSavePass.SetCheck(0);
        m_edPass.SetWindowText(_T(""));
    }

    if ((*m_pLoginUserInfo)[wSel*3+2].Compare(_T("1")) == 0)
    {
        m_btnAutoLogin.SetCheck(1);
    }
    else
    {
        m_btnAutoLogin.SetCheck(0);
    }

    return 0;
}

void CDlg_Chat_Clt::CloseSocket(void)
{
    MessageBox(_T("与服务器断开连接!"));
    return;
}

void CDlg_Chat_Clt::LoginSuccess(ID_ARRAY *pFriendIdArray, USERINFO_MAP *pUserInfoMap)
{
    m_pUserInfoMap = pUserInfoMap;
    m_pFriendIdArray = pFriendIdArray;

    if ((NULL == m_pUserInfoMap) || (NULL == m_pFriendIdArray)) return;

    m_dwMyId = m_Client.GetMyId();
/*
    CString strId;
    for (int i = 0; i < m_pFriendIdArray->GetCount(); i++)
    {
        strId.Format(_T("%d"), (*m_pFriendIdArray)[i]);
        m_wndOutlookBar.InsertItem(1, i, (LPCTSTR)strId, 0, (*m_pFriendIdArray)[i]);
    }
*/
    CString strId;
    strId.Format(_T("我的好友(0/%d)"), m_pFriendIdArray->GetCount());
    m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strId);

    m_Progress.Success();

    this->SetTimer(1, 2000, NULL);
    return;
}

void CDlg_Chat_Clt::LoginFail(DWORD dwError)
{
    m_Progress.Stop();
    m_btnLogin.EnableWindow();

    CString strText(_T("登陆失败!"));

    if (1 == dwError)
        strText += _T("该用户已经登陆.");
    else
        strText += _T("用户名或密码错误.");

    MessageBox(strText);
}

void CDlg_Chat_Clt::OnlineUserInfo(DWORD dwUserId, CStringArrayEx *pstrUserInfo)
{
    if (NULL == pstrUserInfo) return;

    int nImageId = atoi((LPCTSTR)(*pstrUserInfo)[3]);
    m_wndOutlookBar.InsertItem(0, m_wndOutlookBar.GetItemCount(0), (LPCTSTR)(*pstrUserInfo)[1], nImageId, dwUserId);

    CString strCount;
    strCount.Format(_T("在线用户 (%d)"), m_wndOutlookBar.GetItemCount(0));
    m_wndOutlookBar.SetFolderText(0, (LPCTSTR)strCount);

    if (m_dwMyId == dwUserId)
    {
        IMAGEINFO ImageInfo = {0};
        g_ProFile.m_ImageList.GetImageInfo(nImageId, &ImageInfo);
        CSize szImage = CRect(ImageInfo.rcImage).Size();
        CPoint pt(10, 50-szImage.cy-1);
        CDC dc;
        dc.Attach(m_hCompDC);
        g_ProFile.m_ImageList.Draw(&dc, nImageId, pt, ILD_NORMAL);
        dc.Detach();

        RECT rcText = {15+szImage.cx, 30, 180, 50};
        ::DrawText(m_hCompDC, (LPCTSTR)(*pstrUserInfo)[1], (*pstrUserInfo)[1].GetLength(), &rcText, DT_VCENTER|DT_SINGLELINE|DT_WORD_ELLIPSIS);
    }

    m_OnlineUserIdArray.Add(dwUserId);

    if (NULL == m_pFriendIdArray) return;

    for (int i = 0; i < m_pFriendIdArray->GetCount(); i++)
    {
        if (dwUserId == (*m_pFriendIdArray)[i])
        {
            int j = 0;
            for (; j < m_OnlineFriendIdArray.GetCount(); j++)
            {
                if (dwUserId == m_OnlineFriendIdArray[j]) break;
            }

            if (j == m_OnlineFriendIdArray.GetCount())
            {
                m_OnlineFriendIdArray.Add(dwUserId);

                int nImageId = atoi((LPCTSTR)(*pstrUserInfo)[3]);
                m_wndOutlookBar.InsertItem(1, j, (LPCTSTR)(*pstrUserInfo)[1], nImageId, dwUserId);

                strCount.Format(_T("我的好友 (%d/%d)"), m_OnlineFriendIdArray.GetCount(), m_pFriendIdArray->GetCount());
                m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
            }
/*
            m_wndOutlookBar.RemoveItem(1, i);

            int nImageId = atoi((LPCTSTR)(*pstrUserInfo)[3]);
            m_wndOutlookBar.InsertItem(1, i, (LPCTSTR)(*pstrUserInfo)[1], nImageId, dwUserId);

            strCount.Format(_T("我的好友 (%d/%d)"), ++m_nOnlineFriends, m_wndOutlookBar.GetItemCount(1));
            m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
*/
            break;
        }
    }

    m_wndOutlookBar.Invalidate();
}

void CDlg_Chat_Clt::UserExit(DWORD dwUserId)
{
    for (int i = 0; i < m_OnlineUserIdArray.GetCount(); i++)
    {
        if (dwUserId == m_OnlineUserIdArray[i])
        {
            m_wndOutlookBar.RemoveItem(0, i);
            m_OnlineUserIdArray.RemoveAt(i);
            
            CString strCount;
            strCount.Format(_T("在线用户 (%d)"), m_wndOutlookBar.GetItemCount(0));
            m_wndOutlookBar.SetFolderText(0, (LPCTSTR)strCount);
            break;
        }
    }
/*
    for (int i = 0; i < m_pFriendIdArray->GetCount(); i++)
    {
        if (dwUserId == (*m_pFriendIdArray)[i])
        {
            char szUserId[100] = {_T("")};
            itoa(dwUserId, szUserId, 10);
            m_wndOutlookBar.RemoveItem(1, i);
            m_wndOutlookBar.InsertItem(1, i, szUserId, 0, dwUserId);

            CString strCount;
            strCount.Format(_T("我的好友 (%d/%d)"), --m_nOnlineFriends, m_wndOutlookBar.GetItemCount(1));
            m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
            break;
        }
    }
*/
    for (int i = 0; i < m_OnlineFriendIdArray.GetCount(); i++)
    {
        if (dwUserId == m_OnlineFriendIdArray[i])
        {
            m_OnlineFriendIdArray.RemoveAt(i);
            m_wndOutlookBar.RemoveItem(1, i);
            
            CString strCount;
            strCount.Format(_T("我的好友 (%d/%d)"), m_OnlineFriendIdArray.GetCount(), m_pFriendIdArray->GetCount());
            m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
            m_wndOutlookBar.Invalidate();        
            break;
        }
    }
    
   
}

void CDlg_Chat_Clt::AddFriendSuccess(DWORD dwFriendId)
{
    USERINFO UserInfo = {0};

    if (m_pUserInfoMap->Lookup(dwFriendId, UserInfo))
    {
/*      int nImageId = atoi((LPCTSTR)(*UserInfo.pstrUserInfo)[3]);
        m_wndOutlookBar.InsertItem(1, (int)m_pFriendIdArray->GetCount(), (LPCTSTR)(*UserInfo.pstrUserInfo)[1], nImageId, dwFriendId);

        CString strCount;
        strCount.Format(_T("我的好友 (%d/%d)"), ++m_nOnlineFriends, m_wndOutlookBar.GetItemCount(1));
        m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
        m_wndOutlookBar.Invalidate();
*/
        int nImageId = atoi((LPCTSTR)(*UserInfo.pstrUserInfo)[3]);
        m_wndOutlookBar.InsertItem(1, (int)m_OnlineFriendIdArray.GetCount(), (LPCTSTR)(*UserInfo.pstrUserInfo)[1], nImageId, dwFriendId);

        m_OnlineFriendIdArray.Add(dwFriendId);

        CString strCount;
        strCount.Format(_T("我的好友 (%d/%d)"), m_OnlineFriendIdArray.GetCount(), m_pFriendIdArray->GetCount());
        m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
        m_wndOutlookBar.Invalidate();
    }
}

LRESULT CDlg_Chat_Clt::OnAddFriendFail(WPARAM wParam, LPARAM lParam)
{
    ::MessageBox(NULL, _T("添加好友失败"), _T("错误"), MB_OK);
    return 0;
}

void CDlg_Chat_Clt::DelFriendSuccess(DWORD dwFriendId)
{
    USERINFO UserInfo = {0};
    bool bOnline = false;

    if (m_pUserInfoMap->Lookup(dwFriendId, UserInfo)) bOnline = true;
/*
    for (int i = 0; i < m_pFriendIdArray->GetCount(); i++)
    {
        if (dwFriendId == (*m_pFriendIdArray)[i])
        {
            m_wndOutlookBar.RemoveItem(1, i);
            m_pFriendIdArray->RemoveAt(i);

            if (bOnline) --m_nOnlineFriends;
        }
    }

    if (m_nOnlineFriends < 0) m_nOnlineFriends = 0;
    CString strCount;
    strCount.Format(_T("我的好友 (%d/%d)"), m_nOnlineFriends, m_wndOutlookBar.GetItemCount(1));
    m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
    m_wndOutlookBar.Invalidate();
*/
    for (int i = 0; i < m_OnlineFriendIdArray.GetCount(); i++)
    {
        if (dwFriendId == m_OnlineFriendIdArray[i])
        {
            m_OnlineFriendIdArray.RemoveAt(i);
            m_wndOutlookBar.RemoveItem(1, i);

            CString strCount;
            strCount.Format(_T("我的好友 (%d/%d)"), m_OnlineFriendIdArray.GetCount(), m_pFriendIdArray->GetCount());
            m_wndOutlookBar.SetFolderText(1, (LPCTSTR)strCount);
            m_wndOutlookBar.Invalidate();
            break;
        }
    }
}

LRESULT CDlg_Chat_Clt::OnDelFriendFail(WPARAM wParam, LPARAM lParam)
{
    ::MessageBox(NULL, _T("删除好友失败"), _T("错误"), MB_OK);
    return 0;
}

LRESULT CDlg_Chat_Clt::OnSendTextFail(WPARAM wParam, LPARAM lParam)
{
    CString strInfo;
    strInfo.Format(_T("向%d发送文本%d失败"), (DWORD)wParam, (LPARAM)lParam);
    ::MessageBox(NULL, strInfo, _T("错误"), MB_OK);
    return 0;
}

LRESULT CDlg_Chat_Clt::OnNoFriendText(WPARAM wParam, LPARAM lParam)
{
    CString strInfo;
    strInfo.Format(_T("接收到一个非好友(%d)信息:%s"), (DWORD)wParam, (LPCTSTR)lParam);
    ::MessageBox(NULL, strInfo, _T("提示"), MB_OK);
    return 0;
}

LRESULT CDlg_Chat_Clt::OnDelChatDlg(WPARAM wParam, LPARAM lParam)
{
    CDlg_Chat *pDlg = (CDlg_Chat*)wParam;
    if (NULL != pDlg)
    {
        pDlg->DestroyWindow();
        delete pDlg;
    }
    return 0;
}

void CDlg_Chat_Clt::StartActiveUserIcon(DWORD dwUserId)
{
/*  for (int i = 0; i < m_pFriendIdArray->GetCount(); i++)
    {
        if (dwUserId == (*m_pFriendIdArray)[i])
        {
            m_wndOutlookBar.StartActiveItem(i);
            break;
        }
    }
*/
    for (int i = 0; i < m_OnlineFriendIdArray.GetCount(); i++)
    {
        if (dwUserId == m_OnlineFriendIdArray[i])
        {
            m_wndOutlookBar.StartActiveItem(i);
            break;
        }
    }
}
void CDlg_Chat_Clt::StopActiveUserIcon(DWORD dwUserId)
{
/*  for (int i = 0; i < m_pFriendIdArray->GetCount(); i++)
    {
        if (dwUserId == (*m_pFriendIdArray)[i])
        {
            m_wndOutlookBar.StopActiveItem(i);
            break;
        }
    }
*/
    for (int i = 0; i < m_OnlineFriendIdArray.GetCount(); i++)
    {
        if (dwUserId == m_OnlineFriendIdArray[i])
        {
            m_wndOutlookBar.StopActiveItem(i);
            break;
        }
    }
}

void CDlg_Chat_Clt::OnEnLinkRicheditMessage(NMHDR *pNMHDR, LRESULT *pResult)
{
    ENLINK *pEnLink = reinterpret_cast<ENLINK *>(pNMHDR);

    if (pEnLink->msg == WM_LBUTTONUP)
    {

    }
    *pResult = 0;
}
