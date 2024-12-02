/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#include <FoundationKit/MLProcess.h>
#include <POSIXKit/unistd.h>
#include <POSIXKit/signal.h>

MLProcess::MLProcess(const MLChar* path, const MLChar* argv, MLChar* const* envp)
	: mProcessPath(path)
{
	// fork current image into a separate process.
	mProcessHandle = ::fork();

	// if successful (in this fork) execute the process from path.
	if (mProcessHandle == 0)
		posix::execlp(mProcessPath.asBytes(), argv, envp);
}

MLProcess::~MLProcess()
{
	mProcessPath.dispose();
}

void MLProcess::exitThread() noexcept
{

	if (mProcessHandle != 0)
	{
		posix::kill(mProcessHandle, SIGKILL);
		mProcessHandle = 0;
	}
}
