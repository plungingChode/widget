#include "label.hpp"

using namespace genv;

namespace Controls
{
    Label::Label(vec2 start, std::string text, int width, int height, vec2 padding, std::string font, int font_size)
        : Frame(start, width, height),
          padding(padding),
          text(text)
    {
        set_font(font, font_size);
        Frame::border_thickness = 1;
        Control::is_hittest_visible = false;
    }

    Label::Label(vec2 start, std::string text, int width, std::string font, int font_size)
        : Frame(start, width, 0),
          padding(vec2(5, 5)),
          text(text)
    {
        set_font(font, font_size);
        Frame::border_thickness = 1;
        Frame::height = rendered.cascent() + rendered.cdescent() + 10;
        rendered.open(Frame::width, Frame::height);
        Control::is_hittest_visible = false;
    }

    void Label::set_content_offset(vec2 p)
    {
        padding = p;
        schedule_update();
    }

    void Label::set_text(std::string text)
    {
        this->text = text;
        schedule_update();
    }

    void Label::set_text_fill_normal(const std::string& hex)
    {
        set_color(text_fill_normal, hex);
    }

    void Label::set_font(std::string font, int font_size)
    {
        if (!font.empty())
        {
            rendered.load_font(font, font_size);
            this->font = font;
            this->font_size = font_size;
        }
        else
        {
            this->font = "";
            this->font_size = 16;
        }
        schedule_update();
    }

    void Label::render()
    {
        // printf("rendering @ %p\n", (void*)this);
        Frame::render();
        if (text.empty()) return;

        if (focused)
        {   
            rendered << move_to(padding.x, padding.y)
                     << text_fill_focused << genv::text(text);
        }
        else
        {
            rendered << move_to(padding.x, padding.y)
                     << text_fill_normal << genv::text(text);
        }
    }

    void Label::on_mouse_ev(const event& m, const bool btn_held)
    {
        Frame::on_mouse_ev(m, btn_held);
        if (size_changed)
        {
            rendered.load_font(font, font_size);
        }
    }
}