/***************************************************************************
*
*  CTXMEM.H
*
*  This module contains the interfaces to the memory management abstraction.
*
*  The interfaces available to the client components include:
*     Mem_alloc(HND, ULONG, PVOID *)
*     Mem_realloc(HND, ULONG, PVOID *)
*     Mem_free(HND, PVOID)
*     Mem_allocZeroed(HND, ULONG, PVOID *)
*     Mem_cmp(const PVOID, const PVOID, ULONG)
*     Mem_cpy(PVOID, const PVOID, ULONG)
*     Mem_set(PVOID, UINT, ULONG)
*
*  RETURN VALUES:
*     MEM_SUCCESS is returned for success 
*     MEM_FAILURE is returned for failure
*
*  Copyright 1999-2006 Citrix Systems, Inc.  All Rights Reserved.
*
****************************************************************************/

#ifndef _CTXMEM_H_
#define _CTXMEM_H_

/*
 * Include platform specific setup
 */
#include <pctxmem.h>

#define MEM_SUCCESS    0
#define MEM_FAILURE    1
#define MEM_NO_MEMORY  2

/*
 * Define Default Pools
 */

#define MEM_GLOBAL_POOL       ((HND)1)
#define MEM_IO_POOL           ((HND)2)

/*
 * Define the memory abstraction function prototypes
 */
UINT _VPAPI Mem_alloc(HND poolId, size_t size, PVOID *ppBuffer);
UINT _VPAPI Mem_realloc(HND poolId, size_t size, PVOID *ppBuffer);
UINT _VPAPI Mem_free(HND poolId, PVOID pBuffer);
UINT _VPAPI Mem_allocZeroed(HND poolId, size_t size, PVOID *ppBuffer);

/*
 * Define the abstraction prototypes for memcmp, memset, and memcpy if macros
 * have not already been defined.  These macros are treated separately for 
 * simplicity and performance.  They are expected to be defined by the platform
 * via pctxmem.h.
 */

#ifndef Mem_cmp
UINT  _VPAPI Mem_cmp(const PVOID pBuf1, const PVOID pBuf2, ULONG size);
#endif

#ifndef Mem_cpy
PVOID _VPAPI Mem_cpy(PVOID pDest, const PVOID pSrc, ULONG size);
#endif

#ifndef Mem_set
PVOID _VPAPI Mem_set(PVOID pDest, UINT value, ULONG size);
#endif

#endif /* _CTXMEM_H_ */

