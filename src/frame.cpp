#include "frame.hpp"
#include "scene.hpp"
#include "control_common.hpp"

using namespace genv;

Frame::Frame(Scene *s, int x_, int y_, int w_, int h_, const genv::font *f)
    : Control(s, x_, y_, w_, h_, f),
        border_thickness(10)
{
}

void Frame::set_resizable(bool val)
{
    resizable = val;
    reset_resize_hitbox();
}

void Frame::set_color(color& target, int hex)
{
    target = hex_to_color(hex);
    schedule_update();
}

void Frame::set_border_thickness(int thickness)
{
    border_thickness = thickness;
    schedule_update();
}

void Frame::render_resize_area()
{
    rendered 
        << move_to(resize_hitbox.x, resize_hitbox.y)
        << DEFAULT_TEXT_NORMAL
        << box(resize_hitbox.w, resize_hitbox.h);
}

void Frame::update()
{
    if (size_changed)
    {
        rendered.open(w, h);
        set_font(font);
    }

    // draw border
    rendered 
        << move_to(0, 0) 
        << border << box(w, h);

    // draw interior
    if (held)
    {
        rendered << hold_bg;
    }
    else if (focused)
    {
        rendered << focus_bg;
    }
    else if (hovered)
    {
        rendered << hover_bg;
    }
    else
    {
        rendered << normal_bg;
    }
    
    rendered 
        << move_to(border_thickness, border_thickness) 
        << box(w-2*border_thickness, h-2*border_thickness);

    // draw resize marker
    if (resizable)
    {
        render_resize_area();
    }
}

void Frame::render(canvas& c)
{
    if (resizing)
    {
        c << move_to(x, y)
          << border 
          << box(w, h);
    }
    else
    {
        Control::render(c);
    }
}