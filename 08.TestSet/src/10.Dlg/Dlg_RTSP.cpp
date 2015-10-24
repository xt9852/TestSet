// Dlg_RTSP.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "Dlg_RTSP.h"
#include ".\dlg_rtsp.h"

// CDlg_RTSP 对话框

//-----------------------------------------------

HHOOK CDlg_RTSP::m_hMsgHook;
CRealPlayer CDlg_RTSP::m_Player;

extern UINT WM_FULLSCREEN;

//-----------------------------------------------


IMPLEMENT_DYNAMIC(CDlg_RTSP, CDialog)
CDlg_RTSP::CDlg_RTSP(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_RTSP::IDD, pParent)
{
    m_bFullScreen = FALSE;
}

CDlg_RTSP::~CDlg_RTSP()
{
}

void CDlg_RTSP::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlg_RTSP, CDialog)
    ON_WM_DESTROY()
    ON_WM_RBUTTONDOWN()
    ON_REGISTERED_MESSAGE(WM_FULLSCREEN, OnFullScreen)
    ON_MESSAGE(WM_CONTEXTMENU, OnContextMenu)
    ON_BN_CLICKED(IDC_RTSP_BUT_START_SERVER, OnBnClickedButStartServer)
    ON_BN_CLICKED(IDC_RTSP_BUT_START_CLIENT, OnBnClickedButStartClient)
    ON_BN_CLICKED(IDC_RTSP_BUT_RTP_CLIENT, &CDlg_RTSP::OnBnClickedRtspButRtpClient)
    ON_BN_CLICKED(IDC_RTSP_BUT_RTP_SERVER, &CDlg_RTSP::OnBnClickedRtspButRtpServer)
END_MESSAGE_MAP()

BOOL CDlg_RTSP::OnInitDialog()
{
    CDialog::OnInitDialog();

    //--------------------------------------------------------------
    GetDlgItem(IDC_RTSP_IPADDRESS1)->SetWindowText(g_ProFile.m_strIP);
    GetDlgItem(IDC_RTSP_EDIT_PORT)->SetWindowText(_T("60000"));
    GetDlgItem(IDC_RTSP_EDIT)->SetWindowText(_T("F:\\Music")); // RTSP协议的虚拟路径，客户请求的文件名

    GetDlgItem(IDC_RTSP_BUT_START_CLIENT)->EnableWindow( FALSE );

    //--------------------------------------------------------------

    m_PopMenu.LoadMenu(IDR_MAIN_MENU);

    //--------------------------------------------------------------

    return TRUE;
}

void CDlg_RTSP::OnDestroy()
{
    m_Player.DestroyWindow();

    //------------------------------------
    CDialog::OnDestroy();
}

void CDlg_RTSP::OnBnClickedButStartServer()
{
    // 开启服务
    CString strIP;
    CString strPort;
    CString strPath;

    GetDlgItem(IDC_RTSP_IPADDRESS1)->GetWindowText(strIP);
    GetDlgItem(IDC_RTSP_EDIT_PORT)->GetWindowText(strPort);
    GetDlgItem(IDC_RTSP_EDIT)->GetWindowText(strPath);

    BYTE byRet = m_SrvRTSP.Start(strIP, _ttoi(strPort), strPath);

    if (0 == byRet)
    {
        GetDlgItem(IDC_RTSP_BUT_START_SERVER)->EnableWindow(FALSE);
        GetDlgItem(IDC_RTSP_BUT_START_CLIENT)->EnableWindow(TRUE);

        GetDlgItem(IDC_RTSP_EDIT)->SetWindowText(_T("十大弧线球大师.rmvb"));		
    }
    else
    {
        CString msg;
        msg.Format(_T("Init IOCP Error\nErrorCode:%d"), byRet);
        MessageBox(msg);
    }
}

void CDlg_RTSP::OnBnClickedButStartClient()
{
    // 开启客户端
    AfxEnableControlContainer();	

    CString strURL(_T("rtsp://"));
    CString strIP;
    CString strPort;
    CString strFileName;

    GetDlgItem(IDC_RTSP_IPADDRESS1)->GetWindowText(strIP);
    GetDlgItem(IDC_RTSP_EDIT_PORT)->GetWindowText(strPort);
    GetDlgItem(IDC_RTSP_EDIT)->GetWindowText(strFileName);

    strURL += strIP;
    strURL += _T(":");
    strURL += strPort;
    strURL += _T("/");
    strURL += strFileName;

    CRect m_rcVideo;
    this->GetClientRect(m_rcVideo);
    m_rcVideo.top += 60; 

    if (!m_Player.Create(NULL, _T("Player"), WS_CHILD, m_rcVideo, this, -1))
    {
        MessageBox(_T("Failed to Load MediaPlayer ActiveX Control"), _T("Notification"));
        return;
    }

    m_Player.SetControls(_T("ImageWindow"));
    m_Player.SetNoLogo(TRUE);
    m_Player.SetEnableContextMenu(TRUE);
    m_Player.SetImageStatus(FALSE);
    m_Player.SetWantErrors(FALSE);
    m_Player.SetCenter(TRUE);
    m_Player.SetMaintainAspect(TRUE);

    //m_hMsgHook = SetWindowsHookEx(WH_CALLWNDPROC, MsgHook, AfxGetInstanceHandle(), GetCurrentThreadId());

    m_Player.ShowWindow(SW_SHOW);
    m_Player.SetSource(strURL);
    m_Player.Play();

    GetDlgItem(IDC_RTSP_BUT_START_CLIENT)->EnableWindow(FALSE);	
}

LRESULT CDlg_RTSP::OnFullScreen(WPARAM wParam, LPARAM lParam)
{
    if (!m_bFullScreen)
    {
        TRACE("To FullScreen\n");
        m_Player.SetFullScreen();
    }
    else
    {
        g_ProFile.m_pLog->println(LOG_INFO, _T("Don't FullScreen\n"));
        CRect rcPlayer;
        m_Player.GetClientRect(&rcPlayer);
        m_Player.SetWindowPos(NULL, 0, 0, rcPlayer.right, rcPlayer.bottom, SWP_FRAMECHANGED|SWP_SHOWWINDOW);
    }

    m_bFullScreen = ! m_bFullScreen;

    return 0;
}

LRESULT CDlg_RTSP::OnContextMenu(WPARAM wParam, LPARAM lParam)
{
    return 0;
}


LPCTSTR wpnOldProc	= _T("RAZA_MenuOldWndProc");

LRESULT CALLBACK CDlg_RTSP::MsgHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    CWPSTRUCT* pCWP = (CWPSTRUCT*)lParam;

    if (pCWP->hwnd == m_Player.m_hWnd)
    {
        g_ProFile.m_pLog->println(LOG_INFO, _T("%u"), pCWP->message);
    }

    while (nCode == HC_ACTION)
    {
        if (pCWP->message != WM_CREATE && pCWP->message != 0x01E2) break;

        TCHAR szClassName[16];
        int nClassName = GetClassName(pCWP->hwnd, szClassName, 16);
        TRACE(_T("%s\n"), szClassName);
        if (nClassName != 6 || _tcscmp(szClassName, _T("#32768")) != 0) break;

        if (::GetProp(pCWP->hwnd, wpnOldProc) != NULL) break;

        HWND hWndFore = ::GetForegroundWindow();
        if (hWndFore != NULL && CWnd::FromHandlePermanent(hWndFore) == NULL) break;

        WNDPROC pWndProc = (WNDPROC)(LONG_PTR)::GetWindowLong(pCWP->hwnd, GWL_WNDPROC);
        if (pWndProc == NULL) break;
        ASSERT(pWndProc != MenuProc);

        if (!SetProp( pCWP->hwnd, wpnOldProc, pWndProc)) break;

        if (!SetWindowLong(pCWP->hwnd, GWL_WNDPROC, (DWORD)(DWORD_PTR)MenuProc))
        {
            ::RemoveProp(pCWP->hwnd, wpnOldProc);
            break;
        }

        break;
    }

    return CallNextHookEx(CDlg_RTSP::m_hMsgHook, nCode, wParam, lParam);
}

LRESULT	CALLBACK CDlg_RTSP::MenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WNDPROC pWndProc = (WNDPROC)::GetProp( hWnd, wpnOldProc );

    TRACE("CDlg_RTSP::MenuProc       ");

    switch ( uMsg )
    {
    case WM_NCCALCSIZE:
        {
            TRACE("WM_NCCALCSIZE\n");
            NCCALCSIZE_PARAMS* pCalc = (NCCALCSIZE_PARAMS*)lParam;
            pCalc->rgrc[0].left ++;
            pCalc->rgrc[0].top ++;
            pCalc->rgrc[0].right --;
            pCalc->rgrc[0].bottom --;
        }
        return 0;

    case WM_WINDOWPOSCHANGING:
        TRACE("WM_WINDOWPOSCHANGING\n");
        /*		if ( WINDOWPOS* pWndPos = (WINDOWPOS*)lParam )
        {
        DWORD nStyle	= GetWindowLong( hWnd, GWL_STYLE );
        DWORD nExStyle	= GetWindowLong( hWnd, GWL_EXSTYLE );
        CRect rc( 0, 0, 32, 32 );

        AdjustWindowRectEx( &rc, nStyle, FALSE, nExStyle );

        pWndPos->cx -= ( rc.Width() - 34 );
        pWndPos->cy -= ( rc.Height() - 34 ) - 1;

        if ( pWndPos->x != m_nEdgeLeft || pWndPos->y != m_nEdgeTop )
        pWndPos->x ++;
        }
        */		break;

    case WM_PRINT:
        {
            TRACE("WM_PRINT\n");

            /*			if ( lParam & PRF_CLIENT )
            {
            CWnd* pWnd = CWnd::FromHandle( hWnd );
            CDC* pDC = CDC::FromHandle( (HDC)wParam );
            CBitmap bmBuf, *pbmOld;
            CDC dcBuf;
            CRect rc;

            pWnd->GetClientRect( &rc );
            dcBuf.CreateCompatibleDC( pDC );
            bmBuf.CreateCompatibleBitmap( pDC, rc.Width(), rc.Height() );
            pbmOld = (CBitmap*)dcBuf.SelectObject( &bmBuf );

            //m_bPrinted = TRUE;
            dcBuf.FillSolidRect( &rc, GetSysColor( COLOR_MENU ) );
            ::SendMessage( hWnd, WM_PRINTCLIENT, (WPARAM)dcBuf.GetSafeHdc(), 0 );

            pDC->BitBlt( 1, 1, rc.Width(), rc.Height(), &dcBuf, 0, 0, SRCCOPY );
            dcBuf.SelectObject( pbmOld );
            }
            }

            if ( ( lParam & PRF_CHECKVISIBLE ) && ! IsWindowVisible( hWnd ) ) return 0;
            if ( lParam & PRF_NONCLIENT )
            {
            CWnd* pWnd = CWnd::FromHandle( hWnd );
            CDC* pDC = CDC::FromHandle( (HDC)wParam );
            CRect rc;

            pWnd->GetWindowRect( &rc );
            BOOL bEdge = ( rc.left == m_nEdgeLeft && rc.top == m_nEdgeTop );
            rc.OffsetRect( -rc.left, -rc.top );

            pDC->Draw3dRect( &rc, CoolInterface.m_crDisabled, CoolInterface.m_crDisabled );
            if ( bEdge ) pDC->FillSolidRect( rc.left + 1, rc.top, min( rc.Width(), m_nEdgeSize ) - 2, 1, CoolInterface.m_crBackNormal );
            }
            if ( lParam & PRF_CLIENT )

            {
            CWnd* pWnd = CWnd::FromHandle( hWnd );
            CDC* pDC = CDC::FromHandle( (HDC)wParam );
            CBitmap bmBuf, *pbmOld;
            CDC dcBuf;
            CRect rc;

            pWnd->GetClientRect( &rc );
            dcBuf.CreateCompatibleDC( pDC );
            bmBuf.CreateCompatibleBitmap( pDC, rc.Width(), rc.Height() );
            pbmOld = (CBitmap*)dcBuf.SelectObject( &bmBuf );

            m_bPrinted = TRUE;
            dcBuf.FillSolidRect( &rc, GetSysColor( COLOR_MENU ) );
            SendMessage( hWnd, WM_PRINTCLIENT, (WPARAM)dcBuf.GetSafeHdc(), 0 );

            pDC->BitBlt( 1, 1, rc.Width(), rc.Height(), &dcBuf, 0, 0, SRCCOPY );
            dcBuf.SelectObject( pbmOld );
            */		}
            return 0;

    case WM_NCPAINT:
        {
            TRACE("WM_NCPAINT\n");
            /*			CWnd* pWnd = CWnd::FromHandle( hWnd );
            CWindowDC dc( pWnd );
            CRect rc;

            pWnd->GetWindowRect( &rc );
            BOOL bEdge = ( rc.left == m_nEdgeLeft && rc.top == m_nEdgeTop );
            rc.OffsetRect( -rc.left, -rc.top );

            dc.Draw3dRect( &rc, CoolInterface.m_crDisabled, CoolInterface.m_crDisabled );
            if ( bEdge ) dc.FillSolidRect( rc.left + 1, rc.top, min( rc.Width(), m_nEdgeSize ) - 2, 1, CoolInterface.m_crBackNormal );
            */		}
            return 0;

    case WM_PAINT:
        TRACE("WM_PAINT\n");
        //		m_bPrinted = FALSE;
        break;

    case WM_NCDESTROY:
        TRACE("WM_NCDESTROY\n");
        ::RemoveProp( hWnd, wpnOldProc );
        break;
    }

    return CallWindowProc( pWndProc, hWnd, uMsg, wParam, lParam );
}

void CDlg_RTSP::OnRButtonDown(UINT nFlags, CPoint point)
{
    CMenu *p2 = m_PopMenu.GetSubMenu(0);
    p2->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

    CDialog::OnRButtonDown(nFlags, point);
}

#include <stdlib.h>
#include <stdio.h>
#include "rtplib/rtpsession.h"
#include "rtplib/rtppacket.h"

void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        char *errstr;

        // This function gets the error string for a certain error code
        errstr = RTPGetErrorString(rtperr);

        TRACE("Error:\n");
        TRACE("%s\n",errstr);
        exit(-1);
    }
}

unsigned CDlg_RTSP::RtpThread(void* pParam)
{
    // 初使化socket
    WSADATA wsd = {0};
    ::WSAStartup(MAKEWORD(2, 2), &wsd);

    RTPSession sess;
    char ipstr[256];
    int portbase = 2000;
    int status;
    int nCount = 0;

    status = sess.Create(portbase);	
    checkerror(status);

    do 
    {
        // poll for incoming data
        status = sess.PollData();

        // check incoming packets
        if (sess.GotoFirstSourceWithData())
        {
            do
            {
                RTPPacket *pack;

                while ((pack = sess.GetNextPacket()) != NULL)
                {
                    // You can examine the data here
                    TRACE("Got %d packet !  %d %d %s\n", 
                        nCount++,
                        pack->GetExtendedSequenceNumber(),
                        pack->GetTimeStamp(),
                        pack->GetPayload());

                    // we don't longer need the packet, so
                    // we'll delete it
                    delete pack;
                }
            } while (sess.GotoNextSourceWithData());
        }

        //::Sleep(10);

    } while(true);

    return 0;
}

RTPSession sess;
void CDlg_RTSP::OnBnClickedRtspButRtpClient()
{    
    int portbase;
    unsigned long destip;
    int destport;
    char ipstr[256];
    int status,i;
    char dummybuffer[1024];


    destip = inet_addr("192.168.6.1");
    if (destip == INADDR_NONE)
    {
        TRACE("Bad IP address specified\n");
        return;
    }

    destip = ntohl(destip);
    destport = 2000;
    portbase = 1000;

    /*
    First, we'll ask for the necessary information
    */

//     printf("Enter the local portbase\n");
//     scanf("%d",&portbase);
//     printf("\n");
// 
//     printf("Enter the destination IP address\n");
//     scanf("%s",ipstr);
//     destip = inet_addr(ipstr);
//     if (destip == INADDR_NONE)
//     {
//         printf("Bad IP address specified\n");
//         return -1;
//     }

    // The inet_addr function returns a value in network byte order, but
    // we need the IP address in host byte order, so we use a call to
    // ntohl
//     destip = ntohl(destip);
// 
//     printf("Enter the destination port\n");
//     scanf("%d",&destport);

    /*
    Now, we'll create a RTP session, set the destination, send some
    packets and poll for incoming data.
    */

    static bool bInit = false;

    if (!bInit)
    {
        status = sess.Create(portbase);	
        checkerror(status);

        status = sess.AddDestination(destip,destport);
        checkerror(status);

        bInit = true;
    }    

    for (i = 1 ; i <= 10 ; i++)
    {
        TRACE("Sending packet %d/10\n",i);

        // send the packet
        status = sess.SendPacket("123456789*",10,(unsigned char)0,false,(unsigned long)10);
        checkerror(status);

//         // poll for incoming data
//         status = sess.PollData();
// 
//         // check incoming packets
//         if (sess.GotoFirstSourceWithData())
//         {
//             do
//             {
//                 RTPPacket *pack;
// 
//                 while ((pack = sess.GetNextPacket()) != NULL)
//                 {
//                     // You can examine the data here
//                     TRACE("Got packet !\n");
// 
//                     // we don't longer need the packet, so
//                     // we'll delete it
//                     delete pack;
//                 }
//             } while (sess.GotoNextSourceWithData());
//         }

        //TRACE("Press enter to send the next packet\n");
        //gets(dummybuffer);
    }
}

void CDlg_RTSP::OnBnClickedRtspButRtpServer()
{
    static bool bInit = false;

    if (!bInit)
    {
        bInit = true;
        
        int nThreadID = 0;

        _beginthreadex(NULL, 0, RtpThread, NULL, 0, (unsigned int *)&nThreadID);

        GetDlgItem(IDC_RTSP_BUT_RTP_SERVER)->EnableWindow(FALSE);
    }    
}
