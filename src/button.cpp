#include "button.hpp"
#include "scene.hpp"

using namespace genv;

namespace Controls
{
    Button::Button(Scene *s, int x_, int y_, int w_, const std::string &text_, std::function<void()> a, const genv::font *f)
        : Label(s, x_, y_, w_, text_, f), action(a)
    {
        if (font) Control::rendered.transparent(true);
        Control::draggable = false;
        Control::hittest_visible = true;
    }

    Button::Button(Scene *s, int x_, int y_, int w_, int h_, const std::string &text_, std::function<void()> a, const genv::font *f)
        : Label(s, x_, y_, w_, h_, text_, f), action(a)
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
            action();
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

        // draw background
        rendered 
            << move_to(0, 0) 
            << box(w-border_thickness, h-border_thickness);

        int baseline = -10;
        if (!font) baseline += rendered.cascent()+2;

        rendered << border;
        if (held)
        {
            // bevel on bottom right, push in text
            rendered 
                << move_to(1, h-border_thickness) << box(w-1, border_thickness)
                << move_to(w-border_thickness, 1) << box(border_thickness, h-1);
        }
        else
        {
            // bevel on top left
            rendered 
                << move_to(0, 0) << box(w-border_thickness, border_thickness)
                << move_to(0, 0) << box(border_thickness, h-border_thickness);
        }
        // text in the middle
        rendered << move_to(w/2-rendered.twidth(text)/2+held, h/2+baseline+held)
                 << text_fill_normal << genv::text(text); 

        if(resizable)
        {
            render_resize_area();
        }
    }
}