/* -------------------------------------------

	Copyright Amlal EL Mahrouss

------------------------------------------- */

#include <FoundationKit/MLRange.h>

MLRange::operator bool()
{
	return location <= length;
}
