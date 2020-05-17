#ifndef RECT_HPP_INCLUDED
#define RECT_HPP_INCLUDED

#include "vec2.hpp"

struct rect
{
    int x, y;
    int w, h;

    rect(int x, int y, int width, int height);
    rect(vec2 start, int width, int height);
    rect(int width, int height);
    rect();

    bool intersects(const vec2& point) const;
    bool intersects(int x, int y) const;
    bool intersects(const rect& rect) const;
};

#endif
