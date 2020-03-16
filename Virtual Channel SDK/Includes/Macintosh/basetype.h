/*[
 ******************************************************************************
 *
 *	Name:		basetype.h
 *
 *	Purpose:	Defines a number of replacements for standard C types.
 *
 *	Copyright © Citrix Systems, Inc.  All rights reserved.
 *
 ******************************************************************************
]*/

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_

/*
 * Insignia Standard Storage Classes
 */

#define GLOBAL				/* Defined as nothing */
#define LOCAL	static			/* Local to the source file */

/*
 * These seem to be used by Microsoft (Licensing code) in parameters
 */
#define IN
#define OUT
#define INOUT

/*
 * A nice word to replace extern
 */

#define IMPORT	extern

//
// Types marked as 8, 16, 32 or 64 bits are based on the Standard C types. On MacOS X the 32 bit
// types are actually "int" and "unsigned int", both on 32 and 64 bit OS which is good to know
// for printf and trace statements. 
//
typedef int8_t		IS8,  INT8,   *PINT8,   *LPINT8;
typedef uint8_t		IU8,  UINT8,  *PUINT8,  *LPUINT8;
typedef int16_t		IS16, INT16,  *PINT16,  *LPINT16;
typedef uint16_t	IU16, UINT16, *PUINT16, *LPUINT16;
typedef int32_t		IS32, INT32,  *PINT32,  *LPINT32;
typedef uint32_t	IU32, UINT32, *PUINT32, *LPUINT32;
typedef int64_t			  INT64,  *PINT64;
typedef uint64_t		  UINT64, *PUINT64;

//
// Minimum width types to confuse the programmer. Rarely used.
//
typedef unsigned int IUM16, IUM32;
typedef int ISM32;

//
// Two incompatible boolean types. There is also BOOL which is defined by Objective-C. 
//
typedef unsigned int IBOOL, *PIBOOL, *LPIBOOL;
typedef unsigned char BOOLEAN, *PBOOLEAN, *LPBOOLEAN;

//
// Pointless typedefs for void, void*, void** etc.
//
#define VOID void
typedef void		*PVOID, *LPVOID, **PPVOID;

// Pointless typedefs for char, short, int, and long long. 
typedef char				CHAR, *PCHAR, *LPCHAR, **PPCHAR;
typedef unsigned char		UCHAR, *PUCHAR, *LPUCHAR, **PPUCHAR;
typedef short				SHORT;
typedef unsigned short		USHORT, *PUSHORT, *LPUSHORT;
typedef int    				INT, *LPINT;
typedef unsigned int		UINT, *PUINT, *LPUINT;
typedef unsigned long long	ULONGLONG;

//
// Tricky typedefs for LONG. When we say LONG, we actually mean 32 bits. However, CoreFoundation
// already defines ULONG so we will be compatible with that. As a result, LONG has different types
// on 32 and 64 bit builds, but is always 32 bits. 
//
typedef SInt32		LONG;
typedef UInt32		ULONG, *PULONG, *LPULONG;

//
// Typedefs meant for strings and C strings
//
typedef char		*LPSTR, *LPCSTR;

//
// Wide characters. We don't actually support wide characters in any meaningful way; these types are
// just needed to make things compile. If we wanted to support this, we should include <wchar.h> instead. 
//
typedef unsigned short	WCHAR, *PWCHAR;

//
// Various windowisms and pointers to them. Note: HWND is an actual Windows window pointer and 
// shouldn't be used at all. 
//
typedef uint8_t		BYTE, *PBYTE, *LPBYTE;
typedef uint16_t	WORD, *LPWORD;
typedef uint32_t	DWORD, *PDWORD, *LPDWORD;

typedef int32_t		LRESULT;
typedef int32_t		LPARAM;

typedef void		*HANDLE, **LPHANDLE, *HGLOBAL, *HINSTANCE, *HBITMAP;
typedef void		*HWND;

//
// Eliminating PC things from our code.
//
#undef FAR
#undef __cdecl

#define FAR 
#define __cdecl


#define UNUSED() /* UNUSED MACRO */

#endif /* _BASETYPE_H_ */
