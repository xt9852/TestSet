#include "StdAfx.h"
#include ".\avlist.h"

CAVList::CAVList(void)
{
	m_dwAudioId = 0;
	m_dwVideoId = 0;
	m_wLimitNum = 50;
	m_pBuffPool = NULL;
}

CAVList::~CAVList(void)
{
}

bool CAVList::Init(CBuffPool* pBuffPool, WORD wLimitNum)
{
	if (NULL == pBuffPool) return false;

	m_pBuffPool = pBuffPool;
	m_wLimitNum = wLimitNum;

	return true;
}

// 将存的数据限定在m_wLimitNum
bool CAVList::AddLimitNode(DWORD dwKey, LPBYTE pbyData)
{
	if (NULL == pbyData) return false;

	PVOID pvRet = NULL;
	
	EnterCriticalSection(&m_csKeyList);

	try
	{
		m_KeyList.AddTail(dwKey);
		m_KeyMap.SetAt(dwKey, pbyData);

		if (m_KeyList.GetCount() > m_wLimitNum)
		{
			DWORD dwDelKey = (DWORD)m_KeyList.RemoveHead();
			m_KeyMap.Lookup(dwDelKey, pvRet);

			if (NULL != m_pBuffPool)
				m_pBuffPool->Free(pvRet);
			else
				TRACE("CAVList::DelAll m_pBufferPool NULL\n");
			m_KeyMap.RemoveKey(dwDelKey);
		}
	}
	catch(...)
	{
		TRACE("%d", ::GetLastError());
	}

	LeaveCriticalSection(&m_csKeyList);

	return true;
}

void CAVList::DelAll(void)
{
	PVOID pvData = NULL;

	EnterCriticalSection(&m_csKeyList);

	INT_PTR nCount = m_KeyList.GetSize();

	for(int i = 0; i < nCount; i++)
	{
		DWORD dwKey = (DWORD)m_KeyList.RemoveHead();

		m_KeyMap.Lookup(dwKey, pvData);

		if (NULL != m_pBuffPool)
			m_pBuffPool->Free(pvData);
		else
			TRACE("CAVList::DelAll m_pBufferPool NULL\n");
	}
    m_KeyMap.RemoveAll();

	LeaveCriticalSection(&m_csKeyList);
}

int CAVList::EnumAll(void)
{
	EnterCriticalSection(&m_csKeyList);

	int nCount = (int)m_KeyList.GetCount();

	POSITION ps = m_KeyList.GetHeadPosition();

	while (NULL != ps)
	{
		DWORD dwId = (DWORD)m_KeyList.GetNext(ps);
		TRACE("________%d\n", dwId);
	}

	LeaveCriticalSection(&m_csKeyList);

	return nCount;
}
