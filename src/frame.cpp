#include "frame.hpp"
#include "control_common.hpp"

using namespace genv;

namespace Controls
{
    Frame::Frame(int x_, int y_, int w_, int h_, const genv::font *f)
        : Control(x_, y_, w_, h_, f),
          border_thickness(10),
          min_width(15), 
          min_height(15)
    {
    }

    void Frame::set_resizable(bool val)
    {
        resizable = val;
        reset_resize_hitbox();
    }

    void Frame::reset_resize_hitbox()
    {
        vec2 hb_start(w-8, h-8);
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
            vec2 m_rel(m.pos_x - x, m.pos_y - y);
            bool resize_hit = resize_hitbox.intersects(m_rel);

            resizing = resizing || (m.button == btn_left && resize_hit);
        }
        
        if (resizing && held)
        {
            vec2 m_limit(
                std::max((unsigned)m.pos_x, x + min_width),
                std::max((unsigned)m.pos_y, y + min_height)
            );
            
            w += m_limit.x - x - w;
            h += m_limit.y - y - h;
        }
        else if (draggable && held)
        {
            if (!dragged)
            {
                drag_center.x = m.pos_x - x;
                drag_center.y = m.pos_y - y;

                dragged = true;
            }

            x = force_bounds(m.pos_x - drag_center.x, 0, ENV_WIDTH - w);
            y = force_bounds(m.pos_y - drag_center.y, 0, ENV_HEIGHT - h);
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
                drag_center = vec2(x, y); // necessary?
                dragged = false;
                held = false;
            }
        }
    }

    void Frame::render_resize_area()
    {
        rendered 
            << move_to(resize_hitbox.x, resize_hitbox.y)
            << DEFAULT_TEXT_NORMAL
            << box(resize_hitbox.w, resize_hitbox.h);
    }

    void Frame::update()
    {
        if (size_changed)
        {
            rendered = canvas(w, h);
            set_font(this->font);
        }

        // draw border
        rendered 
            << move_to(0, 0) 
            << border << box(w, h);

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
            << box(w-2*border_thickness, h-2*border_thickness);

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
            c << move_to(x, y)
              << border 
              << box(w, h);
        }
        else
        {
            if (needs_update)
            {
                update();
                needs_update = false;
            }
            c << stamp(rendered, x, y);
        }
    }
}