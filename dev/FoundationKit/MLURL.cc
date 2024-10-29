/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLURL.h>
#include <cstring>
#include <sstream>

#define kURLSeparator '/'

MLURL::MLURL(const MLChar* url)
	: mPath(strlen(url))
{
	ML_MUST_PASS(mPath.size() > 1);
	mPath += url;
}

MLURL::~MLURL()
{
	mPath.dispose();
}

/// @brief get path of URL.
/// @return MLString the path as a MLString.
MLString MLURL::getPath() noexcept
{
	constexpr MLInteger bufLen = 4096;

	MLChar		protocolBuf[bufLen];
	MLInteger64 cnterIndex = 0UL;
	MLString	path(bufLen);

	for (MLInteger pathIndex = 0U; pathIndex < mPath.usedBytes(); ++pathIndex)
	{
		if (mPath[pathIndex] == kURLSeparator &&
			mPath[pathIndex - 1] == kURLSeparator)
		{
			++pathIndex;

			for (; pathIndex < mPath.usedBytes(); ++pathIndex)
			{
				protocolBuf[cnterIndex] = mPath[pathIndex];
				++cnterIndex;
			}

			break;
		}
	}

	path += protocolBuf;
	return path;
}

/// @brief get protocol of URL.
/// @return MLInteger the protocol as an enum.
MLInteger MLURL::getProtocol() noexcept
{
	MLInteger	bufLen		= mPath.usedBytes();
	MLChar*		protocolBuf = new MLChar[bufLen];
	MLInteger64 cnter		= 0UL;

	for (MLInteger protoIndex = 0U; protoIndex < mPath.usedBytes(); ++protoIndex)
	{
		if (mPath[protoIndex] == kURLSeparator &&
			mPath[protoIndex - 1] == kURLSeparator)
		{
			break;
		}

		protocolBuf[cnter] = mPath[protoIndex];
		++cnter;
	}

	if (strcmp("file", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kFileProtocol;
	}
	else if (strcmp("http", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kHttpProtocol;
	}
	else if (strcmp("https", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kHttpsProtocol;
	}
	else if (strcmp("zup", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		return kZUPProtocol;
	}
	else if (strcmp("zka", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kZKAProtocol;
	}
	else if (strcmp("param", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kParamProtocol;
	}

	delete[] protocolBuf;
	protocolBuf = nullptr;

	return -1;
}

/// @brief Open path using default app.
/// @return MLInteger exit code.
MLInteger64 MLURL::openPath() noexcept
{
	std::stringstream ssUrl;
	ssUrl << "open "; // 'open' also exists in ZKA.
	ssUrl << mPath.asConstBytes();

	return (MLInteger64)std::system(ssUrl.str().c_str());
}
