#include "button.hpp"

using namespace genv;

namespace Controls
{
    Button::Button(vec2 start, void (*action)(), std::string text, int width, int height, vec2 padding, std::string font, int font_size)
        : Label(start, text, width, height, padding, font, font_size), action(action)
    {
        // Frame::rendered.transparent(true);
        Control::draggable = false;
        Control::hittest_visible = true;
    }

    Button::Button(vec2 start, void (*action)(), std::string text, int width, vec2 padding, std::string font, int font_size)
        : Label(start, text, width, padding, font, font_size), action(action)
    {
        // Frame::rendered.transparent(true);
        Control::draggable = false;
        Control::hittest_visible = true;
    }

    Button::Button(vec2 start, void (*action)(), std::string text, int width, std::string font, int font_size)
        : Label(start, text, width, font, font_size), action(action)
    {
        Frame::rendered.transparent(true);
        Control::draggable = false;
        Control::hittest_visible = true;
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
        if (size_changed)
        {
            rendered.transparent(true);
        }

        rendered 
            << move_to(0, 0) 
            << BLACK 
            << box(width, height);

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
            << box(width-b, height-b);

        int baseline = padding.y;
        if (font.empty()) baseline += rendered.cascent();

        rendered << border;
        if (held)
        {
            // bevel on bottom right, push in text
            rendered 
                << move_to(1, height-b) << box(width-1, b)
                << move_to(width-b, 1) << box(b, height-1)
                << move_to(padding.x+1, baseline+1) 
                << text_fill_normal << genv::text(text);
        }
        else
        {
            // bevel on top left
            rendered 
                << move_to(0, 0) << box(width-b, b)
                << move_to(0, 0) << box(b, height-b)
                << move_to(padding.x, baseline) 
                << text_fill_normal << genv::text(text);
        }

        if(resizable)
        {
            render_resize_area();
        }
    }
}