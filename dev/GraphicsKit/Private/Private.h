/*
 * Created on Thu May 16 2024
 * Last Edited: Fri Oct 25 08:51:19 AM CEST 2024
 * Copyright (c) 2024 EL Mahrouss Logic
 */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>
#include <FoundationKit/MLRect.h>

#include <filesystem>
#include <cstring>
#include <cmath>

/// CORE MACROS ///

#define kMathPI 3.14159265358979323846
#define kRsrcProtocol "gk://"

/// CORE TYPES ///

typedef MLReal	   GKReal;
typedef MLSizeType GKSizeType;
typedef MLInteger  GKInteger;
typedef MLChar	   GKCharacter;
typedef BOOL	   GKBoolean;

/// CORE FUNCTIONS ///

/// @brief Fetch resource as a string.
/// @param input resource path.
/// @return the resource as a string.
inline const MLString gk_rsrc_path(const MLChar* input)
{
	MLString textNil(1);

	/// if input is invalid...
	if (!input)
	{
		return textNil;
	}

	MLString textPath(strlen(input) + strlen(kRsrcProtocol));

	if (*input == 0 ||
		!std::filesystem::exists(input))
	{
		return textNil;
	}

	textPath += kRsrcProtocol;
	textPath += input;

	return textPath;
}

extern const MLInteger cColorProfile;
