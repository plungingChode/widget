#include "textbox.hpp"

using namespace genv;

namespace Controls
{
    TextBox::TextBox(Scene *owner, vec2 start, std::string text, int width, int height, vec2 padding, std::string font, int font_size)
        : Label(owner, start, text, width, height, padding, font, font_size)
    {
        Control::hittest_visible = true;
    }

    TextBox::TextBox(Scene *owner, vec2 start, std::string text, int width, vec2 padding, std::string font, int font_size)
        : Label(owner, start, text, width, padding, font, font_size)
    {
        Control::hittest_visible = true;
    }

    TextBox::TextBox(Scene *owner, vec2 start, std::string text, int width, std::string font, int font_size)
        : Label(owner, start, text, width, font, font_size)
    {
        Control::hittest_visible = true;
    }

    void TextBox::on_key_ev(const event& key_ev, const int key_held)
    {
        char kc = key_held ? (char)key_held : (char)key_ev.keycode;

        if (kc >= 32 && kc <= 255 && 
            rendered.twidth(text+kc) <= (int)width - 2*padding.x)
        {
            // visible charcodes: 32 - 255
            text += kc;
            schedule_update();
        }
        if (kc == key_backspace && text.size() > 0)
        {
            text.pop_back();
            schedule_update();
        }
    }

    void TextBox::update()
    {
        Label::update();
        if (focused)
        {
            int cursor_x = padding.x + rendered.twidth(text) + 2;
            int cursor_y = padding.y;

            rendered << move_to(cursor_x, cursor_y)
                     << text_fill_focused
                     << line(0, rendered.cascent() + rendered.cdescent());
        }
    }
}