/*
 * Created on Thu May 16 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#include <GraphicsKit/Foundation.h>
#include <cmath>

// ================================================ //
/// @brief Combination algorithm for Bezier Curves.
// ================================================ //
MLInteger GKCombination(MLInteger n, MLInteger k)
{
	if (k == 0 || k == n)
		return 1;
	
	return GKCombination(n - 1, k - 1) + GKCombination(n - 1, k);
}

// ================================================ //
/// @brief Implementation of the Bezier Curve algorithm.
/// @param controls_points points as an array.
/// @param resolution resolution of bezier curve.
// ================================================ //
template <MLInteger N>
MLArray<MLPoint, N> GKBezierCurve(const MLArray<MLPoint, N>& control_points, MLInteger resolution)
{
	MLArray<MLPoint, N> curve_points;

	for (MLInteger i = 0; i <= resolution; ++i)
	{
		MLInteger	t	  = i / static_cast<MLInteger>(resolution);
		MLPoint point = {0, 0};

		MLInteger n = N - 1;

		for (MLInteger j = 0; j <= n; ++j)
		{
			MLInteger bernstein = GKCombination(n, j) * std::pow(1 - t, n - j) * std::pow(t, j);

			point.x += bernstein * control_points[j].x;
			point.y += bernstein * control_points[j].y;
		}

		curve_points[i] = point;
	}

	return curve_points;
}

// ================================================ //
/// @brief Implementation of color interpolation.
/// @param c1 color 1
/// @param c2 color 2
/// @param t inertia
// ================================================ //
MLColor GKInterpolateColor(const MLColor& c1, const MLColor& c2, MLInteger t)
{
	return {
		(1 - t) * c1.r + t * c2.r,
		(1 - t) * c1.g + t * c2.g,
		(1 - t) * c1.b + t * c2.b};
}

// ================================================ //
/// @brief Draws a linear gradient.
/// @param p0 point 0.
/// @param p1 point 1.
/// @param c0 color 0.
/// @param c1 color 1.
// ================================================ //
void GKDrawLinearGradient(const MLPoint& p0, const MLPoint& p1, const MLColor& c0, const MLColor& c1)
{
	for (MLInteger x = p0.x; x <= p1.x; ++x)
	{
		MLInteger8 t = (x - p0.x) / (p1.x - p0.x);

		MLColor color = GKInterpolateColor(c0, c1, t);
		GKDrawPixel(x, p0.y, color); // Implement `drawPixel` for your stack
	}
}

// ================================================ //
/// @brief Draws an arc.
/// @param cx x pos.
/// @param cy y pos.
/// @param r r position.
/// @param start_angle start angle.
/// @param end_angle end angle.
/// @param color color variable.
// ================================================ //
void GKDrawArc(MLInteger cx, MLInteger cy, MLReal r, MLReal start_angle, MLReal end_angle, MLColor color)
{
	const MLInteger resolution = 100;

	for (MLInteger i = 0; i <= resolution; ++i)
	{
		MLInteger theta = start_angle + (end_angle - start_angle) * i / resolution;
		MLInteger x	 = cx + r * std::cos(theta);
		MLInteger y	 = cy + r * std::sin(theta);

		GKDrawPixel(x, y, color); // Implement `drawPixel`
	}
}

// ================================================ //
/// @brief Draws a line.
/// @param p1 point 1.
/// @param p2 point 2.
/// @param color color variable.
// ================================================ //
void GKDrawLineEx(MLPoint& p1, MLPoint& p2, MLColor& color)
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

// ================================================ //
/// @brief Draws a rounded rectangle.
/// @param x x position of rectangle.
/// @param x y position of rectangle.
/// @param width width of rectangle.
/// @param height height of rectangle.
/// @param radius raidus of rectangle.
/// @param color color variable.
// ================================================ //
void GKDrawRoundedRectangle(MLInteger x, MLInteger y, MLInteger width, MLInteger height, MLReal radius, MLColor color)
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

// ================================================ //
/// @brief Puts a pixel into the framebuffer.
/// @param cx x position.
/// @param cy y position.
/// @param color color variable.
// ================================================ //
void GKDrawPixel(MLInteger cx, MLInteger cy, MLColor color)
{
	if (!kWindowServerFB)
		return;

	kWindowServerFB[cx * cy] = color;
}

// ================================================ //
/// @brief Overloaded version of GKDrawLine.
/// @param cx x position.
/// @param cy y position.
/// @param cx1 dst x position.
/// @param cy1 dst y position.
/// @param color color variable.
// ================================================ //
void GKDrawLine(MLInteger cx, MLInteger cy, MLInteger cx1, MLInteger cy1, MLColor color)
{
	MLPoint sp, dp;

	sp = {.x = cx, .y = cy};
	dp = { .x = cx1, .y = cy1};

	return GKDrawLineEx(sp, dp, color);
}