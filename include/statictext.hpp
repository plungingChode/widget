#ifndef STATICTEXT_HPP_INCLUDED
#define STATICTEXT_HPP_INCLUDED

#include "control.hpp"
#include <string>

class StaticText : public Control
{
protected:
    std::string text;
    genv::color text_color = DEFAULT_BACKGROUND_NORMAL;

    void update() override;
public:
    StaticText(Scene *owner, int x, int y, const std::string &text, const genv::font *font = nullptr);

    void set_text_color(int hex) { text_color = hex_to_color(hex); }
};

#endif
