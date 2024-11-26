/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>
#include <FoundationKit/MLXML.h>

class MLApplication final ML_OBJECT
{
private:
	MLApplication() = default;

public:
	~MLApplication() override = default;

	ML_COPY_DEFAULT(MLApplication);

public:
	/// @brief Returns the application's name as given by the bundle.
	/// @return the app string.
	const MLString getAppName();

	/// @brief Returns the application's version as given by the bundle.
	/// @return the app string.
	const MLString getAppVersion();

	/// @brief Returns the application's field.
	/// @param fieldName The field's name. (such as MLAppName, MLFooField)
	/// @return the field's value.
	const MLString getAppField(MLString fieldName, MLSizeType fieldLen = 512);

	/// @brief Application singleton
	/// @return the singleton.
	static MLApplication& shared();

	/// @brief Application data as string.
	/// @return data as **MLString**
	const MLString toString() override;

	/// @brief Opens the about modal.
	void showAboutModal() noexcept;
};
