/**********************************************************************
*
* ctxover.h
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
* $Id: //icaclient/release/ica1000/src/examples/vc/server/ctxover/ctxover.h#1 $
*
* Copyright 1998-2004, 2009 Citrix Systems, Inc.  All Rights Reserved.
*
**********************************************************************/

#ifndef _CTXOVER_H
#define _CTXOVER_H


/*
 * General application definitions.
 */
#define SUCCESS 0
#define FAILURE 1
#define TIME_OUT 2000L

#define MAX_IDS_LEN     256   // maximum length that the input parm can be
#define MAXNAME         18    // Max allowed for printing.
#define NO_MORE_DATA    80   // Value at which server stops sending data to client

/*
 * Resource string IDs
 */
#define IDS_ERROR_MALLOC                                100
#define IDS_ERROR_INVALID_PARAMETERS                    101
#define IDS_ERROR_OPEN_FAILED                           104
#define IDS_ERROR_WRITE_FAILED                          105
#define IDS_ERROR_READ_FAILED                           106
#define IDS_ERROR_WRITE_SHORT                           107
#define IDS_ERROR_READ_SHORT                            108
#define IDS_ERROR_CLIENT_PACKET_INVALID                 109
#define IDS_ERROR_CTXOVER_FAIL                          110
#define IDS_ERROR_QUERY_FAIL                            111
#define IDS_ERROR_QUERY_SESSION_FAIL                    112
#define IDS_ERROR_NEEDS_SESSION                         113
#define IDS_ERROR_PROTOCOL                              114
#define IDS_OPENED_CHANNEL                              120
#define IDS_BEGIN_PACKET                                121
#define IDS_END_PACKET                                  122
#define IDS_SENDOVER_SUCCESS                            123
#define IDS_INFO_SENT                                   124
#define IDS_INFO_RCVD                                   125
#define IDS_DATA_SENT                                   126
#define IDS_DATA_RCVD                                   127
#define IDS_QUERY                                       128
#define IDS_QUERY_C2H1                                  129
#define IDS_QUERY_C2H2                                  130
#define IDS_QUERY_C2H3                                  131
#define IDS_QUERY_C2H4                                  132
#define IDS_QUERY_C2H5                                  133
#define IDS_QUERY_C2H6                                  134
#define IDS_QUERY_C2H7                                  135 
#define IDS_QUERY_C2H8                                  136
#define IDS_QUERY_C2H9                                  137
#define IDS_QUERY_C2H10                                 138
#define IDS_SEND_FAILED                                 139
#define IDS_WAIT_THREAD_RETURN                          140


/*
 *   Structures used.
 */
       
typedef struct _THREADRCV {
    HANDLE   hVC;                /* Handle to the Virtual Channel*/
    DWORD    ErrCode;            /* Error Code. Used as return value */
    BOOLEAN  fKill;              /* Flag for the thread to exit */
} THREADRCV, * PTHREADRCV;

/*
 *  Local function prototypes
 */
VOID
ReceiveThread(PTHREADRCV pThrdBlk);

BOOLEAN ServerWrite(HANDLE hVC, 
                   POVER pBufSend);


VOID WINAPI PrintMessage( int nResourceID, ...);


#endif /* _CTXOVER_H */
