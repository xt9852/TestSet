
#include "stdafx.h"
#include "Dlg_Finger.h"


IMPLEMENT_DYNAMIC(CDlg_Finger, CDialog)
CDlg_Finger::CDlg_Finger(CWnd* pParent /*=NULL*/)
    :CDialog(CDlg_Finger::IDD, pParent)
{
    memset(feature_, 0, sizeof(feature_));
}

CDlg_Finger::~CDlg_Finger()
{
}

void CDlg_Finger::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_FINGER_BMP1, bmp1_);
    DDX_Control(pDX, IDC_FINGER_BMP2, bmp2_);
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlg_Finger, CDialog)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_BN_CLICKED(IDC_FINGER_BTN_BMP1, &CDlg_Finger::OnBnClickedFingerBtnBmp1)
    ON_BN_CLICKED(IDC_FINGER_BTN_BMP2, &CDlg_Finger::OnBnClickedFingerBtnBmp2)
    ON_BN_CLICKED(IDC_FINGER_BTN_COMP, &CDlg_Finger::OnBnClickedFingerBtnComp)
END_MESSAGE_MAP()

BOOL CDlg_Finger::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;
}

void CDlg_Finger::OnPaint()
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

BOOL CDlg_Finger::OnEraseBkgnd(CDC* pDC)
{
    //return __super::OnEraseBkgnd(pDC);
    return TRUE;
}


void CDlg_Finger::OnBnClickedFingerBtnBmp1()
{
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_ENABLESIZING, "Bitmap Files (*.bmp)|*.bmp|", this);

    if (dlg.DoModal() != IDOK) return;

    char path[MAX_PATH] = "";
    sprintf_s(path, "%s\\finger_bmp1\\", g_ProFile.getPath());
    CreateDirectory(path, NULL);
    finger_.path_ = path;

    finger_.loadBitmap(dlg.GetPathName());
    finger_.preprocess();
    finger_.getFeature(&feature_[0]);

    sprintf_s(path, "%s\\finger_bmp1\\finger_minutia.bmp", g_ProFile.getPath());

    hImage1_ = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
        path,
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    bmp1_.SendMessage(STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)hImage1_);
}


void CDlg_Finger::OnBnClickedFingerBtnBmp2()
{
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_ENABLESIZING, "Bitmap Files (*.bmp)|*.bmp|", this);

    if (dlg.DoModal() != IDOK) return;

    char path[MAX_PATH] = "";
    sprintf_s(path, "%s\\finger_bmp2\\", g_ProFile.getPath());
    CreateDirectory(path, NULL);
    finger_.path_ = path;

    finger_.loadBitmap(dlg.GetPathName());
    finger_.preprocess();
    finger_.getFeature(&feature_[1]);

    sprintf_s(path, "%s\\finger_bmp2\\finger_minutia.bmp", g_ProFile.getPath());

    hImage2_ = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
        path,
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    bmp2_.SendMessage(STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)hImage2_);
}


void CDlg_Finger::OnBnClickedFingerBtnComp()
{
    int s = finger_.match(&feature_[0], &feature_[1]);

    char info[128] = "";
    sprintf_s(info, "相似度:%d,比较%s", s, (s>50?"成功":"失败"));

    MessageBox(info);
}
