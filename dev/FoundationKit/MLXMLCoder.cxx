/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLXMLCoder.hxx>
#include <iostream>
#include <stdexcept>
#include <cstddef>

/// ctor, dtors...

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
MLString MLXMLCoder::getInnerXML(MLString name, MLSizeType bufSz, bool pureOutput)
{
	return this->getInnerXML(name.asBytes(), bufSz, pureOutput);
}

/// @brief Gets the content of a unique markup.
/// @param name the markup name
/// @param bufSz the buffer size to allocate
/// @param pureOutput strip \t, \n, \r and spaces if set to true.
/// @return MLString the value of **name** as a MLString.
MLString MLXMLCoder::getInnerXML(const char* name, MLSizeType bufSz, bool pureOutput)
{
	try
	{
		ML_MUST_PASS(bufSz != 0);

		MLString bufElement(bufSz);
		bool	 insideElement = false;

		MLSizeType indexType = 0UL;
		for (size_t i = 0; i < mBlob.size(); i++)
		{
			if (mBlob[i] == '<')
			{
				if (mBlob[i + 1] == '/' || mBlob[i + 1] == '?')
				{
					insideElement = false;
				}
				else
				{
					if (mBlob[i + 1] == '!' && mBlob[i + 2] == '-' &&
						mBlob[i + 3] == '-')
					{
						for (; i < mBlob.size(); i++)
						{
							if (mBlob[i] == '-' && mBlob[i + 1] == '-' &&
								mBlob[i + 2] == '>')
							{
								break;
							}
						}
					}
					else
					{
						if (isdigit(mBlob[i + 1]) || isalnum(mBlob[i + 1]))
						{
							if (mBlob[i + 1] != '!' && mBlob[i + 1] != '-')
							{
								goto xml_parse_good;
							}
						}

						if (mBlob[i + 1] != '!' || mBlob[i + 2] != '-' ||
							mBlob[i + 3] != '-')
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
			else if (mBlob[i] == '>')
			{
				insideElement = false;
			}

			if (insideElement)
			{
				size_t y = i;
				for (; y < mBlob.size(); y++)
				{
					if (mBlob[y] == '>')
						break;

					if (mBlob[y] == name[indexType])
					{
						++indexType;
					}
					else
					{
						insideElement = false;
						break;
					}
				}

				if (insideElement)
				{
					++y;

					MLSizeType indexNewStr = 0ul;

					for (; y < mBlob.size(); y++)
					{
						if (mBlob[y] == '<' && mBlob[y + 1] == '/')
						{
							bool noMatch = false;

							if (mBlob[y] == '<')
							{
								size_t yCpy = y + 2;

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
							if (mBlob[y] == '\t' || mBlob[y] == '\n' || mBlob[y] == '\r' ||
								mBlob[y] == ' ')
							{
								continue;
							}
						}

						bufElement[indexNewStr] = mBlob[y];
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

		sprintf(buf, errXml, e.what());

		MLString strError(strlen(buf));
		strError += buf;

		delete []buf;

		return strError;
	}
}

const MLString MLXMLCoder::toString()
{
    auto cLen = 4096;
    cLen += this->mBlob.usedBytes();

	MLString xmlAsJsonStr = MLString(cLen);
	xmlAsJsonStr += "[{ 'name': 'MLXMLCoder', 'blob': '";
	
	for (size_t i = 0; i < this->mBlob.size(); i++)
	{
		if (this->mBlob[i] == '\'')
			xmlAsJsonStr += "\\\\";
		else
			xmlAsJsonStr += this->mBlob[i];
	}
	

	xmlAsJsonStr += "' }]";

	return xmlAsJsonStr;
}
