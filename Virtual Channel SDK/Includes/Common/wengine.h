/*******************************************************************************
 *
 * wengine.h
 *
 * structure for engine APIs.
 *
 * Copyright © Citrix Systems, Inc.  All rights reserved.
 *
 *******************************************************************************/



#ifndef _WENGINE_H_
#define _WENGINE_H_

#include <ctxgraph.h>

/*******************************************************************************
 *
 *  ICAENG_OPENDATA, PICAENG_OPENDATA.
 *
 ******************************************************************************/

typedef struct _ICAENG_OPENDATA
{
    UINT32              uiVersion;     /* structure version */

    /* Version 1 */

    LPSTR               pszClientName; /* client name (???) */


    PFNUIPOLL           pfnUIPoll ;    /* (optional) UI poll function */
    LPSTR               pszLogLabel;   /* (optional) connection id string */
    LPSTR               pszClientSN;   /* (optional) client serial number */
}
ICAENG_OPENDATA, * PICAENG_OPENDATA;


/*******************************************************************************
 *
 *  ICAENG_OPENDATA, PICAENG_OPENDATA.
 *
 ******************************************************************************/

typedef struct _ICAENG_INITSESSIONDATA
{
    UINT32  uiVersion;     /* structure version */

    /* Version 1 */

    UINT32  uiPrfWidth;    /* the preferred width of the remote desktop */
    UINT32  uiPrfHeight;   /* the preferred height of the remote desktop */
    UINT32  uiMaxWidth;    /* the maximum width of the remote desktop */
    UINT32  uiMaxHeight;   /* the maximum height of the remote desktop */
    GRAPH_COLORSPACE    uiPreferredColorSpace;  /* the preferred color space for the remote desktop */
    GRAPH_COLORSPACE    uiClientColorSpace;     /* the color space of the local desktop */

    HND     hWndParent;    /* (optional) parent window handle */
}
ICAENG_INITSESSIONDATA, * PICAENG_INITSESSIONDATA;



/*******************************************************************************
 *
 *  ICAENG_DESKTOPINFO, PICAENG_DESKTOPINFO.
 *
 ******************************************************************************/

typedef struct _ICAENG_DESKTOPINFO
{
    UINT32     uiVersion;  /* structure version */
    /* Version 1 */
    UINT32     uiWidth;
    UINT32     uiHeight;

    UINT16     vColorMode;
    /* version 2 */
    UINT16     uiFlags;
#define DESKTOP_CHANGE_ACCEPTED 0x1
}
ICAENG_DESKTOPINFO, * PICAENG_DESKTOPINFO;


/* Seamless VD interface functions defined in the engine */

INT
TWIVdSeamlessHostCommand( PVOID cmdBuf, UINT16 bufLen );


/* Headless client modes are passed on to ThinWire */

INT
TWVdRenderingMode( PVOID cmdBuf, UINT16 bufLen);


#define	TwOutputMode()	0 /*This mode is full headless mode. 
                                          * Here we discard any thinwire packet
                                          * after the server and client exchange init responses.
                                          * Thus now the server expects no responses from the
                                          * client.  For this mode 
                                          *                 disable disk caching on the client
                                          */

#endif /* _WENGINE_H_ */

