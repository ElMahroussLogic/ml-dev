/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 Amlal El Mahrouss B.V
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

#define kRsrcFallbackUrl "fallback"
#define kRsrcNilUrl "nil"

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