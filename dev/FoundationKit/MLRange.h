/* -------------------------------------------

	Copyright Amlal EL Mahrouss

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
