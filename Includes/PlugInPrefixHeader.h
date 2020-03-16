/*****************************************************************************
*
*	File:	PlugInPrefixHeader.h
*
*	Description: Prefix file for building Virtual Channel PlugIns for MacOS X.
*
*	Copyright 2006-2009 Citrix Systems, Inc. All rights reserved.
* 
****************************************************************************/

// macintosh is defined and will be defined as an empty macro on all Macintosh builds, including
// MacOS 9, Codewarrior based, XCode based and any future builds. It must not be defined on any 
// builds that are not maintained by the Macintosh client team.
#define macintosh


// XCODE_BUILD is defined with a value of 1 if and only if "macintosh" is defined and XCode is
// used for development. It must not be defined on any builds that are not maintained by the
// Macintosh client team, and must only be defined on clients that use XCode for development.
#define XCODE_BUILD 1


// When building using XCode, exactly one of __ppc__ __i386__ __arm__ or the 64 bit options __ppc64__
// and __x86_64__ will be defined by the compiler, so we can define things dependent on these. 
// Exactly one of XCODE_INTEL, XCODE_POWERPC and XCODE_ARM will be defined to 1, the others will
// be undefined, depending on whether we are compiling for PowerPC (32 or 64 bit), Intel (32 or 64
// bit) or Arm (always 32 bit). Exactly one of XCODE_32BIT and XCODE_64BIT will be defined to 1, 
// the other will be undefined, depending on whether we are compiling for a 32 bit processor
// (PowerPC, Intel or Arm) or for a 64 bit processor (PowerPC or Arm).
#undef XCODE_POWERPC
#undef XCODE_INTEL
#undef XCODE_ARM

#undef XCODE_32BIT
#undef XCODE_64BIT

#if defined(__ppc__) || defined(__ppc64__)
	#define XCODE_POWERPC	1
#elif defined(__i386__) || defined(__x86_64__)
	#define XCODE_INTEL		1
#elif defined(__arm__)
	#define XCODE_ARM		1
#else
	#error unrecognized architecture
#endif /* __ppc__ or __i386__ or __ppc64__ or __x86_64__ or __arm__ */

#if defined(__ppc__) || defined(__i386__) || defined(__arm__)
	#define XCODE_32BIT		1
#elif defined(__ppc64__) || defined(__x86_64__)
	#define XCODE_64BIT	1
#else
	#error unrecognized architecture
#endif /* __ppc__ or __i386__ or __ppc64__ or __x86_64__ or __arm__ */


// Exactly one of the macros XCODE_SDK_CARBON, XCODE_SDK_COCOA and XCODE_SDK_UIKIT should be 
// defined as 1, the others should be undefined. They will be defined in a configuration file.
#if XCODE_SDK_CARBON == 1 && ! defined (XCODE_SDK_COCOA) && ! defined (XCODE_SDK_UIKIT)
	// Building for a MacOS X environment using the Carbon framework
#elif XCODE_SDK_COCOA == 1 && ! defined (XCODE_SDK_CARBON) && ! defined (XCODE_SDK_UIKIT)
	// Building for a MacOS X environment using the Cocoa framework
#elif XCODE_SDK_UIKIT == 1 && ! defined (XCODE_SDK_COCOA) && ! defined (XCODE_SDK_CARBON)
	// Building for a MacOS X environment using the UIKit framework
#else
	#error XCODE_SDK_CARBON, XCODE_SDK_COCOA or XCODE_SDK_UIKIT not properly defined.
#endif


// The caller may define at most one of PROD and DEBUG. If none is defined then 
// by default PROD will be defined. 
#ifdef DEBUG
	#ifdef PROD
		#error Both DEBUG and PROD are defined
	#endif
	#undef DEBUG
	#define DEBUG	1
#else
	#undef PROD
	#define PROD	1
#endif


// Two macros to check whether a function is available in this version of MacOS X. v is a version
// number, like MAC_OS_X_VERSION_10_4, where the function is believed to be available, and f is
// the name of the function. COMPILETIME_VERSION_CHECK(v,f) is true if we are using the SDK where
// the function is believed to be available; if the result is 0 the compiler won't even know the
// name of the function. RUNTIME_VERSION_CHECK(v,f) will return true if the function is actually
// available; this macro must only be used if COMPILETIME_VERSION_CHECK returned 1.
#define COMPILETIME_VERSION_CHECK(v,f)	(MAC_OS_X_VERSION_MAX_ALLOWED >= (v))
#define RUNTIME_VERSION_CHECK(v,f)		(MAC_OS_X_VERSION_MIN_REQUIRED >= (v) || &f != NULL)

// This macro makes the Carbon assertion macros compatible with the ASSERT macro used in our source
// code.
#define DEBUG_ASSERT_MESSAGE(componentNameString, assertionString, exceptionLabelString,		\
							 errorString, fileName, lineNumber, value)							\
	ASSERT (! assertionString, TRUE)

// This macro tells all code whether pointers need to be correctly aligned. On PowerPC and Intel
// processors, unaligned reads and writes are just a tiny fraction slower than aligned operations,
// so adding code to work around the problem would just slow things down. On an ARM processor, 
// unaligned reads and writes are signficantly slower; measurements showed that on an iPod Touch,
// each unaligned read or write takes about four microseconds or many hundred instructions. 
#if XCODE_ARM
	#define ALIGNMENT_REQUIRED 1
#else
	#undef ALIGNMENT_REQUIRED
#endif

// We always want CoreFoundation.h and AvailabilityMacros.h. The macro DOMAIN used in some Citrix 
// source files clashes with math.h.
#include <CoreFoundation/CoreFoundation.h>
#include <AvailabilityMacros.h>
#undef DOMAIN		/* clashes with math.h */

#ifdef __OBJC__
	// When compiling Objective-C source files, we always want to include the suitable Objective-C
	// header files, either UIKit.h or Cocoa.h.
	#if XCODE_SDK_UIKIT
		#import <Foundation/Foundation.h>
		#import <UIKit/UIKit.h>
	#else
		#import <Cocoa/Cocoa.h>
	#endif
#endif

