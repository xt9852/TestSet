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

#include "ootypes.h"
#include "oo.h"
#include "ooq931.h"
#include "ooh245.h"
#include "ooRas.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "Media\oortp.h"

/* Initialize the application context within stack */
int ooInitialize(struct ooAppContext **myOOContext, 
                   const char * tracefile, CommandCallback myCallback)
{
   /*Added by Karl on 2005-01-19 below*/
   OOCTXT *pctxt=NULL;
   H245EndPointCapability * pCapability;
   H245AudioCapability * pReceiveAudioCapability;
   H245AudioCapability * pTransmitAudioCapability;
   H245AudioCapability * pReceiveTransmitAudioCapability;
   /*Added by Karl on 2005-01-19 above*/
   
   *myOOContext = (struct ooAppContext *)malloc(
                                             sizeof(struct ooAppContext));
   memset(*myOOContext, 0, sizeof(struct ooAppContext));
   if(*myOOContext == NULL)
   {
      printf("\n ERROR: Failed to allocate memory for application context");
      return OO_FAILED;
   }
   else
   {
      (*myOOContext)->callReference = 0;
      (*myOOContext)->callIdentifier.guid.numocts = 0;
      memset((*myOOContext)->callIdentifier.guid.data, 0, 16);
	  //added by tony below 2004.12.16
	  (*myOOContext)->epIdentifier.nchars = 0;
	  (*myOOContext)->epIdentifier.data = NULL;

	  initContext(&(*myOOContext)->glbCtxt);
	  //added by tony above 2004.12.16

	  //added by tony below 2004.12.13
	  (*myOOContext)->conferenceId.numocts = 0;
	  memset((*myOOContext)->conferenceId.data,0,16);
	  //added by tony above 2004.12.13
	  //added by tony below [2004.12.7]
	  (*myOOContext)->RASChannel = 0;
	  (*myOOContext)->seqNumber = 1;
	  (*myOOContext)->outgoingRas = NULL;
	  (*myOOContext)->RASCallback = NULL;
	  initContext(&((*myOOContext)->outRasListCtxt));
	  dListInit(&((*myOOContext)->outRasQueue));
	  memset((*myOOContext)->GkIp,0,20);
	  (*myOOContext)->RasChanPort = -1;
	  (*myOOContext)->sendRas = 0;
	  //added by tony above [2004.12.7]
      (*myOOContext)->h225Channel = 0;
      (*myOOContext)->h225ChanPort = -1;
      (*myOOContext)->h225Rx = 0;
      (*myOOContext)->h225RxPort = -1;
      (*myOOContext)->h245Channel = 0;
      (*myOOContext)->h245ChanPort = -1;
      (*myOOContext)->h245Rx = 0;
      (*myOOContext)->h245RxPort = -1;
      (*myOOContext)->remoteRtpPort = -1;
	  (*myOOContext)->remoteRtcpPort = -1;
	  memset((*myOOContext)->remoteIP,0,20);
  	  (*myOOContext)->localRtpPort = -1;
      (*myOOContext)->localRtcpPort = -1;
      memset((*myOOContext)->localIP,0,20);
      (*myOOContext)->sendH225 =0;
      (*myOOContext)->sendH245 = 0;
      (*myOOContext)->h225Callback = NULL;
      (*myOOContext)->h245Callback = NULL;
      (*myOOContext)->hCommandCallback = myCallback;
      (*myOOContext)->outgoing = NULL;
      (*myOOContext)->outgoingH245 = NULL;
      initContext(&((*myOOContext)->outH245ListCtxt));
      dListInit(&((*myOOContext)->outH245Queue));
      initContext(&((*myOOContext)->outH225ListCtxt));
      dListInit(&((*myOOContext)->outH225Queue));

      (*myOOContext)->ooMasterSlaveState = OO_MasterSlave_Idle;

      if(tracefile != NULL)
      {
         (*myOOContext)->fptraceFile = fopen(tracefile, "w");
         if((*myOOContext)->fptraceFile == NULL)
         {
            /*free the allocated memory for app context*/
            free((*myOOContext)); 
            return OO_FAILED;
         }
      }
      else
      {
         (*myOOContext)->fptraceFile = stdout;
      }
   }
   

   /* Initialize default port ranges that will be used by stack. 
      Apps can override these by explicitely setting port ranges
   */
   (*myOOContext)->tcpPorts.start = TCPPORTSSTART;
   (*myOOContext)->tcpPorts.max = TCPPORTSEND;
   (*myOOContext)->tcpPorts.current=TCPPORTSSTART;

   (*myOOContext)->udpPorts.start = UDPPORTSSTART;
   (*myOOContext)->udpPorts.max = UDPPORTSEND;
   (*myOOContext)->udpPorts.current = UDPPORTSSTART;

   (*myOOContext)->rtpPorts.start = RTPPORTSSTART;
   (*myOOContext)->rtpPorts.max = RTPPORTSEND;
   (*myOOContext)->rtpPorts.current = RTPPORTSSTART;

   /*Added by Karl on 2004-11-16 below*/
   pctxt = (OOCTXT*)newContext();
   initContext(pctxt);   
   pCapability = (H245EndPointCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245EndPointCapability));
   memset(pCapability, 0, sizeof(H245EndPointCapability));
   
   /*Modifieded by Karl on 2005-01-19 below*/
   pReceiveAudioCapability = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(pReceiveAudioCapability, 0, sizeof(H245AudioCapability)); 
   pTransmitAudioCapability = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(pTransmitAudioCapability, 1, sizeof(H245AudioCapability)); 
   pReceiveTransmitAudioCapability = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(pReceiveTransmitAudioCapability, 2, sizeof(H245AudioCapability));    
   
   (*myOOContext)->endCapability = pCapability;
   (*myOOContext)->endCapability->receiveAudioCapability = pReceiveAudioCapability;
   (*myOOContext)->endCapability->transmitAudioCapability = pTransmitAudioCapability;
   (*myOOContext)->endCapability->receiveAndTransmitAudioCapability = pReceiveTransmitAudioCapability;
   (*myOOContext)->endCapability->receiveAudioCapability->t = 4;
   (*myOOContext)->endCapability->receiveAudioCapability->u.g711Ulaw64k = 60;
   (*myOOContext)->endCapability->transmitAudioCapability->t = 4;
   (*myOOContext)->endCapability->transmitAudioCapability->u.g711Ulaw64k = 60;
   (*myOOContext)->endCapability->receiveAndTransmitAudioCapability->t = 4;
   (*myOOContext)->endCapability->receiveAndTransmitAudioCapability->u.g711Ulaw64k = 60;
   
   /*(*myOOContext)->endCapability = pCapability;
   (*myOOContext)->endCapability->u.receiveAudioCapability = pReceiveAudioCapability;
   (*myOOContext)->endCapability->u.transmitAudioCapability = pTransmitAudioCapability;
   (*myOOContext)->endCapability->u.receiveAndTransmitAudioCapability = pReceiveTransmitAudioCapability;                                    
   (*myOOContext)->endCapability->t=5;
   (*myOOContext)->endCapability->u.receiveAudioCapability->t = 12;
   (*myOOContext)->endCapability->u.receiveAudioCapability->u.g729AnnexA = 60;
   (*myOOContext)->endCapability->u.transmitAudioCapability->t = 12;
   (*myOOContext)->endCapability->u.transmitAudioCapability->u.g729AnnexA = 60;
   (*myOOContext)->endCapability->u.receiveAndTransmitAudioCapability->t = 12;
   (*myOOContext)->endCapability->u.receiveAndTransmitAudioCapability->u.g729AnnexA = 60;
   */
   /*Modifieded by Karl on 2005-01-19 above*/
   /*Added by Karl on 2004-11-16 above*/

   (*myOOContext)->totalOpenLogicalChannels = 0;      
   OOTRACEINFO2((*myOOContext), "Application context initialize - successful");

	ooInitializePlugin();
   return OO_OK;
}

int ooCloseContext(struct ooAppContext *context)
{
   /* free any internal memory allocated
      close trace file free context structure
   */
   if(context != NULL)
   {
	   //added by tony below
	  dListFreeNodes(&(context->outRasListCtxt),&(context->outRasQueue));	
	  //added by tony above
	  dListFreeNodes(&(context->outH225ListCtxt), &(context->outH225Queue));
      dListFreeNodes(&(context->outH245ListCtxt), &(context->outH245Queue));
      freeContext(&context->outH245ListCtxt);
      freeContext(&context->outH225ListCtxt);
	  //added by tony below
	  freeContext(&context->outRasListCtxt);
	  if(context->outgoingRas != NULL)
		  ooFreeRasMessage(context,context->outgoingRas);
	  //added by tony above
	  
      if(context->outgoing != NULL)
      {
         ooFreeQ931Message(context, context->outgoing);
      }
      if(context->outgoingH245 != NULL)
      {
         ooFreeH245Message(context, context->outgoingH245);
      }
      fclose(context->fptraceFile);
      free(context);
   }
   return OO_OK;
}

void ooTrace(struct ooAppContext * context, const char * fmtspec, ...)
{
   va_list arglist;
   char timeString[100];
   char logMessage[MAXLOGMSGLEN];
   char currtime[3];
   static int lasttime=25;
   int printDate =0;

#ifdef _WIN32
   
   SYSTEMTIME systemTime;
   GetLocalTime(&systemTime);
   GetTimeFormat(LOCALE_SYSTEM_DEFAULT,0, &systemTime, "HH':'mm':'ss", timeString, 100);
   GetTimeFormat(LOCALE_SYSTEM_DEFAULT,0, &systemTime, "H", currtime, 3);
   if(lasttime> atoi(currtime))
      printDate=1;
   lasttime = atoi(currtime);
   
#else
   struct tm *ptime;
   struct timeval systemTime;
   char dateString[10];
   gettimeofday(&systemTime, NULL);
   ptime = (struct tm*)localtime(&systemTime.tv_sec);
   strftime(timeString, 100, "%H:%M:%S", ptime);
   strftime(currtime, 3, "%H", ptime);
   if(lasttime>atoi(currtime))
       printDate = 1;
   lasttime = atoi(currtime);   
#endif

   va_start (arglist, fmtspec);
   vsprintf(logMessage, fmtspec, arglist);

#ifdef _WIN32
   if(context != 0)
   {
      if(printDate)
      {
         printDate = 0;
         fprintf(context->fptraceFile, "---------Date %d/%d/%d---------\n",
                         systemTime.wMonth, systemTime.wDay, systemTime.wYear);
      }
      fprintf(context->fptraceFile, "%s:%03d  %s\n", timeString, 
	      systemTime.wMilliseconds, logMessage);
      fflush(context->fptraceFile);
   }
   else
   {
      if(printDate)
      {
         printDate = 0;
         fprintf(0, "---------Date %d/%d/%d---------\n",
                         systemTime.wMonth, systemTime.wDay, systemTime.wYear);
      }
   
      fprintf(0, "%s:%03d  %s\n", timeString, systemTime.wMilliseconds,
	      logMessage);
	  fflush(stdout);
   }
#else
   if(context != 0)
   {
      if(printDate)
      {
	 printDate = 0;
         strftime(dateString, 10, "%D", ptime);
         fprintf(context->fptraceFile, "---------Date %s---------\n", 
		 dateString);
      }
      fprintf(context->fptraceFile, "%s:%03d  %s\n", timeString, 
	      systemTime.tv_usec/1000, logMessage);
      fflush(context->fptraceFile);
   }
   else
   {
      if(printDate)
      {
	 printDate = 0;
         strftime(dateString, 10, "%D", ptime);
         fprintf(0, "---------Date %s---------\n", dateString);
      }
   
      fprintf(0, "%s:%03d  %s\n", timeString, systemTime.tv_usec/1000,
	      logMessage);
      fflush(0);
   }
#endif
      
   va_end(arglist);
}

