
#include "stdafx.h" 
#include "AutoLock.h"

CLock::CLock()
{
	m_pCriticalSection = NULL;
}
CLock::~CLock()
{
	if( NULL != m_pCriticalSection )
    {
		DeleteCriticalSection(m_pCriticalSection);
	}

	if (NULL != m_pCriticalSection)
	{
		delete m_pCriticalSection;
		m_pCriticalSection = NULL;
	}
}


void CLock::Construct(void)
{
	if( NULL == m_pCriticalSection )
    {
		m_pCriticalSection = new CRITICAL_SECTION;

        ASSERT(NULL != m_pCriticalSection);

		InitializeCriticalSection(m_pCriticalSection);
	}
}

void CLock::Lock(void)
{
	if (NULL != m_pCriticalSection)
    {
		EnterCriticalSection(m_pCriticalSection);
	}
}

void CLock::Unlock(void)
{
	if (NULL != m_pCriticalSection)
    {
		LeaveCriticalSection(m_pCriticalSection);
	}
}

//-----------------------------------------------------

CTempLock::CTempLock(CLock* lock)
{	
	m_pCriticalSection = NULL;
	m_pAutoLock = lock;
	if (NULL != m_pAutoLock)
    {
		m_pAutoLock->Lock();
	}
}
CTempLock::CTempLock(CRITICAL_SECTION* criticalSection)
{
	m_pAutoLock = NULL;
	m_pCriticalSection = criticalSection;
	if (NULL != m_pCriticalSection)
    {
		EnterCriticalSection(m_pCriticalSection);
	}
}

CTempLock::CTempLock(CLock& lock)
{
	m_pCriticalSection = NULL;
	m_pAutoLock = &lock;
	if (NULL != m_pAutoLock)
    {
		m_pAutoLock->Lock();
	}
}

CTempLock::~CTempLock()
{
	if (NULL != m_pCriticalSection)
    {
		LeaveCriticalSection(m_pCriticalSection);
	}
    else if (NULL != m_pAutoLock)
    {
		m_pAutoLock->Unlock();
	}
}
