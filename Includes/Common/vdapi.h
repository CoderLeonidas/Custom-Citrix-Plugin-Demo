/* // begin_binsdk */
/***************************************************************************
*
*  VDAPI.H
*
*  This module contains external virtual driver API defines and structures
*
*  Copyright (c) 1994-2001, 2007-2008 Citrix Systems, Inc. All Rights Reserved.
*
****************************************************************************/

#ifndef __VDAPI_H__
#define __VDAPI_H__

#include <icaconst.h>
#include <dllapi.h>
#include <ica.h>
#include "engapi.h"

//
// This file may be included by code that is used to build the Virtual Channel SKD (in that case
// VCSDKMacOSX = 1) or to build plug-ins (XCODE_MACOSX_PLUGIN = 1). In these two cases libmgr.h
// must be included, which will define the interface to use the library manager and call tables.
//
#if VCSDKMacOSX || XCODE_MACOSX_PLUGIN
#include <libmgr.h>
#endif


/*
 *  Index into PD procedure array
 */
#define VDxQUERYINFORMATION      6
#define VDxSETINFORMATION        7
#define VDxCOUNT                 8   /* number of external procedures */


/*
 *  VdOpen structure
 */
typedef INT (WFCAPI *PFNICAENGPOLL)( HND hICAEng );
typedef LRESULT (WFCAPI *PFNSTATUSMESSAGEPROC)( HND hICAEng, int message );
typedef struct _VDOPEN
{
    void* pUnused;							/* Used to be pIniSection */
    PDLLLINK pWdLink;
    ULONG ChannelMask;						/* bit 0 = Virtual_Screen */
    PFNICAENGPOLL pfnWFEngPoll;				/* Only for use by virtual channels */
    PFNSTATUSMESSAGEPROC pfnStatusMsgProc;	/* Only for use by virtual channels */
    PICAENG hICAEng;
} VDOPEN, FAR * PVDOPEN;


/*
 *  VdInformationClass enum
 *   additional information classes can be defined for a given
 *   VD, as long as the number used is greater than that generated
 *   by this enum list. Any changes must be reflected in ICATypes.h.
 */

typedef enum _VDINFOCLASS {
    VdLastError = 0,
    VdKillFocus = 1,
    VdSetFocus = 2,
    VdMousePosition = 3,
    unusedVdThinWireCache = 4,
    VdWinCEClipboardCheck = 5,    /*  Used by WinCE to check for clipboard changes */
    VdDisableModule = 6,
    VdFlush = 7,
    VdInitWindow = 8,
    VdDestroyWindow = 9,
    VdPaint = 10,
    VdThinwireStack = 11,
    VdRealizePaletteFG = 12,   /* inform client to realize it's foreground palette */
    VdRealizePaletteBG = 13,   /* inform client to realize it's background palette */
    VdInactivate = 14,         /* client is about to lose input focus */
    VdGetSecurityAccess = 15,  /* cdm security info */
    VdSetSecurityAccess = 16,  /* cdm security info */
	VdGetAudioSecurityAccess = 17,	/* cdm audio security info */
	VdSetAudioSecurityAccess = 18,	/* cdm audio security info */
	_future_VdGetPDASecurityAccess = 19,		// cdm PDA security info
	_future_VdSetPDASecurityAccess = 20,		// cdm PDA security info
	_future_VdGetTWNSecurityAccess = 21,		// cdm TWN security info
	_future_VdSetTWNSecurityAccess = 22,		// cdm TWN security info
    VdSendLogoff = 23,
    VdCCShutdown = 24,

    VdSeamlessHostCommand = 25,        /* Seamless command call */
    VdSeamlessQueryInformation = 26,   /* Seamless query call */

    VdWindowGotFocus = 27,
    VdSetCursor = 28,                  /* Set: New cursor from TW. Data - PHGCURSOR */
    VdSetCursorPos = 29,               /* Set: New cursor position. Data - VPPOINT */

    VdEnableState = 30,                /* Set/Get driver state (enabled/disabled) */

    VdIcaControlCommand = 31,

    VdVirtualChannel = 32,             /* Set/Get virtual channel data */
    VdWorkArea = 33,                   /* Set the work area of the application */
    VdSupportHighThroughput = 34,
    VdRenderingMode = 35,              /* Set/Get the rendering mode (headless client) */
	_future_VdPauseResume = 36,				// Pause/Resume commands
#ifdef BLT_IS_EXPENSIVE
	_future_VdRedrawNotify = 37,			// Overdrawing suppression.
#endif
	VdDisplayCaps = 38,                /* Get/Set display capabilities and/or preferred mode */
	_future_VdICOSeamlessFunctions = 39,	// Get seamless functions for ICO
	_future_VdPnP = 40,						// Set: Send CLPNP_COMMAND commands inbetween the control VC and the implementation VC (such as VIRTUAL_CCM)

	/* Support for EUEM (Darwin Release For Ohio). This code has been added or
	 * changed to support End User Experience Monitoring functionality. Please do
	 * not change the code in this section without consulting the EUEM team
	 *  Email (at the time of change) "#ENG - Darwin Dev"
	 */
	VdEuemStartupTimes = 41,			// Set: EUEM: pass the startup times of shared sessions to the EUEM VD
	VdEuemTwCallback = 42,				// Set: register the EUEM ICA roundtrip callback
										// function from the thinwire VC to the EUEM VC
	// End of EUEM support section

	_future_VdResizeHotBitmapCache = 43,	 // Set: Tell thinwire driver to resize the hot bitmap cache
	VdSetMonitorLayout = 44,           /* Set: Tell thinwire driver to update monitor layout info */
    VdServerCodePage = 45,
    VdDosPathForLocalPath = 46,        /* Query to CDM to get a Windows path for a Mac path */

	_future_VdGUSBGainFocus = 47,			 // Set: Tell Generic USB driver that engine has gained keyboard focus
	_future_VdGUSBLoseFocus = 48,			 // Set: Tell Generic USB driver that engine has lost keyboard focus
	_future_VdCreateChannelComms = 49,		 // Query: Provide the driver with a pipe to communicate directly with
	_future_VdGetPNPSecurityAccess = 50,	 // usb PNP security info
	_future_VdSetPNPSecurityAccess = 51,	 // usb PNP security info
	_future_VdReverseSeamless = 52,			 // For use with RS specific calls
	_future_VdInfoRequest = 53,				 // Used to request information from a VD
    _future_VdReverseSeamlessPartial = 54,   // partial RS packet data used to form a complete RS VC packet
	_future_VdEuemNotifyReconnect = 55,		 // Notify EUEM about a reconnect
    _future_VdCHAEnabled = 56,               // Notify Drivers about Enabling/Disabling CHA based on CST recommendation	} VDINFOCLASS;
} VDINFOCLASS;

/*
 *  VdQueryInformation structure
 */
typedef struct _VDQUERYINFORMATION {
    VDINFOCLASS VdInformationClass;
    LPVOID pVdInformation;
    int VdInformationLength;
    int VdReturnLength;
} VDQUERYINFORMATION, * PVDQUERYINFORMATION;

/*
 *  VdSetInformation structure
 */
typedef struct _VDSETINFORMATION {
    VDINFOCLASS VdInformationClass;
    LPVOID pVdInformation;
    int VdInformationLength;
} VDSETINFORMATION, * PVDSETINFORMATION;

/*
 *  VdLastError
 */
typedef struct _VDLASTERROR {
    int Error;
    char Message[ MAX_ERRORMESSAGE ];
} VDLASTERROR, * PVDLASTERROR;

/*
 * VD Flush
 */
typedef struct _VDFLUSH {
    UCHAR Channel;
    UCHAR Mask;
} VDFLUSH, * PVDFLUSH;

#define  VDFLUSH_MASK_PURGEINPUT    0x01
#define  VDFLUSH_MASK_PURGEOUTPUT   0x02

/* // end_binsdk */

/*
 * VD Thinwire Stack
 */
typedef struct _VDTWSTACK {
    LPBYTE pTop;
    LPBYTE pMiddle;
    LPBYTE pBottom;
} VDTWSTACK, * PVDTWSTACK;

/*
 * VdVirtualChannel
 */
#define VDVCINFO_MAX_CHANNELNAME  (VIRTUALNAME_LENGTH + 1)
#define VDVCINFO_MAX_CHANNELNUM   VIRTUAL_MAXIMUM

#define VDVCINFO_VERSION_ONE      1
#define VDVCINFO_VERSION_CURRENT  VDVCINFO_VERSION_ONE

#define VDVCINFO_REQUEST_QUERY_CHANNEL_NUMBER   1       /* query */
#define VDVCINFO_REQUEST_QUERY_CHANNEL_NAME     2       /* query */
#define VDVCINFO_REQUEST_QUERY_CHANNEL_COUNT    3       /* query */
#define VDVCINFO_REQUEST_QUERY_READ_TYPE        4       /* query */
#define VDVCINFO_REQUEST_QUERY_READ_SIZE        5       /* query */
#define VDVCINFO_REQUEST_READ_CHANNEL           6       /* query */
#define VDVCINFO_REQUEST_WRITE_CHANNEL          7       /* set */
#define VDVCINFO_REQUEST_CHANNEL_FLAGS          8       /* query/set */

#define VDVCINFO_CHANNEL_FLAGS_FRAGMENT         0x01    /* fragment the request if required */

#define VDVCINFO_PACKET_TYPE_STRING             0       /* no zeroes in data */
#define VDVCINFO_PACKET_TYPE_BINARY             1       /* zeroes in data    */

typedef struct _VDVCINFO {
    ULONG   cbSize;             /* size of VDVCINFO structure with data     */
    USHORT  Version;            /* Version of request structure             */

    ULONG   ulRequest;          /* Ver 1 - type of Virtual Channel Request  */

    VIRTUALNAME szChannelName;  /* Ver 1 - Channel name                     */
    USHORT      usChannelNum;   /* Ver 1 - Channel number                   */

    ULONG   ulValue;            /* Ver 1 - used for simple requests         */

    ULONG   cbVCInfo;           /* Ver 1 - length of Virtual Channel info   */
    ULONG   oVCInfo;            /* Ver 1 - offset to Virtual Channel info   */
                                /* VC info after the structure              */
} VDVCINFO, * PVDVCINFO;

/*
 * VdWorkArea
 */
#define VDWORKAREA_VERSION_ONE      1
#define VDWORKAREA_VERSION_CURRENT  VDWORKAREA_VERSION_ONE

typedef struct _VDWORKAREA {
    UINT16  cbSize;             /* size of VDWORKAREA structure with data   */
    UINT16  Version;            /* Version of request structure             */

    UINT32  uiXPos;             /* Ver 1 - X Position of work area          */
    UINT32  uiYPos;             /* Ver 1 - Y Position of work area          */
    UINT32  uiWidth;            /* Ver 1 - width of work area               */
    UINT32  uiHeight;           /* Ver 1 - height of work area              */

} VDWORKAREA, * PVDWORKAREA;

typedef struct _VDRENDERINGMODE {
    UINT16  cbSize;             /* size of VDRENDERINGMODE structure        */
    UINT16  Version;            /* Version of request structure             */

    UINT32  uiRenderingMode;    /* Ver 1 - The rendering mode for the client*/

} VDRENDERINGMODE, * PVDRENDERINGMODE;

typedef struct _VDTWXYRES {
    UINT16  hRes;
    UINT16  vRes;
} VDTWXYRES, *PVDTWXYRES;

#ifndef CCAPS_4_BIT
#define CCAPS_4_BIT         0x0001      /* from twcommon.h */
#endif
#ifndef CCAPS_8_BIT
#define CCAPS_8_BIT         0x0002      /* from twcommon.h */
#endif
#ifndef CCAPS_16_BIT
#define CCAPS_16_BIT        0x0004      /* from twcommon.h */
#endif
#ifndef CCAPS_24_BIT
#define CCAPS_24_BIT        0x0008      /* from twcommon.h */
#endif

typedef struct _VDTWCAPS
{
    UINT16    depths;
#define VDDCAP_4BPP    CCAPS_4_BIT
#define VDDCAP_8BPP    CCAPS_8_BIT
#define VDDCAP_16BPP   CCAPS_16_BIT
#define VDDCAP_24BPP   CCAPS_24_BIT
    UINT16    fixedResCnt;    /* 0    -> variable resolution up to res[0].hRes X res[0].vRes */
                              /* 1-10 -> only supports fixed resoltions in res[] array */
    VDTWXYRES res[10];
} VDTWCAPS, * PVDTWCAPS;

typedef struct _VDTWMODE
{
    UINT16    depth;  /* One of VDDCAP_xxx bits */
    VDTWXYRES res;
} VDTWMODE, * PVDTWMODE;

typedef struct _VDTWDISPLAYCAPS
{
    UINT32   Flags;
#define VDTW_PREF_UPDATE 0x1
#define VDTW_CAP_UPDATE  0x2
    VDTWMODE Pref;
    VDTWCAPS Caps;
} VDTWDISPLAYCAPS, * PVDTWDISPLAYCAPS;


/* // begin_binsdk */
#endif /* __VDAPI_H__ */
/* // end_binsdk */


