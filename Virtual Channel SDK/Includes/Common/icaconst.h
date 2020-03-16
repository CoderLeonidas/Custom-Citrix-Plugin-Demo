/***************************************************************************
*
*  ICACONST.H
*
*  This module contains constants used by the ICA Client.
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
****************************************************************************/

#ifndef _ICACONST_H_
#define _ICACONST_H_

/*
 *  String lengths and invalid character defines
 */


#ifdef  VERSION1_LABEL
#define LABEL_INVALID_CHARACTERS                "=<>|\"@&()^;,\\/-"
#define LABEL_INVALID_CHARACTERS_SPACED         "= < > | \" @ & ( ) ^ ; ,\\ / -"
#endif


#define DOSFILENAME_LENGTH      12
#define DESCRIPTION_INVALID_CHARACTERS          "\\/:*?\"<>|,.()[];"
#define DESCRIPTION_INVALID_CHARACTERS_SPACED   "\\ / : * ? \" < > | , . ( ) [ ] ;"
#define DESCRIPTION_LENGTH      40 
#define NAMERESOLVER_LENGTH     13
#define TRANSPORTNAME_LENGTH    40
#define ENCRYPTION_LEVEL_NAME_LENGTH 60
#define ENCRYPTIONLEVEL_LENGTH  37

#define LAUNCHREFERENCE_LENGTH	256
#define LAUNCHER_LENGTH       256
#define VERSION_LENGTH         64
#define CLIENTNAME_LENGTH       20                      /* from ica30.h */
#define CLIENTSN_LENGTH         20
#define DOMAIN_LENGTH           256                      /* from ica30.h */
#define USERNAME_LENGTH         256                      /* from ica30.h */
#define PASSWORD_LENGTH         256                      /* from ica30.h */
#define DIRECTORY_LENGTH        256                     /* from ica30.h */

/* Some earlier than MF1.8/SP2 have a lower limit for Unicode strings. */

#define OLD_DOMAIN_LENGTH        17
#define OLD_USERNAME_LENGTH      20
#define OLD_PASSWORD_LENGTH      14

#define INITIALPROGRAM_LENGTH   256                     /* from ica30.h */

#define ENCRYPTEDPASSWORD_LENGTH   (2*PASSWORD_LENGTH+4+8) /* 4 + 2X + pad */
#define ADDRESS_LENGTH          64   /* should be the same as MAX_BR_NAME-1 */

#define DEVICENAME_LENGTH       59

#define KEYBOARDLAYOUT_LENGTH   40

#define XMLADDRESSRESTYPE_LENGTH 30

#define MAXPATH 260
#define FILEPATH_LENGTH         MAXPATH

#define MAX_ERRORMESSAGE    256

/* max count of addresses in server address list
 * must be multiple of 5, because number of servers
 * in a group is a group is 5
 */
#define MAX_BROWSERADDRESSLIST      15

/*
 *  Used for the business recovery feature added to server list
 *
 *  THIS NEEDS TO BE FIXED
 */

#define VALID_ADDRESS 0
#define INVALID_ADDRESS 1
#define SEPERATOR_ADDRESS 2

#define SEPERATOR "-----"

#define RESOLVEWITHDNS "!"

#define ERROR_ADDRESS_IS_SEPERATOR 5

#define SERVERS_IN_GROUP        5

#define SERVER_GROUP1     "Primary"
#define SERVER_GROUP2     "Backup 1"
#define SERVER_GROUP3     "Backup 2"
#define SERVER_GROUP4     "Backup 3"
#define SERVER_GROUP5     "Backup 4"

#define INI_SERVER_GROUP_NAME   "ServerGroupName"

#define MAX_SERVER_GROUP_NAME_SIZE      20

#define CTX_APP_DELIMITER       '#'
#define CTX_APP_DELIMITER_LFN   '"'


/*
 *  The ICA protocol limits cookies to 64 KB, but our ludicrous IPC mechanism
 *  forces me to pick a much smaller size.
 *
 *  Note: Keep this in sync with DEF_COOKIE_MAX_SIZE in icaini.h
 */
#define MAX_COOKIE_SIZE     128

/* 
cpr 233501 
The name of the lock file to prevent pn ( and possible other exes) 
from running when a reboot requirement is pending
*/
#define REBOOT_LOCK_FILE_NAME  "Reboot.lck"

#endif /* _ICACONST_H_ */

