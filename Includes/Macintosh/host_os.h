/*[
 ******************************************************************************
 *
 *	Name:			host_os.h
 *
 *	Derived From:	SoftWindows insignia.h, base_def.h, host_def.h
 *
 *	Author:			Rob Tizzard
 *
 *	Created:		12 February 1996
 *
 *	Purpose:		Defines things required to interface to this host's
 *					operating system.  This may be macros that map system
 *					or library calls, base/host/Mac/Unix interface, or
 *					defines that are required in order to keep system
 *					header files doing the right thing.
 *
 *	Copyright Insignia Solution PLC, 1996.  All rights reserved.
 *  Copyright © Citrix Systems, Inc.  All rights reserved.
 *
 ******************************************************************************
]*/
#ifndef _HOST_OS_H_
#define _HOST_OS_H_

#include <sys/socket.h>

/*
 *----------------------------------------------------------------------------
 *  Macros to define include file directory structure.                        
 *----------------------------------------------------------------------------
 */

#define Public(x)	#x
#define Private(x)	#x
#define Tw(x)		#x
#define Wd(x)		#x
#define Vd(x)		#x
#define Td(x)		#x
#define Pd(x)		#x
#define Ncs(x)		#x
#define Unix(x)		#x
#define Swapper(x)	#x
#define Ne(x)		#x
#define Nr(x)		#x
#define Ggi(x)		#x
#define Cam(x)		#x
#define	Cpm(x)		#x
#define Cdm(x)		#x
#define License(x)	#x
#define Cm(x)		#x
#define Ccm(x)		#x
#define I18n(x)     #x

/*
 *----------------------------------------------------------------------------
 *  Mappings for base include files.                       
 *----------------------------------------------------------------------------
 */

#define StringH	        <string.h>
#define TimeH	        <time.h>
#define MallocH	        <stdlib.h>
#define StatH	        <sys/stat.h>
#define UnistdH         <stdio.h>
//#define TypesH          <types.h>

/*
 *----------------------------------------------------------------------------
 *  System specific defines                  
 *----------------------------------------------------------------------------
 */

//
// Either define BIGEND to a value of 01 or undefine it. Defining to the weird value of 01 has the
// advantage that we find out if this is a redefinition. If __DARWIN_BYTE_ORDER is defined then we
// use it to determine the byte order, otherwise we go by the processor type.
//
#if __DARWIN_BYTE_ORDER && __DARWIN_BIG_ENDIAN && __DARWIN_LITTLE_ENDIAN
	#if __DARWIN_BYTE_ORDER == __DARWIN_BIG_ENDIAN
		#define BIGEND				01
	#elif __DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
		#undef BIGEND
	#else
		#error undefined byte order
	#endif
#else
	#ifdef XCODE_INTEL
		#undef BIGEND						/* Intel Macs are not big-endian! */
	#else
		#error undefined architecture
	#endif /* XCODE_INTEL */
#endif

//
// ALIGNMENT_REQUIRED is defined as 1 (XCODE_ARM) and undefined (elsewhere).
//
// This macro tells all code whether pointers need to be correctly aligned. On PowerPC and Intel
// processors, unaligned reads and writes are just a tiny fraction slower than aligned operations,
// so adding code to work around the problem would just slow things down. On an ARM processor,
// unaligned reads and writes are signficantly slower; measurements showed that on an iPod Touch,
// each unaligned read or write takes about four microseconds or many hundred instructions.
#if XCODE_ARM
#define ALIGNMENT_REQUIRED 1
#else
#undef ALIGNMENT_REQUIRED
#endif


//
// Define LITTLE_ENDIAN_MACHINE and NEED_ALIGNMENT as alternatives. They are always defined.
//
#ifdef BIGEND
#define LITTLE_ENDIAN_MACHINE   00
#else
#define LITTLE_ENDIAN_MACHINE   01
#endif

#ifdef ALIGNMENT_REQUIRED
#define NEED_ALIGNMENT			01
#else
#define NEED_ALIGNMENT			00
#endif


#if (LITTLE_ENDIAN_MACHINE) && (! NEED_ALIGNMENT)
#define LOAD_LITTLE_ENDIAN_ULONG_UNALIGNED(v,p)     do { (v) = *(uint32_t *)(p); } while (0)
#define LOAD_LITTLE_ENDIAN_USHORT_UNALIGNED(v,p)    do { (v) = *(uint16_t *)(p); } while (0)
#define STORE_LITTLE_ENDIAN_USHORT_UNALIGNED(v,p)   do { * (uint16_t *)(p) = (v); } while (0)
#define STORE_LITTLE_ENDIAN_ULONG_UNALIGNED(v,p)    do { * (uint32_t *)(p) = (v); } while (0)
#else
#define LOAD_LITTLE_ENDIAN_ULONG_UNALIGNED(v,p)														\
	do {																							\
		uint8_t * p__ = (p);																		\
		(v) = p__ [0] | (p__ [1] << 8) | (p__ [2] << 16) | (p__ [3] << 24);							\
	} while (0)

#define LOAD_LITTLE_ENDIAN_USHORT_UNALIGNED(v,p)													\
	do {																							\
		uint8_t * p__ = (p);																		\
		(v) = p__ [0] | (p__ [1] << 8);																\
	} while (0)

#define STORE_LITTLE_ENDIAN_USHORT_UNALIGNED(v,p)													\
	do {																							\
		uint8_t * p__ = (p);																		\
		uint16_t v__ = (v);																			\
		p__ [0] = (v__ >> 0); p__ [1] = (v__ >> 8);													\
	} while (0)

#define STORE_LITTLE_ENDIAN_ULONG_UNALIGNED(v,p)													\
	do {																							\
		uint8_t * p__ = (p);																		\
		uint32_t v__ = (v);																			\
		p__ [0] = (v__ >> 0); p__ [1] = (v__ >> 8); p__ [2] = v__ >> 16); p__ [3] = v__ >> 24;		\
	} while (0)

#endif


//
// Defines for generic sockaddr storage
//
#define GEN_SOCKADDR_STORAGE_SIZE   (sizeof(struct sockaddr_storage))
#define GEN_SOCKADDR_STORAGE        struct sockaddr_storage
#define PGEN_SOCKADDR_STORAGE       struct sockaddr_storage *

/*
 *----------------------------------------------------------------------------
 *  Mappings for base functions                 
 *----------------------------------------------------------------------------
 */

#define host_open(name,flags,perms)  open(name,flags,perms)

#define host_getenv		getenv
#define host_access		access

#define host_socket_errno WSAGetLastError()
#define host_socket_close closesocket

IMPORT IU32 host_get_keyboard_layout( IU32 IU32DefaultLayout);

IMPORT void host_NCS_shutdown( void);


/*
 *----------------------------------------------------------------------------
 *  Mappings for base constants               
 *----------------------------------------------------------------------------
 */

#define DIR_DELIM "\0"
#define DEF_ICAROOT "\0"

/*
 *----------------------------------------------------------------------------
 *  Prototypes for standard unix functions not supported by system.              
 *----------------------------------------------------------------------------
 */

#if defined(_ANSI_SOURCE) || defined(__MWERKS__)
IMPORT int strncasecmp(const char *s1, const char *s2, int n);
#endif

/*
 *----------------------------------------------------------------------------
 *  Prototypes for host memory handling functions.             
 *----------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" { 
#endif

	IMPORT void *host_malloc(unsigned long size);
	IMPORT void host_free(void *ptr);
	IMPORT void *host_calloc( unsigned long nmemb, unsigned long size);
	IMPORT void *host_realloc(void *p, unsigned long  size);
	IMPORT char *host_strdup(const char* s);
	IMPORT void host_memcpy(void *dstPtr, void *srcPtr, unsigned long  size);
	IMPORT void *host_memset(void *dstPtr, int c, unsigned long n);			
	IMPORT void host_memmove(void *dstPtr, void *srcPtr, unsigned long  size);
	IMPORT int  host_memcmp(void *dstPtr, void *srcPtr, unsigned long  size);

#ifdef __cplusplus
}
#endif

#define host_bcopy(srcPtr,dstPtr,size) host_memcpy(dstPtr,srcPtr,size)


/*
 *----------------------------------------------------------------------------
 *  Prototypes for ansi string handling routines.             
 *----------------------------------------------------------------------------
 */

IMPORT int host_AnsiUpper (char *string) ;


/*
 *----------------------------------------------------------------------------
 *  Windows'isms that we need to remove/redefine
 *----------------------------------------------------------------------------
 */
#define CALL_TYPE		/* __sdtcall */


#endif /* _HOST_OS_H_ */
