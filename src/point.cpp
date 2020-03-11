#include "point.hpp"

namespace Controls
{
    Point::Point(int x, int y) : x(x), y(y) {};
    Point::Point() : x(0), y(0) {};

    void Point::operator+=(const Point& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
    }
    void Point::operator-=(const Point& rhs)
    {
        this->x -= rhs.x;
        this->y += rhs.y;
    }
    Point operator+(const Point& lhs, const Point& rhs)
    {
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    Point operator-(const Point& lhs, const Point& rhs)
    {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }
}