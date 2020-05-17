#include "vec2.hpp"

vec2::vec2(int x_, int y_) : x(x_), y(y_) {}
vec2::vec2() : x(0), y(0) {}

vec2& vec2::operator+=(const vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}
vec2& vec2::operator-=(const vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}
vec2& vec2::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}
vec2& vec2::operator/=(int scalar)
{
    x /= scalar;
    y /= scalar;
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
