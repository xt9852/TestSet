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
 * @file ootypes.h 
 * This file contains the definitions of common constants and data structures 
 */

#ifndef _OOTYPES_H_
#define _OOTYPES_H_

#include "ooSocket.h"
#include "h323\MULTIMEDIA-SYSTEM-CONTROL.h"
#include "h323\H323-MESSAGES.h"
#include "ooasn1.h"

/* tracing */
#ifdef _OOWARNING
#define TRACELVL 2
#endif
#ifdef _OOINFO
#define TRACELVL 3
#endif
#ifdef _OODEBUGA
#define TRACELVL 4
#endif
#ifdef _OODEBUGB
#define TRACELVL 5
#endif
#ifdef _OODEBUGC
#define TRACELVL 6
#endif

/* Ensure we always log error messages */
#ifndef TRACELVL
#define TRACELVL 1
#endif

#define OOTRACEERR1(a)                ooTrace(NULL, a)
#define OOTRACEERR2(context,a)        ooTrace(context,a)
#define OOTRACEERR3(context,a,b)      ooTrace(context,a,b)
#define OOTRACEERR4(context,a,b,c)    ooTrace(context,a,b,c)
#define OOTRACEERR5(context,a,b,c,d)  ooTrace(context,a,b,c,d)
#define OOTRACEWARN2(context,a)       if(TRACELVL > 1) ooTrace(context,a)
#define OOTRACEWARN3(context,a,b)     if(TRACELVL > 1) ooTrace(context,a,b)
#define OOTRACEWARN4(context,a,b,c)   if(TRACELVL > 1) ooTrace(context,a,b,c)
#define OOTRACEWARN5(context,a,b,c,d) if(TRACELVL > 1) ooTrace(context,a,b,c,d)
#define OOTRACEINFO1(a)               if(TRACELVL > 2) ooTrace(NULL, a)
#define OOTRACEINFO2(context,a)       if(TRACELVL > 2) ooTrace(context,a)
#define OOTRACEINFO3(context,a,b)     if(TRACELVL > 2) ooTrace(context,a,b)
#define OOTRACEINFO4(context,a,b,c)   if(TRACELVL > 2) ooTrace(context,a,b,c)
#define OOTRACEINFO5(context,a,b,c,d) if(TRACELVL > 2) ooTrace(context,a,b,c,d)
#define OOTRACEDBGA2(context,a)       if(TRACELVL > 3) ooTrace(context,a)
#define OOTRACEDBGA3(context,a,b)     if(TRACELVL > 3) ooTrace(context,a,b)
#define OOTRACEDBGA4(context,a,b,c)   if(TRACELVL > 3) ooTrace(context,a,b,c)
#define OOTRACEDBGA5(context,a,b,c,d) if(TRACELVL > 3) ooTrace(context,a,b,c,d)
#define OOTRACEDBGB2(context,a)       if(TRACELVL > 4) ooTrace(context,a)
#define OOTRACEDBGB3(context,a,b)     if(TRACELVL > 4) ooTrace(context,a,b)
#define OOTRACEDBGB4(context,a,b,c)   if(TRACELVL > 4) ooTrace(context,a,b,c)
#define OOTRACEDBGB5(context,a,b,c,d) if(TRACELVL > 4) ooTrace(context,a,b,c,d)
#define OOTRACEDBGC2(context,a)       if(TRACELVL > 5) ooTrace(context,a)
#define OOTRACEDBGC3(context,a,b)     if(TRACELVL > 5) ooTrace(context,a,b)
#define OOTRACEDBGC4(context,a,b,c)   if(TRACELVL > 5) ooTrace(context,a,b,c)
#define OOTRACEDBGC5(context,a,b,c,d) if(TRACELVL > 5) ooTrace(context,a,b,c,d)


/*  types */
#define OO_FAILED -1
#define OO_OK 1
/**
  Various states of master slave determination prcedure
 */
#define OO_MasterSlave_Idle 2
#define OO_MasterSlave_DetermineSent 3
#define OO_MasterSlave_AckReceived 4
#define OO_MasterSlave_DetermineReceived 5
#define OO_MasterSlave_AckSent 6
#define OO_MasterSlave_Master 7
#define OO_MasterSlave_Slave 8

/**
   Terminal type of the endpoint. Default is 60.
 */
#define OOTERMTYPE 60

#define MAXLOGMSGLEN 1024
/**
   Various message types for H225 and H245 messages
 */
#define OORASMSG  100	//added by tony
#define OOQ931MSG 101
#define OOH245MSG 102
#define OOSetup 103
#define OOCallProceeding 104
#define OOAlert 105
#define OOConnect 106
#define OOReleaseComplete 107
#define OOMasterSlaveDetermination 108
#define OOMasterSlaveAck 109
#define OOMasterSlaveReject 110
#define OOMasterSlaveRelease 111
#define OOTerminalCapabilitySet 112
#define OOTerminalCapabilitySetAck 113
#define OOTerminalCapabilitySetReject 114
#define OOOpenLogicalChannel 115
#define OOOpenLogicalChannelAck 116
#define OOOpenLogicalChannelReject 117
#define OOOpenLogicalChannelRelease 118
#define OOEndSessionCommand 119
//added by tony below 2004.12.16
#define OOGatekeeperRequest 120
#define OOGatekeeperConfirm 121
#define OOGatekeeperReject	122
#define OORegistrationRequest	123
#define OORegistrationConfirm	124
#define OORegistrationReject	125
#define OOUnregistrationRequest	126
#define OOUnregistrationConfirm	127
#define OOUnregistrationReject	128
#define OOAdmissionRequest	129
#define OOAdmissionConfirm	130
#define OOAdmissionReject	131
#define OOBandwidthRequest	132
#define OOBandwidthConfirm	133
#define OOBandwidthReject	134
#define OODisengageRequest	135
#define OODisengageConfirm	136
#define OODisengageReject	137
#define OOLocationRequest	138
#define OOLocationConfirm	139
#define OOLocationReject	140
#define OOInfoRequest	141
#define OOInfoRequestResponse	142
//added by tony above 2004.12.16

/**
  Default port ranges used
*/
#define TCPPORTSSTART 2050
#define TCPPORTSEND 2150
#define UDPPORTSSTART 3050
#define UDPPORTSEND 3150
#define RTPPORTSSTART 4050
#define RTPPORTSEND 4250

/**
 Maximum length for received messages 
*/
#define MAXMSGLEN 4096


/** Type of callback functions to be registered at the time of
 * channel creation.
 */
typedef int (*ChannelCallback)(void*);

/**
 * Type of callback function registered at initialization
 * for handling commands
 */
typedef int (*CommandCallback)();
/**
 * This structure is used to define the port ranges to be used
 * by the application.
 */
struct ooH323Ports
{
   int start;
   int max;
   int current;
};

//added by tony below [2004.12.6]
typedef struct
{
	OOCTXT *pctxt;
	H225RasMessage RasMsg;
	ASN1BOOL msgType;			//ras message type
}RasMessage;
//added by tony above [2004.12.6]

/**
 Defines the Q931 message structure. Contains
 context for memory allocation, protocol Discriminator,
 call reference, meesage type and list of user user IEs.
*/
typedef struct Q931Message {
   OOCTXT* pctxt; /* context is used to allocate memory for */
                     /* different parts of the message */
   unsigned protocolDiscriminator;
   unsigned callReference;
   ASN1BOOL fromDestination;
   unsigned messageType; /* Q931MsgTypes  */

   DList ies;
} Q931Message;

/**
 Defines the H245 message structure. All request/response
 and command messages are represented using this structure.
*/
typedef struct H245Message {
   OOCTXT* pctxt;
   H245MultimediaSystemControlMessage h245Msg;
   ASN1UINT msgType;
} H245Message;

/** 
 * This structure holds the application context information
 * within the stack. App must create a context before calling any 
 * other stack function by calling ooInitialize
*/
struct ooAppContext
{
   /**
      The call reference value of the active call.
   */
   ASN1USINT            callReference;
   /**
      The call identifier for the active call.
   */
   H225CallIdentifier   callIdentifier;

	//added by tony below 2004.12.16
	H225EndpointIdentifier epIdentifier;
	OOCTXT glbCtxt;
   //added by tony above 2004.12.16

   //added by tony below 2004.12.13
   ASN1BOOL callByGK;				//call is managered by gatekeeper		
   H225ConferenceIdentifier conferenceId;
   //added by tony above 2004.12.13

   //added by tony below 2004.12.07
	OOSOCKET			RASChannel;
	char				GkIp[20];
	int					RasChanPort;
	ASN1USINT			seqNumber;	
	RasMessage *		outgoingRas;	//pointer to Ras outgoing message begin built
    int					sendRas;		//number of outgoing ras message queued
	ChannelCallback		RASCallback;
	DList				outRasQueue;
	OOCTXT				outRasListCtxt;
	//added by tony above 2004.12.07
	
   /**
      The h225 channel socket if the channel is established.
   */
   OOSOCKET             h225Channel;
   /**
      The h225 channel port if the channel is established.
   */
   int                  h225ChanPort;
   /**
      The h225 receive socket used for listening incoming calls.
   */
   OOSOCKET             h225Rx;
   int                  h225RxPort;
   /**   
      H.245 channel socket, if the channel is established 
   */
   OOSOCKET             h245Channel;
   int                  h245ChanPort;
   OOSOCKET             h245Rx;
   int                  h245RxPort;
   /** Remote RTP port */
   int                  remoteRtpPort;
   /** Remote RTCP port */
   int                  remoteRtcpPort;
   /** Remote IP address */
   char                 remoteIP[20];
   /** Local RTP port */
   int                  localRtpPort;
   /** Local RTCP port */
   int                  localRtcpPort;
   /** Local IP address */
   char                 localIP[20];
	
   /**
      Number of outgoing H225/Q931 messages queued
   */
   int                  sendH225;
   /**
      Number of outgoing H245 messages queued
   */
   int                  sendH245; 

   /** 
      Pointer to callback function handling incoming H.225/Q931 messages
   */
   ChannelCallback      h225Callback;
   /** 
      Pointer to callback function handling incoming Q931 messages 
   */
   ChannelCallback      h245Callback;
   /** 
      Pointer to callback function handling user commands. Supported 
      in linux version only. 
   */
   CommandCallback      hCommandCallback;
   /* Pointer to the trace file */
   FILE *               fptraceFile;
   /** Range of port numbers to be used for TCP connections */
   struct ooH323Ports tcpPorts;
   /** Range of port numbers to be used for UDP connections */
   struct ooH323Ports udpPorts;
   /** Range of port numbers to be used for RTP connections */
   struct ooH323Ports rtpPorts;
   /** 
      Pointer to Q931 outgoing message being built 
   */
   Q931Message *        outgoing;
   /** 
      Pointer to H245 outgoing message being built 
   */
   H245Message *        outgoingH245;
   /** 
      Outgoing H225/Q931 message queue 
   */
   DList                outH225Queue;
   /**
      ASN 1 context used to allocate memory for outH225Queue
   */
   OOCTXT               outH225ListCtxt;
   /** 
      Outgoing H245 message queue 
   */
   DList                outH245Queue;
   /**
      ASN 1 context used to allocate memory for outH245Queue
   */
   OOCTXT               outH245ListCtxt;
   /**
      Master-Slave state
   */   
   int                  ooMasterSlaveState;
   int                  totalOpenLogicalChannels;
   /* Modified by karl on 2005-01-19 Below */
   //The last negotiatory capability      
   H245EndPointCapability  *endCapability;
   /* Modified by karl on 2005-01-19 Above */
};

#endif

