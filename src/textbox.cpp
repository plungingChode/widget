#include "textbox.hpp"

using namespace genv;

TextBox::TextBox(Scene *s, int x_, int y_, const std::string &text_, int w_, const genv::font *f)
    : Label(s, x_, y_, w_, text_, f)
{
    Control::hittest_visible = true;
}

void TextBox::on_key_ev(const event& key_ev, const int key_held)
{
    char kc = key_held ? (char)key_held : (char)key_ev.keycode;

    if (kc >= 32 && kc <= 255 && 
        rendered.twidth(text+kc) <= w - 10)
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
        int cursor_x = 5 + rendered.twidth(text) + 2;
        int cursor_y = 5;

        rendered << move_to(cursor_x, cursor_y)
                    << text_fill_focused
                    << line(0, rendered.cascent() + rendered.cdescent());
    }
}
