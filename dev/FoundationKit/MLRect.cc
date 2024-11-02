/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#include <FoundationKit/MLRect.h>

MLRect::operator bool() { return width > 0 && height > 0; }

BOOL MLRect::sizeMatches(MLRect& rect) noexcept { return rect.height == height && rect.width == width; }

BOOL MLRect::positionMatches(MLRect& rect) noexcept { return rect.y == y && rect.x == x; }
