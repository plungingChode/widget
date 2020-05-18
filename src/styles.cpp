#include "styles.hpp"
#include "controls.hpp"

const int* get_palette(style_t style)
{
    switch (style)
    {
    case DARK:
        return dark_colors;

    case DEFAULT:
    default:
        return default_colors;
    }
}

void set_style(Button *b, style_t style)
{
    const int *palette = get_palette(style);
    b->set_background_color(palette[NORMAL]);
    b->set_focus_color(palette[FOCUS]);
    b->set_border_color(palette[BORDER]);
    b->set_hover_color(palette[HOVER]);
    b->set_hold_color(palette[HOLD]);
    b->set_text_color(palette[TEXT_NORMAL]);
    b->set_text_focus_color(palette[TEXT_FOCUS]);
}

void set_style(Frame *f, style_t style)
{
    const int *palette = get_palette(style);
    f->set_background_color(palette[NORMAL]);
    f->set_focus_color(palette[FOCUS]);
    f->set_border_color(palette[BORDER]);
    f->set_hover_color(palette[HOVER]);
    f->set_hold_color(palette[HOLD]);
}

void set_style(Label *l, style_t style)
{
    const int *palette = get_palette(style);
    l->set_background_color(palette[NORMAL]);
    l->set_focus_color(palette[FOCUS]);
    l->set_border_color(palette[BORDER]);
    l->set_hover_color(palette[HOVER]);
    l->set_hold_color(palette[HOLD]);
    l->set_text_color(palette[TEXT_NORMAL]);
    l->set_text_focus_color(palette[TEXT_FOCUS]);
}

void set_style(ListBox *l, style_t style)
{
    const int *palette = get_palette(style);
    l->set_background_color(palette[NORMAL]);
    l->set_focus_color(palette[NORMAL]);
    l->set_border_color(palette[BORDER]);
    l->set_hover_color(palette[NORMAL]);
    l->set_hold_color(palette[NORMAL]);
    l->set_text_color(palette[TEXT_NORMAL]);
    l->set_text_focus_color(palette[NORMAL]);
    l->set_selection_focused_color(palette[BORDER]);
    l->set_selection_color(palette[LIST_SELECTION]);
}

void set_style(Spinner *s, style_t style)
{
    const int *palette = get_palette(style);
    s->set_background_color(palette[NORMAL]);
    s->set_focus_color(palette[FOCUS]);
    s->set_border_color(palette[BORDER]);
    s->set_hover_color(palette[HOVER]);
    s->set_hold_color(palette[FOCUS]);
    s->set_text_color(palette[TEXT_NORMAL]);
    s->set_text_focus_color(palette[TEXT_FOCUS]);
    s->set_spin_color(palette[HOLD]);
    s->set_spin_btn_color(palette[SPIN_BTN]);
}

void set_style(TextBox *tb, style_t style)
{
    const int *palette = get_palette(style);
    tb->set_background_color(palette[NORMAL]);
    tb->set_focus_color(palette[NORMAL]);
    tb->set_border_color(palette[BORDER]);
    tb->set_hover_color(palette[FOCUS]);
    tb->set_hold_color(palette[FOCUS]);
    tb->set_text_color(palette[TEXT_NORMAL]);
    tb->set_text_focus_color(palette[TEXT_FOCUS]); 
}

void set_style(CheckBox *c, style_t style)
{
    const int *palette = get_palette(style);
    c->set_background_color(palette[NORMAL]);
    c->set_focus_color(palette[FOCUS]);
    c->set_border_color(palette[BORDER]);
    c->set_hover_color(palette[HOVER]);
    c->set_hold_color(palette[HOLD]);
    c->set_text_color(palette[TEXT_FOCUS]);
}