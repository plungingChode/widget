#include "listbox.hpp"
#include <algorithm>

using namespace genv;

namespace Controls
{
    ListBox::ListBox(Scene *s, int x_, int y_, int w_, int items_vis, std::vector<ListBoxItem*> v, const genv::font *f)
        : Frame(s, x_, y_, w_, items_vis*(f->font_size+item_padding)+2, f),
          items(v), selected_item(nullptr), selected_index(-1),
          items_visible(items_vis), show_from(0)
    {
        Control::draggable = false;
        Frame::border_thickness = 1;
        
        set_font(f);
        set_hover_bg(0xffffff);
        set_focus_bg(0xffffff);
        set_hold_bg(0xffffff);

        thumb = rect(vec2(w_-1-15, 0), 15, -1);
        adjust_thumb();
    }

    ListBox::ListBox(Scene *s, int x_, int y_, int w_, int items_vis, const genv::font *f)
        : ListBox(s, x_, y_, w_, items_vis, {}, f)
    {
    }

    void ListBox::adjust_thumb()
    {
        if ((int)items.size() < items_visible)
        {
            thumb.h = h;
        }
        else
        {
            thumb.h = h * items_visible / (float)items.size();

            scroll_diff = force_bounds(thumb.h/2, 1, 8);
            thumb.h = std::max(10, thumb.h);
        }

        if (thumb.y+thumb.h > h)
        {
            thumb.y = h-thumb.h;
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

    void ListBox::sort(listbox_sort sort)
    {
        std::sort(items.begin(), items.end(), sort);
        schedule_update();
    }

    void ListBox::update()
    {
        Frame::update();

        // draw separator
        rendered
            << move_to(w-1-thumb.w-1, 0)
            << border << line(0, h);

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
            << move_to(thumb.x, thumb.y)
            << box(thumb.w, thumb.h);

        // draw items
        int ubound = std::min(items_visible, (int)items.size());
        int baseline_offs = font->font_name.empty() ? rendered.cascent() : 0;
        int item_h = font->font_size+item_padding;

        for (int i = 0; i < ubound; i++)
        {
            int index = show_from+i;
            if (index == selected_index)
            {
                rendered << move_to(1, i*item_h+1);
                if (focused)
                {
                    rendered << selection_bg;
                }
                else
                {
                    rendered << unfocused_selection_bg;
                }
                rendered << box(w-thumb.w-2*1, item_h);
                rendered << selection_fg;
            }
            else
            {
                rendered << foreground;
            }
            rendered 
                << move_to(5+1, i*item_h+1+baseline_offs)
                << text(items[index]->to_string());
        }
    }

    void ListBox::set_font(const genv::font *f)
    {
        if (!f)
        {
            f = &DEFAULT_FONT;
        }
        if (!font || f->font_size != font->font_size)
        {
            size_changed = true;
        }
        Control::set_font(f);
        schedule_update();
    }

    void ListBox::on_mouse_ev(const genv::event &mouse_ev, bool btn_held)
    {
        Frame::on_mouse_ev(mouse_ev, btn_held);
        vec2 m_rel(mouse_ev.pos_x-x, mouse_ev.pos_y-y);
        
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
                    thumb_drag_y = m_rel.y - thumb.y;
                }

                thumb.y = m_rel.y - thumb_drag_y;
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
                    thumb.y -= scroll_diff;
                    thumb_moved = true;
                }

                if (mouse_ev.button == btn_wheeldown)
                {
                    thumb.y += scroll_diff;
                    thumb_moved = true;
                }
            }

            if (!thumb_hovered && mouse_ev.button == btn_left)
            {
                if (m_rel.x < w-1-thumb.w-1 &&
                    m_rel.x > 1)
                {
                    float mouse_pos = m_rel.y / float(h-2+item_padding);

                    selected_index = show_from+(mouse_pos*items_visible);
                    selected_item = items[selected_index];
                }
                else if (m_rel.x > w-1-thumb.w &&
                         m_rel.x < w-1)
                {
                    thumb.y = m_rel.y - thumb.h/2;
                    thumb_moved = true;
                }
            }

            if (thumb_moved)
            {
                thumb.y = force_bounds(thumb.y, 0, int(h-thumb.h));

                show_from = (thumb.y / float(h-thumb.h)) * items.size();
                show_from = force_bounds(show_from, 0, int(items.size()-items_visible));

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

