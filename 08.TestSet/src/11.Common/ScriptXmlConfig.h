#pragma once
#include "Base/XTXml.h"
#include "ScriptParam.h"

class ScriptXmlConfig
{
public:
    ScriptXmlConfig();
    ~ScriptXmlConfig();

protected:
    STEP_LIST stepList_;
    TCHAR     name_[MAX_PATH];
    TCHAR     desc_[MAX_PATH];

public:
    bool OpenFile(LPCTSTR filename);

    STEP_LIST* getScript() { return &stepList_; }

    LPCTSTR getName() { return name_; }

    LPCTSTR getDesc() { return desc_; }
};