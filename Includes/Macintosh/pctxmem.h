/***************************************************************************
*
*  PCTXMEM.H
*
*  This module contains the base implementation of a platform specific
*  memory allocation and manipulation abstraction.
*
*  Version:	$Id: //icaclient/develop/main/src/inc/unix/pctxmem.h#4 $
*
*  Copyright 1999 Citrix Systems, Inc.  All Rights Reserved.
*
****************************************************************************/

#ifndef _PCTXMEM_H_
#define _PCTXMEM_H_

/*
 *  Include string.h to get the memcpy type interfaces.  These interfaces
 *  are part of the memory abstraction.
 */

#include <string.h>

PVOID WFCAPI 
Mem_move(PVOID pDest, const PVOID pSrc, ULONG size);

#endif /* _PCTXMEM_H_ */

