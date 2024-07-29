/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/MLAllocator.hxx>

MLAllocator::MLAllocator() = default;
MLAllocator::~MLAllocator() { delete this; }

/// @brief Get allocator singleton.
/// @return the allocator reference.
MLAllocator& MLAllocator::shared()
{
	static MLAllocator* alloc = nullptr;

	if (!alloc)
	{
		alloc = new MLAllocator();
	}

	return *alloc;
}

/// @brief Get allocator string.
/// @return the allocator as a string.
const MLString MLAllocator::toString()
{
    const auto cLen = 512;

	MLString str = MLString(cLen);
	str += "{'name': 'MLAllocator'}";

	return str;
}
