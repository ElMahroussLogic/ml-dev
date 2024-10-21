/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#pragma once

#ifdef __linux__

#include <FoundationKit/Foundation.h>
#include <unistd.h>
#include <cstdlib>

#define ML_EXEC(PATH) std::system(PATH)

#endif
