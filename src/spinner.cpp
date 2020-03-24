#include "spinner.hpp"
#include <climits>

using namespace genv;

namespace Controls
{
    Spinner::Spinner(vec2 start, int value, int width, int height, vec2 content_offset)
        : Label(start, std::to_string(value), width, height, content_offset),
          min_value(INT_MIN),
          max_value(INT_MAX),
          value(value),
          spin_color(DEFAULT_MOUSEDOWN)
    {
        Control::is_draggable = false;
        Frame::hold_bg = DEFAULT_FOCUS;
        set_spinner_hitboxes();
    }

    void Spinner::set_spinner_hitboxes()
    {
        unsigned int& b = border_thickness;
        spin_up_hitbox = rect(vec2(width - 17 - b, b), width - b, height / 2);
        spin_dn_hitbox = rect(vec2(width - 17 - b, height / 2), width - b, height - b);
        spin_up_icon = read_kep("uarrow.kep");
        spin_dn_icon = read_kep("dnarrow.kep");
    }

    void Spinner::set_spin_color(const std::string& hex)
    {
        set_color(spin_color, hex);
    }

    void Spinner::set_value(const int val)
    {     
        value = std::max(std::min(val, max_value), min_value);
        set_text(std::to_string(value));
    }

    int Spinner::get_value() const
    {
        return value;
    }
    
    void Spinner::on_mouse_ev(const event& m, const bool btn_held)
    {
        Label::on_mouse_ev(m, btn_held);

        spin = spin_none;
        if (is_focused_)
        {
            int value_change = 0;
            if (m.button == btn_wheelup)
            {
                value_change = 1;
            }
            else if (m.button == btn_wheeldown)
            {
                value_change = -1;
            }
            else if (m.button == btn_left)
            {
                // std::cout << "mbutton released\n";
                vec2 mouse = vec2(m.pos_x, m.pos_y) - start;
                if (spin_up_hitbox.intersects(mouse))
                {
                    value_change = 1;
                    spin = spin_up;
                }
                else if (spin_dn_hitbox.intersects(mouse))
                {
                    value_change = -1;
                    spin = spin_down;
                }
            }
            set_value(value+value_change);
        }
    }

    void Spinner::on_key_ev(const event& k, const int key_held)
    {
        // std::cout << "Spin w/ key\n";
        if (is_focused_)
        {
            switch (k.keycode)
            {
            case key_up:
                set_value(value+1);
                break;

            case key_down:
                set_value(value-1);
                break;

            case key_pgup:
                set_value(value+10);
                break;

            case key_pgdn:
                set_value(value-10);
                break;

            default:
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

        rect& r1 = spin_up_hitbox;
        rendered << move_to(r1.start.x, r1.start.y)
                 << btn_border
                 << box(r1.width, r1.height)
                 << move_to(r1.start.x + 1, r1.start.y + 1)
                 << btn_up_bg
                 << box(r1.width - 2, r1.height - 2)
                 << stamp(spin_up_icon, r1.start.x + 3, r1.start.y + r1.height/2 - 3);

        rect& r2 = spin_dn_hitbox;
        rendered << move_to(r2.start.x, r2.start.y)
                 << btn_border
                 << box(r2.width, r2.height)
                 << move_to(r2.start.x + 1, r2.start.y + 1)
                 << btn_dn_bg
                 << box(r2.width - 2, r2.height - 2)
                 << stamp(spin_dn_icon, r2.start.x + 3, r2.start.y + r2.height/2 - 3);
    }
}