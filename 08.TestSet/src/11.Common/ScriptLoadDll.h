#pragma once
#include <map>

typedef struct _tagScriptDll
{
    HMODULE module;
    int refCount; // 此用记数

}SCRIPTDLL, *PSCRIPTDLL;

typedef std::map<std::string, SCRIPTDLL> SCRIPT_DLL_MAP;


class ScriptLoadDll
{
public:
    ScriptLoadDll();
    ~ScriptLoadDll();

protected:
    CRITICAL_SECTION	csUsed_;	// 临界区
    SCRIPT_DLL_MAP      scriptDll_;

public:
    HMODULE getDll(LPCTSTR filename);
    int releaseDll(LPCTSTR filename);
    int releaseDll();
};