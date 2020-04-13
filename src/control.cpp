#include "control.hpp"
#include "scene.hpp"

namespace Controls
{
    Control::Control(Scene *owner)
        : hovered(false), 
          focused(false), 
          held(false),
          resizable(false),
          resizing(false),
          size_changed(false),
          needs_update(true),
          dragged(false),
          drag_center(vec2(0, 0)),
          owner(owner),
          hittest_visible(true),
          draggable(true)
    {
        owner->add_control(this);
    }
}