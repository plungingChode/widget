#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

// #include "point.hpp"
#include "label.hpp"
// #include "graphics.hpp"

namespace Controls
{
    struct Button : public Label
    {
    protected:
        void (*action)();
        genv::canvas content;

    public:
        Button(Point start, const std::string& text, void (*action)(), int width = 100, int height = 30, Point content_offset = Point(7, 7));

        void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) override;
        void render() override;
    };
}

#endif