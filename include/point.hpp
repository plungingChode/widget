#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED

namespace Controls
{
    struct Point
    {
        int x, y;
        Point(int x, int y);
        Point();
        
        void operator+=(const Point& rhs);
        void operator-=(const Point& rhs);
        friend Point operator-(const Point& lhs, const Point& rhs);
        friend Point operator+(const Point& lhs, const Point& rhs);
    };
}

#endif