/* -------------------------------------------

	Copyright EL Mahrouss Logic.

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
};
