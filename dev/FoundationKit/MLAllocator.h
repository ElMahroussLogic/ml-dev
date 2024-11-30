/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>
#include <FoundationKit/MLString.h>

/// @brief Allocator class.
class MLAllocator final ML_OBJECT
{
public:
	explicit MLAllocator();
	~MLAllocator() override;

	/// @brief init a new pointer from a size.
	/// @param cnt the number of TypeInfo to create.
	/// @return a pointer of it.
	template <typename TypeInfo>
	TypeInfo* initArray(MLSizeType cnt)
	{
		if (!cnt)
			++cnt;

		return new TypeInfo[cnt];
	}

	/// @brief Inits a new class with arguments.
	/// @tparam T
	/// @tparam ...A
	/// @param ...args
	/// @return
	template <typename T, typename... A>
	T* init(A... args)
	{
		return new T(args...);
	}

	/// @brief Dispoes an object.
	template <typename T>
	void dispose(T* obj)
	{
		delete obj;
	}

	/// @brief Dispoes an object.
	template <typename T>
	void disposeArray(T* obj)
	{
		delete[] obj;
	}

	void disposeAllocator() noexcept
	{
		delete this;
	}

public:
	/// @brief Get allocator singleton.
	/// @return the allocator reference.
	static MLAllocator& shared();

	/// @brief Get allocator string.
	/// @return the allocator as a string.
	const MLString toString() override;
};
