/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

#include <FoundationKit/Linux/Linux.h>
#include <FoundationKit/MacOS/MacOS.h>
#include <FoundationKit/ZKA/ZKA.h>
#include <FoundationKit/Win32/Win32.h>

/// @brief URL parser class.
class MLURL final ML_OBJECT
{
	MLString mPath;

public:
	explicit MLURL(const MLChar* url);
	explicit MLURL() = delete;

	MLURL& operator=(const MLURL&) = default;
	MLURL(const MLURL&)			   = default;

	~MLURL() override;

	enum
	{
		kFileProtocol,
		kHttpProtocol,
		kHttpsProtocol,
		kZUPProtocol,
		kParamProtocol,
		kZKAProtocol
	};

	/// @brief get path of URL.
	/// @return MLString the path as a MLString.
	MLString getPath() noexcept;

	/// @brief get protocol of URL.
	/// @return MLInteger the protocol as an enum.
	MLInteger getProtocol() noexcept;

	/// @brief Open path using default app.
	/// @return MLInteger exit code.
	MLInteger64 openPath() noexcept;
};