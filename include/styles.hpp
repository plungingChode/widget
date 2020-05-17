#ifndef STYLES_HPP_INCLUDED
#define STYLES_HPP_INCLUDED

class Button;
class Frame;
class Label;
class ListBox;
class Spinner;
class TextBox;

enum style_t
{
    DEFAULT = 0, WINDOWS, DARK
};

enum color_t
{
    NORMAL = 0, FOCUS, BORDER, HOVER, HOLD, TEXT_NORMAL, TEXT_FOCUS, LIST_SELECTION, SPIN_BTN
};

const int default_colors[9] = 
{
    0xFFFFFF, // white
    0xAA8E39, // dk ochre
    0x718EA4, // lt blue
    0xD4BA6A, // lt ochre
    0xAA5939, // crimson
    0x100000, // ~ black (non-transparent)
    0xFFFFFF, // white
    0xBBBBBB, // lt gray
    0x100000, // ~ black (non-transparent)
};

const int dark_colors[9] = 
{
    0x6C6C6C, // dk gray
    0x7C7C7C, // lighter dk gray
    0xE5D96E, // lt yellow
    0x7C7C7C, // lighter dk gray
    0x8C8C8C, // even lighter dk gray
    0xE5D96E, // lt yellow
    0xE5D96E, // lt yellow
    0xB7B49C, // desaturated lt yellow
    0xE5D96E, // lt yellow
};

const int test_colors[1] = {
    0xFF0000
};

const int* get_palette(style_t style);
void set_style(Button* btn, style_t style);
void set_style(Frame* frm, style_t style);
void set_style(Label* lbl, style_t style);
void set_style(ListBox* lb, style_t style);
void set_style(Spinner* spn, style_t style);
void set_style(TextBox* tb, style_t style);

#endif
