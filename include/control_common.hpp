#ifndef CONTROLS_COMMON_HPP_INCLUDED
#define CONTROLS_COMMON_HPP_INCLUDED

#include "graphics.hpp"

namespace Controls
{
    genv::canvas read_kep(const std::string& fname);
    genv::color hex_to_color(const std::string& h);

    const genv::color BLACK = hex_to_color("000000");
    const genv::color DEFAULT_BORDER = hex_to_color("718EA4");
    const genv::color DEFAULT_NORMAL = hex_to_color("FFFFFF");
    const genv::color DEFAULT_HOVER = hex_to_color("D4BA6A");
    const genv::color DEFAULT_FOCUS = hex_to_color("AA8E39");
    const genv::color DEFAULT_MOUSEDOWN = hex_to_color("AA5939");
    const genv::color DEFAULT_TEXT_NORMAL = hex_to_color("100000");
    const genv::color DEFAULT_TEXT_FOCUS = hex_to_color("FFFFFF");

    extern int ENV_WIDTH;
    extern int ENV_HEIGHT;
    extern genv::color BACKGROUND_COLOR;
}

#endif