#include "button.hpp"

using namespace genv;

namespace Controls
{
    Button::Button(vec2 start, const std::string& text, void (*action)(), int width, int height, vec2 content_offset)
        : Label(start, text, width, height, content_offset), action(action)
    {
        Frame::rendered.transparent(true);
        Control::is_draggable = false;
        Control::is_hittest_visible = true;
    }

    void Button::on_mouse_ev(const event& m, const bool btn_held)
    {
        // std::cout << "held: " << _is_held << "btn: " << m.button <<  '\n';
        if (m.button == -btn_left && is_held_ && is_hovered_)
        {
            action();
        }
        Label::on_mouse_ev(m, btn_held);
        if (size_changed_)
        {
            rendered.transparent(true);
        }
    }

    void Button::render()
    {
        if (is_held_)
        {
            fill = hold_bg;
        }
        else if (is_focused_)
        {
            fill = focus_bg;
        }
        else if (is_hovered_)
        {
            fill = hover_bg;
        }
        else
        {
            fill = normal_bg;
        }

        unsigned int& b = border_thickness;
        vec2& o = content_offset;

        // leave gap for bevel effect
        rendered 
            << move_to(0, 0) << BLACK << box(width, height)
            << move_to(0, 0) << fill << box(width - b, height - b);

        if (is_held_)
        {
            // bevel on the bottom right, push in text
            rendered 
                << move_to(1, height-b) << border << box(width-1, b)
                << move_to(width-b, 1) << border << box(b, height-1)
                << move_to(o.x + b+1, o.y + b+1) << text_fill_normal << genv::text(text);
        }
        else
        {
            // bevel on the top left
            rendered 
                << move_to(0, 0) << border << box(width-b, b)
                << move_to(0, 0) << border << box(b, height-b)
                << move_to(o.x, o.y) << text_fill_normal << genv::text(text);
        }
        if(is_resizable_)
        {
            render_resize_area();
        }
    }
}