/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLString.hxx>
#include <FoundationKit/MLXMLCoder.hxx>

class MLApplication final ML_OBJECT
{
	MLApplication() = default;

public:
	~MLApplication() override = default;

	MLApplication& operator=(const MLApplication&) = default;
	MLApplication(const MLApplication&)			   = default;

	/// @brief Returns the application's name as given by the bundle.
	/// @return the app string.
	const MLString getAppName();

	/// @brief Returns the application's version as given by the bundle.
	/// @return the app string.
	const MLString getAppVersion();

	/// @brief Application singleton
	/// @return the singleton.
	static MLApplication& shared();

	/// @brief Application data as string.
	/// @return data as **MLString**
	const MLString toString() override;

	/// @brief Opens the about modal.
	void showAboutModal() noexcept;
};
