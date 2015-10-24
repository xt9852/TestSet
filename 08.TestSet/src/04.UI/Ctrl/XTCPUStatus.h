#pragma once
#include "XTDC.h"

#define SystemBasicInformation 0 
#define SystemPerformanceInformation 2 
#define SystemTimeInformation 3 

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart)) 

class CCpuUsage
{
public:
	CCpuUsage();
	~CCpuUsage();

public:
	int GetCpuUsage();                       //得到系统cpu利用率
	int SetRefreshInterval(int milli_sec);   //定时刷新间隔

private:
	//类型定义
	typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

	typedef struct
	{
		DWORD dwUnknown1;
		ULONG uKeMaximumIncrement;
		ULONG uPageSize;
		ULONG uMmNumberOfPhysicalPages;
		ULONG uMmLowestPhysicalPage;
		ULONG uMmHighestPhysicalPage;
		ULONG uAllocationGranularity;
		PVOID pLowestUserAddress;
		PVOID pMmHighestUserAddress;
		ULONG uKeActiveProcessors;
		BYTE bKeNumberProcessors;
		BYTE bUnknown2;
		WORD wUnknown3;
	} SYSTEM_BASIC_INFORMATION;

	typedef struct
	{
		LARGE_INTEGER liIdleTime;
		DWORD dwSpare[76];
	} SYSTEM_PERFORMANCE_INFORMATION;

	typedef struct
	{
		LARGE_INTEGER liKeBootTime;
		LARGE_INTEGER liKeSystemTime;
		LARGE_INTEGER liExpTimeZoneBias;
		ULONG uCurrentTimeZoneId;
		DWORD dwReserved;
	} SYSTEM_TIME_INFORMATION;

	//变量定义
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
	SYSTEM_TIME_INFORMATION SysTimeInfo;
	SYSTEM_BASIC_INFORMATION SysBaseInfo;
	double dbIdleTime;
	double dbSystemTime;

	LONG status;

	LARGE_INTEGER liOldIdleTime;
	LARGE_INTEGER liOldSystemTime;

	PROCNTQSI NtQuerySystemInformation;

	int m_nCpuUsage;

	//定时
	HWND m_hWnd;
	int  m_nRefreshInterval;//默认为1000毫秒
	int  m_nTimerID;

private:
	static void CalcCpuUsage(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	int OnTimer();
};

inline CCpuUsage::CCpuUsage()
{
	m_hWnd = NULL;
	m_nRefreshInterval = 1000;
	m_nTimerID = 1000;
	m_nCpuUsage = 0;

	memset(&liOldIdleTime  ,   0, sizeof(LARGE_INTEGER));
	memset(&liOldSystemTime,   0, sizeof(LARGE_INTEGER)); 

	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(
		GetModuleHandle(_T("ntdll")) , "NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		return;

	// get number of processors in the system
	status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
	if (status != NO_ERROR)
		return;

	// create control for timer
	m_hWnd = ::CreateWindow(_T("static"), _T(""), 0, 0, 0, 0, 0, NULL, NULL, 0, NULL);
#pragma warning(disable : 4311)
	::SetWindowLong(m_hWnd , GWL_USERDATA , (long)(this));
#pragma warning(default : 4311)

	TIMERPROC tp = (TIMERPROC)CalcCpuUsage;
	SetTimer(m_hWnd , m_nTimerID, m_nRefreshInterval, tp);

}

inline CCpuUsage::~CCpuUsage()
{
	KillTimer(m_hWnd , m_nTimerID);
	DestroyWindow(m_hWnd);
}

inline void CCpuUsage::CalcCpuUsage(HWND hwnd,
									UINT uMsg,
									UINT_PTR idEvent,
									DWORD dwTime)
{
#pragma warning(disable : 4312)
	CCpuUsage* pCpu = (CCpuUsage*)::GetWindowLong(hwnd , GWL_USERDATA);
#pragma warning(disable : 4312)

	if (pCpu)
	{
		pCpu->OnTimer();
	}

}

inline int CCpuUsage::OnTimer()
{
	status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);

	if (status!=NO_ERROR)
		return 0;

	// get new CPU's idle time
	status = NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
	if (status != NO_ERROR)
		return 0;

	// if it's a first call - skip it
	if (liOldIdleTime.QuadPart != 0)
	{
		// CurrentValue = NewValue - OldValue
		dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime);
		dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);

		// CurrentCpuIdle = IdleTime / SystemTime
		dbIdleTime = dbIdleTime / dbSystemTime;

		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
		dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors + 0.5;

		m_nCpuUsage = (UINT)dbIdleTime;
	}

	// store new CPU's idle and system time
	liOldIdleTime = SysPerfInfo.liIdleTime;
	liOldSystemTime = SysTimeInfo.liKeSystemTime;

	// wait one second

	return 0;
}

inline int CCpuUsage::GetCpuUsage()
{
	return m_nCpuUsage;
}

inline int CCpuUsage::SetRefreshInterval(int milli_sec)
{
	m_nRefreshInterval = milli_sec;

	if ( m_hWnd )
	{
		TIMERPROC tp = (TIMERPROC)CalcCpuUsage;
		SetTimer(m_hWnd, m_nTimerID, m_nRefreshInterval ,tp);
	}

	return 0;
}

//-----------------------------------------------------------------------------------------------------

#define CPU_GRID_CX 12
#define CPU_GRID_CY 12

class CXTCPUStatus : public CStatic
{
	DECLARE_DYNAMIC(CXTCPUStatus)

public:
	CXTCPUStatus();
	virtual ~CXTCPUStatus();

	void Init(int nInterval);

private:
	CCpuUsage	m_cpuUsage;
	CXTDC		m_xtDC;
	HDC			m_hDC;
	HDC			m_hCompDC;
	HPEN		m_hPen;
	HPEN		m_hPenLine;
	HPEN		m_hPenBlack;
	HBRUSH		m_hBrush;

	UINT		m_nCPU;
	RECT		m_rItem;
	POINT		*m_pPoint;
	UINT		m_nCountX;
	UINT		m_nCountY;
	SIZE		m_nCompDC;
	UINT		m_nLastX;
	float		m_nInter;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};


