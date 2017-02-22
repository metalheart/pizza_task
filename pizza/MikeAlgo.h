#pragma once
#include "Pizza.h"

std::vector<Slice> get_by_simple_rects(const Pizza<IngradientType>& pizza, int w, int h)
{
    int xmax = (int)pizza.data[0].size();
    int ymax = (int)pizza.data.size();
    std::vector<Slice> result;
    auto checkPR = [&](const Slice & s)
    {
        size_t tmcnt = pizza.ingridient_count(IngradientType::Tomato, s);
        size_t mshcnt = pizza.ingridient_count(IngradientType::Mashroom, s);
        if ((tmcnt >= pizza.min_ingradients) && (mshcnt >= pizza.min_ingradients))
        {
            result.emplace_back(s);
        }
    };

    int i = 0, j = 0;
    for(i = 0; i + w <= xmax; i += w)
        for (j = 0; j + h <= ymax; j += h)
        {
            Slice s(Point(i, j), Point(i + w - 1, j + h - 1));
            checkPR(s);
        }

    if (i < xmax - 1)
    {
        for (int y = 0; y + h <= ymax; y += h)
        {
            Slice s(Point(i, y), Point(xmax - 1, y + h - 1));
            checkPR(s);
        }
    }
    if (j < ymax - 1)
    {
        for (int x = 0; x + w <= xmax; x += w)
        {
            Slice s(Point(x, j), Point(x + w - 1, ymax - 1));
            checkPR(s);
        }
    }


    if ( (i < xmax - 1) && (j < ymax - 1) )
    {
        Slice s(Point(i, j), Point(xmax - 1, ymax - 1));
        checkPR(s);
    }


    return result;
}