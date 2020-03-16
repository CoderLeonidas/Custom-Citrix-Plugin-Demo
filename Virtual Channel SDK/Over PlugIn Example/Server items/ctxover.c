/**********************************************************************
*
* ctxover.c
*
* Example Virtual Channel application
*
* Send and receive packets to/from the VDOVER virtual channel
*
* Copyright 1998-2003, 2009 Citrix Systems, Inc. All Rights Reserved.
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

#include <wfapi.h>   // Citrix Server SDK

#include <vdover.h>  // Citrix shared header

#include "ctxover.h" // local header for ctxover


/*
 *  Global variables
 */
BOOLEAN             vfDebug = FALSE;   // Enable debug messages
ULONG               gLastCount = 0;    // Record initial tick count (time) 
USHORT              guCounter = 0;     // Counter of the packets being exchanged


/****************************************************************************
 *
 *  main
 *
 ***************************************************************************/

int __cdecl
main(INT argc, CHAR **argv)
{
    int         exitcode = SUCCESS;
    DWORD       ThreadId;
    BOOLEAN     rc;
    HANDLE      hVC = NULL;
    HANDLE      hThread = NULL;
    LPTSTR      pSessionInfo = NULL;
    POVER       pBufSend = NULL;
    PVDOVER_C2H pVdQbuf  = NULL;
    DWORD       dwSize;
    PVD_C2H     pvdc2h;
    PMODULE_C2H pmc2h;
    DWORD       i;
    DWORD       ByteCount;
    THREADRCV   trdBlock;
    PTHREADRCV  pTrdBlock=&trdBlock;

    

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
     *  Allocate data buffers.
     */
    if ( (pBufSend=(POVER)calloc(1, sizeof(OVER) )) == NULL ) {
        PrintMessage( IDS_ERROR_MALLOC );
        exitcode = FAILURE;
        goto ExitMain;
    }  

    /*
     *  First, we want to open the channel and report the handle.
     *  If failure, print the error number.
     */
    hVC = WFVirtualChannelOpen( WF_CURRENT_SERVER,
                                WF_CURRENT_SESSION,
                                CTXOVER_VIRTUAL_CHANNEL_NAME );
    if ( hVC ) {
        PrintMessage( IDS_OPENED_CHANNEL, hVC );
    }
    else {
        PrintMessage( IDS_ERROR_OPEN_FAILED, GetLastError() );
        exitcode = FAILURE;
        goto ExitMain;
    }

    /*
     *  Now, query the channel to get data from the client.
     */
    rc = WFVirtualChannelQuery( hVC,
                                WFVirtualClientData,
                                &pVdQbuf,
                                &dwSize );

    if ( rc != TRUE ) {
        PrintMessage( IDS_ERROR_QUERY_FAIL, GetLastError() );
        exitcode = FAILURE;
        goto ExitMain;
    }
    /*
     *  If debug, report the queried data.  First, dump the data in byte form,
     *  then break it apart to show the fields in the VDOVER_C2H structure.
     */
    if ( vfDebug ) {
        USHORT day, month, year, second, minute, hour;

        PrintMessage( IDS_QUERY );
        printf( "    " );
        for ( i=0; i < dwSize; i++ ) {
            if ( (i+1) % 26 == 0 ) {
                printf( "\n    " );
            }
            printf( "%02x ",*(((PBYTE)pVdQbuf)+i) );
        }
        printf( "\n\n" );

        pvdc2h = &pVdQbuf->Header;
        pmc2h  = &pvdc2h->Header;
        day = pmc2h->ModuleDate & 0x1f;           // bits 0-4
        month = (pmc2h->ModuleDate >> 5) & 0xf;   // bits 5-8
        year = (pmc2h->ModuleDate >> 9) & 0x7f;   // bits 9-15
        year += 1980;                             // offset from 1980
        second = pmc2h->ModuleTime & 0x1f;        // bits 0-4
        second *= 2;                              // packed format is sec/2
        minute = (pmc2h->ModuleTime >> 5) & 0x3f; // bits 5-10
        hour = (pmc2h->ModuleTime >> 11) & 0x1f;  // bits 11-15

        /*
         *  Display the results.  Note that ModuleName and HostModuleName are
         *  always ANSI strings.  We display them using printf() because if
         *  UNICODE is defined, a %s in the resource string means to plug in
         *  a UNICODE string.
         */

        PrintMessage( IDS_QUERY_C2H1,  pmc2h->ByteCount );
        PrintMessage( IDS_QUERY_C2H2,  pmc2h->ModuleCount );
        PrintMessage( IDS_QUERY_C2H3,  pmc2h->ModuleClass );
        PrintMessage( IDS_QUERY_C2H4,  pmc2h->VersionL );
        PrintMessage( IDS_QUERY_C2H5,  pmc2h->VersionH );
        PrintMessage( IDS_QUERY_C2H6 );
        printf( "%s\n", pmc2h->ModuleName );
        PrintMessage( IDS_QUERY_C2H7 );
        printf( "%s\n", pmc2h->HostModuleName );
        PrintMessage( IDS_QUERY_C2H8,  month, day, year );
        PrintMessage( IDS_QUERY_C2H9,  hour, minute, second );
        PrintMessage( IDS_QUERY_C2H10, pmc2h->ModuleSize );
    }
     
    /*
     *  Create a thread that will be waiting to receive commands from the client
     */

    
    gLastCount = GetTickCount();
      
    /*
     *  Initialize the thread block to be sent as argument to create thread
     */
    trdBlock.hVC=hVC;
    trdBlock.ErrCode= TRUE;
    trdBlock.fKill = FALSE;

    /*
     * Start the Thread to Receive data from the client
     */

    hThread =CreateThread( NULL,
                      1024 * 2,
                      (LPTHREAD_START_ROUTINE)ReceiveThread,
                      &trdBlock,        
                      0,
                      &ThreadId );                                

    /*
     *  ServerWrite sends data to the client
     */

    rc = ServerWrite(hVC, pBufSend);
    if (!rc)
         exitcode = FAILURE;
    /*
     *  Set this value to be TRUE so that the ReceiveThread can 
     *  return gracefully after all the data has been send
     */
    trdBlock.fKill = TRUE;
    
    PrintMessage(IDS_WAIT_THREAD_RETURN );
    WaitForSingleObject(hThread, INFINITE);
    if (trdBlock.ErrCode == FALSE)
          printf("Error in the ReceiveThread\n");
    
    /*
     *  Finally, close the channel and free allocated memory.
     */
ExitMain:
    
    if ( hThread ) {
        CloseHandle(hThread);
    }
    
    if ( pSessionInfo ) {
        WFFreeMemory( pSessionInfo );
    }
    if ( pVdQbuf ) {
        WFFreeMemory( pVdQbuf );
    }
    if ( hVC ) {
        WFVirtualChannelClose( hVC );
    }
    if ( pBufSend ) {
        free( pBufSend );
    }
    if ( exitcode == FAILURE ) {
        PrintMessage( IDS_ERROR_CTXOVER_FAIL );
    }
    else {
        printf("Exiting main() of server\n");
    }
    return( exitcode );

} /* main() */



/****************************************************************************
* 
* ReceiveThread
*
*       This thread waits to receive command from the client. It assigns
*       the incremented Counter value to the present value 
*
*  ENTRY:
*        pThrdBlk - Structure which has hVC as input,
*                   ErrCode as the Error Code and Flag to exit the thread
*
* EXIT: -
*
*****************************************************************************/
VOID
ReceiveThread(PTHREADRCV pThrdBlk)
{
    BOOLEAN     rc=FALSE;
    ULONG       ulen=0;
    PDRVRESP    pBufRecv;
    HANDLE      hVC;
    INT         i;

    hVC = pThrdBlk->hVC;
    if ( (pBufRecv=(PDRVRESP)calloc(1, sizeof(DRVRESP) )) == NULL ) {
             PrintMessage( IDS_ERROR_MALLOC );
             pThrdBlk->ErrCode = FALSE;
             goto Exit;
    }

    printf("Waiting to receive data from client\n");    
    
    while (!pThrdBlk->fKill) {
        pBufRecv->uLen = sizeof(DRVRESP);
         rc = WFVirtualChannelRead( hVC,
                                    TIME_OUT, // Time in milliseconds
                                    (PCHAR)pBufRecv,
                                    pBufRecv->uLen,
                                    &ulen );
       
        /*
         *  If the Error Code returned is ERROR_IO_INCOMPLETE or WAIT_TIMEOUT
         *  then we carry on as the Client might not have anything to send 
         */
         if ( (rc != TRUE) && 
              ( (GetLastError() == ERROR_IO_INCOMPLETE ) ||
                (GetLastError() == WAIT_TIMEOUT ))) {
           continue;
         }

        /*
         *  Print debugging information -- received over packet and contents.
         */

        if ( vfDebug ) {
           PrintMessage ( IDS_INFO_RCVD );
           PrintMessage ( IDS_DATA_RCVD, pBufRecv->uType, pBufRecv->uLen,
                          pBufRecv->uCounter);
           printf("          ");
           for ( i=0; i < 13 ; i++ ) {
               printf( "%02x ",*(((PBYTE)pBufRecv)+i) );
           }
           printf( "\n" );
        } 
       
        if (pBufRecv->uType != OVERFLOW_JUMP) {
            PrintMessage( IDS_ERROR_PROTOCOL);
            pThrdBlk->ErrCode = FALSE;
            goto Exit;
        } 

        guCounter = pBufRecv->uCounter;
        printf("Counter being updated to %d\n",pBufRecv->uCounter);
    }
    
Exit:
    if ( pBufRecv ) 
        free( pBufRecv );   
    
    return;
}  /* ReceiveThread */




/****************************************************************************
*
* ServerWrite
*
*    Send data to client till the buffer gets overfilled. 
*   Wait for restart and do it again
*
*  ENTRY:
*      hVC          handle to the Virtual Channel
*      pBufSend     Buffer to send to the Client
*      pTrdBlock    ThreadBlock sent to ReceiveThread
*
*  EXIT:
*      returns TRUE if successful, FALSE if not
*
*****************************************************************************/
BOOLEAN 
ServerWrite(HANDLE hVC, 
          POVER pBufSend)
{
    BOOLEAN     rc = TRUE;
    ULONG       ulen = 0;    
       
    /*
     *  Fill in the fields for packet to send
     */
    pBufSend->uCounter = 0;
    pBufSend->uType = OVER_TYPE_BEGIN;
    pBufSend->uSign = VC_OVER_SIGNATURE;
    pBufSend->uLen = sizeof(OVER);
    
    if ( vfDebug ) PrintMessage( IDS_BEGIN_PACKET );

    while (TRUE) {

        pBufSend->ulServerMS  = GetTickCount() - gLastCount;
        guCounter++;
        pBufSend->uCounter = guCounter;
        printf("Server: Seq_No Being sent is %d\n",pBufSend->uCounter);
        
       /*
        *  Send the packet to the client.
        */
        if ( vfDebug ) 
        PrintMessage( IDS_SENDOVER_SUCCESS, pBufSend->uLen,
            GetTickCount() - gLastCount);
        
       rc = WFVirtualChannelWrite(hVC,
                                   (PCHAR)pBufSend,
                                   pBufSend->uLen,
                                   &ulen );
       
        if ( rc != TRUE ) {
            PrintMessage( IDS_ERROR_WRITE_FAILED, GetLastError() );
            goto ErrExit;
        }
    
        if ( pBufSend->uLen != ulen ) {
           PrintMessage( IDS_ERROR_WRITE_SHORT, ulen );
           goto ErrExit;
       }
       /* 
        * Added so that the flow can be seen and the client is not bombarded
        * with data.   
        */
       Sleep(500);

       /*
        * This is when the server decides to end transmission 
        * as it has nothing more to send
        */
       if (pBufSend->uCounter >= NO_MORE_DATA) {
           printf("Server: No more data to send.\n\
Ending connection at Seq No %d\n",NO_MORE_DATA);
           break; 
       }
    }
    
    if ( vfDebug ) {
        PrintMessage( IDS_END_PACKET );
    }
            
    return rc;

ErrExit:
    rc = FALSE;
    return rc;

}/* ServerWrite */


 
/*******************************************************************************
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
 ******************************************************************************/

VOID WINAPI
PrintMessage( int nResourceID, ...)
{
    _TCHAR str1[MAX_IDS_LEN+1], str2[2*MAX_IDS_LEN+1];

    va_list args;
    va_start( args, nResourceID );

    if ( LoadString( NULL, nResourceID, (LPTSTR)str1, sizeof(str1) / sizeof(*str1) ) ) {

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

