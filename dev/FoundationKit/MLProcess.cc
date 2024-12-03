/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <FoundationKit/MLProcess.h>
#include <POSIXKit/unistd.h>
#include <POSIXKit/signal.h>

#define kHowMuchWaitSig 1
#define kHowMuchPathName 4096

// ================================================ //
/// @brief C++ constructor for a process.
// ================================================ //

MLProcess::MLProcess(const MLChar* path, const MLChar* argv, MLChar* const* envp)
	: mProcessPath(kHowMuchPathName)
{
	this->spawnProcess(path, argv, envp);
}

MLProcess::~MLProcess()
{
	mProcessPath.dispose();
}

// ================================================ //
/// @brief Exit process.
// ================================================ //

void MLProcess::exitThread() noexcept
{
	if (mProcessHandle != 0)
	{
		posix::kill(mProcessHandle, SIGKILL);
		mProcessHandle = 0;
	}
}

// ================================================ //
/// @brief spawns a new process.
// ================================================ //

void MLProcess::spawnProcess(const MLChar* path, const MLChar* argv, MLChar* const* envp)
{
	mProcessPath = path;

	// fork current image into a separate process.
	mProcessHandle = ::fork();

	// if successful (in this fork) execute the process from path.
	if (mProcessHandle == 0)
		posix::execlp(mProcessPath.asBytes(), argv, envp);
}

// ================================================ //
/// @brief send signal to a process.
// ================================================ //

void MLProcess::sendSignal(MLInteger sig) noexcept
{
	if (mProcessHandle != 0)
	{
		auto sig_pid = ::fork();

		// if successful (in this fork) execute the process from path.
		if (sig_pid == 0)
		{
			posix::kill(sig_pid, sig);
			sleep(kHowMuchWaitSig);
		}
	}
}