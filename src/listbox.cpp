#include "listbox.hpp"
#include <algorithm>

using namespace genv;

namespace Controls
{
    ListBox::ListBox(vec2 start, int width, int items_visible, std::vector<ListBoxItem*> items, std::string font, int font_size)
        : Frame(start, width, items_visible*(font_size+item_padding)+2),
          items(items), selected_item(nullptr), selected_index(-1),
          items_visible(items_visible), show_from(0)
    {
        Control::draggable = false;
        Frame::border_thickness = 1;
        
        set_font(font, font_size);
        set_hover_bg(0xffffff);
        set_focus_bg(0xffffff);
        set_hold_bg(0xffffff);

        thumb = rect(vec2(width-1-15, 0), 15, -1);
        adjust_thumb();
    }

    ListBox::ListBox(vec2 start, int width, int items_visible, std::string font, int font_size)
        : ListBox(start, width, items_visible, {}, font, font_size)
    {
    }

    void ListBox::adjust_thumb()
    {
        if ((int)items.size() < items_visible)
        {
            thumb.height = height;
        }
        else
        {
            thumb.height = height * items_visible / (float)items.size();

            scroll_diff = force_bounds(thumb.height/2, 1u, 8u);
            thumb.height = std::max(10u, thumb.height);
        }

        if (thumb.start.y+thumb.height > height)
        {
            thumb.start.y = height-thumb.height;
        }
    }

    void ListBox::add_item(ListBoxItem *item)
    {
        items.push_back(item);
        adjust_thumb();
        schedule_update();
    }
    
    void ListBox::remove_item(int index)
    {
        if (index >= 0 && index < (int)items.size())
        {
            delete items[index];
            items.erase(items.begin() + index);

            show_from = force_bounds(show_from, 0, (int)items.size()-items_visible);

            if (index == selected_index)
            {
                selected_item = nullptr;
                selected_index = -1;
            }

            adjust_thumb();
            schedule_update();
        }
    }

    void ListBox::sort(Compare comp)
    {
        std::sort(items.begin(), items.end(), comp);
        schedule_update();
    }

    void ListBox::update()
    {
        Frame::update();

        // draw separator
        rendered
            << move_to(width-1-thumb.width-1, 0)
            << border << line(0, height);

        // draw thumb
        if (thumb_dragged)
        {
            rendered << border;
        }
        else if (thumb_hovered)
        {
            rendered << change_tint(border, 0.2);
        }
        else
        {
            rendered << change_tint(border, 0.5);
        }

        rendered
            << move_to(thumb.start.x, thumb.start.y)
            << box(thumb.width, thumb.height);

        // draw items
        int ubound = std::min(items_visible, (int)items.size());
        int baseline_offs = font.empty() ? rendered.cascent() : 0;
        int item_height = font_size+item_padding;

        for (int i = 0; i < ubound; i++)
        {
            int index = show_from+i;
            if (index == selected_index)
            {
                rendered << move_to(1, i*item_height+1);
                if (focused)
                {
                    rendered << selection_bg;
                }
                else
                {
                    rendered << unfocused_selection_bg;
                }
                rendered << box(width-thumb.width-2*1, item_height);
                rendered << selection_fg;
            }
            else
            {
                rendered << foreground;
            }
            rendered 
                << move_to(5+1, i*item_height+1+baseline_offs)
                << text(items[index]->to_string());
        }
    }

    void ListBox::set_font(std::string font, int font_size)
    {
        if (rendered.load_font(font, font_size))
        {
            this->font = font;
            this->font_size = font_size;
        }
        else
        {
            this->font = "";
            this->font_size = 16;
        }
        schedule_update();
    }

    void ListBox::on_mouse_ev(const genv::event &mouse_ev, bool btn_held)
    {
        Frame::on_mouse_ev(mouse_ev, btn_held);
        vec2 m_rel(mouse_ev.pos_x-start.x, mouse_ev.pos_y-start.y);
        
        bool new_thumb_hover = thumb.intersects(m_rel);
        if (new_thumb_hover != thumb_hovered)
        {
            thumb_hovered = new_thumb_hover;
            schedule_update();
        }

        if (focused)
        {
            bool thumb_moved = false;

            if (thumb_dragged || (thumb_hovered && btn_held))
            {
                dragged = false;

                if (!thumb_dragged)
                {
                    thumb_dragged = true;
                    thumb_drag_y = m_rel.y - thumb.start.y;
                }

                thumb.start.y = m_rel.y - thumb_drag_y;
                thumb_moved = true;
            }
            
            if (!btn_held)
            {
                thumb_dragged = false;
            }

            if (hovered)
            {
                if (mouse_ev.button == btn_wheelup)
                {
                    thumb.start.y -= scroll_diff;
                    thumb_moved = true;
                }

                if (mouse_ev.button == btn_wheeldown)
                {
                    thumb.start.y += scroll_diff;
                    thumb_moved = true;
                }
            }

            if (!thumb_hovered && mouse_ev.button == btn_left)
            {
                if ((unsigned)m_rel.x < width-1-thumb.width-1 &&
                    (unsigned)m_rel.x > 1)
                {
                    float mouse_pos = m_rel.y / float(height-2+item_padding);

                    selected_index = show_from+(mouse_pos*items_visible);
                    selected_item = items[selected_index];
                }
                else if ((unsigned)m_rel.x > width-1-thumb.width &&
                         (unsigned)m_rel.x < width-1)
                {
                    thumb.start.y = m_rel.y - thumb.height/2;
                    thumb_moved = true;
                }
            }

            if (thumb_moved)
            {
                thumb.start.y = force_bounds(thumb.start.y, 0, int(height-thumb.height));

                show_from = (thumb.start.y / float(height-thumb.height)) * items.size();
                show_from = force_bounds(show_from, 0, (int)items.size()-items_visible);

                schedule_update();
            }
        }    
    }

    void ListBox::on_key_ev(const genv::event &key_ev, int key_held)
    {
        // TODO
        
        // if (focused)
        // {
        //     if (key_ev.keycode == key_up && selected_index > 0)
        //     {
        //         --selected_index;

        //     }
        // }
    }
}

