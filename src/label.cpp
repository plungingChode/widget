#include "label.hpp"

using namespace genv;


Label::Label(Scene *s, int x_, int y_, int w_, int h_, const std::string &tx, const genv::font *f)
    : Frame(s, x_, y_, w_, h_,  f), text(tx)
{
    Frame::border_thickness = 1;
    Control::hittest_visible = false;
}

Label::Label(Scene *s, int x_, int y_, int w_, const std::string &tx, const genv::font *f)
    : Label(s, x_, y_, w_, 0, tx, f)
{
    Control::h = rendered.cascent() + rendered.cdescent() + 10;
    rendered.open(Control::w, Control::h);
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

    int baseline = -10;
    if (!font) baseline += rendered.cascent()+2;

    if (focused)
    {   
        rendered << text_fill_focused;
    }
    else
    {
        rendered << text_fill_normal;
    }

    rendered 
        << move_to(5, h/2+baseline)
        << genv::text(text);
}
