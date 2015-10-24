#include "stdafx.h"
#include "ScriptLoadDll.h"


ScriptLoadDll::ScriptLoadDll()
{
    InitializeCriticalSection(&csUsed_);
}

ScriptLoadDll::~ScriptLoadDll()
{
    DeleteCriticalSection(&csUsed_);
}

HMODULE ScriptLoadDll::getDll(LPCTSTR filename)
{
    if (NULL == filename) return NULL;

    HMODULE module = NULL;

    EnterCriticalSection(&csUsed_);

    SCRIPT_DLL_MAP::iterator iter = scriptDll_.find(filename);

    if  (iter != scriptDll_.end())
    {
        iter->second.refCount++;

        module = iter->second.module;
    }
    else
    {
        module = LoadLibrary(filename);

        if (NULL != module)
        {
            SCRIPTDLL dll;
            dll.refCount = 1;
            dll.module = module;
            scriptDll_[filename] = dll;
        }
    }

    LeaveCriticalSection(&csUsed_);

    return module;
}

int ScriptLoadDll::releaseDll(LPCTSTR filename)
{
    if (NULL == filename) return NULL;

    EnterCriticalSection(&csUsed_);

    SCRIPT_DLL_MAP::iterator iter = scriptDll_.find(filename);

    if  (iter != scriptDll_.end())
    {
        if (0 == --iter->second.refCount)
        {
            FreeLibrary(iter->second.module);
            scriptDll_.erase(iter);
        }
    }

    LeaveCriticalSection(&csUsed_);

    return 0;
}

int ScriptLoadDll::releaseDll()
{
    EnterCriticalSection(&csUsed_);

    SCRIPT_DLL_MAP::iterator iter = scriptDll_.begin();

    for  (; iter != scriptDll_.end(); ++iter)
    {
        FreeLibrary(iter->second.module);
    }

    scriptDll_.clear();

    LeaveCriticalSection(&csUsed_);

    return 0;
}