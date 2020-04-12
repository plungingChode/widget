#include "spinner.hpp"
#include <climits>

using namespace genv;

namespace Controls
{
    Spinner::Spinner(vec2 start, int value, int min_value, int max_value, int width, int height, vec2 padding, std::string font, int font_size)
        : Label(start, std::to_string(value), width, height, padding, font, font_size),
          spin(spin_none),
          value(value),
          min_value(min_value),
          max_value(max_value)
    {
        Control::draggable = false;
        Control::hittest_visible = true;
        Frame::hold_bg = DEFAULT_FOCUS;
        set_spinner_hitboxes();
    }

    Spinner::Spinner(vec2 start, int value, int min_value, int max_value, int width, std::string font, int font_size)
        : Label(start, std::to_string(value), width, font, font_size),
          spin(spin_none),
          value(value),
          min_value(min_value),
          max_value(max_value)
    {
        Control::draggable = false;
        Control::hittest_visible = true;
        Frame::hold_bg = DEFAULT_FOCUS;
        set_spinner_hitboxes();
    }

    Spinner::Spinner(vec2 start, int value, int width, int height, vec2 padding, std::string font, int font_size)
        : Spinner(start, value, INT_MIN, INT_MAX, width, height, padding, font, font_size)
    {
    }

    Spinner::Spinner(vec2 start, int value, int width, std::string font, int font_size)
        : Spinner(start, value, INT_MIN, INT_MAX, width, font, font_size)
    {
    }

    void Spinner::set_spinner_hitboxes()
    {
        const int hb_width  = 17;
        const int hb_height = height/2-border_thickness;
        const int hb_x = width-hb_width-border_thickness;

        spin_up_hitbox = rect(vec2(hb_x, border_thickness), hb_width, hb_height-1);
        spin_dn_hitbox = rect(vec2(hb_x, height/2), hb_width, hb_height);
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

    void Spinner::set_border_thickness(unsigned int thickness)
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
            vec2 m_rel = vec2(m.pos_x-start.x, m.pos_y-start.y);

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
            << move_to(up.start.x-1, 0)
            << line(0, height)
            << move_to(dn.start.x, dn.start.y-1)
            << line(dn.width, 0);

        // up btn content
        rendered 
            << move_to(up.start.x, up.start.y)
            << (spin == spin_up ? spin_color : normal_bg)
            << box(up.width, up.height)
            << stamp(spin_up_icon, up.start.x+3, up.start.y+(up.height/2)-3);

        // down btn content
        rendered 
            << move_to(dn.start.x, dn.start.y)
            << (spin == spin_down ? spin_color : normal_bg)
            << box(dn.width, dn.height)
            << stamp(spin_dn_icon, dn.start.x+3, dn.start.y+(dn.height/2)-3);
    }
}