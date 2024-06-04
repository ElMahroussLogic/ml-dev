/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#pragma once

#include <Foundation.hxx>
#include <MLFont.hxx>
#include <MLString.hxx>
#include <cstring>

#define kRsrcProtocol "cgx://"

typedef double CGReal;
typedef size_t CGSizeT;
typedef char   CGCharacter;

typedef struct MLCoreGraphicsPoint final
{
	CGReal X, Y;
} MLCoreGraphicsPoint;

/// @brief fallback URL in case the resource is not found.
/// @see r()
#define kRsrcFallbackUrl "fallback"

/// @brief URL for resources that are not found.
/// @see r()
#define kRsrcNilUrl "nil"

/// @brief Fetch resource as a string.
/// @param input 
/// @return the resource as a string.
inline const MLString r(const char* input)
{
	if (!input)
	{
		MLString text(strlen(input) + strlen(kRsrcProtocol));
		text += kRsrcProtocol;
		text += kRsrcFallbackUrl;

		return text;
	}

    MLString text(strlen(input) + strlen(kRsrcProtocol));
	text += kRsrcProtocol;
	text += input;

	if (*input == 0)
	{
		text += kRsrcNilUrl;
	}

	return text;
}
