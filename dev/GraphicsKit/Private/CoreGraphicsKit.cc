/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#pragma once

#include <GraphicsKit/Foundation.h>

/// @brief Process framebuffer array.
ML_EXTERN_C MLColor* kFBArray;

MLInteger GKCombination(MLInteger n, MLInteger k)
{
	if (k == 0 || k == n)
		return 1;
	
	return GKCombination(n - 1, k - 1) + GKCombination(n - 1, k);
}

template <MLInteger N>
MLArray<MLPoint, N> GKBezierCurve(const MLArray<MLPoint, N>& control_points, MLInteger resolution)
{
	MLArray<MLPoint, N> curve_points;

	for (MLInteger i = 0; i <= resolution; ++i)
	{
		MLReal	t	  = i / static_cast<MLReal>(resolution);
		MLPoint point = {0, 0};

		MLInteger n = N - 1;

		for (MLInteger j = 0; j <= n; ++j)
		{
			MLReal bernstein = GKCombination(n, j) * std::pow(1 - t, n - j) * std::pow(t, j);

			point.x += bernstein * control_points[j].x;
			point.y += bernstein * control_points[j].y;
		}

		curve_points[i] = point;
	}

	return curve_points;
}

MLColor GKInterpolateColor(const MLColor& c1, const MLColor& c2, MLReal t)
{
	return {
		(1 - t) * c1.r + t * c2.r,
		(1 - t) * c1.g + t * c2.g,
		(1 - t) * c1.b + t * c2.b};
}

void GKDrawLinearGradient(const MLPoint& p0, const MLPoint& p1, const MLColor& c0, const MLColor& c1)
{
	for (MLInteger x = p0.x; x <= p1.x; ++x)
	{
		MLReal t = (x - p0.x) / (p1.x - p0.x);

		MLColor color = GKInterpolateColor(c0, c1, t);
		GKDrawPixel(x, p0.y, color); // Implement `drawPixel` for your stack
	}
}

void GKDrawArc(MLReal cx, MLReal cy, MLReal r, MLReal start_angle, MLReal end_angle, MLColor color)
{
	const MLInteger resolution = 100;

	for (MLInteger i = 0; i <= resolution; ++i)
	{
		MLReal theta = start_angle + (end_angle - start_angle) * i / resolution;
		MLReal x	 = cx + r * cos(theta);
		MLReal y	 = cy + r * sin(theta);

		GKDrawPixel(x, y, color); // Implement `drawPixel`
	}
}

void GKDrawLine(MLPoint p1, MLPoint p2, MLColor color)
{
	// Calculate the differences in the x and y directions
	MLInteger dx = std::abs(p2.x - p1.x);
	MLInteger dy = std::abs(p2.y - p1.y);

	// Determine the direction of the steps (whether to increment or decrement)
	MLInteger sx = (p1.x < p2.x) ? 1 : -1;
	MLInteger sy = (p1.y < p2.y) ? 1 : -1;

	// Initial decision variable
	MLInteger err = dx - dy;

	while (YES)
	{
		// Draw the current pixel
		GKDrawPixel(p1.x, p1.y, color);

		// If we have reached the destination point, exit the loop
		if (p1.x == p2.x && p1.y == p2.y)
			break;

		// Calculate the error in both directions
		MLInteger e2 = err * 2;

		// Adjust the error term and update the coordinates accordingly
		if (e2 > -dy)
		{
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

void GKDrawRoundedRectangle(MLReal x, MLReal y, MLReal width, MLReal height, MLReal radius, MLColor color)
{
	// Top-left corner
	GKDrawArc(x + radius, y + radius, radius, kMathPI, 1.5 * kMathPI, color);
	// Top-right corner
	GKDrawArc(x + width - radius, y + radius, radius, 1.5 * kMathPI, 2 * kMathPI, color);
	// Bottom-right corner
	GKDrawArc(x + width - radius, y + height - radius, radius, 0, 0.5 * kMathPI, color);
	// Bottom-left corner
	GKDrawArc(x + radius, y + height - radius, radius, 0.5 * kMathPI, kMathPI, color);

	// Connect arcs with straight lines
	GKDrawLine(x + radius, y, x + width - radius, y, color);					// Top edge
	GKDrawLine(x + width, y + radius, x + width, y + height - radius, color);	// Right edge
	GKDrawLine(x + radius, y + height, x + width - radius, y + height, color); // Bottom edge
	GKDrawLine(x, y + radius, x, y + height - radius, color);					// Left edge
}

void GKDrawPixel(MLInteger cx, MLInteger cy, MLColor color)
{
	kFBArray[cx * cy] = color;
}