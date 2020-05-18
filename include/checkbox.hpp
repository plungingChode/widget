#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "frame.hpp"
#include <string>

class CheckBox : public Frame
{
protected:
    bool checked;
    bool update_caption;
    std::string caption;
    rect check_box;

    genv::canvas check_mark;
    genv::color text_color = DEFAULT_BACKGROUND_NORMAL;

    void reset_check_box();
    void update() override;

public:
    CheckBox(Scene *owner, int x, int y, const std::string &caption, const genv::font *font = nullptr);

    bool get_checked() { return checked; }
    void set_checked(bool val) { checked = val; schedule_update(); }

    void set_border_color(int hex);
    void set_text_color(int hex) { text_color = hex_to_color(hex); update_caption = true; }

    void on_mouse_ev(const genv::event &ev, bool btn_held) override;
    void on_key_ev(const genv::event &ev, int key_held) override;
};

#endif
