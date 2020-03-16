/*************************************************************************
*
* VDMIX.C
*
* Virtual Driver Example - Mix
*
* Copyright 1998-2004, 2009 Citrix Systems, Inc. All Rights Reserved.
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
*************************************************************************/

/*
 * Note: In this source file, everything that is specific to the Mix Sample PlugIn is marked 
 * with a comment containing the word MixSamplePlugIn. Everything else would be generic to
 * all plugins. 
 */
 
/*
 * Include system-specific header files. No system-specific header files are included in the 
 * MacOS X version; the XCode prefixheader feature is used instead.
 */
#ifdef DOS32
#define CITRIX 1
#include <sys/types.h>
#include "wfc32.h"
#endif

#if ! defined (macintosh) && ! defined (unix)
#include <windows.h>         /* for far etc. */
#endif

/* Include Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Include Citrix header files */
#include "citrix.h"
#include "clib.h"

/* from src/inc */
#include "icaconst.h"
#include "clterr.h"
#include "wdapi.h"
#include "vdapi.h"
#include "vd.h"
#include "ctxdebug.h"
#include "logapi.h"
#include "miapi.h"

#include "cwire.h"
#include "cmacro.h"

/* MixSamplePlugIn: Include header files that are specific to this PlugIn */
#include "vdmix.h"
#include "mixwire.h"
/* MixSamplePlugIn end */

#ifdef unix
/* Make sure that we pull in Load from vdapi.a. This is only needed for unix versions, 
 * not for MacOS X or Windows. */
extern int Load();

struct _wrapload {
        int ((*fn)());
} WRAP_LOAD[] = {
        {Load}
};
#endif	/* unix */

LOG_EXTERN_INIT;

/*=============================================================================
==   Functions Defined
=============================================================================*/

/*
 *	These are the required driver functions (exported). They will be called by functions in the
 *	libVCSDK.a library. 
 */
int DriverOpen( PVD, PVDOPEN, PUINT16 );
int DriverClose( PVD, PDLLCLOSE, PUINT16 );
int DriverInfo( PVD, PDLLINFO, PUINT16 );
int DriverPoll( PVD, PDLLPOLL, PUINT16 );
int DriverQueryInformation( PVD, PVDQUERYINFORMATION, PUINT16 );
int DriverSetInformation( PVD, PVDSETINFORMATION, PUINT16 );
int DriverGetLastError( PVD, PVDLASTERROR );

/*
 * This function will be passed to the client engine in the DriverOpen function. 
 */
static void WFCAPI ICADataArrival( PVOID, USHORT, LPBYTE, USHORT );


/*=============================================================================
==   Data
=============================================================================*/


/*
 *  These pointers and function pointers are given to the plugin in the DriverOpen function.
 *  They are needed for communication between PlugIn and the server. 
 */

static PVOID pWd = NULL;
static POUTBUFRESERVEPROC  pOutBufReserve  = NULL;
static POUTBUFAPPENDPROC   pOutBufAppend   = NULL;
static POUTBUFWRITEPROC    pOutBufWrite    = NULL;
static PAPPENDVDHEADERPROC pAppendVdHeader = NULL;

/*
 * Maximum data write size and virtual channel number are needed for communication between
 * plugin and server. 
 */
static USHORT gusMaxDataSize;             /* Maximum Data Write Size */
static USHORT gusVirtualChannelNum;       /* Channel number assigned by WD */

/* MixSamplePlugIn: Variables used by the Mix PlugIn */
static IBOOL        fBufferEmpty = TRUE;          /* True if the data buffer is empty */
static PMIXHEAD    pMixHd = NULL ;               /* pointer to mix data buffer */
static LPBYTE      pTemp = NULL;                 /* Pointer for temporary buffer */

/* A struct extending the MIXHEAD structure; it will be big enough to allocate anything
 * that is sent by the server. */
typedef struct
{
	MIXHEAD header;				/* MIXHEAD common to anything the server sends */
	char bytes [TEMP_SIZE];		/* Largest possible item: TEMP_SIZE bytes to print */
} MIXHEAD_PLUS;

/* Functions used in this code: */
static void AddNo (LPBYTE pBufIp);
static void DispStr (LPBYTE pBufIp);
static void LocTime (PMIXHEAD pHeader);
/* MixSamplePlugIn end */


/*******************************************************************************
 *
 *  DriverOpen
 *
 *    Called once to set up things.
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to virtual driver data structure
 *    pVdOpen (input/output)
 *       pointer to the structure VDOPEN
 *    puiSize (Output)
 *       size of VDOPEN structure.
 *
 * EXIT:
 *    CLIENT_STATUS_SUCCESS - no error
 *    CLIENT_ERROR_NO_MEMORY - could not allocate data buffer
 *    On other errors, an error code is returned from lower level functions.
 *
 ******************************************************************************/

int
DriverOpen( PVD pVd, PVDOPEN pVdOpen, PUINT16 puiSize )
{
    WDSETINFORMATION   wdsi;
    VDWRITEHOOK        vdwh;
    WDQUERYINFORMATION wdqi;
    OPENVIRTUALCHANNEL OpenVirtualChannel;
    int                rc;
    UINT16             uiSize;

    TRACE( TC_VD, TT_API1, "VDMIX: DriverOpen entered" );

	/* MixSamplePlugIn begin */
    fBufferEmpty = TRUE;
	/* MixSamplePlugIn end */

    *puiSize = sizeof(VDOPEN);

    /*
     * Get a virtual channel. MixSamplePlugIn: The only part specific to this plugin is
	 * storing the correct name for this plugin. 
     */
    wdqi.WdInformationClass = WdOpenVirtualChannel;
    wdqi.pWdInformation = &OpenVirtualChannel;
    wdqi.WdInformationLength = sizeof(OPENVIRTUALCHANNEL);
    OpenVirtualChannel.pVCName = CTXMIX_VIRTUAL_CHANNEL_NAME;

    /* uiSize will be set  when we return back from VdCallWd. */
    uiSize = sizeof( WDQUERYINFORMATION);

    rc = VdCallWd( pVd, WDxQUERYINFORMATION, &wdqi, &uiSize  );
    TRACE( TC_VD, TT_API1, "VDMIX: opening channel %s",
            OpenVirtualChannel.pVCName );

    if ( rc != CLIENT_STATUS_SUCCESS ) {
        TRACE( TC_VD, TT_ERROR, "VDMIX: Could not open %s. rc=%d.",
                OpenVirtualChannel.pVCName, rc);
        return( rc );
    }

    gusVirtualChannelNum = OpenVirtualChannel.Channel;

    /*
     *  Used by the engine
     */
    pVdOpen->ChannelMask = (1L << gusVirtualChannelNum);
    pVd->pPrivate   = NULL; /* pointer to private data, if needed */

    /*
     *  Register write hooks for our virtual channel
     */
    vdwh.Type  = gusVirtualChannelNum;
    vdwh.pVdData = pVd;
    vdwh.pProc = (PVDWRITEPROCEDURE) ICADataArrival;
    wdsi.WdInformationClass  = WdVirtualWriteHook;
    wdsi.pWdInformation      = &vdwh;
    wdsi.WdInformationLength = sizeof(VDWRITEHOOK);
    uiSize                   = sizeof( WDSETINFORMATION);

    rc = VdCallWd( pVd, WDxSETINFORMATION, &wdsi, &uiSize  );
    TRACE( TC_VD, TT_API2, "VDMIX: writehook channel number=%u"
            " vdwh.pVdData=%x rc=%d", vdwh.Type, vdwh.pVdData, rc );

    if ( rc != CLIENT_STATUS_SUCCESS ) {
        TRACE( TC_VD, TT_ERROR, "VDMIX: Could not register write hook. rc %d",
                rc);
        return( rc );
    }

    /*
     *  Grab pointers to functions to use to send data to the host
     */
    pWd            = vdwh.pWdData;
    pOutBufReserve = vdwh.pOutBufReserveProc;
    pOutBufAppend  = vdwh.pOutBufAppendProc;
    pOutBufWrite   = vdwh.pOutBufWriteProc;
    pAppendVdHeader= vdwh.pAppendVdHeaderProc;

    TRACE( TC_VD, TT_API1, "VDMIX: Registered");

    /*
     *  MixSamplePlugIn: ALL MEMORY MUST BE ALLOCATED DURING INITIALIZATION.
     *  Allocate a single buffer to respond to the mix request.
     *  This example shows use of the MaximumWriteSize returned via
     *  the previous call.
     *  Subtract one because the first byte is used internally by the
     *  WD for the channel number.  We are given a pointer to the
     *  second byte.
     */
    gusMaxDataSize = vdwh.MaximumWriteSize - 1;
	if (gusMaxDataSize > sizeof (MIXHEAD_PLUS))
		gusMaxDataSize = sizeof (MIXHEAD_PLUS);

    /*
     *  This is the main buffer which is going to be exchanged
     *  between the client and the server. We allocate memory
     *  for the largest item that we might want to send.
     */
    if ( (pMixHd = (PMIXHEAD) malloc (sizeof (MIXHEAD_PLUS))) == NULL ) {
        return( CLIENT_ERROR_NO_MEMORY );
    }

    /*
     *  This is a buffer to write the temporary display string
     * in the DispStr function to the Log file
     */
    if ( (pTemp = (LPBYTE)malloc(TEMP_SIZE)) == NULL ) {
        return( CLIENT_ERROR_NO_MEMORY );
    }
	/* MixSamplePlugIn end */

    return( CLIENT_STATUS_SUCCESS );
}


/*******************************************************************************
 *
 *  ICADataArrival
 *
 *   A data PDU arrived over our channel.
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to virtual driver data structure
 *
 *    uChan (input)
 *       ICA channel the data is for.
 *
 *    pBuf (input)
 *       Buffer with arriving data packet
 *
 *    Length (input)
 *       Length of the data packet
 *
 * EXIT:
 *       void
 *
 ******************************************************************************/

static void WFCAPI ICADataArrival( PVOID pVd, USHORT uChan, LPBYTE pBuf, USHORT Length)
{
	UNREFERENCED_PARAMETER (pVd);
	UNREFERENCED_PARAMETER (uChan);
	UNREFERENCED_PARAMETER (Length);
	
	USHORT uLen;
	
	/* MixSamplePlugIn: These two macros make pPacket a pointer to a struct MIX, doing all
	 * necessary conversions on non-Intel architectures. The struct name MIX is specific to this
	 * plugin. */
    WIRE_PTR(MIXHEAD_PLUS, pPacket);
    WIRE_READ(MIXHEAD_PLUS, pPacket, pBuf);
	/* MixSamplePlugIn end */

    uLen = pPacket->header.uLen;
    TRACE( TC_VD, TT_API3,
        "VDMIX: IcaDataArrival, Len=%d, uLen=%d, pData=[%x][%x][%x][%x]",
        Length, uLen, ((LPBYTE)pPacket)[0], ((LPBYTE)pPacket)[1], ((LPBYTE)pPacket)[2], ((LPBYTE)pPacket)[3] );
    TRACEBUF( TC_VD, TT_API3, pPacket, Length);

    /*
     *  MixSamplePlugIn: fBufferEmpty indicates that Mix's data buffer is empty, that is it 
	 *	doesn't have any data to send to the server. If fBufferEmpty is FALSE then the server 
	 *	should be waiting for a response to this plugin and not sending another request, so we
	 *	ignore this message. 
     */
    if ( !fBufferEmpty ) {
        TRACE( TC_VD, TT_ERROR,
            "VDMIX: ICADataArrival - Error: not all data was sent" );
        return;
    }
	/* MixSamplePlugIn end */

    /*
     *  MixSamplePlugIn: Fill in response: We want to echo back everything that server sent us, up
	 *	to a point. Store the number of bytes that we remember in uLen. Copy all the data from the
	 *	server to the pointer pMixHd, then overwrite the length with the correct value, and store
	 *	the client time in milliseconds. Now the buffer is not empty anymore
     */
    if (uLen > gusMaxDataSize)
        uLen = gusMaxDataSize;

    memcpy( pMixHd, pPacket, uLen );
	pMixHd->uLen = uLen;
    
    if (pMixHd->uFunc == ADD)
    	AddNo ((void *) (pMixHd + 1));
    if (pMixHd->uFunc == DISP)
    	DispStr ((void *) (pMixHd + 1));
    if (pMixHd->uFunc == TIME)
    	LocTime (pMixHd);

    fBufferEmpty = (pMixHd->fRetReq == 0);

    TRACE( TC_VD, TT_API3,
        "VDMIX: ICADataArrival - data queued up, len %d ",
        uLen );
    TRACEBUF( TC_VD, TT_API3, pMixHd, uLen );

    return;
}


/*******************************************************************************
 *
 *  DriverPoll
 *
 *  The Winstation driver calls DriverPoll
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to virtual driver data structure
 *    pVdPoll (input)
 *       pointer to the structure DLLPOLL  (not used)
 *    puiSize (input)
 *       size of DLLPOOL structure.
 *
 * EXIT:
 *    CLIENT_STATUS_SUCCESS - OK so far.  We will be polled again.
 *    CLIENT_STATUS_NO_DATA - No more data to send.
 *    CLIENT_STATUS_ERROR_RETRY - Could not get an output buffer.
 *                            Hopefully, one will be available next time.
 *    Otherwise, a fatal error code is returned from lower level functions.
 *
 *    NOTE:  CLIENT_STATUS_NO_DATA signals the WD that it is OK to stop
 *           polling until another host to client packet comes through.
 ******************************************************************************/

int
DriverPoll( PVD pVd, PDLLPOLL pVdPoll, PUINT16 puiSize )
{
	UNREFERENCED_PARAMETER (pVd);
	UNREFERENCED_PARAMETER (pVdPoll);
	UNREFERENCED_PARAMETER (puiSize);

    int rc = CLIENT_STATUS_NO_DATA;
	USHORT uLen = pMixHd->uLen;

    static IBOOL fFirstTimeDebug = TRUE;  /* Only print on first invocation */

    if ( fFirstTimeDebug == TRUE ) {
        TRACE( TC_VD, TT_API2, "VDMIX: DriverPoll entered" );
        fFirstTimeDebug = FALSE;
    }

    /*
     *  Check for something to write
     */
    if ( fBufferEmpty ) {
        rc = CLIENT_STATUS_NO_DATA;
        goto Exit;
    }

    /*
     *  Write is postponed until this poll loop because the outbufreserve can
     *  fail, forcing us to wait until a buffer is freed - the only way to wait
     *  is to pick things up during the poll loop.
     *
     *  Reserve output buffer space; reserve four bytes more than the length because that
	 *	is the maximum ICA virtual header overhead.
     */
    if ( pOutBufReserve( pWd, (USHORT)(uLen+4) ) ) {
        rc =  CLIENT_STATUS_ERROR_RETRY;
        goto Exit;
    }

    TRACE( TC_VD, TT_API2, "VDMIX: Buffer to Write, type=%u", pMixHd->uType );

    /*
     *  Append ICA Virtual write header
     */
    if (( rc = pAppendVdHeader( pWd, gusVirtualChannelNum, uLen ))
               != CLIENT_STATUS_SUCCESS ) {
        goto Exit;
    }

    /*
     *  Append the Mix packet. It needs to be converted first into the wire format; since we
	 *	can do that only once, we set fBufferEmpty to TRUE at this point so we won't send the
	 *	data again. 
     */
    (void) WIRE_WRITE(MIXHEAD, pMixHd, uLen);
    fBufferEmpty = TRUE;
    if (( rc = pOutBufAppend( pWd, (LPBYTE)pMixHd, uLen ))
               != CLIENT_STATUS_SUCCESS ) {
        goto Exit;
    }

    /*
     *  Write the buffer
     */
    if (( rc = pOutBufWrite( pWd ))
               != CLIENT_STATUS_SUCCESS ) {
        goto Exit;
    }

    rc = CLIENT_STATUS_SUCCESS;

Exit:
    return( rc );
}


/*******************************************************************************
 *
 *  DriverClose
 *
 *  The user interface calls VdClose to close a Vd before unloading it.
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to procotol driver data structure
 *    pVdClose (input/output)
 *       pointer to the structure DLLCLOSE
 *    puiSize (input)
 *       size of DLLCLOSE structure.
 *
 * EXIT:
 *    CLIENT_STATUS_SUCCESS - no error
 *
 ******************************************************************************/
int
DriverClose( PVD pVd, PDLLCLOSE pVdClose, PUINT16 puiSize )
{
	UNREFERENCED_PARAMETER (pVd);
	UNREFERENCED_PARAMETER (pVdClose);
	UNREFERENCED_PARAMETER (puiSize);

	/* MixSamplePlugIn: Deallocate memory allocated for this PlugIn. */
    TRACE( TC_VD, TT_API1, "VDMIX: DriverClose entered" );

    free( pMixHd );
    pMixHd = NULL;
	/* MixSamplePlugIn end */
	
    return( CLIENT_STATUS_SUCCESS );
}


/*******************************************************************************
 *
 *  DriverInfo
 *
 *    This routine is called to get module information
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to virtual driver data structure
 *    pVdInfo (output)
 *       pointer to the structure DLLINFO
 *    puiSize (output)
 *       size of DLLINFO structure
 *
 * EXIT:
 *    CLIENT_STATUS_SUCCESS - no error
 *
 ******************************************************************************/

int
DriverInfo( PVD pVd, PDLLINFO pVdInfo, PUINT16 puiSize )
{
    USHORT ByteCount;
    PVDMIX_C2H pVdData;
    PMODULE_C2H pHeader;
    PVDFLOW pFlow;

	/* MixSamplePlugIn: Choose the right byte count. We always send a VDMIX_C2H struct, 
	 * so the right byte count is the number of bytes of that structure on the server. */
    ByteCount = sizeof (VDMIX_C2H);
	/* MixSamplePlugIn end */

    *puiSize = sizeof(DLLINFO);

    TRACE( TC_VD, TT_API1, "VDMIX: DriverInfo entered" );

    /*
     *  Check if buffer is big enough
     *  If not, the caller is probably trying to determine the required
     *  buffer size, so return it in ByteCount.
     */
    if ( pVdInfo->ByteCount < ByteCount ) {
        pVdInfo->ByteCount = ByteCount;
        return( CLIENT_ERROR_BUFFER_TOO_SMALL );
    }

    /*
     *  MixSamplePlugIn: Initialize default data. Most of this is independent of the plugin,
	 *  except the type of pVdData, and the version number and host module name that are filled in.
     */
    pVdInfo->ByteCount = ByteCount;
    pVdData = (PVDMIX_C2H) pVdInfo->pBuffer;

    /*
     *  Initialize module header
     */
    pHeader = &pVdData->Header.Header;
    pHeader->ByteCount = ByteCount;
    pHeader->ModuleClass = Module_VirtualDriver;

    pHeader->VersionL = CTXMIX_VER_LO;
    pHeader->VersionH = CTXMIX_VER_HI;
    strcpy((char*)(pHeader->HostModuleName), "ICA"); /* max 8 characters */

    /*
     *  Initialize virtual driver header
     */
    pVdData->Header.ChannelMask = pVd->ChannelMask;
    pFlow = &pVdData->Header.Flow;
    pFlow->BandwidthQuota = 0;
    pFlow->Flow = VirtualFlow_None;

    /* MixSamplePlugIn: Add our own data - the maximum size of data that we expect from the
	 * server. */
    pVdData->usMaxDataSize = gusMaxDataSize;

    pVdInfo->ByteCount = WIRE_WRITE(VDMIX_C2H, pVdData, ByteCount);
	/* MixSamplePlugIn end */

    return( CLIENT_STATUS_SUCCESS );
}



/*******************************************************************************
 *
 *  DriverQueryInformation
 *
 *   Required vd function.
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to virtual driver data structure
 *    pVdQueryInformation (input/output)
 *       pointer to the structure VDQUERYINFORMATION
 *    puiSize (output)
 *       size of VDQUERYINFORMATION structure
 *
 * EXIT:
 *    CLIENT_STATUS_SUCCESS - no error
 *
 ******************************************************************************/

int
DriverQueryInformation( PVD pVd, PVDQUERYINFORMATION pVdQueryInformation, PUINT16 puiSize )
{
	UNREFERENCED_PARAMETER (pVd);
	UNREFERENCED_PARAMETER (pVdQueryInformation);

    TRACE( TC_VD, TT_API1, "VDMIX: DriverQueryInformation entered" );
    TRACE( TC_VD, TT_API2, "pVdQueryInformation->VdInformationClass = %d",
         pVdQueryInformation->VdInformationClass);

    *puiSize = sizeof( VDQUERYINFORMATION );

	/* MixSamplePlugIn: We should examine what information the caller wants and supply that
	 * information, but we don't. */
	/* MixSamplePlugIn end */
    return( CLIENT_STATUS_SUCCESS );
}


/*******************************************************************************
 *
 *  DriverSetInformation
 *
 *   Required vd function.
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to virtual driver data structure
 *    pVdSetInformation (input/output)
 *       pointer to the structure VDSETINFORMATION
 *    puiSize (input)
 *       size of VDSETINFORMATION structure
 *
 * EXIT:
 *    CLIENT_STATUS_SUCCESS - no error
 *
 ******************************************************************************/

int
DriverSetInformation( PVD pVd, PVDSETINFORMATION pVdSetInformation, PUINT16 puiSize )
{
	UNREFERENCED_PARAMETER (pVd);
	UNREFERENCED_PARAMETER (pVdSetInformation);
	UNREFERENCED_PARAMETER (puiSize);

    TRACE( TC_VD, TT_API1, "VDMIX: DriverSetInformation entered" );
    TRACE( TC_VD, TT_API2, "pVdSetInformation->VdInformationClass = %d",
         pVdSetInformation->VdInformationClass);

	/* MixSamplePlugIn: We could examine the information sent to use and react to it in some way,
	 * but we don't. */
	/* MixSamplePlugIn end */

   return( CLIENT_STATUS_SUCCESS );
}


/*******************************************************************************
 *
 *  DriverGetLastError
 *
 *   Queries error data.
 *   Required vd function.
 *
 * ENTRY:
 *    pVd (input)
 *       pointer to virtual driver data structure
 *    pLastError (output)
 *       pointer to the error structure to return (message is currently always
 *       NULL)
 *
 * EXIT:
 *    CLIENT_STATUS_SUCCESS - no error
 *
 ******************************************************************************/

int DriverGetLastError( PVD pVd, PVDLASTERROR pLastError )
{
    TRACE( TC_VD, TT_API1, "VDMIX: DriverGetLastError entered" );

    /*
     *  Interpret last error and pass back code and string data
     */

	/* MixSamplePlugIn: We could report a different error and a different message at this 
	 * point. but we don't. */
    pLastError->Error = pVd->LastError;
    pLastError->Message[0] = '\0';
	/* MixSamplePlugIn end */
	
    return(CLIENT_STATUS_SUCCESS);
}


/******************************************************************************
 *
 *  ADDNO:
 *         Function executed on client side to Add two Numbers. Example
 *         of a function that requires a return Value.
 *
 *  ENTRY: pBufIp
 *           Pointer to the Arguments to the function
 *
 *  EXIT:  -
 *
 ******************************************************************************/

static void AddNo (LPBYTE pBufIp)
{
    USHORT num1;
    USHORT num2;

    TRACE( TC_VD, TT_API3, "VDMIX: ADDNO");

    memcpy(&num1, pBufIp, sizeof(USHORT));
    memcpy(&num2, pBufIp + sizeof (USHORT), sizeof(USHORT));

    pMixHd->uLen = sizeof (MIXHEAD);
    TRACE( TC_VD, TT_API3, "VDMIX:Addno %d  %d  ", num1, num2);

    pMixHd->dwRetVal =  num1 + num2;
    TRACE( TC_VD, TT_API2, "Result of addition is %d", pMixHd->dwRetVal);

    return;
}

/******************************************************************************
 *
 *  DispStr:
 *         Function executed on client side to Display a String
 *         (It is written to a log file) Example of a function that
 *         does not require a return value
 *
 *  ENTRY: pBufIp
 *           Pointer to the Arguments to the function
 *
 *  EXIT:  -
 *
 ******************************************************************************/

static void DispStr(LPBYTE pBufIp)
{
    memset(pTemp, '\0', TEMP_SIZE);
    memcpy(pTemp, pBufIp, pMixHd->dwLen1);
    TRACE( TC_VD, TT_API1, "The String Received is '%s'", pTemp);
    printf("DispStr:%s\n", pTemp);
}


/******************************************************************************
 *
 *  LocTime:
 *         Function returns the local time on the executed on client side
 *
 *  ENTRY: pBufIp
 *           Pointer to the Arguments to the function
 *
 *  EXIT:  -
 *
 ******************************************************************************/

static void LocTime (PMIXHEAD pHeader)
{
    TRACE( TC_VD, TT_API2, "VDMIX: Get Local Time");

#if !defined(DOS32) && !defined(WINCE)
    {
    struct tm *newtime;
    VDTM loctm;
    time_t long_time;

    time( &long_time );                /* Get time as long integer. */
    newtime = localtime( &long_time ); /* Convert to local time. */

    loctm.tm_sec = newtime->tm_sec;     /* seconds after the minute - [0,59] */
    loctm.tm_min = newtime->tm_min;     /* minutes after the hour - [0,59] */
    loctm.tm_hour = newtime->tm_hour;   /* hours since midnight - [0,23] */
    loctm.tm_mday = newtime->tm_mday;   /* day of the month - [1,31] */
    loctm.tm_mon = newtime->tm_mon;     /* months since January - [0,11] */
    loctm.tm_year = newtime->tm_year;   /* years since 1900 */
    loctm.tm_wday = newtime->tm_wday;   /* days since Sunday - [0,6] */
    loctm.tm_yday = newtime->tm_yday;   /* days since January 1 - [0,365] */
    loctm.tm_isdst = newtime->tm_isdst; /* daylight savings time flag */

    memcpy(pHeader + 1, &loctm, sizeof(VDTM));
    pMixHd->uLen = sizeof (MIXHEAD) + sizeof (VDTM);
    pMixHd->dwRetVal =  sizeof (MIXHEAD);
    TRACE( TC_VD, TT_API2,
        "The two lengths are (total)%d (mixhead)%d",
        pMixHd->uLen, pMixHd->dwRetVal);
    TRACE( TC_VD, TT_API2, "Local Time is %s", asctime( newtime ));
    }
#else
    /*
     *  This example does not return time for the DOS32 client. Value 1001
     * (arbitarily chosen) is used to convey this
     */
    pMixHd->dwRetVal =  1001;
    pMixHd->uLen = sizeof (MIXHEAD);
#endif

    return;
}

