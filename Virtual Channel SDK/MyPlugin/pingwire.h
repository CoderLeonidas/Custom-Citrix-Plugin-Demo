/*************************************************************************
*
*   This module contains the wire byte swapping routines for vdping
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

#ifndef _PING_WIRE_H
#define _PING_WIRE_H

// Functions for converting data in a VDPING_C2H or PING data structure between the layout on the
// client engine and the layout on the server. These functions are needed on bigendian architectures
// like PowerPC, and on architectures that need aligned data, like ARM. 
#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
USHORT Marshall_Write_VDPING_C2H(PVDPING_C2H input, USHORT inputSize);
USHORT Marshall_Write_PING(PPING input, USHORT inputSize);
void Marshall_Read_PING(LPVOID input, LPVOID output);
#endif // BIGEND || ALIGNMENT_REQUIRED

#endif 	/* _PING_WIRE_H */

