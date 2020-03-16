//
//  libmgr.h
//  ICAClientUniversalBinary
//
//  Created by Christian Bau on 07/12/2012.
//
//

#ifndef _LIBMGR_H_
#define _LIBMGR_H_

// Minimal implementation of libmgr.h to allow Virtual Channel SDK to work. Future Virtual Channel
// plug-ins shouldn't call any functions except the LibMgrUse macro. Current plug-ins may be
// calling other functions.

#include <ctxmem.h>
#include <miapi.h>
#include <logapi.h>
#include <ctxos.h>
#include <ctxfile.h>
#include <ctxpath.h>
#include <ctxwnd.h>
#include <ctxtmr.h>
#include <kbdapi.h>

#ifdef __cplusplus
extern "C" {
#endif
	
	#define LMGR_MAX_NAME 32
	
	typedef UINT32 LMGRVERS;
	typedef UINT32 LMGREVT;
	typedef LMGRVERS      *PLMGRVERS;
	typedef CHAR LMGRNAME[LMGR_MAX_NAME];
	typedef CHAR *PLMGRNAME;
	typedef UINT32 LMGRSTATUS;
	typedef PLIBPROCEDURE *PLMGRTABLE;
	typedef PLMGRTABLE  *PPLMGRTABLE;
	
	#define LIBMGR_STATUS_SUCCESS        0
	#define LIBMGR_STATUS_INUSE          1
	#define LIBMGR_STATUS_NO_MEMORY      2
	#define LIBMGR_STATUS_INVALID        3
	#define LIBMGR_STATUS_NOT_FOUND      4
	#define LIBMGR_STATUS_NOT_SUPPORTED  5
	
	// Function types. Only PLMGRUSE should be called by new code.
	typedef LMGRSTATUS (PWFCAPI PLMGRCONTROL)(LMGREVT);
	typedef LMGRSTATUS (PWFCAPI PLMGRLOAD)(const PLMGRNAME, LMGRVERS,const PLMGRTABLE, PLMGRCONTROL);
	typedef LMGRSTATUS (PWFCAPI PLMGRUNLOAD)(const PLMGRNAME);
	typedef LMGRSTATUS (PWFCAPI PLMGRUSE)(const PLMGRNAME, PLMGRVERS, PPLMGRTABLE);
	typedef LMGRSTATUS (PWFCAPI PLMGRRELEASE)(const PLMGRTABLE);
	typedef LMGRSTATUS (PWFCAPI PLMGRQUERYTABLE)(const PLMGRNAME, PLMGRVERS pVer,PLMGRTABLE *pTable,PLMGRCONTROL *ppfnControl);
	typedef LMGRSTATUS (PWFCAPI PLMGRUPDATETABLE)(const PLMGRNAME,LMGRVERS Ver,const PLMGRTABLE pTable,	PLMGRCONTROL pfnControl);

	// Function pointer table. Must be filled out completely in case older pluggins call functions.
	typedef struct _LIBMGRTABLE {
		PLMGRLOAD    pLMgrLoad;
		PLMGRUNLOAD  pLMgrUnload;
		PLMGRUSE     pLMgrUse;
		PLMGRRELEASE pLMgrRelease;
		PLMGRQUERYTABLE  pLMgrQueryTable;
		PLMGRUPDATETABLE pLMgrUpdateTable;
	} LIBMGRTABLE, *PLIBMGRTABLE;

	// Macro for the only function that new plug-ins should use.
	#define LibMgrUse(pname,pversion,pptable) \
		(g_pLibMgrCallTable ? \
			(*(g_pLibMgrCallTable)->pLMgrUse)(pname,pversion,pptable) : \
			LIBMGR_STATUS_NOT_SUPPORTED)
	

	//----------------------------------------------------------------------------------------------
	// Memory manager call tables
	//----------------------------------------------------------------------------------------------
	#define MEM_STRING "CTXMEM"

	typedef UINT (_PVPAPI PFNMEMALLOC)(HND, ULONG, PVOID *);
	typedef UINT (_PVPAPI PFNMEMREALLOC)(HND, ULONG, PVOID *);
	typedef UINT (_PVPAPI PFNMEMFREE)(HND, PVOID);
	
	typedef struct _MEMCALLTABLE {
		PFNMEMALLOC pfnMemAlloc;
		PFNMEMREALLOC pfnMemRealloc;
		PFNMEMFREE  pfnMemFree;
		PFNMEMALLOC pfnMemAllocZeroed;
	} MEMCALLTABLE, FAR *PMEMCALLTABLE;
	
		
	#define MEM_GLOBAL_INIT  PMEMCALLTABLE g_pMemCallTable = NULL
	#define MEM_EXTERN_INIT  extern PMEMCALLTABLE g_pMemCallTable
		
	#define MemRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(MEM_STRING, pVer, (PPLMGRTABLE)&g_pMemCallTable))
	#define MemRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)((PPLMGRTABLE)&g_pMemCallTable))
		
#if ! LIBMGR_NO_CALL_MACROS
	#define Mem_alloc       (*(g_pMemCallTable)->pfnMemAlloc)
	#define Mem_realloc     (*(g_pMemCallTable)->pfnMemRealloc)
	#define Mem_free        (*(g_pMemCallTable)->pfnMemFree)
	#define Mem_allocZeroed (*(g_pMemCallTable)->pfnMemAllocZeroed)
#endif


	//----------------------------------------------------------------------------------------------
	// Module manager call table
	//----------------------------------------------------------------------------------------------
	#define MODULE_STRING "CTXMODULE"

	typedef int (PWFCAPI PMODULELOAD)( char *, PDLLLINK );
	typedef int (PWFCAPI PMODULEUNLOAD)( PDLLLINK );
	typedef int (PWFCAPI PMODULEENUM)( LPBYTE, USHORT, PUSHORT );
	typedef int (PWFCAPI PMODULECALL)( PDLLLINK, USHORT, PVOID, PUINT16 );
	
	typedef struct _MODULETABLE
	{
		PMODULELOAD     pModuleLoad;
		PMODULEUNLOAD   pModuleUnload;
		PMODULEENUM     pModuleEnum;
		PMODULECALL     pModuleCall;
	}MODULETABLE,  * PMODULETABLE,  *  * PPMODULETABLE;
	
	#define MODULE_GLOBAL_INIT PMODULETABLE g_pModuleCallTable =NULL
	#define MODULE_EXTERN_INIT extern PMODULETABLE g_pModuleCallTable
	
	#define ModuleRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(MODULE_STRING,pVer,(PPLMGRTABLE)&g_pModuleCallTable))
	#define ModuleRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)((PLMGTABLE)g_pModuleCallTable))
		
#if ! LIBMGR_NO_CALL_MACROS
	#define ModuleLoad     (*(g_pModuleCallTable)->pModuleLoad)
	#define ModuleUnload   (*(g_pModuleCallTable)->pModuleUnload)
	#define ModuleEnum     (*(g_pModuleCallTable)->pModuleEnum)
	#define ModuleCall     (*(g_pModuleCallTable)->pModuleCall)
#endif
	
	//----------------------------------------------------------------------------------------------
	// Memini manager call table
	//----------------------------------------------------------------------------------------------
	#define MEMINI_STRING "CTXMEMINI"

	typedef int (PWFCAPI PMISETPROFILEPOINTER)( PCHAR );
	typedef int (PWFCAPI PMISETSECTIONPOINTER)( PCHAR );
	typedef int (PWFCAPI PMIGETPRIVATEPROFILESTRING)( PCHAR, PCHAR, PCHAR, PCHAR, int);
	typedef int (PWFCAPI PMIGETPRIVATEPROFILEINT)( PCHAR, PCHAR, int);
	typedef LONG (PWFCAPI PMIGETPRIVATEPROFILELONG)( PCHAR, PCHAR, long);
	typedef int (PWFCAPI PMIGETPRIVATEPROFILEBOOL)( PCHAR, PCHAR, IBOOL);
	typedef int (PWFCAPI PMIGETLONGCOMMANDLINE)(PCHAR pszLongCmdLine, int cbBuf);
	typedef int (PWFCAPI PMIRELEASEPROFILE)( VOID );
	
	typedef struct _MEMINITABLE
	{
		PMISETPROFILEPOINTER        pmiSetProfilePointer;
		PMISETSECTIONPOINTER        pmiSetSectionPointer;
		PMIGETPRIVATEPROFILESTRING  pmiGetPrivateProfileString;
		PMIGETPRIVATEPROFILEINT     pmiGetPrivateProfileInt;
		PMIGETPRIVATEPROFILELONG    pmiGetPrivateProfileLong;
		PMIGETPRIVATEPROFILEBOOL    pmiGetPrivateProfileBool;
		PMIGETLONGCOMMANDLINE		pmiGetLongCommandLine;
		PMIRELEASEPROFILE           pmiReleaseProfile;
	} MEMINITABLE, FAR * PMEMINITABLE, FAR * FAR * PPMEMINITABLE;
	
	#define MEMINI_GLOBAL_INIT PMEMINITABLE g_pMemIniCallTable = NULL
	#define MEMINI_EXTERN_INIT extern PMEMINITABLE g_pMemIniCallTable
	
	#define MemIniRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(MEMINI_STRING,pVer,(PPLMGRTABLE)&g_pMemIniCallTable))
	#define MemIniRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)((PLMGTABLE)g_pMemIniCallTable))
	
#if ! LIBMGR_NO_CALL_MACROS
	#define miSetProfilePointer (*(g_pMemIniCallTable)->pmiSetProfilePointer)
	#define miSetSectionPointer (*(g_pMemIniCallTable)->pmiSetSectionPointer)
	#define miGetPrivateProfileString   \
		(*(g_pMemIniCallTable)->pmiGetPrivateProfileString)
	#define miGetPrivateProfileInt      \
		(*(g_pMemIniCallTable)->pmiGetPrivateProfileInt)
	#define miGetPrivateProfileLong     \
		(*(g_pMemIniCallTable)->pmiGetPrivateProfileLong)
	#define miGetPrivateProfileBool     \
		(*(g_pMemIniCallTable)->pmiGetPrivateProfileBool)
	#define miGetLongCommandLine		\
		(*(g_pMemIniCallTable)->pmiGetLongCommandLine)
	#define miReleaseProfile            \
		(*(g_pMemIniCallTable)->pmiReleaseProfile)
#endif	

	
	//----------------------------------------------------------------------------------------------
	// Timer manager call table
	//----------------------------------------------------------------------------------------------
	#define TMR_STRING        "CTXTMR"
	
	typedef VPSTATUS (_PVPAPI PFNTMRCREATE)(HND, UINT32, PVOID, PFNDELIVER, PTMR *);
	typedef VPSTATUS (_PVPAPI PFNTMRDESTROY)(PTMR *);
	typedef VPSTATUS (_PVPAPI PFNTMRSETENABLED)(PTMR, IBOOL);
	typedef VPSTATUS (_PVPAPI PFNTMRSETPERIOD)(PTMR, UINT32);
	
	typedef struct _TMRCALLTABLE
	{
		PFNTMRCREATE        pfnTmrCreate;
		PFNTMRDESTROY       pfnTmrDestroy;
		PFNTMRSETENABLED    pfnTmrSetEnabled;
		PFNTMRSETPERIOD     pfnTmrSetPeriod;
	} TMRCALLTABLE, FAR * PTMRCALLTABLE, FAR * FAR * PPTMRCALLTABLE;
	
	#define TMR_GLOBAL_INIT   PTMRCALLTABLE g_pTmrCallTable = NULL
	#define TMR_EXTERN_INIT   extern PTMRCALLTABLE g_pTmrCallTable
	
	#define TmrRunTimeInit( libmgr, pver ) \
		((*(libmgr->pLMgrUse))( TMR_STRING, pver, (PPLMGRTABLE)&g_pTmrCallTable ))
	#define TmrRuntimeRelease( libmgr ) \
		((*(libmgr->pLMgrRelease))( (PLMGRTABLE)g_pTmrCallTable ))

#if ! LIBMGR_NO_CALL_MACROS
	#define Tmr_create          (*g_pTmrCallTable->pfnTmrCreate)
	#define Tmr_destroy         (*g_pTmrCallTable->pfnTmrDestroy)
	#define Tmr_setEnabled      (*g_pTmrCallTable->pfnTmrSetEnabled)
	#define Tmr_setPeriod       (*g_pTmrCallTable->pfnTmrSetPeriod)
#endif


	//----------------------------------------------------------------------------------------------
	// Keyboard manager call table
	//----------------------------------------------------------------------------------------------
	#define KBD_STRING "CTXKBD"

	typedef int (PWFCAPI PKBDGETMODE       )( KBDCLASS * pKbdClass );
	typedef int (PWFCAPI PKBDSETMODE       )( KBDCLASS KbdClass );
	typedef int (PWFCAPI PKBDREADAVAIL     )( int * pCountAvail );
	typedef int (PWFCAPI PKBDREADCHAR      )( int * pCharCode, int * pShiftState );
	typedef int (PWFCAPI PKBDREADSCAN      )( int * pScanCode, int * pShiftState );
	typedef int (PWFCAPI PKBDPUSH          )( int ScanCode, int ShiftState, int Char );
	typedef int (PWFCAPI PKBDSETLEDS       )( int ShiftState );
	typedef int (PWFCAPI PKBDADDHOOK       )( LPVOID pProcedure );
	typedef int (PWFCAPI PKBDREMOVEHOOK    )( LPVOID pProcedure );
	typedef int (PWFCAPI PKBDFLUSH         )( VOID );
	typedef int (PWFCAPI PKBDLOADPREFERENCES)( PKBDPREFERENCES pPref );
	typedef int (PWFCAPI PKBDGETLEDS       )( BYTE * ShiftState );
	
	typedef struct _KBDTABLE
	{
		PKBDGETMODE         pKbdGetMode;
		PKBDSETMODE         pKbdSetMode;
		PKBDREADAVAIL       pKbdReadAvail;
		PKBDREADCHAR        pKbdReadChar;
		PKBDREADSCAN        pKbdReadScan;
		PKBDPUSH            pKbdPush;
		PKBDSETLEDS         pKbdSetLeds;
		PKBDADDHOOK         pKbdAddHook;
		PKBDREMOVEHOOK      pKbdRemoveHook;
		PKBDFLUSH           pKbdFlush;
		PKBDLOADPREFERENCES pKbdLoadPreferences;
		PKBDGETLEDS         pKbdGetLeds;
	}KBDTABLE, FAR * PKBDTABLE, FAR * FAR * PPKBDTABLE;
	
	#define KBD_GLOBAL_INIT PKBDTABLE g_pKbdCallTable = NULL
	#define KBD_EXTERN_INIT extern PKBDTABLE g_pKbdCallTable
	
	#define KbdRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(KBD_STRING,pVer,(PPLMGRTABLE)&g_pKbdCallTable))
	#define KbdRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)((PLMGTABLE)g_pKbdCallTable))
	
#if ! LIBMGR_NO_CALL_MACROS
	#define KbdGetMode          (*(g_pKbdCallTable)->pKbdGetMode)
	#define KbdSetMode          (*(g_pKbdCallTable)->pKbdSetMode)
	#define KbdReadAvail        (*(g_pKbdCallTable)->pKbdReadAvail)
	#define KbdReadChar         (*(g_pKbdCallTable)->pKbdReadChar)
	#define KbdReadScan         (*(g_pKbdCallTable)->pKbdReadScan)
	#define KbdPush             (*(g_pKbdCallTable)->pKbdPush)
	#define KbdSetLeds          (*(g_pKbdCallTable)->pKbdSetLeds)
	#define KbdAddHook          (*(g_pKbdCallTable)->pKbdAddHook)
	#define KbdRemoveHook       (*(g_pKbdCallTable)->pKbdRemoveHook)
	#define KbdFlush            (*(g_pKbdCallTable)->pKbdFlush)
	#define KbdLoadPreferences  (*(g_pKbdCallTable)->pKbdLoadPreferences)
	#define KbdGetLeds          (*(g_pKbdCallTable)->pKbdGetLeds)
#endif

	
	//----------------------------------------------------------------------------------------------
	// Log manager call table
	//----------------------------------------------------------------------------------------------
	#define LOG_STRING "CTXLOG"

	// The first six entries in LOGTABLE are for Plug-ins built for Garter or earlier. They cannot
	// be called anymore, but the function pointers are there for compatibility and they are
	// implemented inside mac_dlibapi.m.
	typedef int  (PWFCAPI PFNLOGOPEN_DEPRECATED)( PLOGOPEN pLogOpen );
	typedef int  (PWFCAPI PLOGCLOSE_DEPRECATED)( void );
	typedef void (PWFCAPI PLOGPRINTF_DEPRECATED)( ULONG LogClass, ULONG LogFeature, PCHAR pFormat, ... );
	typedef void (PWFCAPI PLOGBUFFER_DEPRECATED)( ULONG LogClass, ULONG LogFeature, LPVOID pBuffer, ULONG ByteCount );
	typedef void (PWFCAPI PLOGASSERT_DEPRECATED)( PCHAR, PCHAR, int, int );
	typedef int (PWFCAPI PLOGWHERE_DEPRECATED)( char *logFile, int logLine);
	
	typedef void (* PFNLOGPRINTF_DEPRECATED2) (const char* file, int line, uint64_t LogClass, uint64_t LogFeature, const char* pFormat, ...);
	typedef void (* PFNLOGBUFFER_DEPRECATED2) (const char* file, int line, uint64_t LogClass, uint64_t LogFeature, void* pBuffer, size_t ByteCount);

	typedef void (* PFNLOGASSERT) (const char* pExpr, const char* file, int line, const char* function, int rc);
    
    typedef void (* PFNLOGPRINTF) (const char* file, int line, const char* function, const char* LogClass, const char* LogFeature, const char* pFormat, ...);
	typedef void (* PFNLOGBUFFER) (const char* file, int line, const char* function, const char* LogClass, const char* LogFeature, void* pBuffer, size_t ByteCount);
    
#ifdef __OBJC__
	typedef void (* PFNLOGPRINTF_OBJC) (const char* file, int line, const char* function, const char* LogClass, const char* LogFeature, NSString *format, ...);
#endif
	
    typedef IBOOL (* PFNLOGSHOULDLOG) (uint64_t class, uint64_t features);
    
    typedef int (PWFCAPI PLOGWHERE)(const char *logFile, int logLine, const char *function);
	
	typedef struct _LOGTABLE
	{
		PFNLOGOPEN_DEPRECATED pLogOpen_Deprecated;
		PLOGCLOSE_DEPRECATED  pLogClose_Deprecated;
		PLOGPRINTF_DEPRECATED pLogPrintf_Deprecated;
		PLOGBUFFER_DEPRECATED pLogBuffer_Deprecated;
		PLOGASSERT_DEPRECATED pLogAssert_Deprecated;
		PLOGWHERE_DEPRECATED  pLogWhere_Deprecated;
		
		PFNLOGPRINTF_DEPRECATED2 pLogPrintf_Deprecated2;
		PFNLOGBUFFER_DEPRECATED2 pLogBuffer_Deprecated2;
		PFNLOGASSERT  pLogAssert;
        
        PFNLOGPRINTF pLogPrintf;
		PFNLOGBUFFER pLogBuffer;
        PFNLOGSHOULDLOG pLogShouldLog;
        PLOGWHERE pLogWhere;
#ifdef __OBJC__
		PFNLOGPRINTF_OBJC pLogPrintf_ObjC;
#else
		void *pLogPrintf_ObjC;
#endif
	}   LOGTABLE,FAR *PLOGTABLE,FAR * FAR *PPLOGTABLE;
	
	
	#define LOG_GLOBAL_INIT PLOGTABLE g_pLogCallTable = NULL
	#define LOG_EXTERN_INIT extern PLOGTABLE g_pLogCallTable
	
	#define LogRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(LOG_STRING,pVer,(PPLMGRTABLE)&g_pLogCallTable))
	#define LogRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)((PLMGTABLE)g_pLogCallTable))

#if ! LIBMGR_NO_CALL_MACROS
	#define LogOpen     (*(g_pLogCallTable)->pLogOpen_Deprecated)
	#define LogClose    (*(g_pLogCallTable)->pLogClose_Deprecated)	
	#define LogPrintf if (g_pLogCallTable) (*(g_pLogCallTable)->pLogPrintf)
	#define LogBuffer if (g_pLogCallTable) (*(g_pLogCallTable)->pLogBuffer)
	#define LogAssert if (g_pLogCallTable) (*(g_pLogCallTable)->pLogAssert)
    
    IBOOL StubLogShouldLog(uint64_t logClass, uint64_t logFeatures);
    #define LogShouldLog StubLogShouldLog
	
#ifdef __OBJC__
	#define LogPrintf_ObjC if (g_pLogCallTable) (*(g_pLogCallTable)->pLogPrintf_ObjC)
#endif
	
#endif
	
	
	
	//----------------------------------------------------------------------------------------------
	// CTXOS manager call table
	//----------------------------------------------------------------------------------------------
	#define CTXOS_STRING   "CTXOS"
	
	typedef UINT32 (_PVPAPI PFNGETLICOSID)(VOID);
	typedef UINT32 (_PVPAPI PFNGETLICOEMID)(VOID);
	typedef UINT32 (_PVPAPI PFNGETOSTYPE)(VOID);
	typedef UINT32 (_PVPAPI PFNGETOSVER)(VOID);
	typedef UINT32 (_PVPAPI PFNGETUITYPE)(VOID);
	typedef UINT32 (_PVPAPI PFNGETUSER)(LPSTR pBuffer, LPUINT32 pcCount);
	typedef UINT32 (_PVPAPI PFNGETCOMPUTER)(LPSTR pBuffer, LPUINT32 pcCount);
	typedef IBOOL   (_PVPAPI PFNISPASSTHRU)(VOID);
	typedef void   (_PVPAPI PFNGETTIME)(PCTXTIME);
	typedef void   (_PVPAPI PFNGETDATE)(PCTXDATE);
	typedef void   (_PVPAPI PFNOSDELAY)(ULONG);
	typedef UINT32 (_PVPAPI PFNGETTICKCOUNTINMS)(VOID);
	typedef VPSTATUS (_PVPAPI PFNGETTIMEZONEINFO)(OS_TZI *ptzi);
	typedef IBOOL   (_PVPAPI PFNEXECUTESHELLCMD)(UCHAR *szURL);
	typedef VPSTATUS   (_PVPAPI PFNGETLOCALIPADDRESS)(PCHAR, PINT32);
	typedef VPSTATUS   (_PVPAPI PFNSUPPORTUNICODEINSERTION)(PIBOOL);
	struct _TW_MONITOR_LAYOUT_INFO;
	struct _TWRECTI;
	typedef UINT32 (_PVPAPI PFNGETMONITORLAYOUT)(struct _TW_MONITOR_LAYOUT_INFO**, UINT8);
	
	typedef struct _CTXOS_FUNC_TABLE {
		UINT32                lGetClientLicenseOsId;
		UINT32                lGetClientLicenseOemId;
		UINT32                lGetOsType;
		UINT32                lGetOsVersion;
		UINT32                lGetOsUiType;
		UINT32                lIsPassThruClient;
		UINT32                lGetMinorOsVersion;
		PFNGETUSER            pfnGetUserName;
		PFNGETCOMPUTER        pfnGetComputerName;
		PFNGETTIME            pfnGetTime;
		PFNGETDATE            pfnGetDate;
		PFNOSDELAY            pfnOsDelay;
		PFNGETTICKCOUNTINMS   pfnGetTickCountInMs;
		PFNGETTIMEZONEINFO    pfnGetTimeZoneInfo;
		PFNEXECUTESHELLCMD    pfnExecuteShellCmd;
		PFNGETLOCALIPADDRESS  pfnGetLocalIPAddress;
		PFNSUPPORTUNICODEINSERTION      pfnSupportUnicodeInsertion;
		PFNGETMONITORLAYOUT   pfnGetMonitorLayout;
	} CTXOS_FUNC_TABLE, FAR *PCTXOS_FUNC_TABLE, FAR * FAR *PPCTXOS_FUNC_TABLE;
	
	#define CTXOS_GLOBAL_INIT         PCTXOS_FUNC_TABLE g_pCtxOsTable = NULL
	#define CTXOS_EXTERN_INIT         extern PCTXOS_FUNC_TABLE g_pCtxOsTable
	
	#define CtxOsRunTimeInit(libmgr, pver) \
		((*(libmgr->pLMgrUse))(CTXOS_STRING, pver, (PPLMGRTABLE)&g_pCtxOsTable))
	#define CtxOsRuntimeRelease(libmgr) \
		((*(libmgr->pLMgrRelease))((PLMGRTABLE)g_pCtxOsTable))

#if ! LIBMGR_NO_CALL_MACROS
	#undef Os_GetOsType
	#undef Os_GetOsVersion
	#undef Os_getMinorVersion
	#undef Os_GetOsUiType
	#undef Os_IsPassThruClient

	#define Os_GetClientLicenseOsId()   (g_pCtxOsTable->lGetClientLicenseOsId)
	#define Os_GetClientLicenseOemId()  (g_pCtxOsTable->lGetClientLicenseOemId)
	#define Os_GetOsType()              (g_pCtxOsTable->lGetOsType)
	#define Os_GetOsVersion()           (g_pCtxOsTable->lGetOsVersion)
	#define Os_GetOsUiType()            (g_pCtxOsTable->lGetOsUiType)
	#define Os_IsPassThruClient()       (g_pCtxOsTable->lIsPassThruClient)
	#define Os_GetUserName              (*g_pCtxOsTable->pfnGetUserName)
	#define Os_GetComputerName          (*g_pCtxOsTable->pfnGetComputerName)
	#define Os_GetTime                  (*g_pCtxOsTable->pfnGetTime)
	#define Os_GetDate                  (*g_pCtxOsTable->pfnGetDate)
	#define Os_Delay                    (*g_pCtxOsTable->pfnOsDelay)
	#define Os_GetTickCountInMs         (*g_pCtxOsTable->pfnGetTickCountInMs)
	#define Os_getTimeZoneInfo          (*g_pCtxOsTable->pfnGetTimeZoneInfo)
	#define Os_executeShellCmd          (*g_pCtxOsTable->pfnExecuteShellCmd)
	#define Os_getMinorVersion()        (g_pCtxOsTable->lGetMinorOsVersion)
	#define Os_getLocalIPAddress        (*g_pCtxOsTable->pfnGetLocalIPAddress)
	#define Os_supportUnicodeInsertion  (*g_pCtxOsTable->pfnSupportUnicodeInsertion)
	#define Os_GetMonitorLayout         (*g_pCtxOsTable->pfnGetMonitorLayout)
#endif	
	

	//----------------------------------------------------------------------------------------------
	// Window manager call table
	//----------------------------------------------------------------------------------------------
	#define WND_STRING        "CTXWND"
	
	typedef VPSTATUS (_PVPAPI PFNWNDCREATE)(PVOID, PFNDELIVER, PHND);
	typedef VPSTATUS (_PVPAPI PFNWNDSETUSERDATA)(HND,PVOID);
	typedef VPSTATUS (_PVPAPI PFNWNDGETUSERDATA)(HND,PPVOID);
	typedef VPSTATUS (_PVPAPI PFNWNDSETPARENT)(HND, HND);
	typedef VPSTATUS (_PVPAPI PFNWNDSETVISIBLE)(HND, IBOOL);
	typedef VPSTATUS (_PVPAPI PFNWNDSETSIZE)(HND, PVPSIZE);
	typedef VPSTATUS (_PVPAPI PFNWNDGETSIZE)(HND, PVPSIZE);
	typedef VPSTATUS (_PVPAPI PFNWNDSETPOS)(HND, PVPPOINT);
	typedef VPSTATUS (_PVPAPI PFNWNDREPAINTRECT)(HND, PVPRECT);
	typedef VPSTATUS (_PVPAPI PFNWNDGETREPAINTRECTS)(HND,PVPRECT,INT16,PINT16);
	typedef VPSTATUS (_PVPAPI PFNWNDGETOBSCUREDRECTS)(HND,PVPRECT,PVPRECT,INT16,PINT16);
	typedef VPSTATUS (_PVPAPI PFNWNDSETINPUTPREFERENCES)(PWND_INPUTPREFERENCES);
	typedef VPSTATUS (_PVPAPI PFNWNDGETKEYBOARDINFO)(UINT32,UINT32,CHAR*,PWND_KEYBOARDINFO);
	typedef VPSTATUS (_PVPAPI PFNWNDGETKEYBOARDSTATE)(PUINT32);
	typedef VPSTATUS (_PVPAPI PFNWNDSETKEYBOARDSTATE)(UINT32);
	typedef VPSTATUS (_PVPAPI PFNWNDSETCURSOR)( HND, HGCURSOR );
	typedef VPSTATUS (_PVPAPI PFNWNDSETMOUSEPOS)( INT32, INT32, HND );
	typedef VPSTATUS (_PVPAPI PFNWNDREQUESTFOCUS)( HND );
	typedef VPSTATUS (_PVPAPI PFNWNDDESTROY)(PHND);
	
	
	typedef struct _WNDCALLTABLE
	{
		PFNWNDCREATE              pfnWndCreate;
		PFNWNDSETUSERDATA         pfnWndSetUserData;
		PFNWNDGETUSERDATA         pfnWndGetUserData;
		PFNWNDSETPARENT           pfnWndSetParent;
		PFNWNDSETVISIBLE          pfnWndSetVisible;
		PFNWNDSETSIZE             pfnWndSetSize;
		PFNWNDGETSIZE             pfnWndGetSize;
		PFNWNDSETPOS              pfnWndSetPos;
		PFNWNDREPAINTRECT         pfnWndRepaintRect;
		PFNWNDGETREPAINTRECTS     pfnGetRepaintRects;
		PFNWNDGETOBSCUREDRECTS    pfnGetObscuredRects;
		PFNWNDSETINPUTPREFERENCES pfnWndSetInputPreferences;
		PFNWNDGETKEYBOARDINFO     pfnWndGetKeyboardInfo;
		PFNWNDGETKEYBOARDSTATE    pfnWndGetKeyboardState;
		PFNWNDSETKEYBOARDSTATE    pfnWndSetKeyboardState;
		PFNWNDSETCURSOR           pfnWndSetCursor;
		PFNWNDSETMOUSEPOS         pfnWndSetMousePos;
		PFNWNDREQUESTFOCUS        pfnWndRequestFocus;
		PFNWNDDESTROY             pfnWndDestroy;
	} WNDCALLTABLE, FAR * PWNDCALLTABLE, FAR * FAR * PPWNDCALLTABLE;
	
	#define WND_GLOBAL_INIT   PWNDCALLTABLE g_pWndCallTable = NULL
	#define WND_EXTERN_INIT   extern PWNDCALLTABLE g_pWndCallTable
	
	#define WndRunTimeInit( libmgr, pver ) \
		((*(libmgr->pLMgrUse))( WND_STRING, pver, (PPLMGRTABLE)&g_pWndCallTable ))
	#define WndRuntimeRelease( libmgr ) \
		((*(libmgr->pLMgrRelease))( (PLMGRTABLE)g_pWndCallTable ))

#if ! LIBMGR_NO_CALL_MACROS
	#define Wnd_create               (*g_pWndCallTable->pfnWndCreate)
	#define Wnd_setUserData          (*g_pWndCallTable->pfnWndSetUserData)
	#define Wnd_getUserData          (*g_pWndCallTable->pfnWndGetUserData)
	#define Wnd_setParent            (*g_pWndCallTable->pfnWndSetParent)
	#define Wnd_setVisible           (*g_pWndCallTable->pfnWndSetVisible)
	#define Wnd_setSize              (*g_pWndCallTable->pfnWndSetSize)
	#define Wnd_getSize              (*g_pWndCallTable->pfnWndGetSize)
	#define Wnd_setPos               (*g_pWndCallTable->pfnWndSetPos)
	#define Wnd_repaintRect          (*g_pWndCallTable->pfnWndRepaintRect)
	#define Wnd_getRepaintRects      (*g_pWndCallTable->pfnGetRepaintRects)
	#define Wnd_getObscuredRects     (*g_pWndCallTable->pfnGetObscuredRects)
	#define Wnd_setInputPreferences  (*g_pWndCallTable->pfnWndSetInputPreferences)
	#define Wnd_getKeyboardInfo      (*g_pWndCallTable->pfnWndGetKeyboardInfo)
	#define Wnd_getKeyboardState     (*g_pWndCallTable->pfnWndGetKeyboardState)
	#define Wnd_setKeyboardState     (*g_pWndCallTable->pfnWndSetKeyboardState)
	#define Wnd_setCursor            (*g_pWndCallTable->pfnWndSetCursor)
	#define Wnd_setMousePos          (*g_pWndCallTable->pfnWndSetMousePos)
	#define Wnd_requestFocus         (*g_pWndCallTable->pfnWndRequestFocus)
	#define Wnd_destroy              (*g_pWndCallTable->pfnWndDestroy)
#endif

	//----------------------------------------------------------------------------------------------
	// File manager call table
	//----------------------------------------------------------------------------------------------
	#define FILE_STRING "CTXFILE"

	typedef VPSTATUS (_PVPAPI PFNFILEOPEN)              (PATH_NAME path, UINT16 accessMode, UINT16 disposition, UINT32 fileType, OUT PHND phFile);
	typedef VPSTATUS (_PVPAPI PFNFILEOPENEX)            (PATH_NAME path, UINT16 accessMode, UINT16 disposition, UINT32 fileType, OUT PHND phFile);
	typedef VPSTATUS (_PVPAPI PFNFILEREAD)              (IN HND hFile, UINT32 bytesToRead, PUINT32 pBytesRead, PVOID pBuffer);
	typedef VPSTATUS (_PVPAPI PFNFILEWRITE)             (IN HND hFile, UINT32 bytesToWrite, PUINT32 pBytesWritten, PVOID pBuffer);
	typedef VPSTATUS (_PVPAPI PFNFILESEEK)              (HND hFile, INT32 offset, UINT16 origin);
	typedef VPSTATUS (_PVPAPI PFNFILEDELETE)            (PATH_NAME  path);
	typedef VPSTATUS (_PVPAPI PFNFILETRUNCATE)          (HND hFile, INT32 numberOfBytes);
	typedef VPSTATUS (_PVPAPI PFNFILESETDATE)           (HND hFile); /* TBD */
	typedef VPSTATUS (_PVPAPI PFNFILEGETDATE)           (HND hFile); /* TBD */
	typedef VPSTATUS (_PVPAPI PFNFILESETATTRIBUTES)     (HND hFile); /* TBD */
	typedef VPSTATUS (_PVPAPI PFNFILEGETATTRIBUTES)     (HND hFile); /* TBD */
	typedef VPSTATUS (_PVPAPI PFNFILEFINDFIRST)         (PATH_NAME FileName, PHND phSearchHandle, PFILEIO_FIND_DATA pFindData);
	typedef VPSTATUS (_PVPAPI PFNFILEFINDNEXT)          (HND hSearchHandle, PFILEIO_FIND_DATA pFindData);
	typedef VPSTATUS (_PVPAPI PFNFILEFINDCLOSE)         (PHND phSearchHandle);
	typedef VPSTATUS (_PVPAPI PFNFILECLOSE)             (PHND phFile);
	typedef VPSTATUS (_PVPAPI PFNFILEGETSIZE)           (HND hFile, PUINT32 pSize);
	typedef VPSTATUS (_PVPAPI PFNFILEMKDIR)             (PATH_NAME path);
	typedef VPSTATUS (_PVPAPI PFNFILERMDIR)             (PATH_NAME path);
	typedef VPSTATUS (_PVPAPI PFNFILEGETDISKFREESPACE)  (PATH_NAME path, PUINT32 pHighFreeSpace, PUINT32 pLowFreeSpace);
	
	typedef struct _FILECALLTABLE{
		
		PFNFILEOPEN                 pfnFileOpen;
		PFNFILEOPENEX               pfnFileOpenExclusive;
		PFNFILEREAD                 pfnFileRead;
		PFNFILEWRITE                pfnFileWrite;
		PFNFILESEEK                 pfnFileSeek;
		PFNFILEDELETE               pfnFileDelete;
		PFNFILETRUNCATE             pfnFileTruncate;
		PFNFILESETDATE              pfnFileSetDate;
		PFNFILEGETDATE              pfnFileGetDate;
		PFNFILESETATTRIBUTES        pfnFileSetAttributes;
		PFNFILEGETATTRIBUTES        pfnFileGetAttributes;
		PFNFILEFINDFIRST            pfnFileFindFirst;
		PFNFILEFINDNEXT             pfnFileFindNext;
		PFNFILEFINDCLOSE            pfnFileFindClose;
		PFNFILECLOSE                pfnFileClose;
		PFNFILEGETSIZE              pfnFileGetSize;
		PFNFILEMKDIR                pfnFileMkDir;
		PFNFILERMDIR                pfnFileRmDir;
		PFNFILEGETDISKFREESPACE     pfnFileGetFreeDiskSpace;
		
	} FILECALLTABLE, FAR * PFILECALLTABLE, FAR * FAR * PPFILECALLTABLE;
	
	#define FILE_GLOBAL_INIT    PFILECALLTABLE g_pFileCallTable = NULL;
	#define FILE_EXTERN_INIT    extern PFILECALLTABLE g_pFileCallTable;
	
	#define FileRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(FILE_STRING, pVer,(PPLMGRTABLE)&g_pFileCallTable))
	#define FileRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)( (PPLMGRTABLE) &g_pFileCallTable) )

#if ! LIBMGR_NO_CALL_MACROS
	#define File_open               (*(g_pFileCallTable)->pfnFileOpen)
	#define File_openExclusive      (*(g_pFileCallTable)->pfnFileOpenExclusive)
	#define File_read               (*(g_pFileCallTable)->pfnFileRead)
	#define File_write              (*(g_pFileCallTable)->pfnFileWrite)
	#define File_seek               (*(g_pFileCallTable)->pfnFileSeek)
	#define File_delete             (*(g_pFileCallTable)->pfnFileDelete)
	#define File_truncate           (*(g_pFileCallTable)->pfnFileTruncate)
	#define File_setDate            (*(g_pFileCallTable)->pfnFileSetDate)
	#define File_getDate            (*(g_pFileCallTable)->pfnFileGetDate)
	#define File_setAttributes      (*(g_pFileCallTable)->pfnFileSetAttributes)
	#define File_getAttributes      (*(g_pFileCallTable)->pfnFileGetAttributes)
	#define File_findFirst          (*(g_pFileCallTable)->pfnFileFindFirst)
	#define File_findNext           (*(g_pFileCallTable)->pfnFileFindNext)
	#define File_findClose          (*(g_pFileCallTable)->pfnFileFindClose)
	#define File_close              (*(g_pFileCallTable)->pfnFileClose)
	#define File_getSize            (*(g_pFileCallTable)->pfnFileGetSize)
	#define File_makeDirectory      (*(g_pFileCallTable)->pfnFileMkDir)
	#define File_removeDirectory    (*(g_pFileCallTable)->pfnFileRmDir)
	#define File_getFreeDiskSpace   (*(g_pFileCallTable)->pfnFileGetFreeDiskSpace)
#endif

	//----------------------------------------------------------------------------------------------
	// File manager call table
	//----------------------------------------------------------------------------------------------
	#define PATH_STRING "CTXPATH"

	typedef VPSTATUS (_PVPAPI PFNPATHINITFROMNATIVE)    (PATH_NAME path, CHAR* pNativePath);
	typedef VPSTATUS (_PVPAPI PFNPATHEXTRACTNATIVE)     (PATH_NAME path, CHAR* pNativePath);
	typedef VPSTATUS (_PVPAPI PFNPATHINITFROMDOS)       (PATH_NAME path, CHAR* pDosPath);
	typedef VPSTATUS (_PVPAPI PFNPATHEXTRACTDOS)        (PATH_NAME path, UINT pathFlag, CHAR* pDosPath);
	typedef VPSTATUS (_PVPAPI PFNPATHAPPEND)            (PATH_NAME path, PATH_COMP Comp);
	typedef VPSTATUS (_PVPAPI PFNPATHCOPY)              (PATH_NAME path, PATH_NAME pSrcPath);
	typedef VPSTATUS (_PVPAPI PFNPATHTRUNCATE)          (PATH_NAME path, UINT count);
	typedef VPSTATUS (_PVPAPI PFNPATHCOMPONENTCOUNT)    (PATH_NAME path, PUINT pCount);
	typedef VPSTATUS (_PVPAPI PFNPATHEXTRACTCOMPONENT)  (PATH_NAME path, INT count, PATH_COMP Comp);
	typedef VPSTATUS (_PVPAPI PFNPATHCOMBINE)           (PATH_NAME path, PATH_NAME path2);
	
	typedef struct _PATHCALLTABLE{
		
		PFNPATHINITFROMNATIVE       pfnPathInitFromNative;
		PFNPATHEXTRACTNATIVE        pfnPathExtractNative;
		PFNPATHINITFROMDOS          pfnPathInitFromDos;
		PFNPATHEXTRACTDOS           pfnPathExtractDos;
		PFNPATHAPPEND               pfnPathAppend;
		PFNPATHCOPY                 pfnPathCopy;
		PFNPATHTRUNCATE             pfnPathTruncate;
		PFNPATHCOMPONENTCOUNT       pfnPathComponentCount;
		PFNPATHEXTRACTCOMPONENT     pfnPathExtractComponent;
		PFNPATHCOMBINE              pfnPathCombine;
		
	} PATHCALLTABLE, FAR * PPATHCALLTABLE, FAR * FAR * PPPATHCALLTABLE;
	
	#define PATH_GLOBAL_INIT    PPATHCALLTABLE g_pPathCallTable = NULL;
	#define PATH_EXTERN_INIT    extern PPATHCALLTABLE g_pPathCallTable;

	#define PathRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(PATH_STRING, pVer,(PPLMGRTABLE)&g_pPathCallTable))
	#define PathRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)( (PPLMGRTABLE) &g_pPathCallTable) )
	
#if ! LIBMGR_NO_CALL_MACROS
	#define Path_initFromNative     (*(g_pPathCallTable)->pfnPathInitFromNative)
	#define Path_extractNative      (*(g_pPathCallTable)->pfnPathExtractNative)
	#define Path_initFromDos        (*(g_pPathCallTable)->pfnPathInitFromDos)
	#define Path_extractDos         (*(g_pPathCallTable)->pfnPathExtractDos)
	#define Path_append             (*(g_pPathCallTable)->pfnPathAppend)
	#define Path_copy               (*(g_pPathCallTable)->pfnPathCopy)
	#define Path_truncate           (*(g_pPathCallTable)->pfnPathTruncate)
	#define Path_componentCount     (*(g_pPathCallTable)->pfnPathComponentCount)
	#define Path_extractComponent   (*(g_pPathCallTable)->pfnPathExtractComponent)
	#define Path_combine            (*(g_pPathCallTable)->pfnPathCombine)
#endif	
	
	//----------------------------------------------------------------------------------------------
	// Graph manager call table. Most of this is still defined elsewhere, since the graphics code
	// still uses a call table.
	//----------------------------------------------------------------------------------------------
	#define GRAPH_STRING "CTXGRAPH"
	
	#define GraphRunTimeInit(pLibMgr, pVer) \
		((*pLibMgr->pLMgrUse)(GRAPH_STRING,pVer,(PPLMGRTABLE)&g_pGraphCallTable))
	#define GraphRunTimeRelease(pLibMgr) \
		((*pLibMgr->pLMgrRelease)((PLMGTABLE)g_pGraphCallTable))
	
	
#ifdef __cplusplus
}
#endif

#endif /* _LIBMGR_H_ */
