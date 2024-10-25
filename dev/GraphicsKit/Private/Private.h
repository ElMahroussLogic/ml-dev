/*
 * Created on Thu May 16 2024
 * Last Edited: Fri Oct 25 08:51:19 AM CEST 2024
 * Copyright (c) 2024 ZKA Web Services Co
 */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>
#include <FoundationKit/MLRect.h>

#include <filesystem>
#include <cstring>
#include <cmath>

/// CORE MACROS ///

#define kRsrcProtocol "gk://"

/// CORE TYPES ///

typedef MLReal	   GKReal;
typedef MLSizeType GKSizeType;
typedef MLInteger  GKInteger;
typedef MLChar	   GKCharacter;
typedef BOOL	   GKBoolean;

/// CORE STRUCTS ///

typedef struct GKPoint final
{
	GKReal X, Y;
} GKPoint;

typedef struct GKRect final
{
	GKReal X1, Y1;
	GKReal X2, Y2;
} GKRect;

/// CORE FUNCTIONS ///

/// @brief Fetch resource as a string.
/// @param input
/// @return the resource as a string.
inline const MLString gk_rsrc_path(const char* input)
{
	/// if input is invalid...
	if (!input)
	{
		MLString textNil(1);
		return textNil;
	}

	MLString textPath(strlen(input) + strlen(kRsrcProtocol));

	if (*input == 0 ||
		!std::filesystem::exists(input))
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
