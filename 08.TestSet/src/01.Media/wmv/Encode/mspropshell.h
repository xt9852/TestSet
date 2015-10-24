/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 01 15:52:28 2001
 */
/* Compiler settings for .\mspropshell.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMSPropShell_FWD_DEFINED__
#define __IMSPropShell_FWD_DEFINED__
typedef interface IMSPropShell IMSPropShell;
#endif 	/* __IMSPropShell_FWD_DEFINED__ */


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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_mspropshell_0000 */
/* [local] */ 

EXTERN_GUID( LIBID_MSPROPSHELLLib,      0xC4941F47, 0x8BC1, 0x49D3, 0x99, 0x89, 0x2B, 0x78, 0x26, 0xF2, 0x6A, 0xE6 );
EXTERN_GUID( DIID__IMSPropShellEvents,  0xDF8AD1EA, 0xFCAA, 0x4455, 0x87, 0x72, 0xB4, 0xF5, 0x39, 0x48, 0x8E, 0xE3 );
EXTERN_GUID( CLSID_MSPropShell,         0xE297AB5E, 0x40B0, 0x41BD, 0x9E, 0x06, 0xE4, 0x14, 0x40, 0x84, 0xEE, 0x5F );
EXTERN_GUID( IID_IMSPropShell,          0x119338AA, 0xF278, 0x47CC, 0x9F, 0x88, 0x50, 0x0E, 0x86, 0x51, 0x0B, 0x66 );
EXTERN_GUID( IID_IMSPropPage,           0x24DB76A0, 0x2A25, 0x48BE, 0xB4, 0x0B, 0x67, 0xC0, 0x99, 0x63, 0x61, 0x4C );
EXTERN_GUID( IID_IMSPropPageSite,       0x8E849609, 0xC7E8, 0x4EC7, 0x8B, 0xD3, 0xD5, 0x5E, 0x87, 0x1A, 0x34, 0x0D );
typedef /* [helpstring][uuid] */ 
enum PSSTYLE
    {	pssNoTabs	= 0,
	pssTabsTop	= 0x1,
	pssTabsBottom	= 0x2
    }	PSSTYLE;



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
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *ppUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllPages( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddObject( 
            /* [in] */ LPUNKNOWN pUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllObjects( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoRefresh( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoRefresh( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PageIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ PSSTYLE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ PSSTYLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocaleID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocaleID( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ApplyIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InitNew( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InitNew( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TabWidth( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TabWidth( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageTitle( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PageHasHelp( 
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowPageHelp( 
            /* [in] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSPropShellVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMSPropShell __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMSPropShell __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMSPropShell __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPage )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ LPUNKNOWN pUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPage )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *ppUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAllPages )( 
            IMSPropShell __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddObject )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ LPUNKNOWN pUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAllObjects )( 
            IMSPropShell __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            IMSPropShell __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IMSPropShell __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PageCount )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoRefresh )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoRefresh )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PageIndex )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PageIndex )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ PSSTYLE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ PSSTYLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocaleID )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocaleID )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ApplyIndex )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitNew )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InitNew )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TabWidth )( 
            IMSPropShell __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TabWidth )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PageTitle )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PageHasHelp )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowPageHelp )( 
            IMSPropShell __RPC_FAR * This,
            /* [in] */ long Index);
        
        END_INTERFACE
    } IMSPropShellVtbl;

    interface IMSPropShell
    {
        CONST_VTBL struct IMSPropShellVtbl __RPC_FAR *lpVtbl;
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

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_AddPage_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ LPUNKNOWN pUnknown);


void __RPC_STUB IMSPropShell_AddPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_GetPage_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *ppUnknown);


void __RPC_STUB IMSPropShell_GetPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_RemoveAllPages_Proxy( 
    IMSPropShell __RPC_FAR * This);


void __RPC_STUB IMSPropShell_RemoveAllPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_AddObject_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ LPUNKNOWN pUnknown);


void __RPC_STUB IMSPropShell_AddObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_RemoveAllObjects_Proxy( 
    IMSPropShell __RPC_FAR * This);


void __RPC_STUB IMSPropShell_RemoveAllObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_Apply_Proxy( 
    IMSPropShell __RPC_FAR * This);


void __RPC_STUB IMSPropShell_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_Refresh_Proxy( 
    IMSPropShell __RPC_FAR * This);


void __RPC_STUB IMSPropShell_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageCount_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_PageCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_AutoRefresh_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_AutoRefresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_AutoRefresh_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IMSPropShell_put_AutoRefresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageIndex_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_PageIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_PageIndex_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IMSPropShell_put_PageIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_Style_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ PSSTYLE __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_Style_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ PSSTYLE newVal);


void __RPC_STUB IMSPropShell_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_LocaleID_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_LocaleID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_LocaleID_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IMSPropShell_put_LocaleID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_ApplyIndex_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_ApplyIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_InitNew_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_InitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_InitNew_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IMSPropShell_put_InitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_TabWidth_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_TabWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSPropShell_put_TabWidth_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IMSPropShell_put_TabWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageTitle_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);


void __RPC_STUB IMSPropShell_get_PageTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSPropShell_get_PageHasHelp_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IMSPropShell_get_PageHasHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSPropShell_ShowPageHelp_Proxy( 
    IMSPropShell __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB IMSPropShell_ShowPageHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSPropShell_INTERFACE_DEFINED__ */


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
        
    };
    
#else 	/* C style interface */

    typedef struct IMSPropPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMSPropPage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMSPropPage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPageSite )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ IPropertyPageSite __RPC_FAR *pPageSite);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ HWND hWndParent,
            /* [in] */ LPCRECT pRect,
            /* [in] */ BOOL bModal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Deactivate )( 
            IMSPropPage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPageInfo )( 
            IMSPropPage __RPC_FAR * This,
            /* [out] */ PROPPAGEINFO __RPC_FAR *pPageInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjects )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ ULONG cObjects,
            /* [size_is][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ UINT nCmdShow);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ LPCRECT pRect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPageDirty )( 
            IMSPropPage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            IMSPropPage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Help )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ LPCOLESTR pszHelpDir);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TranslateAccelerator )( 
            IMSPropPage __RPC_FAR * This,
            /* [in] */ MSG __RPC_FAR *pMsg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPageValid )( 
            IMSPropPage __RPC_FAR * This);
        
        END_INTERFACE
    } IMSPropPageVtbl;

    interface IMSPropPage
    {
        CONST_VTBL struct IMSPropPageVtbl __RPC_FAR *lpVtbl;
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

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMSPropPage_IsPageValid_Proxy( 
    IMSPropPage __RPC_FAR * This);


void __RPC_STUB IMSPropPage_IsPageValid_Stub(
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
            BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSPropPageSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMSPropPageSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMSPropPageSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMSPropPageSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStatusChange )( 
            IMSPropPageSite __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocaleID )( 
            IMSPropPageSite __RPC_FAR * This,
            /* [out] */ LCID __RPC_FAR *pLocaleID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPageContainer )( 
            IMSPropPageSite __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TranslateAccelerator )( 
            IMSPropPageSite __RPC_FAR * This,
            /* [in] */ MSG __RPC_FAR *pMsg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInitNew )( 
            IMSPropPageSite __RPC_FAR * This,
            BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } IMSPropPageSiteVtbl;

    interface IMSPropPageSite
    {
        CONST_VTBL struct IMSPropPageSiteVtbl __RPC_FAR *lpVtbl;
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

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMSPropPageSite_GetInitNew_Proxy( 
    IMSPropPageSite __RPC_FAR * This,
    BOOL __RPC_FAR *pVal);


void __RPC_STUB IMSPropPageSite_GetInitNew_Stub(
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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IMSPropShellEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IMSPropShellEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IMSPropShellEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IMSPropShellEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IMSPropShellEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IMSPropShellEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IMSPropShellEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IMSPropShellEventsVtbl;

    interface _IMSPropShellEvents
    {
        CONST_VTBL struct _IMSPropShellEventsVtbl __RPC_FAR *lpVtbl;
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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
