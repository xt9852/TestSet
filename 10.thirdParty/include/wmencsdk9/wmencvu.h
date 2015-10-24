

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for wmencvu.idl:
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

#ifndef __wmencvu_h__
#define __wmencvu_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMEncDataView_FWD_DEFINED__
#define __IWMEncDataView_FWD_DEFINED__
typedef interface IWMEncDataView IWMEncDataView;
#endif 	/* __IWMEncDataView_FWD_DEFINED__ */


#ifndef __IWMEncDataViewVB_FWD_DEFINED__
#define __IWMEncDataViewVB_FWD_DEFINED__
typedef interface IWMEncDataViewVB IWMEncDataViewVB;
#endif 	/* __IWMEncDataViewVB_FWD_DEFINED__ */


#ifndef __IWMEncDataView2_FWD_DEFINED__
#define __IWMEncDataView2_FWD_DEFINED__
typedef interface IWMEncDataView2 IWMEncDataView2;
#endif 	/* __IWMEncDataView2_FWD_DEFINED__ */


#ifndef __IWMEncPrePreview_FWD_DEFINED__
#define __IWMEncPrePreview_FWD_DEFINED__
typedef interface IWMEncPrePreview IWMEncPrePreview;
#endif 	/* __IWMEncPrePreview_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_wmencvu_0000 */
/* [local] */ 

EXTERN_GUID( IID_IWMEncDataView,            0xbb406aa0, 0x2b2b,0x11d3,0xb3,0x6b,0x00,0xc0,0x4f,0x61,0x08,0xff );
EXTERN_GUID( CLSID_WMEncPreview,            0xC3043B13, 0xE649, 0x436A, 0x9C, 0xE7, 0x8D, 0xA8, 0xCB, 0x0B, 0xF7, 0xC8 );
EXTERN_GUID( IID_IWMEncDataView2,           0x113BEC6A, 0x9BAE, 0x48AB, 0x80, 0xA7, 0x5E, 0xF3, 0xC4, 0x9F, 0xE2, 0x03 );
EXTERN_GUID( IID_IWMEncDataViewVB,          0x6E292D34, 0x8123, 0x4E4E, 0xB8, 0x13, 0x46, 0xEE, 0xE3, 0x35, 0x17, 0xDB );
EXTERN_GUID( IID_IWMEncPrePreview,		    0x72F9AA1F, 0x024B, 0x403C, 0xB9, 0x21, 0xAF, 0xCC, 0xE2, 0x41, 0xD4, 0xD4);
#ifndef __wmsdkidl_h__
typedef struct _WMMediaType
    {
    GUID majortype;
    GUID subtype;
    BOOL bFixedSizeSamples;
    BOOL bTemporalCompression;
    ULONG lSampleSize;
    GUID formattype;
    IUnknown *pUnk;
    ULONG cbFormat;
    /* [size_is] */ BYTE *pbFormat;
    } 	WM_MEDIA_TYPE;

#endif


extern RPC_IF_HANDLE __MIDL_itf_wmencvu_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wmencvu_0000_v0_0_s_ifspec;

#ifndef __IWMEncDataView_INTERFACE_DEFINED__
#define __IWMEncDataView_INTERFACE_DEFINED__

/* interface IWMEncDataView */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDataView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BB406AA0-2B2B-11d3-B36B-00C04F6108FF")
    IWMEncDataView : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetViewSetting( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ DWORD dwSize,
            /* [size_is][in] */ BYTE *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetViewSetting( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ DWORD *pdwSize,
            /* [size_is][in] */ BYTE *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddStream( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveStream( 
            /* [in] */ DWORD dwStreamCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMediaFormat( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaFormat( 
            /* [in] */ DWORD dwStreamCookie,
            /* [out] */ WM_MEDIA_TYPE **ppType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( 
            /* [in] */ DWORD dwStreamCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( 
            /* [in] */ DWORD dwStreamCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartAll( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDataViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDataView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDataView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDataView * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetViewSetting )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ DWORD dwSize,
            /* [size_is][in] */ BYTE *pData);
        
        HRESULT ( STDMETHODCALLTYPE *GetViewSetting )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ DWORD *pdwSize,
            /* [size_is][in] */ BYTE *pData);
        
        HRESULT ( STDMETHODCALLTYPE *AddStream )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE *pType);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveStream )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE *SetMediaFormat )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE *pType);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaFormat )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [out] */ WM_MEDIA_TYPE **ppType);
        
        HRESULT ( STDMETHODCALLTYPE *Start )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IWMEncDataView * This,
            /* [in] */ DWORD dwStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE *StartAll )( 
            IWMEncDataView * This);
        
        HRESULT ( STDMETHODCALLTYPE *StopAll )( 
            IWMEncDataView * This);
        
        END_INTERFACE
    } IWMEncDataViewVtbl;

    interface IWMEncDataView
    {
        CONST_VTBL struct IWMEncDataViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDataView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDataView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDataView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDataView_SetViewSetting(This,dwStreamCookie,dwSize,pData)	\
    (This)->lpVtbl -> SetViewSetting(This,dwStreamCookie,dwSize,pData)

#define IWMEncDataView_GetViewSetting(This,dwStreamCookie,pdwSize,pData)	\
    (This)->lpVtbl -> GetViewSetting(This,dwStreamCookie,pdwSize,pData)

#define IWMEncDataView_AddStream(This,dwStreamCookie,pType)	\
    (This)->lpVtbl -> AddStream(This,dwStreamCookie,pType)

#define IWMEncDataView_RemoveStream(This,dwStreamCookie)	\
    (This)->lpVtbl -> RemoveStream(This,dwStreamCookie)

#define IWMEncDataView_SetMediaFormat(This,dwStreamCookie,pType)	\
    (This)->lpVtbl -> SetMediaFormat(This,dwStreamCookie,pType)

#define IWMEncDataView_GetMediaFormat(This,dwStreamCookie,ppType)	\
    (This)->lpVtbl -> GetMediaFormat(This,dwStreamCookie,ppType)

#define IWMEncDataView_Start(This,dwStreamCookie)	\
    (This)->lpVtbl -> Start(This,dwStreamCookie)

#define IWMEncDataView_Stop(This,dwStreamCookie)	\
    (This)->lpVtbl -> Stop(This,dwStreamCookie)

#define IWMEncDataView_StartAll(This)	\
    (This)->lpVtbl -> StartAll(This)

#define IWMEncDataView_StopAll(This)	\
    (This)->lpVtbl -> StopAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWMEncDataView_SetViewSetting_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ DWORD dwSize,
    /* [size_is][in] */ BYTE *pData);


void __RPC_STUB IWMEncDataView_SetViewSetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_GetViewSetting_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ DWORD *pdwSize,
    /* [size_is][in] */ BYTE *pData);


void __RPC_STUB IWMEncDataView_GetViewSetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_AddStream_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ WM_MEDIA_TYPE *pType);


void __RPC_STUB IWMEncDataView_AddStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_RemoveStream_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie);


void __RPC_STUB IWMEncDataView_RemoveStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_SetMediaFormat_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ WM_MEDIA_TYPE *pType);


void __RPC_STUB IWMEncDataView_SetMediaFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_GetMediaFormat_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [out] */ WM_MEDIA_TYPE **ppType);


void __RPC_STUB IWMEncDataView_GetMediaFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_Start_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie);


void __RPC_STUB IWMEncDataView_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_Stop_Proxy( 
    IWMEncDataView * This,
    /* [in] */ DWORD dwStreamCookie);


void __RPC_STUB IWMEncDataView_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_StartAll_Proxy( 
    IWMEncDataView * This);


void __RPC_STUB IWMEncDataView_StartAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_StopAll_Proxy( 
    IWMEncDataView * This);


void __RPC_STUB IWMEncDataView_StopAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDataView_INTERFACE_DEFINED__ */


#ifndef __IWMEncDataViewVB_INTERFACE_DEFINED__
#define __IWMEncDataViewVB_INTERFACE_DEFINED__

/* interface IWMEncDataViewVB */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDataViewVB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6E292D34-8123-4e4e-B813-46EEE33517DB")
    IWMEncDataViewVB : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetViewProperties( 
            /* [in] */ long lStreamCookie,
            /* [in] */ long hWnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetViewProperties( 
            /* [in] */ long lStreamCookie,
            /* [retval][out] */ long *phWnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartView( 
            /* [in] */ long lStreamCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopView( 
            /* [in] */ long lStreamCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartAllViews( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopAllViews( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDataViewVBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDataViewVB * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDataViewVB * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDataViewVB * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetViewProperties )( 
            IWMEncDataViewVB * This,
            /* [in] */ long lStreamCookie,
            /* [in] */ long hWnd);
        
        HRESULT ( STDMETHODCALLTYPE *GetViewProperties )( 
            IWMEncDataViewVB * This,
            /* [in] */ long lStreamCookie,
            /* [retval][out] */ long *phWnd);
        
        HRESULT ( STDMETHODCALLTYPE *StartView )( 
            IWMEncDataViewVB * This,
            /* [in] */ long lStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE *StopView )( 
            IWMEncDataViewVB * This,
            /* [in] */ long lStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE *StartAllViews )( 
            IWMEncDataViewVB * This);
        
        HRESULT ( STDMETHODCALLTYPE *StopAllViews )( 
            IWMEncDataViewVB * This);
        
        END_INTERFACE
    } IWMEncDataViewVBVtbl;

    interface IWMEncDataViewVB
    {
        CONST_VTBL struct IWMEncDataViewVBVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDataViewVB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDataViewVB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDataViewVB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDataViewVB_SetViewProperties(This,lStreamCookie,hWnd)	\
    (This)->lpVtbl -> SetViewProperties(This,lStreamCookie,hWnd)

#define IWMEncDataViewVB_GetViewProperties(This,lStreamCookie,phWnd)	\
    (This)->lpVtbl -> GetViewProperties(This,lStreamCookie,phWnd)

#define IWMEncDataViewVB_StartView(This,lStreamCookie)	\
    (This)->lpVtbl -> StartView(This,lStreamCookie)

#define IWMEncDataViewVB_StopView(This,lStreamCookie)	\
    (This)->lpVtbl -> StopView(This,lStreamCookie)

#define IWMEncDataViewVB_StartAllViews(This)	\
    (This)->lpVtbl -> StartAllViews(This)

#define IWMEncDataViewVB_StopAllViews(This)	\
    (This)->lpVtbl -> StopAllViews(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWMEncDataViewVB_SetViewProperties_Proxy( 
    IWMEncDataViewVB * This,
    /* [in] */ long lStreamCookie,
    /* [in] */ long hWnd);


void __RPC_STUB IWMEncDataViewVB_SetViewProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataViewVB_GetViewProperties_Proxy( 
    IWMEncDataViewVB * This,
    /* [in] */ long lStreamCookie,
    /* [retval][out] */ long *phWnd);


void __RPC_STUB IWMEncDataViewVB_GetViewProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataViewVB_StartView_Proxy( 
    IWMEncDataViewVB * This,
    /* [in] */ long lStreamCookie);


void __RPC_STUB IWMEncDataViewVB_StartView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataViewVB_StopView_Proxy( 
    IWMEncDataViewVB * This,
    /* [in] */ long lStreamCookie);


void __RPC_STUB IWMEncDataViewVB_StopView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataViewVB_StartAllViews_Proxy( 
    IWMEncDataViewVB * This);


void __RPC_STUB IWMEncDataViewVB_StartAllViews_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataViewVB_StopAllViews_Proxy( 
    IWMEncDataViewVB * This);


void __RPC_STUB IWMEncDataViewVB_StopAllViews_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDataViewVB_INTERFACE_DEFINED__ */


#ifndef __IWMEncDataView2_INTERFACE_DEFINED__
#define __IWMEncDataView2_INTERFACE_DEFINED__

/* interface IWMEncDataView2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDataView2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("113BEC6A-9BAE-48ab-80A7-5EF3C49FE203")
    IWMEncDataView2 : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ViewAvailable( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ VARIANT_BOOL fAvail) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ViewAvailable( 
            /* [in] */ DWORD dwStreamCookie,
            /* [retval][out] */ VARIANT_BOOL *pfAvail) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FrameRateBalance( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ VARIANT_BOOL fFrameRateBalance) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FrameRateBalance( 
            /* [in] */ DWORD dwStreamCookie,
            /* [retval][out] */ VARIANT_BOOL *pfFrameRateBalance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsRunning( 
            /* [in] */ DWORD dwStreamCookie,
            /* [retval][out] */ VARIANT_BOOL *pfRunning) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDataView2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDataView2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDataView2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDataView2 * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ViewAvailable )( 
            IWMEncDataView2 * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ VARIANT_BOOL fAvail);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ViewAvailable )( 
            IWMEncDataView2 * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [retval][out] */ VARIANT_BOOL *pfAvail);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrameRateBalance )( 
            IWMEncDataView2 * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ VARIANT_BOOL fFrameRateBalance);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrameRateBalance )( 
            IWMEncDataView2 * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [retval][out] */ VARIANT_BOOL *pfFrameRateBalance);
        
        HRESULT ( STDMETHODCALLTYPE *IsRunning )( 
            IWMEncDataView2 * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [retval][out] */ VARIANT_BOOL *pfRunning);
        
        END_INTERFACE
    } IWMEncDataView2Vtbl;

    interface IWMEncDataView2
    {
        CONST_VTBL struct IWMEncDataView2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDataView2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDataView2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDataView2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDataView2_put_ViewAvailable(This,dwStreamCookie,fAvail)	\
    (This)->lpVtbl -> put_ViewAvailable(This,dwStreamCookie,fAvail)

#define IWMEncDataView2_get_ViewAvailable(This,dwStreamCookie,pfAvail)	\
    (This)->lpVtbl -> get_ViewAvailable(This,dwStreamCookie,pfAvail)

#define IWMEncDataView2_put_FrameRateBalance(This,dwStreamCookie,fFrameRateBalance)	\
    (This)->lpVtbl -> put_FrameRateBalance(This,dwStreamCookie,fFrameRateBalance)

#define IWMEncDataView2_get_FrameRateBalance(This,dwStreamCookie,pfFrameRateBalance)	\
    (This)->lpVtbl -> get_FrameRateBalance(This,dwStreamCookie,pfFrameRateBalance)

#define IWMEncDataView2_IsRunning(This,dwStreamCookie,pfRunning)	\
    (This)->lpVtbl -> IsRunning(This,dwStreamCookie,pfRunning)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IWMEncDataView2_put_ViewAvailable_Proxy( 
    IWMEncDataView2 * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ VARIANT_BOOL fAvail);


void __RPC_STUB IWMEncDataView2_put_ViewAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IWMEncDataView2_get_ViewAvailable_Proxy( 
    IWMEncDataView2 * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [retval][out] */ VARIANT_BOOL *pfAvail);


void __RPC_STUB IWMEncDataView2_get_ViewAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IWMEncDataView2_put_FrameRateBalance_Proxy( 
    IWMEncDataView2 * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ VARIANT_BOOL fFrameRateBalance);


void __RPC_STUB IWMEncDataView2_put_FrameRateBalance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IWMEncDataView2_get_FrameRateBalance_Proxy( 
    IWMEncDataView2 * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [retval][out] */ VARIANT_BOOL *pfFrameRateBalance);


void __RPC_STUB IWMEncDataView2_get_FrameRateBalance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView2_IsRunning_Proxy( 
    IWMEncDataView2 * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [retval][out] */ VARIANT_BOOL *pfRunning);


void __RPC_STUB IWMEncDataView2_IsRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDataView2_INTERFACE_DEFINED__ */


#ifndef __IWMEncPrePreview_INTERFACE_DEFINED__
#define __IWMEncPrePreview_INTERFACE_DEFINED__

/* interface IWMEncPrePreview */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWMEncPrePreview;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("72F9AA1F-024B-403c-B921-AFCCE241D4D4")
    IWMEncPrePreview : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetCaptureParent( 
            /* [in] */ long hWnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPrePreviewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncPrePreview * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncPrePreview * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncPrePreview * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetCaptureParent )( 
            IWMEncPrePreview * This,
            /* [in] */ long hWnd);
        
        END_INTERFACE
    } IWMEncPrePreviewVtbl;

    interface IWMEncPrePreview
    {
        CONST_VTBL struct IWMEncPrePreviewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncPrePreview_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncPrePreview_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncPrePreview_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncPrePreview_SetCaptureParent(This,hWnd)	\
    (This)->lpVtbl -> SetCaptureParent(This,hWnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWMEncPrePreview_SetCaptureParent_Proxy( 
    IWMEncPrePreview * This,
    /* [in] */ long hWnd);


void __RPC_STUB IWMEncPrePreview_SetCaptureParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncPrePreview_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


