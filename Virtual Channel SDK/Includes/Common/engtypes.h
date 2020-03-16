/***************************************************************************
*
*  ENGTYPES.H
*
*  This module contains basic types defined by the ICA Client Engine.
*
*  Copyright � Citrix Systems, Inc.  All rights reserved.
*
****************************************************************************/

#ifndef _ENGTYPES_H_
#define _ENGTYPES_H_

#include "icaconst.h"

/*=============================================================================
 ==   assure consistant structure packing regardless of compiler flags
 ============================================================================*/
#ifdef PLATFORM_PRAGMAS
#pragma ENG_PACKING_ENABLE
#endif


/*=============================================================================
 ==   String typedefs (string length + 1 for NULL terminator)
 ============================================================================*/

typedef CHAR DOSFILENAME[ DOSFILENAME_LENGTH+1 ];
typedef CHAR DESCRIPTION[ DESCRIPTION_LENGTH+1 ];
typedef CHAR NAMERESOLVER[ NAMERESOLVER_LENGTH+1 ];
typedef CHAR TRANSPORTNAME[ TRANSPORTNAME_LENGTH+1 ];
typedef CHAR ENCRYPTIONLEVEL[ ENCRYPTIONLEVEL_LENGTH+1 ];
typedef CHAR CLIENTNAME[ CLIENTNAME_LENGTH+1 ];
typedef CHAR CLIENTSN[ CLIENTSN_LENGTH+1 ];
typedef CHAR DOMAIN[ DOMAIN_LENGTH+1 ];
typedef CHAR USERNAME[ USERNAME_LENGTH+1 ];
typedef CHAR PASSWORD[ PASSWORD_LENGTH+1 ];
typedef CHAR ENCRYPTEDPASSWORD[ ENCRYPTEDPASSWORD_LENGTH+1 ];
typedef CHAR ADDRESS[ ADDRESS_LENGTH+1 ];
typedef ADDRESS ADDRESSLIST [MAX_BROWSERADDRESSLIST];
typedef CHAR DEVICENAME[ DEVICENAME_LENGTH+1 ];
typedef CHAR KEYBOARDLAYOUT[ KEYBOARDLAYOUT_LENGTH+1 ];
typedef CHAR FILEPATH[ FILEPATH_LENGTH+1 ];

/*=============================================================================
 ==   UI suppliers must use user-defined messages above WM_WFENG_USER
 ============================================================================*/
#define WM_WFENG_USER (WM_USER+1000)


/*=============================================================================
 ==   WFENG dll entry points
 ============================================================================*/
#define WFENG_API_VERSION 5L          /* MF 1.8 FR1.9/SP2 Client */

#define WFENGMONITOR_QUERY_LAYOUT				0
#define WFENGMONITOR_QUERY_LAYOUT_WINDOW		1		// only valid for DesiredWinType == 16
#define WFENGMONTIOR_QUERY_LAYOUT_INITIALIZE	2		// only valid for DesiredWinType == 16
#define WFENGMONITOR_QUERY_LAYOUT_WND_CHECK_CAPTION	3


typedef VOID (PWFCAPI PFNUIPOLL)( VOID );


/*
 *  WFEngSetInformation()/WFEngQueryInformation() enum
 */
typedef enum _WFEINFOCLASS {

    unusedWFELastError,           /* Query */
    unusedWFEAddReadHook,         /* Set   */
    unusedWFERemoveReadHook,      /* Set   */
    unusedWFEThinwireCache,       /* Query */
    unusedWFEWindowHandle,        /* Query */
    unusedWFESetFocus,            /* Set   */
    unusedWFEKillFocus,           /* Set   */
    WFERedraw,              /* Set   */
    unusedWFEVdInfo,              /* Set & Query */
    unusedWFELogInfo,             /* Set   */
    WFEHotkey,              /* Set   */
    unusedWFEPnLogOff,            /* Set */
    unusedWFEOwnerData,           /* Set & Query */
    unusedWFESetProductID,        /* Set   */
    unusedWFERaiseSoftkey,        /* Set   */
    unusedWFELowerSoftkey,        /* Set   */
    unusedWFEFileSecurity,        /* Set   */
    unusedWFEClientDataServer,    /* Query */
    unusedWFEClientDataDomain,    /* Query */
    unusedWFEClientDataUsername,  /* Query */
    WFEDesktopInfo,         /* Query */
    unusedWFEGraphParams,   /* Set & Query */
    unusedWFEScaleStatus,         /* Query */
    unusedWFEAdjustParams,        /* Query */
    WFEInitSessionData,     /* Query */
    unusedWFEIOStatus,            /* Query */
    unusedWFEWndSubLst,           /* Query */
    unusedWFEbIPCEngine,          /* Query */
    WFEScreenDC,            /* Set */
    unusedWFEGraphMode,           /* Set & Query */
    WFESetCursor,           /* Set */
    unusedWFEScancodeEvent,       /* Set */
    unusedWFEUnicodeEvent,        /* Set */
    WFEHkeyAction,          /* Set & Query */
    WFESetCursorPos,        /* Set */
    WFEInstallPath,         /* Query */
    WFEKeyboardLayout,      /* Query */
    unusedWFETextModeStatus,      /* Query */
    WFETWIMode,             /* Query */
    unusedWFEScale,               /* Set & Query */
    WFEReconnectInfo,       /* Set & Query */
    unusedWFESession,             /* Set & Query */
    WFEMaxServerLVB,        /* Set */
    unusedWFEEnoughServerMem,     /* Query */
    WFEMultiMonSupport,      /* Query */
	WFEDegradeColorFirst,    /* Set */
	unusedWFEDisplayCaps,          /* Set & Query */
	WFESeamlessEnabled,      /* Set */
	WFESetTWMonitorLayout,   /* Set */
	unusedWFEFullScreenMode,       /* Query */
	WFEGetTWMonitorLayout,					// Query
} WFEINFOCLASS;


/*
 * Data block for WFESetProductID
 */
typedef struct _WFEPRODUCTID {
    USHORT  ProductID;
} WFEPRODUCTID, * PWFEPRODUCTID;


/* hotkey structure */
typedef struct _ICAENG_HOTKEYINFO {
    UINT16  uiHotkeyID;      /* ID of the Hotkey.*/
    UINT16  uiKeyCode;       /* Keycode (could be scan or unicode) associated with the hot key*/
    UINT16  uiShiftState;    /* Shift state associated with hot key*/
    PUCHAR  pKeyCodeSequence;/* Optional key code sequence to be sent to the server.*/
    UINT16  uiLength;        /* Number of bytes to be sent*/
    UINT16  uiSequenceType;  /* Signifies if the Sequence is Unicode or ScanCode */
#define SCANCODE_SEQUENCE 1  /* Sequence is of type ScanCode. */
#define UNICODE_SEQUENCE  2  /* Sequence is of type UniCode. */
#define CHARCODE_SEQUENCE 3  /* Sequence is of type CharCode. */
    
    UINT16  uiShiftStateFixed;
    
#define ALL_STATE   0x0000  /* any shift state is acceptable. No special processing needed*/
#define ALT_STATE   0x0001  /* Server should get only Alt state down. */
#define CTRL_STATE  0x0002  /* Server should get only Ctrl state down. */
#define SHIFT_STATE 0x0004  /* Server should get only Shift state down. */
    PFNDELIVER  pHkeyFunction; /* If sequence not present, call pHkeyFunction*/
} ICAENG_HOTKEYINFO, * PICAENG_HOTKEYINFO;


typedef struct _ICAENG_SCANCODEEVENT
{
    UINT16 cScanCodes;
    PUINT8 pScanCodes;
    UINT16 uiRepeat;
    UINT16 uiShiftState;
}
ICAENG_SCANCODEEVENT, * PICAENG_SCANCODEEVENT;



typedef struct ICAENG_UNICODEEVENT
{
    UINT16          cUnicodeCodes;
    UINT8           uiFlags;               /* the type of char value */
#define WND_UNICODECHAR_KEYUP   0x01
#define WND_UNICODECHAR_SPECIAL 0x02
    UINT16          uiValue;               /* Unicode or special key value */
    UINT16          uiRepeat;
    UINT16          uiShiftState;
}
ICAENG_UNICODEEVENT, * PICAENG_UNICODEEVENT;

/*
 *  Data Block for WFEngQueryInformation() - WFELastError
 */
typedef struct _WFELASTERROR {
    DOSFILENAME DriverName;
    int Error;
    char Message[ MAX_ERRORMESSAGE ];
} WFELASTERROR, * PWFELASTERROR;

/*
 * Data Block for WFEngQuery/SetInformation - WFEReconnectInfo
 */
typedef struct _WFERECONNECTINFO {
	IBOOL         bAddressValid; /* Name, Address, ClientName, and PortNum have valid data */
	BYTE         nRetriesRemaining;    /* Hack alert:  This field is only used
                                       * to communicate across engine instances,
                                       * not within the engine */
	ADDRESS              ConnectionFriendlyName;
	ADDRESS              Name;
	GEN_SOCKADDR_STORAGE Address;
	ADDRESS              IntermediateAddress;  /* for example, DNS name */
	CLIENTNAME           ClientName;
	UINT16               PortNum;
	ADDRESS              SSLGatewayName;
	UINT16               SSLGatewayPortNum;
	UINT16               CGPPortNum;
	UINT16               cbCookie;   /* Input zero to query for cookie size */
	BYTE                 cookie[MAX_COOKIE_SIZE];
	UINT16				 cbCgpSTA;   /* Input zero to query for cookie size */
	BYTE				 cgpSTA[_MAX_PATH + 1];
	IBOOL				 bWasUsingUDT;		// Indicates that the parent was using UDT transport
	HDXOverUDP			 HDXOverUDP;
} WFERECONNECTINFO, * PWFERECONNECTINFO;

#ifdef PLATFORM_PRAGMAS
#pragma ENG_PACKING_RESTORE
#endif

#endif /* _ENGTYPES_H_ */
