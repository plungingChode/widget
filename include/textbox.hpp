#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "label.hpp"

namespace Controls
{
    struct TextBox : public Label
    {
    public:
        TextBox(vec2 start, const std::string& text, int width = 120, int height = 35, vec2 padding = vec2(7, 7));

        void on_key_ev(const genv::event& key_ev, const int key_held = 0) override;
        void render() override;
    };
}

#endif