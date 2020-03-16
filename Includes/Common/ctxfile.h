/*************************************************************************
*
*   ctxfile.h
*
*   File I/O Abstraction header file
*
*   Copyright 1999-2006 Citrix Systems, Inc.  All Rights Reserved.
*
*************************************************************************/
#ifndef __CTXFILE_H__
#define __CTXFILE_H__

#include <ctxpath.h>

#ifdef _cplusplus
extern "C" {
#endif /* #ifdef _cplusplus */

/*
 * File open disposition
 */
#define FILE_CREATE_NEW          0x0001
#define FILE_CREATE_ALWAYS       0x0002
#define FILE_OPEN_EXISTING       0x0004
#define FILE_OPEN_ALWAYS         0x0008

/*
 * File open access mode
 */
#define FILE_READ_ONLY      0x0001	/* allows only read operations on a file */
#define FILE_WRITE_ONLY     0x0002	/* allows only write operations on the file */
#define FILE_APPEND			0x0004	/* allows read-write; but writes are only to the end */
#define FILE_READ_WRITE     0x0008	/* allows read write */
 	

/*
 * File pointer : start, end or current
 */
#define FILE_SEEK_BEGIN      0x0001 /* SEEK_START */
#define FILE_SEEK_CURRENT    0x0002 /* SEEK_CUR */
#define FILE_SEEK_END        0x0004 /* SEEK_END */

/* File Attributes: */

#define FILE_ATTRIB_READONLY 0x0001
#define FILE_ATTRIB_ARCHIVE  0x0002
#define FILE_ATTRIB_HIDDEN   0x0004
/* TODO: Add more attribute definitions. */

/*
 *  FILE IO Error Codes
 */
#define FILEIO_STATUS_SUCCESS           0

#define FILEIO_ERROR_OPEN               1
#define FILEIO_ERROR_OPENEXCLUSIVE      2
#define FILEIO_ERROR_READ               3
#define FILEIO_ERROR_READEOF            19
#define FILEIO_ERROR_WRITE              4
#define FILEIO_ERROR_SEEK               5
#define FILEIO_ERROR_DELETE             6
#define FILEIO_ERROR_TRUNCATE           7
#define FILEIO_ERROR_SETDATE            8
#define FILEIO_ERROR_GETDATE            9
#define FILEIO_ERROR_SETATTRIBUTES      10
#define FILEIO_ERROR_GETATTRIBUTES      11 
#define FILEIO_ERROR_FINDFIRST          12
#define FILEIO_ERROR_FINDNEXT           13
#define FILEIO_ERROR_FINDCLOSE          14
#define FILEIO_ERROR_CLOSE              15
#define FILEIO_ERROR_GETSIZE            16
#define FILEIO_ERROR_MKDIRECTORY        17
#define FILEIO_ERROR_RMDIRECTORY        18 
#define FILEIO_ERROR_GETFREEDISKSPACE   20
#define FILEIO_ERROR_ALREADYEXISTS      21
#define FILEIO_ERROR_NOTFOUND           22



/* File Find Data Structure: */
typedef struct _FILEIO_FIND_DATA {
    UINT32    fileSize;
    UINT16    fileAttributes;

    /* Note: if one of these fields cannot be supported then set it to the value of the other */
    /*       if both of them cannot be supported then set them both to zero */

    UINT32    updateTime;   /* time last updated in seconds since 1st Jan 1980 */
    UINT32    accessTime;   /* time last read in seconds since 1st Jan 1980 */

    PATH_COMP fileName;    

} FILEIO_FIND_DATA, FAR * PFILEIO_FIND_DATA; 
 
typedef PFILEIO_FIND_DATA   FAR * PPFILEIO_FIND_DATA;


typedef enum __FILETYPE 
{
    FILE_TYPE_DATA = 0,
    FILE_TYPE_EXECUTBLE
} 
FILETYPE;


VPSTATUS _VPAPI File_open               (PATH_NAME path, UINT16 accessMode, UINT16 disposition, UINT32 fileType, OUT PHND phFile);
VPSTATUS _VPAPI File_openExclusive      (PATH_NAME path, UINT16 accessMode, UINT16 disposition, UINT32 fileType, OUT PHND phFile);
VPSTATUS _VPAPI File_read               (IN HND hFile, UINT32 bytesToRead, PUINT32 pBytesRead, PVOID pBuffer);
VPSTATUS _VPAPI File_write              (IN HND hFile, UINT32 bytesToWrite, PUINT32 pBytesWritten, PVOID pBuffer);
VPSTATUS _VPAPI File_seek               (HND hFile, INT32 offset, UINT16 origin);
VPSTATUS _VPAPI File_delete             (PATH_NAME  path);
VPSTATUS _VPAPI File_truncate           (HND hFile, INT32 numberOfBytes);
VPSTATUS _VPAPI File_setDate            (HND hFile); /* TBD */
VPSTATUS _VPAPI File_getDate            (HND hFile); /* TBD */
VPSTATUS _VPAPI File_setAttributes      (HND hFile); /* TBD */
VPSTATUS _VPAPI File_getAttributes      (HND hFile); /* TBD */
VPSTATUS _VPAPI File_findFirst          (PATH_NAME FileName, PHND phSearchHandle, PFILEIO_FIND_DATA pFindData);
VPSTATUS _VPAPI File_findNext           (HND hSearchHandle, PFILEIO_FIND_DATA pFindData);
VPSTATUS _VPAPI File_findClose          (PHND phSearchHandle);
VPSTATUS _VPAPI File_close              (PHND phFile);
VPSTATUS _VPAPI File_getSize            (HND hFile, PUINT32 pSize);
VPSTATUS _VPAPI File_makeDirectory      (PATH_NAME path);
VPSTATUS _VPAPI File_removeDirectory    (PATH_NAME path);
VPSTATUS _VPAPI File_getFreeDiskSpace   (PATH_NAME path, PUINT32 pHighFreeSpace, PUINT32 pLowFreeSpace);

#ifdef _cplusplus
}
#endif /* #ifdef _cplusplus */

#endif  /* #ifndef __CTXFILE_H__ */

