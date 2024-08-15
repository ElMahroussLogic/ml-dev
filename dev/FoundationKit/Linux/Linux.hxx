/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#pragma once

#ifdef __linux__

#include <FoundationKit/Foundation.hxx>
#include <unistd.h>
#include <cstdlib>

#define ML_EXEC(PATH) 	 std::system(PATH)

#endif
