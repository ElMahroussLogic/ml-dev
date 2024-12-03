/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLRect.h>

MLRect::operator bool() { return width > 0 && height > 0; }

BOOL MLRect::sizeMatches(MLRect& rect) noexcept { return rect.height == height && rect.width == width; }

BOOL MLRect::positionMatches(MLRect& rect) noexcept { return rect.y == y && rect.x == x; }
