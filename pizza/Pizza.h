#pragma once

#include <vector>
#include <algorithm>
#include <iostream>>

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

  size_t ingridient_count( IngradientType, const Slice& slice ) const;

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

	VectorOfVector<C> ingradient_table(const T& type)
	{
		VectorOfVector<C> result;
		result.reserve(data.size());

		for (const auto& row : data)
		{
			std::vector<C> col;
			col.reserve(row.size());

			std::for_each(row.begin(), row.end(), 
				[&col,&type](const T& t)
				{
					col.push_back(t == type ? 1 : 0);
				}
			);

			result.push_back(std::move(col));
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