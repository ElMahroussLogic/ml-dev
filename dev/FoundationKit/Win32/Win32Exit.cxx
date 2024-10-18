/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/Win32/Win32.hxx>
#include <cstdlib>
#include <thread>

static int sLastExitCode = 0UL;

/// @brief Exits the current thread.
/// @param exitCode it's exit code.
/// @return void, no return arguments.
void MLExitWithCode(MLInteger exitCode, std::thread& currentThread)
{
	sLastExitCode = exitCode;
	::ExitThread(exitCode);
}

void MLExitWithCode(MLInteger exitCode)
{
	sLastExitCode = exitCode;
	::ExitThread(exitCode);
}

/// @brief Get last exit code from any thread.
/// @return the exit code of the thread.
int MLGetExitCode(void)
{
	return sLastExitCode;
}
