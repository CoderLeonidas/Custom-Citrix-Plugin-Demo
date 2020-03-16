/*************************************************************************
*
*  platcomm.h
*
*  Build platform specfic types based on macros specified for
*  a platform.
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
************************************************************************/

#ifndef _PLATCOMM_H_
#define _PLATCOMM_H_

/* VPSIZE defined  */

typedef struct _VPSIZE
{
    UINT32 uiWidth;
    UINT32 uiHeight;
    
} VPSIZE, * PVPSIZE ;

/* VPPOINT defined  */
typedef struct _VPPOINT
{
    INT32  iX;
    INT32  iY;
    
} VPPOINT, * PVPPOINT ;

/* VPRECT defined  */
typedef struct _VPRECT
{
    INT32  iX;
    INT32  iY;
    UINT32 uiWidth;
    UINT32 uiHeight;
} VPRECT, * PVPRECT ;


/*
 *  General Virtual Platform Types
 */
typedef PVOID                 HND;
typedef HND                   * PHND;
typedef UINT32                VPSTATUS;

/*
 *  Function types
 */
typedef UINT32 (* PLIBPROCEDURE)(void);
typedef PLIBPROCEDURE *PPLIBPROCEDURE;
typedef void (* PFNDELIVER)( void* pSubscriber, void* pInfo);

/*
 *  Miscellaneous Macros
 */


#define MSB(x)     ((UINT8) (((x) >> 8) & 0x00ff))
#define LSB(x)     ((UINT8) ((x) & 0x00ff))

/*
 * STATIC is used for embeded drivers.  STATIC should not be defined
 * by default.  Embeded drivers define STATIC as static to keep their
 * function names within the drivers own scope.
 */
#ifndef STATIC
#define STATIC
#endif

/*
 *  Define CONST if it is not defined.
 */
#ifndef CONST
#define CONST  const
#endif

/*
 *  Sometimes we want to implement an interface, but we end up not using
 *  one or more of the parameters.  This macro will get rid of the compiler
 *  warnings with no ill effects.
 */
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)   (P)
#endif

/*
 * The CODECOVERAGE macro is a useful tool to check code coverage during development. To see how to
 * use it, check the Macintosh version of platfix.h
 */
#define CODECOVERAGE(covered, ident) do { } while (0)

/*
 * The CONNECTIONFAILURE macro is a useful tool to check for situations that will eventually lead
 * to a connection failure. To see how to use it, check the Macintosh version of platfix.h
 */
#define CONNECTIONFAILURE(covered, ident) do { } while (0)

#endif /* _PLATCOMM_H_ */
