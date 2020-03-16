/**********************************************************************
*
* vdping.h
*
* shared header for ctxping (server application) and vdping (client plugin).
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

#ifndef __VDPING_H__
#define __VDPING_H__

#include "ica.h"
#include "ica-c2h.h"        /* Required for VD_C2H structure */

/*
 * CTXPING is the seven character virtual channel name that is used for the Ping plugin. The same
 * name must be used in the client plugin and on the server; this name is used to match the server
 * code to the client plugin. 
 */
#define CTXPING_VIRTUAL_CHANNEL_NAME  "CTXPING"
#define VC_TIMEOUT_MILLISECONDS     10000L
#define VC_PING_SIGNATURE           0x4950

/*
 * Lowest and highest compatable version.  See DriverInfo().
 */
#define CTXPING_VER_LO      1
#define CTXPING_VER_HI      1

/*
 * Enforce packing of ping packet structure. This is always used for server code; on MacOS X
 * builds for Intel processors it guarantees the same structure layout as for the server. 
 */
#pragma pack(1)

/* ping packet structure */

typedef struct _PING {
    USHORT  uSign;              /* signature */
    USHORT  uType;              /* type, BEGIN or END, from server */
    USHORT  uLen;               /* packet length from server */
    USHORT  uCounter;           /* sequencer */
    ULONG   ulServerMS;         /* server millisecond clock */
    ULONG   ulClientMS;         /* client millisecond clock */
} PING, * PPING;
#define PING_TYPE_BEGIN     1
#define PING_TYPE_END       2

/* vdping driver info (client to host) structure */
typedef struct _VDPING_C2H
{
    VD_C2H  Header;
    USHORT  usMaxDataSize;      /* maximum data block size */
    USHORT  usPingCount;        /* number of times to ping */
} VDPING_C2H, * PVDPING_C2H;

#pragma pack()

#endif /* __VDPING_H__ */
