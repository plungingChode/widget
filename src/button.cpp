#include "button.hpp"
#include "scene.hpp"

using namespace genv;

namespace Controls
{
    Button::Button(Scene *s, int x_, int y_, int a, const std::string &text_, int w_, int h_, vec2 pad, const genv::font *f)
        : Label(s, x_, y_, text_, w_, h_, pad, f), action(a)
    {
        if (font) Control::rendered.transparent(true);
        Control::draggable = false;
        Control::hittest_visible = true;
    }

    Button::Button(Scene *s, int x_, int y_, int a, const std::string &text_, int w_, vec2 pad, const genv::font *f)
        : Label(s, x_, y_, text_, w_, pad, f), action(a)
    {
        if (font) Control::rendered.transparent(true);
        Control::draggable = false;
        Control::hittest_visible = true;
    }

    Button::Button(Scene *s, int x_, int y_, int a, const std::string &text_, int w_, const genv::font *f)
        : Label(s, x_, y_, text_, w_, f), action(a)
    {
        if (font) Control::rendered.transparent(true);
        Control::draggable = false;
        Control::hittest_visible = true;
    }

    void Button::set_font(const genv::font *f)
    {
        Label::set_font(f);
        if (!f)
        {
            rendered.transparent(false);
        }
    }


    void Button::on_mouse_ev(const event& m, bool btn_held)
    {
        if (m.button == -btn_left && held && hovered)
        {
            owner->action(action);
        }
        Label::on_mouse_ev(m, btn_held);
    }

    void Button::update()
    {
        if (size_changed && font)
        {
            rendered.transparent(true);
        }

        rendered 
            << move_to(0, 0) 
            << BLACK 
            << box(w, h);

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

        unsigned int b = border_thickness;

        // draw background
        rendered 
            << move_to(0, 0) 
            << box(w-b, h-b);

        int baseline = padding.y;
        if (!font) baseline += rendered.cascent();

        rendered << border;
        if (held)
        {
            // bevel on bottom right, push in text
            rendered 
                << move_to(1, h-b) << box(w-1, b)
                << move_to(w-b, 1) << box(b, h-1)
                << move_to(padding.x+1, baseline+1) 
                << text_fill_normal << genv::text(text);
        }
        else
        {
            // bevel on top left
            rendered 
                << move_to(0, 0) << box(w-b, b)
                << move_to(0, 0) << box(b, h-b)
                << move_to(padding.x, baseline) 
                << text_fill_normal << genv::text(text);
        }

        if(resizable)
        {
            render_resize_area();
        }
    }
}