#pragma once
#include "Pizza.h"

template <typename T>
T get(const VectorOfVector<T> v, int row, int col)
{
	if (row < 0 || col < 0)
	{
		return 0;
	}

	return v.at(row).at(col);
}

template <typename T>
VectorOfVector<T> SAT(const VectorOfVector<T>& input)
{
	VectorOfVector<T> result = input;

	for (int i = 0; i < result.size(); ++i)
	{
		auto& row = result.at(i);

		for (int j = 0; j < row.size(); ++j)
		{
			T ele = get(result, i, j)
				+ get(result, i - 1, j)
				+ get(result, i, j - 1)
				- get(result, i - 1, j - 1);

			row[j] = ele;
		}
	}

	return result;
}