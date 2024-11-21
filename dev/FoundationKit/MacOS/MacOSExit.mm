/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <pthread.h>
#include <stdlib.h>

static int kExitCode = 0UL;

/// @brief Exits the current thread.
/// @param exitCode it's exit code.
/// @return void, no return arguments.
void MLExitWithCode(int exitCode, void* currentThreadHandle)
{
	kExitCode = exitCode;
	pthread_exit(currentThreadHandle);
}

/// @brief Exit pthread.
/// @param exitCode the exitcode.
void MLExitWithCode(int exitCode)
{
	kExitCode = exitCode;
	pthread_exit((void*)pthread_self());
}

/// @brief Get last exit code from any thread.
/// @return the exit code of the thread.
int32_t MLGetExitCode(void) { return kExitCode; }
