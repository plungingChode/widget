#ifndef LISTBOX_HPP_INCLUDED
#define LISTBOX_HPP_INCLUDED

#include <string>
#include <vector>
#include <functional>
#include "frame.hpp"

namespace Controls
{
    class ListBoxItem
    {
    public:
        virtual ~ListBoxItem() = default;
        virtual std::string to_string() = 0;
    };

    typedef std::function<bool(ListBoxItem*, ListBoxItem*)> Compare;

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
        ListBox(Scene *owner, int x, int y, int width, int items_visible, std::vector<ListBoxItem*> items, const genv::font *font = &DEFAULT_FONT);
        ListBox(Scene *owner, int x, int y, int width, int items_visible, const genv::font *font = &DEFAULT_FONT);

        void set_font(const genv::font *font) override;

        void add_item(ListBoxItem *item);
        void remove_item(int index);
        void sort(Compare comp);       

        ListBoxItem* get_selected_item() const { return selected_item; }
        int get_selected_index() const { return selected_index; }

        const std::vector<ListBoxItem*>& get_items() const { return items; }

        
        virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held = false) override;
        virtual void on_key_ev(const genv::event &key_ev, int key_held = 0) override;
    };
}

#endif