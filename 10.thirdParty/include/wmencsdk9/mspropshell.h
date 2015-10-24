

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for mspropshell.idl:
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

#ifndef __mspropshell_h__
#define __mspropshell_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMSPropShell_FWD_DEFINED__
#define __IMSPropShell_FWD_DEFINED__
typedef interface IMSPropShell IMSPropShell;
#endif 	/* __IMSPropShell_FWD_DEFINED__ */


#ifndef __IMSPropShellEvents2_FWD_DEFINED__
#define __IMSPropShellEvents2_FWD_DEFINED__
typedef interface IMSPropShellEvents2 IMSPropShellEvents2;
#endif 	/* __IMSPropShellEvents2_FWD_DEFINED__ */


#ifndef __IWMEncPageProp_FWD_DEFINED__
#define __IWMEncPageProp_FWD_DEFINED__
typedef interface IWMEncPageProp IWMEncPageProp;
#endif 	/* __IWMEncPageProp_FWD_DEFINED__ */


#ifndef __IMSPropPage_FWD_DEFINED__
#define __IMSPropPage_FWD_DEFINED__
typedef interface IMSPropPage IMSPropPage;
#endif 	/* __IMSPropPage_FWD_DEFINED__ */


#ifndef __IMSPropPageSite_FWD_DEFINED__
#define __IMSPropPageSite_FWD_DEFINED__
typedef interface IMSPropPageSite IMSPropPageSite;
#endif 	/* __IMSPropPageSite_FWD_DEFINED__ */


#ifndef ___IMSPropShellEvents_FWD_DEFINED__
#define ___IMSPropShellEvents_FWD_DEFINED__
typedef interface _IMSPropShellEvents _IMSPropShellEvents;
#endif 	/* ___IMSPropShellEvents_FWD_DEFINED__ */


#ifndef __MSPropShell_FWD_DEFINED__
#define __MSPropShell_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSPropShell MSPropShell;
#else
typedef struct MSPropShell MSPropShell;
#endif /* __cplusplus */

#endif 	/* __MSPropShell_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_mspropshell_0000 */
/* [local] */ 

EXTERN_GUID( LIBID_MSPROPSHELLLib,      0xC4941F47, 0x8BC1, 0x49D3, 0x99, 0x89, 0x2B, 0x78, 0x26, 0xF2, 0x6A, 0xE6 );
EXTERN_GUID( DIID__IMSPropShellEvents,  0xDF8AD1EA, 0xFCAA, 0x4455, 0x87, 0x72, 0xB4, 0xF5, 0x39, 0x48, 0x8E, 0xE3 );
EXTERN_GUID( IID_IMSPropShellEvents2,  0x48b22f5f, 0xdcad, 0x4b7c, 0xb1, 0x3c, 0xc4, 0x8b, 0x45, 0x9c, 0xe2, 0xe8);
EXTERN_GUID( CLSID_MSPropShell,         0xE297AB5E, 0x40B0, 0x41BD, 0x9E, 0x06, 0xE4, 0x14, 0x40, 0x84, 0xEE, 0x5F );
EXTERN_GUID( IID_IMSPropShell,          0x119338AA, 0xF278, 0x47CC, 0x9F, 0x88, 0x50, 0x0E, 0x86, 0x51, 0x0B, 0x66 );
EXTERN_GUID( IID_IMSPropPage,           0x24DB76A0, 0x2A25, 0x48BE, 0xB4, 0x0B, 0x67, 0xC0, 0x99, 0x63, 0x61, 0x4C );
EXTERN_GUID( IID_IMSPropPageSite,       0x8E849609, 0xC7E8, 0x4EC7, 0x8B, 0xD3, 0xD5, 0x5E, 0x87, 0x1A, 0x34, 0x0D );
EXTERN_GUID( IID_IWMEncPageProp,       0xec74c5c1, 0xd214, 0x4fdd, 0x81, 0xc3, 0xa5, 0x84, 0x3e, 0x57, 0xaa, 0xcb);
typedef /* [helpstring][uuid] */  DECLSPEC_UUID("C3003841-7A40-4091-8B96-996910610EB9") 
enum PSSTYLE
    {	pssNoTabs	= 0,
	pssTabsTop	= 0x1,
	pssTabsBottom	= 0x2
    } 	PSSTYLE;



extern RPC_IF_HANDLE __MIDL_itf_mspropshell_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mspropshell_0000_v0_0_s_ifspec;

#ifndef __IMSPropShell_INTERFACE_DEFINED__
#define __IMSPropShell_INTERFACE_DEFINED__

/* interface IMSPropShell */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMSPropShell;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("119338AA-F278-47CC-9F88-500E86510B66")
    IMSPropShell : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPage( 
            /* [in] */ LPUNKNOWN pUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPage( 
            /* [in] */ long Index,
            /* [retval][out] */ LPUNKNOWN *ppUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllPages( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddObject( 
            /* [in] */ LPUNKNOWN pUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllObjects( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoRefresh( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoRefresh( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageIndex( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PageIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ PSSTYLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ PSSTYLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocaleID( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocaleID( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ApplyIndex( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InitNew( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InitNew( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TabWidth( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TabWidth( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageTitle( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *pbstrTitle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageHasHelp( 
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowPageHelp( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDirty( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsDirty( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetBag( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetBagFromEngine( 
            /* [in] */ VARIANT_BOOL fForce) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Validate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyProperty( 
            /* [in] */ long lIDRecepient,
            /* [in] */ BSTR bstrValue,
            /* [in] */ long lParam1,
            /* [in] */ VARIANT var) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSPropShellVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSPropShell * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSPropShell * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSPropShell * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMSPropShell * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMSPropShell * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMSPropShell * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMSPropShell * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddPage )( 
            IMSPropShell * This,
            /* [in] */ LPUNKNOWN pUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPage )( 
            IMSPropShell * This,
            /* [in] */ long Index,
            /* [retval][out] */ LPUNKNOWN *ppUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllPages )( 
            IMSPropShell * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddObject )( 
            IMSPropShell * This,
            /* [in] */ LPUNKNOWN pUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllObjects )( 
            IMSPropShell * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Apply )( 
            IMSPropShell * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IMSPropShell * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PageCount )( 
            IMSPropShell * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoRefresh )( 
            IMSPropShell * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoRefresh )( 
            IMSPropShell * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PageIndex )( 
            IMSPropShell * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PageIndex )( 
            IMSPropShell * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            IMSPropShell * This,
            /* [retval][out] */ PSSTYLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            IMSPropShell * This,
            /* [in] */ PSSTYLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocaleID )( 
            IMSPropShell * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocaleID )( 
            IMSPropShell * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ApplyIndex )( 
            IMSPropShell * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InitNew )( 
            IMSPropShell * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitNew )( 
            IMSPropShell * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TabWidth )( 
            IMSPropShell * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TabWidth )( 
            IMSPropShell * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PageTitle )( 
            IMSPropShell * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *pbstrTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PageHasHelp )( 
            IMSPropShell * This,
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowPageHelp )( 
            IMSPropShell * This,
            /* [in] */ long Index);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsDirty )( 
            IMSPropShell * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsDirty )( 
            IMSPropShell * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetBag )( 
            IMSPropShell * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetBagFromEngine )( 
            IMSPropShell * This,
            /* [in] */ VARIANT_BOOL fForce);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IMSPropShell * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IMSPropShell * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Validate )( 
            IMSPropShell * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ModifyProperty )( 
            IMSPropShell * This,
            /* [in] */ long lIDRecepient,
            /* [in] */ BSTR bstrValue,
            /* [in] */ long lParam1,
            /* [in] */ VARIANT var);
        
        END_INTERFACE
    } IMSPropShellVtbl;

    interface IMSPropShell
    {
        CONST_VTBL struct IMSPropShellVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSPropShell_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSPropShell_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSPropShell_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSPropShell_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMSPropShell_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMSPropShell_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMSPropShell_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMSPropShell_AddPage(This,pUnknown)	\
    (This)->lpVtbl -> AddPage(This,pUnknown)

#define IMSPropShell_GetPage(This,Index,ppUnknown)	\
    (This)->lpVtbl -> GetPage(This,Index,ppUnknown)

#define IMSPropShell_RemoveAllPages(This)	\
    (This)->lpVtbl -> RemoveAllPages(This)

#define IMSPropShell_AddObject(This,pUnknown)	\
    (This)->lpVtbl -> AddObject(This,pUnknown)

#define IMSPropShell_RemoveAllObjects(This)	\
    (This)->lpVtbl -> RemoveAllObjects(This)

#define IMSPropShell_Apply(This)	\
    (This)->lpVtbl -> Apply(This)

#define IMSPropShell_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IMSPropShell_get_PageCount(This,pVal)	\
    (This)->lpVtbl -> get_PageCount(This,pVal)

#define IMSPropShell_get_AutoRefresh(This,pVal)	\
    (This)->lpVtbl -> get_AutoRefresh(This,pVal)

#define IMSPropShell_put_AutoRefresh(This,newVal)	\
    (This)->lpVtbl -> put_AutoRefresh(This,newVal)

#define IMSPropShell_get_PageIndex(This,pVal)	\
    (This)->lpVtbl -> get_PageIndex(This,pVal)

#define IMSPropShell_put_PageIndex(This,newVal)	\
    (This)->lpVtbl -> put_PageIndex(This,newVal)

#define IMSPropShell_get_Style(This,pVal)	\
    (This)->lpVtbl -> get_Style(This,pVal)

#define IMSPropShell_put_Style(This,newVal)	\
    (This)->lpVtbl -> put_Style(This,newVal)

#define IMSPropShell_get_LocaleID(This,pVal)	\
    (This)->lpVtbl -> get_LocaleID(This,pVal)

#define IMSPropShell_put_LocaleID(This,newVal)	\
    (This)->lpVtbl -> put_LocaleID(This,newVal)

#define IMSPropShell_get_ApplyIndex(This,pVal)	\
    (This)->lpVtbl -> get_ApplyIndex(This,pVal)

#define IMSPropShell_get_InitNew(This,pVal)	\
    (This)->lpVtbl -> get_InitNew(This,pVal)

#define IMSPropShell_put_InitNew(This,newVal)	\
    (This)->lpVtbl -> put_InitNew(This,newVal)

#define IMSPropShell_get_TabWidth(This,pVal)	\
    (This)->lpVtbl -> get_TabWidth(This,pVal)

#define IMSPropShell_put_TabWidth(This,newVal)	\
    (This)->lpVtbl -> put_TabWidth(This,newVal)

#define IMSPropShell_get_PageTitle(This,Index,pbstrTitle)	\
    (This)->lpVtbl -> get_PageTitle(This,Index,pbstrTitle)

#define IMSPropShell_get_PageHasHelp(This,Index,pVal)	\
    (This)->lpVtbl -> get_PageHasHelp(This,Index,pVal)

#define IMSPropShell_ShowPageHelp(This,Index)	\
    (This)->lpVtbl -> ShowPageHelp(This,Index)

#define IMSPropShell_get_IsDirty(This,pVal)	\
    (This)->lpVtbl -> get_IsDirty(This,pVal)

#define IMSPropShell_put_IsDirty(This,newVal)	\
    (This)->lpVtbl -> put_IsDirty(This,newVal)

#define IMSPropShell_ResetBag(This)	\
    (This)->lpVtbl -> ResetBag(This)

#define IMSPropShell_ResetBagFromEngine(This,fForce)	\
    (This)->lpVtbl -> ResetBagFromEngine(This,fForce)

#define IMSPropShell_Load(This)	\
    (This)->lpVtbl -> Load(This)

#define IMSPropShell_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IMSPropShell_Validate(This)	\
    (This)->lpVtbl -> Validate(This)

#define IMSPropShell_ModifyProperty(This,lIDRecepient,bstrValue,lParam1,var)	\
    (This)->lpVtbl -> ModifyProperty(This,lIDRecepient,bstrValue,lParam1,var)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_AddPage_Proxy( 
    IMSPropShell * This,
    /* [in] */ LPUNKNOWN pUnknown);


void __RPC_STUB IMSPropShell_AddPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_GetPage_Proxy( 
    IMSPropShell * This,
    /* [in] */ long Index,
    /* [retval][out] */ LPUNKNOWN *ppUnknown);


void __RPC_STUB IMSPropShell_GetPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_RemoveAllPages_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_RemoveAllPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_AddObject_Proxy( 
    IMSPropShell * This,
    /* [in] */ LPUNKNOWN pUnknown);


void __RPC_STUB IMSPropShell_AddObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_RemoveAllObjects_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_RemoveAllObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_Apply_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_Refresh_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageCount_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMSPropShell_get_PageCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_AutoRefresh_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IMSPropShell_get_AutoRefresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_AutoRefresh_Proxy( 
    IMSPropShell * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IMSPropShell_put_AutoRefresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageIndex_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMSPropShell_get_PageIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_PageIndex_Proxy( 
    IMSPropShell * This,
    /* [in] */ long newVal);


void __RPC_STUB IMSPropShell_put_PageIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_Style_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ PSSTYLE *pVal);


void __RPC_STUB IMSPropShell_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_Style_Proxy( 
    IMSPropShell * This,
    /* [in] */ PSSTYLE newVal);


void __RPC_STUB IMSPropShell_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_LocaleID_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMSPropShell_get_LocaleID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_LocaleID_Proxy( 
    IMSPropShell * This,
    /* [in] */ long newVal);


void __RPC_STUB IMSPropShell_put_LocaleID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_ApplyIndex_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMSPropShell_get_ApplyIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_InitNew_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IMSPropShell_get_InitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_InitNew_Proxy( 
    IMSPropShell * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IMSPropShell_put_InitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_TabWidth_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IMSPropShell_get_TabWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_TabWidth_Proxy( 
    IMSPropShell * This,
    /* [in] */ short newVal);


void __RPC_STUB IMSPropShell_put_TabWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageTitle_Proxy( 
    IMSPropShell * This,
    /* [in] */ long Index,
    /* [retval][out] */ BSTR *pbstrTitle);


void __RPC_STUB IMSPropShell_get_PageTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageHasHelp_Proxy( 
    IMSPropShell * This,
    /* [in] */ long Index,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IMSPropShell_get_PageHasHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_ShowPageHelp_Proxy( 
    IMSPropShell * This,
    /* [in] */ long Index);


void __RPC_STUB IMSPropShell_ShowPageHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_IsDirty_Proxy( 
    IMSPropShell * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IMSPropShell_get_IsDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_IsDirty_Proxy( 
    IMSPropShell * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IMSPropShell_put_IsDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_ResetBag_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_ResetBag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_ResetBagFromEngine_Proxy( 
    IMSPropShell * This,
    /* [in] */ VARIANT_BOOL fForce);


void __RPC_STUB IMSPropShell_ResetBagFromEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_Load_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_Update_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_Validate_Proxy( 
    IMSPropShell * This);


void __RPC_STUB IMSPropShell_Validate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_ModifyProperty_Proxy( 
    IMSPropShell * This,
    /* [in] */ long lIDRecepient,
    /* [in] */ BSTR bstrValue,
    /* [in] */ long lParam1,
    /* [in] */ VARIANT var);


void __RPC_STUB IMSPropShell_ModifyProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSPropShell_INTERFACE_DEFINED__ */


#ifndef __IMSPropShellEvents2_INTERFACE_DEFINED__
#define __IMSPropShellEvents2_INTERFACE_DEFINED__

/* interface IMSPropShellEvents2 */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_IMSPropShellEvents2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48B22F5F-DCAD-4b7c-B13C-C48B459CE2E8")
    IMSPropShellEvents2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnDirtyChanged( 
            /* [in] */ VARIANT_BOOL fDirty) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnQuerySupportApply( 
            /* [out] */ VARIANT_BOOL *pfSupport) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnApplyClicked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnCancelClicked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnHelpClicked( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSPropShellEvents2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSPropShellEvents2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSPropShellEvents2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSPropShellEvents2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnDirtyChanged )( 
            IMSPropShellEvents2 * This,
            /* [in] */ VARIANT_BOOL fDirty);
        
        HRESULT ( STDMETHODCALLTYPE *OnQuerySupportApply )( 
            IMSPropShellEvents2 * This,
            /* [out] */ VARIANT_BOOL *pfSupport);
        
        HRESULT ( STDMETHODCALLTYPE *OnApplyClicked )( 
            IMSPropShellEvents2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnCancelClicked )( 
            IMSPropShellEvents2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnHelpClicked )( 
            IMSPropShellEvents2 * This);
        
        END_INTERFACE
    } IMSPropShellEvents2Vtbl;

    interface IMSPropShellEvents2
    {
        CONST_VTBL struct IMSPropShellEvents2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSPropShellEvents2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSPropShellEvents2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSPropShellEvents2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSPropShellEvents2_OnDirtyChanged(This,fDirty)	\
    (This)->lpVtbl -> OnDirtyChanged(This,fDirty)

#define IMSPropShellEvents2_OnQuerySupportApply(This,pfSupport)	\
    (This)->lpVtbl -> OnQuerySupportApply(This,pfSupport)

#define IMSPropShellEvents2_OnApplyClicked(This)	\
    (This)->lpVtbl -> OnApplyClicked(This)

#define IMSPropShellEvents2_OnCancelClicked(This)	\
    (This)->lpVtbl -> OnCancelClicked(This)

#define IMSPropShellEvents2_OnHelpClicked(This)	\
    (This)->lpVtbl -> OnHelpClicked(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMSPropShellEvents2_OnDirtyChanged_Proxy( 
    IMSPropShellEvents2 * This,
    /* [in] */ VARIANT_BOOL fDirty);


void __RPC_STUB IMSPropShellEvents2_OnDirtyChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropShellEvents2_OnQuerySupportApply_Proxy( 
    IMSPropShellEvents2 * This,
    /* [out] */ VARIANT_BOOL *pfSupport);


void __RPC_STUB IMSPropShellEvents2_OnQuerySupportApply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropShellEvents2_OnApplyClicked_Proxy( 
    IMSPropShellEvents2 * This);


void __RPC_STUB IMSPropShellEvents2_OnApplyClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropShellEvents2_OnCancelClicked_Proxy( 
    IMSPropShellEvents2 * This);


void __RPC_STUB IMSPropShellEvents2_OnCancelClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropShellEvents2_OnHelpClicked_Proxy( 
    IMSPropShellEvents2 * This);


void __RPC_STUB IMSPropShellEvents2_OnHelpClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSPropShellEvents2_INTERFACE_DEFINED__ */


#ifndef __IWMEncPageProp_INTERFACE_DEFINED__
#define __IWMEncPageProp_INTERFACE_DEFINED__

/* interface IWMEncPageProp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncPageProp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC74C5C1-D214-4fdd-81C3-A5843E57AACB")
    IWMEncPageProp : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetBag( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetBagFromEngine( 
            VARIANT_BOOL fForce) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Load( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDirty( 
            BOOL bDirty) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBagDirty( 
            BOOL *pbDirty) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNew( 
            BOOL fNew) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNew( 
            BOOL *pfNew) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableApply( 
            BOOL fEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ModifyProperty( 
            /* [in] */ long lIDRecepient,
            /* [in] */ BSTR bstrValue,
            /* [in] */ long lParam1,
            /* [in] */ VARIANT var) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveBagToEngine( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBagDirty( 
            BOOL bDirty) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Validate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPagePropVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncPageProp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncPageProp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncPageProp * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResetBag )( 
            IWMEncPageProp * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResetBagFromEngine )( 
            IWMEncPageProp * This,
            VARIANT_BOOL fForce);
        
        HRESULT ( STDMETHODCALLTYPE *Load )( 
            IWMEncPageProp * This);
        
        HRESULT ( STDMETHODCALLTYPE *Update )( 
            IWMEncPageProp * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetDirty )( 
            IWMEncPageProp * This,
            BOOL bDirty);
        
        HRESULT ( STDMETHODCALLTYPE *GetBagDirty )( 
            IWMEncPageProp * This,
            BOOL *pbDirty);
        
        HRESULT ( STDMETHODCALLTYPE *SetNew )( 
            IWMEncPageProp * This,
            BOOL fNew);
        
        HRESULT ( STDMETHODCALLTYPE *GetNew )( 
            IWMEncPageProp * This,
            BOOL *pfNew);
        
        HRESULT ( STDMETHODCALLTYPE *EnableApply )( 
            IWMEncPageProp * This,
            BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE *ModifyProperty )( 
            IWMEncPageProp * This,
            /* [in] */ long lIDRecepient,
            /* [in] */ BSTR bstrValue,
            /* [in] */ long lParam1,
            /* [in] */ VARIANT var);
        
        HRESULT ( STDMETHODCALLTYPE *SaveBagToEngine )( 
            IWMEncPageProp * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetBagDirty )( 
            IWMEncPageProp * This,
            BOOL bDirty);
        
        HRESULT ( STDMETHODCALLTYPE *Validate )( 
            IWMEncPageProp * This);
        
        END_INTERFACE
    } IWMEncPagePropVtbl;

    interface IWMEncPageProp
    {
        CONST_VTBL struct IWMEncPagePropVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncPageProp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncPageProp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncPageProp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncPageProp_ResetBag(This)	\
    (This)->lpVtbl -> ResetBag(This)

#define IWMEncPageProp_ResetBagFromEngine(This,fForce)	\
    (This)->lpVtbl -> ResetBagFromEngine(This,fForce)

#define IWMEncPageProp_Load(This)	\
    (This)->lpVtbl -> Load(This)

#define IWMEncPageProp_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IWMEncPageProp_SetDirty(This,bDirty)	\
    (This)->lpVtbl -> SetDirty(This,bDirty)

#define IWMEncPageProp_GetBagDirty(This,pbDirty)	\
    (This)->lpVtbl -> GetBagDirty(This,pbDirty)

#define IWMEncPageProp_SetNew(This,fNew)	\
    (This)->lpVtbl -> SetNew(This,fNew)

#define IWMEncPageProp_GetNew(This,pfNew)	\
    (This)->lpVtbl -> GetNew(This,pfNew)

#define IWMEncPageProp_EnableApply(This,fEnable)	\
    (This)->lpVtbl -> EnableApply(This,fEnable)

#define IWMEncPageProp_ModifyProperty(This,lIDRecepient,bstrValue,lParam1,var)	\
    (This)->lpVtbl -> ModifyProperty(This,lIDRecepient,bstrValue,lParam1,var)

#define IWMEncPageProp_SaveBagToEngine(This)	\
    (This)->lpVtbl -> SaveBagToEngine(This)

#define IWMEncPageProp_SetBagDirty(This,bDirty)	\
    (This)->lpVtbl -> SetBagDirty(This,bDirty)

#define IWMEncPageProp_Validate(This)	\
    (This)->lpVtbl -> Validate(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWMEncPageProp_ResetBag_Proxy( 
    IWMEncPageProp * This);


void __RPC_STUB IWMEncPageProp_ResetBag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_ResetBagFromEngine_Proxy( 
    IWMEncPageProp * This,
    VARIANT_BOOL fForce);


void __RPC_STUB IWMEncPageProp_ResetBagFromEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_Load_Proxy( 
    IWMEncPageProp * This);


void __RPC_STUB IWMEncPageProp_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_Update_Proxy( 
    IWMEncPageProp * This);


void __RPC_STUB IWMEncPageProp_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_SetDirty_Proxy( 
    IWMEncPageProp * This,
    BOOL bDirty);


void __RPC_STUB IWMEncPageProp_SetDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_GetBagDirty_Proxy( 
    IWMEncPageProp * This,
    BOOL *pbDirty);


void __RPC_STUB IWMEncPageProp_GetBagDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_SetNew_Proxy( 
    IWMEncPageProp * This,
    BOOL fNew);


void __RPC_STUB IWMEncPageProp_SetNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_GetNew_Proxy( 
    IWMEncPageProp * This,
    BOOL *pfNew);


void __RPC_STUB IWMEncPageProp_GetNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_EnableApply_Proxy( 
    IWMEncPageProp * This,
    BOOL fEnable);


void __RPC_STUB IWMEncPageProp_EnableApply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_ModifyProperty_Proxy( 
    IWMEncPageProp * This,
    /* [in] */ long lIDRecepient,
    /* [in] */ BSTR bstrValue,
    /* [in] */ long lParam1,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncPageProp_ModifyProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_SaveBagToEngine_Proxy( 
    IWMEncPageProp * This);


void __RPC_STUB IWMEncPageProp_SaveBagToEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_SetBagDirty_Proxy( 
    IWMEncPageProp * This,
    BOOL bDirty);


void __RPC_STUB IWMEncPageProp_SetBagDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncPageProp_Validate_Proxy( 
    IWMEncPageProp * This);


void __RPC_STUB IWMEncPageProp_Validate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncPageProp_INTERFACE_DEFINED__ */


#ifndef __IMSPropPage_INTERFACE_DEFINED__
#define __IMSPropPage_INTERFACE_DEFINED__

/* interface IMSPropPage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMSPropPage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("24DB76A0-2A25-48BE-B40B-67C09963614C")
    IMSPropPage : public IPropertyPage
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsPageValid( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AreObjectsValid( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSPropPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSPropPage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSPropPage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSPropPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPageSite )( 
            IMSPropPage * This,
            /* [in] */ IPropertyPageSite *pPageSite);
        
        HRESULT ( STDMETHODCALLTYPE *Activate )( 
            IMSPropPage * This,
            /* [in] */ HWND hWndParent,
            /* [in] */ LPCRECT pRect,
            /* [in] */ BOOL bModal);
        
        HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            IMSPropPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPageInfo )( 
            IMSPropPage * This,
            /* [out] */ PROPPAGEINFO *pPageInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetObjects )( 
            IMSPropPage * This,
            /* [in] */ ULONG cObjects,
            /* [size_is][in] */ IUnknown **ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE *Show )( 
            IMSPropPage * This,
            /* [in] */ UINT nCmdShow);
        
        HRESULT ( STDMETHODCALLTYPE *Move )( 
            IMSPropPage * This,
            /* [in] */ LPCRECT pRect);
        
        HRESULT ( STDMETHODCALLTYPE *IsPageDirty )( 
            IMSPropPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *Apply )( 
            IMSPropPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *Help )( 
            IMSPropPage * This,
            /* [in] */ LPCOLESTR pszHelpDir);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateAccelerator )( 
            IMSPropPage * This,
            /* [in] */ MSG *pMsg);
        
        HRESULT ( STDMETHODCALLTYPE *IsPageValid )( 
            IMSPropPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *AreObjectsValid )( 
            IMSPropPage * This);
        
        END_INTERFACE
    } IMSPropPageVtbl;

    interface IMSPropPage
    {
        CONST_VTBL struct IMSPropPageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSPropPage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSPropPage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSPropPage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSPropPage_SetPageSite(This,pPageSite)	\
    (This)->lpVtbl -> SetPageSite(This,pPageSite)

#define IMSPropPage_Activate(This,hWndParent,pRect,bModal)	\
    (This)->lpVtbl -> Activate(This,hWndParent,pRect,bModal)

#define IMSPropPage_Deactivate(This)	\
    (This)->lpVtbl -> Deactivate(This)

#define IMSPropPage_GetPageInfo(This,pPageInfo)	\
    (This)->lpVtbl -> GetPageInfo(This,pPageInfo)

#define IMSPropPage_SetObjects(This,cObjects,ppUnk)	\
    (This)->lpVtbl -> SetObjects(This,cObjects,ppUnk)

#define IMSPropPage_Show(This,nCmdShow)	\
    (This)->lpVtbl -> Show(This,nCmdShow)

#define IMSPropPage_Move(This,pRect)	\
    (This)->lpVtbl -> Move(This,pRect)

#define IMSPropPage_IsPageDirty(This)	\
    (This)->lpVtbl -> IsPageDirty(This)

#define IMSPropPage_Apply(This)	\
    (This)->lpVtbl -> Apply(This)

#define IMSPropPage_Help(This,pszHelpDir)	\
    (This)->lpVtbl -> Help(This,pszHelpDir)

#define IMSPropPage_TranslateAccelerator(This,pMsg)	\
    (This)->lpVtbl -> TranslateAccelerator(This,pMsg)


#define IMSPropPage_IsPageValid(This)	\
    (This)->lpVtbl -> IsPageValid(This)

#define IMSPropPage_AreObjectsValid(This)	\
    (This)->lpVtbl -> AreObjectsValid(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMSPropPage_IsPageValid_Proxy( 
    IMSPropPage * This);


void __RPC_STUB IMSPropPage_IsPageValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropPage_AreObjectsValid_Proxy( 
    IMSPropPage * This);


void __RPC_STUB IMSPropPage_AreObjectsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSPropPage_INTERFACE_DEFINED__ */


#ifndef __IMSPropPageSite_INTERFACE_DEFINED__
#define __IMSPropPageSite_INTERFACE_DEFINED__

/* interface IMSPropPageSite */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMSPropPageSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E849609-C7E8-4EC7-8BD3-D55E871A340D")
    IMSPropPageSite : public IPropertyPageSite
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInitNew( 
            BOOL *pVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnQuerySupportApply( 
            /* [out] */ VARIANT_BOOL *pfSupport) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnApplyClicked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnCancelClicked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnHelpClicked( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSPropPageSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSPropPageSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSPropPageSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSPropPageSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnStatusChange )( 
            IMSPropPageSite * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocaleID )( 
            IMSPropPageSite * This,
            /* [out] */ LCID *pLocaleID);
        
        HRESULT ( STDMETHODCALLTYPE *GetPageContainer )( 
            IMSPropPageSite * This,
            /* [out] */ IUnknown **ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateAccelerator )( 
            IMSPropPageSite * This,
            /* [in] */ MSG *pMsg);
        
        HRESULT ( STDMETHODCALLTYPE *GetInitNew )( 
            IMSPropPageSite * This,
            BOOL *pVal);
        
        HRESULT ( STDMETHODCALLTYPE *OnQuerySupportApply )( 
            IMSPropPageSite * This,
            /* [out] */ VARIANT_BOOL *pfSupport);
        
        HRESULT ( STDMETHODCALLTYPE *OnApplyClicked )( 
            IMSPropPageSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnCancelClicked )( 
            IMSPropPageSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnHelpClicked )( 
            IMSPropPageSite * This);
        
        END_INTERFACE
    } IMSPropPageSiteVtbl;

    interface IMSPropPageSite
    {
        CONST_VTBL struct IMSPropPageSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSPropPageSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSPropPageSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSPropPageSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSPropPageSite_OnStatusChange(This,dwFlags)	\
    (This)->lpVtbl -> OnStatusChange(This,dwFlags)

#define IMSPropPageSite_GetLocaleID(This,pLocaleID)	\
    (This)->lpVtbl -> GetLocaleID(This,pLocaleID)

#define IMSPropPageSite_GetPageContainer(This,ppUnk)	\
    (This)->lpVtbl -> GetPageContainer(This,ppUnk)

#define IMSPropPageSite_TranslateAccelerator(This,pMsg)	\
    (This)->lpVtbl -> TranslateAccelerator(This,pMsg)


#define IMSPropPageSite_GetInitNew(This,pVal)	\
    (This)->lpVtbl -> GetInitNew(This,pVal)

#define IMSPropPageSite_OnQuerySupportApply(This,pfSupport)	\
    (This)->lpVtbl -> OnQuerySupportApply(This,pfSupport)

#define IMSPropPageSite_OnApplyClicked(This)	\
    (This)->lpVtbl -> OnApplyClicked(This)

#define IMSPropPageSite_OnCancelClicked(This)	\
    (This)->lpVtbl -> OnCancelClicked(This)

#define IMSPropPageSite_OnHelpClicked(This)	\
    (This)->lpVtbl -> OnHelpClicked(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMSPropPageSite_GetInitNew_Proxy( 
    IMSPropPageSite * This,
    BOOL *pVal);


void __RPC_STUB IMSPropPageSite_GetInitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropPageSite_OnQuerySupportApply_Proxy( 
    IMSPropPageSite * This,
    /* [out] */ VARIANT_BOOL *pfSupport);


void __RPC_STUB IMSPropPageSite_OnQuerySupportApply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropPageSite_OnApplyClicked_Proxy( 
    IMSPropPageSite * This);


void __RPC_STUB IMSPropPageSite_OnApplyClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropPageSite_OnCancelClicked_Proxy( 
    IMSPropPageSite * This);


void __RPC_STUB IMSPropPageSite_OnCancelClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSPropPageSite_OnHelpClicked_Proxy( 
    IMSPropPageSite * This);


void __RPC_STUB IMSPropPageSite_OnHelpClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSPropPageSite_INTERFACE_DEFINED__ */



#ifndef __MSPROPSHELLLib_LIBRARY_DEFINED__
#define __MSPROPSHELLLib_LIBRARY_DEFINED__

/* library MSPROPSHELLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MSPROPSHELLLib;

#ifndef ___IMSPropShellEvents_DISPINTERFACE_DEFINED__
#define ___IMSPropShellEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IMSPropShellEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IMSPropShellEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DF8AD1EA-FCAA-4455-8772-B4F539488EE3")
    _IMSPropShellEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IMSPropShellEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IMSPropShellEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IMSPropShellEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IMSPropShellEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IMSPropShellEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IMSPropShellEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IMSPropShellEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IMSPropShellEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IMSPropShellEventsVtbl;

    interface _IMSPropShellEvents
    {
        CONST_VTBL struct _IMSPropShellEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMSPropShellEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IMSPropShellEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IMSPropShellEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IMSPropShellEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IMSPropShellEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IMSPropShellEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IMSPropShellEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IMSPropShellEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MSPropShell;

#ifdef __cplusplus

class DECLSPEC_UUID("E297AB5E-40B0-41BD-9E06-E4144084EE5F")
MSPropShell;
#endif
#endif /* __MSPROPSHELLLib_LIBRARY_DEFINED__ */

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


