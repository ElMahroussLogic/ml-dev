/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLArray.h>
#include <uuid/uuid.h>

#define kUUIDMaxLen 16

class MLUUID final ML_OBJECT
{
	MLArray<MLUtf8Char, kUUIDMaxLen> mArray;

public:
	explicit MLUUID();
	explicit MLUUID(MLArray<MLUtf8Char, kUUIDMaxLen>& array);

	MLString						 uuidAsString();
	MLArray<MLUtf8Char, kUUIDMaxLen> uuidAsArray();
};
