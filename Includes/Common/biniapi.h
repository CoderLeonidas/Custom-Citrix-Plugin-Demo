/******************************************************************************
*
*   BINIAPI.H
*
*   Header file for Buffered INI APIs.
*
*	Copyright © Citrix Systems, Inc.  All rights reserved.
*
*******************************************************************************/

#ifndef __BINIAPI_H__
#define __BINIAPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================
==   API entry points
=============================================================================*/

//
// The primary function to examine a single line from an INI file. It assumes that the single line
// is stored as a C string in a buffer that can be modified. If the line contains a section header
// then *section will point to the section header as a C string within the buffer, otherwise 
// *section is set to NULL. If the line contains a key = value pair then *key and *value point to 
// the key and the value as C strings within the buffer, otherwise both are NULL. 
//
void ParseIniFileLine (char* buffer, char* *section, char* *key, char* *value); 

//
// A helper function to parse a comma separated list of items. It assumes that the single line is 
// stored as a C string in a buffer that can be modified. The string is split into items separated
// by commas, then whitespace before and after each item is removed, empty items are discarded. The
// items are stored as a list of C strings, followed by an empty string. To iterate through the list,
// use for (char* p = list; *p != 0; p += strlen (p) + 1) ... The buffer should be one byte larger
// than the unparsed input.
//
void ParseIniFileCommaSeparatedList (char* list);


//
// Data structure holding one section of an ini file. Multiple sections can form a linked list. 
// The data format is private except for next, sectionName, and sectionSize. This data structure
// is used to hold the configuration data, combined from the protocol file ("module), the config
// file ("config") and the ica file coming from the server. It is also used to hold the parsed
// data from a single file. 
//
typedef struct _iniFileSection
{
	struct _iniFileSection *next;	// Pointer to next INI section or NULL
	const char*	sectionName;		// Section name allocated with malloc
	size_t	sectionSize;			// Size of section data in bytes (0 means no section data).

// Private data, should not be read outside inifile.c
	char *	configInfo;				// Configuration as list of strings in one buffer, followed by empty string. */
	size_t	configInfoBufSize;		/* Size of the available buffer */
	
} INIFILESECTION;

#ifdef DEBUG
	GLOBAL void IniSectionTrace (INIFILESECTION *fs);
#else
	#define IniSectionTrace(fs) ((void) 0)
#endif /* DEBUG */



//
// Create an empty ini section. sectionName will be duplicated; may be NULL. Duplicate an ini section.
//
INIFILESECTION *CreateEmptyIniSection (const char* sectionName);
extern INIFILESECTION* IniSectionCopy (INIFILESECTION *srcSection);

//
// Change the section name. sectionName will be duplicated, may be NULL. 
//
void IniSectionSetName (INIFILESECTION* fs, const char* sectionName);

//
// Append a string, or key = value to an inisection. Total length must be < MAX_INI_LINE or
// nothing will happen. 
//
void IniSectionAppendString (INIFILESECTION* fs, const char* string);
void IniSectionAppendKeyValue (INIFILESECTION* fs, const char* key, const char* value);

//
// Free an ini section, or a linked list of ini sections. 
//
void IniSectionFree (INIFILESECTION *fs);
void IniSectionFreeList (INIFILESECTION *fs);

//
// Delete a key from a section, if it exists. Add a key = value pair to a section, replacing an
// existing key if present. 
//
void IniSectionDeleteKey (INIFILESECTION *fs, char* key);
void IniSectionSetKeyValue (INIFILESECTION *fs, char* key, const char * value);

//
// Load one ini file section from a file, optionally giving an error message if the section is not
// present. Load all ini file sections from a file, either making an exact copy (for editing), or
// keeping only key=value entries, with all unnecessary white space removed. 
//
INIFILESECTION *LoadINIFileSection(char *filename, char *reqSection, IBOOL mustWork);
INIFILESECTION *LoadAllINIFileSections (char *filename, bool exact);


//
// Helper functions for adding / removing / changing sections in a file, used for updating to
// newer versions. 
//
IBOOL WriteSectionsToIniFile(char *path, INIFILESECTION ** section, IU16 numSections);
IBOOL DeleteSectionofIniFile(char *path, char *sectionName);





//
// Data structure for an iterator through a section of an inifile.
//
typedef struct
{
	INIFILESECTION* section;		// Section that is iterated

	char	buffer [MAX_INI_LINE_UTF8];	// Buffer to hold key and value
	char*	line;					// Pointer to text of current line when iterating
	char*	key;					// Key of current line when iterating
	char*	value;					// Value of current line when iterating
} INIFILESECTIONITERATOR;

//
// Iterator through an inifile section. The iterator is started by calling IniSectionIteratorStart. 
// After each call to IniSectionIteratorNext returning true, iter.line contains a pointer to a
// complete line of the section, key and value contain a pointer to the key and the value part. 
//
void IniSectionIteratorStart (INIFILESECTIONITERATOR* iter, INIFILESECTION* fs);
bool IniSectionIteratorNext (INIFILESECTIONITERATOR* iter);

//
// IniSectionIteratorFind starts an iterator and iterates until searchKey is found or all the section
// has been iterated over. 
// 
bool IniSectionIteratorFind (INIFILESECTIONITERATOR* iter, INIFILESECTION* fs, const char* searchKey);

//
// Helper functions, only used for manipulating module/config to update them, and for reading
// the debug.ini file. 
//
int bGetPrivateProfileString (INIFILESECTION* pSection, const char* pKey, const char* sDefault, char* pBuffer, int bufferSize);
int bGetPrivateProfileInt (INIFILESECTION* pSection, const char* pKey, int iDefault);
IBOOL bGetPrivateProfileBool( INIFILESECTION* pSection, const char* pKey, IBOOL bDefault);

#ifdef __cplusplus
}
#endif

#endif /* __BINIAPI_H__ */
