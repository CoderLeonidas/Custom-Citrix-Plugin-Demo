/*************************************************************************
 *
 *  Macintosh version of windos\platcall.h
 *
 *  Windows/DOS specific calling conventions
 *
 *	Copyright © Citrix Systems, Inc.  All rights reserved.
 *
 ************************************************************************/

#ifndef _MAC_PLATCALL_H_
#define _MAC_PLATCALL_H_
 
/*
 * Old calling convention macros.  These are deprecated as they are not
 * portable between WinDOS and Mac source. 
*/ 


#define _CAPI
#define _PASCALAPI
#define _FASTAPI   
#define _FAR_CAPI      
#define _FAR_PASCALAPI 
#define _FAR_FASTAPI   

#define _VPAPI  
#define _PVPAPI   * 
#ifndef WFCAPI
#define WFCAPI 
#endif
#ifndef PWFCAPI
#define PWFCAPI   *
#endif

#define WFCAPI_NOLOADDS 
#define PWFCAPI_NOLOADDS  *
#define WFCCALLBACK CALLBACK


/*
 * New calling convention macros.  The parameterisation of the return type
 * allows its position relative to the calling convention keywords to be
 * controlled, which is important as they follow the type on WinDOS platforms
 * but precede it on the Mac.
 */
 
#define _CCALL(type)            type
#define _PASCALCALL(type)       type
#define _FASTCALL(type)         type
#define _FAR_CCALL(type)        type
#define _FAR_PASCALCALL(type)   type
#define _FAR_FASTCALL(type)     type
#define WFCCALL(type)           type
#define PWFCCALL(type)          type
#define WFCCALL_NOLOADDS(type)  type
#define PWFCCALL_NOLOADDS(type) type
#define WFCCALLBACKCALL(type)   type

#endif
