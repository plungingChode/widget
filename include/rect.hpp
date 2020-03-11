#ifndef RECT_HPP_INCLUDED
#define RECT_HPP_INCLUDED

#include "point.hpp"

namespace Controls
{
    struct Rect
    {
    public:
        Point start, end;
        unsigned int width, height;

        Rect(Point start, Point end);
        Rect(Point start, int width, int height);
        Rect(int width, int height);
        Rect();

        Point get_start();
        Point get_end();
        unsigned int get_width();
        unsigned int get_height();

        bool intersects(Point p) const;
        bool intersects(int x, int y) const;
    };
}

#endif