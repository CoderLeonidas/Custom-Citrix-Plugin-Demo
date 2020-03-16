/***************************************************************************
*
*  wdwire.h
*
*  This module contains wire marshalling function prototypes for the WD
*
*   revision: $Id$
*
*   Copyright 1999-2000, 2007-2008 Citrix Systems, Inc.  All Rights Reserved.
*
****************************************************************************/

#ifndef _WDWIRE_H_
#define _WDWIRE_H_



/* definition of the size of MOUSEDATA struct on platforms that */
/* don't support packing. Required for mouse.c when calculating */
/* the number of mouse packets from a buffer size. */

#define packed_sizeof_MOUSEDATA 5
#define packed_sizeof_MOUSEDATA_EXTENDED 8

#ifdef BIGEND

/* Prototypes for externally used functions */

USHORT Marshall_C2H_Structures(LPVOID input, USHORT inputSize) ;
USHORT Marshall_Write_MOUSEDATA (LPVOID input, USHORT inputSize);
void Marshall_Read_CAP_HEAD(LPVOID input, LPVOID output);
void Marshall_Read_CAP_REDUCERS_SUPPORTED(LPVOID input, LPVOID output);
void Marshall_Read_PD_H2C(LPVOID input, LPVOID output) ;
void Marshall_Read_WD_H2C(LPVOID input, LPVOID output);
void Marshall_Read_MOUPOSITION(LPVOID input, LPVOID output);
void Marshall_Read_CAP_TIME_ZONE_INFO(LPVOID input, LPVOID output);
void Marshall_Read_CAP_LONG_UNICODE_USERNAME_SUPPORT(LPVOID input, LPVOID output);
void Marshall_Read_CAP_PRT_BW_CTRL(LPVOID input, LPVOID output);
void Marshall_Read_CAP_WANSCALER_SUPPORT(LPVOID input, LPVOID output);

USHORT Marshall_Write_MODULE_C2H(PMODULE_C2H input, USHORT inputSize);
USHORT Marshall_Write_CAP_CHANNEL_MONITORING(PCAP_CHANNEL_MONITORING input, USHORT inputSize);
USHORT Marshall_Write_CAP_SSL_PACKET_OVERHEAD(PCAP_SSL_PACKET_OVERHEAD input, USHORT inputSize);
USHORT Marshall_Write_CAP_CGP_PACKET_OVERHEAD(PCAP_CGP_PACKET_OVERHEAD input, USHORT inputSize);
USHORT Marshall_Write_CAP_HIGH_THROUGHPUT(PCAP_HIGH_THROUGHPUT input, USHORT inputSize);
USHORT Marshall_Write_CAP_DRIVE_MAPPING_ACCELERATION(PCAP_DRIVE_MAPPING_ACCELERATION input, USHORT inputSize);
USHORT Marshall_Write_CAP_LONG_UNICODE_USERNAME_SUPPORT(PCAP_LONG_UNICODE_USERNAME_SUPPORT input, USHORT inputSize);
USHORT Marshall_Write_CAP_PRT_BW_CTRL(PCAP_PRT_BW_CTRL input, USHORT inputSize);
USHORT Marshall_Write_CAP_COOKIE(PCAP_COOKIE input, USHORT inputSize);
USHORT Marshall_Write_CAP_WD_CREDENTIAL_PASSING(PCAP_WD_CREDENTIAL_PASSING input, USHORT inputSize);
USHORT Marshall_Write_CAP_WANSCALER_SUPPORT(PCAP_WANSCALER_SUPPORT input, USHORT inputSize);

#ifdef USE_EUKS
USHORT Marshall_Write_CAP_EUKS(PCAP_EUKS input, USHORT inputSize);
#endif
USHORT Marshall_Write_SHORT (LPVOID input, USHORT inputSize);
void Marshall_Read_CAP_SEAMLESS(LPVOID input, LPVOID output);
void Marshall_Read_CAP_CHANNEL_MONITORING(LPVOID input, LPVOID output);
void Marshall_Read_CAP_HIGH_THROUGHPUT(LPVOID input, LPVOID output);
void Marshall_Read_CAP_INTELLIMOUSE(LPVOID input, LPVOID output);
void Marshall_Read_CAP_REDRAW(LPVOID input, LPVOID output);
void Marshall_Read_CAP_PACKET_PRIORITY(LPVOID input, LPVOID output);
void Marshall_Read_CAP_COOKIE(LPVOID input, LPVOID output);
void Marshall_Read_CAP_SERVER_VERSION(LPVOID input, LPVOID output);
void Marshall_Read_CAP_MAX_VIDEO(LPVOID input, LPVOID output);

USHORT Marshall_Write_VD_C2H (LPVOID input, USHORT packedByteCount);

#endif



#endif /* _WDWIRE_H_ */

