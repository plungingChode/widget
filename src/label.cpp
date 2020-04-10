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
        Control::hittest_visible = false;
    }

    Label::Label(vec2 start, std::string text, int width, vec2 padding, std::string font, int font_size)
        : Frame(start, width, 0),
          padding(padding),
          text(text)
    {
        set_font(font, font_size);
        Frame::border_thickness = 1;
        Frame::height = rendered.cascent() + rendered.cdescent() + 10;
        rendered.open(Frame::width, Frame::height);
        Control::hittest_visible = false;
    }


    Label::Label(vec2 start, std::string text, int width, std::string font, int font_size)
        : Label(start, text, width, vec2(5, 5), font, font_size)
    {
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

    void Label::set_text_fill_focused(const std::string& hex)
    {
        set_color(text_fill_focused, hex);
    }

    void Label::set_font(std::string font, int font_size)
    {
        if (!font.empty())
        {
            // printf("loading font %s\n", font.c_str());
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

    void Label::update()
    {
        Frame::update();
        if (text.empty()) return;

        int baseline = padding.y;
        if (font.empty()) baseline += rendered.cascent();

        if (focused)
        {   
            rendered << move_to(padding.x, baseline)
                     << text_fill_focused << genv::text(text);
        }
        else
        {
            rendered << move_to(padding.x, baseline)
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