#include "control.hpp"

namespace Controls
{
    Control::Control(vec2 drag_center)
        : hovered(false), 
          focused(false), 
          held(false),
          resizable(false),
          resizing(false),
          size_changed(false),
          needs_update(true),
          is_dragged(false),
          drag_center(drag_center),
          is_hittest_visible(true),
          is_draggable(true)
    {
    }
}