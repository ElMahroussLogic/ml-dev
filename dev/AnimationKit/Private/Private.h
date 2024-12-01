/*
 * Created on Thu Jun 20 02:43:48 CEST 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#pragma once

#include <FoundationKit/Foundation.h>

// DEFINE CORE TYPES

typedef MLReal	   CAReal;
typedef MLSizeType CASizeT;
typedef BOOL	   CABOOL;

// DEFINE CORE ALGORITHMS ENUMS.

enum
{
	kAnimationInvalidAlgorithm,
	kAnimationKineticAlgorithm,
	kAnimationFadeInAlgorithm,
	kAnimationFadeOutAlgorithm,
	kAnimationSmartAlgorithm,
	kAnimationAlgorithmCount,
};
