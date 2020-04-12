#ifndef LISTBOX_HPP_INCLUDED
#define LISTBOX_HPP_INCLUDED

#include <string>
#include <vector>
#include "frame.hpp"

namespace Controls
{
    class ListBoxItem
    {
    public:
        virtual ~ListBoxItem() = default;
        virtual std::string to_string() = 0;
    };


    class ListBox : public Frame
    {
    private:
        int scroll_diff = 1;
        void adjust_thumb();

    protected:
        static const int item_padding = 2;

        std::vector<ListBoxItem*> items;
        ListBoxItem *selected_item;
        int selected_index;
        int items_visible;
        int show_from;

        std::string font;
        int font_size;

        rect thumb;
        bool thumb_hovered = false;
        bool thumb_dragged = false;
        int thumb_drag_y = -1;

        genv::color foreground = DEFAULT_TEXT_NORMAL;
        genv::color unfocused_selection_bg = hex_to_color(0xbbbbbb);
        genv::color selection_bg = DEFAULT_BORDER;
        genv::color selection_fg = DEFAULT_TEXT_FOCUS;

        virtual void update() override;
        
    public:
        ListBox(vec2 start, int width, int items_visible, std::vector<ListBoxItem*> items, std::string font = "", int font_size = 16);
        ListBox(vec2 start, int width, int items_visible, std::string font = "", int font_size = 16);

        void add_item(ListBoxItem *item);
        void remove_item(int index);
        void set_font(std::string font, int font_size = 16);

        ListBoxItem* get_selected_item() const { return selected_item; }
        int get_selected_index() const { return selected_index; }

        const std::vector<ListBoxItem*>& get_items() const { return items; }

        virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held = false) override;
        virtual void on_key_ev(const genv::event &key_ev, int key_held = 0) override;
    };
}

#endif