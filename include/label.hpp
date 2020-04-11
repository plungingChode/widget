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

        virtual void update() override;

    public:
        Label(vec2 start, std::string text, int width, int height, vec2 padding, std::string font = "", int font_size = 16);
        Label(vec2 start, std::string text, int width, vec2 padding, std::string font = "", int font_size = 16);
        Label(vec2 start, std::string text, int width, std::string font = "", int font_size = 16);

        void set_padding(vec2 p);
        void set_text(std::string text);
        void set_text_fill_normal(const std::string &hex) { set_color(text_fill_normal, hex); }
        void set_text_fill_focused(const std::string &hex) { set_color(text_fill_focused, hex); }
        virtual void set_font(std::string font, int font_size = 16);
    };
}

#endif