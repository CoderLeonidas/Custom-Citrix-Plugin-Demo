/*************************************************************************
 *
 *  plat.h
 *
 *  Mac specific platform types
 *
 *	Copyright © Citrix Systems, Inc.  All rights reserved.
 *
 ************************************************************************/

#ifndef _MAC_PLAT_H_  
#define _MAC_PLAT_H_

/* Define WINAPI as nothing. WINAPI is used in many places in the code and should be
 * replaced with nothing on MacOS X. */
#define WINAPI

/* Defined on Macs (macintosh) and probably on Unix. */
#define MacOrUnix

/* Define base/host client features */

#include <basetype.h>
#include <hostfeat.h>
#include <basefeat.h>
#include <host_os.h>



/*
 *----------------------------------------------------------------------------
 *  UNIFICATION : Defines to get common WD compiling/working on Macintosh                
 *----------------------------------------------------------------------------
 */

/* This should really be split up between all the plat*.h files but it is easier
 * having them here for convenience.
 */

/* Calls to malloc, realloc and free are redirected to host_malloc, host_realloc and
 * host_free; there is no substitute for calloc but the linker will tell you. 
 *
 * Note that host_malloc, host_realloc and host_free don't like to allocate 0 bytes, 
 * or free or reallocate a null pointer which would be legal for malloc, realloc and
 * free, so that kind of call should be avoided. 
 */

#define realloc(a, s) host_realloc(a, s)
#define malloc(a) host_malloc(a)
#define free(a) host_free(a)
#define calloc(n,s) host_calloc(n,s)
#define strdup(s) host_strdup(s)

/* Macintosh or Unix wants TWI interface. It causes TWI_INTERFACE_ENABLED to be defined. */
#define USE_TWI

/* Use call tables only for graphics; we currently need the call table because srcc modifies it. */
#define USE_GRAPH_CALL_TABLE


/* ZLC functionality */

#define VDZLC_EMBEDDED      	  /* Add Zero Latency to the build */
//#define ZLC_GENERIC2_DISABLED   /* disable generic 2 for now */
#define ZLC_MENU_ENABLED		  /* Enable ZLC menu */

#define VDTWI_EMBEDDED      /* TWI is an embedded module */
#define VDTW_EMBEDDED       /* TW is an embedded module */


/* These used to be in dll.c */

#define DIR_SEPARATOR 		'/'
#define NON_DIR_SEPARATOR	'\\'

/* Maximum file path length */

#define PATH_MAX_SIZE 256
#define MAX_PATH	 PATH_MAX_SIZE

/* High/Low word extraction macros */

#define LOWORD(x)	((x)&0xFFFF)
#define HIWORD(x) 	((x)>>16)

/* Poll network from witin main thinwire loop to fix network timeouts */

#define TW_YIELD

#ifdef TW_YIELD
/* function prototype */
void TWYield(void);
void DisableTWYield(Boolean disable);
#endif 

#define NO_CLIP_BLT 

/* Make UDP and HTTP name resolvers embedded */

#define NR_EMBEDDED


#define _MAX_PATH 1024

/* Enable kerberos pass-through authentication */

#define ENABLE_MAC_PASSTHROUGH_AUTHENTICATION


/*
 *----------------------------------------------------------------------------
 *  UNIFICATION: End              
 *----------------------------------------------------------------------------
 */


/*  Mac specific ini file settings
*/

/*	The Mac clipboard copies all available clipboard formats
	as soon as they are available. For copying an entire Excel
	spreadsheet copying the selection as a picture causes the
	server to fail with an "out of memory" error. To get around
	the problem, allow the user to select a "text only" clipboard.
*/
#define INI_GRAPHICSCLIPBOARD	"DisableGraphicsClipboard"
#define DEF_GRAPHICSCLIPBOARD	FALSE
#define INI_CLIPBOARDTIMEOUT	"ClipboardTimeout"
#define DEF_CLIPBOARDTIMEOUT	300		/* Clipboard timeout in 60ths of a second */

/* CPR 171032: Raising the value of the SCBeginTransaction call timeout (in millisecs) */
#define INI_SCMACWATCHDOG		"MacSCWatchdogMSecs"
#define DEF_SCMACWATCHDOG		2000


/* Define _INLINEAPI as static; this works on all compilers, and optimising compilers will inline
 * static functions when it is beneficial anyway. */
#define _INLINEAPI	static

/* UNREFERENCED_PARAMETER for platcomm.h */
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)   ((void) (P))
#endif

/*
 *  #pragma macros
 */

#if 0 
#define PLATFORM_PRAGMAS  /* no we don't */
#endif

#define ENG_PACKING_ENABLE  /*pack(8)*/
#define ENG_PACKING_RESTORE /*pack()*/

#include <platcall.h>
#include <platcomm.h>

#include <platfix.h> /* Include fixups needed to build client with new unfication code */

#define ICA_SET_LED IcaChangeLed

/*
 * If this is defined we force 8 bit conenctions to use tw1 instead of tw2 if that can be used
 */
 
//#define FORCE_TW1_FOR_8_BIT

#endif /* _MAC_PLAT_H_ */
