/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLRange.h>

MLRange::operator bool()
{
	return location <= length;
}
