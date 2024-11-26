/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLUUID.h>
#include <FoundationKit/MLString.h>
#include <uuid/uuid.h>

/***********************************************************************************/
/// @brief UUID class constructor.
/***********************************************************************************/
MLUUID::MLUUID()
{
	uuid_t uuidOut;
	uuid_generate_random(uuidOut);

	MLSizeType indexUuid = 0UL;

	for (; indexUuid < kUUIDMaxLen; ++indexUuid)
	{
		mArray[indexUuid] = uuidOut[indexUuid];
	}
}

/***********************************************************************************/
/// @brief Construct with MLArray of UUID.
/***********************************************************************************/
MLUUID::MLUUID(MLArray<MLUtf8Char, kUUIDMaxLen>& array)
{
	this->mArray = array;
}

/***********************************************************************************/
/// @brief Returns UUID as string.
/***********************************************************************************/
MLString MLUUID::uuidAsString()
{
	MLChar uuidOut[255] = { 0 };

    auto arr = mArray.dataAsUnsafeArray();
	uuid_unparse(arr, uuidOut);

	return MLString(uuidOut);
}

/// @brief Returns UUID as array.
MLArray<MLUtf8Char, kUUIDMaxLen> MLUUID::uuidAsArray()
{
    return mArray;
}
