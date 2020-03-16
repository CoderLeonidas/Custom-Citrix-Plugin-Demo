/***************************************************************************
*
*  IcaCaps.h
*
*  This module contains ICA capability definitions
*
*  Copyright 1998 - 2015 Citrix Systems, Inc. All Rights Reserved.
*
*  This File describes the structure of the various capability blocks which are
*  used to negotiate capabilities between All hosts and clients.
*
****************************************************************************/

#ifndef __ICACAPS_H__
#define __ICACAPS_H__


/*

Capability Blocks and Lists
---------------------------

Each capability block is self contained and contains enough data to completely
describe the setup of the capability. Capabilities are passed between host
and client in capability lists.

CapabilityList:

c1 - More data indicator ( set if data is broken into multiple packets )
c2 - capability block count (0-255)
c3 - Offset to first capability block (low byte)
c4 - Offset to first capability block (high byte)
cn - list of capability blocks


Capability Block:

c1 - capability signature (low byte)
c2 - capability signature (high byte)
c3 - byte count
cn - variable length capability data (0 - 255 bytes)


Hosts Statement of capabilities
-------------------------------

The host will send over a statement of capabilities tagged onto the end of the
INIT_REQUEST packet. This will be in the form of capability list:

If the capability data is greater than 255 bytes then the capability should
be broken into two capabilities.

. The host will initialise and send only those capabilities it can offer.

. The client will look for only those capabilities it is interested in,
  ignoring those it does not recognise.


Module Negotiation of capabilities
----------------------------------

The module C2H/H2C method of negotiation has been extended to support
capability blocks. These capability blocks
will be added to the end of the INIT_RESPONSE and INIT_CONNECT packets as
capability lists.

For each module:

1. The client, using capability information sent from the host, will put together
a list of capabilities it requests. These are sent as a capability list at
the end of the C2H structure.

2. The host will process capability blocks as follows:
∑ If it does not recognise the signature it will ignore it.
∑ If it recognises the signature but does not want to support the client
  it will ignore the capability.
∑ If it recognises the signature and wants to support the capability it
  will make any minor adjustments to the details of the block and add it to
  the list of agreed capabilities. These are sent back as a capability list
  at the end of the H2C structure.

3. The client will read the agreed contract and process them as required.



Parallel development of capabilities
------------------------------------

The process of capability development can then be done in two stages:
1. Claim a signature supplying a name and a description, this is done by
   adding an entry in the signatures section of IcaCaps.h.
   No details of the data structure is needed at this point but it will inform
   other groups that there is work in progress.

2. Submit the Capability block structure once the work is completed.

Only those hosts/clients which have been programmed to understand the new
capability will use it. All others will ignore the unknown signature.


*****************************************************************************/


/* Capability signatures */

/* Capability Example Code
#define CAPABILITY_USHORTX2 1
#define CAPABILITY_APPENDED_DATA 2
*/

/*
 * MTU
 *
 * Definitions for TD Maximum Transition Unit determination.  If
 * this is supplied by the server then the client may attempt to
 * determine its own MTU and resize its buffers accordingly.  No
 * associated data, just a Boolean switch indicated by presence
 * or absence.
 */

#define CAPABILITY_MTU                  1

#define CAPABILITY_REDUCERS_SUPPORTED   2

/*
 * Seamless 2.0 client need to know before hand certain features
 * availability.
 */

#define CAPABILITY_SEAMLESS             3

/*
 * Intellimouse support - the server can support wheel messages and X1/X2
 * button data
 */

#define CAPABILITY_INTELLIMOUSE         4

/*
    Virtual Channel Packet Priority support - the server can send the priority
    for VCs
*/

#define CAPABILITY_PACKET_PRIORITY      5

/*
 * Ica Channel Monitoring support
 */

#define CAPABILITY_CHANNEL_MONITORING   6



/*
   Ica redraw packet feature support

   The server can support redraw resolution up to 64k * 64k.

   The REDRAW_CAP_EXTENDED_REDRAW flag indicates that
   the server supports PACKET_REDRAW_EXTENDED.

   The REDRAW_CAP_COMPLEX_REGION flag indicates that
   the server supports complex region redraws.

   This capability can be extended in the future to
   support other redraw packets
 */

#define CAPABILITY_REDRAW               7

#define CAPABILITY_TIME_ZONE            8

#define CAPABILITY_LONG_UNICODE_USERNAME_SUPPORT 9

/*
 *  Signals that PACKET_COOKIE is supported
 */
#define CAPABILITY_COOKIE               10


/*
 * Signale that Printer bandwidth control is suport4ed by host
 * If server support that - client can enable high speed printing, 
 * knowing the server would make sure the high bandwidth usage would not kill useabilty
 * If the server is old server that do not have support for that - the client would use 
 * limited bandwidth for printing
 */
#define CAPABILITY_PRT_BW_CTRL          11

#define CAPABILITY_TW2PERSISTENT_CACHE_DEADLOCK_BUG_FIXED 12

#define CAPABILITY_SERVER_VERSION       13

#define CAPABILITY_KEYBOARD_XKEYSYM     14

#define CAPABILITY_CGP_PACKET_OVERHEAD  15

#define CAPABILITY_HIGH_THROUGHPUT      16

#define CAPABILITY_SSL_PACKET_OVERHEAD  17

#define CAPABILITY_WD_CREDENTIAL_PASSING  18

#define CAPABILITY_MAX_VIDEO  19

#define CAPABILITY_EUKS 20

#define CAPABILITY_DRIVE_MAPPING_ACCELERATION  25           /* temporary alpha value was 997 (do not reuse) */

#define CAPABILITY_DYNAMIC_TIME_ZONE 38

/* General defines */
#define FIRST_CAP_OFFSET 4  /* offset from start of capability list to first cap block */
#define MAX_CAPS_IN_LIST 255 /* maximum number of capability blocks per list */
#define MAX_BYTES_INIT_REQUEST_PACKET 255 /* maximum size of the INIT_REQUEST packet */


/* Headers etc */

/* Capability Example Code
typedef struct _CAP_USHORTX2 {
    CAP_HEAD head;
    USHORT item1;
    USHORT item2;
} CAP_USHORTX2, *PCAP_USHORTX2;

typedef struct _CAP_APPENDED_DATA {
    CAP_HEAD head;
    USHORT stringLength;
    USHORT oString;
    USHORT intCount;
    USHORT oIntList;
} CAP_APPENDED_DATA, *PCAP_APPENDED_DATA;
*/

typedef struct _CAP_HEAD {
    USHORT byteCount;
    USHORT signature;
} CAP_HEAD, *PCAP_HEAD;

/* Capability block definitions */

typedef struct _CAP_KEYBOARD_XKEYSYM
{
    CAP_HEAD        head;
    BYTE            version;    /* paranoia */
} CAP_KEYBOARD_XKEYSYM, *PCAP_KEYBOARD_XKEYSYM ;

typedef struct _CAP_REDUCERS_SUPPORTED {
    CAP_HEAD head;
    USHORT reducersSupportedMask;
} CAP_REDUCERS_SUPPORTED, *PCAP_REDUCERS_SUPPORTED;

typedef struct _CAP_SEAMLESS {
    CAP_HEAD head;
    ULONG    seamlessFeaturesMask;
} CAP_SEAMLESS, *PCAP_SEAMLESS;


typedef struct _CAP_INTELLIMOUSE_SUPPORTED
{
    CAP_HEAD head;
    USHORT intellimouseFeaturesMask;
} CAP_INTELLIMOUSE, *PCAP_INTELLIMOUSE;

typedef struct _CAP_CHANNEL_MONITORING
{
    CAP_HEAD head;

    USHORT   Version;
    USHORT   RepeatDelay;
    ULONG    Flags;
    USHORT   MouseThresholdUpperLimit;
    USHORT   MouseThresholdLowerLimit;
} CAP_CHANNEL_MONITORING, *PCAP_CHANNEL_MONITORING;

#define ICM_MODE_FLAG_ENABLE_BM             2
#define ICM_MODE_FLAG_SHOW_MOUSE_FEEDBACK   4

/*
 *  Seamless 2.0 Features bits:
 */

#define SEAMLESS_CAP_SLOGON             1       /* Seamless logon */

/*  These feature bits are reserved, but not in use at the moment */

#define SEAMLESS_CAP_DEFERRED_UPDATE    2       /* Deferred update mode */
#define SEAMLESS_CAP_BALANCE_NC         4       /* Balance non-client settings */
#define SEAMLESS_CAP_NC_PREDICTION      8       /* Speculative redraw of non-client areas */
#define SEAMLESS_CAP_ZERO_LATENCY1     16       /* Zero-latency support, V1 */


/*
 * Intellimous Feature bits:
 */

#define INTELLIMOUSE_CAP_WHEEL          0x0001
#define INTELLIMOUSE_CAP_X1             0x0002
#define INTELLIMOUSE_CAP_X2             0x0004



/*
 * Structure to send virtual channel packet priorities
 */
#ifndef ZERO_ARRAY_LENGTH
#define ZERO_ARRAY_LENGTH
#endif
typedef struct _CAP_PACKET_PRIORITY {
    CAP_HEAD head;
    ULONG PriorityOffset;
    USHORT ArrayLength;
    BYTE fUseLowestPriority;
} CAP_PACKET_PRIORITY, *PCAP_PACKET_PRIORITY;


/*
 * Redraw capability definitions
 */
typedef struct _CAP_REDRAW
{
    CAP_HEAD head;
    USHORT redrawCapsMask;
} CAP_REDRAW, *PCAP_REDRAW;

/*
 * Redraw capability bits:
 */

#define REDRAW_CAP_EXTENDED_REDRAW      0x0001
#define REDRAW_CAP_COMPLEX_REGION       0x0002

struct _DateTime {
    USHORT Year;
    USHORT Month;
    USHORT DayOfWeek;
    USHORT Day;
    USHORT Hour;
    USHORT Minute;
    USHORT Second;
    USHORT Milliseconds;
};

/*
 * Structure to send the time zone info
 */
typedef struct _CAP_TIME_ZONE_INFO {
    CAP_HEAD head;
    ULONG    Version;
    ULONG    OperatingMode;
#define TIME_ZONE_MODE_STANDARD   1
#define TIME_ZONE_MODE_DAYLIGHT   2

    LONG     Bias;

    USHORT   oStandardName;
    struct _DateTime StandardDate;

    LONG     StandardBias;

    USHORT   oDaylightName;
    struct _DateTime DaylightDate;
    LONG     DaylightBias;
    USHORT   EncodingType;  /* 0 for ANSI; 1 for UNICODE */
    USHORT   EncodingData;  /* CodePage info.. */
} CAP_TIME_ZONE_INFO, *PCAP_TIME_ZONE_INFO;

/*
Below is explanation of all the fields in the above structure
===============================================================
Version
Specifies the version number of this capability struture.

OperatingMode
Specifies whether the zone is currently operating under Standard or Daylight time.
  - TIME_ZONE_MODE_STANDARD means the system is currently operating in Standard mode
  - TIME_ZONE_MODE_DAYLIGHT means the system is currently operating in Daylight mode

Bias
Specifies the current bias, in minutes, for local time translation on this
computer. The bias is the difference, in minutes, between Coordinated Universal
Time (UTC) and local time. All translations between UTC and local time are
based on the following formula:

UTC = local time + bias

This member is required.

oStandardName
This is the offset to the null terminated string that contains the name of the
time zone in standard mode. This string can be empty.

StandardDate
Specifies a _DateTime structure that contains a date and local time when the
transition from daylight time to standard time occurs on this operating system.
If this date is not specified, the wMonth member in the structure must be zero.
If this date is specified, the DaylightDate value in the CAP_PACKET_TIME_ZONE
structure must also be specified. This member supports two date formats.
Absolute format specifies an exact date and time when standard time begins.
In this form, the wYear, wMonth, wDay, wHour, wMinute, wSecond, and wMilliseconds
members of the _DateTime structure are used to specify an exact date.

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

oDaylightName
This is the offset to the null terminated string that contains the name of the
time zone in daylight mode. This string can be empty.

DaylightDate
Specifies a _DateTime structure that contains a date and local time when
the transition from standard time to daylight time occurs on this operating
system. If this date is not specified, the wMonth member in the _DateTime
structure must be zero. If this date is specified, the TimeZoneStandardDate value in
the CAP_PACKET_TIME_ZONE structure must also be specified. This member supports
the absolute and day-in-month time formats described for the StandardDate member.

DaylightBias
Specifies a bias value to be used during local time translations that occur
during daylight time. This member is ignored if a value for the TimeZoneDaylightDate
member is not supplied. This value is added to the value of the Bias member
to form the bias used during daylight time. In most time zones, the value
of this member is -60.

EncodingType
The encoding type for the strings that are sent through this capability packet.
It is 0 for ANSI/ASCII and 1 for UNICODE. Currently, the Standard name and the
Daylight Name are the only strings that are sent.

EncodingData
If the encoding type for the strings that are sent in this packet is ASCII
then the code page of the system should be set in this field.
*/

/* Structure to hold the complete capability: the strings are assumed
 * to be no more that 64 bytes long.
 */

typedef struct {
    CAP_TIME_ZONE_INFO  tz_cap;
    char                strings[128];
} CAP_TIME_ZONE_INFO_COMPLETE;


#define TIME_ZONE_KEY_NAME	1
#define IETF_TIME_ZONE_NAME	2


typedef struct _CAP_DYNAMIC_TIME_ZONE_INFO
{
    CAP_HEAD head;
    ULONG    Version;
    ULONG    OperatingMode;
#define TIME_ZONE_MODE_STANDARD   1
#define TIME_ZONE_MODE_DAYLIGHT   2
    
    LONG     Bias;
    
    USHORT   oStandardName;
    struct _DateTime StandardDate;
    LONG     StandardBias;
    
    USHORT   oDaylightName;
    struct _DateTime DaylightDate;
    LONG     DaylightBias;
    
    USHORT   TimeZoneNameType;
    USHORT   oTimeZoneName;
    USHORT   DynamicDaylightTimeDisabled;
    
    USHORT   EncodingType;                  /* 0 for UTF-8; 1 for UTF-16 */
} CAP_DYNAMIC_TIME_ZONE_INFO, *PCAP_DYNAMIC_TIME_ZONE_INFO;
/*
 Below is an explanation of all the fields in the above structure.
 Version. Specifies the version number of this capability structure.
 OperatingMode. Specifies whether the zone is currently operating under standard or daylight savings time.
 TIME_ZONE_MODE_STANDARD means the system is currently operating in standard mode.
 TIME_ZONE_MODE_DAYLIGHT means the system is currently operating in daylight savings mode.
 Bias. Specifies the current bias, in minutes, for local time translation on this computer. The bias is the difference, in minutes, between Coordinated Universal Time (UTC) and local time. All translations between UTC and local time are based on the following formula:
 UTC = local time + bias
 This member is required.
 oStandardName. This is the offset to the null-terminated string that contains the name of the time zone in standard mode. This string can be empty.
 StandardDate. Specifies a _DateTime structure that contains a date and local time when the transition from daylight savings time to standard time occurs on this operating system. If this date is not specified, the wMonth member in the structure must be zero. If this date is specified, the DaylightDate value in the CAP_DYNAMIC_TIME_ZONE_INFO structure must also be specified. This member supports two date formats. Absolute format specifies an exact date and time when standard time begins. In this form, the wYear, wMonth, wDay, wHour, wMinute, wSecond, and wMilliseconds members of the _DateTime structure are used to specify an exact date. Day-in-month format sets the wYear member to zero, sets the wDayOfWeek member to an appropriate weekday, and uses a wDay value in the range 1 through 5 to select the correct day in the month. Using this notation, the first Sunday in April can be specified, as can the last Thursday in October (5 is equal to “the last”).
 StandardBias. Specifies a bias value to be used during local time translations that occur during standard time. This member is ignored if a value for the StandardDate member is not supplied. This value is added to the value of the Bias member to form the bias used during standard time. In most time zones, the value of this member is zero.
 oDaylightName. This is the offset to the null terminated string that contains the name of the time zone in daylight mode. This string can be empty.
 DaylightDate. Specifies a _DateTime structure that contains a date and local time when the transition from standard time to daylight savings time occurs on this operating system. If this date is not specified, the wMonth member in the _DateTime structure must be zero. If this date is specified, the StandardDate value in the CAP_DYNAMIC_TIME_ZONE_INFO structure must also be specified. This member supports the absolute and day-in-month time formats described for the StandardDate member.
 DaylightBias. Specifies a bias value to be used during local time translations that occur during daylight savings time. This member is ignored if a value for the TimeZoneDaylightDate member is not supplied. This value is added to the value of the Bias member to form the bias used during daylight savings time. In most time zones, the value of this member is –60.
 TimeZoneNameType: Client sets this member to indicate the type of time zone name saved in TimeZoneName. It is 1 for Windows time zone key name and 2 for IETF time zone name. Server sets this member to indicate the time zone name types that are supported on server and the value is a combination of the supported time zone name type flags. For example, if server supports both Windows time zone key name and IETF time zone name, server needs to set this member to 3. Currently, only Windows time zone key name is implemented and supported by server.
 
 #define TIME_ZONE_KEY_NAME	1	Windows time zone key name
 #define IETF_TIME_ZONE_NAME	2	IETF time zone name
 
 oTimeZoneName. This is the offset to the null terminated string that contains the time zone name.
 DynamicDaylightTimeDisabled. Specifies whether dynamic daylight saving time is disabled. Setting this member to TRUE disables dynamic daylight saving time, causing the system to use a fixed set of transition dates.
 EncodingType. The encoding type for the strings that are sent through this capability packet. It is zero for UTF-8 and one for UTF-16. Currently, the StandardName, the DaylightName and the TimeZoneName are the only strings that are sent.
 */

typedef struct {
    CAP_DYNAMIC_TIME_ZONE_INFO  tz_cap;
    char                strings[128];
} CAP_DYNAMIC_TIME_ZONE_INFO_COMPLETE;

/*
 * Long Unicode Username capability definitions
 */
typedef struct _CAP_LONG_UNICODE_USERNAME_SUPPORT
{
    CAP_HEAD head;
} CAP_LONG_UNICODE_USERNAME_SUPPORT, *PCAP_LONG_UNICODE_USERNAME_SUPPORT;


/*
 *  Indicates support for PACKET_COOKIE
 */
typedef struct _CAP_COOKIE
{
    CAP_HEAD head;
    BYTE Version; /* paranoia */
    USHORT MaxCookieSize;
} CAP_COOKIE, * PCAP_COOKIE;

#define CAP_COOKIE_VERSION      1


/*
 * Printer Bandwidht control support on host
 */
typedef struct _CAP_PRT_BW_CTRL
{
    CAP_HEAD head;
} CAP_PRT_BW_CTRL, *PCAP_PRT_BW_CTRL;


/*
 * Capability to indicate that the server has the TW2 persistent cache dealock
 * bug fixed.
 */
typedef struct _CAP_TW2PERSISTENT_CACHE_DEADLOCK_BUG_FIXED
{
    CAP_HEAD head;
} CAP_TW2PERSISTENT_CACHE_DEADLOCK_BUG_FIXED, *PCAP_TW2PERSISTENT_CACHE_DEADLOCK_BUG_FIXED;


/* This capability is sent only in the direction of client to server */
typedef struct _CAP_CGP_PACKET_OVERHEAD {
    CAP_HEAD head;
    USHORT Version;             /* = 1 for the first version */
    ULONG CGPPacketOverhead;    /* zero if CGP is not being used */
    ULONG CGPSession;           /* session token for IMA/XTE 
                                 * communication -- future use */
} CAP_CGP_PACKET_OVERHEAD, *PCAP_CGP_PACKET_OVERHEAD;


/*
 * Capability to indicate that the sending WD supports the high throughput capability
 * This implies bandwidth measurement, large (interruptible) virtual writes, and 
 * output packet rate-limitation, etc. 
 */

#define SUPPORT_HIGH_THROUGHPUT_CDM     0x1     /* channel can support high sizes for CDM */
#define SUPPORT_HIGH_THROUGHPUT_CPM     0x2     /* channel can support high sizes for CPM */
/*
 * High throughput resets properly on a TERMINATE disconnect packet, this
 * indicates that no High Throughput header bytes are sent after a  Terminate
 * Ack is sent. Without this flag header bytes are still sent following Terminate
 * Ack.
 */
#define SUPPORT_HIGH_THROUGHPUT_DISCRST 0x4
#define SUPPORT_HIGH_THROUGHPUT_PACKET_INTEGRITY_CHECKS 0x8

typedef struct _CAP_HIGH_THROUGHPUT
{
    CAP_HEAD head;
    ULONG    supportMask;           /* channels that support high throughput - does not use normal channel numbering */
    USHORT   MaxICAPacketLength;    /* cap packet lengths at this, 0 = no cap */
    USHORT   LineLoadingPercent;    /* output relative to line speed estimate, 100 = neutral, 0 = use default */ 
} CAP_HIGH_THROUGHPUT, *PCAP_HIGH_THROUGHPUT;


/* This capability is sent only in the direction of client to server */
typedef struct _CAP_SSL_PACKET_OVERHEAD
{
    CAP_HEAD head;
    USHORT   SSLPacketOverhead;   /* zero if SLL is not being used */
} CAP_SSL_PACKET_OVERHEAD, *PCAP_SSL_PACKET_OVERHEAD;

/*
 *  Server version information
 */
typedef struct _CAP_SERVER_VERSION
{
    CAP_HEAD head;

    USHORT ServerFamily;

#define SERVER_FAMILY_WINDOWS            0x0001
#define SERVER_FAMILY_UNIX               0x0002

    USHORT ServerFamilyVersion;
        
#define SERVER_FAMILY_WINDOWS_XP10FR1    0x0001 /* only for ServerFamily == SERVER_FAMILY_WINDOWS */
#define SERVER_FAMILY_WINDOWS_XP10FR2    0x0002 /* only for ServerFamily == SERVER_FAMILY_WINDOWS */
#define SERVER_FAMILY_UNIX_1x1_FR1       0x0001 /* only for ServerFamily == SERVER_FAMILY_UNIX */

    USHORT ServerVariant;
       
#define SERVER_VARIANT_TSE               0x0001 /* only for ServerFamily == SERVER_FAMILY_WINDOWS */
#define SERVER_VARIANT_WIN2K             0x0002 /* only for ServerFamily == SERVER_FAMILY_WINDOWS */
#define SERVER_VARIANT_SOLARIS_INTEL     0x8001 /* only for ServerFamily == SERVER_FAMILY_UNIX */
#define SERVER_VARIANT_SOLARIS_SPARC     0x8002 /* only for ServerFamily == SERVER_FAMILY_UNIX */
#define SERVER_VARIANT_AIX               0x8003 /* only for ServerFamily == SERVER_FAMILY_UNIX */
#define SERVER_VARIANT_HPUX              0x8004 /* only for ServerFamily == SERVER_FAMILY_UNIX */
#define SERVER_VARIANT_LINUX             0x8005 /* only for ServerFamily == SERVER_FAMILY_UNIX */

} CAP_SERVER_VERSION, *PCAP_SERVER_VERSION;

/*
 * Server capability to send credentials in an enctypted WD packet
 */
typedef struct _CAP_WD_CREDENTIAL_PASSING
{
    CAP_HEAD head;
    BYTE version; /* for Future Use */
} CAP_WD_CREDENTIAL_PASSING, *PCAP_WD_CREDENTIAL_PASSING;

typedef struct _CAP_MAX_VIDEO
{
    CAP_HEAD head;
    ULONG MaxServerLVBMem;
    BYTE  DegradeColorFirst; /* If TRUE, degrade color first, if FALSE, degrade resolution first */
} CAP_MAX_VIDEO, *PCAP_MAX_VIDEO;


/*
 * Extended Unicode Keyboard Support Capability block
 * 
 *  This capability is sent from the host to the client to inform the client that the host 
 *  has Extended Unicode Keyboard Support (EUKS) feature.
 *  If this bit is valid, client can make use of Unicode-Injection flag , that is, 
 *  0x4 for Byte 1 of PACKET_ALT_KEYBOARD2 packet. Version flag tells the client version of EUKS feature.
 *
 *  Mode flag notifies the server of various options that server make use of.   0 = default.
 */

typedef struct _CAP_EUKS
{
    CAP_HEAD head;
    USHORT Version; /* = 1 for the first version of EUKS*/
    USHORT Mode;  /* tells the server to enable EUKS */
}CAP_EUKS, * PCAP_EUKS;

#define READ_AHEAD_V1_SUPPORTED		0x1
#define ASYNC_WRITES_V1_SUPPORTED	0x2
#define DIR_CACHING_V1_SUPPORTED    0x4

typedef struct _CAP_DRIVE_MAPPING_ACCELERATION
{
    CAP_HEAD head;
    USHORT   FeaturesSupported;   /* bitmask from above values */
    USHORT   TotalMaxReadAheadK;  /* maximum amount in units of 1024 that can be read ahead */
    
}CAP_DRIVE_MAPPING_ACCELERATION, *PCAP_DRIVE_MAPPING_ACCELERATION;

#endif  /* __ICACAPS_H__ */

