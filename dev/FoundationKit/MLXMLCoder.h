/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

/// @brief Standard XML extension.
inline const char* cXMLExtension = "xml";

/// @brief XML parser class.
class MLXMLCoder final ML_OBJECT
{
public:
	MLXMLCoder(const char* blob);

	MLXMLCoder& operator=(const MLXMLCoder&) = default;
	MLXMLCoder(const MLXMLCoder&)			 = default;

	~MLXMLCoder() override;

public:
	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param bufSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @return
	MLString getXML(MLString name, MLSizeType bufSz, bool pureOutput);

	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param bufSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @return
	MLString getXML(const MLChar* name, MLSizeType bufSz, bool pureOutput = false, bool getAttribute = false);

	/// @brief Cast XML to string.
	const MLString toString() override;

private:
	MLString mBlob;
};

extern const char* cXMLExtension;
extern const char* cAPlistExtension;
