/* -------------------------------------------

	Copyright (C) 2024, EL Mahrouss Logic, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLRange.h>

MLRange::operator bool()
{
	return location <= length;
}
