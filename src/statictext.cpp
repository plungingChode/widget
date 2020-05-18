#include "statictext.hpp"

using namespace genv;

StaticText::StaticText(Scene *s, int x_, int y_, const std::string &text_, const genv::font *f)
    : Control(s, x_, y_, 0, 0, f), text(text_)
{
    Control::hittest_visible = false;
    w = rendered.twidth(text);
    h = rendered.cascent() + rendered.cdescent() + 1;
    rendered.open(w, h);
    set_font(f);
    rendered.transparent(true);
}

void StaticText::update()
{
    int y_offset = font ? 0 : rendered.cascent();
    rendered 
        << move_to(0, y_offset)
        << text_color
        << genv::text(text);
}
