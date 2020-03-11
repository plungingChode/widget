#include "frame.hpp"
#include "control_common.hpp"

using namespace genv;

namespace Controls
{
    Frame::Frame(Point start, int width, int height)
        : Rect(start, width, height),
          Control(start, start),
          rendered(width, height),
          normal_bg(DEFAULT_NORMAL), 
          hover_bg(DEFAULT_HOVER),
          hold_bg(DEFAULT_MOUSEDOWN), 
          focus_bg(DEFAULT_FOCUS),
          fill(DEFAULT_NORMAL), 
          border(DEFAULT_BORDER),
          border_thickness(10),
          min_width(15),
          min_height(15)
    {
        // std::cout << &rendered << '\n';
    }

    Frame::Frame(Point start, Point end)
        : Frame(start, end.x - start.x, end.y - start.y)
    {
    }

    void Frame::set_resizable(const bool val)
    {
        _is_resizable = val;
        reset_resize_hitbox();
    }

    void Frame::reset_resize_hitbox()
    {
        Point hb_start(width - 8, height - 8);
        resize_hitbox = Rect(hb_start, 8, 8);
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
        _needs_visual_update = true;
    }

    void Frame::on_mouse_ev(const event& m, const bool btn_held)
    {
        if (!is_hittest_visible) return;
        if (_size_changed) _size_changed = false; // assume change was handled

        _is_hovered = intersects(m.pos_x, m.pos_y);

        if (m.button == btn_left && !btn_held)
        {
            _is_focused = _is_hovered;
        }

        _is_held = _is_focused && (m.button == btn_left || btn_held);

        if (_is_held && _is_resizable)
        {
            Point rel_mouse(m.pos_x - start.x, m.pos_y - start.y);
            bool resize_hit = resize_hitbox.intersects(rel_mouse);

            _is_resizing = _is_resizing || (m.button == btn_left && resize_hit);
        }
        
        if (_is_resizing && _is_held)
        {
            Point m_limit;
            m_limit.x = std::max(m.pos_x, start.x + (int)min_width);
            m_limit.y = std::max(m.pos_y, start.y + (int)min_height);

            width  += m_limit.x - start.x - width;
            height += m_limit.y - start.y - height;
        }
        else if (is_draggable && _is_held)
        {
            if (!_is_dragging)
            {
                drag_center.x = m.pos_x - start.x;
                drag_center.y = m.pos_y - start.y;

                // drag_start = start;
                _is_dragging = true;
            }

            // start.x = drag_start.x + m.pos_x - drag_center.x;
            // start.y = drag_start.y + m.pos_y - drag_center.y;
            start.x = m.pos_x - drag_center.x;
            start.y = m.pos_y - drag_center.y;

            start.x = std::min(std::max(start.x, 0), ENV_WIDTH - (int)width);
            start.y = std::min(std::max(start.y, 0), ENV_HEIGHT - (int)height);

            end = start + Point(width, height);
        }
        else
        {
            if (_is_resizing)
            {
                reset_resize_hitbox();
                end.x = start.x + width;
                end.y = start.y + height;

                rendered = canvas(width, height);
                _size_changed = true;
                
                _is_resizing = false;
                _is_held = false;
            }
            if (_is_dragging)
            {
                drag_center = start;
                _is_dragging = false;
                _is_held = false;
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
        if (_is_held)
        {
            fill = hold_bg;
        }
        else if (_is_focused)
        {
            fill = focus_bg;
        }
        else if (_is_hovered)
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

        if (_is_resizable)
        {
            render_resize_area();
        }
    }

    void Frame::draw(canvas& c)
    {
        if (_is_resizing)
        {
            c << move_to(start.x, start.y)
              << border 
              << box(width, height);
        }
        else
        {
            if (_needs_visual_update)
            {
                render();
            }
            c << stamp(rendered, start.x, start.y);
        }
        _needs_visual_update = false;
    }
}