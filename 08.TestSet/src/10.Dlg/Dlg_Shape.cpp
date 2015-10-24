// Dlg_Shape.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_Shape.h"
#include "Common\ScaleBmp.h"


// CDlg_Shape 对话框

IMPLEMENT_DYNAMIC(CDlg_Shape, CDialog)
	CDlg_Shape::CDlg_Shape(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Shape::IDD, pParent),
	m_nDlgHeight(0),
	m_pDesktopWnd(NULL),
	m_pDeskTopDC(NULL)
{
}

CDlg_Shape::~CDlg_Shape()
{
}

void CDlg_Shape::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_Shape, CDialog)
    ON_BN_CLICKED(IDC_SHAPE_BUT_SHAPE,		OnBnClickedButShape)
    ON_BN_CLICKED(IDC_SHAPE_BUT_FACE,		OnBnClickedButFace)
	ON_BN_CLICKED(IDC_SHAPE_BUT_LINE,		OnBnClickedButLine)
    ON_BN_CLICKED(IDC_SHAPE_BUT_SCALE_BMP,	OnBnClickedButScaleBmp)
	ON_BN_CLICKED(IDC_SHAPE_BUT_3D,			OnBnClickedBut3d)
    ON_BN_CLICKED(IDC_SHAPE_BUT_TREE,		OnBnClickedButTree)
END_MESSAGE_MAP()

BOOL CDlg_Shape::OnInitDialog()
{
    CDialog::OnInitDialog();

    //-------------------------------------------------------------
    //查找“Program Manager”窗口
    HWND hWnd= (HWND)::FindWindow("Progman", "Program Manager");
    if (hWnd != NULL)
    {
        //找到“Program Manager”窗口,下面将通过该窗口找到桌面的窗口句柄
        CWnd *pWnd = FindWindowEx(hWnd, NULL, "SHELLDLL_DefView", NULL);
        if (pWnd != NULL)
        {
            //取得桌面ListView控件的窗口句柄
            //真正的桌面,可以用spy++查看
            m_pDesktopWnd = pWnd->GetDlgItem(1);

            m_pDeskTopDC = m_pDesktopWnd->GetWindowDC();

            CRect rcWnd;
            m_pDesktopWnd->GetWindowRect(&rcWnd);
            m_nDlgHeight = rcWnd.Height();
        }
        else
        {
            m_pDesktopWnd = this;

            CRect rcWnd;
            GetWindowRect(&rcWnd);
            m_nDlgHeight = rcWnd.Height();

            m_pDeskTopDC = GetWindowDC();
        }
    }

    //-------------------------------------------------------------

    m_Shape.SetDC(m_pDeskTopDC);
    m_Shape.SetScreenHeight(m_nDlgHeight);

    return TRUE;
}

void CDlg_Shape::OnBnClickedButShape()
{
	if (m_Shape.m_bRun)
	{
		m_Shape.m_bRun = false;
	}
	else if (!m_Shape.m_bThread)
	{
		UINT nThreadId = 0;
		HANDLE hWorkThread = (HANDLE)_beginthreadex(NULL, 0, WorkThread, (void*)this, 0, &nThreadId);
		CloseHandle(hWorkThread);
	}
	else
	{
		m_Shape.m_bRun = true;
	}
}

unsigned CDlg_Shape::WorkThread(LPVOID pParam)
{
    if (NULL == pParam) return -1;

	CDlg_Shape *pThis = reinterpret_cast<CDlg_Shape*>(pParam);
	pThis->m_Shape.Do();

    return 0;
}

void CDlg_Shape::Line(CDC *pdc, int x1, int y1, int x2, int y2)
{
    pdc->MoveTo(x1, y1);
    pdc->LineTo(x2, y2);
}

void CDlg_Shape::OnBnClickedButFace()
{
    CPen *pOldPen = NULL;

    CPen pen1(BS_SOLID, 1, RGB(255, 0, 0));
    CPen pen2(BS_SOLID, 1, RGB(0, 255, 0));
    CPen pen3(BS_SOLID, 1, RGB(0, 0, 255));
    CPen pen4(BS_SOLID, 1, RGB(255, 0, 255));
    CPen pen5(BS_SOLID, 1, RGB(255, 255, 0));
    CPen pen6(BS_SOLID, 1, RGB(0, 255, 255));

    pOldPen = m_pDeskTopDC->SelectObject(&pen1);

    //-----------------------------------------------------
    double u,m;
    int i,j,p[40][40][2];
    double urr[3],vrr[3],t1,t2,t3,r1,r2,r3;

    int C[9][2] = { { 50,180},{200,250},{330,100},
    {120,200},{120,410},{550,230},
    {150,350},{210,100},{500,322}};

    for(i = 0; i < 40; i++)
    {
        u = i / 40.0;
        urr[0] = u*u - 2*u + 1;
        urr[1] = -2*u*u + 2*u;
        urr[2] = u*u;

        for(j = 0; j < 40; j++)
        {
            m = j / 40.0;
            vrr[0] = m*m - 2*m + 1;
            vrr[1] = -2*m*m + 2*m;
            vrr[2] = m*m;

            t1 = urr[0]*C[0][0] + urr[1]*C[3][0] + urr[2]*C[6][0];
            t2 = urr[0]*C[1][0] + urr[1]*C[4][0] + urr[2]*C[7][0];
            t3 = urr[0]*C[2][0] + urr[1]*C[5][0] + urr[2]*C[8][0];
            p[i][j][0] = (int)(t1*vrr[0] + t2*vrr[1] + t3*vrr[2]);

            r1 = urr[0]*C[0][1] + urr[1]*C[3][1] + urr[2]*C[6][1];
            r2 = urr[0]*C[1][1] + urr[1]*C[4][1] + urr[2]*C[7][1];
            r3 = urr[0]*C[2][1] + urr[1]*C[5][1] + urr[2]*C[8][1];
            p[i][j][1] = (int)(r1*vrr[0] + r2*vrr[1] + r3*vrr[2]);

            if (i == 0 && j == 0)
            {
                m_pDeskTopDC->MoveTo(C[0][0], C[0][1]);
            }

            if (i == 0)
            {
                m_pDeskTopDC->SelectObject(&pen1);
                m_pDeskTopDC->LineTo(p[i][j][0],p[i][j][1]);
            }
            if (j != 0 && i != 0)
            {
                if (i == 19)
                {
                    m_pDeskTopDC->SelectObject(&pen2);
                    Line(m_pDeskTopDC, p[i][j-1][0],p[i][j-1][1],p[i][j][0],p[i][j][1]);
                    m_pDeskTopDC->SelectObject(&pen3);
                    Line(m_pDeskTopDC, p[i-1][j][0],p[i-1][j][1],p[i][j][0],p[i][j][1]);
                }
                else
                {
                    m_pDeskTopDC->SelectObject(&pen4);
                    Line(m_pDeskTopDC, p[i-1][j][0],p[i-1][j][1],p[i][j][0],p[i][j][1]);
                    m_pDeskTopDC->SelectObject(&pen5);
                    Line(m_pDeskTopDC, p[i][j-1][0],p[i][j-1][1],p[i][j][0],p[i][j][1]);
                }
            }
            if (j == 0 && i > 0)
            {
                m_pDeskTopDC->SelectObject(&pen6);
                Line(m_pDeskTopDC, p[i-1][j][0],p[i-1][j][1],p[i][j][0],p[i][j][1]);
            }

            //::Sleep(10);
        }
    }

    pOldPen = m_pDeskTopDC->SelectObject(pOldPen);
    pen1.DeleteObject();
    pen2.DeleteObject();
    pen3.DeleteObject();
    pen4.DeleteObject();

    m_pDeskTopDC->ReleaseAttribDC();
}

void CDlg_Shape::OnBnClickedButLine()
{
	double  e  = 2.71828;
	double	pi = 3.1415926/180.0;
	double	t  = 0.0;
	double	nt = 0.0;

	double	x = 0;
	double	y = 0;

	double	r = 0.1;
	double	k = 0.03;
	double	a = 10.0;
	double	b = 10.0;
	double	d = 60.0;

	for (int i = 0; i < 360*20; i++)
	{
		t = i*pi;

		// 摆线
		//x = r * (t - sin(t));
		//y = r * (1 - cos(t));

		// 外摆线(b为动圆半径，a为定圆半径)，a=b时，它就是心脏线
		// x=(a+b)cosθ-bcos[(a+b)θ/b]; 
		// y=(a+b)sinθ-bsin[(a+b)θ/b];
		//x = (a+b)*cos(t)-d*cos((a+b)*t/b);
		//y = (a+b)*sin(t)-d*sin((a+b)*t/b);

		// 内摆线(b为动圆半径，a为定圆半径)
		// x=(a-b)cosθ+bcos[(a-b)θ/b]; 
		// y=(a-b)sinθ-bsin[(a-b)θ/b];
		//x = (a-b)*cos(t)+d*cos((a-b)*t/b);
		//y = (a-b)*sin(t)-d*sin((a-b)*t/b);

		// 对数螺线
		// p = ae^(kt)
		x = a*pow(e,k*t)*cos(t);
		y = a*pow(e,k*t)*sin(t);

		// 双曲螺线
		//x = r/t*cos(t)/t;
		//y = r/t*sin(t)/t;

		// 阿基米德螺线
		//r=10*(1+t)
		//x=r*cos(t*360)
		//y=r*sin(t*360)

		//r=10*(1+t);
		//x=r*cos(t*360);
		//y=r*sin(t*360);

		// 笛卡尔叶形线
		//x^3+y^3-3axy=0
		// x = (3at)/(1+t^3)
		// y = (3at^2)/(1+t^3)
		//x = 3*a*t/(1+pow(t,3));
		//y = 3*a*t*t/(1+pow(t,3));

		m_pDeskTopDC->SetPixel((int)x+600, m_nDlgHeight-((int)y+500) , RGB(0,0,255));
	}

	m_pDeskTopDC->ReleaseAttribDC();
}

void CDlg_Shape::OnBnClickedButScaleBmp()
{
    CString strFilePath;
    CString strFileName;

    CFileDialog FileDlg(TRUE, NULL, NULL, NULL, _T("BMP *.bmp|*.bmp||"));
    FileDlg.m_ofn.lpstrInitialDir = g_ProFile.getPath();   

    if(FileDlg.DoModal()==IDOK)
    {
        strFileName = FileDlg.GetPathName();

        CScaleBmp ScaleBmp;
        if (ScaleBmp.Load(strFileName.GetString()))
        {
            strFileName.Insert(strFileName.GetLength() - 4, "_scale");

            ScaleBmp.SaveBmp(strFileName.GetString(), 10, 10);
        }
    }
}

#define NO 999     /* 一个标志，指示有无对应的点*/
#define W 64       /* 重复的图案宽度 */
#define MAXX 639   /* 三维画最大宽度 */
#define MAXY 479   /* 三维画最大高度 */
#define MAXZ 7     /* 三维形象最大层数 */

void CDlg_Shape::OnBnClickedBut3d()
{
	char szUser[80];   
	DWORD cbUser = 80;   
	GetUserName(szUser, &cbUser);
	TRACE("---------------%s\n", szUser);

	TCHAR szPath[MAX_PATH + 1] = _T("");
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_DESKTOPDIRECTORY, FALSE);
	TRACE("---------------%s\n", szPath);

    int dot[MAXX+1][3];

    /* 下面数据决定看到的三维形象 */
    char *hf[]=
    {
        "11111111111111111111111111111111",
        "11111111111111111111111111111111",
        "11111111111111111111111111111111",
        "11117777777711111177777777711111",
        "11117777777771111177111111771111",
        "11111111117771111177111111771111",
        "11111111117771111177111111771111",
        "11117777777771111177111111771111",
        "11111111117771111177111111771111",
        "11111111117771111177111111771111",
        "11117777777771111177111111771111",
        "11117777777711111177777777711111",
        "11111111111111111111111111111111",
        "11111111111111111111111111111111",
        "11112131415161716151413121111111",
        "11111213141516171615141312111111",
        "11111111111111111111111111111111",
        "11111111111111111111111111111111",
        "11112223344456665443322211111111",
        "11112223344456665443322211111111",
        "10101010101010101010101010101010",
        "01010101010101010101010101010101",
        "10101010101010101010101010101010",
        "01010101010101010101010101010101"
    };

    int lx,rx,tx;
    int i;
    int x,y,h;

    CPen pen1(BS_SOLID, 1, RGB(255, 0, 0));
    CPen pen2(BS_SOLID, 1, RGB(0, 255, 0));
    CPen pen3(BS_SOLID, 1, RGB(0, 0, 255));
    CPen pen4(BS_SOLID, 1, RGB(255, 0, 255));
    CPen pen5(BS_SOLID, 1, RGB(255, 255, 0));
    CPen pen6(BS_SOLID, 1, RGB(0, 255, 255));

    CPen *pen[6];
    pen[0] = &pen1;
    pen[1] = &pen2;
    pen[2] = &pen3;
    pen[3] = &pen4;
    pen[4] = &pen5;
    pen[5] = &pen6;

    for(i=1;i<=8000*3;i++)// 在屏幕上画出随机的线，作为三维画的底纹
    {
        x = rand() % MAXX;
        y = rand() % MAXY;
        m_pDeskTopDC->SelectObject(pen[rand()%6]);
        m_pDeskTopDC->MoveTo(x,y);		
        m_pDeskTopDC->LineTo(x+rand()%70,y+rand()%70);
    }

    for(y=0; y<= MAXY; y+=20)// 从0到MAXY一行一行进行.hf的Y坐标,hf的Y共32行,MAXY=480,480/32=20
    {
        for(x=0; x<=MAXX; x++)// 生成平面数据
        {
            dot[x][1] = NO; // 右视图
            dot[x][2] = NO;	// 左视图

            if (x+W <= MAXX)
                dot[x][1]= x + W; // 生成的图像在右视图上取的点的位置

            if (x-W >= 0)
                dot[x][2]= x - W; // 生成的图像在左视图上取的点的位置
        }

        for(h=1; h<=MAXZ; h++)// 从1层到MAXZ层，逐层处理
        {
            for(x=0; x<=MAXX; x++)
            {
                lx = x - W /2 + h; // 越靠前的图层，两点的距离越近 
                rx = x + W / 2 - h;

                if (hf[y/20][x/20]-48 == h && lx >= 0 && rx <= MAXX)
                {
                    if (dot[lx][1] !=NO)
                        dot[dot[lx][1]][2]= NO;

                    dot[lx][1] = rx;

                    if(dot[rx][2] != NO)
                        dot[dot[rx][2]][1] = NO;

                    dot[rx][2] = lx;
                }
            }
        }

        // 依据前面计算得到的数据画出一行三维画 
        for (x=0; x<=MAXX; x++)
        {
            if (dot[x][2] == NO)
            {
                dot[x][0] = x;
                tx = x;
                while(dot[tx][1]!=NO)
                {
                    tx = dot[tx][1];
                    dot[tx][0] = x;
                }
            }

            if (dot[x][0] != x)
            {
                m_pDeskTopDC->BitBlt(x, y, 1, 19, m_pDeskTopDC, dot[x][0], y, SRCCOPY);
            }
        }
    }
}

typedef struct _tagTreeNode
{
    POINT pt;
    int   value1; // 角度
    int   value2; // 长度
    int   level;  // 层数
    CPen  *pen;   // 画笔

    _tagTreeNode *left;
    _tagTreeNode *right;

}TreeNode, *PTreeNode;

typedef std::list<PTreeNode> TreeNodeList;

void CDlg_Shape::OnBnClickedButTree()
{
    TreeNode *temp = NULL;
    TreeNode *root = new TreeNode;
    memset(root, 0, sizeof(TreeNode));
    root->pt.x = 300;
    root->pt.y = 500;
    root->value1 = 180;
    root->value2 = 50;
    root->pen = new CPen(BS_SOLID, 1, RGB(rand()%256, rand()%256, rand()%256));
    
    int curLevel = -1;
    CPen *pOldPen = m_pDeskTopDC->SelectObject(root->pen);

    TreeNodeList list;
    list.push_back(root);

    for (int i = 0; ; i++)
    {
        TreeNodeList::iterator iter = list.begin();

        if (iter != list.end())
        {
            TreeNode *node = *iter;

            list.pop_front();

            if (node->level != curLevel)
            {
                CPen *pen = new CPen(BS_SOLID, 1, RGB(rand()%256, rand()%256, rand()%256));

                m_pDeskTopDC->SelectObject(pen);

                node->pen = pen;

                curLevel = node->level;
            }

            if (NULL == node->left)
            {
                TreeNode *left = new TreeNode;
                memset(left, 0, sizeof(TreeNode));
                node->left = left;

                left->level  = node->level + 1;
                left->value1 = node->value1 + 30;
                left->value2 = node->value2 - 5;
                left->pt.x = node->pt.x + sin(left->value1 / 180.0 * 3.141592653589793) * left->value2;
                left->pt.y = node->pt.y + cos(left->value1 / 180.0 * 3.141592653589793) * left->value2;

                if (left->value2 <= 0) break;

                list.push_back(left);

                Line(m_pDeskTopDC, node->pt.x,node->pt.y,left->pt.x,left->pt.y);
            }

            if (NULL == node->right)
            {
                TreeNode *right = new TreeNode;
                memset(right, 0, sizeof(TreeNode));
                node->right = right;

                right->level   = node->level + 1;
                right->value1 = node->value1 - 30;
                right->value2 = node->value2 - 5;
                right->pt.x = node->pt.x + sin(right->value1 / 180.0 * 3.141592653589793) * right->value2;
                right->pt.y = node->pt.y + cos(right->value1 / 180.0 * 3.141592653589793) * right->value2;

                if (right->value2 <= 0) break;

                list.push_back(right);

                Line(m_pDeskTopDC, node->pt.x,node->pt.y,right->pt.x,right->pt.y);
            }
        }
    }

    list.clear();
    list.push_back(root);

    for (int i = 0; ; i++)
    {
        TreeNodeList::iterator iter = list.begin();

        if (iter != list.end())
        {
            TreeNode *node = *iter;

            list.pop_front();

            if (NULL != node->left)
            {
                list.push_back(node->left);
            }

            if (NULL != node->right)
            {
                list.push_back(node->right);
            }

            if (NULL != node->pen)
            {
                node->pen->DeleteObject();
                delete node->pen;
            }

            delete node;
        }
        else
        {
            break;
        }
    }

    m_pDeskTopDC->SelectObject(pOldPen);
    m_pDeskTopDC->ReleaseAttribDC();
    list.clear();
}
