

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Nov 04 17:41:55 2015
 */
/* Compiler settings for AddinOLE.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

#ifndef __AddinOLE_h__
#define __AddinOLE_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IShowImage_FWD_DEFINED__
#define __IShowImage_FWD_DEFINED__
typedef interface IShowImage IShowImage;

#endif 	/* __IShowImage_FWD_DEFINED__ */


#ifndef ___IShowImageEvents_FWD_DEFINED__
#define ___IShowImageEvents_FWD_DEFINED__
typedef interface _IShowImageEvents _IShowImageEvents;

#endif 	/* ___IShowImageEvents_FWD_DEFINED__ */


#ifndef __ShowImage_FWD_DEFINED__
#define __ShowImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShowImage ShowImage;
#else
typedef struct ShowImage ShowImage;
#endif /* __cplusplus */

#endif 	/* __ShowImage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IShowImage_INTERFACE_DEFINED__
#define __IShowImage_INTERFACE_DEFINED__

/* interface IShowImage */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IShowImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5CD71D8E-4B61-4618-B420-DBF1312C1DE5")
    IShowImage : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFileTrans( 
            /* [in] */ BSTR filename,
            /* [in] */ UINT64 fileLen,
            /* [in] */ BSTR iconFilename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFileTrans( 
            /* [in] */ BSTR msg,
            /* [in] */ DWORD state,
            /* [in] */ UINT64 param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadGif( 
            /* [in] */ BSTR filename) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IShowImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShowImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShowImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShowImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IShowImage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IShowImage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IShowImage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IShowImage * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadFileTrans )( 
            IShowImage * This,
            /* [in] */ BSTR filename,
            /* [in] */ UINT64 fileLen,
            /* [in] */ BSTR iconFilename);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFileTrans )( 
            IShowImage * This,
            /* [in] */ BSTR msg,
            /* [in] */ DWORD state,
            /* [in] */ UINT64 param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadGif )( 
            IShowImage * This,
            /* [in] */ BSTR filename);
        
        END_INTERFACE
    } IShowImageVtbl;

    interface IShowImage
    {
        CONST_VTBL struct IShowImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShowImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShowImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShowImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShowImage_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IShowImage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IShowImage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IShowImage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IShowImage_LoadFileTrans(This,filename,fileLen,iconFilename)	\
    ( (This)->lpVtbl -> LoadFileTrans(This,filename,fileLen,iconFilename) ) 

#define IShowImage_SetFileTrans(This,msg,state,param)	\
    ( (This)->lpVtbl -> SetFileTrans(This,msg,state,param) ) 

#define IShowImage_LoadGif(This,filename)	\
    ( (This)->lpVtbl -> LoadGif(This,filename) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IShowImage_INTERFACE_DEFINED__ */



#ifndef __AddinOLELib_LIBRARY_DEFINED__
#define __AddinOLELib_LIBRARY_DEFINED__

/* library AddinOLELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AddinOLELib;

#ifndef ___IShowImageEvents_DISPINTERFACE_DEFINED__
#define ___IShowImageEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IShowImageEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IShowImageEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1D6E8FF5-C00D-4A14-A767-80168C019ADB")
    _IShowImageEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IShowImageEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IShowImageEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IShowImageEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IShowImageEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IShowImageEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IShowImageEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IShowImageEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IShowImageEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IShowImageEventsVtbl;

    interface _IShowImageEvents
    {
        CONST_VTBL struct _IShowImageEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IShowImageEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IShowImageEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IShowImageEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IShowImageEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IShowImageEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IShowImageEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IShowImageEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IShowImageEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShowImage;

#ifdef __cplusplus

class DECLSPEC_UUID("1D6E8FF5-C00D-4A14-A767-80168C019ADA")
ShowImage;
#endif
#endif /* __AddinOLELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


