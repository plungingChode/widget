#include "spinner.hpp"
#include <climits>

using namespace genv;

namespace Controls
{
    Spinner::Spinner(vec2 start, int value, int width, int height, vec2 padding)
        : Label(start, std::to_string(value), width, height, padding),
          value(value),
          min_value(INT_MIN),
          max_value(INT_MAX)
    {
        Control::is_draggable = false;
        Frame::hold_bg = DEFAULT_FOCUS;
        set_spinner_hitboxes();
    }

    void Spinner::set_spinner_hitboxes()
    {
        unsigned &b = border_thickness;
        spin_up_hitbox = rect(vec2(width-17-b, b), 17, height/2-b);
        spin_dn_hitbox = rect(vec2(width-17-b, height/2), 17, height/2-b);
        spin_up_icon = read_kep("uarrow.kep");
        spin_dn_icon = read_kep("dnarrow.kep");

    }

    void Spinner::set_spin_color(const std::string& hex)
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
    }

    int Spinner::get_value() const
    {
        return value;
    }
    
    void Spinner::on_mouse_ev(const event& m, bool btn_held)
    {
        Label::on_mouse_ev(m, btn_held);

        spin = spin_none;
        if (focused)
        {
            vec2 mouse = vec2(m.pos_x, m.pos_y) - start;
            if (m.button == btn_wheelup || 
               (m.button == btn_left && spin_up_hitbox.intersects(mouse)))
            {
                mod_value(+1);
            }
            else if (m.button == btn_wheeldown || 
                    (m.button == btn_left && spin_dn_hitbox.intersects(mouse)))
            {
                mod_value(-1);
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
                mod_value(+1);
                break;

            case key_down:
                mod_value(-1);
                break;

            case key_pgup:
                mod_value(+10);
                break;

            case key_pgdn:
                mod_value(-10);
                break;

            default:
                spin = spin_none;
                schedule_update();
                break;  
            }
        }
    }

    void Spinner::render()
    {
        Label::render();
        genv::color btn_border = text_fill_normal;
        genv::color btn_up_bg = normal_bg;
        genv::color btn_dn_bg = normal_bg;

        if (spin == spin_down)
        {
            btn_dn_bg = spin_color;
        }
        else if (spin == spin_up)
        {
            btn_up_bg = spin_color;
        }

        rect &up = spin_up_hitbox;
        rendered << move_to(up.start.x, up.start.y)
                 << btn_border
                 << box(up.width, up.height)
                 << move_to(up.start.x + 1, up.start.y + 1)
                 << btn_up_bg
                 << box(up.width - 2, up.height - 2)
                 << stamp(spin_up_icon, up.start.x + 3, up.start.y + up.height/2 - 3);

        rect &dn = spin_dn_hitbox;
        rendered << move_to(dn.start.x, dn.start.y)
                 << btn_border
                 << box(dn.width, dn.height)
                 << move_to(dn.start.x + 1, dn.start.y + 1)
                 << btn_dn_bg
                 << box(dn.width - 2, dn.height - 2)
                 << stamp(spin_dn_icon, dn.start.x + 3, dn.start.y + dn.height/2 - 3);
    }
}