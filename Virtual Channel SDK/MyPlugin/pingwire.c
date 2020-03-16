/*************************************************************************
*
*   This module contains the wire byte swapping routines for PING
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

#include <citrix.h>
#include <cwire.h>
#include <ica.h>
#include <ica-c2h.h>
#include <icacaps.h>
#include <wdwire.h>
#include <cmacro.h>

#include "vdping.h"
#include "pingwire.h"

/****************************************************************************
 *
 *  Marshall_Write_VDPING_C2H
 *
 *    Marshalls the VDPING_C2H data structure from client format to server 
 *	  format onto the wire to be sent to the server. This routine is required 
 *	  on bigendian platforms (like PowerPC) and on platforms that have stricter
 *	  alignment requirements (like ARM).
 *
 * ENTRY:
 *    pointer to wire buffer containing the VDPING_C2H structure in client format,
 *    not necessarily packed on byte boundaries.
 *
 * EXIT:
 *    returns the packed size of the data written to the wire
 *
 ***************************************************************************/

#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
USHORT Marshall_Write_VDPING_C2H (PVDPING_C2H input, USHORT inputSize)
{
	// The caller supplies the size of the data. This is actually not needed here; it is only 
	// needed on little-endian platforms where the WIRE_WRITE macro just calls memcpy.
	UNREFERENCED_PARAMETER (inputSize);
	
	// "input" uses the byte ordering and the structure layout of the client machine. "writePtr"
	// uses the byte ordering and the structure layout of the server, which is always packed as
	// much as possible. We need to keep track of both separately, in case the structure layout
	// is not the same. Since the Marshall_Write_ functions do a conversion in place, this will
	// only work if the structure layout on the client is the same or larger as on the server.
	LPBYTE writePtr = (LPBYTE)input;

	// First translate the header. This function does an in-place conversion and returns the number
	// of bytes generated. We update the writePtr accordingly so that it will point past the
	// converted data of the C2H header. 
	writePtr += Marshall_Write_VD_C2H (&input->Header, sizeof (VD_C2H));

	// Translate the data specific to this plugin. There are two sixteen bit quantities, they have
	// to be translated in the right order. The macro ctx_wire_write16 will increase the variable
	// writePtr by two bytes. 
	ctx_wire_write16(&input->usMaxDataSize, writePtr);
	ctx_wire_write16(&input->usPingCount, writePtr);

	// Return the number of bytes generated, this is the difference between writePtr after copying
	// all the data, and the initial value of writePtr. 
	return ((USHORT)(writePtr - (LPBYTE)input));
}
#endif // BIGEND || ALIGNMENT_REQUIRED

/****************************************************************************
 *
 *  Marshall_Write_PING
 *
 *    Marshalls the PING data structure from client format to server 
 *	  format onto the wire to be sent to the server. This routine is required 
 *	  on bigendian platforms (like PowerPC) and on platforms that have stricter
 *	  alignment requirements (like ARM).
 *
 * ENTRY:
 *    pointer to wire buffer containing the PING structure in client format,
 *    not necessarily packed on byte boundaries.
 *
 * EXIT:
 *    returns the packed size of the data written to the wire
 *
 ***************************************************************************/

#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
USHORT Marshall_Write_PING (PPING input, USHORT inputSize)
{
	// The caller supplies the size of the data. This is actually not needed here; it is only 
	// needed on little-endian platforms where the WIRE_WRITE macro just calls memcpy.
	UNREFERENCED_PARAMETER (inputSize);
	
	// "input" uses the byte ordering and the structure layout of the client machine. "writePtr"
	// uses the byte ordering and the structure layout of the server, which is always packed as
	// much as possible. We need to keep track of both separately, in case the structure layout
	// is not the same. Since the Marshall_Write_ functions do a conversion in place, this will
	// only work if the structure layout on the client is the same or larger as on the server.
	LPBYTE writePtr = (LPBYTE)input;

	// Translate the data specific to this plugin. There are four sixteen bit quantities, followed
	// by two 32-bit quantities. They have to be translated in the right order. The macro 
	// ctx_wire_write16 will increase the variable writePtr by two bytes, ctx_wire_write32 increases
	// it by four bytes.
	ctx_wire_write16(&input->uSign, writePtr);
	ctx_wire_write16(&input->uType, writePtr);
	ctx_wire_write16(&input->uLen, writePtr);
	ctx_wire_write16(&input->uCounter, writePtr);
	ctx_wire_write32(&input->ulServerMS, writePtr);
	ctx_wire_write32(&input->ulClientMS, writePtr);

	// Return the number of bytes generated, this is the difference between writePtr after copying
	// all the data, and the initial value of writePtr. 
	return ((USHORT)(writePtr - (LPBYTE)input));
}
#endif // BIGEND || ALIGNMENT_REQUIRED

/****************************************************************************
 *
 *  Marshall_Read_PING
 *
 *    Marshalls the PING data structure from server format received from the
 *	  wire to client format. This routine is required on bigendian platforms
 *	  (like PowerPC) and on platforms that have stricter alignment requirements (like ARM).
 *
 * ENTRY:
 *    void pointer to wire buffer containing the data (input), and the
 *    buffer that the data is to be swapped into (output).
 *
 ***************************************************************************/

#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
void Marshall_Read_PING(LPVOID input, LPVOID output)
{
	// "input" uses the byte ordering and the structure layout of the server, while "output" uses
	// the byte ordering and the structure layout of the client engine. The caller has provided
	// separate buffers for both, since the sizes of the structures could be different. 
	LPBYTE readPtr = (LPBYTE)input;
	PPING writePtr = (PPING)output;

	// Translate the data specific to this plugin. There are four sixteen bit quantities, followed
	// by two 32-bit quantities. They have to be translated in the right order. The macro 
	// ctx_wire_read16 will increase the variable readPtr by two bytes, ctx_wire_read32 increases
	// it by four bytes.
	ctx_wire_read16(readPtr, &writePtr->uSign);
	ctx_wire_read16(readPtr, &writePtr->uType);
	ctx_wire_read16(readPtr, &writePtr->uLen);
	ctx_wire_read16(readPtr, &writePtr->uCounter);
	ctx_wire_read32(readPtr, &writePtr->ulServerMS);
	ctx_wire_read32(readPtr, &writePtr->ulClientMS);
}
#endif // BIGEND || ALIGNMENT_REQUIRED


