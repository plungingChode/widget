#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "frame.hpp"

namespace Controls
{
    struct Label : public Frame
    {
    protected:
        genv::color text_fill_normal = DEFAULT_TEXT_NORMAL;
        genv::color text_fill_focused = DEFAULT_TEXT_FOCUS;
        vec2 padding;

        std::string text, font;
        int font_size;

    public:
        Label(vec2 start, std::string text, int width, int height, vec2 padding, std::string font = "", int font_size = 16);
        Label(vec2 start, std::string text, int width, std::string font = "", int font_size = 16);

        void set_content_offset(vec2 p);
        void set_text(std::string text);
        void set_text_fill_normal(const std::string &hex);
        virtual void set_font(std::string font, int font_size = 16);
        virtual void render() override;
        virtual void on_mouse_ev(const genv::event &mouse_ev, const bool btn_held = false) override;
    };
}

#endif