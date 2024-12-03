/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

/// @brief ML String class.
/// @todo SIMD support.
class MLString final ML_OBJECT
{
private:
	MLChar*	   mData{nullptr};
	MLSizeType mCursor, mSize;

public:
	explicit MLString(MLSizeType sizeOfBuffer);
	explicit MLString(const MLChar* buffer);

	~MLString() override;

	MLString& operator=(const MLString& rhs);
	MLString& operator=(const MLChar* rhs);
	MLString(const MLString& rhs);

	MLString& operator+=(const MLChar chr);
	MLString& operator+=(const MLChar* text);
	MLString& operator+=(const MLString text);

	MLSizeType usedBytes();
	MLSizeType size();

	MLChar*		  asBytes();
	const MLChar* asConstBytes() const;

	void dispose() noexcept;
	void reserve(MLSizeType length) noexcept;

	MLChar& operator[](MLSizeType index);

	const MLString toString() override;
};

enum
{
	MLUnicodeStringEncodig = 0,
	MLASCIIStringEncoding,
	MLZKAOSStringEncoding,
};
