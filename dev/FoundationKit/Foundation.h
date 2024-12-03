/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Macros.h>

#ifndef __cplusplus
#error !!! This is not C++ please use standard C++ !!!
#else

#define kMathPI (3.14159265358979323846)
#define kMathEuler (2.718281828459045235360287471352)

class MLObject;
class MLString;

template <typename T, MLSizeType N>
class MLArray;

class MLMutableArray;
class MLJSONCoder;
class MLCoder;
class MLAlert;
class MLURL;
class MLXMLNode;
class MLApplication;
class MLThread;
class MLProcess;
class MLSocket;
class MLAllocator;
class MLUUID;
class MLXMLCoder;
class MLRect;
class MLPoint;

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
		return mContainedObject;
	}

	virtual MLCoder& encode(MLObject* obj)
	{
		mContainedObject = obj;
		return *this;
	}

	virtual MLCoder& decode(MLObject* obj)
	{
		mContainedObject = obj;
		return *this;
	}

protected:
	MLObject* mContainedObject{nullptr};
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
