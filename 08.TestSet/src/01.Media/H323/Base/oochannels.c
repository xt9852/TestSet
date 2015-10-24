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

#include "ooports.h" 
#include "oochannels.h"
#include "oo.h"
#include "ooq931.h"
#include "ooh245.h"
#include "ooRas.h"
#include "oosndrtp.h"

#include "stdio.h"

//added by tony below
int ooSendRasMsg(struct ooAppContext *context)
{
   if(!context)
      return OO_FAILED;

   if(context->outgoingRas != NULL)
   {
      dListAppend(&context->outRasListCtxt, &context->outRasQueue, 
                  context->outgoingRas);
      /* No need to release memory as RTDList uses it*/
      context->outgoingRas = NULL; 
      context->sendRas++;
   }
   return OO_OK;	
}
//added by tony above

int ooSendH225Msg(struct ooAppContext *context)
{
   if(!context)
      return OO_FAILED;
   if(context->outgoing != NULL)
   {
      dListAppend(&context->outH225ListCtxt, &context->outH225Queue, 
                  context->outgoing);
      /* No need to release memory as RTDList uses it*/
      context->outgoing = NULL; 
      context->sendH225++;
   }
 
   return OO_OK;
}

int ooSendH245Msg(struct ooAppContext *context)
{
   if(!context)
      return OO_FAILED;
   if(context->outgoingH245 != NULL)
   {
      dListAppend(&context->outH245ListCtxt, &context->outH245Queue,
                  context->outgoingH245);
      context->outgoingH245 = NULL;
      context->sendH245++;

   }
   return OO_OK;
}  

int ooCreateH245Channel(struct ooAppContext *context, 
                        ChannelCallback hdlH245Event, 
                        struct ooConnectionEP *connectionEP, int dir)
{
   int ret=0;
   OOSOCKET channelSocket=0;
   OOTRACEINFO2(context, "Creating H245 Channel");
   if(dir == OOTRANSMITTER)
   {
        
      if((ret=ooSocketCreate (&channelSocket))!=ASN_OK)
      {
         OOTRACEERR2(context, "Failed to create socket for transmit H245 "
                              "channel");
         return OO_FAILED;
      }
      else
      {
         /*
            bind socket to a port before connecting. Thus avoiding
            implicit bind done by a connect call.
         */
         ret = ooBindPort(context, OOTCP, channelSocket); 
         if(ret == OO_FAILED)
         {
            OOTRACEERR2(context, "Error:Unable to bind to a TCP port");
            return OO_FAILED;
         }
         context->h245ChanPort = ret;
                 
         OOTRACEINFO2(context, "Trying to connect to remote endpoint to setup "
                               "H245 channel");
                 
         if((ret=ooSocketConnect(channelSocket, connectionEP->ipaddress,
                                   connectionEP->port))==ASN_OK)
         {
            context->h245Channel = channelSocket;
            context->h245Callback=hdlH245Event;
            OOTRACEINFO2(context, "H245 transmiter channel creation "
                                  "- succesful");
            return OO_OK;
         }
         else
         {
            OOTRACEINFO2(context, "Failed to connect to remote destination for "
                                "transmit H245 channel");
            return OO_FAILED;
         }

      }
   }
   
   if(dir == OORECEIVER)
   {
      if((ret=ooSocketCreate (&channelSocket))!=ASN_OK)
      {
         OOTRACEERR2(context, "Failed to create socket for receive "
                             "H245 channel");
         return OO_FAILED;
      }
      ret = ooBindPort(context, OOTCP,channelSocket); 
      if(ret == OO_FAILED)
      {
         OOTRACEERR2(context, "Error:Unable to bind to a TCP port");
         return OO_FAILED;
      }
      context->h245RxPort = ret;
      context->h245Rx = channelSocket;
      context->h245Callback = hdlH245Event;
      ooSocketListen(channelSocket, 5);
      OOTRACEINFO2(context, "H245 listener creation - successful");
      return OO_OK;
   }
   return OO_FAILED;
}


int ooCreateH2250Channel(struct ooAppContext *context, 
                         ChannelCallback hdlH2250Event, 
                         struct ooConnectionEP connectionEP, int dir)
{
   int ret=0;
   OOSOCKET channelSocket=0;
   OOIPADDR ipaddrs;
      
   /* Currently only transmitter and receiver supported, no duplex support*/
   if(dir == OOTRANSMITTER)
   {
      if((ret=ooSocketCreate (&channelSocket))!=ASN_OK)
      {
		OOTRACEERR2(context, "Failed to create socket for transmit H2250 channel");
		return OO_FAILED;
      }
      else
      {
         /*
            bind socket to a port before connecting. Thus avoiding
            implicit bind done by a connect call. Avoided on windows as 
            windows sockets have problem in reusing the addresses even after
            setting SO_REUSEADDR, hence in windows we just allow os to bind
            to any random port.
         */
#ifndef _WIN32
         ret = ooBindPort(context, OOTCP,channelSocket); 
#endif
         if(ret == OO_FAILED)
         {
            OOTRACEERR2(context, "Error:Unable to bind to a TCP port");
            return OO_FAILED;
        }
        context->h225ChanPort = ret;
        OOTRACEINFO2(context, "Trying to connect to remote endpoint to setup "
                            "H2250 channel");
        if((ret=ooSocketConnect(channelSocket, connectionEP.ipaddress,
                                connectionEP.port))==ASN_OK)
        {
           context->h225Channel = channelSocket;
           context->h225Callback=hdlH2250Event;
           OOTRACEINFO2(context, "H2250 transmiter channel creation "
                                 "- succesful");
           return OO_OK;
        }
        else
        {
           OOTRACEERR2(context, "Failed to connect to remote destination for "
                                "transmit H2250 channel");
                   
           return OO_FAILED;
        }
        
        return OO_FAILED;
      }
      return OO_FAILED;
   }
   if(dir == OORECEIVER)
   {
      if((ret=ooSocketCreate (&channelSocket))!=ASN_OK)
      {
         OOTRACEERR2(context, "Failed to create socket for receive "
                              "H2250 channel");
         return OO_FAILED;
      }
      ret= ooSocketStrToAddr (connectionEP.ipaddress, &ipaddrs);
      if((ret=ooSocketBind (channelSocket, ipaddrs, 
                            connectionEP.port))==ASN_OK) 
      {
         context->h225Rx = channelSocket;
         context->h225RxPort = connectionEP.port;
         context->h225Callback = hdlH2250Event;
         ooSocketListen(channelSocket, 5); /*listen on socket*/
         OOTRACEINFO2(context, "H2250 listener creation - successful");
         return OO_OK;
      }
      else
      {
         OOTRACEERR2(context, "Failed to create H2250 receive channel");
         return OO_FAILED;
      }
      return OO_FAILED;
   }
   return OO_FAILED;
}

//added by tony below
int ooRasUDPReceive(struct ooAppContext* context)
{
   int  recvLen;
   ASN1OCTET message[MAXMSGLEN];
   int  size =MAXMSGLEN;
   ASN1BOOL aligned = TRUE, trace = FALSE;
   RasMessage *pmsg;
   OOCTXT *pctxt;
   int ret;
	
   OOTRACEDBGC2(context, "Receiving Ras message");
   recvLen = ooSocketRecvFrom(context->RASChannel, message, MAXMSGLEN,0,0);
   if(recvLen < 0)
   {
	  OOTRACEDBGC2(context,"Ras message received failed");
	  return OO_FAILED;		
   }
   OOTRACEDBGC2(context,"Complete Ras message received");

   pctxt = (OOCTXT*)newContext();
   if(pctxt == NULL)
   {
      OOTRACEERR2(context,"ERROR: Failed to allocate ASN1 context for"
                          " incoming ras message creation");
      return OO_FAILED;
   }
   pmsg = (RasMessage*)ASN1MALLOC(pctxt, sizeof(RasMessage));
   pmsg->pctxt = pctxt;

   setPERBuffer(pctxt, message, recvLen, aligned);

   ret = asn1PD_H225RasMessage(pctxt, &(pmsg->RasMsg));
   if(ret != ASN_OK)
   {
      OOTRACEERR2(context, "Error decoding ras message");
      return OO_FAILED;
   }
   if(context->RASCallback!=NULL)
      context->RASCallback(pmsg);
   else
      OOTRACEDBGA2(context, "No ras callback registered");

  return OO_OK;
}
//added by tony above

int ooH2250TCPReceive(struct ooAppContext *context)
{
   int  recvLen=0, total=0, ret=0;
   ASN1OCTET message[MAXMSGLEN], message1[MAXMSGLEN];
   int size =MAXMSGLEN, len;
   char logMessage[MAXMSGLEN];
   Q931Message *pmsg;
   OOCTXT *pctxt;
   struct timeval timeout;
   fd_set readfds;

   /* First read just TPKT header which is four bytes */
   recvLen = ooSocketRecv (context->h225Channel, message, 4);
   /* Since we are working with TCP, need to determine the
      message boundary. Has to be done at channel level, as channels
      know the message formats and can determine boundaries
   */
	if(recvLen == 0)	//the connection has been gracefully closed
		return OO_OK;

   if(recvLen != 4)
   {
      OOTRACEERR2(context, "Error: Reading TPKT header for H225 message");
//      exit(0); /*Need more graceful exit*/
	  ooCloseH225Channel(context);
	  return OO_FAILED;
   }

   pctxt = (OOCTXT*)newContext();
   OOTRACEDBGC2(context, "Receiving H.2250 message");
   if(pctxt == NULL)
   {
      OOTRACEERR2(context,"ERROR: Failed to allocate ASN1 context for "
                          "incoming message creation");
      return OO_FAILED;
   }
   //remarked by tony,initContext is already called by newContext, here call will lead to memory leak.
//  initContext(pctxt);
   pmsg = (Q931Message*)ASN1MALLOC(pctxt, sizeof(Q931Message));
   pmsg->pctxt = pctxt;
   
   
   len = message[2];
   len = len<<8;
   len = len + message[3];
   /* Remaining message length is length - tpkt length */
   len = len - 4;

   /* Now read actual Q931 message body. We should make sure that we
      receive complete message as indicated by len. If we don't then there 
      is something wrong. The loop below receives message, then checks whether
      complete message is received. If not received, then uses select to peek
      for remaining bytes of the message. If message is not received in 3
      seconds, then we have a problem. Report an error and exit.
   */
   while(total < len)
   {
      recvLen = ooSocketRecv (context->h225Channel, message1, len-total);
      memcpy(message+total, message1, recvLen);
      total = total + recvLen;

      if(total == len) break; /* Complete message is received */
      
      FD_ZERO(&readfds);
      FD_SET(context->h225Channel, &readfds);
      timeout.tv_sec = 3;
      timeout.tv_usec = 0;
      ret = ooSocketSelect(context->h225Channel+1, &readfds, NULL, 
                           NULL, &timeout);
      if(ret == -1)
      {
         if(context->h225Channel != 0)
            OOTRACEERR2(context, "Error in select...exiting");
         exit(-1);
      }
      /* If remaining part of the message is not received in 3 seconds 
         exit */
      if(!FD_ISSET(context->h225Channel, &readfds))
      {
         OOTRACEERR2(context, "Error: Incomplete message received");
       //  exit(0); /*Need more graceful exit..*/
		 ooCloseH225Channel(context);
		 return OO_FAILED;
      }
   }
   
   OOTRACEDBGC2(context,"Complete H.2250 message received");
   ooQ931Decode (pmsg, len, message);
   sprintf(logMessage, "Received message type %x", pmsg->messageType);
   OOTRACEDBGA2(context, logMessage);
   if(context->h225Callback!=NULL)
      context->h225Callback(pmsg);
   
   return OO_OK;
}


/* Generic Send Message functionality. Based on type of message to be sent,
   it calls the corresponding function to retrieve the message buffer and 
   then transmits on the associated channel
*/
int ooSendMsg(struct ooAppContext *context, int type)
{
   ASN1OCTET msgbuf[MAXMSGLEN];
   int len=0, ret=0, msgType=0;
   int i =0; 
   memset(msgbuf, 0, sizeof(msgbuf));
   //added by tony below
   if(type == OORASMSG)
   {
	  if(ooGetOutgoingRasMsgbuf(context,msgbuf,&len,&msgType) != OO_OK)
	  {
        OOTRACEERR2(context, "ERROR:Could not retrieve message buffer for "
                             "outgoing RAS msg");
         context->sendRas--;
         return OO_FAILED;
	  }

	  ret = ooSocketSendTo(context->RASChannel,msgbuf,len,context->GkIp,context->RasChanPort);
	  if(ret == ASN_OK)
      {
         context->sendRas--; /* decrement send count */
		 ooOnSendMsg(context,msgType);
         return OO_OK;
      }
      else{
         OOTRACEERR2(context,"H2250 RAS Message send failed");
         context->sendRas--;
		 ooOnSendMsgFail(context,msgType);
         return OO_FAILED;
      }
   }
   //added by tony above
   if(type == OOQ931MSG)
   {
	  if(ooGetOutgoingQ931Msgbuf(context, msgbuf, &len, &msgType)!=OO_OK)
	  {
		 OOTRACEERR2(context, "ERROR:Could not retrieve message buffer for "
							 "outgoing q931 msg");
		 context->sendH225--;
		 return OO_FAILED;
	  }
   
	  /* Send message out via TCP */
      ret = ooSocketSend(context->h225Channel, msgbuf, len);
      if(ret == ASN_OK)
      {
         context->sendH225--; /* decrement send count */
         ooOnSendMsg(context, msgType);
         return OO_OK;
      }
      else{
         context->sendH225--;
		 ooOnSendMsgFail(context,msgType);
         return OO_FAILED;
      }
   }/* end of type==OOQ931MSG */
   if(type == OOH245MSG)
   {
      if(ooGetOutgoingH245Msgbuf(context, msgbuf, &len, &msgType)!=OO_OK)
      {
         OOTRACEERR2(context,"ERROR:Could not retrieve message buffer for "
                            "outgoing h245 message");
         context->sendH245--;
         return OO_FAILED;
      }
      /* Send message out */
      ret = ooSocketSend(context->h245Channel, msgbuf, len);
      if(ret == ASN_OK)
      {
         context->sendH245--;
         ooOnSendMsg(context, msgType);
         return OO_OK;
      }
      else{
         context->sendH245--;
		 ooOnSendMsgFail(context,msgType);
         return OO_FAILED;
      }
   }
   /* Need to add support for other messages such as H245, T38 etc */
   OOTRACEWARN2(context,"ERROR:Unknown message type - message not Sent");
   return OO_FAILED;
}               

int ooAcceptH225Connection(struct ooAppContext *context)    
{
   int ret;
   OOSOCKET h225Channel=0;
   ret = ooSocketAccept (context->h225Rx, &h225Channel, 
                         NULL, NULL);
   if(ret != ASN_OK)
   {
      OOTRACEERR2(context,"Error:Accepting h225 connection");
      return OO_FAILED;
   }
   context->h225Channel=h225Channel; 
   return OO_OK;
}

int ooAcceptH245Connection(struct ooAppContext *context)
{
   int ret;
   OOSOCKET h245Channel=0;
   ret = ooSocketAccept (context->h245Rx, &h245Channel, 
                         NULL, NULL);
   if(ret != ASN_OK)
   {
      OOTRACEERR2(context,"Error:Accepting h245 connection");
      return OO_FAILED;
   }
   context->h245Channel=h245Channel; 
   return OO_OK;
}
   

int ooH245Receive(struct ooAppContext *context)
{
   int  recvLen, ret, len, total=0;
   ASN1OCTET message[MAXMSGLEN], message1[MAXMSGLEN];
   int  size =MAXMSGLEN;
   ASN1BOOL aligned = TRUE, trace = FALSE;
   H245Message *pmsg;
   OOCTXT *pctxt;
   struct timeval timeout;
   fd_set readfds;
   OOTRACEDBGC2(context, "Receiving H245 message");

  recvLen = ooSocketRecv (context->h245Channel, message, 4);
   /* Since we are working with TCP, need to determine the
      message boundary. Has to be done at channel level, as channels
      know the message formats and can determine boundaries
   */
	if(recvLen == 0)	//the connection has been gracefully closed
		return 	OO_OK;

   if(recvLen != 4)
   {
      OOTRACEERR2(context, "Error: Reading TPKT header for H245 message");
//      exit(0); /*Need more graceful exit*/
	  ooCloseH225Channel(context);
	  return OO_FAILED;
   }

   pctxt = (OOCTXT*)newContext();
   if(pctxt == NULL)
   {
      OOTRACEERR2(context,"ERROR: Failed to allocate ASN1 context for"
                          " incoming h245 message creation");
      return OO_FAILED;
   }
   pmsg = (H245Message*)ASN1MALLOC(pctxt, sizeof(H245Message));
   pmsg->pctxt = pctxt;
   /* First read just TPKT header which is four bytes */
 

   len = message[2];
   len = len<<8;
   len = (len | message[3]);
   /* Remaining message length is length - tpkt length */
   len = len - 4;
   /* Now read actual H245 message body. We should make sure that we
      receive complete message as indicated by len. If we don't then there 
      is something wrong. The loop below receives message, then checks whether
      complete message is received. If not received, then uses select to peek
      for remaining bytes of the message. If message is not received in 3
      seconds, then we have a problem. Report an error and exit.
   */
   while(total < len)
   {
      recvLen = ooSocketRecv (context->h245Channel, message1, len-total);
      memcpy(message+total, message1, recvLen);
      total = total + recvLen;
      if(total == len) break; /* Complete message is received */
      FD_ZERO(&readfds);
      FD_SET(context->h245Channel, &readfds);
      timeout.tv_sec = 3;
      timeout.tv_usec = 0;
      ret = ooSocketSelect(context->h245Channel+1, &readfds, NULL, 
                           NULL, &timeout);
      if(ret == -1)
      {
         if(context->h245Channel != 0)
            OOTRACEERR2(context, "Error in select...exiting");
//         exit(-1);
		 ooCloseH225Channel(context);
		 return OO_FAILED;
      }
      /* If remaining part of the message is not received in 3 seconds exit */
      if(!FD_ISSET(context->h245Channel, &readfds))
      {
         OOTRACEERR2(context, "Error: Incomplete h245 message received");
//         exit(0); /*Need more graceful exit..*/
		 ooCloseH225Channel(context);
      }
   }

   OOTRACEDBGC2(context,"Complete H245 message received");
   setPERBuffer(pctxt, message, recvLen, aligned);

   ret = asn1PD_H245MultimediaSystemControlMessage(pctxt, &(pmsg->h245Msg));
   if(ret != ASN_OK)
   {
      OOTRACEERR2(context, "Error decoding H245 message");
      return OO_FAILED;
   }
   if(context->h245Callback!=NULL)
      context->h245Callback(pmsg);
   else
      OOTRACEDBGA2(context, "No H245 callback registered");

  return OO_OK;

}

int ooMonitorChannels(struct ooAppContext *context)
{
   int ret=0, nfds=0;
   struct timeval timeout;
   fd_set readfds, writefds;
   while(1)
   {
      FD_ZERO(&readfds);
      FD_ZERO(&writefds);
      nfds = 0;
      /* Monitor Standard input. Not done in windows as select() call in
         windows does not allow file descriptors
      */
#ifndef _WIN32
      FD_SET(0, &readfds);
#endif
      nfds = 0;
      if(context->h225Rx != 0)
      {
         FD_SET(context->h225Rx, &readfds);
         if(nfds < (int)context->h225Rx)
            nfds = context->h225Rx;
      }
      if(context->h245Rx != 0)
      {
         FD_SET(context->h245Rx, &readfds);
         if(nfds < (int)context->h245Rx)
            nfds = context->h245Rx;
      }
	  //added by tony below
	  if(context->RASChannel != 0)
	  {
		  FD_SET(context->RASChannel,&readfds);
		  if(context->sendRas > 0)
			  FD_SET(context->RASChannel,&writefds);
		  if(nfds < (int)context->RASChannel)
			  nfds = context->RASChannel;
	  }
	  //added by tony above
      if(context->h225Channel != 0)
      {
         FD_SET(context->h225Channel, &readfds);
         if(context->sendH225>0)
            FD_SET(context->h225Channel, &writefds);
         if(nfds < (int)context->h225Channel)
            nfds = context->h225Channel;
      }
   
      if(context->h245Channel != 0)
      {
         FD_SET(context->h245Channel, &readfds);
         if(context->sendH245>0)
            FD_SET(context->h245Channel, &writefds);
         if(nfds < (int)context->h245Channel)
            nfds = context->h245Channel;
      }
      
      timeout.tv_sec = 3;
      timeout.tv_usec = 0;
      nfds = nfds+1;

      ret = ooSocketSelect(nfds, &readfds, &writefds, 
                           NULL, &timeout);
     
      if(ret == -1)
      {
         OOTRACEERR2(context, "Error in select...exiting");
         exit(-1);
      }

#ifndef _WIN32    
      if(FD_ISSET(0, &readfds))
      {
         OOTRACEDBGC2(context, "stdin received");
         context->hCommandCallback();
      }
#endif  
      if(context->h225Rx != 0)
      {
         if(FD_ISSET(context->h225Rx, &readfds))
         {
            OOTRACEDBGA2(context, "New connection at H225 receiver");
            ooAcceptH225Connection(context);
         }      
      }
      if(context->h245Rx != 0)
      {
         if(FD_ISSET(context->h245Rx, &readfds))
         {
            OOTRACEDBGA2(context,"New connection request on H245 receive");
            ooAcceptH245Connection(context);
         }
      }

	  //added by tony below
	  if(context->RASChannel != 0)
	  {
		  if(FD_ISSET(context->RASChannel,&readfds))
		  {
            OOTRACEDBGC2(context, "Received on Ras channel...");
            ooRasUDPReceive(context);
		  }
	  }

	  if(context->RASChannel != 0)
	  {
		  if(FD_ISSET(context->RASChannel,&writefds))
		  {
            OOTRACEDBGC2(context, "SELECT selected send on RAS channel");
            ooSendMsg(context, OORASMSG);
		  }
	  }
	  //added by tony above
	  
      if(context->h225Channel != 0)
      {
         if(FD_ISSET(context->h225Channel, &readfds))
         {
                OOTRACEDBGC2(context, "Received on h225channel...");
                ooH2250TCPReceive(context);
         }
      }

      if(context->h245Channel != 0)
      {
         if(FD_ISSET(context->h245Channel, &readfds))
         {
            OOTRACEDBGC2(context, "H245 message received in select");
            ooH245Receive(context);
         }
      }

      if(context->h225Channel != 0)
      {
         if(FD_ISSET(context->h225Channel, &writefds))
         {
            OOTRACEDBGC2(context, "SELECT selected send on h225channel");
            ooSendMsg(context, OOQ931MSG);
         }
      }

      if(context->h245Channel != 0)
      {
         if(FD_ISSET(context->h245Channel, &writefds))
         {
            OOTRACEDBGC2(context, "Select selected to send h245 message");
            ooSendMsg(context, OOH245MSG);
         }
      }
   }
}

int ooGetH225ChannelPort(struct ooAppContext *context)
{
   return context->h225ChanPort;
}

int ooGetH245ChannelPort(struct ooAppContext *context)
{
   return context->h245ChanPort;
}

int ooGetH245ReceiverPort(struct ooAppContext *context)
{
   return context->h245RxPort;
}   

int ooGetLocalRtcpPort(struct ooAppContext *context)
{
   return context->localRtcpPort;
}

int ooGetLocalRtpPort(struct ooAppContext *context)
{
   return context->localRtpPort;
}

int ooGetRemoteRtpPort(struct ooAppContext *context)
{
   return context->remoteRtpPort;
}

int ooOnSendMsg(struct ooAppContext *context, int msgType)
{
	//modified by tony below 2004.12.16
   switch(msgType)
   {
   case OOSetup:
		OOTRACEDBGC2(context,"H2250Q931 'Call setup' message sent successfully");
		break;
   case OOCallProceeding:
		OOTRACEDBGC2(context,"H2250Q931 'Call proceeding' message sent successfully");
	    break;
   case OOAlert:
		OOTRACEDBGC2(context,"H2250Q931 'Alerting' message sent successfully");
	    break;
   case OOConnect:
		OOTRACEDBGC2(context,"H2250Q931 'Connect' message sent successfully");
		break;
   case OOReleaseComplete:
		OOTRACEDBGC2(context,"H2250Q931 'Release complete' message sent successfully");
		ooCloseH225Channel(context);
		break;
   case OOMasterSlaveDetermination:
		OOTRACEDBGC2(context,"H245 'Master slave determination' message sent successfully");
		break;
   case OOMasterSlaveAck:
		OOTRACEDBGC2(context,"H245 'Master slave determination ACK' message sent successfully");
	    break;
   case OOMasterSlaveReject:
		OOTRACEDBGC2(context,"H245 'Master slave reject' message sent successfully");
	    break;
   case OOMasterSlaveRelease:
		OOTRACEDBGC2(context,"H245 'Master slave release' message sent successfully");
	    break;
   case OOTerminalCapabilitySet:
		OOTRACEDBGC2(context,"H245 'Terminal capability set' message sent successfully");
	    break;
   case OOTerminalCapabilitySetAck:
		OOTRACEDBGC2(context,"H245 'Terminal capability set ack' message sent successfully");
	    break;
   case OOTerminalCapabilitySetReject:
		OOTRACEDBGC2(context,"H245 'Terminal capability set reject' message sent successfully");
	    break;
   case OOOpenLogicalChannel:
		OOTRACEDBGC2(context,"H245 'Open logical channel' message sent successfully");
	    break;
   case OOOpenLogicalChannelAck:
		OOTRACEDBGC2(context,"H245 'Open logical channel ack' message sent successfully");
	    break;
   case OOOpenLogicalChannelReject:
		OOTRACEDBGC2(context,"H245 'Open logical channel reject' message sent successfully");
	    break;
   case OOOpenLogicalChannelRelease:
		OOTRACEDBGC2(context,"H245 'Open logical channel release' message sent successfully");
	    break;
   case OOEndSessionCommand:
		OOTRACEDBGC2(context,"H245 'End session' message sent successfully");
		ooCloseH245Channels(context);
	    ooSendReleaseComplete(context); // Send Release Complete. Has to be sent only if not received release complete
		break;
   case OOGatekeeperRequest:
		OOTRACEDBGC2(context,"RAS 'Gatekeeper request' message sent successfully");
	    break;
   case OOGatekeeperConfirm:
		OOTRACEDBGC2(context,"RAS 'Gatekeeper confirm' message sent successfully");
	    break;
   case OOGatekeeperReject:
		OOTRACEDBGC2(context,"RAS 'Gatekeeper reject' message sent successfully");
	    break;
   case OORegistrationRequest:
		OOTRACEDBGC2(context,"RAS 'Registration request' message sent successfully");
	    break;
   case OORegistrationConfirm:
		OOTRACEDBGC2(context,"RAS 'Registration confirm' message sent successfully");
	    break;
   case OORegistrationReject:
		OOTRACEDBGC2(context,"RAS 'Registration reject' message sent successfully");
	    break;
		//未完待续...
   default:;
   }

  /* switch(msgType)
   {
   case OOEndSessionCommand:
      ooCloseH245Channels(context);
      ooSendReleaseComplete(context); // Send Release Complete. Has to be sent only if not received release complete
	  break;
   case OOReleaseComplete:
	  ooCloseH245Channels(context); 
	  ooCloseH225Channel(context);
	  break;
   default:
     ;
   }*/
  	//modified by tony above 2004.12.16
 
   return OO_OK;
}

EXTERN int ooOnSendMsgFail(struct ooAppContext *context,int msgType)
{
   switch(msgType)
   {
   case OOSetup:
		OOTRACEDBGC2(context,"H2250Q931 'Call setup' message sent failed");
		break;
   case OOCallProceeding:
		OOTRACEDBGC2(context,"H2250Q931 'Call proceeding' message sent failed");
	    break;
   case OOAlert:
		OOTRACEDBGC2(context,"H2250Q931 'Alerting' message sent failed");
	    break;
   case OOConnect:
		OOTRACEDBGC2(context,"H2250Q931 'Connect' message sent failed");
		break;
   case OOReleaseComplete:
		OOTRACEDBGC2(context,"H2250Q931 'Release complete' message sent failed");
		ooCloseH245Channels(context); 
		ooCloseH225Channel(context);
		break;
   case OOMasterSlaveDetermination:
		OOTRACEDBGC2(context,"H245 'Master slave determination' message sent failed");
		break;
   case OOMasterSlaveAck:
		OOTRACEDBGC2(context,"H245 'Master slave determination ACK' message sent failed");
	    break;
   case OOMasterSlaveReject:
		OOTRACEDBGC2(context,"H245 'Master slave reject' message sent failed");
	    break;
   case OOMasterSlaveRelease:
		OOTRACEDBGC2(context,"H245 'Master slave release' message sent failed");
	    break;
   case OOTerminalCapabilitySet:
		OOTRACEDBGC2(context,"H245 'Terminal capability set' message sent failed");
	    break;
   case OOTerminalCapabilitySetAck:
		OOTRACEDBGC2(context,"H245 'Terminal capability set ack' message sent failed");
	    break;
   case OOTerminalCapabilitySetReject:
		OOTRACEDBGC2(context,"H245 'Terminal capability set reject' message sent failed");
	    break;
   case OOOpenLogicalChannel:
		OOTRACEDBGC2(context,"H245 'Open logical channel' message sent failed");
	    break;
   case OOOpenLogicalChannelAck:
		OOTRACEDBGC2(context,"H245 'Open logical channel ack' message sent failed");
	    break;
   case OOOpenLogicalChannelReject:
		OOTRACEDBGC2(context,"H245 'Open logical channel reject' message sent failed");
	    break;
   case OOOpenLogicalChannelRelease:
		OOTRACEDBGC2(context,"H245 'Open logical channel release' message sent failed");
	    break;
   case OOEndSessionCommand:
		OOTRACEDBGC2(context,"H245 'End session' message sent failed");
		ooCloseH245Channels(context);
	    ooSendReleaseComplete(context); // Send Release Complete. Has to be sent only if not received release complete
		break;
   case OOGatekeeperRequest:
		OOTRACEDBGC2(context,"RAS 'Gatekeeper request' message sent failed");
	    break;
   case OOGatekeeperConfirm:
		OOTRACEDBGC2(context,"RAS 'Gatekeeper confirm' message sent failed");
	    break;
   case OOGatekeeperReject:
		OOTRACEDBGC2(context,"RAS 'Gatekeeper reject' message sent failed");
	    break;
   case OORegistrationRequest:
		OOTRACEDBGC2(context,"RAS 'Registration request' message sent failed");
	    break;
   case OORegistrationConfirm:
		OOTRACEDBGC2(context,"RAS 'Registration confirm' message sent failed");
	    break;
   case OORegistrationReject:
		OOTRACEDBGC2(context,"RAS 'Registration reject' message sent failed");
	    break;
		//未完待续...
   default:;
   }

   return OO_OK;
}

int ooCloseH245Channels(struct ooAppContext *context)
{
   OOTRACEINFO2(context, "Closing H245 channel");

   context->sendH245 =0;
   if(context->h245Channel != 0)
      ooSocketClose(context->h245Channel);
   if(context->h245Rx != 0)
      ooSocketClose(context->h245Rx);

   /* Shut down RTP channels */

   ooRTPShutDown(context);

   context->h245Channel = 0;
   context->h245ChanPort= -1;
   context->h245Rx =0;
   context->h245RxPort = -1;
   context->remoteRtpPort = -1;
   context->localRtpPort = -1;
   context->localRtcpPort = -1;
   context->remoteRtcpPort = -1;
   context->totalOpenLogicalChannels = 0;
   context->ooMasterSlaveState = OO_MasterSlave_Idle;
   context->outgoingH245 = NULL;
   /* Note Data is not released here. Need to do that. Currently mem leak*/
   dListFreeNodes(&context->outH245ListCtxt, &context->outH245Queue);
   return OO_OK;
}

int ooCloseH225Channel(struct ooAppContext *context)
{
   ooCloseH245Channels(context);
   OOTRACEINFO2(context, "Closing H225 channel");
   context->sendH225 = 0;
   if(context->h225Channel != 0)
   {
     ooSocketClose(context->h225Channel);
   }
   context->h225Channel = 0;
   context->h225ChanPort = -1;
   context->callReference = 0;
   context->callIdentifier.guid.numocts = 0;
   memset(context->callIdentifier.guid.data, 0, 16);
   //added by tony below 2004.12.13
   context->conferenceId.numocts = 0;
   memset(context->conferenceId.data,0,16);
   //added by tony above 2004.12.13
   /* Note Data is not released here. Need to do that. Currently mem leak*/
   dListFreeNodes(&context->outH225ListCtxt, &context->outH225Queue);
   context->outgoing = NULL;
   /*
      Receive socket is closed as windows application does not allow
      more than one call in one run. Can be worked around very easily
   */
#ifdef _WIN32
   //remarked by tony [11/15/2004]
    /*ooSocketClose(context->h225Rx);
	ooSocketsCleanup();*/
   //remarked end
#endif
   OOTRACEINFO2(context, "H225 channel closed");
   return OO_OK;
}

EXTERN int ooCloseRasChannel(struct ooAppContext *context)
{
   OOTRACEINFO2(context, "Closing RAS channel");
   context->sendRas = 0;
   if(context->RASChannel != 0)
   {
     ooSocketClose(context->RASChannel);
   }
   context->RASChannel = 0;
   context->RasChanPort = -1;
   dListFreeNodes(&context->outRasListCtxt, &context->outRasQueue);
   context->outgoingRas = NULL;
   OOTRACEINFO2(context, "Ras channel closed");
   return OO_OK;	
}