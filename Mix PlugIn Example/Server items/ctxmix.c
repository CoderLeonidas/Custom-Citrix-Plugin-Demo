/**********************************************************************
*
* ctxmix.c
*
* Example Virtual Channel application
*
* Send packets (functions) and receive a response only if required
*
* Copyright 1999-2003, 2009 Citrix Systems, Inc. All Rights Reserved.
*
* Citrix hereby permits you to use, reproduce, modify, display, compile,
* sublicense, and distribute all or any portion of the sample code contained
* in this file, provided that you remove this Copyright attribution from any
* modified version of this file.
*
* THIS SAMPLE CODE IS PROVIDED BY CITRIX "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
*
**********************************************************************/

/*
 *  Include files
 */
#include <windows.h> // Base headers
#include <stdio.h>
#include <tchar.h>
#include <time.h>

#include <wfapi.h>   // Citrix Server SDK

#include <vdmix.h>  // Citrix shared header

#include "ctxmix.h" // local header for CTXPING


/*
 *  Global variables
 */

BOOLEAN     vfDebug = FALSE;   // Flag to control debugging
HANDLE      hVC = NULL;        // Handle to the Virtual Channel
USHORT      dwTime;              // To keep track of timing information


/****************************************************************************
 *
 *  main
 *
 ***************************************************************************/

int __cdecl
main(INT argc, CHAR **argv)
{

    int         exitcode = SUCCESS;
    LPBYTE      pSend = NULL;
    LPBYTE      pRecv = NULL;
    PMIXHEAD    pMixHd = NULL;
    DWORD       ByteCount = 0;
    LPTSTR      pSessionInfo = NULL;
    DWORD       Result = 0;

    dwTime = GetTickCount();

    /*
     *  Determine if we are running in a session.
     */


    if ( WFQuerySessionInformation( WF_CURRENT_SERVER_HANDLE,
                            WF_CURRENT_SESSION,
                            WFSessionId,
                            &pSessionInfo, &ByteCount ) == FALSE ) {
        PrintMessage( IDS_ERROR_QUERY_SESSION_FAIL, GetLastError() );
        exitcode = FAILURE;
        goto ExitMain;
    }
    else if ( (INT)(* pSessionInfo) == 0 ) {     // session 0 is console
        PrintMessage( IDS_ERROR_NEEDS_SESSION );
        exitcode = FAILURE;
        goto ExitMain;
    }

    /*
     *  Look for a /d or -d to turn on debugging output.
     */
    if ( argc > 1 && (argv[1][0] == '/' || argv[1][0] == '-') &&
            tolower(argv[1][1]) == 'd' ) {
        vfDebug = TRUE;
    }

    /*
     * Open the Virtual Channel
     */

    hVC = WFVirtualChannelOpen( WF_CURRENT_SERVER,
                              WF_CURRENT_SESSION,
                              CTXMIX_VIRTUAL_CHANNEL_NAME );
    if ( hVC ) {
           PrintMessage( IDS_OPENED_CHANNEL, hVC );
    }
    else {
        PrintMessage( IDS_ERROR_OPEN_FAILED, GetLastError() );
        exitcode = FAILURE;
        goto ExitMain;
    }

    /*
     * Allocate the buffers
     *
     * pSend will have the actual buffer to be sent
     */
    if ( (pSend=(LPBYTE)malloc(MAX_DATA )) == NULL ) {
       PrintMessage( IDS_ERROR_MALLOC );
       exitcode = FAILURE;
       goto ExitMain;
    }

     if ( (pRecv=(LPBYTE)malloc(MAX_DATA)) == NULL ) {
       PrintMessage( IDS_ERROR_MALLOC );
       exitcode = FAILURE;
       goto ExitMain;
    }

    if (vfDebug)
       printf("Sizeof MIXHEAD is %d\n",sizeof(MIXHEAD));

    /*
     *   Making all the function calls
     */

    Srv_Time(pSend,pRecv);

    Srv_DispStr(pSend,"Test String One");

    Result= Srv_AddNo(pSend,pRecv, 101, 202);
    printf("The sum of the numbers is %d\n",Result);

    Srv_DispStr(pSend,"Test String Two");

    Srv_DispStr(pSend,"Test String Three");

    Srv_DispStr(pSend,"Test String Four");


    Result= Srv_AddNo(pSend,pRecv, 303, 404);
    printf("The sum of the numbers is %d\n",Result);

    Srv_DispStr(pSend,"Test String Five");

    Srv_Time(pSend,pRecv);

    /*
     *  Finally, close the channel and free allocated memory.
     */
ExitMain:
    if ( pSessionInfo ) {
        WFFreeMemory( pSessionInfo );
    }
    if ( hVC ) {
        WFVirtualChannelClose( hVC );
    }
    if ( pSend ) {
        free( pSend );
    }
    if ( exitcode == FAILURE ) {
        PrintMessage( IDS_ERROR_CTXMIX_FAIL );
    }

    return( exitcode );

} /* main() */





/*****************************************************************
*
* Srv_AddNo
*       Server side of the add function. It does not do the actual
*       addition but sets the arguments and other fields in the
*       MIXHEAD packet
*
* ENTRY:
*        pSend  : Pointer to the actual buffer to be sent to the client
*        pRecv : Pointer to the Receive buffer
*       dwArg1, dwArg2 : The two numbers to be added
*
* EXIT:
*       The sum of the two numbers or -1 if error
*
******************************************************************/

DWORD
Srv_AddNo(LPBYTE pSend, LPBYTE pRecv,USHORT dwArg1, USHORT dwArg2)
{

    PMIXHEAD    pMixHd;
    LPBYTE      pData = NULL;

    printf("Function: Srv_AddNo %d %d\n",dwArg1,dwArg2);

    /*
     *  First part of the send buffer is the mixhead structure
     */
    pMixHd = (PMIXHEAD)pSend;
    pData = pSend;
    memset(pSend,0,MAX_DATA);

    /*
     *  This indicates that it requires a response from the client
     */
    pMixHd->fRetReq = TRUE;
    pMixHd->uFunc = ADD;

    /*
     *  Total data being send is MIXHEAD + size of the two arguments
     */
    pMixHd->uLen = sizeof(MIXHEAD);
    pMixHd->uLen += 2*(sizeof(USHORT)) ;

    /*
     *  Second part of pSend is the numbers to be added
     */
    pData += sizeof(MIXHEAD);
    memcpy(pData,&dwArg1,sizeof(USHORT));
    pData += sizeof(USHORT);
    memcpy(pData,&dwArg2,sizeof(USHORT));


    if ( SendCommand(pSend,pRecv) == TRUE) {
       return ((PMIXHEAD)pRecv)->dwRetVal ;
    }
    else {
        printf("Error in SendCommand() called from Srv_AddNo()\n");
        return   -1;
    }
} /* Srv_AddNo */



/*****************************************************************
*
* Srv_Time
*       Server side of the time function. It gets the time from the
*       client and displays it in the right format
* ENTRY:
*       pSend : Pointer to the actual buffer to be sent to the client
*       pRecv : Pointer to the Receive buffer
*
* EXIT:
*
******************************************************************/

VOID
Srv_Time(LPBYTE pSend, LPBYTE pRecv)
{
    PMIXHEAD    pMixHd;
   struct tm   *newtime;
    PVDTM       pLoctm;
    char am_pm[] = "AM";
    ULONG    Temp=0;

    printf("Function: Srv_Time\n");
    /*
     *  First part of the send buffer is the mixhead structure
     */
    pMixHd = (PMIXHEAD)pSend;
    memset(pSend,0,MAX_DATA);

    /*
     *  This indicates that it requires a response from the client
     */
    pMixHd->fRetReq = TRUE;
    pMixHd->uFunc = TIME;

    pMixHd->uLen = sizeof(MIXHEAD);

    if ( !SendCommand(pSend,pRecv) ) {
        printf("Error in SendCommand() called from Srv_Time()\n");
        return;
    }
    else {
    /*
     *  We increment the receive buffer by sizeof MIXHEAD to get to
     * the returned value.
     */

        Temp = ((PMIXHEAD)pRecv)->dwRetVal;
        /*
         *  Value 1001 is arbitarily chosen to reflect that it is a DOS
         *  Client and this example does not get time from the DOS client
         */
        if ( Temp ==1001 ) {
            printf("Time not yet supported for Dos32 and WinCE clients\n");
            return;
        }
        pRecv += Temp;
        newtime = (struct tm *) pRecv;
        pLoctm =(PVDTM) pRecv;
        if ( pLoctm->tm_hour > 12 ) {       /* Set up extension. */
                strcpy( am_pm, "PM" );
                                            /* Convert from 24-hour */
                pLoctm->tm_hour -= 12;      /* to 12-hour clock.  */
        }
        if ( pLoctm->tm_hour == 0 )         /* Set hour to 12 if midnight */
                pLoctm->tm_hour = 12;
        printf( "%.19s %s\n", asctime((struct tm*)pLoctm ), am_pm );
    }

} /* Srv_Time */





/*****************************************************************
*
* Srv_DispStr
*        Server side of the Display String function. It does not
*        do the actual String Display but sets the arguments and
*        other fields in the MIXHEAD packet and fills in pSend
*
* ENTRY:
*        pSend  : The actual buffer to be sent to the client
*        pStr   :  The String to be displayed
*
* EXIT:
*       TRUE if Successful FALSE  if not
*
******************************************************************/

BOOLEAN
Srv_DispStr(LPBYTE pSend,PUCHAR pStr)
{
    PMIXHEAD    pMixHd;
    LPBYTE      pData= NULL;

    printf("Function: Srv_DispStr\n");
    /*
     *  First part of the send buffer is the mixhead structure
     */
    pMixHd = (PMIXHEAD)pSend;
    pData = pSend;
    memset(pSend,0,MAX_DATA);

    pMixHd->fRetReq = FALSE;
    pMixHd->uFunc = DISP;

    /*
     *  Total data being send is MIXHEAD + size of the string being sent
     */
    pMixHd->dwLen1 = strlen(pStr);
    pMixHd->uLen = sizeof(MIXHEAD) + pMixHd->dwLen1 ;

    /*
     *  Second part of pSend is the String to be sent
     */
    pData +=  sizeof(MIXHEAD);
    memcpy(pData,pStr,pMixHd->dwLen1);

    if ( vfDebug )
    printf("Srv_DispStr: The String being send is %s \n",pStr);

    if ( SendCommand(pSend,NULL) == TRUE )
       return TRUE ;
    else {
        printf("Error in SendCommand() called from Srv_Disp()\n");
        return  FALSE;
    }
} /* Srv_DispStr */






/**************************************************************************
*
*  SendCommand -
*       This function sends the data to the client and receives
*       a response if required
*
*  ENTRY:
*        pSend
*           This is the buffer that is sent to the client. It consists of
*           MixHd structure followed by the arguments to the function
*           being called
*        pMixHd
*           Pointer to the Recv Buffer. It too consits of the MIXHEAD
*           structure followed by any string return value if required
*
*   EXIT:
*       TRUE if Successful FALSE if not
*
***************************************************************************/
BOOLEAN
SendCommand (LPBYTE pSend,LPBYTE pRecv)
{
    USHORT  rc;
    USHORT  Reply;
    ULONG ulen;
    ULONG length;

    if ( vfDebug )
        printf("Sending Packet at time : %d \n",GetTickCount() - dwTime);
    else
        printf("Sending Packet\n");

    /*
     *   This decides if a response is requested or not
     */
    Reply = ((PMIXHEAD)pSend)->fRetReq;
    length = ((PMIXHEAD)pSend)->uLen;

    /*
     *  Send the packet to the client.
     */
    if ( vfDebug )
       printf("Packet Length being sent is %d bytes.\n",length);

    rc = WFVirtualChannelWrite( hVC,
                                (PCHAR)pSend,
                                length,
                                &ulen );

    if ( rc != TRUE ) {
        PrintMessage( IDS_ERROR_WRITE_FAILED, GetLastError() );
        return FALSE;
    }

    if ( length != ulen ) {
        PrintMessage( IDS_ERROR_WRITE_SHORT, ulen );
        return FALSE;
    }

    if ( !Reply ) {
        if ( vfDebug ) {
            printf("Send complete (no Reply Required) at time %d. \n",
                GetTickCount() - dwTime);
        }
        else {
           printf("Send complete (no Reply Required).\n");
        }
        return TRUE;
    }


    /*
     *  Read response from the client
     */
    rc = WFVirtualChannelRead( hVC,
                               VC_TIMEOUT_MILLISECONDS,
                               (PCHAR)pRecv,
                               MAX_DATA,
                               &ulen );
    if ( rc != TRUE ) {
        PrintMessage( IDS_ERROR_READ_FAILED, GetLastError());
        return FALSE;
    }

    if ( ((PMIXHEAD)pRecv)->uLen != ulen ) {
        PrintMessage( IDS_ERROR_READ_SHORT, ulen );
        return FALSE;
    }


   if ( vfDebug ) {
       printf("Reply Packet received at time %d. \n",GetTickCount() - dwTime);
   }
   else {
       printf("Reply Packet received.\n");
   }

   return TRUE;
}   /* SendCommand */




/**************************************************************************
 *
 *  PrintMessage
 *      Display a message to stdout with variable arguments.  Message
 *      format string comes from the application resources.
 *
 *  ENTRY:
 *      nResourceID (input)  Resource ID of the format string to use in
 *                           the message.
 *      ...         (input)  Optional additional arguments to be used
 *                           with format string.
 *
 *  EXIT:
 *      none
 *
 *************************************************************************/

VOID WINAPI
PrintMessage( int nResourceID, ...)
{
    _TCHAR str1[MAX_IDS_LEN+1], str2[2*MAX_IDS_LEN+1];

    va_list args;
    va_start( args, nResourceID );

    if ( LoadString( NULL, nResourceID, (LPTSTR)str1, sizeof(str1) ) ) {

        _vstprintf( str2, str1, args );
        _tprintf( str2 );

    }
    else {
        _ftprintf( stderr,
                    _TEXT("PrintMessage(): LoadString %d failed, Error %ld)\n"),
                    nResourceID, GetLastError() );
    }

    va_end(args);

}  /* PrintMessage() */

