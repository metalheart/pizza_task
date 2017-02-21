#include "Pizza.h"

#include <iostream>
#include <fstream>

void output_slices( const std::vector<Slice>& slices ) {
  std::cout << slices.size() << std::endl;
  for ( const auto& s : slices ) {
    std::cout << s.tl.y << " " << s.tl.x << " " << s.br.y << " " << s.br.y << std::endl;
  }
}

std::vector<Slice> get_by_simple_rects( const Pizza<IngradientType>& pizza, size_t w, size_t h )
{
  std::vector<Slice> result;
  return result;
}

int main()
{
	using namespace std;
	Pizza<IngradientType> pizza;

	ifstream input("data.txt");
	input >> pizza;

	auto tomatos = pizza.ingradient_table(IngradientType::Tomato);
  std::vector<Slice> result = get_by_simple_rects( pizza, pizza.max_cells, 1 );
  output_slices( result );

	return 0;
}