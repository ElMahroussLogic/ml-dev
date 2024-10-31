/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

/// @brief Standard XML extension.
inline const char* kXMLExtension = "xml";
inline const char* kXMLMime = "application/xml";

class MLXMLNode;
class MLXMLCoder;

/// @brief XML node class.
class MLXMLNode ML_OBJECT
{
public:
	explicit MLXMLNode(const MLChar* blob);
	explicit MLXMLNode(const MLString blob);

	~MLXMLNode() override;

public:
	ML_COPY_DEFAULT(MLXMLNode);

public:
	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param valueMaxSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @param getAttribute get attribute instead of value.
	/// @return
	MLString getXMLDataFromMarkup(MLString name, MLSizeType valueMaxSz, BOOL pureOutput = false, BOOL getAttribute = false);

	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param valueMaxSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @param getAttribute get attribute instead of value.
	/// @return
	MLString getXMLDataFromMarkup(const MLChar* name, MLSizeType valueMaxSz, BOOL pureOutput = false, BOOL getAttribute = false);

	/// @brief Cast XML to string.
	const MLString toString() override;

private:
	MLString mBlob;
};
