/* -------------------------------------------

	Copyright ZKA Web Services Co.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

/// @brief A X, Y point within a display.
struct MLPoint
{
	MLReal x;
	MLReal y;

	/// @brief Check if point is within the current MLPoint.
	/// @param point the current point to check.
	/// @retval true if point is within this point.
	/// @retval validations failed.
	bool isWithin(MLPoint& point)
	{
		return point.x > x && point.y > y;
	}
};
