/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#pragma once

#include <GraphicsKit/Private/Private.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

void GKDrawArc(MLReal cx, MLReal cy, MLReal r, MLReal startAngle, MLReal endAngle, MLColor color);

void GKDrawLine(MLReal cx, MLReal cy, MLReal cx1, MLReal cy1, MLColor color);

void GKDrawPixel(MLReal cx, MLReal cy, MLColor color);

void GKDrawLinearGradient(const MLPoint& p0, const MLPoint& p1, const MLColor& c0, const MLColor& c1);

void GKDrawArc(MLReal cx, MLReal cy, MLReal r, MLReal start_angle, MLReal end_angle, MLColor color);

void GKDrawLine(MLPoint p1, MLPoint p2, MLColor color);

void GKDrawRoundedRectangle(MLReal x, MLReal y, MLReal width, MLReal height, MLReal radius, MLColor color);

///////////////////////////////////////////////////////////////////////////////////////////////////

template <MLInteger N>
MLArray<MLPoint, N> GKBezierCurve(const MLArray<MLPoint, N>& control_points, MLInteger resolution = 100U);

MLColor GKInterpolateColor(const MLColor& c1, const MLColor& c2, MLInteger t);

///////////////////////////////////////////////////////////////////////////////////////////////////
