/***************************************************************************
*
*   MIAPI.H
*
*   Header file for Memory INI APIs
*
*   Copyright © Citrix Systems, Inc.  All rights reserved.
*
****************************************************************************/

#ifndef __MIAPI_H__
#define __MIAPI_H__

#include "biniapi.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// miGetPrivateProfile... These are the functions that should be used to read configuration values,
// based on the combination of the ICA file, the config settings, and the module settings. 
//

//
// Read a string and store the result into a buffer with a size of bufferSize bytes. If the key is
// not found, the default value is taken instead. If the bufferSize is too small for the result, the
// result is shortened. The length of the string is returned. 
//
// Note: Equivalent to [ICAConfiguration stringForKey: inSection: defaultValue: ]
size_t miGetPrivateProfileString (const char* sectionName, const char* keyName, 
								  const char* defaultValue, 
								  char* buffer, size_t bufferSize);

//
// Read an entry and return the result, converted to an integer. If the key is not found,
// the default value is returned instead.
//
// Note: Equivalent to [ICAConfiguration intForKey: inSection: defaultValue: ]
int miGetPrivateProfileInt (const char* sectionName, const char* keyName,
							int defaultValue);

//
// Read an entry and return the result, converted to an integer. If the key is not found,
// the default value is returned instead.
//
// Note: Equivalent to [ICAConfiguration intForKey: inSection: defaultValue: ]
uint64_t miGetPrivateProfileUInt64 (const char* sectionName, const char* keyName,
									uint64_t defaultValue);

//
// Read an entry and return the result, converted to a boolean value. If the key is no found, the
// default value is returned instead. "on", "yes" and "true" are interpreted as true, everything
// else is interpreted as false. 
//
// Note: Equivalent to [ICAConfiguration boolForKey: inSection: defaultValue: ]
bool miGetPrivateProfileBool (const char* sectionName, const char* keyName, 
							  bool defaultValue);


//
// Officially this reads the "long command line". In reality, it checks whether NCSconfig.documentPath
// is set and returns that, converted to a string suitable for client drive mapping, otherwise
// it reads the INI_LONGPARAMETERS parameters and concatentates them.
//
// Note: Equivalent to [ICAConfiguration longCommandLine]
size_t miGetLongCommandLine (char* buffer, size_t bufferSize);


//
// Equivalent functions which read in an arbitrary configuration instead of the configuration for
// the current connection. 
//
size_t miGetProfileString (INIFILESECTION* config, const char* sectionName, const char* keyName, 
						   const char* defaultValue, 
						   char* buffer, size_t bufferSize);
int miGetProfileInt (INIFILESECTION* config, const char* sectionName, const char* keyName, int defaultValue);
uint64_t miGetProfileUInt64 (INIFILESECTION* config, const char* sectionName, const char* keyName, uint64_t defaultValue);
bool miGetProfileBool (INIFILESECTION* config, const char* sectionName, const char* keyName, bool defaultValue);



unsigned int _htoi (const char* s);


#ifdef __cplusplus
}
#endif

#endif /* __MIAPI_H__ */
