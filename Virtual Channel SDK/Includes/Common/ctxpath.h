/***************************************************************************  
*  
*  CTXPATH.H  
*  
*  This module contains the path abstraction.  
*  
*  The path abstraction considers every drive letter, directory, and  
*  file name has a component.  Every component is a separated by a  
*  special character as defined by the platform.  A path name consists  
*  as a string of these components.  However, the user of a path name  
*  does not access the contents of the path directly.  
*  
*  It is recommended that the path name be stored in a format  
*  matching the platform representation.  However, this is not  
*  required.  
*  
*  
*  INTERESTING ISSUES:  
*  Issue 1) There is an interesting case where a relative path name is used with  
*  a drive specifier.  In this case a seperator is missing between  
*  the drive and relative path?????  What should we do?????  
*  
*  Solving this issue can mean, special logic in interpreting  
*  path names to recognize other separator characters or the  
*  abstraction may have to treat drives separate from components.  
*  
*  Issue 2) wild card characters (currently only accepted in the findFirstPath()  
*  interface have problems with being platform independent.  
*  
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*  
****************************************************************************/  
#ifndef _CTXPATH_H_  
#define _CTXPATH_H_  

#include <citrix.h>

#ifdef _cplusplus
extern "C" {
#endif /* #ifdef _cplusplus */  


/*  
 *  PATH_NAME represents a full path path name that may be relative  
 *  to the current directory or current drive or it may be an absolute  
 *  path name.  The representation of the path is platform specific.  
 */  
typedef char PATH_NAME[PATH_MAX_SIZE];  

/*  
 * PATH_COMP is an individual component within a path name  
 * (e.g. file name, directory name, drive name/letter)  
 */  
typedef char PATH_COMP[PATH_MAX_SIZE];  

/*
 * Path Abstraction Error Codes
 */
#define PATH_STATUS_SUCCESS          0
#define PATH_ERROR_PATH_TOO_LONG     1 

/*
 * Error codes below need to be replaced
 */
#define PATH_APPEND_ERROR 8
#define PATH_COPY_ERROR 2
#define PATH_EXTRACT_DOS_ERROR 3
#define PATH_EXTRACT_NATIVE_ERROR 4
#define PATH_INIT_FROM_NATIVE_ERROR 5
#define PATH_INIT_FROM_DOS_ERROR 6
#define PATH_EXTRACT_COMPONENT_ERROR 7


#define LONG_PATH_NAME 1
#define SHORT_PATH_NAME 2


/*  
 *  Path_initFromNative  
 *  
 *  This interface initializes a path with a string containing  
 *  the systems native representation.  A native representation  
 *  may be provided by a configuration value or UI component.  
 */  
VPSTATUS _VPAPI Path_initFromNative(PATH_NAME path, size_t pathSize, char* pNativePath);

/*  
 *  Path_initFromDOS  
 *  
 *  This interface initializes a path with a string containing  
 *  a DOS representation of a path name.  A DOS representation  
 *  may be provided by a server message in CDM.  
 */  
VPSTATUS _VPAPI Path_initFromDos(PATH_NAME path, char* pDosPath);  

/*  
 *  This interface extracts the native path name suitable for  
 *  display or use in a platform specific OS call.  
 */  
VPSTATUS _VPAPI Path_extractNative(PATH_NAME path, char* pNativePath, size_t nativePathSize);

/*  
 *  Path_copy  
 *  
 *  This interface copies a specified path to a new path variable  
 */  
VPSTATUS _VPAPI Path_copy(PATH_NAME path, size_t pathSize, PATH_NAME pSrcPath);

/*  
 *  Path_truncate  
 *  
 *  This interface truncates the path name by the specified levels.  
 *  The specified levels begins by truncating the file at the end  
 *  and then each directory level from there to the root.  
 */  
VPSTATUS _VPAPI Path_truncate(PATH_NAME path, size_t pathSize, UINT count);

/*  
 *  Path_append  
 *  
 *  This interface appends the given component to the path name.  
 *  The component can be a drive, directory or file name  
 */  
VPSTATUS _VPAPI Path_append(PATH_NAME path, size_t pathSize, PATH_COMP Comp);

/* 
 *  Path_extractComponent  
 *  
 *  This function extracts the specified component.  If the count  
 *  is positive it extracts the given component starting at the root.  
 *  If it is negative, it extracts the given component relative to  
 *  the end (e.g.  -1 extract last component, 2 extracts the second  
 *  component).  
 */  
VPSTATUS _VPAPI Path_extractComponent(PATH_NAME path, INT count, PATH_COMP Comp, size_t CompSize);

/*  
 *  Path_componentCount  
 *  
 *  This function returns the number of components in a path name  
 */  
VPSTATUS _VPAPI Path_componentCount(PATH_NAME path, PUINT pCount);  

/*  
 *  Path_combine
 *  
 *  This interface combines two path names by appending the
 *  second path to the first.  If the first path is not empty,
 *  the drive or begining (absolute) path separator are stripped.
 */  
VPSTATUS _VPAPI Path_combine(PATH_NAME path, size_t pathSize, PATH_NAME path2);

#ifdef _cplusplus
}
#endif /* #ifdef _cplusplus */
  

#endif /* _CTXPATH_H_ */  
  
  
