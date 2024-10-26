/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

/// @brief Standard XML extension.
inline const char* kXMLExtension = "xml";
inline const char* kXMLMime = "application/xml";

class MLXMLMarkup;
class MLXMLCoder;

/// @brief XML parser class.
class MLXMLMarkup final ML_OBJECT
{
public:
	MLXMLMarkup(const char* blob);

	MLXMLMarkup& operator=(const MLXMLMarkup&) = default;
	MLXMLMarkup(const MLXMLMarkup&)			 = default;

	~MLXMLMarkup() override;

public:
	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param bufSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @return
	MLString getXMLDataFromMarkup(MLString name, MLSizeType bufSz, bool pureOutput = false, bool getAttribute = false);

	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param bufSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @return
	MLString getXMLDataFromMarkup(const MLChar* name, MLSizeType bufSz, bool pureOutput = false, bool getAttribute = false);

	/// @brief Cast XML to string.
	const MLString toString() override;

private:
	MLString mBlob;
};
