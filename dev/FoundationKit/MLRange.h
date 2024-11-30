/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

struct MLRange;

struct MLRange final
{
	MLInteger64 location{0UL};
	MLInteger64 length{0UL};

	operator bool();
};
