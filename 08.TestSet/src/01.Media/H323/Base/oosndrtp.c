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

#include "oosndrtp.h"
#include "ooports.h"
#include "oo.h"
#include "Media\oortp.h"

//added by tony below [2005.1.17]
#ifdef _WIN32
HMODULE media;
#else
void * media;
#endif
//added by tony above [2005.1.17]

int ooLoadSndRTPPlugin(struct ooAppContext* context, char * name)
{
   media = 0;
   /* Load the plugin library */
#ifdef _WIN32
   media = LoadLibrary(name);
#else
   media = dlopen(name, RTLD_NOW|RTLD_GLOBAL);
#endif
   if(media == 0)
   {
      OOTRACEERR3(context, "ERROR:Failed to load plug-in library %s", name);
      return OO_FAILED;
   }
   
   /* Retrieve addreses of the plugin interface functions */
#ifdef _WIN32
   FuncPtr_InitializePlugin = (MediaAPI_InitializePlugin) GetProcAddress(media,
                                                         "ooInitializePlugin");
#else
   FuncPtr_InitializePlugin = (MediaAPI_InitializePlugin) dlsym(media, 
                                                         "ooInitializePlugin");
#endif
   if(FuncPtr_InitializePlugin == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooInitializePlugin");
      return OO_FAILED;
   }

#ifdef _WIN32
   FuncPtr_CreateTxRTPChan = (MediaAPI_CreateTxRTPChan) GetProcAddress(media, 
                                                 "ooCreateTransmitRTPChannel");
#else
   FuncPtr_CreateTxRTPChan = (MediaAPI_CreateTxRTPChan) dlsym(media, 
                                                 "ooCreateTransmitRTPChannel");
#endif
   if(FuncPtr_CreateTxRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooCreateTransmitRTPChannel");
      return OO_FAILED;
   }
   
#ifdef _WIN32
   FuncPtr_CloseTxRTPChan = (MediaAPI_CloseTxRTPChan) GetProcAddress(media, 
                                                 "ooCloseTransmitRTPChannel");
#else
   FuncPtr_CloseTxRTPChan = (MediaAPI_CloseTxRTPChan) dlsym(media, 
                                                 "ooCloseTransmitRTPChannel");
#endif
   if(FuncPtr_CloseTxRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooCloseTransmitRTPChannel");
      return OO_FAILED;
   }
   
#ifdef _WIN32
   FuncPtr_CreateRecvRTPChan = (MediaAPI_CreateRecvRTPChan) GetProcAddress
                                          (media, "ooCreateReceiveRTPChannel");
#else
   FuncPtr_CreateRecvRTPChan = (MediaAPI_CreateRecvRTPChan) dlsym(media, 
                                                 "ooCreateReceiveRTPChannel");
#endif
   if(FuncPtr_CreateRecvRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooCreateReceiveRTPChannel");
      return OO_FAILED;
   }
   
#ifdef _WIN32
   FuncPtr_CloseRecvRTPChan = (MediaAPI_CloseRecvRTPChan)GetProcAddress(media, 
                                                 "ooCloseReceiveRTPChannel");
#else
   FuncPtr_CloseRecvRTPChan = (MediaAPI_CloseRecvRTPChan) dlsym(media, 
                                                 "ooCloseReceiveRTPChannel");
#endif
   if(FuncPtr_CloseRecvRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooCloseReceiveRTPChannel");
      return OO_FAILED;
   }

#ifdef _WIN32
   FuncPtr_StartTxWaveFile = (MediaAPI_StartTxWaveFile) GetProcAddress(media, 
                                                  "ooStartTransmitWaveFile");
#else
   FuncPtr_StartTxWaveFile = (MediaAPI_StartTxWaveFile) dlsym(media, 
                                                 "ooStartTransmitWaveFile");
#endif
   if(FuncPtr_StartTxWaveFile == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooStartTransmitWaveFile");
      return OO_FAILED;
   }
   
#ifdef _WIN32
   FuncPtr_StopTxWaveFile = (MediaAPI_StopTxWaveFile) GetProcAddress(media, 
                                                  "ooStopTransmitWaveFile");
#else
   FuncPtr_StopTxWaveFile = (MediaAPI_StopTxWaveFile) dlsym(media, 
                                                 "ooStopTransmitWaveFile");
#endif

   if(FuncPtr_StopTxWaveFile == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooStopTransmitWaveFile");
      return OO_FAILED;
   }

#ifdef _WIN32
   FuncPtr_StartTxMic = (MediaAPI_StartTxMic) GetProcAddress(media, 
                                                  "ooStartTransmitMic");
#else
   FuncPtr_StartTxMic = (MediaAPI_StartTxMic) dlsym(media, 
                                                 "ooStartTransmitMic");
#endif
   if(FuncPtr_StartTxMic == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooStartTransmitMic");
      return OO_FAILED;
   }
   
#ifdef _WIN32
   FuncPtr_StopTxMic = (MediaAPI_StopTxMic) GetProcAddress(media, 
                                                  "ooStopTransmitMic");
#else
   FuncPtr_StopTxMic = (MediaAPI_StopTxMic) dlsym(media, 
                                                 "ooStopTransmitMic");
#endif
   if(FuncPtr_StopTxMic == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooStopTransmitMic");
      return OO_FAILED;
   }

#ifdef _WIN32
   FuncPtr_StartRecvAndPlayback =(MediaAPI_StartRecvAndPlayback)GetProcAddress
                                     (media, "ooStartReceiveAudioAndPlayback");
#else
   FuncPtr_StartRecvAndPlayback = (MediaAPI_StartRecvAndPlayback) dlsym(media, 
                                             "ooStartReceiveAudioAndPlayback");
#endif
   if(FuncPtr_StartRecvAndPlayback == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooStartReceiveAudioAndPlayback");
      return OO_FAILED;
   }

#ifdef _WIN32
   FuncPtr_StopRecvAndPlayback = (MediaAPI_StopRecvAndPlayback) GetProcAddress
                                      (media, "ooStopReceiveAudioAndPlayback");
#else
   FuncPtr_StopRecvAndPlayback = (MediaAPI_StopRecvAndPlayback) dlsym(media, 
                                              "ooStopReceiveAudioAndPlayback");
#endif

   if(FuncPtr_StopRecvAndPlayback == 0)
   {
      OOTRACEERR2(context, "ERROR: Failed to retrieve the address of "
                           "ooStopRecvAndPlayback");
      return OO_FAILED;
   }
   
   /* Initialize the plugin */
   FuncPtr_InitializePlugin();

   return OO_OK;
}


int ooCreateTransmitRTPChannel(struct ooAppContext* context, char * destip, 
                               int port)
{
   int channelId=0;
 /*  if(FuncPtr_CreateTxRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_CreateTxRTPChan(&channelId, destip, port);*/
   return oomCreateTransmitRTPChannel(&channelId, destip, port);

}

int ooCloseTransmitRTPChannel(struct ooAppContext* context)
{
   int channelId=0;
  /* if(FuncPtr_CloseTxRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_CloseTxRTPChan(channelId);*/
   return oomCloseTransmitRTPChannel(channelId);
}

int ooCreateReceiveRTPChannel(struct ooAppContext* context, char* localip, 
                              int localport)
{
   int channelId = 0;
  /* if(FuncPtr_CreateRecvRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_CreateRecvRTPChan(&channelId, localip, localport);*/
   return oomCreateReceiveRTPChannel(&channelId, localip, localport);
}

int ooCloseReceiveRTPChannel(struct ooAppContext* context)
{
   int channelId = 0;
  /* if(FuncPtr_CloseRecvRTPChan == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_CloseRecvRTPChan(channelId);*/
   return oomCloseReceiveRTPChannel(channelId);
}

int ooStartTransmitWaveFile(struct ooAppContext* context, char * filename)
{
   int channelId = 0;
 /*  if(FuncPtr_StartTxWaveFile == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_StartTxWaveFile(channelId, filename);*/
   return oomStartTransmitWaveFile(channelId, filename);
}

int ooStopTransmitWaveFile(struct ooAppContext* context)
{
   int channelId = 0;
/*   if(FuncPtr_StopTxWaveFile == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_StopTxWaveFile(channelId);*/
   return oomStopTransmitWaveFile(channelId);
}

int ooStartTransmitMic(struct ooAppContext* context)
{
   int channelId = 0;
  /* if(FuncPtr_StartTxMic == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_StartTxMic(channelId);*/
   /*Modified by Karl on 2004-11-17 below*/
   return oomStartTransmitMic(channelId,context);
   /*Modified by Karl on 2004-11-17 above*/
}

int ooStopTransmitMic(struct ooAppContext* context)
{
   int channelId = 0;
 /*  if(FuncPtr_StopTxMic == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_StopTxMic(channelId);*/
   /*Modified by Karl on 2005-01-18 below*/   
   //return oomStartTransmitMic(channelId,context );
   return oomStopTransmitMic(channelId);
   /*Modified by Karl on 2005-01-18 above*/
}

int ooStartReceiveAudioAndPlayback(struct ooAppContext* context)
{
   int channelId = 0;
/*   if(FuncPtr_StartRecvAndPlayback == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_StartRecvAndPlayback(channelId);*/
   /*Moidfied by Karl on 2004-11-17 below*/
   return oomStartReceiveAudioAndPlayback(channelId,context);
   /*Moidfied by Karl on 2004-11-17 above*/
}

int ooStopReceiveAudioAndPlayback(struct ooAppContext* context)
{
   int channelId = 0;
/*   if(FuncPtr_StopRecvAndPlayback == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return OO_FAILED;
   }
   return FuncPtr_StopRecvAndPlayback(channelId);*/
   return oomStopReceiveAudioAndPlayback(channelId);
}
/*
int ooStartReceiveAudioAndRecord(struct ooAppContext* context)
{
   int channelId = 0;
   if(FuncPtr_StopRecvAndPlayback == 0)
   {
      OOTRACEERR2(context, "ERROR: Plugin not available");
      return -1;
   }
   return FuncPtr_StopRecvAndPlayback(channelId);
   return 0;
}
int ooStopReceiveAudioAndRecord(struct ooAppContext* context)
{
   return 0;
}
*/

int ooRTPShutDown(struct ooAppContext* context)
{
   int ret = 0;
   ret = ooCloseTransmitRTPChannel(context);
   if(ret != 0)
   {
      OOTRACEERR2(context, "ERROR: Closing Transmit RTP Channel");
      return OO_FAILED;
   }
   ret = ooCloseReceiveRTPChannel(context);
   if(ret != 0)
   {
      OOTRACEERR2(context, "ERROR: Closing Receive RTP Channel");
      return OO_FAILED;
   }
   return OO_OK;
}

int ooReleaseSndRTPPlugin(struct ooAppContext* context)
{
#ifdef _WIN32
   if(!FreeLibrary(media))
   {
      OOTRACEWARN2(context, "Warn: Failed to release the plugin");
      return OO_FAILED;
   }
   else
      OOTRACEINFO2(context, "INFO: Plugin released from memory");
#else
   if(dlclose(media) != 0)
   {
      OOTRACEWARN2(context, "Warn: Failed to release the plugin");
      return OO_FAILED;
   }
   else
      OOTRACEINFO2(context, "INFO: Plugin released from memory");
#endif
   media = 0;
   FuncPtr_InitializePlugin = 0;
   FuncPtr_CreateTxRTPChan = 0;
   FuncPtr_CloseTxRTPChan = 0;
   FuncPtr_CreateRecvRTPChan = 0;
   FuncPtr_CloseRecvRTPChan = 0;
   FuncPtr_StartTxWaveFile = 0;
   FuncPtr_StopTxWaveFile = 0;
   FuncPtr_StartTxMic = 0;
   FuncPtr_StopTxMic = 0;
   FuncPtr_StartRecvAndPlayback = 0;
   FuncPtr_StopRecvAndPlayback = 0;

   return OO_OK;
}

int ooSetLocalRTPAndRTCPAddrs(struct ooAppContext* context)
{
   int port;
   ooGetLocalIPAddress(context->localIP);
   port = ooGetNextPort(context, OORTP);
   /* Ensures that RTP port is an even one */
   if((port & 1) == 1)
     port = ooGetNextPort(context, OORTP);
   
   context->localRtpPort = port;
   context->localRtcpPort = ooGetNextPort(context, OORTP);
   OOTRACEINFO4(context, "Local RTP port: %d Local RTCP port:%d", 
                          context->localRtpPort, context->localRtcpPort);
   return OO_OK;
}


