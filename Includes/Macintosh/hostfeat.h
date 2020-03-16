/*[
 ******************************************************************************
 *
 *	Name:			hostfeat.h
 *
 *	Derived From:	SoftWindows insignia.h, base_def.h, host_def.h
 *
 *	Author:			Rob Tizzard
 *
 *	Created:		21 February 1996
 *
 *	Purpose:		Defines to enable/disable features for this host.
 *
 *	Copyright Insignia Solution PLC, 1996.  All rights reserved.
 *  Copyright © Citrix Systems, Inc.  All rights reserved.
 */

#ifndef _HOSTFEAT_H_
#define _HOSTFEAT_H_

#define HOTKEYS

#if ! MAC_SOUND_DISABLED
#define ENABLE_AUDIO
#endif

/* client com port mapping */
#if ! MAC_CCM_DISABLED
#define ENABLE_CCM
#endif

#define JPN_HOTKEYS

/* Switch on dynamic channel allocation */

#define DYNAMIC_CHANNEL_ALLOCATION

#if ! MAC_CDM_DISABLED
#define VDCDM_EMBEDDED
#endif

/* SmartCard */
#if ! MAC_SMARTCARD_DISABLED
#define ENABLE_CTXSCA
#endif

//#define SPEEDBROWSE
#define GIF_SUPPORTED

// Support for different server versions.
#define SERVER_VERSION_SUPPORT  /* WD server version capability. */

// For the SSL SDK, define whether we need code for the client only, for the server, or for both. 
// Since we are building a client, we only need the client version.
#define CLIENT_BUILD_ONLY 1

/* CDM asynchronous writing support: report locally any failures that
* occur after success has been reported to the server application.
*/

#define SUPPORT_ASYNC_DISK_WRITES 1

// Define this to force desktops with toolbar to appear at 80% of screen size initially. 
#define INITIAL_80PERCENT_WITH_DESKTOP_TOOLBAR 1
//#undef INITIAL_80PERCENT_WITH_DESKTOP_TOOLBAR

// Are config files and connection files read from actual files, or are they read from somewhere
// else? If CONFIG_NOT_USING_FILES is true then we never use real files for config files and other
// configuration files. If CONFIG_SPECIALNAME_MODULE, CONFIG_SPECIALNAME_CONFIG and
// CONFIG_SPECIALNAME_CONNECTION are defined then they are strings identifying names that should not
// be read from a file but should be read by calling a function.  
#if XCODE_SDK_CARBON
	#undef CONFIG_NOT_USING_FILES
	#define CONFIG_SPECIALNAME_CONNECTION	"_Connection_"
#else
	#define CONFIG_NOT_USING_FILES			1
	
	#define CONFIG_SPECIALNAME_MODULE		"_Module_"
	#define CONFIG_SPECIALNAME_CONFIG		"_Config_"
	#define CONFIG_SPECIALNAME_CONNECTION	"_Connection_"
#endif

// Are we supporting a keystore folder outside the keychain? 
#if XCODE_SDK_UIKIT
	#define	MAC_NO_KEYSTORE_FOLDER			1
#else
	#undef MAC_NO_KEYSTORE_FOLDER
#endif

// Handle processing of Apple events sent by the Launcher applications
#if XCODE_SDK_CARBON
	#define ENGINE_HANDLE_LAUNCHER_EVENTS			1
#endif


// Controls if we use libJPEG or Core Graphics for JPEG decompression
// Core Graphics is > 2x faster
#define USE_LIBJPEG							0

#endif /* _HOSTFEAT_H_ */


