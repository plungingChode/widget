#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "label.hpp"
#include <functional>

namespace Controls
{
    class Button : public Label
    {
    protected:
        std::function<void()> action;
        genv::canvas content;

        void update() override;

    public:
        Button(vec2 start, std::function<void()> action, std::string text, int width, int height, vec2 padding, std::string font = "", int font_size = 16);
        Button(vec2 start, std::function<void()> action, std::string text, int width, vec2 padding, std::string font = "", int font_size = 16);
        Button(vec2 start, std::function<void()> action, std::string text, int width, std::string font = "", int font_size = 16);

        virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held = false) override;
    };
}

#endif