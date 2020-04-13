#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "label.hpp"
#include <functional>

namespace Controls
{
    typedef std::function<void()> action_t;

    class Button : public Label
    {
    protected:
        action_t action;
        genv::canvas content;

        void update() override;

    public:
        Button(Scene *owner, vec2 start, action_t action, std::string text, int width, int height, vec2 padding, std::string font = "", int font_size = 16);
        Button(Scene *owner, vec2 start, action_t action, std::string text, int width, vec2 padding, std::string font = "", int font_size = 16);
        Button(Scene *owner, vec2 start, action_t action, std::string text, int width, std::string font = "", int font_size = 16);

        virtual void set_font(std::string font, int font_size = 16) override;
        virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held = false) override;
    };
}

#endif