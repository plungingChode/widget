#include "listbox.hpp"

using namespace genv;

ListBox::ListBox(Scene *s, int x_, int y_, int w_, int items_vis, std::vector<std::string> v, const genv::font *f)
    : Frame(s, x_, y_, w_, items_vis*(f->font_size+item_padding)+2, f),
        items(v), selected_item(nullptr), selected_index(-1),
        items_visible(items_vis), show_from(0)
{
    Control::draggable = false;
    Frame::border_thickness = 1;
    
    set_font(f);
    set_hover_color(0xffffff);
    set_focus_color(0xffffff);
    set_hold_color(0xffffff);

    thumb = rect(vec2(w_-border_thickness-15, border_thickness), 15, -1);
    adjust_thumb();
}

ListBox::ListBox(Scene *s, int x_, int y_, int w_, int items_vis, const genv::font *f)
    : ListBox(s, x_, y_, w_, items_vis, {}, f)
{
}

void ListBox::adjust_thumb()
{
    if ((int)items.size() <= items_visible)
    {
        thumb.h = h-2*border_thickness;
    }
    else
    {
        thumb.h = (h-2*border_thickness) * items_visible / (float)items.size();

        scroll_diff = std::min(std::max(thumb.h/2, 1), 8);
        thumb.h = std::max(10, thumb.h);
    }
    thumb_scroll_items = (items.size() - items_visible) / float(h-2*border_thickness-thumb.h);
}

void ListBox::add_item(const std::string &item)
{
    items.push_back(item);
    adjust_thumb();
    schedule_update();
}

void ListBox::remove_item(int index)
{
    items.erase(items.begin() + index);

    show_from = std::max(std::min(show_from, int(items.size()-items_visible)), 0);

    if (index == selected_index)
    {
        if (items.size() > 0)
        {
            selected_index = std::min(selected_index, (int)items.size()-1);
            selected_item = &items[selected_index];   
        }
        else
        {
            selected_item = nullptr;
            selected_index = -1;
        }
    }

    adjust_thumb();
    schedule_update();
}

void ListBox::set_items(const std::vector<std::string> &new_items)
{
    items = new_items;
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
            rendered << move_to(border_thickness, i*item_h+border_thickness);
            if (focused)
            {
                rendered << selection_bg;
            }
            else
            {
                rendered << unfocused_selection_bg;
            }
            rendered << box(w-thumb.w-2*border_thickness-1, item_h);
            rendered << selection_fg;
        }
        else
        {
            rendered << foreground;
        }
        rendered 
            << move_to(5+1, i*item_h+border_thickness+baseline_offs)
            << text(items[index]);
    }
}

void ListBox::set_font(const genv::font *f)
{
    if (!font || f->font_size != font->font_size)
    {
        size_changed = true;
    }
    Control::set_font(f);
    if (!font)
    {
        font = &DEFAULT_FONT;
    }
    schedule_update();
}

void ListBox::on_mouse_ev(const event &mouse_ev, bool btn_held)
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
            if (m_rel.x < w-border_thickness-thumb.w &&
                m_rel.x > border_thickness)
            {
                float mouse_pos = m_rel.y / float(h-2+item_padding);

                selected_index = show_from+(mouse_pos*items_visible);
                selected_item = &items[selected_index];
            }
            else if (m_rel.x > w-border_thickness-thumb.w &&
                        m_rel.x < w-border_thickness)
            {
                thumb.y = m_rel.y - thumb.h/2;
                thumb_moved = true;
            }
        }

        if (thumb_moved)
        {
            thumb.y = std::min(std::max(thumb.y, border_thickness), int(h-border_thickness-thumb.h));

            show_from = (thumb.y-border_thickness) * thumb_scroll_items;
            show_from = std::max(std::min(show_from, int(items.size()-items_visible)), 0);

            schedule_update();
        }
    }    
}

void ListBox::set_selected(int index)
{
    selected_index = index;
    if (selected_index < show_from)
    {
        show_from = selected_index;
    }
    else if (selected_index >= show_from+items_visible)
    {
        show_from = selected_index-items_visible+1;
    }
    thumb.y = show_from / thumb_scroll_items + border_thickness;
    schedule_update();
}

void ListBox::on_key_ev(const event &key_ev, int key_held)
{
    if (focused)
    {
        if (key_held == key_up && selected_index > 0)
        {
            set_selected(selected_index-1);
        }
        if (key_held == key_down && selected_index < (int)items.size()-1)
        {
            set_selected(selected_index+1);
        }
    }
}
