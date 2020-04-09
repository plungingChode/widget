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

        rect btn_hitbox;
        genv::canvas btn_icon;

        rect listitem_hitbox;
        rect list_hitbox;

        bool is_scrolling;
        vec2 thumb_drag_center;
        rect thumb_hitbox;

        genv::canvas expanded_render;

        ComboBox(vec2 start, std::vector<ComboBoxItem*> items, int width = 100, int height = 30, vec2 padding = vec2(7, 7));
        void set_selected(const int item);
        void render_list();
        // void set_expand_btn_hitbox();
        void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) override;
        void update() override;
        void render(genv::canvas& c) override;
    };
}


#endif