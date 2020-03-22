#ifndef RECT_HPP_INCLUDED
#define RECT_HPP_INCLUDED

#include "vec2.hpp"

namespace Controls
{
    struct rect
    {
        vec2 start;
        unsigned int width, height;

        rect(vec2 start, int width, int height);
        rect(int width, int height);
        rect();

        bool intersects(const vec2& point) const;
        bool intersects(int x, int y) const;
        bool intersects(const rect& rect) const;
    };
}

#endif