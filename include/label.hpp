#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

// #include "point.hpp"
#include "frame.hpp"
// #include "graphics.hpp"

namespace Controls
{
    struct Label : public Frame
    {
    protected:
        genv::color text_fill_normal, text_fill_focused;
        vec2 content_offset;

        std::string text, font_src;

    public:
        Label(vec2 start, const std::string& text,int width = 100, int height = 30, vec2 content_offset = vec2(7, 7));

        void set_content_offset(vec2 p);
        void set_text(const std::string& text);
        void set_text_fill_normal(const std::string& hex);
        virtual void set_font(const std::string& font_src);
        virtual void render() override;
        virtual void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) override;
    };
}

#endif