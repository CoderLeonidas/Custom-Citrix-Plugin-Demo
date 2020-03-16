/******************************************************************************
*
*  KBDAPI.H
*
*  Header file for Keyboard APIs.
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
*******************************************************************************/

#ifndef __KBDAPI_H__
#define __KBDAPI_H__


/*=============================================================================
==   Typedefs and structures
=============================================================================*/

/*
 *  KbdClass enum
 */
typedef enum _KBDCLASS {
    Kbd_Scan,
    Kbd_Ascii,
    Kbd_Closed
#ifdef UNICODESUPPORT
    ,Kbd_Unicode
#endif
} KBDCLASS;

/*
 * Keyboard Preferences (DOS Client Only)
 */
typedef struct _KBDPREFERENCES {
   short KeyboardDelay;
   short KeyboardSpeed;
} KBDPREFERENCES, FAR *PKBDPREFERENCES;

/* macros used to interpret ShiftState used by KbdGetLeds() and KbdSetLeds() */
#define CAPS_LOCK_LED 		0x40
#define NUM_LOCK_LED		0x20
#define SCROLL_LOCK_LED		0x10
#define ALL_LEDS (CAPS_LOCK_LED|NUM_LOCK_LED|SCROLL_LOCK_LED)

/*=============================================================================
==   External functions provided by LoadLibraries()
=============================================================================*/

int WFCAPI KbdOpen( VOID ); // Initialise keyboard code - platform specific
int WFCAPI KbdClose( VOID ); // Initialise keyboard code - platform specific

int WFCAPI KbdGetMode( KBDCLASS * pKbdClass );
int WFCAPI KbdSetMode( KBDCLASS KbdClass );
int WFCAPI KbdReadAvail( int * pCountAvail );
int WFCAPI KbdReadChar( int * pCharCode, int * pShiftState );
int WFCAPI KbdReadScan( int * pScanCode, int * pShiftState );
int WFCAPI KbdPush( int ScanCode, int ShiftState, int Char );
int WFCAPI KbdSetLeds( int ShiftState );
int WFCAPI KbdAddHook( LPVOID pProcedure );
int WFCAPI KbdRemoveHook( LPVOID pProcedure );
int WFCAPI KbdFlush( VOID );
int WFCAPI KbdLoadPreferences( PKBDPREFERENCES pPref );
int WFCAPI KbdGetLeds( BYTE * ShiftState );

#endif /* __KBDAPI_H__ */
