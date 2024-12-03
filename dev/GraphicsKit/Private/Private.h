/*
 * Created on Thu May 16 2024
 * Last Edited: Fri Oct 25 08:51:19 AM CEST 2024
 * Copyright (c) 2024 Amlal EL Mahrouss
 */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>
#include <FoundationKit/MLRect.h>
#include <FoundationKit/MLArray.h>
#include <FoundationKit/MLPoint.h>

typedef MLReal	   GKReal;
typedef MLSizeType GKSizeType;
typedef MLInteger  GKInteger;
typedef MLChar	   GKChar;
typedef BOOL	   GKBOOL;

ML_EXTERN_C const MLInteger kColorProfile;

struct MLColor;
struct MLColorAlpha;

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Color data structure, consists of three MLIntegers representing RGB values.
///////////////////////////////////////////////////////////////////////////////////////////////////

struct MLColor final
{
	MLInteger r, g, b, a;
};

enum
{
	kColorProfileSRGB,
	kColorProfileRGBA,
	kColorProfileRGB,
};

static_assert(sizeof(MLReal) == 8, "GK: MLReal type isn't a 64-bit IEEE float.");

/// @brief Process framebuffer array.
ML_EXTERN_C MLColor* kWindowServerFB;
