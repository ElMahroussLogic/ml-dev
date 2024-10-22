/* -------------------------------------------

	Copyright ZKA Web Services Co.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

struct MLRect
{
	MLInteger64 x;
	MLInteger64 y;
	MLInteger64 width;
	MLInteger64 height;

	operator bool()
	{
		return width > 0 && height > 0;
	}
};
