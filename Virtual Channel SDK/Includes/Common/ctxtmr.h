/*******************************************************************************
*
*   ctxtmr.h
*
*   Timer Abstraction Interface
*
*   Copyright 1998-2006 Citrix Systems, Inc.  All Rights Reserved.
*
******************************************************************************/

#ifndef __CTXTMR_H_
#define __CTXTMR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TMR_SUCCESS             0
#define TMR_OBJ_CREATE_FAILED   1
#define TMR_OBJ_BUSY            2

typedef enum TMR_STATE 
{
    TMR_STATE_ENABLED,
    TMR_STATE_DISABLED,
    TMR_STATE_FIRED,
    TMR_STATE_RUNNING,
    TMR_STATE_RUN_DISABLE
}
TMR_STATE;

/*******************************************************************************
 *
 *  Forward Declarations for opaque TMR structure
 *
 ******************************************************************************/
typedef struct _TMR  TMR;
typedef TMR FAR * PTMR;

/*******************************************************************************
 *
 *  Exported Functions
 *
 *    Tmr_create
 *    Tmr_setEnabled
 *    Tmr_setPeriod
 *    Tmr_destroy
 *
 ******************************************************************************/


/*******************************************************************************
 *
 *  Tmr_create
 *
 *    Creates a timer object and returns its handle.
 *
 ******************************************************************************/
VPSTATUS _VPAPI
Tmr_create( HND        hTC, 
            UINT32     uiPeriod,
            PVOID      pvSubscriber,
            PFNDELIVER pfnDeliver,
            PTMR     * phTimer );


void _VPAPI
Tmr_addTimersToRunLoop (void);
    
/*******************************************************************************
 *
 *  Tmr_setEnabled
 *
 *    Enables or disables a timer object.
 *
 ******************************************************************************/
VPSTATUS _VPAPI
Tmr_setEnabled( PTMR  hTimer,
                IBOOL fEnabled );


/*******************************************************************************
 *
 *  Tmr_setPeriod
 *
 *    Sets the timeout period for a timer.
 *
 ******************************************************************************/
VPSTATUS _VPAPI
Tmr_setPeriod( PTMR   hTimer,
               UINT32 uiPeriod );

/*******************************************************************************
 *
 *  Tmr_destroy
 *
 *    Destroys a timer object given its handle and sets the handle to NULL.
 *
 ******************************************************************************/
VPSTATUS _VPAPI
Tmr_destroy( PTMR *phTimer );

#ifdef __cplusplus
}
#endif


#endif /* __CTXTMR_H_ */

