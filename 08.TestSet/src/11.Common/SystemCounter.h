
/**
	可得到到各个进程和系统的各种记数器的值，包括任务管理的全部的值。和控制面板/管理工具/性能具有同样的功能
*/
#pragma once
#include <Pdh.h>

class CSystemCounter
{
public:
	CSystemCounter();           // 动态创建所使用的受保护的构造函数
	virtual ~CSystemCounter();

	bool OpenPDH(void);
	void ClosePDH(void);

	bool GetObjects(CListCtrl *pListObject);
	bool GetCounters(LPCTSTR lpcsObject, CListCtrl *pListCounter, CListCtrl *pListInstances);
	bool GetValue(LONG &lValue, LPTSTR lpcsObject, LPTSTR lpcsCounter, LPTSTR lpcsInstance = NULL);

protected:
	void InsertListItem(CListCtrl *pList, LPTSTR lpsInfo, int nInfoLen);	

private:
	HQUERY		m_hQuery;
	PDH_STATUS	m_pdhStatus;

	LPTSTR		m_lpsMachineName;
	LPTSTR		m_lpsObjectListBuffer;
	DWORD		m_dwObjectListSize;
	LPTSTR		m_lpsCounterListBuffer;	
	DWORD		m_dwCounterListSize;
	LPTSTR		m_lpsInstanceListBuffer;	
	DWORD		m_dwInstanceListSize;
};
