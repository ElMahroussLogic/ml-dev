/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#include <FoundationKit/Linux/Linux.h>

ML_STATIC int kLastExitCode = 0UL;

/// @brief Exits the current thread.
/// @param exitCode it's exit code.
/// @return void, no return arguments.
void MLExitWithCode(MLInteger exitCode, std::thread& currentThread)
{
	kLastExitCode = exitCode;
	pthread_exit((void*)currentThread.native_handle());
}

/// @brief Exit pthread.
/// @param exitCode the exitcode.
void MLExitWithCode(MLInteger exitCode)
{
	kLastExitCode = exitCode;
	pthread_exit((void*)pthread_self());
}

/// @brief Get last exit code from any thread.
/// @return the exit code of the thread.
int MLGetExitCode(void)
{
	return kLastExitCode;
}
