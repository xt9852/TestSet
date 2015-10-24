
#include "stdafx.h"
#include "resource.h"
#include "Dlg_Media.h"

typedef struct _tagBlockEx* PBLOCKEX;

IMPLEMENT_DYNAMIC(CDlg_Media, CDialog)
CDlg_Media::CDlg_Media(CWnd* pParent /*=NULL*/)
    :CDialog(CDlg_Media::IDD, pParent)
{
// 	m_pbyData = NULL;
// 	m_dwDataLen = 0;
// 	m_hBrush.CreateSolidBrush(RGB(212, 208, 200));
}

CDlg_Media::~CDlg_Media()
{
//	if (NULL != m_pbyData) delete[] m_pbyData;

    OnBnClickedMediaBtnUninit();
}

void CDlg_Media::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MEDIA_TAB, tableCtrl_);
    DDX_Control(pDX, IDC_MEDIA_SLIDER1, m_SoundSel);
}

BEGIN_MESSAGE_MAP(CDlg_Media, CDialog)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_MEDIA_BTN_INIT,               OnBnClickedMediaBtnInit)
    ON_BN_CLICKED(IDC_MEDIA_BTN_UNINIT,             OnBnClickedMediaBtnUninit)
    ON_BN_CLICKED(IDC_MEDIA_BTN_START,              OnBnClickedStart)
    ON_BN_CLICKED(IDC_MEDIA_BTN_STOP,               OnBnClickedStop)
END_MESSAGE_MAP()

BOOL CDlg_Media::OnInitDialog()
{
    CDialog::OnInitDialog();

    tableCtrl_.InsertItem(0,  "H264");
    tableCtrl_.InsertItem(1,  "H323");

    m_SoundSel.SetRange(0, 100, TRUE);
    m_SoundSel.SetTicFreq(10);
// 
//     BYTE byError = m_SrvAV.Init(this);
//     if (0 != byError)
//     {
//         CString strError(_T("初使化客户端错误:"));
//         strError.AppendFormat(_T("%d"), byError);
//         MessageBox(strError);
//         return FALSE;
//     }
// 
//     byError = m_SrvAV.Start();
//     if (0 != byError)
//     {
//         CString strError(_T("运行错误:"));
//         strError.AppendFormat(_T("%d"), byError);
//         MessageBox(strError);
//         return FALSE;
//     }

    return TRUE;
}

void CDlg_Media::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文
    }
    else
    {
        CDialog::OnPaint();
    }
}

BOOL CDlg_Media::OnEraseBkgnd(CDC* pDC)
{
    //return __super::OnEraseBkgnd(pDC);
    return TRUE;
}

void CDlg_Media::OnBnClickedMediaBtnInit()
{
    int cx = IMAGE_WIDTH*2;
    int cy = IMAGE_HEIGHT*2;

    int ret = videoCature_.init(cx, cy);

    if (0 != ret)
    {
        MessageBox("打开射像头失败");
        return;
    }

    ret = videoPlay_.init(20, 80, GetDC()->m_hDC, videoCature_.getBmpInfoHeader());

    if (0 != ret)
    {
        MessageBox("初始化播放器");
        return;
    }

    ret = videoPlay2_.init(420, 80, GetDC()->m_hDC, videoCature_.getBmpInfoHeader());

    if (0 != ret)
    {
        MessageBox("初始化播放器");
        return;
    }

    ret = videoEncode_.init(cx, cy);

    if (0 != ret)
    {
        MessageBox("初始化H264失败");
        return;
    }

    ret = videoDecode_.init(cx, cy);

    if (0 != ret)
    {
        MessageBox("初始化H264失败");
        return;
    }

    videoCature_.setNext(&videoPlay_);
    videoPlay_.setNext(&videoEncode_);
    videoEncode_.setNext(&videoDecode_);
    videoDecode_.setNext(&videoPlay2_);
}

void CDlg_Media::OnBnClickedMediaBtnUninit()
{
    videoPlay_.uninit();
    videoCature_.uninit();
}

void CDlg_Media::OnBnClickedStart()
{
    videoCature_.startCapture();
}

void CDlg_Media::OnBnClickedStop()
{
    videoCature_.stopCapture();
}

void CDlg_Media::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    m_SoundSel.GetPos();

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
