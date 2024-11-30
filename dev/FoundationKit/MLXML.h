/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

/// @brief Standard XML extension.
inline const char* kXMLExtension = "xml";
inline const char* kXMLMime		 = "application/xml";

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
	/***********************************************************************************/
	/// @brief Gets the content of a unique markup (with no attributes)
	/// @param name the markup name
	/// @param buffer_size the buffer size to allocate.
	/// @return MLString the value of **name** as a MLString.
	/***********************************************************************************/
	MLString getValue(MLString name, MLSizeType valueMaxSz);

	/***********************************************************************************/
	/// @brief Gets the content of a unique markup (with no attributes)
	/// @param name the markup name
	/// @param buffer_size the buffer size to allocate.
	/// @return MLString the value of **name** as a MLString.
	/***********************************************************************************/
	MLString getValue(const MLChar* name, MLSizeType valueMaxSz);

	/***********************************************************************************/
	/// @brief Cast XML to string.
	/// @return MLString value as JSON.
	/***********************************************************************************/
	const MLString toString() override;

private:
	MLString mBlob;
};
