/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#include <FoundationKit/MLRange.h>

MLRange::operator bool()
{
	return location <= length;
}
