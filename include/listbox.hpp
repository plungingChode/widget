#ifndef LISTBOX_HPP_INCLUDED
#define LISTBOX_HPP_INCLUDED

#include <string>
#include <vector>
#include <functional>
#include "frame.hpp"

class ListBox : public Frame
{
private:
    int scroll_diff = 1;
    void adjust_thumb();

protected:
    static const int item_padding = 2;

    std::vector<std::string> items;
    std::string *selected_item;
    int selected_index;
    int items_visible;
    int show_from;

    rect thumb;
    bool thumb_hovered = false;
    bool thumb_dragged = false;
    int thumb_drag_y = -1;
    float thumb_scroll_items;

    genv::color foreground = DEFAULT_TEXT_NORMAL;
    genv::color unfocused_selection_bg = hex_to_color(0xbbbbbb);
    genv::color selection_bg = DEFAULT_BORDER;
    genv::color selection_fg = DEFAULT_TEXT_FOCUS;

    virtual void update() override;
    
public:
    ListBox(Scene *owner, int x, int y, int width, int items_visible, std::vector<std::string> items, const genv::font *font = &DEFAULT_FONT);
    ListBox(Scene *owner, int x, int y, int width, int items_visible, const genv::font *font = &DEFAULT_FONT);

    void set_font(const genv::font *font) override;
    void set_text_color(int hex) { set_color(foreground, hex); }
    void set_text_focus_color(int hex) { set_color(selection_fg, hex); }
    void set_selection_color(int hex) { set_color(unfocused_selection_bg, hex); }
    void set_selection_focused_color(int hex) { set_color(selection_bg, hex); }

    void add_item(const std::string &item);
    void remove_item(int index);

    std::string get_selected_item() const { return selected_item ? *selected_item : ""; }
    int get_selected_index() const { return selected_index; }

    const std::vector<std::string>& get_items() const { return items; }
    void set_items(const std::vector<std::string> &new_items);
    void set_selected(int index);

    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held) override;
    virtual void on_key_ev(const genv::event &key_ev, int key_held) override;
};

#endif
