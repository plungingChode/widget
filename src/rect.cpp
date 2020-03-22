#include "rect.hpp"

namespace Controls
{
    rect::rect(vec2 start, vec2 end) 
        : start(start), end(end),
          width(end.x - start.x), 
          height(end.y - start.y)
    {}

    rect::rect(vec2 start, int width, int height)
        : start(start), 
          end(start.x + width, start.y + height),
          width(width), 
          height(height)
    {}

    rect::rect(int width, int height)
        : start(0, 0), end(width, height),
          width(width), height(height)
    {}

    rect::rect() : rect(0, 0)
    {}

    vec2 rect::get_start() { return start; }
    vec2 rect::get_end() { return end; }
    unsigned int rect::get_width() { return width; }
    unsigned int rect::get_height() { return height; }

    bool rect::intersects(vec2 p) const
    {
        return start.x <= p.x && start.y <= p.y
            && end.x >= p.x && end.y >= p.y;
    }

    bool rect::intersects(int x, int y) const
    {
        return start.x <= x && start.y <= y
            && end.x >= x && end.y >= y;
    }
}