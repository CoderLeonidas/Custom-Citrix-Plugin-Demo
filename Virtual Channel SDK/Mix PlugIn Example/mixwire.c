/*************************************************************************
*
*   This module contains the wire byte swapping routines for MIX
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

#include "vdmix.h"
#include "mixwire.h"

/****************************************************************************
 *
 *  Marshall_Write_VDMIX_C2H
 *
 *    Marshalls the VDMIX_C2H data structure from client format to server 
 *	  format onto the wire to be sent to the server. This routine is required 
 *	  on bigendian platforms (like PowerPC) and on platforms that have stricter
 *	  alignment requirements (like ARM).
 *
 * ENTRY:
 *    pointer to wire buffer containing the VDMIX_C2H structure in client format,
 *    not necessarily packed on byte boundaries.
 *
 * EXIT:
 *    returns the packed size of the data written to the wire
 *
 ***************************************************************************/

#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
USHORT Marshall_Write_VDMIX_C2H (PVDMIX_C2H input, USHORT inputSize)
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

	// Translate the data specific to this plugin. There is one sixteen bit quantitiy which has
	// to be translated after the header. The macro ctx_wire_write16 will increase the variable
	// writePtr by two bytes. 
	ctx_wire_write16(&input->usMaxDataSize, writePtr);

	// Return the number of bytes generated, this is the difference between writePtr after copying
	// all the data, and the initial value of writePtr. 
	return ((USHORT)(writePtr - (LPBYTE)input));
}
#endif // BIGEND || ALIGNMENT_REQUIRED

/****************************************************************************
 *
 *  Marshall_Write_MIXHEAD
 *
 *    Marshalls the MIXHEAD data structure from client format to server 
 *	  format onto the wire to be sent to the server. This routine is required 
 *	  on bigendian platforms (like PowerPC) and on platforms that have stricter
 *	  alignment requirements (like ARM).
 *
 * ENTRY:
 *    pointer to wire buffer containing the MIXHEAD structure in client format,
 *    not necessarily packed on byte boundaries.
 *
 * EXIT:
 *    returns the packed size of the data written to the wire
 *
 ***************************************************************************/

#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
USHORT Marshall_Write_MIXHEAD (PMIXHEAD input, USHORT inputSize)
{
	// Save some bits from the MIXHEAD data structure that we will need later. We can't read them
	// after the conversion has started, because things will be overwritten.
	USHORT savedFunc = input->uFunc;
	
	// The caller supplies the size of the data. This is actually not needed here; it is only 
	// needed on little-endian platforms where the WIRE_WRITE macro just calls memcpy.
	UNREFERENCED_PARAMETER (inputSize);
	
	// "input" uses the byte ordering and the structure layout of the client machine. "writePtr"
	// uses the byte ordering and the structure layout of the server, which is always packed as
	// much as possible. We need to keep track of both separately, in case the structure layout
	// is not the same. Since the Marshall_Write_ functions do a conversion in place, this will
	// only work if the structure layout on the client is the same or larger as on the server.
	LPBYTE writePtr = (LPBYTE)input;

	// Translate the data specific to this plugin; see the declaration of MIXHEAD. There is a mixture
	// of two byte and four byte quantities; they have to be translated in the right order. The macro 
	// ctx_wire_write16 will increase the variable writePtr by two bytes, ctx_wire_write32 increases
	// it by four bytes.
	ctx_wire_write16(&input->uType, writePtr);
	ctx_wire_write16(&input->uFunc, writePtr);
	ctx_wire_write32(&input->uLen, writePtr);
	ctx_wire_write16(&input->fRetReq, writePtr);
	ctx_wire_write16(&input->dwLen1, writePtr);
	ctx_wire_write16(&input->dwLen2, writePtr);
	ctx_wire_write32(&input->dwRetVal, writePtr);
	
	// Add additional data for the "TIME" function: In this case the header is followed by a VDTM
	// structure. 
	if (savedFunc == TIME)
	{
		VDTM* pTimeInput = (VDTM *) (input + 1);

		ctx_wire_write32(&pTimeInput->tm_sec, writePtr);
		ctx_wire_write32(&pTimeInput->tm_min, writePtr);
		ctx_wire_write32(&pTimeInput->tm_hour, writePtr);
		ctx_wire_write32(&pTimeInput->tm_mday, writePtr);
		ctx_wire_write32(&pTimeInput->tm_mon, writePtr);
		ctx_wire_write32(&pTimeInput->tm_year, writePtr);
		ctx_wire_write32(&pTimeInput->tm_wday, writePtr);
		ctx_wire_write32(&pTimeInput->tm_yday, writePtr);
		ctx_wire_write32(&pTimeInput->tm_isdst, writePtr);
		
	}

	// Return the number of bytes generated, this is the difference between writePtr after copying
	// all the data, and the initial value of writePtr. 
	return ((USHORT)(writePtr - (LPBYTE)input));
}
#endif // BIGEND || ALIGNMENT_REQUIRED

/****************************************************************************
 *
 *  Marshall_Read_MIXHEAD
 *
 *    Marshalls the MIXHEAD data structure from server format received from the
 *	  wire to client format. This routine is required on bigendian platforms
 *	  (like PowerPC) and on platforms that have stricter alignment requirements (like ARM).
 *
 * ENTRY:
 *    void pointer to wire buffer containing the data (input), and the
 *    buffer that the data is to be swapped into (output).
 *
 ***************************************************************************/

#if defined(BIGEND) || defined(ALIGNMENT_REQUIRED)
void Marshall_Read_MIXHEAD_PLUS(LPVOID input, LPVOID output)
{
	// "input" uses the byte ordering and the structure layout of the server, while "output" uses
	// the byte ordering and the structure layout of the client engine. The caller has provided
	// separate buffers for both, since the sizes of the structures could be different. 
	LPBYTE readPtr = (LPBYTE)input;
	PMIXHEAD writePtr = (PMIXHEAD)output;

	// Translate the data specific to this plugin, see the declaration of MIXHEAD. There is a mixture
	// of two byte and four byte quantities; they have to be translated in the right order. The macro 
	// ctx_wire_read16 will increase the variable readPtr by two bytes, ctx_wire_read32 increases
	// it by four bytes.
	ctx_wire_read16(readPtr, &writePtr->uType);
	ctx_wire_read16(readPtr, &writePtr->uFunc);
	ctx_wire_read32(readPtr, &writePtr->uLen);
	ctx_wire_read16(readPtr, &writePtr->fRetReq);
	ctx_wire_read16(readPtr, &writePtr->dwLen1);
	ctx_wire_read16(readPtr, &writePtr->dwLen2);
	ctx_wire_read32(readPtr, &writePtr->dwRetVal);
	
	// Convert additional data for the "ADD" function: In this case the header is followed by two
	// USHORT variables.
	if (writePtr->uType == ADD)
	{
		USHORT* addData = (USHORT *) (writePtr + 1);

		ctx_wire_read16(readPtr, &addData [0]);
		ctx_wire_read16(readPtr, &addData [1]);
	}
	
	// Convert additional data for the "DISP" function: In this case the header is followed by
	// (dwLen1) bytes of string data.
	if (writePtr->uType == DISP)
	{
		CHAR* addData = (CHAR *) (writePtr + 1);
		USHORT stringLength = writePtr->dwLen1;
		
		memcpy (addData, readPtr, stringLength);
		readPtr += stringLength;
	}
}
#endif // BIGEND || ALIGNMENT_REQUIRED


