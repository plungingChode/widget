#ifndef CONTROLS_COMMON_HPP_INCLUDED
#define CONTROLS_COMMON_HPP_INCLUDED

#include "graphics.hpp"
#include <vector>

#define force_bounds(val, lbound, ubound) std::max(std::min(val, ubound), lbound)

namespace Controls
{
    extern int ENV_WIDTH;
    extern int ENV_HEIGHT;
    extern genv::color BACKGROUND_COLOR;

    genv::canvas read_kep(const std::string& fname);
    genv::canvas read_matrix(const std::vector<std::vector<int>> matrix, genv::color color);
    
    genv::color hex_to_color(int hex);
    genv::color change_shade(const genv::color &c, float dr, float dg, float db);
    genv::color change_shade(const genv::color &c, float d);
    genv::color change_tint(const genv::color &c, float dr, float dg, float db);
    genv::color change_tint(const genv::color &c, float d);

    const genv::color BLACK = hex_to_color(0x000000);
    const genv::color DEFAULT_BORDER = hex_to_color(0x718EA4);
    const genv::color DEFAULT_NORMAL = hex_to_color(0xFFFFFF);
    const genv::color DEFAULT_HOVER = hex_to_color(0xD4BA6A);
    const genv::color DEFAULT_FOCUS = hex_to_color(0xAA8E39);
    const genv::color DEFAULT_MOUSEDOWN = hex_to_color(0xAA5939);
    const genv::color DEFAULT_TEXT_NORMAL = hex_to_color(0x100000);
    const genv::color DEFAULT_TEXT_FOCUS = hex_to_color(0xFFFFFF);

    const std::vector<std::vector<int>> DOWN_ARROW = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}
    };

    const std::vector<std::vector<int>> UP_ARROW = {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,},
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,}, 
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,}, 
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,}, 
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

#endif