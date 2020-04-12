#include "frame.hpp"
#include "control_common.hpp"

using namespace genv;

namespace Controls
{
    Frame::Frame(vec2 start, int width, int height)
        : Control(start),
          rect(start, width, height),
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

    void Frame::set_color(color& target, int hex)
    {
        target = hex_to_color(hex);
        schedule_update();
    }

    void Frame::set_border_thickness(const unsigned thickness)
    {
        border_thickness = thickness;
        schedule_update();
    }

    void Frame::on_mouse_ev(const event& m, const bool btn_held)
    {
        if (!hittest_visible) return;
        size_changed = false; // assume change was handled

        hovered = intersects(m.pos_x, m.pos_y);

        if (m.button == btn_left && !btn_held)
        {
            focused = hovered;
        }

        held = focused && (m.button == btn_left || btn_held);

        if (held && resizable)
        {
            vec2 m_rel(m.pos_x - start.x, m.pos_y - start.y);
            bool resize_hit = resize_hitbox.intersects(m_rel);

            resizing = resizing || (m.button == btn_left && resize_hit);
        }
        
        if (resizing && held)
        {
            vec2 m_limit(
                std::max(m.pos_x, start.x + (int)min_width),
                std::max(m.pos_y, start.y + (int)min_height)
            );
            
            width  += m_limit.x - start.x - width;
            height += m_limit.y - start.y - height;
        }
        else if (draggable && held)
        {
            if (!dragged)
            {
                drag_center.x = m.pos_x - start.x;
                drag_center.y = m.pos_y - start.y;

                dragged = true;
            }

            start.x = force_bounds(m.pos_x - drag_center.x, 0, ENV_WIDTH - (int)width);
            start.y = force_bounds(m.pos_y - drag_center.y, 0, ENV_HEIGHT - (int)height);
        }
        else
        {
            if (resizing)
            {
                reset_resize_hitbox();

                size_changed = true;
                
                resizing = false;
                held = false;
            }
            if (dragged)
            {
                drag_center = start;
                dragged = false;
                held = false;
            }
        }
    }

    void Frame::render_resize_area()
    {
        rendered 
            << move_to(resize_hitbox.start.x, resize_hitbox.start.y)
            << DEFAULT_TEXT_NORMAL
            << box(resize_hitbox.width, resize_hitbox.height);
    }

    void Frame::update()
    {
        if (size_changed)
        {
            rendered = canvas(width, height);
        }

        // draw border
        rendered 
            << move_to(0, 0) 
            << border << box(width, height);

        // draw interior
        if (held)
        {
            rendered << hold_bg;
        }
        else if (focused)
        {
            rendered << focus_bg;
        }
        else if (hovered)
        {
            rendered << hover_bg;
        }
        else
        {
            rendered << normal_bg;
        }
        
        rendered 
            << move_to(border_thickness, border_thickness) 
            << box(width-2*border_thickness, height-2*border_thickness);

        // draw resize marker
        if (resizable)
        {
            render_resize_area();
        }
    }

    void Frame::render(canvas& c)
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
                update();
                needs_update = false;
            }
            c << stamp(rendered, start.x, start.y);
        }
    }
}