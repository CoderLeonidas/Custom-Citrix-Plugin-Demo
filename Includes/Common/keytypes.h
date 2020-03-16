/**********************************************************************
*
*  keytypes.h
*
*  This module contains structures for key press/release storage
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
***********************************************************************/

#ifndef __KEYTYPES_H__
#define __KEYTYPES_H__

/* WdScanCode structure */

typedef struct _SCANCODE {
    USHORT  cScanCodes;
    LPVOID  pScanCodes;
    USHORT  uiRepeat;
} SCANCODE, * PSCANCODE;

/* WdCharCode structure */

typedef struct _CHARCODE {
    USHORT  cCharCodes;
    LPVOID  pCharCodes;
    USHORT  uiRepeat;
} CHARCODE, * PCHARCODE;

#if defined(UNICODESUPPORT) || defined(USE_EUKS)

/* WdUnicodeCode structure */

typedef struct _UNICODECODE {
    USHORT  cUnicodeCodes;
    LPVOID  pUnicodeCodes;
    USHORT  uiRepeat;
} UNICODECODE, * PUNICODECODE;

/*
 *  Unicode keyboard packet
 *  structure -- stored in
 *  pUnicodesCodes array
 *  in _UNICODECODE
 */
#define KEYUP       0x01
#define SPECIALKEY  0x02
#define UCINSERT    0x04

typedef struct _UNICODECHAR {
        BYTE  bCharType;          /* KEYUP, SPECIALKEY & KEYUP, etc. */
        BYTE  cCharValue[2];      /* Unicode or special key value */
} UNICODECHAR, * PUNICODECHAR;
#endif

#endif /* __KEYTYPES_H__ */
