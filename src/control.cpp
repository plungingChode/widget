#include "control.hpp"

namespace Controls
{
    Control::Control(vec2 drag_center, vec2 drag_start)
        : drag_center(drag_center),
          _is_hovered(false), 
          _is_focused(false), 
          _is_held(false),
          _needs_visual_update(true),
          is_hittest_visible(true),
          is_draggable(true),
          _is_dragging(false),
          _is_resizable(false),
          _is_resizing(false),
          _size_changed(false)
    {
    }

    void Control::update_visuals()
    {
        _needs_visual_update = true;
    }

    bool Control::is_focused() const
    {
        return _is_focused;
    }

    bool Control::is_hovered() const
    {
        return _is_hovered;
    }

    bool Control::is_held() const
    {
        return _is_held;
    }

    bool Control::updated() const
    {
        return _needs_visual_update;
    }
}