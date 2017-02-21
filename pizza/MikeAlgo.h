#pragma once
#include "Pizza.h"

std::vector<Slice> get_by_simple_rects(const Pizza<IngradientType>& pizza, size_t w, size_t h)
{
    std::vector<Slice> result;
    for(size_t i = 0; i < pizza.data[0].size(); i += w - 1)
        for (size_t j = 0; j < pizza.data.size(); i += w - 1)
        {
            Point p1 = Point(i, j);
            Point p2 = Point(i + w, j + h);
            size_t tmcnt = pizza.ingridient_count(IngradientType::Tomato, Slice(p1, p2));
            size_t mshcnt = pizza.ingridient_count(IngradientType::Mashroom, Slice(p1, p2));
            if ((tmcnt >= pizza.min_ingradients) && (mshcnt >= pizza.min_ingradients))
            {
                result.push_back(Slice(p1, p2));
            }
        }

    return result;
}