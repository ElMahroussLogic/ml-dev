/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLAlert.hxx>
#include <FoundationKit/MLAllocator.hxx>
#include <FoundationKit/Win32/Win32.hxx>

/// @brief Raised when an assertion fails.
/// @param none.
/// @return none.
ML_EXPORT void MLAssert(const char* expr, const char* file, const int line)
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
