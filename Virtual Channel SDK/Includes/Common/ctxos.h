/*******************************************************************************
 *
 *  CTXOS.h
 *
 *  Operating System Platform Abstractions
 *
 *  Copyright (c) 1998-2015 Citrix Systems, Inc. All Rights Reserved.
 *
 ******************************************************************************/

#ifndef _CTXOS_H_
#define _CTXOS_H_


#include <ctxgraph.h>

/*
 *  Include a potenial platform specific header file.
 */
#include <pctxos.h>

typedef struct _CTXTIME
{
    BYTE hour;          /* The hour of the day (0-23) */
    BYTE minute;        /* The minute of the current hour (0-59) */
    BYTE second;        /* The second of the current minute (0-59) */
    BYTE hsecond;       /* The millisecond of the current minute (0-999) */
}CTXTIME, FAR * PCTXTIME;

typedef struct _CTXDATE
{
    BYTE    day;        /* The day of the current month (1-31)*/
    BYTE    month;      /* The month of the current year (1-12) */
    USHORT  year;       /* The year where year 1999=1999 */
}CTXDATE, FAR * PCTXDATE;

typedef struct _OS_DATETIME {
    UINT16 Year;
    UINT16 Month;
    UINT16 DayOfWeek;
    UINT16 Day;
    UINT16 Hour;
    UINT16 Minute;
    UINT16 Second;
    UINT16 Milliseconds;
} OS_DATETIME, *POS_DATETIME, FAR *LPOS_DATETIME;

typedef struct _OS_TZI {
    UINT32        Version;
    UINT32        OperatingMode;
#define OS_TIME_ZONE_MODE_STANDARD       1
#define OS_TIME_ZONE_MODE_DAYLIGHT       2

    INT32         Bias;
    CHAR          StandardName[ 64 ];
    OS_DATETIME   StandardDate;
    INT32         StandardBias;
    CHAR          DaylightName[ 64 ];
    OS_DATETIME   DaylightDate;
    INT32         DaylightBias;
} OS_TZI, *POS_TZI, FAR *LPOS_TZI;

/*
Below is explanation of all the fields in the above structure
===============================================================
Version
Specifies the version number of this struture. 

OperatingMode
Specifies whether the zone is currently operating under Standard or Daylight time.
  - OS_TIME_ZONE_MODE_STANDARD means the system is currently operating in Standard mode
  - OS_TIME_ZONE_MODE_DAYLIGHT means the system is currently operating in Daylight mode

Bias 
Specifies the current bias, in minutes, for local time translation on this
computer. The bias is the difference, in minutes, between Coordinated Universal
Time (UTC) and local time. All translations between UTC and local time are
based on the following formula: 

UTC = local time + bias 
 
This member is required. 

StandardName
Specifies a null-terminated string associated with the name of time zone
during standard time. This should only be used for information purposes only.  
This string can be be null.

StandardDate 
Specifies a OS_DATETIME structure that contains a date and local time when the
transition from daylight time to standard time occurs on this operating system. 
If this date is not specified, the wMonth member in the structure must be zero.
If this date is specified, the DaylightDate value in the OS_TZI
structure must also be specified. This member supports two date formats. 
Absolute format specifies an exact date and time when standard time begins. 
In this form, the wYear, wMonth, wDay, wHour, wMinute, wSecond, and wMilliseconds
members of the OS_DATETIME structure are used to specify an exact date.

Day-in-month format is specified by setting the wYear member to zero, setting
the wDayOfWeek member to an appropriate weekday, and using a wDay value in the
range 1 through 5 to select the correct day in the month. Using this notation,
the first Sunday in April can be specified, as can the last Thursday in October
(5 is equal to "the last").

StandardBias 
Specifies a bias value to be used during local time translations that occur
during standard time. This member is ignored if a value for the StandardDate
member is not supplied. This value is added to the value of the Bias member
to form the bias used during standard time. In most time zones, the value
of this member is zero. 

DaylightName
Specifies a null-terminated string associated with the name of time zone
during daylight savings time. This should only be used for information purposes only.  
This string can be be null.

DaylightDate 
Specifies a OS_DATETIME structure that contains a date and local time when 
the transition from standard time to daylight time occurs on this operating
system. If this date is not specified, the wMonth member in the OS_DATETIME
structure must be zero. If this date is specified, the StandardDate value in
the OS_TZI structure must also be specified. This member supports
the absolute and day-in-month time formats described for the StandardDate member. 

DaylightBias 
Specifies a bias value to be used during local time translations that occur
during daylight time. This member is ignored if a value for the DaylightDate
member is not supplied. This value is added to the value of the Bias member
to form the bias used during daylight time. In most time zones, the value
of this member is -60.

*/

typedef struct _OS_DTZI {
    UINT32        Version;
    UINT32        OperatingMode;
#define OS_TIME_ZONE_MODE_STANDARD       1
#define OS_TIME_ZONE_MODE_DAYLIGHT       2
    
    INT32         Bias;
    CHAR          StandardName[ 64 ];
    OS_DATETIME   StandardDate;
    INT32         StandardBias;
    CHAR          DaylightName[ 64 ];
    OS_DATETIME   DaylightDate;
    INT32         DaylightBias;
} OS_DTZI, *POS_DTZI, FAR *LPOS_DTZI;


/*
 *  License ID's specified by Microsoft
 */
#ifndef CLIENTLIC_IMAGE_ID_CITRIX
#define CLIENTLIC_IMAGE_ID_CITRIX   0x00010000
#endif
#ifndef CLIENTLIC_OS_ID_OTHER
#define CLIENTLIC_OS_ID_OTHER       0xFF000000
#endif

/*
 *  Below are Operation System Version types that the client may need
 *  to know. Unix platforms should define OS_TYPE_UNIX to be one of
 *  the per-platform Unix values below.
 */
#define OS_TYPE_UNKNOWN    0      /* Windows Unknown */
#define OS_TYPE_WIN16      1      /* Windows (Win32s on 3.1) */
#define OS_TYPE_WINDOWS    2      /* Windows WIN32 */
#define OS_TYPE_WINNT      3      /* Windows NT platform */
#define OS_TYPE_DOS        4      /* DOS */
#define OS_TYPE_MACOS      5      /* MacOS */
#define OS_TYPE_DEC        6	  /* Digital Unix aka Compaq Tru64 Unix */
#define OS_TYPE_HPUX       7	  /* Hewlett Packard HP-UX */
#define OS_TYPE_SUNOS      8	  /* Sun SunOS */
#define OS_TYPE_SOLARIS    9	  /* Sun Solaris */
#define OS_TYPE_SGI        10	  /* Silicon Graphics IRIX */
#define OS_TYPE_RS6000     11	  /* IBM AIX */
#define OS_TYPE_LINUX      12	  /* Linux (Redhat, Caldera, SuSE, Slackware) */
#define OS_TYPE_SCO        13	  /* SCO Systems (UnixWare, OS5) */
#define OS_TYPE_SOLX86     14	  /* Sun Solaris (Intel Platform Edition) */
#define OS_TYPE_LINUXARM   15	  /* Linux ARM */
#define OS_TYPE_NETBSD     16	  /* NetBSD */
#define OS_TYPE_SCO_CMW    17	  /* SCO OpenDesktop 3 and Secureware CMW port */
#define OS_TYPE_OS2        18     /* IBM OS/2 */

/* 
 * Unix platform progression
 */
#define OS_TYPE_UNIX_BASE  OS_TYPE_DEC

/*
 *  Below are arbitrary assignments of macro names to specific operating
 *  system versions associated with an OS_TYPE.  The actual values are not
 *  relevant.  Just the ascending order corresponding to new versions of an OS.
 */

#define OS_VERSION_BASE         0      /* An arbitrary version for an OS */

/*
 * WinNT version progression.
 */
#define OS_VERSION_WINNT351    30
#define OS_VERSION_WINNT40     40
#define OS_VERSION_WINNT50     50

/*
 * Windows 16 bit version progression
 */
#define OS_VERSION_WIN31       10
#define OS_VERSION_WINWKGP     20

/*
 * Windows 32 bit version progression
 */
#define OS_VERSION_WIN95       10
#define OS_VERSION_WIN95OSR2   12
#define OS_VERSION_WIN98       20

/*
 * OS/2 version progression.
 */
#define OS_VERSION_WARP3		10
#define OS_VERSION_WARP4		20

/*
 * DOS version progression
 */
#define OS_VERSION_DOS_BASE     0

/*
 *  Below are potential UI types of the Operating System that the client may
 *  need to know.
 */
#define OS_UI_TYPE_NONE         0
#define OS_UI_TYPE_WIN31        1
#define OS_UI_TYPE_WIN95        2
#define OS_UI_TYPE_PM			3 /* OS/2 Presentation Manager */

/*
 * Status codes from this abstraction
 */
#define OS_STATUS_SUCCESS       0
#define OS_STATUS_NOT_SUPPORTED 1


extern UINT32 _VPAPI Os_GetClientLicenseOsId(VOID);
extern UINT32 _VPAPI Os_GetClientLicenseOemId(VOID);
extern void  _VPAPI Os_GetTime(PCTXTIME);
extern void  _VPAPI Os_GetDate(PCTXDATE);
extern void  _VPAPI Os_Delay(ULONG);
extern UINT32 _VPAPI Os_GetTickCountInMs(VOID);
extern uint64_t Os_GetCurrentEpochTimeInMs (void);
extern void Os_InitProcessCreationTime(void) ;
extern uint64_t Os_GetProcessCreationEpochTimeInMs (void);
extern VPSTATUS _VPAPI Os_getTimeZoneInfo(OS_TZI *ptzi);
extern void GetNewVersionIETFTimeZoneName(char *destinationTimezoneName, const char *originalTimezoneName, int destinationTimeZoneNameLength);
extern IBOOL _VPAPI Os_executeShellCmd(UCHAR *szURL);
extern VPSTATUS _VPAPI Os_getLocalIPAddress(PCHAR, PINT32);
extern VPSTATUS  _VPAPI Os_supportUnicodeInsertion(PIBOOL pbSupported);


// Os_GetMonitorLayout gets a list of all monitors, excluding monitors that don't intersect with
// *pRequiredRect if that pointer is not NULL, and adjusted so that the top left coordinate is at
// (0, 0). 
struct _TW_MONITOR_LAYOUT_INFO;
extern UINT32 Os_GetMonitorLayout(struct _TW_MONITOR_LAYOUT_INFO* *pMonLayout, UINT8 PreferredLaunchMonitor);

#ifdef macintosh
	#define Os_GetOsType()			OS_TYPE_MACOS
	#define Os_GetOsVersion()		OS_VERSION_BASE
	#define Os_getMinorVersion()	0
	#define Os_GetOsUiType()		OS_UI_TYPE_NONE
	#define Os_IsPassThruClient()	FALSE
#else
	extern UINT32 _VPAPI Os_GetOsType(VOID);
	extern UINT32 _VPAPI Os_GetOsVersion(VOID);
	extern UINT32 _VPAPI Os_getMinorVersion(VOID);
	extern UINT32 _VPAPI Os_GetOsUiType(VOID);
	extern UINT32 _VPAPI Os_IsPassThruClient(VOID);
#endif

#endif /* _CTXOS_H_ */

