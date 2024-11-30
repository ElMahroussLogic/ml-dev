/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved.

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

	ML_COPY_DEFAULT(MLArray);

	T& operator[](const MLSizeType& At)
	{
		return fArray[At];
	}

	bool isEmpty() const
	{
		MLSizeType count = 0;

		for (MLSizeType i = 0; i < N; i++)
		{
			if (fArray[i])
				++count;
		}

		return count == 0;
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
