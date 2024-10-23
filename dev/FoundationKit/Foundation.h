/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#pragma once

#define ML_INLINE inline
#define ML_CONST  const
#define ML_STATIC static

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
#endif // ifndef __APPLE__

#define ML_OBJECT : public MLObject

#define ML_UNUSED(X) ((void)(X))

#ifndef ML_PACKED
#if defined(__NDK__)
#define ML_PACKED __attribute__((packed))
#define ML_EXPORT __attribute__((libexport))
#define ML_IMPORT __attribute__((libimport))
#else
#define ML_PACKED
#define ML_EXPORT
#define ML_IMPORT
#endif
#endif // !PACKED

#define ML_EXTERN extern

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
typedef unsigned int		   MLUnsignedInteger;
typedef unsigned long long int MLUnsignedInteger64;
typedef long long int		   MLLong;
typedef void*				   MLPointer;
typedef long long int		   MLSizeType;
typedef float				   MLReal;

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
/// @param
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

#ifndef __cplusplus
#error !!! This is not C++, please use C++. !!!
#else
class MLObject;
class MLString;

template <typename T, MLSizeType N>
class MLArray;

class MLMutableArray;
class MLJSONCoder;
class MLCoder;
class MLAlert;
class MLURL;
class MLXMLCoder;
class MLApplication;
class MLThread;
class MLProcess;
class MLSocket;
class MLAllocator;
class MLUUID;

class MLObject
{
public:
	explicit MLObject() = default;
	virtual ~MLObject() = default;

	MLObject& operator=(const MLObject&) = default;
	MLObject(const MLObject&)			 = default;

	virtual const MLString toString();

	virtual const void encode(MLCoder* output);
	virtual const void decode(MLCoder* output);
};

class MLCoder final ML_OBJECT
{
public:
	explicit MLCoder() = default;
	virtual ~MLCoder() = default;

	MLCoder& operator=(const MLCoder&) = default;
	MLCoder(const MLCoder&)			   = default;

	virtual MLObject* getResult()
	{
		return nullptr;
	}

	virtual MLCoder& encode(MLObject* obj)
	{
		return *this;
	}

	virtual MLCoder& decode(MLObject* obj)
	{
		return *this;
	}
};

#endif

#ifdef _WIN32
#include <Windows.h>
#define MLSleep Sleep
#else
#include <unistd.h>
#define MLSleep(X) sleep(X / 1000)
#endif

#define ML_ARRAY_LENGTH(ARR) (sizeof(ARR) / sizeof(ARR[0]))

/// @brief Launches an alert box from the API.
/// @param title title of dialog.
/// @param msg message of dialog.
/// @return which option was selected.
ML_EXTERN_C int MLAlertBox(const char* title, const char* msg, const char* link_provider = "about:blank");
