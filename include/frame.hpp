#ifndef FRAME_HPP_INCLUDED
#define FRAME_HPP_INCLUDED

#include "control.hpp"
#include "control_common.hpp"
// #include "rect.hpp"
// #include "graphics.hpp"

namespace Controls
{
    struct Frame : public Control, public rect
    {
    protected:
        genv::color normal_bg = DEFAULT_NORMAL;
        genv::color hover_bg  = DEFAULT_HOVER;
        genv::color focus_bg  = DEFAULT_FOCUS;
        genv::color hold_bg   = DEFAULT_MOUSEDOWN;
        genv::color border    = DEFAULT_BORDER;
        genv::color fill;
        unsigned border_thickness;
        unsigned min_width, min_height;

        genv::canvas rendered;

        void set_color(genv::color& target, const std::string& hex);

    public:
        Frame(vec2 start, unsigned width, unsigned height);

        void set_resizable(const bool val) override;
        void reset_resize_hitbox();
        void set_normal_bg(const std::string& hex);
        void set_focus_bg(const std::string& hex);
        void set_hover_bg(const std::string& hex);
        void set_drag_bg(const std::string& hex);
        void set_border_color(const std::string& hex);
        void set_border_thickness(const unsigned thickness);

        virtual void render_resize_area();

        virtual void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) override;
        virtual void on_key_ev(const genv::event& key_ev, const int key_held = 0) override {}
        virtual void render() override;
        virtual void draw(genv::canvas& c) override;
    };
}

#endif