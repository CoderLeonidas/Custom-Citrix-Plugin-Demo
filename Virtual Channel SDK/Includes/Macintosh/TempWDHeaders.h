/*
 *  TempWDHeaders.h
 *  TempWDHeaders.h
 *
 *  Created by Don Swatman on 27-Jun-2011
 *  Copyright © Citrix Systems, Inc.  All rights reserved.
 *
 */

// Temporary holding file for the wire driver stuff, until we make it part of AX. Definitions are
// found in wdapi.h in other clients; in the Macintosh client wdapi.h includes this file.
//
// Anything that is commented out here can still be found in wdapi.h; if new items are needed in
// MacAX drivers, they should be added here and removed from wdapi.h. 

#ifndef __TempWDHeaders_H__
#define __TempWDHeaders_H__

#import "clterr.h"

 //  Index into WD procedure array 
#define WDxQUERYINFORMATION      6
#define WDxSETINFORMATION        7
#define WDxCOUNT                 8  // number of external wd procedures 


 //  WdInformationClass enum
 
typedef enum _WDINFOCLASS {
    WdClientData,
    WdStatistics,
    WdLastError,
    WdConnect,
    WdDisconnect,
    WdKillFocus,
    WdSetFocus,
    WdEnablePassThrough,
    WdDisablePassThrough,
    WdVdAddress,
    WdVirtualWriteHook,
    WdAddReadHook,
    WdRemoveReadHook,
    WdAddWriteHook,
    WdRemoveWriteHook,
    WdModemStatus,
    WdXferBufferSize,     // Get: Size of host and client buffers 
    WdCharCode,
    WdScanCode,
    WdMouseInfo,
    WdInitWindow,
    WdDestroyWindow,
    WdRedraw,             // Tell the host to redraw 
    WdThinwireStack,      // Pass the thinwire stack to the thinwire vd 
    WdHostVersion,        // get - Host Version information
    WdRealizePaletteFG,   // inform client to realize it's foreground palette 
    WdRealizePaletteBG,   // inform client to realize it's background palette 
    WdInactivate,         // client is about to lose input focus 
    WdSetProductID,
    WdGetTerminateInfo,   // test for legitimate terminate 
    WdRaiseSoftkey,       // raise the soft keyboard 
    WdLowerSoftkey,       // lower the soft keyboard 
    WdIOStatus,           // IO status 
    WdOpenVirtualChannel, // get - Open a virtual channel 
    WdCache,              // persistent caching command set 
    WdGetInfoData,        // Information from host to client 
    WdWindowSwitch,       // window has switched back, check keyboard state
    WdUnicodeCode,        // window has sent unicode information to wd 
	WdPassThruLogoff,
    WdClientIdInfo,        // Get the client identification information 
    WdPartialDisconnect,   // A PN Refresh connection will disconnect 
    WdDesktopInfo,         // Get/Set: information about the remote desktop
    WdSeamlessHostCommand, // Set: Seamless Host Agent command 
    WdSeamlessQueryInformation, // Get: Seamless information 
    _unused_WdZlRegisterUnicodeHook,      // Set : Zero Latency Unicode hook registration
    _unused_WdZLUnRegisterUnicodeHook,     // Set : Zero Latency Unicode hook unregistration
    _unused_WdZLRegisterScanCodeHook,    // Set: Zero Latency scan code hook registration
    _unused_WdZlUnregisterScanCodeHook,  // Set: Zero Latency scan code hook unregistration
    WdIcmQueryStatus,            // Get: Ica Channel Monitoring status 
    WdIcmSendPingRequest,        // Set: Send ping request and call callback if specified 
    WdSetCursor,                 // Set: New cursor from TW. Data - PHGCURSOR 
    WdFullScreenMode,            // Get: Return TRUE if full screen text is enabled
    WdFullScreenPaint,           // Set: Full Screen Mode needs redrawn
    WdSeamlessInfo,              // Get: Seamless information/capabilities from WD 
    WdCodePage,                  // Get: Retrieve server/client-default codepage 
    WdIcaControlCommand,         // Set: ICA Control Command 
    WdReconnectInfo,             // Get: Information needed for auto reconnect 
    WdServerSupportBWControl4Printing, // return TRUE if server supports printer bandwidth control
    WdVirtualChannel,            // Get: Virtual channel information 
    WdGetLatencyInformation,     // Get: Latency information 
    WdKeyboardInput,             // Get/Set: Enable/Disable keyboard input 
    WdMouseInput,                // Get/Set: Enable/Disable mouse input 
    WdCredentialPassing,         // Set: Passing Credentials through WD 
    WdRenderingMode,             // Set: Virtual channel the rendering mode (Headless)
    WdEUKSVersion,               // Get: Get Server EUKS version.
	
	// These are present in the latest Windows client, but not implemented. Added to avoid future
	// changes of enum values. Remove "_future_" when an enum value is used and implemented.
    _future_WdPauseResume,               // Get/Set: Pause/Resume virtual channels
    _future_WdQueryMMWindowInfo,         // Get: Query the information for the MMVD
    _future_WdICOSeamlessFunctions,      // Get/Set: ICO command
	
	_future_WdSetC2HPriority,            // Set: Set the virtual channel priority from client to server.
								 // IMPORTANT: YOU CAN ONLY SET THE PRIORITY BEFORE YOU HAVE SENT
								 // ANY PROTOCOL FOR THE VC
    _future_WdPnP,                       // Set: Send CLPNP_COMMAND commands in-between the control VC and
								 // the implementation VC (such as VIRTUAL_CCM)
	

    // Support for EUEM (Darwin Release For Ohio). This code has been added or changed to support
	// End User Experience Monitoring functionality. Please do not change the code in this section
	// without consulting the EUEM team . Email (at the time of change) "#ENG - Darwin Dev".
    WdEuemEndSLCD,               // Set endSLCD
    WdEuemStartupTimes,          // Get/Set. Set startup times from wfcrun32. Get startup times from
								 // VD EUEM
    WdEuemTwCallback,            // Set: register the EUEM ICA roundtrip callback function from the
								 // thinwire VC to the EUEM VC
    WdSessionIsReconnected,      // Get. Get indication if the session was auto reconnected using a
								 // token from VD EUEM
    WdUserActivity,              // Get/Set. Get indication if there has been user activity in the
								 // session from VD EUEM
    WdSessionResumed,            // Set. Called when a session is reconnected.
    WdSessionShared,             // Set. Called when a session becomes shared.
    // End of EUEM support section

	// These are present in the latest Windows client, but not implemented. Added to avoid future
	// changes of enum values.
    _future_WdLicensedFeatures,           // Get: Get Licensed Features
    _future_WdResizeHotBitmapCache,       // Set: Tell thinwire driver to resize the hot bitmap cache
    _future_WdLockDisplay,                // The Server has had its screen locked
    _future_WdCodePageUTF8Support,        // Get: CodePage 65001 (UTF-8) support status
	
    _future_WdCreateChannelComms,         // Get: Provide the driver with a pipe to communicate directly with.
	
    //added for 64 VC support
	_future_WdQueryVCNumbersForVD,        // Get: a list of virtual channels numbers that were registered since
								  // last call to WdQueryVCNumbersForVD
	_future_WdVirtualWriteHookEx,		  // Added 6/19/2009 by LHR for MTCA compatible channels
	_future_WdInternalFunction,			  // Used mostly for debug purposes, params specific to version under test
	_future_WdSendVirtualAck,			  // Send virtual ack ICA packet for a given channel
	_future_WdNotifyEuemOfReconnect,	  // Send a "set information" to EUEM that a reconnect has occurred (sent by CGP)
	_future_WdDummy1,					  // AVAILABLE
	_future_WdRequestPoll,				  // VD is requesting to be polled to send data (HPC API Version >= 1)
	_future_WdHpcProperties,			  // VD will use the specified version of the HPC API (HPC API Version >= 1)
	_future_WdAddressInfo,				  // Get: retrieve resolved address info (used by VDSSPI)
	WdSetDefaultDisplayVc,				  // Set: sets/resets the caller/thinwire to be the default display VC
    _future_WdQueryHostWindowId,          // Get Host Window ID
    _future_WdRtpSetup,                   // Set: mechanism for sending RTP_SETUP commands.

    WdGetICAWindowInfo,                   // Get: Get info about the ICA window
    WdGetClientWindowFromServerWindow,    // Get: Get the client window corresponding to the given server window
	
	WdClientAddress,					  // Get: Get the client socket address (ASCII string)

	WdSslConnectionInfo,				  // Get: Get the SSL connection information
	WdSslCertificateChain,				  // Get: Get the SSL certificate chain
    WdSetInputSourceCJK,                  // Set: Set the current input source whether CJK languages.
    WdSetIMEChannelBindStatus,            // Set: Set the IME channel bind status
    WdSetComposingExtent,                 // Set: Set the composing extent in VDA
	
	WdSendBufferResize,					  // Set: Send PACKET_BUFFER_RESIZE if needed after a reconnect.
	
	WdDidSendCredentials,				  // Get: Get indication if PACKET_CREDENTIALS was sent
	
	WdIcaDetected,						  // Get: Get indication if ICA string was detected
} WDINFOCLASS;

 
 //  WdQueryInformation structure
 
typedef struct _WDQUERYINFORMATION {
	WDINFOCLASS WdInformationClass;
	void* pWdInformation;
	ushort WdInformationLength;
	ushort WdReturnLength;
} WDQUERYINFORMATION, * PWDQUERYINFORMATION;
/*
//
 //  WdSetInformation structure
 
typedef struct _WDSETINFORMATION {
    WDINFOCLASS WdInformationClass;
    LPVOID pWdInformation;
    ushort WdInformationLength;
} WDSETINFORMATION, * PWDSETINFORMATION;
// // end_binsdk 

//
 //  WdOpen structure
 
typedef struct _WDOPEN {
    INIFILESECTION* pIniSection;         // in: pointer to ini file section buffer 
    PDLLLINK pPdLink;           // in: top most protocol driver 
    PDLLLINK pScriptLink;       // in: pointer to scripting dll 
    PDLLLINK pDll;              // in: pointer to a list of all loaded dlls 
    ushort OutBufHeader;        // in: number of header bytes to reserve 
    ushort OutBufTrailer;       // in: number of trailer bytes to reserve 
    ushort OutBufParam;         // in: number of parameter bytes to reserve 
    ushort fOutBufCopy: 1;      // in: pd copies data into new outbuf 
    ushort fOutBufFrame: 1;     // in: framing protocol driver is loaded 
    ushort fAsync: 1;           // in: Async connection or not 
    ushort MaxVirtualChannels;  // out: maximum virtual channels supported 
    HND hICAEng;                // in: handle to ICA engine 
} WDOPEN, * PWDOPEN;

//
 //  WdConnect structure
 
typedef struct _WDCONNECT {
    ushort NotUsed;
} WDCONNECT, * PWDCONNECT;

*/

 //  WdHostVersion structure
 
typedef struct _HostVersion {
    unsigned char HostLevel;
} HOSTVERSION, * PHOSTVERSION;

/*
typedef struct _WDCLIENTIDINFO {
    ushort ProductId;
} WDCLIENTIDINFO, *PWDCLIENTIDINFO;
*/

// WdHostBufferSize structure
 
typedef struct _WDXFERBUFFERSIZE
{
    ushort HostBufferSize;
    ushort ClientBufferSize;
} WDXFERBUFFERSIZE, * PWDXFERBUFFERSIZE;

/*
//
// WdVirtualChannel defines
 
#define MAX_VC_PACKET_HEADER_SIZE   4               // BYTE ICACmd, BYTE Channel, WORD length 

#define WDVCINFO_VERSION_ONE        1
#define WDVCINFO_VERSION_CURRENT    WDVCINFO_VERSION_ONE

#define WDVCINFO_REQUEST_GET_CHANNEL_COUNT          1       // Ver 1 
#define WDVCINFO_REQUEST_GET_CHANNEL_INFO_BY_INDEX  2       // Ver 1 
#define WDVCINFO_REQUEST_GET_CHANNEL_NUMBER_BY_NAME 3       // Ver 1 
#define WDVCINFO_REQUEST_GET_CHANNEL_NAME_BY_NUMBER 4       // Ver 1 
#define WDVCINFO_REQUEST_GET_MAX_CHANNEL_COUNT      5       // Ver 1 
#define WDVCINFO_REQUEST_GET_MAX_CHANNEL_WRITE      6       // Ver 1 
#define WDVCINFO_REQUEST_GET_MAX_CHANNEL_READ       7       // Ver 1 

//
// WdVirtualChannel structure
 
typedef struct _WDVIRTUALCHANNELINFO
{
    ULONG        cbSize;
    ULONG        Version;
    ULONG        Request;                   // Ver 1 - Request type         
    VIRTUALNAME  ChannelName;               // Ver 1 - Channel name         
    ushort       ChannelNumber;             // Ver 1 - Channel number       
    ushort       usValue;                   // Ver 1 - Input/output value   
    ULONG        ulValue;                   // Ver 1 - Input/output value   
} WDVIRTUALCHANNELINFO, * PWDVIRTUALCHANNELINFO;

//
// WdGetLatencyInformation structure
 
#define WDLATENCYINFO_VERSION_ONE        1
#define WDLATENCYINFO_VERSION_CURRENT    WDLATENCYINFO_VERSION_ONE

typedef struct _WDLATENCYINFO
{
    ULONG   cbSize;
    ULONG   Version;
	
    //
    // Version 1
     
    UINT32  LastLatency;
    UINT32  AverageLatency;
    INT32   RoundTripDeviation;
	
} WDLATENCYINFO, * PWDLATENCYINFO;


//
/  WdGetInfoData structure
 
#define INFODATA_ID_SIZE 8
typedef struct _INFODATA {
    UCHAR Id[INFODATA_ID_SIZE];
    // PUCHAR pData; 
} INFODATA, * PINFODATA;

// // begin_binsdk 
//
//  WdOpenVirtualChannel structure
 
typedef struct _OPENVIRTUALCHANNEL {
    LPVOID  pVCName;
    ushort  Channel;
} OPENVIRTUALCHANNEL, * POPENVIRTUALCHANNEL;

#define INVALID_VC_HANDLE 0xffff

// // end_binsdk 

#include "keytypes.h"


//  WdMouseInfo structure
 
typedef struct _MOUSEINFO {
    ushort  cMouseData;
    LPVOID  pMouseData;
} MOUSEINFO, * PMOUSEINFO;


#define WDKEYBOARDINPUT_VERSION_ONE         1
#define WDKEYBOARDINPUT_VERSION_CURRENT     WDKEYBOARDINPUT_VERSION_ONE
//
//  WdKeyboardInput structure
 
typedef struct _WDKEYBOARDINPUT 
{
    ushort  cbSize;
    ushort  Version;
    BOOL    bEnable;
} WDKEYBOARDINPUT, * PWDKEYBOARDINPUT;

#define WDMOUSEINPUT_VERSION_ONE         1
#define WDMOUSEINPUT_VERSION_CURRENT     WDMOUSEINPUT_VERSION_ONE

//  WdMouseInput structure
 
typedef struct _WDMOUSEINPUT 
{
    ushort  cbSize;
    ushort  Version;
    BOOL    bEnable;
} WDMOUSEINPUT, * PWDMOUSEINPUT;

// // begin_binsdk 


//  Set Info Class enum
 
typedef enum _SETINFOCLASS {
    CallbackComplete
} SETINFOCLASS, * PSETINFOCLASS;

//
//  Query Info Class enum
 
typedef enum _QUERYINFOCLASS {
    QueryHostVersion,
    OpenVirtualChannel
} QUERYINFOCLASS, * PQUERYINFOCLASS;
*/

//  Outbuf Buffer data structure
 
typedef struct _OUTBUF {
	
    //
    //  Non-inherited fields
     
    struct _OUTBUF * pLink;      // wd/td outbuf linked list 
    void * pParam;               // pointer to allocated parameter memory 
    uint8_t *pMemory;              // pointer to allocated buffer memory 
    uint8_t *pBuffer;              // pointer within buffer memory 
    ushort MaxByteCount;         // maximum buffer byte count (static) 
    ushort ByteCount;            // byte count pointed to by pBuffer 
	
    uint8_t *pSaveBuffer;          // saved outbuf buffer pointer 
    ushort SaveByteCount;        // saved outbuf byte count 
	
    //
    //  Inherited fields (when pd allocates new outbuf and copies the data)
     
    uint32_t StartTime;            // pdreli - transmit time (used to measure roundtrip) 
    ushort fControl: 1;         // pdreli - control buffer (ack/nak) 
    ushort fRetransmit: 1;      // pdreli - outbuf retransmit 
    ushort fCompress: 1;        // pdcomp - compress data 
    uint8_t Sequence;              // pdreli - sequence number 
    uint8_t Fragment;              // pdreli - fragment number 
	
} OUTBUF, * POUTBUF;
/*
//
// WdIcmQueryStatus structure
 
typedef struct _WDICMQUERYSTATUSDATA
{
	BOOL    fHostAvailable;  // Host can support ICM    
	UINT8   Version;         // Agreed protocol version 
	
	BOOL    fPingEnabled;    // The client can send ping packets      
	BOOL    fBMEnabled;      // Background channel monitoring enabled 
	
	UINT16  uBMRepeatDelay;  // Background channel monitoring repeat delay, sec. 
	
	UINT32  LastLatency;
	UINT32  AverageLatency;
	
} WDICMQUERYSTATUSDATA, *PWDICMQUERYSTATUSDATA;
*/
//
// WDSEAMLESSINFO structure
 
typedef struct _WDSEAMLESSINFO
{
	uint32_t     fSeamless20Logon;      // The server can support seamless 2.0 logon 
	uint32_t     fSynchronousSeamless;  // MF20 synchronous seamless 
	
	uint32_t     fEnabled;              // Seamless mode enabled for this session 
	uint32_t     fPaused;               // Host agent paused (simulated full screen 
	
} WDSEAMLESSINFO, *PWDSEAMLESSINFO;
/*
//
// WdIcmSendPingRequest structure
 
typedef struct _WDICMSENDPINGREQUEST
{
	PVOID    pfnCallback;        // Callback function. Can be NULL 
	PVOID    Context;            // Callback context. Can be NULL  
	BOOL     fUrgent;            // if TRUE then flush on the next poll 
	
} WDICMSENDPINGREQUEST, *PWDICMSENDPINGREQUEST;

//
//  WdReconnectInfo structure
 
typedef struct _WDRECONNECTINFO
{
	UINT32       ReconnectManagerId;
	BOOL         bAddressValid; // Name, Address, ClientName, and PortNum are valid 
	ADDRESS      ConnectionFriendlyName;
	ADDRESS      Name;
	ADDRESS      Address;
	ADDRESS      IntermediateAddress;
	CLIENTNAME   ClientName;
	ushort       PortNum;
	ADDRESS      SSLGatewayName;
	ushort       SSLGatewayPortNum;
	ushort       CGPPortNum;
	UINT16       cbCookie;   // Input zero to query for cookie size  
	PVOID        cookie[1];  // Placeholder - cookie begins here in the buffer 
} WDRECONNECTINFO, *PWDRECONNECTINFO;

typedef int  (PWFCAPI POUTBUFALLOCPROC)( LPVOID, POUTBUF * );
typedef void (PWFCAPI POUTBUFFREEPROC)( LPVOID, POUTBUF );
typedef int  (PWFCAPI PPROCESSINPUTPROC)( LPVOID, LPBYTE, ushort );
typedef int  (PWFCAPI PSETINFOPROC)( LPVOID, SETINFOCLASS, LPBYTE, ushort );
typedef void (PWFCAPI PIOHOOKPROC)( LPBYTE, ushort );
// // end_binsdk 
typedef int  (PWFCAPI PAPPENDICAPKTPROC)( LPVOID, ushort, LPBYTE, ushort );
// // begin_binsdk 
typedef int  (PWFCAPI PQUERYINFOPROC)( LPVOID, QUERYINFOCLASS, LPBYTE, ushort );
typedef int  (PWFCAPI POUTBUFRESERVEPROC)( LPVOID, ushort );
typedef int  (PWFCAPI POUTBUFAPPENDPROC)( LPVOID, LPBYTE, ushort );
typedef int  (PWFCAPI POUTBUFWRITEPROC)( LPVOID );
typedef int  (PWFCAPI PAPPENDVDHEADERPROC)( LPVOID, ushort, ushort );

#define FLUSH_IMMEDIATELY                   0

typedef struct _MEMORY_SECTION {
    UINT    length;
    LPBYTE  pSection;
} MEMORY_SECTION, far * LPMEMORY_SECTION;

typedef int (PWFCAPI PQUEUEVIRTUALWRITEPROC) (LPVOID, ushort, LPMEMORY_SECTION, ushort, ushort);


//=============================================================================
 ==   Virtual driver hook structures
 ============================================================================

//
//  Virtual driver write hook structure
 
typedef void (PWFCAPI PVDWRITEPROCEDURE)( LPVOID, ushort, LPBYTE, ushort );

//
//  Used when registering virtual write hook  (WdVirtualWriteHook)
 
typedef struct _VDWRITEHOOK {
    ushort Type;                             // in: virtual channel id 
    LPVOID pVdData;                          // in: pointer to virtual driver data 
    PVDWRITEPROCEDURE pProc;                 // in: pointer to vd write procedure (wd->vd) 
    LPVOID pWdData;                          // out: pointer to wd structure 
    POUTBUFRESERVEPROC pOutBufReserveProc;   // out: pointer to OutBufReserve 
    POUTBUFAPPENDPROC pOutBufAppendProc;     // out: pointer to OutBufAppend 
    POUTBUFWRITEPROC pOutBufWriteProc;       // out: pointer to OutBufWrite 
    PAPPENDVDHEADERPROC pAppendVdHeaderProc; // out: pointer to AppendVdHeader 
    ushort MaximumWriteSize;                 // out: maximum ica write size 
    PQUEUEVIRTUALWRITEPROC pQueueVirtualWriteProc;  // out: pointer to QueueVirtualWrite 
} VDWRITEHOOK, * PVDWRITEHOOK;
// // end_binsdk 

//
//  Used as an internal winstation structure
 
typedef struct _WDVDWRITEHOOK {
    LPVOID pData;                  // pointer to virtual driver data 
    PVDWRITEPROCEDURE pProc;       // pointer to virtual driver write procedure 
} WDVDWRITEHOOK, * PWDVDWRITEHOOK;

//
//  Used when registering virtual write hook  (WdVirtualWriteHook)
 
typedef struct _VDWRITEHOOK20 {
    ushort Type;                             // in: virtual channel id 
    LPVOID pVdData;                          // in: pointer to virtual driver data 
    PVDWRITEPROCEDURE pProc;                 // in: pointer to vd write procedure (wd->vd) 
    LPVOID pWdData;                          // out: pointer to wd structure 
    POUTBUFRESERVEPROC pOutBufReserveProc;   // out: pointer to OutBufReserve 
    POUTBUFAPPENDPROC pOutBufAppendProc;     // out: pointer to OutBufAppend 
    POUTBUFWRITEPROC pOutBufWriteProc;       // out: pointer to OutBufWrite 
    PAPPENDVDHEADERPROC pAppendVdHeaderProc; // out: pointer to AppendVdHeader 
    PAPPENDICAPKTPROC pAppendICAPktProc;     // out: pointer to AppendICAPacket 
    ushort MaximumWriteSize;                 // out: maximum ica write size 
} VDWRITEHOOK20, * PVDWRITEHOOK20;

//
// WdRedraw structure
 
typedef struct _WDRCL {         // SetFocusProcedure parameter (via PACKET_REDRAW) 
	ULONG x:12, // X coordinate 
y:12; // Y coordinate 
} WDRCL, *PWDRCL;

#define WD_CALL_INDEX  254  // index for WDSETINFO calls using external VdInfo calls 


// The opaque handle to the WD itself. 

typedef struct _WD * PWD;
// // begin_binsdk 
*/


// WdSessionIsReconnected structure
typedef struct _WDSESSIONISRECONNECTEDINFO
{
    bool isReconnected ;  // Check bool type
    UInt32 numCgpAutoreconnectsSeen ;
} WDSESSIONISRECONNECTEDINFO, * PWDSESSIONISRECONNECTEDINFO;


//
// Thinwire callback function into EUEM (UserExperience) virtual channel. The Thinwire channel
// will call a callback function of this type when triggered. The callback function is registered
// by using a WDxSETINFORMATION call with a WdEuemTwCallback / VdEuemTwCallback parameter
//
typedef void (*EUEMTWCALLBACK) (void* paramValue, // paramValue from EUEMTWCALLBACKREG
								uint8_t seq,
								uint32_t euemTriggerDelta,
								uint32_t firstDrawDelta,
								uint32_t frameCutDelta,
								uint32_t frameSendDelta,
								uint32_t wdTriggerDelta);

typedef struct
{
	EUEMTWCALLBACK	pFnCallback;
	void*			paramValue;
} EUEMTWCALLBACKREG;


//
// This structure contains a collection of EUEM data collected at various stages of the startup process.
//
// In this data structure a duration of zero means that no measurement has been made,
// for non-zero durations, one millisecond has must be subtracted to obtain the actual durations
//
// Original comments from Windows code. 
//

typedef struct
{
	bool sharedSessionLaunch;
	int32_t SLCD;					// new sessions only, this is set in wfcrun32
	uint64_t startSLCD;				// shared launches only, this is set in wfcrun32
	uint64_t endSLCD;				// shared launches only, this is retrieved from the WD
	
	// the following fields can be set in wfcrun32 for both shared and new sessions */
	
	uint64_t startSCD;
	uint64_t wficaStartSCD;
	uint64_t startIFDCD;
	uint64_t wficaEndIFDCD;
	uint64_t endIFDCD;
	uint64_t startSCCD;
	
	// these fields are extracted from the ica file, in either wfcrun32 or in the euem vd
	
	int32_t CFDCD;
	int32_t COCD;
	int32_t AECD;
	int32_t RECD;
	int32_t REWD;
	int32_t NRWD;
	int32_t TRWD;
	int32_t LPWD;
	int32_t BUCC;					// Backup Url Client Count
	
	// these are set in the WD
	
	int32_t NRCD;
	uint64_t endSCD;
	
	// shared sessions only, this is set in wfcrun32 and ...., null terminated
	
	char applicationName[256];
	char launcher[32];
	
	// used in vdeuem
	
	int32_t IFDCD;
	int32_t SCCD;
	int32_t SCD;
	uint8_t launcherType;
	
	// timestamp when EUEM process starts up
	uint64_t wficaStartupTimestamp;
	
} EUEM_STARTUP_TIMES, * PEUEM_STARTUP_TIMES;


/*
 * Various types used to refer to a window
 */
typedef enum _WDICAWINDOWTYPE
{
	windowTypeUnspecified = 0,
	windowTypeWin32HWND,
	windowTypeCarbonWindowRef,
	windowTypeCocoaNSWindow,
	windowTypeCocoaNSWindowArray,
} WDICAWINDOWTYPE, * PWDICAWINDOWTYPE;


/*
 * An abstracted reference to a particular type of window
 */
typedef struct _WDICAWINDOWHANDLE
{
	WDICAWINDOWTYPE type;
	void *handle;
} WDICAWINDOWHANDLE, * PWDICAWINDOWHANDLE;


/*
 * The current mode of the ICA window
 */
typedef union _WDICAWINDOWMODE
{
	struct
	{
		uint32_t Reserved : 1;
		uint32_t Seamless : 1;
		uint32_t Panning : 1;
		uint32_t Scaling : 1;
	} Flags;
	uint32_t Value;
} WDICAWINDOWMODE;


/*
 * Populated by WdGetICAWindowInfo call
 */
typedef struct _WDICAWINDOWINFO
{
	WDICAWINDOWHANDLE window;                                /* A pointer of some sort to the ica window */
	WDICAWINDOWMODE mode;                                    /* The current mode of the window */
	uint32_t xWinWidth, yWinHeight, xViewWidth, yViewHeight; /* ICA window dimensions */
	uint32_t xViewOffset, yViewOffset;                       /* The window's view offset (i.e. panning) */
} WDICAWINDOWINFO, * PWDICAWINDOWINFO;


#endif // __TempWDHeaders_H__


