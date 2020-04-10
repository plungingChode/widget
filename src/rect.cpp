#include "rect.hpp"

namespace Controls
{
    rect::rect(vec2 start, int width, int height)
        : start(start), 
          width(width), 
          height(height)
    {}

    rect::rect(int width, int height)
        : start(0, 0),
          width(width), 
          height(height)
    {}

    rect::rect() : rect(0, 0)
    {}

    bool rect::intersects(const vec2& p) const
    {
        return start.x <= p.x && start.x+width >= (unsigned)p.x &&
               start.y <= p.y && start.y+height>= (unsigned)p.y;
    }

    bool rect::intersects(int x, int y) const
    {
         return start.x <= x && start.x+width >= (unsigned)x &&
                start.y <= y && start.y+height>= (unsigned)y;
    }

    bool rect::intersects(const rect& r) const
    {
        return start.x+width >= (unsigned)r.start.x 
            && r.start.x+r.width >= (unsigned)start.x
            && start.y+height>= (unsigned)r.start.y 
            && r.start.y+r.height>= (unsigned)start.y;
    }
}