#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "label.hpp"

namespace Controls
{
      struct TextBox : public Label
    {
    private:
        Point cursor_pos;
        unsigned int cursor_height;

        void update_cursor();

    public:
        TextBox(Point start, const std::string& text, int width = 120, int height = 35, Point content_offset = Point(7, 7));

        void on_key_ev(const genv::event& key_ev, const int key_held = 0) override;
        void set_font(const std::string& font_src) override;
        void render() override;
    };
}

#endif