#include "checkbox.hpp"

using namespace genv;

CheckBox::CheckBox(Scene *s, int x_, int y_, const std::string &caption_, const genv::font *f)
    : Frame(s, x_, y_, 0, 0, f), checked(false), update_caption(true), caption(caption_), check_box(0, 0, 19, 19)
{
    Control::resizable = false;
    Control::draggable = false;

    check_mark = read_matrix(CHECK_MARK, border);

    h = 20;
    if (font)
    {
        h = std::max(h, font->font_size);
    }
    w = check_box.w + 7 + rendered.twidth(caption);
    check_box.y = h/2 - check_box.h/2;

    rendered.open(w, h);
    set_font(font);

    rendered.transparent(true);
}

void CheckBox::set_border_color(int hex)
{
    Frame::set_border_color(hex);
    check_mark = read_matrix(CHECK_MARK, border);
}

void CheckBox::update()
{
    rendered
        << border
        << move_to(check_box.x, check_box.y)
        << box(check_box.w, check_box.h);

    if (held)
    {
        rendered << hold_bg;
    }
    else if (focused)
    {
        rendered << focus_bg;
    }
    else if (hovered)
    {
        rendered << hover_bg;
    }
    else
    {
        rendered << normal_bg;
    }

    rendered
        << move_to(check_box.x + 1, check_box.y + 1)
        << box(check_box.w - 2, check_box.h - 2);

    if (checked)
    {
        rendered << stamp(check_mark, check_box.x+3, check_box.y+3);
    }

    if (update_caption)
    {
        int baseline = -10;
        if (!font) baseline += rendered.cascent()+2;

        rendered 
            << text_color
            << move_to(check_box.w + 7, h/2+baseline)
            << genv::text(caption);

        update_caption = false;
    }
}

void CheckBox::on_mouse_ev(const event &ev, bool btn_held)
{
    if (held && hovered && ev.button == -btn_left)
    {
        checked = !checked;
    }
    Frame::on_mouse_ev(ev, btn_held);
} 

void CheckBox::on_key_ev(const event &ev, int key_held)
{
    if (focused && (ev.keycode == -key_enter || ev.keycode == -key_space))
    {
        checked = !checked;
        schedule_update();
    }
}