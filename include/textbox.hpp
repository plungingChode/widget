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
        TextBox(Scene *owner, int x, int y, const std::string &text, int width, int height, vec2 padding, const genv::font *font = nullptr);
        TextBox(Scene *owner, int x, int y, const std::string &text, int width, vec2 padding, const genv::font *font = nullptr);
        TextBox(Scene *owner, int x, int y, const std::string &text, int width, const genv::font *font = nullptr);

        virtual void on_key_ev(const genv::event& key_ev, const int key_held = 0) override;
    };
}

#endif