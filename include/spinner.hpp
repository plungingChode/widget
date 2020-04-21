#ifndef SPINNER_HPP_INCLUDED
#define SPINNER_HPP_INCLUDED

#include "label.hpp"

namespace Controls
{
    class Spinner : public Label
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

        genv::canvas spin_up_icon = read_matrix(UP_ARROW, genv::color(1,0,0));
        genv::canvas spin_dn_icon = read_matrix(DOWN_ARROW, genv::color(1,0,0));

        vec2 up_icon_pos;
        vec2 dn_icon_pos;

        genv::color spin_color = DEFAULT_MOUSEDOWN;

        virtual void update() override;
        virtual void set_value(int val);
        virtual void mod_value(int d);
        
    public:
        int min_value;
        int max_value;

        int diff_small = 1;
        int diff_big   = 10;

        Spinner(Scene *owner, int x, int y, int value, int min_value, int max_value, int width, int height, vec2 padding, const genv::font *font = nullptr);
        Spinner(Scene *owner, int x, int y, int value, int min_value, int max_value, int width, const genv::font *font = nullptr);
        Spinner(Scene *owner, int x, int y, int value, int width, int height, vec2 padding, const genv::font *font = nullptr);
        Spinner(Scene *owner, int x, int y, int value, int width, const genv::font *font = nullptr);

        void set_spin_color(int hex);
        void set_border_thickness(unsigned thickness) override;

        int get_value() const;
        
        virtual void on_mouse_ev(const event &mouse_ev, bool btn_held = false) override;
        virtual void on_key_ev(const event &key_ev, int key_held = false) override;
    };
}

#endif