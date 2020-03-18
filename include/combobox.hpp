#ifndef COMBOBOX_HPP_INCLUDED
#define COMBOBOX_HPP_INCLUDED

#include "label.hpp"
#include <string>
#include <vector>

namespace Controls
{
    struct ComboBoxItem
    {
        virtual std::string to_string() const = 0;
    };

    struct ComboBox : public Label
    {
        bool is_expanded;
        unsigned int items_visible;
        int hover_pos;

        int selected_index;
        ComboBoxItem* selected_item;
        std::vector<ComboBoxItem*> items;

        Rect btn_hitbox;
        genv::canvas btn_icon;

        Rect listitem_hitbox;
        Rect list_hitbox;

        bool is_scrolling;
        Point thumb_drag_center;
        Rect thumb_hitbox;

        genv::canvas expanded_render;

        ComboBox(Point start, std::vector<ComboBoxItem*> items, int width = 100, int height = 30, Point content_offset = Point(7, 7));
        void set_selected(const int item);
        void render_list();
        // void set_expand_btn_hitbox();
        void set_font(const std::string& font_src) override;
        void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) override;
        void render() override;
        void draw(genv::canvas& c) override;
    };
}


#endif