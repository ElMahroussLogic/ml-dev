/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#include "FoundationKit/Foundation.h"
#include <FoundationKit/MLAllocator.h>
#include <FoundationKit/MLString.h>
#include <cstring>

MLString::MLString(MLSizeType sizeOfBuffer)
{
	this->reserve(sizeOfBuffer);
}

MLString::MLString(const MLChar* buffer)
{
	this->reserve(::strlen(buffer));
	*this += buffer;
}

MLString::~MLString() = default;

MLString& MLString::operator+=(const MLString text)
{
	*this += text.mData;
	return *this;
}

MLString& MLString::operator=(const MLChar* rhs)
{
	this->dispose();
	this->reserve(::strlen(rhs));
	
	*this += rhs;

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

void MLString::dispose() noexcept
{
	if (mData)
	{
		MLAllocator::shared().disposeArray(mData);
		mData = nullptr;
	}
}

void MLString::reserve(MLSizeType length) noexcept
{
	if (mData)
		return;

	mCursor = 0;
	mSize	= length;
	mData	= MLAllocator::shared().initArray<MLChar>(mSize);

	memset(mData, 0, mSize);
}

const MLString MLString::toString()
{
	const auto length_buffer = 4096;

	MLString str(length_buffer);
	str += "['ClassName': 'MLString']";

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
