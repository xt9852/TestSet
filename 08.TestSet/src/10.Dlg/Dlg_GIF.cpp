// Dlg_GIF.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "Dlg_GIF.h"
#include ".\dlg_gif.h"
#include<vfw.h>

typedef struct gifImage{
    WORD lWidth;
    WORD lHeight;
    WORD width;
    WORD height;
    struct flag{
        BYTE d:3;
        BYTE c:1;
        BYTE b:3;
        BYTE a:1;
    }Flag;
}GifImage,*PGifImage;

// Flag为一个标志，a指是否存在局域性调色板，b为存储方式（与本主题无关），c为RGB值是否经过排序（无关），d为调色板的大小，为3*2^(d+1);
// 文件组织:"GIF" + *** + {图象开头(0x00,0x2c) + 图像结构(GifImage) + 压缩有关的数字(BYTE) + 图象的大小 + 图象存储内容 } + {...} + 数据块结束(0x00)


#include <math.h>

static UINT GifThread(LPVOID gifDC)
{
    CDC* pdc = (CDC*)gifDC;
    HINSTANCE handle = ::AfxGetResourceHandle();

    /*	HRSRC hrsrc = ::FindResource(handle, MAKEINTRESOURCE(),"IMAGE");
    DWORD word = ::SizeofResource(handle,hrsrc);
    BYTE* lpBy = (BYTE*)LoadResource(handle,hrsrc);
    */
    std::string fileName = g_ProFile.getPath() + std::string("\\res\\1.gif");

    FILE *file;
    file = fopen(fileName.c_str(), "r");
    if(NULL == file) return -1;

    fseek(file, 0, SEEK_END);
    DWORD word = ftell(file);

    BYTE *lpBy = new BYTE[word];

    fseek(file, 0, SEEK_SET);
    fread(lpBy, word, 1, file);
    fclose(file);

    BYTE* pByte[20];
    DWORD nu[20];
    int num = 0;
    DWORD firstLocation = 0;
    for(DWORD j=0;j<word;j++)
    {
        if(lpBy[j]==0x2c)
        {
            if(lpBy[j-1]==0x00)
            {

                if(num==0)
                {
                    firstLocation = j;
                }
                PGifImage nowImage = (PGifImage)&lpBy[j+1];
                if(nowImage->Flag.a==0)
                {
                    DWORD number = 1+sizeof(GifImage);
                    while(lpBy[j+number]!=0)
                    {
                        number = number+(DWORD)lpBy[j+number]+1;
                    }
                    number++;
                    pByte[num] = new BYTE[number];
                    for(DWORD n=0;n<number;n++)
                    {
                        *(BYTE*)(pByte[num]+n) = lpBy[j+n];
                    }
                    nu[num] = number;
                    j = j+number-1;
                    num++;
                }
                else
                {
                    int number = 1+sizeof(GifImage)+1+3*(int)floor(pow(2.0,nowImage->Flag.d));
                    while(lpBy[j+number]!=0)
                    {
                        number = number+lpBy[j+number];
                    }
                    pByte[num] = new BYTE[number];
                    for(int n=0;n<number;n++)
                    {
                        *(BYTE*)(pByte[num]+n) = lpBy[j+n];
                    }
                    nu[num] = number;
                    j = j+number-1;
                    num++;
                }
            }
        }
    }
    for(int i = 0; i < 3; i++)
    {
        for(int m=0;m<num;m++)
        {
            CBrush brush(RGB(255,255,255));
            pdc->FillRect(CRect(0,0,500,500),&brush);
            DWORD DDD;
            VirtualProtect(lpBy,word,PAGE_READWRITE,&DDD);
            for(DWORD n=0;n<nu[m];n++)
            {
                lpBy[firstLocation+n] = *(BYTE*)(pByte[m]+n);
            }
            VirtualProtect(lpBy,word,DDD,NULL);

            CMemFile memfile(lpBy,word);
            CArchive ar(&memfile,CArchive::load|CArchive::bNoFlushOnDelete);
            CArchiveStream arcstream(&ar);
            CComQIPtr<IPicture> m_picture;
            HRESULT hr = OleLoadPicture((LPSTREAM)&arcstream,0,false,IID_IPicture,(void**)&m_picture);
            long a,b;
            m_picture->get_Width(&a);
            m_picture->get_Height(&b);
            CSize sz(a,b);
            pdc->HIMETRICtoDP(&sz);
            CRect rect;
            m_picture->Render(*pdc,0,0,sz.cx,sz.cy,0,b,a,-b,&rect);
            Sleep(100);
        }
    }

    delete[] lpBy;
    return 1;
}



extern UINT WM_HTML_CLICK;


// CDlg_GIF 对话框

IMPLEMENT_DYNAMIC(CDlg_GIF, CDialog)
CDlg_GIF::CDlg_GIF(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_GIF::IDD, pParent)
{
}

CDlg_GIF::~CDlg_GIF()
{
}

void CDlg_GIF::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_GIF_RICHEDIT, m_RichEdit);
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_GIF, CDialog)
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_REGISTERED_MESSAGE(WM_HTML_CLICK, OnHtmlClick)
    ON_BN_CLICKED(IDC_GIF_BTN_GIF, OnBnClickedGifBtnGif)   
    ON_BN_CLICKED(IDC_GIF_BTN_CALL_JAVASCRIPT, OnBnClickedGifBtnCallJavascript)
END_MESSAGE_MAP()


BOOL CDlg_GIF::OnInitDialog()
{
    CDialog::OnInitDialog();

    //--------------------------------------------------------------

    std::string strPath;

    for (int i = 0; i < 5; i++)
	{
        m_pKeyFile[i] = NULL;
	}

    m_RichEdit.Init();

    m_RichEdit.WriteKeyLink("\nWriteKeyLink");
    m_RichEdit.WriteKeyText("         WriteKeyText\n");
    m_pKeyFile[0] = m_RichEdit.WriteKeyTransFile("传输文件控件", (UINT64)10*1024*1024*1024, "res\\Contact0.ico", "开始");
    
    m_RichEdit.SetKeyTransFile(m_pKeyFile[0], _T(""), 1, (UINT64)6*1024*1024*1024);

    m_RichEdit.WriteKeyText("\n");
    m_pKeyFile[1] = m_RichEdit.WriteKeyTransFile("TestSet.rc2", 1000, "", "开始");
    m_RichEdit.WriteKeyText("\n");
    strPath = g_ProFile.getPath() + std::string("\\res\\1001.gif");
    m_RichEdit.WriteKeyImage(strPath.c_str());
    strPath = g_ProFile.getPath() + std::string("\\res\\001.jpg");
    m_pKeyFile[2] = m_RichEdit.WriteKeyImage(strPath.c_str());
    strPath = g_ProFile.getPath() + std::string("\\res\\Contact4.ico");
    m_RichEdit.WriteKeyImage(strPath.c_str());
    m_RichEdit.WriteKeyText("\n");
    strPath = g_ProFile.getPath() + std::string("\\res\\1002.gif");
    m_pKeyFile[3] = m_RichEdit.WriteKeyGif(strPath.c_str());

    strPath = g_ProFile.getPath() + std::string("\\res\\003.jpg");
    m_RichEdit.SetKeyImage(m_pKeyFile[2], strPath.c_str());
    strPath = g_ProFile.getPath() + std::string("\\res\\1001.gif");
    m_RichEdit.SetKeyGif(m_pKeyFile[2], strPath.c_str());

    //--------------------------------------------------------------
    // 网页

	strPath = g_ProFile.getPath();
	strPath += "\\res\\htm\\Demo.htm";

    // 创建浏览器
    m_Browser.CreateFromStatic(IDC_GIF_STATIC1, this);
    m_Browser.Navigate2(strPath.c_str(),NULL,NULL);

    //m_HtmlCtrl.CreateFromCtrl(IDC_GIF_STATIC1, this);
    //m_HtmlCtrl.Navigate(g_ProFile.getPath() + "\\res\\htm\\ShowImage.html");

    //--------------------------------------------------------------	

    GetDlgItem(IDC_GIF_EDIT1)->SetWindowText("0");

    this->SetTimer(1, 200, NULL);

    //--------------------------------------------------------------

    return TRUE;
}

void CDlg_GIF::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文
    }
    else
    {		
        CDialog::OnPaint();

        //if (m_hDC == NULL || m_hCompDC == NULL)	return;
        //::BitBlt(m_hDC, 0, 0, 100, 100, m_hCompDC, 0, 0, SRCCOPY);
    }
}

void CDlg_GIF::OnBnClickedGifBtnGif()
{
    CString strFilePath;
    CString strFileName;

    CFileDialog FileDlg(TRUE, NULL, NULL, NULL, "GIF *.gif|*.gif||");
    FileDlg.m_ofn.lpstrInitialDir = g_ProFile.getPath();   

    if(FileDlg.DoModal()==IDOK)
    {
        strFileName = FileDlg.GetFileName();
        m_gif.Load((LPCTSTR)strFileName);

        UINT nCount = m_gif.getFrameCount();

        CString strFrameNum;
        GetDlgItem(IDC_GIF_EDIT1)->GetWindowText(strFrameNum);
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

            m_gif.Draw(::GetDC(this->GetSafeHwnd()), 0, 0, nFrameNum);
        }
    }
}

void CDlg_GIF::OnTimer(UINT nIDEvent)
{
    static int a = 0;
    m_RichEdit.SetKeyTransFile(m_pKeyFile[1], _T(""), 1, a++);
    CDialog::OnTimer(nIDEvent);
}

LRESULT CDlg_GIF::OnHtmlClick(WPARAM wParam, LPARAM lParam)
{
    std::string strFileName = g_ProFile.getPath();
	strFileName += "\\res\\";
	strFileName += (LPCTSTR)wParam;

    switch ((int)lParam)
    {
    case FILE_GIF:
        {
            KEY_AREA *pKey = m_RichEdit.WriteKeyGif(strFileName.c_str());
            break;
        }
    case FILE_JPG:
    case FILE_BMP:
        {
            KEY_AREA *pKey = m_RichEdit.WriteKeyImage(strFileName.c_str());
            break;
        }
    default:
        break;
    }
    m_RichEdit.WriteText("\n");
    return 0;
}

void CDlg_GIF::OnBnClickedGifBtnCallJavascript()
{
    m_Browser.CallJScript("ShowTime");
}
