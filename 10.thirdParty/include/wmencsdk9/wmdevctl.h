

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for wmdevctl.idl:
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

#ifndef __wmdevctl_h__
#define __wmdevctl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMEncEditDecisionData_FWD_DEFINED__
#define __IWMEncEditDecisionData_FWD_DEFINED__
typedef interface IWMEncEditDecisionData IWMEncEditDecisionData;
#endif 	/* __IWMEncEditDecisionData_FWD_DEFINED__ */


#ifndef __IWMEncEditDecisionList_FWD_DEFINED__
#define __IWMEncEditDecisionList_FWD_DEFINED__
typedef interface IWMEncEditDecisionList IWMEncEditDecisionList;
#endif 	/* __IWMEncEditDecisionList_FWD_DEFINED__ */


#ifndef __IWMEncDeviceControlPlugin_FWD_DEFINED__
#define __IWMEncDeviceControlPlugin_FWD_DEFINED__
typedef interface IWMEncDeviceControlPlugin IWMEncDeviceControlPlugin;
#endif 	/* __IWMEncDeviceControlPlugin_FWD_DEFINED__ */


#ifndef __IWMEncEditDecisionList_FWD_DEFINED__
#define __IWMEncEditDecisionList_FWD_DEFINED__
typedef interface IWMEncEditDecisionList IWMEncEditDecisionList;
#endif 	/* __IWMEncEditDecisionList_FWD_DEFINED__ */


#ifndef __IWMEncEditDecisionData_FWD_DEFINED__
#define __IWMEncEditDecisionData_FWD_DEFINED__
typedef interface IWMEncEditDecisionData IWMEncEditDecisionData;
#endif 	/* __IWMEncEditDecisionData_FWD_DEFINED__ */


#ifndef __IWMEncDeviceControlPlugin_FWD_DEFINED__
#define __IWMEncDeviceControlPlugin_FWD_DEFINED__
typedef interface IWMEncDeviceControlPlugin IWMEncDeviceControlPlugin;
#endif 	/* __IWMEncDeviceControlPlugin_FWD_DEFINED__ */


#ifndef ___IWMEncDeviceControlEvents_FWD_DEFINED__
#define ___IWMEncDeviceControlEvents_FWD_DEFINED__
typedef interface _IWMEncDeviceControlEvents _IWMEncDeviceControlEvents;
#endif 	/* ___IWMEncDeviceControlEvents_FWD_DEFINED__ */


#ifndef __WMEncEditDecisionList_FWD_DEFINED__
#define __WMEncEditDecisionList_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncEditDecisionList WMEncEditDecisionList;
#else
typedef struct WMEncEditDecisionList WMEncEditDecisionList;
#endif /* __cplusplus */

#endif 	/* __WMEncEditDecisionList_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "wmencode.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_wmdevctl_0000 */
/* [local] */ 

#pragma once
EXTERN_GUID( LIBID_WMDEVICECONTROLLib,            0x22F0E5C5, 0x5008, 0x4E2E, 0xBC, 0x60, 0x20, 0x27, 0xF5, 0xC2, 0x36, 0xCE );
EXTERN_GUID( DIID__IWMEncDeviceControlEvents,   0x632B6066, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( CLSID_WMEncEditDecisionList,       0x632B608F, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncEditDecisionList,		0x632B608D, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncEditDecisionData,	    0x632B608E, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncDeviceControlPlugin,		0x632B608B, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
typedef 
enum WMENC_DEVICE_MODE
    {	WMENC_DEVICE_PLAY	= 0x1,
	WMENC_DEVICE_PAUSE	= 0x2,
	WMENC_DEVICE_STOP	= 0x3,
	WMENC_DEVICE_FF	= 0x4,
	WMENC_DEVICE_REW	= 0x5,
	WMENC_DEVICE_STEP_FWD	= 0x6,
	WMENC_DEVICE_STEP_REW	= 0x7,
	WMENC_DEVICE_CUE	= 0x8,
	WMENC_DEVICE_EJECT	= 0x9,
	WMENC_DEVICE_VAR_FORWARD	= 0xa,
	WMENC_DEVICE_VAR_REVERSE	= 0xb
    } 	WMENC_DEVICE_MODE;

typedef struct WMTIMECODE
    {
    WORD wFrameRate;
    WORD wFrameFract;
    DWORD dwFrames;
    } 	WMTIMECODE;

typedef struct WMTIMECODE_SAMPLE
    {
    LONGLONG qwTick;
    WMTIMECODE timecode;
    DWORD dwUser;
    DWORD dwFlags;
    } 	WMTIMECODE_SAMPLE;



extern RPC_IF_HANDLE __MIDL_itf_wmdevctl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wmdevctl_0000_v0_0_s_ifspec;

#ifndef __IWMEncEditDecisionData_INTERFACE_DEFINED__
#define __IWMEncEditDecisionData_INTERFACE_DEFINED__

/* interface IWMEncEditDecisionData */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_IWMEncEditDecisionData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B608E-BBC6-11D2-A329-006097C4E476")
    IWMEncEditDecisionData : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ VARIANT *pVarValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT *pVarValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncEditDecisionDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncEditDecisionData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncEditDecisionData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncEditDecisionData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncEditDecisionData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncEditDecisionData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncEditDecisionData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncEditDecisionData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncEditDecisionData * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncEditDecisionData * This,
            /* [in] */ long Index,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ VARIANT *pVarValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IWMEncEditDecisionData * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT *pVarValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncEditDecisionData * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncEditDecisionData * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncEditDecisionData * This);
        
        END_INTERFACE
    } IWMEncEditDecisionDataVtbl;

    interface IWMEncEditDecisionData
    {
        CONST_VTBL struct IWMEncEditDecisionDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncEditDecisionData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncEditDecisionData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncEditDecisionData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncEditDecisionData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncEditDecisionData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncEditDecisionData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncEditDecisionData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncEditDecisionData_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncEditDecisionData_Item(This,Index,pvarName,pVarValue)	\
    (This)->lpVtbl -> Item(This,Index,pvarName,pVarValue)

#define IWMEncEditDecisionData_get_Value(This,bstrName,pVarValue)	\
    (This)->lpVtbl -> get_Value(This,bstrName,pVarValue)

#define IWMEncEditDecisionData_Add(This,bstrName,varValue)	\
    (This)->lpVtbl -> Add(This,bstrName,varValue)

#define IWMEncEditDecisionData_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define IWMEncEditDecisionData_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionData_get_Count_Proxy( 
    IWMEncEditDecisionData * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncEditDecisionData_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionData_Item_Proxy( 
    IWMEncEditDecisionData * This,
    /* [in] */ long Index,
    /* [out] */ VARIANT *pvarName,
    /* [retval][out] */ VARIANT *pVarValue);


void __RPC_STUB IWMEncEditDecisionData_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionData_get_Value_Proxy( 
    IWMEncEditDecisionData * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ VARIANT *pVarValue);


void __RPC_STUB IWMEncEditDecisionData_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionData_Add_Proxy( 
    IWMEncEditDecisionData * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT varValue);


void __RPC_STUB IWMEncEditDecisionData_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionData_Remove_Proxy( 
    IWMEncEditDecisionData * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncEditDecisionData_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionData_RemoveAll_Proxy( 
    IWMEncEditDecisionData * This);


void __RPC_STUB IWMEncEditDecisionData_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncEditDecisionData_INTERFACE_DEFINED__ */


#ifndef __IWMEncEditDecisionList_INTERFACE_DEFINED__
#define __IWMEncEditDecisionList_INTERFACE_DEFINED__

/* interface IWMEncEditDecisionList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncEditDecisionList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B608D-BBC6-11D2-A329-006097C4E476")
    IWMEncEditDecisionList : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *piCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncEditDecisionData **ppEditData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [retval][out] */ IWMEncEditDecisionData **ppEditData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long iIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncEditDecisionListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncEditDecisionList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncEditDecisionList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncEditDecisionList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncEditDecisionList * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncEditDecisionList * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncEditDecisionList * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncEditDecisionList * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncEditDecisionList * This,
            /* [retval][out] */ long *piCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncEditDecisionList * This,
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncEditDecisionData **ppEditData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncEditDecisionList * This,
            /* [retval][out] */ IWMEncEditDecisionData **ppEditData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncEditDecisionList * This,
            /* [in] */ long iIndex);
        
        END_INTERFACE
    } IWMEncEditDecisionListVtbl;

    interface IWMEncEditDecisionList
    {
        CONST_VTBL struct IWMEncEditDecisionListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncEditDecisionList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncEditDecisionList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncEditDecisionList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncEditDecisionList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncEditDecisionList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncEditDecisionList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncEditDecisionList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncEditDecisionList_get_Count(This,piCount)	\
    (This)->lpVtbl -> get_Count(This,piCount)

#define IWMEncEditDecisionList_Item(This,iIndex,ppEditData)	\
    (This)->lpVtbl -> Item(This,iIndex,ppEditData)

#define IWMEncEditDecisionList_Add(This,ppEditData)	\
    (This)->lpVtbl -> Add(This,ppEditData)

#define IWMEncEditDecisionList_Remove(This,iIndex)	\
    (This)->lpVtbl -> Remove(This,iIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionList_get_Count_Proxy( 
    IWMEncEditDecisionList * This,
    /* [retval][out] */ long *piCount);


void __RPC_STUB IWMEncEditDecisionList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionList_Item_Proxy( 
    IWMEncEditDecisionList * This,
    /* [in] */ long iIndex,
    /* [retval][out] */ IWMEncEditDecisionData **ppEditData);


void __RPC_STUB IWMEncEditDecisionList_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionList_Add_Proxy( 
    IWMEncEditDecisionList * This,
    /* [retval][out] */ IWMEncEditDecisionData **ppEditData);


void __RPC_STUB IWMEncEditDecisionList_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncEditDecisionList_Remove_Proxy( 
    IWMEncEditDecisionList * This,
    /* [in] */ long iIndex);


void __RPC_STUB IWMEncEditDecisionList_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncEditDecisionList_INTERFACE_DEFINED__ */


#ifndef __IWMEncDeviceControlPlugin_INTERFACE_DEFINED__
#define __IWMEncDeviceControlPlugin_INTERFACE_DEFINED__

/* interface IWMEncDeviceControlPlugin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDeviceControlPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B608B-BBC6-11D2-A329-006097C4E476")
    IWMEncDeviceControlPlugin : public IDispatch
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ControlSource( 
            /* [in] */ BSTR bstrSource) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ControlSource( 
            /* [retval][out] */ BSTR *pbstrSource) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EditDecisionList( 
            /* [retval][out] */ IWMEncEditDecisionList **ppEditList) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreRoll( 
            /* [retval][out] */ long *plPreroll) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreRoll( 
            /* [in] */ long lPreroll) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PostRoll( 
            /* [retval][out] */ long *plPostroll) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PostRoll( 
            /* [in] */ long lPostroll) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetOperation( 
            /* [in] */ WMENC_DEVICE_MODE enumMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDeviceState( 
            /* [retval][out] */ WMENC_DEVICECONTROL_STATE *penumState) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IgnoreEDL( 
            /* [in] */ VARIANT_BOOL bIgnoreEDL) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IgnoreEDL( 
            /* [retval][out] */ VARIANT_BOOL *pbIgnoreEDL) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartupLatency( 
            /* [retval][out] */ long *plLantency) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartupLatency( 
            /* [in] */ long lLantency) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StopLatency( 
            /* [in] */ long lLantency) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StopLatency( 
            /* [retval][out] */ long *plLantency) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentPosition( 
            /* [retval][out] */ WMTIMECODE_SAMPLE *ptimecodeSample) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentATN( 
            /* [retval][out] */ WMTIMECODE_SAMPLE *ptimecodeSample) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentEDLEntry( 
            /* [retval][out] */ long *plCurrentEntry) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FrameRate( 
            /* [retval][out] */ long *plFrameRate) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FrameRate( 
            /* [in] */ long lFrameRate) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TotalEDLDurationInTimecode( 
            long *plDuration) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TotalEDLDurationInMilliseconds( 
            long *plDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDeviceControlPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDeviceControlPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDeviceControlPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncDeviceControlPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ControlSource )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ BSTR bstrSource);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ControlSource )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ BSTR *pbstrSource);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EditDecisionList )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ IWMEncEditDecisionList **ppEditList);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreRoll )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ long *plPreroll);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PreRoll )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ long lPreroll);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PostRoll )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ long *plPostroll);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PostRoll )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ long lPostroll);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetOperation )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ WMENC_DEVICE_MODE enumMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDeviceState )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ WMENC_DEVICECONTROL_STATE *penumState);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IgnoreEDL )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ VARIANT_BOOL bIgnoreEDL);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IgnoreEDL )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ VARIANT_BOOL *pbIgnoreEDL);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartupLatency )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ long *plLantency);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartupLatency )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ long lLantency);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopLatency )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ long lLantency);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopLatency )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ long *plLantency);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentPosition )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ WMTIMECODE_SAMPLE *ptimecodeSample);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentATN )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ WMTIMECODE_SAMPLE *ptimecodeSample);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentEDLEntry )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ long *plCurrentEntry);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrameRate )( 
            IWMEncDeviceControlPlugin * This,
            /* [retval][out] */ long *plFrameRate);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrameRate )( 
            IWMEncDeviceControlPlugin * This,
            /* [in] */ long lFrameRate);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TotalEDLDurationInTimecode )( 
            IWMEncDeviceControlPlugin * This,
            long *plDuration);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TotalEDLDurationInMilliseconds )( 
            IWMEncDeviceControlPlugin * This,
            long *plDuration);
        
        END_INTERFACE
    } IWMEncDeviceControlPluginVtbl;

    interface IWMEncDeviceControlPlugin
    {
        CONST_VTBL struct IWMEncDeviceControlPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDeviceControlPlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDeviceControlPlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDeviceControlPlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDeviceControlPlugin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncDeviceControlPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncDeviceControlPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncDeviceControlPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncDeviceControlPlugin_put_ControlSource(This,bstrSource)	\
    (This)->lpVtbl -> put_ControlSource(This,bstrSource)

#define IWMEncDeviceControlPlugin_get_ControlSource(This,pbstrSource)	\
    (This)->lpVtbl -> get_ControlSource(This,pbstrSource)

#define IWMEncDeviceControlPlugin_get_EditDecisionList(This,ppEditList)	\
    (This)->lpVtbl -> get_EditDecisionList(This,ppEditList)

#define IWMEncDeviceControlPlugin_get_PreRoll(This,plPreroll)	\
    (This)->lpVtbl -> get_PreRoll(This,plPreroll)

#define IWMEncDeviceControlPlugin_put_PreRoll(This,lPreroll)	\
    (This)->lpVtbl -> put_PreRoll(This,lPreroll)

#define IWMEncDeviceControlPlugin_get_PostRoll(This,plPostroll)	\
    (This)->lpVtbl -> get_PostRoll(This,plPostroll)

#define IWMEncDeviceControlPlugin_put_PostRoll(This,lPostroll)	\
    (This)->lpVtbl -> put_PostRoll(This,lPostroll)

#define IWMEncDeviceControlPlugin_SetOperation(This,enumMode)	\
    (This)->lpVtbl -> SetOperation(This,enumMode)

#define IWMEncDeviceControlPlugin_GetDeviceState(This,penumState)	\
    (This)->lpVtbl -> GetDeviceState(This,penumState)

#define IWMEncDeviceControlPlugin_put_IgnoreEDL(This,bIgnoreEDL)	\
    (This)->lpVtbl -> put_IgnoreEDL(This,bIgnoreEDL)

#define IWMEncDeviceControlPlugin_get_IgnoreEDL(This,pbIgnoreEDL)	\
    (This)->lpVtbl -> get_IgnoreEDL(This,pbIgnoreEDL)

#define IWMEncDeviceControlPlugin_get_StartupLatency(This,plLantency)	\
    (This)->lpVtbl -> get_StartupLatency(This,plLantency)

#define IWMEncDeviceControlPlugin_put_StartupLatency(This,lLantency)	\
    (This)->lpVtbl -> put_StartupLatency(This,lLantency)

#define IWMEncDeviceControlPlugin_put_StopLatency(This,lLantency)	\
    (This)->lpVtbl -> put_StopLatency(This,lLantency)

#define IWMEncDeviceControlPlugin_get_StopLatency(This,plLantency)	\
    (This)->lpVtbl -> get_StopLatency(This,plLantency)

#define IWMEncDeviceControlPlugin_get_CurrentPosition(This,ptimecodeSample)	\
    (This)->lpVtbl -> get_CurrentPosition(This,ptimecodeSample)

#define IWMEncDeviceControlPlugin_get_CurrentATN(This,ptimecodeSample)	\
    (This)->lpVtbl -> get_CurrentATN(This,ptimecodeSample)

#define IWMEncDeviceControlPlugin_get_CurrentEDLEntry(This,plCurrentEntry)	\
    (This)->lpVtbl -> get_CurrentEDLEntry(This,plCurrentEntry)

#define IWMEncDeviceControlPlugin_get_FrameRate(This,plFrameRate)	\
    (This)->lpVtbl -> get_FrameRate(This,plFrameRate)

#define IWMEncDeviceControlPlugin_put_FrameRate(This,lFrameRate)	\
    (This)->lpVtbl -> put_FrameRate(This,lFrameRate)

#define IWMEncDeviceControlPlugin_get_TotalEDLDurationInTimecode(This,plDuration)	\
    (This)->lpVtbl -> get_TotalEDLDurationInTimecode(This,plDuration)

#define IWMEncDeviceControlPlugin_get_TotalEDLDurationInMilliseconds(This,plDuration)	\
    (This)->lpVtbl -> get_TotalEDLDurationInMilliseconds(This,plDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_put_ControlSource_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ BSTR bstrSource);


void __RPC_STUB IWMEncDeviceControlPlugin_put_ControlSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_ControlSource_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ BSTR *pbstrSource);


void __RPC_STUB IWMEncDeviceControlPlugin_get_ControlSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_EditDecisionList_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ IWMEncEditDecisionList **ppEditList);


void __RPC_STUB IWMEncDeviceControlPlugin_get_EditDecisionList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_PreRoll_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ long *plPreroll);


void __RPC_STUB IWMEncDeviceControlPlugin_get_PreRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_put_PreRoll_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ long lPreroll);


void __RPC_STUB IWMEncDeviceControlPlugin_put_PreRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_PostRoll_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ long *plPostroll);


void __RPC_STUB IWMEncDeviceControlPlugin_get_PostRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_put_PostRoll_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ long lPostroll);


void __RPC_STUB IWMEncDeviceControlPlugin_put_PostRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_SetOperation_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ WMENC_DEVICE_MODE enumMode);


void __RPC_STUB IWMEncDeviceControlPlugin_SetOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_GetDeviceState_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ WMENC_DEVICECONTROL_STATE *penumState);


void __RPC_STUB IWMEncDeviceControlPlugin_GetDeviceState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_put_IgnoreEDL_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ VARIANT_BOOL bIgnoreEDL);


void __RPC_STUB IWMEncDeviceControlPlugin_put_IgnoreEDL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_IgnoreEDL_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ VARIANT_BOOL *pbIgnoreEDL);


void __RPC_STUB IWMEncDeviceControlPlugin_get_IgnoreEDL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_StartupLatency_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ long *plLantency);


void __RPC_STUB IWMEncDeviceControlPlugin_get_StartupLatency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_put_StartupLatency_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ long lLantency);


void __RPC_STUB IWMEncDeviceControlPlugin_put_StartupLatency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_put_StopLatency_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ long lLantency);


void __RPC_STUB IWMEncDeviceControlPlugin_put_StopLatency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_StopLatency_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ long *plLantency);


void __RPC_STUB IWMEncDeviceControlPlugin_get_StopLatency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_CurrentPosition_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ WMTIMECODE_SAMPLE *ptimecodeSample);


void __RPC_STUB IWMEncDeviceControlPlugin_get_CurrentPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_CurrentATN_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ WMTIMECODE_SAMPLE *ptimecodeSample);


void __RPC_STUB IWMEncDeviceControlPlugin_get_CurrentATN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_CurrentEDLEntry_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ long *plCurrentEntry);


void __RPC_STUB IWMEncDeviceControlPlugin_get_CurrentEDLEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_FrameRate_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [retval][out] */ long *plFrameRate);


void __RPC_STUB IWMEncDeviceControlPlugin_get_FrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_put_FrameRate_Proxy( 
    IWMEncDeviceControlPlugin * This,
    /* [in] */ long lFrameRate);


void __RPC_STUB IWMEncDeviceControlPlugin_put_FrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_TotalEDLDurationInTimecode_Proxy( 
    IWMEncDeviceControlPlugin * This,
    long *plDuration);


void __RPC_STUB IWMEncDeviceControlPlugin_get_TotalEDLDurationInTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPlugin_get_TotalEDLDurationInMilliseconds_Proxy( 
    IWMEncDeviceControlPlugin * This,
    long *plDuration);


void __RPC_STUB IWMEncDeviceControlPlugin_get_TotalEDLDurationInMilliseconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDeviceControlPlugin_INTERFACE_DEFINED__ */



#ifndef __WMDEVICECONTROLLib_LIBRARY_DEFINED__
#define __WMDEVICECONTROLLib_LIBRARY_DEFINED__

/* library WMDEVICECONTROLLib */
/* [helpstring][version][uuid] */ 





EXTERN_C const IID LIBID_WMDEVICECONTROLLib;

#ifndef ___IWMEncDeviceControlEvents_DISPINTERFACE_DEFINED__
#define ___IWMEncDeviceControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWMEncDeviceControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWMEncDeviceControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("632B6066-BBC6-11D2-A329-006097C4E476")
    _IWMEncDeviceControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWMEncDeviceControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWMEncDeviceControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWMEncDeviceControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWMEncDeviceControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWMEncDeviceControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWMEncDeviceControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWMEncDeviceControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWMEncDeviceControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWMEncDeviceControlEventsVtbl;

    interface _IWMEncDeviceControlEvents
    {
        CONST_VTBL struct _IWMEncDeviceControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWMEncDeviceControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWMEncDeviceControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWMEncDeviceControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWMEncDeviceControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWMEncDeviceControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWMEncDeviceControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWMEncDeviceControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWMEncDeviceControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WMEncEditDecisionList;

#ifdef __cplusplus

class DECLSPEC_UUID("632B608F-BBC6-11D2-A329-006097C4E476")
WMEncEditDecisionList;
#endif
#endif /* __WMDEVICECONTROLLib_LIBRARY_DEFINED__ */

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


