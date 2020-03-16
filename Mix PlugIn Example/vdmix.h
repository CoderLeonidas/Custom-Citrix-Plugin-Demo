/**********************************************************************
*
* vdmix.h
*
* shared header for ctxmix (server application) and vdmix (client plugin).
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

#ifndef __VDMIX_H__
#define __VDMIX_H__

#include "ica.h"
#include "ica-c2h.h"        /* Required for VD_C2H structure */

/*
 * CTXMIX is the seven character virtual channel name that is used for the Mix plugin. The same
 * name must be used in the client plugin and on the server; this name is used to match the server
 * code to the client plugin. 
 */
#define CTXMIX_VIRTUAL_CHANNEL_NAME "Mix"
#define VC_TIMEOUT_MILLISECONDS  10000L
#define MAX_DATA                 2040
#define TEMP_SIZE                512

/*
 *  Enumeration of the functions that are implemented
 */
enum FUNCTIONS {ADD, DISP, TIME };

/*
 * Lowest and highest compatable version.  See DriverInfo().
 */
#define CTXMIX_VER_LO 1
#define CTXMIX_VER_HI 1

/*
 * Enforce packing of mix packet structure. This is always used for server code; on MacOS X
 * builds for Intel processors it guarantees the same structure layout as for the server. 
 */
#pragma pack(1)

/*
 * Mix data header structure
 */
typedef struct _MIXHEAD {
    USHORT      uType;              /* packet type */
    USHORT      uFunc;              /* Index of Function */
    ULONG       uLen;               /* Length of data */
    USHORT      fRetReq;            /* True if return value required */
    USHORT      dwLen1;             /* length of data for pointer arg #1 */
    USHORT   	dwLen2;             /* length of data for pointer arg #2  */
    ULONG       dwRetVal;           /* Return Value from client */
	
// uFunct == ADD:		The server will send the following two items. No data is
//						added to the header in a reply. 
//	USHORT		num1;				/* First number to be added */
//	USHORT		num2;				/* Second number to be added */

// case uFunc == DISP:	The server will add an array of [dwLen1] characters. The
//						client shouldn't actually reply to the server, but no data
//						will be added anyway
//	CHAR		str [dwLen1];		/* Array of characters, not zero terminated */

// case uFunc == TIME:	The server will not add any data to the header. However, 
//						a struct VDTM will be added in the reply.
//	VDTM		datetime;
}  MIXHEAD, *PMIXHEAD;

/*
 * Vdmix driver info (client to host) structure
 */

typedef struct _VDMIX_C2H
{
    VD_C2H  Header;
    USHORT  usMaxDataSize;      // maximum data block size
} VDMIX_C2H, *PVDMIX_C2H;

/*
 *   This structure is added for compatability with WIN16
 */
typedef struct _vdtm {
      ULONG tm_sec;     /* seconds after the minute - [0,59] */
      ULONG tm_min;     /* minutes after the hour - [0,59] */
      ULONG tm_hour;    /* hours since midnight - [0,23] */
      ULONG tm_mday;    /* day of the month - [1,31] */
      ULONG tm_mon;     /* months since January - [0,11] */
      ULONG tm_year;    /* years since 1900 */
      ULONG tm_wday;    /* days since Sunday - [0,6] */
      ULONG tm_yday;    /* days since January 1 - [0,365] */
     ULONG tm_isdst;    /* daylight savings time flag */
} VDTM, *PVDTM;


#pragma pack()

#endif /* __VDMIX_H__ */
