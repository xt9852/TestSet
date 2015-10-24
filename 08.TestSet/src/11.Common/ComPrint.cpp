#include "stdafx.h"
#include "ComPrint.h"


CComPrint::CComPrint()
	:m_hCom(NULL),
	m_bPortReady(FALSE),
	m_bWriteRC(FALSE),
	m_bReadRC(FALSE),
	m_dwBytesWritten(0),
	m_dwBytesRead(0)
{
	memset(&m_dcb, 0, sizeof(m_dcb));
	memset(&m_CommTimeouts, 0, sizeof(m_CommTimeouts));
}

CComPrint::~CComPrint()
{
	CloseHandle(m_hCom);
}

int CComPrint::OpenCOM(int nCmdNum)
{
	m_sComPort.Format(_T("COM%d"), nCmdNum);

	m_hCom = CreateFile(m_sComPort, 
		GENERIC_READ | GENERIC_WRITE,
		0,				// exclusive access
		NULL,			// no security
		OPEN_EXISTING,
		0,				// no overlapped I/O
		NULL);			// null template

	if (NULL != m_hCom)
	{
		m_bPortReady		= SetupComm(m_hCom, 128, 128);
		m_bPortReady		= GetCommState(m_hCom, &m_dcb);

		m_dcb.BaudRate		= 9600;
		m_dcb.ByteSize		= 8;
		m_dcb.Parity		= NOPARITY;
		m_dcb.StopBits		= ONESTOPBIT;
		m_dcb.fAbortOnError = TRUE;
		m_dcb.fBinary		= TRUE;

		m_bPortReady		= SetCommState(m_hCom, &m_dcb);
		m_bPortReady		= GetCommTimeouts (m_hCom, &m_CommTimeouts);

		m_CommTimeouts.ReadIntervalTimeout			= 50;
		m_CommTimeouts.ReadTotalTimeoutConstant		= 50;
		m_CommTimeouts.ReadTotalTimeoutMultiplier	= 10;
		m_CommTimeouts.WriteTotalTimeoutConstant	= 50;
		m_CommTimeouts.WriteTotalTimeoutMultiplier	= 10;

		m_bPortReady		= SetCommTimeouts (m_hCom, &m_CommTimeouts);

		return 0;
	}
	return -1;
}

void CComPrint::CloseCOM()
{
	CloseHandle(m_hCom);
	m_hCom = NULL;
}



// 选择字符集命令
// 27,54,		使用字符集1的字符进行打印，字符集1中有字符224个,代码范围20H-FFH（32-255）包括ASCII字符，及各种图形符号等
// 27,55,		使用字符集2的字符进行打印，字符集2中有字符224个,代码范围20H-FFH（32-255）包括德，法，俄，日语片假名等
// 28,38,		进入汉字方式,代码范围20H-7FH（32-127）

// 进纸命令
// 10,			打印缓冲区内容,打印机向前走纸一个字符行
// 27,74,n		打印机向前n行, n 在 1 - 255 之间

// 格式设置命令
// 27,49,n		为后面的换行命令设置n点行间距(点为以对值，不受放大或缩小命令影响), n 在 1 - 255 之间
// 27,112,n		设置字符之间的间距为n点, n 在 0 - 255 之间
// 27,66, n1,n2...0,输入垂直表音隔间隔值n1,n2,最多可输入8个间隔值
// 11			打印上一命令的下一垂直造表位
// 27,68, n1,n2...0,输入水平表音隔间隔值n1,n2,最多可输入8个间隔值
// 9			打印上一命令的下一水平造表位
// 27,102,m,n	如果m=0,将打印n个空格,如果m=1,,将打印n个空行, n 在 1 - 255 之间
// 27,81,		设置右限,右侧不侧不打印的字符数
// 27,108,		设置左限,左侧不侧不打印的字符数
// 27,109,n		灰度打印,n取1~6,1颜色最浅,6最深,默认值为1

// 字符设置命令
// 27,85,n		横向放大,n取1~8,16点阵打印机为n=2,24点阵n=1
// 27,86,n		纵向放大,n取1~8,16点阵打印机为n=2,24点阵n=1
// 27,87,n		横纵向放大,n取1~8,16点阵打印机为n=2,24点阵n=1
// 27,45,n		n=1允许下划线打印,n=0不允许下划线打印
// 27,43,n		n=1允许上划线打印,n=0不允许上划线打印
// 27,105,n		n=1允许反白打印,n=0不允许反打印
// 27,99,n		n=1正向打印,n=0反向打印
// 28,73,n		旋转6*8字符,n=0为0度,,n=1为90度,n=2为180度,n=3为270度

// 用户定义字符设置命令
// 27,38,m,n1,n2,...,ni, 用户自定义字符,m为该用户自定义字符码取(32~61)
// 27,37,m,n1,n2,...,ni, 替换用户自定义字符,m为该用户自定义字符码取(32~61)
// 27,58,m,		恢复字符集中的字符

// 图形打印命令
// 27,75,ml,mh,n1,n2,...,ni 宽mh*256+ml

// 初使化命令
// 27,64		初始化打印机
// 13			对缓冲区内的命令和字符进行处理
// 27,100,n n=0打印机不工作,n=1打印机工作
// 28,118		向主机传送打印机是否处于缺纸状态,00为正常,04缺纸

// 条型码打印
// 29,87,n1,n2    n1为条码窄条尺寸,默认n1=3,n2为条码宽条尺寸
// 29,107,n,[d],0 n选择打印条码系统,n=2为EAN-13,n=3为EAN-8,[d]为打印的条码字符
// 29,72,n        n=0不打印HRI字符,默认n=0,n=1为打印HRI
// 29,104,n       设置条码高,n取0~255,n=0为256点
// 29,119,n       设置条码宽,n取0~4,默认n=3, n=1,窄条宽1,宽条宽3, n=2,窄条宽2,宽条宽3, n=3,窄条宽3,宽条宽7, n=4,窄条宽4,宽条宽9


// 正向打印
void CComPrint::Print(CString csText)
{
	char szCmd[3];
	memset(szCmd,'\0',3);
	szCmd[0] = 27;
	szCmd[1] = 99;
	szCmd[2] = 1; //0,反向打印  1,正向打印

	PurgeComm(m_hCom, PURGE_RXCLEAR|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_TXABORT);

	WriteFile(m_hCom, szCmd, 3, &m_dwBytesWritten, NULL);

	WriteFile(m_hCom, csText.GetString(), (DWORD)csText.GetLength(), &m_dwBytesWritten, NULL);
}


void CComPrint::WinPrint(CString csText)
{
	char szPrinter[200] = "";
	char *pszDevice = NULL;
	char *pszDriver = NULL;
	char *pszOutput = NULL;

	HDC hdcPrint = NULL; // 定义一个设备环境句柄

	static DOCINFO di={sizeof(DOCINFO),"printer",NULL};

	// 得到设备字符串存入数组szPrinter中
	GetProfileString("windows","device",",,,",szPrinter,80); 

	// 将设备字符串分解
	if( (NULL != (pszDevice = strtok(szPrinter,","))) && 
		(NULL != (pszDriver = strtok(NULL,","))) &&
		(NULL != (pszOutput = strtok(NULL,","))))
	{
		// 创建一个打印机设备句柄
		if((hdcPrint = CreateDC(pszDriver,pszDevice, pszOutput, NULL)) != 0)
		{ 
			if (StartDoc(hdcPrint, &di) > 0)	//开始执行一个打印作业 
			{ 
				StartPage(hdcPrint);			//打印机走纸,开始打印 
				SaveDC(hdcPrint);				//保存打印机设备句柄

				// 输出文字
				CRect rcText(0,0,0,0);
				::DrawText(hdcPrint, csText, csText.GetLength(), &rcText, DT_CALCRECT);	// 计算大小
				::DrawText(hdcPrint, csText, csText.GetLength(), &rcText, DT_WORDBREAK);

				RestoreDC(hdcPrint,-1);			//恢复打印机设备句柄 
				EndPage(hdcPrint);				//打印机停纸,停止打印 
				EndDoc(hdcPrint);				//结束一个打印作业 
			} 

			// 用API函数DeleteDC销毁一个打印机设备句柄 
			DeleteDC(hdcPrint);
		}
	}
}

void CComPrint::PrintBmp(UINT nBmpId)
{
	char szPrinter[200] = "";
	char *pszDevice = NULL;
	char *pszDriver = NULL;
	char *pszOutput = NULL;

	HDC hdcPrint = NULL; // 定义一个设备环境句柄

	static DOCINFO di={sizeof(DOCINFO),"printer",NULL};

	// 得到设备字符串存入数组szPrinter中
	GetProfileString("windows","device",",,,",szPrinter,80); 

	// 将设备字符串分解
	if( (NULL != (pszDevice = strtok(szPrinter,","))) && 
		(NULL != (pszDriver = strtok(NULL,","))) &&
		(NULL != (pszOutput = strtok(NULL,","))))
	{
		// 创建一个打印机设备句柄
		if((hdcPrint = CreateDC(pszDriver,pszDevice, pszOutput, NULL)) != 0)
		{ 
			if (StartDoc(hdcPrint, &di) > 0)	//开始执行一个打印作业 
			{ 
				StartPage(hdcPrint);			//打印机走纸,开始打印 
				SaveDC(hdcPrint);				//保存打印机设备句柄

				#pragma warning(disable:4312)

				// 输出图片
				HBITMAP hBitmap=::LoadBitmap(AfxGetInstanceHandle(),(LPCTSTR)nBmpId);
				BITMAP bitmap;
				::GetObject(hBitmap,sizeof(BITMAP),&bitmap);

				#pragma warning(default:4312)

				HDC dcMem;
				dcMem=::CreateCompatibleDC(hdcPrint);
				HBITMAP hOldBmp=(HBITMAP)::SelectObject(dcMem,hBitmap);

				int nVertCenterPos = ::GetDeviceCaps(hdcPrint, VERTRES) / 2;
				::StretchBlt(hdcPrint,1,50,400,bitmap.bmHeight,dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);

				::SelectObject(dcMem,hOldBmp);
				::DeleteDC(dcMem);
				::DeleteObject(hBitmap);

				RestoreDC(hdcPrint,-1); //恢复打印机设备句柄 
				EndPage(hdcPrint); //打印机停纸,停止打印 
				EndDoc(hdcPrint); //结束一个打印作业 
			} 

			// 用API函数DeleteDC销毁一个打印机设备句柄 
			DeleteDC(hdcPrint);
		}
	}
}

