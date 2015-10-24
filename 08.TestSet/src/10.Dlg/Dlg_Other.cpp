// Dlg\Dlg_Other.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg/Dlg_Other.h"
#include "Base/XTXml.h"
#include "Common/ComPrint.h"
#include "Common/WebInvoke.h"


IMPLEMENT_DYNAMIC(CDlg_Other, CDialog)
	CDlg_Other::CDlg_Other(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Other::IDD, pParent),
	m_nHotKeyID(0),
	m_hInWrite(NULL),
	m_hInRead(NULL),
	m_hOutRead(NULL),
	m_hOutWrite(NULL)
{
}

CDlg_Other::~CDlg_Other()
{
	UnregisterHotKey(GetSafeHwnd(), m_nHotKeyID);
}

void CDlg_Other::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_Other, CDialog)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_BN_CLICKED(IDC_OTHER_BTN_OPEN,	OnBnClickedOtherBtnOpen)
	ON_BN_CLICKED(IDC_OTHER_BTN_OSBIT,	OnBnClickedOtherBtnOSbit)
	ON_BN_CLICKED(IDC_OTHER_BTN_DISK,	OnBnClickedOtherBtnDisk)
	ON_BN_CLICKED(IDC_OTHER_BTN_CP,		OnBnClickedOtherBtnCp)
	ON_BN_CLICKED(IDC_OTHER_BTN_DMP,	OnBnClickedOtherBtnDmp)
	ON_BN_CLICKED(IDC_OTHER_BTN_ASM,	OnBnClickedOtherBtnAsm)
	ON_BN_CLICKED(IDC_OTHER_BTN_ASM_C,	OnBnClickedOtherBtnAsmC)
	ON_BN_CLICKED(IDC_OTHER_BTN_PRINT,	OnBnClickedOtherBtnPrint)
	ON_BN_CLICKED(IDC_OTHER_BTN_COMPILE,OnBnClickedOtherBtnCompile)
	ON_BN_CLICKED(IDC_OTHER_BTN_LOADDLL,OnBnClickedOtherBtnLoaddll)
	ON_BN_CLICKED(IDC_OTHER_BTN_GUID,	OnBnClickedOtherBtnGuid)
	ON_BN_CLICKED(IDC_OTHER_BTN_DESKTOP,OnBnClickedOtherBtnDesktop)
	ON_BN_CLICKED(IDC_OTHER_BTN_PROCESS,OnBnClickedOtherBtnProcess)
	ON_BN_CLICKED(IDC_OTHER_BTN_HOTKEY, OnBnClickedOtherBtnHotkey)
	ON_BN_CLICKED(IDC_OTHER_BTN_VFUNC,	OnBnClickedOtherBtnVfunc)
	ON_BN_CLICKED(IDC_OTHER_BTN_PIPE,   OnBnClickedOtherBtnPipe)
	ON_BN_CLICKED(IDC_OTHER_BTN_PIPE2,  OnBnClickedOtherBtnPipe2)
    ON_BN_CLICKED(IDC_OTHER_BTN_SCRIPT, &CDlg_Other::OnBnClickedOtherBtnScript)
    ON_BN_CLICKED(IDC_OTHER_BTN_NTFS, &CDlg_Other::OnBnClickedOtherBtnNtfs)
    ON_WM_RBUTTONDOWN()
    ON_BN_CLICKED(IDC_OTHER_BTN_BSDIFF, &CDlg_Other::OnBnClickedOtherBtnBsdiff)
    ON_BN_CLICKED(IDC_OTHER_BTN_LUA, &CDlg_Other::OnBnClickedOtherBtnLua)
END_MESSAGE_MAP()

#include "tlhelp32.h"

// 关闭解码驱动程序
BOOL KillProcessFromName(LPCSTR lpProcessName)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(hSnapShot,&pe))
	{
		return FALSE;
	}

	while (Process32Next(hSnapShot,&pe))
	{
		CString scTmp = pe.szExeFile;
		if(lpProcessName == scTmp)
		{
			DWORD dwProcessID = pe.th32ProcessID;
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);
			TerminateProcess(hProcess,0);
			CloseHandle(hProcess);
			return TRUE;
		}
		scTmp.ReleaseBuffer();
	}

	return FALSE;
}

BOOL CDlg_Other::OnInitDialog()
{
    GetDlgItem(IDC_OTHER_EDIT)->SetWindowText(_T("DCMainWin_old.txt DCMainWin_new.txt patch"));

	return TRUE;
}

LONG CDlg_Other::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	MessageBox("你按下了组合键:Ctrl+Alt+Shift+F1");
	return 0;
}

// 计算机二进制中1的个数,x-1这个是关键
int CDlg_Other::func(int x)
{
	int countx = 0;
	while(x)
	{
		countx++;
		x = x&(x-1);
	}
	return countx;
}

/*
 *\fn         void SetTransparent(BYTE byTrans)
 *\brief      设置窗体透明度
 *\param[in]  BYTE byTrans 透明度(0-255)
 *\return     void 无
 */
void CDlg_Other::SetTransparent(BYTE byTrans)
{
    LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
    SetWindowLong(m_hWnd, GWL_EXSTYLE, lStyle | 0x80000);

    HINSTANCE hInst = ::LoadLibrary(_T("User32.dll"));
    if (NULL != hInst)
    {
        typedef BOOL(WINAPI *TransFunc)(HWND, COLORREF, BYTE, DWORD);

        TransFunc trans_fun = NULL;
        trans_fun =(TransFunc)::GetProcAddress(hInst, _T("SetLayeredWindowAttributes"));
        if (trans_fun)
        {
            trans_fun(this->GetSafeHwnd(), 0, byTrans, 2);
        }

        FreeLibrary(hInst);
    }
}

void CDlg_Other::OnBnClickedOtherBtnOpen()
{
    int a = func(9999);

    CFileStatus fileStatus={0};

    CFile::GetStatus("TestSet.exe", fileStatus);

    INT64 nTime = fileStatus.m_mtime.GetTime();
}

class Test
{
    int a;
    static int b;
};

// 先指向地址0处,字段就是所在的位置
#define FPOS(type, field) ((DWORD) &((type *)0)->field)

void CDlg_Other::OnBnClickedOtherBtnOSbit()
{
	//------------------------------------------------------------
	// 不用第三方参数的情况下，交换两个参数的值

	int nNum1 = 4;
	int nNum2 = 3;

	nNum1 ^= nNum2;
	nNum2 ^= nNum1;
	nNum1 ^= nNum2;

	nNum1 += nNum2;
	nNum2 = nNum1 - nNum2;
	nNum1 -= nNum2;

	struct Struct1
	{
		double d1;
		char c1;
		int i1;
	};

	int a = sizeof(Struct1); //16

	struct Struct2
	{
		double d1;
		int i1;
		char c1;
	};

	a = sizeof(Struct2); //16

	struct Struct3
	{
		double d1;
		char c1;
		double d2;
		char c2;
	};

	a = sizeof(Struct3); //32

#pragma pack(push) // 保存对齐状态
#pragma pack(4) // 设定为4字节对齐

	struct Struct4
	{
		double d1;
		char c1;
		double d2;
		char c2;
	};

#pragma pack(pop) // 恢复对齐状态

	a = sizeof(Struct4); //24

#pragma pack(push) // 保存对齐状态
	//#pragma pack(1) // 设定为1字节

	struct Struct5
	{
		char t:2;
		char k:2;
		unsigned short i:2;
		unsigned short j:2;
		char l:2;
		unsigned long m;
	};

#pragma pack(pop) // 恢复对齐状态


	a = sizeof(Struct5);//12

	// 结构或者类中的静态成员不对结构或者类的大小产生影响，静态变量的存储位置与结构或者类的实例地址无关
    a = sizeof(Test); //4,class Test{int a; static int b;};

	class Test1 { };

	a = sizeof(Test1); //1,,系统默认，必须保证结构或类的每一个实例在内存中都有唯一的地址

	//-------------------------------------------------------------

	DWORD dwPos = FPOS(Struct4, c1);
	CString strText;
	strText.Format("c1位于结构体Struct4的%d", dwPos);
	MessageBox(strText);

	//-------------------------------------------------------------
	char c1='a';
	char c2='b';

	const char *p1; // 指向const的指针
	p1 = &c1;
	p1 = &c2;
	//*p1 = c1; //error
	//*p1 = 'c'; //error

	char const *p2; // 指向const的指针
	p2 = &c1;
	p2 = &c2;
	//*p2 = 'c'; //error
	//*p2 = c1; //error

	char * const p3 = &c2; // const 指针
	*p3 = 'd';
	*p3 = c1;
	//p3 = &c1; //error

	const char * const p4 = &c1;
	//p4 = &c2; //error
	//*p4 = 'e'; //error
}

//-------------------------------------------------------------------------------------------
//int E_API E_Disk_GetPartitionType(IN const char *pchar_param_DriveName)
//typedef int (*lpFun)(const char *pchar_param_DriveName);

//unsigned long E_Disk_GetDiskNumberByFilePath(IN const char *pchar_param_FilePath)

typedef long (*lpFun1)(const char *pchar_param_FilePath);

/*
bool E_API E_Disk_ReadData(IN unsigned long ulong_param_DiskNum,
IN const char *pchar_param_DriverName,
IN void *pvoid_param_DataBuffer,
IN unsigned long ulong_param_DataLength,
IN LONGLONG llg_param_ByteOffset)
*/

typedef bool (*lpFun2)(unsigned long ulong_param_DiskNum,
	const char *pchar_param_DriverName,
	void *pvoid_param_DataBuffer,
	unsigned long ulong_param_DataLength,
	LONGLONG llg_param_ByteOffset);
/*

主引导扇区

33 c0 8e d0 bc 00 7c fb 50 07 50 1f fc be 1b 7c
bf 1b 06 50 57 b9 e5 01 f3 a4 cb bd be 07 b1 04
38 6e 00 7c 09 75 13 83 c5 10 e2 f4 cd 18 8b f5
83 c6 10 49 74 19 38 2c 74 f6 a0 b5 07 b4 07 8b
f0 ac 3c 00 74 fc bb 07 00 b4 0e cd 10 eb f2 88
4e 10 e8 46 00 73 2a fe 46 10 80 7e 04 0b 74 0b
80 7e 04 0c 74 05 a0 b6 07 75 d2 80 46 02 06 83
46 08 06 83 56 0a 00 e8 21 00 73 05 a0 b6 07 eb
bc 81 3e fe 7d 55 aa 74 0b 80 7e 10 00 74 c8 a0
b7 07 eb a9 8b fc 1e 57 8b f5 cb bf 05 00 8a 56
00 b4 08 cd 13 72 23 8a c1 24 3f 98 8a de 8a fc
43 f7 e3 8b d1 86 d6 b1 06 d2 ee 42 f7 e2 39 56
0a 77 23 72 05 39 46 08 73 1c b8 01 02 bb 00 7c
8b 4e 02 8b 56 00 cd 13 73 51 4f 74 4e 32 e4 8a
56 00 cd 13 eb e4 8a 56 00 60 bb aa 55 b4 41 cd
13 72 36 81 fb 55 aa 75 30 f6 c1 01 74 2b 61 60
6a 00 6a 00 ff 76 0a ff 76 08 6a 00 68 00 7c 6a
01 6a 10 b4 42 8b f4 cd 13 61 61 73 0e 4f 74 0b
32 e4 8a 56 00 cd 13 eb d6 61 f9 c3 49 6e 76 61
6c 69 64 20 70 61 72 74 69 74 69 6f 6e 20 74 61
62 6c 65 00 45 72 72 6f 72 20 6c 6f 61 64 69 6e
67 20 6f 70 65 72 61 74 69 6e 67 20 73 79 73 74
65 6d 00 4d 69 73 73 69 6e 67 20 6f 70 65 72 61
74 69 6e 67 20 73 79 73 74 65 6d 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 2c 44 63 80 00 00 00 00 00 80 01
01 00 07 fe ff ff 3f 00 00 00 74 3c 0d 03 00 00
c1 ff 0f fe ff ff b3 3c 0d 03 4d bc eb 0a 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 55 aa

//------------------------------------------------
第1部分(80) 分区标记 00 --> 非活动分区
80 --> 活动分区
82 --> Linux Native分区
83 --> Linux Swap 分区

第2部分(01 01 00) 分区开始位置:扇区号(后6bit),磁道号,柱面号(8bit + 扇区号前2bit = 10bit)

第3部分(07) 分区类型 04 --> DOS FAT16<32M
05 --> EXTEND
06 --> DOS FAT16>32M
07 --> NTFS(OS/2)
0f --> 扩展分区
83 --> LINUX>64M

第4部分(fe ff ff) 分区结束位置:扇区号(后6bit),磁道号,柱面号(8bit + 扇区号前2bit = 10bit)

第5部分(3f 00 00 00) 该分区起始逻辑扇区

第6部分(74 3c 0d 03) 该分区占用的总扇区数


//------------------------------------------------
系统引导扇区

eb 52 90 4e 54 46 53 20 20 20 20 00 02 08 00 00
00 00 00 00 00 f8 00 00 3f 00 ff 00 3f 00 00 00
00 00 00 00 80 00 80 00 73 3c 0d 03 00 00 00 00
00 00 0c 00 00 00 00 00 c7 d3 30 00 00 00 00 00
f6 00 00 00 01 00 00 00 96 36 70 3c 53 70 3c d0
00 00 00 00 fa 33 c0 8e d0 bc 00 7c fb b8 c0 07
8e d8 e8 16 00 b8 00 0d 8e c0 33 db c6 06 0e 00
10 e8 53 00 68 00 0d 68 6a 02 cb 8a 16 24 00 b4
08 cd 13 73 05 b9 ff ff 8a f1 66 0f b6 c6 40 66
0f b6 d1 80 e2 3f f7 e2 86 cd c0 ed 06 41 66 0f
b7 c9 66 f7 e1 66 a3 20 00 c3 b4 41 bb aa 55 8a
16 24 00 cd 13 72 0f 81 fb 55 aa 75 09 f6 c1 01
74 04 fe 06 14 00 c3 66 60 1e 06 66 a1 10 00 66
03 06 1c 00 66 3b 06 20 00 0f 82 3a 00 1e 66 6a
00 66 50 06 53 66 68 10 00 01 00 80 3e 14 00 00
0f 85 0c 00 e8 b3 ff 80 3e 14 00 00 0f 84 61 00
b4 42 8a 16 24 00 16 1f 8b f4 cd 13 66 58 5b 07
66 58 66 58 1f eb 2d 66 33 d2 66 0f b7 0e 18 00
66 f7 f1 fe c2 8a ca 66 8b d0 66 c1 ea 10 f7 36
1a 00 86 d6 8a 16 24 00 8a e8 c0 e4 06 0a cc b8
01 02 cd 13 0f 82 19 00 8c c0 05 20 00 8e c0 66
ff 06 10 00 ff 0e 0e 00 0f 85 6f ff 07 1f 66 61
c3 a0 f8 01 e8 09 00 a0 fb 01 e8 03 00 fb eb fe
b4 01 8b f0 ac 3c 00 74 09 b4 0e bb 07 00 cd 10
eb f2 c3 0d 0a 41 20 64 69 73 6b 20 72 65 61 64
20 65 72 72 6f 72 20 6f 63 63 75 72 72 65 64 00
0d 0a 4e 54 4c 44 52 20 69 73 20 6d 69 73 73 69
6e 67 00 0d 0a 4e 54 4c 44 52 20 69 73 20 63 6f
6d 70 72 65 73 73 65 64 00 0d 0a 50 72 65 73 73
20 43 74 72 6c 2b 41 6c 74 2b 44 65 6c 20 74 6f
20 72 65 73 74 61 72 74 0d 0a 00 00 00 00 00 00
00 00 00 00 00 00 00 00 83 a0 b3 c9 00 00 55 aa

//------------------------------------------------
第1部分(00 02) 每个扇区的字节数
第2部分(08) 每个簇的扇区数,两者相乘不能超过32K(簇最大大小)
第3部分(00 00) 保留扇区数
第4部分(00) FAT数据结构的数
第3部分(00 00) 目录项的数
第3部分(00 00) FAT16:扇区总数
第4部分(f8) 介质类型
第3部分(00 00) FAT结构占有的扇区数
第3部分(3f 00) 每个磁道的扇区数
第3部分(ff 00) 每个柱面的磁头数
第3部分(3f 00 00 00) 隐藏扇区数
第3部分(00 00 00 00) FAT32:所有扇区数
第3部分(80 00 80 00) FAT的大小
第3部分(73 3c) 标志
第3部分(0d 03) 文件系统的版本 NTFS:扇区总数低32位
第3部分(00 00 00 00) 根目录的起始簇号 NTFS:扇区总数高32位
第3部分(00 00 0c 00) 主文件表(MFT: Master File Table)的逻辑簇号低32位
第3部分(00 00 00 00) 主文件表(MFT: Master File Table)的逻辑簇号高32位
第3部分(c7 d3 30 00) 主文件表镜像（备份）的逻辑簇号低32位
第3部分(00 00 00 00) 主文件表镜像（备份）的逻辑簇号高32位
第3部分(f6) 每文件记录段的簇数（必须为2的幂，负数表示位移量）
第3部分(00 00 00) 保留对齐字节
第3部分(01) 缺省的每索引分配缓冲的簇数（必须为2的幂，负数表示位移）
第3部分(00 00 00) 保留对齐字节
第3部分(96 36 70 3c) 卷序列号低32位
第3部分(53 70 3c d0) 卷序列号高32位
第3部分(00 00 00 00) 校验和

*/


#include <windows.h>
#include <winioctl.h>

BOOL GetDriveGeometry(DISK_GEOMETRY *pdg)
{
	HANDLE hDevice; // handle to the drive to be examined
	BOOL bResult; // results flag
	DWORD junk; // discard results

	hDevice = CreateFile("\\\\.\\PhysicalDrive0", // drive to open
		0, // no access to the drive
		FILE_SHARE_READ | // share mode
		FILE_SHARE_WRITE,
		NULL, // default security attributes
		OPEN_EXISTING, // disposition
		0, // file attributes
		NULL); // do not copy file attributes

	if (hDevice == INVALID_HANDLE_VALUE) // cannot open the drive
	{
		return (FALSE);
	}

	bResult = DeviceIoControl(hDevice, // device to be queried
		IOCTL_DISK_GET_DRIVE_GEOMETRY, // operation to perform
		NULL, 0, // no input buffer
		pdg, sizeof(*pdg), // output buffer
		&junk, // # bytes returned
		(LPOVERLAPPED) NULL); // synchronous I/O

	CloseHandle(hDevice);

	return (bResult);
}

void CDlg_Other::OnBnClickedOtherBtnDisk()
{
	DISK_GEOMETRY pdg; // disk drive geometry structure
	BOOL bResult; // generic results flag
	ULONGLONG DiskSize; // size of the drive, in bytes

	bResult = GetDriveGeometry (&pdg);

	if (bResult)
	{
		TRACE("Cylinders = %I64d\n", pdg.Cylinders);
		TRACE("Tracks per cylinder = %ld\n", (ULONG) pdg.TracksPerCylinder);
		TRACE("Sectors per track = %ld\n", (ULONG) pdg.SectorsPerTrack);
		TRACE("Bytes per sector = %ld\n", (ULONG) pdg.BytesPerSector);

		DiskSize = pdg.Cylinders.QuadPart * (ULONG)pdg.TracksPerCylinder *
			(ULONG)pdg.SectorsPerTrack * (ULONG)pdg.BytesPerSector;
		TRACE("Disk size = %I64d (Bytes) = %I64d (Mb)\n", DiskSize,
			DiskSize / (1024 * 1024));
	}
	else
	{
		TRACE("GetDriveGeometry failed. Error %ld.\n", GetLastError());
	}

	char szData[1024*10] = {""};
	long lDiskNum = 0;
	long lBegin = 32256;
	long lLength = 1024;

	CString strFileName;
	strFileName.Format(_T("DiskData_%d_%d.dat"), lBegin, lLength);

	HINSTANCE hDll = LoadLibrary(_T("WinAPIExV.dll"));
	if (NULL != hDll)
	{
		lpFun1 Fun1 = (lpFun1)GetProcAddress(hDll, "E_Disk_GetDiskNumberByFilePath");
		if (NULL != Fun1)
		{
			lDiskNum = Fun1("C:\\");

			lpFun2 Fun2 = (lpFun2)GetProcAddress(hDll, "E_Disk_ReadData");
			if (NULL != Fun2)
			{
				bool nRet = Fun2(lDiskNum, NULL, (void*)szData, lLength, lBegin);

				if (nRet)
				{
					CFile file;
					if (file.Open(strFileName, CFile::modeCreate | CFile::modeReadWrite))
					{
						file.Write(szData, 1024);
						file.Close();
					}
				}
			}
		}

		::FreeLibrary(hDll);
	}
	else
	{
		LOG(ERROR) << "调用WinAPIExV.dll出错！";
	}
}

// 连接点
void CDlg_Other::OnBnClickedOtherBtnCp()
{
	CWebInvoke IEWeb;

	DWORD dwRet = IEWeb.OpenUrl("down.e-jjj.com", "", -1);
	CString strMsg;
	strMsg.Format(_T("%d"), dwRet);
	AfxMessageBox(strMsg);
}

void CDlg_Other::OnBnClickedOtherBtnDmp()
{
	char *a = new char[2];
	memset(a, 'a ', 2048); // 特意做的缓冲区溢出，记录DUMP数据
	printf("%s", a);
}

void FastMemcpy(char * Dest, char * Src, unsigned int Len)
{
	__asm
	{
		mov esi, Src;
		mov edi, Dest;
		mov eax, Len;

		mov edx, 0; // eax = len / 64, edx = len % 64
		mov ecx, 64;
		div ecx;

		push edx; // remain

		cmp eax, 0;
		je copy;

		mov ebx, 8;
		mul ebx; // ecx = eax * 64

		mov ecx, eax;

		lea esi, [esi+ecx*8]; // to end 64 block
		lea edi, [edi+ecx*8];
		neg ecx;

writeloop:
		prefetchnta [esi+ecx*8]; // fetch ahead by 512 bytes

		movq mm0, [esi+ecx*8]; // qword
		movq mm1, [esi+ecx*8+8];
		movq mm2, [esi+ecx*8+16];
		movq mm3, [esi+ecx*8+24];
		movq mm4, [esi+ecx*8+32];
		movq mm5, [esi+ecx*8+40];
		movq mm6, [esi+ecx*8+48];
		movq mm7, [esi+ecx*8+56];

		movntq [edi+ecx*8], mm0;
		movntq [edi+ecx*8+8], mm1;
		movntq [edi+ecx*8+16], mm2;
		movntq [edi+ecx*8+24], mm3;
		movntq [edi+ecx*8+32], mm4;
		movntq [edi+ecx*8+40], mm5;
		movntq [edi+ecx*8+48], mm6;
		movntq [edi+ecx*8+56], mm7;

		add ecx, 8;
		jnz writeloop;
		sfence;
		EMMS;

copy:
		pop ecx;
		rep movsb;
	}
}

TCHAR g_tszCaption[] = _T("Info");

void CDlg_Other::OnBnClickedOtherBtnAsm()
{
	// MD5.cpp 是有一个用C调用汇编的函数

	// 用汇编调用C++的函数

	TCHAR tszMsg[] = _T("C function MessageBox invoked by asm !");
	__asm
	{
		push MB_OK OR MB_ICONINFORMATION;
		lea eax, g_tszCaption;
		push eax;
		lea eax, tszMsg; // 局部变量用 lea
		push eax;
		call DWORD PTR [MessageBox]; // 注意这里不是 CALL MessageBox，而是调用重定位过的函数地址

		push 9999;
		mov ecx, this;
		call func;
	}

	/**

	不要使用函数名称当作标号，否则将转跳到函数中执行

	美元符号"$"用于指定当前指令位置，常用于条件跳转中，例如:

	JNE $+5 ; 下面这条指令的长度是 5 个字节
	JMP _Label
	NOP ; $+5，转跳到了这里

	"属性"菜单项，在属性对话框中，点击"自定义生成步骤"，设置如下项目：

	命令行：ML.exe /nologo /c /coff "-Fo$(IntDir)\$(InputName).obj" "$(InputPath)"
	输出：$(IntDir)\$(InputName).obj

	生成调试信息加入"/Zi"参数

	如果要在汇编文件中调用 Windows API，可以从(http://www.masm32.com)下载 MASM32包(包含了 MASM 汇编工具、
	非常完整的 Windows API 头文件/库文件、实用宏以及大量的 Win32 汇编例子等)。
	相应地，应该在命令行中加入"/I X:\MASM32\INCLUDE"参数指定 Windows API 汇编头文件(.inc)的路径

	ML.EXE 参数说明

	/AT ：允许小模式
	/Bl ：指定链接器
	/c ：只编译，不链接
	/Cp ：保留用户标识符的大小写
	/Cu ：所有标识符映射为大写
	/Cx ：用public或者extrn引用的标志符保留大小写
	/coff：产生coff格式的目标文件
	/F ：设置堆栈长度
	/Fe ：命名可执行程序
	/Fo ：命名目标文件
	/FPi ：对80x87指令进行软件仿真
	/G ：使用Pascal，C或者stdcall调用
	/I ：添加包含文件的路径
	/WX ：视警告为错误
	/W ：设置警告级别
	/Zd ：在调试信息中添加行标号
	/Zf ：使所有符号变为PUBLIC类型
	/Zi ：在调试信息中添加符号信息
	/Zm ：与MASM5.10兼容
	/Zp[n] ：设置结构的对齐方式
	/Zs ：只进行语法检测

	LINK.EXE 參數說明

	LINK [objs],[exefile],[mapfile],[libs],[deffile]

	/A:size ：排列区段位址，不可用于DOS程式
	/B ：忽略.lib或.obj路径错误提示
	/CO ：加入CodeView的符号及列号
	/CP:number ：设定程序最大空间(单位16B)
	/DO ：以预设值(DOSSEG)排列区段顺序
	/DS ：载入资料至资料区段高位址
	/E ：压缩执行档，与/CO或/INC不容
	/F ：使远程呼叫致能与/PAC并用
	/HE ：显示link.exe选择项
	/HI ：执行时载入高记意位址
	/INC ：准备加入ILINK连结
	/INF ：显示连结过程的信息
	/LI ：加入列号结合位址至MAP程式
	/M ：加入公用符号至MAP程序
	/NOD[:library] ：忽略指定程序库
	/NOE ：阻止LINK从程序库中搜寻扩充字
	/NOF ：远程呼叫失效
	/NOI ：区別大小写字母
	/NOG ：忽略群组的定义，以便与早版相容
	/NOL ：忽略LINK版权信息
	/NON ：与/DO同，但不加程序起始位元组
	/NOP ：不压缩邻近程序区段
	/OV ：设定抑制插断
	/PACKC:number ：压缩邻近程序区段
	/PACKD:number ：压缩邻近资源区段
	/PAU ：暂停以便更换磁片
	/PM ：指定Windows或OS/2程式型态
	/Q ：建立程式库给Quick语言
	/SE:number ：设定连结时区段总数，預设为128
	/ST:number ：以此设定堆栈的大小(1~64KB)
	/T ：建立权小模式程序.COM(需设.model tiny)
	/? ：显示简单的LINK语法
	/subsystem:windows：普通pe文件
	/subsystem:console：控制台文件
	/Dll

	# RC [options] srcipt-file

	# options是编译选项，script-file是需要编译的资源脚本文件。

	# /d ：为预处理器定义符号，可以与#ifdef共同使用
	# /fo ：指定rex输出的文件名，如/fo Hello
	# /u ：指定包含文件，如果使用了/i选项，将首先去/i选项指定的目录中寻找包含文件
	然后再去INCLUDE环境变量中去寻找包含文件
	# /l ：指定默认的编译语言，比如/l409相当于在资源脚本中指定LANGUAGE LANG_ENGLISH，
	SUBLANG_ENGLISH_US，也就是替换了在rc脚本中的如下语句：#pargma code_page(409)
	# /n ：在字符串(一种资源类型)中的所有字符都将有0结束符(\0)
	# /r ：忽略在现有makefile的兼容性
	# /v ：显示编译器在编译过程中输入的信息
	# /x ：不使用INCLUDE环境变量来查找头文件和资源文件


	_cdecl 是c调用，参数从右向左入栈，在call后会有 add esp,**，用于平衡堆栈，
	对于像printf,，CString::Format，new 等不能确定有多少个参数，也是用调用后平衡堆栈

	__stdcall 很多Windows API都是使用这种调用方式，参数从右向左入栈

	__fastcall 利用寄存器传输参数的调用方式，
	使用VC，那么前两个参数传给ECX和EDX寄存器，剩下的从右向左入栈；
	如果使用C++Builder，那么前三个双字依次通过EAX，EDX和ECX寄存器传送，其它的从右向左入栈

	__msfastcall 是Inprise公司为了和微软的调用规范兼容而采用的一个特别的关键字

	*/ //---------------------------------------------------------

	UCHAR mycpuid[20] = {""};
	ULONG s1 = 0;
	ULONG s2 = 0;

	__asm
	{
		mov eax,0;

		//执行CPUID指令必须给EAX赋予入口参数
		//当EAX=0时，执行CPUID指令可通过EAX返回
		//处理器能够赋予 EAX 的最大值
		//并通过EBX，EDX，ECX返回生产厂商的标识串
		//Intel公司的为："Genu","ineI","ntel"
		//Cyrix公司的为："Cyri","xIns","tead"
		//AMD公司的为："Auth","enti","cAMD"
		cpuid;
		mov dword ptr mycpuid[0],ebx;
		mov dword ptr mycpuid[4],edx;
		mov dword ptr mycpuid[8],ecx;

		mov eax, 01h;
		xor edx, edx;
		cpuid;
		mov s1, edx;
		mov s2, eax;

		mov eax, 03h;
		xor ecx, ecx;
		xor edx, edx;
		cpuid;
		mov s1, edx;
		mov s2, ecx;
	}


	//---------------------------------------------------------

	char sz1[1000] = {""};
	char sz2[] = "0123456789012345678901234567890123456789"
		"01234567890123456789012345678901234567890123456789"
		"01234567890123456789012345678901234567890123456789*";

	FastMemcpy(&sz1[0], &sz2[0], sizeof(sz2));
}


extern "C" DWORD __stdcall GetArgument(DWORD ai)
{
	TRACE("GetArgument %d\n", ai);
	return ai;
}

extern "C" DWORD __stdcall GetArgument2(DWORD ai);


void CDlg_Other::OnBnClickedOtherBtnAsmC()
{
	// C++调用汇编函数GetArgument2, 在GetArgument2中再调用C++的GetArgument
	// GetArgument2在test.asm中定义
	DWORD nRet = GetArgument2(10);
}

void CDlg_Other::OnBnClickedOtherBtnPrint()
{
	CComPrint Print;
	Print.WinPrint("11111111\n这是测试打印");
}

//#include "common/CXml/Xml.h"
//using namespace JWXml;

void CDlg_Other::OnBnClickedOtherBtnCompile()
{
// 	XT_XML::xml xml;
// 	CString strProjectName;
// 	CString strDebugUsedMfc;
// 
// 	if (xml.Open(_T("TestSet.vcproj")))
// 	{
// 		strProjectName = xml.GetRoot()->GetAttribute(_T("Name"));
// 	}
}

#include "Common/MemLoadDll.h"

void CDlg_Other::OnBnClickedOtherBtnLoaddll()
{
	CString strFileName;

	GetDlgItem(IDC_OTHER_LIST1)->GetWindowText(strFileName);

	CFile f;
	if (f.Open(strFileName,CFile::modeRead))
	{
		int FileLength = (int)f.GetLength();
		void *lpBuf = new char[FileLength];
		f.Read(lpBuf, FileLength);
		f.Close();

		CMemLoadDll a;
		if(a.MemLoadLibrary(lpBuf, FileLength)) //加载dll到当前进程的地址空间
		{
			typedef int (*DLLFUNCTION)(char *);
			DLLFUNCTION fDll = (DLLFUNCTION)a.MemGetProcAddress("ShowInfo");
			if(fDll != NULL)
			{
				MessageBox("找到函数！！");
				CString str;
				str.Format(_T("Result is: %s & %s"), fDll(NULL), fDll("My test text"));
				MessageBox(str);
			}
			else
			{
				DWORD err = GetLastError();
				CString str;
				str.Format(_T("Error: %d"), err);
				MessageBox(str);
			}
		}

		delete[] lpBuf;
	}
}



#include "Common/GUID.h"
#include ".\dlg_other.h"


void CDlg_Other::OnBnClickedOtherBtnGuid()
{
	tGUID NameSpace_DNS = { // 6ba7b810-9dad-11d1-80b4-00c04fd430c8
		0x6ba7b810,
		0x9dad,
		0x11d1,
		0x80, 0xb4, 0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8
	};

	tGUID id = {0};

	CGUID guid;
	guid.CreateGUIDv1(&id);

	TRACE("%0.8x-%0.4x-%0.4x-%0.2x%0.2x-%0.2x%0.2x%0.2x%0.2x%0.2x%0.2x\n",
		id.dwTimeLow,
		id.wTimeMid,
		id.wTimeHighAndVersion,
		id.byClockSeqHighAndReserved,
		id.byClockSeqLow,
		id.Node.nodeID[0],
		id.Node.nodeID[1],
		id.Node.nodeID[2],
		id.Node.nodeID[3],
		id.Node.nodeID[4],
		id.Node.nodeID[5]);

	char szName[] = "www.xt9852.com";
	memset(&id, 0, sizeof(id));
	guid.CraateGUIDv3(&id, NameSpace_DNS, szName, (int)strlen(szName));

	TRACE("%0.8x-%0.4x-%0.4x-%0.2x%0.2x-%0.2x%0.2x%0.2x%0.2x%0.2x%0.2x\n",
		id.dwTimeLow,
		id.wTimeMid,
		id.wTimeHighAndVersion,
		id.byClockSeqHighAndReserved,
		id.byClockSeqLow,
		id.Node.nodeID[0],
		id.Node.nodeID[1],
		id.Node.nodeID[2],
		id.Node.nodeID[3],
		id.Node.nodeID[4],
		id.Node.nodeID[5]);

	memset(&id, 0, sizeof(id));
	guid.CreateGUIDv4(&id);

	TRACE("%0.8x-%0.4x-%0.4x-%0.2x%0.2x-%0.2x%0.2x%0.2x%0.2x%0.2x%0.2x\n\n",
		id.dwTimeLow,
		id.wTimeMid,
		id.wTimeHighAndVersion,
		id.byClockSeqHighAndReserved,
		id.byClockSeqLow,
		id.Node.nodeID[0],
		id.Node.nodeID[1],
		id.Node.nodeID[2],
		id.Node.nodeID[3],
		id.Node.nodeID[4],
		id.Node.nodeID[5]);
}

// 得到桌面句柄，可以直接在桌面上画东西啦
void CDlg_Other::OnBnClickedOtherBtnDesktop()
{
	//查找“Program Manager”窗口
	HWND hWnd= (HWND)::FindWindow("Progman", "Program Manager");
	if (hWnd != NULL)
	{
		//找到“Program Manager”窗口,下面将通过该窗口找到桌面的窗口句柄
		CWnd *pWnd = FindWindowEx(hWnd, NULL, "SHELLDLL_DefView", NULL);
		if (hWnd != NULL)
		{
			//取得桌面ListView控件的窗口句柄
			//真正的桌面,可以用spy++查看
			CWnd *pDesktopWnd = pWnd->GetDlgItem(1);

			CDC *pDC = pDesktopWnd->GetWindowDC();

			RECT rc = {0,0,400,400};
			CBrush Brush(RGB(255,0,0));

			pDC->FillRect(&rc, &Brush);
		}
	}
}

// 等待进程退出,好像调用regedit.exe就不行
void CDlg_Other::OnBnClickedOtherBtnProcess()
{
	char temp_name[256] = "TestSet.exe";
	DWORD exitcode;
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;

	CreateProcess(NULL,temp_name, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);

	GetExitCodeProcess(pi.hProcess, &exitcode);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

// 注册系统热键，当按下这个组合键时，系统会发送WM_HOTKEY消息
void CDlg_Other::OnBnClickedOtherBtnHotkey()
{
	m_nHotKeyID = 0;

	RegisterHotKey(GetSafeHwnd(), m_nHotKeyID, MOD_CONTROL|MOD_ALT|MOD_SHIFT, VK_F1);

	MessageBox("已经注册了系统热键\n按Ctrl+Alt+Shift+F1试一式");
}


void CDlg_Other::OnBnClickedOtherBtnVfunc()
{
	class Base1
	{
	public:
		int nNum1;
		virtual void a1() { ::MessageBox(NULL, "Base1::a1()", "Base1", MB_OK); }
		virtual void b1() { ::MessageBox(NULL, "Base1::b1()", "Base1", MB_OK); }
	};

	int nSize1 = sizeof(Base1);

	typedef void(*Fun)(void);
	Fun pFun = NULL;

	/*
	Base1 内存结构
	|---------|      _________________
	| 虚表指针|---->| a1指针 | b1指针 |
	|---------|      -----------------
	| nNum1   |
	|---------|
	*/

	Base1 b1;

	CString strMessage;
	strMessage.Format("b1地址:%x\n"
		"类中虚函数表地址:%x\n"
		"虚函数表指向地址(即第一个虚函数地址):%x\n"
		"Base1::nNum1:%x",
		(int*)(&b1),
		(int*)(&b1),
		(int*)*(int*)(&b1),
		(int*)&(b1.nNum1));

	MessageBox(strMessage);

	pFun = (Fun)*((int*)*(int*)(&b1)+1); // 指向Base1的b1函数
	pFun();

	// 和上面的语句功能相同
	int** pVftnTab = (int**)&b1;

	for (int i = 0; i < 2; i++)
	{
		pFun = (Fun)pVftnTab[0][i];

		if (NULL != pFun)
		{
			pFun();
		}
		else
		{
			break;
		}
	}

	/*
	一般继承(无虚函数重载)
	1）虚函数按照其声明顺序放于表中。
	2）父类的虚函数在子类的虚函数前面。

	Derive1
	|---------|      ________________________________________
	| 虚表指针|---->| Base1::a1指针 | Base1::b1指针 | i1指针 |
	|---------|      ----------------------------------------
	| nNum1   |
	|---------|
	| nNum3   |
	|---------|
	*/

	class Derive1 : public Base1
	{
	public:
		int nNum3;
		virtual void i1() { ::MessageBox(NULL, "Derive1::i1()", "Derive1", MB_OK); }
	};

	Derive1 d1;

	strMessage.Format("一般继承(无虚函数重载)\n"
		"d1地址:%x\n"
		"类中虚函数表地址:%x\n"
		"虚函数表指向地址(即第一个虚函数地址):%x\n"
		"Base1::nNum1:%x\n"
		"Derive1::nNum3:%x",
		(int*)(&d1),
		(int*)(&d1),
		(int*)*(int*)(&d1),
		(int*)&(d1.nNum1),
		(int*)&(d1.nNum3));

	MessageBox(strMessage);

	pVftnTab = (int**)&d1;

	for (int i = 0; i < 3; i++)
	{
		pFun = (Fun)pVftnTab[0][i];

		if (NULL != pFun)
		{
			pFun();
		}
		else
		{
			break;
		}
	}

	/*
	一般继承(有虚函数重载)
	1）重载的f()函数被放到了虚表中原来父类虚函数的位置。
	2）没有被重载的函数依旧。

	Derive1
	|---------|      __________________________________________
	| 虚表指针|---->| Derive2::c1指针 | Base1::d1指针 | e2指针 |
	|---------|      ------------------------------------------
	| nNum1   |
	|---------|
	| nNum3   |
	|---------|
	*/

	class Base2
	{
	public:
		int nNum2;
		virtual void c1() { ::MessageBox(NULL, "Base2::c1()", "Base2", MB_OK); }
		virtual void d1() { ::MessageBox(NULL, "Base2::d1()", "Base2", MB_OK); }
	};

	class Derive2 : public Base2
	{
	public:
		int nNum4;
		virtual void c1() { ::MessageBox(NULL, "Derive2::c1()", "Derive2", MB_OK); }
		virtual void e2() { ::MessageBox(NULL, "Derive2::e2()", "Derive2", MB_OK); }
	};
	
	Derive2 d2;

	strMessage.Format("一般继承(有虚函数重载)\n"
		"d2地址:%x\n"
		"类中虚函数表地址:%x\n"
		"虚函数表指向地址(即第一个虚函数地址):%x\n"
		"Base2::nNum2:%x\n"
		"Derive2::nNum4:%x",
		(int*)(&d2),
		(int*)(&d2),
		(int*)*(int*)(&d2),
		(int*)&(d2.nNum2),
		(int*)&(d2.nNum4));

	MessageBox(strMessage);

	pVftnTab = (int**)&d2;

	for (int i = 0; i < 3; i++)
	{
		pFun = (Fun)pVftnTab[0][i];

		if (NULL != pFun)
		{
			pFun();
		}
		else
		{
			break;
		}
	}

	/*
	多重继承（无虚函数重载）
	1）每个父类都有自己的虚表。
	2）子类的成员函数被放到了第一个父类的表中。（所谓的第一个父类是按照声明顺序来判断的）

	Derive3
	|---------|      ___________________________________________________________
	| 虚表指针|---->| Base1::a1指针 | Base1::b1指针 | Derive3::e3 | Derive3::f3 |
	|---------|      -----------------------------------------------------------
	| nNum1   |
	|---------|      _______________________________
	| 虚表指针|---->| Base2::c1指针 | Base1::d1指针 |
	|---------|      -------------------------------
	| nNum2   |
	|---------|
	| nNum4   |
	|---------|
	*/

	class Derive3 : public Base1, public Base2
	{
	public:
		int nNum4;
		virtual void e3() { ::MessageBox(NULL, "Derive3::e3()", "Derive3", MB_OK); }
		virtual void f3() { ::MessageBox(NULL, "Derive3::f3()", "Derive3", MB_OK); }
	};

	Derive3 d3;

	strMessage.Format("多重继承（无虚函数重载）\n"
		"d3地址:%x\n"
		"类中虚函数表地址:%x\n"
		"虚函数表指向地址(即第一个虚函数地址):%x\n"
		"Base1::nNum1:%x\n"
		"Base2::nNum2:%x\n"
		"Derive3::nNum4:%x",
		(int*)(&d3),
		(int*)(&d3),
		(int*)*(int*)(&d3),
		(int*)&(d3.nNum1),
		(int*)&(d3.nNum2),
		(int*)&(d3.nNum4));

	MessageBox(strMessage);

	pVftnTab = (int**)&d3;

	for (int i = 0; i < 4; i++)
	{
		pFun = (Fun)pVftnTab[0][i];

		if (NULL != pFun)
		{
			pFun();
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		pFun = (Fun)pVftnTab[2][i];

		if (NULL != pFun)
		{
			pFun();
		}
		else
		{
			break;
		}
	}

	/*
	多重继承（有虚函数重载）
	1）每个父类都有自己的虚表。
	2）子类的成员函数被放到了第一个父类的表中。（所谓的第一个父类是按照声明顺序来判断的）
	3）重载的函数被放到了虚表中原来父类虚函数的位置。
	4）没有被重载的函数依旧。

	Derive4
	|---------|      _______________________________________________
	| 虚表指针|---->| Derive4::a1指针 | Base1::b1指针 | Derive3::f3 |
	|---------|      -----------------------------------------------
	| nNum1   |
	|---------|      _________________________________
	| 虚表指针|---->| Derive4::c1指针 | Base1::d1指针 |
	|---------|      ---------------------------------
	| nNum2   |
	|---------|
	| nNum4   |
	|---------|
	*/

	class Derive4 : public Base1, public Base2
	{
	public:
		int nNum4;
		virtual void a1() { ::MessageBox(NULL, "Derive4::a1()", "Derive4", MB_OK); }
		virtual void c1() { ::MessageBox(NULL, "Derive4::c1()", "Derive4", MB_OK); }
		virtual void f3() { ::MessageBox(NULL, "Derive4::f3()", "Derive4", MB_OK); }
	};

	Derive4 d4;

	strMessage.Format("多重继承（有虚函数重载）\n"
		"d4地址:%x\n"
		"类中虚函数表地址:%x\n"
		"虚函数表指向地址(即第一个虚函数地址):%x\n"
		"Base1::nNum1:%x\n"
		"Base2::nNum2:%x\n"
		"Derive4::nNum4:%x",
		(int*)(&d4),
		(int*)(&d4),
		(int*)*(int*)(&d4),
		(int*)&(d4.nNum1),
		(int*)&(d4.nNum2),
		(int*)&(d4.nNum4));

	MessageBox(strMessage);

	pVftnTab = (int**)&d4;

	for (int i = 0; i < 3; i++)
	{
		pFun = (Fun)pVftnTab[0][i];

		if (NULL != pFun)
		{
			pFun();
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		pFun = (Fun)pVftnTab[2][i];

		if (NULL != pFun)
		{
			pFun();
		}
		else
		{
			break;
		}
	}
}

void ProcFunc(void *pthis, char *data, int len)
{
	TRACE(data);
}

#include "Common/RunProcess.h"

void CDlg_Other::OnBnClickedOtherBtnPipe()
{
	if (m_hInWrite == NULL)
	{
		unsigned int threadId = 0;
		_beginthreadex(NULL, 0, WorkThread, this, 0, &threadId);
	}
}

/**
 *\fn         WorkThread()
 *\brief      线程函数。
 *\param[in]  param 线程参数。
 *\return     线程退出码
 */
unsigned CDlg_Other::WorkThread(void* param)
{
	// 得到this指针
	CDlg_Other *pthis = reinterpret_cast<CDlg_Other*>(param);

	pthis->WorkThreadProc();
	return 0;
}

/**
 *\fn         WorkThreadProc()
 *\brief      线程函数。
 */
void CDlg_Other::WorkThreadProc()
{
	// in,out相对于被调用的程序

	RunProcess proc;

	if (proc.CreateAnonymousPipe(m_hInWrite, m_hInRead) && 
		proc.CreateAnonymousPipe(m_hOutWrite, m_hOutRead))
	{
		proc.setParam(this);
		proc.setProcFunc(ProcFunc);
		proc.Run("plink.exe", "D:\\TestSet\\Tools", "root@172.1.109.194 -pw 666666", false, m_hInRead, m_hOutRead, m_hOutWrite);
	}

	CloseHandle(m_hInWrite);
	m_hInWrite = NULL;
}

void CDlg_Other::OnBnClickedOtherBtnPipe2()
{
	CString strText;
	GetDlgItem(IDC_OTHER_EDIT)->GetWindowText(strText);

	strText += "\n";

	DWORD num = 0;
	WriteFile(m_hInWrite, strText, strText.GetLength(), &num, NULL);
}

#include "Common/ScriptEngine.h"

void CDlg_Other::OnBnClickedOtherBtnScript()
{
    ScriptEngine engine;
    if (0 == engine.AddScripe(_T("D:\\TestSet\\Environment\\res\\config\\script.xml")))
    {
        engine.RunScript(_T("script1"));
    }
}

//#include "NTFS/NTFS_FileRecord.h"

void CDlg_Other::OnBnClickedOtherBtnNtfs()
{
    //CNTFSVolume* pVolume = new CNTFSVolume(_T("D"));

    // USN(Update Sequence Number)

    typedef std::map<DWORDLONG, std::string> FILE_MAP;
    FILE_MAP fileMap;
    FILE_MAP::iterator iter;

    // 打开磁盘卷
    HANDLE diskVol = CreateFile("\\\\.\\D:",
        GENERIC_READ | GENERIC_WRITE, // 可以为0
        FILE_SHARE_READ | FILE_SHARE_WRITE, // 必须包含有FILE_SHARE_WRITE
        NULL, // 这里不需要
        OPEN_EXISTING, // 必须包含OPEN_EXISTING, CREATE_ALWAYS可能会导致错误
        FILE_ATTRIBUTE_READONLY, // FILE_ATTRIBUTE_NORMAL可能会导致错误
        NULL);

    if (INVALID_HANDLE_VALUE == diskVol)
    {
        TRACE("error:%d", GetLastError());
        return;
    }

    // 获取USN日志基本信息
    DWORD retData = 0;
    USN_JOURNAL_DATA usnInfo = {0};

    if (!DeviceIoControl(diskVol, FSCTL_QUERY_USN_JOURNAL, NULL, 0, 
        &usnInfo, sizeof(usnInfo),
        &retData, NULL))
    {
        TRACE("error:%d", GetLastError());
        return;
    }

    //枚举USN日志文件中的所有记录
    int i = 0;
    int pathLen = 0;
    const char *path = NULL;
    int buffer_len = 1204*1024*10;
    char *buffer = new char[buffer_len]; // 用于储存记录的缓冲,尽量足够地大

    WORD fileAtt = 0;
    WORD filenameLen = 0;
    char filename[1024] = "";

    PUSN_RECORD usnRecord = NULL;
    MFT_ENUM_DATA mftData = {0, 0, usnInfo.NextUsn};

    while (DeviceIoControl(diskVol, FSCTL_ENUM_USN_DATA, 
        &mftData, sizeof(mftData), 
        buffer, buffer_len, 
        &retData, NULL))
    {
        usnRecord = (PUSN_RECORD)(((PCHAR)buffer)+sizeof(USN));

        while (0 != usnRecord->FileName[0])
        {
            filenameLen = usnRecord->FileNameLength;
            fileAtt = (usnRecord->FileAttributes>>4)%2;

            filenameLen = WideCharToMultiByte(CP_OEMCP, NULL, 
                usnRecord->FileName, filenameLen/2,
                filename,filenameLen,NULL,FALSE);

            filename[filenameLen] = '\0';

            FILE_MAP::iterator iter = fileMap.find(usnRecord->ParentFileReferenceNumber);

            if (iter != fileMap.end())
            {
                path = iter->second.c_str();
                pathLen = iter->second.length();
            }
            else
            {
                path = "D:\\";
                pathLen = 3;
            }

            for (i = filenameLen; i >= 0; i--)
            {
                filename[pathLen+i] = filename[i];
            }

            strncpy(filename, path, pathLen);

            if ((1 == fileAtt))
            {
                strcat(filename, "\\");
            }

            fileMap.insert(FILE_MAP::value_type(usnRecord->FileReferenceNumber, filename));

            usnRecord = (PUSN_RECORD)(((char*)usnRecord)+usnRecord->RecordLength);

            //TRACE("%s %x\n", filename, fileAtt);
        }

        mftData.StartFileReferenceNumber = *(USN *)&buffer;
    }
}

void CDlg_Other::OnRButtonDown(UINT nFlags, CPoint point)
{
    ClientToScreen(&point);

    TCHAR path[MAX_PATH] = _T("");
    GetModuleFileName(NULL, path, ARRAYSIZE(path));

    CString pathName(path);

    CShellContextMenu menu_;
    menu_.SetObjects(pathName);
    menu_.ShowContextMenu(this, point);

    CDialog::OnRButtonDown(nFlags, point);
}

#include "BsDiff/bsdiff.h"
#include "BsDiff/bspatch.h"
#include "Common/StrConver.h"

void CDlg_Other::OnBnClickedOtherBtnBsdiff()
{
    CString strText;
    GetDlgItem(IDC_OTHER_EDIT)->GetWindowText(strText);

    VECTOR_STR paramList;
    CStrConver::TokenizeData(strText, " ", paramList);

    // param: old file name, new file name, patch file name
    int ret = CreateBinaryPatch(paramList[0].c_str(), paramList[1].c_str(), paramList[2].c_str());

    // param: old file name, patch file name, new file name
    ret = ApplyBinaryPatch(paramList[0].c_str(), paramList[2].c_str(), "new.exe");
}

extern "C"
{
#include "lua\lua.h"
#include "lua\lualib.h"
#include "lua\lauxlib.h"
}

#pragma comment(lib, "../lib/lua/lua52.lib")

int fcAdd(lua_State *lu)
{
    int a = lua_tointeger(lu, 1);
    int b = lua_tointeger(lu, 2);
    lua_pushnumber(lu, a+b); //结果压栈
    return 1; //返回1个结果
}

void CDlg_Other::OnBnClickedOtherBtnLua()
{
    int n = 0;
    int ret = 0;
    const char *info = NULL;

    /* 创建Lua对象 */
    lua_State *lu = luaL_newstate();
    luaL_openlibs(lu);

    /* 栈操作 */
    lua_pushinteger(lu, 1);     // 压入一个int类型的数据,数值为1
    lua_pushinteger(lu, 3);     // 压入一个int类型的数据,数值为3

    n = lua_tointeger(lu, 1);   // 获得栈中第一个元素(也就是刚刚放入的第一个元素"1")
    n = lua_tointeger(lu, 2);   // 获得栈中第二个元素

    n = lua_gettop(lu);         // 获得栈中的元素总数(如果总数为0,表示空.前面放入两个,这里的值为2)
    lua_pop(lu, 2);             // 剔除栈中元素(剔除两个,栈空)
    n = lua_gettop(lu);         // 获得栈中元素总数

    /* 执行内存脚本 */
    const char *str = "print (\"Hello world!\")";

    ret = luaL_loadbuffer(lu, str, strlen(str), "name"); // "name"是chunk名字,用于debug或者错误信息的标识

    n = lua_gettop(lu);

    ret = lua_pcall(lu, 0, 0, 0);// 调用函数(参数的个数,返回参数个数,错误)

    n = lua_gettop(lu);

    if (n != 0)
    {
        info = lua_tostring(lu, -1);// 取得错误信息

        TRACE("%s ret:%d info:%s", str, ret, info);

        lua_pop(lu, n); // 清栈
    }

    /*加载脚本中定义的变量*/
    ret = luaL_dofile(lu, "../Environment/res/config/test.lua");

    n = lua_gettop(lu);

    // lua_setglobal 将栈内的数据传给脚本
    // lua_getglobal 将脚本内的数据传给栈
    lua_getglobal(lu, "aa");// 将脚内变量aa的值压栈
    lua_getglobal(lu, "bb");// 将脚内变量bb的值压栈

    n = lua_gettop(lu);

    int bb = lua_tointeger(lu, -1); // 负从栈顶开始,正从栈底开始
    int aa = lua_tointeger(lu, -2);

    lua_pop(lu, n);

    /* 执行脚本中定义的无参函数 */
    lua_getglobal(lu, "hello"); // 压入hello函数名字,无论函数还是变量,都是通过压入名字然后去调用的

    n = lua_gettop(lu);

    ret = lua_pcall(lu, 0,0,0);//参数nargs为0，表示调用的是无参的函数

    n = lua_gettop(lu);

    lua_pop(lu, n);

    n = lua_gettop(lu);

    /* 执行脚本中定义的有参函数 */
    lua_getglobal(lu, "fadd");
    lua_pushnumber(lu, aa); // 压入即将作为参数的对象
    lua_pushnumber(lu, bb);

    n = lua_gettop(lu);

    //调用函数并获得返回结果(如果nret为0,表示调用成功,返回值会放入栈,通过取值即可获得.
    //否则失败,失败时lua会产生失败信息放入栈,通过取值就可以获得错误信息)
    ret = lua_pcall(lu, 2,1,0); // 调用脚本函数fadd后清栈,然后将返回值再入栈

    n = lua_gettop(lu);

    if (ret != 0)
    {
        info = lua_tostring(lu, -1);

        TRACE("执行脚本中定义的有参函数:fadd ret:%d info:%s", ret, str);
    }
    else
    {
        ret = lua_tointeger(lu, -1);

        TRACE("执行脚本中定义的有参函数:fadd %d+%d=%d", aa, bb, ret);
    }

    lua_pop(lu, n);
    n = lua_gettop(lu);

    /* 脚本中调用C++函数 */
    lua_pushcfunction(lu, fcAdd);   // 压入c++函数

    n = lua_gettop(lu);

    lua_setglobal(lu, "fcAdd");     // 将fcAdd出栈传给脚本

    n = lua_gettop(lu);

    lua_getglobal(lu, "fc");        // 压入脚本函数
    lua_pushnumber(lu, aa);
    lua_pushnumber(lu, bb);

    n = lua_gettop(lu);

    ret = lua_pcall(lu, 2,1,0);     // 调用函数

    n = lua_gettop(lu);

    if (ret != 0)
    {
        str = lua_tostring(lu, -1);
        TRACE("%s\n", str);
    }
    else
    {
        ret = lua_tointeger(lu, -1);
        TRACE("调用C++函数:%d+%d=%d", aa, bb, n);
    }

    lua_pop(lu, n);

    lua_close(lu);
}
