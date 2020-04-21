#ifndef FRAME_HPP_INCLUDED
#define FRAME_HPP_INCLUDED

#include "control.hpp"
#include "control_common.hpp"

namespace Controls
{
    class Frame : public Control
    {
    protected:
        genv::color normal_bg = DEFAULT_NORMAL;
        genv::color hover_bg  = DEFAULT_HOVER;
        genv::color focus_bg  = DEFAULT_FOCUS;
        genv::color hold_bg   = DEFAULT_MOUSEDOWN;
        genv::color border    = DEFAULT_BORDER;
        unsigned int border_thickness;
        unsigned int min_width, min_height;

        rect resize_hitbox;

        void set_color(genv::color &target, int hex);        
        void reset_resize_hitbox();
        virtual void render_resize_area();
        virtual void update() override;

    public:
        Frame(Scene *owner, int x, int y, int width, int height, const genv::font *font = nullptr);

        void set_resizable(bool val) override;
        void set_normal_bg(int hex) { set_color(normal_bg, hex); }
        void set_focus_bg(int hex) { set_color(focus_bg, hex); }
        void set_hover_bg(int hex) { set_color(hover_bg, hex); }
        void set_hold_bg(int hex) { set_color(hold_bg, hex); }
        void set_border_color(int hex) { set_color(border, hex); }
        
        void set_min_width(int mw) { min_width = mw; }
        void set_min_height(int mh) { min_height = mh; }
        virtual void set_border_thickness(unsigned int thickness);

        virtual void on_mouse_ev(const event &mouse_ev, bool btn_held = false) override;
        virtual void on_key_ev(const event &key_ev, int key_held = 0) override {}
        virtual void render(genv::canvas &c) override;
    };
}

#endif