/**********************************************************************
*
* ctxmix.h
*
* Citrix hereby permits you to use, reproduce, modify, display, compile,
* sublicense, and distribute all or any portion of the sample code contained
* in this file, provided that you remove this Copyright attribution from any
* modified version of this file.
*
* THIS SAMPLE CODE IS PROVIDED BY CITRIX "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
*
* $Id: //icaclient/release/ica1000/src/examples/vc/server/ctxmix/ctxmix.h#1 $
*
* Copyright 1999-2004, 2009 Citrix Systems, Inc.  All Rights Reserved.
*
**********************************************************************/

#ifndef _CTXMIX_H
#define _CTXMIX_H


/*
 * General application definitions.
 */
#define SUCCESS 0
#define FAILURE 1

#define MAX_IDS_LEN   256   // maximum length that the input parm can be

/*
 * Resource string IDs
 */
#define IDS_ERROR_MALLOC                                100
#define IDS_ERROR_OPEN_FAILED                           101
#define IDS_ERROR_WRITE_FAILED                          102
#define IDS_ERROR_READ_FAILED                           103
#define IDS_ERROR_WRITE_SHORT                           104
#define IDS_ERROR_READ_SHORT                            105
#define IDS_ERROR_CTXMIX_FAIL                           106
#define IDS_ERROR_NEEDS_SESSION                         107
#define IDS_ERROR_QUERY_SESSION_FAIL                    108
#define IDS_OPENED_CHANNEL                              109



/*
 *  Local function prototypes
 */

VOID WINAPI PrintMessage( int nResourceID, ...);

DWORD 
Srv_AddNo(LPBYTE pSend, LPBYTE pRecv,USHORT dwArg1, USHORT dwArg2);

BOOLEAN 
Srv_DispStr(LPBYTE pSend,PUCHAR pStr);

VOID 
Srv_Time(LPBYTE pSend, LPBYTE pRecv);

BOOLEAN
SendCommand (LPBYTE pSend,LPBYTE pRecv);

#endif /* _CTXMIX_H */
