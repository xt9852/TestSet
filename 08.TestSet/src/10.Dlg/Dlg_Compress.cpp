
#include "stdafx.h"
#include "Dlg_Compress.h"
#include "Zip/zlib.h"
//#include "Zip/zconf.h"
#pragma comment(lib, "../lib/MySQL/zlib.lib")

/* 
  航空述语	Morse码 念法 
A Alfa		.-		AL-FAH
B Bravo		-...	BRAH-VOH
C Charlie	-.-.	CHAR-LEE
D Delta		-..		DELL-TAH
E Echo		.		ECK-OH
F Foxtrot	..-.	FOKS-TROT
G Golf		--.		GOLF
H Hotel		....	HOH-TEL
I India		..		IN-DEE-AH
J Juliet	.---	JEW-LEE-ETT
K Kilo		-.-		KEY-LOH
L Lima		.-..	LEE-MAH
M Mike		--		MIKE
N November	-.		NO-VEM-BER
O Oscar		---		OSS-CAH
P Papa		.--.	PAH-PAH
Q Quebec	--.-	KEH-BECK
R Romeo		.-.		ROW-ME-OH
S Sierra	...		SEE-AIR-RAH
T Tango		-		TANG-GO
U Uniform	..-		YOU-NEE-FORM
V Victor	...-	VIK-TAH
W Whisky	.--		WISS-KEY
X Xray		-..-	ECKS-RAY
Y Yankee	-.--	YANG-KEY
Z Zulu		--..	ZOO-LOO
1 one		.----	WUN
2 two		..---	TOO
3 three		...--	TREE
4 four		....-	FOW-ER
5 five		.....	FIFE
6 six		-....	SIX
7 seven		--...	SEV-EN
8 eight		---..	AIT
9 nine		----.	NIN-ER
0 zero		-----	ZEE-RO

10 ten
11 eleven
12 twelve


希尔密码:
a=0 ~ z=26
与一个n*n矩阵相乘，结果模26
密钥必须可逆,也模26


仿射密码:
e(x) = (ax + b) % m
d(x) = (a^)(x - b) % m
a和m互质
(a^)为a对m的乘法逆元
a*(a^) % m = 1

例:
当
a=17
b=5
m=26
a^=23
则
e(10)=(17*10+5)%26=19
d(19)=23*(19-5)%26=10

int Ni(int a, int b) //求a相对于b的逆元
{
int i = 0;
while(a*(++i)%b!=1);
return i;
}


维吉利亚:
  abc...xyz
a abc...xyz
b bcd...yza
c cde...zab
. ...   ...
. ...   ...
x xyz...uvw
y yza...vwx
z zab...wxy


恩尼格码:

转子
  ABCDEFGHIJKLMNOPQRSTUVWXYZ
1 EKMFLGDQVZNTOWYHXUSPAIBRCJ
2 AJDKSIRUXBLHWTMCQGZNPYFVOE
3 BDFHJLCPRTXVZNYEIWGAKMUSQO
4 ESOVPZJAYQUIRHXLNFTGKDCMWB
5 VZBRGITYUPSDNHLXAWMJQOFECK
6 JPGVOUMFYQBENHZRDKASXLICTW
7 NZJHGRCXMYSWBOUFAIVLPEKQDT
8 FKQHTLXOCBJSPDZRAMEWNIUYGV
9 LEYJVCNIXWPBQMDRTAKZGFUHOS
0 FSOKANUERHMBTIYCWLQPZXVGJD

反射器
Non-rotate Umkehrwalzes5
B: AY BR CU DH EQ FS GL IP JX KN MO TZ VW
C: AF BV CP DJ EI GO HY KR LZ MX NW QT SU

used in M-4
B: AE BN CK DQ FU GY HW IJ LO MP RX SZ TV
C: AR BD CO EJ FN GT HK IV LM PW QZ SX UY


//-----------------------------------------------------------------------------------

n价行列式的值D:(递归应用)

当n=1时,D=|a11|
当n>=2时,D=a11*A11+a12*A12+...+a1n*A1n

例:
n=2,D=a11*A11+a12*A12=a11*(-1)^(1+1)|a22|+a12*(-1)^(1+2)|a21|=a11*a22-a12*a21

n=3,D=a11*A11+a12*A12+a13*A13=a11*(-1)^(1+1)|a22 a23|+a12*(-1)^(1+2)|a21 a23|+a13*(-1)^(1+3)|a21 a22|
                                            |a32 a33|               |a31 a33|               |a31 a32|

=a11*(a22*a33-a23*a32)-a12*(a21*a33-a23*a31)+a13*(a21*a32-a22*a31)
=a11*a22*a33-a11*a23*a32-a12*a21*a33+a12*a23*a31+a13*a21*a32-a13*a22*a31

//-----------------------------------------------------------------------------------
矩阵A:
|1 2 3|
|2 2 1|
|3 4 3|

矩阵A的1行1列的余子式:
|2 1|
|4 3|

矩阵A的1行2列的余子式:
|1 1|
|3 3|

A11= ((-1)^(1+1))*|2 1| = 2
                  |4 3|

A12= ((-1)^(1+2))*|2 1| = -3
                  |3 3|

A13= ((-1)^(1+3))*|2 2| = 2
                  |3 4|

A21= ((-1)^(2+1))*|2 3| = 6
                  |4 3|

A22= ((-1)^(2+2))*|1 3| = -6
                  |3 3|

A23= ((-1)^(2+3))*|1 2| = 2
                  |3 4|

A31= ((-1)^(3+1))*|2 3| = -4
                  |2 1|

A32= ((-1)^(3+2))*|1 3| = 5
                  |2 1|

A33= ((-1)^(3+3))*|1 2| = -2
                  |2 2|

矩阵A的值(D)=1*2 - 2*(-3) + 3*2=2
矩阵A的值(D)=6+6+24_18-12-4=2     (2!=0)有逆矩阵

            | 2  6 -4|
伴随矩阵A^*=|-3 -6  5|
            | 2  2 -2|

                 1         1           1  | 2  6 -4|   |   1  3  -2|
A的逆矩阵A^(-1)=--- A^*= ------ A^* = --- |-3 -6  5| = |-1.5 -3 2.5|
                |A|       D(A)         2  | 2  2 -2|   |   1  1  -1|

//-----------------------------------------------------------------------------------
    |0  1  2  1  0  0|
A|E=|1  1  4  0  1  0|
    |1 -1  0  0  0  1|

r2<->r1:(1,2行互换)
|1  1  4  0  1  0|
|0  1  2  1  0  0|
|1 -1  0  0  0  1|

r3=-2r1+r3:(1行乘(-2)加3行)
|1  1  4  0  1  0|
|0  1  2  1  0  0|
|1 -3 -8  0 -2  1|

r3=3r2+r3,r1=-r2+r1:
|1  0  2 -1  1  0|
|0  1  2  1  0  0|
|0  0 -2  3 -2  1|

r3=r3/(-2):
|1  0  2 -1   1  0  |
|0  1  2  1   0  0  |
|0  0  1 -3/2 1 -1/2|

r1=-2r3+r1,r2=-2r3+r2:
|1  0  0  2  -1  1  |
|0  1  0  4  -2  1  |
|0  0  1 -3/2 1 -1/2|

A^(-1):
| 2  -1  1  |
| 4  -2  1  |
|-3/2 1 -1/2|

//-----------------------------------------------------------------------------------

x+2z=1
x+y+4z=0
2x+y=-1

解方程:

定义AX=B

  |0  1  2|   |x|   | 1|
A=|1  1  4| X=|y| B=| 0|
  |1 -1  0|   |z|   |-1|

          | 2  -1  1  || 1| | 1|
X=A^(-1)B=| 4  -2  1  || 0|=| 3|
          |-3/2 1 -1/2||-1| |-1|

x=1 y=3 z=-1

*/
int Ni(int a, int b) //求a相对于b的逆元
{
	int i = 0;
	while(a*(++i)%b!=1);
	return i;
}

IMPLEMENT_DYNAMIC(CDlg_Compress, CDialog)
CDlg_Compress::CDlg_Compress(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Compress::IDD, pParent)
{
	m_dwTimeD = 200;
	m_dwTimeDown = 0;
	m_dwTimeUp = 0;
	m_nLen = 0;
}

CDlg_Compress::~CDlg_Compress()
{
}

void CDlg_Compress::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_Compress, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
    ON_BN_CLICKED(IDC_COMPRESS_BTN_COMPRESS, OnBnClickedBtnCompress)
    ON_BN_CLICKED(IDC_COMPRESS_BTN_UNCOMPRESS, OnBnClickedBtnUncompress)
	ON_BN_CLICKED(IDC_COMPRESS_BTN_MORS, OnBnClickedCompressBtnMors)
	ON_BN_CLICKED(IDC_COMPRESS_BTN_UNMORS, OnBnClickedCompressBtnUnmors)
END_MESSAGE_MAP()


BOOL CDlg_Compress::OnInitDialog()
{
    CDialog::OnInitDialog();

	int a[3][3] = { 1,0,1,2,1,0,-3,2,-5 };
	//int a[3][3] = { 'A','B','C','D','E','F','G','H','I' };

	int b = a[0][0]*a[1][1]*a[2][2]-a[0][0]*a[1][2]*a[2][1]
	-a[0][1]*a[1][0]*a[2][2]+a[0][1]*a[2][0]*a[1][2]
	+a[0][2]*a[1][0]*a[2][1]-a[0][2]*a[1][1]*a[2][0];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			TRACE("%d\t", a[i][j]);
		}
		TRACE("\n");
	}

	TRACE("= %d\n", b);

	//--------------------------------------------------------------
/*
	m_mapCode[_T("01")]		= _T("A");
	m_mapCode[_T("1000")]	= _T("B");
	m_mapCode[_T("1010")]	= _T("C");
	m_mapCode[_T("100")]	= _T("D");
	m_mapCode[_T("0")]		= _T("E");
	m_mapCode[_T("0010")]	= _T("F");
	m_mapCode[_T("110")]	= _T("G");
	m_mapCode[_T("0000")]	= _T("H");
	m_mapCode[_T("00")]		= _T("I");
	m_mapCode[_T("0111")]	= _T("J");
	m_mapCode[_T("101")]	= _T("K");
	m_mapCode[_T("0100")]	= _T("L");
	m_mapCode[_T("11")]		= _T("M");
	m_mapCode[_T("10")]		= _T("N");
	m_mapCode[_T("111")]	= _T("O");
	m_mapCode[_T("0110")]	= _T("P");
	m_mapCode[_T("1101")]	= _T("Q");
	m_mapCode[_T("010")]	= _T("R");
	m_mapCode[_T("000")]	= _T("S");
	m_mapCode[_T("1")]		= _T("T");
	m_mapCode[_T("001")]	= _T("U");
	m_mapCode[_T("0001")]	= _T("V");
	m_mapCode[_T("011")]	= _T("W");
	m_mapCode[_T("1001")]	= _T("X");
	m_mapCode[_T("1011")]	= _T("Y");
	m_mapCode[_T("1100")]	= _T("Z");

	m_mapCode[_T("01111")]	= _T("1");
	m_mapCode[_T("00111")]	= _T("2");
	m_mapCode[_T("00011")]	= _T("3");
	m_mapCode[_T("00001")]	= _T("4");
	m_mapCode[_T("00000")]	= _T("5");
	m_mapCode[_T("10000")]	= _T("6");
	m_mapCode[_T("11000")]	= _T("7");
	m_mapCode[_T("11100")]	= _T("8");
	m_mapCode[_T("11110")]	= _T("9");
	m_mapCode[_T("11111")]	= _T("0");

	m_mapCode[_T("010101")]	= _T(".");
	m_mapCode[_T("101010")]	= _T(";");	// 分号
	m_mapCode[_T("111000")]	= _T(":");	// 冒号
	m_mapCode[_T("110011")]	= _T(",");	
	m_mapCode[_T("001100")]	= _T("?");
	m_mapCode[_T("10001")]	= _T("=");
	m_mapCode[_T("011110")]	= _T("\'");	// 单引
	m_mapCode[_T("10010")]	= _T("/");
	m_mapCode[_T("101011")]	= _T("!");
	m_mapCode[_T("100001")]	= _T("-");
	m_mapCode[_T("0011 01")]= _T("_");
	m_mapCode[_T("010010")]	= _T("\"");	// 双引
	m_mapCode[_T("10110")]	= _T("(");
	m_mapCode[_T("101101")]	= _T(")");
	m_mapCode[_T("0001001")]= _T("$");
	m_mapCode[_T("0 000")]	= _T("&");
	m_mapCode[_T("011010")]	= _T("@");
*/
	m_mapCode[_T(".-")]		= _T("A");
	m_mapCode[_T("-...")]	= _T("B");
	m_mapCode[_T("-.-.")]	= _T("C");
	m_mapCode[_T("-..")]	= _T("D");
	m_mapCode[_T(".")]		= _T("E");
	m_mapCode[_T("..-.")]	= _T("F");
	m_mapCode[_T("--.")]	= _T("G");
	m_mapCode[_T("....")]	= _T("H");
	m_mapCode[_T("..")]		= _T("I");
	m_mapCode[_T(".---")]	= _T("J");
	m_mapCode[_T("-.-")]	= _T("K");
	m_mapCode[_T(".-..")]	= _T("L");
	m_mapCode[_T("--")]		= _T("M");
	m_mapCode[_T("-.")]		= _T("N");
	m_mapCode[_T("---")]	= _T("O");
	m_mapCode[_T(".--.")]	= _T("P");
	m_mapCode[_T("--.-")]	= _T("Q");
	m_mapCode[_T(".-.")]	= _T("R");
	m_mapCode[_T("...")]	= _T("S");
	m_mapCode[_T("-")]		= _T("T");
	m_mapCode[_T("..-")]	= _T("U");
	m_mapCode[_T("...-")]	= _T("V");
	m_mapCode[_T(".--")]	= _T("W");
	m_mapCode[_T("-..-")]	= _T("X");
	m_mapCode[_T("-.--")]	= _T("Y");
	m_mapCode[_T("--..")]	= _T("Z");

	m_mapCode[_T(".----")]	= _T("1");
	m_mapCode[_T("..---")]	= _T("2");
	m_mapCode[_T("...--")]	= _T("3");
	m_mapCode[_T("....-")]	= _T("4");
	m_mapCode[_T(".....")]	= _T("5");
	m_mapCode[_T("-....")]	= _T("6");
	m_mapCode[_T("--...")]	= _T("7");
	m_mapCode[_T("---..")]	= _T("8");
	m_mapCode[_T("----.")]	= _T("9");
	m_mapCode[_T("-----")]	= _T("0");

	m_mapCode[_T(".-.-.-")]	= _T(".");
	m_mapCode[_T("-.-.-.")]	= _T(";");	// 分号
	m_mapCode[_T("---...")]	= _T(":");	// 冒号
	m_mapCode[_T("--..--")]	= _T(",");	
	m_mapCode[_T("..--..")]	= _T("?");
	m_mapCode[_T("-...-")]	= _T("=");
	m_mapCode[_T(".----.")]	= _T("\'");	// 单引
	m_mapCode[_T("-..-.")]	= _T("/");
	m_mapCode[_T("-.-.--")]	= _T("!");
	m_mapCode[_T("-....-")]	= _T("-");
	m_mapCode[_T("..--.-")] = _T("_");
	m_mapCode[_T(".-..-.")]	= _T("\"");	// 双引
	m_mapCode[_T("-.--.")]	= _T("(");
	m_mapCode[_T("-.--.-")]	= _T(")");
	m_mapCode[_T("...-..-")]= _T("$");
	m_mapCode[_T(". ...")]	= _T("&");
	m_mapCode[_T(".--.-.")]	= _T("@");

	m_mapCode[_T(".-.-.")]	= _T("AR");	// 停止，消息结束
	m_mapCode[_T(".-...")]  = _T("AS");	// 等待
	m_mapCode[_T("-.-")]	= _T("K");	// 邀请发射信号,一般跟随AR，表示“该你了”
	m_mapCode[_T("...-.-")]	= _T("SK");	// 终止，联络结束
	m_mapCode[_T("-...-")]	= _T("BT");	// 分隔符
	m_mapCode[_T("...-.")]	= _T("SN");	// 我将重新发送最后一个单词
	m_mapCode[_T(".. ..")]	= _T("II");	// 同样
	m_mapCode[_T("........")]= _T("HH");// 错误

	//------------------------------------------------------

	m_mapCode[_T("A")] = _T(".-");
	m_mapCode[_T("B")] = _T("-...");
	m_mapCode[_T("C")] = _T("-.-.");
	m_mapCode[_T("D")] = _T("-..");
	m_mapCode[_T("E")] = _T(".");
	m_mapCode[_T("F")] = _T("..-.");
	m_mapCode[_T("G")] = _T("--.");
	m_mapCode[_T("H")] = _T("....");
	m_mapCode[_T("I")] = _T("..");
	m_mapCode[_T("J")] = _T(".---");
	m_mapCode[_T("K")] = _T("-.-");
	m_mapCode[_T("L")] = _T(".-..");
	m_mapCode[_T("M")] = _T("--");
	m_mapCode[_T("N")] = _T("-.");
	m_mapCode[_T("O")] = _T("---");
	m_mapCode[_T("P")] = _T(".--.");
	m_mapCode[_T("Q")] = _T("--.-");
	m_mapCode[_T("R")] = _T(".-.");
	m_mapCode[_T("S")] = _T("...");
	m_mapCode[_T("T")] = _T("-");
	m_mapCode[_T("U")] = _T("..-");
	m_mapCode[_T("V")] = _T("...-");
	m_mapCode[_T("W")] = _T(".--");
	m_mapCode[_T("X")] = _T("-..-");
	m_mapCode[_T("Y")] = _T("-.--");
	m_mapCode[_T("Z")] = _T("--..");
				   
	m_mapCode[_T("1")]	= _T(".----");
	m_mapCode[_T("2")]	= _T("..---");
	m_mapCode[_T("3")]	= _T("...--");
	m_mapCode[_T("4")]	= _T("....-");
	m_mapCode[_T("5")]	= _T(".....");
	m_mapCode[_T("6")]	= _T("-....");
	m_mapCode[_T("7")]	= _T("--...");
	m_mapCode[_T("8")]	= _T("---..");
	m_mapCode[_T("9")]	= _T("----.");
	m_mapCode[_T("0")]	= _T("-----");
	
	//m_mapCode[_T(".")]	= _T(".-.-.-");
	m_mapCode[_T(";")]	= _T("-.-.-.");	// 分号
	m_mapCode[_T(":")]	= _T("---...");	// 冒号
	m_mapCode[_T(",")]	= _T("--..--");	
	m_mapCode[_T("?")]	= _T("..--..");
	m_mapCode[_T("=")]	= _T("-...- ");
	m_mapCode[_T("\'")]	= _T(".----.");	// 单引
	m_mapCode[_T("/")]	= _T("-..-.");
	m_mapCode[_T("!")]	= _T("-.-.--");
	//m_mapCode[_T("-")]	= _T("-....-");
	m_mapCode[_T("_")]  = _T("..--.-");
	m_mapCode[_T("\"")]	= _T(".-..-.");	// 双引
	m_mapCode[_T("(")]	= _T("-.--.");
	m_mapCode[_T(")")]	= _T("-.--.-");
	m_mapCode[_T("$")]	= _T("...-..-");
	m_mapCode[_T("&")]	= _T(". ...");
	m_mapCode[_T("@")]	= _T(".--.-.");

    return TRUE;
}


void CDlg_Compress::OnBnClickedBtnCompress()
{
    // 因为压缩函数的输出缓冲必须比输入大0.1% + 12 然后一个DWORD用来保存压缩前的大小
    // int compress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);

    CString strFileName;
    CString strCompress;
    GetDlgItem(IDC_COMPRESS_EDIT_FILENAME)->GetWindowText(strFileName);
    GetDlgItem(IDC_COMPRESS_EDIT_CONTENT)->GetWindowText(strCompress);

    int inLen = strCompress.GetLength();
    unsigned char *out = new unsigned char[inLen*2];
    unsigned long outLen = inLen*2;

    int ret = compress(out, &outLen, (LPBYTE)(LPCSTR)strCompress, inLen);
    if (0 == ret)
    {
        CFile File;
        if (File.Open(strFileName, CFile::modeCreate | CFile::modeReadWrite))
        {
            File.Write(out, outLen);
            File.Close();
        }
        MessageBox("Compress OK!");
    }
    else
    {
        strCompress.Format("Error:%s", zError(ret));
        MessageBox(strCompress);
    }

    delete[] out; 
}

void CDlg_Compress::OnBnClickedBtnUncompress()
{
	CString strCompress;
    CString strFileName;
    GetDlgItem(IDC_COMPRESS_EDIT_FILENAME)->GetWindowText(strFileName);

    CFile File;
    if (File.Open(strFileName, CFile::modeRead))
    {
        ULONG inLen = File.GetLength();
		unsigned char *in = new unsigned char[inLen];
        File.Read(in, inLen);
		File.Close();

        unsigned long outLen = 1000 * inLen;
        unsigned char *out = new BYTE[outLen];

        int ret = uncompress(out, &outLen, in, inLen);
        if (0 == ret)
        {
            out[outLen] = 0;
            GetDlgItem(IDC_COMPRESS_EDIT_CONTENT)->SetWindowText((LPCTSTR)out);
            MessageBox("Uncompress OK!");
        }
        else
        {
            strCompress.Format("Error:%s\n", zError(ret));
            TRACE(strCompress);
            MessageBox("Uncompress don't OK!");
        }

		delete[] in;
        delete[] out;
    }
}

void CDlg_Compress::OnBnClickedCompressBtnMors()
{
	CString strMore;
	CString strKey;
	CString strCode;
	CString strText;

	GetDlgItem(IDC_COMPRESS_EDIT_CONTENT)->GetWindowText(strText);

	int nLen = strText.GetLength();

	for (int i = 0; i < nLen; i++)
	{
		strKey.Format(_T("%c"), strText[i]);
		strKey.MakeUpper();

		if (m_mapCode.Lookup(strKey, strCode))
		{
			strMore.AppendFormat(_T("%c=%s\n"), strText[i], strCode);
		}
		else
		{
			strMore.AppendFormat(_T("%c=不知道\n"), strText[i]);
		}
	}

	MessageBox(strMore);
}

void CDlg_Compress::OnBnClickedCompressBtnUnmors()
{
	CString strMore;
	CString strKey;
	CString strCode;
	CString strText;

	GetDlgItem(IDC_COMPRESS_EDIT_CONTENT)->GetWindowText(strMore);
	
	int i = 0;

	while (true)
	{
		strKey = strMore.Tokenize(" ", i);

		if (_T("") == strKey) break;

		if (m_mapCode.Lookup(strKey, strCode))
		{
			strText.AppendFormat(_T("%s\t=%s\n"), strKey, strCode);
		}
		else
		{
			strText.AppendFormat(_T("%s\t=不知道\n"), strKey);
		}
	}

	MessageBox(strText);
}

void CDlg_Compress::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	this->Down();

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDlg_Compress::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->Down();

	CDialog::OnLButtonDown(nFlags, point);
}

void CDlg_Compress::Down(void)
{
	m_bDown = TRUE;

	m_dwTimeDown = ::GetTickCount();

	if (_T("") != m_strCode)
	{
		if ((m_dwTimeDown - m_dwTimeUp) >= 3*m_dwTimeD)
		{
			CString strCode;
			if (m_mapCode.Lookup(m_strCode, strCode))
			{
				if (m_nLen < 4)
					TRACE("\t\t>\t%s\n", strCode);
				else
					TRACE("\t>\t%s\n", strCode);
			}
			else
			{
				if (m_nLen < 4)
					TRACE("\t\t>\tError\n");
				else
					TRACE("\t>\tError\n");
			}

			m_strCode = _T("");
			m_nLen = 0;
		}
	}
}

void CDlg_Compress::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		m_bDown = FALSE;

		m_dwTimeUp = ::GetTickCount();

		// 划一般是三个点的长度
		// 点划之间的间隔是一个点的长度
		// 字元之间的间隔是三个点的长度
		// 单词之间的间隔是七个点的长度

		if ((m_dwTimeUp - m_dwTimeDown) <= m_dwTimeD)	
		{
			//m_strCode += _T("0");
			//TRACE("0");
			m_strCode += _T(".");
			TRACE(".");
		}
		else
		{
			//m_strCode += _T("1");
			//TRACE("1");
			m_strCode += _T("-");
			TRACE("-");
		}

		m_nLen++;
	}

	CDialog::OnLButtonUp(nFlags, point);
}