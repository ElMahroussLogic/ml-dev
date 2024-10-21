/* -------------------------------------------

	Copyright ZKA Web Services Co.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>

struct MLRect
{
	MLInteger64 x;
	MLInteger64 y;
	MLInteger	width;
	MLInteger	height;

	operator bool()
	{
		return width > 0 && height > 0;
	}
};
