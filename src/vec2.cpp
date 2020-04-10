#include "vec2.hpp"

namespace Controls
{
    vec2::vec2(int x, int y) : x(x), y(y) {}
    vec2::vec2() : x(0), y(0) {}

    vec2& vec2::operator+=(const vec2& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    vec2& vec2::operator-=(const vec2& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    vec2& vec2::operator*=(int scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }
    vec2& vec2::operator/=(int scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    vec2 operator+(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    vec2 operator-(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }
    vec2 operator*(const vec2& v, int scalar)
    {
        return vec2(v.x*scalar, v.y*scalar);
    }
    vec2 operator*(int scalar, const vec2& v)
    {
        return vec2(v.x*scalar, v.y*scalar);
    }
    vec2 operator/(const vec2& v, int scalar)
    {
        return vec2(v.x/scalar, v.y/scalar);
    }
    vec2 operator/(int scalar, const vec2& v)
    {
        return vec2(v.x/scalar, v.y/scalar);
    }
}