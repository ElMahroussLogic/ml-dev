/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>

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
	MLString(const MLString& rhs);

	MLString& operator+=(const MLChar chr);
	MLString& operator+=(const MLChar* text);
	MLString& operator+=(const MLString text);

	MLSizeType usedBytes();
	MLSizeType size();

	MLChar*		  asBytes();
	const MLChar* asConstBytes() const;

	void dispose();

	MLChar& operator[](MLSizeType index);

	const MLString toString() override;
};
