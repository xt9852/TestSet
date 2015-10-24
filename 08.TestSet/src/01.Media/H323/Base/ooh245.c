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

#include "ooh245.h"
#include "oosndrtp.h"

#ifdef _WIN32
#include <stdlib.h>
#include <time.h>
#endif
static ASN1OBJID gh245ProtocolID = {
  6, { 0, 0, 8, 245, 0, 8 }
};

int ooCreateH245Message(struct ooAppContext *context, int type)
{
   OOCTXT* pctxt = NULL;
   if(context->outgoingH245 != NULL)
   {
      OOTRACEWARN2(context, "Can not create H245 message - message exists");
      return OO_FAILED;
   }

   pctxt = (OOCTXT*)newContext();
   if(pctxt == NULL)
   {
      OOTRACEERR2(context,"ERROR: Failed to allocate ASN1 context for "
                         "outgoing H245 message creation");
      return OO_FAILED;
   }
   context->outgoingH245 = (H245Message*)ASN1MALLOC(pctxt, 
                                             sizeof(H245Message));
   if(context->outgoingH245 == NULL)
   {
      OOTRACEERR2(context,"Failed to allocate memory for h245 message");
      return OO_FAILED;
   }
   else
   {
      memset(context->outgoingH245, 0, sizeof(context->outgoingH245));
      context->outgoingH245->pctxt = pctxt;
      context->outgoingH245->h245Msg.t = type;
      switch(type)
      {
         case  T_H245MultimediaSystemControlMessage_request:
            context->outgoingH245->h245Msg.u.request = 
                                     (H245RequestMessage*)ASN1MALLOC(pctxt,
                                     sizeof(H245RequestMessage));
            /*Check for successful mem allocation, and if successful initialize
              mem to zero*/
            if(context->outgoingH245->h245Msg.u.request == 0)
            {
               OOTRACEERR2(context, "Memory allocation for H.245 request"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingH245->h245Msg.u.request, 0, 
                                              sizeof(H245RequestMessage));
            break;
         case T_H245MultimediaSystemControlMessage_response:
            context->outgoingH245->h245Msg.u.response = 
                                     (H245ResponseMessage*)ASN1MALLOC(pctxt,
                                     sizeof(H245ResponseMessage));
            /*Check for successful mem allocation, and if successful initialize
              mem to zero*/
            if(context->outgoingH245->h245Msg.u.response == 0)
            {
               OOTRACEERR2(context, "Memory allocation for H.245 response"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingH245->h245Msg.u.response, 0, 
                                              sizeof(H245ResponseMessage));

            break;
         case T_H245MultimediaSystemControlMessage_command:
            context->outgoingH245->h245Msg.u.command = 
                                     (H245CommandMessage*)ASN1MALLOC(pctxt,
                                     sizeof(H245CommandMessage));
            /*Check for successful mem allocation, and if successful initialize
              mem to zero*/
            if(context->outgoingH245->h245Msg.u.command == 0)
            {
               OOTRACEERR2(context, "Memory allocation for H.245 command"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingH245->h245Msg.u.command, 0, 
                                       sizeof(H245CommandMessage));
            
            break;
         case T_H245MultimediaSystemControlMessage_indication:
            context->outgoingH245->h245Msg.u.indication = 
                                     (H245IndicationMessage*)ASN1MALLOC(pctxt,
                                     sizeof(H245IndicationMessage));
            /*Check for successful mem allocation, and if successful initialize
              mem to zero*/
            if(context->outgoingH245->h245Msg.u.indication == 0)
            {
               OOTRACEERR2(context, "Memory allocation for H.245 indication"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingH245->h245Msg.u.indication, 0, 
                                              sizeof(H245IndicationMessage));
            break;
         default:
            OOTRACEERR2(context,"ERROR: H245 message type not supported");
      }
      return OO_OK;
   }
}

int ooFreeH245Message(struct ooAppContext *context, H245Message *pmsg)
{
   OOCTXT *pctxt;
   if(pmsg == NULL)
   {
      OOTRACEWARN2(context, "ERROR: No message to free");
      return OO_FAILED;
   }
   if(context->outgoingH245 == pmsg)
      context->outgoingH245 = NULL;

   pctxt = pmsg->pctxt;
   freeContext(pctxt);
   ASN1CRTFREE0(pctxt);
  
   return OO_OK;
}

int ooAddMasterSlaveDetermination(struct ooAppContext *context,
                                  H245MasterSlaveDetermination masterSlave)
{
   H245RequestMessage * request=NULL;
   OOCTXT *pctxt=NULL;

   if(context->outgoingH245 == NULL)
   {
      OOTRACEWARN2(context,"Warning:No outgoing H245 message found");
      return OO_FAILED;
   }

   if(context->outgoingH245->h245Msg.t != 
      T_H245MultimediaSystemControlMessage_request)
   {
      OOTRACEWARN2(context, "Warning: Outgoing H245 message is"
                          " not of type Request");
      return OO_FAILED;
   }

   context->outgoingH245->msgType = OOMasterSlaveDetermination;

   /* Set request type as MasterSlaveDetermination */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEWARN2(context, "Warn: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_masterSlaveDetermination;
   request->u.masterSlaveDetermination = (H245MasterSlaveDetermination*)
                  ASN1MALLOC(pctxt, sizeof(H245MasterSlaveDetermination));   
   memset(request->u.masterSlaveDetermination, 0, 
                                 sizeof(request->u.masterSlaveDetermination));
   request->u.masterSlaveDetermination->terminalType = 
                                 masterSlave.terminalType;
   request->u.masterSlaveDetermination->statusDeterminationNumber = 
                                 masterSlave.statusDeterminationNumber;
#ifndef _COMPACT
   dListInit(&(request->u.masterSlaveDetermination->extElem1));
#endif /* !_COMPACT */
   return OO_OK;
}


int ooGetOutgoingH245Msgbuf(struct ooAppContext *context,
                            ASN1OCTET *msgbuf, int *len, int *msgType)
{
   H245Message *p_h245Msg=NULL;
   H245MultimediaSystemControlMessage *multimediaMsg=NULL;
   DListNode * p_msgNode=NULL;
   int i =0;
   ASN1BOOL aligned =TRUE, trace =FALSE;
   ASN1OCTET encodeBuf[1024];
   ASN1OCTET* encodeptr=NULL;
   int encodeLen=0;
   OOCTXT* pctxt=NULL;
   memset(encodeBuf, 0, sizeof(encodeBuf));

   if(context->outH245Queue.count == 0)
   {
      OOTRACEERR2(context,"ERROR:No outgoing h245 message");
      return OO_FAILED;
   }
   p_msgNode = context->outH245Queue.head;
   p_h245Msg = (H245Message*) p_msgNode->data;
   *msgType = p_h245Msg->msgType;
   multimediaMsg = &(p_h245Msg->h245Msg);
   
   /* Encode the Multimedia Control Message */
   pctxt = p_h245Msg->pctxt;
   setPERBuffer(pctxt, encodeBuf, sizeof(encodeBuf), aligned);

   if(asn1PE_H245MultimediaSystemControlMessage(pctxt, multimediaMsg,context)!=ASN_OK)
   {
      OOTRACEERR2(context, "ERROR: H245 Message encoding failed");
      /* Free memory associated with the message */
      freeContext(pctxt);
      ASN1CRTFREE0(pctxt);
      return OO_FAILED;
   }
   
   encodeptr = encodeGetMsgPtr(pctxt, &encodeLen);
   
   /* Populate message buffer to be returned */
   *len = encodeLen + 4;
   msgbuf[i++] = 3; /* TPKT version */
   msgbuf[i++] = 0; /* TPKT resevred */
   /* 1st octet of length, will be populated once len is determined */
   msgbuf[i++] = (*len>>8); 
   /* 2nd octet of length, will be populated once len is determined */
   msgbuf[i++] = *len;
   memcpy((msgbuf + i), encodeptr, encodeLen);

   /* Remove the message from rtdlist outH245Queue */
   dListRemove(&(context->outH245Queue), p_msgNode);

   /* Free memory associated with the message */
   freeContext(pctxt);
   ASN1CRTFREE0(pctxt);
   
   if(p_msgNode)
      ASN1MEMFREEPTR(&(context->outH245ListCtxt), p_msgNode);      
  
  return OO_OK;
}

/*Added by Karl on 2005-01-17 below*/
//建立接收数据能力表receiveAudioCapability CapabilityTable
int ooSendIntegrationCallTermCapMsg(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245TerminalCapabilitySet *termCap;
   H245AudioCapability *receiveAudioCapG711;
   H245AudioCapability *receiveAudioCapG729A;
   H245AudioCapability *receiveAudioCapG728;
   //H245AudioCapability *receiveAudioCapG7231;
   H245AudioCapability *receiveAudioCapG721;
   H245CapabilityTableEntry *entry1G711;
   H245CapabilityTableEntry *entry1G729A;
   H245CapabilityTableEntry *entry1G728;
   //H245CapabilityTableEntry *entry1G7231;
   H245CapabilityTableEntry *entry1G721;
   H245AlternativeCapabilitySet *altSet1, *altSet2;
   H245CapabilityDescriptor *capDesc;

   ret = ooCreateH245Message(context,  
                             T_H245MultimediaSystemControlMessage_request);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create H245 message");
      return ret;
   }

  /* Set request type as TerminalCapabilitySet */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEERR2(context, "ERROR: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_terminalCapabilitySet;
   request->u.terminalCapabilitySet = (H245TerminalCapabilitySet*)
                  ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySet)); 
   termCap = request->u.terminalCapabilitySet;
   memset(termCap, 0, sizeof(H245TerminalCapabilitySet));
   termCap->m.multiplexCapabilityPresent = 0;
   termCap->m.capabilityTablePresent = 1;
   termCap->m.capabilityDescriptorsPresent = 1;
   termCap->sequenceNumber = 1;
   termCap->protocolIdentifier = gh245ProtocolID; /* protocol id */
   
#ifndef _COMPACT
   dListInit(&(termCapG711->extElem1));
#endif /* !_COMPACT */
   /* Audio G711Ulaw64k capabilities for receive*/
   receiveAudioCapG711 = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCapG711, 0, sizeof(H245AudioCapability));   
   receiveAudioCapG711->t = T_H245AudioCapability_g711Ulaw64k;
   receiveAudioCapG711->u.g711Ulaw64k = 60;  

   /* Add  G711Ulaw64k Capabilities to Capability Table */
   entry1G711 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   //entry2 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
   //                   sizeof(H245CapabilityTableEntry));
   memset(entry1G711, 0, sizeof(H245CapabilityTableEntry));
   //memset(entry2, 0, sizeof(H245CapabilityTableEntry));
   entry1G711->m.capabilityPresent = 1;
   entry1G711->capability.t = T_H245Capability_receiveAudioCapability;
   entry1G711->capability.u.receiveAudioCapability = receiveAudioCapG711;
   entry1G711->capabilityTableEntryNumber = 1; 
   
   dListInit(&(termCap->capabilityTable));
   dListAppend(pctxt , &(termCap->capabilityTable), entry1G711);
   
   /* Audio G729AnnexA capabilities for receive*/
   receiveAudioCapG729A = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCapG729A, 0, sizeof(H245AudioCapability));   
   receiveAudioCapG729A->t = T_H245AudioCapability_g729AnnexA;
   receiveAudioCapG729A->u.g729AnnexA = 60;  

   /* Add  G729AnnexA Capabilities to Capability Table */
   entry1G729A = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   memset(entry1G729A, 0, sizeof(H245CapabilityTableEntry));
   entry1G729A->m.capabilityPresent = 1;
   entry1G729A->capability.t = T_H245Capability_receiveAudioCapability;
   entry1G729A->capability.u.receiveAudioCapability = receiveAudioCapG729A;
   entry1G729A->capabilityTableEntryNumber = 2; 
      
   dListAppend(pctxt , &(termCap->capabilityTable), entry1G729A);   
   
   /* Audio G721 capabilities for receive*/
   receiveAudioCapG721 = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCapG721, 0, sizeof(H245AudioCapability));   
   receiveAudioCapG721->t = T_H245AudioCapability_g721_32k;
   receiveAudioCapG721->u.g721_32k = 60;  

   /* Add  G721 Capabilities to Capability Table */
   entry1G721 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));   
   memset(entry1G721, 0, sizeof(H245CapabilityTableEntry));
   entry1G721->m.capabilityPresent = 1;
   entry1G721->capability.t = T_H245Capability_receiveAudioCapability;
   entry1G721->capability.u.receiveAudioCapability = receiveAudioCapG721;
   entry1G721->capabilityTableEntryNumber = 3; 
   
   dListAppend(pctxt , &(termCap->capabilityTable), entry1G721);

   /* Audio G728 capabilities for receive*/
   receiveAudioCapG728 = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCapG728, 0, sizeof(H245AudioCapability));   
   receiveAudioCapG728->t = T_H245AudioCapability_g728;
   receiveAudioCapG728->u.g728 = 60;  

   /* Add  G728 Capabilities to Capability Table */
   entry1G728 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));   
   memset(entry1G728, 0, sizeof(H245CapabilityTableEntry));
   entry1G728->m.capabilityPresent = 1;
   entry1G728->capability.t = T_H245Capability_receiveAudioCapability;
   entry1G728->capability.u.receiveAudioCapability = receiveAudioCapG728;
   entry1G728->capabilityTableEntryNumber = 4; 
   
   dListAppend(pctxt , &(termCap->capabilityTable), entry1G728);

   /* Add Alternative Capability Set */
   altSet1 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet1, 0, sizeof(H245AlternativeCapabilitySet));
   altSet1->n = 1;
   altSet1->elem[0] = 1;

   altSet2 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet2, 0, sizeof(H245AlternativeCapabilitySet));
   altSet2->n = 1;
   altSet2->elem[0] = 2;

   /* Add capability descriptior */
   capDesc = (H245CapabilityDescriptor*)
             ASN1MALLOC(pctxt, sizeof(H245CapabilityDescriptor));
   memset(capDesc, 0, sizeof(H245CapabilityDescriptor));
   capDesc->m.simultaneousCapabilitiesPresent = 1;
   capDesc->capabilityDescriptorNumber = 0;
   dListInit(&(capDesc->simultaneousCapabilities));
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet1);
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet2);

   dListInit(&(termCap->capabilityDescriptors));
   dListAppend(pctxt, &(termCap->capabilityDescriptors), capDesc);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending terminal capability set message");
   return OO_OK;
}
/*Added by Karl on 2005-01-17 above*/

int ooSendG711CallTermCapMsg(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245TerminalCapabilitySet *termCap;
   H245AudioCapability *receiveAudioCap, *transmitAudioCap;
   H245CapabilityTableEntry *entry1, *entry2;
   H245AlternativeCapabilitySet *altSet1, *altSet2;
   H245CapabilityDescriptor *capDesc;

   ret = ooCreateH245Message(context,  
                             T_H245MultimediaSystemControlMessage_request);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create H245 message");
      return ret;
   }

  /* Set request type as TerminalCapabilitySet */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEERR2(context, "ERROR: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_terminalCapabilitySet;
   request->u.terminalCapabilitySet = (H245TerminalCapabilitySet*)
                  ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySet)); 
   termCap = request->u.terminalCapabilitySet;
   memset(termCap, 0, sizeof(H245TerminalCapabilitySet));
   termCap->m.multiplexCapabilityPresent = 0;
   termCap->m.capabilityTablePresent = 1;
   termCap->m.capabilityDescriptorsPresent = 1;
   /*Modified by karl on 2004-11-19 below*/
   //termCap->sequenceNumber = 1;  
   termCap->sequenceNumber = 12;  //12代表G729
   /*Modified by karl on 2004-11-19 below*/  
   termCap->protocolIdentifier = gh245ProtocolID; /* protocol id */
#ifndef _COMPACT
   dListInit(&(termCap->extElem1));
#endif /* !_COMPACT */
   /* Audio capabilities for receive and transmit */
   receiveAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCap, 0, sizeof(H245AudioCapability));
   transmitAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(transmitAudioCap, 0, sizeof(H245AudioCapability));
   receiveAudioCap->t = T_H245AudioCapability_g711Ulaw64k;
   receiveAudioCap->u.g711Ulaw64k = 240;
   transmitAudioCap->t = T_H245AudioCapability_g711Ulaw64k;
   transmitAudioCap->u.g711Ulaw64k = 240; 

   /* Add  Capabilities to Capability Table */
   entry1 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   entry2 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   memset(entry1, 0, sizeof(H245CapabilityTableEntry));
   memset(entry2, 0, sizeof(H245CapabilityTableEntry));
   entry1->m.capabilityPresent = 1;
   entry1->capability.t = T_H245Capability_receiveAudioCapability;
   entry1->capability.u.receiveAudioCapability = receiveAudioCap;
   entry1->capabilityTableEntryNumber = 1;
   
   entry2->m.capabilityPresent = 1;
   entry2->capability.t =  T_H245Capability_transmitAudioCapability;
   entry2->capability.u.transmitAudioCapability = transmitAudioCap;
   entry2->capabilityTableEntryNumber = 2;
   dListInit(&(termCap->capabilityTable));
   dListAppend(pctxt , &(termCap->capabilityTable), entry1);
   dListAppend(pctxt , &(termCap->capabilityTable), entry2);

   /* Add Alternative Capability Set */
   altSet1 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet1, 0, sizeof(H245AlternativeCapabilitySet));
   altSet1->n = 1;
   altSet1->elem[0] = 1;

   altSet2 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet2, 0, sizeof(H245AlternativeCapabilitySet));
   altSet2->n = 1;
   altSet2->elem[0] = 2;

   /* Add capability descriptior */
   capDesc = (H245CapabilityDescriptor*)
             ASN1MALLOC(pctxt, sizeof(H245CapabilityDescriptor));
   memset(capDesc, 0, sizeof(H245CapabilityDescriptor));
   capDesc->m.simultaneousCapabilitiesPresent = 1;
   capDesc->capabilityDescriptorNumber = 0;
   dListInit(&(capDesc->simultaneousCapabilities));
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet1);
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet2);

   dListInit(&(termCap->capabilityDescriptors));
   dListAppend(pctxt, &(termCap->capabilityDescriptors), capDesc);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending terminal capability set message");
   return OO_OK;
}

/*Added by Karl on 2004-11-15 below*/
int ooSendG729ACallTermCapMsg(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245TerminalCapabilitySet *termCap;
   H245AudioCapability *receiveAudioCap, *transmitAudioCap;
   H245CapabilityTableEntry *entry1, *entry2;
   H245AlternativeCapabilitySet *altSet1, *altSet2;
   H245CapabilityDescriptor *capDesc;

   ret = ooCreateH245Message(context,  
                             T_H245MultimediaSystemControlMessage_request);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create H245 message");
      return ret;
   }

  /* Set request type as TerminalCapabilitySet */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEERR2(context, "ERROR: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_terminalCapabilitySet;
   request->u.terminalCapabilitySet = (H245TerminalCapabilitySet*)
                  ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySet)); 
   termCap = request->u.terminalCapabilitySet;
   memset(termCap, 0, sizeof(H245TerminalCapabilitySet));
   termCap->m.multiplexCapabilityPresent = 0;
   termCap->m.capabilityTablePresent = 1;
   termCap->m.capabilityDescriptorsPresent = 1;
   /*Modified by karl on 2004-11-19 below*/
   //termCap->sequenceNumber = 1;  
   termCap->sequenceNumber = 12;  //12代表G729
   /*Modified by karl on 2004-11-19 below*/
   termCap->protocolIdentifier = gh245ProtocolID; /* protocol id */
#ifndef _COMPACT
   dListInit(&(termCap->extElem1));
#endif /* !_COMPACT */
   /* Audio capabilities for receive and transmit */
   receiveAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCap, 0, sizeof(H245AudioCapability));
   transmitAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(transmitAudioCap, 0, sizeof(H245AudioCapability));
   receiveAudioCap->t = T_H245AudioCapability_g729AnnexA;
   receiveAudioCap->u.g729AnnexA = 240;
   transmitAudioCap->t = T_H245AudioCapability_g729AnnexA;
   transmitAudioCap->u.g729AnnexA = 240; 

   /* Add  Capabilities to Capability Table */
   entry1 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   entry2 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   memset(entry1, 0, sizeof(H245CapabilityTableEntry));
   memset(entry2, 0, sizeof(H245CapabilityTableEntry));
   entry1->m.capabilityPresent = 1;
   entry1->capability.t = T_H245Capability_receiveAudioCapability;
   entry1->capability.u.receiveAudioCapability = receiveAudioCap;
   entry1->capabilityTableEntryNumber = 1;
   
   entry2->m.capabilityPresent = 1;
   entry2->capability.t =  T_H245Capability_transmitAudioCapability;
   entry2->capability.u.transmitAudioCapability = transmitAudioCap;
   entry2->capabilityTableEntryNumber = 2;
   dListInit(&(termCap->capabilityTable));
   dListAppend(pctxt , &(termCap->capabilityTable), entry1);
   dListAppend(pctxt , &(termCap->capabilityTable), entry2);

   /* Add Alternative Capability Set */
   altSet1 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet1, 0, sizeof(H245AlternativeCapabilitySet));
   altSet1->n = 1;
   altSet1->elem[0] = 1;

   altSet2 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet2, 0, sizeof(H245AlternativeCapabilitySet));
   altSet2->n = 1;
   altSet2->elem[0] = 2;

   /* Add capability descriptior */
   capDesc = (H245CapabilityDescriptor*)
             ASN1MALLOC(pctxt, sizeof(H245CapabilityDescriptor));
   memset(capDesc, 0, sizeof(H245CapabilityDescriptor));
   capDesc->m.simultaneousCapabilitiesPresent = 1;
   capDesc->capabilityDescriptorNumber = 0;
   dListInit(&(capDesc->simultaneousCapabilities));
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet1);
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet2);

   dListInit(&(termCap->capabilityDescriptors));
   dListAppend(pctxt, &(termCap->capabilityDescriptors), capDesc);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending terminal capability set message");
   return OO_OK;
}
/*Added by Karl on 2004-11-15 above*/

/*Modified by Karl on 2004-11-16 below*/
int ooSendG711TransmitTermCapMsg(struct ooAppContext *context)
/*Modified by Karl on 2004-11-16 Above*/
{//本函数代码是孤代码,没有用到
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245TerminalCapabilitySet *termCap;
   H245AudioCapability *transmitAudioCap;
   H245CapabilityTableEntry *entry1;
   H245AlternativeCapabilitySet *altSet1;
   H245CapabilityDescriptor *capDesc;

   ret = ooCreateH245Message(context,  
                             T_H245MultimediaSystemControlMessage_request);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create H245 message");
      return ret;
   }

  /* Set request type as TerminalCapabilitySet */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEERR2(context, "ERROR: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_terminalCapabilitySet;
   request->u.terminalCapabilitySet = (H245TerminalCapabilitySet*)
                  ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySet)); 
   termCap = request->u.terminalCapabilitySet;
   memset(termCap, 0, sizeof(H245TerminalCapabilitySet));
   termCap->m.multiplexCapabilityPresent = 0;
   termCap->m.capabilityTablePresent = 1;
   termCap->m.capabilityDescriptorsPresent = 1;
   termCap->sequenceNumber = 12;//代表G729能力协商
   termCap->protocolIdentifier = gh245ProtocolID;
#ifndef _COMPACT
   dListInit(&(termCap->extElem1));
#endif /* !_COMPACT */
   /* Define transmit audio capability */
   transmitAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(transmitAudioCap, 0, sizeof(H245AudioCapability));
   transmitAudioCap->t = T_H245AudioCapability_g711Ulaw64k;
   transmitAudioCap->u.g711Ulaw64k = 240; 

   /* Add transmit audio capability to Capability Table */
   entry1 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   memset(entry1, 0, sizeof(H245CapabilityTableEntry));
   entry1->m.capabilityPresent = 1;
   entry1->capability.t =  T_H245Capability_transmitAudioCapability;
   entry1->capability.u.transmitAudioCapability = transmitAudioCap;
   entry1->capabilityTableEntryNumber = 1;
   dListInit(&(termCap->capabilityTable));
   dListAppend(pctxt , &(termCap->capabilityTable), entry1);
   
   /* Add Alternative Capability Set */
   
   altSet1 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet1, 0, sizeof(H245AlternativeCapabilitySet));
   altSet1->n = 1;
   altSet1->elem[0] = 1;
   /* Add capability descriptor */
   capDesc = (H245CapabilityDescriptor*)
             ASN1MALLOC(pctxt, sizeof(H245CapabilityDescriptor));
   memset(capDesc, 0, sizeof(H245CapabilityDescriptor));
   capDesc->m.simultaneousCapabilitiesPresent = 1;
   capDesc->capabilityDescriptorNumber = 0;
   dListInit(&(capDesc->simultaneousCapabilities));
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet1);
   
   dListInit(&(termCap->capabilityDescriptors));
   dListAppend(pctxt, &(termCap->capabilityDescriptors), capDesc);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending terminal capability set message");
   return OO_OK;
}
/*Added by Karl on 2004-11-26 below*/
int ooSendG721CallTermCapMsg(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245TerminalCapabilitySet *termCap;
   H245AudioCapability *receiveAudioCap, *transmitAudioCap;
   H245CapabilityTableEntry *entry1, *entry2;
   H245AlternativeCapabilitySet *altSet1, *altSet2;
   H245CapabilityDescriptor *capDesc;

   ret = ooCreateH245Message(context,  
                             T_H245MultimediaSystemControlMessage_request);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create H245 message");
      return ret;
   }

  /* Set request type as TerminalCapabilitySet */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEERR2(context, "ERROR: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_terminalCapabilitySet;
   request->u.terminalCapabilitySet = (H245TerminalCapabilitySet*)
                  ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySet)); 
   termCap = request->u.terminalCapabilitySet;
   memset(termCap, 0, sizeof(H245TerminalCapabilitySet));
   termCap->m.multiplexCapabilityPresent = 0;
   termCap->m.capabilityTablePresent = 1;
   termCap->m.capabilityDescriptorsPresent = 1;   
   termCap->sequenceNumber = 12;  //12代表G729能力协商
   termCap->protocolIdentifier = gh245ProtocolID; /* protocol id */
#ifndef _COMPACT
   dListInit(&(termCap->extElem1));
#endif /* !_COMPACT */
   /* Audio capabilities for receive and transmit */
   receiveAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCap, 0, sizeof(H245AudioCapability));
   transmitAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(transmitAudioCap, 0, sizeof(H245AudioCapability));
   receiveAudioCap->t = T_H245AudioCapability_g721_32k;
   receiveAudioCap->u.g721_32k = 240;
   transmitAudioCap->t = T_H245AudioCapability_g721_32k;
   transmitAudioCap->u.g721_32k = 240; 

   /* Add  Capabilities to Capability Table */
   entry1 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   entry2 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   memset(entry1, 0, sizeof(H245CapabilityTableEntry));
   memset(entry2, 0, sizeof(H245CapabilityTableEntry));
   entry1->m.capabilityPresent = 1;
   entry1->capability.t = T_H245Capability_receiveAudioCapability;
   entry1->capability.u.receiveAudioCapability = receiveAudioCap;
   entry1->capabilityTableEntryNumber = 1;
   
   entry2->m.capabilityPresent = 1;
   entry2->capability.t =  T_H245Capability_transmitAudioCapability;
   entry2->capability.u.transmitAudioCapability = transmitAudioCap;
   entry2->capabilityTableEntryNumber = 2;
   dListInit(&(termCap->capabilityTable));
   dListAppend(pctxt , &(termCap->capabilityTable), entry1);
   dListAppend(pctxt , &(termCap->capabilityTable), entry2);

   /* Add Alternative Capability Set */
   altSet1 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet1, 0, sizeof(H245AlternativeCapabilitySet));
   altSet1->n = 1;
   altSet1->elem[0] = 1;

   altSet2 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet2, 0, sizeof(H245AlternativeCapabilitySet));
   altSet2->n = 1;
   altSet2->elem[0] = 2;

   /* Add capability descriptior */
   capDesc = (H245CapabilityDescriptor*)
             ASN1MALLOC(pctxt, sizeof(H245CapabilityDescriptor));
   memset(capDesc, 0, sizeof(H245CapabilityDescriptor));
   capDesc->m.simultaneousCapabilitiesPresent = 1;
   capDesc->capabilityDescriptorNumber = 0;
   dListInit(&(capDesc->simultaneousCapabilities));
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet1);
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet2);

   dListInit(&(termCap->capabilityDescriptors));
   dListAppend(pctxt, &(termCap->capabilityDescriptors), capDesc);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending terminal capability set message");
   return OO_OK;
}
/*Added by Karl on 2004-11-26 above*/
/*Added by Karl on 2005-01-13 below*/
int ooSendG728CallTermCapMsg(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245TerminalCapabilitySet *termCap;
   H245AudioCapability *receiveAudioCap, *transmitAudioCap;
   H245CapabilityTableEntry *entry1, *entry2;
   H245AlternativeCapabilitySet *altSet1, *altSet2;
   H245CapabilityDescriptor *capDesc;

   ret = ooCreateH245Message(context,  
                             T_H245MultimediaSystemControlMessage_request);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create H245 message");
      return ret;
   }

  /* Set request type as TerminalCapabilitySet */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEERR2(context, "ERROR: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_terminalCapabilitySet;
   request->u.terminalCapabilitySet = (H245TerminalCapabilitySet*)
                  ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySet)); 
   termCap = request->u.terminalCapabilitySet;
   memset(termCap, 0, sizeof(H245TerminalCapabilitySet));
   termCap->m.multiplexCapabilityPresent = 0;
   termCap->m.capabilityTablePresent = 1;
   termCap->m.capabilityDescriptorsPresent = 1;   
   termCap->sequenceNumber = 12;  //12代表G729能力协商
   termCap->protocolIdentifier = gh245ProtocolID; /* protocol id */
#ifndef _COMPACT
   dListInit(&(termCap->extElem1));
#endif /* !_COMPACT */
   /* Audio capabilities for receive and transmit */
   receiveAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCap, 0, sizeof(H245AudioCapability));
   transmitAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(transmitAudioCap, 0, sizeof(H245AudioCapability));
   receiveAudioCap->t = T_H245AudioCapability_g728;
   receiveAudioCap->u.g728 = 240;
   transmitAudioCap->t = T_H245AudioCapability_g728;
   transmitAudioCap->u.g728 = 240; 

   /* Add  Capabilities to Capability Table */
   entry1 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   entry2 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   memset(entry1, 0, sizeof(H245CapabilityTableEntry));
   memset(entry2, 0, sizeof(H245CapabilityTableEntry));
   entry1->m.capabilityPresent = 1;
   entry1->capability.t = T_H245Capability_receiveAudioCapability;
   entry1->capability.u.receiveAudioCapability = receiveAudioCap;
   entry1->capabilityTableEntryNumber = 1;
   
   entry2->m.capabilityPresent = 1;
   entry2->capability.t =  T_H245Capability_transmitAudioCapability;
   entry2->capability.u.transmitAudioCapability = transmitAudioCap;
   entry2->capabilityTableEntryNumber = 2;
   dListInit(&(termCap->capabilityTable));
   dListAppend(pctxt , &(termCap->capabilityTable), entry1);
   dListAppend(pctxt , &(termCap->capabilityTable), entry2);

   /* Add Alternative Capability Set */
   altSet1 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet1, 0, sizeof(H245AlternativeCapabilitySet));
   altSet1->n = 1;
   altSet1->elem[0] = 1;

   altSet2 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet2, 0, sizeof(H245AlternativeCapabilitySet));
   altSet2->n = 1;
   altSet2->elem[0] = 2;

   /* Add capability descriptior */
   capDesc = (H245CapabilityDescriptor*)
             ASN1MALLOC(pctxt, sizeof(H245CapabilityDescriptor));
   memset(capDesc, 0, sizeof(H245CapabilityDescriptor));
   capDesc->m.simultaneousCapabilitiesPresent = 1;
   capDesc->capabilityDescriptorNumber = 0;
   dListInit(&(capDesc->simultaneousCapabilities));
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet1);
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet2);

   dListInit(&(termCap->capabilityDescriptors));
   dListAppend(pctxt, &(termCap->capabilityDescriptors), capDesc);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending terminal capability set message");
   return OO_OK;
}
int ooSendG7231CallTermCapMsg(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245TerminalCapabilitySet *termCap;
   H245AudioCapability *receiveAudioCap, *transmitAudioCap;
   H245CapabilityTableEntry *entry1, *entry2;
   H245AlternativeCapabilitySet *altSet1, *altSet2;
   H245CapabilityDescriptor *capDesc;

   ret = ooCreateH245Message(context,  
                             T_H245MultimediaSystemControlMessage_request);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create H245 message");
      return ret;
   }

  /* Set request type as TerminalCapabilitySet */
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));
   if(request == NULL)
   {
      OOTRACEERR2(context, "ERROR: No memory allocated for request message");
      return OO_FAILED;
   }

   request->t = T_H245RequestMessage_terminalCapabilitySet;
   request->u.terminalCapabilitySet = (H245TerminalCapabilitySet*)
                  ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySet)); 
   termCap = request->u.terminalCapabilitySet;
   memset(termCap, 0, sizeof(H245TerminalCapabilitySet));
   termCap->m.multiplexCapabilityPresent = 0;
   termCap->m.capabilityTablePresent = 1;
   termCap->m.capabilityDescriptorsPresent = 1;   
   termCap->sequenceNumber = 12;  //12代表G729能力协商
   termCap->protocolIdentifier = gh245ProtocolID; /* protocol id */
#ifndef _COMPACT
   dListInit(&(termCap->extElem1));
#endif /* !_COMPACT */
   /* Audio capabilities for receive and transmit */
   receiveAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(receiveAudioCap, 0, sizeof(H245AudioCapability));
   transmitAudioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                      sizeof(H245AudioCapability));
   memset(transmitAudioCap, 0, sizeof(H245AudioCapability));
   receiveAudioCap->t = T_H245AudioCapability_g7231;   
   receiveAudioCap->u.g7231->maxAl_sduAudioFrames = 240;
   receiveAudioCap->u.g7231->silenceSuppression = 0;
   transmitAudioCap->t = T_H245AudioCapability_g7231;
   transmitAudioCap->u.g7231->maxAl_sduAudioFrames = 240; 
   transmitAudioCap->u.g7231->silenceSuppression = 0;

   /* Add  Capabilities to Capability Table */
   entry1 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   entry2 = (H245CapabilityTableEntry*) ASN1MALLOC(pctxt,
                      sizeof(H245CapabilityTableEntry));
   memset(entry1, 0, sizeof(H245CapabilityTableEntry));
   memset(entry2, 0, sizeof(H245CapabilityTableEntry));
   entry1->m.capabilityPresent = 1;
   entry1->capability.t = T_H245Capability_receiveAudioCapability;
   entry1->capability.u.receiveAudioCapability = receiveAudioCap;
   entry1->capabilityTableEntryNumber = 1;
   
   entry2->m.capabilityPresent = 1;
   entry2->capability.t =  T_H245Capability_transmitAudioCapability;
   entry2->capability.u.transmitAudioCapability = transmitAudioCap;
   entry2->capabilityTableEntryNumber = 2;
   dListInit(&(termCap->capabilityTable));
   dListAppend(pctxt , &(termCap->capabilityTable), entry1);
   dListAppend(pctxt , &(termCap->capabilityTable), entry2);

   /* Add Alternative Capability Set */
   altSet1 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet1, 0, sizeof(H245AlternativeCapabilitySet));
   altSet1->n = 1;
   altSet1->elem[0] = 1;

   altSet2 = (H245AlternativeCapabilitySet*)
             ASN1MALLOC(pctxt, sizeof(H245AlternativeCapabilitySet));
   memset(altSet2, 0, sizeof(H245AlternativeCapabilitySet));
   altSet2->n = 1;
   altSet2->elem[0] = 2;

   /* Add capability descriptior */
   capDesc = (H245CapabilityDescriptor*)
             ASN1MALLOC(pctxt, sizeof(H245CapabilityDescriptor));
   memset(capDesc, 0, sizeof(H245CapabilityDescriptor));
   capDesc->m.simultaneousCapabilitiesPresent = 1;
   capDesc->capabilityDescriptorNumber = 0;
   dListInit(&(capDesc->simultaneousCapabilities));
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet1);
   dListAppend(pctxt, &(capDesc->simultaneousCapabilities), altSet2);

   dListInit(&(termCap->capabilityDescriptors));
   dListAppend(pctxt, &(termCap->capabilityDescriptors), capDesc);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending terminal capability set message");
   return OO_OK;
}
/*Added by Karl on 2005-01-13 above*/

int ooH245AcknowledgeTerminalCapabilitySet(struct ooAppContext *context,
                                           H245SequenceNumber seqNo)
{
   H245ResponseMessage * response=NULL;
   OOCTXT *pctxt=NULL;
   int ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_response);
   if(ret != OO_OK)
   {
      OOTRACEERR2(context, "ERROR:H245 message creation failed for - "
                           "TerminalCapability Set Ack");
      return OO_FAILED;
   }
   context->outgoingH245->msgType = OOTerminalCapabilitySetAck;
   response = context->outgoingH245->h245Msg.u.response;
   memset(response, 0, sizeof(H245ResponseMessage));
   pctxt = context->outgoingH245->pctxt;
   response->t = T_H245ResponseMessage_terminalCapabilitySetAck;
   
   response->u.terminalCapabilitySetAck = (H245TerminalCapabilitySetAck*)
                   ASN1MALLOC(pctxt, sizeof(H245TerminalCapabilitySetAck));

   memset(response->u.terminalCapabilitySetAck, 0, 
                                 sizeof(response->u.terminalCapabilitySetAck));
   response->u.terminalCapabilitySetAck->sequenceNumber = seqNo;
#ifndef _COMPACT
   dListInit(&(response->u.terminalCapabilitySetAck->extElem1));   
#endif /* !_COMPACT */
   ooSendH245Msg(context);
   return OO_OK;
}


ASN1UINT ooGenerateStatusDeterminationNumber()
{
   ASN1UINT statusDeterminationNumber;
   unsigned int seed = 1876;   
#ifndef _WIN32   
   srandom(time(0));
   statusDeterminationNumber = random()%16777215;
#else
   srand((unsigned)time( NULL ) );
   statusDeterminationNumber = rand()%16777215;
#endif
   return statusDeterminationNumber;
}

int ooHandleMasterSlave(struct ooAppContext *context, void * pmsg, 
                          int msgType)
{
   H245MasterSlaveDetermination *masterSlave;
   H245MasterSlaveDeterminationAck *masterSlaveAck;
   ASN1UINT statusDeterminationNumber;
   int attempts;
   switch(msgType)
   {
      case OOMasterSlaveDetermination:
         OOTRACEINFO2(context, "Master Slave Determination received");
     /*    if(context->ooMasterSlaveState != OO_MasterSlave_Idle)
         {
            OOTRACEDBGA2(context, "Master Slave Determination Already "
                                  "in progress");
            return OO_OK;
         }*/
         context->ooMasterSlaveState = OO_MasterSlave_DetermineReceived;
         masterSlave = (H245MasterSlaveDetermination*)pmsg;
         
         if(masterSlave->terminalType < OOTERMTYPE)
         {
            ooSendMasterSlaveDeterminationAck(context, "slave");
            context->ooMasterSlaveState =  OO_MasterSlave_AckSent;
            return OO_OK;
         }
         if(masterSlave->terminalType > OOTERMTYPE)
         {
            ooSendMasterSlaveDeterminationAck(context, "master");
            context->ooMasterSlaveState =  OO_MasterSlave_AckSent;
            return OO_OK;
         }
         /* Since term types are same, master slave determination will
            be done based on statusdetermination number
         */
         for(attempts = 0; attempts <3; attempts++)
         {
            OOTRACEDBGA2(context,"Determining master-slave ");
            statusDeterminationNumber = 
                              ooGenerateStatusDeterminationNumber();
            if(masterSlave->statusDeterminationNumber < 
                          statusDeterminationNumber)
            {
               ooSendMasterSlaveDeterminationAck(context, "slave");
               context->ooMasterSlaveState =  OO_MasterSlave_AckSent;
               return OO_OK;
            }
            if(masterSlave->statusDeterminationNumber > 
                            statusDeterminationNumber)
            {
               ooSendMasterSlaveDeterminationAck(context, "master");
               context->ooMasterSlaveState =  OO_MasterSlave_AckSent;
               return OO_OK;
            }
         }
         
         if(attempts == 3)
         {
            OOTRACEWARN2(context,"Warn: Failed to determine master-slave - "
                                 " default slave");
            ooSendMasterSlaveDeterminationAck(context, "master");
            context->ooMasterSlaveState =  OO_MasterSlave_AckSent;
            return OO_OK;
         }
         break;
      case OOMasterSlaveAck:
         masterSlaveAck = (H245MasterSlaveDeterminationAck*)pmsg;
         if(context->ooMasterSlaveState == OO_MasterSlave_AckSent)
         {
            if(masterSlaveAck->decision.t == 
                    T_H245MasterSlaveDeterminationAck_decision_master)
               context->ooMasterSlaveState = OO_MasterSlave_Master;
            else
               context->ooMasterSlaveState = OO_MasterSlave_Slave;

            return OO_OK;
         }
         if(context->ooMasterSlaveState == OO_MasterSlave_DetermineSent)
         {
            if(masterSlaveAck->decision.t == 
               T_H245MasterSlaveDeterminationAck_decision_master)
            {
               ooSendMasterSlaveDeterminationAck(context, "slave");
               context->ooMasterSlaveState =  OO_MasterSlave_Master;
               return OO_OK;
            }
            else
            {
               ooSendMasterSlaveDeterminationAck(context, "master");
               context->ooMasterSlaveState = OO_MasterSlave_Slave;
               return OO_OK;
            }
         }
         break;
       default:
          OOTRACEWARN2(context,"Warn:Unhandled Master Slave message received");
   }
   return OO_OK;      
}

int ooSendMasterSlaveDetermination(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage h245Message;
   H245MasterSlaveDetermination masterSlave;
   memset(&masterSlave, 0, sizeof(masterSlave));
   if(context->ooMasterSlaveState != OO_MasterSlave_Idle)
   {
      OOTRACEINFO3(context, "MasterSlave determination already in progress %d",                             context->ooMasterSlaveState);
      return OO_FAILED;
   }
    h245Message.t = T_H245RequestMessage_masterSlaveDetermination;
   
   masterSlave.terminalType = OOTERMTYPE; 
   masterSlave.statusDeterminationNumber = 
                       ooGenerateStatusDeterminationNumber();
#ifndef _COMPACT
   dListInit(&(masterSlave.extElem1));
#endif /* !_COMPACT */   
   ret = ooCreateH245Message(context,
                   T_H245MultimediaSystemControlMessage_request);
   if(ret != OO_OK)
   {
      OOTRACEERR2(context, "Error: creating H245 message - Master"
                           " Slave Determination");
      return OO_FAILED;
   }
          
   ret = ooAddMasterSlaveDetermination(context, masterSlave);
   if(ret != OO_OK)
   {
      OOTRACEERR2(context, "Error: Adding Master Slave determination to"
                           " outgoing message");
      return OO_FAILED;
   }
   OOTRACEINFO2(context, "Sending MasterSlave Determination");
   ooSendH245Msg(context);
   context->ooMasterSlaveState = OO_MasterSlave_DetermineSent;
   return OO_OK;
}

int ooSendMasterSlaveDeterminationAck(struct ooAppContext *context,
                                      char * status)
{
   int ret=0;
   H245ResponseMessage * response=NULL;
   OOCTXT *pctxt=NULL;

   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_response);
   if(ret != OO_OK)
   {
      OOTRACEERR2(context, "Error:H245 message creation failed for -"
                           " MasterSlave Determination Ack");
      return OO_FAILED;
   }
   context->outgoingH245->msgType = OOMasterSlaveAck;
   response = context->outgoingH245->h245Msg.u.response;
   memset(response, 0, sizeof(H245ResponseMessage));
   pctxt = context->outgoingH245->pctxt;
   response->t = T_H245ResponseMessage_masterSlaveDeterminationAck;
   response->u.masterSlaveDeterminationAck = (H245MasterSlaveDeterminationAck*)
                   ASN1MALLOC(pctxt, sizeof(H245MasterSlaveDeterminationAck));
   memset(response->u.masterSlaveDeterminationAck, 0, 
                             sizeof(response->u.masterSlaveDeterminationAck));
   if(!strcmp("master", status))
      response->u.masterSlaveDeterminationAck->decision.t = 
                         T_H245MasterSlaveDeterminationAck_decision_master;
   else
      response->u.masterSlaveDeterminationAck->decision.t = 
                         T_H245MasterSlaveDeterminationAck_decision_slave;
   
#ifndef _COMPACT
   dListInit(&(response->u.masterSlaveDeterminationAck->extElem1));
#endif /* !_COMPACT */
   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending MasterSlave determination Ack");
   return OO_OK;
}

/*Added by Karl on 2004-11-15 below */
int ooOpeng729AnnexALogicalChannel(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245OpenLogicalChannel_forwardLogicalChannelParameters *flcp;
   H245AudioCapability *audioCap;
   H245H2250LogicalChannelParameters *h2250lcp;
   H245UnicastAddress *unicastAddrs;
   H245UnicastAddress_iPAddress *iPAddress;
   char localip[20];
   char hexip[20];
   int addr_part1, addr_part2, addr_part3, addr_part4;

   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_request);
   if(ret != OO_OK)
   {
	  OOTRACEERR3(context, "Error: H245 message creation failed for - %s",
                           "Open G729Annex channel");
      return OO_FAILED;
   }

   context->outgoingH245->msgType = OOOpenLogicalChannel;
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));

   request->t = T_H245RequestMessage_openLogicalChannel;
   request->u.openLogicalChannel = (H245OpenLogicalChannel*)
                     ASN1MALLOC(pctxt, sizeof(H245OpenLogicalChannel));
   memset(request->u.openLogicalChannel, 0, 
                                     sizeof(request->u.openLogicalChannel));
   request->u.openLogicalChannel->forwardLogicalChannelNumber = 1;
   
#ifndef _COMPACT
   dListInit(&(request->u.openLogicalChannel->extElem1));
#endif /* !_COMPACT */
   /* Populate H245OpenLogicalChannel_ForwardLogicalChannel Parameters*/
   flcp = &(request->u.openLogicalChannel->forwardLogicalChannelParameters);
   flcp->m.portNumberPresent = 0;
   flcp->m.forwardLogicalChannelDependencyPresent = 0;
   flcp->m.replacementForPresent = 0;

#ifndef _COMPACT
   dListInit(&(flcp->extElem1));
#endif /* !_COMPACT */
   /* data type of channel is audio */
   flcp->dataType.t = T_H245DataType_audioData;

   /* set audio capability for channel */
   audioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                                     sizeof(H245AudioCapability));
   memset(audioCap, 0, sizeof(audioCap));
   audioCap->t = T_H245AudioCapability_g729AnnexA;
   audioCap->u.g729AnnexA = 30; /* 30 frames per packet */
   
   flcp->dataType.u.audioData = audioCap;
   flcp->multiplexParameters.t = 
      T_H245OpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters;
   flcp->multiplexParameters.u.h2250LogicalChannelParameters = 
                         (H245H2250LogicalChannelParameters*)ASN1MALLOC(pctxt, 
                          sizeof(H245H2250LogicalChannelParameters));

   h2250lcp = flcp->multiplexParameters.u.h2250LogicalChannelParameters;
   memset(h2250lcp, 0, sizeof(h2250lcp));

#ifndef _COMPACT
   dListInit(&(h2250lcp->extElem1));
#endif /* !_COMPACT */

   h2250lcp->sessionID = 1;
   h2250lcp->mediaGuaranteedDelivery = 0;
   h2250lcp->silenceSuppression = 0;
   h2250lcp->m.mediaControlChannelPresent = 1;
   
   h2250lcp->mediaControlChannel.t = 
                                 T_H245TransportAddress_unicastAddress;
   h2250lcp->mediaControlChannel.u.unicastAddress =  (H245UnicastAddress*)
                         ASN1MALLOC(pctxt, sizeof(H245UnicastAddress));

   unicastAddrs = h2250lcp->mediaControlChannel.u.unicastAddress;
   memset(unicastAddrs, 0, sizeof(unicastAddrs));
   unicastAddrs->t = T_H245UnicastAddress_iPAddress;
   unicastAddrs->u.iPAddress = (H245UnicastAddress_iPAddress*)
               ASN1MALLOC(pctxt, sizeof(H245UnicastAddress_iPAddress));
   iPAddress = unicastAddrs->u.iPAddress;
   memset(iPAddress, 0, sizeof(iPAddress));

#ifndef _COMPACT
   dListInit(&(iPAddress->extElem1));
#endif /* !_COMPACT */

   ooGetLocalIPAddress(localip);
   sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3,
                                  &addr_part4);
   sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
                                 addr_part4);
   sscanf(hexip, "%x %x %x %x", &(iPAddress->network.data[0]),
                                &(iPAddress->network.data[1]), 
                                &(iPAddress->network.data[2]), 
                                &(iPAddress->network.data[3]));
   iPAddress->network.numocts = 4;
   iPAddress->tsapIdentifier = ooGetLocalRtcpPort(context);
   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending OpenLogicalChannel");
   return OO_OK;
}
/*Added by Karl on 2004-11-15 above */

int ooOpeng711ulawLogicalChannel(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245OpenLogicalChannel_forwardLogicalChannelParameters *flcp;
   H245AudioCapability *audioCap;
   H245H2250LogicalChannelParameters *h2250lcp;
   H245UnicastAddress *unicastAddrs;
   H245UnicastAddress_iPAddress *iPAddress;
   char localip[20];
   char hexip[20];
   int addr_part1, addr_part2, addr_part3, addr_part4;

   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_request);
   if(ret != OO_OK)
   {
      OOTRACEERR3(context, "Error: H245 message creation failed for - %s",
                           "Open G711 u law channel");
      return OO_FAILED;
   }

   context->outgoingH245->msgType = OOOpenLogicalChannel;
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));

   request->t = T_H245RequestMessage_openLogicalChannel;
   request->u.openLogicalChannel = (H245OpenLogicalChannel*)
                     ASN1MALLOC(pctxt, sizeof(H245OpenLogicalChannel));
   memset(request->u.openLogicalChannel, 0, 
                                     sizeof(request->u.openLogicalChannel));
   request->u.openLogicalChannel->forwardLogicalChannelNumber = 1;
   
#ifndef _COMPACT
   dListInit(&(request->u.openLogicalChannel->extElem1));
#endif /* !_COMPACT */
   /* Populate H245OpenLogicalChannel_ForwardLogicalChannel Parameters*/
   flcp = &(request->u.openLogicalChannel->forwardLogicalChannelParameters);
   flcp->m.portNumberPresent = 0;
   flcp->m.forwardLogicalChannelDependencyPresent = 0;
   flcp->m.replacementForPresent = 0;

#ifndef _COMPACT
   dListInit(&(flcp->extElem1));
#endif /* !_COMPACT */
   /* data type of channel is audio */
   flcp->dataType.t = T_H245DataType_audioData;

   /* set audio capability for channel */
   audioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                                     sizeof(H245AudioCapability));
   memset(audioCap, 0, sizeof(audioCap));
   audioCap->t = T_H245AudioCapability_g711Ulaw64k;
   audioCap->u.g711Ulaw64k = 30; /* 30 frames per packet */
   
   flcp->dataType.u.audioData = audioCap;
   flcp->multiplexParameters.t = 
      T_H245OpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters;
   flcp->multiplexParameters.u.h2250LogicalChannelParameters = 
                         (H245H2250LogicalChannelParameters*)ASN1MALLOC(pctxt, 
                          sizeof(H245H2250LogicalChannelParameters));

   h2250lcp = flcp->multiplexParameters.u.h2250LogicalChannelParameters;
   memset(h2250lcp, 0, sizeof(h2250lcp));

#ifndef _COMPACT
   dListInit(&(h2250lcp->extElem1));
#endif /* !_COMPACT */

   h2250lcp->sessionID = 1;
   h2250lcp->mediaGuaranteedDelivery = 0;
   h2250lcp->silenceSuppression = 0;
   h2250lcp->m.mediaControlChannelPresent = 1;
   
   h2250lcp->mediaControlChannel.t = 
                                 T_H245TransportAddress_unicastAddress;
   h2250lcp->mediaControlChannel.u.unicastAddress =  (H245UnicastAddress*)
                         ASN1MALLOC(pctxt, sizeof(H245UnicastAddress));

   unicastAddrs = h2250lcp->mediaControlChannel.u.unicastAddress;
   memset(unicastAddrs, 0, sizeof(unicastAddrs));
   unicastAddrs->t = T_H245UnicastAddress_iPAddress;
   unicastAddrs->u.iPAddress = (H245UnicastAddress_iPAddress*)
               ASN1MALLOC(pctxt, sizeof(H245UnicastAddress_iPAddress));
   iPAddress = unicastAddrs->u.iPAddress;
   memset(iPAddress, 0, sizeof(iPAddress));

#ifndef _COMPACT
   dListInit(&(iPAddress->extElem1));
#endif /* !_COMPACT */

   ooGetLocalIPAddress(localip);
   sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3,
                                  &addr_part4);
   sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
                                 addr_part4);
   sscanf(hexip, "%x %x %x %x", &(iPAddress->network.data[0]),
                                &(iPAddress->network.data[1]), 
                                &(iPAddress->network.data[2]), 
                                &(iPAddress->network.data[3]));
   iPAddress->network.numocts = 4;
   iPAddress->tsapIdentifier = ooGetLocalRtcpPort(context);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending OpenLogicalChannel");
   return OO_OK;
}   
/*Added by Karl on 2005-01-14 below */
int ooOpeng7231LogicalChannel(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245OpenLogicalChannel_forwardLogicalChannelParameters *flcp;
   H245AudioCapability *audioCap;
   H245H2250LogicalChannelParameters *h2250lcp;
   H245UnicastAddress *unicastAddrs;
   H245UnicastAddress_iPAddress *iPAddress;
   char localip[20];
   char hexip[20];
   int addr_part1, addr_part2, addr_part3, addr_part4;

   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_request);
   if(ret != OO_OK)
   {
	  OOTRACEERR3(context, "Error: H245 message creation failed for - %s",
                           "Open G7231 channel");
      return OO_FAILED;
   }

   context->outgoingH245->msgType = OOOpenLogicalChannel;
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));

   request->t = T_H245RequestMessage_openLogicalChannel;
   request->u.openLogicalChannel = (H245OpenLogicalChannel*)
                     ASN1MALLOC(pctxt, sizeof(H245OpenLogicalChannel));
   memset(request->u.openLogicalChannel, 0, 
                                     sizeof(request->u.openLogicalChannel));
   request->u.openLogicalChannel->forwardLogicalChannelNumber = 1;
   
#ifndef _COMPACT
   dListInit(&(request->u.openLogicalChannel->extElem1));
#endif /* !_COMPACT */
   /* Populate H245OpenLogicalChannel_ForwardLogicalChannel Parameters*/
   flcp = &(request->u.openLogicalChannel->forwardLogicalChannelParameters);
   flcp->m.portNumberPresent = 0;
   flcp->m.forwardLogicalChannelDependencyPresent = 0;
   flcp->m.replacementForPresent = 0;

#ifndef _COMPACT
   dListInit(&(flcp->extElem1));
#endif /* !_COMPACT */
   /* data type of channel is audio */
   flcp->dataType.t = T_H245DataType_audioData;

   /* set audio capability for channel */
   audioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                                     sizeof(H245AudioCapability));
   memset(audioCap, 0, sizeof(audioCap));
   audioCap->t = T_H245AudioCapability_g7231;
   audioCap->u.g7231->maxAl_sduAudioFrames = 30; /* 30 frames per packet */
   audioCap->u.g7231->silenceSuppression = 0;
   
   flcp->dataType.u.audioData = audioCap;
   flcp->multiplexParameters.t = 
      T_H245OpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters;
   flcp->multiplexParameters.u.h2250LogicalChannelParameters = 
                         (H245H2250LogicalChannelParameters*)ASN1MALLOC(pctxt, 
                          sizeof(H245H2250LogicalChannelParameters));

   h2250lcp = flcp->multiplexParameters.u.h2250LogicalChannelParameters;
   memset(h2250lcp, 0, sizeof(h2250lcp));

#ifndef _COMPACT
   dListInit(&(h2250lcp->extElem1));
#endif /* !_COMPACT */

   h2250lcp->sessionID = 1;
   h2250lcp->mediaGuaranteedDelivery = 0;
   h2250lcp->silenceSuppression = 0;
   h2250lcp->m.mediaControlChannelPresent = 1;
   
   h2250lcp->mediaControlChannel.t = 
                                 T_H245TransportAddress_unicastAddress;
   h2250lcp->mediaControlChannel.u.unicastAddress =  (H245UnicastAddress*)
                         ASN1MALLOC(pctxt, sizeof(H245UnicastAddress));

   unicastAddrs = h2250lcp->mediaControlChannel.u.unicastAddress;
   memset(unicastAddrs, 0, sizeof(unicastAddrs));
   unicastAddrs->t = T_H245UnicastAddress_iPAddress;
   unicastAddrs->u.iPAddress = (H245UnicastAddress_iPAddress*)
               ASN1MALLOC(pctxt, sizeof(H245UnicastAddress_iPAddress));
   iPAddress = unicastAddrs->u.iPAddress;
   memset(iPAddress, 0, sizeof(iPAddress));

#ifndef _COMPACT
   dListInit(&(iPAddress->extElem1));
#endif /* !_COMPACT */

   ooGetLocalIPAddress(localip);
   sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3,
                                  &addr_part4);
   sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
                                 addr_part4);
   sscanf(hexip, "%x %x %x %x", &(iPAddress->network.data[0]),
                                &(iPAddress->network.data[1]), 
                                &(iPAddress->network.data[2]), 
                                &(iPAddress->network.data[3]));
   iPAddress->network.numocts = 4;
   iPAddress->tsapIdentifier = ooGetLocalRtcpPort(context);
   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending OpenLogicalChannel");
   return OO_OK;
}
int ooOpeng728LogicalChannel(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245OpenLogicalChannel_forwardLogicalChannelParameters *flcp;
   H245AudioCapability *audioCap;
   H245H2250LogicalChannelParameters *h2250lcp;
   H245UnicastAddress *unicastAddrs;
   H245UnicastAddress_iPAddress *iPAddress;
   char localip[20];
   char hexip[20];
   int addr_part1, addr_part2, addr_part3, addr_part4;

   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_request);
   if(ret != OO_OK)
   {
	  OOTRACEERR3(context, "Error: H245 message creation failed for - %s",
                           "Open G728 channel");
      return OO_FAILED;
   }

   context->outgoingH245->msgType = OOOpenLogicalChannel;
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));

   request->t = T_H245RequestMessage_openLogicalChannel;
   request->u.openLogicalChannel = (H245OpenLogicalChannel*)
                     ASN1MALLOC(pctxt, sizeof(H245OpenLogicalChannel));
   memset(request->u.openLogicalChannel, 0, 
                                     sizeof(request->u.openLogicalChannel));
   request->u.openLogicalChannel->forwardLogicalChannelNumber = 1;
   
#ifndef _COMPACT
   dListInit(&(request->u.openLogicalChannel->extElem1));
#endif /* !_COMPACT */
   /* Populate H245OpenLogicalChannel_ForwardLogicalChannel Parameters*/
   flcp = &(request->u.openLogicalChannel->forwardLogicalChannelParameters);
   flcp->m.portNumberPresent = 0;
   flcp->m.forwardLogicalChannelDependencyPresent = 0;
   flcp->m.replacementForPresent = 0;

#ifndef _COMPACT
   dListInit(&(flcp->extElem1));
#endif /* !_COMPACT */
   /* data type of channel is audio */
   flcp->dataType.t = T_H245DataType_audioData;

   /* set audio capability for channel */
   audioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                                     sizeof(H245AudioCapability));
   memset(audioCap, 0, sizeof(audioCap));
   audioCap->t = T_H245AudioCapability_g728;
   audioCap->u.g728 = 30; /* 30 frames per packet */
   
   flcp->dataType.u.audioData = audioCap;
   flcp->multiplexParameters.t = 
      T_H245OpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters;
   flcp->multiplexParameters.u.h2250LogicalChannelParameters = 
                         (H245H2250LogicalChannelParameters*)ASN1MALLOC(pctxt, 
                          sizeof(H245H2250LogicalChannelParameters));

   h2250lcp = flcp->multiplexParameters.u.h2250LogicalChannelParameters;
   memset(h2250lcp, 0, sizeof(h2250lcp));

#ifndef _COMPACT
   dListInit(&(h2250lcp->extElem1));
#endif /* !_COMPACT */

   h2250lcp->sessionID = 1;
   h2250lcp->mediaGuaranteedDelivery = 0;
   h2250lcp->silenceSuppression = 0;
   h2250lcp->m.mediaControlChannelPresent = 1;
   
   h2250lcp->mediaControlChannel.t = 
                                 T_H245TransportAddress_unicastAddress;
   h2250lcp->mediaControlChannel.u.unicastAddress =  (H245UnicastAddress*)
                         ASN1MALLOC(pctxt, sizeof(H245UnicastAddress));

   unicastAddrs = h2250lcp->mediaControlChannel.u.unicastAddress;
   memset(unicastAddrs, 0, sizeof(unicastAddrs));
   unicastAddrs->t = T_H245UnicastAddress_iPAddress;
   unicastAddrs->u.iPAddress = (H245UnicastAddress_iPAddress*)
               ASN1MALLOC(pctxt, sizeof(H245UnicastAddress_iPAddress));
   iPAddress = unicastAddrs->u.iPAddress;
   memset(iPAddress, 0, sizeof(iPAddress));

#ifndef _COMPACT
   dListInit(&(iPAddress->extElem1));
#endif /* !_COMPACT */

   ooGetLocalIPAddress(localip);
   sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3,
                                  &addr_part4);
   sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
                                 addr_part4);
   sscanf(hexip, "%x %x %x %x", &(iPAddress->network.data[0]),
                                &(iPAddress->network.data[1]), 
                                &(iPAddress->network.data[2]), 
                                &(iPAddress->network.data[3]));
   iPAddress->network.numocts = 4;
   iPAddress->tsapIdentifier = ooGetLocalRtcpPort(context);
   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending OpenLogicalChannel");
   return OO_OK;
}
/*Added by Karl on 2005-01-14 above */

/*Added by Karl on 2004-11-26 below */
int ooOpeng721LogicalChannel(struct ooAppContext *context)
{
   int ret;
   H245RequestMessage * request;
   OOCTXT *pctxt;
   H245OpenLogicalChannel_forwardLogicalChannelParameters *flcp;
   H245AudioCapability *audioCap;
   H245H2250LogicalChannelParameters *h2250lcp;
   H245UnicastAddress *unicastAddrs;
   H245UnicastAddress_iPAddress *iPAddress;
   char localip[20];
   char hexip[20];
   int addr_part1, addr_part2, addr_part3, addr_part4;

   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_request);
   if(ret != OO_OK)
   {
	  OOTRACEERR3(context, "Error: H245 message creation failed for - %s",
                           "Open G721Annex channel");      
      return OO_FAILED;
   }

   context->outgoingH245->msgType = OOOpenLogicalChannel;
   request = context->outgoingH245->h245Msg.u.request;
   pctxt = context->outgoingH245->pctxt;
   memset(request, 0, sizeof(H245RequestMessage));

   request->t = T_H245RequestMessage_openLogicalChannel;
   request->u.openLogicalChannel = (H245OpenLogicalChannel*)
                     ASN1MALLOC(pctxt, sizeof(H245OpenLogicalChannel));
   memset(request->u.openLogicalChannel, 0, 
                                     sizeof(request->u.openLogicalChannel));
   request->u.openLogicalChannel->forwardLogicalChannelNumber = 1;
   
#ifndef _COMPACT
   dListInit(&(request->u.openLogicalChannel->extElem1));
#endif /* !_COMPACT */
   /* Populate H245OpenLogicalChannel_ForwardLogicalChannel Parameters*/
   flcp = &(request->u.openLogicalChannel->forwardLogicalChannelParameters);
   flcp->m.portNumberPresent = 0;
   flcp->m.forwardLogicalChannelDependencyPresent = 0;
   flcp->m.replacementForPresent = 0;

#ifndef _COMPACT
   dListInit(&(flcp->extElem1));
#endif /* !_COMPACT */
   /* data type of channel is audio */
   flcp->dataType.t = T_H245DataType_audioData;

   /* set audio capability for channel */
   audioCap = (H245AudioCapability*) ASN1MALLOC(pctxt,
                                     sizeof(H245AudioCapability));
   memset(audioCap, 0, sizeof(audioCap));
   audioCap->t = T_H245AudioCapability_g721_32k;
   audioCap->u.g721_32k = 30; /* 30 frames per packet */
   
   flcp->dataType.u.audioData = audioCap;
   flcp->multiplexParameters.t = 
      T_H245OpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters;
   flcp->multiplexParameters.u.h2250LogicalChannelParameters = 
                         (H245H2250LogicalChannelParameters*)ASN1MALLOC(pctxt, 
                          sizeof(H245H2250LogicalChannelParameters));

   h2250lcp = flcp->multiplexParameters.u.h2250LogicalChannelParameters;
   memset(h2250lcp, 0, sizeof(h2250lcp));

#ifndef _COMPACT
   dListInit(&(h2250lcp->extElem1));
#endif /* !_COMPACT */

   h2250lcp->sessionID = 1;
   h2250lcp->mediaGuaranteedDelivery = 0;
   h2250lcp->silenceSuppression = 0;
   h2250lcp->m.mediaControlChannelPresent = 1;
   
   h2250lcp->mediaControlChannel.t = 
                                 T_H245TransportAddress_unicastAddress;
   h2250lcp->mediaControlChannel.u.unicastAddress =  (H245UnicastAddress*)
                         ASN1MALLOC(pctxt, sizeof(H245UnicastAddress));

   unicastAddrs = h2250lcp->mediaControlChannel.u.unicastAddress;
   memset(unicastAddrs, 0, sizeof(unicastAddrs));
   unicastAddrs->t = T_H245UnicastAddress_iPAddress;
   unicastAddrs->u.iPAddress = (H245UnicastAddress_iPAddress*)
               ASN1MALLOC(pctxt, sizeof(H245UnicastAddress_iPAddress));
   iPAddress = unicastAddrs->u.iPAddress;
   memset(iPAddress, 0, sizeof(iPAddress));

#ifndef _COMPACT
   dListInit(&(iPAddress->extElem1));
#endif /* !_COMPACT */

   ooGetLocalIPAddress(localip);
   sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3,
                                  &addr_part4);
   sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
                                 addr_part4);
   sscanf(hexip, "%x %x %x %x", &(iPAddress->network.data[0]),
                                &(iPAddress->network.data[1]), 
                                &(iPAddress->network.data[2]), 
                                &(iPAddress->network.data[3]));
   iPAddress->network.numocts = 4;
   iPAddress->tsapIdentifier = ooGetLocalRtcpPort(context);
   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending OpenLogicalChannel");
   return OO_OK;
}
/*Added by Karl on 2004-11-26 above */

int ooHandleOpenLogicalChannel(struct ooAppContext *context, 
                                 H245OpenLogicalChannel *olc)
{
   int ret;
   H245ResponseMessage * response;
   OOCTXT *pctxt;
   H245OpenLogicalChannelAck *olcAck;
   H245H2250LogicalChannelAckParameters *h2250lcap;
   H245UnicastAddress *unicastAddrs;
   H245UnicastAddress_iPAddress *iPAddress;
   H245UnicastAddress *unicastAddrs1;
   H245UnicastAddress_iPAddress *iPAddress1;
   char localip[20];
   char hexip[20];
   int addr_part1, addr_part2, addr_part3, addr_part4;

   H245OpenLogicalChannel_forwardLogicalChannelParameters *flcp =
    &(olc->forwardLogicalChannelParameters);

   /* Check whether channel type is supported. Only supported channel 
      type for now is g729Annex and g711ulaw audio channel.
   */
   /*Modified by Karl on 2004-11-16 below*/
   if(!((flcp->dataType.t == T_H245DataType_audioData) &&
        (flcp->dataType.u.audioData->t == T_H245AudioCapability_g729AnnexA)))
   {      
	  if(!((flcp->dataType.t == T_H245DataType_audioData) &&
			/*(flcp->dataType.u.audioData->t == T_H245AudioCapability_g711Ulaw64k)))*/
			((flcp->dataType.u.audioData->t == T_H245AudioCapability_g711Ulaw64k)
			|| (flcp->dataType.u.audioData->t == T_H245AudioCapability_g721_32k)
			|| (flcp->dataType.u.audioData->t == T_H245AudioCapability_g721_24k)
			|| (flcp->dataType.u.audioData->t == T_H245AudioCapability_g721_40k)
			)))

	   {
		  OOTRACEWARN2(context, "Warning: Received OpenLogicalChannel type "
								"not supported");
		  return OO_OK; /* Need to return OpenLogicalChannelReject */
	   }    
   }
   /*Modified by Karl on 2004-11-16 above*/

   if(flcp->multiplexParameters.t != 
      T_H245OpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters)
   {
      OOTRACEWARN2(context, "Warning: Received OpenLogicalChannel type "
                            "not supported");
      return OO_OK; /* Need to return OpenLogicalChannelReject */
   }
   
   /* when RTCP will be supported remote rtcp address will be extracted here */
   

   /* Set Receive address */
   ooSetLocalRTPAndRTCPAddrs(context);

   /* Generate an Ack for the open channel request */
   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_response);
   if(ret != OO_OK)
   {
      OOTRACEERR3(context, "Error: H245 message creation failed for - %s",
                         "OpenLogicalChannel Ack");
      return OO_FAILED;
   }

   context->outgoingH245->msgType = OOOpenLogicalChannelAck;
   response = context->outgoingH245->h245Msg.u.response;
   pctxt = context->outgoingH245->pctxt;
   memset(response, 0, sizeof(H245ResponseMessage));
   response->t = T_H245ResponseMessage_openLogicalChannelAck;
   response->u.openLogicalChannelAck = (H245OpenLogicalChannelAck*)
                   ASN1MALLOC(pctxt, sizeof(H245OpenLogicalChannelAck));   
   olcAck = response->u.openLogicalChannelAck;
   memset(olcAck, 0, sizeof(H245OpenLogicalChannelAck));
   olcAck->forwardLogicalChannelNumber = olc->forwardLogicalChannelNumber;

#ifndef _COMPACT
   dListInit(&(olcAck->extElem1));
#endif /* !_COMPACT */

   olcAck->m.forwardMultiplexAckParametersPresent = 1;
   olcAck->forwardMultiplexAckParameters.t = 
     T_H245OpenLogicalChannelAck_forwardMultiplexAckParameters_h2250LogicalChannelAckParameters;
   olcAck->forwardMultiplexAckParameters.u.h2250LogicalChannelAckParameters = 
                      (H245H2250LogicalChannelAckParameters*)ASN1MALLOC(pctxt, 
                      sizeof(H245H2250LogicalChannelAckParameters));
   h2250lcap = 
      olcAck->forwardMultiplexAckParameters.u.h2250LogicalChannelAckParameters;
   memset(h2250lcap, 0, sizeof(H245H2250LogicalChannelAckParameters));

#ifndef _COMPACT
   dListInit(&(h2250lcap->extElem1));
#endif /* !_COMPACT */

   h2250lcap->m.mediaChannelPresent = 1;
   h2250lcap->m.mediaControlChannelPresent = 1;
   h2250lcap->m.sessionIDPresent = 1;
   h2250lcap->sessionID = 1;
   
   h2250lcap->mediaChannel.t = 
                         T_H245TransportAddress_unicastAddress;
   h2250lcap->mediaChannel.u.unicastAddress =  (H245UnicastAddress*)
                         ASN1MALLOC(pctxt, sizeof(H245UnicastAddress));

   unicastAddrs = h2250lcap->mediaChannel.u.unicastAddress;
   memset(unicastAddrs, 0, sizeof(H245UnicastAddress));
   unicastAddrs->t = T_H245UnicastAddress_iPAddress;
   unicastAddrs->u.iPAddress = (H245UnicastAddress_iPAddress*)
               ASN1MALLOC(pctxt, sizeof(H245UnicastAddress_iPAddress));
   iPAddress = unicastAddrs->u.iPAddress;
   memset(iPAddress, 0, sizeof(H245UnicastAddress_iPAddress));

#ifndef _COMPACT
   dListInit(&(iPAddress->extElem1));
#endif /* !_COMPACT */

   ooGetLocalIPAddress(localip);
   sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3,
                                  &addr_part4);
   sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, 
                                     addr_part3, addr_part4);
   sscanf(hexip, "%x %x %x %x", &(iPAddress->network.data[0]),
                                &(iPAddress->network.data[1]), 
                                &(iPAddress->network.data[2]), 
                                &(iPAddress->network.data[3]));
   iPAddress->network.numocts = 4;
   iPAddress->tsapIdentifier = ooGetLocalRtpPort(context);

   /* media contrcol channel */
   h2250lcap->mediaControlChannel.t = 
                                 T_H245TransportAddress_unicastAddress;
   h2250lcap->mediaControlChannel.u.unicastAddress =  (H245UnicastAddress*)
                         ASN1MALLOC(pctxt, sizeof(H245UnicastAddress));

   unicastAddrs1 = h2250lcap->mediaControlChannel.u.unicastAddress;
   memset(unicastAddrs1, 0, sizeof(H245UnicastAddress));
   unicastAddrs1->t = T_H245UnicastAddress_iPAddress;
   unicastAddrs1->u.iPAddress = (H245UnicastAddress_iPAddress*)
               ASN1MALLOC(pctxt, sizeof(H245UnicastAddress_iPAddress));
   iPAddress1 = unicastAddrs1->u.iPAddress;
   memset(iPAddress1, 0, sizeof(H245UnicastAddress_iPAddress));

#ifndef _COMPACT
   dListInit(&(iPAddress1->extElem1));
#endif /* !_COMPACT */

   sscanf(hexip, "%x %x %x %x", &(iPAddress1->network.data[0]),
                                &(iPAddress1->network.data[1]), 
                                &(iPAddress1->network.data[2]), 
                                &(iPAddress1->network.data[3]));
   iPAddress1->network.numocts = 4;
   iPAddress1->tsapIdentifier = ooGetLocalRtcpPort(context);

   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending OpenLogicalChannelAck");
   /* Increment number of open logical channels */
   context->totalOpenLogicalChannels++;

   return OO_OK;
}       

int ooOnReceivedOpenLogicalChannelAck(struct ooAppContext *context,
                                        H245OpenLogicalChannelAck *olcAck)
{
   char remoteip[20];
   H245H2250LogicalChannelAckParameters *h2250lcap;
   H245UnicastAddress *unicastAddr;
   H245UnicastAddress_iPAddress *iPAddress;
   H245UnicastAddress *unicastAddr1;
   H245UnicastAddress_iPAddress *iPAddress1;

   if(!((olcAck->m.forwardMultiplexAckParametersPresent == 1) &&
        (olcAck->forwardMultiplexAckParameters.t == 
         T_H245OpenLogicalChannelAck_forwardMultiplexAckParameters_h2250LogicalChannelAckParameters)))
   {
      OOTRACEERR2(context, "Error: Processing open logical channel ack -" 
                           "Logical channel Ack parameters absent");
      return OO_OK;  /* should send CloseLogicalChannel request */
   }

   h2250lcap = 
      olcAck->forwardMultiplexAckParameters.u.h2250LogicalChannelAckParameters;
   /* Extract media channel address */
   if(h2250lcap->m.mediaChannelPresent != 1)
   { 
      OOTRACEERR2(context, "Error: Processing OpenLogicalChannelAck - "
                           "media channel absent");
      return OO_FAILED;
   }
   if(h2250lcap->mediaChannel.t != T_H245TransportAddress_unicastAddress)
   {
      OOTRACEERR2(context, "Error: Processing OpenLogicalChannelAck - "
                           "media channel address type is not unicast");
      return OO_FAILED;
   }
   
   unicastAddr = h2250lcap->mediaChannel.u.unicastAddress;
   if(unicastAddr->t != T_H245UnicastAddress_iPAddress)
   {
      OOTRACEERR2(context, "Error: Processing OpenLogicalChannelAck - "
                           "media channel address type is not IP");
      return OO_FAILED;
   }
   iPAddress = unicastAddr->u.iPAddress;
   
   sprintf(remoteip,"%d.%d.%d.%d", iPAddress->network.data[0],
                                  iPAddress->network.data[1], 
                                  iPAddress->network.data[2], 
                                  iPAddress->network.data[3]);
   context->remoteRtpPort = iPAddress->tsapIdentifier;
   
   /* Extract media control channel address */
   if(h2250lcap->m.mediaControlChannelPresent != 1)
   { 
      OOTRACEERR2(context, "Error: Processing OpenLogicalChannelAck - "
                           "Missing media control channel");
      return OO_FAILED;
   }
   if(h2250lcap->mediaControlChannel.t != 
                                     T_H245TransportAddress_unicastAddress)
   {
      OOTRACEERR2(context, "Error: Processing OpenLogicalChannelAck - "
                          "media control channel addres type is not unicast");
      return OO_FAILED;
   }
   
   unicastAddr1 = h2250lcap->mediaControlChannel.u.unicastAddress;
   if(unicastAddr1->t != T_H245UnicastAddress_iPAddress)
   {
      OOTRACEERR2(context, "Error: Processing OpenLogicalChannelAck - "
                          "media control channel address type is not IP");
      return OO_FAILED;
   }
   iPAddress1 = unicastAddr1->u.iPAddress;
   context->remoteRtcpPort = iPAddress1->tsapIdentifier;

   /* Set remote destination address for rtp session */
   strcpy(context->remoteIP, remoteip);
   /* Increment number of open logical channels */
   context->totalOpenLogicalChannels++;
   return OO_OK;
}

/**
 * Currently only disconnect end session command is supported.
 **/

int ooSendEndSessionCommand(struct ooAppContext *context)
{
   int ret;
   H245CommandMessage * command;
   OOCTXT *pctxt;

   ret = ooCreateH245Message(context, 
                      T_H245MultimediaSystemControlMessage_command);
   if(ret != OO_OK)
   {
      OOTRACEERR3(context, "Error: H245 message creation failed for - %s",
                         "End Session Command");
      return OO_FAILED;
   }
   context->outgoingH245->msgType = OOEndSessionCommand;

   command = context->outgoingH245->h245Msg.u.command;
   pctxt = context->outgoingH245->pctxt;
   memset(command, 0, sizeof(H245CommandMessage));
   command->t = T_H245CommandMessage_endSessionCommand;
   command->u.endSessionCommand = (H245EndSessionCommand*) ASN1MALLOC(pctxt,
                                  sizeof(H245EndSessionCommand));
   memset(command->u.endSessionCommand, 0, sizeof(H245EndSessionCommand));
   command->u.endSessionCommand->t = T_H245EndSessionCommand_disconnect;
   ooSendH245Msg(context);
   OOTRACEINFO2(context, "Sending EndSession Command");
   return OO_OK;
}


int ooHandleH245Command(struct ooAppContext *context, 
                        H245CommandMessage *command)
{
   int ret;
   switch(command->t)
   {
      case T_H245CommandMessage_endSessionCommand:
         OOTRACEINFO2(context, "Received EndSession command");
         ret = ooSendReleaseComplete(context);
         if(ret != OO_OK)
         {
            OOTRACEERR2(context, "Error: Sending release complete");
            return OO_FAILED;
         }
         break;
      case T_H245CommandMessage_sendTerminalCapabilitySet:
         OOTRACEWARN2(context, "Warning: Received command Send terminal "
                               "capability set - Not handled");
         break;
      case T_H245CommandMessage_flowControlCommand:
         OOTRACEWARN2(context, "Warning: Flow control command received - Not"
                               " handled");
         break;
      default:
         OOTRACEWARN2(context, "Warning: Unhandled H245 command message "
                               "received");
   }
   return OO_OK;
}
