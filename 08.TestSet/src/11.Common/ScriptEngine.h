#pragma once
#include "ScriptXmlConfig.h"
#include "ScriptLoadDll.h"
#include "ScriptParam.h"
#include <map>


typedef std::map<std::string, STEP_LIST> SCRIPT_MAP;

class ScriptEngine
{
public:
    ScriptEngine();
    ~ScriptEngine();

protected:
    SCRIPT_MAP      scriptMap_;
    ScriptXmlConfig scriptXml_;
    ScriptLoadDll   scriptDll_;
    ScriptParam     scriptParam_;

    int ReplaceStr(LPTSTR text, int textBufferSize, LPTSTR srcText, LPCTSTR desText);

    bool getParamName(LPCTSTR name, LPTSTR param, int paramSize);

    int ParseParam(PARAM *param);

    int ParseInputParam(STEP_LIST::iterator iter);
    int ParseOutputParam(STEP_LIST::iterator iter);
    int RunStep(STEP_LIST::iterator iter);

public:
    int AddScripe(LPCTSTR filename);    
    int RunScript(LPCTSTR scriptName);
};