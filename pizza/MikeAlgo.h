#pragma once
#include "Pizza.h"

std::vector<Slice> get_by_simple_rects(const Pizza<IngradientType>& pizza, size_t w, size_t h)
{
    size_t i = 0, j = 0;
    std::vector<Slice> result;
    while (i < pizza.data[0].size())
    {
        while (j < pizza.data.size())
        {
            Point p1 = Point(i, j);
            Point p2 = Point(i + w, j + h);
            size_t tmcnt = pizza.ingridient_count(IngradientType::Tomato, Slice(p1, p2));
            size_t mshcnt = pizza.ingridient_count(IngradientType::Mashroom, Slice(p1, p2));
            if ((tmcnt < pizza.min_ingradients) && (mshcnt < pizza.min_ingradients))
            {
                result.push_back(Slice(p1, p2));
            }
            i += w;
            j += h;
        }
    }

    return result;
}