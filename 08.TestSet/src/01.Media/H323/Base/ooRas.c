/*
 * Copyright (C) 2004 by Giant Electronics, Inc.
 *****************************************************************************/
#include "ooRas.h"

#ifdef _WIN32
//#include <stdlib.h>
//#include <time.h>
#include <stdio.h>
#endif
static ASN1OBJID gRasProtocolID = {
  6, { 0, 0, 8, 2250, 0, 2 }
};

int ooCreateRasMessage(struct ooAppContext *context, int type)
{
   OOCTXT* pctxt = NULL;
   if(context->outgoingRas != NULL)
   {
      OOTRACEWARN2(context, "Can not create Ras message - message exists");
      return OO_FAILED;
   }

   pctxt = (OOCTXT*)newContext();
   if(pctxt == NULL)
   {
      OOTRACEERR2(context,"ERROR: Failed to allocate ASN1 context for "
                         "outgoing Ras message creation");
      return OO_FAILED;
   }

   context->outgoingRas = (RasMessage*)ASN1MALLOC(pctxt,sizeof(RasMessage));
   if(context->outgoingRas == NULL)
   {
      OOTRACEERR2(context,"Failed to allocate memory for Ras message");
      return OO_FAILED;
   }
   else
   {
      memset(context->outgoingRas, 0, sizeof(context->outgoingRas));
      context->outgoingRas->pctxt = pctxt;
      context->outgoingRas->RasMsg.t = type;
      switch(type)
      {
         case  T_H225RasMessage_gatekeeperRequest:
            context->outgoingRas->RasMsg.u.gatekeeperRequest = 
				(H225GatekeeperRequest*)ASN1MALLOC(pctxt,sizeof(H225GatekeeperRequest));
            
            if(context->outgoingRas->RasMsg.u.gatekeeperRequest == 0)
            {
               OOTRACEERR2(context, "Memory allocation for Ras gatekeeper request"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingRas->RasMsg.u.gatekeeperRequest, 0, 
					sizeof(H225GatekeeperRequest));
            break;
         case T_H225RasMessage_gatekeeperConfirm :
            context->outgoingRas->RasMsg.u.gatekeeperConfirm =
				(H225GatekeeperConfirm*)ASN1MALLOC(pctxt,sizeof(H225GatekeeperConfirm));
            
			if(context->outgoingRas->RasMsg.u.gatekeeperConfirm == 0)
            {
               OOTRACEERR2(context, "Memory allocation for Ras confirm"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingRas->RasMsg.u.gatekeeperConfirm, 0,
					sizeof(H225GatekeeperConfirm));
            break;
         case T_H225RasMessage_gatekeeperReject:
            context->outgoingRas->RasMsg.u.gatekeeperReject = 
				(H225GatekeeperReject*)ASN1MALLOC(pctxt,sizeof(H225GatekeeperReject));
            if(context->outgoingRas->RasMsg.u.gatekeeperReject == 0)
            {
               OOTRACEERR2(context, "Memory allocation for ras gatekeeper reject"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingRas->RasMsg.u.gatekeeperReject, 0, 
					sizeof(H225GatekeeperReject));
             break;
         case T_H225RasMessage_registrationRequest:
            context->outgoingRas->RasMsg.u.registrationRequest = 
                 (H225RegistrationRequest*)ASN1MALLOC(pctxt,sizeof(H225RegistrationRequest));
            if(context->outgoingRas->RasMsg.u.registrationRequest == 0)
            {
               OOTRACEERR2(context, "Memory allocation for ras registration request"
                                     " message failed");
               return OO_FAILED;
            }
            else
               memset(context->outgoingRas->RasMsg.u.registrationRequest, 0, 
                    sizeof(H225RegistrationRequest));
            break;
		case T_H225RasMessage_registrationConfirm:
			context->outgoingRas->RasMsg.u.registrationConfirm = 
				(H225RegistrationConfirm*)ASN1MALLOC(pctxt,sizeof(H225RegistrationConfirm));
			if(context->outgoingRas->RasMsg.u.registrationConfirm == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras registration confirm"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.registrationConfirm,0,
					sizeof(H225RegistrationConfirm));
			break;
		case T_H225RasMessage_registrationReject:
			context->outgoingRas->RasMsg.u.registrationReject = 
				(H225RegistrationReject*)ASN1MALLOC(pctxt,sizeof(H225RegistrationReject));
			if(context->outgoingRas->RasMsg.u.registrationReject == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras registration reject"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.registrationReject,0,
					sizeof(H225RegistrationReject));
			break;
		case T_H225RasMessage_unregistrationRequest:
			context->outgoingRas->RasMsg.u.unregistrationRequest = 
				(H225UnregistrationRequest*)ASN1MALLOC(pctxt,sizeof(H225UnregistrationRequest));
			if(context->outgoingRas->RasMsg.u.unregistrationRequest == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras unregistration request"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.unregistrationRequest,0,
					sizeof(H225UnregistrationRequest));				
			break;
		case T_H225RasMessage_unregistrationConfirm:
			context->outgoingRas->RasMsg.u.unregistrationConfirm = 
				(H225UnregistrationConfirm*)ASN1MALLOC(pctxt,sizeof(H225UnregistrationConfirm));
			if(context->outgoingRas->RasMsg.u.unregistrationConfirm == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras unregistration confirm"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.unregistrationConfirm,0,
					sizeof(H225UnregistrationConfirm));
			break;
		case T_H225RasMessage_unregistrationReject:
			context->outgoingRas->RasMsg.u.unregistrationReject = 
				(H225UnregistrationReject*)ASN1MALLOC(pctxt,sizeof(H225UnregistrationReject));
			if(context->outgoingRas->RasMsg.u.unregistrationReject == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras unregistration reject"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.unregistrationReject,0,
					sizeof(H225UnregistrationReject));
			break;
		case T_H225RasMessage_admissionRequest:
			context->outgoingRas->RasMsg.u.admissionRequest = 
				(H225AdmissionRequest*)ASN1MALLOC(pctxt,sizeof(H225AdmissionRequest));
			if(context->outgoingRas->RasMsg.u.admissionRequest == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras admission request"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.admissionRequest,0,
					sizeof(H225AdmissionRequest));				
			break;
		case T_H225RasMessage_admissionConfirm:
			context->outgoingRas->RasMsg.u.admissionConfirm = 
				(H225AdmissionConfirm*)ASN1MALLOC(pctxt,sizeof(H225AdmissionConfirm));
			if(context->outgoingRas->RasMsg.u.admissionConfirm == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras admission confirm"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.admissionConfirm,0,
					sizeof(H225AdmissionConfirm));
			break;
		case T_H225RasMessage_admissionReject:
			context->outgoingRas->RasMsg.u.admissionReject = 
				(H225AdmissionReject*)ASN1MALLOC(pctxt,sizeof(H225AdmissionReject));
			if(context->outgoingRas->RasMsg.u.admissionReject == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras admission reject"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.admissionReject,0,
					sizeof(H225AdmissionReject));
			break;
		case T_H225RasMessage_bandwidthRequest:
			context->outgoingRas->RasMsg.u.bandwidthRequest = 
				(H225BandwidthRequest*)ASN1MALLOC(pctxt,sizeof(H225BandwidthRequest));
			if(context->outgoingRas->RasMsg.u.bandwidthRequest == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras bandwidth request"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.bandwidthRequest,0,
					sizeof(H225BandwidthRequest));				
			break;
		case T_H225RasMessage_bandwidthConfirm:
			context->outgoingRas->RasMsg.u.bandwidthConfirm = 
				(H225BandwidthConfirm*)ASN1MALLOC(pctxt,sizeof(H225BandwidthConfirm));
			if(context->outgoingRas->RasMsg.u.bandwidthConfirm == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras bandwidth confirm"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.bandwidthConfirm,0,
					sizeof(H225BandwidthConfirm));
			break;
		case T_H225RasMessage_bandwidthReject:
			context->outgoingRas->RasMsg.u.bandwidthReject = 
				(H225BandwidthReject*)ASN1MALLOC(pctxt,sizeof(H225BandwidthReject));
			if(context->outgoingRas->RasMsg.u.bandwidthReject == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras bandwidth reject"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.bandwidthReject,0,
					sizeof(H225AdmissionReject));
			break;
		case T_H225RasMessage_disengageRequest:
			context->outgoingRas->RasMsg.u.disengageRequest = 
				(H225DisengageRequest*)ASN1MALLOC(pctxt,sizeof(H225DisengageRequest));
			if(context->outgoingRas->RasMsg.u.disengageRequest == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras disengage request"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.disengageRequest,0,
					sizeof(H225DisengageRequest));				
			break;
		case T_H225RasMessage_disengageConfirm:
			context->outgoingRas->RasMsg.u.disengageConfirm = 
				(H225DisengageConfirm*)ASN1MALLOC(pctxt,sizeof(H225DisengageConfirm));
			if(context->outgoingRas->RasMsg.u.disengageConfirm == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras disengage confirm"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.disengageConfirm,0,
					sizeof(H225BandwidthConfirm));
			break;
		case T_H225RasMessage_disengageReject:
			context->outgoingRas->RasMsg.u.disengageReject = 
				(H225DisengageReject*)ASN1MALLOC(pctxt,sizeof(H225DisengageReject));
			if(context->outgoingRas->RasMsg.u.disengageReject == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras disengage reject"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.disengageReject,0,
					sizeof(H225DisengageReject));
			break;
		case T_H225RasMessage_locationRequest:
			context->outgoingRas->RasMsg.u.locationRequest = 
				(H225LocationRequest*)ASN1MALLOC(pctxt,sizeof(H225LocationRequest));
			if(context->outgoingRas->RasMsg.u.locationRequest == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras location request"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.locationRequest,0,
					sizeof(H225LocationRequest));				
			break;
		case T_H225RasMessage_locationConfirm:
			context->outgoingRas->RasMsg.u.locationConfirm = 
				(H225LocationConfirm*)ASN1MALLOC(pctxt,sizeof(H225LocationConfirm));
			if(context->outgoingRas->RasMsg.u.locationConfirm == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras location confirm"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.locationConfirm,0,
					sizeof(H225LocationConfirm));
			break;
		case T_H225RasMessage_locationReject:
			context->outgoingRas->RasMsg.u.locationReject = 
				(H225LocationReject*)ASN1MALLOC(pctxt,sizeof(H225LocationReject));
			if(context->outgoingRas->RasMsg.u.locationReject == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras location reject"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.locationReject,0,
					sizeof(H225LocationReject));
			break;
		case T_H225RasMessage_infoRequest:
			context->outgoingRas->RasMsg.u.infoRequest = 
				(H225InfoRequest*)ASN1MALLOC(pctxt,sizeof(H225InfoRequest));
			if(context->outgoingRas->RasMsg.u.infoRequest == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras info request"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.infoRequest,0,
					sizeof(H225InfoRequest));				
			break;
		case T_H225RasMessage_infoRequestResponse:
			context->outgoingRas->RasMsg.u.infoRequestResponse = 
				(H225InfoRequestResponse*)ASN1MALLOC(pctxt,sizeof(H225InfoRequestResponse));
			if(context->outgoingRas->RasMsg.u.infoRequestResponse == 0) 
			{  
				OOTRACEERR2(context, "Memory allocation for ras info Request response"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.infoRequestResponse,0,
					sizeof(H225InfoRequestResponse));
			break;
		case T_H225RasMessage_nonStandardMessage:
			context->outgoingRas->RasMsg.u.nonStandardMessage = 
				(H225NonStandardMessage*)ASN1MALLOC(pctxt,sizeof(H225NonStandardMessage));
			if(context->outgoingRas->RasMsg.u.nonStandardMessage == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras nonStandard message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.nonStandardMessage,0,
					sizeof(H225NonStandardMessage));
			break;
		case T_H225RasMessage_requestInProgress:
			context->outgoingRas->RasMsg.u.requestInProgress = 
				(H225RequestInProgress*)ASN1MALLOC(pctxt,sizeof(H225RequestInProgress));
			if(context->outgoingRas->RasMsg.u.requestInProgress == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras request In progress message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.requestInProgress,0,
					sizeof(H225RequestInProgress));
			break;
		case T_H225RasMessage_resourcesAvailableIndicate:
			context->outgoingRas->RasMsg.u.resourcesAvailableIndicate = 
				(H225ResourcesAvailableIndicate*)ASN1MALLOC(pctxt,sizeof(H225ResourcesAvailableIndicate));
			if(context->outgoingRas->RasMsg.u.resourcesAvailableIndicate == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras resources Available Indicate message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.resourcesAvailableIndicate,0,
					sizeof(H225ResourcesAvailableIndicate));
			break;
		case T_H225RasMessage_resourcesAvailableConfirm:
			context->outgoingRas->RasMsg.u.resourcesAvailableConfirm = 
				(H225ResourcesAvailableConfirm*)ASN1MALLOC(pctxt,sizeof(H225ResourcesAvailableConfirm));
			if(context->outgoingRas->RasMsg.u.resourcesAvailableConfirm == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras resourcesAvailableConfirm message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.resourcesAvailableConfirm,0,
					sizeof(H225ResourcesAvailableConfirm));
			break;
		case T_H225RasMessage_infoRequestAck:
			context->outgoingRas->RasMsg.u.infoRequestAck = 
				(H225InfoRequestAck*)ASN1MALLOC(pctxt,sizeof(H225InfoRequestAck));
			if(context->outgoingRas->RasMsg.u.infoRequestAck == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras info request message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.infoRequestAck,0,
					sizeof(H225InfoRequestAck));
			break;
		case T_H225RasMessage_infoRequestNak:
			context->outgoingRas->RasMsg.u.infoRequestNak = 
				(H225InfoRequestNak*)ASN1MALLOC(pctxt,sizeof(H225InfoRequestNak));
			if(context->outgoingRas->RasMsg.u.infoRequestNak == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras InfoRequestNak message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.infoRequestNak,0,
					sizeof(H225InfoRequestNak));
			break;
		case T_H225RasMessage_serviceControlIndication:
			context->outgoingRas->RasMsg.u.serviceControlIndication = 
				(H225ServiceControlIndication*)ASN1MALLOC(pctxt,sizeof(H225ServiceControlIndication));
			if(context->outgoingRas->RasMsg.u.serviceControlIndication == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras serviceControlIndication message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.serviceControlIndication,0,
					sizeof(H225ServiceControlIndication));
			break;
		case T_H225RasMessage_serviceControlResponse:
			context->outgoingRas->RasMsg.u.serviceControlResponse = 
				(H225ServiceControlResponse*)ASN1MALLOC(pctxt,sizeof(H225ServiceControlResponse));
			if(context->outgoingRas->RasMsg.u.serviceControlResponse == 0)
			{  
				OOTRACEERR2(context, "Memory allocation for ras serviceControlResponse message"
                                     " message failed");
				return OO_FAILED;
			}
			else
				memset(context->outgoingRas->RasMsg.u.serviceControlResponse,0,
					sizeof(H225ServiceControlResponse));
			break;
		case T_H225RasMessage_admissionConfirmSequence:
			break;
         default:
            OOTRACEERR2(context,"ERROR: Ras message type not supported");
      }
      return OO_OK;
   }
}

int ooFreeRasMessage(struct ooAppContext *context, RasMessage *pmsg)
{
   OOCTXT *pctxt;
   if(pmsg == NULL)
   {
      OOTRACEWARN2(context, "ERROR: No Ras message to free");
      return OO_FAILED;
   } 

   if(context->outgoingRas == pmsg)
      context->outgoingRas = NULL;
   pctxt = pmsg->pctxt;
   freeContext(pctxt);
   ASN1CRTFREE0(pctxt);
  
   return OO_OK;
}

int ooGetOutgoingRasMsgbuf(struct ooAppContext *context,ASN1OCTET *msgbuf,int *len,int *msgType)
{
   RasMessage *p_RasMsg=NULL;
   H225RasMessage *h225RasMsg=NULL;
   DListNode * p_msgNode=NULL;
   int i =0;
   ASN1BOOL aligned =TRUE, trace =FALSE;
   ASN1OCTET encodeBuf[1024];
   ASN1OCTET* encodeptr=NULL;
   int encodeLen=0;
   OOCTXT* pctxt=NULL;
   memset(encodeBuf, 0, sizeof(encodeBuf));

   if(context->outRasQueue.count == 0)
   {
      OOTRACEERR2(context,"ERROR:No outgoing ras message");
      return OO_FAILED;
   }
   p_msgNode = context->outRasQueue.head;
   p_RasMsg = (RasMessage*) p_msgNode->data;
   *msgType = p_RasMsg->msgType;
   h225RasMsg = &(p_RasMsg->RasMsg);
   /* Encode the Multimedia Control Message */
   pctxt = p_RasMsg->pctxt;
   setPERBuffer(pctxt, encodeBuf, sizeof(encodeBuf), aligned);

   if(asn1PE_H225RasMessage(pctxt, h225RasMsg)!=ASN_OK)
   {
      OOTRACEERR2(context, "ERROR: ras Message encoding failed");
      /* Free memory associated with the message */
      freeContext(pctxt);
      ASN1CRTFREE0(pctxt);
      return OO_FAILED;
   }
   
   encodeptr = encodeGetMsgPtr(pctxt, &encodeLen);
   memcpy(msgbuf,encodeptr,encodeLen);
   *len = encodeLen;

   dListRemove(&(context->outRasQueue), p_msgNode);

   /* Free memory associated with the message */
   freeContext(pctxt);
   ASN1CRTFREE0(pctxt);
   
   if(p_msgNode)
      ASN1MEMFREEPTR(&(context->outRasListCtxt), p_msgNode);      

   return OO_OK;
}

/*EXTERN int ooSendRegistrationRequestMsg(struct ooAppContext *context)
{
	int ret;
	H225RegistrationRequest *regRequest;
	OOCTXT *pctxt;
	static ASN1USINT SeqNo = 0;
	H225TransportAddress *CallSignalAddress;
	int addr_seg1,addr_seg2,addr_seg3,addr_seg4;
	char hexIp[20];
	H225TransportAddress_ipAddress destIpAddr;
	H225TransportAddress *RasAddress;


   ret = ooCreateRasMessage(context,T_H225RasMessage_registrationRequest);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(context,"Error:Failed to create Ras message");
      return ret;
   }
	
   regRequest = context->outgoingRas->RasMsg.u.registrationRequest;
   pctxt = context->outgoingRas->pctxt;

   regRequest->m.terminalAliasPresent = 1;
   regRequest->requestSeqNum = ( SeqNo++ ) % 65536;
   regRequest->protocolIdentifier = gRasProtocolID;
   regRequest->discoveryComplete = FALSE;
   CallSignalAddress = (H225TransportAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress));
   memset(CallSignalAddress,0,sizeof(H225TransportAddress));
   CallSignalAddress->t = T_H225TransportAddress_ipAddress;

   sscanf(destIp,"%d.%d.%d.%d",&addr_seg1,&addr_seg2,&addr_seg3,&addr_seg4);
   sprintf(hexIp,"%x %x %x %x",addr_seg1,addr_seg2,addr_seg3,addr_seg4);
   sscanf(hexIp,"%x %x %x %x",&destIpAddr.ip.data[0],&destIpAddr.ip.data[1],
	   &destIpAddr.ip.data[2],&destIpAddr.ip.data[3]);
   CallSignalAddress->u.ipAddress = &destIpAddr;

   dListInit(&(regRequest->callSignalAddress));
   dListAppend(pctxt,&(regRequest->callSignalAddress),CallSignalAddress);
	
   RasAddress = (H225TransportAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress));
   memset(RasAddress,0,sizeof(H225TransportAddress));
   dListInit(&(regRequest->rasAddress));
   dListAppend(pctxt,&(regRequest->rasAddress),RasAddress);
	


		
	
	return OO_OK;
}*/

