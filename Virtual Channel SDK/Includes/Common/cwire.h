/***************************************************************************
*
*  cwire.h
*
*  This module contains swapping macros for bigendian platforms
*
*   Written by: davidh@ctxuk.citrix.com
*   Date: 15 June 1999
*
*   revision: $Id$
*
*   Copyright (c) 1999-2000, 2009 Citrix Systems, Inc. All Rights Reserved.
*
****************************************************************************/

#ifndef _CWIRE_H_
#define _CWIRE_H_

/* Wire macro definitions.											*/
/*																	*/
/* For write operations the destination pointer is incremented. 	*/
/* For read operations the source pointer is incremented. 			*/
/* Its is intended that the pointer to the wire buffer that is 		*/
/* incremented.														*/



#ifdef BIGEND
	#define ctx_wire_write8(src, dst)	{_ctx_copy8(((LPBYTE) src), ((LPBYTE) dst)) dst += 1 ; }
	#define ctx_wire_write16(src, dst)	{_ctx_swap16(((LPBYTE) src), ((LPBYTE) dst)) dst += 2 ; }
	#define ctx_wire_write32(src, dst)	{_ctx_swap32(((LPBYTE) src), ((LPBYTE) dst)) dst += 4 ; }

	#define ctx_wire_read8(src, dst)	{_ctx_copy8(((LPBYTE) src), ((LPBYTE) dst)) src += 1 ; }
	#define ctx_wire_read16(src, dst)	{_ctx_swap16(((LPBYTE) src), ((LPBYTE) dst)) src += 2 ; }
	#define ctx_wire_read32(src, dst)	{_ctx_swap32(((LPBYTE) src), ((LPBYTE) dst)) src += 4 ; }
#else
	#define ctx_wire_write8(src, dst)	{_ctx_copy8(((LPBYTE) src), ((LPBYTE) dst)) dst += 1 ; }
	#define ctx_wire_write16(src, dst)	{_ctx_copy16(((LPBYTE) src), ((LPBYTE) dst)) dst += 2 ; }
	#define ctx_wire_write32(src, dst)	{_ctx_copy32(((LPBYTE) src), ((LPBYTE) dst)) dst += 4 ; }

	#define ctx_wire_read8(src, dst)	{_ctx_copy8(((LPBYTE) src), ((LPBYTE) dst)) src += 1 ; }
	#define ctx_wire_read16(src, dst)	{_ctx_copy16(((LPBYTE) src), ((LPBYTE) dst)) src += 2 ; }
	#define ctx_wire_read32(src, dst)	{_ctx_copy32(((LPBYTE) src), ((LPBYTE) dst)) src += 4 ; }
#endif






#define _ctx_copy8(src, dst) \
	if (src != dst) \
		dst [0] = src [0] ; 



#ifdef BIGEND
// Bigendian machines: Copy two or four bytes and swap them around at the same time.
#define _ctx_swap16(src, dst) \
	if (src == dst) { \
		BYTE temp = src[0]; \
		src[0] = src[1]; \
		src[1] = temp; \
	} else { \
		dst[0] = src[1]; \
		dst[1] = src[0]; \
	} 

	

#define _ctx_swap32(src, dst) \
	if (src == dst) { \
		BYTE temp = src[0]; \
		src[0] = src[3]; \
		src[3] = temp; \
		temp = src[1]; \
		src[1] = src[2]; \
		src[2] = temp; \
	} else { \
		dst[0] = src[3]; \
		dst[3] = src[0]; \
		dst[1] = src[2]; \
		dst[2] = src[1]; \
	} 

#else
// Littleendian machines: Copy two or four bytes without swapping them.
#define _ctx_copy16(src, dst) \
	if (src != dst) { \
		unsigned char tmp0 = src [0]; \
		unsigned char tmp1 = src [1]; \
		dst [0] = tmp0; \
		dst [1] = tmp1; \
	}

#define _ctx_copy32(src, dst) \
	if (src != dst) { \
		unsigned char tmp0 = src [0]; \
		unsigned char tmp1 = src [1]; \
		unsigned char tmp2 = src [2]; \
		unsigned char tmp3 = src [3]; \
		dst [0] = tmp0; \
		dst [1] = tmp1; \
		dst [2] = tmp2; \
		dst [3] = tmp3; \
	}
#endif





#endif /* _CWIRE_H_ */

