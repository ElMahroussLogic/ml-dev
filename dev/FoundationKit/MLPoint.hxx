/* -------------------------------------------

	Copyright ZKA Web Services Co.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>

struct MLPoint
{
	MLReal x;
	MLReal y;

	operator bool()
	{
		return x > 0 && y > 0;
	}
};
