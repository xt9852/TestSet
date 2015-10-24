#include "StdAfx.h"
#include "KeyList.h"

CKeyList::CKeyList()
{
    InitializeCriticalSection(&csUsed_);
}

CKeyList::~CKeyList()
{
    DelAll();
    DeleteCriticalSection(&csUsed_);
}

void CKeyList::AddHead(__int64 key, void *data)
{
    EnterCriticalSection(&csUsed_);

    keyList_.push_front(key);
    keyMap_.insert(MAP_KEY_::value_type(key, data));

    LeaveCriticalSection(&csUsed_);
}

void CKeyList::AddTail(__int64 key, void *data)
{
    EnterCriticalSection(&csUsed_);

	keyList_.push_back(key);
	keyMap_.insert(MAP_KEY_::value_type(key, data));

    LeaveCriticalSection(&csUsed_);
}

void* CKeyList::GetHead(bool del)
{
    void *data = NULL;
    EnterCriticalSection(&csUsed_);

    if (0 != keyList_.size())
    {
        LIST_KEY::iterator iterList = keyList_.begin();
        MAP_KEY_::iterator iterMap = keyMap_.find(*iterList);

		data = iterMap->second;

        if (del)
        {
			keyList_.erase(iterList);
			keyMap_.erase(iterMap);
        }
    }

    LeaveCriticalSection(&csUsed_);

    return data;
}

void* CKeyList::GetTail(bool del)
{
    void *data = NULL;
    EnterCriticalSection(&csUsed_);

	if (0 != keyList_.size())
	{
		LIST_KEY::iterator iterList = --(keyList_.end());
		MAP_KEY_::iterator iterMap = keyMap_.find(*iterList);

		data = iterMap->second;

		if (del)
		{
			keyList_.erase(iterList);
			keyMap_.erase(iterMap);
		}
	}

    LeaveCriticalSection(&csUsed_);

    return data;
}

PVOID CKeyList::GetNode(__int64 key)
{
    void *data = NULL;
    EnterCriticalSection(&csUsed_);

	MAP_KEY_::iterator iter = keyMap_.find(key);
    
	if (iter != keyMap_.end())
	{
		data = iter->second;
	}

    LeaveCriticalSection(&csUsed_);

    return data;
}

void* CKeyList::DelNode(__int64 key)
{
    void* data = NULL;
	EnterCriticalSection(&csUsed_);

	keyMap_.erase(key);
    
    LIST_KEY::iterator iter = keyList_.begin();

	for (; iter != keyList_.end(); ++iter)
	{
		if (*iter == key)
		{
			keyList_.erase(iter);
			break;
		}
	}

    LeaveCriticalSection(&csUsed_);

    return data;
}

void CKeyList::DelAll()
{
    EnterCriticalSection(&csUsed_);

    keyList_.clear();
    keyMap_.clear();

    LeaveCriticalSection(&csUsed_);
}

int CKeyList::getCount()
{
    EnterCriticalSection(&csUsed_);

    int count = keyMap_.size();

    LeaveCriticalSection(&csUsed_);

    return count;
}
