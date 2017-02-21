#include "Pizza.h"
#include "MaxAlgo.h"
#include "MikeAlgo.h"

#include <iostream>
#include <fstream>


void output_slices( std::ostream& os, const std::vector<Slice>& slices ) {
  os << slices.size() << std::endl;
  for ( const auto& s : slices ) {
    os << s.tl.y << " " << s.tl.x << " " << s.br.y << " " << s.br.x << std::endl;
  }
}

size_t slices_area( const std::vector<Slice>& slices ) 
{
  size_t area = 0;
  for ( const auto& s : slices ) {
    area += (s.br.x - s.tl.x + 1) * (s.br.y - s.tl.y + 1);
  }
  return area;
}

int main()
{
	using namespace std;
	Pizza<IngradientType> pizza;

	ifstream input("data.txt");
	input >> pizza;

	auto tomatos = pizza.ingradient_table(IngradientType::Tomato);
  std::vector<std::pair<int, int>> sizes;
  for ( int w = 1; w < pizza.max_cells; ++w ) 
  {
    for ( int h = 1; h < pizza.max_cells / w; ++h ) 
    {
      if ( w * h <= pizza.max_cells && w * h >= pizza.min_ingradients * 2 ) 
      {
        sizes.emplace_back( w, h );
      }
    }
  }
#if 10
  std::vector<Slice> best_result;
  size_t best_area = 0;
  for ( auto size : sizes ) 
  {
    auto result = get_by_simple_rects( pizza, size.first, size.second );
    size_t area = slices_area( result );
    if ( area > best_area ) 
    {
      best_area = area;
      best_result = result;
      std::cout << "New best area: " << best_area << std::endl;
    }
  }

#else
  std::vector<Slice> best_result = get_by_simple_rects( pizza, pizza.max_cells, 1 );
#endif
  std::ofstream os( "best_result.txt" );
  output_slices( os, best_result );


	auto sat = SAT(tomatos);

	return 0;
}