#include "stdafx.h"
#include "ScriptEngine.h"


ScriptEngine::ScriptEngine()
{
}

ScriptEngine::~ScriptEngine()
{
    SCRIPT_MAP::iterator iter = scriptMap_.begin();

    for (; iter != scriptMap_.end(); ++iter)
    {
        STEP_LIST::iterator stepIter = iter->second.begin();

        for (; stepIter != iter->second.end(); ++stepIter)
        {
            STEP *step = (*stepIter);
            PARM_LIST::iterator paramIter = step->paramList.begin();

            for (; paramIter != step->paramList.end(); ++paramIter)
            {
                PARAM *param = (*paramIter);
                delete param;
            }

            step->paramList.clear();
            delete step;
        }
        
        iter->second.clear();
    }

    scriptMap_.clear();
}

int ScriptEngine::AddScripe(LPCTSTR filename)
{
    if (scriptXml_.OpenFile(filename))
    {
        STEP_LIST *script = scriptXml_.getScript();

        if (NULL != script)
        {
            scriptMap_[scriptXml_.getName()] = *script;
            return 0;
        }
    }

    return -1;
}

bool ScriptEngine::getParamName(LPCTSTR name, LPTSTR param, int paramSize)
{
    if (NULL == name) return NULL;

    int len = _tcslen(name);

    if (len <= 4) return NULL;

    if (('#' == name[0]) &&
        ('#' == name[1]) &&
        ('#' == name[len-2]) &&
        ('#' == name[len-1]))
    {
        _tcsncpy_s(param, paramSize, &name[2], len-4);
        return true;
    }

    return false;
}

int ScriptEngine::ReplaceStr(LPTSTR text, int textBufferSize, LPTSTR srcText, LPCTSTR desText)
{
    if (NULL == text || NULL == srcText || NULL == desText || 0 == textBufferSize) return -1;

    std::string::size_type pos = 0;
    std::string::size_type srclen = _tcslen(srcText);
    std::string::size_type dstlen = _tcslen(desText);

    std::string src(srcText);
    std::string str(text);

    while((pos = str.find(src, pos)) != std::string::npos)
    {
        str.replace(pos, srclen, desText);
        pos += dstlen;
    }

    _tcscpy_s(text, textBufferSize, str.c_str());

    return 0;
}

int ScriptEngine::ParseParam(PARAM *param)
{
    USES_CONVERSION;

    if (NULL == param) return -1;

    if (param->valueStr != NULL)
    {
        ReplaceStr(param->valueStr, param->size, _T("\\n"), _T("\n"));
    }

    while (param->valueStr != NULL) 
    {
        LPCTSTR end = NULL;
        LPCTSTR begin = _tcsstr(param->valueStr, _T("##"));

        if (NULL == begin) return -2;

        end = _tcsstr(begin+1, _T("##"));

        if (NULL == end) return -3;

        TCHAR name[MAX_PATH] = _T("");
        _tcsncpy_s(name, ARRAYSIZE(name), &begin[2], (end-begin) / sizeof(TCHAR) - 2);

        TCHAR name1[MAX_PATH] = _T("");
        _stprintf_s(name1, ARRAYSIZE(name1), _T("##%s##"), name);

        PARAM *p1 = scriptParam_.getParam(name);

        if (NULL == p1) continue;

        switch(p1->type)
        {
        case PARAM_INT:
        case PARAM_VOID_PTR:
        case PARAM_VOID_PTR_PTR:
            {
                TCHAR value[MAX_PATH] = _T("");
                _stprintf_s(value, ARRAYSIZE(value), _T("%d"), p1->getInt());
                ReplaceStr(param->valueStr, param->size, name1, value);
                break;
            }
        case PARAM_FLOAT:
            {
                TCHAR value[MAX_PATH] = _T("");
                _stprintf_s(value, ARRAYSIZE(value), _T("%f"), p1->getFloat());
                ReplaceStr(param->valueStr, param->size, name1, value);
                break;
            }
        case PARAM_DOUBLE:
            {
                TCHAR value[MAX_PATH] = _T("");
                _stprintf_s(value, ARRAYSIZE(value), _T("%lf"), p1->getDouble());
                ReplaceStr(param->valueStr, param->size, name1, value);
                break;
            }
        case PARAM_TCHAR:
            {
                ReplaceStr(param->valueStr, param->size, name1, p1->getTchar());
                break;
            }
        case PARAM_CAHR:
            {
                ReplaceStr(param->valueStr, param->size, name1, A2T((LPSTR)p1->getChar()));
                break;
            }
        case PARAM_WCHAR:
            {
                ReplaceStr(param->valueStr, param->size, name1, W2T(p1->getWchar()));
                break;
            }
        case PARAM_STD_STRING:
            {
                std::string *str = p1->getString();
                ReplaceStr(param->valueStr, param->size, name1, A2T((LPSTR)str->c_str()));
                break;
            }
        case PARAM_STD_WSTRING:
            {
                std::wstring *str = p1->getWstring();
                ReplaceStr(param->valueStr, param->size, name1, W2T(str->c_str()));
                break;
            }
        }
    }

    return 0;
}

int ScriptEngine::ParseInputParam(STEP_LIST::iterator iter)
{
    USES_CONVERSION;

    PARM_LIST::iterator paramiter = (*iter)->paramList.begin();
    for (; paramiter != (*iter)->paramList.end(); ++paramiter)
    {
        PARAM *param = (*paramiter);

        ParseParam(param);

        param->updateData();
    }

    return 0;
}

int ScriptEngine::ParseOutputParam(STEP_LIST::iterator iter)
{
    USES_CONVERSION;

    STEP *step = (*iter);

    // 保存返回值
    scriptParam_.setParam(step->ret.name, &(step->ret));

    // 处理其它参数
    PARM_LIST::iterator paramiter = step->paramList.begin();
    for (; paramiter != step->paramList.end(); ++paramiter)
    {
        PARAM *param = (*paramiter);

        if (!param->input)
        {
            scriptParam_.setParam(param->name, param);
        }
    }

    return 0;
}

int ScriptEngine::RunStep(STEP_LIST::iterator iter)
{
    STEP *step = (*iter);

    HMODULE module = scriptDll_.getDll(step->dll);

    if (NULL != module)
    {
        DWORD func = (DWORD)GetProcAddress(module, step->func);

        if (NULL != func)
        {
            int retValue = 0;
            PARAM *param = NULL;

            PARM_LIST::reverse_iterator paramiter = step->paramList.rbegin();
            for (int value = 0; paramiter != step->paramList.rend(); ++paramiter)
            {
                param = (*paramiter);

                value = (int)param->value;

                __asm
                {
                    push value;
                }
            }

            __asm
            {
                call func;

                mov retValue, eax;
            }

            step->ret.value = retValue;
            step->ret.type = PARAM_INT;
        }

        return 0;
    }
    
    return -1;
}

int ScriptEngine::RunScript(LPCTSTR scriptName)
{
    if (NULL == scriptName) return -1;

    SCRIPT_MAP::iterator iter = scriptMap_.find(scriptName);

    if (iter != scriptMap_.end())
    {
        STEP_LIST::iterator stepIter = iter->second.begin();

        for (; stepIter != iter->second.end(); ++stepIter)
        {
            ParseInputParam(stepIter);
            RunStep(stepIter);
            ParseOutputParam(stepIter);
        }

        scriptDll_.releaseDll();
    }

    return 0;
}
