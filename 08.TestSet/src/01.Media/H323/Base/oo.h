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
 * @file oo.h 
 * This file defines the functions for initializing and closing stack contexts
 */


#ifndef _OO_H_
#define _OO_H_
#include "ootypes.h"

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
 * This function is the first function to be invoked before using stack. It
 * initializes the stack context for an application.
 *
 * @param context    Pointer to a pointer variable of type ooAppContext
 *                   which will have address of the newly created stack 
 *                   context on return.
 * @param tracefile  Absolute path to the trace file to be used for 
 *                   storing traces
 * @param myCallback Callback function to handle user input. Used only in 
 *                   linux version.
 *
 * @return          - OO_OK on success
 *                  - OO_FAILED on failure
 */
EXTERN int ooInitialize(struct ooAppContext **context, const char * tracefile,
                        CommandCallback myCallback);


/**
 * This function is the last function to be invoked after done using the 
 * stack. It closes the stack context for an application, releasing all 
 * the associated memory.
 *
 * @param context   Pointer to the ooAppContext which has to be freed.
 *
 * @return          - OO_OK on success
 *                  - OO_FAILED on failure
 */
EXTERN int ooCloseContext(struct ooAppContext *context);

/**
 * This function is used to write the messages to the trace file.
 *
 * @param context   Pointer to the ooContext to which the message 
 *                  belongs.
 * @param fmtspec   Printf style format spec.
 * @param ...       Printf style variable list of arguments              
 *
 * @return          - none
 */
EXTERN void ooTrace(struct ooAppContext *context, const char * fmtspec, 
                      ...);

#ifdef __cplusplus
}
#endif
#endif
