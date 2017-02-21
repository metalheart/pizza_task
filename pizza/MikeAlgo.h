#pragma once
#include "Pizza.h"

std::vector<Slice> get_by_simple_rects(const Pizza<IngradientType>& pizza, size_t w, size_t h)
{
    std::vector<Slice> result;
    for( int i = 0; i + w < pizza.data[0].size(); i += w)
        for ( int j = 0; j + h < pizza.data.size(); j += h)
        {
            Slice s(Point(i, j), Point(i + w - 1, j + h - 1));
            size_t tmcnt = pizza.ingridient_count(IngradientType::Tomato, s);
            size_t mshcnt = pizza.ingridient_count(IngradientType::Mashroom, s);
            if ((tmcnt >= pizza.min_ingradients) && (mshcnt >= pizza.min_ingradients))
            {
                result.push_back(s);
            }
        }
    return result;
}