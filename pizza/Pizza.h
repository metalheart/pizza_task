#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

enum class IngradientType
{
	None = 0,
	Tomato,
	Mashroom
};

IngradientType convert(char c)
{
	switch(c)
	{
	case 'T': return IngradientType::Tomato;
	case 'M': return IngradientType::Mashroom;
	default: return IngradientType::None;
	}
}

template <class T>
using VectorOfVector = std::vector<std::vector<T>>;

struct Point
{
  Point( int x, int y )
    : x( x )
    , y( y ) {
  }

  int x;
  int y;
};

struct Slice
{
  Slice( const Point& tl, const Point& br )
    : tl( tl )
    , br( br ) {
  }

  Point tl;
  Point br;
};

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

template <class T, class C = unsigned char>
struct Pizza
{
	void allocate(size_t row, size_t col)
	{
		data.resize(row);
		std::for_each(data.begin(), data.end(), [&col](std::vector<T>& row) {row.resize(col);});
	}

	// row x column
	VectorOfVector<T> data;
	size_t min_ingradients;
	size_t max_cells;

	C ingridient_count(IngradientType type, const Slice& slice) const
	{
		auto sat = SAT<C>(ingradient_table(type));

		C counts = get(sat, slice.br.y, slice.br.x)
			+ get(sat, slice.tl.y, slice.tl.x)
			- get(sat, slice.tl.y, slice.br.x)
			- get(sat, slice.br.y, slice.tl.x);

		return counts;
	}

	std::vector<T> row(size_t row)
	{
		return data.at(row);
	}

	std::vector<T> col(size_t col)
	{
		std::vector<T> result;
		
		for (const ayot& row : data)
		{
			result.push_back(row.at(col));
		}

		return result;
	}

	VectorOfVector<C> ingradient_table(const T& type) const
	{
		VectorOfVector<C> result;
		result.reserve(data.size());

		for (const auto& row : data)
		{
			std::vector<C> rrow;
			rrow.reserve(row.size());

			std::for_each(row.begin(), row.end(), 
				[&rrow,&type](const T& t)
				{
					rrow.push_back(t == type ? 1 : 0);
				}
			);

			result.push_back(std::move(rrow));
		}

		return result;

	}
};

template <class T, class C>
std::istream& operator >> (std::istream& stream, Pizza<T,C>& pizza)
{
	size_t row = 0, col = 0, min_ingradients = 0, max_cells = 0;
	stream >> row >> col >> min_ingradients >> max_cells;

	pizza.min_ingradients = min_ingradients;
	pizza.max_cells = max_cells;

	char buff[1024];

	stream.ignore();

	while (!stream.eof())
	{
		stream.getline(buff, 1024);

		std::vector<T> row;

		char *ptr = buff;
		while (*ptr)
		{
			row.push_back(convert(*ptr));
			++ptr;
		}

		pizza.data.push_back(std::move(row));
	}

	return stream;
}