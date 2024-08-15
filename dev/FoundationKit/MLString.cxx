/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/MLAllocator.hxx>
#include <FoundationKit/MLString.hxx>
#include <cstring>

MLString::MLString(MLSizeType sizeOfBuffer)
{
	mCursor = 0;
	mSize	= sizeOfBuffer;
	mData	= MLAllocator::shared().initWithSize<MLChar>(sizeOfBuffer);
	memset(mData, 0, mSize);
}

MLString::~MLString() = default;

MLString& MLString::operator+=(const MLString text)
{
	*this += text.mData;
	return *this;
}

MLString& MLString::operator+=(const MLChar chr)
{
	MLChar buf[2];
	buf[0] = chr;
	buf[1] = 0;

	*this += buf;

	return *this;
}

MLString& MLString::operator+=(const MLChar* text)
{
	MLSizeType sz_rhs = strlen(text);

	if (sz_rhs == 0)
		return *this;
	if (mCursor > mSize || sz_rhs > mSize)
		return *this;

	memcpy(mData + mCursor, text, sz_rhs);
	mCursor += sz_rhs;

	return *this;
}

MLSizeType MLString::usedBytes()
{
	return mCursor;
}

MLSizeType MLString::size()
{
	return mSize;
}

MLChar& MLString::operator[](MLSizeType index)
{
	return mData[index];
}

MLChar* MLString::asBytes()
{
	return mData;
}

const MLChar* MLString::asConstBytes() const
{
	return mData;
}

void MLString::dispose()
{
	MLAllocator::shared().disposeArray(mData);
}

const MLString MLString::toString()
{
	const auto cLen = 512;

	MLString str(cLen);
	str += "MLString";

	return str;
}

MLString& MLString::operator=(const MLString& rhs)
{
	mData	= rhs.mData;
	mCursor = rhs.mCursor;
	mSize	= rhs.mSize;

	return *this;
}

MLString::MLString(const MLString& rhs)
{
	mData	= rhs.mData;
	mCursor = rhs.mCursor;
	mSize	= rhs.mSize;
}
