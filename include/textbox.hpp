#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "label.hpp"

class TextBox : public Label
{
protected:
    void update() override;

public:
    TextBox(Scene *owner, int x, int y, const std::string &text, int width, const genv::font *font = nullptr);

    std::string get_text() const { return text; }

    virtual void on_key_ev(const genv::event& key_ev, int key_held) override;
};

#endif