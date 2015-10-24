#include "StdAfx.h"
#include ".\sink.h"


/*
在COM组件的 连接点中添加函数Fire_OpenFile()，COM中的其它都可以直接调用Fire_OpenFile()
客户端需要CSink类

1,如果要用到连接点(connect point), 新建工程时，就不要选中属性化，要选中代理和存根
2,添加ATL简单对象，或ATL控件时，要选中连接点

ATL的com对象在用网页调用时，是有鼠标点击事件的，但如果用RichEdit2加载就不会有鼠标点击事件


template <class T>
class CProxy_IFileTransEvents : public IConnectionPointImpl<T, &__uuidof(_IFileTransEvents), CComDynamicUnkArray>
{
	//警告此类将由向导重新生成。
public:

	HRESULT Fire_OpenFile(BSTR bstrFileName)
	{
		HRESULT hr = S_OK;
		T * pThis = static_cast<T *>(this);
		int nConnections = m_vec.GetSize();

		for (int iConnection = 0; iConnection < nConnections; iConnection++)
		{
			pThis->Lock();
			CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
			pThis->Unlock();

			IDispatch * pConnection = static_cast<IDispatch *>(punkConnection.p);

			if (pConnection)
			{
				CComVariant varResult;
				CComVariant avarParams[1];
				avarParams[0].vt = VT_BSTR;
				avarParams[0].bstrVal = bstrFileName;
				DISPPARAMS params = { avarParams, NULL, 1, 0 };

				hr = pConnection->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &varResult, NULL, NULL);
			}
		}
		return E_NOTIMPL;
	}
};
*/


CSink::CSink(void)
    :m_dwRef(0),
    m_pevComplete(NULL),
    m_plErrorCode(NULL)
{
}

CSink::~CSink(void)
{
    m_dwRef--;
}

void CSink::SetParam(CEvent *pevComplete, LONG *plErrorCode)
{
    m_pevComplete = pevComplete;
    m_plErrorCode = plErrorCode;
}

// STDMETHODIMP 是宏，等价于 long __stdcall
STDMETHODIMP CSink::QueryInterface(const struct _GUID &iid,void ** ppv)
{
    if (!ppv) return E_POINTER;

    *ppv = NULL;
    if (IsEqualIID(iid, __uuidof(IDispatch)) || IsEqualIID(iid, __uuidof(IUnknown)))
    {
        *ppv = (IDispatch *)this;
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

ULONG __stdcall CSink::AddRef(void)
{
    return ++m_dwRef;
}

ULONG __stdcall CSink::Release(void)
{
    if (--m_dwRef) return m_dwRef;
    //	delete this;
    return 0;
}

STDMETHODIMP CSink::GetTypeInfoCount(unsigned int *)
{ return E_NOTIMPL;	}	// 不用实现，反正也不用

STDMETHODIMP CSink::GetTypeInfo(unsigned int,unsigned long,struct ITypeInfo **)
{ return E_NOTIMPL;	}	// 不用实现，反正也不用

STDMETHODIMP CSink::GetIDsOfNames(const IID &,LPOLESTR *,UINT,LCID,DISPID *)
{ return E_NOTIMPL; }	// 不用实现，反正也不用

STDMETHODIMP CSink::Invoke(long dispID,
                           const struct _GUID &,
                           unsigned long,
                           unsigned short,
                           DISPPARAMS * pParams,
                           VARIANT *,
                           EXCEPINFO *,
                           unsigned int *)
{
    if (NULL == this)
        return S_OK;

    try
    {
        TRACE(_T("%d\n"), dispID);

        if (dispID == 271)	// DISPID_NAVIGATEERROR
        {
            VARIANT StatusCode = *((pParams->rgvarg[1]).pvarVal);

            if (StatusCode.lVal == -2146697211)
                *m_plErrorCode = 3;
            else
                *m_plErrorCode = StatusCode.lVal;

            m_pevComplete->SetEvent();

            char buf[200];
            sprintf(buf, "Navigate Error, code is: %d\n", StatusCode.lVal);//static_cast<int>(StatusCode.lVal));
            TRACE(buf);		
        }
        else if(dispID == 259)	// DISPID_DOCUMENTCOMPLETE
        {
            m_plErrorCode = 0;
            m_pevComplete->SetEvent();
        }
    }
    catch (...)
    {
        TRACE(_T("sink error %d\n"), ::GetLastError());
    }

    return S_OK;
}
