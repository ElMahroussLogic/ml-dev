/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLString.hxx>

#include <FoundationKit/Linux/Linux.hxx>
#include <FoundationKit/MacOS/MacOS.hxx>
#include <FoundationKit/ZKA/ZKA.hxx>
#include <FoundationKit/Win32/Win32.hxx>

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
