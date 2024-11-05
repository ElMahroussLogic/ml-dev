/* -------------------------------------------

	Copyright Amlal EL Mahrouss

------------------------------------------- */

#pragma once

#ifdef __linux__

#include <FoundationKit/Foundation.h>
#include <unistd.h>
#include <cstdlib>
#include <thread>

#define ML_EXEC(PATH) std::system(PATH)

#endif
