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
        unsigned int border_thickness;
        unsigned int min_width, min_height;

        genv::canvas rendered;

        void set_color(genv::color& target, const std::string& hex);        
        void reset_resize_hitbox();
        virtual void render_resize_area();
        virtual void update() override;

    public:
        Frame(vec2 start, int width, int height);

        void set_resizable(bool val) override;
        void set_normal_bg(const std::string& hex) { set_color(normal_bg, hex); }
        void set_focus_bg(const std::string& hex) { set_color(focus_bg, hex); }
        void set_hover_bg(const std::string& hex) { set_color(hover_bg, hex); }
        void set_hold_bg(const std::string& hex) { set_color(hold_bg, hex); }
        void set_border_color(const std::string& hex) { set_color(border, hex); }
        
        virtual void set_border_thickness(unsigned int thickness);
        void set_min_width(unsigned int w) { min_width = w; }
        void set_min_height(unsigned int h) { min_height = h; }

        virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held = false) override;
        virtual void on_key_ev(const genv::event& key_ev, int key_held = 0) override {}
        virtual void render(genv::canvas& c) override;
    };
}

#endif