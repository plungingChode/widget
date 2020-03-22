#include "combobox.hpp"
#include <iostream>

using namespace genv;

namespace Controls
{
    ComboBox::ComboBox(vec2 start, std::vector<ComboBoxItem*> items, 
        int width, int height, vec2 content_offset)
            : 
            Label(start, "", width, height, content_offset),   
            items(items),
            items_visible(5),
            hover_pos(-1),
            selected_item(nullptr)
    {
        Control::is_hittest_visible = true;
        Control::is_draggable = false;
        Control::_is_resizable = false;

        unsigned int& b = border_thickness;
        // btn_hitbox = rect(vec2(width - 17 - b, b), vec2(width - b, height - b));
        btn_icon = read_kep("dnarrow.kep");

        list_hitbox = rect(width, items_visible*height);
        expanded_render = canvas(width, items_visible*height);

        // thumb_hitbox = rect(vec2(list_hitbox.end.x-btn_hitbox.width, 0), btn_hitbox.width, 40);

        if (items.size() && items[0])
        {
            std::cout << "item OK" << '\n'; 
            set_selected(0);
        }
    }

    void ComboBox::set_font(const std::string& font_src)
    {
        Label::set_font(font_src);
        expanded_render.load_font(font_src);
    }

    void ComboBox::set_selected(const int index)
    {
        selected_index = index;
        selected_item = items[index];
        set_text(selected_item->to_string());
    }

    void ComboBox::on_mouse_ev(const event& m, const bool btn_held)
    {
        Label::on_mouse_ev(m, btn_held);
        
        if (_is_focused)
        {
            vec2 m_rel(m.pos_x - start.x, m.pos_y - start.y);
            // if (is_expanded && list_hitbox.intersects(m_rel))
            // {
            //     _is_hovered = true;
            // }

            // Point& t = thumb_hitbox.start;
            // std::cout << t.x << ':' << t.y << '\n';
            // std::cout << m_rel.x << ':' << m_rel.y << '\n';

            if (m.button == btn_left && 
                btn_hitbox.intersects(m_rel))
            {
                std::cout << "expand!\n";
                is_expanded = !is_expanded;

                is_scrolling = false;
                _needs_visual_update = true;
            }
            else if (thumb_hitbox.intersects(m_rel))
            {
                std::cout << "thumb dragging?\n";
                if (!is_scrolling)
                {
                    thumb_drag_center = m_rel;
                    is_scrolling = true;
                }

                int& thumb_y = thumb_hitbox.start.y;
                thumb_y += m.pos_y - thumb_drag_center.y;
                // thumb_y = std::min((unsigned)std::max(thumb_y, 0), list_hitbox.height - thumb_hitbox.height);
            }
        } 
        // else if (!_is_focused)
        // {
        //     std::cout << "collapse!\n";
        //     is_scrolling = false;
        //     is_expanded = false;
        //     _needs_visual_update = true;
        // }
    }

    void ComboBox::render_list()
    {
        unsigned int& b = border_thickness;
        rect& list = list_hitbox;
        rect& thumb = thumb_hitbox;

        expanded_render
            << move_to(0, 0) << border << box(list_hitbox.width, list_hitbox.height)
            << move_to(b, b) << normal_bg << box(list_hitbox.width-2*b, list_hitbox.height-2*b)
            << move_to(list.width-b-thumb.width, 0) << border << line(0, list.height);

        int from = selected_index ? selected_index-1 : selected_index;
        int to = std::min(items.size(), (size_t)items_visible);

        for (int i = from; i < to; i++)
        {
            expanded_render 
                << move_to(content_offset.x, i*height + content_offset.y) 
                << text_fill_normal 
                << genv::text(items[i]->to_string());
        }

        // expanded_render
        //     << move_to(list.width-b-thumb.width, 0) << border << box(thumb.width, thumb.height);

        expanded_render
             << move_to(thumb.start.x, thumb.start.y) << border << box(thumb.width, thumb.height);
    }

    void ComboBox::render()
    {
        Label::render();

        rect& xp = btn_hitbox;
        rendered << move_to(xp.start.x, xp.start.y)
                 << text_fill_normal
                 << box(xp.width, xp.height)
                 << move_to(xp.start.x + 1, xp.start.y + 1)
                 << normal_bg
                 << box(xp.width - 2, xp.height - 2)
                 << stamp(btn_icon, xp.start.x + 3, xp.start.y + xp.height/2 - 3);

        render_list();
    }

    void ComboBox::draw(canvas& c)
    {
        Frame::draw(c);
        if (is_expanded)
        {
            c << stamp(expanded_render, start.x, start.y+height);
        }
    }
}
