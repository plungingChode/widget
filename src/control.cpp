#include "control.hpp"
#include "scene.hpp"

bool Control::FORCE_GLOBAL_FONT = false;

Control::Control(Scene *s, int x_, int y_, int w_, int h_, const genv::font *f)
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
        hittest_visible(true),
        draggable(true),
        drag_center(vec2(0, 0)),
        owner(s),
        font(nullptr)
{
    set_font(f);
    s->add_control(this);
}

void Control::set_font(const genv::font *f)
{
    if (FORCE_GLOBAL_FONT && owner)
    {
        f = owner->get_global_font();
    }

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