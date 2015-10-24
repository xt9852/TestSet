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
#include "oo.h"


int ooSetTCPPorts(struct ooAppContext *context, int start, int max)
{
   if(start < 1024)
      context->tcpPorts.start = 1024;
   else
      context->tcpPorts.start = start;
   if(max > 65500)
      context->tcpPorts.max = 65500;
   else 
      context->tcpPorts.max = max;

   if(context->tcpPorts.max<context->tcpPorts.start)
   {
      OOTRACEERR2(context, "Error: Failed to set tcp ports- "
                           "Max port number less than Start port number");
      return OO_FAILED;
   }
   context->tcpPorts.current = start;
        
   OOTRACEINFO2(context, "TCP port range initialize - successful");
   return OO_OK;
}

/* Sets the range of ports that can be potentially used for UDP
   transport
*/
int ooSetUDPPorts(struct ooAppContext *context, int start, int max)
{
   if(start < 1024)
      context->udpPorts.start = 1024;
   else
      context->udpPorts.start = start;
   if(max > 65500)
      context->udpPorts.max = 65500;
   else 
      context->udpPorts.max = max;
        
   if(context->udpPorts.max<context->udpPorts.start)
   {
      OOTRACEERR2(context, "Error: Failed to set udp ports- Max port number"
                           " less than Start port number");
      return OO_FAILED;
   }
        
   context->udpPorts.current = start;
        
   OOTRACEINFO2(context, "UDP port range initialize - successful");

   return OO_OK;
}

/* Sets the range of ports that can be potentially used for RTP
   RTCP transport
*/
int ooSetRTPPorts(struct ooAppContext *context, int start, int max)
{
   if(start < 1024)
      context->rtpPorts.start = 1024;
   else
      context->rtpPorts.start = start;
   if(max > 65500)
      context->rtpPorts.max = 65500;
   else 
      context->rtpPorts.max = max;
        
   if(context->rtpPorts.max<context->rtpPorts.start)
   {
      OOTRACEERR2(context, "Error: Failed to set rtp ports- Max port number"
                           " less than Start port number");
      return OO_FAILED;
   }
        
   context->rtpPorts.current = start;
   OOTRACEINFO2(context, "RTP port range initialize - successful");
   return OO_OK;
}

/* Get the next port of type TCP/UDP/RTP */
int ooGetNextPort(struct ooAppContext *context, int type)
{
   if(type==OOTCP)
   {
      if(context->tcpPorts.current <= context->tcpPorts.max)
         return context->tcpPorts.current++;
      else
      {
         context->tcpPorts.current = context->tcpPorts.start;
         return context->tcpPorts.current++;
      }
   }
   if(type==OOUDP)
   {
      if(context->udpPorts.current <= context->udpPorts.max)
         return context->udpPorts.current++;
      else
      {
         context->udpPorts.current = context->udpPorts.start;
         return context->udpPorts.current++;
      }
   }
   if(type==OORTP)
   {
      if(context->rtpPorts.current <= context->rtpPorts.max)
         return context->rtpPorts.current++;
      else
      {
         context->rtpPorts.current = context->rtpPorts.start;
         return context->rtpPorts.current++;
      }
   }
   return OO_FAILED;
}

int ooBindPort(struct ooAppContext *context, int type, 
               OOSOCKET socket)
{
   int initialPort, bindPort, ret;
   OOIPADDR ipAddrs;
   char localip[40];
   ooGetLocalIPAddress(localip);
   initialPort = ooGetNextPort(context, type);
   bindPort = initialPort;
   ret= ooSocketStrToAddr (localip, &ipAddrs);
   while(1)
   {
      if((ret=ooSocketBind(socket, ipAddrs, 
                     bindPort))==ASN_OK)
         return bindPort;
      else
      {
         bindPort = ooGetNextPort(context, type);
         if(bindPort == initialPort)
            return OO_FAILED;
      }
   }
}

        
