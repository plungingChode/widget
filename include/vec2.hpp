#ifndef VEC2_HPP_INCLUDED
#define VEC2_HPP_INCLUDED

namespace Controls
{
    struct vec2
    {
        int x, y;
        vec2(int x, int y);
        vec2();
        
        void operator+=(const vec2& rhs);
        void operator-=(const vec2& rhs);
        friend vec2 operator-(const vec2& lhs, const vec2& rhs);
        friend vec2 operator+(const vec2& lhs, const vec2& rhs);
    };
}

#endif