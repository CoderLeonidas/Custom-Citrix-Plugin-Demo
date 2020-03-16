/*[
 ******************************************************************************
 *
 *	Name:		basefeat.h
 *
 *	Derived From:	basetypes.h
 *
 *	Author:		David Peter
 *
 *	Created:	15th May 1998
 *
 *	Version:	$Id$
 *
 *	Purpose:	Defines features common across all platforms.
 *
 *	Copyright 1998 - 2012 Citrix Systems, Inc. All rights reserved.
 *
 ******************************************************************************
]*/

#ifndef _BASE_FEAT_H_
#define _BASE_FEAT_H_

/* turn on Unicode support and Extended Unicode Keyboard Support*/
#define UNICODESUPPORT
#define USE_EUKS

/* turn on persistent caching features */
#define DIM

/* CTX_PACKED_STRUCT is needed for hosts that use gcc - it is added to
 * structure declarations to mark them as packed. If a host needs it, it
 * should be defined in hostfeat.h. Here we declare a default version.
 */

#ifndef CTX_PACKED_STRUCT
#define CTX_PACKED_STRUCT
#endif

/* Similarly ODD_PACKED_STRUCT is needed on some hosts. */

#ifndef ODD_PACKED_STRUCT
#define ODD_PACKED_STRUCT
#endif

/* turn on support for old-style configuration where Server section entries 
 * can override defaults in WFClient sections.
 */
#define SUPPORT_OLD_CONFIG


#endif /* _BASE_FEAT_H */
