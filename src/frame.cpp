#include "frame.hpp"
#include "control_common.hpp"

using namespace genv;

namespace Controls
{
    Frame::Frame(vec2 start, unsigned width, unsigned height)
        : Control(start),
          rect(start, width, height),
          fill(normal_bg),
          border_thickness(10),
          min_width(15), 
          min_height(15),
          rendered(width, height)
    { 
    }

    void Frame::set_resizable(const bool val)
    {
        resizable = val;
        reset_resize_hitbox();
    }

    void Frame::reset_resize_hitbox()
    {
        vec2 hb_start(width - 8, height - 8);
        resize_hitbox = rect(hb_start, 8, 8);
    }

    void Frame::set_color(color& target, const std::string& hex)
    {
        target = hex_to_color(hex);
    }

    void Frame::set_normal_bg(const std::string& hex)
    {
        set_color(normal_bg, hex);
    }

    void Frame::set_focus_bg(const std::string& hex)
    {
        set_color(focus_bg, hex);
    }

    void Frame::set_hover_bg(const std::string& hex)
    {
        set_color(hover_bg, hex);
    }

    void Frame::set_drag_bg(const std::string& hex)
    {
        set_color(hold_bg, hex);
    }

    void Frame::set_border_color(const std::string& hex)
    {
        set_color(border, hex);
    }

    void Frame::set_border_thickness(const unsigned thickness)
    {
        border_thickness = thickness;
        needs_update = true;
    }

    void Frame::on_mouse_ev(const event& m, const bool btn_held)
    {
        if (!is_hittest_visible) return;
        if (size_changed) size_changed = false; // assume change was handled

        hovered = intersects(m.pos_x, m.pos_y);

        if (m.button == btn_left && !btn_held)
        {
            focused = hovered;
        }

        held = focused && (m.button == btn_left || btn_held);

        if (held && resizable)
        {
            vec2 rel_mouse(m.pos_x - start.x, m.pos_y - start.y);
            bool resize_hit = resize_hitbox.intersects(rel_mouse);

            resizing = resizing || (m.button == btn_left && resize_hit);
        }
        
        if (resizing && held)
        {
            vec2 m_limit;
            m_limit.x = std::max(m.pos_x, start.x + (int)min_width);
            m_limit.y = std::max(m.pos_y, start.y + (int)min_height);

            width  += m_limit.x - start.x - width;
            height += m_limit.y - start.y - height;
        }
        else if (is_draggable && held)
        {
            if (!is_dragged)
            {
                drag_center.x = m.pos_x - start.x;
                drag_center.y = m.pos_y - start.y;

                is_dragged = true;
            }

            start.x = m.pos_x - drag_center.x;
            start.y = m.pos_y - drag_center.y;

            start.x = std::min(std::max(start.x, 0), ENV_WIDTH - (int)width);
            start.y = std::min(std::max(start.y, 0), ENV_HEIGHT - (int)height);
        }
        else
        {
            if (resizing)
            {
                reset_resize_hitbox();

                rendered = canvas(width, height);
                size_changed = true;
                
                resizing = false;
                held = false;
            }
            if (is_dragged)
            {
                drag_center = start;
                is_dragged = false;
                held = false;
            }
        }
    }

    void Frame::render_resize_area()
    {
        rendered << move_to(resize_hitbox.start.x, resize_hitbox.start.y)
                 << DEFAULT_TEXT_NORMAL
                 << box(resize_hitbox.width, resize_hitbox.height);
    }

    void Frame::render()
    {
        if (held)
        {
            fill = hold_bg;
        }
        else if (focused)
        {
            fill = focus_bg;
        }
        else if (hovered)
        {
            fill = hover_bg;
        }
        else
        {
            fill = normal_bg;
        }

        int b = border_thickness;
        // std::cout << "Frame @ " << this << " updated\n";
        rendered << move_to(0, 0) << border << box(width, height)
                 << move_to(b, b) << fill << box(width - 2*b, height - 2*b);

        if (resizable)
        {
            render_resize_area();
        }
    }

    void Frame::draw(canvas& c)
    {
        if (resizing)
        {
            c << move_to(start.x, start.y)
              << border 
              << box(width, height);
        }
        else
        {
            if (needs_update)
            {
                render();
            }
            c << stamp(rendered, start.x, start.y);
        }
        needs_update = false;
    }
}