/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

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
	MLString str = MLString("['ClassName': 'MLAllocator']");
	return str;
}
