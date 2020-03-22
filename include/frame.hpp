#ifndef FRAME_HPP_INCLUDED
#define FRAME_HPP_INCLUDED

#include "control.hpp"
// #include "rect.hpp"
// #include "graphics.hpp"

namespace Controls
{
    struct Frame : public Control, public rect
    {
    protected:
        genv::color normal_bg, hover_bg, focus_bg, hold_bg;
        genv::color fill, border;
        unsigned int border_thickness;
        unsigned int min_width, min_height;

        genv::canvas rendered;

        void set_color(genv::color& target, const std::string& hex);

    public:
        Frame(vec2 start, vec2 end);
        Frame(vec2 start, int width, int height);

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