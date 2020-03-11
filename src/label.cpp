#include "label.hpp"

using namespace genv;

namespace Controls
{
    Label::Label(Point start, const std::string& text, int width, int height, Point content_offset)
        : text_fill_normal(DEFAULT_TEXT_NORMAL),
          text_fill_focused(DEFAULT_TEXT_FOCUS),
          text(text),
          content_offset(content_offset),
          Frame(start, width, height)
    {
        Frame::border_thickness = 1;
        Control::is_hittest_visible = false;
    }

    void Label::set_content_offset(Point p)
    {
        content_offset = p;
        update_visuals();
    }

    void Label::set_text(const std::string& text)
    {
        this->text = text;
        update_visuals();
    }

    void Label::set_text_fill_normal(const std::string& hex)
    {
        set_color(text_fill_normal, hex);
    }

    void Label::set_font(const std::string& font_src)
    {
        rendered.load_font(font_src);
        this->font_src = font_src;
    }

    void Label::render()
    {
        Frame::render();
        if (text.empty()) return;

        if (_is_focused)
        {   
            // std::cout << "rendering text '" << text << "'\n";
            rendered << move_to(content_offset.x, content_offset.y)
                     << text_fill_focused << genv::text(text);
        }
        else
        {
            // std::cout << "rendering text '" << text << "'\n";
            rendered << move_to(content_offset.x, content_offset.y)
                     << text_fill_normal << genv::text(text);
        }
    }

    void Label::on_mouse_ev(const event& m, const bool btn_held)
    {
        Frame::on_mouse_ev(m, btn_held);
        if (_size_changed)
        {
            // std::cout << "Reload font\n";
            rendered.load_font(font_src);
        }
    }
}