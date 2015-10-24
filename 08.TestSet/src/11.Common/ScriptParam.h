#pragma once
#include <map>

enum
{
    PARAM_INT = 1,
    PARAM_FLOAT,
    PARAM_DOUBLE,
    PARAM_TCHAR,
    PARAM_CAHR,
    PARAM_WCHAR,
    PARAM_STD_STRING,
    PARAM_STD_WSTRING,
    PARAM_VOID_PTR,
    PARAM_VOID_PTR_PTR,
};

typedef struct _tagParam
{
    int getInt() { return (int)value; }

    float getFloat(){ return (float)value; }

    double getDouble() { return value; }

    LPCSTR getChar() { return (LPCSTR)(int)value; }

    LPCWSTR getWchar() { return (LPCWSTR)(int)value; }

    LPCTSTR getTchar() { return (LPCTSTR)(int)value; }

    std::string* getString() { return (std::string*)(int)value; }

    std::wstring* getWstring() { return (std::wstring*)(int)value; }

    void* getVoidPtr() { return (void*)(int)value; }

    void* getVoidPtrPtr() { return (void*)(int)value; }

    void setValue(LPCSTR v, LPCSTR s)
    {
        if (NULL == v) return;

        size =  (NULL == s) ? strlen(v) + 1 : atoi(s);

        valueStr = new TCHAR[size];
        _tcscpy_s(valueStr, size, A2T((LPSTR)v));
    }

    void updateData()
    {
        USES_CONVERSION;

        switch(type)
        {
        case PARAM_INT:
            {
                value = atoi(valueStr);
                delete valueStr;
                valueStr = NULL;
                break;
            }
        case PARAM_FLOAT:
        case PARAM_DOUBLE:
            {
                value = atof(valueStr);
                delete valueStr;
                valueStr = NULL;
                break;
            }
        case PARAM_CAHR:
            {
                char *p = new char[size];
                strcpy(p, T2A(valueStr));
                value = (int)p;
                delete valueStr;
                valueStr = NULL;
                break;
            }
        case PARAM_WCHAR:
            {
                wchar_t *p = new wchar_t[size];
                wcscpy(p, T2W(valueStr));
                value = (int)p;
                delete valueStr;
                valueStr = NULL;
                break;
            }
        case PARAM_TCHAR:
            {
                TCHAR *p = new TCHAR[size];
                _tcscpy(p, valueStr);
                value = (int)p;
                delete valueStr;
                valueStr = NULL;
                break;
            }
        case PARAM_STD_STRING:
            {
                std::string *str = new std::string(T2A(valueStr));
                value = (int)str;
                delete valueStr;
                valueStr = NULL;
                break;
            }
        case PARAM_STD_WSTRING:
            {
                std::wstring *str = new std::wstring(T2W(valueStr));
                value = (int)str;
                delete valueStr;
                valueStr = NULL;
                break;
            }
        case PARAM_VOID_PTR_PTR:
        case PARAM_VOID_PTR:
            {
                value = (0 == _tcscmp(valueStr, _T("NULL"))) ? NULL : atoi(valueStr);
                delete valueStr;
                valueStr = NULL;
                break;
            }
        }
    }

    void setName(LPCSTR n)
    {
        if (NULL == n) return;

        USES_CONVERSION;
        _tcscpy_s(name, ARRAYSIZE(name), A2T((LPSTR)n));
    }

    void setInput(LPCSTR i)
    {
        if (NULL == i) return;

        input = (0 == strcmp(i, "true"));
    }

    void setType(LPCSTR t)
    {
        if (NULL == t) return;

        if (0 == strcmp(t, _T("PARAM_INT")))
            type = PARAM_INT;
        else if (0 == strcmp(t, "PARAM_FLOAT"))
            type = PARAM_FLOAT;
        else if (0 == strcmp(t, "PARAM_DOUBLE"))
            type = PARAM_DOUBLE;
        else if (0 == strcmp(t, "PARAM_TCHAR"))
            type = PARAM_TCHAR;
        else if (0 == strcmp(t, "PARAM_CAHR"))
            type = PARAM_CAHR;
        else if (0 == strcmp(t, "PARAM_WCHAR"))
            type = PARAM_WCHAR;
        else if (0 == strcmp(t, "PARAM_STD_STRING"))
            type = PARAM_STD_STRING;
        else if (0 == strcmp(t, "PARAM_STD_WSTRING"))
            type = PARAM_STD_WSTRING;
        else if (0 == strcmp(t, "PARAM_VOID_PTR"))
            type = PARAM_VOID_PTR;
        else if (0 == strcmp(t, "PARAM_VOID_PTR_PTR"))
            type = PARAM_VOID_PTR_PTR;
        else
            type = PARAM_INT;
    }

    _tagParam::_tagParam()
    {
        name[0] = _T('\0');
        typeStr[0] = _T('\0');
        valueStr = NULL;
        type = 0;
        size = 0;
        input = true;
        value = 0.0;
    }

    _tagParam::~_tagParam()
    {
        switch(type)
        {
        case PARAM_CAHR:
            {
                LPCSTR p = getChar();
                delete p;
                break;
            }
        case PARAM_WCHAR:
            {
                LPCWSTR p = getWchar();
                delete p;
                break;
            }
        case PARAM_TCHAR:
            {
                LPCTSTR p = getTchar();
                delete p;
                break;
            }
        case PARAM_STD_STRING:
            {
                std::string *p = getString();
                delete p;
                break;
            }
        case PARAM_STD_WSTRING:
            {
                std::wstring *p = getWstring();
                delete p;
                break;
            }
        }
    }

    TCHAR name[MAX_PATH];
    TCHAR typeStr[MAX_PATH];
    TCHAR *valueStr;

    int size;
    int type;
    bool input;
    double value;

}PARAM, *PPARAM;

typedef std::list<PARAM*> PARM_LIST;
typedef std::map<std::string, PARAM*> PARAM_MAP;

typedef struct _tagStep
{
    _tagStep::_tagStep()
    {
        func[0] = '\0';
        dll[0] = _T('\0');
        url[0] = _T('\0');
        paramList.clear();
    }

    void setFunc(LPCSTR f)
    {
        //USES_CONVERSION;
        //_tcscpy_s(func, ARRAYSIZE(func), A2T((LPSTR)f));
        strcpy(func, f);
    }

    void setDll(LPCSTR d)
    {
        USES_CONVERSION;
        _tcscpy_s(dll, ARRAYSIZE(dll), A2T((LPSTR)d));
    }

    void setUrl(LPCSTR u)
    {
        USES_CONVERSION;
        _tcscpy_s(url, ARRAYSIZE(url), A2T((LPSTR)u));
    }

    void setRetName(LPCSTR n)
    {
       ret.setName(n);
    }

    void setRetType(LPCSTR t)
    {
        ret.setType(t);
    }

    char func[MAX_PATH];
    TCHAR dll[MAX_PATH];
    TCHAR url[MAX_PATH];

    PARAM ret;
    PARM_LIST paramList;

}STEP, *PSTEP;

typedef std::list<STEP*> STEP_LIST;

//-----------------------------------------------------

class ScriptParam
{
public:
    ScriptParam();
    ~ScriptParam();

protected:
    PARAM_MAP scriptParam_;

public:
    PARAM* getParam(LPCTSTR name);
    void setParam(LPCTSTR name, PARAM *value);
};