/* -------------------------------------------

	Copyright ZKA Web Services Co.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.h>

template <typename T, MLSizeType N>
class MLArray ML_OBJECT
{
public:
	explicit MLArray()
	{
		for (MLSizeType i = 0; i < N; i++)
		{
			if (!fArray[i])
				fArray[i] = T();
		}
	}

	~MLArray() = default;

	MLArray& operator=(const MLArray&) = default;
	MLArray(const MLArray&)			   = default;

	T& operator[](const MLSizeType& At)
	{
		return fArray[At];
	}

	bool isEmpty() const
	{
		return false;
	}

	const MLSizeType capacity()
	{
		return N;
	}

	const MLSizeType count()
	{
		MLSizeType count = 0;

		for (MLSizeType i = 0; i < N; i++)
		{
			if (fArray[i])
				++count;
		}

		return count;
	}

	const T* dataAsUnsafeArray()
	{
		return fArray;
	}

	operator bool()
	{
		return !this->isEmpty();
	}

private:
	T fArray[N];
};
