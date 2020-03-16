/***************************************************************
*
*  pctxfile.h
*
*  Contains definitions of macintosh specific structure(s) 
*  for File IO abstraction.
*
*  Copyright 1999-2000, 2002, 2006 Citrix Systems, Inc.  All Rights Reserved.
*
**************************************************************/

/*( ===================================================================
*	Source Revision History
*
*	Rev	Date		Who	Description
*  ====================================================================
*	21/08/2008		cbau	Use abstract types
*	06/09/2006		cbau	Changed to use mac_FSUtilities
*	24/01/2002		cbau	Changed to using precompiled header files.
*	23/01/2002		KTAM	Added CitrixCarbon.h for macosx build. Updated old header file names.
*  ====================================================================
)*/

#ifndef _MAC_PCTXFILE_H
#define _MAC_PCTXFILE_H

/* Macintosh platform specific file object */
typedef struct _FILEOBJ {

    TOpaqueIORef fileRef;	
    UINT32      accessMode;		
    UINT32      disposition;
    IBOOL        readOnly;
    IBOOL        writeOnly;
    IBOOL        append;
    IBOOL		exclusive;
    
} FILEOBJ;

typedef FILEOBJ     *PFILEOBJ;
typedef PFILEOBJ    *PPFILEOBJ;

/* Macintosh platform specific filefirst, findnext, findclose handle */
typedef struct _FILEIO_FIND_HND {

	char					searchPattern [256];
	TOpaqueFileIteratorRef	theIterator;
   
} FILEIO_FIND_HND; 

typedef FILEIO_FIND_HND     *PFILEIO_FIND_HND;
typedef PFILEIO_FIND_HND    *PPFILEIO_FIND_HND;

/* Macintosh folder seperator character/string constants */

#define MAC_PATH_SEP_CHR  ':'
#define MAC_PATH_SEP_STR  ":"


#endif /* _MAC_PCTXFILE_H */
