#pragma once
#include "oaidl.h"

class CSink :
	public IDispatch
{
public:
	CSink(void);
	~CSink(void);
private:
	CEdit *m_pEdit;
public:
	void SetResultWnd(CEdit * pEdit);
// IUnknown
	STDMETHOD(QueryInterface)(const struct _GUID &iid,void ** ppv);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
// IDispatch
	STDMETHOD(GetTypeInfoCount)(unsigned int *);
	STDMETHOD(GetTypeInfo)(unsigned int,unsigned long,struct ITypeInfo ** );
	STDMETHOD(GetIDsOfNames)(const IID &,LPOLESTR *,UINT,LCID,DISPID *);
	STDMETHOD(Invoke)(long dispID,const struct _GUID &,unsigned long,unsigned short,struct tagDISPPARAMS * pParams,struct tagVARIANT *,struct tagEXCEPINFO *,unsigned int *);
};
