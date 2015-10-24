

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for localagent.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __localagent_h__
#define __localagent_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMEncoderNamesCollection_FWD_DEFINED__
#define __IWMEncoderNamesCollection_FWD_DEFINED__
typedef interface IWMEncoderNamesCollection IWMEncoderNamesCollection;
#endif 	/* __IWMEncoderNamesCollection_FWD_DEFINED__ */


#ifndef __IWMEncoderAgent_FWD_DEFINED__
#define __IWMEncoderAgent_FWD_DEFINED__
typedef interface IWMEncoderAgent IWMEncoderAgent;
#endif 	/* __IWMEncoderAgent_FWD_DEFINED__ */


#ifndef __IWMEncoderNamesCollection_FWD_DEFINED__
#define __IWMEncoderNamesCollection_FWD_DEFINED__
typedef interface IWMEncoderNamesCollection IWMEncoderNamesCollection;
#endif 	/* __IWMEncoderNamesCollection_FWD_DEFINED__ */


#ifndef __WMEncoderAgent_FWD_DEFINED__
#define __WMEncoderAgent_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncoderAgent WMEncoderAgent;
#else
typedef struct WMEncoderAgent WMEncoderAgent;
#endif /* __cplusplus */

#endif 	/* __WMEncoderAgent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_localagent_0000 */
/* [local] */ 

EXTERN_GUID( CLSID_WMEncoderNamesCollection,    0xC728738A, 0xC81C, 0x4CDB, 0xBD, 0x92, 0x6B, 0x7A, 0xBF, 0x4C, 0xF3, 0xF0 );
EXTERN_GUID( IID_IWMEncoderAgent,               0x00BB9AE0, 0xA7B8, 0x4966, 0x93, 0x7D, 0x6A, 0xED, 0x09, 0x2E, 0x7E, 0x4F );
EXTERN_GUID( CLSID_WMEncoderAgent,              0xB6913798, 0x10BF, 0x430C, 0xA2, 0x6F, 0xE6, 0xDE, 0xE2, 0x2E, 0xB9, 0xBA );
EXTERN_GUID( LIBID_WMEncAgtLib,                 0xD9655475, 0x53BD, 0x431C, 0xB2, 0x2F, 0xCC, 0x98, 0xBC, 0xE3, 0x30, 0x82 );
EXTERN_GUID( IID_IWMEncoderNamesCollection,     0x8EE540F8, 0xDEF6, 0x4D3E, 0xA2, 0xC3, 0x22, 0x67, 0xB1, 0x0B, 0x7F, 0x54 );


extern RPC_IF_HANDLE __MIDL_itf_localagent_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_localagent_0000_v0_0_s_ifspec;

#ifndef __IWMEncoderNamesCollection_INTERFACE_DEFINED__
#define __IWMEncoderNamesCollection_INTERFACE_DEFINED__

/* interface IWMEncoderNamesCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncoderNamesCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8EE540F8-DEF6-4D3E-A2C3-2267B10B7F54")
    IWMEncoderNamesCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long iIndex,
            /* [retval][out] */ BSTR *pbstrValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncoderNamesCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncoderNamesCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncoderNamesCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncoderNamesCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncoderNamesCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncoderNamesCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncoderNamesCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncoderNamesCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncoderNamesCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncoderNamesCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncoderNamesCollection * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncoderNamesCollection * This,
            /* [in] */ long iIndex,
            /* [retval][out] */ BSTR *pbstrValue);
        
        END_INTERFACE
    } IWMEncoderNamesCollectionVtbl;

    interface IWMEncoderNamesCollection
    {
        CONST_VTBL struct IWMEncoderNamesCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncoderNamesCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncoderNamesCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncoderNamesCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncoderNamesCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncoderNamesCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncoderNamesCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncoderNamesCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncoderNamesCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncoderNamesCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncoderNamesCollection_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncoderNamesCollection_Item(This,iIndex,pbstrValue)	\
    (This)->lpVtbl -> Item(This,iIndex,pbstrValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderNamesCollection_get_length_Proxy( 
    IWMEncoderNamesCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncoderNamesCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderNamesCollection_get_Count_Proxy( 
    IWMEncoderNamesCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncoderNamesCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderNamesCollection_get__NewEnum_Proxy( 
    IWMEncoderNamesCollection * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncoderNamesCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderNamesCollection_Item_Proxy( 
    IWMEncoderNamesCollection * This,
    /* [in] */ long iIndex,
    /* [retval][out] */ BSTR *pbstrValue);


void __RPC_STUB IWMEncoderNamesCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncoderNamesCollection_INTERFACE_DEFINED__ */


#ifndef __IWMEncoderAgent_INTERFACE_DEFINED__
#define __IWMEncoderAgent_INTERFACE_DEFINED__

/* interface IWMEncoderAgent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncoderAgent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00BB9AE0-A7B8-4966-937D-6AED092E7E4F")
    IWMEncoderAgent : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateEncoder( 
            /* [in] */ BSTR bstrEncoderName,
            /* [optional][in] */ VARIANT varEncoderProgId,
            /* [retval][out] */ IDispatch **ppDispApp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEncoder( 
            /* [in] */ BSTR name,
            /* [retval][out] */ IDispatch **ppDispEncoder) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderNamesCollection( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Register( 
            /* [in] */ BSTR bstrName,
            /* [in] */ IDispatch *pUnkEncoder,
            /* [retval][out] */ DWORD *pdwCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnRegister( 
            /* [in] */ DWORD dwCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncoderAgentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncoderAgent * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncoderAgent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncoderAgent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncoderAgent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncoderAgent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncoderAgent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncoderAgent * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateEncoder )( 
            IWMEncoderAgent * This,
            /* [in] */ BSTR bstrEncoderName,
            /* [optional][in] */ VARIANT varEncoderProgId,
            /* [retval][out] */ IDispatch **ppDispApp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEncoder )( 
            IWMEncoderAgent * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ IDispatch **ppDispEncoder);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EncoderNamesCollection )( 
            IWMEncoderAgent * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Register )( 
            IWMEncoderAgent * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ IDispatch *pUnkEncoder,
            /* [retval][out] */ DWORD *pdwCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnRegister )( 
            IWMEncoderAgent * This,
            /* [in] */ DWORD dwCookie);
        
        END_INTERFACE
    } IWMEncoderAgentVtbl;

    interface IWMEncoderAgent
    {
        CONST_VTBL struct IWMEncoderAgentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncoderAgent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncoderAgent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncoderAgent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncoderAgent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncoderAgent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncoderAgent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncoderAgent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncoderAgent_CreateEncoder(This,bstrEncoderName,varEncoderProgId,ppDispApp)	\
    (This)->lpVtbl -> CreateEncoder(This,bstrEncoderName,varEncoderProgId,ppDispApp)

#define IWMEncoderAgent_GetEncoder(This,name,ppDispEncoder)	\
    (This)->lpVtbl -> GetEncoder(This,name,ppDispEncoder)

#define IWMEncoderAgent_get_EncoderNamesCollection(This,pVal)	\
    (This)->lpVtbl -> get_EncoderNamesCollection(This,pVal)

#define IWMEncoderAgent_Register(This,bstrName,pUnkEncoder,pdwCookie)	\
    (This)->lpVtbl -> Register(This,bstrName,pUnkEncoder,pdwCookie)

#define IWMEncoderAgent_UnRegister(This,dwCookie)	\
    (This)->lpVtbl -> UnRegister(This,dwCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderAgent_CreateEncoder_Proxy( 
    IWMEncoderAgent * This,
    /* [in] */ BSTR bstrEncoderName,
    /* [optional][in] */ VARIANT varEncoderProgId,
    /* [retval][out] */ IDispatch **ppDispApp);


void __RPC_STUB IWMEncoderAgent_CreateEncoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderAgent_GetEncoder_Proxy( 
    IWMEncoderAgent * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ IDispatch **ppDispEncoder);


void __RPC_STUB IWMEncoderAgent_GetEncoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderAgent_get_EncoderNamesCollection_Proxy( 
    IWMEncoderAgent * This,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB IWMEncoderAgent_get_EncoderNamesCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderAgent_Register_Proxy( 
    IWMEncoderAgent * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ IDispatch *pUnkEncoder,
    /* [retval][out] */ DWORD *pdwCookie);


void __RPC_STUB IWMEncoderAgent_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderAgent_UnRegister_Proxy( 
    IWMEncoderAgent * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IWMEncoderAgent_UnRegister_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncoderAgent_INTERFACE_DEFINED__ */



#ifndef __WMEncAgtLib_LIBRARY_DEFINED__
#define __WMEncAgtLib_LIBRARY_DEFINED__

/* library WMEncAgtLib */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_WMEncAgtLib;

EXTERN_C const CLSID CLSID_WMEncoderAgent;

#ifdef __cplusplus

class DECLSPEC_UUID("B6913798-10BF-430C-A26F-E6DEE22EB9BA")
WMEncoderAgent;
#endif
#endif /* __WMEncAgtLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


