/*************************************************************************
 *
 *  platsys.h
 *
 *  MAC specific platform system types
 *
 *  $Id$
 *
 * Copyright 1999-2000, 2006, 2008 Citrix Systems Inc.  All Rights Reserved
 *
 ************************************************************************/

/*( ===================================================================
*	Source Revision History
 *
 *	Rev	Date		Who	Description
 *  ====================================================================
*	17/07/2008  cbau    Allow turning off separate keystore folder
 *	21/04/2008		cbau	Mac doesn't provide partial path for keystore folder.
 *	26/10/2006		cbau	Mac provides full path for keystore folder.
 *  ====================================================================
)*/
#ifndef _MAC_PLATSYS_H_
#define _MAC_PLATSYS_H_

/*
 * Platform specfic prototypes
 */

int LoadString( HINSTANCE unUsed,int err,char * msg,int sizeMsg ) ;
ULONG QueryLocaleCodePage ( void ) ;
int host_AnsiUpper (char *theString) ;

// This define is used in the function SSLStartup: SSLStartup needs to determine a path to the
// keystore directory holding among other things SSL certificates. Usually this is created with
// the name "keystore" somewhere in it. SSLStartup relies on the client to return the full posix
// path of the keystore directory.
#if ! MAC_NO_KEYSTORE_FOLDER
	// Return the full path for the keystore folder in path. Result is an empty string on
	// failure.
	void host_getKeystoreFolderFullPath (char* path, int max_size);
#endif


/*
 * Platform specific macros
 */

#define CtxCharUpper	host_AnsiUpper

#ifndef GetACP
#define GetACP() 		QueryLocaleCodePage()
#endif

#endif /* _MAC_PLATSYS_H_ */
