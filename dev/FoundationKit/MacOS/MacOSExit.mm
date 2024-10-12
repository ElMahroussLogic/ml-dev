/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <cstdlib>
#include <thread>

static int sLastExitCode = 0UL;

/// @brief Exits the current thread.
/// @param exitCode it's exit code.
/// @return void, no return arguments.
void MLExitWithCode(int exitCode, std::thread& currentThread)
{
	sLastExitCode = exitCode;
	pthread_exit((void*)currentThread.native_handle());
}

/// @brief Exit pthread.
/// @param exitCode the exitcode.
void MLExitWithCode(int exitCode)
{
	sLastExitCode = exitCode;
	pthread_exit((void*)pthread_self());
}

/// @brief Get last exit code from any thread.
/// @return the exit code of the thread.
int32_t MLGetExitCode(void) { return sLastExitCode; }
