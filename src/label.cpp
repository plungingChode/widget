#include "label.hpp"

using namespace genv;

namespace Controls
{
    Label::Label(Scene *owner, vec2 start, std::string text, int width, int height, vec2 padding, std::string font, int font_size)
        : Frame(owner, start, width, height),
          padding(padding),
          text(text)
    {
        set_font(font, font_size);
        Frame::border_thickness = 1;
        Control::hittest_visible = false;
    }

    Label::Label(Scene *owner, vec2 start, std::string text, int width, vec2 padding, std::string font, int font_size)
        : Frame(owner, start, width, 0),
          padding(padding),
          text(text)
    {
        set_font(font, font_size);
        Frame::border_thickness = 1;
        Frame::height = rendered.cascent() + rendered.cdescent() + 10;
        rendered.open(Frame::width, Frame::height);
        Control::hittest_visible = false;
    }


    Label::Label(Scene *owner, vec2 start, std::string text, int width, std::string font, int font_size)
        : Label(owner, start, text, width, vec2(5, 5), font, font_size)
    {
    }

    void Label::set_padding(vec2 p)
    {
        padding = p;
        schedule_update();
    }

    void Label::set_text(std::string text)
    {
        this->text = text;
        schedule_update();
    }

    void Label::set_font(std::string font, int font_size)
    {
        if (rendered.load_font(font, font_size))
        {
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

        if (size_changed)
        {
            set_font(font, font_size);
        }
        
        if (text.empty()) return;

        int baseline = padding.y;
        if (font.empty()) baseline += rendered.cascent();

        if (focused)
        {   
            rendered << text_fill_focused;
        }
        else
        {
            rendered << text_fill_normal;
        }

        rendered 
            << move_to(padding.x, baseline)
            << genv::text(text);
    }
}