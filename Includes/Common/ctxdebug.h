/******************************************************************************
*
*  CTXDEBUG.H
*
*     Header file for Logging and Tracing ASSERT and TRACE macros
*
*  Copyright © Citrix Systems, Inc.  All rights reserved.
*
*******************************************************************************/

#ifndef __CTXDEBUG_H__
#define __CTXDEBUG_H__

/*=============================================================================
 ==   ASSERT macro
 ============================================================================*/
#undef  ASSERT


// For C++ source files we want to record detailed signature information. For all other 
// source file types we'll stick to a more concise representation.
#ifdef __cplusplus
    #define PRETTY_FUNC __PRETTY_FUNCTION__
#else
    #define PRETTY_FUNC __FUNCTION__
#endif

#ifdef DEBUG
#define ASSERT(exp,rc) { \
   if (!(exp)) { \
      LogAssert( #exp, __FILE__, __LINE__, PRETTY_FUNC, rc ); \
   } \
}

#elif defined (macintosh) && defined (ASSERT_CODE_COVERAGE)
	/* Define the ASSERT macro on some macintosh versions even when DEBUG is not
	 * defined to enable checking for ASSERTs in a non-DEBUG build. Any ASSERT that
	 * catches a problem will end up calling the function Mac_AssertNotification, 
	 * where a breakpoint can be set. This would better fit into platfix.h, but
	 * many source files include ctxdebug.h later. */
	#define ASSERT(exp,rc) do {													\
		static bool calledBefore = false;											\
		if (! (exp)) Mac_AssertNotification (#exp, rc, &calledBefore);				\
	} while (0)

#ifdef __cplusplus
extern "C" {
#endif

#if __GNUC__ >= 4
	extern void Mac_AssertNotification (const char* expr, int rc, bool *pCalledBefore) __attribute__ ((noreturn));
#else
	extern void Mac_AssertNotification (const char* expr, int rc, bool *pCalledBefore);
#endif

#ifdef __cplusplus
}
#endif

#else
// Compile actual code to avoid analyzer warnings. LogAssertReturnCode is an inline function 
// doing nothing, so hopefully everything is optimized away. 
#define ASSERT(exp,rc) { if (! (exp)) LogAssertReturnCode (rc); }
#endif

#ifndef TRACING_ENABLED
#define TRACING_ENABLED 1
#endif

#if TRACING_ENABLED
#undef TRACE

//
// Trace Helper Macros (shouldn't be called directly)
//

#define __TRACE(func, class, class_str, feature, feature_str, format, ...)	\
	do { \
		if (LogShouldLog(class, feature)) {    \
			LogPrintf(__FILE__, __LINE__, func, class_str, feature_str, format, ##__VA_ARGS__); \
		} \
	} while (0)

#define __TRACE_ONCE(class, class_str, feature, feature_str, format, ...)	\
	const char *func##__LINE__ = PRETTY_FUNC;	\
	static dispatch_once_t onceToken##__LINE__;	\
	dispatch_once(&onceToken##__LINE__, ^{		\
		__TRACE(func##__LINE__, class, class_str, feature, feature_str, format, ##__VA_ARGS__); \
	})

#define __TRACEBUF(func, class, class_str, feature, feature_str, buffer, bytes) \
	do {	\
		if (LogShouldLog(class, feature)) {       \
			LogBuffer(__FILE__, __LINE__, func, class_str, feature_str, buffer, bytes); \
		}	\
	} while(0)

#define __TRACEBUF_ONCE(class, class_str, feature, feature_str, buffer, bytes) \
	const char *func##__LINE__ = PRETTY_FUNC;	\
	static dispatch_once_t onceToken##__LINE__;	\
	dispatch_once(&onceToken##__LINE__, ^{		\
		__TRACEBUF(func##__LINE__, class, class_str, feature, feature_str, buffer, bytes) \
	})

#ifdef __OBJC__
#define __TRACE_OBJC(func, class, class_str, feature, feature_str, format, ...) \
	do { \
		if (LogShouldLog(class, feature)) {			\
			LogPrintf_ObjC(__FILE__, __LINE__, func, class_str, feature_str, format, ##__VA_ARGS__);	\
	} \
	} while(0)

#define __TRACE_OBJC_ONCE(class, class_str, feature, feature_str, format, ...) \
	const char *func##__LINE__ = PRETTY_FUNC;	\
	static dispatch_once_t onceToken##__LINE__;	\
	dispatch_once(&onceToken##__LINE__, ^{		\
		__TRACE_OBJC(func##__LINE__, class, class_str, feature, feature_str, format, ##__VA_ARGS__); \
	})
#endif

//
// Debug and Release Trace Macros
//
#define TRACE(class, feature, format, ...) \
	__TRACE(PRETTY_FUNC, class, #class, feature, #feature, format, ##__VA_ARGS__)

#define TRACE_ONCE(class, feature, format, ...) \
	__TRACE_ONCE(class, #class, feature, #feature, format, ##__VA_ARGS__)

#define TRACEBUF(class, feature, buffer, bytes) \
	__TRACEBUF(PRETTY_FUNC, class, #class, feature, #feature, buffer, bytes)

#define TRACEBUF_ONCE(class, feature, buffer, bytes) \
	__TRACEBUF_ONCE(class, #class, feature, #feature, buffer, bytes)

#ifdef __OBJC__
#define TRACE_OBJC(class, feature, format, ...) \
	__TRACE_OBJC(PRETTY_FUNC, class, #class, feature, #feature, format, ##__VA_ARGS__)

#define TRACE_OBJC_ONCE(class, feature, format, ...) \
	__TRACE_OBJC_ONCE(class, #class, feature, #feature, format, ##__VA_ARGS__)
#endif

//
// Debug-only Trace Macros
//
#ifdef DEBUG

#define DTRACE(class, feature, format, ...)				__TRACE(PRETTY_FUNC, class, #class, feature, #feature, format, ##__VA_ARGS__)
#define DTRACE_ONCE(class, feature, format, ...)		__TRACE_ONCE(class, #class, feature, #feature, format, ##__VA_ARGS__)
#define DTRACEBUF(class, feature, buffer, bytes)		__TRACEBUF(PRETTY_FUNC, class, #class, feature, #feature, buffer, bytes)
#define DTRACEBUF_ONCE(class, feature, buffer, bytes)	__TRACEBUF_ONCE(class, #class, feature, #feature, buffer, bytes)
#ifdef __OBJC__
#define DTRACE_OBJC(class, feature, format, ...)		__TRACE_OBJC(PRETTY_FUNC, class, #class, feature, #feature, format, ##__VA_ARGS__)
#define DTRACE_OBJC_ONCE(class, feature, format, ...)	__TRACE_OBJC_ONCE(class, #class, feature, #feature, format, ##__VA_ARGS__)
#endif

#else	// DEBUG

#define DTRACE(class, feature, format, ...)				do {} while(0)
#define DTRACE_ONCE(class, feature, format, ...)		do {} while(0)
#define DTRACEBUF(class, feature, buffer, bytes)		do {} while(0)
#define DTRACEBUF_ONCE(class, feature, buffer, bytes)	do {} while(0)
#ifdef __OBJC__
#define DTRACE_OBJC(class, feature, format, ...)		do {} while(0)
#define DTRACE_OBJC_ONCE(class, feature, format, ...)   do {} while(0)
#endif

#endif	// DEBUG

#else	// TRACING_ENABLED
    
#define TRACE(class, feature, format, ...)				do {} while(0)
#define TRACE_ONCE(class, feature, format, ...)			do {} while(0)
#define TRACEBUF(class, feature, buffer, bytes)			do {} while(0)
#define TRACEBUF_ONCE(class, feature, buffer, bytes)	do {} while(0)
#ifdef __OBJC__
#define TRACE_OBJC(class, feature, format, ...)			do {} while(0)
#define TRACE_OBJC_ONCE(class, feature, format, ...)	do {} while(0)
#endif

#define DTRACE(class, feature, format, ...)				do {} while(0)
#define DTRACE_ONCE(class, feature, format, ...)		do {} while(0)
#define DTRACEBUF(class, feature, buffer, bytes)		do {} while(0)
#define DTRACEBUF_ONCE(class, feature, buffer, bytes)	do {} while(0)
#ifdef __OBJC__
#define DTRACE_OBJC(class, feature, format, ...)		do {} while(0)
#define DTRACE_OBJC_ONCE(class, feature, format, ...)   do {} while(0)
#endif

#endif  // TRACING_ENABLED 

#endif  // __CTXDEBUG_H__
