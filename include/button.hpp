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

        void update() override;

    public:
        Button(Scene *owner, int x, int y, int width, int height, const std::string &text, std::function<void()> action, const genv::font *font = nullptr);
        Button(Scene *owner, int x, int y, int width, const std::string &text, std::function<void()> action, const genv::font *font = nullptr);

        virtual void set_font(const genv::font *font) override;
        virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held = false) override;
    };
}

#endif