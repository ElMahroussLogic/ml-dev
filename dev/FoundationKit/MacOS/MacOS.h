/* -------------------------------------------

	Copyright (C) 2024, EL Mahrouss Logic, all rights reserved

------------------------------------------- */

#pragma once

#ifdef __APPLE__

#include <FoundationKit/Foundation.h>
#include <unistd.h>
#include <cstdlib>

#define ML_EXEC(PATH) std::system(PATH)

#endif // __APPLE__
