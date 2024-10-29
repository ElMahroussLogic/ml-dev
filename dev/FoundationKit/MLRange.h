/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

struct MLRange;

struct MLRange final
{
	MLInteger64 location;
	MLInteger64 length;

	operator bool()
	{
		return location <= length;
	}
};
