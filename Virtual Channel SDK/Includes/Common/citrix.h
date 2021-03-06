/***************************************************************************
*
*   citrix.h
*
*   This file provides the basic macros and types common to all platforms,
*   and those defined for the particular platform that is being built.
*
*   The actual platform-specific definitions are included from the platform
*   sub-directory whose location is specified by the appropriate compiler
*   option.
*
*   Copyright © Citrix Systems, Inc.  All rights reserved.
*
****************************************************************************/

#ifndef _CITRIX_H_
#define _CITRIX_H_

/*
 * Include platform-specific header files related to the platform
 * tools and the platform types.
 */
#include "plat.h"
#include "plattool.h"
#include "platsys.h"

/*
 * Include common header files.
 */

#include "utilmacros.h"

#endif /* _CITRIX_H_ */
