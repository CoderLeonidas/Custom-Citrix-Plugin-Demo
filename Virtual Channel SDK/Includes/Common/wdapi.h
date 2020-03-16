/**********************************************************************
*
*  WDAPI.H
*
*  This module contains external winstation driver API
*  defines and structures
*
 *  Copyright � Citrix Systems, Inc.  All rights reserved.
*
***********************************************************************/

#ifndef __WDAPI_H__
#define __WDAPI_H__

//
// Note: Much of the information in this file has been moved to TempWDHeaders.h, the rest has  been
// moved as well but is commented out. So when changes are made in this file, the commented out
// items in TempWDHeaders.h should be changed as well. 
//
#import "TempWDHeaders.h"

#include <dllapi.h>
#include <vrtlclss.h>
#include <engtypes.h>
#include <ica.h>
#include "engapi.h"
#include <sys/socket.h>

/*
 *  WdSetInformation structure
 */
typedef struct _WDSETINFORMATION {
    WDINFOCLASS WdInformationClass;
    void* pWdInformation;
    USHORT WdInformationLength;
} WDSETINFORMATION, * PWDSETINFORMATION;


/*
 *  WdOpen structure
 */
typedef struct _WDOPEN {
    PDLLLINK pPdLink;           /* in: top most protocol driver */
    PDLLLINK pScriptLink;       /* in: pointer to scripting dll */
    PDLLLINK pDll;              /* in: pointer to a list of all loaded dlls */
    USHORT OutBufHeader;        /* in: number of header bytes to reserve */
    USHORT OutBufTrailer;       /* in: number of trailer bytes to reserve */
    USHORT OutBufParam;         /* in: number of parameter bytes to reserve */
    USHORT fOutBufCopy: 1;      /* in: pd copies data into new outbuf */
    USHORT fOutBufFrame: 1;     /* in: framing protocol driver is loaded */
    USHORT fAsync: 1;           /* in: Async connection or not */
    USHORT MaxVirtualChannels;  /* out: maximum virtual channels supported */
    HND hICAEng;                /* in: handle to ICA engine */
#if XCODE_SDK_UIKIT             /* still needed for iOS, AX_VC tvw */
    PPLIBPROCEDURE pfnStatusMsgProc; /* AX_VC tvw revisit status message procedure */
    void* pIniSection;         /* AX_VC tvw revisit pointer to ini file section buffer */
#endif // XCODE_SDK_UIKIT
} WDOPEN, * PWDOPEN;

/*
 *  WdConnect structure
 */
typedef struct _WDCONNECT {
    USHORT NotUsed;
} WDCONNECT, * PWDCONNECT;

typedef struct _WDCLIENTIDINFO {
    USHORT ProductId;
} WDCLIENTIDINFO, *PWDCLIENTIDINFO;


/*
 * WdVirtualChannel defines
 */
#define MAX_VC_PACKET_HEADER_SIZE   4               /* BYTE ICACmd, BYTE Channel, WORD length */

#define WDVCINFO_VERSION_ONE        1
#define WDVCINFO_VERSION_CURRENT    WDVCINFO_VERSION_ONE

#define WDVCINFO_REQUEST_GET_CHANNEL_COUNT          1       /* Ver 1 */
#define WDVCINFO_REQUEST_GET_CHANNEL_INFO_BY_INDEX  2       /* Ver 1 */
#define WDVCINFO_REQUEST_GET_CHANNEL_NUMBER_BY_NAME 3       /* Ver 1 */
#define WDVCINFO_REQUEST_GET_CHANNEL_NAME_BY_NUMBER 4       /* Ver 1 */
#define WDVCINFO_REQUEST_GET_MAX_CHANNEL_COUNT      5       /* Ver 1 */
#define WDVCINFO_REQUEST_GET_MAX_CHANNEL_WRITE      6       /* Ver 1 */
#define WDVCINFO_REQUEST_GET_MAX_CHANNEL_READ       7       /* Ver 1 */

/*
 * WdVirtualChannel structure
 */
typedef struct _WDVIRTUALCHANNELINFO
{
    ULONG        cbSize;
    ULONG        Version;
    ULONG        Request;                   /* Ver 1 - Request type         */
    VIRTUALNAME  ChannelName;               /* Ver 1 - Channel name         */
    USHORT       ChannelNumber;             /* Ver 1 - Channel number       */
    USHORT       usValue;                   /* Ver 1 - Input/output value   */
    ULONG        ulValue;                   /* Ver 1 - Input/output value   */
} WDVIRTUALCHANNELINFO, * PWDVIRTUALCHANNELINFO;

/*
 * WdGetLatencyInformation structure
 */
#define WDLATENCYINFO_VERSION_ONE        1
#define WDLATENCYINFO_VERSION_CURRENT    WDLATENCYINFO_VERSION_ONE

typedef struct _WDLATENCYINFO
{
    ULONG   cbSize;
    ULONG   Version;

    /*
     * Version 1
     */
    UINT32  LastLatency;
    UINT32  AverageLatency;
    INT32   RoundTripDeviation;

} WDLATENCYINFO, * PWDLATENCYINFO;


/*
 *  WdGetInfoData structure
 */
#define INFODATA_ID_SIZE 8
typedef struct _INFODATA {
    UCHAR Id[INFODATA_ID_SIZE];
    /* PUCHAR pData; */
} INFODATA, * PINFODATA;

/* // begin_binsdk */
/*
 *  WdOpenVirtualChannel structure
 */
typedef struct _OPENVIRTUALCHANNEL {
    void*   pVCName;
    USHORT  Channel;
} OPENVIRTUALCHANNEL, * POPENVIRTUALCHANNEL;

#define INVALID_VC_HANDLE 0xffff

/* // end_binsdk */

#include "keytypes.h"

/*
 *  WdMouseInfo structure
 */
typedef struct _MOUSEINFO {
    USHORT  cMouseData;
    void*   pMouseData;
} MOUSEINFO, * PMOUSEINFO;


#define WDKEYBOARDINPUT_VERSION_ONE         1
#define WDKEYBOARDINPUT_VERSION_CURRENT     WDKEYBOARDINPUT_VERSION_ONE
/*
 *  WdKeyboardInput structure
 */
typedef struct _WDKEYBOARDINPUT 
{
    USHORT  cbSize;
    USHORT  Version;
    IBOOL    bEnable;
} WDKEYBOARDINPUT, * PWDKEYBOARDINPUT;

#define WDMOUSEINPUT_VERSION_ONE         1
#define WDMOUSEINPUT_VERSION_CURRENT     WDMOUSEINPUT_VERSION_ONE
/*
 *  WdMouseInput structure
 */
typedef struct _WDMOUSEINPUT 
{
    USHORT  cbSize;
    USHORT  Version;
    IBOOL    bEnable;
} WDMOUSEINPUT, * PWDMOUSEINPUT;

/* // begin_binsdk */

/*
 *  Set Info Class enum
 */
typedef enum _SETINFOCLASS {
    CallbackComplete
} SETINFOCLASS, * PSETINFOCLASS;

/*
 *  Query Info Class enum
 */
typedef enum _QUERYINFOCLASS {
    QueryHostVersion,
    OpenVirtualChannel
} QUERYINFOCLASS, * PQUERYINFOCLASS;

/*
 * WdIcmQueryStatus structure
 */
typedef struct _WDICMQUERYSTATUSDATA
{
   IBOOL    fHostAvailable;  /* Host can support ICM    */
   UINT8   Version;         /* Agreed protocol version */

   IBOOL    fPingEnabled;    /* The client can send ping packets      */
   IBOOL    fBMEnabled;      /* Background channel monitoring enabled */

   UINT16  uBMRepeatDelay;  /* Background channel monitoring repeat delay, sec. */

   UINT32  LastLatency;
   UINT32  AverageLatency;

} WDICMQUERYSTATUSDATA, *PWDICMQUERYSTATUSDATA;

/*
 * WdIcmSendPingRequest structure
 */
typedef struct _WDICMSENDPINGREQUEST
{
   PVOID    pfnCallback;        /* Callback function. Can be NULL */
   PVOID    Context;            /* Callback context. Can be NULL  */
   IBOOL     fUrgent;            /* if TRUE then flush on the next poll */

} WDICMSENDPINGREQUEST, *PWDICMSENDPINGREQUEST;

/*
 *  WdReconnectInfo structure
 */
typedef struct _WDRECONNECTINFO
{
   UINT32               ReconnectManagerId;
   IBOOL                bAddressValid; /* Name, Address, ClientName, and PortNum are valid */
   ADDRESS              ConnectionFriendlyName;
   ADDRESS              Name;
   GEN_SOCKADDR_STORAGE Address;
   ADDRESS              IntermediateAddress;
   CLIENTNAME           ClientName;
   USHORT               PortNum;
   ADDRESS              SSLGatewayName;
   USHORT               SSLGatewayPortNum;
   USHORT               CGPPortNum;
   IBOOL				bWasUsingUDT;
   HDXOverUDP			HDXOverUDP;
   UINT16               cbCookie;   /* Input zero to query for cookie size  */
   PVOID                cookie[1];  /* Placeholder - cookie begins here in the buffer */
} WDRECONNECTINFO, *PWDRECONNECTINFO;

typedef int  (PWFCAPI POUTBUFALLOCPROC)( void*, POUTBUF * );
typedef void (PWFCAPI POUTBUFFREEPROC)( void*, POUTBUF );
typedef int  (PWFCAPI PPROCESSINPUTPROC)( void*, LPBYTE, USHORT );
typedef int  (PWFCAPI PSETINFOPROC)( void*, SETINFOCLASS, LPBYTE, USHORT );
/* // end_binsdk */
typedef int  (PWFCAPI PAPPENDICAPKTPROC)( void*, USHORT, LPBYTE, USHORT );
/* // begin_binsdk */
typedef int  (PWFCAPI PQUERYINFOPROC)( void*, QUERYINFOCLASS, LPBYTE, USHORT );
typedef int  (PWFCAPI POUTBUFRESERVEPROC)( void*, USHORT );
typedef int  (PWFCAPI POUTBUFAPPENDPROC)( void*, LPBYTE, USHORT );
typedef int  (PWFCAPI POUTBUFWRITEPROC)( void* );
typedef int  (PWFCAPI PAPPENDVDHEADERPROC)( void*, USHORT, USHORT );

#define FLUSH_IMMEDIATELY                   0

typedef struct _MEMORY_SECTION {
    UINT    length;
    LPBYTE  pSection;
} MEMORY_SECTION, *LPMEMORY_SECTION;

typedef int (PWFCAPI PQUEUEVIRTUALWRITEPROC) (void*, USHORT, LPMEMORY_SECTION, USHORT, USHORT);


/*=============================================================================
 ==   Virtual driver hook structures
 ============================================================================*/

/*
 *  Virtual driver write hook structure
 */
typedef void (PWFCAPI PVDWRITEPROCEDURE)( void*, USHORT, LPBYTE, USHORT );

/*
 *  Used when registering virtual write hook  (WdVirtualWriteHook)
 */
typedef struct _VDWRITEHOOK {
    USHORT Type;                             /* in: virtual channel id */
    void* pVdData;                          /* in: pointer to virtual driver data */
    PVDWRITEPROCEDURE pProc;                 /* in: pointer to vd write procedure (wd->vd) */
    void* pWdData;                          /* out: pointer to wd structure */
    POUTBUFRESERVEPROC pOutBufReserveProc;   /* out: pointer to OutBufReserve */
    POUTBUFAPPENDPROC pOutBufAppendProc;     /* out: pointer to OutBufAppend */
    POUTBUFWRITEPROC pOutBufWriteProc;       /* out: pointer to OutBufWrite */
    PAPPENDVDHEADERPROC pAppendVdHeaderProc; /* out: pointer to AppendVdHeader */
    USHORT MaximumWriteSize;                 /* out: maximum ica write size */
    PQUEUEVIRTUALWRITEPROC pQueueVirtualWriteProc;  /* out: pointer to QueueVirtualWrite */
} VDWRITEHOOK, * PVDWRITEHOOK;
/* // end_binsdk */

/*
 *  Used as an internal winstation structure
 */
typedef struct _WDVDWRITEHOOK {
    void* pData;                  /* pointer to virtual driver data */
    PVDWRITEPROCEDURE pProc;       /* pointer to virtual driver write procedure */
} WDVDWRITEHOOK, * PWDVDWRITEHOOK;

/*
 *  Used when registering virtual write hook  (WdVirtualWriteHook)
 */
typedef struct _VDWRITEHOOK20 {
    USHORT Type;                             /* in: virtual channel id */
    void* pVdData;                          /* in: pointer to virtual driver data */
    PVDWRITEPROCEDURE pProc;                 /* in: pointer to vd write procedure (wd->vd) */
    void* pWdData;                          /* out: pointer to wd structure */
    POUTBUFRESERVEPROC pOutBufReserveProc;   /* out: pointer to OutBufReserve */
    POUTBUFAPPENDPROC pOutBufAppendProc;     /* out: pointer to OutBufAppend */
    POUTBUFWRITEPROC pOutBufWriteProc;       /* out: pointer to OutBufWrite */
    PAPPENDVDHEADERPROC pAppendVdHeaderProc; /* out: pointer to AppendVdHeader */
    PAPPENDICAPKTPROC pAppendICAPktProc;     /* out: pointer to AppendICAPacket */
    USHORT MaximumWriteSize;                 /* out: maximum ica write size */
} VDWRITEHOOK20, * PVDWRITEHOOK20;

/*
 * WdRedraw structure
 */
typedef struct _WDRCL {         /* SetFocusProcedure parameter (via PACKET_REDRAW) */
   ULONG x:12, /* X coordinate */
         y:12; /* Y coordinate */
} WDRCL, *PWDRCL;

#define WD_CALL_INDEX  254  /* index for WDSETINFO calls using external VdInfo calls */


/* The opaque handle to the WD itself. */

typedef struct _WD * PWD;
/* // begin_binsdk */

#endif /* __WDAPI_H__*/
/* // end_binsdk */
