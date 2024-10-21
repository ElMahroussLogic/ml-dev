/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLXMLCoder.h>

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cstring>

MLXMLCoder::MLXMLCoder(const MLChar* blob)
	: mBlob(strlen(blob))
{
	mBlob += blob;
}

MLXMLCoder::~MLXMLCoder()
{
	mBlob.dispose();
}

/// @brief Gets the content of a unique markup.
/// @param name the markup name
/// @param bufSz the buffer size to allocate
/// @param pureOutput strip \t, \n, \r and spaces if set to true.
/// @return MLString the value of **name** as a MLString.
MLString MLXMLCoder::getXML(MLString name, MLSizeType bufSz, bool pureOutput)
{
	return this->getXML(name.asBytes(), bufSz, pureOutput);
}

/// @brief Gets the content of a unique markup.
/// @param name the markup name
/// @param bufSz the buffer size to allocate
/// @param pureOutput strip \t, \n, \r and spaces if set to true.
/// @return MLString the value of **name** as a MLString.
MLString MLXMLCoder::getXML(const MLChar* name, MLSizeType bufSz, bool pureOutput, bool getAttribute)
{
	try
	{
		ML_MUST_PASS(bufSz != 0);

		MLString bufElement(bufSz);
		bool	 insideElement = false;

		MLSizeType indexType = 0UL;

		for (MLSizeType blobIndex = 0; blobIndex < mBlob.size(); ++blobIndex)
		{
			if (mBlob[blobIndex] == '<')
			{
				if (mBlob[blobIndex + 1] == '/' || mBlob[blobIndex + 1] == '?')
				{
					insideElement = false;
				}
				else
				{
					if (mBlob[blobIndex + 1] == '!' && mBlob[blobIndex + 2] == '-' &&
						mBlob[blobIndex + 3] == '-')
					{
						for (; blobIndex < mBlob.size(); blobIndex++)
						{
							if (mBlob[blobIndex] == '-' && mBlob[blobIndex + 1] == '-' &&
								mBlob[blobIndex + 2] == '>')
							{
								break;
							}
						}
					}
					else
					{
						if (isdigit(mBlob[blobIndex + 1]) || isalnum(mBlob[blobIndex + 1]))
						{
							if (mBlob[blobIndex + 1] != '!' && mBlob[blobIndex + 1] != '-')
							{
								goto xml_parse_good;
							}
						}

						if (mBlob[blobIndex + 1] != '!' || mBlob[blobIndex + 2] != '-' ||
							mBlob[blobIndex + 3] != '-')
						{
							throw std::runtime_error("Invalid XML comment.");
						}
					}

				xml_parse_good:
					insideElement = true;
					indexType	  = 0UL;

					continue;
				}
			}
			else if (mBlob[blobIndex] == '>')
			{
				insideElement = false;
			}

			MLSizeType indexNewStr = 0ul;

			if (insideElement)
			{
				MLSizeType blobIndexAt = blobIndex;

				for (; blobIndexAt < mBlob.size(); ++blobIndexAt)
				{
					if (mBlob[blobIndexAt] == name[indexType])
					{
						++indexType;
					}
					else
					{
						if (mBlob[blobIndexAt] == ' ' &&
							std::isalnum(mBlob[blobIndexAt + 1]))
						{

							for (; blobIndexAt < mBlob.size(); ++blobIndexAt)
							{
								if (mBlob[blobIndexAt] == '\"')
								{
									++blobIndexAt;

									for (; blobIndexAt < mBlob.size(); ++blobIndexAt)
									{
										if (mBlob[blobIndexAt] == '\"')
										{
											break;
										}

										if (getAttribute)
										{
											bufElement[indexNewStr] = mBlob[blobIndexAt];
											++indexNewStr;
										}
									}

									if (getAttribute)
										return bufElement;

									break;
								}
							}
						}

						if (mBlob[blobIndexAt] == '>')
						{
							break;
						}
					}
				}

				if (insideElement)
				{
					++blobIndexAt;

					for (; blobIndexAt < mBlob.size(); blobIndexAt++)
					{
						if (mBlob[blobIndexAt] == '<' && mBlob[blobIndexAt + 1] == '/')
						{
							bool noMatch = false;

							if (mBlob[blobIndexAt] == '<')
							{
								size_t yCpy = blobIndexAt + 2;

								for (size_t x = 0; x < strlen(name); ++x)
								{
									if (mBlob[yCpy] == '/')
									{
										++yCpy;
										continue;
									}
									if (mBlob[yCpy] == '>')
									{
										break;
									}

									if (mBlob[yCpy] != name[x])
									{
										noMatch = true;
										break;
									}

									++yCpy;
								}

								if (!noMatch)
									break;
							}
						}

						if (pureOutput)
						{
							if (mBlob[blobIndexAt] == '\t' || mBlob[blobIndexAt] == '\n' || mBlob[blobIndexAt] == '\r' ||
								mBlob[blobIndexAt] == ' ')
							{
								continue;
							}
						}

						bufElement[indexNewStr] = mBlob[blobIndexAt];
						++indexNewStr;
					}

					bufElement[indexNewStr] = 0;
				}
			}
		}

		return bufElement;
	}
	catch (const std::runtime_error& e)
	{
		MLLog("%s\n", e.what());

		const MLChar* errXml =
			"<XmlError><Message>%s</Message></XmlError>";

		size_t length_xml = 4096;
		length_xml += strlen(e.what());

		MLChar* buf = new MLChar[length_xml];

		snprintf(buf, length_xml, errXml, e.what());

		MLString strError(strlen(buf));
		strError += buf;

		delete[] buf;

		return strError;
	}
}

const MLString MLXMLCoder::toString()
{
	auto cLen = 4096;
	cLen += this->mBlob.usedBytes();

	MLString xmlAsJsonStr = MLString(cLen);
	xmlAsJsonStr += "[{ 'name': 'MLXMLCoder', 'blob': '";

	for (size_t blobIndex = 0; blobIndex < this->mBlob.size(); blobIndex++)
	{
		if (this->mBlob[blobIndex] == '\'')
			xmlAsJsonStr += "\\\\";
		else
			xmlAsJsonStr += this->mBlob[blobIndex];
	}

	xmlAsJsonStr += "' }]";

	return xmlAsJsonStr;
}
