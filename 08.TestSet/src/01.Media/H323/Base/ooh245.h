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
 * @file ooh245.h 
 * This file contains functions to support H245 negotiations. 
 */
#ifndef _OOH245HDR_H_
#define _OOH245HDR_H_

#include "ooasn1.h"
#include "ootypes.h"
#include "oochannels.h"
#include "oo.h"
#include "oosndrtp.h"
#include "ooq931.h"
#include "h323\MULTIMEDIA-SYSTEM-CONTROL.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXTERN
#ifdef _WIN32
#define EXTERN __declspec(dllexport)
#else
#define EXTERN
#endif /* _WIN32 */
#endif /* EXTERN */

/** 
 * @defgroup h245 H245 Message Handling
 * @{
 */
/**
 * Creates an outgoing H245 message of the type specified by the type
 * argument for the Application context. 
 *
 * @param context   Pointer to application context.
 * @param type      Type of the message to be created.
 *                  (Request/Response/Command/Indication)
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooCreateH245Message(struct ooAppContext *context, int type);


/**
 * Frees up the memory used by the H245 message.
 *
 * @param context   Pointer to application context.
 * @param pmsg      Pointer to an H245 message structure.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooFreeH245Message(struct ooAppContext *context, 
                             H245Message *pmsg);
/*Added by Karl on 2004-11-16 below */
/**
 * Creates TerminalCapability set messages with g729AnnexA transmit/receive
 * capabilities.
 *
 * @param context   Pointer to application context.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooSendG729ACallTermCapMsg(struct ooAppContext *context);
/*Added by Karl on 2004-11-16 above */

/*Added by Karl on 2005-01-17 below */
/**
 * Creates TerminalCapability set messages with g729AnnexA transmit/receive
 * capabilities.
 *
 * @param context   Pointer to application context.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooSendIntegrationCallTermCapMsg(struct ooAppContext *context);
/*Added by Karl on 2005-01-17 above */
/**
 * Creates TerminalCapability set messages with g711ulaw64k transmit/receive
 * capabilities.
 *
 * @param context   Pointer to application context.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooSendG711CallTermCapMsg(struct ooAppContext *context);
/*Added by Karl on 2005-01-14 below */
/**
 * Creates TerminalCapability set messages with g728 transmit/receive
 * capabilities.
 *
 * @param context   Pointer to application context.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooSendG728CallTermCapMsg(struct ooAppContext *context);
/**
 * Creates TerminalCapability set messages with g7231 transmit/receive
 * capabilities.
 *
 * @param context   Pointer to application context.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooSendG7231CallTermCapMsg(struct ooAppContext *context);
/*Added by Karl on 2005-01-14 above */
/*Added by Karl on 2004-11-26 below */
/**
 * Creates TerminalCapability set messages with g721 transmit/receive
 * capabilities.
 *
 * @param context   Pointer to application context.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooSendG721CallTermCapMsg(struct ooAppContext *context);
/*Added by Karl on 2004-11-26 above */
/**
 * Sends a TerminalCapability set message with G711 transmit
 * capability.
 *
 * @param context   Pointer to application context.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooSendG711TransmitTermCapMsg(struct ooAppContext *context);

/**
 * Adds MasterSlave Determination request to an outgoing H245 message
 *
 * @param context     Pointer to application context.
 * @param masterSlave MasterSlave determination request structure.
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooAddMasterSlaveDetermination(struct ooAppContext *context,
                                  H245MasterSlaveDetermination masterSlave);

/**
 * Retrieves the outgoing H245 message from the outgoing h245 queue and
 * encodes it and returns the encoded data in the msgBuf supplied as an 
 * argument.
 *
 * @param context     Pointer to application context.
 * @param msgbuf      Pointer to a buffer in which encoded message data will
 *                    be returned.
 * @param len         Pointer to an int containing the length of the buffer
 *                    passed, on return it contains the length of the encoded
 *                    data.
 * @param msgType     Pointer to an int which on returns contains the message 
 *                    type of the encoded message.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooGetOutgoingH245Msgbuf(struct ooAppContext *context,
                                   ASN1OCTET *msgbuf, int *len, int *msgType);

/**
 * Sends master-slave determination request.
 * 
 * @param context     Pointer to application context.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooSendMasterSlaveDetermination(struct ooAppContext *context);

/**
 * Sends master-slave determination ack.
 * 
 * @param context     Pointer to application context.
 * @param status      Character string indicating the (master/slave) status of
 *                    the remote endpoint
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooSendMasterSlaveDeterminationAck(struct ooAppContext *context,
                                             char * status);

/**
 * Handles incoming open logical channel request and send an ack for 
 * the same.
 * 
 * @param context     Pointer to application context.
 * @param olc         Pointer to an OpenLogicalChannel request.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooHandleOpenLogicalChannel(struct ooAppContext *context, 
                                      H245OpenLogicalChannel *olc);

/**
 * Handles incoming H245 commands. Currently only EndSession command is
 * supported.
 * 
 * @param context     Pointer to application context.
 * @param command     Pointer to the command message.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooHandleH245Command(struct ooAppContext *context, 
                               H245CommandMessage *command);

/**
 * Sends an EndSession command. 
 * 
 * @param context     Pointer to application context.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooSendEndSessionCommand(struct ooAppContext *context);

/**
 * Generates a random number for status determination purpose. 
 *
 * @return            Returns the randomly generated status determination
 *                    number.
 */
EXTERN ASN1UINT ooGenerateStatusDeterminationNumber();

/*Added by Karl on 2004-11-16 below */
/**
 * Sends Open Logical Channel request for g729AnnexA audio channel.
 *  
 * @param context     Pointer to application context.
 * 
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooOpeng729AnnexALogicalChannel(struct ooAppContext *context);
/*Added by Karl on 2004-11-16 above */

/**
 * Sends Open Logical Channel request for g711ulaw audio channel.
 *  
 * @param context     Pointer to application context.
 * 
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooOpeng711ulawLogicalChannel(struct ooAppContext *context);

/*Added by Karl on 2005-01-14 below */
/**
 * Sends Open Logical Channel request for g7231 audio channel.
 *  
 * @param context     Pointer to application context.
 * 
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooOpeng7231LogicalChannel(struct ooAppContext *context);
/**
 * Sends Open Logical Channel request for g728 audio channel.
 *  
 * @param context     Pointer to application context.
 * 
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooOpeng728LogicalChannel(struct ooAppContext *context);
/*Added by Karl on 2005-01-14 above */

/*Added by Karl on 2004-11-26 below */
/**
 * Sends Open Logical Channel request for g721 audio channel.
 *  
 * @param context     Pointer to application context.
 * 
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooOpeng721LogicalChannel(struct ooAppContext *context);
/*Added by Karl on 2004-11-26 above */

/**

/**
 * Handles incoming MasterSlave determination requests and Acks. In case of 
 * Request it generates status determination number and sends Ack accordingly.
 * In case of incoming Ack, it responds back with Ack, if the incoming Ack is
 * for determination request initiated by the endpoint.
 *  
 * @param context     Pointer to application context.
 * @param pmsg        Pointer to incoming MasterSlave Request/Response message.
 * @param msgType     Type of the message being passed to it.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooHandleMasterSlave(struct ooAppContext *context, void * pmsg, 
                               int msgType);

/**
 * This function is invoked when OpenLogicalChannel Ack is received. It 
 * extracts media channel and media control channel addresses from the message
 * and starts media channel.
 *  
 * @param context     Pointer to application context.
 * @param olcAck      Pointer to OpenLogicalChannel Ack message.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooOnReceivedOpenLogicalChannelAck(struct ooAppContext *context,
                                        H245OpenLogicalChannelAck *olcAck);

/**
 * This function is invoked to send a TerminalCapabilitySet Ack message
 * acknowledging the received TerminalCapabilitySet message.
 *  
 * @param context     Pointer to application context.
 * @param seqNo       Sequence number of the TerminalCapabiltySet message being
 *                    acknowledged.
 *
 * @return            Completion status of operation: 0 (OO_OK) = success,
 *                    negative return value is error.         
 */
EXTERN int ooH245AcknowledgeTerminalCapabilitySet(struct ooAppContext 
                                                  *context, 
                                                  H245SequenceNumber seqNo);
/** 
 * @} 
 */
#ifdef __cplusplus
}
#endif

#endif
