/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/MLUUID.h>
#include <FoundationKit/MLString.h>
#include <uuid/uuid.h>

MLUUID::MLUUID()
{
	uuid_t uuidOut;
	uuid_generate_random(uuidOut);

	for (MLSizeType indexUuid = 0UL; indexUuid < kUUIDMaxLen; ++indexUuid)
	{
		mArray[indexUuid] = uuidOut[indexUuid];
	}
}

MLString MLUUID::uuidAsString()
{
    MLChar out[255] = { 0 };

    auto arr = mArray.dataAsUnsafeArray();
    uuid_unparse(arr, out);

    return MLString(out);
}

MLArray<MLUtf8Char, kUUIDMaxLen> MLUUID::uuidAsArray()
{
    return mArray;
}
