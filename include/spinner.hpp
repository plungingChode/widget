#ifndef SPINNER_HPP_INCLUDED
#define SPINNER_HPP_INCLUDED

#include "label.hpp"

namespace Controls
{
    struct Spinner : public Label
    {
    private:
        void set_spinner_hitboxes();

    protected:
        enum SpinAction
        {
            spin_none, spin_up, spin_down
        };
        SpinAction spin;

        int value;
        rect spin_up_hitbox;
        rect spin_dn_hitbox;

        genv::canvas spin_up_icon;
        genv::canvas spin_dn_icon;

        vec2 up_icon_pos;
        vec2 dn_icon_pos;

        genv::color spin_color = DEFAULT_MOUSEDOWN;

        void update() override;

    public:
        int min_value;
        int max_value;

        Spinner(vec2 start, int value, int width, int height, vec2 padding, std::string font = "", int font_size = 16);
        Spinner(vec2 start, int value, int width, std::string font = "", int font_size = 16);

        void set_spin_color(const std::string& hex);
        void set_border_thickness(unsigned thickness) override;

        void set_value(int val);
        void mod_value(int d);
        int get_value() const;
        
        void on_mouse_ev(const genv::event &mouse_ev, bool btn_held = false) override;
        void on_key_ev(const genv::event &key_ev, int key_held = false) override;
    };
}

#endif