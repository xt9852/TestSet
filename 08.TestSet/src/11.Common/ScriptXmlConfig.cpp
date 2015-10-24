#include "stdafx.h"
#include "ScriptXmlConfig.h"


ScriptXmlConfig::ScriptXmlConfig()
{
    stepList_.clear();
}

ScriptXmlConfig::~ScriptXmlConfig()
{
}

bool ScriptXmlConfig::OpenFile(LPCTSTR filename)
{
    USES_CONVERSION;
    
    XT_XML::xml xml_;

    bool bRet = xml_.LoadFile(T2A((LPTSTR)filename));

    if (bRet)
    {
        XT_XML::TiXmlElementEx *scriptElement = xml_.GetRoot()->SelectSingleNode("Script");

        if (NULL == scriptElement) return false;

        LPCSTR name = scriptElement->Attribute("name");
        LPCSTR desc = scriptElement->Attribute("desc");
        _tcscpy_s(name_, ARRAYSIZE(name_), A2T((LPTSTR)name));
        _tcscpy_s(desc_, ARRAYSIZE(desc_), A2T((LPTSTR)desc));

		XT_XML::TiXmlElementExs stepElements = scriptElement->SelectNodes("Step");

        for (int i = 0; i < stepElements.getCount(); i++)
        {
            LPCSTR func = stepElements[i]->Attribute("func");
            LPCSTR dll = stepElements[i]->Attribute("dll");
            LPCSTR url = stepElements[i]->Attribute("url");
            LPCSTR ret = stepElements[i]->Attribute("return");
            LPCSTR type = stepElements[i]->Attribute("type");

            STEP *step = new STEP;
            step->setFunc(func);
            step->setDll(dll);
            step->setUrl(url);
            step->setRetName(ret);
            step->setRetType(type);

            XT_XML::TiXmlElementExs paramElements = stepElements[i]->SelectNodes("Param");

            for (int j = 0; j < paramElements.getCount(); j++)
            {
                LPCSTR name = paramElements[j]->Attribute("name");
                LPCSTR type = paramElements[j]->Attribute("type");
                LPCSTR size = paramElements[j]->Attribute("size");
                LPCSTR value = paramElements[j]->Attribute("value");
                LPCSTR input = paramElements[j]->Attribute("input");

                PARAM *param = new PARAM;
                param->setName(name);
                param->setType(type);
                param->setInput(input);
                param->setValue(value, size);

                step->paramList.push_back(param);
            }

            stepList_.push_back(step);
        }
    }

    return bRet;
}

