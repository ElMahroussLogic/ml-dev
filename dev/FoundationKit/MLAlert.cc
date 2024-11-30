/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLAlert.h>
#include <FoundationKit/MLApplication.h>

#include <cstdarg>
#include <cstdio>

#ifdef _WIN32
#define _WIN32_IE 0x0300
#include <FoundationKit/Win32/Win32.h>
#endif // ifdef _WIN32

/// @brief Defines the alert modal for the MLKit.

/// @brief C++ constructor.
MLAlert::MLAlert()	= default;

/// @brief C++ desctructor.
MLAlert::~MLAlert() = default;

/// @brief Shows a modal with title and message.
/// @param title the title.
/// @param format the message format.
/// @param va_list params of format.
/// @return if the user clicked ok.
bool MLAlert::runModal(const MLChar* title, const MLChar* format, ...)
{
	va_list va;
	va_start(va, format);

	MLChar msg[4096];

	vsnprintf(msg, 4096, format, va);

	va_end(va);

	auto isOk = !::MLAlertBox(title, msg);

	return isOk;
}

/// @brief Shows an error modal with title and message.
/// @param title the title.
/// @param format the message format.
/// @param va_list params of format.
/// @return what the user choose.
MLInteger MLAlert::runErrorModal(const MLChar* title, const MLChar* format, ...)
{
	va_list va;
	va_start(va, format);

	MLChar msg[4096];

	vsnprintf(msg, 4096, format, va);

	va_end(va);

#ifdef _WIN32
	int isOk = ::MessageBoxA(nullptr, msg, title, MB_ABORTRETRYIGNORE | MB_ICONERROR);
#else
	auto isOk = !::MLAlertBox(title, msg);
#endif

	return isOk;
}

/// @brief Shows a modal with no title.
/// @param message
/// @return
bool MLAlert::runModal(const MLChar* message)
{
#ifdef _WIN32
	return ::MessageBoxA(nullptr, message, MLApplication::shared().getAppName().asConstBytes(), MB_OK | MB_ICONINFORMATION) == IDOK;
#else
	return !::MLAlertBox(message, MLApplication::shared().getAppName().asConstBytes());
#endif
}

const MLString MLAlert::toString()
{
	MLString str = MLString("['ClassName': 'MLAlert']");
	return str;
}
