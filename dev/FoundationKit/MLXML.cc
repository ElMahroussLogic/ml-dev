/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLXML.h>

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cstring>

MLXMLNode::MLXMLNode(const MLChar* blob)
	: mBlob(strlen(blob))
{
	mBlob += blob;
}

MLXMLNode::MLXMLNode(const MLString blob)
	: mBlob(blob)
{
	ML_MUST_PASS(mBlob.size() > 0);
}

MLXMLNode::~MLXMLNode()
{
	mBlob.dispose();
}

/***********************************************************************************/
/// @brief Gets the content of a unique markup.
/// @param name the markup name
/// @param buffer_size the buffer size to allocate
/// @return MLString the value of **name** as a MLString.
/***********************************************************************************/
MLString MLXMLNode::getValue(MLString name, MLSizeType buffer_size)
{
	return this->getValue(name.asBytes(), buffer_size);
}

/***********************************************************************************/
/// @brief Gets the content of a unique markup.
/// @param name the markup name
/// @param buffer_size the buffer size to allocate.
/// @return MLString the value of **name** as a MLString.
/***********************************************************************************/
MLString MLXMLNode::getValue(const MLChar* name, MLSizeType buffer_size)
{
	try
	{
		ML_MUST_PASS(buffer_size != 0);

		MLString xml_data(buffer_size);

		for (MLSizeType blob_index = 0; blob_index < mBlob.size(); ++blob_index)
		{
			if (mBlob[blob_index] == '<' &&
				mBlob[blob_index + 1] == '/')
			{
				for (; blob_index < mBlob.size(); ++blob_index)
				{
					if (mBlob[blob_index] == '>')
					{
						break;
					}
				}

				break;
			}

			if (mBlob[blob_index] == '<')
			{
				MLInteger64 name_idx = 0UL;

				++blob_index;

				for (; blob_index < mBlob.size(); ++blob_index)
				{
					if (mBlob[blob_index] == '>')
						break;

					if (name[name_idx] == 0)
						break;

					if (mBlob[blob_index] == name[name_idx])
					{
						++name_idx;
						continue;
					}

					xml_data += '\0';
					return xml_data;
				}

				++blob_index;
			}

			xml_data += mBlob[blob_index];
		}

		xml_data += '\0';
		return xml_data;
	}
	catch (const std::runtime_error& e)
	{
		MLLog("%s\n", e.what());

		const MLChar* errXml =
			"<XmlError>%s</XmlError>";

		MLSizeType length_xml = 4096;
		length_xml += strlen(e.what());

		MLChar* buf = new MLChar[length_xml];

		snprintf(buf, length_xml, errXml, e.what());

		MLString strError(strlen(buf));
		strError += buf;

		delete[] buf;

		return strError;
	}
}

/***********************************************************************************/
/// @brief returns the XML node information, alongside it's blob.
/// @return An MLString class.
/***********************************************************************************/
const MLString MLXMLNode::toString()
{
	MLSizeType kLengthOfXML = this->mBlob.usedBytes();
	kLengthOfXML += this->mBlob.usedBytes();

	MLString xmlAsJsonStr = MLString(kLengthOfXML);
	xmlAsJsonStr += "[ 'ClassName': 'MLXMLNode', 'ClassBlob': '";

	for (MLSizeType blob_index = 0; blob_index < this->mBlob.size(); ++blob_index)
	{
		if (this->mBlob[blob_index] == '\'')
			xmlAsJsonStr += "\\\\";
		else
			xmlAsJsonStr += this->mBlob[blob_index];
	}

	xmlAsJsonStr += "' ]";

	return xmlAsJsonStr;
}
