
#include "stdafx.h"
#include "resource.h"
#include "Dlg_Media.h"

typedef struct _tagBlockEx* PBLOCKEX;

IMPLEMENT_DYNAMIC(CDlg_Media, CDialog)
CDlg_Media::CDlg_Media(CWnd* pParent /*=NULL*/)
    :CDialog(CDlg_Media::IDD, pParent)
{
}

CDlg_Media::~CDlg_Media()
{
    OnBnClickedMediaBtnUninit();
}

void CDlg_Media::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MEDIA_TAB, tableCtrl_);
    DDX_Control(pDX, IDC_MEDIA_SLIDER1, soundCtrl_);
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

    soundCtrl_.SetRange(0, 100, TRUE);
    soundCtrl_.SetTicFreq(10);

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

    ret = videoPlay1_.init(20, 80, GetDC()->m_hDC, videoCature_.getBmpInfoHeader());

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

    videoCature_.setNext(&videoPlay1_);
    videoPlay1_.setNext(&videoEncode_);
    videoEncode_.setNext(&videoDecode_);
    videoDecode_.setNext(&videoPlay2_);
}

void CDlg_Media::OnBnClickedMediaBtnUninit()
{
    videoCature_.stopCapture();
    videoPlay1_.uninit();
    videoPlay2_.uninit();
    videoCature_.uninit();
    videoEncode_.uninit();
    videoDecode_.uninit();
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
    soundCtrl_.GetPos();

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
