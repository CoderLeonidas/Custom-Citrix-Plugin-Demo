/******************************************************************************
*
*  ICAID.H
*     This file contains definitions for client identification
*
*  NOTE: this file should only be given to people with an ICA license
*
*  Copyright 1998-2000 Citrix Systems, Inc.  All Rights Reserved
*
*******************************************************************************/

#ifndef __ICAID_H__
#define __ICAID_H__

/*
 *  Client product id
 */
#define CLIENTID_CITRIX_DOS          0x0001   /* citrix dos client     */
       /*  Client ID 2 is not to be used */
#define CLIENTID_CITRIX_CONSOLE      0x0003   /* citrix console        */
#define CLIENTID_CITRIX_TEXT_TERM    0x0004   /* citrix text terminals */
#define CLIENTID_CITRIX_MVGA_TERM    0x0007   /* citrix MVGA terminals */
#define CLIENTID_CITRIX_NEW_JAVA     0x0008   /* citrix JAVA client    */
#define CLIENTID_CITRIX_EPOC         0x000A   /* citrix EPOC client   */
#define CLIENTID_CITRIX_OS2          0x000B   /* citrix OS/2 client   */
#define CLIENTID_CITRIX_DOS32        0x000E   /* citrix DOS32 client   */
#define CLIENTID_CITRIX_WINCE        0x1f09   /* citrix WinCE client   */
#define CLIENTID_CITRIX_UNIX	       0x0051     /* citrix unix client */
#define CLIENTID_CITRIX_MAC 	       0x0052     /* Citrix Mac client */

#define CLIENTID_CITRIX_INTERNET     0x0101   /* citrix internet client */

#define CLIENTID_FORCESERIALIZE_FLAG 0x4000   /* client requires license no. */
#define CLIENTID_TERMINAL_FLAG       0x8000   /* terminal based client  */

#endif /* __ICAID_H__ */

