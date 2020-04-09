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
        void reset_resize_hitbox();
        virtual void render_resize_area();
        virtual void update() override;

    public:
        Frame(vec2 start, unsigned width, unsigned height);

        void set_resizable(bool val) override;
        void set_normal_bg(const std::string& hex);
        void set_focus_bg(const std::string& hex);
        void set_hover_bg(const std::string& hex);
        void set_drag_bg(const std::string& hex);
        void set_border_color(const std::string& hex);
        virtual void set_border_thickness(unsigned thickness);

        virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held = false) override;
        virtual void on_key_ev(const genv::event& key_ev, int key_held = 0) override {}
        virtual void render(genv::canvas& c) override;
    };
}

#endif