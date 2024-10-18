/*
 * Created on Thu Jun 20 02:43:48 CEST 2024
 *
 * Copyright (c) 2024 ZKA Web Services Co
 */

#pragma once

#include <FoundationKit/Foundation.hxx>

struct MLCoreAnimationPoint;
struct MLCoreAnimationRect;

// DEFINE CORE TYPES

typedef float  CAReal;
typedef size_t CASizeT;
typedef bool   CABoolean;

// DEFINE CORE STRUCTS

/// @brief Point description struct.
typedef struct MLCoreAnimationPoint final
{
	CAReal X, Y;
} MLCoreAnimationPoint;

/// @brief Rectangle description struct.
typedef struct MLCoreAnimationRect final
{
	CAReal X1, Y1;
	CAReal X2, Y2;
} MLCoreAnimationRect;

// DEFINE CORE ALGORITHMS

enum
{
	eKineticAlgo,
	eFadeInAlgo,
	eFadeOutAlgo,
	eSmartSmoothAlgo,
};
