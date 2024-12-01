/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#pragma once

#include "FoundationKit/Macros.h"
#include <FoundationKit/MLArray.h>
#include <GraphicsKit/Private/Private.h>
#include <FoundationKit/MLPoint.h>
#include <GraphicsKit/GKContextInterface.h>

struct MLColor;
struct MLColorAlpha;

/// @brief Color data structure, consists of three MLIntegers representing RGB values.
struct MLColor final
{
	MLInteger r, g, b;
};

/// @brief Color data structure, consists of three MLIntegers representing RGB values.
/// @note This version adds the alpha value.
struct MLColorAlpha final
{
	MLInteger r, g, b, a;
};


void GKDrawArc(MLReal cx, MLReal cy, MLReal r, MLReal startAngle, MLReal endAngle, MLColor color);

void GKDrawLine(MLReal cx, MLReal cy, MLReal cx1, MLReal cy1, MLColor color);

void GKDrawPixel(MLReal cx, MLReal cy, MLColor color);

template <MLInteger N>
MLArray<MLPoint, N> GKBezierCurve(const MLArray<MLPoint, N>& control_points, MLInteger resolution = 100U);

MLColor GKInterpolateColor(const MLColor& c1, const MLColor& c2, MLInteger t);

void GKDrawLinearGradient(const MLPoint& p0, const MLPoint& p1, const MLColor& c0, const MLColor& c1);

void GKDrawArc(MLReal cx, MLReal cy, MLReal r, MLReal startAngle, MLReal endAngle, MLColor color);

void GKDrawLine(MLPoint p1, MLPoint p2, MLColor color);

void GKDrawRoundedRectangle(MLReal x, MLReal y, MLReal width, MLReal height, MLReal radius, MLColor color);