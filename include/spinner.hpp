#ifndef SPINNER_HPP_INCLUDED
#define SPINNER_HPP_INCLUDED

// #include "point.hpp"
#include "label.hpp"
// #include "graphics.hpp"

namespace Controls
{
    struct Spinner : public Label
    {
    protected:
        enum SpinAction
        {
            spin_none, spin_up, spin_down
        };
        SpinAction spin;

        int value;
        Rect spin_up_hitbox;
        Rect spin_dn_hitbox;

        genv::canvas spin_up_icon;
        genv::canvas spin_dn_icon;

        genv::color spin_color;

    public:
        int max_value;
        int min_value;

        Spinner(Point start, int value, int width = 100, int height = 30, Point content_offset = Point(7, 7));

        void set_spinner_hitboxes();

        void set_spin_color(const std::string& hex);
        void set_value(const int val);
        int get_value() const;
        void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) override;
        void on_key_ev(const genv::event& key_ev, const int key_held = false) override;

        virtual void render() override;
    };
}

#endif