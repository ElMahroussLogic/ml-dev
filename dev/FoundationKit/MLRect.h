/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

struct MLRect
{
	MLInteger64 x{0UL};
	MLInteger64 y{0UL};
	MLInteger64 width{0UL};
	MLInteger64 height{0UL};

	operator bool();

	BOOL sizeMatches(MLRect& rect) noexcept;
	BOOL positionMatches(MLRect& rect) noexcept;
};
