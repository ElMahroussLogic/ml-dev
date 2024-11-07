/* -------------------------------------------

	Copyright (C) 2024, EL Mahrouss Logic, all rights reserved.

------------------------------------------- */

#pragma once

#define ML_INLINE inline
#define ML_CONST  const
#define ML_STATIC static

#define ML_DEPRECATED __attribute__((deprecated))

#ifdef __x86_64__
#define ML_AMD64	1
#define ML_PLATFORM "AMD64"
#endif

#ifdef __aarch64__
#define ML_ARM64	1
#define ML_PLATFORM "ARM64"
#endif

#ifndef OBJC_BOOL_DEFINED
#define BOOL bool
#define YES	 true
#define NO	 false
#endif // ifndef OBJC_BOOL_DEFINED

#define ML_OBJECT : public MLObject

#define ML_UNUSED(X) ((void)(X))

#ifndef ML_PACKED
#if defined(__TOOLCHAINKIT__)
#define ML_PACKED __attribute__((packed))
#define ML_EXPORT __attribute__((libexport))
#define ML_IMPORT __attribute__((libimport))
#else
#define ML_PACKED
#define ML_EXPORT
#define ML_IMPORT
#endif
#endif // ifndef PACKED

#ifndef __cplusplus
#define ML_EXTERN_C extern
#else
#define ML_EXTERN_C extern "C"
#endif

typedef char				   MLChar;
typedef unsigned char		   MLUtf8Char;
typedef wchar_t				   MLUtf16Char;
typedef int					   MLInteger;
typedef long long int		   MLInteger64;
typedef unsigned char		   MLInteger8;
typedef unsigned int		   MLUnsignedInteger;
typedef unsigned long long int MLUnsignedInteger64;
typedef long long int		   MLLong;
typedef void*				   MLPointer;
typedef long long int		   MLSizeType;
typedef double				   MLReal;

/// @brief Exits thread with code.
/// @param exitCode it's exit code.
/// @param currentThread the current thread to exit.
/// @return void, no return arguments.
ML_IMPORT void MLExitThreadWithCode(MLInteger exitCode, MLPointer currentThread);

/// @brief Exits the current thread.
/// @param exitCode it's exit code.
/// @return void, no return arguments.
ML_IMPORT void MLExitWithCode(MLInteger exitCode);

/// @brief Get last exit code from any thread.
/// @return the exit code of the thread.
ML_IMPORT MLInteger MLGetExitCode(void);

/// @brief Writes to stdout using a custom formating.
/// @param format the format itself.
/// @param ... variable arguments.
/// @return void.
ML_IMPORT void MLLog(const MLChar* format, ...);

/// @brief Trigerred when an assertion fails.
/// @param expr the expression converted to string.
/// @param file the file.
ML_IMPORT void MLAssert(const MLChar* expr, const MLChar* file, const MLInteger line);

#define ML_MUST_PASS(X)                   \
	if (!(X))                             \
	{                                     \
		MLAssert(#X, __FILE__, __LINE__); \
	}

#define ML_COPY_DELETE(KLASS)                \
	KLASS& operator=(const KLASS&) = delete; \
	KLASS(const KLASS&)			   = delete;

#define ML_COPY_DEFAULT(KLASS)                \
	KLASS& operator=(const KLASS&) = default; \
	KLASS(const KLASS&)			   = default;

#define ML_MOVE_DELETE(KLASS)           \
	KLASS& operator=(KLASS&&) = delete; \
	KLASS(KLASS&&)			  = delete;

#define ML_MOVE_DEFAULT(KLASS)           \
	KLASS& operator=(KLASS&&) = default; \
	KLASS(KLASS&&)			  = default;