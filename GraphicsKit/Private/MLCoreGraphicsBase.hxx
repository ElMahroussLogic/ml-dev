/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#pragma once

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLString.hxx>
#include <cstring>

/// CORE MACROS ///

#define kRsrcProtocol "cg://"

/// CORE TYPES ///

typedef double CGReal;
typedef size_t CGSizeT;
typedef char   CGCharacter;
typedef bool   CGBoolean;

/// CORE STRUCTS ///

typedef struct MLCoreGraphicsPoint final
{
	CGReal X, Y;
} MLCoreGraphicsPoint;

typedef struct MLCoreGraphicsRect final
{
	CGReal X1, Y1;
	CGReal X2, Y2;
} MLCoreGraphicsRect;

/// CORE FUNCTIONS ///

/// @brief Fetch resource as a string.
/// @param input
/// @return the resource as a string.
inline const MLString r(const char* input)
{
    /// if input is invalid...
	if (!input)
	{
		MLString textNil(1);
		return textNil;
	}

	MLString textPath(strlen(input) + strlen(kRsrcProtocol));

	if (*input == 0)
	{
	   return textPath;
	}
	else
	{
	   textPath += kRsrcProtocol;
	   textPath += input;
	}

	return textPath;
}

extern const MLInteger cColorProfile;
