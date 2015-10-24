/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 01 15:52:24 2001
 */
/* Compiler settings for .\wmencvu.idl:
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

#ifndef __wmencvu_h__
#define __wmencvu_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWMEncDataView_FWD_DEFINED__
#define __IWMEncDataView_FWD_DEFINED__
typedef interface IWMEncDataView IWMEncDataView;
#endif 	/* __IWMEncDataView_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_wmencvu_0000 */
/* [local] */ 

EXTERN_GUID( IID_IWMEncDataView,            0xbb406aa0, 0x2b2b,0x11d3,0xb3,0x6b,0x00,0xc0,0x4f,0x61,0x08,0xff );
EXTERN_GUID( CLSID_WMEncPreview,            0xC3043B13, 0xE649, 0x436A, 0x9C, 0xE7, 0x8D, 0xA8, 0xCB, 0x0B, 0xF7, 0xC8 );
#ifndef __wmsdkidl_h__
typedef struct  _WMMediaType
    {
    GUID majortype;
    GUID subtype;
    BOOL bFixedSizeSamples;
    BOOL bTemporalCompression;
    ULONG lSampleSize;
    GUID formattype;
    IUnknown __RPC_FAR *pUnk;
    ULONG cbFormat;
    /* [size_is] */ BYTE __RPC_FAR *pbFormat;
    }	WM_MEDIA_TYPE;

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
            /* [size_is][in] */ BYTE __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetViewSetting( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ DWORD __RPC_FAR *pdwSize,
            /* [size_is][in] */ BYTE __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddStream( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE __RPC_FAR *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveStream( 
            /* [in] */ DWORD dwStreamCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMediaFormat( 
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE __RPC_FAR *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaFormat( 
            /* [in] */ DWORD dwStreamCookie,
            /* [out] */ WM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppType) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncDataView __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncDataView __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetViewSetting )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ DWORD dwSize,
            /* [size_is][in] */ BYTE __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetViewSetting )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ DWORD __RPC_FAR *pdwSize,
            /* [size_is][in] */ BYTE __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddStream )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE __RPC_FAR *pType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveStream )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaFormat )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [in] */ WM_MEDIA_TYPE __RPC_FAR *pType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaFormat )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie,
            /* [out] */ WM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IWMEncDataView __RPC_FAR * This,
            /* [in] */ DWORD dwStreamCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartAll )( 
            IWMEncDataView __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAll )( 
            IWMEncDataView __RPC_FAR * This);
        
        END_INTERFACE
    } IWMEncDataViewVtbl;

    interface IWMEncDataView
    {
        CONST_VTBL struct IWMEncDataViewVtbl __RPC_FAR *lpVtbl;
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
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ DWORD dwSize,
    /* [size_is][in] */ BYTE __RPC_FAR *pData);


void __RPC_STUB IWMEncDataView_SetViewSetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_GetViewSetting_Proxy( 
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ DWORD __RPC_FAR *pdwSize,
    /* [size_is][in] */ BYTE __RPC_FAR *pData);


void __RPC_STUB IWMEncDataView_GetViewSetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_AddStream_Proxy( 
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ WM_MEDIA_TYPE __RPC_FAR *pType);


void __RPC_STUB IWMEncDataView_AddStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_RemoveStream_Proxy( 
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie);


void __RPC_STUB IWMEncDataView_RemoveStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_SetMediaFormat_Proxy( 
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [in] */ WM_MEDIA_TYPE __RPC_FAR *pType);


void __RPC_STUB IWMEncDataView_SetMediaFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_GetMediaFormat_Proxy( 
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie,
    /* [out] */ WM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppType);


void __RPC_STUB IWMEncDataView_GetMediaFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_Start_Proxy( 
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie);


void __RPC_STUB IWMEncDataView_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_Stop_Proxy( 
    IWMEncDataView __RPC_FAR * This,
    /* [in] */ DWORD dwStreamCookie);


void __RPC_STUB IWMEncDataView_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_StartAll_Proxy( 
    IWMEncDataView __RPC_FAR * This);


void __RPC_STUB IWMEncDataView_StartAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWMEncDataView_StopAll_Proxy( 
    IWMEncDataView __RPC_FAR * This);


void __RPC_STUB IWMEncDataView_StopAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDataView_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
