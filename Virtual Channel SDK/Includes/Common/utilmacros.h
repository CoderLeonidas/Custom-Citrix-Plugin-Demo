/***************************************************************************
*
*   utilmacros.h
*
*   This file contains various useful macro definitions.
*
*   These macros are common to all platforms and so MUST be completely
*   portable.
*
*   $Id$
*
*   Copyright 2005-2006 Citrix Systems, Inc.  All Rights Reserved.
*
****************************************************************************/

#ifndef _UTILMACROS_H_
#define _UTILMACROS_H_


#define CLEAR_STRING(string)                (string)[0] = '\0'
#define IS_EMPTY_STRING(string)             ((string)[0] == '\0')

#define ELEMENTS_IN_ARRAY(array)            (sizeof(array) / sizeof((array)[0]))

/* N.B. the argument to this macro MUST be a string literal, so that the
 *      sizeof operator gives the correct result (if the argument were a
 *      string pointer, sizeof would give the size of the pointer!) - so
 *      concatenate the argument with an empty string, which is syntactically
 *      legal only if that argument is indeed a literal!
 */
#define LITERAL_LENGTH(literal)             (sizeof("" literal) - 1)

/* ICA uses the Microsoft separator int file paths. */

#define ICA_PATH_SEPARATOR '\\'

#endif /* _UTILMACROS_H_ */
