/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLRange.h>

MLRange::operator bool()
{
	return location <= length;
}
