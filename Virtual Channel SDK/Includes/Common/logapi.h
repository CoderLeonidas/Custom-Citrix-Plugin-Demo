/********************************************************************
*
*  LOGAPI.H
*
*  Header file for Logging and Tracing
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
*********************************************************************/

#ifndef __LOGAPI_H__
#define __LOGAPI_H__

#include "engtypes.h"
#include "ctxdebug.h"

/*
 *  Logging and Tracing flag definitions
 */

//
// Trace classes flags, to be used as first parameter of TRACE
//
#define TC_WD       (((uint64_t) 1) << 1)		// WinStation Driver API
#define TC_RELI     (((uint64_t) 1) << 2)		// Reliable Protocol Driver
#define TC_FRAME    (((uint64_t) 1) << 3)		// Frame Protocol Driver
#define TC_PROXY    (((uint64_t) 1) << 4)		// Proxy Driver
#define TC_PD       (((uint64_t) 1) << 5)		// Protocol Driver
#define TC_TD       (((uint64_t) 1) << 6)		// Transport Driver
#define TC_VD       (((uint64_t) 1) << 7)		// Virtual Driver
#define TC_CDM      (((uint64_t) 1) << 8)		// Client Drive Mapping
#define TC_CPM      (((uint64_t) 1) << 9)		// Client Printer Maping
#define TC_KEY      (((uint64_t) 1) << 10)		// Keyboard
#define TC_MOU      (((uint64_t) 1) << 11)		// Mouse
#define TC_LIB      (((uint64_t) 1) << 12)		// Libraries?
#define TC_CLIP     (((uint64_t) 1) << 13)		// Clipboard
#define TC_RECONNECT (((uint64_t) 1) << 14)		// Reconnecting
#define TC_TW       (((uint64_t) 1) << 15)		// Thinwire + Thinwire1
#define TC_SRCC     (((uint64_t) 1) << 16)		// SRCC
#define TC_WENG     (((uint64_t) 1) << 17)		// Windows Client Engine
#define TC_SCARDVD  (((uint64_t) 1) << 18)		// Smartcard
#define TC_SPB      (((uint64_t) 1) << 19)		// SpeedBrowse
#define TC_NCS      (((uint64_t) 1) << 20)		// NCS
#define TC_WFSHELL  (((uint64_t) 1) << 21)		// WFShell
#define TC_DEVELOP	(((uint64_t) 1) << 22)		// Used while a feature is being developed
// TC_ZLC no longer used. Flag can be reused. 
//#define TC_ZLC      (((uint64_t) 1) << 23)		// Zero Latency
#define TC_TWI      (((uint64_t) 1) << 24)		// Transparent Window Interface
#define TC_MONITORS	(((uint64_t) 1) << 25)		// Anyting related to monitors
#define TC_VP       (((uint64_t) 1) << 26)		// File system
#define TC_CM       (((uint64_t) 1) << 27)		// Cursor Management
#define TC_CCM      (((uint64_t) 1) << 28)		// Client Comms Mapping
// TC_FONT no longer used. Flag can be reused. 
//#define TC_FONT     (((uint64_t) 1) << 29)		// Font handling
#define LOG_ASSERT  (((uint64_t) 1) << 30)		// Always log this class */
#define LOG_CLASS   (((uint64_t) 1) << 31)		// Standard logging class
#define TC_EUEM		(((uint64_t) 1) << 32)		// EUEM support
#define TC_CGP		(((uint64_t) 1) << 33)		// CGP
#define TC_CGPCORE	(((uint64_t) 1) << 34)		// CGP Core
#define TC_TCPPROXY	(((uint64_t) 1) << 35)		// TCP Proxy
#define TC_GUSB		(((uint64_t) 1) << 36)		// Generic USB
#define TC_UDT		(((uint64_t) 1) << 37)		// UDT logs
#define TC_CAM      (((uint64_t) 1) << 38)      // Audio Virtual Channel
#define TC_CTL		(((uint64_t) 1) << 39)		// Control Virtual Channel
#define TC_SSLSDK	(((uint64_t) 1) << 40)		// SSLSDK
#define TC_CTXIME	(((uint64_t) 1) << 41)		// CTXIME
#define TC_NSAP     (((uint64_t) 1) << 42)      // NSAP VC
#define TC_ALL      (~ (uint64_t) 0)

#define TC_TW1		TC_TW						// Intentional synonym


//
// Trace enable flags, to be used as second parameter of TRACE. There are more flags in twh2inch.
//
#define TT_API1         (((uint64_t) 1) << 0)          /* api level 1 */
#define TT_API2         (((uint64_t) 1) << 1)          /* api level 2 */
#define TT_API3         (((uint64_t) 1) << 2)          /* api level 3 */
#define TT_API4         (((uint64_t) 1) << 3)          /* api level 4 */
#define TT_CONFIG       (((uint64_t) 1) << 4)          /* configuration status */
#define TT_CONNECT      (((uint64_t) 1) << 5)          /* connect / disconnect status */
#define TT_OFRAME       (((uint64_t) 1) << 6)          /* outbound frame header */
#define TT_IFRAME       (((uint64_t) 1) << 7)          /* inbound frame header */
#define TT_OFRAME2      (((uint64_t) 1) << 8)          /* outbound frame header (level 2) */
#define TT_IFRAME2      (((uint64_t) 1) << 9)          /* inbound frame header (level 2) */
#define TT_OCOOK        (((uint64_t) 1) << 10)         /* outbound cooked dump */
#define TT_ICOOK        (((uint64_t) 1) << 11)         /* inbound cooked dump */
#define TT_ORAW         (((uint64_t) 1) << 12)         /* outbound raw data dump */
#define TT_IRAW         (((uint64_t) 1) << 13)         /* inbound raw data dump */
#define TT_CONFIG2      (((uint64_t) 1) << 14)         /* configuration status (level 2)*/
#define TT_MEM          (((uint64_t) 1) << 15)         /* memory usage */
#define TT_L1           (((uint64_t) 1) << 16)         /* level 1 */
#define TT_L2           (((uint64_t) 1) << 17)         /* level 2 */
#define TT_L3           (((uint64_t) 1) << 18)         /* level 3 */
#define TT_L4           (((uint64_t) 1) << 19)         /* level 4 */
#define TT_ACR          (((uint64_t) 1) << 20)         /* Errors that will cause a client reconnect attemp */
#define TT_EUEMSTARTUP  (((uint64_t) 1) << 21)         /* tracing of startup instrumentation */
#define TT_ERROR        TC_ALL          /* error condition (Debug ERROR) */

#define LOG_CONNECT     (((uint64_t) 1) << 0)		// UI standard logging flags
#define LOG_ERRORS      (((uint64_t) 1) << 1)
#define LOG_TRANSMIT    (((uint64_t) 1) << 2)
#define LOG_RECEIVE     (((uint64_t) 1) << 3)
#define LOG_KEYBOARD    (((uint64_t) 1) << 4)


//
// Logging option flags
//
#define LOG_APPEND       (((uint64_t) 1) << 0)				// Append to existing log file instead of creating a new one
#define LOG_FLUSH        (((uint64_t) 1) << 1)				// Flush log file after each line
#define LOG_PRINTF       (((uint64_t) 1) << 2)				// Call printf as well

#define LOG_NO_TIMES		(((uint64_t) 1) << 3)
#define LOG_ASSERT_STDERR	(((uint64_t) 1) << 4)
#define LOG_TAIL_ONLY		(((uint64_t) 1) << 5)
#define LOG_NO_THREAD		(((uint64_t) 1) << 6)

#ifdef __cplusplus
extern "C" {
#endif
    
typedef enum _LoggingTnitializationStatus {
    LoggingTnitializationStatusNone,        // Logging has never been initialized
    LoggingTnitializationStatusPending,     // In the process of being initialized
    LoggingTnitializationStatusComplete,    // Logging has been successively initialized
} LoggingInitializationStatus;
    
typedef enum _LoggingMode {
    LoggingModeOff,
    LoggingModeNormal,
    LoggingModeConnectionDiagnostics,
} LoggingMode;
	
/*
 *  Logging structures
 */
	
typedef struct _LOGOPEN {
    LoggingMode LoggingMode;
	uint64_t LogClass;
	uint64_t LogFlags;
	uint64_t LogFeatures;
	ULONG    LogBufferSize;
    ULONG    LogMaxNumberOfLogFiles;            // DEFAULT_MAX_LOG_FILES_NO_MAXIMUM == no maximum
    char     LogFileName[MAXFILEPATH];
    char     LoggingModeString[MAX_INI_LINE];   // String representation of LoggingMode
    unsigned short LogCGPCoreTraceLevel;
    LoggingInitializationStatus InitializationStatus;
} LOGOPEN, FAR *PLOGOPEN;
	
/* 
 *  Logging functions
 */
	
#if __GNUC__ >= 4
/* On gcc compilers, we can get improved compiler warnings by telling the compiler that the 
 * LogPrintf function has a format string and arguments similar to the printf function. The
 * format string is the sixth argument, the printf parameters start with the seventh argument. */
#define LOGPRINTFATTRIBUTES(F, A) __attribute__((format(printf, F, A)))
#else
#define LOGPRINTFATTRIBUTES
#endif

#ifndef CLANG_ANALYZER_NORETURN
#if __has_feature(attribute_analyzer_noreturn)
#define CLANG_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
#else
#define CLANG_ANALYZER_NORETURN
#endif
#endif
	
int LogLoad (void);

int  LogOpen( void );
int  LogClose( void );

void LogAssert(const char* pExpr, const char* pFileName, int LineNumber, 
               const char* function, int rc ) CLANG_ANALYZER_NORETURN;
void LogPrintf(const char* file, int line, const char* function, const char* LogClass, 
               const char* LogFeature, const char* pFormat, ...) LOGPRINTFATTRIBUTES(6, 7);
void LogBuffer(const char* file, int line, const char* function, const char* LogClass, 
               const char* LogFeature, void* pBuffer, size_t ByteCount);
void LogPrintfVA(const char* file, int line, const char* function, const char* LogClass,
                 const char* LogFeature, const char* pFormat, va_list args) LOGPRINTFATTRIBUTES(6, 0);
	
#ifdef __OBJC__

void LogPrintf_ObjC(const char* file, int line, const char* function, const char* LogClass,
				   const char* LogFeature, NSString *format, ...) NS_FORMAT_FUNCTION(6, 7);
void LogPrintfVA_ObjC(const char* file, int line, const char* function, const char* LogClass,
					  const char* LogFeature, NSString* format, va_list args) NS_FORMAT_FUNCTION(6, 0);
	
#endif

// Helper function to avoid warnings for ASSERT statements in non-debug code. 
static inline void CLANG_ANALYZER_NORETURN LogAssertReturnCode (int rc)  { (void)rc; }

// Log the result of a connection attempt.
void LogConnectionAttemptResult(int status);

// Remove old log files - controlled via traceMaxNumberOfLogsFiles
void LogCullLogFiles(IBOOL executeAsync);
    
void LogSetClass(uint64_t mask);
void LogUnsetClass(uint64_t mask);
void LogSetFeature(uint64_t mask);
void LogUnsetFeature(uint64_t mask);
void LogSetFlag(uint64_t mask);
void LogUnsetFlag(uint64_t mask);
uint64_t LogGetClass(void);
uint64_t LogGetFeature(void);
uint64_t LogGetFlags(void);
   
// Return the value of the traceCGPCoreLevel setting in the configuration file    
unsigned short LogCGPCoreTraceLevel(void);

extern LOGOPEN gLogSettings;

// Call to determine if logging should occur given a pair of class and features
inline IBOOL LogShouldLog(uint64_t logClass, uint64_t logFeatures)
{
    return gLogSettings.LogClass & logClass && gLogSettings.LogFeatures & logFeatures;
}

// A version that isn't inlined - currently only used by the virtual channel sdk    
IBOOL LogShouldLogNonInline(uint64_t logClass, uint64_t logFeatures);
    
// Internal
void LogInit (void);
    
#ifdef __cplusplus
}
#endif

#endif /* __LOGAPI_H__ */
