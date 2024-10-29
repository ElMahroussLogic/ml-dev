/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#include <FoundationKit/MLRect.h>

MLRect::operator bool()
{
	return width > 0 && height > 0;
}
