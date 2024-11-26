/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

/// @brief A X, Y point within a display.
struct MLPoint
{
	MLInteger64 x{0};
	MLInteger64 y{0};

	/// @brief Check if point is within the current MLPoint.
	/// @param point the current point to check.
	/// @retval true if point is within this point.
	/// @retval validations failed.
	bool isWithin(MLPoint& point);
};
