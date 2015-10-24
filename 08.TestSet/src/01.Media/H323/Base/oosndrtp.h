/*
 * Copyright (C) 2004 by Objective Systems, Inc.
 *
 * This software is furnished under an open source license and may be 
 * used and copied only in accordance with the terms of this license. 
 * The text of the license may generally be found in the root 
 * directory of this installation in the LICENSE.txt file.  It 
 * can also be viewed online at the following URL:
 *
 *   http://www.obj-sys.com/open/license.html
 *
 * Any redistributions of this file including modified versions must 
 * maintain this copyright notice.
 *
 *****************************************************************************/

/**
 * @file oosndrtp.h 
 * This file contains functions to read from sound device and playback.
 * It also provides a wrapper for oRTP function calls and creates threads
 * for receiving and sending rtp packets.
 */

#ifndef _OO_SNDRTP_H_
#define _OO_SNDRTP_H_


#include <stdlib.h>
#include "ootypes.h"


#ifndef _WIN32
#include <dlfcn.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXTERN
#ifdef _WIN32
#define EXTERN __declspec(dllexport)
#else
#define EXTERN
#endif /* _WIN32 */
#endif

/**
 * @defgroup pluginInterface Media plug-in Interface definitions
 * @{
 */
/** Signature for function to Create Tx RTP channel*/
typedef int (*MediaAPI_CreateTxRTPChan)(int* channelId, char * destip, int port);
/** Signature for function to Close Tx RTP channel*/
typedef int (*MediaAPI_CloseTxRTPChan)(int);
/** Signature for function to Create Rx RTP channel*/
typedef int (*MediaAPI_CreateRecvRTPChan)(int* channelId, char* localip, int localport);
/** Signature for function to Close Rx RTP channel*/
typedef int (*MediaAPI_CloseRecvRTPChan)(int);
/** Signature for function to Start transmission of media file */
typedef int (*MediaAPI_StartTxWaveFile)(int channelId, char * filename);
/** Signature for function to Stop transmission of media file*/
typedef int (*MediaAPI_StopTxWaveFile)(int channelId);
/** Signature for function to Start transmitting captured audio from 
 *   microphone
 */
typedef int (*MediaAPI_StartTxMic)(int channelId);
/** Signature for function to Stop transmitting microphone data*/
typedef int (*MediaAPI_StopTxMic)(int channelId);
/** Signature for function to Start receiving rtp data and playback*/
typedef int (*MediaAPI_StartRecvAndPlayback)(int channelId);
/** Signature for function to stop receiving rtp data */
typedef int (*MediaAPI_StopRecvAndPlayback)(int channelId);
/** Signature for function to Initialize the media plug-in*/
typedef int (*MediaAPI_InitializePlugin)();
/**
 * @}
 */

/** 
 * @defgroup media Media plugin support functions
 * @{
 */

/* Media API */

//remarked by tony below [2005.1.17]
/*
#ifdef _WIN32
HMODULE media;
#else
void * media;
#endif*/
//remarked by tony above [2005.1.17]

static MediaAPI_CreateTxRTPChan   FuncPtr_CreateTxRTPChan = 0;
static MediaAPI_CloseTxRTPChan    FuncPtr_CloseTxRTPChan = 0;
static MediaAPI_CreateRecvRTPChan FuncPtr_CreateRecvRTPChan = 0;
static MediaAPI_CloseRecvRTPChan  FuncPtr_CloseRecvRTPChan = 0;
static MediaAPI_StartTxWaveFile   FuncPtr_StartTxWaveFile = 0;
static MediaAPI_StopTxWaveFile    FuncPtr_StopTxWaveFile = 0;
static MediaAPI_StartTxMic        FuncPtr_StartTxMic = 0;
static MediaAPI_StopTxMic         FuncPtr_StopTxMic = 0;
static MediaAPI_StartRecvAndPlayback FuncPtr_StartRecvAndPlayback = 0;
static MediaAPI_StopRecvAndPlayback  FuncPtr_StopRecvAndPlayback = 0;
static MediaAPI_InitializePlugin  FuncPtr_InitializePlugin = 0;


/**
 * Loads the media plugin into the process space.
 * @param context   Pointer to application context.
 * @param name      Name of the media plug-in library.
 *
 * @return          Completion status - 0 on success, -1 on failure
 */
EXTERN int ooLoadSndRTPPlugin(struct ooAppContext* context, char * name);

/**
 * Unloads the plug-in from process space.
 * @param context   Pointer to application context.
 * 
 * @return          Completion status - 0 on success, -1 on failure  
 */
EXTERN int ooReleaseSndRTPPlugin(struct ooAppContext* context);

/**
 * Creates a transmit RTP channel. Basically calls the corresponding function
 * of the plug-in library.
 * @param context    Pointer to application context.
 * @param destip     IP address of the destination endpoint.
 * @param port       Destination port number.
 *
 * @return           Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCreateTransmitRTPChannel
   (struct ooAppContext* context, char * destip, int port);

/**
 * Closes a transmit RTP channel. Basically calls the corresponding function
 * of the plug-in library.
 * @param context    Pointer to application context.
 * 
 * @return           Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCloseTransmitRTPChannel
   (struct ooAppContext* context);

/**
 * Creates a receive RTP channel. Basically calls the corresponding function
 * of the plug-in library.
 * @param context    Pointer to application context.
 * @param localip    IP address of the endpoint where RTP data will be received.
 * @param localport  Port number of the local endpoint
 *
 * @return           Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCreateReceiveRTPChannel
   (struct ooAppContext* context, char* localip, int localport);

/**
 * Closes a receive RTP channel. Basically calls the corresponding function
 * of the plug-in library.
 * @param context    Pointer to application context.
 * 
 * @return           Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCloseReceiveRTPChannel
   (struct ooAppContext* context);

/**
 * Start transmitting a audio file. This calls corresponding function
 * of the plug-in library.
 * @param context     Pointer to application context.
 * @param filename    Name of the file to be played.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooStartTransmitWaveFile
   (struct ooAppContext* context, char * filename);

/**
 * Stop transmission of a audio file. This calls corresponding function
 * of the plug-in library.
 * @param context      Pointer to the application context.
 *
 * @return              Completion status - 0 on success, -1 on failure
 */
EXTERN int ooStopTransmitWaveFile
   (struct ooAppContext* context);

/**
 * Starts capturing audio data from mic and transmits it as rtp stream. This
 * calls corresponding interface function of the plug-in library.
 * @param context     Pointer to application context.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooStartTransmitMic
   (struct ooAppContext* context);

/**
 * Stop transmission of mic audio data. This calls corresponding interface
 * function of the plug-in library.
 * @param context      Pointer to the application context.
 *
 * @return              Completion status - 0 on success, -1 on failure
 */
EXTERN int ooStopTransmitMic
   (struct ooAppContext* context);

/**
 * Starts receiving rtp stream data and play it on the speakers. This 
 * calls corresponding interface function of the plug-in library.
 * @param context     Pointer to application context.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooStartReceiveAudioAndPlayback
   (struct ooAppContext* context);

/**
 * Stop receiving rtp stream data.This calls corresponding interface function 
 * of the plug-in library.
 * @param context     Pointer to application context.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooStopReceiveAudioAndPlayback
   (struct ooAppContext* context);

/** Not suuported currently */
EXTERN int ooStartReceiveAudioAndRecord
   (struct ooAppContext* context);
/** Not supported currently */
EXTERN int ooStopReceiveAudioAndRecord
   (struct ooAppContext* context);

/**
 * Set local RTP and RTCP addresses for the session. This function 
 * gets next available ports for RTP and RTCP communication and
 * stores them in application context.
 * @param context     Pointer to application context within the stack.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSetLocalRTPAndRTCPAddrs(struct ooAppContext* context);

/**
 * Closes transmit and receive RTP channels, if open. This calls 
 * corresponding interface functions to close the channels.
 * @param context    Pointer to application context.
 *
 * @return           Completion status - 0 on success, -1 on failure
 */
EXTERN int ooRTPShutDown(struct ooAppContext* context);
/** 
 * @} 
 */
#ifdef __cplusplus
}
#endif
#endif
