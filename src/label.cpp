#include "label.hpp"

using namespace genv;

namespace Controls
{
    Label::Label(int x_, int y_, const std::string &tx, int w_, int h_, vec2 pad, const genv::font *f)
        : Frame(x_, y_, w_, h_, f),
          padding(pad),
          text(tx)
    {
        Frame::border_thickness = 1;
        Control::hittest_visible = false;
    }

    Label::Label(int x_, int y_, const std::string &tx, int w_, vec2 pad, const genv::font *f)
        : Frame(x_, y_, w_, 0, f),
          padding(pad),
          text(tx)
    {
        Frame::border_thickness = 1;
        Control::hittest_visible = false;

        Control::h = rendered.cascent() + rendered.cdescent() + 10;
        rendered.open(Control::w, Control::h);
    }


    Label::Label(int x_, int y_, const std::string &tx, int w_, const genv::font *f)
        : Label(x_, y_, tx, w_, vec2(5, 5), f)
    {
    }

    void Label::set_padding(vec2 p)
    {
        padding = p;
        schedule_update();
    }

    void Label::set_text(const std::string &text_)
    {
        this->text = text_;
        schedule_update();
    }

    void Label::update()
    {        
        Frame::update();
        
        if (text.empty()) return;

        int baseline = padding.y;
        if (!font) baseline += rendered.cascent();

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