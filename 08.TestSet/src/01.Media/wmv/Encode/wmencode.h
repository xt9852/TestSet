/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 01 15:52:24 2001
 */
/* Compiler settings for .\wmencode.idl:
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

#ifndef __wmencode_h__
#define __wmencode_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWMEncSourcePluginInfoManager_FWD_DEFINED__
#define __IWMEncSourcePluginInfoManager_FWD_DEFINED__
typedef interface IWMEncSourcePluginInfoManager IWMEncSourcePluginInfoManager;
#endif 	/* __IWMEncSourcePluginInfoManager_FWD_DEFINED__ */


#ifndef __IWMEncTransformPluginInfoManager_FWD_DEFINED__
#define __IWMEncTransformPluginInfoManager_FWD_DEFINED__
typedef interface IWMEncTransformPluginInfoManager IWMEncTransformPluginInfoManager;
#endif 	/* __IWMEncTransformPluginInfoManager_FWD_DEFINED__ */


#ifndef __IWMEncPluginInfo_FWD_DEFINED__
#define __IWMEncPluginInfo_FWD_DEFINED__
typedef interface IWMEncPluginInfo IWMEncPluginInfo;
#endif 	/* __IWMEncPluginInfo_FWD_DEFINED__ */


#ifndef __IWMEncTransform_FWD_DEFINED__
#define __IWMEncTransform_FWD_DEFINED__
typedef interface IWMEncTransform IWMEncTransform;
#endif 	/* __IWMEncTransform_FWD_DEFINED__ */


#ifndef __IWMEncTransformCollection_FWD_DEFINED__
#define __IWMEncTransformCollection_FWD_DEFINED__
typedef interface IWMEncTransformCollection IWMEncTransformCollection;
#endif 	/* __IWMEncTransformCollection_FWD_DEFINED__ */


#ifndef __IWMEncDisplayInfo_FWD_DEFINED__
#define __IWMEncDisplayInfo_FWD_DEFINED__
typedef interface IWMEncDisplayInfo IWMEncDisplayInfo;
#endif 	/* __IWMEncDisplayInfo_FWD_DEFINED__ */


#ifndef __IWMEncAttributes_FWD_DEFINED__
#define __IWMEncAttributes_FWD_DEFINED__
typedef interface IWMEncAttributes IWMEncAttributes;
#endif 	/* __IWMEncAttributes_FWD_DEFINED__ */


#ifndef __IWMEncProfile_FWD_DEFINED__
#define __IWMEncProfile_FWD_DEFINED__
typedef interface IWMEncProfile IWMEncProfile;
#endif 	/* __IWMEncProfile_FWD_DEFINED__ */


#ifndef __IWMEncProfileCollection_FWD_DEFINED__
#define __IWMEncProfileCollection_FWD_DEFINED__
typedef interface IWMEncProfileCollection IWMEncProfileCollection;
#endif 	/* __IWMEncProfileCollection_FWD_DEFINED__ */


#ifndef __IWMEncFile_FWD_DEFINED__
#define __IWMEncFile_FWD_DEFINED__
typedef interface IWMEncFile IWMEncFile;
#endif 	/* __IWMEncFile_FWD_DEFINED__ */


#ifndef __IWMEncBroadcast_FWD_DEFINED__
#define __IWMEncBroadcast_FWD_DEFINED__
typedef interface IWMEncBroadcast IWMEncBroadcast;
#endif 	/* __IWMEncBroadcast_FWD_DEFINED__ */


#ifndef __IWMEncDataViewCollection_FWD_DEFINED__
#define __IWMEncDataViewCollection_FWD_DEFINED__
typedef interface IWMEncDataViewCollection IWMEncDataViewCollection;
#endif 	/* __IWMEncDataViewCollection_FWD_DEFINED__ */


#ifndef __IWMEncPostViewCollection_FWD_DEFINED__
#define __IWMEncPostViewCollection_FWD_DEFINED__
typedef interface IWMEncPostViewCollection IWMEncPostViewCollection;
#endif 	/* __IWMEncPostViewCollection_FWD_DEFINED__ */


#ifndef __IWMEncSource_FWD_DEFINED__
#define __IWMEncSource_FWD_DEFINED__
typedef interface IWMEncSource IWMEncSource;
#endif 	/* __IWMEncSource_FWD_DEFINED__ */


#ifndef __IWMEncVideoSource_FWD_DEFINED__
#define __IWMEncVideoSource_FWD_DEFINED__
typedef interface IWMEncVideoSource IWMEncVideoSource;
#endif 	/* __IWMEncVideoSource_FWD_DEFINED__ */


#ifndef __IWMEncSourceGroup_FWD_DEFINED__
#define __IWMEncSourceGroup_FWD_DEFINED__
typedef interface IWMEncSourceGroup IWMEncSourceGroup;
#endif 	/* __IWMEncSourceGroup_FWD_DEFINED__ */


#ifndef __IWMEncSourceGroupCollection_FWD_DEFINED__
#define __IWMEncSourceGroupCollection_FWD_DEFINED__
typedef interface IWMEncSourceGroupCollection IWMEncSourceGroupCollection;
#endif 	/* __IWMEncSourceGroupCollection_FWD_DEFINED__ */


#ifndef __IWMEncoder_FWD_DEFINED__
#define __IWMEncoder_FWD_DEFINED__
typedef interface IWMEncoder IWMEncoder;
#endif 	/* __IWMEncoder_FWD_DEFINED__ */


#ifndef __IWMEncProfileManager_FWD_DEFINED__
#define __IWMEncProfileManager_FWD_DEFINED__
typedef interface IWMEncProfileManager IWMEncProfileManager;
#endif 	/* __IWMEncProfileManager_FWD_DEFINED__ */


#ifndef __IWMEncoderApp_FWD_DEFINED__
#define __IWMEncoderApp_FWD_DEFINED__
typedef interface IWMEncoderApp IWMEncoderApp;
#endif 	/* __IWMEncoderApp_FWD_DEFINED__ */


#ifndef __IWMEncOutputStats_FWD_DEFINED__
#define __IWMEncOutputStats_FWD_DEFINED__
typedef interface IWMEncOutputStats IWMEncOutputStats;
#endif 	/* __IWMEncOutputStats_FWD_DEFINED__ */


#ifndef __IWMEncFileArchiveStats_FWD_DEFINED__
#define __IWMEncFileArchiveStats_FWD_DEFINED__
typedef interface IWMEncFileArchiveStats IWMEncFileArchiveStats;
#endif 	/* __IWMEncFileArchiveStats_FWD_DEFINED__ */


#ifndef __IWMEncIndexerStats_FWD_DEFINED__
#define __IWMEncIndexerStats_FWD_DEFINED__
typedef interface IWMEncIndexerStats IWMEncIndexerStats;
#endif 	/* __IWMEncIndexerStats_FWD_DEFINED__ */


#ifndef __IWMEncStatistics_FWD_DEFINED__
#define __IWMEncStatistics_FWD_DEFINED__
typedef interface IWMEncStatistics IWMEncStatistics;
#endif 	/* __IWMEncStatistics_FWD_DEFINED__ */


#ifndef __IWMEncNetConnectionStats_FWD_DEFINED__
#define __IWMEncNetConnectionStats_FWD_DEFINED__
typedef interface IWMEncNetConnectionStats IWMEncNetConnectionStats;
#endif 	/* __IWMEncNetConnectionStats_FWD_DEFINED__ */


#ifndef __IWMEncSource_FWD_DEFINED__
#define __IWMEncSource_FWD_DEFINED__
typedef interface IWMEncSource IWMEncSource;
#endif 	/* __IWMEncSource_FWD_DEFINED__ */


#ifndef __IWMEncVideoSource_FWD_DEFINED__
#define __IWMEncVideoSource_FWD_DEFINED__
typedef interface IWMEncVideoSource IWMEncVideoSource;
#endif 	/* __IWMEncVideoSource_FWD_DEFINED__ */


#ifndef __IWMEncNetConnectionStats_FWD_DEFINED__
#define __IWMEncNetConnectionStats_FWD_DEFINED__
typedef interface IWMEncNetConnectionStats IWMEncNetConnectionStats;
#endif 	/* __IWMEncNetConnectionStats_FWD_DEFINED__ */


#ifndef __IWMEncOutputStats_FWD_DEFINED__
#define __IWMEncOutputStats_FWD_DEFINED__
typedef interface IWMEncOutputStats IWMEncOutputStats;
#endif 	/* __IWMEncOutputStats_FWD_DEFINED__ */


#ifndef __IWMEncFileArchiveStats_FWD_DEFINED__
#define __IWMEncFileArchiveStats_FWD_DEFINED__
typedef interface IWMEncFileArchiveStats IWMEncFileArchiveStats;
#endif 	/* __IWMEncFileArchiveStats_FWD_DEFINED__ */


#ifndef __IWMEncIndexerStats_FWD_DEFINED__
#define __IWMEncIndexerStats_FWD_DEFINED__
typedef interface IWMEncIndexerStats IWMEncIndexerStats;
#endif 	/* __IWMEncIndexerStats_FWD_DEFINED__ */


#ifndef __IWMEncDataViewCollection_FWD_DEFINED__
#define __IWMEncDataViewCollection_FWD_DEFINED__
typedef interface IWMEncDataViewCollection IWMEncDataViewCollection;
#endif 	/* __IWMEncDataViewCollection_FWD_DEFINED__ */


#ifndef __IWMEncPostViewCollection_FWD_DEFINED__
#define __IWMEncPostViewCollection_FWD_DEFINED__
typedef interface IWMEncPostViewCollection IWMEncPostViewCollection;
#endif 	/* __IWMEncPostViewCollection_FWD_DEFINED__ */


#ifndef ___IWMEncoderEvents_FWD_DEFINED__
#define ___IWMEncoderEvents_FWD_DEFINED__
typedef interface _IWMEncoderEvents _IWMEncoderEvents;
#endif 	/* ___IWMEncoderEvents_FWD_DEFINED__ */


#ifndef ___IWMEncoderAppEvents_FWD_DEFINED__
#define ___IWMEncoderAppEvents_FWD_DEFINED__
typedef interface _IWMEncoderAppEvents _IWMEncoderAppEvents;
#endif 	/* ___IWMEncoderAppEvents_FWD_DEFINED__ */


#ifndef __WMEncoder_FWD_DEFINED__
#define __WMEncoder_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncoder WMEncoder;
#else
typedef struct WMEncoder WMEncoder;
#endif /* __cplusplus */

#endif 	/* __WMEncoder_FWD_DEFINED__ */


#ifndef __WMEncoderApp_FWD_DEFINED__
#define __WMEncoderApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncoderApp WMEncoderApp;
#else
typedef struct WMEncoderApp WMEncoderApp;
#endif /* __cplusplus */

#endif 	/* __WMEncoderApp_FWD_DEFINED__ */


#ifndef __WMEncSourcesPage_FWD_DEFINED__
#define __WMEncSourcesPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncSourcesPage WMEncSourcesPage;
#else
typedef struct WMEncSourcesPage WMEncSourcesPage;
#endif /* __cplusplus */

#endif 	/* __WMEncSourcesPage_FWD_DEFINED__ */


#ifndef __WMEncSourcesAltPage_FWD_DEFINED__
#define __WMEncSourcesAltPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncSourcesAltPage WMEncSourcesAltPage;
#else
typedef struct WMEncSourcesAltPage WMEncSourcesAltPage;
#endif /* __cplusplus */

#endif 	/* __WMEncSourcesAltPage_FWD_DEFINED__ */


#ifndef __WMEncDisplayInfoPage_FWD_DEFINED__
#define __WMEncDisplayInfoPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncDisplayInfoPage WMEncDisplayInfoPage;
#else
typedef struct WMEncDisplayInfoPage WMEncDisplayInfoPage;
#endif /* __cplusplus */

#endif 	/* __WMEncDisplayInfoPage_FWD_DEFINED__ */


#ifndef __WMEncAttributesPage_FWD_DEFINED__
#define __WMEncAttributesPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncAttributesPage WMEncAttributesPage;
#else
typedef struct WMEncAttributesPage WMEncAttributesPage;
#endif /* __cplusplus */

#endif 	/* __WMEncAttributesPage_FWD_DEFINED__ */


#ifndef __WMEncProfilePage_FWD_DEFINED__
#define __WMEncProfilePage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncProfilePage WMEncProfilePage;
#else
typedef struct WMEncProfilePage WMEncProfilePage;
#endif /* __cplusplus */

#endif 	/* __WMEncProfilePage_FWD_DEFINED__ */


#ifndef __WMEncOutputPage_FWD_DEFINED__
#define __WMEncOutputPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncOutputPage WMEncOutputPage;
#else
typedef struct WMEncOutputPage WMEncOutputPage;
#endif /* __cplusplus */

#endif 	/* __WMEncOutputPage_FWD_DEFINED__ */


#ifndef __WMEncAdvancedPage_FWD_DEFINED__
#define __WMEncAdvancedPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncAdvancedPage WMEncAdvancedPage;
#else
typedef struct WMEncAdvancedPage WMEncAdvancedPage;
#endif /* __cplusplus */

#endif 	/* __WMEncAdvancedPage_FWD_DEFINED__ */


#ifndef __WMEncMonMainPage_FWD_DEFINED__
#define __WMEncMonMainPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncMonMainPage WMEncMonMainPage;
#else
typedef struct WMEncMonMainPage WMEncMonMainPage;
#endif /* __cplusplus */

#endif 	/* __WMEncMonMainPage_FWD_DEFINED__ */


#ifndef __WMEncMonDisplayInfoPage_FWD_DEFINED__
#define __WMEncMonDisplayInfoPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncMonDisplayInfoPage WMEncMonDisplayInfoPage;
#else
typedef struct WMEncMonDisplayInfoPage WMEncMonDisplayInfoPage;
#endif /* __cplusplus */

#endif 	/* __WMEncMonDisplayInfoPage_FWD_DEFINED__ */


#ifndef __WMEncMonConnectionsPage_FWD_DEFINED__
#define __WMEncMonConnectionsPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncMonConnectionsPage WMEncMonConnectionsPage;
#else
typedef struct WMEncMonConnectionsPage WMEncMonConnectionsPage;
#endif /* __cplusplus */

#endif 	/* __WMEncMonConnectionsPage_FWD_DEFINED__ */


#ifndef __WMEncProfileManager_FWD_DEFINED__
#define __WMEncProfileManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncProfileManager WMEncProfileManager;
#else
typedef struct WMEncProfileManager WMEncProfileManager;
#endif /* __cplusplus */

#endif 	/* __WMEncProfileManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_wmencode_0000 */
/* [local] */ 

#pragma once

EXTERN_GUID( LIBID_WMEncoderLib,            0x632B6060, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( DIID__IWMEncoderEvents,        0x632B6062, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( DIID__IWMEncoderAppEvents,     0x32B8ECC9, 0x2901, 0x11D3, 0x8F, 0xB8, 0x00, 0xC0, 0x4F, 0x61, 0x09, 0xB7 );
EXTERN_GUID( CLSID_WMEncoder,               0x632B606A, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( CLSID_WMEncoderApp,            0x632B606B, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( CLSID_WMEncSourcesPage,        0x247161C5, 0x995C, 0x4097, 0x9F, 0xF4, 0x65, 0x5D, 0xC6, 0xD1, 0x2D, 0xB5 );
EXTERN_GUID( CLSID_WMEncSourcesAltPage,     0x95F57411, 0x9A21, 0x4846, 0xB1, 0x31, 0x45, 0x0A, 0xDB, 0xEA, 0xE7, 0x53 );
EXTERN_GUID( CLSID_WMEncDisplayInfoPage,    0x4178CE3B, 0x11B1, 0x46DD, 0xA3, 0x6D, 0xBB, 0xCD, 0x36, 0xA5, 0x42, 0x5A );
EXTERN_GUID( CLSID_WMEncAttributesPage,     0x0037AC54, 0xE32B, 0x4ACA, 0x98, 0x64, 0x09, 0xF8, 0x69, 0xAA, 0x82, 0xFE );
EXTERN_GUID( CLSID_WMEncProfilePage,        0xFF8F1D65, 0xAD2B, 0x47F1, 0x9E, 0x71, 0x66, 0xB7, 0xD3, 0x5E, 0x38, 0x52 );
EXTERN_GUID( CLSID_WMEncOutputPage,         0x447AC255, 0xCE81, 0x43AD, 0x98, 0x27, 0xAF, 0xDD, 0xB1, 0x56, 0x1B, 0x07 );
EXTERN_GUID( CLSID_WMEncAdvancedPage,       0xD5DC4B7F, 0x786B, 0x42b7, 0xB8, 0x3B, 0xFE, 0x1B, 0x5F, 0xC1, 0x5E, 0x2C );
EXTERN_GUID( CLSID_WMEncMonMainPage,        0xDF0AD8E0, 0xF91C, 0x4109, 0xAE, 0x46, 0x1E, 0xAA, 0x5C, 0xD8, 0xAB, 0x08 );
EXTERN_GUID( CLSID_WMEncMonDisplayInfoPage, 0xA7E9EBC4, 0x4B2D, 0x44F4, 0x8D, 0xDC, 0x28, 0xBE, 0x73, 0x91, 0x1E, 0x0A );
EXTERN_GUID( CLSID_WMEncMonConnectionsPage, 0x8D52AA2E, 0x40BE, 0x46D7, 0x8F, 0x36, 0xDB, 0x7B, 0x0F, 0x63, 0x68, 0x24 );
EXTERN_GUID( CLSID_WMEncProfileManager,     0xA8D3AD02, 0x7508, 0x4004, 0xB2, 0xE9, 0xAD, 0x33, 0xF0, 0x87, 0xF4, 0x3C );
EXTERN_GUID( IID_IWMEncSourcePluginInfoManager,       0x5AE18C51, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncTransformPluginInfoManager,    0x5AE18C52, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncPluginInfo,                    0x5AE18C53, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncTransformCollection,           0x5AE18C54, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncDataViewCollection,            0x5AE18C55, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncSourceGroupCollection,       0x632B606F, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncSourceGroup,         0x632B6071, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncDisplayInfo,         0x632B6073, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncAttributes,          0x632B6075, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncProfileCollection,   0x632B6077, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncProfile,             0x632B6078, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncFile,                0x632B607B, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncBroadcast,           0x632B607D, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncoder,                0x632B607F, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncoderApp,             0x632B6080, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncOutputStats,         0x2BE53BA6, 0xB726, 0x11D2, 0xA8, 0xEB, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncFileArchiveStats,    0xB12B5B14, 0xF6D2, 0x4a47, 0xAA, 0xED, 0x63, 0x74, 0x98, 0xBD, 0x49, 0xD6);
EXTERN_GUID( IID_IWMEncIndexerStats,        0xC23F0A1E, 0x53DF, 0x4f6d, 0xB8, 0xF4, 0xEF, 0x32, 0x42, 0xD5, 0x35, 0xDE);
EXTERN_GUID( IID_IWMEncStatistics,          0x632B6082, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncNetConnectionStats,  0x632B6083, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncSource,              0x632B6084, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncVideoSource,         0x632B6086, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncProfileManager,      0x731B9D9E, 0x6CF4, 0x4C37, 0xA6, 0xA9, 0xA8, 0x9B, 0x88, 0x0D, 0x36, 0xEC);
EXTERN_GUID( IID_IWMEncPostViewCollection,  0x2b712593, 0xb68c, 0x40dc, 0x80, 0xc3, 0x41, 0x24, 0xbe, 0xa9, 0x21, 0x6a);
EXTERN_GUID( IID_IWMEncTransform,           0x58441831, 0x0B0C, 0x4A19, 0xAE, 0x34, 0x54, 0x2F, 0x1D, 0x39, 0x36, 0x78);
////////////////////////////////////////////////////////////////
//
//
#define WMENC_TOTAL     ( ( WMENC_SOURCE_TYPE ) 0x00000003 )
#define WMENC_ANY       ( ( WMENC_SOURCE_TYPE ) 0xFFFFFFFF )
#define WMENC_STREAMLEVEL_TRANSFORM_PLUGIN      0x00000001
#define WMENC_GROUPLEVEL_TRANSFORM_PLUGIN       0x00000002
#define WMENC_BOTHLEVEL_TRANSFORM_PLUGIN        0x00000003

typedef /* [helpstring][uuid] */ CURRENCY WMENC_LONGLONG;

typedef /* [helpstring][uuid] */ 
enum WMENC_ENCODER_STATE
    {	WMENC_ENCODER_STARTING	= 0x1,
	WMENC_ENCODER_RUNNING	= 0x2,
	WMENC_ENCODER_PAUSED	= 0x3,
	WMENC_ENCODER_STOPPING	= 0x4,
	WMENC_ENCODER_STOPPED	= 0x5
    }	WMENC_ENCODER_STATE;

typedef /* [helpstring][uuid] */ 
enum WMENC_ARCHIVE_TYPE
    {	WMENC_ARCHIVE_LOCAL	= 0x1
    }	WMENC_ARCHIVE_TYPE;

typedef /* [helpstring][uuid] */ 
enum WMENC_ARCHIVE_OPERATION
    {	WMENC_ARCHIVE_START	= 0x1,
	WMENC_ARCHIVE_STOP	= 0x2,
	WMENC_ARCHIVE_PAUSE	= 0x3
    }	WMENC_ARCHIVE_OPERATION;

typedef /* [helpstring][uuid] */ 
enum WMENC_ARCHIVE_STATE
    {	WMENC_ARCHIVE_RUNNING	= 0x1,
	WMENC_ARCHIVE_PAUSED	= 0x2,
	WMENC_ARCHIVE_STOPPED	= 0x3
    }	WMENC_ARCHIVE_STATE;

typedef /* [helpstring][uuid] */ 
enum WMENC_SOURCE_TYPE
    {	WMENC_AUDIO	= 0x1,
	WMENC_VIDEO	= 0x2,
	WMENC_SCRIPT	= 0x4
    }	WMENC_SOURCE_TYPE;

typedef /* [helpstring][uuid] */ 
enum WMENC_SOURCE_STATE
    {	WMENC_SOURCE_START	= 0x1,
	WMENC_SOURCE_STOP	= 0x2,
	WMENC_SOURCE_PREPARE	= 0x3,
	WMENC_SOURCE_UNPREPARE	= 0x4
    }	WMENC_SOURCE_STATE;

typedef /* [helpstring][uuid] */ 
enum WMENC_PLUGIN_TYPE
    {	WMENC_PLUGIN_SOURCE	= 0x1,
	WMENC_PLUGIN_TRANSFORM	= 0x2
    }	WMENC_PLUGIN_TYPE;

typedef /* [helpstring][uuid] */ 
enum WMENC_BROADCAST_PROTOCOL
    {	WMENC_PROTOCOL_HTTP	= 0x1
    }	WMENC_BROADCAST_PROTOCOL;

typedef /* [helpstring][uuid] */ 
enum WMENC_MEDIA_FILTER
    {	WMENC_FILTER_NONE	= 0,
	WMENC_FILTER_A	= 0x1,
	WMENC_FILTER_AV	= 0x11,
	WMENC_FILTER_AS	= 0x101,
	WMENC_FILTER_AVS	= 0x111
    }	WMENC_MEDIA_FILTER;

typedef /* [helpstring][uuid] */ 
enum WMENC_CROPPING_MODE
    {	WMENC_CROPPING_ABSOLUTE	= 0
    }	WMENC_CROPPING_MODE;

typedef /* [helpstring][uuid] */ 
enum WMENC_INDEXER_STATE
    {	WMENC_INDEXER_RUNNING	= 0x1,
	WMENC_INDEXER_STOPPED	= 0x2
    }	WMENC_INDEXER_STATE;

typedef /* [helpstring][uuid] */ 
enum WMENCAPP_PROP_CLASS
    {	WMENCAPP_PROP_USER	= 0x1
    }	WMENCAPP_PROP_CLASS;

typedef /* [helpstring][uuid] */ 
enum WMENC_VIDEO_OPTIMIZATION
    {	WMENC_VIDEO_STANDARD	= 0x1,
	WMENC_VIDEO_DEINTERLACE	= 0x2,
	WMENC_VIDEO_INVERSETELECINE	= 0x3
    }	WMENC_VIDEO_OPTIMIZATION;

typedef /* [helpstring][uuid] */ 
enum WMENC_PIXELFORMAT_VIDEO
    {	WMENC_PIXELFORMAT_AUTO	= 0x1,
	WMENC_PIXELFORMAT_IYUV	= 0x56555949,
	WMENC_PIXELFORMAT_I420	= 0x30323449,
	WMENC_PIXELFORMAT_YV12	= 0x32315659,
	WMENC_PIXELFORMAT_YUY2	= 0x32595559,
	WMENC_PIXELFORMAT_UYVY	= 0x59565955,
	WMENC_PIXELFORMAT_YVYU	= 0x55595659,
	WMENC_PIXELFORMAT_YVU9	= 0x39555659,
	WMENC_PIXELFORMAT_RGB24	= 0xe436eb7d,
	WMENC_PIXELFORMAT_RGB32	= 0xe436eb7e,
	WMENC_PIXELFORMAT_RGB555	= 0xe436eb7c,
	WMENC_PIXELFORMAT_RGB565	= 0xe436eb7b,
	WMENC_PIXELFORMAT_RGB8	= 0xe436eb7a,
	WMENC_PIXELFORMAT_RGB4	= 0xe436eb79,
	WMENC_PIXELFORMAT_RGB1	= 0xe436eb78
    }	WMENC_PIXELFORMAT_VIDEO;

typedef /* [helpstring][uuid] */ 
enum WMENC_INDEXER_OPERATION
    {	WMENC_INDEXER_STOP	= 0x1
    }	WMENC_INDEXER_OPERATION;

typedef /* [helpstring][uuid] */ 
enum WMENC_AUDIOLEVEL_UNITS
    {	WMENC_AUDIOLEVEL_DB	= 0x1,
	WMENC_AUDIOLEVEL_LINEAR	= 0x2
    }	WMENC_AUDIOLEVEL_UNITS;



extern RPC_IF_HANDLE __MIDL_itf_wmencode_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wmencode_0000_v0_0_s_ifspec;

#ifndef __IWMEncSourcePluginInfoManager_INTERFACE_DEFINED__
#define __IWMEncSourcePluginInfoManager_INTERFACE_DEFINED__

/* interface IWMEncSourcePluginInfoManager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncSourcePluginInfoManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AE18C51-DB2E-11D2-A34A-006097C4E476")
    IWMEncSourcePluginInfoManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo __RPC_FAR *__RPC_FAR *ppPluginInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourcePluginInfoManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This,
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo __RPC_FAR *__RPC_FAR *ppPluginInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWMEncSourcePluginInfoManager __RPC_FAR * This);
        
        END_INTERFACE
    } IWMEncSourcePluginInfoManagerVtbl;

    interface IWMEncSourcePluginInfoManager
    {
        CONST_VTBL struct IWMEncSourcePluginInfoManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncSourcePluginInfoManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncSourcePluginInfoManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncSourcePluginInfoManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncSourcePluginInfoManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncSourcePluginInfoManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncSourcePluginInfoManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncSourcePluginInfoManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncSourcePluginInfoManager_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncSourcePluginInfoManager_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncSourcePluginInfoManager_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncSourcePluginInfoManager_Item(This,iIndex,ppPluginInfo)	\
    (This)->lpVtbl -> Item(This,iIndex,ppPluginInfo)

#define IWMEncSourcePluginInfoManager_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_get_length_Proxy( 
    IWMEncSourcePluginInfoManager __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncSourcePluginInfoManager_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_get_Count_Proxy( 
    IWMEncSourcePluginInfoManager __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncSourcePluginInfoManager_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_get__NewEnum_Proxy( 
    IWMEncSourcePluginInfoManager __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);


void __RPC_STUB IWMEncSourcePluginInfoManager_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_Item_Proxy( 
    IWMEncSourcePluginInfoManager __RPC_FAR * This,
    /* [in] */ long iIndex,
    /* [retval][out] */ IWMEncPluginInfo __RPC_FAR *__RPC_FAR *ppPluginInfo);


void __RPC_STUB IWMEncSourcePluginInfoManager_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_Refresh_Proxy( 
    IWMEncSourcePluginInfoManager __RPC_FAR * This);


void __RPC_STUB IWMEncSourcePluginInfoManager_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSourcePluginInfoManager_INTERFACE_DEFINED__ */


#ifndef __IWMEncTransformPluginInfoManager_INTERFACE_DEFINED__
#define __IWMEncTransformPluginInfoManager_INTERFACE_DEFINED__

/* interface IWMEncTransformPluginInfoManager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncTransformPluginInfoManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AE18C52-DB2E-11D2-A34A-006097C4E476")
    IWMEncTransformPluginInfoManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo __RPC_FAR *__RPC_FAR *ppPluginInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncTransformPluginInfoManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This,
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo __RPC_FAR *__RPC_FAR *ppPluginInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWMEncTransformPluginInfoManager __RPC_FAR * This);
        
        END_INTERFACE
    } IWMEncTransformPluginInfoManagerVtbl;

    interface IWMEncTransformPluginInfoManager
    {
        CONST_VTBL struct IWMEncTransformPluginInfoManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncTransformPluginInfoManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncTransformPluginInfoManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncTransformPluginInfoManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncTransformPluginInfoManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncTransformPluginInfoManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncTransformPluginInfoManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncTransformPluginInfoManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncTransformPluginInfoManager_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncTransformPluginInfoManager_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncTransformPluginInfoManager_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncTransformPluginInfoManager_Item(This,iIndex,ppPluginInfo)	\
    (This)->lpVtbl -> Item(This,iIndex,ppPluginInfo)

#define IWMEncTransformPluginInfoManager_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_get_length_Proxy( 
    IWMEncTransformPluginInfoManager __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncTransformPluginInfoManager_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_get_Count_Proxy( 
    IWMEncTransformPluginInfoManager __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncTransformPluginInfoManager_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_get__NewEnum_Proxy( 
    IWMEncTransformPluginInfoManager __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);


void __RPC_STUB IWMEncTransformPluginInfoManager_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_Item_Proxy( 
    IWMEncTransformPluginInfoManager __RPC_FAR * This,
    /* [in] */ long iIndex,
    /* [retval][out] */ IWMEncPluginInfo __RPC_FAR *__RPC_FAR *ppPluginInfo);


void __RPC_STUB IWMEncTransformPluginInfoManager_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_Refresh_Proxy( 
    IWMEncTransformPluginInfoManager __RPC_FAR * This);


void __RPC_STUB IWMEncTransformPluginInfoManager_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncTransformPluginInfoManager_INTERFACE_DEFINED__ */


#ifndef __IWMEncPluginInfo_INTERFACE_DEFINED__
#define __IWMEncPluginInfo_INTERFACE_DEFINED__

/* interface IWMEncPluginInfo */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncPluginInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AE18C53-DB2E-11D2-A34A-006097C4E476")
    IWMEncPluginInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SchemeType( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSchemeType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CLSID( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCLSID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaType( 
            /* [retval][out] */ WMENC_SOURCE_TYPE __RPC_FAR *penumMediaType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PluginType( 
            /* [retval][out] */ WMENC_PLUGIN_TYPE __RPC_FAR *penumType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Copyright( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCopyright) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoURL( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInfoURL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Resources( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResources) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Exclusive( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbExclusive) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PropertyPage( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProppage) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransformFlags( 
            /* [retval][out] */ short __RPC_FAR *piFlags) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Hidden( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbHidden) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPluginInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncPluginInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncPluginInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SchemeType )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSchemeType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CLSID )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaType )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE __RPC_FAR *penumMediaType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PluginType )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ WMENC_PLUGIN_TYPE __RPC_FAR *penumType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Copyright )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCopyright);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoURL )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInfoURL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Resources )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResources);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Exclusive )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbExclusive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PropertyPage )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProppage);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransformFlags )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *piFlags);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hidden )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbHidden);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncPluginInfo __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResource);
        
        END_INTERFACE
    } IWMEncPluginInfoVtbl;

    interface IWMEncPluginInfo
    {
        CONST_VTBL struct IWMEncPluginInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncPluginInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncPluginInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncPluginInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncPluginInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncPluginInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncPluginInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncPluginInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncPluginInfo_get_SchemeType(This,pbstrSchemeType)	\
    (This)->lpVtbl -> get_SchemeType(This,pbstrSchemeType)

#define IWMEncPluginInfo_get_CLSID(This,pbstrCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,pbstrCLSID)

#define IWMEncPluginInfo_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IWMEncPluginInfo_get_MediaType(This,penumMediaType)	\
    (This)->lpVtbl -> get_MediaType(This,penumMediaType)

#define IWMEncPluginInfo_get_PluginType(This,penumType)	\
    (This)->lpVtbl -> get_PluginType(This,penumType)

#define IWMEncPluginInfo_get_Copyright(This,pbstrCopyright)	\
    (This)->lpVtbl -> get_Copyright(This,pbstrCopyright)

#define IWMEncPluginInfo_get_InfoURL(This,pbstrInfoURL)	\
    (This)->lpVtbl -> get_InfoURL(This,pbstrInfoURL)

#define IWMEncPluginInfo_get_Resources(This,pbResources)	\
    (This)->lpVtbl -> get_Resources(This,pbResources)

#define IWMEncPluginInfo_get_Exclusive(This,pbExclusive)	\
    (This)->lpVtbl -> get_Exclusive(This,pbExclusive)

#define IWMEncPluginInfo_get_PropertyPage(This,pbProppage)	\
    (This)->lpVtbl -> get_PropertyPage(This,pbProppage)

#define IWMEncPluginInfo_get_TransformFlags(This,piFlags)	\
    (This)->lpVtbl -> get_TransformFlags(This,piFlags)

#define IWMEncPluginInfo_get_Hidden(This,pbHidden)	\
    (This)->lpVtbl -> get_Hidden(This,pbHidden)

#define IWMEncPluginInfo_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncPluginInfo_Item(This,lIndex,pbstrResource)	\
    (This)->lpVtbl -> Item(This,lIndex,pbstrResource)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_SchemeType_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrSchemeType);


void __RPC_STUB IWMEncPluginInfo_get_SchemeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_CLSID_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCLSID);


void __RPC_STUB IWMEncPluginInfo_get_CLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Name_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IWMEncPluginInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_MediaType_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ WMENC_SOURCE_TYPE __RPC_FAR *penumMediaType);


void __RPC_STUB IWMEncPluginInfo_get_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_PluginType_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ WMENC_PLUGIN_TYPE __RPC_FAR *penumType);


void __RPC_STUB IWMEncPluginInfo_get_PluginType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Copyright_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCopyright);


void __RPC_STUB IWMEncPluginInfo_get_Copyright_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_InfoURL_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrInfoURL);


void __RPC_STUB IWMEncPluginInfo_get_InfoURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Resources_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResources);


void __RPC_STUB IWMEncPluginInfo_get_Resources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Exclusive_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbExclusive);


void __RPC_STUB IWMEncPluginInfo_get_Exclusive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_PropertyPage_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProppage);


void __RPC_STUB IWMEncPluginInfo_get_PropertyPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_TransformFlags_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *piFlags);


void __RPC_STUB IWMEncPluginInfo_get_TransformFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Hidden_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbHidden);


void __RPC_STUB IWMEncPluginInfo_get_Hidden_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Count_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncPluginInfo_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_Item_Proxy( 
    IWMEncPluginInfo __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrResource);


void __RPC_STUB IWMEncPluginInfo_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncPluginInfo_INTERFACE_DEFINED__ */


#ifndef __IWMEncTransform_INTERFACE_DEFINED__
#define __IWMEncTransform_INTERFACE_DEFINED__

/* interface IWMEncTransform */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("58441831-0B0C-4a19-AE34-542F1D393678")
    IWMEncTransform : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInput( 
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme = L"",
            /* [defaultvalue][in] */ BSTR bstrInitData = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInput( 
            /* [out] */ BSTR __RPC_FAR *pbstrScheme,
            /* [out] */ BSTR __RPC_FAR *pbstrInitData,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInput) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransformPlugin( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncTransform __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncTransform __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncTransform __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncTransform __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncTransform __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInput )( 
            IWMEncTransform __RPC_FAR * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrInitData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInput )( 
            IWMEncTransform __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrScheme,
            /* [out] */ BSTR __RPC_FAR *pbstrInitData,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInput);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformPlugin )( 
            IWMEncTransform __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin);
        
        END_INTERFACE
    } IWMEncTransformVtbl;

    interface IWMEncTransform
    {
        CONST_VTBL struct IWMEncTransformVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncTransform_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncTransform_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncTransform_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncTransform_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncTransform_SetInput(This,bstrInput,bstrScheme,bstrInitData)	\
    (This)->lpVtbl -> SetInput(This,bstrInput,bstrScheme,bstrInitData)

#define IWMEncTransform_GetInput(This,pbstrScheme,pbstrInitData,pbstrInput)	\
    (This)->lpVtbl -> GetInput(This,pbstrScheme,pbstrInitData,pbstrInput)

#define IWMEncTransform_GetTransformPlugin(This,ppUnkPlugin)	\
    (This)->lpVtbl -> GetTransformPlugin(This,ppUnkPlugin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransform_SetInput_Proxy( 
    IWMEncTransform __RPC_FAR * This,
    /* [in] */ BSTR bstrInput,
    /* [defaultvalue][in] */ BSTR bstrScheme,
    /* [defaultvalue][in] */ BSTR bstrInitData);


void __RPC_STUB IWMEncTransform_SetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransform_GetInput_Proxy( 
    IWMEncTransform __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrScheme,
    /* [out] */ BSTR __RPC_FAR *pbstrInitData,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrInput);


void __RPC_STUB IWMEncTransform_GetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransform_GetTransformPlugin_Proxy( 
    IWMEncTransform __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin);


void __RPC_STUB IWMEncTransform_GetTransformPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncTransform_INTERFACE_DEFINED__ */


#ifndef __IWMEncTransformCollection_INTERFACE_DEFINED__
#define __IWMEncTransformCollection_INTERFACE_DEFINED__

/* interface IWMEncTransformCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncTransformCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AE18C54-DB2E-11D2-A34A-006097C4E476")
    IWMEncTransformCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncTransform __RPC_FAR *__RPC_FAR *ppTransform) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [retval][out] */ IWMEncTransform __RPC_FAR *__RPC_FAR *ppTransform) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long lIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ long lMove,
            /* [in] */ long lInFrontOf) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncTransformCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncTransformCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncTransformCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncTransform __RPC_FAR *__RPC_FAR *ppTransform);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [retval][out] */ IWMEncTransform __RPC_FAR *__RPC_FAR *ppTransform);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [in] */ long lIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )( 
            IWMEncTransformCollection __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IWMEncTransformCollection __RPC_FAR * This,
            /* [in] */ long lMove,
            /* [in] */ long lInFrontOf);
        
        END_INTERFACE
    } IWMEncTransformCollectionVtbl;

    interface IWMEncTransformCollection
    {
        CONST_VTBL struct IWMEncTransformCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncTransformCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncTransformCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncTransformCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncTransformCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncTransformCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncTransformCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncTransformCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncTransformCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncTransformCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncTransformCollection_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncTransformCollection_Item(This,lIndex,ppTransform)	\
    (This)->lpVtbl -> Item(This,lIndex,ppTransform)

#define IWMEncTransformCollection_Add(This,ppTransform)	\
    (This)->lpVtbl -> Add(This,ppTransform)

#define IWMEncTransformCollection_Remove(This,lIndex)	\
    (This)->lpVtbl -> Remove(This,lIndex)

#define IWMEncTransformCollection_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define IWMEncTransformCollection_Move(This,lMove,lInFrontOf)	\
    (This)->lpVtbl -> Move(This,lMove,lInFrontOf)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_get_length_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncTransformCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_get_Count_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncTransformCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_get__NewEnum_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);


void __RPC_STUB IWMEncTransformCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Item_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ IWMEncTransform __RPC_FAR *__RPC_FAR *ppTransform);


void __RPC_STUB IWMEncTransformCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Add_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This,
    /* [retval][out] */ IWMEncTransform __RPC_FAR *__RPC_FAR *ppTransform);


void __RPC_STUB IWMEncTransformCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Remove_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This,
    /* [in] */ long lIndex);


void __RPC_STUB IWMEncTransformCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_RemoveAll_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This);


void __RPC_STUB IWMEncTransformCollection_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Move_Proxy( 
    IWMEncTransformCollection __RPC_FAR * This,
    /* [in] */ long lMove,
    /* [in] */ long lInFrontOf);


void __RPC_STUB IWMEncTransformCollection_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncTransformCollection_INTERFACE_DEFINED__ */


#ifndef __IWMEncDisplayInfo_INTERFACE_DEFINED__
#define __IWMEncDisplayInfo_INTERFACE_DEFINED__

/* interface IWMEncDisplayInfo */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDisplayInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6073-BBC6-11D2-A329-006097C4E476")
    IWMEncDisplayInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR bstrTitle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Author( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAuthor) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Author( 
            /* [in] */ BSTR bstrAuthor) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Copyright( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCopyright) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Copyright( 
            /* [in] */ BSTR bstrCopyright) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rating( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRating) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rating( 
            /* [in] */ BSTR bstrRating) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDesc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDisplayInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncDisplayInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncDisplayInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Title )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Author )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrAuthor);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Author )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrAuthor);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Copyright )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCopyright);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Copyright )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrCopyright);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rating )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRating);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rating )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrRating);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IWMEncDisplayInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrDesc);
        
        END_INTERFACE
    } IWMEncDisplayInfoVtbl;

    interface IWMEncDisplayInfo
    {
        CONST_VTBL struct IWMEncDisplayInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDisplayInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDisplayInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDisplayInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDisplayInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncDisplayInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncDisplayInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncDisplayInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncDisplayInfo_get_Title(This,pbstrTitle)	\
    (This)->lpVtbl -> get_Title(This,pbstrTitle)

#define IWMEncDisplayInfo_put_Title(This,bstrTitle)	\
    (This)->lpVtbl -> put_Title(This,bstrTitle)

#define IWMEncDisplayInfo_get_Author(This,pbstrAuthor)	\
    (This)->lpVtbl -> get_Author(This,pbstrAuthor)

#define IWMEncDisplayInfo_put_Author(This,bstrAuthor)	\
    (This)->lpVtbl -> put_Author(This,bstrAuthor)

#define IWMEncDisplayInfo_get_Copyright(This,pbstrCopyright)	\
    (This)->lpVtbl -> get_Copyright(This,pbstrCopyright)

#define IWMEncDisplayInfo_put_Copyright(This,bstrCopyright)	\
    (This)->lpVtbl -> put_Copyright(This,bstrCopyright)

#define IWMEncDisplayInfo_get_Rating(This,pbstrRating)	\
    (This)->lpVtbl -> get_Rating(This,pbstrRating)

#define IWMEncDisplayInfo_put_Rating(This,bstrRating)	\
    (This)->lpVtbl -> put_Rating(This,bstrRating)

#define IWMEncDisplayInfo_get_Description(This,pbstrDesc)	\
    (This)->lpVtbl -> get_Description(This,pbstrDesc)

#define IWMEncDisplayInfo_put_Description(This,bstrDesc)	\
    (This)->lpVtbl -> put_Description(This,bstrDesc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Title_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);


void __RPC_STUB IWMEncDisplayInfo_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Title_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [in] */ BSTR bstrTitle);


void __RPC_STUB IWMEncDisplayInfo_put_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Author_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrAuthor);


void __RPC_STUB IWMEncDisplayInfo_get_Author_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Author_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [in] */ BSTR bstrAuthor);


void __RPC_STUB IWMEncDisplayInfo_put_Author_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Copyright_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCopyright);


void __RPC_STUB IWMEncDisplayInfo_get_Copyright_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Copyright_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [in] */ BSTR bstrCopyright);


void __RPC_STUB IWMEncDisplayInfo_put_Copyright_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Rating_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRating);


void __RPC_STUB IWMEncDisplayInfo_get_Rating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Rating_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [in] */ BSTR bstrRating);


void __RPC_STUB IWMEncDisplayInfo_put_Rating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Description_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);


void __RPC_STUB IWMEncDisplayInfo_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Description_Proxy( 
    IWMEncDisplayInfo __RPC_FAR * This,
    /* [in] */ BSTR bstrDesc);


void __RPC_STUB IWMEncDisplayInfo_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDisplayInfo_INTERFACE_DEFINED__ */


#ifndef __IWMEncAttributes_INTERFACE_DEFINED__
#define __IWMEncAttributes_INTERFACE_DEFINED__

/* interface IWMEncAttributes */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6075-BBC6-11D2-A329-006097C4E476")
    IWMEncAttributes : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [out] */ BSTR __RPC_FAR *pbstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pVarValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncAttributes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncAttributes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [in] */ long Index,
            /* [out] */ BSTR __RPC_FAR *pbstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pVarValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWMEncAttributes __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )( 
            IWMEncAttributes __RPC_FAR * This);
        
        END_INTERFACE
    } IWMEncAttributesVtbl;

    interface IWMEncAttributes
    {
        CONST_VTBL struct IWMEncAttributesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncAttributes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncAttributes_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncAttributes_Item(This,Index,pbstrName,pVarValue)	\
    (This)->lpVtbl -> Item(This,Index,pbstrName,pVarValue)

#define IWMEncAttributes_Add(This,bstrName,varValue)	\
    (This)->lpVtbl -> Add(This,bstrName,varValue)

#define IWMEncAttributes_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define IWMEncAttributes_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_get_Count_Proxy( 
    IWMEncAttributes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncAttributes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_Item_Proxy( 
    IWMEncAttributes __RPC_FAR * This,
    /* [in] */ long Index,
    /* [out] */ BSTR __RPC_FAR *pbstrName,
    /* [retval][out] */ VARIANT __RPC_FAR *pVarValue);


void __RPC_STUB IWMEncAttributes_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_Add_Proxy( 
    IWMEncAttributes __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT varValue);


void __RPC_STUB IWMEncAttributes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_Remove_Proxy( 
    IWMEncAttributes __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncAttributes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_RemoveAll_Proxy( 
    IWMEncAttributes __RPC_FAR * This);


void __RPC_STUB IWMEncAttributes_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncAttributes_INTERFACE_DEFINED__ */


#ifndef __IWMEncProfile_INTERFACE_DEFINED__
#define __IWMEncProfile_INTERFACE_DEFINED__

/* interface IWMEncProfile */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6078-BBC6-11D2-A329-006097C4E476")
    IWMEncProfile : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrDescription) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaCount( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short __RPC_FAR *piCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MultipleBitrate( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbMBR) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudienceCollection( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAudienceCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxPacketSize( 
            /* [retval][out] */ long __RPC_FAR *plMaxPacketSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxPacketSize( 
            /* [in] */ long lMaxPacketSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncProfile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncProfile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncProfile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncProfile __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncProfile __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncProfile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncProfile __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWMEncProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IWMEncProfile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrDescription);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaCount )( 
            IWMEncProfile __RPC_FAR * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short __RPC_FAR *piCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MultipleBitrate )( 
            IWMEncProfile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbMBR);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudienceCollection )( 
            IWMEncProfile __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAudienceCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxPacketSize )( 
            IWMEncProfile __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMaxPacketSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxPacketSize )( 
            IWMEncProfile __RPC_FAR * This,
            /* [in] */ long lMaxPacketSize);
        
        END_INTERFACE
    } IWMEncProfileVtbl;

    interface IWMEncProfile
    {
        CONST_VTBL struct IWMEncProfileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncProfile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncProfile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncProfile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncProfile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncProfile_get_Name(This,bstrName)	\
    (This)->lpVtbl -> get_Name(This,bstrName)

#define IWMEncProfile_get_Description(This,bstrDescription)	\
    (This)->lpVtbl -> get_Description(This,bstrDescription)

#define IWMEncProfile_get_MediaCount(This,enumType,piCount)	\
    (This)->lpVtbl -> get_MediaCount(This,enumType,piCount)

#define IWMEncProfile_get_MultipleBitrate(This,pbMBR)	\
    (This)->lpVtbl -> get_MultipleBitrate(This,pbMBR)

#define IWMEncProfile_get_AudienceCollection(This,ppAudienceCollection)	\
    (This)->lpVtbl -> get_AudienceCollection(This,ppAudienceCollection)

#define IWMEncProfile_get_MaxPacketSize(This,plMaxPacketSize)	\
    (This)->lpVtbl -> get_MaxPacketSize(This,plMaxPacketSize)

#define IWMEncProfile_put_MaxPacketSize(This,lMaxPacketSize)	\
    (This)->lpVtbl -> put_MaxPacketSize(This,lMaxPacketSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_Name_Proxy( 
    IWMEncProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrName);


void __RPC_STUB IWMEncProfile_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_Description_Proxy( 
    IWMEncProfile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrDescription);


void __RPC_STUB IWMEncProfile_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_MediaCount_Proxy( 
    IWMEncProfile __RPC_FAR * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [retval][out] */ short __RPC_FAR *piCount);


void __RPC_STUB IWMEncProfile_get_MediaCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_MultipleBitrate_Proxy( 
    IWMEncProfile __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbMBR);


void __RPC_STUB IWMEncProfile_get_MultipleBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_AudienceCollection_Proxy( 
    IWMEncProfile __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAudienceCollection);


void __RPC_STUB IWMEncProfile_get_AudienceCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_MaxPacketSize_Proxy( 
    IWMEncProfile __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMaxPacketSize);


void __RPC_STUB IWMEncProfile_get_MaxPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_put_MaxPacketSize_Proxy( 
    IWMEncProfile __RPC_FAR * This,
    /* [in] */ long lMaxPacketSize);


void __RPC_STUB IWMEncProfile_put_MaxPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncProfile_INTERFACE_DEFINED__ */


#ifndef __IWMEncProfileCollection_INTERFACE_DEFINED__
#define __IWMEncProfileCollection_INTERFACE_DEFINED__

/* interface IWMEncProfileCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncProfileCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6077-BBC6-11D2-A329-006097C4E476")
    IWMEncProfileCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileDirectory( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrDirectory) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileDirectory( 
            /* [in] */ BSTR bstrDirectory) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IWMEncProfile __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncProfileCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncProfileCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncProfileCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProfileDirectory )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProfileDirectory )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [in] */ BSTR bstrDirectory);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncProfileCollection __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IWMEncProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWMEncProfileCollection __RPC_FAR * This);
        
        END_INTERFACE
    } IWMEncProfileCollectionVtbl;

    interface IWMEncProfileCollection
    {
        CONST_VTBL struct IWMEncProfileCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncProfileCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncProfileCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncProfileCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncProfileCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncProfileCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncProfileCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncProfileCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncProfileCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncProfileCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncProfileCollection_get_ProfileDirectory(This,bstrDirectory)	\
    (This)->lpVtbl -> get_ProfileDirectory(This,bstrDirectory)

#define IWMEncProfileCollection_put_ProfileDirectory(This,bstrDirectory)	\
    (This)->lpVtbl -> put_ProfileDirectory(This,bstrDirectory)

#define IWMEncProfileCollection_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncProfileCollection_Item(This,Index,ppProfile)	\
    (This)->lpVtbl -> Item(This,Index,ppProfile)

#define IWMEncProfileCollection_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_get_length_Proxy( 
    IWMEncProfileCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncProfileCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_get_Count_Proxy( 
    IWMEncProfileCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncProfileCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_get_ProfileDirectory_Proxy( 
    IWMEncProfileCollection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrDirectory);


void __RPC_STUB IWMEncProfileCollection_get_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_put_ProfileDirectory_Proxy( 
    IWMEncProfileCollection __RPC_FAR * This,
    /* [in] */ BSTR bstrDirectory);


void __RPC_STUB IWMEncProfileCollection_put_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_get__NewEnum_Proxy( 
    IWMEncProfileCollection __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);


void __RPC_STUB IWMEncProfileCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_Item_Proxy( 
    IWMEncProfileCollection __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IWMEncProfile __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IWMEncProfileCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_Refresh_Proxy( 
    IWMEncProfileCollection __RPC_FAR * This);


void __RPC_STUB IWMEncProfileCollection_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncProfileCollection_INTERFACE_DEFINED__ */


#ifndef __IWMEncFile_INTERFACE_DEFINED__
#define __IWMEncFile_INTERFACE_DEFINED__

/* interface IWMEncFile */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B607B-BBC6-11D2-A329-006097C4E476")
    IWMEncFile : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalFileName( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteFileName( 
            /* [in] */ BSTR bstrFileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncFile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncFile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncFile __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncFile __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncFile __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalFileName )( 
            IWMEncFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalFileName )( 
            IWMEncFile __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteFileName )( 
            IWMEncFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteFileName )( 
            IWMEncFile __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName);
        
        END_INTERFACE
    } IWMEncFileVtbl;

    interface IWMEncFile
    {
        CONST_VTBL struct IWMEncFileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncFile_get_LocalFileName(This,pbstrFileName)	\
    (This)->lpVtbl -> get_LocalFileName(This,pbstrFileName)

#define IWMEncFile_put_LocalFileName(This,bstrFileName)	\
    (This)->lpVtbl -> put_LocalFileName(This,bstrFileName)

#define IWMEncFile_get_RemoteFileName(This,pbstrFileName)	\
    (This)->lpVtbl -> get_RemoteFileName(This,pbstrFileName)

#define IWMEncFile_put_RemoteFileName(This,bstrFileName)	\
    (This)->lpVtbl -> put_RemoteFileName(This,bstrFileName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFile_get_LocalFileName_Proxy( 
    IWMEncFile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName);


void __RPC_STUB IWMEncFile_get_LocalFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFile_put_LocalFileName_Proxy( 
    IWMEncFile __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncFile_put_LocalFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFile_get_RemoteFileName_Proxy( 
    IWMEncFile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName);


void __RPC_STUB IWMEncFile_get_RemoteFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFile_put_RemoteFileName_Proxy( 
    IWMEncFile __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncFile_put_RemoteFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncFile_INTERFACE_DEFINED__ */


#ifndef __IWMEncBroadcast_INTERFACE_DEFINED__
#define __IWMEncBroadcast_INTERFACE_DEFINED__

/* interface IWMEncBroadcast */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncBroadcast;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B607D-BBC6-11D2-A329-006097C4E476")
    IWMEncBroadcast : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PortNumber( 
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [retval][out] */ long __RPC_FAR *piPort) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PortNumber( 
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [in] */ long iPort) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncBroadcastVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncBroadcast __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncBroadcast __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncBroadcast __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncBroadcast __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncBroadcast __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncBroadcast __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncBroadcast __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PortNumber )( 
            IWMEncBroadcast __RPC_FAR * This,
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [retval][out] */ long __RPC_FAR *piPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PortNumber )( 
            IWMEncBroadcast __RPC_FAR * This,
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [in] */ long iPort);
        
        END_INTERFACE
    } IWMEncBroadcastVtbl;

    interface IWMEncBroadcast
    {
        CONST_VTBL struct IWMEncBroadcastVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncBroadcast_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncBroadcast_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncBroadcast_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncBroadcast_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncBroadcast_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncBroadcast_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncBroadcast_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncBroadcast_get_PortNumber(This,enumProtocol,piPort)	\
    (This)->lpVtbl -> get_PortNumber(This,enumProtocol,piPort)

#define IWMEncBroadcast_put_PortNumber(This,enumProtocol,iPort)	\
    (This)->lpVtbl -> put_PortNumber(This,enumProtocol,iPort)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBroadcast_get_PortNumber_Proxy( 
    IWMEncBroadcast __RPC_FAR * This,
    /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
    /* [retval][out] */ long __RPC_FAR *piPort);


void __RPC_STUB IWMEncBroadcast_get_PortNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBroadcast_put_PortNumber_Proxy( 
    IWMEncBroadcast __RPC_FAR * This,
    /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
    /* [in] */ long iPort);


void __RPC_STUB IWMEncBroadcast_put_PortNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncBroadcast_INTERFACE_DEFINED__ */


#ifndef __IWMEncDataViewCollection_INTERFACE_DEFINED__
#define __IWMEncDataViewCollection_INTERFACE_DEFINED__

/* interface IWMEncDataViewCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDataViewCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AE18C55-DB2E-11D2-A34A-006097C4E476")
    IWMEncDataViewCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataView,
            /* [retval][out] */ long __RPC_FAR *plStreamCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IUnknown __RPC_FAR *pDataView,
            /* [retval][out] */ long __RPC_FAR *plStreamCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long lStreamCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDataViewCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncDataViewCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncDataViewCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [in] */ long Index,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataView,
            /* [retval][out] */ long __RPC_FAR *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pDataView,
            /* [retval][out] */ long __RPC_FAR *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWMEncDataViewCollection __RPC_FAR * This,
            /* [in] */ long lStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )( 
            IWMEncDataViewCollection __RPC_FAR * This);
        
        END_INTERFACE
    } IWMEncDataViewCollectionVtbl;

    interface IWMEncDataViewCollection
    {
        CONST_VTBL struct IWMEncDataViewCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDataViewCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDataViewCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDataViewCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDataViewCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncDataViewCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncDataViewCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncDataViewCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncDataViewCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncDataViewCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncDataViewCollection_Item(This,Index,ppDataView,plStreamCookie)	\
    (This)->lpVtbl -> Item(This,Index,ppDataView,plStreamCookie)

#define IWMEncDataViewCollection_Add(This,pDataView,plStreamCookie)	\
    (This)->lpVtbl -> Add(This,pDataView,plStreamCookie)

#define IWMEncDataViewCollection_Remove(This,lStreamCookie)	\
    (This)->lpVtbl -> Remove(This,lStreamCookie)

#define IWMEncDataViewCollection_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_get_length_Proxy( 
    IWMEncDataViewCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncDataViewCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_get_Count_Proxy( 
    IWMEncDataViewCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncDataViewCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_Item_Proxy( 
    IWMEncDataViewCollection __RPC_FAR * This,
    /* [in] */ long Index,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataView,
    /* [retval][out] */ long __RPC_FAR *plStreamCookie);


void __RPC_STUB IWMEncDataViewCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_Add_Proxy( 
    IWMEncDataViewCollection __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pDataView,
    /* [retval][out] */ long __RPC_FAR *plStreamCookie);


void __RPC_STUB IWMEncDataViewCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_Remove_Proxy( 
    IWMEncDataViewCollection __RPC_FAR * This,
    /* [in] */ long lStreamCookie);


void __RPC_STUB IWMEncDataViewCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_RemoveAll_Proxy( 
    IWMEncDataViewCollection __RPC_FAR * This);


void __RPC_STUB IWMEncDataViewCollection_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDataViewCollection_INTERFACE_DEFINED__ */


#ifndef __IWMEncPostViewCollection_INTERFACE_DEFINED__
#define __IWMEncPostViewCollection_INTERFACE_DEFINED__

/* interface IWMEncPostViewCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncPostViewCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B712593-B68C-40dc-80C3-4124BEA9216A")
    IWMEncPostViewCollection : public IWMEncDataViewCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ViewBandwidth( 
            /* [retval][out] */ long __RPC_FAR *plBandwidth) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ViewBandwidth( 
            /* [in] */ long lBandwidth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPostViewCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncPostViewCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncPostViewCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ long Index,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataView,
            /* [retval][out] */ long __RPC_FAR *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pDataView,
            /* [retval][out] */ long __RPC_FAR *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ long lStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )( 
            IWMEncPostViewCollection __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ViewBandwidth )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plBandwidth);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ViewBandwidth )( 
            IWMEncPostViewCollection __RPC_FAR * This,
            /* [in] */ long lBandwidth);
        
        END_INTERFACE
    } IWMEncPostViewCollectionVtbl;

    interface IWMEncPostViewCollection
    {
        CONST_VTBL struct IWMEncPostViewCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncPostViewCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncPostViewCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncPostViewCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncPostViewCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncPostViewCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncPostViewCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncPostViewCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncPostViewCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncPostViewCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncPostViewCollection_Item(This,Index,ppDataView,plStreamCookie)	\
    (This)->lpVtbl -> Item(This,Index,ppDataView,plStreamCookie)

#define IWMEncPostViewCollection_Add(This,pDataView,plStreamCookie)	\
    (This)->lpVtbl -> Add(This,pDataView,plStreamCookie)

#define IWMEncPostViewCollection_Remove(This,lStreamCookie)	\
    (This)->lpVtbl -> Remove(This,lStreamCookie)

#define IWMEncPostViewCollection_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)


#define IWMEncPostViewCollection_get_ViewBandwidth(This,plBandwidth)	\
    (This)->lpVtbl -> get_ViewBandwidth(This,plBandwidth)

#define IWMEncPostViewCollection_put_ViewBandwidth(This,lBandwidth)	\
    (This)->lpVtbl -> put_ViewBandwidth(This,lBandwidth)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPostViewCollection_get_ViewBandwidth_Proxy( 
    IWMEncPostViewCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plBandwidth);


void __RPC_STUB IWMEncPostViewCollection_get_ViewBandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncPostViewCollection_put_ViewBandwidth_Proxy( 
    IWMEncPostViewCollection __RPC_FAR * This,
    /* [in] */ long lBandwidth);


void __RPC_STUB IWMEncPostViewCollection_put_ViewBandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncPostViewCollection_INTERFACE_DEFINED__ */


#ifndef __IWMEncSource_INTERFACE_DEFINED__
#define __IWMEncSource_INTERFACE_DEFINED__

/* interface IWMEncSource */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6084-BBC6-11D2-A329-006097C4E476")
    IWMEncSource : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ WMENC_SOURCE_TYPE __RPC_FAR *enumType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInput( 
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme = L"",
            /* [defaultvalue][in] */ BSTR bstrStreamName = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInput( 
            /* [out] */ BSTR __RPC_FAR *bstrStreamName,
            /* [out] */ BSTR __RPC_FAR *bstrScheme,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInput) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Repeat( 
            /* [in] */ VARIANT_BOOL bRepeat) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Repeat( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRepeat) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkIn( 
            /* [retval][out] */ long __RPC_FAR *plMarkIn) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkIn( 
            /* [in] */ long lMarkIn) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkOut( 
            /* [retval][out] */ long __RPC_FAR *plMarkOut) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkOut( 
            /* [in] */ long lMarkOut) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransformCollection( 
            /* [retval][out] */ IWMEncTransformCollection __RPC_FAR *__RPC_FAR *ppTransformCollection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransformPluginCount( 
            /* [out] */ DWORD __RPC_FAR *pdwCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransformPlugin( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkTransformPlugin) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreviewCollection( 
            /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PostviewCollection( 
            /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSourcePlugin( 
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncSource __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IWMEncSource __RPC_FAR * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE __RPC_FAR *enumType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInput )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrStreamName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInput )( 
            IWMEncSource __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *bstrStreamName,
            /* [out] */ BSTR __RPC_FAR *bstrScheme,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Repeat )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Repeat )( 
            IWMEncSource __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarkIn )( 
            IWMEncSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMarkIn);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarkIn )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ long lMarkIn);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarkOut )( 
            IWMEncSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMarkOut);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarkOut )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ long lMarkOut);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransformCollection )( 
            IWMEncSource __RPC_FAR * This,
            /* [retval][out] */ IWMEncTransformCollection __RPC_FAR *__RPC_FAR *ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformPluginCount )( 
            IWMEncSource __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformPlugin )( 
            IWMEncSource __RPC_FAR * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkTransformPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreviewCollection )( 
            IWMEncSource __RPC_FAR * This,
            /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostviewCollection )( 
            IWMEncSource __RPC_FAR * This,
            /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourcePlugin )( 
            IWMEncSource __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin);
        
        END_INTERFACE
    } IWMEncSourceVtbl;

    interface IWMEncSource
    {
        CONST_VTBL struct IWMEncSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncSource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncSource_get_Type(This,enumType)	\
    (This)->lpVtbl -> get_Type(This,enumType)

#define IWMEncSource_SetInput(This,bstrInput,bstrScheme,bstrStreamName)	\
    (This)->lpVtbl -> SetInput(This,bstrInput,bstrScheme,bstrStreamName)

#define IWMEncSource_GetInput(This,bstrStreamName,bstrScheme,pbstrInput)	\
    (This)->lpVtbl -> GetInput(This,bstrStreamName,bstrScheme,pbstrInput)

#define IWMEncSource_put_Repeat(This,bRepeat)	\
    (This)->lpVtbl -> put_Repeat(This,bRepeat)

#define IWMEncSource_get_Repeat(This,pbRepeat)	\
    (This)->lpVtbl -> get_Repeat(This,pbRepeat)

#define IWMEncSource_get_MarkIn(This,plMarkIn)	\
    (This)->lpVtbl -> get_MarkIn(This,plMarkIn)

#define IWMEncSource_put_MarkIn(This,lMarkIn)	\
    (This)->lpVtbl -> put_MarkIn(This,lMarkIn)

#define IWMEncSource_get_MarkOut(This,plMarkOut)	\
    (This)->lpVtbl -> get_MarkOut(This,plMarkOut)

#define IWMEncSource_put_MarkOut(This,lMarkOut)	\
    (This)->lpVtbl -> put_MarkOut(This,lMarkOut)

#define IWMEncSource_get_TransformCollection(This,ppTransformCollection)	\
    (This)->lpVtbl -> get_TransformCollection(This,ppTransformCollection)

#define IWMEncSource_GetTransformPluginCount(This,pdwCount)	\
    (This)->lpVtbl -> GetTransformPluginCount(This,pdwCount)

#define IWMEncSource_GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)	\
    (This)->lpVtbl -> GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)

#define IWMEncSource_get_PreviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PreviewCollection(This,ppDataViewCollection)

#define IWMEncSource_get_PostviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PostviewCollection(This,ppDataViewCollection)

#define IWMEncSource_GetSourcePlugin(This,ppUnkPlugin)	\
    (This)->lpVtbl -> GetSourcePlugin(This,ppUnkPlugin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_Type_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [retval][out] */ WMENC_SOURCE_TYPE __RPC_FAR *enumType);


void __RPC_STUB IWMEncSource_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_SetInput_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [in] */ BSTR bstrInput,
    /* [defaultvalue][in] */ BSTR bstrScheme,
    /* [defaultvalue][in] */ BSTR bstrStreamName);


void __RPC_STUB IWMEncSource_SetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetInput_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *bstrStreamName,
    /* [out] */ BSTR __RPC_FAR *bstrScheme,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrInput);


void __RPC_STUB IWMEncSource_GetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSource_put_Repeat_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bRepeat);


void __RPC_STUB IWMEncSource_put_Repeat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_Repeat_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRepeat);


void __RPC_STUB IWMEncSource_get_Repeat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_MarkIn_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMarkIn);


void __RPC_STUB IWMEncSource_get_MarkIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSource_put_MarkIn_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [in] */ long lMarkIn);


void __RPC_STUB IWMEncSource_put_MarkIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_MarkOut_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plMarkOut);


void __RPC_STUB IWMEncSource_get_MarkOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSource_put_MarkOut_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [in] */ long lMarkOut);


void __RPC_STUB IWMEncSource_put_MarkOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_TransformCollection_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [retval][out] */ IWMEncTransformCollection __RPC_FAR *__RPC_FAR *ppTransformCollection);


void __RPC_STUB IWMEncSource_get_TransformCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetTransformPluginCount_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwCount);


void __RPC_STUB IWMEncSource_GetTransformPluginCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetTransformPlugin_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [in] */ DWORD dwIndex,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkTransformPlugin);


void __RPC_STUB IWMEncSource_GetTransformPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_PreviewCollection_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection);


void __RPC_STUB IWMEncSource_get_PreviewCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_PostviewCollection_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection);


void __RPC_STUB IWMEncSource_get_PostviewCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetSourcePlugin_Proxy( 
    IWMEncSource __RPC_FAR * This,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin);


void __RPC_STUB IWMEncSource_GetSourcePlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSource_INTERFACE_DEFINED__ */


#ifndef __IWMEncVideoSource_INTERFACE_DEFINED__
#define __IWMEncVideoSource_INTERFACE_DEFINED__

/* interface IWMEncVideoSource */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncVideoSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6086-BBC6-11D2-A329-006097C4E476")
    IWMEncVideoSource : public IWMEncSource
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingMode( 
            /* [retval][out] */ WMENC_CROPPING_MODE __RPC_FAR *penumCroppingMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingMode( 
            /* [in] */ WMENC_CROPPING_MODE enumCroppingMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingLeftMargin( 
            /* [retval][out] */ long __RPC_FAR *plLeft) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingLeftMargin( 
            /* [in] */ long lLeft) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingTopMargin( 
            /* [retval][out] */ long __RPC_FAR *plTop) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingTopMargin( 
            /* [in] */ long lTop) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingRightMargin( 
            /* [retval][out] */ long __RPC_FAR *plRight) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingRightMargin( 
            /* [in] */ long lRight) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingBottomMargin( 
            /* [retval][out] */ long __RPC_FAR *plBottom) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingBottomMargin( 
            /* [in] */ long lBottom) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Optimization( 
            /* [retval][out] */ WMENC_VIDEO_OPTIMIZATION __RPC_FAR *penumOptimization) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Optimization( 
            /* [in] */ WMENC_VIDEO_OPTIMIZATION enumOptimization) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PixelFormat( 
            /* [retval][out] */ WMENC_PIXELFORMAT_VIDEO __RPC_FAR *penumPixelFormat) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PixelFormat( 
            /* [in] */ WMENC_PIXELFORMAT_VIDEO enumPixelFormat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncVideoSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncVideoSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncVideoSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE __RPC_FAR *enumType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInput )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrStreamName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInput )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *bstrStreamName,
            /* [out] */ BSTR __RPC_FAR *bstrScheme,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Repeat )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Repeat )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarkIn )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMarkIn);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarkIn )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ long lMarkIn);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarkOut )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plMarkOut);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarkOut )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ long lMarkOut);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransformCollection )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ IWMEncTransformCollection __RPC_FAR *__RPC_FAR *ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformPluginCount )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformPlugin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkTransformPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreviewCollection )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostviewCollection )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ IWMEncDataViewCollection __RPC_FAR *__RPC_FAR *ppDataViewCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourcePlugin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CroppingMode )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ WMENC_CROPPING_MODE __RPC_FAR *penumCroppingMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CroppingMode )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ WMENC_CROPPING_MODE enumCroppingMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CroppingLeftMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLeft);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CroppingLeftMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ long lLeft);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CroppingTopMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plTop);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CroppingTopMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ long lTop);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CroppingRightMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plRight);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CroppingRightMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ long lRight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CroppingBottomMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plBottom);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CroppingBottomMargin )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ long lBottom);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Optimization )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ WMENC_VIDEO_OPTIMIZATION __RPC_FAR *penumOptimization);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Optimization )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ WMENC_VIDEO_OPTIMIZATION enumOptimization);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PixelFormat )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [retval][out] */ WMENC_PIXELFORMAT_VIDEO __RPC_FAR *penumPixelFormat);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PixelFormat )( 
            IWMEncVideoSource __RPC_FAR * This,
            /* [in] */ WMENC_PIXELFORMAT_VIDEO enumPixelFormat);
        
        END_INTERFACE
    } IWMEncVideoSourceVtbl;

    interface IWMEncVideoSource
    {
        CONST_VTBL struct IWMEncVideoSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncVideoSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncVideoSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncVideoSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncVideoSource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncVideoSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncVideoSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncVideoSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncVideoSource_get_Type(This,enumType)	\
    (This)->lpVtbl -> get_Type(This,enumType)

#define IWMEncVideoSource_SetInput(This,bstrInput,bstrScheme,bstrStreamName)	\
    (This)->lpVtbl -> SetInput(This,bstrInput,bstrScheme,bstrStreamName)

#define IWMEncVideoSource_GetInput(This,bstrStreamName,bstrScheme,pbstrInput)	\
    (This)->lpVtbl -> GetInput(This,bstrStreamName,bstrScheme,pbstrInput)

#define IWMEncVideoSource_put_Repeat(This,bRepeat)	\
    (This)->lpVtbl -> put_Repeat(This,bRepeat)

#define IWMEncVideoSource_get_Repeat(This,pbRepeat)	\
    (This)->lpVtbl -> get_Repeat(This,pbRepeat)

#define IWMEncVideoSource_get_MarkIn(This,plMarkIn)	\
    (This)->lpVtbl -> get_MarkIn(This,plMarkIn)

#define IWMEncVideoSource_put_MarkIn(This,lMarkIn)	\
    (This)->lpVtbl -> put_MarkIn(This,lMarkIn)

#define IWMEncVideoSource_get_MarkOut(This,plMarkOut)	\
    (This)->lpVtbl -> get_MarkOut(This,plMarkOut)

#define IWMEncVideoSource_put_MarkOut(This,lMarkOut)	\
    (This)->lpVtbl -> put_MarkOut(This,lMarkOut)

#define IWMEncVideoSource_get_TransformCollection(This,ppTransformCollection)	\
    (This)->lpVtbl -> get_TransformCollection(This,ppTransformCollection)

#define IWMEncVideoSource_GetTransformPluginCount(This,pdwCount)	\
    (This)->lpVtbl -> GetTransformPluginCount(This,pdwCount)

#define IWMEncVideoSource_GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)	\
    (This)->lpVtbl -> GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)

#define IWMEncVideoSource_get_PreviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PreviewCollection(This,ppDataViewCollection)

#define IWMEncVideoSource_get_PostviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PostviewCollection(This,ppDataViewCollection)

#define IWMEncVideoSource_GetSourcePlugin(This,ppUnkPlugin)	\
    (This)->lpVtbl -> GetSourcePlugin(This,ppUnkPlugin)


#define IWMEncVideoSource_get_CroppingMode(This,penumCroppingMode)	\
    (This)->lpVtbl -> get_CroppingMode(This,penumCroppingMode)

#define IWMEncVideoSource_put_CroppingMode(This,enumCroppingMode)	\
    (This)->lpVtbl -> put_CroppingMode(This,enumCroppingMode)

#define IWMEncVideoSource_get_CroppingLeftMargin(This,plLeft)	\
    (This)->lpVtbl -> get_CroppingLeftMargin(This,plLeft)

#define IWMEncVideoSource_put_CroppingLeftMargin(This,lLeft)	\
    (This)->lpVtbl -> put_CroppingLeftMargin(This,lLeft)

#define IWMEncVideoSource_get_CroppingTopMargin(This,plTop)	\
    (This)->lpVtbl -> get_CroppingTopMargin(This,plTop)

#define IWMEncVideoSource_put_CroppingTopMargin(This,lTop)	\
    (This)->lpVtbl -> put_CroppingTopMargin(This,lTop)

#define IWMEncVideoSource_get_CroppingRightMargin(This,plRight)	\
    (This)->lpVtbl -> get_CroppingRightMargin(This,plRight)

#define IWMEncVideoSource_put_CroppingRightMargin(This,lRight)	\
    (This)->lpVtbl -> put_CroppingRightMargin(This,lRight)

#define IWMEncVideoSource_get_CroppingBottomMargin(This,plBottom)	\
    (This)->lpVtbl -> get_CroppingBottomMargin(This,plBottom)

#define IWMEncVideoSource_put_CroppingBottomMargin(This,lBottom)	\
    (This)->lpVtbl -> put_CroppingBottomMargin(This,lBottom)

#define IWMEncVideoSource_get_Optimization(This,penumOptimization)	\
    (This)->lpVtbl -> get_Optimization(This,penumOptimization)

#define IWMEncVideoSource_put_Optimization(This,enumOptimization)	\
    (This)->lpVtbl -> put_Optimization(This,enumOptimization)

#define IWMEncVideoSource_get_PixelFormat(This,penumPixelFormat)	\
    (This)->lpVtbl -> get_PixelFormat(This,penumPixelFormat)

#define IWMEncVideoSource_put_PixelFormat(This,enumPixelFormat)	\
    (This)->lpVtbl -> put_PixelFormat(This,enumPixelFormat)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingMode_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [retval][out] */ WMENC_CROPPING_MODE __RPC_FAR *penumCroppingMode);


void __RPC_STUB IWMEncVideoSource_get_CroppingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingMode_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [in] */ WMENC_CROPPING_MODE enumCroppingMode);


void __RPC_STUB IWMEncVideoSource_put_CroppingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingLeftMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLeft);


void __RPC_STUB IWMEncVideoSource_get_CroppingLeftMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingLeftMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [in] */ long lLeft);


void __RPC_STUB IWMEncVideoSource_put_CroppingLeftMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingTopMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plTop);


void __RPC_STUB IWMEncVideoSource_get_CroppingTopMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingTopMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [in] */ long lTop);


void __RPC_STUB IWMEncVideoSource_put_CroppingTopMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingRightMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plRight);


void __RPC_STUB IWMEncVideoSource_get_CroppingRightMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingRightMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [in] */ long lRight);


void __RPC_STUB IWMEncVideoSource_put_CroppingRightMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingBottomMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plBottom);


void __RPC_STUB IWMEncVideoSource_get_CroppingBottomMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingBottomMargin_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [in] */ long lBottom);


void __RPC_STUB IWMEncVideoSource_put_CroppingBottomMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_Optimization_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [retval][out] */ WMENC_VIDEO_OPTIMIZATION __RPC_FAR *penumOptimization);


void __RPC_STUB IWMEncVideoSource_get_Optimization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_Optimization_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [in] */ WMENC_VIDEO_OPTIMIZATION enumOptimization);


void __RPC_STUB IWMEncVideoSource_put_Optimization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_PixelFormat_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [retval][out] */ WMENC_PIXELFORMAT_VIDEO __RPC_FAR *penumPixelFormat);


void __RPC_STUB IWMEncVideoSource_get_PixelFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_PixelFormat_Proxy( 
    IWMEncVideoSource __RPC_FAR * This,
    /* [in] */ WMENC_PIXELFORMAT_VIDEO enumPixelFormat);


void __RPC_STUB IWMEncVideoSource_put_PixelFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncVideoSource_INTERFACE_DEFINED__ */


#ifndef __IWMEncSourceGroup_INTERFACE_DEFINED__
#define __IWMEncSourceGroup_INTERFACE_DEFINED__

/* interface IWMEncSourceGroup */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncSourceGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6071-BBC6-11D2-A329-006097C4E476")
    IWMEncSourceGroup : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceCount( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short __RPC_FAR *iSourceCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Source( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iIndex,
            /* [retval][out] */ IWMEncSource __RPC_FAR *__RPC_FAR *ppSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSource( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ IWMEncSource __RPC_FAR *__RPC_FAR *ppSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveSource( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IWMEncProfile __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Profile( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudienceCollection( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAudienceCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoArchive( 
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [retval][out] */ WMENC_ARCHIVE_OPERATION __RPC_FAR *penumArchiveOp) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoArchive( 
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoSetFileSource( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PrepareToEncode( 
            VARIANT_BOOL bPrepare) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GroupTransformCollection( 
            /* [retval][out] */ IWMEncTransformCollection __RPC_FAR *__RPC_FAR *ppTransformCollection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGroupTransformPluginCount( 
            /* [out] */ DWORD __RPC_FAR *pdwCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGroupTransformPlugin( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourceGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncSourceGroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncSourceGroup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourceCount )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short __RPC_FAR *iSourceCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Source )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iIndex,
            /* [retval][out] */ IWMEncSource __RPC_FAR *__RPC_FAR *ppSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSource )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ IWMEncSource __RPC_FAR *__RPC_FAR *ppSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveSource )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [retval][out] */ IWMEncProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Profile )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudienceCollection )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAudienceCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoArchive )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [retval][out] */ WMENC_ARCHIVE_OPERATION __RPC_FAR *penumArchiveOp);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoArchive )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutoSetFileSource )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareToEncode )( 
            IWMEncSourceGroup __RPC_FAR * This,
            VARIANT_BOOL bPrepare);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GroupTransformCollection )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [retval][out] */ IWMEncTransformCollection __RPC_FAR *__RPC_FAR *ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGroupTransformPluginCount )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGroupTransformPlugin )( 
            IWMEncSourceGroup __RPC_FAR * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin);
        
        END_INTERFACE
    } IWMEncSourceGroupVtbl;

    interface IWMEncSourceGroup
    {
        CONST_VTBL struct IWMEncSourceGroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncSourceGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncSourceGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncSourceGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncSourceGroup_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncSourceGroup_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncSourceGroup_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncSourceGroup_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncSourceGroup_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IWMEncSourceGroup_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IWMEncSourceGroup_get_SourceCount(This,enumType,iSourceCount)	\
    (This)->lpVtbl -> get_SourceCount(This,enumType,iSourceCount)

#define IWMEncSourceGroup_get_Source(This,enumType,iIndex,ppSource)	\
    (This)->lpVtbl -> get_Source(This,enumType,iIndex,ppSource)

#define IWMEncSourceGroup_AddSource(This,enumType,ppSource)	\
    (This)->lpVtbl -> AddSource(This,enumType,ppSource)

#define IWMEncSourceGroup_RemoveSource(This,enumType,var)	\
    (This)->lpVtbl -> RemoveSource(This,enumType,var)

#define IWMEncSourceGroup_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IWMEncSourceGroup_put_Profile(This,var)	\
    (This)->lpVtbl -> put_Profile(This,var)

#define IWMEncSourceGroup_get_AudienceCollection(This,ppAudienceCollection)	\
    (This)->lpVtbl -> get_AudienceCollection(This,ppAudienceCollection)

#define IWMEncSourceGroup_get_AutoArchive(This,enumArchiveType,penumArchiveOp)	\
    (This)->lpVtbl -> get_AutoArchive(This,enumArchiveType,penumArchiveOp)

#define IWMEncSourceGroup_put_AutoArchive(This,enumArchiveType,enumArchiveOp)	\
    (This)->lpVtbl -> put_AutoArchive(This,enumArchiveType,enumArchiveOp)

#define IWMEncSourceGroup_AutoSetFileSource(This,bstrFileName)	\
    (This)->lpVtbl -> AutoSetFileSource(This,bstrFileName)

#define IWMEncSourceGroup_PrepareToEncode(This,bPrepare)	\
    (This)->lpVtbl -> PrepareToEncode(This,bPrepare)

#define IWMEncSourceGroup_get_GroupTransformCollection(This,ppTransformCollection)	\
    (This)->lpVtbl -> get_GroupTransformCollection(This,ppTransformCollection)

#define IWMEncSourceGroup_GetGroupTransformPluginCount(This,pdwCount)	\
    (This)->lpVtbl -> GetGroupTransformPluginCount(This,pdwCount)

#define IWMEncSourceGroup_GetGroupTransformPlugin(This,dwIndex,ppUnkPlugin)	\
    (This)->lpVtbl -> GetGroupTransformPlugin(This,dwIndex,ppUnkPlugin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_Name_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IWMEncSourceGroup_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_put_Name_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IWMEncSourceGroup_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_SourceCount_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [retval][out] */ short __RPC_FAR *iSourceCount);


void __RPC_STUB IWMEncSourceGroup_get_SourceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_Source_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ short iIndex,
    /* [retval][out] */ IWMEncSource __RPC_FAR *__RPC_FAR *ppSource);


void __RPC_STUB IWMEncSourceGroup_get_Source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_AddSource_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [retval][out] */ IWMEncSource __RPC_FAR *__RPC_FAR *ppSource);


void __RPC_STUB IWMEncSourceGroup_AddSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_RemoveSource_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncSourceGroup_RemoveSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_Profile_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [retval][out] */ IWMEncProfile __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB IWMEncSourceGroup_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_put_Profile_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncSourceGroup_put_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_AudienceCollection_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAudienceCollection);


void __RPC_STUB IWMEncSourceGroup_get_AudienceCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_AutoArchive_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
    /* [retval][out] */ WMENC_ARCHIVE_OPERATION __RPC_FAR *penumArchiveOp);


void __RPC_STUB IWMEncSourceGroup_get_AutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_put_AutoArchive_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
    /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);


void __RPC_STUB IWMEncSourceGroup_put_AutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_AutoSetFileSource_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncSourceGroup_AutoSetFileSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_PrepareToEncode_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    VARIANT_BOOL bPrepare);


void __RPC_STUB IWMEncSourceGroup_PrepareToEncode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_GroupTransformCollection_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [retval][out] */ IWMEncTransformCollection __RPC_FAR *__RPC_FAR *ppTransformCollection);


void __RPC_STUB IWMEncSourceGroup_get_GroupTransformCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_GetGroupTransformPluginCount_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwCount);


void __RPC_STUB IWMEncSourceGroup_GetGroupTransformPluginCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_GetGroupTransformPlugin_Proxy( 
    IWMEncSourceGroup __RPC_FAR * This,
    /* [in] */ DWORD dwIndex,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkPlugin);


void __RPC_STUB IWMEncSourceGroup_GetGroupTransformPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSourceGroup_INTERFACE_DEFINED__ */


#ifndef __IWMEncSourceGroupCollection_INTERFACE_DEFINED__
#define __IWMEncSourceGroupCollection_INTERFACE_DEFINED__

/* interface IWMEncSourceGroupCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncSourceGroupCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B606F-BBC6-11D2-A329-006097C4E476")
    IWMEncSourceGroupCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroup,
            /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroupInfront) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Active( 
            /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Active( 
            /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroup) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourceGroupCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncSourceGroupCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncSourceGroupCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroup,
            /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroupInfront);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Active )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Active )( 
            IWMEncSourceGroupCollection __RPC_FAR * This,
            /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroup);
        
        END_INTERFACE
    } IWMEncSourceGroupCollectionVtbl;

    interface IWMEncSourceGroupCollection
    {
        CONST_VTBL struct IWMEncSourceGroupCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncSourceGroupCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncSourceGroupCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncSourceGroupCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncSourceGroupCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncSourceGroupCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncSourceGroupCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncSourceGroupCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncSourceGroupCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncSourceGroupCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncSourceGroupCollection_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncSourceGroupCollection_Item(This,var,ppSourceGroup)	\
    (This)->lpVtbl -> Item(This,var,ppSourceGroup)

#define IWMEncSourceGroupCollection_Add(This,bstrName,ppSourceGroup)	\
    (This)->lpVtbl -> Add(This,bstrName,ppSourceGroup)

#define IWMEncSourceGroupCollection_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define IWMEncSourceGroupCollection_Move(This,pSourceGroup,pSourceGroupInfront)	\
    (This)->lpVtbl -> Move(This,pSourceGroup,pSourceGroupInfront)

#define IWMEncSourceGroupCollection_get_Active(This,ppSourceGroup)	\
    (This)->lpVtbl -> get_Active(This,ppSourceGroup)

#define IWMEncSourceGroupCollection_put_Active(This,pSourceGroup)	\
    (This)->lpVtbl -> put_Active(This,pSourceGroup)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_get_length_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncSourceGroupCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_get_Count_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncSourceGroupCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_get__NewEnum_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pIUnknown);


void __RPC_STUB IWMEncSourceGroupCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Item_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Add_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Remove_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncSourceGroupCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Move_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroup,
    /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroupInfront);


void __RPC_STUB IWMEncSourceGroupCollection_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_get_Active_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [retval][out] */ IWMEncSourceGroup __RPC_FAR *__RPC_FAR *ppSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_get_Active_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_put_Active_Proxy( 
    IWMEncSourceGroupCollection __RPC_FAR * This,
    /* [in] */ IWMEncSourceGroup __RPC_FAR *pSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_put_Active_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSourceGroupCollection_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_wmencode_0260 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_wmencode_0260_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wmencode_0260_v0_0_s_ifspec;

#ifndef __IWMEncoder_INTERFACE_DEFINED__
#define __IWMEncoder_INTERFACE_DEFINED__

/* interface IWMEncoder */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B607F-BBC6-11D2-A329-006097C4E476")
    IWMEncoder : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLocaleID( 
            /* [in] */ long lLocaleID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoStop( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbStop) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoStop( 
            /* [in] */ VARIANT_BOOL bStop) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PrepareToEncode( 
            VARIANT_BOOL bPrepare) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Archive( 
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendScript( 
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrData) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableAutoArchive( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnableAutoArchive) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableAutoArchive( 
            /* [in] */ VARIANT_BOOL bEnableAutoArchive) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecordingLevel( 
            /* [in] */ short iIndex,
            /* [retval][out] */ long __RPC_FAR *lLevel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordingLevel( 
            /* [in] */ short iIndex,
            /* [in] */ long lLevel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecordingMute( 
            /* [in] */ short iIndex,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRecordMute) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordingMute( 
            /* [in] */ short iIndex,
            /* [in] */ VARIANT_BOOL bRecordMute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioLevel( 
            /* [in] */ WMENC_AUDIOLEVEL_UNITS units,
            /* [in] */ short iIndex,
            /* [out][in] */ long __RPC_FAR *plDuration,
            /* [out] */ double __RPC_FAR *pdLMin,
            /* [out] */ double __RPC_FAR *pdLAvg,
            /* [out] */ double __RPC_FAR *pdLMax,
            /* [out] */ double __RPC_FAR *pdRMin,
            /* [out] */ double __RPC_FAR *pdRAvg,
            /* [out] */ double __RPC_FAR *pdRMax) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceGroupCollection( 
            /* [retval][out] */ IWMEncSourceGroupCollection __RPC_FAR *__RPC_FAR *ppSourceGroupCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourcePluginInfoManager( 
            /* [retval][out] */ IWMEncSourcePluginInfoManager __RPC_FAR *__RPC_FAR *ppSourcePluginInfoManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransformPluginInfoManager( 
            /* [retval][out] */ IWMEncTransformPluginInfoManager __RPC_FAR *__RPC_FAR *ppTransformPluginInfoManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayInfo( 
            /* [retval][out] */ IWMEncDisplayInfo __RPC_FAR *__RPC_FAR *ppDisplayInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attributes( 
            /* [retval][out] */ IWMEncAttributes __RPC_FAR *__RPC_FAR *ppAttributes) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Broadcast( 
            /* [retval][out] */ IWMEncBroadcast __RPC_FAR *__RPC_FAR *ppBroadcast) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_File( 
            /* [retval][out] */ IWMEncFile __RPC_FAR *__RPC_FAR *ppFile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Statistics( 
            /* [retval][out] */ IWMEncStatistics __RPC_FAR *__RPC_FAR *ppStatistics) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileCollection( 
            /* [retval][out] */ IWMEncProfileCollection __RPC_FAR *__RPC_FAR *ppProfileCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RunState( 
            /* [retval][out] */ WMENC_ENCODER_STATE __RPC_FAR *penumState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorState( 
            /* [retval][out] */ long __RPC_FAR *plResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ArchiveState( 
            /* [in] */ WMENC_ARCHIVE_TYPE enumType,
            /* [retval][out] */ WMENC_ARCHIVE_STATE __RPC_FAR *penumArchiveState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteAdmin( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRemoteAdmin) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteAdmin( 
            /* [in] */ VARIANT_BOOL bRemoteAdmin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateBroadcastInfo( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexerState( 
            /* [retval][out] */ WMENC_INDEXER_STATE __RPC_FAR *penumIndexerState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoIndex( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbAutoIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoIndex( 
            /* [in] */ VARIANT_BOOL bAutoIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Indexer( 
            /* [in] */ WMENC_INDEXER_OPERATION enumIndexerOp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncoder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncoder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncoder __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocaleID )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ long lLocaleID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IWMEncoder __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IWMEncoder __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoStop )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbStop);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoStop )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bStop);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IWMEncoder __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareToEncode )( 
            IWMEncoder __RPC_FAR * This,
            VARIANT_BOOL bPrepare);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IWMEncoder __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Archive )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendScript )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableAutoArchive )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnableAutoArchive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableAutoArchive )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bEnableAutoArchive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecordingLevel )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ long __RPC_FAR *lLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RecordingLevel )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ short iIndex,
            /* [in] */ long lLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecordingMute )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRecordMute);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RecordingMute )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ short iIndex,
            /* [in] */ VARIANT_BOOL bRecordMute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioLevel )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ WMENC_AUDIOLEVEL_UNITS units,
            /* [in] */ short iIndex,
            /* [out][in] */ long __RPC_FAR *plDuration,
            /* [out] */ double __RPC_FAR *pdLMin,
            /* [out] */ double __RPC_FAR *pdLAvg,
            /* [out] */ double __RPC_FAR *pdLMax,
            /* [out] */ double __RPC_FAR *pdRMin,
            /* [out] */ double __RPC_FAR *pdRAvg,
            /* [out] */ double __RPC_FAR *pdRMax);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourceGroupCollection )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncSourceGroupCollection __RPC_FAR *__RPC_FAR *ppSourceGroupCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourcePluginInfoManager )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncSourcePluginInfoManager __RPC_FAR *__RPC_FAR *ppSourcePluginInfoManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransformPluginInfoManager )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncTransformPluginInfoManager __RPC_FAR *__RPC_FAR *ppTransformPluginInfoManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayInfo )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncDisplayInfo __RPC_FAR *__RPC_FAR *ppDisplayInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncAttributes __RPC_FAR *__RPC_FAR *ppAttributes);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Broadcast )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncBroadcast __RPC_FAR *__RPC_FAR *ppBroadcast);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_File )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncFile __RPC_FAR *__RPC_FAR *ppFile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Statistics )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncStatistics __RPC_FAR *__RPC_FAR *ppStatistics);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProfileCollection )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ IWMEncProfileCollection __RPC_FAR *__RPC_FAR *ppProfileCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RunState )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ WMENC_ENCODER_STATE __RPC_FAR *penumState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorState )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ArchiveState )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumType,
            /* [retval][out] */ WMENC_ARCHIVE_STATE __RPC_FAR *penumArchiveState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteAdmin )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRemoteAdmin);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteAdmin )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bRemoteAdmin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateBroadcastInfo )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IndexerState )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ WMENC_INDEXER_STATE __RPC_FAR *penumIndexerState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoIndex )( 
            IWMEncoder __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbAutoIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoIndex )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bAutoIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Indexer )( 
            IWMEncoder __RPC_FAR * This,
            /* [in] */ WMENC_INDEXER_OPERATION enumIndexerOp);
        
        END_INTERFACE
    } IWMEncoderVtbl;

    interface IWMEncoder
    {
        CONST_VTBL struct IWMEncoderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncoder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncoder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncoder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncoder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncoder_SetLocaleID(This,lLocaleID)	\
    (This)->lpVtbl -> SetLocaleID(This,lLocaleID)

#define IWMEncoder_Load(This,bstrFileName)	\
    (This)->lpVtbl -> Load(This,bstrFileName)

#define IWMEncoder_Save(This,bstrFileName)	\
    (This)->lpVtbl -> Save(This,bstrFileName)

#define IWMEncoder_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IWMEncoder_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWMEncoder_get_AutoStop(This,pbStop)	\
    (This)->lpVtbl -> get_AutoStop(This,pbStop)

#define IWMEncoder_put_AutoStop(This,bStop)	\
    (This)->lpVtbl -> put_AutoStop(This,bStop)

#define IWMEncoder_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IWMEncoder_PrepareToEncode(This,bPrepare)	\
    (This)->lpVtbl -> PrepareToEncode(This,bPrepare)

#define IWMEncoder_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IWMEncoder_Archive(This,enumArchiveType,enumArchiveOp)	\
    (This)->lpVtbl -> Archive(This,enumArchiveType,enumArchiveOp)

#define IWMEncoder_SendScript(This,iIndex,bstrType,bstrData)	\
    (This)->lpVtbl -> SendScript(This,iIndex,bstrType,bstrData)

#define IWMEncoder_get_EnableAutoArchive(This,pbEnableAutoArchive)	\
    (This)->lpVtbl -> get_EnableAutoArchive(This,pbEnableAutoArchive)

#define IWMEncoder_put_EnableAutoArchive(This,bEnableAutoArchive)	\
    (This)->lpVtbl -> put_EnableAutoArchive(This,bEnableAutoArchive)

#define IWMEncoder_get_RecordingLevel(This,iIndex,lLevel)	\
    (This)->lpVtbl -> get_RecordingLevel(This,iIndex,lLevel)

#define IWMEncoder_put_RecordingLevel(This,iIndex,lLevel)	\
    (This)->lpVtbl -> put_RecordingLevel(This,iIndex,lLevel)

#define IWMEncoder_get_RecordingMute(This,iIndex,pbRecordMute)	\
    (This)->lpVtbl -> get_RecordingMute(This,iIndex,pbRecordMute)

#define IWMEncoder_put_RecordingMute(This,iIndex,bRecordMute)	\
    (This)->lpVtbl -> put_RecordingMute(This,iIndex,bRecordMute)

#define IWMEncoder_GetAudioLevel(This,units,iIndex,plDuration,pdLMin,pdLAvg,pdLMax,pdRMin,pdRAvg,pdRMax)	\
    (This)->lpVtbl -> GetAudioLevel(This,units,iIndex,plDuration,pdLMin,pdLAvg,pdLMax,pdRMin,pdRAvg,pdRMax)

#define IWMEncoder_get_SourceGroupCollection(This,ppSourceGroupCollection)	\
    (This)->lpVtbl -> get_SourceGroupCollection(This,ppSourceGroupCollection)

#define IWMEncoder_get_SourcePluginInfoManager(This,ppSourcePluginInfoManager)	\
    (This)->lpVtbl -> get_SourcePluginInfoManager(This,ppSourcePluginInfoManager)

#define IWMEncoder_get_TransformPluginInfoManager(This,ppTransformPluginInfoManager)	\
    (This)->lpVtbl -> get_TransformPluginInfoManager(This,ppTransformPluginInfoManager)

#define IWMEncoder_get_DisplayInfo(This,ppDisplayInfo)	\
    (This)->lpVtbl -> get_DisplayInfo(This,ppDisplayInfo)

#define IWMEncoder_get_Attributes(This,ppAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,ppAttributes)

#define IWMEncoder_get_Broadcast(This,ppBroadcast)	\
    (This)->lpVtbl -> get_Broadcast(This,ppBroadcast)

#define IWMEncoder_get_File(This,ppFile)	\
    (This)->lpVtbl -> get_File(This,ppFile)

#define IWMEncoder_get_Statistics(This,ppStatistics)	\
    (This)->lpVtbl -> get_Statistics(This,ppStatistics)

#define IWMEncoder_get_ProfileCollection(This,ppProfileCollection)	\
    (This)->lpVtbl -> get_ProfileCollection(This,ppProfileCollection)

#define IWMEncoder_get_RunState(This,penumState)	\
    (This)->lpVtbl -> get_RunState(This,penumState)

#define IWMEncoder_get_ErrorState(This,plResult)	\
    (This)->lpVtbl -> get_ErrorState(This,plResult)

#define IWMEncoder_get_ArchiveState(This,enumType,penumArchiveState)	\
    (This)->lpVtbl -> get_ArchiveState(This,enumType,penumArchiveState)

#define IWMEncoder_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IWMEncoder_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IWMEncoder_get_RemoteAdmin(This,pbRemoteAdmin)	\
    (This)->lpVtbl -> get_RemoteAdmin(This,pbRemoteAdmin)

#define IWMEncoder_put_RemoteAdmin(This,bRemoteAdmin)	\
    (This)->lpVtbl -> put_RemoteAdmin(This,bRemoteAdmin)

#define IWMEncoder_GenerateBroadcastInfo(This,bstrFileName)	\
    (This)->lpVtbl -> GenerateBroadcastInfo(This,bstrFileName)

#define IWMEncoder_get_IndexerState(This,penumIndexerState)	\
    (This)->lpVtbl -> get_IndexerState(This,penumIndexerState)

#define IWMEncoder_get_AutoIndex(This,pbAutoIndex)	\
    (This)->lpVtbl -> get_AutoIndex(This,pbAutoIndex)

#define IWMEncoder_put_AutoIndex(This,bAutoIndex)	\
    (This)->lpVtbl -> put_AutoIndex(This,bAutoIndex)

#define IWMEncoder_Indexer(This,enumIndexerOp)	\
    (This)->lpVtbl -> Indexer(This,enumIndexerOp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_SetLocaleID_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ long lLocaleID);


void __RPC_STUB IWMEncoder_SetLocaleID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Load_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncoder_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Save_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncoder_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Start_Proxy( 
    IWMEncoder __RPC_FAR * This);


void __RPC_STUB IWMEncoder_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Stop_Proxy( 
    IWMEncoder __RPC_FAR * This);


void __RPC_STUB IWMEncoder_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_AutoStop_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbStop);


void __RPC_STUB IWMEncoder_get_AutoStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_AutoStop_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bStop);


void __RPC_STUB IWMEncoder_put_AutoStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Pause_Proxy( 
    IWMEncoder __RPC_FAR * This);


void __RPC_STUB IWMEncoder_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_PrepareToEncode_Proxy( 
    IWMEncoder __RPC_FAR * This,
    VARIANT_BOOL bPrepare);


void __RPC_STUB IWMEncoder_PrepareToEncode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Reset_Proxy( 
    IWMEncoder __RPC_FAR * This);


void __RPC_STUB IWMEncoder_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Archive_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
    /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);


void __RPC_STUB IWMEncoder_Archive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_SendScript_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ short iIndex,
    /* [in] */ BSTR bstrType,
    /* [in] */ BSTR bstrData);


void __RPC_STUB IWMEncoder_SendScript_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_EnableAutoArchive_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnableAutoArchive);


void __RPC_STUB IWMEncoder_get_EnableAutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_EnableAutoArchive_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bEnableAutoArchive);


void __RPC_STUB IWMEncoder_put_EnableAutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RecordingLevel_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ long __RPC_FAR *lLevel);


void __RPC_STUB IWMEncoder_get_RecordingLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_RecordingLevel_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ short iIndex,
    /* [in] */ long lLevel);


void __RPC_STUB IWMEncoder_put_RecordingLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RecordingMute_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRecordMute);


void __RPC_STUB IWMEncoder_get_RecordingMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_RecordingMute_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ short iIndex,
    /* [in] */ VARIANT_BOOL bRecordMute);


void __RPC_STUB IWMEncoder_put_RecordingMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_GetAudioLevel_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ WMENC_AUDIOLEVEL_UNITS units,
    /* [in] */ short iIndex,
    /* [out][in] */ long __RPC_FAR *plDuration,
    /* [out] */ double __RPC_FAR *pdLMin,
    /* [out] */ double __RPC_FAR *pdLAvg,
    /* [out] */ double __RPC_FAR *pdLMax,
    /* [out] */ double __RPC_FAR *pdRMin,
    /* [out] */ double __RPC_FAR *pdRAvg,
    /* [out] */ double __RPC_FAR *pdRMax);


void __RPC_STUB IWMEncoder_GetAudioLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_SourceGroupCollection_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncSourceGroupCollection __RPC_FAR *__RPC_FAR *ppSourceGroupCollection);


void __RPC_STUB IWMEncoder_get_SourceGroupCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_SourcePluginInfoManager_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncSourcePluginInfoManager __RPC_FAR *__RPC_FAR *ppSourcePluginInfoManager);


void __RPC_STUB IWMEncoder_get_SourcePluginInfoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_TransformPluginInfoManager_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncTransformPluginInfoManager __RPC_FAR *__RPC_FAR *ppTransformPluginInfoManager);


void __RPC_STUB IWMEncoder_get_TransformPluginInfoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_DisplayInfo_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncDisplayInfo __RPC_FAR *__RPC_FAR *ppDisplayInfo);


void __RPC_STUB IWMEncoder_get_DisplayInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Attributes_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncAttributes __RPC_FAR *__RPC_FAR *ppAttributes);


void __RPC_STUB IWMEncoder_get_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Broadcast_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncBroadcast __RPC_FAR *__RPC_FAR *ppBroadcast);


void __RPC_STUB IWMEncoder_get_Broadcast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_File_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncFile __RPC_FAR *__RPC_FAR *ppFile);


void __RPC_STUB IWMEncoder_get_File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Statistics_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncStatistics __RPC_FAR *__RPC_FAR *ppStatistics);


void __RPC_STUB IWMEncoder_get_Statistics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_ProfileCollection_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ IWMEncProfileCollection __RPC_FAR *__RPC_FAR *ppProfileCollection);


void __RPC_STUB IWMEncoder_get_ProfileCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RunState_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ WMENC_ENCODER_STATE __RPC_FAR *penumState);


void __RPC_STUB IWMEncoder_get_RunState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_ErrorState_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plResult);


void __RPC_STUB IWMEncoder_get_ErrorState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_ArchiveState_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumType,
    /* [retval][out] */ WMENC_ARCHIVE_STATE __RPC_FAR *penumArchiveState);


void __RPC_STUB IWMEncoder_get_ArchiveState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Name_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IWMEncoder_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_Name_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IWMEncoder_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RemoteAdmin_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRemoteAdmin);


void __RPC_STUB IWMEncoder_get_RemoteAdmin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_RemoteAdmin_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bRemoteAdmin);


void __RPC_STUB IWMEncoder_put_RemoteAdmin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_GenerateBroadcastInfo_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncoder_GenerateBroadcastInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_IndexerState_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ WMENC_INDEXER_STATE __RPC_FAR *penumIndexerState);


void __RPC_STUB IWMEncoder_get_IndexerState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_AutoIndex_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbAutoIndex);


void __RPC_STUB IWMEncoder_get_AutoIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_AutoIndex_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bAutoIndex);


void __RPC_STUB IWMEncoder_put_AutoIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Indexer_Proxy( 
    IWMEncoder __RPC_FAR * This,
    /* [in] */ WMENC_INDEXER_OPERATION enumIndexerOp);


void __RPC_STUB IWMEncoder_Indexer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncoder_INTERFACE_DEFINED__ */


#ifndef __IWMEncProfileManager_INTERFACE_DEFINED__
#define __IWMEncProfileManager_INTERFACE_DEFINED__

/* interface IWMEncProfileManager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncProfileManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("731B9D9E-6CF4-4C37-A6A9-A89B880D36EC")
    IWMEncProfileManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WMEncProfileList( 
            /* [in] */ WMENC_MEDIA_FILTER filter,
            /* [in] */ long lcid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WMEncProfileListEx( 
            /* [in] */ WMENC_MEDIA_FILTER filter,
            /* [in] */ WMENC_MEDIA_FILTER newDefault,
            /* [in] */ long lcid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WMEncProfileEdit( 
            /* [in] */ BSTR bstrProfileName,
            /* [in] */ WMENC_MEDIA_FILTER lfilter,
            /* [in] */ long lcid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDetailsString( 
            /* [in] */ BSTR bstrProfileName,
            /* [in] */ long lcid,
            /* [retval][out] */ BSTR __RPC_FAR *bstrDetailsString) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileDirectory( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrDirectory) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileDirectory( 
            /* [in] */ BSTR bstrDirectory) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastCreatedProfile( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrProfile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastEditedProfile( 
            /* [retval][out] */ BSTR __RPC_FAR *bstrProfile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncProfileManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncProfileManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncProfileManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WMEncProfileList )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ WMENC_MEDIA_FILTER filter,
            /* [in] */ long lcid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WMEncProfileListEx )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ WMENC_MEDIA_FILTER filter,
            /* [in] */ WMENC_MEDIA_FILTER newDefault,
            /* [in] */ long lcid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WMEncProfileEdit )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ BSTR bstrProfileName,
            /* [in] */ WMENC_MEDIA_FILTER lfilter,
            /* [in] */ long lcid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDetailsString )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ BSTR bstrProfileName,
            /* [in] */ long lcid,
            /* [retval][out] */ BSTR __RPC_FAR *bstrDetailsString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProfileDirectory )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProfileDirectory )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [in] */ BSTR bstrDirectory);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastCreatedProfile )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrProfile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastEditedProfile )( 
            IWMEncProfileManager __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *bstrProfile);
        
        END_INTERFACE
    } IWMEncProfileManagerVtbl;

    interface IWMEncProfileManager
    {
        CONST_VTBL struct IWMEncProfileManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncProfileManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncProfileManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncProfileManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncProfileManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncProfileManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncProfileManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncProfileManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncProfileManager_WMEncProfileList(This,filter,lcid)	\
    (This)->lpVtbl -> WMEncProfileList(This,filter,lcid)

#define IWMEncProfileManager_WMEncProfileListEx(This,filter,newDefault,lcid)	\
    (This)->lpVtbl -> WMEncProfileListEx(This,filter,newDefault,lcid)

#define IWMEncProfileManager_WMEncProfileEdit(This,bstrProfileName,lfilter,lcid)	\
    (This)->lpVtbl -> WMEncProfileEdit(This,bstrProfileName,lfilter,lcid)

#define IWMEncProfileManager_GetDetailsString(This,bstrProfileName,lcid,bstrDetailsString)	\
    (This)->lpVtbl -> GetDetailsString(This,bstrProfileName,lcid,bstrDetailsString)

#define IWMEncProfileManager_get_ProfileDirectory(This,bstrDirectory)	\
    (This)->lpVtbl -> get_ProfileDirectory(This,bstrDirectory)

#define IWMEncProfileManager_put_ProfileDirectory(This,bstrDirectory)	\
    (This)->lpVtbl -> put_ProfileDirectory(This,bstrDirectory)

#define IWMEncProfileManager_get_LastCreatedProfile(This,bstrProfile)	\
    (This)->lpVtbl -> get_LastCreatedProfile(This,bstrProfile)

#define IWMEncProfileManager_get_LastEditedProfile(This,bstrProfile)	\
    (This)->lpVtbl -> get_LastEditedProfile(This,bstrProfile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_WMEncProfileList_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [in] */ WMENC_MEDIA_FILTER filter,
    /* [in] */ long lcid);


void __RPC_STUB IWMEncProfileManager_WMEncProfileList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_WMEncProfileListEx_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [in] */ WMENC_MEDIA_FILTER filter,
    /* [in] */ WMENC_MEDIA_FILTER newDefault,
    /* [in] */ long lcid);


void __RPC_STUB IWMEncProfileManager_WMEncProfileListEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_WMEncProfileEdit_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [in] */ BSTR bstrProfileName,
    /* [in] */ WMENC_MEDIA_FILTER lfilter,
    /* [in] */ long lcid);


void __RPC_STUB IWMEncProfileManager_WMEncProfileEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_GetDetailsString_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [in] */ BSTR bstrProfileName,
    /* [in] */ long lcid,
    /* [retval][out] */ BSTR __RPC_FAR *bstrDetailsString);


void __RPC_STUB IWMEncProfileManager_GetDetailsString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_get_ProfileDirectory_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrDirectory);


void __RPC_STUB IWMEncProfileManager_get_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_put_ProfileDirectory_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [in] */ BSTR bstrDirectory);


void __RPC_STUB IWMEncProfileManager_put_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_get_LastCreatedProfile_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrProfile);


void __RPC_STUB IWMEncProfileManager_get_LastCreatedProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_get_LastEditedProfile_Proxy( 
    IWMEncProfileManager __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *bstrProfile);


void __RPC_STUB IWMEncProfileManager_get_LastEditedProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncProfileManager_INTERFACE_DEFINED__ */


#ifndef __IWMEncoderApp_INTERFACE_DEFINED__
#define __IWMEncoderApp_INTERFACE_DEFINED__

/* interface IWMEncoderApp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncoderApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6080-BBC6-11D2-A329-006097C4E476")
    IWMEncoderApp : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Encoder( 
            /* [retval][out] */ IWMEncoder __RPC_FAR *__RPC_FAR *ppEncoder) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UILock( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UILock( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayWidth( 
            /* [in] */ short iIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayHeight( 
            /* [in] */ short iIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ WMENCAPP_PROP_CLASS enumClass,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT __RPC_FAR *pValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetProperty( 
            /* [in] */ WMENCAPP_PROP_CLASS enumClass,
            /* [in] */ BSTR bstrProperty,
            /* [in] */ VARIANT Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveProperties( 
            /* [in] */ WMENCAPP_PROP_CLASS enumClass) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncoderAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncoderApp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncoderApp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Encoder )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [retval][out] */ IWMEncoder __RPC_FAR *__RPC_FAR *ppEncoder);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UILock )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UILock )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayWidth )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayHeight )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ WMENCAPP_PROP_CLASS enumClass,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT __RPC_FAR *pValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperty )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ WMENCAPP_PROP_CLASS enumClass,
            /* [in] */ BSTR bstrProperty,
            /* [in] */ VARIANT Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveProperties )( 
            IWMEncoderApp __RPC_FAR * This,
            /* [in] */ WMENCAPP_PROP_CLASS enumClass);
        
        END_INTERFACE
    } IWMEncoderAppVtbl;

    interface IWMEncoderApp
    {
        CONST_VTBL struct IWMEncoderAppVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncoderApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncoderApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncoderApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncoderApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncoderApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncoderApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncoderApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncoderApp_get_Encoder(This,ppEncoder)	\
    (This)->lpVtbl -> get_Encoder(This,ppEncoder)

#define IWMEncoderApp_get_Visible(This,pVal)	\
    (This)->lpVtbl -> get_Visible(This,pVal)

#define IWMEncoderApp_put_Visible(This,newVal)	\
    (This)->lpVtbl -> put_Visible(This,newVal)

#define IWMEncoderApp_get_Top(This,pVal)	\
    (This)->lpVtbl -> get_Top(This,pVal)

#define IWMEncoderApp_put_Top(This,newVal)	\
    (This)->lpVtbl -> put_Top(This,newVal)

#define IWMEncoderApp_get_Left(This,pVal)	\
    (This)->lpVtbl -> get_Left(This,pVal)

#define IWMEncoderApp_put_Left(This,newVal)	\
    (This)->lpVtbl -> put_Left(This,newVal)

#define IWMEncoderApp_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define IWMEncoderApp_put_Width(This,newVal)	\
    (This)->lpVtbl -> put_Width(This,newVal)

#define IWMEncoderApp_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define IWMEncoderApp_put_Height(This,newVal)	\
    (This)->lpVtbl -> put_Height(This,newVal)

#define IWMEncoderApp_get_UILock(This,pVal)	\
    (This)->lpVtbl -> get_UILock(This,pVal)

#define IWMEncoderApp_put_UILock(This,newVal)	\
    (This)->lpVtbl -> put_UILock(This,newVal)

#define IWMEncoderApp_get_DisplayWidth(This,iIndex,pVal)	\
    (This)->lpVtbl -> get_DisplayWidth(This,iIndex,pVal)

#define IWMEncoderApp_get_DisplayHeight(This,iIndex,pVal)	\
    (This)->lpVtbl -> get_DisplayHeight(This,iIndex,pVal)

#define IWMEncoderApp_GetProperty(This,enumClass,bstrProperty,pValue)	\
    (This)->lpVtbl -> GetProperty(This,enumClass,bstrProperty,pValue)

#define IWMEncoderApp_SetProperty(This,enumClass,bstrProperty,Value)	\
    (This)->lpVtbl -> SetProperty(This,enumClass,bstrProperty,Value)

#define IWMEncoderApp_SaveProperties(This,enumClass)	\
    (This)->lpVtbl -> SaveProperties(This,enumClass)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Encoder_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [retval][out] */ IWMEncoder __RPC_FAR *__RPC_FAR *ppEncoder);


void __RPC_STUB IWMEncoderApp_get_Encoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Visible_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Visible_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWMEncoderApp_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Top_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Top_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Left_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Left_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Width_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Width_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Height_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Height_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_UILock_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_UILock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_UILock_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWMEncoderApp_put_UILock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_DisplayWidth_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_DisplayWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_DisplayHeight_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWMEncoderApp_get_DisplayHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_GetProperty_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ WMENCAPP_PROP_CLASS enumClass,
    /* [in] */ BSTR bstrProperty,
    /* [retval][out] */ VARIANT __RPC_FAR *pValue);


void __RPC_STUB IWMEncoderApp_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_SetProperty_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ WMENCAPP_PROP_CLASS enumClass,
    /* [in] */ BSTR bstrProperty,
    /* [in] */ VARIANT Value);


void __RPC_STUB IWMEncoderApp_SetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_SaveProperties_Proxy( 
    IWMEncoderApp __RPC_FAR * This,
    /* [in] */ WMENCAPP_PROP_CLASS enumClass);


void __RPC_STUB IWMEncoderApp_SaveProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncoderApp_INTERFACE_DEFINED__ */


#ifndef __IWMEncOutputStats_INTERFACE_DEFINED__
#define __IWMEncOutputStats_INTERFACE_DEFINED__

/* interface IWMEncOutputStats */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncOutputStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2BE53BA6-B726-11D2-A8EB-006097C4E476")
    IWMEncOutputStats : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SampleCount( 
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwSampleCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ByteCount( 
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwByteCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DroppedSampleCount( 
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwDroppedSampleCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DroppedByteCount( 
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwDroppedByteCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentBitrate( 
            /* [retval][out] */ long __RPC_FAR *plCurrentBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AverageBitrate( 
            /* [retval][out] */ long __RPC_FAR *plAverageBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpectedBitrate( 
            /* [retval][out] */ long __RPC_FAR *plExpectedBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentSampleRate( 
            /* [retval][out] */ long __RPC_FAR *plCurrentSampleRate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AverageSampleRate( 
            /* [retval][out] */ long __RPC_FAR *plAverageSampleRate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpectedSampleRate( 
            /* [retval][out] */ long __RPC_FAR *plExpectedSampleRate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncOutputStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncOutputStats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncOutputStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SampleCount )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwSampleCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ByteCount )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwByteCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DroppedSampleCount )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwDroppedSampleCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DroppedByteCount )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwDroppedByteCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentBitrate )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCurrentBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AverageBitrate )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plAverageBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpectedBitrate )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plExpectedBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentSampleRate )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCurrentSampleRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AverageSampleRate )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plAverageSampleRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpectedSampleRate )( 
            IWMEncOutputStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plExpectedSampleRate);
        
        END_INTERFACE
    } IWMEncOutputStatsVtbl;

    interface IWMEncOutputStats
    {
        CONST_VTBL struct IWMEncOutputStatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncOutputStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncOutputStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncOutputStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncOutputStats_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncOutputStats_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncOutputStats_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncOutputStats_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncOutputStats_get_SampleCount(This,pqwSampleCount)	\
    (This)->lpVtbl -> get_SampleCount(This,pqwSampleCount)

#define IWMEncOutputStats_get_ByteCount(This,pqwByteCount)	\
    (This)->lpVtbl -> get_ByteCount(This,pqwByteCount)

#define IWMEncOutputStats_get_DroppedSampleCount(This,pqwDroppedSampleCount)	\
    (This)->lpVtbl -> get_DroppedSampleCount(This,pqwDroppedSampleCount)

#define IWMEncOutputStats_get_DroppedByteCount(This,pqwDroppedByteCount)	\
    (This)->lpVtbl -> get_DroppedByteCount(This,pqwDroppedByteCount)

#define IWMEncOutputStats_get_CurrentBitrate(This,plCurrentBitrate)	\
    (This)->lpVtbl -> get_CurrentBitrate(This,plCurrentBitrate)

#define IWMEncOutputStats_get_AverageBitrate(This,plAverageBitrate)	\
    (This)->lpVtbl -> get_AverageBitrate(This,plAverageBitrate)

#define IWMEncOutputStats_get_ExpectedBitrate(This,plExpectedBitrate)	\
    (This)->lpVtbl -> get_ExpectedBitrate(This,plExpectedBitrate)

#define IWMEncOutputStats_get_CurrentSampleRate(This,plCurrentSampleRate)	\
    (This)->lpVtbl -> get_CurrentSampleRate(This,plCurrentSampleRate)

#define IWMEncOutputStats_get_AverageSampleRate(This,plAverageSampleRate)	\
    (This)->lpVtbl -> get_AverageSampleRate(This,plAverageSampleRate)

#define IWMEncOutputStats_get_ExpectedSampleRate(This,plExpectedSampleRate)	\
    (This)->lpVtbl -> get_ExpectedSampleRate(This,plExpectedSampleRate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_SampleCount_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwSampleCount);


void __RPC_STUB IWMEncOutputStats_get_SampleCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_ByteCount_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwByteCount);


void __RPC_STUB IWMEncOutputStats_get_ByteCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_DroppedSampleCount_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwDroppedSampleCount);


void __RPC_STUB IWMEncOutputStats_get_DroppedSampleCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_DroppedByteCount_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwDroppedByteCount);


void __RPC_STUB IWMEncOutputStats_get_DroppedByteCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_CurrentBitrate_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCurrentBitrate);


void __RPC_STUB IWMEncOutputStats_get_CurrentBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_AverageBitrate_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plAverageBitrate);


void __RPC_STUB IWMEncOutputStats_get_AverageBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_ExpectedBitrate_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plExpectedBitrate);


void __RPC_STUB IWMEncOutputStats_get_ExpectedBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_CurrentSampleRate_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCurrentSampleRate);


void __RPC_STUB IWMEncOutputStats_get_CurrentSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_AverageSampleRate_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plAverageSampleRate);


void __RPC_STUB IWMEncOutputStats_get_AverageSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_ExpectedSampleRate_Proxy( 
    IWMEncOutputStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plExpectedSampleRate);


void __RPC_STUB IWMEncOutputStats_get_ExpectedSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncOutputStats_INTERFACE_DEFINED__ */


#ifndef __IWMEncFileArchiveStats_INTERFACE_DEFINED__
#define __IWMEncFileArchiveStats_INTERFACE_DEFINED__

/* interface IWMEncFileArchiveStats */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncFileArchiveStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B12B5B14-F6D2-4a47-AAED-637498BD49D6")
    IWMEncFileArchiveStats : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileSize( 
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwOutputFileSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDuration( 
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwOutputFileDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncFileArchiveStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncFileArchiveStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncFileArchiveStats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncFileArchiveStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncFileArchiveStats __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncFileArchiveStats __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncFileArchiveStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncFileArchiveStats __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileSize )( 
            IWMEncFileArchiveStats __RPC_FAR * This,
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwOutputFileSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileDuration )( 
            IWMEncFileArchiveStats __RPC_FAR * This,
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwOutputFileDuration);
        
        END_INTERFACE
    } IWMEncFileArchiveStatsVtbl;

    interface IWMEncFileArchiveStats
    {
        CONST_VTBL struct IWMEncFileArchiveStatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncFileArchiveStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncFileArchiveStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncFileArchiveStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncFileArchiveStats_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncFileArchiveStats_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncFileArchiveStats_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncFileArchiveStats_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncFileArchiveStats_get_FileSize(This,pqwOutputFileSize)	\
    (This)->lpVtbl -> get_FileSize(This,pqwOutputFileSize)

#define IWMEncFileArchiveStats_get_FileDuration(This,pqwOutputFileDuration)	\
    (This)->lpVtbl -> get_FileDuration(This,pqwOutputFileDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileArchiveStats_get_FileSize_Proxy( 
    IWMEncFileArchiveStats __RPC_FAR * This,
    /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwOutputFileSize);


void __RPC_STUB IWMEncFileArchiveStats_get_FileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileArchiveStats_get_FileDuration_Proxy( 
    IWMEncFileArchiveStats __RPC_FAR * This,
    /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *pqwOutputFileDuration);


void __RPC_STUB IWMEncFileArchiveStats_get_FileDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncFileArchiveStats_INTERFACE_DEFINED__ */


#ifndef __IWMEncIndexerStats_INTERFACE_DEFINED__
#define __IWMEncIndexerStats_INTERFACE_DEFINED__

/* interface IWMEncIndexerStats */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncIndexerStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C23F0A1E-53DF-4f6d-B8F4-EF3242D535DE")
    IWMEncIndexerStats : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileCount( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PercentComplete( 
            /* [retval][out] */ long __RPC_FAR *plPercent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncIndexerStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncIndexerStats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncIndexerStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileCount )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PercentComplete )( 
            IWMEncIndexerStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plPercent);
        
        END_INTERFACE
    } IWMEncIndexerStatsVtbl;

    interface IWMEncIndexerStats
    {
        CONST_VTBL struct IWMEncIndexerStatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncIndexerStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncIndexerStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncIndexerStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncIndexerStats_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncIndexerStats_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncIndexerStats_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncIndexerStats_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncIndexerStats_get_FileCount(This,plCount)	\
    (This)->lpVtbl -> get_FileCount(This,plCount)

#define IWMEncIndexerStats_get_FileName(This,lIndex,pbstrFileName)	\
    (This)->lpVtbl -> get_FileName(This,lIndex,pbstrFileName)

#define IWMEncIndexerStats_get_PercentComplete(This,plPercent)	\
    (This)->lpVtbl -> get_PercentComplete(This,plPercent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncIndexerStats_get_FileCount_Proxy( 
    IWMEncIndexerStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncIndexerStats_get_FileCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncIndexerStats_get_FileName_Proxy( 
    IWMEncIndexerStats __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFileName);


void __RPC_STUB IWMEncIndexerStats_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncIndexerStats_get_PercentComplete_Proxy( 
    IWMEncIndexerStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plPercent);


void __RPC_STUB IWMEncIndexerStats_get_PercentComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncIndexerStats_INTERFACE_DEFINED__ */


#ifndef __IWMEncStatistics_INTERFACE_DEFINED__
#define __IWMEncStatistics_INTERFACE_DEFINED__

/* interface IWMEncStatistics */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncStatistics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6082-BBC6-11D2-A329-006097C4E476")
    IWMEncStatistics : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncodingTime( 
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *plTime) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WMFOutputStats( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamOutputStats( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [in] */ short iStreamIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NetConnectionStats( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispNetConnectionStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileArchiveStats( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppFileArchiveStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamOutputCount( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [retval][out] */ short __RPC_FAR *pStreamOutputCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexerStats( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIndexerStats) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncStatisticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncStatistics __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncStatistics __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncodingTime )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *plTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WMFOutputStats )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamOutputStats )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [in] */ short iStreamIndex,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetConnectionStats )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispNetConnectionStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileArchiveStats )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppFileArchiveStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamOutputCount )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [retval][out] */ short __RPC_FAR *pStreamOutputCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IndexerStats )( 
            IWMEncStatistics __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIndexerStats);
        
        END_INTERFACE
    } IWMEncStatisticsVtbl;

    interface IWMEncStatistics
    {
        CONST_VTBL struct IWMEncStatisticsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncStatistics_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncStatistics_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncStatistics_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncStatistics_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncStatistics_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncStatistics_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncStatistics_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncStatistics_get_EncodingTime(This,plTime)	\
    (This)->lpVtbl -> get_EncodingTime(This,plTime)

#define IWMEncStatistics_get_WMFOutputStats(This,ppStats)	\
    (This)->lpVtbl -> get_WMFOutputStats(This,ppStats)

#define IWMEncStatistics_get_StreamOutputStats(This,enumType,iMediaIndex,iStreamIndex,pStats)	\
    (This)->lpVtbl -> get_StreamOutputStats(This,enumType,iMediaIndex,iStreamIndex,pStats)

#define IWMEncStatistics_get_NetConnectionStats(This,ppDispNetConnectionStats)	\
    (This)->lpVtbl -> get_NetConnectionStats(This,ppDispNetConnectionStats)

#define IWMEncStatistics_get_FileArchiveStats(This,ppFileArchiveStats)	\
    (This)->lpVtbl -> get_FileArchiveStats(This,ppFileArchiveStats)

#define IWMEncStatistics_get_StreamOutputCount(This,enumType,iMediaIndex,pStreamOutputCount)	\
    (This)->lpVtbl -> get_StreamOutputCount(This,enumType,iMediaIndex,pStreamOutputCount)

#define IWMEncStatistics_get_IndexerStats(This,ppIndexerStats)	\
    (This)->lpVtbl -> get_IndexerStats(This,ppIndexerStats)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_EncodingTime_Proxy( 
    IWMEncStatistics __RPC_FAR * This,
    /* [retval][out] */ WMENC_LONGLONG __RPC_FAR *plTime);


void __RPC_STUB IWMEncStatistics_get_EncodingTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_WMFOutputStats_Proxy( 
    IWMEncStatistics __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppStats);


void __RPC_STUB IWMEncStatistics_get_WMFOutputStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_StreamOutputStats_Proxy( 
    IWMEncStatistics __RPC_FAR * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ short iMediaIndex,
    /* [in] */ short iStreamIndex,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pStats);


void __RPC_STUB IWMEncStatistics_get_StreamOutputStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_NetConnectionStats_Proxy( 
    IWMEncStatistics __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispNetConnectionStats);


void __RPC_STUB IWMEncStatistics_get_NetConnectionStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_FileArchiveStats_Proxy( 
    IWMEncStatistics __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppFileArchiveStats);


void __RPC_STUB IWMEncStatistics_get_FileArchiveStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_StreamOutputCount_Proxy( 
    IWMEncStatistics __RPC_FAR * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ short iMediaIndex,
    /* [retval][out] */ short __RPC_FAR *pStreamOutputCount);


void __RPC_STUB IWMEncStatistics_get_StreamOutputCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_IndexerStats_Proxy( 
    IWMEncStatistics __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIndexerStats);


void __RPC_STUB IWMEncStatistics_get_IndexerStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncStatistics_INTERFACE_DEFINED__ */


#ifndef __IWMEncNetConnectionStats_INTERFACE_DEFINED__
#define __IWMEncNetConnectionStats_INTERFACE_DEFINED__

/* interface IWMEncNetConnectionStats */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncNetConnectionStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6083-BBC6-11D2-A329-006097C4E476")
    IWMEncNetConnectionStats : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientCount( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientInfo( 
            /* [in] */ long lIndex,
            /* [out] */ WMENC_BROADCAST_PROTOCOL __RPC_FAR *pProtocal,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrIP) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncNetConnectionStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWMEncNetConnectionStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWMEncNetConnectionStats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWMEncNetConnectionStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWMEncNetConnectionStats __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWMEncNetConnectionStats __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWMEncNetConnectionStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWMEncNetConnectionStats __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientCount )( 
            IWMEncNetConnectionStats __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientInfo )( 
            IWMEncNetConnectionStats __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [out] */ WMENC_BROADCAST_PROTOCOL __RPC_FAR *pProtocal,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrIP);
        
        END_INTERFACE
    } IWMEncNetConnectionStatsVtbl;

    interface IWMEncNetConnectionStats
    {
        CONST_VTBL struct IWMEncNetConnectionStatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncNetConnectionStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncNetConnectionStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncNetConnectionStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncNetConnectionStats_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncNetConnectionStats_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncNetConnectionStats_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncNetConnectionStats_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncNetConnectionStats_get_ClientCount(This,plCount)	\
    (This)->lpVtbl -> get_ClientCount(This,plCount)

#define IWMEncNetConnectionStats_get_ClientInfo(This,lIndex,pProtocal,pbstrIP)	\
    (This)->lpVtbl -> get_ClientInfo(This,lIndex,pProtocal,pbstrIP)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncNetConnectionStats_get_ClientCount_Proxy( 
    IWMEncNetConnectionStats __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IWMEncNetConnectionStats_get_ClientCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncNetConnectionStats_get_ClientInfo_Proxy( 
    IWMEncNetConnectionStats __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [out] */ WMENC_BROADCAST_PROTOCOL __RPC_FAR *pProtocal,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrIP);


void __RPC_STUB IWMEncNetConnectionStats_get_ClientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncNetConnectionStats_INTERFACE_DEFINED__ */



#ifndef __WMEncoderLib_LIBRARY_DEFINED__
#define __WMEncoderLib_LIBRARY_DEFINED__

/* library WMEncoderLib */
/* [helpstring][version][uuid] */ 








EXTERN_C const IID LIBID_WMEncoderLib;

#ifndef ___IWMEncoderEvents_DISPINTERFACE_DEFINED__
#define ___IWMEncoderEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWMEncoderEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWMEncoderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("632B6062-BBC6-11D2-A329-006097C4E476")
    _IWMEncoderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWMEncoderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IWMEncoderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IWMEncoderEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IWMEncoderEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IWMEncoderEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IWMEncoderEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IWMEncoderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IWMEncoderEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IWMEncoderEventsVtbl;

    interface _IWMEncoderEvents
    {
        CONST_VTBL struct _IWMEncoderEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWMEncoderEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWMEncoderEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWMEncoderEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWMEncoderEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWMEncoderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWMEncoderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWMEncoderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWMEncoderEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IWMEncoderAppEvents_DISPINTERFACE_DEFINED__
#define ___IWMEncoderAppEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWMEncoderAppEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWMEncoderAppEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("32B8ECC9-2901-11D3-8FB8-00C04F6109B7")
    _IWMEncoderAppEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWMEncoderAppEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IWMEncoderAppEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IWMEncoderAppEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IWMEncoderAppEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IWMEncoderAppEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IWMEncoderAppEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IWMEncoderAppEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IWMEncoderAppEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IWMEncoderAppEventsVtbl;

    interface _IWMEncoderAppEvents
    {
        CONST_VTBL struct _IWMEncoderAppEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWMEncoderAppEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWMEncoderAppEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWMEncoderAppEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWMEncoderAppEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWMEncoderAppEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWMEncoderAppEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWMEncoderAppEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWMEncoderAppEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WMEncoder;

#ifdef __cplusplus

class DECLSPEC_UUID("632B606A-BBC6-11D2-A329-006097C4E476")
WMEncoder;
#endif

EXTERN_C const CLSID CLSID_WMEncoderApp;

#ifdef __cplusplus

class DECLSPEC_UUID("632B606B-BBC6-11D2-A329-006097C4E476")
WMEncoderApp;
#endif

EXTERN_C const CLSID CLSID_WMEncSourcesPage;

#ifdef __cplusplus

class DECLSPEC_UUID("247161C5-995C-4097-9FF4-655DC6D12DB5")
WMEncSourcesPage;
#endif

EXTERN_C const CLSID CLSID_WMEncSourcesAltPage;

#ifdef __cplusplus

class DECLSPEC_UUID("95F57411-9A21-4846-B131-450ADBEAE753")
WMEncSourcesAltPage;
#endif

EXTERN_C const CLSID CLSID_WMEncDisplayInfoPage;

#ifdef __cplusplus

class DECLSPEC_UUID("4178CE3B-11B1-46DD-A36D-BBCD36A5425A")
WMEncDisplayInfoPage;
#endif

EXTERN_C const CLSID CLSID_WMEncAttributesPage;

#ifdef __cplusplus

class DECLSPEC_UUID("0037AC54-E32B-4ACA-9864-09F869AA82FE")
WMEncAttributesPage;
#endif

EXTERN_C const CLSID CLSID_WMEncProfilePage;

#ifdef __cplusplus

class DECLSPEC_UUID("FF8F1D65-AD2B-47F1-9E71-66B7D35E3852")
WMEncProfilePage;
#endif

EXTERN_C const CLSID CLSID_WMEncOutputPage;

#ifdef __cplusplus

class DECLSPEC_UUID("447AC255-CE81-43AD-9827-AFDDB1561B07")
WMEncOutputPage;
#endif

EXTERN_C const CLSID CLSID_WMEncAdvancedPage;

#ifdef __cplusplus

class DECLSPEC_UUID("D5DC4B7F-786B-42b7-B83B-FE1B5FC15E2C")
WMEncAdvancedPage;
#endif

EXTERN_C const CLSID CLSID_WMEncMonMainPage;

#ifdef __cplusplus

class DECLSPEC_UUID("DF0AD8E0-F91C-4109-AE46-1EAA5CD8AB08")
WMEncMonMainPage;
#endif

EXTERN_C const CLSID CLSID_WMEncMonDisplayInfoPage;

#ifdef __cplusplus

class DECLSPEC_UUID("A7E9EBC4-4B2D-44F4-8DDC-28BE73911E0A")
WMEncMonDisplayInfoPage;
#endif

EXTERN_C const CLSID CLSID_WMEncMonConnectionsPage;

#ifdef __cplusplus

class DECLSPEC_UUID("8D52AA2E-40BE-46D7-8F36-DB7B0F636824")
WMEncMonConnectionsPage;
#endif

EXTERN_C const CLSID CLSID_WMEncProfileManager;

#ifdef __cplusplus

class DECLSPEC_UUID("A8D3AD02-7508-4004-B2E9-AD33F087F43C")
WMEncProfileManager;
#endif
#endif /* __WMEncoderLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
