#include "StdAfx.h"
#include ".\sink.h"

CSink::CSink(void)
: m_pEdit(NULL)
{
}

CSink::~CSink(void)
{
}

void CSink::SetResultWnd(CEdit * pEdit)
{
	m_pEdit = pEdit;
}

// STDMETHODIMP 是宏，等价于 long __stdcall
STDMETHODIMP CSink::QueryInterface(const struct _GUID &iid,void ** ppv)
{
	*ppv=this;
	return S_OK;
}

ULONG __stdcall CSink::AddRef(void)
{	return 1;	}	// 做个假的就可以，因为反正这个对象在程序结束前是不会退出的

ULONG __stdcall CSink::Release(void)
{	return 0;	}	// 做个假的就可以，因为反正这个对象在程序结束前是不会退出的

STDMETHODIMP CSink::GetTypeInfoCount(unsigned int *)
{	return E_NOTIMPL;	}	// 不用实现，反正也不用

STDMETHODIMP CSink::GetTypeInfo(unsigned int,unsigned long,struct ITypeInfo ** )
{	return E_NOTIMPL;	}	// 不用实现，反正也不用

STDMETHODIMP CSink::GetIDsOfNames(const IID &,LPOLESTR *,UINT,LCID,DISPID *)
{	return E_NOTIMPL;	}	// 不用实现，反正也不用

STDMETHODIMP CSink::Invoke(
				long dispID,
				const struct _GUID &,
				unsigned long,
				unsigned short,
				struct tagDISPPARAMS * pParams,
				struct tagVARIANT *,
				struct tagEXCEPINFO *,
				unsigned int *)
{							// 只需要实现这个就足够啦
	switch(dispID)
	{
	case 1:	//根据不同的dispID,完成不同的回调函数
		if( !m_pEdit )
		{
			AfxMessageBox( _T("没有调用 SetResultWnd() 设置显示结果的窗口") );
		}
		else
		{
			CString str;
			str.Format( _T("%d"), pParams->rgvarg[0].lVal );
			m_pEdit->SetWindowText( str );
		}
		break;
	default:
		AfxMessageBox( _T("怎么可能，根本就没有这个号码的函数呀") );
		break;
	}
	return S_OK;
}
