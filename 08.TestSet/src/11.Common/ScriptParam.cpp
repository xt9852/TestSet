#include "stdafx.h"
#include "ScriptParam.h"


ScriptParam::ScriptParam()
{
}

ScriptParam::~ScriptParam()
{
    scriptParam_.clear();
}

PARAM* ScriptParam::getParam(LPCTSTR name)
{
    PARAM_MAP::iterator iter = scriptParam_.find(name);

    if (iter != scriptParam_.end())
    {
        return iter->second;
    }

    return NULL;
}

void ScriptParam::setParam(LPCTSTR name, PARAM *value)
{
    PARAM_MAP::iterator iter = scriptParam_.find(name);

    if (iter != scriptParam_.end())
    {
        iter->second = value;
    }
    else
    {
        scriptParam_[name] = value;
    }
}
