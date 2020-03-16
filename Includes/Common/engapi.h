/***************************************************************************
*
*  ENGAPI.H
*
*  This module contains definitions for types and prototypes used by
*  functions related to the engine.
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
****************************************************************************/

#ifndef _ENGAPI_H_
#define _ENGAPI_H_

#include <engtypes.h>
#include <wengine.h>

typedef struct _ICAENG ICAENG, *PICAENG;


#ifdef __cplusplus
extern "C" {
#endif

int ICAEngLoad (void);
int ICAEngUnload (void);

void ICAEng_ResetToInitialState (void);

int ICAEngUnloadDrivers (PICAENG pICAEng);
int ICAEngOpen (PICAENG_OPENDATA pIcaEngOpenData, PICAENG *ppICAEng);
int ICAEngClose (PICAENG pICAEng);
int ICAEngLoadWd (PICAENG pICAEng, char* moduleName);
int ICAEngLoadPd (PICAENG pICAEng, char* moduleName);
int ICAEngLoadVd (PICAENG pICAEng, char* moduleName);

int ICAEngGetInfo (PICAENG pICAEng, WFEINFOCLASS InfoClass, void* pData, unsigned int cbData);
int ICAEngSetInfo (PICAENG pICAEng, WFEINFOCLASS InfoClass, void* pData, unsigned int cbData);
int ICAEngInitSession (PICAENG pICAEng, PICAENG_INITSESSIONDATA pData);
int ICAEngConnect (PICAENG pICAEng);
int ICAEngDisconnect (PICAENG pICAEng);
int ICAEngPoll (PICAENG pICAEng);
int ICAEngMessageLoop (PICAENG pICAEng);

INT32 FakeUIStatusMsg (PICAENG hICAEng, INT32 iMessage); 
void display_ICA_status(const char *string, int code);

#ifdef __cplusplus
}
#endif


#endif /* _ENGAPI_H_ */
