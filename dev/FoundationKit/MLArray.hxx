/* -------------------------------------------

	Copyright ZKA Web Services Co.

------------------------------------------- */

#pragma once

#include <FoundationKit/Foundation.hxx>

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

	bool Empty() const
	{
		return false;
	}

	const MLSizeType Capacity()
	{
		return N;
	}

	const MLSizeType Count()
	{
		MLSizeType count = 0;

		for (MLSizeType i = 0; i < N; i++)
		{
			if (fArray[i])
				++count;
		}

		return count;
	}

	const T* CData()
	{
		return fArray;
	}

	operator bool()
	{
		return !Empty();
	}

private:
	T fArray[N];
};
