

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for wmencode.idl:
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

#ifndef __wmencode_h__
#define __wmencode_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMEncSourcePluginInfoManager_FWD_DEFINED__
#define __IWMEncSourcePluginInfoManager_FWD_DEFINED__
typedef interface IWMEncSourcePluginInfoManager IWMEncSourcePluginInfoManager;
#endif 	/* __IWMEncSourcePluginInfoManager_FWD_DEFINED__ */


#ifndef __IWMEncInputCollection_FWD_DEFINED__
#define __IWMEncInputCollection_FWD_DEFINED__
typedef interface IWMEncInputCollection IWMEncInputCollection;
#endif 	/* __IWMEncInputCollection_FWD_DEFINED__ */


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


#ifndef __IWMEncFile2_FWD_DEFINED__
#define __IWMEncFile2_FWD_DEFINED__
typedef interface IWMEncFile2 IWMEncFile2;
#endif 	/* __IWMEncFile2_FWD_DEFINED__ */


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


#ifndef __IWMEncSourceGroup2_FWD_DEFINED__
#define __IWMEncSourceGroup2_FWD_DEFINED__
typedef interface IWMEncSourceGroup2 IWMEncSourceGroup2;
#endif 	/* __IWMEncSourceGroup2_FWD_DEFINED__ */


#ifndef __IWMEncSourceGroupCollection_FWD_DEFINED__
#define __IWMEncSourceGroupCollection_FWD_DEFINED__
typedef interface IWMEncSourceGroupCollection IWMEncSourceGroupCollection;
#endif 	/* __IWMEncSourceGroupCollection_FWD_DEFINED__ */


#ifndef __IWMEncoder_FWD_DEFINED__
#define __IWMEncoder_FWD_DEFINED__
typedef interface IWMEncoder IWMEncoder;
#endif 	/* __IWMEncoder_FWD_DEFINED__ */


#ifndef __IWMEncoder2_FWD_DEFINED__
#define __IWMEncoder2_FWD_DEFINED__
typedef interface IWMEncoder2 IWMEncoder2;
#endif 	/* __IWMEncoder2_FWD_DEFINED__ */


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


#ifndef __IWMEncOutputStats2_FWD_DEFINED__
#define __IWMEncOutputStats2_FWD_DEFINED__
typedef interface IWMEncOutputStats2 IWMEncOutputStats2;
#endif 	/* __IWMEncOutputStats2_FWD_DEFINED__ */


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


#ifndef __IWMEncStatistics2_FWD_DEFINED__
#define __IWMEncStatistics2_FWD_DEFINED__
typedef interface IWMEncStatistics2 IWMEncStatistics2;
#endif 	/* __IWMEncStatistics2_FWD_DEFINED__ */


#ifndef __IWMEncNetConnectionStats_FWD_DEFINED__
#define __IWMEncNetConnectionStats_FWD_DEFINED__
typedef interface IWMEncNetConnectionStats IWMEncNetConnectionStats;
#endif 	/* __IWMEncNetConnectionStats_FWD_DEFINED__ */


#ifndef __IWMEncNetConnectionStats2_FWD_DEFINED__
#define __IWMEncNetConnectionStats2_FWD_DEFINED__
typedef interface IWMEncNetConnectionStats2 IWMEncNetConnectionStats2;
#endif 	/* __IWMEncNetConnectionStats2_FWD_DEFINED__ */


#ifndef __IWMEncPushDistribution_FWD_DEFINED__
#define __IWMEncPushDistribution_FWD_DEFINED__
typedef interface IWMEncPushDistribution IWMEncPushDistribution;
#endif 	/* __IWMEncPushDistribution_FWD_DEFINED__ */


#ifndef __IWMEncDeviceControlPluginInfoManager_FWD_DEFINED__
#define __IWMEncDeviceControlPluginInfoManager_FWD_DEFINED__
typedef interface IWMEncDeviceControlPluginInfoManager IWMEncDeviceControlPluginInfoManager;
#endif 	/* __IWMEncDeviceControlPluginInfoManager_FWD_DEFINED__ */


#ifndef __IWMEncDeviceControl_FWD_DEFINED__
#define __IWMEncDeviceControl_FWD_DEFINED__
typedef interface IWMEncDeviceControl IWMEncDeviceControl;
#endif 	/* __IWMEncDeviceControl_FWD_DEFINED__ */


#ifndef __IWMEncDeviceControlCollection_FWD_DEFINED__
#define __IWMEncDeviceControlCollection_FWD_DEFINED__
typedef interface IWMEncDeviceControlCollection IWMEncDeviceControlCollection;
#endif 	/* __IWMEncDeviceControlCollection_FWD_DEFINED__ */


#ifndef __IWMEncContentAnalyzer_FWD_DEFINED__
#define __IWMEncContentAnalyzer_FWD_DEFINED__
typedef interface IWMEncContentAnalyzer IWMEncContentAnalyzer;
#endif 	/* __IWMEncContentAnalyzer_FWD_DEFINED__ */


#ifndef __IWMEncBasicEdit_FWD_DEFINED__
#define __IWMEncBasicEdit_FWD_DEFINED__
typedef interface IWMEncBasicEdit IWMEncBasicEdit;
#endif 	/* __IWMEncBasicEdit_FWD_DEFINED__ */


#ifndef __IWMEncVideoSource2_FWD_DEFINED__
#define __IWMEncVideoSource2_FWD_DEFINED__
typedef interface IWMEncVideoSource2 IWMEncVideoSource2;
#endif 	/* __IWMEncVideoSource2_FWD_DEFINED__ */


#ifndef __IWMEncAudioSource_FWD_DEFINED__
#define __IWMEncAudioSource_FWD_DEFINED__
typedef interface IWMEncAudioSource IWMEncAudioSource;
#endif 	/* __IWMEncAudioSource_FWD_DEFINED__ */


#ifndef __IWMEncPushDistributionStats_FWD_DEFINED__
#define __IWMEncPushDistributionStats_FWD_DEFINED__
typedef interface IWMEncPushDistributionStats IWMEncPushDistributionStats;
#endif 	/* __IWMEncPushDistributionStats_FWD_DEFINED__ */


#ifndef __IWMEncAudienceObj_FWD_DEFINED__
#define __IWMEncAudienceObj_FWD_DEFINED__
typedef interface IWMEncAudienceObj IWMEncAudienceObj;
#endif 	/* __IWMEncAudienceObj_FWD_DEFINED__ */


#ifndef __IWMEncProfile2_FWD_DEFINED__
#define __IWMEncProfile2_FWD_DEFINED__
typedef interface IWMEncProfile2 IWMEncProfile2;
#endif 	/* __IWMEncProfile2_FWD_DEFINED__ */


#ifndef __IWMEncWatermarkCollection_FWD_DEFINED__
#define __IWMEncWatermarkCollection_FWD_DEFINED__
typedef interface IWMEncWatermarkCollection IWMEncWatermarkCollection;
#endif 	/* __IWMEncWatermarkCollection_FWD_DEFINED__ */


#ifndef __IWMEncFileSet_FWD_DEFINED__
#define __IWMEncFileSet_FWD_DEFINED__
typedef interface IWMEncFileSet IWMEncFileSet;
#endif 	/* __IWMEncFileSet_FWD_DEFINED__ */


#ifndef __IWMEncFileTransferSource_FWD_DEFINED__
#define __IWMEncFileTransferSource_FWD_DEFINED__
typedef interface IWMEncFileTransferSource IWMEncFileTransferSource;
#endif 	/* __IWMEncFileTransferSource_FWD_DEFINED__ */


#ifndef __IWMEncStreamEdit_FWD_DEFINED__
#define __IWMEncStreamEdit_FWD_DEFINED__
typedef interface IWMEncStreamEdit IWMEncStreamEdit;
#endif 	/* __IWMEncStreamEdit_FWD_DEFINED__ */


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


#ifndef __IWMEncBroadcast_FWD_DEFINED__
#define __IWMEncBroadcast_FWD_DEFINED__
typedef interface IWMEncBroadcast IWMEncBroadcast;
#endif 	/* __IWMEncBroadcast_FWD_DEFINED__ */


#ifndef __IWMEncPushDistribution_FWD_DEFINED__
#define __IWMEncPushDistribution_FWD_DEFINED__
typedef interface IWMEncPushDistribution IWMEncPushDistribution;
#endif 	/* __IWMEncPushDistribution_FWD_DEFINED__ */


#ifndef __IWMEncoder_FWD_DEFINED__
#define __IWMEncoder_FWD_DEFINED__
typedef interface IWMEncoder IWMEncoder;
#endif 	/* __IWMEncoder_FWD_DEFINED__ */


#ifndef __IWMEncoder2_FWD_DEFINED__
#define __IWMEncoder2_FWD_DEFINED__
typedef interface IWMEncoder2 IWMEncoder2;
#endif 	/* __IWMEncoder2_FWD_DEFINED__ */


#ifndef __IWMEncFile_FWD_DEFINED__
#define __IWMEncFile_FWD_DEFINED__
typedef interface IWMEncFile IWMEncFile;
#endif 	/* __IWMEncFile_FWD_DEFINED__ */


#ifndef __IWMEncFile2_FWD_DEFINED__
#define __IWMEncFile2_FWD_DEFINED__
typedef interface IWMEncFile2 IWMEncFile2;
#endif 	/* __IWMEncFile2_FWD_DEFINED__ */


#ifndef __IWMEncSourceGroup_FWD_DEFINED__
#define __IWMEncSourceGroup_FWD_DEFINED__
typedef interface IWMEncSourceGroup IWMEncSourceGroup;
#endif 	/* __IWMEncSourceGroup_FWD_DEFINED__ */


#ifndef __IWMEncSourceGroup2_FWD_DEFINED__
#define __IWMEncSourceGroup2_FWD_DEFINED__
typedef interface IWMEncSourceGroup2 IWMEncSourceGroup2;
#endif 	/* __IWMEncSourceGroup2_FWD_DEFINED__ */


#ifndef __IWMEncOutputStats2_FWD_DEFINED__
#define __IWMEncOutputStats2_FWD_DEFINED__
typedef interface IWMEncOutputStats2 IWMEncOutputStats2;
#endif 	/* __IWMEncOutputStats2_FWD_DEFINED__ */


#ifndef __IWMEncVideoSource2_FWD_DEFINED__
#define __IWMEncVideoSource2_FWD_DEFINED__
typedef interface IWMEncVideoSource2 IWMEncVideoSource2;
#endif 	/* __IWMEncVideoSource2_FWD_DEFINED__ */


#ifndef __IWMEncAudioSource_FWD_DEFINED__
#define __IWMEncAudioSource_FWD_DEFINED__
typedef interface IWMEncAudioSource IWMEncAudioSource;
#endif 	/* __IWMEncAudioSource_FWD_DEFINED__ */


#ifndef __IWMEncPushDistributionStats_FWD_DEFINED__
#define __IWMEncPushDistributionStats_FWD_DEFINED__
typedef interface IWMEncPushDistributionStats IWMEncPushDistributionStats;
#endif 	/* __IWMEncPushDistributionStats_FWD_DEFINED__ */


#ifndef __IWMEncStatistics_FWD_DEFINED__
#define __IWMEncStatistics_FWD_DEFINED__
typedef interface IWMEncStatistics IWMEncStatistics;
#endif 	/* __IWMEncStatistics_FWD_DEFINED__ */


#ifndef __IWMEncStatistics2_FWD_DEFINED__
#define __IWMEncStatistics2_FWD_DEFINED__
typedef interface IWMEncStatistics2 IWMEncStatistics2;
#endif 	/* __IWMEncStatistics2_FWD_DEFINED__ */


#ifndef __IWMEncAudienceObj_FWD_DEFINED__
#define __IWMEncAudienceObj_FWD_DEFINED__
typedef interface IWMEncAudienceObj IWMEncAudienceObj;
#endif 	/* __IWMEncAudienceObj_FWD_DEFINED__ */


#ifndef __IWMEncFileSet_FWD_DEFINED__
#define __IWMEncFileSet_FWD_DEFINED__
typedef interface IWMEncFileSet IWMEncFileSet;
#endif 	/* __IWMEncFileSet_FWD_DEFINED__ */


#ifndef __IWMEncFileTransferSource_FWD_DEFINED__
#define __IWMEncFileTransferSource_FWD_DEFINED__
typedef interface IWMEncFileTransferSource IWMEncFileTransferSource;
#endif 	/* __IWMEncFileTransferSource_FWD_DEFINED__ */


#ifndef __IWMEncNetConnectionStats2_FWD_DEFINED__
#define __IWMEncNetConnectionStats2_FWD_DEFINED__
typedef interface IWMEncNetConnectionStats2 IWMEncNetConnectionStats2;
#endif 	/* __IWMEncNetConnectionStats2_FWD_DEFINED__ */


#ifndef __IWMEncInputCollection_FWD_DEFINED__
#define __IWMEncInputCollection_FWD_DEFINED__
typedef interface IWMEncInputCollection IWMEncInputCollection;
#endif 	/* __IWMEncInputCollection_FWD_DEFINED__ */


#ifndef ___IWMEncoderEvents_FWD_DEFINED__
#define ___IWMEncoderEvents_FWD_DEFINED__
typedef interface _IWMEncoderEvents _IWMEncoderEvents;
#endif 	/* ___IWMEncoderEvents_FWD_DEFINED__ */


#ifndef ___IWMEncBasicEditEvents_FWD_DEFINED__
#define ___IWMEncBasicEditEvents_FWD_DEFINED__
typedef interface _IWMEncBasicEditEvents _IWMEncBasicEditEvents;
#endif 	/* ___IWMEncBasicEditEvents_FWD_DEFINED__ */


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


#ifndef __WMEncVideoSizePage_FWD_DEFINED__
#define __WMEncVideoSizePage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncVideoSizePage WMEncVideoSizePage;
#else
typedef struct WMEncVideoSizePage WMEncVideoSizePage;
#endif /* __cplusplus */

#endif 	/* __WMEncVideoSizePage_FWD_DEFINED__ */


#ifndef __WMEncProcessingPage_FWD_DEFINED__
#define __WMEncProcessingPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncProcessingPage WMEncProcessingPage;
#else
typedef struct WMEncProcessingPage WMEncProcessingPage;
#endif /* __cplusplus */

#endif 	/* __WMEncProcessingPage_FWD_DEFINED__ */


#ifndef __WMEncPluginsPage_FWD_DEFINED__
#define __WMEncPluginsPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncPluginsPage WMEncPluginsPage;
#else
typedef struct WMEncPluginsPage WMEncPluginsPage;
#endif /* __cplusplus */

#endif 	/* __WMEncPluginsPage_FWD_DEFINED__ */


#ifndef __WMEncDRMPage_FWD_DEFINED__
#define __WMEncDRMPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncDRMPage WMEncDRMPage;
#else
typedef struct WMEncDRMPage WMEncDRMPage;
#endif /* __cplusplus */

#endif 	/* __WMEncDRMPage_FWD_DEFINED__ */


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


#ifndef __WMEncBasicEdit_FWD_DEFINED__
#define __WMEncBasicEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncBasicEdit WMEncBasicEdit;
#else
typedef struct WMEncBasicEdit WMEncBasicEdit;
#endif /* __cplusplus */

#endif 	/* __WMEncBasicEdit_FWD_DEFINED__ */


#ifndef __WMEncStreamEdit_FWD_DEFINED__
#define __WMEncStreamEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncStreamEdit WMEncStreamEdit;
#else
typedef struct WMEncStreamEdit WMEncStreamEdit;
#endif /* __cplusplus */

#endif 	/* __WMEncStreamEdit_FWD_DEFINED__ */


#ifndef __WMEncProfile2_FWD_DEFINED__
#define __WMEncProfile2_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMEncProfile2 WMEncProfile2;
#else
typedef struct WMEncProfile2 WMEncProfile2;
#endif /* __cplusplus */

#endif 	/* __WMEncProfile2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "wmdrmprf.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_wmencode_0000 */
/* [local] */ 

#pragma once
#pragma once







EXTERN_GUID( LIBID_WMEncoderLib,            0x632B6060, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( DIID__IWMEncoderEvents,        0x632B6062, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( DIID__IWMEncoderAppEvents,     0x32B8ECC9, 0x2901, 0x11D3, 0x8F, 0xB8, 0x00, 0xC0, 0x4F, 0x61, 0x09, 0xB7 );
EXTERN_GUID( DIID__IWMEncBasicEditEvents,   0xAB5AF3CC, 0x9347, 0x4DC1, 0x92, 0xE3, 0xB9, 0x65, 0x37, 0xB8, 0xC4, 0x46 );
EXTERN_GUID( CLSID_WMEncoder,               0x632B606A, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( CLSID_WMEncoderApp,            0x632B606B, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76 );
EXTERN_GUID( CLSID_WMEncSourcesPage,        0x247161C5, 0x995C, 0x4097, 0x9F, 0xF4, 0x65, 0x5D, 0xC6, 0xD1, 0x2D, 0xB5 );
EXTERN_GUID( CLSID_WMEncSourcesAltPage,     0x95F57411, 0x9A21, 0x4846, 0xB1, 0x31, 0x45, 0x0A, 0xDB, 0xEA, 0xE7, 0x53 );
EXTERN_GUID( CLSID_WMEncDisplayInfoPage,    0x4178CE3B, 0x11B1, 0x46DD, 0xA3, 0x6D, 0xBB, 0xCD, 0x36, 0xA5, 0x42, 0x5A );
EXTERN_GUID( CLSID_WMEncAttributesPage,     0x0037AC54, 0xE32B, 0x4ACA, 0x98, 0x64, 0x09, 0xF8, 0x69, 0xAA, 0x82, 0xFE );
EXTERN_GUID( CLSID_WMEncProfilePage,        0xFF8F1D65, 0xAD2B, 0x47F1, 0x9E, 0x71, 0x66, 0xB7, 0xD3, 0x5E, 0x38, 0x52 );
EXTERN_GUID( CLSID_WMEncOutputPage,         0x447AC255, 0xCE81, 0x43AD, 0x98, 0x27, 0xAF, 0xDD, 0xB1, 0x56, 0x1B, 0x07 );
EXTERN_GUID( CLSID_WMEncAdvancedPage,       0xD5DC4B7F, 0x786B, 0x42b7, 0xB8, 0x3B, 0xFE, 0x1B, 0x5F, 0xC1, 0x5E, 0x2C );
EXTERN_GUID( CLSID_WMEncVideoSizePage,    0x94e15fa1, 0x68af, 0x4281, 0xa6, 0x7c, 0x7d, 0x5a, 0x8, 0x61, 0x69, 0xf2 );
EXTERN_GUID( CLSID_WMEncProcessingPage,  0x12594540, 0x9b58, 0x4fe9, 0xa7, 0xea, 0x8a, 0x10, 0xf6, 0x41, 0xb0, 0x49 );
EXTERN_GUID( CLSID_WMEncPluginsPage,      0xa9b377b6, 0x7d6f, 0x4f37, 0xb2, 0x8, 0x2a, 0xf6, 0xdc, 0x85, 0xe6, 0x8);
EXTERN_GUID( CLSID_WMEncDRMPage,          0xfcc970b8, 0x86d5, 0x4a30, 0xac, 0x33, 0xb7, 0x66, 0x79, 0xbd, 0xf9, 0x70);
EXTERN_GUID( CLSID_WMEncMonMainPage,        0xDF0AD8E0, 0xF91C, 0x4109, 0xAE, 0x46, 0x1E, 0xAA, 0x5C, 0xD8, 0xAB, 0x08 );
EXTERN_GUID( CLSID_WMEncMonDisplayInfoPage, 0xA7E9EBC4, 0x4B2D, 0x44F4, 0x8D, 0xDC, 0x28, 0xBE, 0x73, 0x91, 0x1E, 0x0A );
EXTERN_GUID( CLSID_WMEncMonConnectionsPage, 0x8D52AA2E, 0x40BE, 0x46D7, 0x8F, 0x36, 0xDB, 0x7B, 0x0F, 0x63, 0x68, 0x24 );
EXTERN_GUID( CLSID_WMEncProfileManager,     0xA8D3AD02, 0x7508, 0x4004, 0xB2, 0xE9, 0xAD, 0x33, 0xF0, 0x87, 0xF4, 0x3C );
EXTERN_GUID( CLSID_WMEncBasicEdit,          0x9571D958, 0x9BCF, 0x4E19, 0xA3, 0x74, 0xFC, 0x2F, 0x32, 0x1C, 0x8F, 0x61 );
EXTERN_GUID( CLSID_WMEncMonStatsPage,       0xDF0AD8E1, 0xF91C, 0x4109, 0xAE, 0x46, 0x1E, 0xAA, 0x5C, 0xD8, 0xAB, 0x08 );
EXTERN_GUID( CLSID_WMEncMonServerPage,      0xDF0AD8E3, 0xF91C, 0x4109, 0xAE, 0x46, 0x1E, 0xAA, 0x5C, 0xD8, 0xAB, 0x08 );
EXTERN_GUID( IID_IWMEncSourcePluginInfoManager,       0x5AE18C51, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncTransformPluginInfoManager,    0x5AE18C52, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncPluginInfo,                    0x5AE18C53, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncTransformCollection,           0x5AE18C54, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncDataViewCollection,            0x5AE18C55, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncSourceGroupCollection,       0x632B606F, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncSourceGroup,         0x632B6071, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncSourceGroup2,        0x632B608A, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncDisplayInfo,         0x632B6073, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncAttributes,          0x632B6075, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncProfileCollection,   0x632B6077, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncProfile,             0x632B6078, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncFile,                0x632B607B, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncBroadcast,           0x632B607D, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncoder,                0x632B607F, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncoder2,               0x632B6081, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
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
EXTERN_GUID( IID_IWMEncPushDistribution,    0x10CBC166, 0x7F83, 0x451E, 0x90, 0xA1, 0x75, 0xF4, 0x3E, 0x2C, 0x20, 0xA0);
EXTERN_GUID( IID_IWMEncFile2,               0x10CBC168, 0x7F83, 0x451E, 0x90, 0xA1, 0x75, 0xF4, 0x3E, 0x2C, 0x20, 0xA0);
EXTERN_GUID( IID_IWMEncDeviceControlPluginInfoManager,  0x632B6087, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncDeviceControl,       0x632B6089, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncDeviceControlCollection,       0x632B608C, 0xBBC6, 0x11D2, 0xA3, 0x29, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( IID_IWMEncOutputStats2,        0x18DB3000, 0xFFEA, 0x4363, 0x80, 0xC5, 0x81, 0x8A, 0xF4, 0x17, 0xBC, 0x84);
EXTERN_GUID( IID_IWMEncContentAnalyzer,     0x221ADE1A, 0x3CF9, 0x4BA2, 0x84, 0x1C, 0xE5, 0x80, 0xC5, 0x88, 0x76, 0x6A);
EXTERN_GUID( IID_IWMEncBasicEdit,           0x22A65C28, 0xF99D, 0x4C0D, 0x80, 0x70, 0x5F, 0x86, 0xFE, 0x6E, 0xC5, 0x55);
EXTERN_GUID( IID_IWMEncVideoSource2,        0xC0973771, 0x5F87, 0x456A, 0xB3, 0x1B, 0x51, 0x71, 0xC2, 0x8A, 0xC0, 0x1E);
EXTERN_GUID( IID_IWMEncAudioSource,         0xC0973772, 0x5F87, 0x456A, 0xB3, 0x1B, 0x51, 0x71, 0xC2, 0x8A, 0xC0, 0x1E);
EXTERN_GUID( IID_IWMEncStatistics2,         0x3C694BEE, 0xBA71, 0x4967, 0x88, 0xEA, 0x43, 0xF8, 0xC2, 0x7E, 0xD9, 0x18);
EXTERN_GUID( IID_IWMEncPushDistributionStats,         0x252F3333, 0x53D0, 0x47D9, 0x94, 0xC6, 0xC3, 0x87, 0x36, 0xF1, 0xBA, 0x6A);
EXTERN_GUID( IID_IWMEncWatermarkCollection, 0x252F3335, 0x53D0, 0x47D9, 0x94, 0xC6, 0xC3, 0x87, 0x36, 0xF1, 0xBA, 0x6A);
EXTERN_GUID( IID_IWMEncNetConnectionStats2, 0x52350A39, 0x5581, 0x4b7B, 0xA6, 0x5A, 0xF3, 0x78, 0x48, 0xF2, 0xC0, 0xF6);
EXTERN_GUID( IID_IWMEncInputCollection,     0xaafde109, 0xeb40, 0x47bc, 0x96, 0xc3, 0xb4, 0xfb, 0xf5, 0x2a, 0x56, 0x8d);
EXTERN_GUID( CLSID_WMEncProfile2,             0xA5AC04E7, 0x3E13, 0x48CE, 0xA4, 0x3F, 0x9F, 0xBA, 0x59, 0xDB, 0x15, 0x44 );
EXTERN_GUID( IID_IWMEncProfile2,              0xC70E1CAC, 0x32D2, 0x4e22, 0xA0, 0xFF, 0x3A, 0x32, 0xE3, 0x15, 0xD0, 0x95 );
EXTERN_GUID( IID_IWMEncAudienceObj,           0xBB494815, 0x9432, 0x47f2, 0x97, 0x9D, 0x94, 0xE4, 0xAE, 0x6C, 0x96, 0xCF );
EXTERN_GUID( CLSID_WMEncFileTransferSource,     0x2EFB8BAD, 0x7074, 0x4814, 0x9F, 0xBF, 0x93, 0x8A, 0xD1, 0xF7, 0xFB, 0x01 );
EXTERN_GUID( IID_IWMEncFileTransferSource,      0x8E452E5A, 0xB739, 0x452F, 0xA4, 0xD2, 0x5D, 0x84, 0xFD, 0x52, 0x49, 0x16 );
EXTERN_GUID( IID_IWMEncFileSet,                 0x54B54844, 0x4F93, 0x458E, 0xAC, 0x10, 0x45, 0xFF, 0xED, 0x1D, 0x18, 0x16 );
EXTERN_GUID( IID_IWMEncStreamEdit,              0x5AE18C57, 0xDB2E, 0x11D2, 0xA3, 0x4A, 0x00, 0x60, 0x97, 0xC4, 0xE4, 0x76);
EXTERN_GUID( CLSID_WMEncStreamEdit,             0x216D96AA, 0x9109, 0x472e, 0x8C, 0xDD, 0x82, 0x1C, 0x95, 0x2C, 0x4D, 0x6E);
////////////////////////////////////////////////////////////////
//
//
#define WMENC_TOTAL     ( ( WMENC_SOURCE_TYPE ) 0x00000004 )
#define WMENC_ANY       ( ( WMENC_SOURCE_TYPE ) 0xFFFFFFFF )
#define WMENC_STREAMLEVEL_TRANSFORM_PLUGIN      0x00000001
#define WMENC_GROUPLEVEL_TRANSFORM_PLUGIN       0x00000002
#define WMENC_BOTHLEVEL_TRANSFORM_PLUGIN        0x00000003

////////////////////////////////////////////////////////////////
// The following defines are the property names for IWMEncOutputStats2.
// They define the names for the sample drop rate for encoding process.
////////////////////////////////////////////////////////////////
#define WMENC_STATS_CURRENT_SAMPLEDROPRATE_INQUEUE  L"CurrentSampleDropRateInQueue"
#define WMENC_STATS_CURRENT_SAMPLEDROPRATE_INCODEC  L"CurrentSampleDropRateInCodec"
#define WMENC_STATS_CURRENT_SAMPLEDROPRATE_INMUX    L"CurrentSampleDropRateInMux"
#define WMENC_STATS_TOTAL_SAMPLESDROPPED_INQUEUE    L"TotalSamplesDroppedInQueue"
#define WMENC_STATS_TOTAL_SAMPLESDROPPED_INCODEC    L"TotalSamplesDroppedInCodec"
#define WMENC_STATS_TOTAL_SAMPLESDROPPED_INMUX      L"TotalSamplesDroppedInMux"
#define WMENC_STATS_PERCENT_CODECBUFFERFULLNESS     L"PercentCodecBufferFullness"
////////////////////////////////////////////////////////////////
// The following defines are for extracting the profile at the end of encoding.
////////////////////////////////////////////////////////////////
#define WMENC_STATS_DEVICE_CONFORMANCE_TEMPLATE  L"DeviceConformanceTemplate"
////////////////////////////////////////////////////////////////
// The following defines are the property names for IWMEncPushDistributionStats.
////////////////////////////////////////////////////////////////
#define WMENC_STATS_PUSH_PEAK_STARTTIME            L"PubPointStartTimeForPeak"
#define WMENC_STATS_PUSH_CURRENT_CONNECTEDPLAYERS  L"PubPointCurrentConnectedPlayers"
#define WMENC_STATS_PUSH_PEAK_CONNECTEDPLAYERS     L"PubPointPeakConnectedPlayers"
#define WMENC_STATS_PUSH_TOTAL_CONNECTEDPLAYERS    L"PubPointTotalConnectedPlayers"
#define WMENC_STATS_PUSH_PLAYERSLIMIT              L"PubPointPlayersLimit"
#define WMENC_STATS_PUSH_CURRENT_PLAYERBANDWIDTH   L"PubPointCurrentPlayerBandwidth"
#define WMENC_STATS_PUSH_PEAK_PLAYERBANDWIDTH      L"PubPointPeakPlayerBandwidth"
#define WMENC_STATS_PUSH_BANDWIDTHLIMIT            L"PubPointBandwidthLimit"
#define WMENC_STATS_PUSH_CPU                       L"CurrentServerCPU"
////////////////////////////////////////////////////////////////
// The following defines 5.1 fold down coefficient.
////////////////////////////////////////////////////////////////
#define WMENC_AUDIO_SURROUND_MIX                L"SurroundMix"
#define WMENC_AUDIO_CENTER_MIX                  L"CenterMix"
#define WMENC_AUDIO_SUBWOOFER_MIX               L"LFEMix"
////////////////////////////////////////////////////////////////
// The following defines predefined Source Group Rollover Name.
////////////////////////////////////////////////////////////////
#define WMENC_SOURCEGROUP_AUTOROLLOVER_TO_NEXT     L"WMENC_SOURCEGROUP_AUTOROLLOVER_TO_NEXT"
#define WMENC_SOURCEGROUP_AUTOROLLOVER_TO_FIRST    L"WMENC_SOURCEGROUP_AUTOROLLOVER_TO_FIRST"
////////////////////////////////////////////////////////////////
// The following defines are the propertynames for IWMEncProfile2.
////////////////////////////////////////////////////////////////
#define WMENC_PROFILE2_BUFFER_WINDOW                L"BufferWindow"
#define WMENC_PROFILE2_DEVICE_CONFORMANCE_TARGET    L"DeviceConformanceTarget"
typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BA5-B726-11D2-A8EB-006097C4E476") CURRENCY WMENC_LONGLONG;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BA7-B726-11D2-A8EB-006097C4E476") 
enum WMENC_ENCODER_STATE
    {	WMENC_ENCODER_STARTING	= 0x1,
	WMENC_ENCODER_RUNNING	= 0x2,
	WMENC_ENCODER_PAUSED	= 0x3,
	WMENC_ENCODER_STOPPING	= 0x4,
	WMENC_ENCODER_STOPPED	= 0x5,
	WMENC_ENCODER_END_PREPROCESS	= 0x6,
	WMENC_ENCODER_PAUSING	= 0x7
    } 	WMENC_ENCODER_STATE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BA8-B726-11D2-A8EB-006097C4E476") 
enum WMENC_ARCHIVE_TYPE
    {	WMENC_ARCHIVE_LOCAL	= 0x1
    } 	WMENC_ARCHIVE_TYPE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BA9-B726-11D2-A8EB-006097C4E476") 
enum WMENC_ARCHIVE_OPERATION
    {	WMENC_ARCHIVE_START	= 0x1,
	WMENC_ARCHIVE_STOP	= 0x2,
	WMENC_ARCHIVE_PAUSE	= 0x3
    } 	WMENC_ARCHIVE_OPERATION;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BAA-B726-11D2-A8EB-006097C4E476") 
enum WMENC_ARCHIVE_STATE
    {	WMENC_ARCHIVE_RUNNING	= 0x1,
	WMENC_ARCHIVE_PAUSED	= 0x2,
	WMENC_ARCHIVE_STOPPED	= 0x3
    } 	WMENC_ARCHIVE_STATE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BAB-B726-11D2-A8EB-006097C4E476") 
enum WMENC_SOURCE_TYPE
    {	WMENC_AUDIO	= 0x1,
	WMENC_VIDEO	= 0x2,
	WMENC_SCRIPT	= 0x4,
	WMENC_FILETRANSFER	= 0x8
    } 	WMENC_SOURCE_TYPE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BAC-B726-11D2-A8EB-006097C4E476") 
enum WMENC_SOURCE_STATE
    {	WMENC_SOURCE_START	= 0x1,
	WMENC_SOURCE_STOP	= 0x2,
	WMENC_SOURCE_PREPARE	= 0x3,
	WMENC_SOURCE_UNPREPARE	= 0x4,
	WMENC_START_FILETRANSFER	= 0x5,
	WMENC_STOP_FILETRANSFER	= 0x6
    } 	WMENC_SOURCE_STATE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BAD-B726-11D2-A8EB-006097C4E476") 
enum WMENC_DEVICECONTROL_STATE
    {	WMENC_DEVICECONTROL_PLAYING	= 0x1,
	WMENC_DEVICECONTROL_PAUSED	= 0x2,
	WMENC_DEVICECONTROL_STOPPED	= 0x3,
	WMENC_DEVICECONTROL_FASTFORWARDING	= 0x4,
	WMENC_DEVICECONTROL_REWINDING	= 0x5,
	WMENC_DEVICECONTROL_CUEING	= 0x6,
	WMENC_DEVICECONTROL_PREROLLING	= 0x7,
	WMENC_DEVICECONTROL_UNSTABLE	= 0x9,
	WMENC_DEVICECONTROL_EJECT	= 0xa,
	WMENC_DEVICECONTROL_VAR_FORWARD	= 0xb,
	WMENC_DEVICECONTROL_VAR_REVERSE	= 0xc,
	WMENC_DEVICECONTROL_ENDOFTAPE	= 0xd
    } 	WMENC_DEVICECONTROL_STATE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BAE-B726-11D2-A8EB-006097C4E476") 
enum WMENC_PLUGIN_TYPE
    {	WMENC_PLUGIN_SOURCE	= 0x1,
	WMENC_PLUGIN_TRANSFORM	= 0x2,
	WMENC_PLUGIN_DEVICECONTROL	= 0x3
    } 	WMENC_PLUGIN_TYPE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2BE53BAF-B726-11D2-A8EB-006097C4E476") 
enum WMENC_BROADCAST_PROTOCOL
    {	WMENC_PROTOCOL_HTTP	= 0x1,
	WMENC_PROTOCOL_PUSH_DISTRIBUTION	= 0x2
    } 	WMENC_BROADCAST_PROTOCOL;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("30298E9E-7A93-473f-9E01-625869CF382E") 
enum WMENC_MEDIA_FILTER
    {	WMENC_FILTER_NONE	= 0,
	WMENC_FILTER_A	= 0x1,
	WMENC_FILTER_AV	= 0x11,
	WMENC_FILTER_AS	= 0x101,
	WMENC_FILTER_AVS	= 0x111
    } 	WMENC_MEDIA_FILTER;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("EEAA5F39-A1F8-4696-B612-1022F39500BC") 
enum WMENC_CROPPING_MODE
    {	WMENC_CROPPING_ABSOLUTE	= 0
    } 	WMENC_CROPPING_MODE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("8FA09255-5B77-4da8-BE45-B756E4B80C24") 
enum WMENC_INDEXER_STATE
    {	WMENC_INDEXER_RUNNING	= 0x1,
	WMENC_INDEXER_STOPPED	= 0x2
    } 	WMENC_INDEXER_STATE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("9514675E-2B6F-43CB-8D15-57F8E3EADDF4") 
enum WMENCAPP_PROP_CLASS
    {	WMENCAPP_PROP_USER	= 0x1
    } 	WMENCAPP_PROP_CLASS;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("E40CC379-3603-4f77-AF9B-B0F0CCF7EBDC") 
enum WMENC_VIDEO_OPTIMIZATION
    {	WMENC_VIDEO_STANDARD	= 0x1,
	WMENC_VIDEO_DEINTERLACE	= 0x2,
	WMENC_VIDEO_INVERSETELECINE	= 0x3,
	WMENC_VIDEO_PROCESS_INTERLACED	= 0x4,
	WMENC_VIDEO_TELECINE_AUTO	= 0x10,
	WMENC_VIDEO_TELECINE_AA_TOP	= 0x20,
	WMENC_VIDEO_TELECINE_BB_TOP	= 0x30,
	WMENC_VIDEO_TELECINE_BC_TOP	= 0x40,
	WMENC_VIDEO_TELECINE_CD_TOP	= 0x50,
	WMENC_VIDEO_TELECINE_DD_TOP	= 0x60,
	WMENC_VIDEO_TELECINE_AA_BOTTOM	= 0x70,
	WMENC_VIDEO_TELECINE_BB_BOTTOM	= 0x80,
	WMENC_VIDEO_TELECINE_BC_BOTTOM	= 0x90,
	WMENC_VIDEO_TELECINE_CD_BOTTOM	= 0xa0,
	WMENC_VIDEO_TELECINE_DD_BOTTOM	= 0xb0,
	WMENC_VIDEO_FLIPPING_VERTICAL	= 0x100,
	WMENC_VIDEO_INTERLACED_AUTO	= 0x1000,
	WMENC_VIDEO_INTERLACED_TOP_FIRST	= 0x2000,
	WMENC_VIDEO_INTERLACED_BOTTOM_FIRST	= 0x3000
    } 	WMENC_VIDEO_OPTIMIZATION;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("384C1030-317C-42fc-A5A0-537FDC6FB92F") 
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
    } 	WMENC_PIXELFORMAT_VIDEO;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("B0FA616E-C173-45e5-BCC6-7DA3B185979E") 
enum WMENC_INDEXER_OPERATION
    {	WMENC_INDEXER_STOP	= 0x1
    } 	WMENC_INDEXER_OPERATION;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("3BE52C8E-9B0D-4f21-B237-DF76317F38EC") 
enum WMENC_AUDIOLEVEL_UNITS
    {	WMENC_AUDIOLEVEL_DB	= 0x1,
	WMENC_AUDIOLEVEL_LINEAR	= 0x2
    } 	WMENC_AUDIOLEVEL_UNITS;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("3BE52C8F-9B0D-4f21-B237-DF76317F38EC") 
enum WMENC_STORAGE_FORMAT
    {	WMENC_STORAGE_FORMAT_V1	= 0x1,
	WMENC_STORAGE_FORMAT_V2	= 0x2
    } 	WMENC_STORAGE_FORMAT;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("DC3C7C50-F4CE-462c-9236-645F276F5716") 
enum WMENC_BASICEDIT_STATE
    {	WMENC_BASICEDIT_RUNNING	= 0x1,
	WMENC_BASICEDIT_STOPPED	= 0x2
    } 	WMENC_BASICEDIT_STATE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("DC3C7C51-F4CE-462c-9236-645F276F5716") 
enum WMENC_CONTENT_MODE
    {	WMENC_AUDIOCONTENT_NO_MODE	= 0,
	WMENC_AUDIOCONTENT_SPEECH_MODE	= 0x1,
	WMENC_AUDIOCONTENT_MIXED_MODE	= 0x2
    } 	WMENC_CONTENT_MODE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("2CB3CB95-45AF-4dfc-B209-EE715EDE803C") 
enum WMENC_PROFILE_COMPATIBILITY
    {	WMENC_ENCODER_V8	= 0,
	WMENC_ENCODER_V9	= 0x1
    } 	WMENC_PROFILE_COMPATIBILITY;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("15B36445-1FC5-4ef8-8928-ECDD4A245412") 
enum WMENC_PROFILE_VBR_MODE
    {	WMENC_PVM_NONE	= 0x1,
	WMENC_PVM_PEAK	= 0x2,
	WMENC_PVM_UNCONSTRAINED	= 0x3,
	WMENC_PVM_BITRATE_BASED	= 0x4
    } 	WMENC_PROFILE_VBR_MODE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("09EA2938-3777-4672-8FEA-E8AC7D76156F") 
enum WMENC_PROFILE_BROADCAST_MODE
    {	WMENC_PFM_CUSTOM	= 0x1,
	WMENC_PFM_NTSC	= 0x2,
	WMENC_PFM_PAL	= 0x3
    } 	WMENC_PROFILE_BROADCAST_MODE;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("09EA2939-3777-4672-8FEA-E8AC7D76156F") 
enum WMENC_MEDIA_CONTENT
    {	WMENC_CONTENT_NOTHING	= 0,
	WMENC_CONTENT_ONE_AUDIO	= 0x1,
	WMENC_CONTENT_ONE_VIDEO	= 0x10,
	WMENC_CONTENT_ONE_SCRIPT	= 0x100,
	WMENC_CONTENT_ONE_AUDIO_ONE_VIDEO	= 0x11,
	WMENC_CONTENT_ONE_AUDIO_ONE_SCRIPT	= 0x101,
	WMENC_CONTENT_ONE_VIDEO_ONE_SCRIPT	= 0x110,
	WMENC_CONTENT_ONE_AUDIO_ONE_VIDEO_ONE_SCRIPT	= 0x111,
	WMENC_CONTENT_ONE_AUDIO_ONE_FILETRANSFER	= 0x1001,
	WMENC_CONTENT_ONE_VIDEO_ONE_FILETRANSFER	= 0x1010,
	WMENC_CONTENT_ONE_AUDIO_ONE_VIDEO_ONE_FILETRANSFER	= 0x1011,
	WMENC_CONTENT_ONE_AUDIO_ONE_VIDEO_ONE_SCRIPT_ONE_FILETRANSFER	= 0x1111
    } 	WMENC_MEDIA_CONTENT;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("159AABD8-2242-4c96-A077-D9B32E6111E1") 
enum WMENC_VIDEOCOMPLEXITY
    {	WMENC_DEFAULT_COMPLEXITY	= -1,
	WMENC_COMPLEXITY_LEVEL0	= 0,
	WMENC_COMPLEXITY_LEVEL20	= 20,
	WMENC_COMPLEXITY_LEVEL40	= 40,
	WMENC_COMPLEXITY_LEVEL50	= 50,
	WMENC_COMPLEXITY_LEVEL60	= 60,
	WMENC_COMPLEXITY_LEVEL80	= 80,
	WMENC_COMPLEXITY_LEVEL100	= 100
    } 	WMENC_VIDEOCOMPLEXITY;



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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourcePluginInfoManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncSourcePluginInfoManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncSourcePluginInfoManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncSourcePluginInfoManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncSourcePluginInfoManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncSourcePluginInfoManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncSourcePluginInfoManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncSourcePluginInfoManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncSourcePluginInfoManager * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncSourcePluginInfoManager * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncSourcePluginInfoManager * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncSourcePluginInfoManager * This,
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWMEncSourcePluginInfoManager * This);
        
        END_INTERFACE
    } IWMEncSourcePluginInfoManagerVtbl;

    interface IWMEncSourcePluginInfoManager
    {
        CONST_VTBL struct IWMEncSourcePluginInfoManagerVtbl *lpVtbl;
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
    IWMEncSourcePluginInfoManager * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncSourcePluginInfoManager_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_get_Count_Proxy( 
    IWMEncSourcePluginInfoManager * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncSourcePluginInfoManager_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_get__NewEnum_Proxy( 
    IWMEncSourcePluginInfoManager * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncSourcePluginInfoManager_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_Item_Proxy( 
    IWMEncSourcePluginInfoManager * This,
    /* [in] */ long iIndex,
    /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo);


void __RPC_STUB IWMEncSourcePluginInfoManager_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourcePluginInfoManager_Refresh_Proxy( 
    IWMEncSourcePluginInfoManager * This);


void __RPC_STUB IWMEncSourcePluginInfoManager_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSourcePluginInfoManager_INTERFACE_DEFINED__ */


#ifndef __IWMEncInputCollection_INTERFACE_DEFINED__
#define __IWMEncInputCollection_INTERFACE_DEFINED__

/* interface IWMEncInputCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncInputCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("aafde109-eb40-47bc-96c3-b4fbf52a568d")
    IWMEncInputCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pretval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncInputCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncInputCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncInputCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncInputCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncInputCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncInputCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncInputCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncInputCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncInputCollection * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pretval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncInputCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncInputCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncInputCollection * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        END_INTERFACE
    } IWMEncInputCollectionVtbl;

    interface IWMEncInputCollection
    {
        CONST_VTBL struct IWMEncInputCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncInputCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncInputCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncInputCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncInputCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncInputCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncInputCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncInputCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncInputCollection_Item(This,lIndex,pretval)	\
    (This)->lpVtbl -> Item(This,lIndex,pretval)

#define IWMEncInputCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncInputCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncInputCollection_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncInputCollection_Item_Proxy( 
    IWMEncInputCollection * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ BSTR *pretval);


void __RPC_STUB IWMEncInputCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncInputCollection_get_length_Proxy( 
    IWMEncInputCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncInputCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncInputCollection_get_Count_Proxy( 
    IWMEncInputCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncInputCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncInputCollection_get__NewEnum_Proxy( 
    IWMEncInputCollection * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncInputCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncInputCollection_INTERFACE_DEFINED__ */


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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncTransformPluginInfoManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncTransformPluginInfoManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncTransformPluginInfoManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncTransformPluginInfoManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncTransformPluginInfoManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncTransformPluginInfoManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncTransformPluginInfoManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncTransformPluginInfoManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncTransformPluginInfoManager * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncTransformPluginInfoManager * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncTransformPluginInfoManager * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncTransformPluginInfoManager * This,
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWMEncTransformPluginInfoManager * This);
        
        END_INTERFACE
    } IWMEncTransformPluginInfoManagerVtbl;

    interface IWMEncTransformPluginInfoManager
    {
        CONST_VTBL struct IWMEncTransformPluginInfoManagerVtbl *lpVtbl;
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
    IWMEncTransformPluginInfoManager * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncTransformPluginInfoManager_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_get_Count_Proxy( 
    IWMEncTransformPluginInfoManager * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncTransformPluginInfoManager_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_get__NewEnum_Proxy( 
    IWMEncTransformPluginInfoManager * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncTransformPluginInfoManager_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_Item_Proxy( 
    IWMEncTransformPluginInfoManager * This,
    /* [in] */ long iIndex,
    /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo);


void __RPC_STUB IWMEncTransformPluginInfoManager_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformPluginInfoManager_Refresh_Proxy( 
    IWMEncTransformPluginInfoManager * This);


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
            /* [retval][out] */ BSTR *pbstrSchemeType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CLSID( 
            /* [retval][out] */ BSTR *pbstrCLSID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaType( 
            /* [retval][out] */ WMENC_SOURCE_TYPE *penumMediaType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PluginType( 
            /* [retval][out] */ WMENC_PLUGIN_TYPE *penumType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Copyright( 
            /* [retval][out] */ BSTR *pbstrCopyright) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoURL( 
            /* [retval][out] */ BSTR *pbstrInfoURL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Resources( 
            /* [retval][out] */ VARIANT_BOOL *pbResources) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Exclusive( 
            /* [retval][out] */ VARIANT_BOOL *pbExclusive) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PropertyPage( 
            /* [retval][out] */ VARIANT_BOOL *pbProppage) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransformFlags( 
            /* [retval][out] */ short *piFlags) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Hidden( 
            /* [retval][out] */ VARIANT_BOOL *pbHidden) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pbstrResource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPluginInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncPluginInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncPluginInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncPluginInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncPluginInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncPluginInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncPluginInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncPluginInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SchemeType )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ BSTR *pbstrSchemeType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ BSTR *pbstrCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaType )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE *penumMediaType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PluginType )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ WMENC_PLUGIN_TYPE *penumType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Copyright )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ BSTR *pbstrCopyright);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InfoURL )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ BSTR *pbstrInfoURL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Resources )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ VARIANT_BOOL *pbResources);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Exclusive )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ VARIANT_BOOL *pbExclusive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PropertyPage )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ VARIANT_BOOL *pbProppage);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformFlags )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ short *piFlags);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Hidden )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ VARIANT_BOOL *pbHidden);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncPluginInfo * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncPluginInfo * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pbstrResource);
        
        END_INTERFACE
    } IWMEncPluginInfoVtbl;

    interface IWMEncPluginInfo
    {
        CONST_VTBL struct IWMEncPluginInfoVtbl *lpVtbl;
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
    IWMEncPluginInfo * This,
    /* [retval][out] */ BSTR *pbstrSchemeType);


void __RPC_STUB IWMEncPluginInfo_get_SchemeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_CLSID_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ BSTR *pbstrCLSID);


void __RPC_STUB IWMEncPluginInfo_get_CLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Name_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB IWMEncPluginInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_MediaType_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ WMENC_SOURCE_TYPE *penumMediaType);


void __RPC_STUB IWMEncPluginInfo_get_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_PluginType_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ WMENC_PLUGIN_TYPE *penumType);


void __RPC_STUB IWMEncPluginInfo_get_PluginType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Copyright_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ BSTR *pbstrCopyright);


void __RPC_STUB IWMEncPluginInfo_get_Copyright_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_InfoURL_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ BSTR *pbstrInfoURL);


void __RPC_STUB IWMEncPluginInfo_get_InfoURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Resources_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ VARIANT_BOOL *pbResources);


void __RPC_STUB IWMEncPluginInfo_get_Resources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Exclusive_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ VARIANT_BOOL *pbExclusive);


void __RPC_STUB IWMEncPluginInfo_get_Exclusive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_PropertyPage_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ VARIANT_BOOL *pbProppage);


void __RPC_STUB IWMEncPluginInfo_get_PropertyPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_TransformFlags_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ short *piFlags);


void __RPC_STUB IWMEncPluginInfo_get_TransformFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Hidden_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ VARIANT_BOOL *pbHidden);


void __RPC_STUB IWMEncPluginInfo_get_Hidden_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_get_Count_Proxy( 
    IWMEncPluginInfo * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncPluginInfo_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncPluginInfo_Item_Proxy( 
    IWMEncPluginInfo * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ BSTR *pbstrResource);


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
            /* [out] */ BSTR *pbstrScheme,
            /* [out] */ BSTR *pbstrInitData,
            /* [retval][out] */ BSTR *pbstrInput) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransformPlugin( 
            /* [retval][out] */ IUnknown **ppUnkPlugin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncTransform * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncTransform * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncTransform * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncTransform * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncTransform * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncTransform * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInput )( 
            IWMEncTransform * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrInitData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInput )( 
            IWMEncTransform * This,
            /* [out] */ BSTR *pbstrScheme,
            /* [out] */ BSTR *pbstrInitData,
            /* [retval][out] */ BSTR *pbstrInput);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPlugin )( 
            IWMEncTransform * This,
            /* [retval][out] */ IUnknown **ppUnkPlugin);
        
        END_INTERFACE
    } IWMEncTransformVtbl;

    interface IWMEncTransform
    {
        CONST_VTBL struct IWMEncTransformVtbl *lpVtbl;
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
    IWMEncTransform * This,
    /* [in] */ BSTR bstrInput,
    /* [defaultvalue][in] */ BSTR bstrScheme,
    /* [defaultvalue][in] */ BSTR bstrInitData);


void __RPC_STUB IWMEncTransform_SetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransform_GetInput_Proxy( 
    IWMEncTransform * This,
    /* [out] */ BSTR *pbstrScheme,
    /* [out] */ BSTR *pbstrInitData,
    /* [retval][out] */ BSTR *pbstrInput);


void __RPC_STUB IWMEncTransform_GetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransform_GetTransformPlugin_Proxy( 
    IWMEncTransform * This,
    /* [retval][out] */ IUnknown **ppUnkPlugin);


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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncTransform **ppTransform) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [retval][out] */ IWMEncTransform **ppTransform) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncTransformCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncTransformCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncTransformCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncTransformCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncTransformCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncTransformCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncTransformCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncTransformCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncTransformCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncTransformCollection * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncTransformCollection * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncTransform **ppTransform);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncTransformCollection * This,
            /* [retval][out] */ IWMEncTransform **ppTransform);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncTransformCollection * This,
            /* [in] */ long lIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncTransformCollection * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IWMEncTransformCollection * This,
            /* [in] */ long lMove,
            /* [in] */ long lInFrontOf);
        
        END_INTERFACE
    } IWMEncTransformCollectionVtbl;

    interface IWMEncTransformCollection
    {
        CONST_VTBL struct IWMEncTransformCollectionVtbl *lpVtbl;
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
    IWMEncTransformCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncTransformCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_get_Count_Proxy( 
    IWMEncTransformCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncTransformCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_get__NewEnum_Proxy( 
    IWMEncTransformCollection * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncTransformCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Item_Proxy( 
    IWMEncTransformCollection * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ IWMEncTransform **ppTransform);


void __RPC_STUB IWMEncTransformCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Add_Proxy( 
    IWMEncTransformCollection * This,
    /* [retval][out] */ IWMEncTransform **ppTransform);


void __RPC_STUB IWMEncTransformCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Remove_Proxy( 
    IWMEncTransformCollection * This,
    /* [in] */ long lIndex);


void __RPC_STUB IWMEncTransformCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_RemoveAll_Proxy( 
    IWMEncTransformCollection * This);


void __RPC_STUB IWMEncTransformCollection_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncTransformCollection_Move_Proxy( 
    IWMEncTransformCollection * This,
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
            /* [retval][out] */ BSTR *pbstrTitle) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR bstrTitle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Author( 
            /* [retval][out] */ BSTR *pbstrAuthor) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Author( 
            /* [in] */ BSTR bstrAuthor) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Copyright( 
            /* [retval][out] */ BSTR *pbstrCopyright) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Copyright( 
            /* [in] */ BSTR bstrCopyright) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rating( 
            /* [retval][out] */ BSTR *pbstrRating) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rating( 
            /* [in] */ BSTR bstrRating) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pbstrDesc) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDesc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDisplayInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDisplayInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDisplayInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDisplayInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncDisplayInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncDisplayInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncDisplayInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncDisplayInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IWMEncDisplayInfo * This,
            /* [retval][out] */ BSTR *pbstrTitle);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IWMEncDisplayInfo * This,
            /* [in] */ BSTR bstrTitle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Author )( 
            IWMEncDisplayInfo * This,
            /* [retval][out] */ BSTR *pbstrAuthor);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Author )( 
            IWMEncDisplayInfo * This,
            /* [in] */ BSTR bstrAuthor);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Copyright )( 
            IWMEncDisplayInfo * This,
            /* [retval][out] */ BSTR *pbstrCopyright);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Copyright )( 
            IWMEncDisplayInfo * This,
            /* [in] */ BSTR bstrCopyright);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rating )( 
            IWMEncDisplayInfo * This,
            /* [retval][out] */ BSTR *pbstrRating);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rating )( 
            IWMEncDisplayInfo * This,
            /* [in] */ BSTR bstrRating);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IWMEncDisplayInfo * This,
            /* [retval][out] */ BSTR *pbstrDesc);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IWMEncDisplayInfo * This,
            /* [in] */ BSTR bstrDesc);
        
        END_INTERFACE
    } IWMEncDisplayInfoVtbl;

    interface IWMEncDisplayInfo
    {
        CONST_VTBL struct IWMEncDisplayInfoVtbl *lpVtbl;
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
    IWMEncDisplayInfo * This,
    /* [retval][out] */ BSTR *pbstrTitle);


void __RPC_STUB IWMEncDisplayInfo_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Title_Proxy( 
    IWMEncDisplayInfo * This,
    /* [in] */ BSTR bstrTitle);


void __RPC_STUB IWMEncDisplayInfo_put_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Author_Proxy( 
    IWMEncDisplayInfo * This,
    /* [retval][out] */ BSTR *pbstrAuthor);


void __RPC_STUB IWMEncDisplayInfo_get_Author_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Author_Proxy( 
    IWMEncDisplayInfo * This,
    /* [in] */ BSTR bstrAuthor);


void __RPC_STUB IWMEncDisplayInfo_put_Author_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Copyright_Proxy( 
    IWMEncDisplayInfo * This,
    /* [retval][out] */ BSTR *pbstrCopyright);


void __RPC_STUB IWMEncDisplayInfo_get_Copyright_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Copyright_Proxy( 
    IWMEncDisplayInfo * This,
    /* [in] */ BSTR bstrCopyright);


void __RPC_STUB IWMEncDisplayInfo_put_Copyright_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Rating_Proxy( 
    IWMEncDisplayInfo * This,
    /* [retval][out] */ BSTR *pbstrRating);


void __RPC_STUB IWMEncDisplayInfo_get_Rating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Rating_Proxy( 
    IWMEncDisplayInfo * This,
    /* [in] */ BSTR bstrRating);


void __RPC_STUB IWMEncDisplayInfo_put_Rating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_get_Description_Proxy( 
    IWMEncDisplayInfo * This,
    /* [retval][out] */ BSTR *pbstrDesc);


void __RPC_STUB IWMEncDisplayInfo_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncDisplayInfo_put_Description_Proxy( 
    IWMEncDisplayInfo * This,
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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [out] */ BSTR *pbstrName,
            /* [retval][out] */ VARIANT *pVarValue) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncAttributes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncAttributes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncAttributes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncAttributes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncAttributes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncAttributes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncAttributes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncAttributes * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncAttributes * This,
            /* [in] */ long Index,
            /* [out] */ BSTR *pbstrName,
            /* [retval][out] */ VARIANT *pVarValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncAttributes * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncAttributes * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncAttributes * This);
        
        END_INTERFACE
    } IWMEncAttributesVtbl;

    interface IWMEncAttributes
    {
        CONST_VTBL struct IWMEncAttributesVtbl *lpVtbl;
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
    IWMEncAttributes * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncAttributes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_Item_Proxy( 
    IWMEncAttributes * This,
    /* [in] */ long Index,
    /* [out] */ BSTR *pbstrName,
    /* [retval][out] */ VARIANT *pVarValue);


void __RPC_STUB IWMEncAttributes_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_Add_Proxy( 
    IWMEncAttributes * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT varValue);


void __RPC_STUB IWMEncAttributes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_Remove_Proxy( 
    IWMEncAttributes * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncAttributes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAttributes_RemoveAll_Proxy( 
    IWMEncAttributes * This);


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
            /* [retval][out] */ BSTR *bstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *bstrDescription) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaCount( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short *piCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MultipleBitrate( 
            /* [retval][out] */ VARIANT_BOOL *pbMBR) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudienceCollection( 
            /* [retval][out] */ IDispatch **ppAudienceCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxPacketSize( 
            /* [retval][out] */ long *plMaxPacketSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxPacketSize( 
            /* [in] */ long lMaxPacketSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncProfile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncProfile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncProfile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncProfile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncProfile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncProfile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncProfile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMEncProfile * This,
            /* [retval][out] */ BSTR *bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IWMEncProfile * This,
            /* [retval][out] */ BSTR *bstrDescription);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaCount )( 
            IWMEncProfile * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short *piCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MultipleBitrate )( 
            IWMEncProfile * This,
            /* [retval][out] */ VARIANT_BOOL *pbMBR);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudienceCollection )( 
            IWMEncProfile * This,
            /* [retval][out] */ IDispatch **ppAudienceCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxPacketSize )( 
            IWMEncProfile * This,
            /* [retval][out] */ long *plMaxPacketSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxPacketSize )( 
            IWMEncProfile * This,
            /* [in] */ long lMaxPacketSize);
        
        END_INTERFACE
    } IWMEncProfileVtbl;

    interface IWMEncProfile
    {
        CONST_VTBL struct IWMEncProfileVtbl *lpVtbl;
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
    IWMEncProfile * This,
    /* [retval][out] */ BSTR *bstrName);


void __RPC_STUB IWMEncProfile_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_Description_Proxy( 
    IWMEncProfile * This,
    /* [retval][out] */ BSTR *bstrDescription);


void __RPC_STUB IWMEncProfile_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_MediaCount_Proxy( 
    IWMEncProfile * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [retval][out] */ short *piCount);


void __RPC_STUB IWMEncProfile_get_MediaCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_MultipleBitrate_Proxy( 
    IWMEncProfile * This,
    /* [retval][out] */ VARIANT_BOOL *pbMBR);


void __RPC_STUB IWMEncProfile_get_MultipleBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_AudienceCollection_Proxy( 
    IWMEncProfile * This,
    /* [retval][out] */ IDispatch **ppAudienceCollection);


void __RPC_STUB IWMEncProfile_get_AudienceCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_get_MaxPacketSize_Proxy( 
    IWMEncProfile * This,
    /* [retval][out] */ long *plMaxPacketSize);


void __RPC_STUB IWMEncProfile_get_MaxPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile_put_MaxPacketSize_Proxy( 
    IWMEncProfile * This,
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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileDirectory( 
            /* [retval][out] */ BSTR *bstrDirectory) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileDirectory( 
            /* [in] */ BSTR bstrDirectory) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IWMEncProfile **ppProfile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncProfileCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncProfileCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncProfileCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncProfileCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncProfileCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncProfileCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncProfileCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncProfileCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncProfileCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncProfileCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileDirectory )( 
            IWMEncProfileCollection * This,
            /* [retval][out] */ BSTR *bstrDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProfileDirectory )( 
            IWMEncProfileCollection * This,
            /* [in] */ BSTR bstrDirectory);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncProfileCollection * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncProfileCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IWMEncProfile **ppProfile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWMEncProfileCollection * This);
        
        END_INTERFACE
    } IWMEncProfileCollectionVtbl;

    interface IWMEncProfileCollection
    {
        CONST_VTBL struct IWMEncProfileCollectionVtbl *lpVtbl;
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
    IWMEncProfileCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncProfileCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_get_Count_Proxy( 
    IWMEncProfileCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncProfileCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_get_ProfileDirectory_Proxy( 
    IWMEncProfileCollection * This,
    /* [retval][out] */ BSTR *bstrDirectory);


void __RPC_STUB IWMEncProfileCollection_get_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_put_ProfileDirectory_Proxy( 
    IWMEncProfileCollection * This,
    /* [in] */ BSTR bstrDirectory);


void __RPC_STUB IWMEncProfileCollection_put_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_get__NewEnum_Proxy( 
    IWMEncProfileCollection * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncProfileCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_Item_Proxy( 
    IWMEncProfileCollection * This,
    /* [in] */ long Index,
    /* [retval][out] */ IWMEncProfile **ppProfile);


void __RPC_STUB IWMEncProfileCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileCollection_Refresh_Proxy( 
    IWMEncProfileCollection * This);


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
            /* [retval][out] */ BSTR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalFileName( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteFileName( 
            /* [retval][out] */ BSTR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteFileName( 
            /* [in] */ BSTR bstrFileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalFileName )( 
            IWMEncFile * This,
            /* [retval][out] */ BSTR *pbstrFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalFileName )( 
            IWMEncFile * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteFileName )( 
            IWMEncFile * This,
            /* [retval][out] */ BSTR *pbstrFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteFileName )( 
            IWMEncFile * This,
            /* [in] */ BSTR bstrFileName);
        
        END_INTERFACE
    } IWMEncFileVtbl;

    interface IWMEncFile
    {
        CONST_VTBL struct IWMEncFileVtbl *lpVtbl;
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
    IWMEncFile * This,
    /* [retval][out] */ BSTR *pbstrFileName);


void __RPC_STUB IWMEncFile_get_LocalFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFile_put_LocalFileName_Proxy( 
    IWMEncFile * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncFile_put_LocalFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFile_get_RemoteFileName_Proxy( 
    IWMEncFile * This,
    /* [retval][out] */ BSTR *pbstrFileName);


void __RPC_STUB IWMEncFile_get_RemoteFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFile_put_RemoteFileName_Proxy( 
    IWMEncFile * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncFile_put_RemoteFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncFile_INTERFACE_DEFINED__ */


#ifndef __IWMEncFile2_INTERFACE_DEFINED__
#define __IWMEncFile2_INTERFACE_DEFINED__

/* interface IWMEncFile2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncFile2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10CBC168-7F83-451e-90A1-75F43E2C20A0")
    IWMEncFile2 : public IWMEncFile
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDuration( 
            /* [retval][out] */ WMENC_LONGLONG *plTime) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDuration( 
            /* [in] */ WMENC_LONGLONG lTime) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileSize( 
            /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileSize( 
            /* [in] */ WMENC_LONGLONG qwOutputFileSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncFile2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncFile2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncFile2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncFile2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncFile2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncFile2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncFile2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncFile2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalFileName )( 
            IWMEncFile2 * This,
            /* [retval][out] */ BSTR *pbstrFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalFileName )( 
            IWMEncFile2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteFileName )( 
            IWMEncFile2 * This,
            /* [retval][out] */ BSTR *pbstrFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteFileName )( 
            IWMEncFile2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDuration )( 
            IWMEncFile2 * This,
            /* [retval][out] */ WMENC_LONGLONG *plTime);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDuration )( 
            IWMEncFile2 * This,
            /* [in] */ WMENC_LONGLONG lTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileSize )( 
            IWMEncFile2 * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileSize )( 
            IWMEncFile2 * This,
            /* [in] */ WMENC_LONGLONG qwOutputFileSize);
        
        END_INTERFACE
    } IWMEncFile2Vtbl;

    interface IWMEncFile2
    {
        CONST_VTBL struct IWMEncFile2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncFile2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncFile2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncFile2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncFile2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncFile2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncFile2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncFile2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncFile2_get_LocalFileName(This,pbstrFileName)	\
    (This)->lpVtbl -> get_LocalFileName(This,pbstrFileName)

#define IWMEncFile2_put_LocalFileName(This,bstrFileName)	\
    (This)->lpVtbl -> put_LocalFileName(This,bstrFileName)

#define IWMEncFile2_get_RemoteFileName(This,pbstrFileName)	\
    (This)->lpVtbl -> get_RemoteFileName(This,pbstrFileName)

#define IWMEncFile2_put_RemoteFileName(This,bstrFileName)	\
    (This)->lpVtbl -> put_RemoteFileName(This,bstrFileName)


#define IWMEncFile2_get_FileDuration(This,plTime)	\
    (This)->lpVtbl -> get_FileDuration(This,plTime)

#define IWMEncFile2_put_FileDuration(This,lTime)	\
    (This)->lpVtbl -> put_FileDuration(This,lTime)

#define IWMEncFile2_get_FileSize(This,pqwOutputFileSize)	\
    (This)->lpVtbl -> get_FileSize(This,pqwOutputFileSize)

#define IWMEncFile2_put_FileSize(This,qwOutputFileSize)	\
    (This)->lpVtbl -> put_FileSize(This,qwOutputFileSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFile2_get_FileDuration_Proxy( 
    IWMEncFile2 * This,
    /* [retval][out] */ WMENC_LONGLONG *plTime);


void __RPC_STUB IWMEncFile2_get_FileDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFile2_put_FileDuration_Proxy( 
    IWMEncFile2 * This,
    /* [in] */ WMENC_LONGLONG lTime);


void __RPC_STUB IWMEncFile2_put_FileDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFile2_get_FileSize_Proxy( 
    IWMEncFile2 * This,
    /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileSize);


void __RPC_STUB IWMEncFile2_get_FileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFile2_put_FileSize_Proxy( 
    IWMEncFile2 * This,
    /* [in] */ WMENC_LONGLONG qwOutputFileSize);


void __RPC_STUB IWMEncFile2_put_FileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncFile2_INTERFACE_DEFINED__ */


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
            /* [retval][out] */ long *piPort) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PortNumber( 
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [in] */ long iPort) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncBroadcastVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncBroadcast * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncBroadcast * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncBroadcast * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncBroadcast * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncBroadcast * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncBroadcast * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncBroadcast * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PortNumber )( 
            IWMEncBroadcast * This,
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [retval][out] */ long *piPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PortNumber )( 
            IWMEncBroadcast * This,
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [in] */ long iPort);
        
        END_INTERFACE
    } IWMEncBroadcastVtbl;

    interface IWMEncBroadcast
    {
        CONST_VTBL struct IWMEncBroadcastVtbl *lpVtbl;
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
    IWMEncBroadcast * This,
    /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
    /* [retval][out] */ long *piPort);


void __RPC_STUB IWMEncBroadcast_get_PortNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBroadcast_put_PortNumber_Proxy( 
    IWMEncBroadcast * This,
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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [out] */ IUnknown **ppDataView,
            /* [retval][out] */ long *plStreamCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IUnknown *pDataView,
            /* [retval][out] */ long *plStreamCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long lStreamCookie) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDataViewCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDataViewCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDataViewCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDataViewCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncDataViewCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncDataViewCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncDataViewCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncDataViewCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncDataViewCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncDataViewCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncDataViewCollection * This,
            /* [in] */ long Index,
            /* [out] */ IUnknown **ppDataView,
            /* [retval][out] */ long *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncDataViewCollection * This,
            /* [in] */ IUnknown *pDataView,
            /* [retval][out] */ long *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncDataViewCollection * This,
            /* [in] */ long lStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncDataViewCollection * This);
        
        END_INTERFACE
    } IWMEncDataViewCollectionVtbl;

    interface IWMEncDataViewCollection
    {
        CONST_VTBL struct IWMEncDataViewCollectionVtbl *lpVtbl;
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
    IWMEncDataViewCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncDataViewCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_get_Count_Proxy( 
    IWMEncDataViewCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncDataViewCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_Item_Proxy( 
    IWMEncDataViewCollection * This,
    /* [in] */ long Index,
    /* [out] */ IUnknown **ppDataView,
    /* [retval][out] */ long *plStreamCookie);


void __RPC_STUB IWMEncDataViewCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_Add_Proxy( 
    IWMEncDataViewCollection * This,
    /* [in] */ IUnknown *pDataView,
    /* [retval][out] */ long *plStreamCookie);


void __RPC_STUB IWMEncDataViewCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_Remove_Proxy( 
    IWMEncDataViewCollection * This,
    /* [in] */ long lStreamCookie);


void __RPC_STUB IWMEncDataViewCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDataViewCollection_RemoveAll_Proxy( 
    IWMEncDataViewCollection * This);


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
            /* [retval][out] */ long *plBandwidth) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ViewBandwidth( 
            /* [in] */ long lBandwidth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPostViewCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncPostViewCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncPostViewCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncPostViewCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncPostViewCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncPostViewCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncPostViewCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncPostViewCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncPostViewCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncPostViewCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncPostViewCollection * This,
            /* [in] */ long Index,
            /* [out] */ IUnknown **ppDataView,
            /* [retval][out] */ long *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncPostViewCollection * This,
            /* [in] */ IUnknown *pDataView,
            /* [retval][out] */ long *plStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncPostViewCollection * This,
            /* [in] */ long lStreamCookie);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncPostViewCollection * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ViewBandwidth )( 
            IWMEncPostViewCollection * This,
            /* [retval][out] */ long *plBandwidth);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ViewBandwidth )( 
            IWMEncPostViewCollection * This,
            /* [in] */ long lBandwidth);
        
        END_INTERFACE
    } IWMEncPostViewCollectionVtbl;

    interface IWMEncPostViewCollection
    {
        CONST_VTBL struct IWMEncPostViewCollectionVtbl *lpVtbl;
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
    IWMEncPostViewCollection * This,
    /* [retval][out] */ long *plBandwidth);


void __RPC_STUB IWMEncPostViewCollection_get_ViewBandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncPostViewCollection_put_ViewBandwidth_Proxy( 
    IWMEncPostViewCollection * This,
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
            /* [retval][out] */ WMENC_SOURCE_TYPE *enumType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInput( 
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme = L"",
            /* [defaultvalue][in] */ BSTR bstrStreamName = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInput( 
            /* [out] */ BSTR *bstrStreamName,
            /* [out] */ BSTR *bstrScheme,
            /* [retval][out] */ BSTR *pbstrInput) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Repeat( 
            /* [in] */ VARIANT_BOOL bRepeat) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Repeat( 
            /* [retval][out] */ VARIANT_BOOL *pbRepeat) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkIn( 
            /* [retval][out] */ long *plMarkIn) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkIn( 
            /* [in] */ long lMarkIn) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkOut( 
            /* [retval][out] */ long *plMarkOut) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkOut( 
            /* [in] */ long lMarkOut) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransformCollection( 
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransformPluginCount( 
            /* [out] */ DWORD *pdwCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransformPlugin( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkTransformPlugin) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreviewCollection( 
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PostviewCollection( 
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSourcePlugin( 
            /* [retval][out] */ IUnknown **ppUnkPlugin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncSource * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncSource * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncSource * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncSource * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IWMEncSource * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE *enumType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInput )( 
            IWMEncSource * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrStreamName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInput )( 
            IWMEncSource * This,
            /* [out] */ BSTR *bstrStreamName,
            /* [out] */ BSTR *bstrScheme,
            /* [retval][out] */ BSTR *pbstrInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Repeat )( 
            IWMEncSource * This,
            /* [in] */ VARIANT_BOOL bRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Repeat )( 
            IWMEncSource * This,
            /* [retval][out] */ VARIANT_BOOL *pbRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkIn )( 
            IWMEncSource * This,
            /* [retval][out] */ long *plMarkIn);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkIn )( 
            IWMEncSource * This,
            /* [in] */ long lMarkIn);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkOut )( 
            IWMEncSource * This,
            /* [retval][out] */ long *plMarkOut);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkOut )( 
            IWMEncSource * This,
            /* [in] */ long lMarkOut);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformCollection )( 
            IWMEncSource * This,
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPluginCount )( 
            IWMEncSource * This,
            /* [out] */ DWORD *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPlugin )( 
            IWMEncSource * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkTransformPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreviewCollection )( 
            IWMEncSource * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PostviewCollection )( 
            IWMEncSource * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSourcePlugin )( 
            IWMEncSource * This,
            /* [retval][out] */ IUnknown **ppUnkPlugin);
        
        END_INTERFACE
    } IWMEncSourceVtbl;

    interface IWMEncSource
    {
        CONST_VTBL struct IWMEncSourceVtbl *lpVtbl;
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
    IWMEncSource * This,
    /* [retval][out] */ WMENC_SOURCE_TYPE *enumType);


void __RPC_STUB IWMEncSource_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_SetInput_Proxy( 
    IWMEncSource * This,
    /* [in] */ BSTR bstrInput,
    /* [defaultvalue][in] */ BSTR bstrScheme,
    /* [defaultvalue][in] */ BSTR bstrStreamName);


void __RPC_STUB IWMEncSource_SetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetInput_Proxy( 
    IWMEncSource * This,
    /* [out] */ BSTR *bstrStreamName,
    /* [out] */ BSTR *bstrScheme,
    /* [retval][out] */ BSTR *pbstrInput);


void __RPC_STUB IWMEncSource_GetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSource_put_Repeat_Proxy( 
    IWMEncSource * This,
    /* [in] */ VARIANT_BOOL bRepeat);


void __RPC_STUB IWMEncSource_put_Repeat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_Repeat_Proxy( 
    IWMEncSource * This,
    /* [retval][out] */ VARIANT_BOOL *pbRepeat);


void __RPC_STUB IWMEncSource_get_Repeat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_MarkIn_Proxy( 
    IWMEncSource * This,
    /* [retval][out] */ long *plMarkIn);


void __RPC_STUB IWMEncSource_get_MarkIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSource_put_MarkIn_Proxy( 
    IWMEncSource * This,
    /* [in] */ long lMarkIn);


void __RPC_STUB IWMEncSource_put_MarkIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_MarkOut_Proxy( 
    IWMEncSource * This,
    /* [retval][out] */ long *plMarkOut);


void __RPC_STUB IWMEncSource_get_MarkOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSource_put_MarkOut_Proxy( 
    IWMEncSource * This,
    /* [in] */ long lMarkOut);


void __RPC_STUB IWMEncSource_put_MarkOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_TransformCollection_Proxy( 
    IWMEncSource * This,
    /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);


void __RPC_STUB IWMEncSource_get_TransformCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetTransformPluginCount_Proxy( 
    IWMEncSource * This,
    /* [out] */ DWORD *pdwCount);


void __RPC_STUB IWMEncSource_GetTransformPluginCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetTransformPlugin_Proxy( 
    IWMEncSource * This,
    /* [in] */ DWORD dwIndex,
    /* [out] */ IUnknown **ppUnkTransformPlugin);


void __RPC_STUB IWMEncSource_GetTransformPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_PreviewCollection_Proxy( 
    IWMEncSource * This,
    /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);


void __RPC_STUB IWMEncSource_get_PreviewCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSource_get_PostviewCollection_Proxy( 
    IWMEncSource * This,
    /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);


void __RPC_STUB IWMEncSource_get_PostviewCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSource_GetSourcePlugin_Proxy( 
    IWMEncSource * This,
    /* [retval][out] */ IUnknown **ppUnkPlugin);


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
            /* [retval][out] */ WMENC_CROPPING_MODE *penumCroppingMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingMode( 
            /* [in] */ WMENC_CROPPING_MODE enumCroppingMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingLeftMargin( 
            /* [retval][out] */ long *plLeft) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingLeftMargin( 
            /* [in] */ long lLeft) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingTopMargin( 
            /* [retval][out] */ long *plTop) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingTopMargin( 
            /* [in] */ long lTop) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingRightMargin( 
            /* [retval][out] */ long *plRight) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingRightMargin( 
            /* [in] */ long lRight) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CroppingBottomMargin( 
            /* [retval][out] */ long *plBottom) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CroppingBottomMargin( 
            /* [in] */ long lBottom) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Optimization( 
            /* [retval][out] */ WMENC_VIDEO_OPTIMIZATION *penumOptimization) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Optimization( 
            /* [in] */ WMENC_VIDEO_OPTIMIZATION enumOptimization) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PixelFormat( 
            /* [retval][out] */ WMENC_PIXELFORMAT_VIDEO *penumPixelFormat) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PixelFormat( 
            /* [in] */ WMENC_PIXELFORMAT_VIDEO enumPixelFormat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncVideoSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncVideoSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncVideoSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncVideoSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncVideoSource * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncVideoSource * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncVideoSource * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncVideoSource * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE *enumType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInput )( 
            IWMEncVideoSource * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrStreamName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInput )( 
            IWMEncVideoSource * This,
            /* [out] */ BSTR *bstrStreamName,
            /* [out] */ BSTR *bstrScheme,
            /* [retval][out] */ BSTR *pbstrInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Repeat )( 
            IWMEncVideoSource * This,
            /* [in] */ VARIANT_BOOL bRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Repeat )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ VARIANT_BOOL *pbRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkIn )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ long *plMarkIn);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkIn )( 
            IWMEncVideoSource * This,
            /* [in] */ long lMarkIn);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkOut )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ long *plMarkOut);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkOut )( 
            IWMEncVideoSource * This,
            /* [in] */ long lMarkOut);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformCollection )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPluginCount )( 
            IWMEncVideoSource * This,
            /* [out] */ DWORD *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPlugin )( 
            IWMEncVideoSource * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkTransformPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreviewCollection )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PostviewCollection )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSourcePlugin )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ IUnknown **ppUnkPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingMode )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ WMENC_CROPPING_MODE *penumCroppingMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingMode )( 
            IWMEncVideoSource * This,
            /* [in] */ WMENC_CROPPING_MODE enumCroppingMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingLeftMargin )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ long *plLeft);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingLeftMargin )( 
            IWMEncVideoSource * This,
            /* [in] */ long lLeft);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingTopMargin )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ long *plTop);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingTopMargin )( 
            IWMEncVideoSource * This,
            /* [in] */ long lTop);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingRightMargin )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ long *plRight);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingRightMargin )( 
            IWMEncVideoSource * This,
            /* [in] */ long lRight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingBottomMargin )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ long *plBottom);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingBottomMargin )( 
            IWMEncVideoSource * This,
            /* [in] */ long lBottom);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Optimization )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ WMENC_VIDEO_OPTIMIZATION *penumOptimization);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Optimization )( 
            IWMEncVideoSource * This,
            /* [in] */ WMENC_VIDEO_OPTIMIZATION enumOptimization);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelFormat )( 
            IWMEncVideoSource * This,
            /* [retval][out] */ WMENC_PIXELFORMAT_VIDEO *penumPixelFormat);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PixelFormat )( 
            IWMEncVideoSource * This,
            /* [in] */ WMENC_PIXELFORMAT_VIDEO enumPixelFormat);
        
        END_INTERFACE
    } IWMEncVideoSourceVtbl;

    interface IWMEncVideoSource
    {
        CONST_VTBL struct IWMEncVideoSourceVtbl *lpVtbl;
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
    IWMEncVideoSource * This,
    /* [retval][out] */ WMENC_CROPPING_MODE *penumCroppingMode);


void __RPC_STUB IWMEncVideoSource_get_CroppingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingMode_Proxy( 
    IWMEncVideoSource * This,
    /* [in] */ WMENC_CROPPING_MODE enumCroppingMode);


void __RPC_STUB IWMEncVideoSource_put_CroppingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingLeftMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [retval][out] */ long *plLeft);


void __RPC_STUB IWMEncVideoSource_get_CroppingLeftMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingLeftMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [in] */ long lLeft);


void __RPC_STUB IWMEncVideoSource_put_CroppingLeftMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingTopMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [retval][out] */ long *plTop);


void __RPC_STUB IWMEncVideoSource_get_CroppingTopMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingTopMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [in] */ long lTop);


void __RPC_STUB IWMEncVideoSource_put_CroppingTopMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingRightMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [retval][out] */ long *plRight);


void __RPC_STUB IWMEncVideoSource_get_CroppingRightMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingRightMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [in] */ long lRight);


void __RPC_STUB IWMEncVideoSource_put_CroppingRightMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_CroppingBottomMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [retval][out] */ long *plBottom);


void __RPC_STUB IWMEncVideoSource_get_CroppingBottomMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_CroppingBottomMargin_Proxy( 
    IWMEncVideoSource * This,
    /* [in] */ long lBottom);


void __RPC_STUB IWMEncVideoSource_put_CroppingBottomMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_Optimization_Proxy( 
    IWMEncVideoSource * This,
    /* [retval][out] */ WMENC_VIDEO_OPTIMIZATION *penumOptimization);


void __RPC_STUB IWMEncVideoSource_get_Optimization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_Optimization_Proxy( 
    IWMEncVideoSource * This,
    /* [in] */ WMENC_VIDEO_OPTIMIZATION enumOptimization);


void __RPC_STUB IWMEncVideoSource_put_Optimization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_get_PixelFormat_Proxy( 
    IWMEncVideoSource * This,
    /* [retval][out] */ WMENC_PIXELFORMAT_VIDEO *penumPixelFormat);


void __RPC_STUB IWMEncVideoSource_get_PixelFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource_put_PixelFormat_Proxy( 
    IWMEncVideoSource * This,
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
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceCount( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short *iSourceCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Source( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iIndex,
            /* [retval][out] */ IWMEncSource **ppSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSource( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ IWMEncSource **ppSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveSource( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IWMEncProfile **ppProfile) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Profile( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudienceCollection( 
            /* [retval][out] */ IDispatch **ppAudienceCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoArchive( 
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [retval][out] */ WMENC_ARCHIVE_OPERATION *penumArchiveOp) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoArchive( 
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoSetFileSource( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PrepareToEncode( 
            VARIANT_BOOL bPrepare) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GroupTransformCollection( 
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGroupTransformPluginCount( 
            /* [out] */ DWORD *pdwCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGroupTransformPlugin( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkPlugin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourceGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncSourceGroup * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncSourceGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncSourceGroup * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncSourceGroup * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncSourceGroup * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncSourceGroup * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncSourceGroup * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMEncSourceGroup * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWMEncSourceGroup * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceCount )( 
            IWMEncSourceGroup * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short *iSourceCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Source )( 
            IWMEncSourceGroup * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iIndex,
            /* [retval][out] */ IWMEncSource **ppSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddSource )( 
            IWMEncSourceGroup * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ IWMEncSource **ppSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveSource )( 
            IWMEncSourceGroup * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IWMEncSourceGroup * This,
            /* [retval][out] */ IWMEncProfile **ppProfile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Profile )( 
            IWMEncSourceGroup * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudienceCollection )( 
            IWMEncSourceGroup * This,
            /* [retval][out] */ IDispatch **ppAudienceCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoArchive )( 
            IWMEncSourceGroup * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [retval][out] */ WMENC_ARCHIVE_OPERATION *penumArchiveOp);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoArchive )( 
            IWMEncSourceGroup * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoSetFileSource )( 
            IWMEncSourceGroup * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PrepareToEncode )( 
            IWMEncSourceGroup * This,
            VARIANT_BOOL bPrepare);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GroupTransformCollection )( 
            IWMEncSourceGroup * This,
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGroupTransformPluginCount )( 
            IWMEncSourceGroup * This,
            /* [out] */ DWORD *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGroupTransformPlugin )( 
            IWMEncSourceGroup * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkPlugin);
        
        END_INTERFACE
    } IWMEncSourceGroupVtbl;

    interface IWMEncSourceGroup
    {
        CONST_VTBL struct IWMEncSourceGroupVtbl *lpVtbl;
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
    IWMEncSourceGroup * This,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB IWMEncSourceGroup_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_put_Name_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IWMEncSourceGroup_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_SourceCount_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [retval][out] */ short *iSourceCount);


void __RPC_STUB IWMEncSourceGroup_get_SourceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_Source_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ short iIndex,
    /* [retval][out] */ IWMEncSource **ppSource);


void __RPC_STUB IWMEncSourceGroup_get_Source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_AddSource_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [retval][out] */ IWMEncSource **ppSource);


void __RPC_STUB IWMEncSourceGroup_AddSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_RemoveSource_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncSourceGroup_RemoveSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_Profile_Proxy( 
    IWMEncSourceGroup * This,
    /* [retval][out] */ IWMEncProfile **ppProfile);


void __RPC_STUB IWMEncSourceGroup_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_put_Profile_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncSourceGroup_put_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_AudienceCollection_Proxy( 
    IWMEncSourceGroup * This,
    /* [retval][out] */ IDispatch **ppAudienceCollection);


void __RPC_STUB IWMEncSourceGroup_get_AudienceCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_AutoArchive_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
    /* [retval][out] */ WMENC_ARCHIVE_OPERATION *penumArchiveOp);


void __RPC_STUB IWMEncSourceGroup_get_AutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_put_AutoArchive_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
    /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);


void __RPC_STUB IWMEncSourceGroup_put_AutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_AutoSetFileSource_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncSourceGroup_AutoSetFileSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_PrepareToEncode_Proxy( 
    IWMEncSourceGroup * This,
    VARIANT_BOOL bPrepare);


void __RPC_STUB IWMEncSourceGroup_PrepareToEncode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_get_GroupTransformCollection_Proxy( 
    IWMEncSourceGroup * This,
    /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);


void __RPC_STUB IWMEncSourceGroup_get_GroupTransformCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_GetGroupTransformPluginCount_Proxy( 
    IWMEncSourceGroup * This,
    /* [out] */ DWORD *pdwCount);


void __RPC_STUB IWMEncSourceGroup_GetGroupTransformPluginCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup_GetGroupTransformPlugin_Proxy( 
    IWMEncSourceGroup * This,
    /* [in] */ DWORD dwIndex,
    /* [out] */ IUnknown **ppUnkPlugin);


void __RPC_STUB IWMEncSourceGroup_GetGroupTransformPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSourceGroup_INTERFACE_DEFINED__ */


#ifndef __IWMEncSourceGroup2_INTERFACE_DEFINED__
#define __IWMEncSourceGroup2_INTERFACE_DEFINED__

/* interface IWMEncSourceGroup2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncSourceGroup2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B608A-BBC6-11D2-A329-006097C4E476")
    IWMEncSourceGroup2 : public IWMEncSourceGroup
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceControlCollection( 
            /* [retval][out] */ IWMEncDeviceControlCollection **ppDeviceControlCollection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutoRollover( 
            /* [out] */ VARIANT *pvar,
            /* [retval][out] */ BSTR *pbstrSourceGroupName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAutoRollover( 
            /* [in] */ long lRolloverTime,
            /* [in] */ BSTR bstrSourceGroupName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourceGroup2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncSourceGroup2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncSourceGroup2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncSourceGroup2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMEncSourceGroup2 * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceCount )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short *iSourceCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Source )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iIndex,
            /* [retval][out] */ IWMEncSource **ppSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddSource )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ IWMEncSource **ppSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveSource )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IWMEncSourceGroup2 * This,
            /* [retval][out] */ IWMEncProfile **ppProfile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Profile )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudienceCollection )( 
            IWMEncSourceGroup2 * This,
            /* [retval][out] */ IDispatch **ppAudienceCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoArchive )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [retval][out] */ WMENC_ARCHIVE_OPERATION *penumArchiveOp);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoArchive )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoSetFileSource )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PrepareToEncode )( 
            IWMEncSourceGroup2 * This,
            VARIANT_BOOL bPrepare);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GroupTransformCollection )( 
            IWMEncSourceGroup2 * This,
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGroupTransformPluginCount )( 
            IWMEncSourceGroup2 * This,
            /* [out] */ DWORD *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGroupTransformPlugin )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeviceControlCollection )( 
            IWMEncSourceGroup2 * This,
            /* [retval][out] */ IWMEncDeviceControlCollection **ppDeviceControlCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutoRollover )( 
            IWMEncSourceGroup2 * This,
            /* [out] */ VARIANT *pvar,
            /* [retval][out] */ BSTR *pbstrSourceGroupName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAutoRollover )( 
            IWMEncSourceGroup2 * This,
            /* [in] */ long lRolloverTime,
            /* [in] */ BSTR bstrSourceGroupName);
        
        END_INTERFACE
    } IWMEncSourceGroup2Vtbl;

    interface IWMEncSourceGroup2
    {
        CONST_VTBL struct IWMEncSourceGroup2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncSourceGroup2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncSourceGroup2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncSourceGroup2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncSourceGroup2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncSourceGroup2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncSourceGroup2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncSourceGroup2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncSourceGroup2_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IWMEncSourceGroup2_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IWMEncSourceGroup2_get_SourceCount(This,enumType,iSourceCount)	\
    (This)->lpVtbl -> get_SourceCount(This,enumType,iSourceCount)

#define IWMEncSourceGroup2_get_Source(This,enumType,iIndex,ppSource)	\
    (This)->lpVtbl -> get_Source(This,enumType,iIndex,ppSource)

#define IWMEncSourceGroup2_AddSource(This,enumType,ppSource)	\
    (This)->lpVtbl -> AddSource(This,enumType,ppSource)

#define IWMEncSourceGroup2_RemoveSource(This,enumType,var)	\
    (This)->lpVtbl -> RemoveSource(This,enumType,var)

#define IWMEncSourceGroup2_get_Profile(This,ppProfile)	\
    (This)->lpVtbl -> get_Profile(This,ppProfile)

#define IWMEncSourceGroup2_put_Profile(This,var)	\
    (This)->lpVtbl -> put_Profile(This,var)

#define IWMEncSourceGroup2_get_AudienceCollection(This,ppAudienceCollection)	\
    (This)->lpVtbl -> get_AudienceCollection(This,ppAudienceCollection)

#define IWMEncSourceGroup2_get_AutoArchive(This,enumArchiveType,penumArchiveOp)	\
    (This)->lpVtbl -> get_AutoArchive(This,enumArchiveType,penumArchiveOp)

#define IWMEncSourceGroup2_put_AutoArchive(This,enumArchiveType,enumArchiveOp)	\
    (This)->lpVtbl -> put_AutoArchive(This,enumArchiveType,enumArchiveOp)

#define IWMEncSourceGroup2_AutoSetFileSource(This,bstrFileName)	\
    (This)->lpVtbl -> AutoSetFileSource(This,bstrFileName)

#define IWMEncSourceGroup2_PrepareToEncode(This,bPrepare)	\
    (This)->lpVtbl -> PrepareToEncode(This,bPrepare)

#define IWMEncSourceGroup2_get_GroupTransformCollection(This,ppTransformCollection)	\
    (This)->lpVtbl -> get_GroupTransformCollection(This,ppTransformCollection)

#define IWMEncSourceGroup2_GetGroupTransformPluginCount(This,pdwCount)	\
    (This)->lpVtbl -> GetGroupTransformPluginCount(This,pdwCount)

#define IWMEncSourceGroup2_GetGroupTransformPlugin(This,dwIndex,ppUnkPlugin)	\
    (This)->lpVtbl -> GetGroupTransformPlugin(This,dwIndex,ppUnkPlugin)


#define IWMEncSourceGroup2_get_DeviceControlCollection(This,ppDeviceControlCollection)	\
    (This)->lpVtbl -> get_DeviceControlCollection(This,ppDeviceControlCollection)

#define IWMEncSourceGroup2_GetAutoRollover(This,pvar,pbstrSourceGroupName)	\
    (This)->lpVtbl -> GetAutoRollover(This,pvar,pbstrSourceGroupName)

#define IWMEncSourceGroup2_SetAutoRollover(This,lRolloverTime,bstrSourceGroupName)	\
    (This)->lpVtbl -> SetAutoRollover(This,lRolloverTime,bstrSourceGroupName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup2_get_DeviceControlCollection_Proxy( 
    IWMEncSourceGroup2 * This,
    /* [retval][out] */ IWMEncDeviceControlCollection **ppDeviceControlCollection);


void __RPC_STUB IWMEncSourceGroup2_get_DeviceControlCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup2_GetAutoRollover_Proxy( 
    IWMEncSourceGroup2 * This,
    /* [out] */ VARIANT *pvar,
    /* [retval][out] */ BSTR *pbstrSourceGroupName);


void __RPC_STUB IWMEncSourceGroup2_GetAutoRollover_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroup2_SetAutoRollover_Proxy( 
    IWMEncSourceGroup2 * This,
    /* [in] */ long lRolloverTime,
    /* [in] */ BSTR bstrSourceGroupName);


void __RPC_STUB IWMEncSourceGroup2_SetAutoRollover_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSourceGroup2_INTERFACE_DEFINED__ */


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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ IWMEncSourceGroup *pSourceGroup,
            /* [in] */ IWMEncSourceGroup *pSourceGroupInfront) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Active( 
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Active( 
            /* [in] */ IWMEncSourceGroup *pSourceGroup) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncSourceGroupCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncSourceGroupCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncSourceGroupCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncSourceGroupCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncSourceGroupCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncSourceGroupCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncSourceGroupCollection * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ IWMEncSourceGroup *pSourceGroup,
            /* [in] */ IWMEncSourceGroup *pSourceGroupInfront);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Active )( 
            IWMEncSourceGroupCollection * This,
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Active )( 
            IWMEncSourceGroupCollection * This,
            /* [in] */ IWMEncSourceGroup *pSourceGroup);
        
        END_INTERFACE
    } IWMEncSourceGroupCollectionVtbl;

    interface IWMEncSourceGroupCollection
    {
        CONST_VTBL struct IWMEncSourceGroupCollectionVtbl *lpVtbl;
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
    IWMEncSourceGroupCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncSourceGroupCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_get_Count_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncSourceGroupCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_get__NewEnum_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncSourceGroupCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Item_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Add_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Remove_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [in] */ VARIANT var);


void __RPC_STUB IWMEncSourceGroupCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_Move_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [in] */ IWMEncSourceGroup *pSourceGroup,
    /* [in] */ IWMEncSourceGroup *pSourceGroupInfront);


void __RPC_STUB IWMEncSourceGroupCollection_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_get_Active_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_get_Active_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncSourceGroupCollection_put_Active_Proxy( 
    IWMEncSourceGroupCollection * This,
    /* [in] */ IWMEncSourceGroup *pSourceGroup);


void __RPC_STUB IWMEncSourceGroupCollection_put_Active_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncSourceGroupCollection_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_wmencode_0283 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_wmencode_0283_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wmencode_0283_v0_0_s_ifspec;

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
            /* [retval][out] */ VARIANT_BOOL *pbStop) = 0;
        
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
            /* [retval][out] */ VARIANT_BOOL *pbEnableAutoArchive) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableAutoArchive( 
            /* [in] */ VARIANT_BOOL bEnableAutoArchive) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecordingLevel( 
            /* [in] */ short iIndex,
            /* [retval][out] */ long *lLevel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordingLevel( 
            /* [in] */ short iIndex,
            /* [in] */ long lLevel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecordingMute( 
            /* [in] */ short iIndex,
            /* [retval][out] */ VARIANT_BOOL *pbRecordMute) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordingMute( 
            /* [in] */ short iIndex,
            /* [in] */ VARIANT_BOOL bRecordMute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioLevel( 
            /* [in] */ WMENC_AUDIOLEVEL_UNITS units,
            /* [in] */ short iIndex,
            /* [out][in] */ long *plDuration,
            /* [out] */ double *pdLMin,
            /* [out] */ double *pdLAvg,
            /* [out] */ double *pdLMax,
            /* [out] */ double *pdRMin,
            /* [out] */ double *pdRAvg,
            /* [out] */ double *pdRMax) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceGroupCollection( 
            /* [retval][out] */ IWMEncSourceGroupCollection **ppSourceGroupCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourcePluginInfoManager( 
            /* [retval][out] */ IWMEncSourcePluginInfoManager **ppSourcePluginInfoManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransformPluginInfoManager( 
            /* [retval][out] */ IWMEncTransformPluginInfoManager **ppTransformPluginInfoManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayInfo( 
            /* [retval][out] */ IWMEncDisplayInfo **ppDisplayInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attributes( 
            /* [retval][out] */ IWMEncAttributes **ppAttributes) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Broadcast( 
            /* [retval][out] */ IWMEncBroadcast **ppBroadcast) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_File( 
            /* [retval][out] */ IWMEncFile **ppFile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Statistics( 
            /* [retval][out] */ IWMEncStatistics **ppStatistics) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileCollection( 
            /* [retval][out] */ IWMEncProfileCollection **ppProfileCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RunState( 
            /* [retval][out] */ WMENC_ENCODER_STATE *penumState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorState( 
            /* [retval][out] */ long *plResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ArchiveState( 
            /* [in] */ WMENC_ARCHIVE_TYPE enumType,
            /* [retval][out] */ WMENC_ARCHIVE_STATE *penumArchiveState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteAdmin( 
            /* [retval][out] */ VARIANT_BOOL *pbRemoteAdmin) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteAdmin( 
            /* [in] */ VARIANT_BOOL bRemoteAdmin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateBroadcastInfo( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexerState( 
            /* [retval][out] */ WMENC_INDEXER_STATE *penumIndexerState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoIndex( 
            /* [retval][out] */ VARIANT_BOOL *pbAutoIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoIndex( 
            /* [in] */ VARIANT_BOOL bAutoIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Indexer( 
            /* [in] */ WMENC_INDEXER_OPERATION enumIndexerOp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncoder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncoder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncoder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncoder * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncoder * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncoder * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncoder * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLocaleID )( 
            IWMEncoder * This,
            /* [in] */ long lLocaleID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IWMEncoder * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IWMEncoder * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IWMEncoder * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IWMEncoder * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoStop )( 
            IWMEncoder * This,
            /* [retval][out] */ VARIANT_BOOL *pbStop);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoStop )( 
            IWMEncoder * This,
            /* [in] */ VARIANT_BOOL bStop);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IWMEncoder * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PrepareToEncode )( 
            IWMEncoder * This,
            VARIANT_BOOL bPrepare);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IWMEncoder * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Archive )( 
            IWMEncoder * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendScript )( 
            IWMEncoder * This,
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnableAutoArchive )( 
            IWMEncoder * This,
            /* [retval][out] */ VARIANT_BOOL *pbEnableAutoArchive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnableAutoArchive )( 
            IWMEncoder * This,
            /* [in] */ VARIANT_BOOL bEnableAutoArchive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecordingLevel )( 
            IWMEncoder * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ long *lLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecordingLevel )( 
            IWMEncoder * This,
            /* [in] */ short iIndex,
            /* [in] */ long lLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecordingMute )( 
            IWMEncoder * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ VARIANT_BOOL *pbRecordMute);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecordingMute )( 
            IWMEncoder * This,
            /* [in] */ short iIndex,
            /* [in] */ VARIANT_BOOL bRecordMute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioLevel )( 
            IWMEncoder * This,
            /* [in] */ WMENC_AUDIOLEVEL_UNITS units,
            /* [in] */ short iIndex,
            /* [out][in] */ long *plDuration,
            /* [out] */ double *pdLMin,
            /* [out] */ double *pdLAvg,
            /* [out] */ double *pdLMax,
            /* [out] */ double *pdRMin,
            /* [out] */ double *pdRAvg,
            /* [out] */ double *pdRMax);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceGroupCollection )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncSourceGroupCollection **ppSourceGroupCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourcePluginInfoManager )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncSourcePluginInfoManager **ppSourcePluginInfoManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformPluginInfoManager )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncTransformPluginInfoManager **ppTransformPluginInfoManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayInfo )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncDisplayInfo **ppDisplayInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attributes )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncAttributes **ppAttributes);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Broadcast )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncBroadcast **ppBroadcast);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_File )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncFile **ppFile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Statistics )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncStatistics **ppStatistics);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileCollection )( 
            IWMEncoder * This,
            /* [retval][out] */ IWMEncProfileCollection **ppProfileCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunState )( 
            IWMEncoder * This,
            /* [retval][out] */ WMENC_ENCODER_STATE *penumState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ErrorState )( 
            IWMEncoder * This,
            /* [retval][out] */ long *plResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ArchiveState )( 
            IWMEncoder * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumType,
            /* [retval][out] */ WMENC_ARCHIVE_STATE *penumArchiveState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMEncoder * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWMEncoder * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteAdmin )( 
            IWMEncoder * This,
            /* [retval][out] */ VARIANT_BOOL *pbRemoteAdmin);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteAdmin )( 
            IWMEncoder * This,
            /* [in] */ VARIANT_BOOL bRemoteAdmin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateBroadcastInfo )( 
            IWMEncoder * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexerState )( 
            IWMEncoder * This,
            /* [retval][out] */ WMENC_INDEXER_STATE *penumIndexerState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoIndex )( 
            IWMEncoder * This,
            /* [retval][out] */ VARIANT_BOOL *pbAutoIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoIndex )( 
            IWMEncoder * This,
            /* [in] */ VARIANT_BOOL bAutoIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Indexer )( 
            IWMEncoder * This,
            /* [in] */ WMENC_INDEXER_OPERATION enumIndexerOp);
        
        END_INTERFACE
    } IWMEncoderVtbl;

    interface IWMEncoder
    {
        CONST_VTBL struct IWMEncoderVtbl *lpVtbl;
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
    IWMEncoder * This,
    /* [in] */ long lLocaleID);


void __RPC_STUB IWMEncoder_SetLocaleID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Load_Proxy( 
    IWMEncoder * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncoder_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Save_Proxy( 
    IWMEncoder * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncoder_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Start_Proxy( 
    IWMEncoder * This);


void __RPC_STUB IWMEncoder_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Stop_Proxy( 
    IWMEncoder * This);


void __RPC_STUB IWMEncoder_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_AutoStop_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ VARIANT_BOOL *pbStop);


void __RPC_STUB IWMEncoder_get_AutoStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_AutoStop_Proxy( 
    IWMEncoder * This,
    /* [in] */ VARIANT_BOOL bStop);


void __RPC_STUB IWMEncoder_put_AutoStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Pause_Proxy( 
    IWMEncoder * This);


void __RPC_STUB IWMEncoder_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_PrepareToEncode_Proxy( 
    IWMEncoder * This,
    VARIANT_BOOL bPrepare);


void __RPC_STUB IWMEncoder_PrepareToEncode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Reset_Proxy( 
    IWMEncoder * This);


void __RPC_STUB IWMEncoder_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Archive_Proxy( 
    IWMEncoder * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
    /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);


void __RPC_STUB IWMEncoder_Archive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_SendScript_Proxy( 
    IWMEncoder * This,
    /* [in] */ short iIndex,
    /* [in] */ BSTR bstrType,
    /* [in] */ BSTR bstrData);


void __RPC_STUB IWMEncoder_SendScript_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_EnableAutoArchive_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ VARIANT_BOOL *pbEnableAutoArchive);


void __RPC_STUB IWMEncoder_get_EnableAutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_EnableAutoArchive_Proxy( 
    IWMEncoder * This,
    /* [in] */ VARIANT_BOOL bEnableAutoArchive);


void __RPC_STUB IWMEncoder_put_EnableAutoArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RecordingLevel_Proxy( 
    IWMEncoder * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ long *lLevel);


void __RPC_STUB IWMEncoder_get_RecordingLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_RecordingLevel_Proxy( 
    IWMEncoder * This,
    /* [in] */ short iIndex,
    /* [in] */ long lLevel);


void __RPC_STUB IWMEncoder_put_RecordingLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RecordingMute_Proxy( 
    IWMEncoder * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ VARIANT_BOOL *pbRecordMute);


void __RPC_STUB IWMEncoder_get_RecordingMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_RecordingMute_Proxy( 
    IWMEncoder * This,
    /* [in] */ short iIndex,
    /* [in] */ VARIANT_BOOL bRecordMute);


void __RPC_STUB IWMEncoder_put_RecordingMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_GetAudioLevel_Proxy( 
    IWMEncoder * This,
    /* [in] */ WMENC_AUDIOLEVEL_UNITS units,
    /* [in] */ short iIndex,
    /* [out][in] */ long *plDuration,
    /* [out] */ double *pdLMin,
    /* [out] */ double *pdLAvg,
    /* [out] */ double *pdLMax,
    /* [out] */ double *pdRMin,
    /* [out] */ double *pdRAvg,
    /* [out] */ double *pdRMax);


void __RPC_STUB IWMEncoder_GetAudioLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_SourceGroupCollection_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncSourceGroupCollection **ppSourceGroupCollection);


void __RPC_STUB IWMEncoder_get_SourceGroupCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_SourcePluginInfoManager_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncSourcePluginInfoManager **ppSourcePluginInfoManager);


void __RPC_STUB IWMEncoder_get_SourcePluginInfoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_TransformPluginInfoManager_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncTransformPluginInfoManager **ppTransformPluginInfoManager);


void __RPC_STUB IWMEncoder_get_TransformPluginInfoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_DisplayInfo_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncDisplayInfo **ppDisplayInfo);


void __RPC_STUB IWMEncoder_get_DisplayInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Attributes_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncAttributes **ppAttributes);


void __RPC_STUB IWMEncoder_get_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Broadcast_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncBroadcast **ppBroadcast);


void __RPC_STUB IWMEncoder_get_Broadcast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_File_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncFile **ppFile);


void __RPC_STUB IWMEncoder_get_File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Statistics_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncStatistics **ppStatistics);


void __RPC_STUB IWMEncoder_get_Statistics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_ProfileCollection_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ IWMEncProfileCollection **ppProfileCollection);


void __RPC_STUB IWMEncoder_get_ProfileCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RunState_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ WMENC_ENCODER_STATE *penumState);


void __RPC_STUB IWMEncoder_get_RunState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_ErrorState_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ long *plResult);


void __RPC_STUB IWMEncoder_get_ErrorState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_ArchiveState_Proxy( 
    IWMEncoder * This,
    /* [in] */ WMENC_ARCHIVE_TYPE enumType,
    /* [retval][out] */ WMENC_ARCHIVE_STATE *penumArchiveState);


void __RPC_STUB IWMEncoder_get_ArchiveState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_Name_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB IWMEncoder_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_Name_Proxy( 
    IWMEncoder * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IWMEncoder_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_RemoteAdmin_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ VARIANT_BOOL *pbRemoteAdmin);


void __RPC_STUB IWMEncoder_get_RemoteAdmin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_RemoteAdmin_Proxy( 
    IWMEncoder * This,
    /* [in] */ VARIANT_BOOL bRemoteAdmin);


void __RPC_STUB IWMEncoder_put_RemoteAdmin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_GenerateBroadcastInfo_Proxy( 
    IWMEncoder * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncoder_GenerateBroadcastInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_IndexerState_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ WMENC_INDEXER_STATE *penumIndexerState);


void __RPC_STUB IWMEncoder_get_IndexerState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder_get_AutoIndex_Proxy( 
    IWMEncoder * This,
    /* [retval][out] */ VARIANT_BOOL *pbAutoIndex);


void __RPC_STUB IWMEncoder_get_AutoIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder_put_AutoIndex_Proxy( 
    IWMEncoder * This,
    /* [in] */ VARIANT_BOOL bAutoIndex);


void __RPC_STUB IWMEncoder_put_AutoIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder_Indexer_Proxy( 
    IWMEncoder * This,
    /* [in] */ WMENC_INDEXER_OPERATION enumIndexerOp);


void __RPC_STUB IWMEncoder_Indexer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncoder_INTERFACE_DEFINED__ */


#ifndef __IWMEncoder2_INTERFACE_DEFINED__
#define __IWMEncoder2_INTERFACE_DEFINED__

/* interface IWMEncoder2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncoder2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6081-BBC6-11D2-A329-006097C4E476")
    IWMEncoder2 : public IWMEncoder
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceControlPluginInfoManager( 
            /* [retval][out] */ IWMEncDeviceControlPluginInfoManager **ppDeviceControlPluginInfoManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentAnalyzer( 
            /* [retval][out] */ IWMEncContentAnalyzer **ppContentAnalyzer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertCleanpoint( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SynchronizeOperation( 
            /* [retval][out] */ VARIANT_BOOL *pbSyncOp) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SynchronizeOperation( 
            /* [in] */ VARIANT_BOOL bSyncOp) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderDRMContentAuthor( 
            /* [retval][out] */ IWMDRMContentAuthor **ppEncoderDRMAuthor) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WatermarkCollection( 
            /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
            /* [retval][out] */ IWMEncWatermarkCollection **ppWatermarks) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWatermark( 
            /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
            /* [in] */ short iIndex,
            /* [out] */ VARIANT *pvarConfigFile,
            /* [out] */ VARIANT *pvarCLSID,
            /* [retval][out] */ BSTR *pbstrWatermarkName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWatermark( 
            /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrWaterMarkName,
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ BSTR bstrConfigFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Flush( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableTimecode( 
            /* [retval][out] */ VARIANT_BOOL *pfTimecode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableTimecode( 
            /* [in] */ VARIANT_BOOL fTimecode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreserveSourceTimecode( 
            /* [retval][out] */ VARIANT_BOOL *pfSourceTimecode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PreserveSourceTimecode( 
            /* [in] */ VARIANT_BOOL fSourceTimecode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartingTimecode( 
            /* [retval][out] */ long *plTimecode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartingTimecode( 
            /* [in] */ long lTimecode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimecodeFrameRate( 
            /* [retval][out] */ long *plFrameRate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TimecodeFrameRate( 
            /* [in] */ long lFrameRate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoComplexity( 
            /* [retval][out] */ WMENC_VIDEOCOMPLEXITY *penumVideoComplexity) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoComplexity( 
            /* [in] */ WMENC_VIDEOCOMPLEXITY enumVideoComplexity) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncoder2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncoder2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncoder2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncoder2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncoder2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncoder2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncoder2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncoder2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLocaleID )( 
            IWMEncoder2 * This,
            /* [in] */ long lLocaleID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IWMEncoder2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IWMEncoder2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IWMEncoder2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IWMEncoder2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoStop )( 
            IWMEncoder2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbStop);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoStop )( 
            IWMEncoder2 * This,
            /* [in] */ VARIANT_BOOL bStop);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IWMEncoder2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PrepareToEncode )( 
            IWMEncoder2 * This,
            VARIANT_BOOL bPrepare);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IWMEncoder2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Archive )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumArchiveType,
            /* [in] */ WMENC_ARCHIVE_OPERATION enumArchiveOp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendScript )( 
            IWMEncoder2 * This,
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnableAutoArchive )( 
            IWMEncoder2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbEnableAutoArchive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnableAutoArchive )( 
            IWMEncoder2 * This,
            /* [in] */ VARIANT_BOOL bEnableAutoArchive);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecordingLevel )( 
            IWMEncoder2 * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ long *lLevel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecordingLevel )( 
            IWMEncoder2 * This,
            /* [in] */ short iIndex,
            /* [in] */ long lLevel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecordingMute )( 
            IWMEncoder2 * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ VARIANT_BOOL *pbRecordMute);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecordingMute )( 
            IWMEncoder2 * This,
            /* [in] */ short iIndex,
            /* [in] */ VARIANT_BOOL bRecordMute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioLevel )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_AUDIOLEVEL_UNITS units,
            /* [in] */ short iIndex,
            /* [out][in] */ long *plDuration,
            /* [out] */ double *pdLMin,
            /* [out] */ double *pdLAvg,
            /* [out] */ double *pdLMax,
            /* [out] */ double *pdRMin,
            /* [out] */ double *pdRAvg,
            /* [out] */ double *pdRMax);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceGroupCollection )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncSourceGroupCollection **ppSourceGroupCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourcePluginInfoManager )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncSourcePluginInfoManager **ppSourcePluginInfoManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformPluginInfoManager )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncTransformPluginInfoManager **ppTransformPluginInfoManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayInfo )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncDisplayInfo **ppDisplayInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attributes )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncAttributes **ppAttributes);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Broadcast )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncBroadcast **ppBroadcast);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_File )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncFile **ppFile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Statistics )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncStatistics **ppStatistics);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileCollection )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncProfileCollection **ppProfileCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunState )( 
            IWMEncoder2 * This,
            /* [retval][out] */ WMENC_ENCODER_STATE *penumState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ErrorState )( 
            IWMEncoder2 * This,
            /* [retval][out] */ long *plResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ArchiveState )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_ARCHIVE_TYPE enumType,
            /* [retval][out] */ WMENC_ARCHIVE_STATE *penumArchiveState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMEncoder2 * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWMEncoder2 * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteAdmin )( 
            IWMEncoder2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbRemoteAdmin);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteAdmin )( 
            IWMEncoder2 * This,
            /* [in] */ VARIANT_BOOL bRemoteAdmin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateBroadcastInfo )( 
            IWMEncoder2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexerState )( 
            IWMEncoder2 * This,
            /* [retval][out] */ WMENC_INDEXER_STATE *penumIndexerState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoIndex )( 
            IWMEncoder2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbAutoIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoIndex )( 
            IWMEncoder2 * This,
            /* [in] */ VARIANT_BOOL bAutoIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Indexer )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_INDEXER_OPERATION enumIndexerOp);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeviceControlPluginInfoManager )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncDeviceControlPluginInfoManager **ppDeviceControlPluginInfoManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentAnalyzer )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMEncContentAnalyzer **ppContentAnalyzer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertCleanpoint )( 
            IWMEncoder2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SynchronizeOperation )( 
            IWMEncoder2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbSyncOp);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SynchronizeOperation )( 
            IWMEncoder2 * This,
            /* [in] */ VARIANT_BOOL bSyncOp);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EncoderDRMContentAuthor )( 
            IWMEncoder2 * This,
            /* [retval][out] */ IWMDRMContentAuthor **ppEncoderDRMAuthor);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WatermarkCollection )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
            /* [retval][out] */ IWMEncWatermarkCollection **ppWatermarks);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWatermark )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
            /* [in] */ short iIndex,
            /* [out] */ VARIANT *pvarConfigFile,
            /* [out] */ VARIANT *pvarCLSID,
            /* [retval][out] */ BSTR *pbstrWatermarkName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWatermark )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrWaterMarkName,
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ BSTR bstrConfigFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Flush )( 
            IWMEncoder2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnableTimecode )( 
            IWMEncoder2 * This,
            /* [retval][out] */ VARIANT_BOOL *pfTimecode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnableTimecode )( 
            IWMEncoder2 * This,
            /* [in] */ VARIANT_BOOL fTimecode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreserveSourceTimecode )( 
            IWMEncoder2 * This,
            /* [retval][out] */ VARIANT_BOOL *pfSourceTimecode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PreserveSourceTimecode )( 
            IWMEncoder2 * This,
            /* [in] */ VARIANT_BOOL fSourceTimecode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartingTimecode )( 
            IWMEncoder2 * This,
            /* [retval][out] */ long *plTimecode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartingTimecode )( 
            IWMEncoder2 * This,
            /* [in] */ long lTimecode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimecodeFrameRate )( 
            IWMEncoder2 * This,
            /* [retval][out] */ long *plFrameRate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimecodeFrameRate )( 
            IWMEncoder2 * This,
            /* [in] */ long lFrameRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoComplexity )( 
            IWMEncoder2 * This,
            /* [retval][out] */ WMENC_VIDEOCOMPLEXITY *penumVideoComplexity);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoComplexity )( 
            IWMEncoder2 * This,
            /* [in] */ WMENC_VIDEOCOMPLEXITY enumVideoComplexity);
        
        END_INTERFACE
    } IWMEncoder2Vtbl;

    interface IWMEncoder2
    {
        CONST_VTBL struct IWMEncoder2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncoder2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncoder2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncoder2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncoder2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncoder2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncoder2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncoder2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncoder2_SetLocaleID(This,lLocaleID)	\
    (This)->lpVtbl -> SetLocaleID(This,lLocaleID)

#define IWMEncoder2_Load(This,bstrFileName)	\
    (This)->lpVtbl -> Load(This,bstrFileName)

#define IWMEncoder2_Save(This,bstrFileName)	\
    (This)->lpVtbl -> Save(This,bstrFileName)

#define IWMEncoder2_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IWMEncoder2_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWMEncoder2_get_AutoStop(This,pbStop)	\
    (This)->lpVtbl -> get_AutoStop(This,pbStop)

#define IWMEncoder2_put_AutoStop(This,bStop)	\
    (This)->lpVtbl -> put_AutoStop(This,bStop)

#define IWMEncoder2_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IWMEncoder2_PrepareToEncode(This,bPrepare)	\
    (This)->lpVtbl -> PrepareToEncode(This,bPrepare)

#define IWMEncoder2_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IWMEncoder2_Archive(This,enumArchiveType,enumArchiveOp)	\
    (This)->lpVtbl -> Archive(This,enumArchiveType,enumArchiveOp)

#define IWMEncoder2_SendScript(This,iIndex,bstrType,bstrData)	\
    (This)->lpVtbl -> SendScript(This,iIndex,bstrType,bstrData)

#define IWMEncoder2_get_EnableAutoArchive(This,pbEnableAutoArchive)	\
    (This)->lpVtbl -> get_EnableAutoArchive(This,pbEnableAutoArchive)

#define IWMEncoder2_put_EnableAutoArchive(This,bEnableAutoArchive)	\
    (This)->lpVtbl -> put_EnableAutoArchive(This,bEnableAutoArchive)

#define IWMEncoder2_get_RecordingLevel(This,iIndex,lLevel)	\
    (This)->lpVtbl -> get_RecordingLevel(This,iIndex,lLevel)

#define IWMEncoder2_put_RecordingLevel(This,iIndex,lLevel)	\
    (This)->lpVtbl -> put_RecordingLevel(This,iIndex,lLevel)

#define IWMEncoder2_get_RecordingMute(This,iIndex,pbRecordMute)	\
    (This)->lpVtbl -> get_RecordingMute(This,iIndex,pbRecordMute)

#define IWMEncoder2_put_RecordingMute(This,iIndex,bRecordMute)	\
    (This)->lpVtbl -> put_RecordingMute(This,iIndex,bRecordMute)

#define IWMEncoder2_GetAudioLevel(This,units,iIndex,plDuration,pdLMin,pdLAvg,pdLMax,pdRMin,pdRAvg,pdRMax)	\
    (This)->lpVtbl -> GetAudioLevel(This,units,iIndex,plDuration,pdLMin,pdLAvg,pdLMax,pdRMin,pdRAvg,pdRMax)

#define IWMEncoder2_get_SourceGroupCollection(This,ppSourceGroupCollection)	\
    (This)->lpVtbl -> get_SourceGroupCollection(This,ppSourceGroupCollection)

#define IWMEncoder2_get_SourcePluginInfoManager(This,ppSourcePluginInfoManager)	\
    (This)->lpVtbl -> get_SourcePluginInfoManager(This,ppSourcePluginInfoManager)

#define IWMEncoder2_get_TransformPluginInfoManager(This,ppTransformPluginInfoManager)	\
    (This)->lpVtbl -> get_TransformPluginInfoManager(This,ppTransformPluginInfoManager)

#define IWMEncoder2_get_DisplayInfo(This,ppDisplayInfo)	\
    (This)->lpVtbl -> get_DisplayInfo(This,ppDisplayInfo)

#define IWMEncoder2_get_Attributes(This,ppAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,ppAttributes)

#define IWMEncoder2_get_Broadcast(This,ppBroadcast)	\
    (This)->lpVtbl -> get_Broadcast(This,ppBroadcast)

#define IWMEncoder2_get_File(This,ppFile)	\
    (This)->lpVtbl -> get_File(This,ppFile)

#define IWMEncoder2_get_Statistics(This,ppStatistics)	\
    (This)->lpVtbl -> get_Statistics(This,ppStatistics)

#define IWMEncoder2_get_ProfileCollection(This,ppProfileCollection)	\
    (This)->lpVtbl -> get_ProfileCollection(This,ppProfileCollection)

#define IWMEncoder2_get_RunState(This,penumState)	\
    (This)->lpVtbl -> get_RunState(This,penumState)

#define IWMEncoder2_get_ErrorState(This,plResult)	\
    (This)->lpVtbl -> get_ErrorState(This,plResult)

#define IWMEncoder2_get_ArchiveState(This,enumType,penumArchiveState)	\
    (This)->lpVtbl -> get_ArchiveState(This,enumType,penumArchiveState)

#define IWMEncoder2_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IWMEncoder2_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IWMEncoder2_get_RemoteAdmin(This,pbRemoteAdmin)	\
    (This)->lpVtbl -> get_RemoteAdmin(This,pbRemoteAdmin)

#define IWMEncoder2_put_RemoteAdmin(This,bRemoteAdmin)	\
    (This)->lpVtbl -> put_RemoteAdmin(This,bRemoteAdmin)

#define IWMEncoder2_GenerateBroadcastInfo(This,bstrFileName)	\
    (This)->lpVtbl -> GenerateBroadcastInfo(This,bstrFileName)

#define IWMEncoder2_get_IndexerState(This,penumIndexerState)	\
    (This)->lpVtbl -> get_IndexerState(This,penumIndexerState)

#define IWMEncoder2_get_AutoIndex(This,pbAutoIndex)	\
    (This)->lpVtbl -> get_AutoIndex(This,pbAutoIndex)

#define IWMEncoder2_put_AutoIndex(This,bAutoIndex)	\
    (This)->lpVtbl -> put_AutoIndex(This,bAutoIndex)

#define IWMEncoder2_Indexer(This,enumIndexerOp)	\
    (This)->lpVtbl -> Indexer(This,enumIndexerOp)


#define IWMEncoder2_get_DeviceControlPluginInfoManager(This,ppDeviceControlPluginInfoManager)	\
    (This)->lpVtbl -> get_DeviceControlPluginInfoManager(This,ppDeviceControlPluginInfoManager)

#define IWMEncoder2_get_ContentAnalyzer(This,ppContentAnalyzer)	\
    (This)->lpVtbl -> get_ContentAnalyzer(This,ppContentAnalyzer)

#define IWMEncoder2_InsertCleanpoint(This)	\
    (This)->lpVtbl -> InsertCleanpoint(This)

#define IWMEncoder2_get_SynchronizeOperation(This,pbSyncOp)	\
    (This)->lpVtbl -> get_SynchronizeOperation(This,pbSyncOp)

#define IWMEncoder2_put_SynchronizeOperation(This,bSyncOp)	\
    (This)->lpVtbl -> put_SynchronizeOperation(This,bSyncOp)

#define IWMEncoder2_get_EncoderDRMContentAuthor(This,ppEncoderDRMAuthor)	\
    (This)->lpVtbl -> get_EncoderDRMContentAuthor(This,ppEncoderDRMAuthor)

#define IWMEncoder2_get_WatermarkCollection(This,enumSourceType,ppWatermarks)	\
    (This)->lpVtbl -> get_WatermarkCollection(This,enumSourceType,ppWatermarks)

#define IWMEncoder2_GetWatermark(This,enumSourceType,iIndex,pvarConfigFile,pvarCLSID,pbstrWatermarkName)	\
    (This)->lpVtbl -> GetWatermark(This,enumSourceType,iIndex,pvarConfigFile,pvarCLSID,pbstrWatermarkName)

#define IWMEncoder2_SetWatermark(This,enumSourceType,iIndex,bstrWaterMarkName,bstrCLSID,bstrConfigFile)	\
    (This)->lpVtbl -> SetWatermark(This,enumSourceType,iIndex,bstrWaterMarkName,bstrCLSID,bstrConfigFile)

#define IWMEncoder2_Flush(This)	\
    (This)->lpVtbl -> Flush(This)

#define IWMEncoder2_get_EnableTimecode(This,pfTimecode)	\
    (This)->lpVtbl -> get_EnableTimecode(This,pfTimecode)

#define IWMEncoder2_put_EnableTimecode(This,fTimecode)	\
    (This)->lpVtbl -> put_EnableTimecode(This,fTimecode)

#define IWMEncoder2_get_PreserveSourceTimecode(This,pfSourceTimecode)	\
    (This)->lpVtbl -> get_PreserveSourceTimecode(This,pfSourceTimecode)

#define IWMEncoder2_put_PreserveSourceTimecode(This,fSourceTimecode)	\
    (This)->lpVtbl -> put_PreserveSourceTimecode(This,fSourceTimecode)

#define IWMEncoder2_get_StartingTimecode(This,plTimecode)	\
    (This)->lpVtbl -> get_StartingTimecode(This,plTimecode)

#define IWMEncoder2_put_StartingTimecode(This,lTimecode)	\
    (This)->lpVtbl -> put_StartingTimecode(This,lTimecode)

#define IWMEncoder2_get_TimecodeFrameRate(This,plFrameRate)	\
    (This)->lpVtbl -> get_TimecodeFrameRate(This,plFrameRate)

#define IWMEncoder2_put_TimecodeFrameRate(This,lFrameRate)	\
    (This)->lpVtbl -> put_TimecodeFrameRate(This,lFrameRate)

#define IWMEncoder2_get_VideoComplexity(This,penumVideoComplexity)	\
    (This)->lpVtbl -> get_VideoComplexity(This,penumVideoComplexity)

#define IWMEncoder2_put_VideoComplexity(This,enumVideoComplexity)	\
    (This)->lpVtbl -> put_VideoComplexity(This,enumVideoComplexity)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_DeviceControlPluginInfoManager_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ IWMEncDeviceControlPluginInfoManager **ppDeviceControlPluginInfoManager);


void __RPC_STUB IWMEncoder2_get_DeviceControlPluginInfoManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_ContentAnalyzer_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ IWMEncContentAnalyzer **ppContentAnalyzer);


void __RPC_STUB IWMEncoder2_get_ContentAnalyzer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_InsertCleanpoint_Proxy( 
    IWMEncoder2 * This);


void __RPC_STUB IWMEncoder2_InsertCleanpoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_SynchronizeOperation_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ VARIANT_BOOL *pbSyncOp);


void __RPC_STUB IWMEncoder2_get_SynchronizeOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_put_SynchronizeOperation_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ VARIANT_BOOL bSyncOp);


void __RPC_STUB IWMEncoder2_put_SynchronizeOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_EncoderDRMContentAuthor_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ IWMDRMContentAuthor **ppEncoderDRMAuthor);


void __RPC_STUB IWMEncoder2_get_EncoderDRMContentAuthor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_WatermarkCollection_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
    /* [retval][out] */ IWMEncWatermarkCollection **ppWatermarks);


void __RPC_STUB IWMEncoder2_get_WatermarkCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_GetWatermark_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
    /* [in] */ short iIndex,
    /* [out] */ VARIANT *pvarConfigFile,
    /* [out] */ VARIANT *pvarCLSID,
    /* [retval][out] */ BSTR *pbstrWatermarkName);


void __RPC_STUB IWMEncoder2_GetWatermark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_SetWatermark_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSourceType,
    /* [in] */ short iIndex,
    /* [in] */ BSTR bstrWaterMarkName,
    /* [in] */ BSTR bstrCLSID,
    /* [in] */ BSTR bstrConfigFile);


void __RPC_STUB IWMEncoder2_SetWatermark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_Flush_Proxy( 
    IWMEncoder2 * This);


void __RPC_STUB IWMEncoder2_Flush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_EnableTimecode_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ VARIANT_BOOL *pfTimecode);


void __RPC_STUB IWMEncoder2_get_EnableTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_put_EnableTimecode_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ VARIANT_BOOL fTimecode);


void __RPC_STUB IWMEncoder2_put_EnableTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_PreserveSourceTimecode_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ VARIANT_BOOL *pfSourceTimecode);


void __RPC_STUB IWMEncoder2_get_PreserveSourceTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_put_PreserveSourceTimecode_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ VARIANT_BOOL fSourceTimecode);


void __RPC_STUB IWMEncoder2_put_PreserveSourceTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_StartingTimecode_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ long *plTimecode);


void __RPC_STUB IWMEncoder2_get_StartingTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_put_StartingTimecode_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ long lTimecode);


void __RPC_STUB IWMEncoder2_put_StartingTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_TimecodeFrameRate_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ long *plFrameRate);


void __RPC_STUB IWMEncoder2_get_TimecodeFrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_put_TimecodeFrameRate_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ long lFrameRate);


void __RPC_STUB IWMEncoder2_put_TimecodeFrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_get_VideoComplexity_Proxy( 
    IWMEncoder2 * This,
    /* [retval][out] */ WMENC_VIDEOCOMPLEXITY *penumVideoComplexity);


void __RPC_STUB IWMEncoder2_get_VideoComplexity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoder2_put_VideoComplexity_Proxy( 
    IWMEncoder2 * This,
    /* [in] */ WMENC_VIDEOCOMPLEXITY enumVideoComplexity);


void __RPC_STUB IWMEncoder2_put_VideoComplexity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncoder2_INTERFACE_DEFINED__ */


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
            /* [retval][out] */ BSTR *bstrDetailsString) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileDirectory( 
            /* [retval][out] */ BSTR *bstrDirectory) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileDirectory( 
            /* [in] */ BSTR bstrDirectory) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastCreatedProfile( 
            /* [retval][out] */ BSTR *bstrProfile) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastEditedProfile( 
            /* [retval][out] */ BSTR *bstrProfile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncProfileManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncProfileManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncProfileManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncProfileManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncProfileManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncProfileManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncProfileManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncProfileManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WMEncProfileList )( 
            IWMEncProfileManager * This,
            /* [in] */ WMENC_MEDIA_FILTER filter,
            /* [in] */ long lcid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WMEncProfileListEx )( 
            IWMEncProfileManager * This,
            /* [in] */ WMENC_MEDIA_FILTER filter,
            /* [in] */ WMENC_MEDIA_FILTER newDefault,
            /* [in] */ long lcid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WMEncProfileEdit )( 
            IWMEncProfileManager * This,
            /* [in] */ BSTR bstrProfileName,
            /* [in] */ WMENC_MEDIA_FILTER lfilter,
            /* [in] */ long lcid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDetailsString )( 
            IWMEncProfileManager * This,
            /* [in] */ BSTR bstrProfileName,
            /* [in] */ long lcid,
            /* [retval][out] */ BSTR *bstrDetailsString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileDirectory )( 
            IWMEncProfileManager * This,
            /* [retval][out] */ BSTR *bstrDirectory);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProfileDirectory )( 
            IWMEncProfileManager * This,
            /* [in] */ BSTR bstrDirectory);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastCreatedProfile )( 
            IWMEncProfileManager * This,
            /* [retval][out] */ BSTR *bstrProfile);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastEditedProfile )( 
            IWMEncProfileManager * This,
            /* [retval][out] */ BSTR *bstrProfile);
        
        END_INTERFACE
    } IWMEncProfileManagerVtbl;

    interface IWMEncProfileManager
    {
        CONST_VTBL struct IWMEncProfileManagerVtbl *lpVtbl;
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
    IWMEncProfileManager * This,
    /* [in] */ WMENC_MEDIA_FILTER filter,
    /* [in] */ long lcid);


void __RPC_STUB IWMEncProfileManager_WMEncProfileList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_WMEncProfileListEx_Proxy( 
    IWMEncProfileManager * This,
    /* [in] */ WMENC_MEDIA_FILTER filter,
    /* [in] */ WMENC_MEDIA_FILTER newDefault,
    /* [in] */ long lcid);


void __RPC_STUB IWMEncProfileManager_WMEncProfileListEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_WMEncProfileEdit_Proxy( 
    IWMEncProfileManager * This,
    /* [in] */ BSTR bstrProfileName,
    /* [in] */ WMENC_MEDIA_FILTER lfilter,
    /* [in] */ long lcid);


void __RPC_STUB IWMEncProfileManager_WMEncProfileEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_GetDetailsString_Proxy( 
    IWMEncProfileManager * This,
    /* [in] */ BSTR bstrProfileName,
    /* [in] */ long lcid,
    /* [retval][out] */ BSTR *bstrDetailsString);


void __RPC_STUB IWMEncProfileManager_GetDetailsString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_get_ProfileDirectory_Proxy( 
    IWMEncProfileManager * This,
    /* [retval][out] */ BSTR *bstrDirectory);


void __RPC_STUB IWMEncProfileManager_get_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_put_ProfileDirectory_Proxy( 
    IWMEncProfileManager * This,
    /* [in] */ BSTR bstrDirectory);


void __RPC_STUB IWMEncProfileManager_put_ProfileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_get_LastCreatedProfile_Proxy( 
    IWMEncProfileManager * This,
    /* [retval][out] */ BSTR *bstrProfile);


void __RPC_STUB IWMEncProfileManager_get_LastCreatedProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfileManager_get_LastEditedProfile_Proxy( 
    IWMEncProfileManager * This,
    /* [retval][out] */ BSTR *bstrProfile);


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
            /* [retval][out] */ IWMEncoder **ppEncoder) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UILock( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UILock( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayWidth( 
            /* [in] */ short iIndex,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayHeight( 
            /* [in] */ short iIndex,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ WMENCAPP_PROP_CLASS enumClass,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pValue) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncoderApp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncoderApp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncoderApp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncoderApp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncoderApp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncoderApp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncoderApp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Encoder )( 
            IWMEncoderApp * This,
            /* [retval][out] */ IWMEncoder **ppEncoder);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IWMEncoderApp * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IWMEncoderApp * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Top )( 
            IWMEncoderApp * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Top )( 
            IWMEncoderApp * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Left )( 
            IWMEncoderApp * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Left )( 
            IWMEncoderApp * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IWMEncoderApp * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IWMEncoderApp * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IWMEncoderApp * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IWMEncoderApp * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UILock )( 
            IWMEncoderApp * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UILock )( 
            IWMEncoderApp * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayWidth )( 
            IWMEncoderApp * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayHeight )( 
            IWMEncoderApp * This,
            /* [in] */ short iIndex,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetProperty )( 
            IWMEncoderApp * This,
            /* [in] */ WMENCAPP_PROP_CLASS enumClass,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetProperty )( 
            IWMEncoderApp * This,
            /* [in] */ WMENCAPP_PROP_CLASS enumClass,
            /* [in] */ BSTR bstrProperty,
            /* [in] */ VARIANT Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveProperties )( 
            IWMEncoderApp * This,
            /* [in] */ WMENCAPP_PROP_CLASS enumClass);
        
        END_INTERFACE
    } IWMEncoderAppVtbl;

    interface IWMEncoderApp
    {
        CONST_VTBL struct IWMEncoderAppVtbl *lpVtbl;
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
    IWMEncoderApp * This,
    /* [retval][out] */ IWMEncoder **ppEncoder);


void __RPC_STUB IWMEncoderApp_get_Encoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Visible_Proxy( 
    IWMEncoderApp * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IWMEncoderApp_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Visible_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWMEncoderApp_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Top_Proxy( 
    IWMEncoderApp * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMEncoderApp_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Top_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Left_Proxy( 
    IWMEncoderApp * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMEncoderApp_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Left_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Width_Proxy( 
    IWMEncoderApp * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMEncoderApp_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Width_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_Height_Proxy( 
    IWMEncoderApp * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMEncoderApp_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_Height_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMEncoderApp_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_UILock_Proxy( 
    IWMEncoderApp * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IWMEncoderApp_get_UILock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_put_UILock_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWMEncoderApp_put_UILock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_DisplayWidth_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMEncoderApp_get_DisplayWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_get_DisplayHeight_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ short iIndex,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMEncoderApp_get_DisplayHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_GetProperty_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ WMENCAPP_PROP_CLASS enumClass,
    /* [in] */ BSTR bstrProperty,
    /* [retval][out] */ VARIANT *pValue);


void __RPC_STUB IWMEncoderApp_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_SetProperty_Proxy( 
    IWMEncoderApp * This,
    /* [in] */ WMENCAPP_PROP_CLASS enumClass,
    /* [in] */ BSTR bstrProperty,
    /* [in] */ VARIANT Value);


void __RPC_STUB IWMEncoderApp_SetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncoderApp_SaveProperties_Proxy( 
    IWMEncoderApp * This,
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
            /* [retval][out] */ WMENC_LONGLONG *pqwSampleCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ByteCount( 
            /* [retval][out] */ WMENC_LONGLONG *pqwByteCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DroppedSampleCount( 
            /* [retval][out] */ WMENC_LONGLONG *pqwDroppedSampleCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DroppedByteCount( 
            /* [retval][out] */ WMENC_LONGLONG *pqwDroppedByteCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentBitrate( 
            /* [retval][out] */ long *plCurrentBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AverageBitrate( 
            /* [retval][out] */ long *plAverageBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpectedBitrate( 
            /* [retval][out] */ long *plExpectedBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentSampleRate( 
            /* [retval][out] */ long *plCurrentSampleRate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AverageSampleRate( 
            /* [retval][out] */ long *plAverageSampleRate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpectedSampleRate( 
            /* [retval][out] */ long *plExpectedSampleRate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncOutputStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncOutputStats * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncOutputStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncOutputStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncOutputStats * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncOutputStats * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncOutputStats * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncOutputStats * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SampleCount )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwSampleCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ByteCount )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwByteCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DroppedSampleCount )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwDroppedSampleCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DroppedByteCount )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwDroppedByteCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentBitrate )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ long *plCurrentBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AverageBitrate )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ long *plAverageBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpectedBitrate )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ long *plExpectedBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentSampleRate )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ long *plCurrentSampleRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AverageSampleRate )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ long *plAverageSampleRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpectedSampleRate )( 
            IWMEncOutputStats * This,
            /* [retval][out] */ long *plExpectedSampleRate);
        
        END_INTERFACE
    } IWMEncOutputStatsVtbl;

    interface IWMEncOutputStats
    {
        CONST_VTBL struct IWMEncOutputStatsVtbl *lpVtbl;
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
    IWMEncOutputStats * This,
    /* [retval][out] */ WMENC_LONGLONG *pqwSampleCount);


void __RPC_STUB IWMEncOutputStats_get_SampleCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_ByteCount_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ WMENC_LONGLONG *pqwByteCount);


void __RPC_STUB IWMEncOutputStats_get_ByteCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_DroppedSampleCount_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ WMENC_LONGLONG *pqwDroppedSampleCount);


void __RPC_STUB IWMEncOutputStats_get_DroppedSampleCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_DroppedByteCount_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ WMENC_LONGLONG *pqwDroppedByteCount);


void __RPC_STUB IWMEncOutputStats_get_DroppedByteCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_CurrentBitrate_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ long *plCurrentBitrate);


void __RPC_STUB IWMEncOutputStats_get_CurrentBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_AverageBitrate_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ long *plAverageBitrate);


void __RPC_STUB IWMEncOutputStats_get_AverageBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_ExpectedBitrate_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ long *plExpectedBitrate);


void __RPC_STUB IWMEncOutputStats_get_ExpectedBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_CurrentSampleRate_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ long *plCurrentSampleRate);


void __RPC_STUB IWMEncOutputStats_get_CurrentSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_AverageSampleRate_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ long *plAverageSampleRate);


void __RPC_STUB IWMEncOutputStats_get_AverageSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats_get_ExpectedSampleRate_Proxy( 
    IWMEncOutputStats * This,
    /* [retval][out] */ long *plExpectedSampleRate);


void __RPC_STUB IWMEncOutputStats_get_ExpectedSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncOutputStats_INTERFACE_DEFINED__ */


#ifndef __IWMEncOutputStats2_INTERFACE_DEFINED__
#define __IWMEncOutputStats2_INTERFACE_DEFINED__

/* interface IWMEncOutputStats2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncOutputStats2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("18DB3000-FFEA-4363-80C5-818AF417BC84")
    IWMEncOutputStats2 : public IWMEncOutputStats
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Property( 
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncOutputStats2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncOutputStats2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncOutputStats2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncOutputStats2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncOutputStats2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncOutputStats2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncOutputStats2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncOutputStats2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SampleCount )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwSampleCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ByteCount )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwByteCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DroppedSampleCount )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwDroppedSampleCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DroppedByteCount )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwDroppedByteCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentBitrate )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ long *plCurrentBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AverageBitrate )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ long *plAverageBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpectedBitrate )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ long *plExpectedBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentSampleRate )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ long *plCurrentSampleRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AverageSampleRate )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ long *plAverageSampleRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpectedSampleRate )( 
            IWMEncOutputStats2 * This,
            /* [retval][out] */ long *plExpectedSampleRate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Property )( 
            IWMEncOutputStats2 * This,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvValue);
        
        END_INTERFACE
    } IWMEncOutputStats2Vtbl;

    interface IWMEncOutputStats2
    {
        CONST_VTBL struct IWMEncOutputStats2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncOutputStats2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncOutputStats2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncOutputStats2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncOutputStats2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncOutputStats2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncOutputStats2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncOutputStats2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncOutputStats2_get_SampleCount(This,pqwSampleCount)	\
    (This)->lpVtbl -> get_SampleCount(This,pqwSampleCount)

#define IWMEncOutputStats2_get_ByteCount(This,pqwByteCount)	\
    (This)->lpVtbl -> get_ByteCount(This,pqwByteCount)

#define IWMEncOutputStats2_get_DroppedSampleCount(This,pqwDroppedSampleCount)	\
    (This)->lpVtbl -> get_DroppedSampleCount(This,pqwDroppedSampleCount)

#define IWMEncOutputStats2_get_DroppedByteCount(This,pqwDroppedByteCount)	\
    (This)->lpVtbl -> get_DroppedByteCount(This,pqwDroppedByteCount)

#define IWMEncOutputStats2_get_CurrentBitrate(This,plCurrentBitrate)	\
    (This)->lpVtbl -> get_CurrentBitrate(This,plCurrentBitrate)

#define IWMEncOutputStats2_get_AverageBitrate(This,plAverageBitrate)	\
    (This)->lpVtbl -> get_AverageBitrate(This,plAverageBitrate)

#define IWMEncOutputStats2_get_ExpectedBitrate(This,plExpectedBitrate)	\
    (This)->lpVtbl -> get_ExpectedBitrate(This,plExpectedBitrate)

#define IWMEncOutputStats2_get_CurrentSampleRate(This,plCurrentSampleRate)	\
    (This)->lpVtbl -> get_CurrentSampleRate(This,plCurrentSampleRate)

#define IWMEncOutputStats2_get_AverageSampleRate(This,plAverageSampleRate)	\
    (This)->lpVtbl -> get_AverageSampleRate(This,plAverageSampleRate)

#define IWMEncOutputStats2_get_ExpectedSampleRate(This,plExpectedSampleRate)	\
    (This)->lpVtbl -> get_ExpectedSampleRate(This,plExpectedSampleRate)


#define IWMEncOutputStats2_get_Property(This,bstrProperty,pvValue)	\
    (This)->lpVtbl -> get_Property(This,bstrProperty,pvValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncOutputStats2_get_Property_Proxy( 
    IWMEncOutputStats2 * This,
    /* [in] */ BSTR bstrProperty,
    /* [retval][out] */ VARIANT *pvValue);


void __RPC_STUB IWMEncOutputStats2_get_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncOutputStats2_INTERFACE_DEFINED__ */


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
            /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDuration( 
            /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncFileArchiveStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncFileArchiveStats * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncFileArchiveStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncFileArchiveStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncFileArchiveStats * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncFileArchiveStats * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncFileArchiveStats * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncFileArchiveStats * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileSize )( 
            IWMEncFileArchiveStats * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDuration )( 
            IWMEncFileArchiveStats * This,
            /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileDuration);
        
        END_INTERFACE
    } IWMEncFileArchiveStatsVtbl;

    interface IWMEncFileArchiveStats
    {
        CONST_VTBL struct IWMEncFileArchiveStatsVtbl *lpVtbl;
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
    IWMEncFileArchiveStats * This,
    /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileSize);


void __RPC_STUB IWMEncFileArchiveStats_get_FileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileArchiveStats_get_FileDuration_Proxy( 
    IWMEncFileArchiveStats * This,
    /* [retval][out] */ WMENC_LONGLONG *pqwOutputFileDuration);


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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PercentComplete( 
            /* [retval][out] */ long *plPercent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncIndexerStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncIndexerStats * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncIndexerStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncIndexerStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncIndexerStats * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncIndexerStats * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncIndexerStats * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncIndexerStats * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileCount )( 
            IWMEncIndexerStats * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileName )( 
            IWMEncIndexerStats * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ BSTR *pbstrFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PercentComplete )( 
            IWMEncIndexerStats * This,
            /* [retval][out] */ long *plPercent);
        
        END_INTERFACE
    } IWMEncIndexerStatsVtbl;

    interface IWMEncIndexerStats
    {
        CONST_VTBL struct IWMEncIndexerStatsVtbl *lpVtbl;
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
    IWMEncIndexerStats * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncIndexerStats_get_FileCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncIndexerStats_get_FileName_Proxy( 
    IWMEncIndexerStats * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ BSTR *pbstrFileName);


void __RPC_STUB IWMEncIndexerStats_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncIndexerStats_get_PercentComplete_Proxy( 
    IWMEncIndexerStats * This,
    /* [retval][out] */ long *plPercent);


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
            /* [retval][out] */ WMENC_LONGLONG *plTime) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WMFOutputStats( 
            /* [retval][out] */ IDispatch **ppStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamOutputStats( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [in] */ short iStreamIndex,
            /* [retval][out] */ IDispatch **pStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NetConnectionStats( 
            /* [retval][out] */ IDispatch **ppDispNetConnectionStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileArchiveStats( 
            /* [retval][out] */ IDispatch **ppFileArchiveStats) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamOutputCount( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [retval][out] */ short *pStreamOutputCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexerStats( 
            /* [retval][out] */ IDispatch **ppIndexerStats) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncStatisticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncStatistics * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncStatistics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncStatistics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncStatistics * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncStatistics * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncStatistics * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncStatistics * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EncodingTime )( 
            IWMEncStatistics * This,
            /* [retval][out] */ WMENC_LONGLONG *plTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WMFOutputStats )( 
            IWMEncStatistics * This,
            /* [retval][out] */ IDispatch **ppStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamOutputStats )( 
            IWMEncStatistics * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [in] */ short iStreamIndex,
            /* [retval][out] */ IDispatch **pStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetConnectionStats )( 
            IWMEncStatistics * This,
            /* [retval][out] */ IDispatch **ppDispNetConnectionStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileArchiveStats )( 
            IWMEncStatistics * This,
            /* [retval][out] */ IDispatch **ppFileArchiveStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamOutputCount )( 
            IWMEncStatistics * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [retval][out] */ short *pStreamOutputCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexerStats )( 
            IWMEncStatistics * This,
            /* [retval][out] */ IDispatch **ppIndexerStats);
        
        END_INTERFACE
    } IWMEncStatisticsVtbl;

    interface IWMEncStatistics
    {
        CONST_VTBL struct IWMEncStatisticsVtbl *lpVtbl;
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
    IWMEncStatistics * This,
    /* [retval][out] */ WMENC_LONGLONG *plTime);


void __RPC_STUB IWMEncStatistics_get_EncodingTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_WMFOutputStats_Proxy( 
    IWMEncStatistics * This,
    /* [retval][out] */ IDispatch **ppStats);


void __RPC_STUB IWMEncStatistics_get_WMFOutputStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_StreamOutputStats_Proxy( 
    IWMEncStatistics * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ short iMediaIndex,
    /* [in] */ short iStreamIndex,
    /* [retval][out] */ IDispatch **pStats);


void __RPC_STUB IWMEncStatistics_get_StreamOutputStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_NetConnectionStats_Proxy( 
    IWMEncStatistics * This,
    /* [retval][out] */ IDispatch **ppDispNetConnectionStats);


void __RPC_STUB IWMEncStatistics_get_NetConnectionStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_FileArchiveStats_Proxy( 
    IWMEncStatistics * This,
    /* [retval][out] */ IDispatch **ppFileArchiveStats);


void __RPC_STUB IWMEncStatistics_get_FileArchiveStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_StreamOutputCount_Proxy( 
    IWMEncStatistics * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ short iMediaIndex,
    /* [retval][out] */ short *pStreamOutputCount);


void __RPC_STUB IWMEncStatistics_get_StreamOutputCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics_get_IndexerStats_Proxy( 
    IWMEncStatistics * This,
    /* [retval][out] */ IDispatch **ppIndexerStats);


void __RPC_STUB IWMEncStatistics_get_IndexerStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncStatistics_INTERFACE_DEFINED__ */


#ifndef __IWMEncStatistics2_INTERFACE_DEFINED__
#define __IWMEncStatistics2_INTERFACE_DEFINED__

/* interface IWMEncStatistics2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncStatistics2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C694BEE-BA71-4967-88EA-43F8C27ED918")
    IWMEncStatistics2 : public IWMEncStatistics
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PushDistributionStats( 
            /* [retval][out] */ IDispatch **ppDispPushDistributionStats) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncStatistics2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncStatistics2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncStatistics2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncStatistics2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncStatistics2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncStatistics2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncStatistics2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncStatistics2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EncodingTime )( 
            IWMEncStatistics2 * This,
            /* [retval][out] */ WMENC_LONGLONG *plTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WMFOutputStats )( 
            IWMEncStatistics2 * This,
            /* [retval][out] */ IDispatch **ppStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamOutputStats )( 
            IWMEncStatistics2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [in] */ short iStreamIndex,
            /* [retval][out] */ IDispatch **pStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetConnectionStats )( 
            IWMEncStatistics2 * This,
            /* [retval][out] */ IDispatch **ppDispNetConnectionStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileArchiveStats )( 
            IWMEncStatistics2 * This,
            /* [retval][out] */ IDispatch **ppFileArchiveStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamOutputCount )( 
            IWMEncStatistics2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iMediaIndex,
            /* [retval][out] */ short *pStreamOutputCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IndexerStats )( 
            IWMEncStatistics2 * This,
            /* [retval][out] */ IDispatch **ppIndexerStats);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PushDistributionStats )( 
            IWMEncStatistics2 * This,
            /* [retval][out] */ IDispatch **ppDispPushDistributionStats);
        
        END_INTERFACE
    } IWMEncStatistics2Vtbl;

    interface IWMEncStatistics2
    {
        CONST_VTBL struct IWMEncStatistics2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncStatistics2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncStatistics2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncStatistics2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncStatistics2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncStatistics2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncStatistics2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncStatistics2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncStatistics2_get_EncodingTime(This,plTime)	\
    (This)->lpVtbl -> get_EncodingTime(This,plTime)

#define IWMEncStatistics2_get_WMFOutputStats(This,ppStats)	\
    (This)->lpVtbl -> get_WMFOutputStats(This,ppStats)

#define IWMEncStatistics2_get_StreamOutputStats(This,enumType,iMediaIndex,iStreamIndex,pStats)	\
    (This)->lpVtbl -> get_StreamOutputStats(This,enumType,iMediaIndex,iStreamIndex,pStats)

#define IWMEncStatistics2_get_NetConnectionStats(This,ppDispNetConnectionStats)	\
    (This)->lpVtbl -> get_NetConnectionStats(This,ppDispNetConnectionStats)

#define IWMEncStatistics2_get_FileArchiveStats(This,ppFileArchiveStats)	\
    (This)->lpVtbl -> get_FileArchiveStats(This,ppFileArchiveStats)

#define IWMEncStatistics2_get_StreamOutputCount(This,enumType,iMediaIndex,pStreamOutputCount)	\
    (This)->lpVtbl -> get_StreamOutputCount(This,enumType,iMediaIndex,pStreamOutputCount)

#define IWMEncStatistics2_get_IndexerStats(This,ppIndexerStats)	\
    (This)->lpVtbl -> get_IndexerStats(This,ppIndexerStats)


#define IWMEncStatistics2_get_PushDistributionStats(This,ppDispPushDistributionStats)	\
    (This)->lpVtbl -> get_PushDistributionStats(This,ppDispPushDistributionStats)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStatistics2_get_PushDistributionStats_Proxy( 
    IWMEncStatistics2 * This,
    /* [retval][out] */ IDispatch **ppDispPushDistributionStats);


void __RPC_STUB IWMEncStatistics2_get_PushDistributionStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncStatistics2_INTERFACE_DEFINED__ */


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
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientInfo( 
            /* [in] */ long lIndex,
            /* [out] */ WMENC_BROADCAST_PROTOCOL *pProtocol,
            /* [retval][out] */ BSTR *pbstrIP) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncNetConnectionStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncNetConnectionStats * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncNetConnectionStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncNetConnectionStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncNetConnectionStats * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncNetConnectionStats * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncNetConnectionStats * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncNetConnectionStats * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientCount )( 
            IWMEncNetConnectionStats * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientInfo )( 
            IWMEncNetConnectionStats * This,
            /* [in] */ long lIndex,
            /* [out] */ WMENC_BROADCAST_PROTOCOL *pProtocol,
            /* [retval][out] */ BSTR *pbstrIP);
        
        END_INTERFACE
    } IWMEncNetConnectionStatsVtbl;

    interface IWMEncNetConnectionStats
    {
        CONST_VTBL struct IWMEncNetConnectionStatsVtbl *lpVtbl;
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

#define IWMEncNetConnectionStats_get_ClientInfo(This,lIndex,pProtocol,pbstrIP)	\
    (This)->lpVtbl -> get_ClientInfo(This,lIndex,pProtocol,pbstrIP)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncNetConnectionStats_get_ClientCount_Proxy( 
    IWMEncNetConnectionStats * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncNetConnectionStats_get_ClientCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncNetConnectionStats_get_ClientInfo_Proxy( 
    IWMEncNetConnectionStats * This,
    /* [in] */ long lIndex,
    /* [out] */ WMENC_BROADCAST_PROTOCOL *pProtocol,
    /* [retval][out] */ BSTR *pbstrIP);


void __RPC_STUB IWMEncNetConnectionStats_get_ClientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncNetConnectionStats_INTERFACE_DEFINED__ */


#ifndef __IWMEncNetConnectionStats2_INTERFACE_DEFINED__
#define __IWMEncNetConnectionStats2_INTERFACE_DEFINED__

/* interface IWMEncNetConnectionStats2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncNetConnectionStats2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52350A39-5581-4b7b-A65A-F37848F2C0F6")
    IWMEncNetConnectionStats2 : public IWMEncNetConnectionStats
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostURL( 
            /* [retval][out] */ BSTR *pbstrHostURL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncNetConnectionStats2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncNetConnectionStats2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncNetConnectionStats2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncNetConnectionStats2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncNetConnectionStats2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncNetConnectionStats2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncNetConnectionStats2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncNetConnectionStats2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientCount )( 
            IWMEncNetConnectionStats2 * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientInfo )( 
            IWMEncNetConnectionStats2 * This,
            /* [in] */ long lIndex,
            /* [out] */ WMENC_BROADCAST_PROTOCOL *pProtocol,
            /* [retval][out] */ BSTR *pbstrIP);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HostURL )( 
            IWMEncNetConnectionStats2 * This,
            /* [retval][out] */ BSTR *pbstrHostURL);
        
        END_INTERFACE
    } IWMEncNetConnectionStats2Vtbl;

    interface IWMEncNetConnectionStats2
    {
        CONST_VTBL struct IWMEncNetConnectionStats2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncNetConnectionStats2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncNetConnectionStats2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncNetConnectionStats2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncNetConnectionStats2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncNetConnectionStats2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncNetConnectionStats2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncNetConnectionStats2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncNetConnectionStats2_get_ClientCount(This,plCount)	\
    (This)->lpVtbl -> get_ClientCount(This,plCount)

#define IWMEncNetConnectionStats2_get_ClientInfo(This,lIndex,pProtocol,pbstrIP)	\
    (This)->lpVtbl -> get_ClientInfo(This,lIndex,pProtocol,pbstrIP)


#define IWMEncNetConnectionStats2_get_HostURL(This,pbstrHostURL)	\
    (This)->lpVtbl -> get_HostURL(This,pbstrHostURL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncNetConnectionStats2_get_HostURL_Proxy( 
    IWMEncNetConnectionStats2 * This,
    /* [retval][out] */ BSTR *pbstrHostURL);


void __RPC_STUB IWMEncNetConnectionStats2_get_HostURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncNetConnectionStats2_INTERFACE_DEFINED__ */


#ifndef __IWMEncPushDistribution_INTERFACE_DEFINED__
#define __IWMEncPushDistribution_INTERFACE_DEFINED__

/* interface IWMEncPushDistribution */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncPushDistribution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10CBC166-7F83-451e-90A1-75F43E2C20A0")
    IWMEncPushDistribution : public IWMEncBroadcast
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerName( 
            /* [retval][out] */ BSTR *pbstrServerName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServerName( 
            /* [in] */ BSTR bstrServerName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PublishingPoint( 
            /* [retval][out] */ BSTR *pbstrPublishingPoint) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PublishingPoint( 
            /* [in] */ BSTR bstrPublishingPoint) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Template( 
            /* [retval][out] */ BSTR *pbstrTemplate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Template( 
            /* [in] */ BSTR bstrTemplate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoRemovePublishingPoint( 
            /* [retval][out] */ VARIANT_BOOL *pbAutoRemove) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoRemovePublishingPoint( 
            /* [in] */ VARIANT_BOOL bAutoRemove) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateMulticastInfoFile( 
            /* [in] */ BSTR bstrNSCFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateAnnouncementFile( 
            /* [in] */ BSTR bstrNSCURL,
            /* [in] */ BSTR bstrASXFileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPushDistributionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncPushDistribution * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncPushDistribution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncPushDistribution * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncPushDistribution * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncPushDistribution * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncPushDistribution * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncPushDistribution * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PortNumber )( 
            IWMEncPushDistribution * This,
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [retval][out] */ long *piPort);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PortNumber )( 
            IWMEncPushDistribution * This,
            /* [in] */ WMENC_BROADCAST_PROTOCOL enumProtocol,
            /* [in] */ long iPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerName )( 
            IWMEncPushDistribution * This,
            /* [retval][out] */ BSTR *pbstrServerName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServerName )( 
            IWMEncPushDistribution * This,
            /* [in] */ BSTR bstrServerName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PublishingPoint )( 
            IWMEncPushDistribution * This,
            /* [retval][out] */ BSTR *pbstrPublishingPoint);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PublishingPoint )( 
            IWMEncPushDistribution * This,
            /* [in] */ BSTR bstrPublishingPoint);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Template )( 
            IWMEncPushDistribution * This,
            /* [retval][out] */ BSTR *pbstrTemplate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Template )( 
            IWMEncPushDistribution * This,
            /* [in] */ BSTR bstrTemplate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoRemovePublishingPoint )( 
            IWMEncPushDistribution * This,
            /* [retval][out] */ VARIANT_BOOL *pbAutoRemove);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoRemovePublishingPoint )( 
            IWMEncPushDistribution * This,
            /* [in] */ VARIANT_BOOL bAutoRemove);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateMulticastInfoFile )( 
            IWMEncPushDistribution * This,
            /* [in] */ BSTR bstrNSCFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateAnnouncementFile )( 
            IWMEncPushDistribution * This,
            /* [in] */ BSTR bstrNSCURL,
            /* [in] */ BSTR bstrASXFileName);
        
        END_INTERFACE
    } IWMEncPushDistributionVtbl;

    interface IWMEncPushDistribution
    {
        CONST_VTBL struct IWMEncPushDistributionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncPushDistribution_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncPushDistribution_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncPushDistribution_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncPushDistribution_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncPushDistribution_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncPushDistribution_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncPushDistribution_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncPushDistribution_get_PortNumber(This,enumProtocol,piPort)	\
    (This)->lpVtbl -> get_PortNumber(This,enumProtocol,piPort)

#define IWMEncPushDistribution_put_PortNumber(This,enumProtocol,iPort)	\
    (This)->lpVtbl -> put_PortNumber(This,enumProtocol,iPort)


#define IWMEncPushDistribution_get_ServerName(This,pbstrServerName)	\
    (This)->lpVtbl -> get_ServerName(This,pbstrServerName)

#define IWMEncPushDistribution_put_ServerName(This,bstrServerName)	\
    (This)->lpVtbl -> put_ServerName(This,bstrServerName)

#define IWMEncPushDistribution_get_PublishingPoint(This,pbstrPublishingPoint)	\
    (This)->lpVtbl -> get_PublishingPoint(This,pbstrPublishingPoint)

#define IWMEncPushDistribution_put_PublishingPoint(This,bstrPublishingPoint)	\
    (This)->lpVtbl -> put_PublishingPoint(This,bstrPublishingPoint)

#define IWMEncPushDistribution_get_Template(This,pbstrTemplate)	\
    (This)->lpVtbl -> get_Template(This,pbstrTemplate)

#define IWMEncPushDistribution_put_Template(This,bstrTemplate)	\
    (This)->lpVtbl -> put_Template(This,bstrTemplate)

#define IWMEncPushDistribution_get_AutoRemovePublishingPoint(This,pbAutoRemove)	\
    (This)->lpVtbl -> get_AutoRemovePublishingPoint(This,pbAutoRemove)

#define IWMEncPushDistribution_put_AutoRemovePublishingPoint(This,bAutoRemove)	\
    (This)->lpVtbl -> put_AutoRemovePublishingPoint(This,bAutoRemove)

#define IWMEncPushDistribution_GenerateMulticastInfoFile(This,bstrNSCFileName)	\
    (This)->lpVtbl -> GenerateMulticastInfoFile(This,bstrNSCFileName)

#define IWMEncPushDistribution_GenerateAnnouncementFile(This,bstrNSCURL,bstrASXFileName)	\
    (This)->lpVtbl -> GenerateAnnouncementFile(This,bstrNSCURL,bstrASXFileName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_get_ServerName_Proxy( 
    IWMEncPushDistribution * This,
    /* [retval][out] */ BSTR *pbstrServerName);


void __RPC_STUB IWMEncPushDistribution_get_ServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_put_ServerName_Proxy( 
    IWMEncPushDistribution * This,
    /* [in] */ BSTR bstrServerName);


void __RPC_STUB IWMEncPushDistribution_put_ServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_get_PublishingPoint_Proxy( 
    IWMEncPushDistribution * This,
    /* [retval][out] */ BSTR *pbstrPublishingPoint);


void __RPC_STUB IWMEncPushDistribution_get_PublishingPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_put_PublishingPoint_Proxy( 
    IWMEncPushDistribution * This,
    /* [in] */ BSTR bstrPublishingPoint);


void __RPC_STUB IWMEncPushDistribution_put_PublishingPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_get_Template_Proxy( 
    IWMEncPushDistribution * This,
    /* [retval][out] */ BSTR *pbstrTemplate);


void __RPC_STUB IWMEncPushDistribution_get_Template_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_put_Template_Proxy( 
    IWMEncPushDistribution * This,
    /* [in] */ BSTR bstrTemplate);


void __RPC_STUB IWMEncPushDistribution_put_Template_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_get_AutoRemovePublishingPoint_Proxy( 
    IWMEncPushDistribution * This,
    /* [retval][out] */ VARIANT_BOOL *pbAutoRemove);


void __RPC_STUB IWMEncPushDistribution_get_AutoRemovePublishingPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_put_AutoRemovePublishingPoint_Proxy( 
    IWMEncPushDistribution * This,
    /* [in] */ VARIANT_BOOL bAutoRemove);


void __RPC_STUB IWMEncPushDistribution_put_AutoRemovePublishingPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_GenerateMulticastInfoFile_Proxy( 
    IWMEncPushDistribution * This,
    /* [in] */ BSTR bstrNSCFileName);


void __RPC_STUB IWMEncPushDistribution_GenerateMulticastInfoFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistribution_GenerateAnnouncementFile_Proxy( 
    IWMEncPushDistribution * This,
    /* [in] */ BSTR bstrNSCURL,
    /* [in] */ BSTR bstrASXFileName);


void __RPC_STUB IWMEncPushDistribution_GenerateAnnouncementFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncPushDistribution_INTERFACE_DEFINED__ */


#ifndef __IWMEncDeviceControlPluginInfoManager_INTERFACE_DEFINED__
#define __IWMEncDeviceControlPluginInfoManager_INTERFACE_DEFINED__

/* interface IWMEncDeviceControlPluginInfoManager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDeviceControlPluginInfoManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6087-BBC6-11D2-A329-006097C4E476")
    IWMEncDeviceControlPluginInfoManager : public IDispatch
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
            /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDeviceControlPluginInfoManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDeviceControlPluginInfoManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDeviceControlPluginInfoManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncDeviceControlPluginInfoManager * This,
            /* [in] */ long iIndex,
            /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWMEncDeviceControlPluginInfoManager * This);
        
        END_INTERFACE
    } IWMEncDeviceControlPluginInfoManagerVtbl;

    interface IWMEncDeviceControlPluginInfoManager
    {
        CONST_VTBL struct IWMEncDeviceControlPluginInfoManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDeviceControlPluginInfoManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDeviceControlPluginInfoManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDeviceControlPluginInfoManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDeviceControlPluginInfoManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncDeviceControlPluginInfoManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncDeviceControlPluginInfoManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncDeviceControlPluginInfoManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncDeviceControlPluginInfoManager_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncDeviceControlPluginInfoManager_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncDeviceControlPluginInfoManager_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncDeviceControlPluginInfoManager_Item(This,iIndex,ppPluginInfo)	\
    (This)->lpVtbl -> Item(This,iIndex,ppPluginInfo)

#define IWMEncDeviceControlPluginInfoManager_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPluginInfoManager_get_length_Proxy( 
    IWMEncDeviceControlPluginInfoManager * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncDeviceControlPluginInfoManager_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPluginInfoManager_get_Count_Proxy( 
    IWMEncDeviceControlPluginInfoManager * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncDeviceControlPluginInfoManager_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPluginInfoManager_get__NewEnum_Proxy( 
    IWMEncDeviceControlPluginInfoManager * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncDeviceControlPluginInfoManager_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPluginInfoManager_Item_Proxy( 
    IWMEncDeviceControlPluginInfoManager * This,
    /* [in] */ long iIndex,
    /* [retval][out] */ IWMEncPluginInfo **ppPluginInfo);


void __RPC_STUB IWMEncDeviceControlPluginInfoManager_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlPluginInfoManager_Refresh_Proxy( 
    IWMEncDeviceControlPluginInfoManager * This);


void __RPC_STUB IWMEncDeviceControlPluginInfoManager_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDeviceControlPluginInfoManager_INTERFACE_DEFINED__ */


#ifndef __IWMEncDeviceControl_INTERFACE_DEFINED__
#define __IWMEncDeviceControl_INTERFACE_DEFINED__

/* interface IWMEncDeviceControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDeviceControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B6089-BBC6-11D2-A329-006097C4E476")
    IWMEncDeviceControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInput( 
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme = L"",
            /* [defaultvalue][in] */ BSTR bstrInitData = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInput( 
            /* [out] */ VARIANT *pbstrScheme,
            /* [out] */ VARIANT *pbstrInitData,
            /* [retval][out] */ BSTR *pbstrInput) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDeviceControlPlugin( 
            /* [retval][out] */ IUnknown **ppUnkPlugin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDeviceControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDeviceControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDeviceControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDeviceControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncDeviceControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncDeviceControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncDeviceControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncDeviceControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInput )( 
            IWMEncDeviceControl * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrInitData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInput )( 
            IWMEncDeviceControl * This,
            /* [out] */ VARIANT *pbstrScheme,
            /* [out] */ VARIANT *pbstrInitData,
            /* [retval][out] */ BSTR *pbstrInput);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDeviceControlPlugin )( 
            IWMEncDeviceControl * This,
            /* [retval][out] */ IUnknown **ppUnkPlugin);
        
        END_INTERFACE
    } IWMEncDeviceControlVtbl;

    interface IWMEncDeviceControl
    {
        CONST_VTBL struct IWMEncDeviceControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDeviceControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDeviceControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDeviceControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDeviceControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncDeviceControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncDeviceControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncDeviceControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncDeviceControl_SetInput(This,bstrInput,bstrScheme,bstrInitData)	\
    (This)->lpVtbl -> SetInput(This,bstrInput,bstrScheme,bstrInitData)

#define IWMEncDeviceControl_GetInput(This,pbstrScheme,pbstrInitData,pbstrInput)	\
    (This)->lpVtbl -> GetInput(This,pbstrScheme,pbstrInitData,pbstrInput)

#define IWMEncDeviceControl_GetDeviceControlPlugin(This,ppUnkPlugin)	\
    (This)->lpVtbl -> GetDeviceControlPlugin(This,ppUnkPlugin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControl_SetInput_Proxy( 
    IWMEncDeviceControl * This,
    /* [in] */ BSTR bstrInput,
    /* [defaultvalue][in] */ BSTR bstrScheme,
    /* [defaultvalue][in] */ BSTR bstrInitData);


void __RPC_STUB IWMEncDeviceControl_SetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControl_GetInput_Proxy( 
    IWMEncDeviceControl * This,
    /* [out] */ VARIANT *pbstrScheme,
    /* [out] */ VARIANT *pbstrInitData,
    /* [retval][out] */ BSTR *pbstrInput);


void __RPC_STUB IWMEncDeviceControl_GetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControl_GetDeviceControlPlugin_Proxy( 
    IWMEncDeviceControl * This,
    /* [retval][out] */ IUnknown **ppUnkPlugin);


void __RPC_STUB IWMEncDeviceControl_GetDeviceControlPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDeviceControl_INTERFACE_DEFINED__ */


#ifndef __IWMEncDeviceControlCollection_INTERFACE_DEFINED__
#define __IWMEncDeviceControlCollection_INTERFACE_DEFINED__

/* interface IWMEncDeviceControlCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncDeviceControlCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632B608C-BBC6-11D2-A329-006097C4E476")
    IWMEncDeviceControlCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pIUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncDeviceControl **ppDeviceControl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [retval][out] */ IWMEncDeviceControl **ppDeviceControl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long lIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncDeviceControlCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncDeviceControlCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncDeviceControlCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncDeviceControlCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncDeviceControlCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncDeviceControlCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncDeviceControlCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncDeviceControlCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncDeviceControlCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncDeviceControlCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWMEncDeviceControlCollection * This,
            /* [retval][out] */ LPUNKNOWN *pIUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncDeviceControlCollection * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncDeviceControl **ppDeviceControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncDeviceControlCollection * This,
            /* [retval][out] */ IWMEncDeviceControl **ppDeviceControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncDeviceControlCollection * This,
            /* [in] */ long lIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncDeviceControlCollection * This);
        
        END_INTERFACE
    } IWMEncDeviceControlCollectionVtbl;

    interface IWMEncDeviceControlCollection
    {
        CONST_VTBL struct IWMEncDeviceControlCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncDeviceControlCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncDeviceControlCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncDeviceControlCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncDeviceControlCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncDeviceControlCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncDeviceControlCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncDeviceControlCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncDeviceControlCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncDeviceControlCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncDeviceControlCollection_get__NewEnum(This,pIUnknown)	\
    (This)->lpVtbl -> get__NewEnum(This,pIUnknown)

#define IWMEncDeviceControlCollection_Item(This,lIndex,ppDeviceControl)	\
    (This)->lpVtbl -> Item(This,lIndex,ppDeviceControl)

#define IWMEncDeviceControlCollection_Add(This,ppDeviceControl)	\
    (This)->lpVtbl -> Add(This,ppDeviceControl)

#define IWMEncDeviceControlCollection_Remove(This,lIndex)	\
    (This)->lpVtbl -> Remove(This,lIndex)

#define IWMEncDeviceControlCollection_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlCollection_get_length_Proxy( 
    IWMEncDeviceControlCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncDeviceControlCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlCollection_get_Count_Proxy( 
    IWMEncDeviceControlCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncDeviceControlCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlCollection_get__NewEnum_Proxy( 
    IWMEncDeviceControlCollection * This,
    /* [retval][out] */ LPUNKNOWN *pIUnknown);


void __RPC_STUB IWMEncDeviceControlCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlCollection_Item_Proxy( 
    IWMEncDeviceControlCollection * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ IWMEncDeviceControl **ppDeviceControl);


void __RPC_STUB IWMEncDeviceControlCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlCollection_Add_Proxy( 
    IWMEncDeviceControlCollection * This,
    /* [retval][out] */ IWMEncDeviceControl **ppDeviceControl);


void __RPC_STUB IWMEncDeviceControlCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlCollection_Remove_Proxy( 
    IWMEncDeviceControlCollection * This,
    /* [in] */ long lIndex);


void __RPC_STUB IWMEncDeviceControlCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncDeviceControlCollection_RemoveAll_Proxy( 
    IWMEncDeviceControlCollection * This);


void __RPC_STUB IWMEncDeviceControlCollection_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncDeviceControlCollection_INTERFACE_DEFINED__ */


#ifndef __IWMEncContentAnalyzer_INTERFACE_DEFINED__
#define __IWMEncContentAnalyzer_INTERFACE_DEFINED__

/* interface IWMEncContentAnalyzer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncContentAnalyzer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("221ADE1A-3CF9-4ba2-841C-E580C588766A")
    IWMEncContentAnalyzer : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceGroup( 
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SourceGroup( 
            /* [in] */ IWMEncSourceGroup *pSourceGroup) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Property( 
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvarValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncContentAnalyzerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncContentAnalyzer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncContentAnalyzer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncContentAnalyzer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncContentAnalyzer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncContentAnalyzer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncContentAnalyzer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncContentAnalyzer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceGroup )( 
            IWMEncContentAnalyzer * This,
            /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SourceGroup )( 
            IWMEncContentAnalyzer * This,
            /* [in] */ IWMEncSourceGroup *pSourceGroup);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IWMEncContentAnalyzer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IWMEncContentAnalyzer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Property )( 
            IWMEncContentAnalyzer * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [in] */ short iIndex,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvarValue);
        
        END_INTERFACE
    } IWMEncContentAnalyzerVtbl;

    interface IWMEncContentAnalyzer
    {
        CONST_VTBL struct IWMEncContentAnalyzerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncContentAnalyzer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncContentAnalyzer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncContentAnalyzer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncContentAnalyzer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncContentAnalyzer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncContentAnalyzer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncContentAnalyzer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncContentAnalyzer_get_SourceGroup(This,ppSourceGroup)	\
    (This)->lpVtbl -> get_SourceGroup(This,ppSourceGroup)

#define IWMEncContentAnalyzer_put_SourceGroup(This,pSourceGroup)	\
    (This)->lpVtbl -> put_SourceGroup(This,pSourceGroup)

#define IWMEncContentAnalyzer_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IWMEncContentAnalyzer_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWMEncContentAnalyzer_Property(This,enumType,iIndex,bstrProperty,pvarValue)	\
    (This)->lpVtbl -> Property(This,enumType,iIndex,bstrProperty,pvarValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncContentAnalyzer_get_SourceGroup_Proxy( 
    IWMEncContentAnalyzer * This,
    /* [retval][out] */ IWMEncSourceGroup **ppSourceGroup);


void __RPC_STUB IWMEncContentAnalyzer_get_SourceGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncContentAnalyzer_put_SourceGroup_Proxy( 
    IWMEncContentAnalyzer * This,
    /* [in] */ IWMEncSourceGroup *pSourceGroup);


void __RPC_STUB IWMEncContentAnalyzer_put_SourceGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncContentAnalyzer_Start_Proxy( 
    IWMEncContentAnalyzer * This);


void __RPC_STUB IWMEncContentAnalyzer_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncContentAnalyzer_Stop_Proxy( 
    IWMEncContentAnalyzer * This);


void __RPC_STUB IWMEncContentAnalyzer_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncContentAnalyzer_Property_Proxy( 
    IWMEncContentAnalyzer * This,
    /* [in] */ WMENC_SOURCE_TYPE enumType,
    /* [in] */ short iIndex,
    /* [in] */ BSTR bstrProperty,
    /* [retval][out] */ VARIANT *pvarValue);


void __RPC_STUB IWMEncContentAnalyzer_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncContentAnalyzer_INTERFACE_DEFINED__ */


#ifndef __IWMEncBasicEdit_INTERFACE_DEFINED__
#define __IWMEncBasicEdit_INTERFACE_DEFINED__

/* interface IWMEncBasicEdit */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncBasicEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("22A65C28-F99D-4c0d-8070-5F86FE6EC555")
    IWMEncBasicEdit : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaFile( 
            /* [retval][out] */ BSTR *pbstrMediaFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaFile( 
            /* [in] */ BSTR bstrMediaFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputFile( 
            /* [retval][out] */ BSTR *pbstrOutputFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputFile( 
            /* [in] */ BSTR bstrOutputFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfigFile( 
            /* [retval][out] */ BSTR *pbstrConfigXMLFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConfigFile( 
            /* [in] */ BSTR bstrConfigXMLFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkIn( 
            /* [retval][out] */ WMENC_LONGLONG *pllMarkIn) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkIn( 
            /* [in] */ WMENC_LONGLONG llMarkIn) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkOut( 
            /* [retval][out] */ WMENC_LONGLONG *pllMarkOut) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkOut( 
            /* [in] */ WMENC_LONGLONG llMarkOut) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ VARIANT_BOOL *pfIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Index( 
            /* [in] */ VARIANT_BOOL pfIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveConfigFile( 
            /* [in] */ BSTR bstrConfigXMLFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveProfile( 
            /* [in] */ BSTR bstrProfileFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IWMEncProfile2 **ppIWMEncProfile2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RunState( 
            /* [retval][out] */ WMENC_BASICEDIT_STATE *penumState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ WMENC_LONGLONG *pllDuration) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorState( 
            /* [retval][out] */ long *plResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressPercent( 
            /* [retval][out] */ long *plProgressPercent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncBasicEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncBasicEdit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncBasicEdit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncBasicEdit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncBasicEdit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncBasicEdit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncBasicEdit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncBasicEdit * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFile )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ BSTR *pbstrMediaFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaFile )( 
            IWMEncBasicEdit * This,
            /* [in] */ BSTR bstrMediaFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputFile )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ BSTR *pbstrOutputFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputFile )( 
            IWMEncBasicEdit * This,
            /* [in] */ BSTR bstrOutputFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfigFile )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ BSTR *pbstrConfigXMLFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConfigFile )( 
            IWMEncBasicEdit * This,
            /* [in] */ BSTR bstrConfigXMLFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkIn )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ WMENC_LONGLONG *pllMarkIn);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkIn )( 
            IWMEncBasicEdit * This,
            /* [in] */ WMENC_LONGLONG llMarkIn);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkOut )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ WMENC_LONGLONG *pllMarkOut);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkOut )( 
            IWMEncBasicEdit * This,
            /* [in] */ WMENC_LONGLONG llMarkOut);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Index )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pfIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Index )( 
            IWMEncBasicEdit * This,
            /* [in] */ VARIANT_BOOL pfIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveConfigFile )( 
            IWMEncBasicEdit * This,
            /* [in] */ BSTR bstrConfigXMLFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveProfile )( 
            IWMEncBasicEdit * This,
            /* [in] */ BSTR bstrProfileFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ IWMEncProfile2 **ppIWMEncProfile2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IWMEncBasicEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IWMEncBasicEdit * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunState )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ WMENC_BASICEDIT_STATE *penumState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Duration )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ WMENC_LONGLONG *pllDuration);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ErrorState )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ long *plResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgressPercent )( 
            IWMEncBasicEdit * This,
            /* [retval][out] */ long *plProgressPercent);
        
        END_INTERFACE
    } IWMEncBasicEditVtbl;

    interface IWMEncBasicEdit
    {
        CONST_VTBL struct IWMEncBasicEditVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncBasicEdit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncBasicEdit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncBasicEdit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncBasicEdit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncBasicEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncBasicEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncBasicEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncBasicEdit_get_MediaFile(This,pbstrMediaFileName)	\
    (This)->lpVtbl -> get_MediaFile(This,pbstrMediaFileName)

#define IWMEncBasicEdit_put_MediaFile(This,bstrMediaFileName)	\
    (This)->lpVtbl -> put_MediaFile(This,bstrMediaFileName)

#define IWMEncBasicEdit_get_OutputFile(This,pbstrOutputFileName)	\
    (This)->lpVtbl -> get_OutputFile(This,pbstrOutputFileName)

#define IWMEncBasicEdit_put_OutputFile(This,bstrOutputFileName)	\
    (This)->lpVtbl -> put_OutputFile(This,bstrOutputFileName)

#define IWMEncBasicEdit_get_ConfigFile(This,pbstrConfigXMLFileName)	\
    (This)->lpVtbl -> get_ConfigFile(This,pbstrConfigXMLFileName)

#define IWMEncBasicEdit_put_ConfigFile(This,bstrConfigXMLFileName)	\
    (This)->lpVtbl -> put_ConfigFile(This,bstrConfigXMLFileName)

#define IWMEncBasicEdit_get_MarkIn(This,pllMarkIn)	\
    (This)->lpVtbl -> get_MarkIn(This,pllMarkIn)

#define IWMEncBasicEdit_put_MarkIn(This,llMarkIn)	\
    (This)->lpVtbl -> put_MarkIn(This,llMarkIn)

#define IWMEncBasicEdit_get_MarkOut(This,pllMarkOut)	\
    (This)->lpVtbl -> get_MarkOut(This,pllMarkOut)

#define IWMEncBasicEdit_put_MarkOut(This,llMarkOut)	\
    (This)->lpVtbl -> put_MarkOut(This,llMarkOut)

#define IWMEncBasicEdit_get_Index(This,pfIndex)	\
    (This)->lpVtbl -> get_Index(This,pfIndex)

#define IWMEncBasicEdit_put_Index(This,pfIndex)	\
    (This)->lpVtbl -> put_Index(This,pfIndex)

#define IWMEncBasicEdit_SaveConfigFile(This,bstrConfigXMLFileName)	\
    (This)->lpVtbl -> SaveConfigFile(This,bstrConfigXMLFileName)

#define IWMEncBasicEdit_SaveProfile(This,bstrProfileFileName)	\
    (This)->lpVtbl -> SaveProfile(This,bstrProfileFileName)

#define IWMEncBasicEdit_get_Profile(This,ppIWMEncProfile2)	\
    (This)->lpVtbl -> get_Profile(This,ppIWMEncProfile2)

#define IWMEncBasicEdit_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IWMEncBasicEdit_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWMEncBasicEdit_get_RunState(This,penumState)	\
    (This)->lpVtbl -> get_RunState(This,penumState)

#define IWMEncBasicEdit_get_Duration(This,pllDuration)	\
    (This)->lpVtbl -> get_Duration(This,pllDuration)

#define IWMEncBasicEdit_get_ErrorState(This,plResult)	\
    (This)->lpVtbl -> get_ErrorState(This,plResult)

#define IWMEncBasicEdit_get_ProgressPercent(This,plProgressPercent)	\
    (This)->lpVtbl -> get_ProgressPercent(This,plProgressPercent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_MediaFile_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ BSTR *pbstrMediaFileName);


void __RPC_STUB IWMEncBasicEdit_get_MediaFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_put_MediaFile_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ BSTR bstrMediaFileName);


void __RPC_STUB IWMEncBasicEdit_put_MediaFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_OutputFile_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ BSTR *pbstrOutputFileName);


void __RPC_STUB IWMEncBasicEdit_get_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_put_OutputFile_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ BSTR bstrOutputFileName);


void __RPC_STUB IWMEncBasicEdit_put_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_ConfigFile_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ BSTR *pbstrConfigXMLFileName);


void __RPC_STUB IWMEncBasicEdit_get_ConfigFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_put_ConfigFile_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ BSTR bstrConfigXMLFileName);


void __RPC_STUB IWMEncBasicEdit_put_ConfigFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_MarkIn_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ WMENC_LONGLONG *pllMarkIn);


void __RPC_STUB IWMEncBasicEdit_get_MarkIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_put_MarkIn_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ WMENC_LONGLONG llMarkIn);


void __RPC_STUB IWMEncBasicEdit_put_MarkIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_MarkOut_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ WMENC_LONGLONG *pllMarkOut);


void __RPC_STUB IWMEncBasicEdit_get_MarkOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_put_MarkOut_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ WMENC_LONGLONG llMarkOut);


void __RPC_STUB IWMEncBasicEdit_put_MarkOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_Index_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pfIndex);


void __RPC_STUB IWMEncBasicEdit_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_put_Index_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ VARIANT_BOOL pfIndex);


void __RPC_STUB IWMEncBasicEdit_put_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_SaveConfigFile_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ BSTR bstrConfigXMLFileName);


void __RPC_STUB IWMEncBasicEdit_SaveConfigFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_SaveProfile_Proxy( 
    IWMEncBasicEdit * This,
    /* [in] */ BSTR bstrProfileFileName);


void __RPC_STUB IWMEncBasicEdit_SaveProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_Profile_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ IWMEncProfile2 **ppIWMEncProfile2);


void __RPC_STUB IWMEncBasicEdit_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_Start_Proxy( 
    IWMEncBasicEdit * This);


void __RPC_STUB IWMEncBasicEdit_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_Stop_Proxy( 
    IWMEncBasicEdit * This);


void __RPC_STUB IWMEncBasicEdit_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_RunState_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ WMENC_BASICEDIT_STATE *penumState);


void __RPC_STUB IWMEncBasicEdit_get_RunState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_Duration_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ WMENC_LONGLONG *pllDuration);


void __RPC_STUB IWMEncBasicEdit_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_ErrorState_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ long *plResult);


void __RPC_STUB IWMEncBasicEdit_get_ErrorState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncBasicEdit_get_ProgressPercent_Proxy( 
    IWMEncBasicEdit * This,
    /* [retval][out] */ long *plProgressPercent);


void __RPC_STUB IWMEncBasicEdit_get_ProgressPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncBasicEdit_INTERFACE_DEFINED__ */


#ifndef __IWMEncVideoSource2_INTERFACE_DEFINED__
#define __IWMEncVideoSource2_INTERFACE_DEFINED__

/* interface IWMEncVideoSource2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncVideoSource2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0973771-5F87-456a-B31B-5171C28AC01E")
    IWMEncVideoSource2 : public IWMEncVideoSource
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long *plWidth) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long lWidth) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long *plHeight) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long lHeight) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PixelAspectRatioX( 
            /* [retval][out] */ short *piRatioX) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PixelAspectRatioX( 
            /* [in] */ short iRatioX) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PixelAspectRatioY( 
            /* [retval][out] */ short *piRatioY) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PixelAspectRatioY( 
            /* [in] */ short iRatioY) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreProcessPass( 
            /* [retval][out] */ short *piPassesCount) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PreProcessPass( 
            /* [in] */ short iPassesCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumerateInputs( 
            /* [retval][out] */ IWMEncInputCollection **ppInputCol) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Input( 
            /* [in] */ short iSourceID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Channel( 
            /* [in] */ short iChannelNum) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Country( 
            /* [in] */ long lCountry) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TVType( 
            /* [in] */ short iTunerInputType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TVFormat( 
            /* [in] */ long lAnalogVideoStandard) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Input( 
            /* [retval][out] */ short *piSourceID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Channel( 
            /* [retval][out] */ short *piChannelNum) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Country( 
            /* [retval][out] */ long *plCountry) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TVType( 
            /* [retval][out] */ short *piTunerInputType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TVFormat( 
            /* [retval][out] */ long *plAnalogVideoStandard) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelMin( 
            /* [out][retval] */ long *plChannelMin) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelMax( 
            /* [out][retval] */ long *plChannelMax) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ long *plDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncVideoSource2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncVideoSource2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncVideoSource2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncVideoSource2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncVideoSource2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncVideoSource2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncVideoSource2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncVideoSource2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE *enumType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInput )( 
            IWMEncVideoSource2 * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrStreamName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInput )( 
            IWMEncVideoSource2 * This,
            /* [out] */ BSTR *bstrStreamName,
            /* [out] */ BSTR *bstrScheme,
            /* [retval][out] */ BSTR *pbstrInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Repeat )( 
            IWMEncVideoSource2 * This,
            /* [in] */ VARIANT_BOOL bRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Repeat )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkIn )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plMarkIn);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkIn )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lMarkIn);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkOut )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plMarkOut);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkOut )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lMarkOut);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformCollection )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPluginCount )( 
            IWMEncVideoSource2 * This,
            /* [out] */ DWORD *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPlugin )( 
            IWMEncVideoSource2 * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkTransformPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreviewCollection )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PostviewCollection )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSourcePlugin )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ IUnknown **ppUnkPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingMode )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ WMENC_CROPPING_MODE *penumCroppingMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingMode )( 
            IWMEncVideoSource2 * This,
            /* [in] */ WMENC_CROPPING_MODE enumCroppingMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingLeftMargin )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plLeft);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingLeftMargin )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lLeft);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingTopMargin )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plTop);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingTopMargin )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lTop);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingRightMargin )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plRight);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingRightMargin )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lRight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CroppingBottomMargin )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plBottom);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CroppingBottomMargin )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lBottom);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Optimization )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ WMENC_VIDEO_OPTIMIZATION *penumOptimization);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Optimization )( 
            IWMEncVideoSource2 * This,
            /* [in] */ WMENC_VIDEO_OPTIMIZATION enumOptimization);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelFormat )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ WMENC_PIXELFORMAT_VIDEO *penumPixelFormat);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PixelFormat )( 
            IWMEncVideoSource2 * This,
            /* [in] */ WMENC_PIXELFORMAT_VIDEO enumPixelFormat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plWidth);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lWidth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plHeight);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lHeight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelAspectRatioX )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ short *piRatioX);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PixelAspectRatioX )( 
            IWMEncVideoSource2 * This,
            /* [in] */ short iRatioX);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelAspectRatioY )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ short *piRatioY);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PixelAspectRatioY )( 
            IWMEncVideoSource2 * This,
            /* [in] */ short iRatioY);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreProcessPass )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ short *piPassesCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PreProcessPass )( 
            IWMEncVideoSource2 * This,
            /* [in] */ short iPassesCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumerateInputs )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ IWMEncInputCollection **ppInputCol);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Input )( 
            IWMEncVideoSource2 * This,
            /* [in] */ short iSourceID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Channel )( 
            IWMEncVideoSource2 * This,
            /* [in] */ short iChannelNum);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Country )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lCountry);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TVType )( 
            IWMEncVideoSource2 * This,
            /* [in] */ short iTunerInputType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TVFormat )( 
            IWMEncVideoSource2 * This,
            /* [in] */ long lAnalogVideoStandard);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Input )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ short *piSourceID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Channel )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ short *piChannelNum);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Country )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plCountry);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TVType )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ short *piTunerInputType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TVFormat )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plAnalogVideoStandard);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelMin )( 
            IWMEncVideoSource2 * This,
            /* [out][retval] */ long *plChannelMin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelMax )( 
            IWMEncVideoSource2 * This,
            /* [out][retval] */ long *plChannelMax);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Duration )( 
            IWMEncVideoSource2 * This,
            /* [retval][out] */ long *plDuration);
        
        END_INTERFACE
    } IWMEncVideoSource2Vtbl;

    interface IWMEncVideoSource2
    {
        CONST_VTBL struct IWMEncVideoSource2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncVideoSource2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncVideoSource2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncVideoSource2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncVideoSource2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncVideoSource2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncVideoSource2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncVideoSource2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncVideoSource2_get_Type(This,enumType)	\
    (This)->lpVtbl -> get_Type(This,enumType)

#define IWMEncVideoSource2_SetInput(This,bstrInput,bstrScheme,bstrStreamName)	\
    (This)->lpVtbl -> SetInput(This,bstrInput,bstrScheme,bstrStreamName)

#define IWMEncVideoSource2_GetInput(This,bstrStreamName,bstrScheme,pbstrInput)	\
    (This)->lpVtbl -> GetInput(This,bstrStreamName,bstrScheme,pbstrInput)

#define IWMEncVideoSource2_put_Repeat(This,bRepeat)	\
    (This)->lpVtbl -> put_Repeat(This,bRepeat)

#define IWMEncVideoSource2_get_Repeat(This,pbRepeat)	\
    (This)->lpVtbl -> get_Repeat(This,pbRepeat)

#define IWMEncVideoSource2_get_MarkIn(This,plMarkIn)	\
    (This)->lpVtbl -> get_MarkIn(This,plMarkIn)

#define IWMEncVideoSource2_put_MarkIn(This,lMarkIn)	\
    (This)->lpVtbl -> put_MarkIn(This,lMarkIn)

#define IWMEncVideoSource2_get_MarkOut(This,plMarkOut)	\
    (This)->lpVtbl -> get_MarkOut(This,plMarkOut)

#define IWMEncVideoSource2_put_MarkOut(This,lMarkOut)	\
    (This)->lpVtbl -> put_MarkOut(This,lMarkOut)

#define IWMEncVideoSource2_get_TransformCollection(This,ppTransformCollection)	\
    (This)->lpVtbl -> get_TransformCollection(This,ppTransformCollection)

#define IWMEncVideoSource2_GetTransformPluginCount(This,pdwCount)	\
    (This)->lpVtbl -> GetTransformPluginCount(This,pdwCount)

#define IWMEncVideoSource2_GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)	\
    (This)->lpVtbl -> GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)

#define IWMEncVideoSource2_get_PreviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PreviewCollection(This,ppDataViewCollection)

#define IWMEncVideoSource2_get_PostviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PostviewCollection(This,ppDataViewCollection)

#define IWMEncVideoSource2_GetSourcePlugin(This,ppUnkPlugin)	\
    (This)->lpVtbl -> GetSourcePlugin(This,ppUnkPlugin)


#define IWMEncVideoSource2_get_CroppingMode(This,penumCroppingMode)	\
    (This)->lpVtbl -> get_CroppingMode(This,penumCroppingMode)

#define IWMEncVideoSource2_put_CroppingMode(This,enumCroppingMode)	\
    (This)->lpVtbl -> put_CroppingMode(This,enumCroppingMode)

#define IWMEncVideoSource2_get_CroppingLeftMargin(This,plLeft)	\
    (This)->lpVtbl -> get_CroppingLeftMargin(This,plLeft)

#define IWMEncVideoSource2_put_CroppingLeftMargin(This,lLeft)	\
    (This)->lpVtbl -> put_CroppingLeftMargin(This,lLeft)

#define IWMEncVideoSource2_get_CroppingTopMargin(This,plTop)	\
    (This)->lpVtbl -> get_CroppingTopMargin(This,plTop)

#define IWMEncVideoSource2_put_CroppingTopMargin(This,lTop)	\
    (This)->lpVtbl -> put_CroppingTopMargin(This,lTop)

#define IWMEncVideoSource2_get_CroppingRightMargin(This,plRight)	\
    (This)->lpVtbl -> get_CroppingRightMargin(This,plRight)

#define IWMEncVideoSource2_put_CroppingRightMargin(This,lRight)	\
    (This)->lpVtbl -> put_CroppingRightMargin(This,lRight)

#define IWMEncVideoSource2_get_CroppingBottomMargin(This,plBottom)	\
    (This)->lpVtbl -> get_CroppingBottomMargin(This,plBottom)

#define IWMEncVideoSource2_put_CroppingBottomMargin(This,lBottom)	\
    (This)->lpVtbl -> put_CroppingBottomMargin(This,lBottom)

#define IWMEncVideoSource2_get_Optimization(This,penumOptimization)	\
    (This)->lpVtbl -> get_Optimization(This,penumOptimization)

#define IWMEncVideoSource2_put_Optimization(This,enumOptimization)	\
    (This)->lpVtbl -> put_Optimization(This,enumOptimization)

#define IWMEncVideoSource2_get_PixelFormat(This,penumPixelFormat)	\
    (This)->lpVtbl -> get_PixelFormat(This,penumPixelFormat)

#define IWMEncVideoSource2_put_PixelFormat(This,enumPixelFormat)	\
    (This)->lpVtbl -> put_PixelFormat(This,enumPixelFormat)


#define IWMEncVideoSource2_get_Width(This,plWidth)	\
    (This)->lpVtbl -> get_Width(This,plWidth)

#define IWMEncVideoSource2_put_Width(This,lWidth)	\
    (This)->lpVtbl -> put_Width(This,lWidth)

#define IWMEncVideoSource2_get_Height(This,plHeight)	\
    (This)->lpVtbl -> get_Height(This,plHeight)

#define IWMEncVideoSource2_put_Height(This,lHeight)	\
    (This)->lpVtbl -> put_Height(This,lHeight)

#define IWMEncVideoSource2_get_PixelAspectRatioX(This,piRatioX)	\
    (This)->lpVtbl -> get_PixelAspectRatioX(This,piRatioX)

#define IWMEncVideoSource2_put_PixelAspectRatioX(This,iRatioX)	\
    (This)->lpVtbl -> put_PixelAspectRatioX(This,iRatioX)

#define IWMEncVideoSource2_get_PixelAspectRatioY(This,piRatioY)	\
    (This)->lpVtbl -> get_PixelAspectRatioY(This,piRatioY)

#define IWMEncVideoSource2_put_PixelAspectRatioY(This,iRatioY)	\
    (This)->lpVtbl -> put_PixelAspectRatioY(This,iRatioY)

#define IWMEncVideoSource2_get_PreProcessPass(This,piPassesCount)	\
    (This)->lpVtbl -> get_PreProcessPass(This,piPassesCount)

#define IWMEncVideoSource2_put_PreProcessPass(This,iPassesCount)	\
    (This)->lpVtbl -> put_PreProcessPass(This,iPassesCount)

#define IWMEncVideoSource2_EnumerateInputs(This,ppInputCol)	\
    (This)->lpVtbl -> EnumerateInputs(This,ppInputCol)

#define IWMEncVideoSource2_put_Input(This,iSourceID)	\
    (This)->lpVtbl -> put_Input(This,iSourceID)

#define IWMEncVideoSource2_put_Channel(This,iChannelNum)	\
    (This)->lpVtbl -> put_Channel(This,iChannelNum)

#define IWMEncVideoSource2_put_Country(This,lCountry)	\
    (This)->lpVtbl -> put_Country(This,lCountry)

#define IWMEncVideoSource2_put_TVType(This,iTunerInputType)	\
    (This)->lpVtbl -> put_TVType(This,iTunerInputType)

#define IWMEncVideoSource2_put_TVFormat(This,lAnalogVideoStandard)	\
    (This)->lpVtbl -> put_TVFormat(This,lAnalogVideoStandard)

#define IWMEncVideoSource2_get_Input(This,piSourceID)	\
    (This)->lpVtbl -> get_Input(This,piSourceID)

#define IWMEncVideoSource2_get_Channel(This,piChannelNum)	\
    (This)->lpVtbl -> get_Channel(This,piChannelNum)

#define IWMEncVideoSource2_get_Country(This,plCountry)	\
    (This)->lpVtbl -> get_Country(This,plCountry)

#define IWMEncVideoSource2_get_TVType(This,piTunerInputType)	\
    (This)->lpVtbl -> get_TVType(This,piTunerInputType)

#define IWMEncVideoSource2_get_TVFormat(This,plAnalogVideoStandard)	\
    (This)->lpVtbl -> get_TVFormat(This,plAnalogVideoStandard)

#define IWMEncVideoSource2_get_ChannelMin(This,plChannelMin)	\
    (This)->lpVtbl -> get_ChannelMin(This,plChannelMin)

#define IWMEncVideoSource2_get_ChannelMax(This,plChannelMax)	\
    (This)->lpVtbl -> get_ChannelMax(This,plChannelMax)

#define IWMEncVideoSource2_get_Duration(This,plDuration)	\
    (This)->lpVtbl -> get_Duration(This,plDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_Width_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ long *plWidth);


void __RPC_STUB IWMEncVideoSource2_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_Width_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ long lWidth);


void __RPC_STUB IWMEncVideoSource2_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_Height_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ long *plHeight);


void __RPC_STUB IWMEncVideoSource2_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_Height_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ long lHeight);


void __RPC_STUB IWMEncVideoSource2_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_PixelAspectRatioX_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ short *piRatioX);


void __RPC_STUB IWMEncVideoSource2_get_PixelAspectRatioX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_PixelAspectRatioX_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ short iRatioX);


void __RPC_STUB IWMEncVideoSource2_put_PixelAspectRatioX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_PixelAspectRatioY_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ short *piRatioY);


void __RPC_STUB IWMEncVideoSource2_get_PixelAspectRatioY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_PixelAspectRatioY_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ short iRatioY);


void __RPC_STUB IWMEncVideoSource2_put_PixelAspectRatioY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_PreProcessPass_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ short *piPassesCount);


void __RPC_STUB IWMEncVideoSource2_get_PreProcessPass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_PreProcessPass_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ short iPassesCount);


void __RPC_STUB IWMEncVideoSource2_put_PreProcessPass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_EnumerateInputs_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ IWMEncInputCollection **ppInputCol);


void __RPC_STUB IWMEncVideoSource2_EnumerateInputs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_Input_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ short iSourceID);


void __RPC_STUB IWMEncVideoSource2_put_Input_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_Channel_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ short iChannelNum);


void __RPC_STUB IWMEncVideoSource2_put_Channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_Country_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ long lCountry);


void __RPC_STUB IWMEncVideoSource2_put_Country_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_TVType_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ short iTunerInputType);


void __RPC_STUB IWMEncVideoSource2_put_TVType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_put_TVFormat_Proxy( 
    IWMEncVideoSource2 * This,
    /* [in] */ long lAnalogVideoStandard);


void __RPC_STUB IWMEncVideoSource2_put_TVFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_Input_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ short *piSourceID);


void __RPC_STUB IWMEncVideoSource2_get_Input_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_Channel_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ short *piChannelNum);


void __RPC_STUB IWMEncVideoSource2_get_Channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_Country_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ long *plCountry);


void __RPC_STUB IWMEncVideoSource2_get_Country_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_TVType_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ short *piTunerInputType);


void __RPC_STUB IWMEncVideoSource2_get_TVType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_TVFormat_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ long *plAnalogVideoStandard);


void __RPC_STUB IWMEncVideoSource2_get_TVFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_ChannelMin_Proxy( 
    IWMEncVideoSource2 * This,
    /* [out][retval] */ long *plChannelMin);


void __RPC_STUB IWMEncVideoSource2_get_ChannelMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_ChannelMax_Proxy( 
    IWMEncVideoSource2 * This,
    /* [out][retval] */ long *plChannelMax);


void __RPC_STUB IWMEncVideoSource2_get_ChannelMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncVideoSource2_get_Duration_Proxy( 
    IWMEncVideoSource2 * This,
    /* [retval][out] */ long *plDuration);


void __RPC_STUB IWMEncVideoSource2_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncVideoSource2_INTERFACE_DEFINED__ */


#ifndef __IWMEncAudioSource_INTERFACE_DEFINED__
#define __IWMEncAudioSource_INTERFACE_DEFINED__

/* interface IWMEncAudioSource */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncAudioSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0973772-5F87-456a-B31B-5171C28AC01E")
    IWMEncAudioSource : public IWMEncSource
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentMode( 
            /* [retval][out] */ WMENC_CONTENT_MODE *penumMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContentMode( 
            /* [in] */ WMENC_CONTENT_MODE enumMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentEDL( 
            /* [retval][out] */ BSTR *pbstrEDL) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContentEDL( 
            /* [in] */ BSTR bstrEDL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreProcessPass( 
            /* [retval][out] */ short *piPassesCount) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PreProcessPass( 
            /* [in] */ short iPassesCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ long *plDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncAudioSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncAudioSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncAudioSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncAudioSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncAudioSource * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncAudioSource * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncAudioSource * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncAudioSource * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ WMENC_SOURCE_TYPE *enumType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInput )( 
            IWMEncAudioSource * This,
            /* [in] */ BSTR bstrInput,
            /* [defaultvalue][in] */ BSTR bstrScheme,
            /* [defaultvalue][in] */ BSTR bstrStreamName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInput )( 
            IWMEncAudioSource * This,
            /* [out] */ BSTR *bstrStreamName,
            /* [out] */ BSTR *bstrScheme,
            /* [retval][out] */ BSTR *pbstrInput);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Repeat )( 
            IWMEncAudioSource * This,
            /* [in] */ VARIANT_BOOL bRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Repeat )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ VARIANT_BOOL *pbRepeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkIn )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ long *plMarkIn);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkIn )( 
            IWMEncAudioSource * This,
            /* [in] */ long lMarkIn);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkOut )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ long *plMarkOut);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkOut )( 
            IWMEncAudioSource * This,
            /* [in] */ long lMarkOut);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformCollection )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ IWMEncTransformCollection **ppTransformCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPluginCount )( 
            IWMEncAudioSource * This,
            /* [out] */ DWORD *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransformPlugin )( 
            IWMEncAudioSource * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IUnknown **ppUnkTransformPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreviewCollection )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PostviewCollection )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ IWMEncDataViewCollection **ppDataViewCollection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSourcePlugin )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ IUnknown **ppUnkPlugin);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentMode )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ WMENC_CONTENT_MODE *penumMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ContentMode )( 
            IWMEncAudioSource * This,
            /* [in] */ WMENC_CONTENT_MODE enumMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentEDL )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ BSTR *pbstrEDL);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ContentEDL )( 
            IWMEncAudioSource * This,
            /* [in] */ BSTR bstrEDL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreProcessPass )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ short *piPassesCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PreProcessPass )( 
            IWMEncAudioSource * This,
            /* [in] */ short iPassesCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Duration )( 
            IWMEncAudioSource * This,
            /* [retval][out] */ long *plDuration);
        
        END_INTERFACE
    } IWMEncAudioSourceVtbl;

    interface IWMEncAudioSource
    {
        CONST_VTBL struct IWMEncAudioSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncAudioSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncAudioSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncAudioSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncAudioSource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncAudioSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncAudioSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncAudioSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncAudioSource_get_Type(This,enumType)	\
    (This)->lpVtbl -> get_Type(This,enumType)

#define IWMEncAudioSource_SetInput(This,bstrInput,bstrScheme,bstrStreamName)	\
    (This)->lpVtbl -> SetInput(This,bstrInput,bstrScheme,bstrStreamName)

#define IWMEncAudioSource_GetInput(This,bstrStreamName,bstrScheme,pbstrInput)	\
    (This)->lpVtbl -> GetInput(This,bstrStreamName,bstrScheme,pbstrInput)

#define IWMEncAudioSource_put_Repeat(This,bRepeat)	\
    (This)->lpVtbl -> put_Repeat(This,bRepeat)

#define IWMEncAudioSource_get_Repeat(This,pbRepeat)	\
    (This)->lpVtbl -> get_Repeat(This,pbRepeat)

#define IWMEncAudioSource_get_MarkIn(This,plMarkIn)	\
    (This)->lpVtbl -> get_MarkIn(This,plMarkIn)

#define IWMEncAudioSource_put_MarkIn(This,lMarkIn)	\
    (This)->lpVtbl -> put_MarkIn(This,lMarkIn)

#define IWMEncAudioSource_get_MarkOut(This,plMarkOut)	\
    (This)->lpVtbl -> get_MarkOut(This,plMarkOut)

#define IWMEncAudioSource_put_MarkOut(This,lMarkOut)	\
    (This)->lpVtbl -> put_MarkOut(This,lMarkOut)

#define IWMEncAudioSource_get_TransformCollection(This,ppTransformCollection)	\
    (This)->lpVtbl -> get_TransformCollection(This,ppTransformCollection)

#define IWMEncAudioSource_GetTransformPluginCount(This,pdwCount)	\
    (This)->lpVtbl -> GetTransformPluginCount(This,pdwCount)

#define IWMEncAudioSource_GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)	\
    (This)->lpVtbl -> GetTransformPlugin(This,dwIndex,ppUnkTransformPlugin)

#define IWMEncAudioSource_get_PreviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PreviewCollection(This,ppDataViewCollection)

#define IWMEncAudioSource_get_PostviewCollection(This,ppDataViewCollection)	\
    (This)->lpVtbl -> get_PostviewCollection(This,ppDataViewCollection)

#define IWMEncAudioSource_GetSourcePlugin(This,ppUnkPlugin)	\
    (This)->lpVtbl -> GetSourcePlugin(This,ppUnkPlugin)


#define IWMEncAudioSource_get_ContentMode(This,penumMode)	\
    (This)->lpVtbl -> get_ContentMode(This,penumMode)

#define IWMEncAudioSource_put_ContentMode(This,enumMode)	\
    (This)->lpVtbl -> put_ContentMode(This,enumMode)

#define IWMEncAudioSource_get_ContentEDL(This,pbstrEDL)	\
    (This)->lpVtbl -> get_ContentEDL(This,pbstrEDL)

#define IWMEncAudioSource_put_ContentEDL(This,bstrEDL)	\
    (This)->lpVtbl -> put_ContentEDL(This,bstrEDL)

#define IWMEncAudioSource_get_PreProcessPass(This,piPassesCount)	\
    (This)->lpVtbl -> get_PreProcessPass(This,piPassesCount)

#define IWMEncAudioSource_put_PreProcessPass(This,iPassesCount)	\
    (This)->lpVtbl -> put_PreProcessPass(This,iPassesCount)

#define IWMEncAudioSource_get_Duration(This,plDuration)	\
    (This)->lpVtbl -> get_Duration(This,plDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudioSource_get_ContentMode_Proxy( 
    IWMEncAudioSource * This,
    /* [retval][out] */ WMENC_CONTENT_MODE *penumMode);


void __RPC_STUB IWMEncAudioSource_get_ContentMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudioSource_put_ContentMode_Proxy( 
    IWMEncAudioSource * This,
    /* [in] */ WMENC_CONTENT_MODE enumMode);


void __RPC_STUB IWMEncAudioSource_put_ContentMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudioSource_get_ContentEDL_Proxy( 
    IWMEncAudioSource * This,
    /* [retval][out] */ BSTR *pbstrEDL);


void __RPC_STUB IWMEncAudioSource_get_ContentEDL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudioSource_put_ContentEDL_Proxy( 
    IWMEncAudioSource * This,
    /* [in] */ BSTR bstrEDL);


void __RPC_STUB IWMEncAudioSource_put_ContentEDL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudioSource_get_PreProcessPass_Proxy( 
    IWMEncAudioSource * This,
    /* [retval][out] */ short *piPassesCount);


void __RPC_STUB IWMEncAudioSource_get_PreProcessPass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudioSource_put_PreProcessPass_Proxy( 
    IWMEncAudioSource * This,
    /* [in] */ short iPassesCount);


void __RPC_STUB IWMEncAudioSource_put_PreProcessPass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudioSource_get_Duration_Proxy( 
    IWMEncAudioSource * This,
    /* [retval][out] */ long *plDuration);


void __RPC_STUB IWMEncAudioSource_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncAudioSource_INTERFACE_DEFINED__ */


#ifndef __IWMEncPushDistributionStats_INTERFACE_DEFINED__
#define __IWMEncPushDistributionStats_INTERFACE_DEFINED__

/* interface IWMEncPushDistributionStats */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncPushDistributionStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("252F3333-53D0-47d9-94C6-C38736F1BA6A")
    IWMEncPushDistributionStats : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Property( 
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvarProperty) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncPushDistributionStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncPushDistributionStats * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncPushDistributionStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncPushDistributionStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncPushDistributionStats * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncPushDistributionStats * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncPushDistributionStats * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncPushDistributionStats * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Property )( 
            IWMEncPushDistributionStats * This,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvarProperty);
        
        END_INTERFACE
    } IWMEncPushDistributionStatsVtbl;

    interface IWMEncPushDistributionStats
    {
        CONST_VTBL struct IWMEncPushDistributionStatsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncPushDistributionStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncPushDistributionStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncPushDistributionStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncPushDistributionStats_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncPushDistributionStats_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncPushDistributionStats_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncPushDistributionStats_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncPushDistributionStats_get_Property(This,bstrProperty,pvarProperty)	\
    (This)->lpVtbl -> get_Property(This,bstrProperty,pvarProperty)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncPushDistributionStats_get_Property_Proxy( 
    IWMEncPushDistributionStats * This,
    /* [in] */ BSTR bstrProperty,
    /* [retval][out] */ VARIANT *pvarProperty);


void __RPC_STUB IWMEncPushDistributionStats_get_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncPushDistributionStats_INTERFACE_DEFINED__ */


#ifndef __IWMEncAudienceObj_INTERFACE_DEFINED__
#define __IWMEncAudienceObj_INTERFACE_DEFINED__

/* interface IWMEncAudienceObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncAudienceObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BB494815-9432-47f2-979D-94E4AE6C96CF")
    IWMEncAudienceObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Selected( 
            /* [retval][out] */ VARIANT_BOOL *pfSelected) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Selected( 
            /* [in] */ VARIANT_BOOL fSelected) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TotalBitrate( 
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TotalPeakBitrate( 
            /* [retval][out] */ long *plPeakBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCodec( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plCodecIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioCodec( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lCodecIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioFormat( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plFormatIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioFormat( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lFormatIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAudioConfig( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ short nChannels,
            /* [in] */ long nSamplesPerSec,
            /* [in] */ long lBitrate,
            /* [in] */ short wBitsPerSample) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioPeakBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioPeakBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioBufferMax( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBMax) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioBufferMax( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBMax) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCodec( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plCodecIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoCodec( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lCodecIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoPeakBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoPeakBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoWidth( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plWidth) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoWidth( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lWidth) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoHeight( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plHeight) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoHeight( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lHeight) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoFPS( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plFPS) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoFPS( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lFPS) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoKeyFrameDistance( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ WMENC_LONGLONG *pllKFS) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoKeyFrameDistance( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ WMENC_LONGLONG llKFS) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoImageSharpness( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plIQuality) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoImageSharpness( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lIQuality) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCompressionQuality( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plCQuality) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoCompressionQuality( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lCQuality) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoBufferSize( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBS) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoBufferSize( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBS) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoBufferMax( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBMax) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoBufferMax( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBMax) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScriptBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ScriptBitrate( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamBitrate( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StreamBitrate( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Property( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvarProperty) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Property( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ BSTR bstrProperty,
            /* [in] */ VARIANT varProperty) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncAudienceObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncAudienceObj * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncAudienceObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncAudienceObj * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncAudienceObj * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncAudienceObj * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncAudienceObj * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncAudienceObj * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Selected )( 
            IWMEncAudienceObj * This,
            /* [retval][out] */ VARIANT_BOOL *pfSelected);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Selected )( 
            IWMEncAudienceObj * This,
            /* [in] */ VARIANT_BOOL fSelected);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TotalBitrate )( 
            IWMEncAudienceObj * This,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TotalPeakBitrate )( 
            IWMEncAudienceObj * This,
            /* [retval][out] */ long *plPeakBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioCodec )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plCodecIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioCodec )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lCodecIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioFormat )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plFormatIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioFormat )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lFormatIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAudioConfig )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ short nChannels,
            /* [in] */ long nSamplesPerSec,
            /* [in] */ long lBitrate,
            /* [in] */ short wBitsPerSample);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioPeakBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioPeakBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioBufferMax )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBMax);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioBufferMax )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBMax);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCodec )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plCodecIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoCodec )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lCodecIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoPeakBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoPeakBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoWidth )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plWidth);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoWidth )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lWidth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoHeight )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plHeight);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoHeight )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lHeight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoFPS )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plFPS);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoFPS )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lFPS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoKeyFrameDistance )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ WMENC_LONGLONG *pllKFS);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoKeyFrameDistance )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ WMENC_LONGLONG llKFS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoImageSharpness )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plIQuality);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoImageSharpness )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lIQuality);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCompressionQuality )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plCQuality);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoCompressionQuality )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lCQuality);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoBufferSize )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBS);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoBufferSize )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoBufferMax )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBMax);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoBufferMax )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBMax);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScriptBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScriptBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StreamBitrate )( 
            IWMEncAudienceObj * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ long lBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Property )( 
            IWMEncAudienceObj * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ BSTR bstrProperty,
            /* [retval][out] */ VARIANT *pvarProperty);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Property )( 
            IWMEncAudienceObj * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ BSTR bstrProperty,
            /* [in] */ VARIANT varProperty);
        
        END_INTERFACE
    } IWMEncAudienceObjVtbl;

    interface IWMEncAudienceObj
    {
        CONST_VTBL struct IWMEncAudienceObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncAudienceObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncAudienceObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncAudienceObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncAudienceObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncAudienceObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncAudienceObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncAudienceObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncAudienceObj_get_Selected(This,pfSelected)	\
    (This)->lpVtbl -> get_Selected(This,pfSelected)

#define IWMEncAudienceObj_put_Selected(This,fSelected)	\
    (This)->lpVtbl -> put_Selected(This,fSelected)

#define IWMEncAudienceObj_get_TotalBitrate(This,plBitrate)	\
    (This)->lpVtbl -> get_TotalBitrate(This,plBitrate)

#define IWMEncAudienceObj_get_TotalPeakBitrate(This,plPeakBitrate)	\
    (This)->lpVtbl -> get_TotalPeakBitrate(This,plPeakBitrate)

#define IWMEncAudienceObj_get_AudioCodec(This,iRenderSiteIndex,plCodecIndex)	\
    (This)->lpVtbl -> get_AudioCodec(This,iRenderSiteIndex,plCodecIndex)

#define IWMEncAudienceObj_put_AudioCodec(This,iRenderSiteIndex,lCodecIndex)	\
    (This)->lpVtbl -> put_AudioCodec(This,iRenderSiteIndex,lCodecIndex)

#define IWMEncAudienceObj_get_AudioBitrate(This,iRenderSiteIndex,plBitrate)	\
    (This)->lpVtbl -> get_AudioBitrate(This,iRenderSiteIndex,plBitrate)

#define IWMEncAudienceObj_get_AudioFormat(This,iRenderSiteIndex,plFormatIndex)	\
    (This)->lpVtbl -> get_AudioFormat(This,iRenderSiteIndex,plFormatIndex)

#define IWMEncAudienceObj_put_AudioFormat(This,iRenderSiteIndex,lFormatIndex)	\
    (This)->lpVtbl -> put_AudioFormat(This,iRenderSiteIndex,lFormatIndex)

#define IWMEncAudienceObj_SetAudioConfig(This,iRenderSiteIndex,nChannels,nSamplesPerSec,lBitrate,wBitsPerSample)	\
    (This)->lpVtbl -> SetAudioConfig(This,iRenderSiteIndex,nChannels,nSamplesPerSec,lBitrate,wBitsPerSample)

#define IWMEncAudienceObj_get_AudioPeakBitrate(This,iRenderSiteIndex,plBitrate)	\
    (This)->lpVtbl -> get_AudioPeakBitrate(This,iRenderSiteIndex,plBitrate)

#define IWMEncAudienceObj_put_AudioPeakBitrate(This,iRenderSiteIndex,lBitrate)	\
    (This)->lpVtbl -> put_AudioPeakBitrate(This,iRenderSiteIndex,lBitrate)

#define IWMEncAudienceObj_get_AudioBufferMax(This,iRenderSiteIndex,plBMax)	\
    (This)->lpVtbl -> get_AudioBufferMax(This,iRenderSiteIndex,plBMax)

#define IWMEncAudienceObj_put_AudioBufferMax(This,iRenderSiteIndex,lBMax)	\
    (This)->lpVtbl -> put_AudioBufferMax(This,iRenderSiteIndex,lBMax)

#define IWMEncAudienceObj_get_VideoCodec(This,iRenderSiteIndex,plCodecIndex)	\
    (This)->lpVtbl -> get_VideoCodec(This,iRenderSiteIndex,plCodecIndex)

#define IWMEncAudienceObj_put_VideoCodec(This,iRenderSiteIndex,lCodecIndex)	\
    (This)->lpVtbl -> put_VideoCodec(This,iRenderSiteIndex,lCodecIndex)

#define IWMEncAudienceObj_get_VideoBitrate(This,iRenderSiteIndex,plBitrate)	\
    (This)->lpVtbl -> get_VideoBitrate(This,iRenderSiteIndex,plBitrate)

#define IWMEncAudienceObj_put_VideoBitrate(This,iRenderSiteIndex,lBitrate)	\
    (This)->lpVtbl -> put_VideoBitrate(This,iRenderSiteIndex,lBitrate)

#define IWMEncAudienceObj_get_VideoPeakBitrate(This,iRenderSiteIndex,plBitrate)	\
    (This)->lpVtbl -> get_VideoPeakBitrate(This,iRenderSiteIndex,plBitrate)

#define IWMEncAudienceObj_put_VideoPeakBitrate(This,iRenderSiteIndex,lBitrate)	\
    (This)->lpVtbl -> put_VideoPeakBitrate(This,iRenderSiteIndex,lBitrate)

#define IWMEncAudienceObj_get_VideoWidth(This,iRenderSiteIndex,plWidth)	\
    (This)->lpVtbl -> get_VideoWidth(This,iRenderSiteIndex,plWidth)

#define IWMEncAudienceObj_put_VideoWidth(This,iRenderSiteIndex,lWidth)	\
    (This)->lpVtbl -> put_VideoWidth(This,iRenderSiteIndex,lWidth)

#define IWMEncAudienceObj_get_VideoHeight(This,iRenderSiteIndex,plHeight)	\
    (This)->lpVtbl -> get_VideoHeight(This,iRenderSiteIndex,plHeight)

#define IWMEncAudienceObj_put_VideoHeight(This,iRenderSiteIndex,lHeight)	\
    (This)->lpVtbl -> put_VideoHeight(This,iRenderSiteIndex,lHeight)

#define IWMEncAudienceObj_get_VideoFPS(This,iRenderSiteIndex,plFPS)	\
    (This)->lpVtbl -> get_VideoFPS(This,iRenderSiteIndex,plFPS)

#define IWMEncAudienceObj_put_VideoFPS(This,iRenderSiteIndex,lFPS)	\
    (This)->lpVtbl -> put_VideoFPS(This,iRenderSiteIndex,lFPS)

#define IWMEncAudienceObj_get_VideoKeyFrameDistance(This,iRenderSiteIndex,pllKFS)	\
    (This)->lpVtbl -> get_VideoKeyFrameDistance(This,iRenderSiteIndex,pllKFS)

#define IWMEncAudienceObj_put_VideoKeyFrameDistance(This,iRenderSiteIndex,llKFS)	\
    (This)->lpVtbl -> put_VideoKeyFrameDistance(This,iRenderSiteIndex,llKFS)

#define IWMEncAudienceObj_get_VideoImageSharpness(This,iRenderSiteIndex,plIQuality)	\
    (This)->lpVtbl -> get_VideoImageSharpness(This,iRenderSiteIndex,plIQuality)

#define IWMEncAudienceObj_put_VideoImageSharpness(This,iRenderSiteIndex,lIQuality)	\
    (This)->lpVtbl -> put_VideoImageSharpness(This,iRenderSiteIndex,lIQuality)

#define IWMEncAudienceObj_get_VideoCompressionQuality(This,iRenderSiteIndex,plCQuality)	\
    (This)->lpVtbl -> get_VideoCompressionQuality(This,iRenderSiteIndex,plCQuality)

#define IWMEncAudienceObj_put_VideoCompressionQuality(This,iRenderSiteIndex,lCQuality)	\
    (This)->lpVtbl -> put_VideoCompressionQuality(This,iRenderSiteIndex,lCQuality)

#define IWMEncAudienceObj_get_VideoBufferSize(This,iRenderSiteIndex,plBS)	\
    (This)->lpVtbl -> get_VideoBufferSize(This,iRenderSiteIndex,plBS)

#define IWMEncAudienceObj_put_VideoBufferSize(This,iRenderSiteIndex,lBS)	\
    (This)->lpVtbl -> put_VideoBufferSize(This,iRenderSiteIndex,lBS)

#define IWMEncAudienceObj_get_VideoBufferMax(This,iRenderSiteIndex,plBMax)	\
    (This)->lpVtbl -> get_VideoBufferMax(This,iRenderSiteIndex,plBMax)

#define IWMEncAudienceObj_put_VideoBufferMax(This,iRenderSiteIndex,lBMax)	\
    (This)->lpVtbl -> put_VideoBufferMax(This,iRenderSiteIndex,lBMax)

#define IWMEncAudienceObj_get_ScriptBitrate(This,iRenderSiteIndex,plBitrate)	\
    (This)->lpVtbl -> get_ScriptBitrate(This,iRenderSiteIndex,plBitrate)

#define IWMEncAudienceObj_put_ScriptBitrate(This,iRenderSiteIndex,lBitrate)	\
    (This)->lpVtbl -> put_ScriptBitrate(This,iRenderSiteIndex,lBitrate)

#define IWMEncAudienceObj_get_StreamBitrate(This,enumSrcType,iRenderSiteIndex,plBitrate)	\
    (This)->lpVtbl -> get_StreamBitrate(This,enumSrcType,iRenderSiteIndex,plBitrate)

#define IWMEncAudienceObj_put_StreamBitrate(This,enumSrcType,iRenderSiteIndex,lBitrate)	\
    (This)->lpVtbl -> put_StreamBitrate(This,enumSrcType,iRenderSiteIndex,lBitrate)

#define IWMEncAudienceObj_get_Property(This,enumSrcType,iRenderSiteIndex,bstrProperty,pvarProperty)	\
    (This)->lpVtbl -> get_Property(This,enumSrcType,iRenderSiteIndex,bstrProperty,pvarProperty)

#define IWMEncAudienceObj_put_Property(This,enumSrcType,iRenderSiteIndex,bstrProperty,varProperty)	\
    (This)->lpVtbl -> put_Property(This,enumSrcType,iRenderSiteIndex,bstrProperty,varProperty)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_Selected_Proxy( 
    IWMEncAudienceObj * This,
    /* [retval][out] */ VARIANT_BOOL *pfSelected);


void __RPC_STUB IWMEncAudienceObj_get_Selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_Selected_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ VARIANT_BOOL fSelected);


void __RPC_STUB IWMEncAudienceObj_put_Selected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_TotalBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncAudienceObj_get_TotalBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_TotalPeakBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [retval][out] */ long *plPeakBitrate);


void __RPC_STUB IWMEncAudienceObj_get_TotalPeakBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_AudioCodec_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plCodecIndex);


void __RPC_STUB IWMEncAudienceObj_get_AudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_AudioCodec_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lCodecIndex);


void __RPC_STUB IWMEncAudienceObj_put_AudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_AudioBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncAudienceObj_get_AudioBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_AudioFormat_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plFormatIndex);


void __RPC_STUB IWMEncAudienceObj_get_AudioFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_AudioFormat_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lFormatIndex);


void __RPC_STUB IWMEncAudienceObj_put_AudioFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_SetAudioConfig_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ short nChannels,
    /* [in] */ long nSamplesPerSec,
    /* [in] */ long lBitrate,
    /* [in] */ short wBitsPerSample);


void __RPC_STUB IWMEncAudienceObj_SetAudioConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_AudioPeakBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncAudienceObj_get_AudioPeakBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_AudioPeakBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBitrate);


void __RPC_STUB IWMEncAudienceObj_put_AudioPeakBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_AudioBufferMax_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBMax);


void __RPC_STUB IWMEncAudienceObj_get_AudioBufferMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_AudioBufferMax_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBMax);


void __RPC_STUB IWMEncAudienceObj_put_AudioBufferMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoCodec_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plCodecIndex);


void __RPC_STUB IWMEncAudienceObj_get_VideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoCodec_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lCodecIndex);


void __RPC_STUB IWMEncAudienceObj_put_VideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncAudienceObj_get_VideoBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBitrate);


void __RPC_STUB IWMEncAudienceObj_put_VideoBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoPeakBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncAudienceObj_get_VideoPeakBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoPeakBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBitrate);


void __RPC_STUB IWMEncAudienceObj_put_VideoPeakBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoWidth_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plWidth);


void __RPC_STUB IWMEncAudienceObj_get_VideoWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoWidth_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lWidth);


void __RPC_STUB IWMEncAudienceObj_put_VideoWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoHeight_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plHeight);


void __RPC_STUB IWMEncAudienceObj_get_VideoHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoHeight_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lHeight);


void __RPC_STUB IWMEncAudienceObj_put_VideoHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoFPS_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plFPS);


void __RPC_STUB IWMEncAudienceObj_get_VideoFPS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoFPS_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lFPS);


void __RPC_STUB IWMEncAudienceObj_put_VideoFPS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoKeyFrameDistance_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ WMENC_LONGLONG *pllKFS);


void __RPC_STUB IWMEncAudienceObj_get_VideoKeyFrameDistance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoKeyFrameDistance_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ WMENC_LONGLONG llKFS);


void __RPC_STUB IWMEncAudienceObj_put_VideoKeyFrameDistance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoImageSharpness_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plIQuality);


void __RPC_STUB IWMEncAudienceObj_get_VideoImageSharpness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoImageSharpness_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lIQuality);


void __RPC_STUB IWMEncAudienceObj_put_VideoImageSharpness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoCompressionQuality_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plCQuality);


void __RPC_STUB IWMEncAudienceObj_get_VideoCompressionQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoCompressionQuality_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lCQuality);


void __RPC_STUB IWMEncAudienceObj_put_VideoCompressionQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoBufferSize_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBS);


void __RPC_STUB IWMEncAudienceObj_get_VideoBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoBufferSize_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBS);


void __RPC_STUB IWMEncAudienceObj_put_VideoBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_VideoBufferMax_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBMax);


void __RPC_STUB IWMEncAudienceObj_get_VideoBufferMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_VideoBufferMax_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBMax);


void __RPC_STUB IWMEncAudienceObj_put_VideoBufferMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_ScriptBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncAudienceObj_get_ScriptBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_ScriptBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBitrate);


void __RPC_STUB IWMEncAudienceObj_put_ScriptBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_StreamBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncAudienceObj_get_StreamBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_StreamBitrate_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ long lBitrate);


void __RPC_STUB IWMEncAudienceObj_put_StreamBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_get_Property_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ BSTR bstrProperty,
    /* [retval][out] */ VARIANT *pvarProperty);


void __RPC_STUB IWMEncAudienceObj_get_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncAudienceObj_put_Property_Proxy( 
    IWMEncAudienceObj * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ BSTR bstrProperty,
    /* [in] */ VARIANT varProperty);


void __RPC_STUB IWMEncAudienceObj_put_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncAudienceObj_INTERFACE_DEFINED__ */


#ifndef __IWMEncProfile2_INTERFACE_DEFINED__
#define __IWMEncProfile2_INTERFACE_DEFINED__

/* interface IWMEncProfile2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncProfile2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C70E1CAC-32D2-4e22-A0FF-3A32E315D095")
    IWMEncProfile2 : public IWMEncProfile
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentType( 
            /* [retval][out] */ long *plSrcType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContentType( 
            /* [in] */ long lSrcType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromIWMProfile( 
            /* [in] */ IUnknown *pUnkProfile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromFile( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromMemory( 
            /* [in] */ BSTR bstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToIWMProfile( 
            /* [retval][out] */ IUnknown **pUnkProfile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToFile( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToMemory( 
            /* [retval][out] */ BSTR *pbstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [in] */ IWMEncProfile2 *pObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudienceCount( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Audience( 
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncAudienceObj **ppAudience) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAudience( 
            /* [in] */ long lBitrate,
            /* [retval][out] */ IWMEncAudienceObj **ppAudience) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAudience( 
            /* [in] */ long lIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ValidateMode( 
            /* [retval][out] */ VARIANT_BOOL *pfValidate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ValidateMode( 
            /* [in] */ VARIANT_BOOL fValidate) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Validate( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CompatibilityMode( 
            /* [retval][out] */ WMENC_PROFILE_COMPATIBILITY *penumCompat) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CompatibilityMode( 
            /* [in] */ WMENC_PROFILE_COMPATIBILITY enumCompat) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VBRMode( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [retval][out] */ WMENC_PROFILE_VBR_MODE *penumVBR) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VBRMode( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ WMENC_PROFILE_VBR_MODE enumVBR) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileName( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileName( 
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileDescription( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileDescription( 
            /* [retval][out] */ BSTR *pbstrDescription) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCodecCount( 
            /* [retval][out] */ long *plAudioCodecCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumAudioCodec( 
            /* [in] */ long lCodecIndex,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ long *lFormatTag) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioFormatCount( 
            /* [in] */ long lCodecIndex,
            /* [retval][out] */ long *plAudioFormatCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumAudioFormat( 
            /* [in] */ long lCodecIndex,
            /* [in] */ long lFormatIndex,
            /* [out] */ VARIANT *pvarName,
            /* [out] */ VARIANT *pvarSamplingRate,
            /* [out] */ VARIANT *pvarNChannels,
            /* [out] */ VARIANT *pvarBitsPerSample,
            /* [retval][out] */ long *plBitrate) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCodecCount( 
            /* [retval][out] */ long *plVideoCodecCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumVideoCodec( 
            /* [in] */ long lCodecIndex,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ long *lFourCC) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCodecIndexFromFourCC( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lFourCC,
            /* [retval][out] */ long *plIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCodecFourCCFromIndex( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lIndex,
            /* [retval][out] */ long *plFourCC) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LanguageCount( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [retval][out] */ long *plLanguageCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Language( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ long lLanguageIndex,
            /* [retval][out] */ long *lcidLanguage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddLanguage( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ long lcidLanguage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveLanguage( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ long lcidLanguage) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BroadcastMode( 
            /* [retval][out] */ WMENC_PROFILE_BROADCAST_MODE *penumBroadcastMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BroadcastMode( 
            /* [in] */ WMENC_PROFILE_BROADCAST_MODE enumBroadcastMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DetectCompatibility( 
            /* [retval][out] */ WMENC_PROFILE_COMPATIBILITY *penumCompat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Merge( 
            /* [in] */ IWMEncProfile2 *pWMEncProfileObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Compare( 
            /* [in] */ IWMEncProfile2 *pCompObj,
            /* [out] */ VARIANT_BOOL *pfSubset,
            /* [retval][out] */ VARIANT_BOOL *pfEqual) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InterlaceMode( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ VARIANT_BOOL *pfInterlaceMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InterlaceMode( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ VARIANT_BOOL fInterlaceMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NonSquarePixelMode( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ VARIANT_BOOL *pfNonSquarePixelMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NonSquarePixelMode( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ VARIANT_BOOL fNonSquarePixelMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableTimecode( 
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ VARIANT_BOOL *pfTimecode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableTimecode( 
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ VARIANT_BOOL fTimecode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinPacketSize( 
            /* [retval][out] */ long *plMinPacketSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinPacketSize( 
            /* [in] */ long lMinPacketSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncProfile2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncProfile2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncProfile2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncProfile2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncProfile2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncProfile2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncProfile2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncProfile2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ BSTR *bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ BSTR *bstrDescription);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaCount )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumType,
            /* [retval][out] */ short *piCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MultipleBitrate )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbMBR);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudienceCollection )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ IDispatch **ppAudienceCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxPacketSize )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ long *plMaxPacketSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxPacketSize )( 
            IWMEncProfile2 * This,
            /* [in] */ long lMaxPacketSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentType )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ long *plSrcType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ContentType )( 
            IWMEncProfile2 * This,
            /* [in] */ long lSrcType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadFromIWMProfile )( 
            IWMEncProfile2 * This,
            /* [in] */ IUnknown *pUnkProfile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadFromFile )( 
            IWMEncProfile2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadFromMemory )( 
            IWMEncProfile2 * This,
            /* [in] */ BSTR bstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveToIWMProfile )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ IUnknown **pUnkProfile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveToFile )( 
            IWMEncProfile2 * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveToMemory )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ BSTR *pbstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IWMEncProfile2 * This,
            /* [in] */ IWMEncProfile2 *pObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IWMEncProfile2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudienceCount )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Audience )( 
            IWMEncProfile2 * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncAudienceObj **ppAudience);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAudience )( 
            IWMEncProfile2 * This,
            /* [in] */ long lBitrate,
            /* [retval][out] */ IWMEncAudienceObj **ppAudience);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAudience )( 
            IWMEncProfile2 * This,
            /* [in] */ long lIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ValidateMode )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ VARIANT_BOOL *pfValidate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ValidateMode )( 
            IWMEncProfile2 * This,
            /* [in] */ VARIANT_BOOL fValidate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Validate )( 
            IWMEncProfile2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompatibilityMode )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ WMENC_PROFILE_COMPATIBILITY *penumCompat);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CompatibilityMode )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_PROFILE_COMPATIBILITY enumCompat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VBRMode )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [retval][out] */ WMENC_PROFILE_VBR_MODE *penumVBR);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VBRMode )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ WMENC_PROFILE_VBR_MODE enumVBR);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProfileName )( 
            IWMEncProfile2 * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileName )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProfileDescription )( 
            IWMEncProfile2 * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileDescription )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ BSTR *pbstrDescription);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioCodecCount )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ long *plAudioCodecCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumAudioCodec )( 
            IWMEncProfile2 * This,
            /* [in] */ long lCodecIndex,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ long *lFormatTag);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioFormatCount )( 
            IWMEncProfile2 * This,
            /* [in] */ long lCodecIndex,
            /* [retval][out] */ long *plAudioFormatCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumAudioFormat )( 
            IWMEncProfile2 * This,
            /* [in] */ long lCodecIndex,
            /* [in] */ long lFormatIndex,
            /* [out] */ VARIANT *pvarName,
            /* [out] */ VARIANT *pvarSamplingRate,
            /* [out] */ VARIANT *pvarNChannels,
            /* [out] */ VARIANT *pvarBitsPerSample,
            /* [retval][out] */ long *plBitrate);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCodecCount )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ long *plVideoCodecCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumVideoCodec )( 
            IWMEncProfile2 * This,
            /* [in] */ long lCodecIndex,
            /* [out] */ VARIANT *pvarName,
            /* [retval][out] */ long *lFourCC);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCodecIndexFromFourCC )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lFourCC,
            /* [retval][out] */ long *plIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCodecFourCCFromIndex )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lIndex,
            /* [retval][out] */ long *plFourCC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LanguageCount )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [retval][out] */ long *plLanguageCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Language )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ long lLanguageIndex,
            /* [retval][out] */ long *lcidLanguage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddLanguage )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ long lcidLanguage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveLanguage )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ short iRenderSite,
            /* [in] */ long lcidLanguage);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BroadcastMode )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ WMENC_PROFILE_BROADCAST_MODE *penumBroadcastMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BroadcastMode )( 
            IWMEncProfile2 * This,
            /* [in] */ WMENC_PROFILE_BROADCAST_MODE enumBroadcastMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DetectCompatibility )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ WMENC_PROFILE_COMPATIBILITY *penumCompat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Merge )( 
            IWMEncProfile2 * This,
            /* [in] */ IWMEncProfile2 *pWMEncProfileObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Compare )( 
            IWMEncProfile2 * This,
            /* [in] */ IWMEncProfile2 *pCompObj,
            /* [out] */ VARIANT_BOOL *pfSubset,
            /* [retval][out] */ VARIANT_BOOL *pfEqual);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InterlaceMode )( 
            IWMEncProfile2 * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ VARIANT_BOOL *pfInterlaceMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InterlaceMode )( 
            IWMEncProfile2 * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ VARIANT_BOOL fInterlaceMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NonSquarePixelMode )( 
            IWMEncProfile2 * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ VARIANT_BOOL *pfNonSquarePixelMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NonSquarePixelMode )( 
            IWMEncProfile2 * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ VARIANT_BOOL fNonSquarePixelMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnableTimecode )( 
            IWMEncProfile2 * This,
            /* [in] */ short iRenderSiteIndex,
            /* [retval][out] */ VARIANT_BOOL *pfTimecode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnableTimecode )( 
            IWMEncProfile2 * This,
            /* [in] */ short iRenderSiteIndex,
            /* [in] */ VARIANT_BOOL fTimecode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinPacketSize )( 
            IWMEncProfile2 * This,
            /* [retval][out] */ long *plMinPacketSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinPacketSize )( 
            IWMEncProfile2 * This,
            /* [in] */ long lMinPacketSize);
        
        END_INTERFACE
    } IWMEncProfile2Vtbl;

    interface IWMEncProfile2
    {
        CONST_VTBL struct IWMEncProfile2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncProfile2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncProfile2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncProfile2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncProfile2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncProfile2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncProfile2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncProfile2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncProfile2_get_Name(This,bstrName)	\
    (This)->lpVtbl -> get_Name(This,bstrName)

#define IWMEncProfile2_get_Description(This,bstrDescription)	\
    (This)->lpVtbl -> get_Description(This,bstrDescription)

#define IWMEncProfile2_get_MediaCount(This,enumType,piCount)	\
    (This)->lpVtbl -> get_MediaCount(This,enumType,piCount)

#define IWMEncProfile2_get_MultipleBitrate(This,pbMBR)	\
    (This)->lpVtbl -> get_MultipleBitrate(This,pbMBR)

#define IWMEncProfile2_get_AudienceCollection(This,ppAudienceCollection)	\
    (This)->lpVtbl -> get_AudienceCollection(This,ppAudienceCollection)

#define IWMEncProfile2_get_MaxPacketSize(This,plMaxPacketSize)	\
    (This)->lpVtbl -> get_MaxPacketSize(This,plMaxPacketSize)

#define IWMEncProfile2_put_MaxPacketSize(This,lMaxPacketSize)	\
    (This)->lpVtbl -> put_MaxPacketSize(This,lMaxPacketSize)


#define IWMEncProfile2_get_ContentType(This,plSrcType)	\
    (This)->lpVtbl -> get_ContentType(This,plSrcType)

#define IWMEncProfile2_put_ContentType(This,lSrcType)	\
    (This)->lpVtbl -> put_ContentType(This,lSrcType)

#define IWMEncProfile2_LoadFromIWMProfile(This,pUnkProfile)	\
    (This)->lpVtbl -> LoadFromIWMProfile(This,pUnkProfile)

#define IWMEncProfile2_LoadFromFile(This,bstrFileName)	\
    (This)->lpVtbl -> LoadFromFile(This,bstrFileName)

#define IWMEncProfile2_LoadFromMemory(This,bstrData)	\
    (This)->lpVtbl -> LoadFromMemory(This,bstrData)

#define IWMEncProfile2_SaveToIWMProfile(This,pUnkProfile)	\
    (This)->lpVtbl -> SaveToIWMProfile(This,pUnkProfile)

#define IWMEncProfile2_SaveToFile(This,bstrFileName)	\
    (This)->lpVtbl -> SaveToFile(This,bstrFileName)

#define IWMEncProfile2_SaveToMemory(This,pbstrData)	\
    (This)->lpVtbl -> SaveToMemory(This,pbstrData)

#define IWMEncProfile2_Clone(This,pObj)	\
    (This)->lpVtbl -> Clone(This,pObj)

#define IWMEncProfile2_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IWMEncProfile2_get_AudienceCount(This,plCount)	\
    (This)->lpVtbl -> get_AudienceCount(This,plCount)

#define IWMEncProfile2_get_Audience(This,lIndex,ppAudience)	\
    (This)->lpVtbl -> get_Audience(This,lIndex,ppAudience)

#define IWMEncProfile2_AddAudience(This,lBitrate,ppAudience)	\
    (This)->lpVtbl -> AddAudience(This,lBitrate,ppAudience)

#define IWMEncProfile2_DeleteAudience(This,lIndex)	\
    (This)->lpVtbl -> DeleteAudience(This,lIndex)

#define IWMEncProfile2_get_ValidateMode(This,pfValidate)	\
    (This)->lpVtbl -> get_ValidateMode(This,pfValidate)

#define IWMEncProfile2_put_ValidateMode(This,fValidate)	\
    (This)->lpVtbl -> put_ValidateMode(This,fValidate)

#define IWMEncProfile2_Validate(This)	\
    (This)->lpVtbl -> Validate(This)

#define IWMEncProfile2_get_CompatibilityMode(This,penumCompat)	\
    (This)->lpVtbl -> get_CompatibilityMode(This,penumCompat)

#define IWMEncProfile2_put_CompatibilityMode(This,enumCompat)	\
    (This)->lpVtbl -> put_CompatibilityMode(This,enumCompat)

#define IWMEncProfile2_get_VBRMode(This,enumSrcType,iRenderSite,penumVBR)	\
    (This)->lpVtbl -> get_VBRMode(This,enumSrcType,iRenderSite,penumVBR)

#define IWMEncProfile2_put_VBRMode(This,enumSrcType,iRenderSite,enumVBR)	\
    (This)->lpVtbl -> put_VBRMode(This,enumSrcType,iRenderSite,enumVBR)

#define IWMEncProfile2_put_ProfileName(This,bstrName)	\
    (This)->lpVtbl -> put_ProfileName(This,bstrName)

#define IWMEncProfile2_get_ProfileName(This,pbstrName)	\
    (This)->lpVtbl -> get_ProfileName(This,pbstrName)

#define IWMEncProfile2_put_ProfileDescription(This,bstrDescription)	\
    (This)->lpVtbl -> put_ProfileDescription(This,bstrDescription)

#define IWMEncProfile2_get_ProfileDescription(This,pbstrDescription)	\
    (This)->lpVtbl -> get_ProfileDescription(This,pbstrDescription)

#define IWMEncProfile2_get_AudioCodecCount(This,plAudioCodecCount)	\
    (This)->lpVtbl -> get_AudioCodecCount(This,plAudioCodecCount)

#define IWMEncProfile2_EnumAudioCodec(This,lCodecIndex,pvarName,lFormatTag)	\
    (This)->lpVtbl -> EnumAudioCodec(This,lCodecIndex,pvarName,lFormatTag)

#define IWMEncProfile2_get_AudioFormatCount(This,lCodecIndex,plAudioFormatCount)	\
    (This)->lpVtbl -> get_AudioFormatCount(This,lCodecIndex,plAudioFormatCount)

#define IWMEncProfile2_EnumAudioFormat(This,lCodecIndex,lFormatIndex,pvarName,pvarSamplingRate,pvarNChannels,pvarBitsPerSample,plBitrate)	\
    (This)->lpVtbl -> EnumAudioFormat(This,lCodecIndex,lFormatIndex,pvarName,pvarSamplingRate,pvarNChannels,pvarBitsPerSample,plBitrate)

#define IWMEncProfile2_get_VideoCodecCount(This,plVideoCodecCount)	\
    (This)->lpVtbl -> get_VideoCodecCount(This,plVideoCodecCount)

#define IWMEncProfile2_EnumVideoCodec(This,lCodecIndex,pvarName,lFourCC)	\
    (This)->lpVtbl -> EnumVideoCodec(This,lCodecIndex,pvarName,lFourCC)

#define IWMEncProfile2_GetCodecIndexFromFourCC(This,enumSrcType,lFourCC,plIndex)	\
    (This)->lpVtbl -> GetCodecIndexFromFourCC(This,enumSrcType,lFourCC,plIndex)

#define IWMEncProfile2_GetCodecFourCCFromIndex(This,enumSrcType,lIndex,plFourCC)	\
    (This)->lpVtbl -> GetCodecFourCCFromIndex(This,enumSrcType,lIndex,plFourCC)

#define IWMEncProfile2_get_LanguageCount(This,enumSrcType,iRenderSite,plLanguageCount)	\
    (This)->lpVtbl -> get_LanguageCount(This,enumSrcType,iRenderSite,plLanguageCount)

#define IWMEncProfile2_get_Language(This,enumSrcType,iRenderSite,lLanguageIndex,lcidLanguage)	\
    (This)->lpVtbl -> get_Language(This,enumSrcType,iRenderSite,lLanguageIndex,lcidLanguage)

#define IWMEncProfile2_AddLanguage(This,enumSrcType,iRenderSite,lcidLanguage)	\
    (This)->lpVtbl -> AddLanguage(This,enumSrcType,iRenderSite,lcidLanguage)

#define IWMEncProfile2_RemoveLanguage(This,enumSrcType,iRenderSite,lcidLanguage)	\
    (This)->lpVtbl -> RemoveLanguage(This,enumSrcType,iRenderSite,lcidLanguage)

#define IWMEncProfile2_get_BroadcastMode(This,penumBroadcastMode)	\
    (This)->lpVtbl -> get_BroadcastMode(This,penumBroadcastMode)

#define IWMEncProfile2_put_BroadcastMode(This,enumBroadcastMode)	\
    (This)->lpVtbl -> put_BroadcastMode(This,enumBroadcastMode)

#define IWMEncProfile2_DetectCompatibility(This,penumCompat)	\
    (This)->lpVtbl -> DetectCompatibility(This,penumCompat)

#define IWMEncProfile2_Merge(This,pWMEncProfileObj)	\
    (This)->lpVtbl -> Merge(This,pWMEncProfileObj)

#define IWMEncProfile2_Compare(This,pCompObj,pfSubset,pfEqual)	\
    (This)->lpVtbl -> Compare(This,pCompObj,pfSubset,pfEqual)

#define IWMEncProfile2_get_InterlaceMode(This,iRenderSiteIndex,pfInterlaceMode)	\
    (This)->lpVtbl -> get_InterlaceMode(This,iRenderSiteIndex,pfInterlaceMode)

#define IWMEncProfile2_put_InterlaceMode(This,iRenderSiteIndex,fInterlaceMode)	\
    (This)->lpVtbl -> put_InterlaceMode(This,iRenderSiteIndex,fInterlaceMode)

#define IWMEncProfile2_get_NonSquarePixelMode(This,iRenderSiteIndex,pfNonSquarePixelMode)	\
    (This)->lpVtbl -> get_NonSquarePixelMode(This,iRenderSiteIndex,pfNonSquarePixelMode)

#define IWMEncProfile2_put_NonSquarePixelMode(This,iRenderSiteIndex,fNonSquarePixelMode)	\
    (This)->lpVtbl -> put_NonSquarePixelMode(This,iRenderSiteIndex,fNonSquarePixelMode)

#define IWMEncProfile2_get_EnableTimecode(This,iRenderSiteIndex,pfTimecode)	\
    (This)->lpVtbl -> get_EnableTimecode(This,iRenderSiteIndex,pfTimecode)

#define IWMEncProfile2_put_EnableTimecode(This,iRenderSiteIndex,fTimecode)	\
    (This)->lpVtbl -> put_EnableTimecode(This,iRenderSiteIndex,fTimecode)

#define IWMEncProfile2_get_MinPacketSize(This,plMinPacketSize)	\
    (This)->lpVtbl -> get_MinPacketSize(This,plMinPacketSize)

#define IWMEncProfile2_put_MinPacketSize(This,lMinPacketSize)	\
    (This)->lpVtbl -> put_MinPacketSize(This,lMinPacketSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_ContentType_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ long *plSrcType);


void __RPC_STUB IWMEncProfile2_get_ContentType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_ContentType_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lSrcType);


void __RPC_STUB IWMEncProfile2_put_ContentType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_LoadFromIWMProfile_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ IUnknown *pUnkProfile);


void __RPC_STUB IWMEncProfile2_LoadFromIWMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_LoadFromFile_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncProfile2_LoadFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_LoadFromMemory_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ BSTR bstrData);


void __RPC_STUB IWMEncProfile2_LoadFromMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_SaveToIWMProfile_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ IUnknown **pUnkProfile);


void __RPC_STUB IWMEncProfile2_SaveToIWMProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_SaveToFile_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB IWMEncProfile2_SaveToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_SaveToMemory_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ BSTR *pbstrData);


void __RPC_STUB IWMEncProfile2_SaveToMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_Clone_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ IWMEncProfile2 *pObj);


void __RPC_STUB IWMEncProfile2_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_Clear_Proxy( 
    IWMEncProfile2 * This);


void __RPC_STUB IWMEncProfile2_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_AudienceCount_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncProfile2_get_AudienceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_Audience_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ IWMEncAudienceObj **ppAudience);


void __RPC_STUB IWMEncProfile2_get_Audience_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_AddAudience_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lBitrate,
    /* [retval][out] */ IWMEncAudienceObj **ppAudience);


void __RPC_STUB IWMEncProfile2_AddAudience_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_DeleteAudience_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lIndex);


void __RPC_STUB IWMEncProfile2_DeleteAudience_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_ValidateMode_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ VARIANT_BOOL *pfValidate);


void __RPC_STUB IWMEncProfile2_get_ValidateMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_ValidateMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ VARIANT_BOOL fValidate);


void __RPC_STUB IWMEncProfile2_put_ValidateMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_Validate_Proxy( 
    IWMEncProfile2 * This);


void __RPC_STUB IWMEncProfile2_Validate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_CompatibilityMode_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ WMENC_PROFILE_COMPATIBILITY *penumCompat);


void __RPC_STUB IWMEncProfile2_get_CompatibilityMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_CompatibilityMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_PROFILE_COMPATIBILITY enumCompat);


void __RPC_STUB IWMEncProfile2_put_CompatibilityMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_VBRMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSite,
    /* [retval][out] */ WMENC_PROFILE_VBR_MODE *penumVBR);


void __RPC_STUB IWMEncProfile2_get_VBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_VBRMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSite,
    /* [in] */ WMENC_PROFILE_VBR_MODE enumVBR);


void __RPC_STUB IWMEncProfile2_put_VBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_ProfileName_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IWMEncProfile2_put_ProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_ProfileName_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB IWMEncProfile2_get_ProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_ProfileDescription_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IWMEncProfile2_put_ProfileDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_ProfileDescription_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ BSTR *pbstrDescription);


void __RPC_STUB IWMEncProfile2_get_ProfileDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_AudioCodecCount_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ long *plAudioCodecCount);


void __RPC_STUB IWMEncProfile2_get_AudioCodecCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_EnumAudioCodec_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lCodecIndex,
    /* [out] */ VARIANT *pvarName,
    /* [retval][out] */ long *lFormatTag);


void __RPC_STUB IWMEncProfile2_EnumAudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_AudioFormatCount_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lCodecIndex,
    /* [retval][out] */ long *plAudioFormatCount);


void __RPC_STUB IWMEncProfile2_get_AudioFormatCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_EnumAudioFormat_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lCodecIndex,
    /* [in] */ long lFormatIndex,
    /* [out] */ VARIANT *pvarName,
    /* [out] */ VARIANT *pvarSamplingRate,
    /* [out] */ VARIANT *pvarNChannels,
    /* [out] */ VARIANT *pvarBitsPerSample,
    /* [retval][out] */ long *plBitrate);


void __RPC_STUB IWMEncProfile2_EnumAudioFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_VideoCodecCount_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ long *plVideoCodecCount);


void __RPC_STUB IWMEncProfile2_get_VideoCodecCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_EnumVideoCodec_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lCodecIndex,
    /* [out] */ VARIANT *pvarName,
    /* [retval][out] */ long *lFourCC);


void __RPC_STUB IWMEncProfile2_EnumVideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_GetCodecIndexFromFourCC_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ long lFourCC,
    /* [retval][out] */ long *plIndex);


void __RPC_STUB IWMEncProfile2_GetCodecIndexFromFourCC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_GetCodecFourCCFromIndex_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ long lIndex,
    /* [retval][out] */ long *plFourCC);


void __RPC_STUB IWMEncProfile2_GetCodecFourCCFromIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_LanguageCount_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSite,
    /* [retval][out] */ long *plLanguageCount);


void __RPC_STUB IWMEncProfile2_get_LanguageCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_Language_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSite,
    /* [in] */ long lLanguageIndex,
    /* [retval][out] */ long *lcidLanguage);


void __RPC_STUB IWMEncProfile2_get_Language_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_AddLanguage_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSite,
    /* [in] */ long lcidLanguage);


void __RPC_STUB IWMEncProfile2_AddLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_RemoveLanguage_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ short iRenderSite,
    /* [in] */ long lcidLanguage);


void __RPC_STUB IWMEncProfile2_RemoveLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_BroadcastMode_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ WMENC_PROFILE_BROADCAST_MODE *penumBroadcastMode);


void __RPC_STUB IWMEncProfile2_get_BroadcastMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_BroadcastMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ WMENC_PROFILE_BROADCAST_MODE enumBroadcastMode);


void __RPC_STUB IWMEncProfile2_put_BroadcastMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_DetectCompatibility_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ WMENC_PROFILE_COMPATIBILITY *penumCompat);


void __RPC_STUB IWMEncProfile2_DetectCompatibility_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_Merge_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ IWMEncProfile2 *pWMEncProfileObj);


void __RPC_STUB IWMEncProfile2_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_Compare_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ IWMEncProfile2 *pCompObj,
    /* [out] */ VARIANT_BOOL *pfSubset,
    /* [retval][out] */ VARIANT_BOOL *pfEqual);


void __RPC_STUB IWMEncProfile2_Compare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_InterlaceMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ VARIANT_BOOL *pfInterlaceMode);


void __RPC_STUB IWMEncProfile2_get_InterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_InterlaceMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ VARIANT_BOOL fInterlaceMode);


void __RPC_STUB IWMEncProfile2_put_InterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_NonSquarePixelMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ VARIANT_BOOL *pfNonSquarePixelMode);


void __RPC_STUB IWMEncProfile2_get_NonSquarePixelMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_NonSquarePixelMode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ VARIANT_BOOL fNonSquarePixelMode);


void __RPC_STUB IWMEncProfile2_put_NonSquarePixelMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_EnableTimecode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ short iRenderSiteIndex,
    /* [retval][out] */ VARIANT_BOOL *pfTimecode);


void __RPC_STUB IWMEncProfile2_get_EnableTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_EnableTimecode_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ short iRenderSiteIndex,
    /* [in] */ VARIANT_BOOL fTimecode);


void __RPC_STUB IWMEncProfile2_put_EnableTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_get_MinPacketSize_Proxy( 
    IWMEncProfile2 * This,
    /* [retval][out] */ long *plMinPacketSize);


void __RPC_STUB IWMEncProfile2_get_MinPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncProfile2_put_MinPacketSize_Proxy( 
    IWMEncProfile2 * This,
    /* [in] */ long lMinPacketSize);


void __RPC_STUB IWMEncProfile2_put_MinPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncProfile2_INTERFACE_DEFINED__ */


#ifndef __IWMEncWatermarkCollection_INTERFACE_DEFINED__
#define __IWMEncWatermarkCollection_INTERFACE_DEFINED__

/* interface IWMEncWatermarkCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncWatermarkCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("252F3335-53D0-47d9-94C6-C38736F1BA6A")
    IWMEncWatermarkCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long iIndex,
            /* [out] */ VARIANT *pvarCLSID,
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncWatermarkCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncWatermarkCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncWatermarkCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncWatermarkCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncWatermarkCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncWatermarkCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncWatermarkCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncWatermarkCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_length )( 
            IWMEncWatermarkCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncWatermarkCollection * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncWatermarkCollection * This,
            /* [in] */ long iIndex,
            /* [out] */ VARIANT *pvarCLSID,
            /* [retval][out] */ BSTR *pbstrName);
        
        END_INTERFACE
    } IWMEncWatermarkCollectionVtbl;

    interface IWMEncWatermarkCollection
    {
        CONST_VTBL struct IWMEncWatermarkCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncWatermarkCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncWatermarkCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncWatermarkCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncWatermarkCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncWatermarkCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncWatermarkCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncWatermarkCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncWatermarkCollection_get_length(This,plCount)	\
    (This)->lpVtbl -> get_length(This,plCount)

#define IWMEncWatermarkCollection_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncWatermarkCollection_Item(This,iIndex,pvarCLSID,pbstrName)	\
    (This)->lpVtbl -> Item(This,iIndex,pvarCLSID,pbstrName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncWatermarkCollection_get_length_Proxy( 
    IWMEncWatermarkCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncWatermarkCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncWatermarkCollection_get_Count_Proxy( 
    IWMEncWatermarkCollection * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncWatermarkCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncWatermarkCollection_Item_Proxy( 
    IWMEncWatermarkCollection * This,
    /* [in] */ long iIndex,
    /* [out] */ VARIANT *pvarCLSID,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB IWMEncWatermarkCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncWatermarkCollection_INTERFACE_DEFINED__ */


#ifndef __IWMEncFileSet_INTERFACE_DEFINED__
#define __IWMEncFileSet_INTERFACE_DEFINED__

/* interface IWMEncFileSet */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncFileSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54B54844-4F93-458e-AC10-45FFED1D1816")
    IWMEncFileSet : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [out] */ VARIANT *pvarFileName,
            /* [retval][out] */ BSTR *pbstrFileURL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrFileURL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long lIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ long lMove,
            /* [in] */ long lInFrontOf) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInput( 
            /* [in] */ long lIndex,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrURL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Time( 
            /* [retval][out] */ WMENC_LONGLONG *pllSendTime) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Time( 
            /* [in] */ WMENC_LONGLONG llMsSendTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncFileSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncFileSet * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncFileSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncFileSet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncFileSet * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncFileSet * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncFileSet * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncFileSet * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncFileSet * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncFileSet * This,
            /* [in] */ long lIndex,
            /* [out] */ VARIANT *pvarFileName,
            /* [retval][out] */ BSTR *pbstrFileURL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncFileSet * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrFileURL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncFileSet * This,
            /* [in] */ long lIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncFileSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IWMEncFileSet * This,
            /* [in] */ long lMove,
            /* [in] */ long lInFrontOf);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInput )( 
            IWMEncFileSet * This,
            /* [in] */ long lIndex,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrURL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Time )( 
            IWMEncFileSet * This,
            /* [retval][out] */ WMENC_LONGLONG *pllSendTime);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Time )( 
            IWMEncFileSet * This,
            /* [in] */ WMENC_LONGLONG llMsSendTime);
        
        END_INTERFACE
    } IWMEncFileSetVtbl;

    interface IWMEncFileSet
    {
        CONST_VTBL struct IWMEncFileSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncFileSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncFileSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncFileSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncFileSet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncFileSet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncFileSet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncFileSet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncFileSet_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncFileSet_Item(This,lIndex,pvarFileName,pbstrFileURL)	\
    (This)->lpVtbl -> Item(This,lIndex,pvarFileName,pbstrFileURL)

#define IWMEncFileSet_Add(This,bstrFileName,bstrFileURL)	\
    (This)->lpVtbl -> Add(This,bstrFileName,bstrFileURL)

#define IWMEncFileSet_Remove(This,lIndex)	\
    (This)->lpVtbl -> Remove(This,lIndex)

#define IWMEncFileSet_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define IWMEncFileSet_Move(This,lMove,lInFrontOf)	\
    (This)->lpVtbl -> Move(This,lMove,lInFrontOf)

#define IWMEncFileSet_SetInput(This,lIndex,bstrFileName,bstrURL)	\
    (This)->lpVtbl -> SetInput(This,lIndex,bstrFileName,bstrURL)

#define IWMEncFileSet_get_Time(This,pllSendTime)	\
    (This)->lpVtbl -> get_Time(This,pllSendTime)

#define IWMEncFileSet_put_Time(This,llMsSendTime)	\
    (This)->lpVtbl -> put_Time(This,llMsSendTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_get_Count_Proxy( 
    IWMEncFileSet * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncFileSet_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_Item_Proxy( 
    IWMEncFileSet * This,
    /* [in] */ long lIndex,
    /* [out] */ VARIANT *pvarFileName,
    /* [retval][out] */ BSTR *pbstrFileURL);


void __RPC_STUB IWMEncFileSet_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_Add_Proxy( 
    IWMEncFileSet * This,
    /* [in] */ BSTR bstrFileName,
    /* [in] */ BSTR bstrFileURL);


void __RPC_STUB IWMEncFileSet_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_Remove_Proxy( 
    IWMEncFileSet * This,
    /* [in] */ long lIndex);


void __RPC_STUB IWMEncFileSet_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_RemoveAll_Proxy( 
    IWMEncFileSet * This);


void __RPC_STUB IWMEncFileSet_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_Move_Proxy( 
    IWMEncFileSet * This,
    /* [in] */ long lMove,
    /* [in] */ long lInFrontOf);


void __RPC_STUB IWMEncFileSet_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_SetInput_Proxy( 
    IWMEncFileSet * This,
    /* [in] */ long lIndex,
    /* [in] */ BSTR bstrFileName,
    /* [in] */ BSTR bstrURL);


void __RPC_STUB IWMEncFileSet_SetInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_get_Time_Proxy( 
    IWMEncFileSet * This,
    /* [retval][out] */ WMENC_LONGLONG *pllSendTime);


void __RPC_STUB IWMEncFileSet_get_Time_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFileSet_put_Time_Proxy( 
    IWMEncFileSet * This,
    /* [in] */ WMENC_LONGLONG llMsSendTime);


void __RPC_STUB IWMEncFileSet_put_Time_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncFileSet_INTERFACE_DEFINED__ */


#ifndef __IWMEncFileTransferSource_INTERFACE_DEFINED__
#define __IWMEncFileTransferSource_INTERFACE_DEFINED__

/* interface IWMEncFileTransferSource */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWMEncFileTransferSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E452E5A-B739-452f-A4D2-5D84FD524916")
    IWMEncFileTransferSource : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncFileSet **ppEntry) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [retval][out] */ IWMEncFileSet **ppHTMLDataGroup) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long lIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ long lMove,
            /* [in] */ long lInFrontOf) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserDrivenMode( 
            /* [retval][out] */ VARIANT_BOOL *pfSendMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserDrivenMode( 
            /* [in] */ VARIANT_BOOL fSendMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ IWMEncFileSet *pIWMEncFileSet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ WMENC_SOURCE_STATE *penumSourceState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Active( 
            /* [retval][out] */ IWMEncFileSet **ppIWMEncFileSet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncFileTransferSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncFileTransferSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncFileTransferSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncFileTransferSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncFileTransferSource * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncFileTransferSource * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncFileTransferSource * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncFileTransferSource * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWMEncFileTransferSource * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IWMEncFileTransferSource * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ IWMEncFileSet **ppEntry);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWMEncFileTransferSource * This,
            /* [retval][out] */ IWMEncFileSet **ppHTMLDataGroup);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWMEncFileTransferSource * This,
            /* [in] */ long lIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IWMEncFileTransferSource * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IWMEncFileTransferSource * This,
            /* [in] */ long lMove,
            /* [in] */ long lInFrontOf);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserDrivenMode )( 
            IWMEncFileTransferSource * This,
            /* [retval][out] */ VARIANT_BOOL *pfSendMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UserDrivenMode )( 
            IWMEncFileTransferSource * This,
            /* [in] */ VARIANT_BOOL fSendMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            IWMEncFileTransferSource * This,
            /* [in] */ IWMEncFileSet *pIWMEncFileSet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Abort )( 
            IWMEncFileTransferSource * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            IWMEncFileTransferSource * This,
            /* [retval][out] */ WMENC_SOURCE_STATE *penumSourceState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Active )( 
            IWMEncFileTransferSource * This,
            /* [retval][out] */ IWMEncFileSet **ppIWMEncFileSet);
        
        END_INTERFACE
    } IWMEncFileTransferSourceVtbl;

    interface IWMEncFileTransferSource
    {
        CONST_VTBL struct IWMEncFileTransferSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncFileTransferSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncFileTransferSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncFileTransferSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncFileTransferSource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncFileTransferSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncFileTransferSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncFileTransferSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncFileTransferSource_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IWMEncFileTransferSource_Item(This,lIndex,ppEntry)	\
    (This)->lpVtbl -> Item(This,lIndex,ppEntry)

#define IWMEncFileTransferSource_Add(This,ppHTMLDataGroup)	\
    (This)->lpVtbl -> Add(This,ppHTMLDataGroup)

#define IWMEncFileTransferSource_Remove(This,lIndex)	\
    (This)->lpVtbl -> Remove(This,lIndex)

#define IWMEncFileTransferSource_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define IWMEncFileTransferSource_Move(This,lMove,lInFrontOf)	\
    (This)->lpVtbl -> Move(This,lMove,lInFrontOf)

#define IWMEncFileTransferSource_get_UserDrivenMode(This,pfSendMode)	\
    (This)->lpVtbl -> get_UserDrivenMode(This,pfSendMode)

#define IWMEncFileTransferSource_put_UserDrivenMode(This,fSendMode)	\
    (This)->lpVtbl -> put_UserDrivenMode(This,fSendMode)

#define IWMEncFileTransferSource_Send(This,pIWMEncFileSet)	\
    (This)->lpVtbl -> Send(This,pIWMEncFileSet)

#define IWMEncFileTransferSource_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define IWMEncFileTransferSource_get_State(This,penumSourceState)	\
    (This)->lpVtbl -> get_State(This,penumSourceState)

#define IWMEncFileTransferSource_get_Active(This,ppIWMEncFileSet)	\
    (This)->lpVtbl -> get_Active(This,ppIWMEncFileSet)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_get_Count_Proxy( 
    IWMEncFileTransferSource * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IWMEncFileTransferSource_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_Item_Proxy( 
    IWMEncFileTransferSource * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ IWMEncFileSet **ppEntry);


void __RPC_STUB IWMEncFileTransferSource_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_Add_Proxy( 
    IWMEncFileTransferSource * This,
    /* [retval][out] */ IWMEncFileSet **ppHTMLDataGroup);


void __RPC_STUB IWMEncFileTransferSource_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_Remove_Proxy( 
    IWMEncFileTransferSource * This,
    /* [in] */ long lIndex);


void __RPC_STUB IWMEncFileTransferSource_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_RemoveAll_Proxy( 
    IWMEncFileTransferSource * This);


void __RPC_STUB IWMEncFileTransferSource_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_Move_Proxy( 
    IWMEncFileTransferSource * This,
    /* [in] */ long lMove,
    /* [in] */ long lInFrontOf);


void __RPC_STUB IWMEncFileTransferSource_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_get_UserDrivenMode_Proxy( 
    IWMEncFileTransferSource * This,
    /* [retval][out] */ VARIANT_BOOL *pfSendMode);


void __RPC_STUB IWMEncFileTransferSource_get_UserDrivenMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_put_UserDrivenMode_Proxy( 
    IWMEncFileTransferSource * This,
    /* [in] */ VARIANT_BOOL fSendMode);


void __RPC_STUB IWMEncFileTransferSource_put_UserDrivenMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_Send_Proxy( 
    IWMEncFileTransferSource * This,
    /* [in] */ IWMEncFileSet *pIWMEncFileSet);


void __RPC_STUB IWMEncFileTransferSource_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_Abort_Proxy( 
    IWMEncFileTransferSource * This);


void __RPC_STUB IWMEncFileTransferSource_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_get_State_Proxy( 
    IWMEncFileTransferSource * This,
    /* [retval][out] */ WMENC_SOURCE_STATE *penumSourceState);


void __RPC_STUB IWMEncFileTransferSource_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncFileTransferSource_get_Active_Proxy( 
    IWMEncFileTransferSource * This,
    /* [retval][out] */ IWMEncFileSet **ppIWMEncFileSet);


void __RPC_STUB IWMEncFileTransferSource_get_Active_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncFileTransferSource_INTERFACE_DEFINED__ */


#ifndef __IWMEncStreamEdit_INTERFACE_DEFINED__
#define __IWMEncStreamEdit_INTERFACE_DEFINED__

/* interface IWMEncStreamEdit */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMEncStreamEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AE18C57-DB2E-11D2-A34A-006097C4E476")
    IWMEncStreamEdit : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputFile( 
            /* [retval][out] */ BSTR *pbstrOutputFile) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputFile( 
            /* [in] */ BSTR bstrOutputFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddStream( 
            /* [in] */ BSTR bstrInputFile,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lInputAudienceIndex,
            /* [in] */ short iInputRenderSite,
            /* [in] */ long lInputLangId,
            /* [in] */ long lOutputAudienceIndex,
            /* [in] */ short iOutputRenderSite) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllStreams( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Validate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputProfile( 
            /* [retval][out] */ IWMEncProfile2 **ppIWMEncProfile2) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RunState( 
            /* [retval][out] */ WMENC_BASICEDIT_STATE *penumState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStream( 
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lOutputAudienceIndex,
            /* [in] */ short iOutputRenderSite,
            /* [in] */ long lcidLang,
            /* [out] */ VARIANT *pvarInputFile,
            /* [out] */ VARIANT *pvarInputAudienceIndex,
            /* [retval][out] */ short *piInputRenderSite) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressPercent( 
            /* [retval][out] */ long *plProgressPercent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMEncStreamEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMEncStreamEdit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMEncStreamEdit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMEncStreamEdit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMEncStreamEdit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMEncStreamEdit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMEncStreamEdit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMEncStreamEdit * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputFile )( 
            IWMEncStreamEdit * This,
            /* [retval][out] */ BSTR *pbstrOutputFile);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputFile )( 
            IWMEncStreamEdit * This,
            /* [in] */ BSTR bstrOutputFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddStream )( 
            IWMEncStreamEdit * This,
            /* [in] */ BSTR bstrInputFile,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lInputAudienceIndex,
            /* [in] */ short iInputRenderSite,
            /* [in] */ long lInputLangId,
            /* [in] */ long lOutputAudienceIndex,
            /* [in] */ short iOutputRenderSite);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllStreams )( 
            IWMEncStreamEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Validate )( 
            IWMEncStreamEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IWMEncStreamEdit * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IWMEncStreamEdit * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputProfile )( 
            IWMEncStreamEdit * This,
            /* [retval][out] */ IWMEncProfile2 **ppIWMEncProfile2);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunState )( 
            IWMEncStreamEdit * This,
            /* [retval][out] */ WMENC_BASICEDIT_STATE *penumState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStream )( 
            IWMEncStreamEdit * This,
            /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
            /* [in] */ long lOutputAudienceIndex,
            /* [in] */ short iOutputRenderSite,
            /* [in] */ long lcidLang,
            /* [out] */ VARIANT *pvarInputFile,
            /* [out] */ VARIANT *pvarInputAudienceIndex,
            /* [retval][out] */ short *piInputRenderSite);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgressPercent )( 
            IWMEncStreamEdit * This,
            /* [retval][out] */ long *plProgressPercent);
        
        END_INTERFACE
    } IWMEncStreamEditVtbl;

    interface IWMEncStreamEdit
    {
        CONST_VTBL struct IWMEncStreamEditVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMEncStreamEdit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMEncStreamEdit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMEncStreamEdit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMEncStreamEdit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMEncStreamEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMEncStreamEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMEncStreamEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMEncStreamEdit_get_OutputFile(This,pbstrOutputFile)	\
    (This)->lpVtbl -> get_OutputFile(This,pbstrOutputFile)

#define IWMEncStreamEdit_put_OutputFile(This,bstrOutputFile)	\
    (This)->lpVtbl -> put_OutputFile(This,bstrOutputFile)

#define IWMEncStreamEdit_AddStream(This,bstrInputFile,enumSrcType,lInputAudienceIndex,iInputRenderSite,lInputLangId,lOutputAudienceIndex,iOutputRenderSite)	\
    (This)->lpVtbl -> AddStream(This,bstrInputFile,enumSrcType,lInputAudienceIndex,iInputRenderSite,lInputLangId,lOutputAudienceIndex,iOutputRenderSite)

#define IWMEncStreamEdit_RemoveAllStreams(This)	\
    (This)->lpVtbl -> RemoveAllStreams(This)

#define IWMEncStreamEdit_Validate(This)	\
    (This)->lpVtbl -> Validate(This)

#define IWMEncStreamEdit_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IWMEncStreamEdit_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWMEncStreamEdit_get_OutputProfile(This,ppIWMEncProfile2)	\
    (This)->lpVtbl -> get_OutputProfile(This,ppIWMEncProfile2)

#define IWMEncStreamEdit_get_RunState(This,penumState)	\
    (This)->lpVtbl -> get_RunState(This,penumState)

#define IWMEncStreamEdit_GetStream(This,enumSrcType,lOutputAudienceIndex,iOutputRenderSite,lcidLang,pvarInputFile,pvarInputAudienceIndex,piInputRenderSite)	\
    (This)->lpVtbl -> GetStream(This,enumSrcType,lOutputAudienceIndex,iOutputRenderSite,lcidLang,pvarInputFile,pvarInputAudienceIndex,piInputRenderSite)

#define IWMEncStreamEdit_get_ProgressPercent(This,plProgressPercent)	\
    (This)->lpVtbl -> get_ProgressPercent(This,plProgressPercent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_get_OutputFile_Proxy( 
    IWMEncStreamEdit * This,
    /* [retval][out] */ BSTR *pbstrOutputFile);


void __RPC_STUB IWMEncStreamEdit_get_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_put_OutputFile_Proxy( 
    IWMEncStreamEdit * This,
    /* [in] */ BSTR bstrOutputFile);


void __RPC_STUB IWMEncStreamEdit_put_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_AddStream_Proxy( 
    IWMEncStreamEdit * This,
    /* [in] */ BSTR bstrInputFile,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ long lInputAudienceIndex,
    /* [in] */ short iInputRenderSite,
    /* [in] */ long lInputLangId,
    /* [in] */ long lOutputAudienceIndex,
    /* [in] */ short iOutputRenderSite);


void __RPC_STUB IWMEncStreamEdit_AddStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_RemoveAllStreams_Proxy( 
    IWMEncStreamEdit * This);


void __RPC_STUB IWMEncStreamEdit_RemoveAllStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_Validate_Proxy( 
    IWMEncStreamEdit * This);


void __RPC_STUB IWMEncStreamEdit_Validate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_Start_Proxy( 
    IWMEncStreamEdit * This);


void __RPC_STUB IWMEncStreamEdit_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_Stop_Proxy( 
    IWMEncStreamEdit * This);


void __RPC_STUB IWMEncStreamEdit_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_get_OutputProfile_Proxy( 
    IWMEncStreamEdit * This,
    /* [retval][out] */ IWMEncProfile2 **ppIWMEncProfile2);


void __RPC_STUB IWMEncStreamEdit_get_OutputProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_get_RunState_Proxy( 
    IWMEncStreamEdit * This,
    /* [retval][out] */ WMENC_BASICEDIT_STATE *penumState);


void __RPC_STUB IWMEncStreamEdit_get_RunState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_GetStream_Proxy( 
    IWMEncStreamEdit * This,
    /* [in] */ WMENC_SOURCE_TYPE enumSrcType,
    /* [in] */ long lOutputAudienceIndex,
    /* [in] */ short iOutputRenderSite,
    /* [in] */ long lcidLang,
    /* [out] */ VARIANT *pvarInputFile,
    /* [out] */ VARIANT *pvarInputAudienceIndex,
    /* [retval][out] */ short *piInputRenderSite);


void __RPC_STUB IWMEncStreamEdit_GetStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMEncStreamEdit_get_ProgressPercent_Proxy( 
    IWMEncStreamEdit * This,
    /* [retval][out] */ long *plProgressPercent);


void __RPC_STUB IWMEncStreamEdit_get_ProgressPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMEncStreamEdit_INTERFACE_DEFINED__ */



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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWMEncoderEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWMEncoderEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWMEncoderEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWMEncoderEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWMEncoderEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWMEncoderEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWMEncoderEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWMEncoderEventsVtbl;

    interface _IWMEncoderEvents
    {
        CONST_VTBL struct _IWMEncoderEventsVtbl *lpVtbl;
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


#ifndef ___IWMEncBasicEditEvents_DISPINTERFACE_DEFINED__
#define ___IWMEncBasicEditEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWMEncBasicEditEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWMEncBasicEditEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AB5AF3CC-9347-4dc1-92E3-B96537B8C446")
    _IWMEncBasicEditEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWMEncBasicEditEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWMEncBasicEditEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWMEncBasicEditEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWMEncBasicEditEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWMEncBasicEditEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWMEncBasicEditEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWMEncBasicEditEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWMEncBasicEditEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWMEncBasicEditEventsVtbl;

    interface _IWMEncBasicEditEvents
    {
        CONST_VTBL struct _IWMEncBasicEditEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWMEncBasicEditEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWMEncBasicEditEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWMEncBasicEditEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWMEncBasicEditEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWMEncBasicEditEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWMEncBasicEditEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWMEncBasicEditEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWMEncBasicEditEvents_DISPINTERFACE_DEFINED__ */


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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWMEncoderAppEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWMEncoderAppEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWMEncoderAppEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWMEncoderAppEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWMEncoderAppEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWMEncoderAppEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWMEncoderAppEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWMEncoderAppEventsVtbl;

    interface _IWMEncoderAppEvents
    {
        CONST_VTBL struct _IWMEncoderAppEventsVtbl *lpVtbl;
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

EXTERN_C const CLSID CLSID_WMEncVideoSizePage;

#ifdef __cplusplus

class DECLSPEC_UUID("94E15FA1-68AF-4281-A67C-7D5A086169F2")
WMEncVideoSizePage;
#endif

EXTERN_C const CLSID CLSID_WMEncProcessingPage;

#ifdef __cplusplus

class DECLSPEC_UUID("12594540-9B58-4fe9-A7EA-8A10F641B049")
WMEncProcessingPage;
#endif

EXTERN_C const CLSID CLSID_WMEncPluginsPage;

#ifdef __cplusplus

class DECLSPEC_UUID("A9B377B6-7D6F-4f37-B208-2AF6DC85E608")
WMEncPluginsPage;
#endif

EXTERN_C const CLSID CLSID_WMEncDRMPage;

#ifdef __cplusplus

class DECLSPEC_UUID("FCC970B8-86D5-4a30-AC33-B76679BDF970")
WMEncDRMPage;
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

EXTERN_C const CLSID CLSID_WMEncBasicEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("9571D958-9BCF-4e19-A374-FC2F321C8F61")
WMEncBasicEdit;
#endif

EXTERN_C const CLSID CLSID_WMEncStreamEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("216D96AA-9109-472e-8CDD-821C952C4D6E")
WMEncStreamEdit;
#endif

EXTERN_C const CLSID CLSID_WMEncProfile2;

#ifdef __cplusplus

class DECLSPEC_UUID("A5AC04E7-3E13-48CE-A43F-9FBA59DB1544")
WMEncProfile2;
#endif
#endif /* __WMEncoderLib_LIBRARY_DEFINED__ */

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


