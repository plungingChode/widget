#include "spinner.hpp"
#include <climits>

using namespace genv;

Spinner::Spinner(Scene *s, int x_, int y_, int w_, int h_, int val, int min_val, int max_val, const genv::font *f)
    : Label(s, x_, y_,  w_, h_, std::to_string(val), f),
        spin(spin_none),
        value(val),
        min_value(min_val),
        max_value(max_val)
{
    Control::draggable = false;
    Control::hittest_visible = true;
    Frame::hold_bg = DEFAULT_BACKGROUND_FOCUS;

    spin_up_icon = read_matrix(UP_ARROW, spin_btn_color);
    spin_dn_icon = read_matrix(DOWN_ARROW, spin_btn_color);

    set_spinner_hitboxes();
}

void Spinner::set_spinner_hitboxes()
{
    const int hb_width  = 17;
    const int hb_height = h/2-border_thickness;
    const int hb_x = w-hb_width-border_thickness;

    spin_up_hitbox = rect(vec2(hb_x, border_thickness), hb_width, hb_height-1);
    spin_dn_hitbox = rect(vec2(hb_x, h/2), hb_width, hb_height);
}

void Spinner::set_spin_btn_color(int hex)
{
    spin_up_icon = read_matrix(UP_ARROW, border);
    spin_dn_icon = read_matrix(DOWN_ARROW, border);    
}

void Spinner::set_spin_color(int hex)
{
    set_color(spin_color, hex);
}

void Spinner::set_value(int val)
{     
    value = std::max(std::min(val, max_value), min_value);
    set_text(std::to_string(value));
}

void Spinner::mod_value(int d)
{
    set_value(value+d);

    if (d > 0) spin = spin_up;
    else if (d < 0) spin = spin_down;
    else spin = spin_none;

    schedule_update();
}

int Spinner::get_value() const
{
    return value;
}

void Spinner::set_border_thickness(int thickness)
{
    Frame::set_border_thickness(thickness);
    set_spinner_hitboxes();
    schedule_update();
}

void Spinner::on_mouse_ev(const event& m, bool btn_held)
{
    Label::on_mouse_ev(m, btn_held);

    spin = spin_none;
    if (focused)
    {
        vec2 m_rel = vec2(m.pos_x-x, m.pos_y-y);

        if (m.button == btn_wheelup || 
            (m.button == btn_left && spin_up_hitbox.intersects(m_rel)))
        {
            mod_value(+diff_small);
        }
        else if (m.button == btn_wheeldown || 
                (m.button == btn_left && spin_dn_hitbox.intersects(m_rel)))
        {
            mod_value(-diff_small);
        }
    }
}

void Spinner::on_key_ev(const event& k, int key_held)
{
    int kc = key_held ? key_held : k.keycode;

    if (focused)
    {
        switch (kc)
        {
        case key_up:
            mod_value(+diff_small);
            break;

        case key_down:
            mod_value(-diff_small);
            break;

        case key_pgup:
            mod_value(+diff_big);
            break;

        case key_pgdn:
            mod_value(-diff_big);
            break;

        default:
            spin = spin_none;
            schedule_update();
            break;  
        }
    }
}

void Spinner::update()
{
    Label::update();

    const rect &up = spin_up_hitbox;
    const rect &dn = spin_dn_hitbox;

    // button borders
    rendered 
        << border
        << move_to(up.x-1, 0)
        << line(0, h)
        << move_to(dn.x, dn.y-1)
        << line(dn.w, 0);

    // up btn content
    rendered 
        << move_to(up.x, up.y)
        << (spin == spin_up ? spin_color : normal_bg)
        << box(up.w, up.h)
        << stamp(spin_up_icon, up.x+3, up.y+(up.h/2)-3);

    // down btn content
    rendered 
        << move_to(dn.x, dn.y)
        << (spin == spin_down ? spin_color : normal_bg)
        << box(dn.w, dn.h)
        << stamp(spin_dn_icon, dn.x+3, dn.y+(dn.h/2)-3);
}
