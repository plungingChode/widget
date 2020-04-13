#include "textbox.hpp"

using namespace genv;

namespace Controls
{
    TextBox::TextBox(Scene *owner, int x, int y, const std::string &text_, int w, int h, vec2 pad, const genv::font *f)
        : Label(owner, x, y, text_, w, h, pad, f)
    {
        Control::hittest_visible = true;
    }

    TextBox::TextBox(Scene *owner, int x, int y, const std::string &text_, int w, vec2 pad, const genv::font *f)
        : Label(owner, x, y, text_, w, pad, f)
    {
        Control::hittest_visible = true;
    }

    TextBox::TextBox(Scene *owner, int x, int y, const std::string &text_, int w, const genv::font *f)
        : Label(owner, x, y, text_, w, f)
    {
        Control::hittest_visible = true;
    }

    void TextBox::on_key_ev(const event& key_ev, const int key_held)
    {
        char kc = key_held ? (char)key_held : (char)key_ev.keycode;

        if (kc >= 32 && kc <= 255 && 
            rendered.twidth(text+kc) <= (int)w - 2*padding.x)
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