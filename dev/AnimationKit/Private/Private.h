/*
 * Created on Thu Jun 20 02:43:48 CEST 2024
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 */

#pragma once

#include <FoundationKit/Foundation.h>

// DEFINE CORE TYPES

typedef MLReal	   CAReal;
typedef MLSizeType CASizeT;
typedef BOOL	   CABoolean;

// DEFINE CORE ALGORITHMS ENUMS.

enum
{
	kInvalidAlgorithm,
	kKineticAlgorithm,
	kFadeInAlgorithm,
	kFadeOutAlgorithm,
	kSmartAnimationAlgorithm,
	kAlgorithmCount,
};
