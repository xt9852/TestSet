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

#include "ooq931.h"
#include "oo.h"
#include "ooasn1.h"
#include "oochannels.h"
#include <time.h>

static ASN1OBJID gProtocolID = {
   6, { 0, 0, 8, 2250, 0, 4 }
};

EXTERN int ooQ931Decode (Q931Message* msg, int length, ASN1OCTET *data) 
{
   int offset;
   int rv = ASN_OK;

   dListInit (&msg->ies); /* clear information elements list */

   if (length < 5)  /* Packet too short */
      return Q931_E_TOOSHORT;

   msg->protocolDiscriminator = data[0];

   if (data[1] != 2) /* Call reference must be 2 bytes long */
      return Q931_E_INVCALLREF;

   msg->callReference = ((data[2] & 0x7f) << 8) | data[3];
   msg->fromDestination = (data[2] & 0x80) != 0;

   msg->messageType = data[4];

   /* Have preamble, start getting the informationElements into buffers */
   offset = 5;
   while (offset < length) {
      Q931InformationElement *ie;
      int ieOff = offset;
      /* Get field discriminator */
      int discriminator = data[offset++];

      /* For discriminator with high bit set there is no data */
      if ((discriminator & 0x80) == 0) {
         int len = data[offset++], alen;

         if (discriminator == Q931UserUserIE) {
            /* Special case of User-user field, there is some confusion here as
               the Q931 documentation claims the length is a single byte,
               unfortunately all H.323 based apps have a 16 bit length here, so
               we allow for said longer length. There is presumably an addendum
               to Q931 which describes this, and provides a means to 
               discriminate between the old 1 byte and the new 2 byte systems. 
               However, at present we assume it is always 2 bytes until we find
               something that breaks it. 
            */
            len <<= 8;
            len |= data[offset++];

            /* we also have a protocol discriminator, which we ignore */
            offset++;
            len--;
         }

         /* watch out for negative lengths! (ED, 11/5/03) */
         if (len < 0) {
            return Q931_E_INVLENGTH;
         }
         else if (offset + len > length) {
            alen = 0;
            len = -len;
            rv = Q931_E_INVLENGTH;
         }
         else alen = len;

         ie = (Q931InformationElement*) 
            ASN1MALLOC (msg->pctxt, sizeof(*ie) - sizeof(ie->data) + alen);
         ie->discriminator = discriminator;
         ie->offset = ieOff;
         ie->length = len;
         if (alen != 0) 
            memcpy(ie->data, data + offset, alen);
         offset += len;
      }
      else {
         ie = (Q931InformationElement*) ASN1MALLOC (msg->pctxt, 
                                        sizeof(*ie) - sizeof(ie->data));
         ie->discriminator = discriminator;
         ie->offset = offset;
         ie->length = 0;
      }

      dListAppend (msg->pctxt, &msg->ies, ie);
      if (rv != ASN_OK)
         return rv;
   }

   return rv;
}

EXTERN Q931InformationElement* ooQ931GetIE (const Q931Message* q931msg, 
                                              int ieCode)
{
   DListNode* curNode;
   unsigned int i;

   for(i = 0, curNode = q931msg->ies.head; i < q931msg->ies.count; i++) {
      Q931InformationElement *ie = (Q931InformationElement*) curNode->data;
      if (ie->discriminator == ieCode) {
         return ie;
      }
      curNode = curNode->next;
   }
   return NULL;
}

char* ooQ931GetMessageTypeName(int messageType, char* buf) {
   switch (messageType) {
      case Q931AlertingMsg :
         strcpy(buf, "Alerting");
         break;
      case Q931CallProceedingMsg :
         strcpy(buf, "CallProceeding");
         break;
      case Q931ConnectMsg :
         strcpy(buf, "Connect");
         break;
      case Q931ConnectAckMsg :
         strcpy(buf, "ConnectAck");
         break;
      case Q931ProgressMsg :
         strcpy(buf, "Progress");
         break;
      case Q931SetupMsg :
         strcpy(buf, "Setup");
         break;
      case Q931SetupAckMsg :
         strcpy(buf, "SetupAck");
         break;
      case Q931FacilityMsg :
         strcpy(buf, "Facility");
         break;
      case Q931ReleaseCompleteMsg :
         strcpy(buf, "ReleaseComplete");
         break;
      case Q931StatusEnquiryMsg :
         strcpy(buf, "StatusEnquiry");
         break;
      case Q931StatusMsg :
         strcpy(buf, "Status");
         break;
      case Q931InformationMsg :
         strcpy(buf, "Information");
         break;
      case Q931NationalEscapeMsg :
         strcpy(buf, "Escape");
         break;
      default:
         sprintf(buf, "<%u>", messageType);
   }
   return buf;
}

char* ooQ931GetIEName(int number, char* buf) {
   switch (number) {
      case Q931BearerCapabilityIE :
         strcpy(buf, "Bearer-Capability");
         break;
      case Q931CauseIE :
         strcpy(buf, "Cause");
         break;
      case Q931FacilityIE :
         strcpy(buf, "Facility");
         break;
      case Q931ProgressIndicatorIE :
         strcpy(buf, "Progress-Indicator");
         break;
      case Q931CallStateIE :
         strcpy(buf, "Call-State");
         break;
      case Q931DisplayIE :
         strcpy(buf, "Display");
         break;
      case Q931SignalIE :
         strcpy(buf, "Signal");
         break;
      case Q931CallingPartyNumberIE :
         strcpy(buf, "Calling-Party-Number");
         break;
      case Q931CalledPartyNumberIE :
         strcpy(buf, "Called-Party-Number");
         break;
      case Q931RedirectingNumberIE :
         strcpy(buf, "Redirecting-Number");
         break;
      case Q931UserUserIE :
         strcpy(buf, "User-User");
         break;
      default:
         sprintf(buf, "0x%02x", number);
   }
   return buf;
}

EXTERN void ooQ931Print (const Q931Message* q931msg) {
   char buf[1000];
   DListNode* curNode;
   unsigned int i;

   printf("Q.931 Message:\n");
   printf("   protocolDiscriminator: %i\n", q931msg->protocolDiscriminator);
   printf("   callReference: %i\n", q931msg->callReference);
   printf("   from: %s\n", (q931msg->fromDestination ? 
                                       "destination" : "originator"));
   printf("   messageType: %s (0x%X)\n\n", 
              ooQ931GetMessageTypeName(q931msg->messageType, buf), 
                                               q931msg->messageType);

   for(i = 0, curNode = q931msg->ies.head; i < q931msg->ies.count; i++) {
      Q931InformationElement *ie = (Q931InformationElement*) curNode->data;
      int length = (ie->length >= 0) ? ie->length : -ie->length;
      printf("   IE[%i] (offset 0x%X):\n", i, ie->offset);
      printf("      discriminator: %s (0x%X)\n", 
               ooQ931GetIEName(ie->discriminator, buf), ie->discriminator);
      printf("      data length: %i\n", length);
 
      curNode = curNode->next;
      printf("\n");
   }
}

int ooCreateQ931Message(struct ooAppContext * context, int msgType)
{
   OOCTXT *pctxt = NULL;
   if(context->outgoing != NULL)
   {
      OOTRACEWARN2(context,"Warning: Can not create q931 message - message exists");
      return OO_FAILED;
   }
   pctxt = (OOCTXT*)newContext();
   if(pctxt == NULL)
   {
      OOTRACEERR2(context, "Error: Failed to allocate ASN1 context for "
                           "outgoing message creation");
      return OO_FAILED;
   }
   
   /*remarked by tony 2005.2.14 initContext already include in newContext()
   /this call will lead to memory leak(36 bytes)*/
//   initContext(pctxt);
   context->outgoing = (Q931Message*)ASN1MALLOC(pctxt, sizeof(Q931Message));
   if(context->outgoing == NULL)
   {
      OOTRACEERR2(context,"Error: Failed to allocate memory for q931 message");
      return OO_FAILED;
   }
   else
   {
      context->outgoing->pctxt = pctxt;
      context->outgoing->protocolDiscriminator = 8;
      /* If setup message then generate new call ref, otherwise use 
         existing call ref.
      */
	  //modified by tony below 2004.12.13
      /*if(msgType == Q931SetupMsg)
      {
         context->outgoing->callReference = ooGenerateCallReference();
         context->callReference = context->outgoing->callReference;
      }
      else
         context->outgoing->callReference = context->callReference;*/
	  if(msgType == Q931SetupMsg && context->callByGK == FALSE)
		  context->callReference = ooGenerateCallReference();
	  context->outgoing->callReference = context->callReference;
	  //modified by tony above 2004.12.13
      context->outgoing->fromDestination = FALSE;
      context->outgoing->messageType = msgType;
      return OO_OK;
   }
}

ASN1USINT ooGenerateCallReference()
{
   int seed = 3745;
#ifndef _WIN32
   srandom(seed);
   return (ASN1USINT)(random()%10000);
#else
   return (ASN1USINT)387564; /*Need to implement corresponding procedure for windows */
#endif
}

//added by tony below 2004.12.13
void ooGenerateGUID(ASN1OCTET guid[16])
{
	short i,random;
	static int seed = 1;
	seed = (seed + 100) % 65535;
	srand( seed );
	for(i = 0; i < 8; i++)
	{
		random = rand();
		memcpy(&guid[i * 2],&random,sizeof(short));
	}
}

//added by tony above 2004.12.13
int ooAddUserUserIE(struct ooAppContext *context,H225H323_UserInformation *userInfo)
{
   ASN1OCTET msgbuf[1024];
   ASN1OCTET * msgptr=NULL;
   int  len;
   ASN1BOOL aligned = TRUE, trace = FALSE;
   Q931InformationElement* ie=NULL;
   memset(msgbuf, 0, sizeof(msgbuf));
   if(context->outgoing ==NULL)
   {
      OOTRACEERR2(context, "Error: In add user-user IE - no outgoing message");
      return OO_FAILED;
   }
    
   setPERBuffer(context->outgoing->pctxt, msgbuf, sizeof(msgbuf), aligned);
 
   if(asn1PE_H225H323_UserInformation (context->outgoing->pctxt,userInfo)==ASN_OK)
   {
      OOTRACEINFO2(context, "UserInfo encoding - successful");
   }
   else{
      OOTRACEERR2(context, "Error: UserInfo encoding failed");
      return OO_FAILED;
   }

   msgptr = encodeGetMsgPtr(context->outgoing->pctxt, &len);

   /* Allocate memory to hold complete UserUser Information */
   ie = (Q931InformationElement*)ASN1MALLOC (context->outgoing->pctxt,
                                     sizeof(*ie) - sizeof(ie->data) + len);
   if(ie == NULL)
   {
      OOTRACEERR2(context, "Error: Allocation of Q931Information "
                           "Element Failed");
      return OO_FAILED;
   }
   ie->discriminator = Q931UserUserIE;
   ie->length = len;
   memcpy(ie->data, msgptr, len);
   /* Add the user to user IE NOTE: ALL IEs SHOULD BE IN ASCENDING ORDER OF 
      THEIR DISCRIMINATOR AS PER SPEC. 
   */
   dListInit (&(context->outgoing->ies));
   if((dListAppend (context->outgoing->pctxt, 
                      &(context->outgoing->ies), ie)) == NULL)
   {
      OOTRACEERR2(context, "Error: Failed to add UUIE in outgoing message");
      return OO_FAILED;
   }

   return OO_OK;
}

/* Need to figure out what parameters are to be passed to create 
   bearer capability 
*/
/*
int ooAddBearerCapabilityIE(struct ooAppContext *context)
{
}
*/


int ooFreeQ931Message(struct ooAppContext *context, Q931Message *q931Msg)
{
   OOCTXT * pctxt;
   pctxt = q931Msg->pctxt;
   if(q931Msg == context->outgoing)
      context->outgoing = NULL;
   freeContext(pctxt);
   ASN1CRTFREE0(pctxt);

   return OO_OK;
}


int ooQ931GetUUIE(struct ooAppContext *context, Q931Message *q931Msg, 
                    H225H323_UserInformation *userInfo)
{
   DListNode* curNode;
   unsigned int i;
   ASN1BOOL aligned=TRUE, trace=FALSE;
   int stat;
   Q931InformationElement *ie;
   if(q931Msg ==NULL)
   {
      OOTRACEERR2(context,"Error: ooQ931GetUUIE failed - NULL q931 message");
      return OO_FAILED;
   }
        
   /* Search for UserUser IE */
   for(i = 0, curNode = q931Msg->ies.head; i < q931Msg->ies.count; 
                                             i++, curNode = curNode->next) 
   {
      ie = (Q931InformationElement*) curNode->data;
      if(ie->discriminator == Q931UserUserIE)
         break;
   }
   if(i == q931Msg->ies.count)
   {
      OOTRACEERR2(context, "No UserUser IE found");
      return OO_FAILED;
   }
        
   /* Decode user-user ie */
   setPERBuffer (q931Msg->pctxt, ie->data, ie->length, aligned);
   
   stat = asn1PD_H225H323_UserInformation (q931Msg->pctxt, userInfo);
   if(stat != ASN_OK)
   {
      OOTRACEERR2(context, "Error: UserUser IE decode failed");
      return OO_FAILED;
   }
   return OO_OK;
}

int ooGetOutgoingQ931Msgbuf(struct ooAppContext *context, 
                            ASN1OCTET * msgbuf, int * len, int *msgType)
{
   int i=0, ieLen=0, k=0;
   ASN1UINT j=0;
   DListNode* curNode=NULL, *p_msgNode=NULL;
   Q931Message * q931Msg=NULL;
   OOCTXT * pctxt=NULL;;
   if(context->outH225Queue.count == 0)
   {
      OOTRACEWARN2(context,"Warning: No outgoing h225 message");
      return OO_FAILED;
   }
   
   p_msgNode = context->outH225Queue.head;
   
   q931Msg = (Q931Message*) p_msgNode->data;
   pctxt = q931Msg->pctxt;
   
   if(q931Msg->messageType == Q931SetupMsg)
      *msgType = OOSetup;
   else if(q931Msg->messageType == Q931ConnectMsg)
      *msgType = OOConnect;
   else if(q931Msg->messageType == Q931CallProceedingMsg)
      *msgType = OOCallProceeding;
   else if(q931Msg->messageType == Q931AlertingMsg)
     *msgType = OOAlert;
   else if(q931Msg->messageType == Q931ReleaseCompleteMsg)
      *msgType = OOReleaseComplete;

   
   msgbuf[i++] = 3; /* TPKT version */
   msgbuf[i++] = 0; /* TPKT resevred */
   /* 1st octet of length, will be populated once len is determined */
   msgbuf[i++] = 0; 
   /* 2nd octet of length, will be populated once len is determined */
   msgbuf[i++] = 0; 
   /* Q931 protocol discriminator */
   msgbuf[i++] = q931Msg->protocolDiscriminator;
   msgbuf[i++] = 2; /* length of call ref is two octets */
   //modified by tony below 2004.12.22
   if(q931Msg->messageType == Q931CallProceedingMsg || 
	   q931Msg->messageType == Q931AlertingMsg ||
	   q931Msg->messageType == Q931ConnectMsg)
		msgbuf[i++] = (q931Msg->callReference >> 8) + 0x80; //set the called flag in callreference
   else
		msgbuf[i++] = q931Msg->callReference >> 8;/* populate 1st octet */
   	
   //modified by tony above 2004.12.22	
   msgbuf[i++] = q931Msg->callReference; /* populate 2nd octet */
   msgbuf[i++] = q931Msg->messageType; /* type of q931 message */
   
   for(j = 0, curNode = q931Msg->ies.head; j < q931Msg->ies.count; j++) 
   {
      Q931InformationElement *ie = (Q931InformationElement*) curNode->data;
          
      ieLen = ie->length;

      /* Add the ie discriminator in message buffer */
      msgbuf[i++] = ie->discriminator; 
          
      /* For user-user IE, we have to add protocol discriminator */
      if (ie->discriminator == Q931UserUserIE)
      {
         ieLen++; /* length includes protocol discriminator octet. */
         msgbuf[i++] = (ieLen>>8); /* 1st octet for length */
         msgbuf[i++] = ieLen;      /* 2nd octet for length */
         ieLen--;
         msgbuf[i++] = 5; /* protocol discriminator */
         memcpy((msgbuf + i), ie->data, ieLen);
         i += ieLen-1;
         
      }
      else if(ie->discriminator == Q931CauseIE)
      {
         msgbuf[i++] = (ieLen>>8);
         msgbuf[i++] = ieLen;
         memcpy((msgbuf+i), ie->data, ieLen);
         i += ieLen -1;
      }else
      {
         OOTRACEWARN2(context, "Warning: Only UUIE is supported currently");
         return OO_FAILED;
      }
   }
   *len = i+1; /* complete message length */
   /* Tpkt length octets populated with total length of the message */
   msgbuf[2] = (*len >> 8); 
   msgbuf[3] = *len;        /* including tpkt header */

   /* Remove the message from rtdlist outH225Queue */
   dListRemove(&(context->outH225Queue), p_msgNode);

   /* Free memory associated with the message */
   freeContext(pctxt);
   ASN1CRTFREE0(pctxt);

   if(p_msgNode)
      ASN1MEMFREEPTR(&(context->outH225ListCtxt), p_msgNode);

   return OO_OK;
}


int ooOnReceivedSetup(struct ooAppContext *context, Q931Message *q931Msg)
{
   H225H323_UserInformation userInfo;
   H225Setup_UUIE *setup;
   context->callReference = q931Msg->callReference;
   
   ooQ931GetUUIE(context, q931Msg, &userInfo);
   setup = userInfo.h323_uu_pdu.h323_message_body.u.setup;
   if(setup == NULL)
   {
      OOTRACEERR2(context, "Error: Setup UUIE not found in received setup message");
      return OO_FAILED;
   }
   memcpy(context->callIdentifier.guid.data, setup->callIdentifier.guid.data, 
          setup->callIdentifier.guid.numocts);
   context->callIdentifier.guid.numocts = setup->callIdentifier.guid.numocts;

   memcpy(context->conferenceId.data,setup->conferenceID.data,setup->conferenceID.numocts);
   context->conferenceId.numocts = setup->conferenceID.numocts;
   return OO_OK;
}

int ooSendCallProceeding(struct ooAppContext *context)
{
   int ret;    
   H225H323_UserInformation userInfo;
   H225VendorIdentifier *vendor;
   H225CallProceeding_UUIE callProceeding;
   ret = ooCreateQ931Message(context, Q931CallProceedingMsg);
   if(ret != OO_OK)
   {      
      OOTRACEERR2(context, "Error: In allocating memory for - H225 Call "
                           "Proceeding message");
      return OO_FAILED;
   }
   
   
   memset (&userInfo, 0, sizeof(userInfo));
   userInfo.h323_uu_pdu.m.h245TunnelingPresent=1; 
   userInfo.h323_uu_pdu.h245Tunneling = FALSE; 
   userInfo.h323_uu_pdu.h323_message_body.t = 
         T_H225H323_UU_PDU_h323_message_body_callProceeding;
   
   memset(&callProceeding, 0, sizeof(callProceeding));
   userInfo.h323_uu_pdu.h323_message_body.u.callProceeding = &callProceeding;
   callProceeding.m.multipleCallsPresent = 1;
   callProceeding.m.maintainConnectionPresent = 1;
   callProceeding.multipleCalls = FALSE;
   callProceeding.maintainConnection = FALSE;

   callProceeding.m.callIdentifierPresent = 1;
   callProceeding.callIdentifier.guid.numocts = 
                                   context->callIdentifier.guid.numocts;
   memcpy(callProceeding.callIdentifier.guid.data, 
          context->callIdentifier.guid.data, 
          context->callIdentifier.guid.numocts);
   callProceeding.protocolIdentifier = gProtocolID;  
   callProceeding.destinationInfo.m.vendorPresent = 1;
   vendor = &callProceeding.destinationInfo.vendor;
   vendor->m.productIdPresent = 1;
   vendor->m.versionIdPresent = 1;
   vendor->vendor.t35CountryCode = 9;
   vendor->vendor.t35Extension = 0;
   vendor->vendor.manufacturerCode=61;
   vendor->productId.numocts = ASN1MIN(strlen("GiantVoip"), 
                                    sizeof(vendor->productId.data));
   strncpy(vendor->productId.data, "GiantVoip", vendor->productId.numocts);

      
   vendor->versionId.numocts = ASN1MIN(strlen("Version 1.0"), 
                                     sizeof(vendor->versionId.data));
   strncpy(vendor->versionId.data, "Version 1.0", vendor->versionId.numocts); 
   ooAddUserUserIE(context, &userInfo);
   ooSendH225Msg(context);
   OOTRACEINFO2(context, "Sending Call Proceeding");
   return OO_OK;
}

int ooSendAlerting(struct ooAppContext *context)
{  
   int ret;   
   H225H323_UserInformation userInfo;
   H225Alerting_UUIE alerting;
//   H225VendorIdentifier *vendor;
   ret = ooCreateQ931Message(context, Q931AlertingMsg);
   if(ret != OO_OK)
   {      
      OOTRACEERR2(context, "Error: In allocating memory for - H225 "
                           "Alerting message");
      return OO_FAILED;
   }
   memset (&userInfo, 0, sizeof(userInfo));
   userInfo.h323_uu_pdu.h323_message_body.t = 
         T_H225H323_UU_PDU_h323_message_body_alerting;
   
   memset(&alerting, 0, sizeof(alerting));
   userInfo.h323_uu_pdu.h323_message_body.u.alerting = &alerting;
//   alerting.m.multipleCallsPresent = 1;
//   alerting.multipleCalls = FALSE;
//   alerting.m.maintainConnectionPresent = 1;
//   alerting.maintainConnection =  TRUE;

   alerting.m.callIdentifierPresent = 1;
   alerting.callIdentifier.guid.numocts = 
                                   context->callIdentifier.guid.numocts;
   memcpy(alerting.callIdentifier.guid.data, 
         context->callIdentifier.guid.data, 
          context->callIdentifier.guid.numocts);
   alerting.protocolIdentifier = gProtocolID;
   
//   alerting.destinationInfo.m.vendorPresent = 1;
//   vendor = &alerting.destinationInfo.vendor;
//   vendor->m.productIdPresent = 1;
//   vendor->m.versionIdPresent = 1;
//   vendor->vendor.t35CountryCode = 9;
//   vendor->vendor.t35Extension = 0;
//   vendor->vendor.manufacturerCode=61;
//   vendor->productId.numocts = ASN1MIN(strlen("GiantVoip"), 
//                                       sizeof(vendor->productId.data));
//   strncpy(vendor->productId.data, "GiantVoip", vendor->productId.numocts);

//	vendor->versionId.numocts = ASN1MIN(strlen("Version1.0"), 
//                                        sizeof(vendor->versionId.data));
//   strncpy(vendor->versionId.data, "Version1.0", vendor->versionId.numocts);

   //added by tony below [2004.12.20]
   alerting.destinationInfo.m.terminalPresent = TRUE;
   alerting.destinationInfo.terminal.m.nonStandardDataPresent = 0;
//   alerting.destinationInfo.mc = FALSE;
//   alerting.destinationInfo.undefinedNode = FALSE;
//   alerting.m.presentationIndicatorPresent = TRUE;
//   alerting.presentationIndicator.t = T_H225PresentationIndicator_presentationAllowed;
//   alerting.m.screeningIndicatorPresent = TRUE;
//   alerting.screeningIndicator = userProvidedVerifiedAndFailed;
   //added by tony above [2004.12.20]

   ooAddUserUserIE(context, &userInfo);
   ooSendH225Msg(context);
   OOTRACEINFO2(context, "Sending Alerting");
   return OO_OK;
}

int ooSendConnect(struct ooAppContext *context)
{
   int ret,i=0;    
   char localip[20], hexip[20];
   int addr_part1, addr_part2, addr_part3, addr_part4;
   H225H323_UserInformation userInfoConnect;
   H225Connect_UUIE connect;
   H225TransportAddress_ipAddress h245IpAddr;
   H225VendorIdentifier *vendor;

   ret = ooCreateQ931Message(context, Q931ConnectMsg);
   if(ret != OO_OK)
   {      
      OOTRACEERR2(context, "Error: In allocating memory for - H225 "
                           "Connect message");
      return OO_FAILED;
   }
   
   memset (&userInfoConnect, 0, sizeof(userInfoConnect));
//   userInfoConnect.h323_uu_pdu.m.h245TunnelingPresent=1; 
//   userInfoConnect.h323_uu_pdu.h245Tunneling = FALSE; 
   userInfoConnect.h323_uu_pdu.h323_message_body.t = 
                     T_H225H323_UU_PDU_h323_message_body_connect;
   
   memset(&connect, 0, sizeof(connect));
   userInfoConnect.h323_uu_pdu.h323_message_body.u.connect = &connect;
/*   connect.m.fastStartPresent = 0;
   connect.m.multipleCallsPresent = 1;
   connect.m.maintainConnectionPresent = 1;
   connect.multipleCalls = FALSE;
   connect.maintainConnection = FALSE;*/
   
    /* Add h245 address */
   connect.m.h245AddressPresent = 1;
   connect.h245Address.t = T_H225TransportAddress_ipAddress;
   
   memset(&h245IpAddr, 0, sizeof(h245IpAddr));

   ooGetLocalIPAddress(localip);
   sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, 
                                  &addr_part3, &addr_part4);
   sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
                                 addr_part4);
   sscanf(hexip, "%x %x %x %x", &h245IpAddr.ip.data[0], &h245IpAddr.ip.data[1],
           &h245IpAddr.ip.data[2], &h245IpAddr.ip.data[3]);
   
   h245IpAddr.ip.numocts=4;
   h245IpAddr.port = context->h245RxPort;
   connect.h245Address.u.ipAddress = &h245IpAddr;

   //modified by tony 2005.1.10 below
/* connect.conferenceID.numocts = 16;
   for (i = 0; i < 16; i++)
      connect.conferenceID.data[i] = i + 1;*/
   connect.conferenceID.numocts = context->conferenceId.numocts;
   memcpy(connect.conferenceID.data,context->conferenceId.data,context->conferenceId.numocts);
	//modified by tony 2005.1.10 above

   connect.m.callIdentifierPresent = 1;
   connect.callIdentifier.guid.numocts = 
                                 context->callIdentifier.guid.numocts;
   memcpy(connect.callIdentifier.guid.data, context->callIdentifier.guid.data, 
                                         context->callIdentifier.guid.numocts);
   connect.protocolIdentifier = gProtocolID;  

   connect.destinationInfo.m.vendorPresent = 1;
   vendor = &connect.destinationInfo.vendor;
   vendor->m.productIdPresent = 1;
   vendor->m.versionIdPresent = 1;
   vendor->vendor.t35CountryCode = 9;
   vendor->vendor.t35Extension = 0;
   vendor->vendor.manufacturerCode=61;
   vendor->productId.numocts = ASN1MIN(strlen("GiantVoip"), 
                                         sizeof(vendor->productId.data));
   strncpy(vendor->productId.data, "GiantVoip", vendor->productId.numocts);

      
   vendor->versionId.numocts = ASN1MIN(strlen("Version 1.0"), 
                                           sizeof(vendor->versionId.data));
   strncpy(vendor->versionId.data, "Version 1.0", vendor->versionId.numocts); 

   connect.destinationInfo.m.terminalPresent = 1;
   connect.destinationInfo.terminal.m.nonStandardDataPresent = 0;

   ooAddUserUserIE(context, &userInfoConnect);
   ooSendH225Msg(context);
   OOTRACEINFO2(context, "Sending H.225 Connect message");
   return OO_OK;
}

int ooSendReleaseComplete(struct ooAppContext *context)
{
   int ret, ieLen, standard = 0, location = 0;   
   Q931InformationElement* ie=NULL;
   ASN1OCTET dataBuf[1024];
   H225H323_UserInformation userInfo;
   H225ReleaseComplete_UUIE releaseComplete;
   memset(&userInfo, 0, sizeof(userInfo));
   memset(&releaseComplete, 0, sizeof(releaseComplete));
   OOTRACEDBGA2(context, "Building Release Complete message to send");
   ret = ooCreateQ931Message(context, Q931ReleaseCompleteMsg);
   if(ret != OO_OK)
   {      
      OOTRACEERR2(context, "Error: In allocating memory for - H225 Release "
                          "Complete message");
      return OO_FAILED;
   }
   /* Add cause ie */
   ieLen = 2;
   dataBuf[0] = (0x80 | ((standard&3)<<5) | (location&15));
   dataBuf[1] = (0x80 | Q931NormalCallClearing);   
       
   /* Allocate memory to hold complete Cause IE Information */
   ie = (Q931InformationElement*)ASN1MALLOC (context->outgoing->pctxt,
                                     sizeof(*ie) - sizeof(ie->data) + ieLen);
   if(ie == NULL)
   {
      OOTRACEERR2(context, "Error: Allocation of Q931Information "
                          "Element Failed");
      return OO_FAILED;
   }
   ie->discriminator = Q931CauseIE;
   ie->length = ieLen;
   memcpy(ie->data, dataBuf, ieLen);

   /* NOTE: ALL IEs SHOULD BE IN ASCENDING ORDER OF 
      THEIR DISCRIMINATOR AS PER SPEC. WE NEED TO TAKE CARE OF THIS.
   */
   dListInit (&(context->outgoing->ies));
   if((dListAppend (context->outgoing->pctxt, 
                      &(context->outgoing->ies), ie)) == NULL)
   {
      OOTRACEERR2(context, "Error: Failed to add UUIE in outgoing message");
      return OO_FAILED;
   }

   /* Add user-user ie */
#ifndef _COMPACT
   dListInit(&userInfo.extElem1);
   dListInit(&userInfo.user_data.extElem1);
   dListInit(&userInfo.h323_uu_pdu.extElem1);
#endif
   userInfo.h323_uu_pdu.m.h245TunnelingPresent=1; 
   userInfo.h323_uu_pdu.h245Tunneling = FALSE;
   userInfo.h323_uu_pdu.h323_message_body.t = 
           T_H225H323_UU_PDU_h323_message_body_releaseComplete;
   
   userInfo.h323_uu_pdu.h323_message_body.u.releaseComplete = &releaseComplete;
#ifndef _COMPACT
   dListInit(&releaseComplete.extElem1);
#endif
   releaseComplete.m.callIdentifierPresent = 1;
   releaseComplete.protocolIdentifier = gProtocolID;
   releaseComplete.callIdentifier.guid.numocts = 
           context->callIdentifier.guid.numocts;
   memcpy(releaseComplete.callIdentifier.guid.data, 
                                  context->callIdentifier.guid.data,
                                  context->callIdentifier.guid.numocts);
#ifndef _COMPACT
   dListInit(&releaseComplete.callIdentifier.extElem1);
#endif
   ooAddUserUserIE(context, &userInfo);
   OOTRACEINFO2(context,"Sending Release Complete message");
   /* Send H225 message */   
   ooSendH225Msg(context);

   return OO_OK;
}
