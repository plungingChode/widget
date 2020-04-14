#include "control.hpp"
#include "scene.hpp"

namespace Controls
{
    Control::Control(int x_, int y_, int w_, int h_, const genv::font *f)
        : rect(x_, y_, w_, h_),
          rendered(w_, h_),
          hovered(false), 
          focused(false), 
          held(false),
          resizable(false),
          resizing(false),
          size_changed(false),
          needs_update(true),
          dragged(false),
          drag_center(vec2(0, 0)),
          owner(nullptr),
          font(f),
          hittest_visible(true),
          draggable(true)
    {
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