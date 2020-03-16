/**********************************************************************
*
* vdover.h
*
* shared header for ctxover (server application) and vdover (client plugin).
*
* Copyright 1998-2003, 2009 Citrix Systems, Inc. All Rights Reserved.
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
**********************************************************************/

#ifndef __VDOVER_H__
#define __VDOVER_H__

#include "ica.h"
#include "ica-c2h.h"        /* Required for VD_C2H structure */

/*
 * CTXOVER is the seven character virtual channel name that is used for the Over plugin. The same
 * name must be used in the client plugin and on the server; this name is used to match the server
 * code to the client plugin. 
 */
#define CTXOVER_VIRTUAL_CHANNEL_NAME  "CTXOVER"
#define VC_TIMEOUT_MILLISECONDS         10000L
#define VC_OVER_SIGNATURE               0x4920

/*
 * Lowest and highest compatable version.  See DriverInfo().
 */
#define CTXOVER_VER_LO      1
#define CTXOVER_VER_HI      1

#define INT_CNT             5

/*
 * Enforce packing of over packet structure. This is always used for server code; on MacOS X
 * builds for Intel processors it guarantees the same structure layout as for the server. 
 */
#pragma pack(1)


/* Valid uType fields*/

#define OVER_TYPE_BEGIN     1
#define OVER_TYPE_END       2
#define OVERFLOW_JUMP       3


/* OverFlow packet structure */

typedef struct _OVER {
    USHORT  uSign;              /* signature */
    USHORT  uType;              /* type, BEGIN or END, from server */
    USHORT  uLen;               /* packet length from server */
    USHORT  uCounter;           /* sequencer */
    ULONG   ulServerMS;         /* server millisecond clock */
} OVER, * POVER;

typedef struct _DRVRESP {
    USHORT  uType;              /* type OVERFLOW_JUMP from client */
    USHORT  uLen;               /* packet length from client */
    USHORT  uCounter;           /* sequencer */
} DRVRESP, * PDRVRESP;

/* vdover driver info (client to host) structure */
typedef struct _VDOVER_C2H
{
    VD_C2H  Header;
    USHORT  usMaxDataSize;      /* maximum data block size */
} VDOVER_C2H, * PVDOVER_C2H;

#pragma pack()

#endif /* __VDOVER_H__ */
