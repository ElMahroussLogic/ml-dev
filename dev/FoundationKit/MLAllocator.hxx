/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>
#include <FoundationKit/MLString.hxx>

/// @brief Allocator class.
class MLAllocator final ML_OBJECT
{
public:
	explicit MLAllocator();
	~MLAllocator() override;

	/// @brief init a new pointer from a size.
	/// @param sz the size to give.
	/// @return a pointer of it.
	template <typename TypeInfo>
	TypeInfo* initWithSize(MLSizeType sz)
	{
		if (!sz)
			++sz;

		return new TypeInfo[sz];
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

public:
	/// @brief Get allocator singleton.
	/// @return the allocator reference.
	static MLAllocator& shared();

	/// @brief Get allocator string.
	/// @return the allocator as a string.
	const MLString toString() override;
};
