/*************************************************************************
*
* VDOVER.C
*
* Virtual Driver Example - Over
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
*************************************************************************/

/*
 * Note: In this source file, everything that is specific to the Over Sample PlugIn is marked 
 * with a comment containing the word OverSamplePlugIn. Everything else would be generic to
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

/* OverSamplePlugIn: Include header files that are specific to this PlugIn */
#include "vdover.h"
#include "overwire.h"
/* OverSamplePlugIn end */

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

/* OverSamplePlugIn: Variables used by the Over PlugIn */
static IBOOL fBufferEmpty = TRUE;           /* True if the data buffer is empty */
static PDRVRESP pDrvToSrv;              /* pointer to reply buffer from drv to Srv */
static POVER    pOver;                  /* Pointer to receive data from Srv */
/* OverSamplePlugIn end */


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

    TRACE( TC_VD, TT_API1, "VDOVER: DriverOpen entered" );

	/* OverSamplePlugIn begin */
    fBufferEmpty = TRUE;
	/* OverSamplePlugIn end */

    *puiSize = sizeof(VDOPEN);

    /*
     * Get a virtual channel. OverSamplePlugIn: The only part specific to this plugin is
	 * storing the correct name for this plugin. 
     */
    wdqi.WdInformationClass = WdOpenVirtualChannel;
    wdqi.pWdInformation = &OpenVirtualChannel;
    wdqi.WdInformationLength = sizeof(OPENVIRTUALCHANNEL);
    OpenVirtualChannel.pVCName = CTXOVER_VIRTUAL_CHANNEL_NAME;

    /* uiSize will be set  when we return back from VdCallWd. */
    uiSize = sizeof( WDQUERYINFORMATION);

    rc = VdCallWd( pVd, WDxQUERYINFORMATION, &wdqi, &uiSize  );
    TRACE( TC_VD, TT_API1, "VDOVER: opening channel %s",
            OpenVirtualChannel.pVCName );

    if ( rc != CLIENT_STATUS_SUCCESS ) {
        TRACE( TC_VD, TT_ERROR, "VDOVER: Could not open %s. rc=%d.",
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
    TRACE( TC_VD, TT_API2, "VDOVER: writehook channel number=%u"
            " vdwh.pVdData=%x rc=%d",
            vdwh.Type, vdwh.pVdData, rc );

    if ( rc != CLIENT_STATUS_SUCCESS ) {
        TRACE( TC_VD, TT_ERROR, "VDOVER: Could not register write hook. rc %d",
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

    TRACE( TC_VD, TT_API1, "VDOVER: Registered");

    /*
     *  ALL MEMORY MUST BE ALLOCATED DURING INITIALIZATION.
     *  Allocate a single buffer to send commands to the server
     *  This example shows use of the MaximumWriteSize returned via
     *  the previous call.
     *  Subtract one because the first byte is used internally by the
     *  WD for the channel number.  We are given a pointer to the
     *  second byte.
     */

	/* OverSamplePlugIn begin */
    if ( (pDrvToSrv = (PDRVRESP)malloc(sizeof(DRVRESP ))) == NULL ) {
        return( CLIENT_ERROR_NO_MEMORY );
    }

    memset(pDrvToSrv, 0, sizeof(DRVRESP));

    /*
     * pOver is used as the buffer to receive the data from the server
     */

    if ( (pOver = (POVER)malloc(sizeof(OVER))) == NULL ) {
        return( CLIENT_ERROR_NO_MEMORY );
    }
	/* OverSamplePlugIn end */

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

static void WFCAPI ICADataArrival( PVOID pVd, USHORT uChan, LPBYTE pBuf,
                                  USHORT Length )
{
	UNREFERENCED_PARAMETER (pVd);
	UNREFERENCED_PARAMETER (uChan);
	UNREFERENCED_PARAMETER (Length);

	/* OverSamplePlugIn: These two macros make pPacket a pointer to a struct OVER, doing all
	 * necessary conversions on non-Intel architectures. The struct name OVER is specific to this
	 * plugin. */
    WIRE_PTR(OVER, pPacket);
    WIRE_READ(OVER, pPacket, pBuf);
	/* OverSamplePlugIn end */

    TRACE( TC_VD, TT_API3,
        "VDOVER: IcaDataArrival, Len=%d, uLen=%d, pData=[%x][%x][%x][%x]",
        Length, pPacket->uLen, ((LPBYTE)pPacket)[0], ((LPBYTE)pPacket)[1], ((LPBYTE)pPacket)[2], ((LPBYTE)pPacket)[3] );
    TRACEBUF( TC_VD, TT_API3, pPacket, Length);

    /*
     * OverSamplePlugIn: ICADataArrival is called (polled) when the underlying WinStation 
     * Driver(WD) has data to pass to the Virtual Channel. The fBufferEmpty 
     * condition is added so that the client does not accept any more data till
     * it has sent back a message to the server. The data sent by the server 
     * during this time will be lost. If the following condition is not checked 
     * then the client can continue to receive data from the server. (The data 
     * being stored by the WD.) 
     */
     
    if ( !fBufferEmpty ) {
        TRACE( TC_VD, TT_ERROR,
            "VDOVER: ICADataArrival - Error: not all data was sent" );
        return;
    }
	/* OverSamplePlugIn end */

    /*
     *  OverSamplePlugIn: We always expect the correct number of bytes. If the packet is too small,
	 *	we ignore it completely. If the packet is too long, we ignore the excess data. Both should
	 *	not happen. 
     */
	if (pPacket->uLen < sizeof (OVER)) {
        TRACE( TC_VD, TT_ERROR,
            "VDOVER: ICADataArrival - Error: Packet length too small, packet ignored" );
		return;
    }
	if (pPacket->uLen > sizeof (OVER)) {
        TRACE( TC_VD, TT_ERROR,
            "VDOVER: ICADataArrival - Error: Packet length too large, excess data ignored" );
		return;
    }

    /*
     * Copy data from pPacket - buffer with arriving data packet to
     * pOver - buffer to hold the packet type being sent by the
     * server.
     */
    *pOver = *pPacket;

    /*
     *  When the counter is divisible by 10, we set fBufferEmpty to false, so DriverPoll will
	 *  send data to the server. The data inside the reply is the counter plus 7. The numbers 10
	 *	and 7 are chosen arbitarily
     */
    if (pPacket->uCounter % 10 == 0) {
        fBufferEmpty=FALSE;
        TRACE( TC_VD, TT_ERROR,
          "VDOVER: ICADataArrival fBufferEmpty made false" );
		pDrvToSrv->uType = OVERFLOW_JUMP;
		pDrvToSrv->uLen = sizeof (DRVRESP);
        pDrvToSrv->uCounter = pPacket->uCounter + 7;
    }

    TRACE( TC_VD, TT_API3,
        "VDOVER: ICADataArrival uCounter %d ", pPacket->uCounter );
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
	USHORT uLen;

    static IBOOL fFirstTimeDebug = TRUE;  /* Only print on first invocation */

    if ( fFirstTimeDebug == TRUE ) {
        TRACE( TC_VD, TT_API2, "VDOVER: DriverPoll entered" );
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
     *  Reserve output buffer space; reserve four bytes more than the length because that
	 *	is the maximum ICA virtual header overhead. Return if there is no block available
	 *	right now, we will be polled again later. 
     */
	uLen = pDrvToSrv->uLen;
    if ( pOutBufReserve( pWd, uLen+4 ) ) {
        rc =  CLIENT_STATUS_ERROR_RETRY;
        goto Exit;
    }


    /*
     *  Fill in Client to Server packet
     */
    TRACE( TC_VD, TT_API2, "VDOVER: Buffer to Write, type=%u",
        pDrvToSrv->uType );

    /*
     *  Append ICA Virtual write header
     */
    if (( rc = pAppendVdHeader( pWd, gusVirtualChannelNum, uLen ))
               != CLIENT_STATUS_SUCCESS ) {
        goto Exit;
    }

    /*
     *  Append the reply packet. It needs to be converted first into the wire format; since we
	 *	can do that only once, we set fBufferEmpty to TRUE at this point so we won't send the
	 *	data again. 
     */
    (void) WIRE_WRITE(DRVRESP, pDrvToSrv, uLen);
    fBufferEmpty = TRUE;
    if (( rc = pOutBufAppend( pWd, (LPBYTE)pDrvToSrv, uLen ))
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

    TRACE( TC_VD, TT_API1, "VDOVER: DriverClose entered" );

	/* OverSamplePlugIn: Deallocate memory allocated for this PlugIn. */

    if (pDrvToSrv)
        free( pDrvToSrv );
    if (pOver)
        free(pOver);
        
    pDrvToSrv = NULL;
    pOver = NULL;
	/* OverSamplePlugIn end */
	
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
    PVDOVER_C2H pVdData;
    PMODULE_C2H pHeader;
    PVDFLOW pFlow;

	/* OverSamplePlugIn: Choose the right byte count. We always send a VDOVER_C2H struct, 
	 * so the right byte count is the number of bytes of that structure on the server. */
    ByteCount = sizeof (VDOVER_C2H);
	/* OverSamplePlugIn end */

    *puiSize = sizeof(DLLINFO);

    TRACE( TC_VD, TT_API1, "VDOVER: DriverInfo entered" );

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
     *  OverSamplePlugIn: Initialize default data. Most of this is independent of the plugin,
	 *  except the type of pVdData, and the version number and host module name that are filled in.
     */
    pVdInfo->ByteCount = ByteCount;
    pVdData = (PVDOVER_C2H) pVdInfo->pBuffer;

    /*
     *  Initialize module header
     */
    pHeader = &pVdData->Header.Header;
    pHeader->ByteCount = ByteCount;
    pHeader->ModuleClass = Module_VirtualDriver;

    pHeader->VersionL = CTXOVER_VER_LO;
    pHeader->VersionH = CTXOVER_VER_HI;
    strcpy((char*)(pHeader->HostModuleName), "ICA"); /* max 8 characters */

    /*
     *  Initialize virtual driver header
     */
    pVdData->Header.ChannelMask = pVd->ChannelMask;
    pFlow = &pVdData->Header.Flow;
    pFlow->BandwidthQuota = 0;
    pFlow->Flow = VirtualFlow_None;

    /* OverSamplePlugIn: Add our own data - the only item is the maximum size of data that
	 * we expect from the server. */
    pVdData->usMaxDataSize = gusMaxDataSize;
    (void) WIRE_WRITE(VDOVER_C2H, pVdData, ByteCount);
	/* OverSamplePlugIn end */

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

    TRACE( TC_VD, TT_API1, "VDOVER: DriverQueryInformation entered" );
    TRACE( TC_VD, TT_API2, "pVdQueryInformation->VdInformationClass = %d",
         pVdQueryInformation->VdInformationClass);

    *puiSize = sizeof( VDQUERYINFORMATION );

	/* OverSamplePlugIn: We should examine what information the caller wants and supply that
	 * information, but we don't. */
	/* OverSamplePlugIn end */
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

    TRACE( TC_VD, TT_API1, "VDOVER: DriverSetInformation entered" );
    TRACE( TC_VD, TT_API2, "pVdSetInformation->VdInformationClass = %d",
         pVdSetInformation->VdInformationClass);

	/* OverSamplePlugIn: We could examine the information sent to use and react to it in some way,
	 * but we don't. */
	/* OverSamplePlugIn end */

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
    TRACE( TC_VD, TT_API1, "VDOVER: DriverGetLastError entered" );

    /*
     *  Interpret last error and pass back code and string data
     */

	/* OverSamplePlugIn: We could report a different error and a different message at this 
	 * point. but we don't. */
    pLastError->Error = pVd->LastError;
    pLastError->Message[0] = '\0';
	/* OverSamplePlugIn end */
	
    return(CLIENT_STATUS_SUCCESS);
}

