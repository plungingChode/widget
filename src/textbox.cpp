#include "textbox.hpp"

using namespace genv;

namespace Controls
{
    TextBox::TextBox(vec2 start, const std::string& text, int width, int height, vec2 content_offset)
        : Label(start, text, width, height, content_offset)
    {
        Control::is_hittest_visible = true;
        update_cursor();
    }

    void TextBox::update_cursor()
    {
        cursor_pos.x = content_offset.x + rendered.twidth(text);
        cursor_pos.y = content_offset.y;
        cursor_height = rendered.cascent() + rendered.cdescent();
    }

    void TextBox::set_font(const std::string& font_src)
    {
        Label::set_font(font_src);
        update_cursor();
    }

    void TextBox::on_key_ev(const event& key_ev, const int key_held)
    {
        char kc = key_held ? (char)key_held : (char)key_ev.keycode;

        if (kc >= 32 && 
            kc <= 255 && 
            rendered.twidth(text+kc) <= width - 2*content_offset.x)
        {
            // visible charcodes: 32 - 255
            text += kc;
            update_cursor();
            update_visuals();
        }
        if (kc == key_backspace)
        {
            if (text.size() > 0)
            {
                text.resize(text.size() - 1);
            }
            update_cursor();
            update_visuals();
        }
    }

    void TextBox::render()
    {
        Label::render();
        if (is_focused_)
        {
            rendered << move_to(cursor_pos.x + 2, cursor_pos.y)
                     << text_fill_focused
                     << line(0, cursor_height);
        }
    }
}