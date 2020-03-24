#include "control.hpp"

namespace Controls
{
    Control::Control(vec2 drag_center)
        : drag_center(drag_center),
          is_hovered_(false), 
          is_focused_(false), 
          is_held_(false),
          needs_visual_update_(true),
          is_hittest_visible(true),
          is_draggable(true),
          is_dragging_(false),
          is_resizable_(false),
          is_resizing_(false),
          size_changed_(false)
    {
    }

    void Control::update_visuals()
    {
        needs_visual_update_ = true;
    }

    bool Control::is_focused() const
    {
        return is_focused_;
    }

    bool Control::is_hovered() const
    {
        return is_hovered_;
    }

    bool Control::is_held() const
    {
        return is_held_;
    }

    bool Control::updated() const
    {
        return needs_visual_update_;
    }
}