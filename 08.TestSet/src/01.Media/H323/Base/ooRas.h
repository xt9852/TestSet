/*
 * Copyright (C) 2004 by Giant Electronic, Inc.
 * ****************************************************************************/

/**
 * @file ooRas.h 
 * This file contains functions to support Ras negotiations. 
 */
#ifndef _OORASHDR_H_
#define _OORASHDR_H_

#include "ooasn1.h"
#include "h323\H323-MESSAGES.h"
#include "ootypes.h"
#include "oo.h"
/*#include "oochannels.h"

#include "oosndrtp.h"
#include "ooq931.h"
#include "MULTIMEDIA-SYSTEM-CONTROL.h"*/

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

/* Structure for holding RAS setup information*/
/*typedef struct{
   OOSOCKET sock;	//RAS channel
   char GkIp[20];	//Gatekeeper ip
   unsigned short seqNo; // last SeqNo recv or xmitted
}OORasInfo*/;
/**
 * Creates an outgoing Ras message of the type specified by the type
 * argument for the Application context. 
 *
 * @param context   Pointer to application context.
 * @param type      Type of the message to be created.
 *                  (Request/Response/Command/Indication)
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooCreateRasMessage(struct ooAppContext *context, int type);

/**
 * Frees up the memory used by the Ras message.
 *
 * @param context   Pointer to application context.
 * @param pmsg      Pointer to an H245 message structure.
 *
 * @return          Completion status of operation: 0 (OO_OK) = success,
 *                  negative return value is error.         
 */
EXTERN int ooFreeRasMessage(struct ooAppContext *context, RasMessage *pmsg);


EXTERN int ooGetOutgoingRasMsgbuf(struct ooAppContext *context,ASN1OCTET *msgbuf, int *len,int *msgType);
/************************************************************************/
/* Send registration request RAS message
	@param context Pointer to application context.
/************************************************************************/
//EXTERN int ooSendRegistrationRequestMsg(struct ooAppContext *context);


#ifdef __cplusplus
}
#endif

#endif
