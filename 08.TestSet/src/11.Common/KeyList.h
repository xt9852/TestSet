#pragma once
#include <map>
#include <list>

typedef std::list<__int64>			LIST_KEY;
typedef std::map<__int64, void*>	MAP_KEY_;

class CKeyList
{
public:
	CKeyList(void);
	~CKeyList(void);

protected:
	CRITICAL_SECTION	csUsed_;
	LIST_KEY			keyList_;
	MAP_KEY_			keyMap_;

public:
    void     AddHead(__int64 key, void *data);
	void     AddTail(__int64 key, void *data);

    void*    GetHead(bool del);
    void*    GetTail(bool del);
    void*    GetNode(__int64 key);

    POSITION GetHeadPos();
    POSITION GetTailPos();
    PVOID    GetNext(POSITION &ps);
    PVOID    GetPrev(POSITION &ps);

    void     DelHead();
    void     DelTail();
    void     DelAll();
    PVOID    DelNode(__int64 key);

	int      getCount();
};
