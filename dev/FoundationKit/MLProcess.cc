/* -------------------------------------------

	Copyright (C) 2024, EL Mahrouss Logic, all rights reserved.

------------------------------------------- */

#include <FoundationKit/MLProcess.h>

#include <unistd.h>
#include <signal.h>

MLProcess::MLProcess(const MLChar* path, const MLChar* argv, MLChar* const* envp)
	: mProcessPath(path)
{
	mProcessHandle = fork();

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