/***************************************************************************
*
*  DLLAPI.H
*
*  This module contains client DLL access definitions
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
****************************************************************************/

#ifndef __DLLAPI_H__
#define __DLLAPI_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _EMBEDDLL FAR *PEMBEDDLL;
/*
 *  DLL link structure
 */
typedef struct _DLLLINK {
    USHORT Segment;             /* starting seg of mem allocated for dll (aligned) */
    USHORT DllSize;             /* actual size of dll in paragraphs */
    USHORT ProcCount;           /* number of procedures in call table */
    PVOID pProcedures;          /* pointer to procedure call table */
    PVOID pData;                /* pointer to dll data structure */
    PUCHAR pMemory;             /* pointer to malloced memory (not aligned) */
    char ModuleName[13];        /* client module name (8.3) */
    LPVOID pLibMgrCallTable;    // Pointer to lib manager table (used by VCSDK only)
    USHORT ModuleDate;          /* module date in dos format */
    USHORT ModuleTime;          /* module time in dos format */
    ULONG ModuleSize;           /* module file size in bytes */
    struct _DLLLINK * pNext;    /* pointer to next DLLLINK structure */
    ULONG DllFlags;             /* DLL flags (embed..) */
    /* Everything after here is not included for the ModuleEnum call. */

    HND		LibraryHandle;		// Result of DLib_create or Embed_create

} DLLLINK, * PDLLLINK;

typedef int (PWFCAPI PMAINLOAD)( PDLLLINK );
#define ENUM_DLLLINK_SIZE (sizeof(DLLLINK))  

/*
 * Dll flags definition (32 of them possible)
 */
#define DLL_FLAGS_EMBED    1

typedef int (PWFCAPI PLOADPROCEDURE)( PDLLLINK, USHORT );
typedef int (PWFCAPI PDLLPROCEDURE)( PVOID, PVOID, PUINT16 );

 
int WFCAPI ModuleInit(  PDLLLINK, PMAINLOAD,PEMBEDDLL );
int WFCAPI ModuleUninit( VOID );

int WFCAPI ModuleLoad( char *, PDLLLINK );
int WFCAPI ModuleUnload( PDLLLINK );
int WFCAPI ModuleEnum( LPBYTE, USHORT, PUSHORT );
int WFCAPI ModuleCall( PDLLLINK, USHORT, PVOID, PUINT16 );

/*
 *  ExeOpen structure
 */
typedef struct _EXEOPEN {
    void* unused;
} EXEOPEN, * PEXEOPEN;


/*=============================================================================
 ==   Common dll entry points for all dlls
 ============================================================================*/
 

#define DLLxLOAD                 0
#define DLLxUNLOAD               1
#define DLLxOPEN                 2
#define DLLxCLOSE                3
#define DLLxINFO                 4
#define DLLxPOLL                 5

/*
 *  DLLxCLOSE structure
 */
typedef struct _DLLCLOSE {
    int NotUsed;
} DLLCLOSE, * PDLLCLOSE;

/*
 *  DLLxINFO structure
 */
typedef struct _DLLINFO {
    LPBYTE pBuffer;
    USHORT ByteCount;
} DLLINFO, * PDLLINFO;

/*
 *  DLLxPOLL structure
 */
typedef struct _DLLPOLL {
    ULONG CurrentTime;          /* current time in msec */
} DLLPOLL, * PDLLPOLL;

typedef INT (PWFCAPI PEMBEDLOAD)( PDLLLINK pLink );

typedef struct _EMBEDDLL {
  char      *DllName;                  /* name of DLL */
  PEMBEDLOAD DllLoad;                  /* DLL load function */
  PVOID      pfnMain;                  /* DLL LIBMAIN or DLLMain entry */
} EMBEDDLL;


#ifdef __cplusplus
}
#endif

#endif /* __DLLAPI_H__ */
