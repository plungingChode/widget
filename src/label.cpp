#include "label.hpp"

using namespace genv;

namespace Controls
{
    Label::Label(Scene *s, int x, int y, const std::string &tx, int w, int h, vec2 pad, const genv::font *f)
        : Frame(s, x, y, w, h, f),
          padding(pad),
          text(tx)
    {
        Frame::border_thickness = 1;
        Control::hittest_visible = false;
    }

    Label::Label(Scene *s, int x, int y, const std::string &tx, int w, vec2 pad, const genv::font *f)
        : Frame(s, x, y, w, 0, f),
          padding(pad),
          text(tx)
    {
        Frame::border_thickness = 1;
        Control::hittest_visible = false;

        Control::h = rendered.cascent() + rendered.cdescent() + 10;
        rendered.open(Control::w, Control::h);
    }


    Label::Label(Scene *s, int x, int y, const std::string &tx, int w, const genv::font *f)
        : Label(s, x, y, tx, w, vec2(5, 5), f)
    {
    }

    void Label::set_padding(vec2 p)
    {
        padding = p;
        schedule_update();
    }

    void Label::set_text(const std::string &tx)
    {
        this->text = tx;
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