/*************************************************************************
*
*   platclib.h
*
*   MAC specific header file for C runtime routines.
*
*   Copyright 1999 Citrix Systems, Inc.  All Rights Reserved.
*
*   Revisions
*	15/05/2002	cbau	Move stricmp here; make it work with C++
*	17/01/2002	KTAM	strdup and strncasecmp have both been implemented
*				as part of the ANSI C library for gcc OSX.
*************************************************************************/

#ifndef _MAC_PLATCLIB_H_
#define _MAC_PLATCLIB_H_

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#include "clibcomm.h"

#define strnicmp strncasecmp
#define _strnicmp strnicmp

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	#if defined(_ANSI_SOURCE) || defined(__MWERKS__)
	extern char * strdup(const char *);
	extern int strncasecmp(const char *s1, const char *s2, int n);
	#endif

	extern char * strlwr(char *s1);
	extern ULONG host_getmsec( void);
	extern int sscanf(const char * s, const char * format, ...);
	extern int stricmp(const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef __cplusplus
	class istream;
	class ostream;
#endif /* __cplusplus */

#endif	/* _MAC_PLATCLIB_H_ */
