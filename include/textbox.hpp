#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "label.hpp"

namespace Controls
{
    class TextBox : public Label
    {
    protected:
        void update() override;

    public:
        TextBox(Scene *owner, vec2 start, std::string text, int width, int height, vec2 padding, std::string font = "", int font_size = 16);
        TextBox(Scene *owner, vec2 start, std::string text, int width, vec2 padding, std::string font = "", int font_size = 16);
        TextBox(Scene *owner, vec2 start, std::string text, int width, std::string font = "", int font_size = 16);

        virtual void on_key_ev(const genv::event& key_ev, const int key_held = 0) override;
    };
}

#endif