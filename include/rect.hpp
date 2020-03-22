#ifndef RECT_HPP_INCLUDED
#define RECT_HPP_INCLUDED

#include "point.hpp"

namespace Controls
{
    struct rect
    {
    public:
        vec2 start, end;
        unsigned int width, height;

        rect(vec2 start, vec2 end);
        rect(vec2 start, int width, int height);
        rect(int width, int height);
        rect();

        vec2 get_start();
        vec2 get_end();
        unsigned int get_width();
        unsigned int get_height();

        bool intersects(vec2 p) const;
        bool intersects(int x, int y) const;
    };
}

#endif