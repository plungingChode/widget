#include "frame.hpp"
#include "control_common.hpp"

using namespace genv;

namespace Controls
{
    Frame::Frame(vec2 start, int width, int height)
        : rect(start, width, height),
          Control(start),
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

    void Frame::set_resizable(const bool val)
    {
        is_resizable_ = val;
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
        needs_visual_update_ = true;
    }

    void Frame::on_mouse_ev(const event& m, const bool btn_held)
    {
        if (!is_hittest_visible) return;
        if (size_changed_) size_changed_ = false; // assume change was handled

        is_hovered_ = intersects(m.pos_x, m.pos_y);

        if (m.button == btn_left && !btn_held)
        {
            is_focused_ = is_hovered_;
        }

        is_held_ = is_focused_ && (m.button == btn_left || btn_held);

        if (is_held_ && is_resizable_)
        {
            vec2 rel_mouse(m.pos_x - start.x, m.pos_y - start.y);
            bool resize_hit = resize_hitbox.intersects(rel_mouse);

            is_resizing_ = is_resizing_ || (m.button == btn_left && resize_hit);
        }
        
        if (is_resizing_ && is_held_)
        {
            vec2 m_limit;
            m_limit.x = std::max(m.pos_x, start.x + (int)min_width);
            m_limit.y = std::max(m.pos_y, start.y + (int)min_height);

            width  += m_limit.x - start.x - width;
            height += m_limit.y - start.y - height;
        }
        else if (is_draggable && is_held_)
        {
            if (!is_dragging_)
            {
                drag_center.x = m.pos_x - start.x;
                drag_center.y = m.pos_y - start.y;

                is_dragging_ = true;
            }

            start.x = m.pos_x - drag_center.x;
            start.y = m.pos_y - drag_center.y;

            start.x = std::min(std::max(start.x, 0), ENV_WIDTH - (int)width);
            start.y = std::min(std::max(start.y, 0), ENV_HEIGHT - (int)height);
        }
        else
        {
            if (is_resizing_)
            {
                reset_resize_hitbox();

                rendered = canvas(width, height);
                size_changed_ = true;
                
                is_resizing_ = false;
                is_held_ = false;
            }
            if (is_dragging_)
            {
                drag_center = start;
                is_dragging_ = false;
                is_held_ = false;
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
        if (is_held_)
        {
            fill = hold_bg;
        }
        else if (is_focused_)
        {
            fill = focus_bg;
        }
        else if (is_hovered_)
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

        if (is_resizable_)
        {
            render_resize_area();
        }
    }

    void Frame::draw(canvas& c)
    {
        if (is_resizing_)
        {
            c << move_to(start.x, start.y)
              << border 
              << box(width, height);
        }
        else
        {
            if (needs_visual_update_)
            {
                render();
            }
            c << stamp(rendered, start.x, start.y);
        }
        needs_visual_update_ = false;
    }
}