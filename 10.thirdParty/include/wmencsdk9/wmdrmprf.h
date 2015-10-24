

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for wmdrmprf.idl:
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

#ifndef __wmdrmprf_h__
#define __wmdrmprf_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMDRMProfileCollection_FWD_DEFINED__
#define __IWMDRMProfileCollection_FWD_DEFINED__
typedef interface IWMDRMProfileCollection IWMDRMProfileCollection;
#endif 	/* __IWMDRMProfileCollection_FWD_DEFINED__ */


#ifndef __IWMDRMContentAuthor_FWD_DEFINED__
#define __IWMDRMContentAuthor_FWD_DEFINED__
typedef interface IWMDRMContentAuthor IWMDRMContentAuthor;
#endif 	/* __IWMDRMContentAuthor_FWD_DEFINED__ */


#ifndef __IWMDRMProfile_FWD_DEFINED__
#define __IWMDRMProfile_FWD_DEFINED__
typedef interface IWMDRMProfile IWMDRMProfile;
#endif 	/* __IWMDRMProfile_FWD_DEFINED__ */


#ifndef __IWMDRMAttributes_FWD_DEFINED__
#define __IWMDRMAttributes_FWD_DEFINED__
typedef interface IWMDRMAttributes IWMDRMAttributes;
#endif 	/* __IWMDRMAttributes_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_wmdrmprf_0000 */
/* [local] */ 

#pragma once



EXTERN_GUID( IID_IWMDRMContentAuthor,       0x632B609D, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMDRMProfileCollection,   0x097A1BE3, 0x4692, 0x4ADD, 0xBF, 0x3F, 0x1A, 0xDB, 0xC3, 0x70, 0xF6, 0x62);
EXTERN_GUID( IID_IWMDRMProfile,				0x632B609E, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMDRMAttributes,          0x632B60A0, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);


extern RPC_IF_HANDLE __MIDL_itf_wmdrmprf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wmdrmprf_0000_v0_0_s_ifspec;

#ifndef __IWMDRMProfileCollection_INTERFACE_DEFINED__
#define __IWMDRMProfileCollection_INTERFACE_DEFINED__

/* interface IWMDRMProfileCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMDRMProfileCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("097A1BE3-4692-4add-BF3F-1ADBC370F662")
    IWMDRMProfileCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ IWMDRMProfile **ppDRMProfile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMDRMProfileCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMDRMProfileCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMDRMProfileCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMDRMProfileCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMDRMProfileCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMDRMProfileCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMDRMProfileCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMDRMProfileCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMDRMProfileCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMDRMProfileCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMDRMProfileCollection * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMDRMProfileCollection * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ IWMDRMProfile **ppDRMProfile);
        
        END_INTERFACE
    } IWMDRMProfileCollectionVtbl;

    interface IWMDRMProfileCollection
    {
        CONST_VTBL struct IWMDRMProfileCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMDRMProfileCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMDRMProfileCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMDRMProfileCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMDRMProfileCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMDRMProfileCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMDRMProfileCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMDRMProfileCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMDRMProfileCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMDRMProfileCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMDRMProfileCollection_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMDRMProfileCollection_Item(This,var,ppDRMProfile)	\
    (This)->lpVtbl -> Item(This,var,ppDRMProfile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfileCollection_get_length_Proxy( 
    IWMDRMProfileCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMDRMProfileCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfileCollection_get_Count_Proxy( 
    IWMDRMProfileCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMDRMProfileCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfileCollection_get__NewEnum_Proxy( 
    IWMDRMProfileCollection * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMDRMProfileCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMProfileCollection_Item_Proxy( 
    IWMDRMProfileCollection * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ IWMDRMProfile **ppDRMProfile);


void __RPC_STUB IWMDRMProfileCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMDRMProfileCollection_INTERFACE_DEFINED__ */


#ifndef __IWMDRMContentAuthor_INTERFACE_DEFINED__
#define __IWMDRMContentAuthor_INTERFACE_DEFINED__

/* interface IWMDRMContentAuthor */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMDRMContentAuthor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B609D-BBC6-11D2-A329-006097C4E476")
    IWMDRMContentAuthor : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSessionDRMProfile( 
            /* [in] */ BSTR bstrProfileID,
            /* [out][in] */ VARIANT *pvartrKID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSessionDRMProfile( 
            /* [out] */ VARIANT *pvar,
            /* [retval][out] */ BSTR *pbstrKID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentID( 
            /* [retval][out] */ BSTR *pbstrCID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContentID( 
            /* [in] */ BSTR bstrCID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attributes( 
            /* [retval][out] */ IWMDRMAttributes **ppAttributes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDRMProfile( 
            /* [in] */ BSTR bstrProviderURL,
            /* [in] */ BSTR bstrSignaturePrivKey,
            /* [in] */ BSTR bstrSignatureCrt,
            /* [in] */ BSTR bstrSignatureLicSrvCert,
            /* [in] */ BSTR bstrSignatureRootCert,
            /* [out] */ VARIANT *pbstrProfileID,
            /* [out] */ VARIANT *pvarSeed,
            /* [retval][out] */ BSTR *pbstrPubKey) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDRMProfile( 
            /* [in] */ BSTR bstrProfileID,
            /* [retval][out] */ IWMDRMProfile **ppDRMProfile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveDRMProfile( 
            /* [in] */ BSTR bstrProfileID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ImportDRMProfile( 
            /* [in] */ BSTR bstrPassword,
            /* [in] */ BSTR bstrFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportDRMProfile( 
            /* [in] */ BSTR bstrProfileID,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ BSTR bstrFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateKeyID( 
            /* [retval][out] */ BSTR *pbstrKID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateContentID( 
            /* [retval][out] */ BSTR *pbstrCID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DRMProfileCollection( 
            /* [retval][out] */ IWMDRMProfileCollection **ppUnkDRMProfiles) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMDRMContentAuthorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMDRMContentAuthor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMDRMContentAuthor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMDRMContentAuthor * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMDRMContentAuthor * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMDRMContentAuthor * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMDRMContentAuthor * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMDRMContentAuthor * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSessionDRMProfile )( 
            IWMDRMContentAuthor * This,
            /* [in] */ BSTR bstrProfileID,
            /* [out][in] */ VARIANT *pvartrKID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSessionDRMProfile )( 
            IWMDRMContentAuthor * This,
            /* [out] */ VARIANT *pvar,
            /* [retval][out] */ BSTR *pbstrKID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentID )( 
            IWMDRMContentAuthor * This,
            /* [retval][out] */ BSTR *pbstrCID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ContentID )( 
            IWMDRMContentAuthor * This,
            /* [in] */ BSTR bstrCID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attributes )( 
            IWMDRMContentAuthor * This,
            /* [retval][out] */ IWMDRMAttributes **ppAttributes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDRMProfile )( 
            IWMDRMContentAuthor * This,
            /* [in] */ BSTR bstrProviderURL,
            /* [in] */ BSTR bstrSignaturePrivKey,
            /* [in] */ BSTR bstrSignatureCrt,
            /* [in] */ BSTR bstrSignatureLicSrvCert,
            /* [in] */ BSTR bstrSignatureRootCert,
            /* [out] */ VARIANT *pbstrProfileID,
            /* [out] */ VARIANT *pvarSeed,
            /* [retval][out] */ BSTR *pbstrPubKey);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDRMProfile )( 
            IWMDRMContentAuthor * This,
            /* [in] */ BSTR bstrProfileID,
            /* [retval][out] */ IWMDRMProfile **ppDRMProfile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveDRMProfile )( 
            IWMDRMContentAuthor * This,
            /* [in] */ BSTR bstrProfileID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ImportDRMProfile )( 
            IWMDRMContentAuthor * This,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ BSTR bstrFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExportDRMProfile )( 
            IWMDRMContentAuthor * This,
            /* [in] */ BSTR bstrProfileID,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ BSTR bstrFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateKeyID )( 
            IWMDRMContentAuthor * This,
            /* [retval][out] */ BSTR *pbstrKID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateContentID )( 
            IWMDRMContentAuthor * This,
            /* [retval][out] */ BSTR *pbstrCID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DRMProfileCollection )( 
            IWMDRMContentAuthor * This,
            /* [retval][out] */ IWMDRMProfileCollection **ppUnkDRMProfiles);
        
        END_INTERFACE
    } IWMDRMContentAuthorVtbl;

    interface IWMDRMContentAuthor
    {
        CONST_VTBL struct IWMDRMContentAuthorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMDRMContentAuthor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMDRMContentAuthor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMDRMContentAuthor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMDRMContentAuthor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMDRMContentAuthor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMDRMContentAuthor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMDRMContentAuthor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMDRMContentAuthor_SetSessionDRMProfile(This,bstrProfileID,pvartrKID)	\
    (This)->lpVtbl -> SetSessionDRMProfile(This,bstrProfileID,pvartrKID)

#define IWMDRMContentAuthor_GetSessionDRMProfile(This,pvar,pbstrKID)	\
    (This)->lpVtbl -> GetSessionDRMProfile(This,pvar,pbstrKID)

#define IWMDRMContentAuthor_get_ContentID(This,pbstrCID)	\
    (This)->lpVtbl -> get_ContentID(This,pbstrCID)

#define IWMDRMContentAuthor_put_ContentID(This,bstrCID)	\
    (This)->lpVtbl -> put_ContentID(This,bstrCID)

#define IWMDRMContentAuthor_get_Attributes(This,ppAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,ppAttributes)

#define IWMDRMContentAuthor_CreateDRMProfile(This,bstrProviderURL,bstrSignaturePrivKey,bstrSignatureCrt,bstrSignatureLicSrvCert,bstrSignatureRootCert,pbstrProfileID,pvarSeed,pbstrPubKey)	\
    (This)->lpVtbl -> CreateDRMProfile(This,bstrProviderURL,bstrSignaturePrivKey,bstrSignatureCrt,bstrSignatureLicSrvCert,bstrSignatureRootCert,pbstrProfileID,pvarSeed,pbstrPubKey)

#define IWMDRMContentAuthor_GetDRMProfile(This,bstrProfileID,ppDRMProfile)	\
    (This)->lpVtbl -> GetDRMProfile(This,bstrProfileID,ppDRMProfile)

#define IWMDRMContentAuthor_RemoveDRMProfile(This,bstrProfileID)	\
    (This)->lpVtbl -> RemoveDRMProfile(This,bstrProfileID)

#define IWMDRMContentAuthor_ImportDRMProfile(This,bstrPassword,bstrFile)	\
    (This)->lpVtbl -> ImportDRMProfile(This,bstrPassword,bstrFile)

#define IWMDRMContentAuthor_ExportDRMProfile(This,bstrProfileID,bstrPassword,bstrFile)	\
    (This)->lpVtbl -> ExportDRMProfile(This,bstrProfileID,bstrPassword,bstrFile)

#define IWMDRMContentAuthor_GenerateKeyID(This,pbstrKID)	\
    (This)->lpVtbl -> GenerateKeyID(This,pbstrKID)

#define IWMDRMContentAuthor_GenerateContentID(This,pbstrCID)	\
    (This)->lpVtbl -> GenerateContentID(This,pbstrCID)

#define IWMDRMContentAuthor_get_DRMProfileCollection(This,ppUnkDRMProfiles)	\
    (This)->lpVtbl -> get_DRMProfileCollection(This,ppUnkDRMProfiles)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_SetSessionDRMProfile_Proxy( 
    IWMDRMContentAuthor * This,
    /* [in] */ BSTR bstrProfileID,
    /* [out][in] */ VARIANT *pvartrKID);


void __RPC_STUB IWMDRMContentAuthor_SetSessionDRMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_GetSessionDRMProfile_Proxy( 
    IWMDRMContentAuthor * This,
    /* [out] */ VARIANT *pvar,
    /* [retval][out] */ BSTR *pbstrKID);


void __RPC_STUB IWMDRMContentAuthor_GetSessionDRMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_get_ContentID_Proxy( 
    IWMDRMContentAuthor * This,
    /* [retval][out] */ BSTR *pbstrCID);


void __RPC_STUB IWMDRMContentAuthor_get_ContentID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_put_ContentID_Proxy( 
    IWMDRMContentAuthor * This,
    /* [in] */ BSTR bstrCID);


void __RPC_STUB IWMDRMContentAuthor_put_ContentID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_get_Attributes_Proxy( 
    IWMDRMContentAuthor * This,
    /* [retval][out] */ IWMDRMAttributes **ppAttributes);


void __RPC_STUB IWMDRMContentAuthor_get_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_CreateDRMProfile_Proxy( 
    IWMDRMContentAuthor * This,
    /* [in] */ BSTR bstrProviderURL,
    /* [in] */ BSTR bstrSignaturePrivKey,
    /* [in] */ BSTR bstrSignatureCrt,
    /* [in] */ BSTR bstrSignatureLicSrvCert,
    /* [in] */ BSTR bstrSignatureRootCert,
    /* [out] */ VARIANT *pbstrProfileID,
    /* [out] */ VARIANT *pvarSeed,
    /* [retval][out] */ BSTR *pbstrPubKey);


void __RPC_STUB IWMDRMContentAuthor_CreateDRMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_GetDRMProfile_Proxy( 
    IWMDRMContentAuthor * This,
    /* [in] */ BSTR bstrProfileID,
    /* [retval][out] */ IWMDRMProfile **ppDRMProfile);


void __RPC_STUB IWMDRMContentAuthor_GetDRMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_RemoveDRMProfile_Proxy( 
    IWMDRMContentAuthor * This,
    /* [in] */ BSTR bstrProfileID);


void __RPC_STUB IWMDRMContentAuthor_RemoveDRMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_ImportDRMProfile_Proxy( 
    IWMDRMContentAuthor * This,
    /* [in] */ BSTR bstrPassword,
    /* [in] */ BSTR bstrFile);


void __RPC_STUB IWMDRMContentAuthor_ImportDRMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_ExportDRMProfile_Proxy( 
    IWMDRMContentAuthor * This,
    /* [in] */ BSTR bstrProfileID,
    /* [in] */ BSTR bstrPassword,
    /* [in] */ BSTR bstrFile);


void __RPC_STUB IWMDRMContentAuthor_ExportDRMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_GenerateKeyID_Proxy( 
    IWMDRMContentAuthor * This,
    /* [retval][out] */ BSTR *pbstrKID);


void __RPC_STUB IWMDRMContentAuthor_GenerateKeyID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_GenerateContentID_Proxy( 
    IWMDRMContentAuthor * This,
    /* [retval][out] */ BSTR *pbstrCID);


void __RPC_STUB IWMDRMContentAuthor_GenerateContentID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMContentAuthor_get_DRMProfileCollection_Proxy( 
    IWMDRMContentAuthor * This,
    /* [retval][out] */ IWMDRMProfileCollection **ppUnkDRMProfiles);


void __RPC_STUB IWMDRMContentAuthor_get_DRMProfileCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMDRMContentAuthor_INTERFACE_DEFINED__ */


#ifndef __IWMDRMProfile_INTERFACE_DEFINED__
#define __IWMDRMProfile_INTERFACE_DEFINED__

/* interface IWMDRMProfile */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMDRMProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B609E-BBC6-11D2-A329-006097C4E476")
    IWMDRMProfile : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ BSTR *pbstrProfileID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProviderURL( 
            /* [retval][out] */ BSTR *pbstrProviderURL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pbstrProfileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrProfileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pbstrProfileDesc) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrProfileDesc) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LicenseAcquisitionURL( 
            /* [retval][out] */ BSTR *pbstrLAINFO) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LicenseAcquisitionURL( 
            /* [in] */ BSTR bstrLAINFO) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_V1LicenseAcquisitionURL( 
            /* [retval][out] */ BSTR *pbstrLAINFO) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_V1LicenseAcquisitionURL( 
            /* [in] */ BSTR bstrLAINFO) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attributes( 
            /* [retval][out] */ IWMDRMAttributes **ppAttributes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentRevocation( 
            /* [retval][out] */ BSTR *pbstrContentRevocation) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMDRMProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMDRMProfile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMDRMProfile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMDRMProfile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMDRMProfile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMDRMProfile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMDRMProfile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMDRMProfile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IWMDRMProfile * This,
            /* [retval][out] */ BSTR *pbstrProfileID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProviderURL )( 
            IWMDRMProfile * This,
            /* [retval][out] */ BSTR *pbstrProviderURL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMDRMProfile * This,
            /* [retval][out] */ BSTR *pbstrProfileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWMDRMProfile * This,
            /* [in] */ BSTR bstrProfileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IWMDRMProfile * This,
            /* [retval][out] */ BSTR *pbstrProfileDesc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IWMDRMProfile * This,
            /* [in] */ BSTR bstrProfileDesc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LicenseAcquisitionURL )( 
            IWMDRMProfile * This,
            /* [retval][out] */ BSTR *pbstrLAINFO);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LicenseAcquisitionURL )( 
            IWMDRMProfile * This,
            /* [in] */ BSTR bstrLAINFO);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_V1LicenseAcquisitionURL )( 
            IWMDRMProfile * This,
            /* [retval][out] */ BSTR *pbstrLAINFO);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_V1LicenseAcquisitionURL )( 
            IWMDRMProfile * This,
            /* [in] */ BSTR bstrLAINFO);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attributes )( 
            IWMDRMProfile * This,
            /* [retval][out] */ IWMDRMAttributes **ppAttributes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IWMDRMProfile * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentRevocation )( 
            IWMDRMProfile * This,
            /* [retval][out] */ BSTR *pbstrContentRevocation);
        
        END_INTERFACE
    } IWMDRMProfileVtbl;

    interface IWMDRMProfile
    {
        CONST_VTBL struct IWMDRMProfileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMDRMProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMDRMProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMDRMProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMDRMProfile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMDRMProfile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMDRMProfile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMDRMProfile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMDRMProfile_get_ID(This,pbstrProfileID)	\
    (This)->lpVtbl -> get_ID(This,pbstrProfileID)

#define IWMDRMProfile_get_ProviderURL(This,pbstrProviderURL)	\
    (This)->lpVtbl -> get_ProviderURL(This,pbstrProviderURL)

#define IWMDRMProfile_get_Name(This,pbstrProfileName)	\
    (This)->lpVtbl -> get_Name(This,pbstrProfileName)

#define IWMDRMProfile_put_Name(This,bstrProfileName)	\
    (This)->lpVtbl -> put_Name(This,bstrProfileName)

#define IWMDRMProfile_get_Description(This,pbstrProfileDesc)	\
    (This)->lpVtbl -> get_Description(This,pbstrProfileDesc)

#define IWMDRMProfile_put_Description(This,bstrProfileDesc)	\
    (This)->lpVtbl -> put_Description(This,bstrProfileDesc)

#define IWMDRMProfile_get_LicenseAcquisitionURL(This,pbstrLAINFO)	\
    (This)->lpVtbl -> get_LicenseAcquisitionURL(This,pbstrLAINFO)

#define IWMDRMProfile_put_LicenseAcquisitionURL(This,bstrLAINFO)	\
    (This)->lpVtbl -> put_LicenseAcquisitionURL(This,bstrLAINFO)

#define IWMDRMProfile_get_V1LicenseAcquisitionURL(This,pbstrLAINFO)	\
    (This)->lpVtbl -> get_V1LicenseAcquisitionURL(This,pbstrLAINFO)

#define IWMDRMProfile_put_V1LicenseAcquisitionURL(This,bstrLAINFO)	\
    (This)->lpVtbl -> put_V1LicenseAcquisitionURL(This,bstrLAINFO)

#define IWMDRMProfile_get_Attributes(This,ppAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,ppAttributes)

#define IWMDRMProfile_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IWMDRMProfile_get_ContentRevocation(This,pbstrContentRevocation)	\
    (This)->lpVtbl -> get_ContentRevocation(This,pbstrContentRevocation)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_ID_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ BSTR *pbstrProfileID);


void __RPC_STUB IWMDRMProfile_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_ProviderURL_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ BSTR *pbstrProviderURL);


void __RPC_STUB IWMDRMProfile_get_ProviderURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_Name_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ BSTR *pbstrProfileName);


void __RPC_STUB IWMDRMProfile_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_put_Name_Proxy( 
    IWMDRMProfile * This,
    /* [in] */ BSTR bstrProfileName);


void __RPC_STUB IWMDRMProfile_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_Description_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ BSTR *pbstrProfileDesc);


void __RPC_STUB IWMDRMProfile_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_put_Description_Proxy( 
    IWMDRMProfile * This,
    /* [in] */ BSTR bstrProfileDesc);


void __RPC_STUB IWMDRMProfile_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_LicenseAcquisitionURL_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ BSTR *pbstrLAINFO);


void __RPC_STUB IWMDRMProfile_get_LicenseAcquisitionURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_put_LicenseAcquisitionURL_Proxy( 
    IWMDRMProfile * This,
    /* [in] */ BSTR bstrLAINFO);


void __RPC_STUB IWMDRMProfile_put_LicenseAcquisitionURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_V1LicenseAcquisitionURL_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ BSTR *pbstrLAINFO);


void __RPC_STUB IWMDRMProfile_get_V1LicenseAcquisitionURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_put_V1LicenseAcquisitionURL_Proxy( 
    IWMDRMProfile * This,
    /* [in] */ BSTR bstrLAINFO);


void __RPC_STUB IWMDRMProfile_put_V1LicenseAcquisitionURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_Attributes_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ IWMDRMAttributes **ppAttributes);


void __RPC_STUB IWMDRMProfile_get_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_Update_Proxy( 
    IWMDRMProfile * This);


void __RPC_STUB IWMDRMProfile_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMProfile_get_ContentRevocation_Proxy( 
    IWMDRMProfile * This,
    /* [retval][out] */ BSTR *pbstrContentRevocation);


void __RPC_STUB IWMDRMProfile_get_ContentRevocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMDRMProfile_INTERFACE_DEFINED__ */


#ifndef __IWMDRMAttributes_INTERFACE_DEFINED__
#define __IWMDRMAttributes_INTERFACE_DEFINED__

/* interface IWMDRMAttributes */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMDRMAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B60A0-BBC6-11D2-A329-006097C4E476")
    IWMDRMAttributes : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ VARIANT *pVarValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ VARIANT *pvarValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMDRMAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMDRMAttributes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMDRMAttributes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMDRMAttributes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMDRMAttributes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMDRMAttributes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMDRMAttributes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMDRMAttributes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMDRMAttributes * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMDRMAttributes * This,
            /* [in] */ long Index,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ VARIANT *pVarValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMDRMAttributes * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IWMDRMAttributes * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ VARIANT *pvarValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMDRMAttributes * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMDRMAttributes * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMDRMAttributes * This);
        
        END_INTERFACE
    } IWMDRMAttributesVtbl;

    interface IWMDRMAttributes
    {
        CONST_VTBL struct IWMDRMAttributesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMDRMAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMDRMAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMDRMAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMDRMAttributes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMDRMAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMDRMAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMDRMAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMDRMAttributes_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMDRMAttributes_Item(This,Index,pvarName,pVarValue)	\
    (This)->lpVtbl -> Item(This,Index,pvarName,pVarValue)

#define IWMDRMAttributes_get_Name(This,lIndex,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,lIndex,pbstrName)

#define IWMDRMAttributes_get_Value(This,var,pvarValue)	\
    (This)->lpVtbl -> get_Value(This,var,pvarValue)

#define IWMDRMAttributes_Add(This,bstrName,varValue)	\
    (This)->lpVtbl -> Add(This,bstrName,varValue)

#define IWMDRMAttributes_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define IWMDRMAttributes_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMAttributes_get_Count_Proxy( 
    IWMDRMAttributes * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMDRMAttributes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMAttributes_Item_Proxy( 
    IWMDRMAttributes * This,
    /* [in] */ long Index,
    /* [out] */ VARIANT *pvarName,
    /* [retval][out] */ VARIANT *pVarValue);


void __RPC_STUB IWMDRMAttributes_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMAttributes_get_Name_Proxy( 
    IWMDRMAttributes * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB IWMDRMAttributes_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMDRMAttributes_get_Value_Proxy( 
    IWMDRMAttributes * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ VARIANT *pvarValue);


void __RPC_STUB IWMDRMAttributes_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMAttributes_Add_Proxy( 
    IWMDRMAttributes * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT varValue);


void __RPC_STUB IWMDRMAttributes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMAttributes_Remove_Proxy( 
    IWMDRMAttributes * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMDRMAttributes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMDRMAttributes_RemoveAll_Proxy( 
    IWMDRMAttributes * This);


void __RPC_STUB IWMDRMAttributes_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMDRMAttributes_INTERFACE_DEFINED__ */


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


