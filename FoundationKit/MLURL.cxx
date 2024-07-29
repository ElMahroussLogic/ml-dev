/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLURL.hxx>

#include <cstring>

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

	MLChar protocolBuf[bufLen];
	MLInteger64 cnter = 0UL;
	MLString path(bufLen);

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
	constexpr MLInteger bufLen = 512;
	MLChar protocolBuf[bufLen];
	MLInteger64 cnter = 0UL;

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
		return kFileProtocol;
	}
	else if (strcmp("http://", protocolBuf) == 0)
	{
		return kHttpProtocol;
	}
	else if (strcmp("https://", protocolBuf) == 0)
	{
		return kHttpsProtocol;
	}
	else if (strcmp("zup://", protocolBuf) == 0)
	{
		return kZUPProtocol;
	}
	else if (strcmp("oscc://", protocolBuf) == 0)
	{
		return kParamProtocol;
	}

	return -1;
}

/// @brief Open path using default app.
/// @return MLInteger exit code.
MLInteger64 MLURL::openPath() noexcept
{
	return (MLInteger64)ML_EXEC(mPath.asConstBytes());
}
