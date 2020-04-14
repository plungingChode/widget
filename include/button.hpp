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
        Button(int x, int y, action_t action, const std::string &text, int width, int height, vec2 padding, const genv::font *font = nullptr);
        Button(int x, int y, action_t action, const std::string &text, int width, vec2 padding, const genv::font *font = nullptr);
        Button(int x, int y, action_t action, const std::string &text, int width, const genv::font *font = nullptr);

        virtual void set_font(const genv::font *font) override;
        virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held = false) override;
    };
}

#endif