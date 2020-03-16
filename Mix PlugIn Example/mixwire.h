/*************************************************************************
*
*   This module contains the wire byte swapping routines for vdmix
*
*   Copyright 2001, 2009 Citrix Systems, Inc.  All Rights Reserved.
*
*   Citrix hereby permits you to use, reproduce, modify, display, compile,
*   sublicense, and distribute all or any portion of the sample code contained
*   in this file, provided that you remove this Copyright attribution from any
*   modified version of this file.
*
*   THIS SAMPLE CODE IS PROVIDED BY CITRIX "AS IS" AND ANY EXPRESS OR IMPLIED
*   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
*
*************************************************************************/

#ifndef _MIX_WIRE_H
#define _MIX_WIRE_H

// Functions for converting data in a VDMIX_C2H or MIXHEAD data structure between the layout on the
// client engine and the layout on the server. These functions are needed on bigendian architectures
// like PowerPC, and on architectures that need aligned data, like ARM. There is a problem because
// we don't actually convert a MIXHEAD data structure but a bigger structure; this is Ok when writing
// to the server because conversion is done in place; when reading from the server, we need to
// make sure that there is more space, which is done by defining a struct MIXHEAD_PLUS with
// additional space.
#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
USHORT Marshall_Write_VDMIX_C2H(PVDMIX_C2H input, USHORT inputSize);
USHORT Marshall_Write_MIXHEAD(PMIXHEAD input, USHORT inputSize);
void Marshall_Read_MIXHEAD_PLUS(LPVOID input, LPVOID output);
#endif // BIGEND || ALIGNMENT_REQUIRED

#endif 	/* _MIX_WIRE_H */

