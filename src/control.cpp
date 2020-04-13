#include "control.hpp"
#include "scene.hpp"

namespace Controls
{
    Control::Control(Scene *s, int x, int y, int w, int h, const genv::font *f)
        : rect(x, y, w, h),
          rendered(w, h),
          hovered(false), 
          focused(false), 
          held(false),
          resizable(false),
          resizing(false),
          size_changed(false),
          needs_update(true),
          dragged(false),
          drag_center(vec2(0, 0)),
          owner(s),
          font(f),
          hittest_visible(true),
          draggable(true)
    {
        s->add_control(this);
        set_font(f);
    }

    void Control::set_font(const genv::font *f)
    {
        if (f && rendered.load_font(f->font_name, f->font_size))
        {
            this->font = f;
        }
        else
        {
            this->font = nullptr;
        }
        schedule_update();
    }
}