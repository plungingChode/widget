#ifndef VEC2_HPP_INCLUDED
#define VEC2_HPP_INCLUDED

namespace Controls
{
    struct vec2
    {
        int x, y;
        vec2(int x, int y);
        vec2();

        double len() const;
        
        vec2& operator+=(const vec2& rhs);
        vec2& operator-=(const vec2& rhs);
        vec2& operator*=(int scalar);
        vec2& operator/=(int scalar);
        friend vec2 operator-(const vec2& lhs, const vec2& rhs);
        friend vec2 operator+(const vec2& lhs, const vec2& rhs);
        friend vec2 operator*(const vec2& v, int scalar);
        friend vec2 operator*(int scalar, const vec2& v);
        friend vec2 operator/(const vec2& v, int scalar);
        friend vec2 operator/(int scalar, const vec2& v);
    };
}

#endif