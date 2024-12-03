/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 */

#pragma once

#include <GraphicsKit/Private/Private.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

void GKDrawLine(MLInteger cx, MLInteger cy, MLInteger cx1, MLInteger cy1, MLColor color);

void GKDrawPixel(MLInteger cx, MLInteger cy, MLColor color);

void GKDrawLinearGradient(const MLPoint& p_src, const MLPoint& p_dst, const MLColor& c_src, const MLColor& c_dst);

void GKDrawArc(MLInteger rx, MLInteger ry, MLReal rp, MLReal start_angle, MLReal end_angle, MLColor color);

void GKDrawLineEx(MLPoint& p_src, MLPoint& p_dst, MLColor& color);

void GKDrawRoundedRectangle(MLInteger x, MLInteger y, MLInteger width, MLInteger height, MLInteger radius, MLColor color);

///////////////////////////////////////////////////////////////////////////////////////////////////

template <MLInteger N>
MLArray<MLPoint, N> GKBezierCurve(const MLArray<MLPoint, N>& control_points, MLInteger resolution = 100U);

MLColor GKInterpolateColor(const MLColor& c1, const MLColor& c2, MLInteger t);

///////////////////////////////////////////////////////////////////////////////////////////////////
