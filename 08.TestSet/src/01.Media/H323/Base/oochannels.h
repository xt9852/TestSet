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
 * @file oochannels.h 
 * This file contains functions to create and use channels. 
 */
#ifndef _OOCHANNELS_H_
#define _OOCHANNELS_H_

#include "h323\H323-MESSAGES.h"
#include "h323\MULTIMEDIA-SYSTEM-CONTROL.h"
#include "ootypes.h"
#include "ooSocket.h"

#define OORECEIVER 1
#define OOTRANSMITTER 2
#define OODUPLEX 3

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
 * @defgroup channels Channel Management
 * @{
 */
/* Structure for holding connection endpoint  information */
struct ooConnectionEP
{
   char ipaddress[20];
   int port;
};

/**
 * This function is invoked to create H2250 channels in either direction.
 *
 * @param context       Pointer to the context for which channel has to
 *                      be created.
 * @param hdlH2250Event Handle to a callback function which will handle the
 *                      events associated with the channel being created.
 * @param connectionEp  Connection endpoint for the channel.
 *                      - For receiver channel, this is local endpoint.
 *                      - For transmitter channel, this is remote endpoint.
 * @param dir           Direction of the channel to be created.
 *                      - OOTRANSMITTER, for transmit channel.
 *                      - OORECEIVER, for receive channel.
 *
 * @return              Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCreateH2250Channel(struct ooAppContext *context, 
                                ChannelCallback hdlH2250Event, 
                                struct ooConnectionEP connectionEp, int dir);

/**
 * This function is invoked to create H245 channels.
 *
 * @param context       Pointer to the context for which channel has to
 *                      be created.
 * @param hdlH245Event  Handle to a callback function which will handle the
 *                      events associated with the channel being created.
 * @param connectionEP  Connection endpoint for the channel.
 *                      - For receiver channel, this is local endpoint.
 *                      - For transmitter channel, this is remote endpoint.
 * @param dir           Direction of the channel to be created.
 *                      - OOTRANSMITTER, for transmit channel.
 *                      - OORECEIVER, for receive chaneel.
 *
 * @return              Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCreateH245Channel(struct ooAppContext *context, 
                               ChannelCallback hdlH245Event, 
                               struct ooConnectionEP *connectionEP, int dir);

//added by tony below
EXTERN int ooRasUDPReceive(struct ooAppContext *context);
//added by tony above

/**
 * This function is invoked to receive a H2250 message. It receives and
 * decodes a H2250 message and passes it to the callback function 
 * registered by the application at the time of channel creation.
 *
 * @param context     Pointer to the application context.
 * 
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooH2250TCPReceive(struct ooAppContext *context);

/**
 * This function is invoked to send a message out on the channel.
 *
 * @param context     Pointer to the context for which message has
 *                    to be sent.
 * @param type        Type of the message to be sent. Type of message
 *                    decide the channel on which it will be sent.
 *                    - OOQ931MSG - Q931 message to be sent.
 *                    - OOH245MSG - H245 message to be sent.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendMsg(struct ooAppContext *context, int type);

/**
 * This function is invoked to receive a H245 message. It receives and 
 * decodes the message and passes it back to the callback function
 * registered by the application at the time of H245 channel creation.
 *
 * @param context     Pointer to the application context.
 * 
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooH245Receive(struct ooAppContext *context);

/**
 * Accepts incoming connection requests for establishing an H225 channel.
 *
 * @param context     Pointer to the application context.
 * 
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooAcceptH225Connection(struct ooAppContext *context);

/**
 * Accepts incoming connection requests for establishing an H245 channel.
 *
 * @param context     Pointer to the application context.
 * 
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooAcceptH245Connection(struct ooAppContext *context);

/**
 * Monitors all the channels currently active and calls appropriate
 * routines to read/write onto the channels and accept incoming 
 * connection requests.
 *
 * @param context     Pointer to the application context.
 * 
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooMonitorChannels(struct ooAppContext *context); 

//added by tony below
EXTERN int ooSendRasMsg(struct ooAppContext *context);
//added by tony above

/**
 * Enqueues the outgoing H225 message onto the outgoing h225 queue
 * from where it will be transmitted when the socket is writeable and all
 * the H225 messages queued before it are already transmitted.
 *
 * @param context     Pointer to the application context.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendH225Msg(struct ooAppContext *context);

/**
 * Enqueues the outgoing H245 message onto the outgoing h245 queue
 * from where it will be transmitted when the socket is writeable and all
 * the H245 messages queued before it are already transmitted.
 *
 * @param context     Pointer to the application context.
 *
 * @return            Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendH245Msg(struct ooAppContext *context);

/**
 * Retrives the h225 channel port currently being used by the active call.
 *
 * @param context    Pointer to application context.
 *
 * @return           Returns the H2250 port number if there is an active call,
 *                   negative value is returned otherwise.
 */
EXTERN int ooGetH225ChannelPort(struct ooAppContext *context);

/**
 * Retrives the h245 channel port currently being used by the active call.
 *
 * @param context    Pointer to application context.
 *
 * @return           Returns the H245 port number if there is an active
 *                   channel, negative value is returned otherwise.
 */
EXTERN int ooGetH245ChannelPort(struct ooAppContext *context);

/**
 * Retrives the h245 receiver port, ie, port being used for listening incoming
 * H245 connection requests.
 *
 * @param context    Pointer to application context.
 *
 * @return           Returns the H245 port number.
 */
EXTERN int ooGetH245ReceiverPort(struct ooAppContext *context);

/**
 * Retrives the local rtcp port, used for receiving incoming rtcp packets.
 *
 * @param context    Pointer to application context.
 *
 * @return           Returns the RTCP port number, negative value is 
 *                   returned otherwise.
 */
EXTERN int ooGetLocalRtcpPort(struct ooAppContext *context);

/**
 * Retrives the local rtp port, used for receiving incoming rtp packets.
 *
 * @param context    Pointer to application context.
 *
 * @return           Returns the RTP port number, negative value is 
 *                   returned otherwise.
 */
EXTERN int ooGetLocalRtpPort(struct ooAppContext *context);

/**
 * Retrives the remote rtp port, on which the remote endpoint is listening for
 * rtp packets.
 *
 * @param context    Pointer to application context.
 *
 * @return           Returns the RTP port number, negative value is 
 *                   returned otherwise.
 */
EXTERN int ooGetRemoteRtpPort(struct ooAppContext *context);


/**
 * This is called after an H225/H245 message is sent. Any housekeeping to be 
 * done after sending a message can be done here. Currently implements 
 * procedures for EndSession and ReleaseComplete.
 *
 * @param context    Pointer to application context.
 * @param msgType    Type of the message sent.
 *
 * @return           Returns the RTP port number, negative value is 
 *                   returned otherwise.
 */
EXTERN int ooOnSendMsg(struct ooAppContext *context, int msgType);

//added by tony below 2004.12.16
EXTERN int ooOnSendMsgFail(struct ooAppContext *context,int msgType);
//added by tony above 2004.12.16

/**
 * This is called after the call is ended by sending/receiving EndSession 
 * command.
 * It closes RTP and H245 channels setup for the call.
 *
 * @param context    Pointer to application context.
 *
 * @return           Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCloseH245Channels(struct ooAppContext *context);

/**
 * This is called after the call is ended by sending/receiving ReleaseComplete
 * message. It closes open H225 channels.
 *
 * @param context    Pointer to application context.
 *
 * @return           Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCloseH225Channel(struct ooAppContext *context);

/** 
 * @} 
 */
//added by tony below 2004.12.13
EXTERN int ooCloseRasChannel(struct ooAppContext *context);
//added by tony above 2004.12.13

#ifdef __cplusplus
}
#endif
#endif

