/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

class MLProcess final ML_OBJECT
{
public:
	MLProcess(const MLChar* path, const MLChar* argv, MLChar* const* envp);
	~MLProcess() override;

	ML_COPY_DEFAULT(MLProcess);

	void exitThread() noexcept;

private:
	MLString	mProcessPath;
	MLInteger64 mProcessHandle{0};
};
