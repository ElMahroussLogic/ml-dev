/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLURL.h>
#include <cstring>
#include <sstream>

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
	MLInteger64 cnter = 0UL;
	MLString	path(bufLen);

	for (MLInteger i = 0U; i < mPath.usedBytes(); ++i)
	{
		if (mPath[i] == '/' &&
			mPath[i - 1] == '/')
		{
			++i;

			for (; i < mPath.usedBytes(); ++i)
			{
				protocolBuf[cnter] = mPath[i];
				++cnter;
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

	for (MLInteger i = 0U; i < mPath.usedBytes(); ++i)
	{
		if (mPath[i] == '/' &&
			mPath[i - 1] == '/')
		{
			protocolBuf[cnter] = mPath[i];
			break;
		}

		protocolBuf[cnter] = mPath[i];
		++cnter;
	}

	if (strcmp("file://", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kFileProtocol;
	}
	else if (strcmp("http://", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kHttpProtocol;
	}
	else if (strcmp("https://", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kHttpsProtocol;
	}
	else if (strcmp("zup://", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		return kZUPProtocol;
	}
	else if (strcmp("zka://", protocolBuf) == 0)
	{
		delete[] protocolBuf;
		protocolBuf = nullptr;

		return kZKAProtocol;
	}
	else if (strcmp("param://", protocolBuf) == 0)
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
    std::stringstream ss_url;
    ss_url << "open "; // 'open' also exists in ZKA.
    ss_url << mPath.asConstBytes();

	return (MLInteger64)std::system(ss_url.str().c_str());
}
