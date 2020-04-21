#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "label.hpp"
#include <functional>

namespace Controls
{
    class Button : public Label
    {
    protected:
        const int action;

        void update() override;

    public:
        Button(Scene *owner, int x, int y, int action, const std::string &text, int width, int height, vec2 padding, const genv::font *font = nullptr);
        Button(Scene *owner, int x, int y, int action, const std::string &text, int width, vec2 padding, const genv::font *font = nullptr);
        Button(Scene *owner, int x, int y, int action, const std::string &text, int width, const genv::font *font = nullptr);

        virtual void set_font(const genv::font *font) override;
        virtual void on_mouse_ev(const event& mouse_ev, bool btn_held = false) override;
    };
}

#endif