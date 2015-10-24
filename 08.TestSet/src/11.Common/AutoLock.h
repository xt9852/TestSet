#ifndef _C_AUTO_LOCK__H
#define _C_AUTO_LOCK__H

#pragma once
#include <windows.h> 

class CLock
{
public:	
	CLock();
	~CLock();

public:
    void Construct(void);
	void Lock(void);
	void Unlock(void);
private:
	CRITICAL_SECTION* m_pCriticalSection;
};

class  CTempLock
{
public:	
	CTempLock(CLock* lock);
	CTempLock(CLock& lock);
	CTempLock(CRITICAL_SECTION* criticalSection);
	~CTempLock();

private:
	CLock* m_pAutoLock;
	CRITICAL_SECTION* m_pCriticalSection;
};

#endif