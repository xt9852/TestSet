// H323MsgHandler.cpp: implementation of the CH323MsgHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "H323MsgHandler.h"
#include "Base\ooh245.h"

#include "IncomingCallDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HANDLE CH323MsgHandler::hRespondEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
BOOL CH323MsgHandler::bAcceptCall = FALSE;
extern struct ooAppContext* myContext;
struct ooAppContext* CH323MsgHandler::context;
CDlg_H323* CH323MsgHandler::MainWnd = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CH323MsgHandler::CH323MsgHandler()
{

}

CH323MsgHandler::~CH323MsgHandler()
{

}

DWORD CH323MsgHandler::MsgMonitorProc(LPVOID lpParameter)
{
	MainWnd = (CDlg_H323*)lpParameter;
	context = myContext;
	ooMonitorChannels(context);
	return 1;
}

//////////////////////////////////////////////////////////////////////////
int CH323MsgHandler::OnReceivedRasMsg(void *msg)
{
	RasMessage *RasMsg = (RasMessage*)msg;
	int nResult;
	switch(RasMsg->RasMsg.t)
	{
	case T_H225RasMessage_gatekeeperRequest:
		break;
	case T_H225RasMessage_gatekeeperConfirm:
		break;
	case T_H225RasMessage_gatekeeperReject:
		break;
	case T_H225RasMessage_registrationRequest:
		nResult = OnRecvRasRRQ(RasMsg);
		break;
	case T_H225RasMessage_registrationConfirm:
		nResult = OnRecvRasRCF(RasMsg);
		break;
	case T_H225RasMessage_registrationReject:
		nResult = OnRecvRasRRJ(RasMsg);
		break;
	case T_H225RasMessage_unregistrationRequest:
		nResult = OnRecvRasURQ(RasMsg);
		break;
	case T_H225RasMessage_unregistrationConfirm:
		nResult = OnRecvRasUCF(RasMsg);
		break;
	case T_H225RasMessage_unregistrationReject:
		nResult = OnRecvRasURJ(RasMsg);
		break;
	case T_H225RasMessage_admissionRequest:
		nResult = OnRecvRasARQ(RasMsg);
		break;
	case T_H225RasMessage_admissionConfirm:
		nResult = OnRecvRasACF(RasMsg);
		break;
	case T_H225RasMessage_admissionReject:
		nResult = OnRecvRasRRJ(RasMsg);
		break;
	case T_H225RasMessage_bandwidthRequest:
		break;
	case T_H225RasMessage_bandwidthConfirm:
		break;
	case T_H225RasMessage_bandwidthReject:
		break;
	case T_H225RasMessage_disengageRequest:
		nResult = OnRecvRasDRQ(RasMsg);
		break;
	case T_H225RasMessage_disengageConfirm:
		nResult = OnRecvRasDCF(RasMsg);
		break;
	case T_H225RasMessage_disengageReject:
		nResult = OnRecvRasDRJ(RasMsg);
		break;
	case T_H225RasMessage_locationRequest:
		break;
	case T_H225RasMessage_locationConfirm:
		break;
	case T_H225RasMessage_locationReject:
		break;
	case T_H225RasMessage_infoRequest:
		break;
	case T_H225RasMessage_infoRequestResponse:
		break;
	case T_H225RasMessage_nonStandardMessage:
		break;
	case T_H225RasMessage_unknownMessageResponse:
		break;
	case T_H225RasMessage_requestInProgress:
		break;
	case T_H225RasMessage_resourcesAvailableIndicate:
		break;
	case T_H225RasMessage_resourcesAvailableConfirm:
		break;
	case T_H225RasMessage_infoRequestAck:
		break;
	case T_H225RasMessage_infoRequestNak:
		break;
	case T_H225RasMessage_serviceControlIndication:
		break;
	case T_H225RasMessage_serviceControlResponse:
		break;
	case T_H225RasMessage_admissionConfirmSequence:
		break;
	default:
		 OOTRACEWARN2(context, "Invalid Ras message type received");
		 ooFreeRasMessage(context, RasMsg);
		 nResult = -1;
	}
	
	return nResult;
}

int CH323MsgHandler::OnRecvRasRRQ(RasMessage *msg)
{

	return 0;
}

int CH323MsgHandler::OnRecvRasRCF(RasMessage *msg)
{
	OOTRACEINFO2(context, "Ras RCF message received");
	//here do something with the Ras RCF message...
	
	//暂时写在这里，应该做成函数来处理相应的消息
	int nCharNum = msg->RasMsg.u.registrationConfirm->endpointIdentifier.nchars;
	if(nCharNum > 0)
	{
		context->epIdentifier.nchars = nCharNum;
		context->epIdentifier.data = (ASN116BITCHAR*)ASN1MALLOC(&context->glbCtxt,nCharNum * sizeof(ASN116BITCHAR));
		memcpy(context->epIdentifier.data,msg->RasMsg.u.registrationConfirm->endpointIdentifier.data,
			sizeof(ASN116BITCHAR) * nCharNum);
	}

	MainWnd->PostMessage(WM_USER_RECVRCF);
	
	ooFreeRasMessage(context, msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasRRJ(RasMessage *msg)
{

	ooFreeRasMessage(context,msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasURQ(RasMessage *msg)
{
	ooFreeRasMessage(context,msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasUCF(RasMessage *msg)
{
	OOTRACEINFO2(context, "Ras RCF message received");
	MainWnd->m_bRegistered = FALSE;
	SetEvent(hRespondEvent);
	ooFreeRasMessage(context, msg);	
	return 0;
}

int CH323MsgHandler::OnRecvRasURJ(RasMessage *msg)
{

	ooFreeRasMessage(context,msg);
	return 0;	
}

int CH323MsgHandler::OnRecvRasARQ(RasMessage *msg)
{

	ooFreeRasMessage(context,msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasACF(RasMessage *msg)
{
	OOTRACEINFO2(context, "Ras ACF message received");
	//here do something with the Ras ACF message...

	H225TransportAddress *pAddress = &(msg->RasMsg.u.admissionConfirm->destCallSignalAddress);
	if(pAddress->t == T_H225TransportAddress_ipAddress)	//记录被叫地址
	{
		sprintf(context->remoteIP, "%d.%d.%d.%d", 
			   pAddress->u.ipAddress->ip.data[0], 
			   pAddress->u.ipAddress->ip.data[1],
			   pAddress->u.ipAddress->ip.data[2],
			   pAddress->u.ipAddress->ip.data[3]);
	}

	if(MainWnd->m_bAsCaller)	//作为主叫收到此消息
		MainWnd->PostMessage(WM_USER_RECVACF);
	else	//作为被叫收到此消息
	{
		ooSendAlerting(context);
		ooCreateH245Channel(context, &CH323MsgHandler::OnReceivedH245Msg,NULL, OORECEIVER);
		ooSendConnect(context); // Send connect message - call accepted
		MainWnd->PostMessage(WM_USER_SENDCONNECT);
	}
	
	ooFreeRasMessage(context, msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasARJ(RasMessage *msg)
{

	ooFreeRasMessage(context, msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasDRQ(RasMessage *msg)
{

	ooFreeRasMessage(context, msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasDCF(RasMessage *msg)
{
	SetEvent(hRespondEvent);

	ooFreeRasMessage(context,msg);
	return 0;
}

int CH323MsgHandler::OnRecvRasDRJ(RasMessage *msg)
{

	ooFreeRasMessage(context, msg);
	return 0;
}
//////////////////////////////////////////////////////////////////////////

int CH323MsgHandler::OnReceivedH2250Msg(void *msg)
{
	Q931Message *q931Msg = (Q931Message*)msg;
	int nType = q931Msg->messageType;
	int nResult;
	switch(nType)
	{
	case Q931SetupMsg:
		nResult = OnRecvQ931SetupMsg(q931Msg);
		break;
	case Q931CallProceedingMsg:
		nResult = OnRecvQ931CallProceedingMsg(q931Msg);
		break;
	case Q931AlertingMsg:
		nResult = OnRecvQ931AlertingMsg(q931Msg);
		break;
	case Q931ConnectMsg:
		nResult = OnRecvQ931ConnectMsg(q931Msg);
		break;
	case Q931InformationMsg:
		nResult = OnRecvQ931InformationMsg(q931Msg);
		break;
	case Q931ReleaseCompleteMsg:
		nResult = OnRecvQ931ReleaseCompleteMsg(q931Msg);
		break;
	case Q931FacilityMsg:
		nResult = OnRecvQ931FacilityMsg(q931Msg);
		break;
	case Q931ProgressMsg:
		nResult = OnRecvQ931ProgressMsg(q931Msg);
		break;
	case Q931StatusMsg:
		nResult = OnRecvQ931StatusMsg(q931Msg);
		break;
	case Q931StatusEnquiryMsg:
		nResult = OnRecvQ931StatusEnquiryMsg(q931Msg);
		break;
	case Q931SetupAckMsg:
		nResult = OnRecvQ931SetupAckMsg(q931Msg);
		break;
	case Q931NotifyMsg:
		nResult = OnRecvQ931NotifyMsg(q931Msg);
		break;
	default:
		 OOTRACEWARN2(context, "Invalid H.225 message type received");
		 ooFreeQ931Message(context, q931Msg);
		 nResult = -1;
	}

	return nResult;
}

int CH323MsgHandler::OnReceivedH245Msg(void *msg)
{
  H245Message *pH245 = (H245Message*)msg;
   /* There are four major types of H.245 messages that can be received.
      Request/Response/Command/Indication. Each one of them need to be 
      handled separately.
   */   
  H245RequestMessage *request;
   H245ResponseMessage *response;
   H245CommandMessage *command;
   static H245RequestMessage *OLDrequest;
   H245TerminalCapabilitySet *termCap;
   int iResult=0;   
   switch(pH245->h245Msg.t)
   {
     /* H.245 Request message is received */
     case (T_H245MultimediaSystemControlMessage_request)://1
         request = pH245->h245Msg.u.request;		 
         switch(request->t)
         {
         case T_H245RequestMessage_terminalCapabilitySet://3			
			OLDrequest =pH245->h245Msg.u.request;
            //在此确定能力Capability
			termCap = (H245TerminalCapabilitySet*)(request->u.terminalCapabilitySet);	
			OnNegotiateCapability(termCap);//函数协商接收音频能力
			OnReceivedTerminalCapabilitySet(
                        request->u.terminalCapabilitySet);//设定接收能力在能力列表中的序号
			//iCapabilitySet=1;
			/*Modified by Karl on 2004-11-19 below*/
    		
            /*if(termCap->sequenceNumber==1 || termCap->sequenceNumber==4 || termCap->sequenceNumber<=4){
			    context->endCapability->receiveAudioCapability->t = 4;
			    context->endCapability->receiveAudioCapability->u.g711Ulaw64k = 240;
			}else if(termCap->sequenceNumber==12){//G729AnnexA
			    context->endCapability->receiveAudioCapability->t = 12;
			    context->endCapability->receiveAudioCapability->u.g729AnnexA = 60;			    				
                context->endCapability->receiveAudioCapability->t = T_H245AudioCapability_g729AnnexA;				
			}else if(termCap->sequenceNumber==7){
			    context->endCapability->receiveAudioCapability->t = 7;
			    context->endCapability->receiveAudioCapability->u.g721_32k = 60;
                context->endCapability->receiveAudioCapability->t = T_H245AudioCapability_g721_32k;
			}*/
			/*Modified by Karl on 2004-11-19 above*/
            break;
         case T_H245RequestMessage_masterSlaveDetermination://2
            ooHandleMasterSlave(context, 
                                  request->u.masterSlaveDetermination, 
                                  OOMasterSlaveDetermination);
            break;
         case T_H245RequestMessage_openLogicalChannel://4
			//根据对方的接收Audio能力,决定何种传输能力
			if(request->u.openLogicalChannel->forwardLogicalChannelParameters.dataType.u.audioData->t == 12)
			{
				context->endCapability->transmitAudioCapability->t = 12;
			    context->endCapability->transmitAudioCapability->u.g729AnnexA = 60;
				                
				context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g729AnnexA;
			}else if(request->u.openLogicalChannel->forwardLogicalChannelParameters.dataType.u.audioData->t == 4
				|| request->u.openLogicalChannel->forwardLogicalChannelParameters.dataType.u.audioData->t == 1
				|| request->u.openLogicalChannel->forwardLogicalChannelParameters.dataType.u.audioData->t <= 4)
			{
			    context->endCapability->transmitAudioCapability->t = 4;
			    context->endCapability->transmitAudioCapability->u.g711Ulaw64k = 240;
			    //context->endCapability->receiveAndTransmitAudioCapability->t = 4;
			    //context->endCapability->receiveAndTransmitAudioCapability->u.g711Ulaw64k = 240;
				
				context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g711Ulaw64k;
				
			}else if(request->u.openLogicalChannel->forwardLogicalChannelParameters.dataType.u.audioData->t == 7)
			{
			    context->endCapability->transmitAudioCapability->t = 7;
			    context->endCapability->transmitAudioCapability->u.g721_32k = 60;
                
				context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g721_32k;
			}
            ooHandleOpenLogicalChannel(context, 
                                       request->u.openLogicalChannel);
            ooCreateReceiveRTPChannel(context, context->localIP, 
                                      context->localRtpPort);
            ooStartReceiveAudioAndPlayback(context);
            break;
         case T_H245RequestMessage_closeLogicalChannel://5
            break;
         default:
            ;
         }
         break;
      /* H.245 Response message is received */ 
      case (T_H245MultimediaSystemControlMessage_response)://2
         response = pH245->h245Msg.u.response;
         switch(response->t)
         {
         case T_H245ResponseMessage_masterSlaveDeterminationAck://2
            ooHandleMasterSlave(context, 
                                  response->u.masterSlaveDeterminationAck, 
                                  OOMasterSlaveAck);
			/*Modified by Karl on 2005-01-19 below*/
            /*Default Send terminal capability set message for G.729A transmit/
               receive capability.
            */
            /* Send terminal capability set message for G.711/G729/G721 transmit/
               receive capability.
            */            
		   iResult = ooSendIntegrationCallTermCapMsg(context);
           /*if(context->endCapability->receiveAndTransmitAudioCapability->t == 12){
				iResult = ooSendG729ACallTermCapMsg(context);
			}else if(context->endCapability->receiveAndTransmitAudioCapability->t == 4){
				ooSendG711CallTermCapMsg(context);
			}else if(context->endCapability->receiveAndTransmitAudioCapability->t == 7){
				iResult = ooSendG721CallTermCapMsg(context);
			}*/
			/*Modified by Karl on 2005-01-19 above*/
            break;
         case T_H245ResponseMessage_terminalCapabilitySetAck://4
    		/*Modified by Karl on 2004-11-18 below*/
            /* Since capabilities are exchanged, create RTP session */
			/* Open G.729AnnexA  channel */
			/*if(response->u.terminalCapabilitySetAck->sequenceNumber == 12)
			{
				context->endCapability->transmitAudioCapability->t = 12;
			    context->endCapability->transmitAudioCapability->u.g729AnnexA = 60;
				                
				context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g729AnnexA;
			}else if(response->u.terminalCapabilitySetAck->sequenceNumber == 4
				|| response->u.terminalCapabilitySetAck->sequenceNumber == 1
				|| response->u.terminalCapabilitySetAck->sequenceNumber <= 4)
			{
				//context->endCapability->receiveAudioCapability->t = 4;
			    //context->endCapability->receiveAudioCapability->u.g711Ulaw64k = 240;
			    context->endCapability->transmitAudioCapability->t = 4;
			    context->endCapability->transmitAudioCapability->u.g711Ulaw64k = 240;
			    //context->endCapability->receiveAndTransmitAudioCapability->t = 4;
			    //context->endCapability->receiveAndTransmitAudioCapability->u.g711Ulaw64k = 240;
				
				//context->endCapability->receiveAudioCapability->t = T_H245AudioCapability_g711Ulaw64k;
				//context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g711Ulaw64k;
				
			}else if(response->u.terminalCapabilitySetAck->sequenceNumber == 7)
			{
			    context->endCapability->transmitAudioCapability->t = 7;
			    context->endCapability->transmitAudioCapability->u.g721_32k = 60;
                
				context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g721_32k;
			}*/		 
			iResult=0;
			if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g729AnnexA)
			{
				iResult = ooOpeng729AnnexALogicalChannel(context);
			}else if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g711Ulaw64k)
			{
				iResult = ooOpeng711ulawLogicalChannel(context);
			}else if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g721_32k)
            {
				iResult = ooOpeng721LogicalChannel(context);
			}
         
			/*Modified by Karl on 2004-11-18 above*/
            break;
         case T_H245ResponseMessage_openLogicalChannelAck://==6
            ooOnReceivedOpenLogicalChannelAck(context, 
                                           response->u.openLogicalChannelAck);
            
            /* Since (G.729A/G.711/G.721) logical channel is created, start RTP transmit */
            ooCreateTransmitRTPChannel(context, context->remoteIP, 
                                       context->remoteRtpPort);
			ooStartTransmitMic(context);
            break;
		 case T_H245ResponseMessage_openLogicalChannelReject://==7			 
			 iResult=0;
			 break;
         default:
            ;
         }
         break;
      /* H.245 command message is received */
      case (T_H245MultimediaSystemControlMessage_command)://3
         command = pH245->h245Msg.u.command;
         ooHandleH245Command(context, command);
         break;
      /* H.245 Indication message received */
      case (T_H245MultimediaSystemControlMessage_indication)://4
		 iResult=0;
         break;
      case (T_H245MultimediaSystemControlMessage_extElem1)://5
		 iResult=0;
         break;
      default:
        ;
   }
   ooFreeH245Message(context, pH245);
   return OO_OK;	
}

/*** ------		Q931 message handler ------ ***/
int CH323MsgHandler::OnRecvQ931SetupMsg(Q931Message *msg)
{
	OOTRACEINFO2(context, "H.225 Call setup message received");
	//Do something with the Call setup message here
	
	if(MainWnd->DoNotBother() == TRUE) //勿打扰
	{
		ooSendReleaseComplete(context);
		ooFreeQ931Message(context,msg);
		return 0;
	}

	ooOnReceivedSetup(context, msg);
 	ooSendCallProceeding(context);
	if(MainWnd->IsAutoAnswer() == FALSE)
	{
		MainWnd->PostMessage(WM_USER_INCOMINGCALL);
		WaitForSingleObject(hRespondEvent,INFINITE); //等待主线程对来电的反应
		if(bAcceptCall == FALSE)	//拒绝来电
		{
			ooSendReleaseComplete(context);
			ooFreeQ931Message(context,msg);
			return 0;
		}

		//复位hRespond,bAcceptCall
		ResetEvent(hRespondEvent);
		bAcceptCall = FALSE;
	}

	if(context->callByGK)
	{
		//这里需要改一下
		MainWnd->m_bAsCaller = FALSE;
		MainWnd->AdmissionRequest();
		ooFreeQ931Message(context,msg);
		return 0;
	}

	ooSendAlerting(context);
	/* Create H.245 channel and listen for incoming messages. Note
	here, we also register the call back function which will handle
	received H.245 control messages. */
	ooCreateH245Channel(context, OnReceivedH245Msg,NULL, OORECEIVER);
	ooSendConnect(context); // Send connect message - call accepted
	MainWnd->PostMessage(WM_USER_SENDCONNECT);

	/* Free up the mem used by the received message, as it's processing 
	is done.*/
	ooFreeQ931Message(context, msg);
	return 0;
}

int CH323MsgHandler::OnRecvQ931CallProceedingMsg(Q931Message *msg)
{
	return 0;
}

int CH323MsgHandler::OnRecvQ931AlertingMsg(Q931Message* msg)
{

	return 0;
}

int CH323MsgHandler::OnRecvQ931ConnectMsg(Q931Message *msg)
{
	OOTRACEINFO2(context, "H.225 Connect message received");
	
	OnReceivedSignalConnect(msg);
	MainWnd->PostMessage(WM_USER_RECVCONNECT);

	//for debug
	H225H323_UserInformation ui;
	ooQ931GetUUIE(context,msg,&ui);
	//
	ooFreeQ931Message(context, msg);
	return 0;
}

int CH323MsgHandler::OnRecvQ931InformationMsg(Q931Message *msg)
{
	return 0;
}

int CH323MsgHandler::OnRecvQ931ReleaseCompleteMsg(Q931Message *msg)
{
	H225H323_UserInformation ui;
	ooQ931GetUUIE(context,msg,&ui);
	if(ui.h323_uu_pdu.h323_message_body.t != T_H225H323_UU_PDU_h323_message_body_releaseComplete)
	{
		OOTRACEINFO2(context, "Receive invalid H.225 releaseComplete message");
		ooFreeQ931Message(context,msg);
		return -1;
	}

	OOTRACEINFO2(context, "Receive invalid H.225 releaseComplete message");
	switch(ui.h323_uu_pdu.h323_message_body.u.releaseComplete->reason.t)
	{
	case T_H225ReleaseCompleteReason_destinationRejection:
		AfxMessageBox("呼叫被拒绝!");
		break;
	//...待完成
	}
	
	if(context->callByGK)
		MainWnd->DisengageRequest();
	else
		SetEvent(hRespondEvent);

	ooCloseH225Channel(myContext);// Close H.225 channel
	ooFreeQ931Message(context, msg);
	MainWnd->PostMessage(WM_USER_RECVReleaseComplete);
	return 0;
}

int CH323MsgHandler::OnRecvQ931FacilityMsg(Q931Message *msg)
{
	return 0;

}

int CH323MsgHandler::OnRecvQ931ProgressMsg(Q931Message *msg)
{
	return 0;

}

int CH323MsgHandler::OnRecvQ931StatusMsg(Q931Message *msg)
{
	return 0;

}

int CH323MsgHandler::OnRecvQ931StatusEnquiryMsg(Q931Message *msg)
{
	return 0;

}

int CH323MsgHandler::OnRecvQ931SetupAckMsg(Q931Message *msg)
{
	return 0;

}

int CH323MsgHandler::OnRecvQ931NotifyMsg(Q931Message *msg)
{
	return 0;
	
}

int CH323MsgHandler::OnReceivedSignalConnect(Q931Message *q931Msg)
{
	int ret;
	H225H323_UserInformation userInfo;
	struct ooConnectionEP connectionEP;
	H225TransportAddress *h245Address;
	H225Connect_UUIE *connect;

	//Retrieve the user-user IE from received H.225 message    
	if(ooQ931GetUUIE(context, q931Msg, &userInfo) !=OO_OK)
	{
	  OOTRACEERR2(context, "Error: UUIE decode failed in received H.225 Connect message.");
	  return -1;
	}
	
	//Retrieve the connect message from the user-user IE 
	connect = userInfo.h323_uu_pdu.h323_message_body.u.connect;
	if(connect == NULL)
	{
	  OOTRACEERR2(context, "Error: Received Connect message does not "
							 "have Connect UUIE");
	  return -1;
	}
	//Retrieve the H.245 control channel address from the connect msg
	if(connect->m.h245AddressPresent == 0)
	{
	  OOTRACEERR2(context, "Error: Received Connect message does not "
							 "have H.245 address");
	  return -1;
	}
	h245Address = &(connect->h245Address);
	if(h245Address->t != T_H225TransportAddress_ipAddress)
	{
	  OOTRACEERR2(context,  "Error: Unknown H245 address type in "
							  "received Connect message");
	  return OO_FAILED;
	}
	sprintf(connectionEP.ipaddress, "%d.%d.%d.%d", 
		   h245Address->u.ipAddress->ip.data[0], 
		   h245Address->u.ipAddress->ip.data[1],
		   h245Address->u.ipAddress->ip.data[2],
		   h245Address->u.ipAddress->ip.data[3]);
	connectionEP.port = h245Address->u.ipAddress->port;
	/* Create an H.245 channel. The H.245 control addres of the destination 
	  is passed so that stack will connect to the destination endpoint 
	*/
	if(ooCreateH245Channel(context, &CH323MsgHandler::OnReceivedH245Msg, 
							&connectionEP, OOTRANSMITTER)== OO_FAILED)
	{
	  OOTRACEERR2(context, "Error: H.245 channel creation failed");
	  return -1;
	}

	//Send Master Slave determination Message
	ret = ooSendMasterSlaveDetermination(context);
	if(ret != OO_OK)
	{
	  OOTRACEERR2(context, "Error: MasterSlaveDetermination not sent");
	}

	return OO_OK;  
}
//////////////////////////////////////////////////////////////////////////
int CH323MsgHandler::OnReceivedTerminalCapabilitySet(void * pmsg)
{
   H245TerminalCapabilitySet *termCap = (H245TerminalCapabilitySet*)pmsg;
   ooH245AcknowledgeTerminalCapabilitySet(context,termCap->sequenceNumber);
   return OO_OK;	
}

/*Added by Karl on 2005-01-18 below*/
/*本函数协商接收音频能力*/
int CH323MsgHandler::OnNegotiateCapability(H245TerminalCapabilitySet* termCap)
{
    H245TerminalCapabilitySet_capabilityTable CapList;
	H245CapabilityTableEntry * entry;
    H245AudioCapability * entryReceiveCap;
	DListNode* pnode;
    int iCount = 0;	
	CapList = termCap->capabilityTable;
	pnode = CapList.head;
	iCount = (int)CapList.count;
    for(int i = 0; i < iCount; i++)
	{		
	    entry = (H245CapabilityTableEntry *)pnode->data;
		entryReceiveCap = entry->capability.u.receiveAudioCapability;
		switch(entryReceiveCap->t)
		{
		case 1://nonstandard
			if(context->endCapability->receiveAudioCapability->t <= 1)
			{
				context->endCapability->receiveAudioCapability->t = 4;
				context->endCapability->receiveAudioCapability->u.g711Ulaw64k = 60;
			}
			break;
		case 2://g711Alaw64k
			break;
		case 3://g711Alaw56k
			break;
		case 4://g711ulaw64k
			context->endCapability->receiveAudioCapability->t = 4;
		    context->endCapability->receiveAudioCapability->u.g711Ulaw64k = 60;
			//这里的transmitAudioCapability只是初步设定,最后在对方确认后有可能改变
		    context->endCapability->transmitAudioCapability->t = 4;
		    context->endCapability->transmitAudioCapability->u.g711Ulaw64k = 60;
			break;
		case 5://g711ulaw56k
			break;
		case 6://g721-40k			
			break;
		case 7://g721_32k
			if(context->endCapability->receiveAudioCapability->t <= 7)
			{
				context->endCapability->receiveAudioCapability->t = 7;
				context->endCapability->receiveAudioCapability->u.g721_32k = 60;
				context->endCapability->receiveAudioCapability->t = T_H245AudioCapability_g721_32k;

				//这里的transmitAudioCapability只是初步设定,最后在对方确认后有可能改变
			    context->endCapability->transmitAudioCapability->t = 7;
			    context->endCapability->transmitAudioCapability->u.g721_32k = 60;
			    context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g721_32k;
			}
			//return OO_OK;//获得较优算法,可以直接返回,不再需要协商-测试路径
			break;
		case 8://g721-24k
			//termCap->sequenceNumber = 8;
			break;
		case 9://g7231
			//termCap->sequenceNumber = 9;
			break;
		case 10://g728
            //termCap->sequenceNumber = 10;
			break;
		case 11://g729
			//termCap->sequenceNumber = 11;
			break;
		case 12://g729AnnexA
  		    context->endCapability->receiveAudioCapability->t = 12;
    	    context->endCapability->receiveAudioCapability->u.g729AnnexA = 60;			
            context->endCapability->receiveAudioCapability->t = T_H245AudioCapability_g729AnnexA;
            //这里的transmitAudioCapability只是初步设定,最后在对方确认后有可能改变
			context->endCapability->transmitAudioCapability->t = 12;
			context->endCapability->transmitAudioCapability->u.g729AnnexA = 60;
			context->endCapability->transmitAudioCapability->t = T_H245AudioCapability_g729AnnexA;
			return OO_OK;//获得较优算法,可以直接返回,不再需要协商
			break;
		case 13://
			break;
		case 14:
			break;
		case 15:
			break;
		case 16:
			break;
		case 17:
			break;
		case 18:
			break;
		case 19:
			break;
		case 20:
			break;
		case 21:
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			break;
		case 25:
			break;
		case 26:
			break;
		case 27:
			break;
		default:
			if(termCap->sequenceNumber <= 0)
			{
			   termCap->sequenceNumber = 1;
			}
			break;		
		}
		pnode = pnode->next;
		if(!pnode){
			break;
		}
	}
	if(termCap->sequenceNumber == 0)
	{
		termCap->sequenceNumber = 1;
	}else if(termCap->sequenceNumber == 4){
		termCap->sequenceNumber = 1;
	}
	return OO_OK;
}
/*Added by Karl on 2005-01-18 above*/