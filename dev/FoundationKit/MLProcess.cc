/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved.

------------------------------------------- */

#include <FoundationKit/MLProcess.h>

ML_EXTERN_C
{
#include <unistd.h>
#include <signal.h>
};

MLProcess::MLProcess(const MLChar* path, const MLChar* argv, MLChar* const* envp)
	: mProcessPath(path)
{
	// fork current image into a separate process.
	mProcessHandle = ::fork();

	// if successful (in this fork) execute the process from path.
	if (mProcessHandle == 0)
		::execlp(mProcessPath.asBytes(), argv, envp);
}

MLProcess::~MLProcess()
{
	mProcessPath.dispose();
}

void MLProcess::exitThread() noexcept
{

	if (mProcessHandle != 0)
	{
		::kill(mProcessHandle, SIGKILL);
		mProcessHandle = 0;
	}
}
