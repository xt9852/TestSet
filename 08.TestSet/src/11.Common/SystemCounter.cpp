// SystemCounter.cpp : 实现文件
//

#include "stdafx.h"
#include "SystemCounter.h"
#include <PdhMsg.h>
#pragma comment(lib , "Pdh.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CSystemCounter::CSystemCounter()
	:m_hQuery(NULL),
	m_pdhStatus(0),
	m_lpsMachineName(NULL),
	m_lpsObjectListBuffer(NULL),
	m_dwObjectListSize(0),
	m_lpsCounterListBuffer(NULL),
	m_dwCounterListSize(0),
	m_lpsInstanceListBuffer(NULL),
	m_dwInstanceListSize(0)
{
}

CSystemCounter::~CSystemCounter()
{
	ClosePDH();
}

bool CSystemCounter::OpenPDH(void)
{
	m_pdhStatus = PdhOpenQuery(0, 0, &m_hQuery);

	if (ERROR_SUCCESS != m_pdhStatus) return false;

	return true;
}

void CSystemCounter::ClosePDH(void)
{
	// 关闭计数器
	if (NULL != m_hQuery)
	{
		PdhCloseQuery(m_hQuery);
		m_hQuery = NULL;
	}

	if (NULL != m_lpsObjectListBuffer)
	{
		delete[] m_lpsObjectListBuffer;
		m_lpsObjectListBuffer = NULL;
	}

	if (NULL != m_lpsCounterListBuffer)
	{
		delete[] m_lpsCounterListBuffer;
		m_lpsCounterListBuffer= NULL;
	}

	if (NULL != m_lpsInstanceListBuffer)
	{
		delete[] m_lpsInstanceListBuffer;
		m_lpsInstanceListBuffer= NULL;
	}
}

bool CSystemCounter::GetObjects(CListCtrl *pListObject)
{
	if (NULL == m_hQuery)
		OpenPDH();

	if (NULL == m_hQuery) return false;

	if (NULL != m_lpsObjectListBuffer) delete[] m_lpsObjectListBuffer;

	// 枚举计数项目
	// 第一次得到缓冲区大小，第二次得到数
	m_pdhStatus = PdhEnumObjects(
		NULL,
		m_lpsMachineName,
		m_lpsObjectListBuffer,
		&m_dwObjectListSize,
		PERF_DETAIL_WIZARD,
		TRUE);

	m_lpsObjectListBuffer = new TCHAR[m_dwObjectListSize + 1];
	if (m_lpsObjectListBuffer == NULL) return false;

	m_pdhStatus = PdhEnumObjects(
		NULL,
		m_lpsMachineName,
		m_lpsObjectListBuffer,
		&m_dwObjectListSize,
		PERF_DETAIL_WIZARD,
		TRUE);

	if (ERROR_SUCCESS != m_pdhStatus) return false;

	InsertListItem(pListObject, m_lpsObjectListBuffer, m_dwObjectListSize);

	return true;	
}
bool CSystemCounter::GetCounters(LPCTSTR lpcsObject, CListCtrl *pListCounter, CListCtrl *pListInstances)
{
	if (NULL == m_hQuery)
		OpenPDH();

	if (NULL == m_hQuery) return false;

	if (NULL != m_lpsCounterListBuffer) delete[] m_lpsCounterListBuffer;
	if (NULL != m_lpsInstanceListBuffer) delete[] m_lpsInstanceListBuffer;

	m_pdhStatus = PdhEnumObjectItems(
		NULL,                   // [IN]数据源，NT4.0必须为NULL
		m_lpsMachineName,       // [IN]机器名。本地机器为NULL
		lpcsObject,				// [IN]计数器对象名
		m_lpsCounterListBuffer, // [OUT]接收计数器列表的缓冲区，如果计数器列表长度为0，则该项为空
		&m_dwCounterListSize,	// [IN/OUT]设置或接收计数器列表长度
		m_lpsInstanceListBuffer,// [OUT]接收实例列表的缓冲区，如果计数器列表长度为0，则该项为空
		&m_dwInstanceListSize,	// [IN/OUT]设置或接收实例列表长度
		PERF_DETAIL_WIZARD,		// 获取信息的级别
								// PERF_DETAIL_NOVICE 初级级别 
								// PERF_DETAIL_ADVANCE 高级级别（包含初级）
								// PERF_DETAIL_EXPERT 专家级别（包含初级和高级）
								// PERF_DETAIL_WIZARD 系统级别（包含所有级别）
		0);						// 最后一个参数系统保留为0

	m_lpsCounterListBuffer = new TCHAR[m_dwCounterListSize + 1];
	if (NULL == m_lpsCounterListBuffer) return false;

	m_lpsInstanceListBuffer = new TCHAR[m_dwInstanceListSize + 1];
	if (NULL == m_lpsInstanceListBuffer) return false;

	// 获取指定计数器对象的所有计数器和实例
	m_pdhStatus = PdhEnumObjectItems(
		NULL,
		m_lpsMachineName,
		lpcsObject,
		m_lpsCounterListBuffer,
		&m_dwCounterListSize,
		m_lpsInstanceListBuffer,
		&m_dwInstanceListSize,
		PERF_DETAIL_WIZARD,
		0);

	if (m_pdhStatus != ERROR_SUCCESS) return false;

	InsertListItem(pListCounter, m_lpsCounterListBuffer, m_dwCounterListSize);
	InsertListItem(pListInstances, m_lpsInstanceListBuffer, m_dwInstanceListSize);

	return true;
}

bool CSystemCounter::GetValue(LONG &lValue, LPTSTR lpcsObject, LPTSTR lpcsCounter, LPTSTR lpcsInstance/* = NULL*/)
{
	if (NULL == m_hQuery)
		OpenPDH();

	if (NULL == m_hQuery) return false;

	TCHAR szBuffer[256] = TEXT("");
	DWORD dwBufferSize = sizeof(szBuffer);

	HCOUNTER hCouterSet = {0};	
	PDH_FMT_COUNTERVALUE pdhfmtValue = {0};
	PDH_COUNTER_PATH_ELEMENTS pdhCpe = {0}; 

	pdhCpe.szMachineName = m_lpsMachineName;
	pdhCpe.szObjectName = lpcsObject; 
	pdhCpe.szCounterName = lpcsCounter;
	pdhCpe.szInstanceName = lpcsInstance;
	pdhCpe.szParentInstance = NULL; 
	pdhCpe.dwInstanceIndex = -1;

	// get path
	m_pdhStatus = PdhMakeCounterPath(&pdhCpe, szBuffer, &dwBufferSize, 0);
	if (ERROR_SUCCESS != m_pdhStatus) return false;

	// add counter
	m_pdhStatus = PdhAddCounter(m_hQuery, szBuffer, 0, &hCouterSet); 
	if (ERROR_SUCCESS != m_pdhStatus) return false;

	// get the data. 
	m_pdhStatus = PdhCollectQueryData(m_hQuery);
	if (ERROR_SUCCESS != m_pdhStatus) return false;

	// format counter values. 
	m_pdhStatus = PdhGetFormattedCounterValue(hCouterSet, PDH_FMT_LONG | PDH_FMT_NOSCALE, NULL, &pdhfmtValue);
	if (ERROR_SUCCESS != m_pdhStatus) return false;

	lValue = pdhfmtValue.longValue;

	return true;
}


void CSystemCounter::InsertListItem(CListCtrl *pList, LPTSTR lpsInfo, int nInfoLen)
{
	if (NULL == pList) return;

	int nSubLen = 0;

	LPTSTR lpsHead = lpsInfo;

	while (NULL != lpsHead && (nSubLen = (int)_tcslen(lpsHead)) > 0 && nInfoLen > 0)
	{
		pList->InsertItem(pList->GetItemCount(), lpsHead);

		lpsHead += nSubLen + 1;
		nInfoLen -= nSubLen + 1;
	}
}