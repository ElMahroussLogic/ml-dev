/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLAlert.h>
#include <FoundationKit/MLAllocator.h>
#include <FoundationKit/Win32/Win32.h>

/// @brief Raised when an assertion fails.
/// @param none.
/// @return none.
ML_EXPORT VOID MLAssert(const MLChar* expr, const MLChar* file, const MLInteger line)
{
	MLAlert* alert = MLAllocator::shared().init<MLAlert>();
	auto	 res   = alert->runErrorModal("FoundationKit Runtime.",
									  "File: %s\nCause: %s\nLine: %i", file, expr, line);

	MLAllocator::shared().dispose<MLAlert>(alert);

#ifdef _WIN32
	if (res == IDABORT)
	{
		MLExitWithCode(-34);
	}
	else if (res == IDRETRY)
	{
#ifdef ML_DEBUG
		if (IsDebuggerPresent())
		{
			DebugBreak();
		}
#endif

		MLExitWithCode(-33);
	}
#endif // _WIN32
}
