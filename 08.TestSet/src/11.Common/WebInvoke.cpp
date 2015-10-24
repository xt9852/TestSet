// WebInvoke.cpp : 实现文件
//

#include "stdafx.h"
#include "WebInvoke.h"
#include <WinInet.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CWebInvoke::CWebInvoke()
    :m_lErrorCode(0)
{
}

CWebInvoke::~CWebInvoke()
{	
}

DWORD CWebInvoke::OpenUrl(LPCSTR strUrl, LPSTR strProxy, DWORD dwTime)
{
    try
    {
        IID		iidEvents = { 0x34a715a0, 0x6587, 0x11d0, { 0x92, 0x4a, 0x00, 0x20, 0xaf, 0xc7, 0xac, 0x4d }};
        DWORD	dwCookie;	// 连接的 cookie
        m_lErrorCode = 0;

        SetProxy(strProxy);

        m_evComplete.ResetEvent();

        m_sink.SetParam(&m_evComplete, &m_lErrorCode);	

        ::CoInitialize(NULL);

        CComPtr<IWebBrowser2> ptrWebBrowser; 
        ptrWebBrowser.CoCreateInstance(L"InternetExplorer.Application.1");
        if (ptrWebBrowser == 0) 
        { 
            TRACE(_T("com interface failed... %d\n"), ::GetLastError());
            return 1;
        }

        CComQIPtr<IConnectionPoint> spCP;
        CComQIPtr<IConnectionPointContainer> spContainer(ptrWebBrowser);
        if (!spContainer)
        {
            TRACE(_T("组件没有提供连接点功能 %d\n"), ::GetLastError());
            return 1;
        }
        else if (!spCP)
        {
            // 得到连接点接口
            spContainer->FindConnectionPoint(iidEvents, &spCP);
            if (!spCP)
            {
                TRACE(_T("没有找到连接点接口 %d\n"), ::GetLastError());
                return 1;
            }
            else
            {
                HRESULT hr = spCP->Advise(reinterpret_cast<IDispatch*>(&m_sink), &dwCookie);
                if (FAILED(hr))
                {
                    TRACE(_T("连接失败 %d\n"), ::GetLastError());
                    return 1;
                }
            }
        }

        USES_CONVERSION;

        VARIANT vUrl;
        VARIANT vNULL;
        ::VariantInit(&vUrl);
        ::VariantInit(&vNULL);
        vUrl.vt = VT_BSTR;
        vUrl.bstrVal = SysAllocString(T2W(strUrl));
        vNULL.vt = VT_BSTR;
        vNULL.bstrVal = SysAllocString(L"");

        ptrWebBrowser->put_Visible(true); 
        ptrWebBrowser->Navigate2(&vUrl, &vNULL, &vNULL, &vNULL, &vNULL);

        //		spCP.Release();
        //		spContainer.Release();
        //		ptrWebBrowser.Release();

        ::VariantClear(&vUrl);
        ::VariantClear(&vNULL);

        MSG msg;
        while (!m_evComplete.Lock(1))
        {
            if (--dwTime == 0)
            {
                ptrWebBrowser->put_Visible(false); 
                m_lErrorCode = 2;
                break;
            }

            if (::GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                Sleep(1);
            }
        }

        UnenableProxy();
    }
    catch (...)
    {
        TRACE(_T("OpenUrl error %d\n"), ::GetLastError());
    }

    return m_lErrorCode;
}


void CWebInvoke::SetProxy(LPCSTR pszProxy)
{
    if (NULL == pszProxy || 0 == strcmp("", pszProxy))
        return;

    DWORD dwEnable = 1;
    HKEY hk = NULL;
    LONG lret = RegOpenKeyEx(HKEY_CURRENT_USER,
        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"),
        NULL,KEY_WRITE|KEY_SET_VALUE,&hk);
    if (lret == ERROR_SUCCESS && NULL != hk)
    {
        lret = RegSetValueEx(hk, _T("ProxyServer"), NULL, REG_SZ, (LPBYTE)pszProxy, (DWORD)strlen(pszProxy));
        lret = RegSetValueEx(hk, _T("ProxyEnable"), NULL, REG_DWORD, (LPBYTE)&dwEnable, sizeof(dwEnable));
        RegCloseKey(hk);

        if (!InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0))
            TRACE("InternetQueryOption failed! (%d)\n", GetLastError());

        if (!InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0))
            TRACE("InternetQueryOption failed! (%d)\n", GetLastError());
    }
}
void CWebInvoke::UnenableProxy(void)
{
    DWORD dwEnable = 0;
    HKEY hk = NULL;
    LONG lret = RegOpenKeyEx(HKEY_CURRENT_USER,
        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"),
        NULL,KEY_WRITE|KEY_SET_VALUE,&hk);
    if (lret == ERROR_SUCCESS && NULL != hk)
    {
        lret = RegSetValueEx(hk, _T("ProxyEnable"), NULL, REG_DWORD, (LPBYTE)&dwEnable, sizeof(dwEnable));
        RegCloseKey(hk);

        if (!InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0))
            TRACE("InternetQueryOption failed! (%d)\n", GetLastError());

        if (!InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0))
            TRACE("InternetQueryOption failed! (%d)\n", GetLastError());
    }
}


