/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/MLAllocator.h>

/// @brief Allocator constructor.
MLAllocator::MLAllocator() = default;

/// @brief Allocator desctructor.
MLAllocator::~MLAllocator() = default;

/// @brief Get allocator singleton.
/// @return the allocator reference.
MLAllocator& MLAllocator::shared()
{
	static MLAllocator* alloc = nullptr;

	if (!alloc)
		alloc = new MLAllocator();

	return *alloc;
}

/// @brief Get allocator string.
/// @return the allocator as a string.
const MLString MLAllocator::toString()
{
	const auto cLen = 512;

	MLString str = MLString(cLen);
	str += "['ClassName': 'MLAllocator']";

	return str;
}
