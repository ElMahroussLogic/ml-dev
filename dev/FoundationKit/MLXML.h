/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

/// @brief Standard XML extension.
inline const char* kXMLExtension = "xml";
inline const char* kXMLMime		 = "application/xml";

class MLXMLParser;
class MLXMLCoder;

/// @brief XML node class.
class MLXMLParser ML_OBJECT
{
public:
	explicit MLXMLParser(const MLChar* blob);
	explicit MLXMLParser(const MLString blob);

	~MLXMLParser() override;

public:
	ML_COPY_DEFAULT(MLXMLParser);

public:
	/***********************************************************************************/
	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param valueMaxSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @param getAttribute get attribute instead of value.
	/// @return XML as string.
	/***********************************************************************************/
	MLString parseXML(MLString name, MLSizeType valueMaxSz, BOOL pureOutput = false, BOOL getAttribute = false);

	/***********************************************************************************/
	/// @brief Gets the content of a unique markup.
	/// @param name the markup name
	/// @param valueMaxSz the buffer size to allocate
	/// @param pureOutput strip \t, \n, \r and spaces if set to true.
	/// @param getAttribute get attribute instead of value.
	/// @return XML as string.
	/***********************************************************************************/
	MLString parseXML(const MLChar* name, MLSizeType valueMaxSz, BOOL pureOutput = false, BOOL getAttribute = false);

	/***********************************************************************************/
	/// @brief Cast XML to string.
	/// @return MLString value as JSON.
	/***********************************************************************************/
	const MLString toString() override;

private:
	MLString mBlob;
};
