/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLPoint.h>

/// @brief Check if point is within the current MLPoint.
/// @param point the current point to check.
/// @retval true if point is within this point.
/// @retval validations failed.
bool MLPoint::isWithin(MLPoint& point)
{
	return point.x > x && point.y > y;
}
