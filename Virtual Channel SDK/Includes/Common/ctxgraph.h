/******************************************************************************
 * 
 *  ctxgraph.h
 *
 *  Graphics abstraction definitions.
 *
 *  Copyright  Citrix Systems, Inc. All rights reserved.
 *
 *****************************************************************************/

#ifndef _CTXGRAPH_H_
#define _CTXGRAPH_H_

#include "basetype.h"
#include "platcomm.h"

/*****************************************************************************
 *
 *  Error codes
 *
 *****************************************************************************/

#define GRAPH_SUCCESS		              0x00000000

#define GRAPH_ERR_NO_MEM                      0x80000001
#define GRAPH_ERR_INVALID_PARAMETER           0x80000002
#define GRAPH_ERR_OUT_OF_BOUNDS               0x80000003
#define GRAPH_ERR_NOT_PALETTED_SURFACE        0x80000004
#define GRAPH_ERR_PALETTE_ATTACHED            0x80000005
#define GRAPH_ERR_BUFFER_TOO_SMALL            0x80000006
#define GRAPH_ERR_CREATE_CRITICAL_SECTION     0x80000007
#define GRAPH_ERR_ENTER_CRITICAL_SECTION      0x80000008
#define GRAPH_ERR_LEAVE_CRITICAL_SECTION      0x80000009
#define GRAPH_ERR_DESTROY_CRITICAL_SECTION    0x8000000A
#define GRAPH_ERR_BAD_USER_HANDLE             0x8000000B
#define GRAPH_ERR_FREE_MEM                    0x8000000C 	
#define GRAPH_ERR_GDC_SHARING_VIOLATION       0x8000000D
#define GRAPH_ERR_PLATFORM_REGION_CREATE      0x8000000E
#define GRAPH_ERR_PLATFORM_REGION_DESTROY     0x8000000F
#define GRAPH_ERR_PLATFORM_REGION_GETBOX      0x80000010
#define GRAPH_ERR_PLATFORM_REGION_COMBINE     0x80000011
#define GRAPH_ERR_VALUE_NOT_SET               0x80000012
#define GRAPH_ERR_OS_API_FAILURE              0x80000013
#define GRAPH_ERR_ENUM_FAILED                 0x80000014
#define GRAPH_ERR_UNSUPPORTED                 0x80000015
#define GRAPH_ERR_INTERNAL_ERROR              0x80000016
#define GRAPH_ERR_PLATFORM_REGION_OFFSET      0x80000017
#define GRAPH_ERR_PLATFORM_REGION_STARTENUM   0x80000018
#define GRAPH_ERR_BAD_DEPTH                   0x80000019
#define GRAPH_ERR_NOT_IMPLEMENTED             0x8FFFFFFF

/*****************************************************************************
 *
 *  Data types
 *
 *****************************************************************************/

/*
 *  GA Capabilities
 */

/*
 *  !!!
 *  For version 1, ignore BEZIERS, ELLIPSES, LINE_ALG_NT, OFFSCREEN_SURF,
 *  and BITMAP2 (i.e. only VERSION, LINES, CURSOR, and BITMAP1 are valid).
 *  !!!
 */
#define GCAPINDEX_GA_VERSION        0   /* probly not necessary, but hey... */
#define GCAPINDEX_LINES             1   /* GDC_drawLines API available */
#define GCAPINDEX_BEZIERS           2   /* GDC_drawBeziers API available */
#define GCAPINDEX_ELLIPSES          3   /* GDC_drawEllipse API available  */
#define GCAPINDEX_CURSOR            4   /* what kind of cursor support */
#define GCAPINDEX_LINE_ALG_NT       5   /* GDC_drawLines supports NT line alg */
#define GCAPINDEX_OFFSCREEN_SURF    6   /* can draw on offscreen GDCs */
#define GCAPINDEX_BITMAP1           7   /* what kind of bitmaps are supported */
#define GCAPINDEX_BITMAP2           8   /* cont'd */
#define GCAPINDEX_OBSCUREDREGION    9   /* platform supports bitblt obscured regions */
#define GCAPINDEX_PALNOREDRAW       10  /* client do not need redraw after palette change*/

#define GCAPINDEX_MULTISIZE_BRUSH   11  /* support multisize brushes   */
#define GCAPINDEX_JPEG              12  /* support IJG JPEG library commands */
#define GCAPINDEX_MAX               13  /* keep this updated */


/* for most things */
#define GCAP_NOT_IMPLEMENTED        0x00
#define GCAP_IMPLEMENTED            0xFF

/* for GCAPINDEX_CURSOR */
#define GCAP_CURSOR_HARDWARE    1
#define GCAP_CURSOR_SOFTWARE    2

/* for GCAPINDEX_BITMAP1 */
#define GCAP_BITMAP_PALETTED_1BPP   0x01
#define GCAP_BITMAP_PALETTED_2BPP   0x02    /* IGNORE for version 1 */
#define GCAP_BITMAP_PALETTED_4BPP   0x04
#define GCAP_BITMAP_PALETTED_8BPP   0x08
#define GCAP_BITMAP_RGB_15BIT       0x10    /* IGNORE for version 1 */
#define GCAP_BITMAP_RGB_16BIT       0x20    /* IGNORE for version 1 */
#define GCAP_BITMAP_RGB_24BIT       0x40    /* IGNORE for version 1 */
#define GCAP_BITMAP_RGB_32BIT       0x80    /* IGNORE for version 1 */

/* for GCAPINDEX_BITMAP2 */
#define GCAP_BITMAP_YUV_24BIT       0x01    /* IGNORE for version 1 */
 
/* Bitmap creation modes: */
#define GA_BITMAP_CREATE_COMPATIBLE 0x00   /* Standard - compatible with the screen */
#define GA_BITMAP_CREATE_SECTION    0x01   /* Using DIB section (on Windows), used for accelerated data access */
#define GA_BITMAP_CREATE_LVB        0x02   /* let the platform code know if this bitmap is going to be used for an LVB */

/*
 *  Typedefs
 */
 
/* GAI object types - callers of GAI use these incomplete types as
 * handles, but internally GAI knows the internals of the structs.
 */
typedef struct _GDC *HGDC, **PHGDC;
typedef struct _GBRUSH *HGBRUSH, **PHGBRUSH;
typedef struct _GBITMAP *HGBITMAP, **PHGBITMAP;
typedef struct _GCURSOR *HGCURSOR, **PHGCURSOR;
typedef struct _GREGION *HGREGION, **PHGREGION;


typedef enum
{
    GCS_UNSPECIFIED,
    GCS_PALETTED_1BIT,
    GCS_PALETTED_2BIT,
    GCS_PALETTED_4BIT,               /* 4bit deprecated 11/08, but enum value should remain */
    GCS_PALETTED_8BIT,
    GCS_RGB_15BIT,
    GCS_RGB_16BIT,
    GCS_RGB_24BIT,
    GCS_RGB_32BIT
} GRAPH_COLORSPACE;

#define COLOR_INVALID    0x00
#define COLOR_RGB        0x01
#define COLOR_YUV        0x02               /* IGNORE for version 1 */
#define COLOR_PALETTEREF 0x03
#define COLOR_IDENTITYPAL 0x04

typedef struct
{
    UINT8 colorData[3];
    UINT8 flags;
} GRAPH_COLOR, * PGRAPH_COLOR;

typedef struct
{
    INT32 width;
    INT32 height;
    GRAPH_COLORSPACE colorSpace;
    PGRAPH_COLOR vColors;
} GRAPH_BITMAPINFO, * PGRAPH_BITMAPINFO;

typedef struct
{
    INT32 xLeft;
    INT32 yTop;
    INT32 xRight;
    INT32 yBottom;
} GRAPH_RECT, * PGRAPH_RECT;


typedef struct
{
    INT32 resX;
    INT32 resY;
    GRAPH_COLORSPACE colorSpace;
} GRAPH_MODEINFO, * PGRAPH_MODEINFO;

typedef enum
{
    ROP2_CLEAR,                 /* 0          */
    ROP2_SRC,                   /* S          */
    ROP2_DST,                   /* D          */
    ROP2_NOTDST,                /* ~D         */
    ROP2_SRC_AND_DST,           /* S & D      */
    ROP2_SRC_AND_NOTDST,        /* S & ~D     */
    ROP2_NOTSRC_AND_DST,        /* ~S & D     */
    ROP2_SRC_OR_DST,            /* S | D      */
    ROP2_SRC_OR_NOTDST,         /* S | ~D     */
    ROP2_NOTSRC_OR_DST,         /* ~S | D     */
    ROP2_SRC_XOR_DST,           /* S xor D    */
    ROP2_NOT_SRC,               /* ~(S)       */
    ROP2_NOT_SRC_AND_DST,       /* ~(S & D)   */
    ROP2_NOT_SRC_OR_DST,        /* ~(S | D)   */
    ROP2_NOT_SRC_XOR_DST,       /* ~(S xor D) */
    ROP2_SET,                    /* 1          */
    ROP2_INVALID
} GRAPH_ROP2, *PGRAPH_ROP2;



typedef UINT8 GRAPH_ROP3;

/*
 *  Give names to some particularly useful ROP3s.  
 */
#define GRP_SRCCOPY     (GRAPH_ROP3)0xCC /* dest = source                   */
#define GRP_SRCPAINT    (GRAPH_ROP3)0xEE /* dest = source OR dest           */
#define GRP_SRCAND      (GRAPH_ROP3)0x88 /* dest = source AND dest          */
#define GRP_SRCINVERT   (GRAPH_ROP3)0x66 /* dest = source XOR dest          */
#define GRP_SRCERASE    (GRAPH_ROP3)0x44 /* dest = source AND (NOT dest )   */
#define GRP_NOTSRCCOPY  (GRAPH_ROP3)0x33 /* dest = (NOT source)             */
#define GRP_NOTSRCERASE (GRAPH_ROP3)0x11 /* dest = (NOT src) AND (NOT dest) */
#define GRP_MERGECOPY   (GRAPH_ROP3)0xC0 /* dest = (source AND pattern)     */
#define GRP_MERGEPAINT  (GRAPH_ROP3)0xBB /* dest = (NOT source) OR dest     */
#define GRP_PATCOPY     (GRAPH_ROP3)0xF0 /* dest = pattern                  */
#define GRP_PATPAINT    (GRAPH_ROP3)0xFB /* dest = DPSnoo                   */
#define GRP_PATINVERT   (GRAPH_ROP3)0x5A /* dest = pattern XOR dest         */
#define GRP_DSTINVERT   (GRAPH_ROP3)0x55 /* dest = (NOT dest)               */
#define GRP_BLACKNESS   (GRAPH_ROP3)0x00 /* dest = BLACK                    */
#define GRP_WHITENESS   (GRAPH_ROP3)0xFF /* dest = WHITE                    */
#define GRP_DESTORPAT	(GRAPH_ROP3)0xFA /* dest = dest OR pat				*/


typedef enum
{
    REGION_OP_UNION,
    REGION_OP_DIFF,
    REGION_OP_INTERSECT,
    REGION_OP_XOR,
    REGION_OP_COPY
} GRAPH_REGION_OP;

typedef USHORT GRAPH_COLOR16;

typedef struct
{
    INT32   x;
    INT32   y;
    GRAPH_COLOR16 Red;
    GRAPH_COLOR16 Green;
    GRAPH_COLOR16 Blue;
} GRAPH_TRIVERTEX, *PGRAPH_TRIVERTEX;

typedef BOOLEAN
(* PFNENUMMODESCALLBACK)( PGRAPH_MODEINFO, PVOID );


/* 
 * Below definitions are used with CALLBACK FUNCTIONS that are set
 * through the Graph_setCallbacks function.
 *
 * Part of the definition is that the caller of Graph_setCallbacks() provides
 * a pointer to persistent memory (static or dynamically allocated) so that
 * the GA does need not (and should not) copy the structure. That allows the
 * caller to change the functions at any time.
 *
 * OSS - here means off screen surfaces (also known as in-memory bitmaps)
 *
 */

typedef BOOLEAN (* PFNOSSCALLBACK)(HGDC, PVOID);


typedef struct _ga_callbacks {
 	PFNOSSCALLBACK	OnBitmapCreateFailed;   
 	PFNOSSCALLBACK	OnBitmapIsDirty;            
} GRAPH_CALLBACKS, *PGRAPH_CALLBACKS;

 
/****************************************************************************
 * Callback function definition that is used for the JPEG functionality     *
 * provided by the GAI                                                      *
 *                                                                          *
 * Description                                                              *
 *                                                                          *
 * A function pointer to a callback function with this prototype can be     *
 * passed into the GAI JPEG decompression functions.  When the libJPEG JPEG *
 * engine requires more data, the callback function provided by the caller  *
 * will be invoked.  The caller will return through the parameters of the   *
 * function a pointer to the additional JPEG data, and the length of that   *
 * data.  The additional JPEG data will be sequential with the data already *
 * passed into the function.  This function may be called many times during *
 * the decompression of a single image.  The number of times that the       *
 * function is invoked is dependant on the amount of data returned to GAI   *
 * with each invocation of this function.                                   *
 *                                                                          *
 * Parameters                                                               *
 *                                                                          *
 * ppBuffer: Out parameter which receives a pointer to additional JPEG data.*
 *                                                                          *
 * pByteCount: Pointer to UINT32 which receives the length of the buffer    *
 * pointed at by the pointer returned through the ppBuffer parameter.       *
 ***************************************************************************/

typedef IBOOL (* PFNSOURCEFILLBUFFER) (PVOID * pContext, PBYTE * ppBuffer,PUINT32 pByteCount);

typedef enum CTXCODEC
{
    UNSUPPORTED_CODEC,
    JPEG_CODEC,
    PEGASUS_IMAGE_CODEC,
    HDPHOTO_CODEC,
    H264_CODEC
}CTXCODEC , * PCTXCODEC;

typedef struct BITMAP_ENCODED_DATA
{
    PBYTE pEncodedData;
    UINT32 EncodedDataSize;
    CTXCODEC Codec;
	BOOLEAN bSwapRB;
}BITMAP_ENCODED_DATA, *PBITMAP_ENCODED_DATA;

typedef struct BITMAP_DECODER_CALLBACK
{
    PFNSOURCEFILLBUFFER pfnSourceFillBuffer;
    PVOID               pContext;
}BITMAP_DECODER_CALLBACK, *PBITMAP_DECODER_CALLBACK;


typedef struct BITMAP_DECODE_DATA
{
    PBYTE               pBitmapBits;
    UINT32              BitmapBitSize;
    PGRAPH_BITMAPINFO   pBitmapInfo;
    PUINT               pDesiredBitsPerPixel;
	UINT32				stride;
}BITMAP_DECODE_DATA, *PBITMAP_DECODE_DATA;


#define MAX_DIRTY_RECT 31 //from protocol spec
typedef struct IMAGE_REGION_DATA
{
    UINT8              RectCount;
    //Sharpening Context
    UINT8               ImageQ;
    GRAPH_RECT          DirtyRect[MAX_DIRTY_RECT];
}IMAGE_REGION_DATA, *PIMAGE_REGION_DATA;


/*****************************************************************************
 *
 *  Function types for vtable
 *
 *****************************************************************************/
typedef VPSTATUS (* PFNGDC_REALIZEPALETTE)(HGDC);
typedef VPSTATUS (* PFNGDC_CREATECOMPATIBLE)(HGDC, PHGDC);
typedef VPSTATUS (* PFNGDC_DESTROY)(PHGDC);
typedef VPSTATUS (* PFNGDC_SELECTBITMAP)(HGDC, HGBITMAP);
typedef VPSTATUS (* PFNGDC_SELECTCLIPREGION)(HGDC, HGREGION);
typedef VPSTATUS (* PFNGDC_SELECTBRUSH)(HGDC, HGBRUSH);
typedef VPSTATUS (* PFNGDC_SETBRUSHORIGIN)(HGDC, INT32, INT32);
typedef VPSTATUS (* PFNGDC_SETPALETTE)(HGDC, UINT8, UINT16, PGRAPH_COLOR, PIBOOL);
typedef VPSTATUS (* PFNGDC_SETFGCOLOR)(HGDC, GRAPH_COLOR);
typedef VPSTATUS (* PFNGDC_GETFGCOLOR)(HGDC, PGRAPH_COLOR);
typedef VPSTATUS (* PFNGDC_SETBKCOLOR)(HGDC, GRAPH_COLOR);
typedef VPSTATUS (* PFNGDC_GETBKCOLOR)(HGDC, PGRAPH_COLOR);
typedef VPSTATUS (* PFNGDC_SETROP2)(HGDC, GRAPH_ROP2);
typedef VPSTATUS (* PFNGDC_GETROP2)(HGDC, PGRAPH_ROP2);
typedef VPSTATUS (* PFNGDC_BITBLT)(HGDC, INT32, INT32, INT32, INT32,
                                         HGDC, INT32, INT32, GRAPH_ROP3, PHGREGION);
typedef VPSTATUS (* PFNGDC_PAINTREGION)(HGDC, HGREGION);
typedef VPSTATUS (* PFNGDC_FILLRECT)(HGDC, PGRAPH_RECT);
typedef VPSTATUS (* PFNGDC_MOVETO)(HGDC, INT32, INT32);
typedef VPSTATUS (* PFNGDC_LINETO)(HGDC, INT32, INT32);
typedef VPSTATUS (* PFNGDC_GETBITS)(HGDC, PGRAPH_RECT,
                                          PGRAPH_BITMAPINFO, PVOID);
typedef VPSTATUS (* PFNGDC_SETBITS)(HGDC, INT32, INT32, INT32, INT32,
                                          INT32, INT32, PVOID, PGRAPH_BITMAPINFO, GRAPH_ROP3);
typedef VPSTATUS (* PFNGDC_STRETCHBITS)(HGDC, INT32, INT32, INT32, INT32,
                                          INT32, INT32, INT32, INT32, PVOID, PGRAPH_BITMAPINFO, GRAPH_ROP3);
typedef VPSTATUS (* PFNGRAPH_GRADIENTFILL) (HGDC, PGRAPH_TRIVERTEX, UINT32, PUINT32, UINT32, UINT32);

/*****************************************************************************
 *
 *  Vtable type
 *
 *****************************************************************************/
typedef struct _GRAPHCALLTABLE
{
    PFNGDC_REALIZEPALETTE       pfnGDC_realizePalette;
    PFNGDC_CREATECOMPATIBLE     pfnGDC_createCompatible;
    PFNGDC_DESTROY              pfnGDC_destroy;
    PFNGDC_SELECTBITMAP         pfnGDC_selectBitmap;
    PFNGDC_SELECTCLIPREGION     pfnGDC_selectClipRegion;
    PFNGDC_SELECTBRUSH          pfnGDC_selectBrush;
    PFNGDC_SETBRUSHORIGIN       pfnGDC_setBrushOrigin;
    PFNGDC_SETPALETTE           pfnGDC_setPalette;
    PFNGDC_SETFGCOLOR           pfnGDC_setFgColor;
    PFNGDC_GETFGCOLOR           pfnGDC_getFgColor;
    PFNGDC_SETBKCOLOR           pfnGDC_setBkColor;
    PFNGDC_GETBKCOLOR           pfnGDC_getBkColor;
    PFNGDC_SETROP2              pfnGDC_setROP2;
    PFNGDC_GETROP2              pfnGDC_getROP2;
    PFNGDC_BITBLT               pfnGDC_bitBlt;
    PFNGDC_PAINTREGION          pfnGDC_paintRegion;
    PFNGDC_FILLRECT             pfnGDC_fillRect;
    PFNGDC_MOVETO               pfnGDC_moveTo;
    PFNGDC_LINETO               pfnGDC_lineTo;
    PFNGDC_GETBITS              pfnGDC_getBits;
    PFNGDC_SETBITS              pfnGDC_setBits;
    PFNGDC_STRETCHBITS          pfnGDC_stretchBits;
    PFNGRAPH_GRADIENTFILL       pfnGDC_gradientFill;
} GRAPHCALLTABLE, * PGRAPHCALLTABLE, ** PPGRAPHCALLTABLE;

VPSTATUS Graph_load(void);
VPSTATUS Graph_unload(void);

const GRAPHCALLTABLE* Graph_GetTable (void);
void Graph_SetTable (const GRAPHCALLTABLE* newTable);



/*****************************************************************************
 *
 *  Macros for accessing the vtable
 *
 *****************************************************************************/
#define GRAPH_GLOBAL_INIT const GRAPHCALLTABLE* g_pGraphCallTable = NULL;
#define GRAPH_EXTERN_INIT extern const GRAPHCALLTABLE* g_pGraphCallTable;

// Note: It is hard to see how this would work without call tables, because we use a hack to swap
// the tables. 
#ifdef USE_GRAPH_CALL_TABLE

#define GraphSetupCallTable() g_pGraphCallTable = Graph_GetTable ()

#if !MAC_INTEL_COMPILING_WRAPPER
GRAPH_EXTERN_INIT
#endif /* !MAC_INTEL_COMPILING_WRAPPER */

#define GDC_realizePalette (*(g_pGraphCallTable)->pfnGDC_realizePalette)
#define GDC_createCompatible (*(g_pGraphCallTable)->pfnGDC_createCompatible)
#define GDC_destroy (*(g_pGraphCallTable)->pfnGDC_destroy)
#define GDC_selectBitmap (*(g_pGraphCallTable)->pfnGDC_selectBitmap)
#define GDC_selectClipRegion (*(g_pGraphCallTable)->pfnGDC_selectClipRegion)
#define GDC_selectBrush (*(g_pGraphCallTable)->pfnGDC_selectBrush)
#define GDC_setBrushOrigin (*(g_pGraphCallTable)->pfnGDC_setBrushOrigin)
#define GDC_setPalette (*(g_pGraphCallTable)->pfnGDC_setPalette)
#define GDC_setFgColor (*(g_pGraphCallTable)->pfnGDC_setFgColor)
#define GDC_getFgColor (*(g_pGraphCallTable)->pfnGDC_getFgColor)
#define GDC_setBkColor (*(g_pGraphCallTable)->pfnGDC_setBkColor)
#define GDC_getBkColor (*(g_pGraphCallTable)->pfnGDC_getBkColor)
#define GDC_setROP2 (*(g_pGraphCallTable)->pfnGDC_setROP2)
#define GDC_getROP2 (*(g_pGraphCallTable)->pfnGDC_getROP2)
#define GDC_bitBlt (*(g_pGraphCallTable)->pfnGDC_bitBlt)
#define GDC_paintRegion (*(g_pGraphCallTable)->pfnGDC_paintRegion)
#define GDC_fillRect (*(g_pGraphCallTable)->pfnGDC_fillRect)
#define GDC_moveTo (*(g_pGraphCallTable)->pfnGDC_moveTo)
#define GDC_lineTo (*(g_pGraphCallTable)->pfnGDC_lineTo)
#define GDC_getBits (*(g_pGraphCallTable)->pfnGDC_getBits)
#define GDC_setBits (*(g_pGraphCallTable)->pfnGDC_setBits)
#define GDC_stretchBits (*(g_pGraphCallTable)->pfnGDC_stretchBits)
#define GDC_gradientFill (*(g_pGraphCallTable)->pfnGDC_gradientFill)
#endif

VPSTATUS Graph_getDisplayMode (PGRAPH_MODEINFO pModeInfo);
VPSTATUS Graph_setDisplayMode (PGRAPH_MODEINFO pModeInfo);
VPSTATUS Graph_enumDisplayModes (PFNENUMMODESCALLBACK pfnEnumModesCallback, PVOID pUserData);
VPSTATUS Graph_getCapabilities (PUINT16 pcbCaps, PUINT8 pCaps);
VPSTATUS GDC_flush (HGDC hGDC);
VPSTATUS GDC_clone (HGDC hGDC_Orig, PHGDC phGDC_Clone);
VPSTATUS GDC_create (HND hWindow, PHGDC pNewHGDC);
VPSTATUS Brush_create (HGDC hgdc, PGRAPH_BITMAPINFO pBitmapInfo, PVOID pBitmapData, PHGBRUSH phBrush);
VPSTATUS Brush_createSolid (GRAPH_COLOR color, PHGBRUSH phBrush);
VPSTATUS Brush_duplicateSolidBrush (HGBRUSH  SourceBrush, PHGBRUSH pDestinationBrush);
VPSTATUS Brush_destroy (PHGBRUSH phBrush);
VPSTATUS Bitmap_destroy (PHGBITMAP phBitmap);
VPSTATUS Bitmap_create (HGDC hgdc, PGRAPH_BITMAPINFO pBitmapInfo, PVOID pBitmapData, PHGBITMAP phBitmap, UINT32  flags);

VPSTATUS Bitmap_createFromJPEG (PBYTE pJpegData, UINT32 jpegDataSize, PFNSOURCEFILLBUFFER pfnSourceFillBuffer, 
								PVOID pContext, PGRAPH_BITMAPINFO pBitmapInfo, PBYTE* ppBitmapBits, PUINT32 pBitmapBitSize);

VPSTATUS Bitmap_queryJPEGInformation (PBYTE pJpegData, UINT32 jpegDataSize, PFNSOURCEFILLBUFFER pfnSourceFillBuffer,
									  PVOID pContext, PGRAPH_BITMAPINFO pBitmapInfo, PUINT32 pDecompressedByteCount);

IBOOL Bitmap_supportsEncodedType (CTXCODEC CodecType);

VPSTATUS Bitmap_createFromEncoded (PBITMAP_ENCODED_DATA pEncodedData,
                                   PBITMAP_DECODER_CALLBACK pRenderCallback,
                                   PBITMAP_DECODE_DATA pDecodedData);

VPSTATUS Bitmap_queryEncodedInformation (PBITMAP_ENCODED_DATA pEncodedData, PUINT pDesiredBitsPerPixel,
										 PUINT32 pDecompressedByteCount);

VPSTATUS Bitmap_createFromEncodedH264(PBITMAP_ENCODED_DATA pEncodedData, PBITMAP_DECODER_CALLBACK pRenderCallback, PBITMAP_DECODE_DATA pDecodedData, PGRAPH_RECT rect,  PGRAPH_RECT pDirtyRect, UINT8 rcCount);

VPSTATUS Bitmap_queryEncodedInformationH264(PBITMAP_ENCODED_DATA pEncodedData, PUINT pDesiredBitsPerPixel, PUINT32 pDecompressedByteCount,PGRAPH_RECT rect);

VPSTATUS Bitmap_createFromEncodedJPEG(PBITMAP_ENCODED_DATA pEncodedData, PBITMAP_DECODE_DATA pDecodedData);

VPSTATUS Cursor_create (INT32 xHotSpot, INT32 yHotSpot, PVOID pFaceData, PGRAPH_BITMAPINFO pFaceInfo,
						PVOID pMaskData, PGRAPH_BITMAPINFO pMaskInfo, BOOLEAN fMonochrome, BOOLEAN fHasAlpha, HGDC hgDC, PHGCURSOR phCursor);
VPSTATUS Cursor_createColorCursor( INT32 xHotSpot, INT32 yHotSpot, PVOID pFaceData, PGRAPH_BITMAPINFO pFaceInfo, PHGCURSOR phCursor);
VPSTATUS Cursor_destroy (PHGCURSOR phCursor);
VPSTATUS Region_create (UINT16 numRects, PGRAPH_RECT vRects, PHGREGION phRegion);
VPSTATUS Region_destroy (PHGREGION phRegion);
VPSTATUS Region_combine (HGREGION hRegion1, HGREGION hRegion2, GRAPH_REGION_OP op, HGREGION hResult);
VPSTATUS Region_getBox (HGREGION hRegion, PGRAPH_RECT pRect);
VPSTATUS Region_offset (HGREGION hRegion, INT32 xOffset, INT32 yOffset);
VPSTATUS Region_startEnum (HGREGION hRegion, PPVOID ppState);
IBOOL Region_enum (PVOID pState, PGRAPH_RECT pRect);
VPSTATUS Region_endEnum (PVOID pState);
VPSTATUS Graph_setCallbacks (GRAPH_CALLBACKS *pGraphCallbacks);
VPSTATUS GDC_setUserData (HGDC   hGDC, PVOID pUserData);
VPSTATUS GDC_getUserData (HGDC   hGDC, PPVOID ppUserData);
VPSTATUS Graph_getFontSmoothing (PUSHORT pType);

// We'll be using hard-coded RGBA format instead of RGB (or any other format)
// because this saves us from processing in CoreGraphics, where it tries to
// convert image RGB to RGBA and ends up consuming lot of CPU.
#define USE_RGBA_AS_FINAL_IMAGE_FORMAT 1

#ifndef USE_GRAPH_CALL_TABLE
/*****************************************************************************
 *
 *  Prototypes for when we aren't using the vtable (e.g. GA implementations)
 *
 *****************************************************************************/

#ifdef IN
#undef IN
#endif
#define IN

#ifdef OUT
#undef OUT
#endif
#define OUT

#ifdef INOUT
#undef INOUT
#endif
#define INOUT

#define GraphSetupCallTable()

VPSTATUS
GDC_realizePalette(
    IN HGDC hGDC);


VPSTATUS
GDC_createCompatible(
    IN   HGDC  hGDC,
    OUT  PHGDC pNewHGDC );

VPSTATUS
GDC_destroy(
    IN  PHGDC phGDC );

VPSTATUS
GDC_selectBitmap(
    IN  HGDC hGDC,
    IN  HGBITMAP hBitmap );

VPSTATUS
GDC_selectClipRegion(
    IN  HGDC hGDC,
    IN  HGREGION hRegion );

VPSTATUS
GDC_selectBrush(
    IN  HGDC hGDC,
    IN  HGBRUSH hBrush );

VPSTATUS
GDC_setBrushOrigin(
    IN   HGDC hGDC,
    IN   INT32 newX,
    IN   INT32 newY );

VPSTATUS
GDC_setPalette(
    IN    HGDC hGDC,
    IN    UINT8 startEntry,
    IN    UINT16 numEntries,
    IN    PGRAPH_COLOR vColors,
    INOUT PIBOOL pbRedraw);

VPSTATUS
GDC_setFgColor(
    IN  HGDC hGDC,
    IN  GRAPH_COLOR color );

VPSTATUS
GDC_getFgColor(
    IN  HGDC hGDC,
    OUT PGRAPH_COLOR pColor );

VPSTATUS
GDC_setBkColor(
    IN  HGDC hGDC,
    IN  GRAPH_COLOR color );

VPSTATUS
GDC_getBkColor(
    IN  HGDC hGDC,
    OUT PGRAPH_COLOR pColor );

VPSTATUS
GDC_setROP2(
    IN  HGDC hGDC,
    IN  GRAPH_ROP2 rop );

VPSTATUS
GDC_getROP2(
IN  HGDC hGDC ,
OUT PGRAPH_ROP2 pROP2
);

VPSTATUS
GDC_bitBlt(
    IN  HGDC hDstGDC,
    IN  INT32 destX,
    IN  INT32 destY,
    IN  INT32 destWidth,
    IN  INT32 destHeight,
    IN  HGDC hSrcGDC,
    IN  INT32 srcX,
    IN  INT32 srcY,
    IN  GRAPH_ROP3 rop,
    INOUT PHGREGION phObscuredRegion );

VPSTATUS
GDC_paintRegion(
    IN   HGDC hGDC,
    IN   HGREGION hRegion );

VPSTATUS
GDC_fillRect(
    IN   HGDC hGDC,
    IN   PGRAPH_RECT pRect );

VPSTATUS
GDC_moveTo(
    IN   HGDC hGDC,
    IN   INT32 newX,
    IN   INT32 newY );

VPSTATUS
GDC_lineTo(
    IN   HGDC hGDC,
    IN   INT32 endX,
    IN   INT32 endY );

VPSTATUS
GDC_getBits(
    IN    HGDC hGDC,
    IN    PGRAPH_RECT pSrcRect,
    INOUT PGRAPH_BITMAPINFO pGBitmapInfo,
    OUT   PVOID pData);

VPSTATUS
GDC_setBits(
    IN   HGDC dest,
    IN   INT32 destX,
    IN   INT32 destY,
    IN   INT32 Width,
    IN   INT32 Height,
    IN   INT32 srcX,
    IN   INT32 srcY,
    IN   PVOID pData,
    IN   PGRAPH_BITMAPINFO pGBitmapInfo,
    IN   GRAPH_ROP3 rop );

VPSTATUS
GDC_gradientFill(
                 IN   HGDC dest,                 
                 IN   PGRAPH_TRIVERTEX pVertex,
                 IN   UINT32 nVertex,
                 IN   PUINT32 pMesh,
                 IN   UINT32 nMesh,
                 IN   UINT32 mode);

VPSTATUS
GDC_stretchBits(
    IN   HGDC dest,
    IN   INT32 destX,
    IN   INT32 destY,
    IN   INT32 destWidth,
    IN   INT32 destHeight,
    IN   INT32 srcX,
    IN   INT32 srcY,
    IN   INT32 srcWidth,
    IN   INT32 srcHeight,
    IN   PVOID pData,
    IN   PGRAPH_BITMAPINFO pGBitmapInfo,
    IN   GRAPH_ROP3 rop );


#endif /* USE_GRAPH_CALL_TABLE */



#endif /* _CTXGRAPH_H_ */

