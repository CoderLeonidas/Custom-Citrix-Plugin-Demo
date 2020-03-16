/*************************************************************************
 *
 *  platfix.h
 *
 *  Fixups that allow the macintosh client to build with new common include
 *  files that are used.
 *
 *	Copyright © Citrix Systems, Inc.  All rights reserved.
 *
 ************************************************************************/

#ifndef _MAC_PLAT_FIX_H_  
#define _MAC_PLAT_FIX_H_

/*
 *----------------------------------------------------------------------------
 *  UNIFICATION : Defines needed to get Mac client working with common headers                    
 *----------------------------------------------------------------------------
 */

/*=============================================================================
 ==  Configuration INI keys (INI_) and defaults (DEF_)
 ============================================================================*/
 
/* In Win32 these go in the registry instead of the INI file... */
#define INI_SAVESETTINGSONEXIT "SaveSettingsOnExit"	/* Used by CSM */
#define DEF_SAVESETTINGSONEXIT TRUE					/* Used by CSM */


#if defined(MacOrUnix) && !defined(INI_LOGFILE)	
#define INI_LOGFILE         "LogFile"				/* Used by CSM */
#define DEF_LOGFILE         "wfclient.log"				/* Used by CSM */
#endif

/*=============================================================================
 ==  Client Name INI key (INI_) and defaults (DEF_)
 ==     The ClientName is in <boot-drive>:\WFCNAME.INI for DOS and WIN16
 ==                and is in <system-drive>:\WFCNAME.INI for WIN32
 ============================================================================*/

#define INI_COMPORTCOUNT	"LastComPortNum"			/* Used by CSM */
#define DEF_COMPORTCOUNT      	0						/* Used by CSM */

#define INI_COMPORTDEVICE	"ComPort"					/* Used by CSM */
#define DEF_COMPORTDEVICE      	""							/* Used by CSM */

/*=============================================================================
 ==   Transport Driver INI keys (INI_) and defaults (DEF_)
 ============================================================================*/

#define INI_TCPGROUPNAME "TcpGroupName"	/* Used by CSM */
#define DEF_TCPGROUPNAME ""				/* Used by CSM */

#define INI_KEYBOARDMAPPINGFILE	    "KeyboardMappingFile"	/* Used by CSM */
#define DEF_KEYBOARDMAPPINGFILE		""						/* Used by CSM */

#define INI_KEYBOARDDESCRIPTION		"KeyboardDescription"	/* Used by CSM */
#define DEF_KEYBOARDDESCRIPTION		""						/* Used by CSM */


/*=============================================================================
 ==  AppServer INI keys (INI_) and defaults (DEF_)
 ============================================================================*/

#define INI_NO_WINDOW_MANAGER	"NoWindowManager"	/* Used by CSM */

#define INI_MINIMIZE	    "MinimizeOnUse"	/* Used by CSM */
#define DEF_MINIMIZE	    FALSE			/* Used by CSM */
#define INI_POPUP	    	"PopupOnExit"	/* Used by CSM */
#define DEF_POPUP	    	FALSE			/* Used by CSM */

#define INI_APPROXIMATE_COLORS "ApproximateColors"	/* Used by CSM */
#define DEF_APPROXIMATE_COLORS FALSE				/* Used by CSM */

#define INI_APPROX_COLORS_USE_DEFAULT  "UseDefaultSettingForColormap"	/* Used by CSM */
#define DEF_APPROX_COLORS_USE_DEFAULT  TRUE								/* Used by CSM */

/*
 *  vdtw30.dll
 */

#define INI_USEDEFAULTVISUAL        "UseDefaultVisual"
#define DEF_USEDEFAULTVISUAL        FALSE
#define INI_USEUSERVISUALID         "UseUserVisualID"
#define DEF_USEUSERVISUALID         FALSE
#define INI_USERVISUALID            "UserVisualID"
#define DEF_USERVISUALID            0
#define INI_LARGECACHESIZE_IN_K "LargeCacheSizeInK"
#define DEF_LARGECACHESIZE_IN_K 2048

/*
 * Backing Store
 */
#define INI_ALLOW_BACKING_STORE "AllowBackingStore"
#define DEF_ALLOW_BACKING_STORE FALSE

/*
 * Force server redrawing
 */
#define INI_SERVER_REDRAW	"UseServerRedraw"
#define DEF_SERVER_REDRAW	FALSE

#define INI_USEFULLSCREEN  "UseFullScreen"
#define DEF_USEFULLSCREEN  FALSE

#define INI_TWI_MODE            "TWIMode"
#define DEF_TWI_MODE    FALSE

#define INI_TRUE            "True"
#define INI_FALSE           "False"

/* Version numbers stored in the WFClient Section of the ini files. */
#define INI_ISVERSION        "ISVersion"
#define DEF_ISVERSION        0
#define ISVERSION_1	     DEF_ISVERSION	/* Not present */
#define ISVERSION_2	     200		/* 2.0.0 */
#define ISVERSION_3	     300		/* 3.0.0 */
#define ISVERSION_4	     400		/* 4.0.0 */
#define ISVERSION_4_1_0  410		/* 4.1.0 */
#define ISVERSION_6		 600		/* 6.0.0 */
#define ISVERSION_6_0_1	 601		/* 6.0.1 */
#define ISVERSION_6_2_0	 620		/* 6.20.0 */
#define ISVERSION_6_3_0	 630		/* 6.30 */
#define ISVERSION_7_0_0	 700		/* 7.00 */
#define ISVERSION_7_1_0	 710		/* 7.1.0 */
#define ISVERSION_8_0_0	 800		/* 8.0.0 */
#define ISVERSION_11_1_0 1110       /* 11.1.0 */
#define ISVERSION_11_8_0 1180       /* 11.8.0 */
#define ISVERSION_11_9_0 1190       /* 11.9.0 */
#define ISVERSION_12_1_0 1210		/* 12.1.0 */
#define ISVERSION_12_4_0 1240		/* 12.4.0 */
#define ISVERSION_12_6_0 1260		/* 12.6.0 */
#define ISVERSION_12_8_0 1280		/* 12.8.0 */
#define ISVERSION_12_8_1 1281		/* 12.8.1 */
#define ISVERSION_12_9_0 1290		/* 12.9.0 */
#define ISVERSION_12_10_0 12100		/* 12.10.0 */



#define CURRENT_ISVERSION    ISVERSION_12_10_0

/*
 *  vdcdm30.dll
 */

#define INI_VDCDM30		"ClientDrive"


#define INI_VIRTUAL_DRIVER   "VirtualDriver"

/*
 *  Client Audio Mapping
 */
 
#ifdef MacOrUnix
#define INI_VDCAM30			"ClientAudio"
#else
#error MacOrUnix not defined???
#endif 

#define INI_CLIENTAUTOQUIT  "DisableClientAutoQuit"
#define DEF_CLIENTAUTOQUIT   TRUE

#define INI_USEFULLSCREEN  "UseFullScreen"
#define DEF_USEFULLSCREEN  FALSE

/*
 *  vdcpm30.dll
 */

/* Printer types supported. 0 = none, 1 and 2 are for obsolete postscript and direct printing. 
 * 3 = PCL4 printing (obsolete), 4 = PCL5 printing (obsolete), 5 = PostScript printing (PostScript
 * printing is the only supported method for the current client version. */
#define PRINTER_TYPE_NONE		0
#define PRINTER_TYPE_PCL4		3
#define PRINTER_TYPE_PCL5		4
#define PRINTER_TYPE_PS			5

/* Which type of printer is in use. At the moment this feature is not checked because we only
 * support one print method (PostScript printing; PRINTER_TYPE_PS) */

/*		#define INI_PRINTER_TYPE		"PrinterType"				*/
/*		#define DEF_PRINTER_TYPE		PRINTER_TYPE_PS				*/


#define INI_VDCPM30		"ClientPrinter"


/*
 * Mac Printer entries
 */

/* DPP 9/5/96 - support for turning on TcpNodelay */
#define INI_TCPNODELAY  "TcpNoDelay"
#define DEF_TCPNODELAY  FALSE

/*=============================================================================
 ==   String typedefs (string length + 1 for NULL terminator)
 ============================================================================*/

#define WFENG_NUM_HOTKEYS		 (10+WFENG_NUM_JAPANESE_HOTKEYS)

#define KEYBOARDMAPPINGFILE_LENGTH	80
#define KEYBOARDDESCRIPTION_LENGTH 	80

typedef CHAR KEYBOARDMAPPINGFILE[ KEYBOARDMAPPINGFILE_LENGTH + 1 ];
typedef CHAR KEYBOARDDESCRIPTION[ KEYBOARDDESCRIPTION_LENGTH + 1 ];

/*============================================================================
 ===  Used for the com port device specification feature on prefs form
 ===========================================================================*/                              
#define MAX_COM_PORTS	64

/*============================================================================
 ===  Used for the business recovery feature added to server list 
 ===========================================================================*/                              
#define MAX_BROWSERADDRESSLIST		15	/* max number of servers and seperators in the server address list */
#define SERVERS_IN_GROUP		5
#define MAX_BROWSER_GROUPS		(MAX_BROWSERADDRESSLIST/SERVERS_IN_GROUP)	/* number of browser group names */

/*
 * Drive Mapping keys - each should have the drive letter appended, eg DriveEnabledA,
 * DriveReadAccessB
 */
#define INI_DRIVE_RW_YES		0		/* Can read/write */
#define INI_DRIVE_RW_NO			1		/* Can't read/write */
#define INI_CDM_MAX_DRIVES		26	/* Max number of drives 'A' - 'Z' */

/* 
 * Com Port Mapping User Definable Settings
 * 
 */

#define INI_COMPORTCOUNT	"LastComPortNum"
#define INI_COMPORTDEVICE	"ComPort"

#define INI_CCM_COMPORT_STEM INI_COMPORTDEVICE 
#define NULL_CCM_COMPORT      ""
#define INI_CCM_LAST_PORTNO INI_COMPORTCOUNT 
#define DEF_CCM_LAST_PORTNO 0	

/*=============================================================================
 ==   Protocol Driver INI keys (INI_) and defaults (DEF_)
 ============================================================================*/

#define INI_PROTOCOL_SUPPORT  "ProtocolSupport"

/* INI file names for built-in PDs */

#define INI_PDFRAME	"Framing"
#define INI_PDCRYPT	"Encrypt"
#define INI_PDRC5   "EncRC5"    /* RSA encryption PD module section */
#define INI_PDRELI	"Reliable"
#define INI_PDRFRAME	"RFrame"
#define INI_PDMODEM	"Modem"
#define INI_PDCOMPR	"Compress"
#define INI_PDOEMFLTR	"OemFilter"
#define INI_PDOEMCONN	"OemConnect"

/* Should go in main tree kbdapi.h */

/* codes for LED mask. These are as they appear in the PACKET_SET_LED ICA command */
#define CAPS_LOCK_LED 		0x40
#define CAPS_LOCK_SHIFT		6
#define NUM_LOCK_LED		0x20
#define NUM_LOCK_SHIFT		5
#define SCROLL_LOCK_LED		0x10
#define SCROLL_LOCK_SHIFT	4

#define ALL_LEDS (CAPS_LOCK_LED|NUM_LOCK_LED|SCROLL_LOCK_LED)


/* Should be cdmapi.h */

/*
	CDM Find data
*/

#define MAX_WIN_LONGNAME_PATH	256
#define MAX_WIN_ALTERNATE_PATH	14
#define LENGTH_8_DOT_3			12

/* Should be ccmwire.h */

/* Ini section names for default port settings active when the port is opened.	*/
/* Default port settings are defined in terms of CCM base constants.			*/

#define INI_CCM_DATABITS		"SerialDefaultDataBits"
#define DEF_CCM_DATABITS		CCM_DEFAULT_DATABITS

#define INI_CCM_STOPBITS		"SerialDefaultStopBits"
#define DEF_CCM_STOPBITS		CCM_DEFAULT_STOPBITS

#define INI_CCM_PARITY			"SerialDefaultParity"
#define DEF_CCM_PARITY			CCM_DEFAULT_PARITY

#define INI_CCM_BAUD			"SerialDefaultBaud"
#define DEF_CCM_BAUD			CCM_DEFAULT_BAUD

#define INI_CCM_TXQUEUESIZE		"SerialDefaultTxQueueSize"
#define DEF_CCM_TXQUEUESIZE		CCM_DEFAULT_TXQUEUESIZE

#define INI_CCM_RXQUEUESIZE		"SerialDefaultRxQueueSize"
#define DEF_CCM_RXQUEUESIZE		CCM_DEFAULT_RXQUEUESIZE

#define INI_CCM_HANDSHAKE		"SerialDefaultHandshake"
#define DEF_CCM_HANDSHAKE		CCM_DEFAULT_HANDSHAKE

#define INI_CCM_FLOWREPLACE		"SerialDefaultFlowReplace"
#define DEF_CCM_FLOWREPLACE		CCM_DEFAULT_FLOWREPLACE

#define INI_CCM_XONLIMIT		"SerialDefaultXonLimit"
#define DEF_CCM_XONLIMIT		CCM_DEFAULT_XONLIMIT

#define INI_CCM_XOFFLIMIT		"SerialDefaultXoffLimit"
#define DEF_CCM_XOFFLIMIT		CCM_DEFAULT_XOFFLIMIT

#define INI_CCM_XON				"SerialDefaultXonChar"
#define DEF_CCM_XON				CCM_DEFAULT_XON

#define INI_CCM_XOFF			"SerialDefaultXoffChar"
#define DEF_CCM_XOFF			CCM_DEFAULT_XOFF


/*=============================================================================
 ==  Configuration INI keys (INI_) and defaults (DEF_)
 ============================================================================*/

#define INI_NAMERESOLVER      "NameResolver"
#define INI_NAMERESOLVERW     "NameResolverWeb"

#define INI_DRIVERNAME		  "DriverName"
#define INI_REDUCER		 	  "Reducer"

#define INI_WDTYPE            "WinStationDriver"
#define DEF_WDTYPE            INI_ICA30

#define MAX_INI_LINE    	270 // Used to be 256 in some places and 256 in others
#define MAX_INI_LINE_UTF8	MAX_INI_LINE * 4	// UTF-8 worst case scenario is 4-bytes for a single character

#define MAXFILEPATH 		255		/* Used by CSM */

#define INI_PCKEYBOARDTYPE  "KeyboardType"
#define DEF_PCKEYBOARDTYPE  "(Default)"

#define INI_INTERFACEPORT	"InterfacePort"  /* Used by CSM */
#define DEF_INTERFACEPORT   0				 /* Used by CSM */

#define INI_INTERFACEADDRESS  "InterfaceAddress"  /* Used by CSM */
#define DEF_INTERFACEADDRESS  ""				  /* Used by CSM */

#define HOT_KEY1	0		/* Used by CSM */
#define HOT_KEY2	1		/* Used by CSM */
#define HOT_KEY3	2		/* Used by CSM */
#define HOT_KEY4	3		/* Used by CSM */
#define HOT_KEY5	4		/* Used by CSM */
#define HOT_KEY6	5		/* Used by CSM */
#define HOT_KEY7	6		/* Used by CSM */
#define HOT_KEY8	7		/* Used by CSM */
#define HOT_KEY9	8		/* Used by CSM */
#define HOT_KEY10	9		/* Used by CSM */
#define HOT_KEY11	10		/* Used by CSM */
#define HOT_KEY12	11		/* Used by CSM */
#define HOT_KEY13	12		/* Used by CSM */
#define HOT_KEY14	13		/* Used by CSM */
#define HOT_KEY15	14		/* Used by CSM */

#define INI_USE_KOTOERI_SHORTCUTS   "UseKotoeriShortcuts"
#define DEF_USE_KOTOERI_SHORTCUTS   FALSE

#define INI_USE_JAPANESE_HOTKEYS   "EnableJapaneseHotkeys"
#define DEF_USE_JAPANESE_HOTKEYS   FALSE

#define INI_ADD_KOTOERI_MENU        "AddHotkeyMenu"
#define DEF_ADD_KOTOERI_MENU        FALSE

#define INI_SPLASHDELAY	    "SplashDelay"	/* Used by CSM */
#define DEF_SPLASHDELAY	    2				/* Used by CSM */

/*
 * file associations
 */
#define INI_FILETYPE			"FileType"
#define DEF_FILETYPE			""


/* Mac Smart Card VD entries */
#define INI_PCSC_LIBRARY_NAME           "PCSCLibraryName"
#define DEF_PCSC_LIBRARY_NAME           "libpcsclite.so"
#define INI_PCSC_CODEPAGE               "PCSCCodePage"
#define DEF_PCSC_CODEPAGE               0


#define VD__COUNT VDxCOUNT

/* Unsupported browser error */

#define BR_ERROR_CLUSTER_LOCATE 8L

/* Needed to compile ZLC */

#define CALLBACK
#define MAKELONG(a, b) ((LONG) (a) | ((LONG) (b) << 16))

/* Copied from wingdi.h */


#define TWI_BI_RGB 0

typedef struct tagBITMAPINFOHEADER
{
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER;
typedef BITMAPINFOHEADER*      PBITMAPINFOHEADER;
typedef BITMAPINFOHEADER * LPBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
   BYTE   	rgbBlue;
   BYTE   	rgbGreen;
   BYTE   	rgbRed;
   BYTE   	rgbReserved;
} RGBQUAD, *LPRGBQUAD;

#define HBRUSH HANDLE

/* taken from the unix platfix.h */
#define LOBYTE(x)	(x & 0xff)
#define HIBYTE(x)	((x >> 8) & 0xff)

#define TEXT( string) string

/* Macros to enable code coverage checking. ENABLE_CODE_COVERAGE should only be defined during
 * development, and a function CodeCoverage must be available somewhere. Any uses of the macro
 * CODECOVERAGE should be removed once code is debugged. To use: CODECOVERAGE (FALSE, "text") 
 * will stop on the first call. CODECOVERAGE (TRUE, "text") will _not_ stop; this makes it possible
 * to keep locations where you might want code coverage in the source code, but disabled. */
#if ENABLE_CODE_COVERAGE
	#undef CODECOVERAGE
	#define CODECOVERAGE(covered, ident) do { static IBOOL coverage = covered;		\
											  CodeCoverage (ident, &coverage); }	\
										while (0)

	extern void CodeCoverage (char* ident, IBOOL* coverage); 
#endif /* ENABLE_CODE_COVERAGE */

/* Macros to enable checking for situations that will cause a connection failure. 
 * DEBUG_CONNECTION_FAILURES should only be defined during development, and a function 
 * ConnectionFailure must be available somewhere. To use: CONNECTIONFAILURE (FALSE, "text") 
 * will stop on the first call. CONNECTIONFAILURE (TRUE, "text") will _not_ stop; this makes it
 * possible to keep locations where you might want to check for connection failures in the source
 * code, but disabled. */
#if DEBUG_CONNECTION_FAILURES
	#undef CONNECTIONFAILURE
	#define CONNECTIONFAILURE(covered, ident) 													\
		do {																					\
			static IBOOL coverage = covered;													\
			TRACE (TC_RECONNECT, TT_API1, "Connection failed or going to fail");				\
			ConnectionFailure (ident, &coverage); }												\
	  while (0)

	extern void ConnectionFailure (char* ident, IBOOL* coverage); 
#endif /* DEBUG_CONNECTION_FAILURES */

extern const char *GetMacICAClientVersion(void);
#undef VER_CLIENTVERSION_STR
#define VER_CLIENTVERSION_STR GetMacICAClientVersion()


/*
 *----------------------------------------------------------------------------
 *  UNIFICATION : End                     
 *----------------------------------------------------------------------------
 */
 
#endif /* _MAC_PLAT_FIX_H_ */
