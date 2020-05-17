#include "rect.hpp"

rect::rect(vec2 start, int width, int height)
    : x(start.x), y(start.y),
        w(width), h(height)
{
}

rect::rect(int x_, int y_, int width, int height)
    : x(x_), y(y_), w(width), h(height)
{
}

rect::rect(int width, int height)
    : x(0), y(0), w(width), h(height)
{
}

rect::rect() : rect(0, 0)
{
}

bool rect::intersects(const vec2& p) const
{
    return x <= p.x && x+w >= p.x &&
            y <= p.y && y+h>= p.y;
}

bool rect::intersects(int x_, int y_) const
{
        return x <= x_ && x+w >= x_ &&
            y <= y_ && y+h>= y_;
}

bool rect::intersects(const rect& r) const
{
    return x+w >= r.x && r.x+r.w >= x
        && y+h>= r.y && r.y+r.h>= y;
}
