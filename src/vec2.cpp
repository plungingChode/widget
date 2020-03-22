#include "vec2.hpp"

namespace Controls
{
    vec2::vec2(int x, int y) : x(x), y(y) {};
    vec2::vec2() : x(0), y(0) {};

    void vec2::operator+=(const vec2& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
    }
    void vec2::operator-=(const vec2& rhs)
    {
        this->x -= rhs.x;
        this->y += rhs.y;
    }
    vec2 operator+(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    vec2 operator-(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }
}