#pragma once
#include "Pizza.h"

std::vector<Slice> get_by_simple_rects(const Pizza<IngradientType>& pizza, size_t w, size_t h)
{
    size_t cw = 0, ch = 0;
    std::vector<Slice> result;
    float gsize = pizza.data[0].size();
    float vsize = pizza.data.size();
    int imax = (gsize / w + 0.5);
    int jmax = (vsize / h + 0.5);
    for (int i = 0; i < imax; ++i)
        for (int j = 0; j < jmax; ++i)
        {
            Point p1 = Point(std::min(i*w, (size_t)gsize), std::min(j*h, (size_t)vsize));
            Point p2 = Point(std::min(i*w, (size_t)gsize), std::min(j*h, (size_t)vsize));
            pizza.ingridient_count(IngradientType::Tomato, Slice(p1, p2));
        }
    return result;
}