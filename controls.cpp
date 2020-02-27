#include "controls.hpp"
using namespace genv;

// hi

namespace Controls
{    
    // Point
    Point::Point(int x, int y) : x(x), y(y) {};
    Point::Point() : x(0), y(0) {};
    
    // Rect
    Rect::Rect(Point start, Point end) 
        : start(start), end(end),
          width(end.x - start.x), 
          height(end.y - start.y)
    {}

    Rect::Rect(Point start, int width, int height)
        : start(start), 
          end(start.x + width, start.y + height),
          width(width), 
          height(height)
    {}

    Rect::Rect(int width, int height)
        : start(0, 0), end(width, height),
          width(width), height(height)
    {}

    bool Rect::intersects(Point p) const
    {
        return start.x <= p.x && start.y <= p.y
            && end.x >= p.x && end.y >= p.y;
    }

    bool Rect::intersects(int x, int y) const
    {
        return start.x <= x && start.y <= y
            && end.x >= x && end.y >= y;
    }

    // Control base
    // initialize defaults
    Control::Control(Point start, Point end)
        : Rect(start, end),
          color_normal(DEFAULT_NORMAL), 
          color_hover(DEFAULT_HOVER),
          color_drag(DEFAULT_DRAG), 
          color_focus(DEFAULT_FOCUS),
          fill(DEFAULT_NORMAL), 
          border(DEFAULT_BORDER),
          border_thickness(10),
          _is_hovered(false), 
          _is_focused(false), 
          _is_dragging(false),
          _needs_update(true),
          _updated(true),
          drag_center(start),
          drag_start(start),
          is_draggable(true),
          rendered(width, height)
    {}

    Control::Control(Point start, int width, int height)
        : Control::Control(start, Point(start.x + width, start.y + height))
    {}

    inline void Control::set_drag(bool val)
    {
        _is_dragging = val;
        _needs_update = true;
        _updated = true;
    }

    inline void Control::set_color(color& target, const std::string& hex)
    {
        target = hex_to_color(hex);
    }

    bool Control::is_focused() const
    {
        return _is_focused;
    }

    bool Control::updated() const
    {
        return _updated;
    }

    void Control::set_normal_color(const std::string& hex)
    {
        set_color(color_normal, hex);
    }

    void Control::set_focus_color(const std::string& hex)
    {
        set_color(color_focus, hex);
    }

    void Control::set_hover_color(const std::string& hex)
    {
        set_color(color_hover, hex);
    }

    void Control::set_border_color(const std::string& hex)
    {
        set_color(border, hex);
    }

    void Control::set_border_thickness(const int thickness)
    {
        border_thickness = thickness;
    }

    void Control::set_hover(bool val)
    {
        _is_hovered = val;
        _needs_update = true;
        _updated = true;
    }

    void Control::set_focus(bool val)
    {
        _is_focused = val;
        _needs_update = true;
        _updated = true;
    }

    bool Control::check_drag(const event& mouse_ev, const int btn)
    {
        if (is_draggable)
        {
            if (btn == btn_left && _is_focused)
            {
                if (_is_hovered && !_is_dragging)
                {
                    drag_center.x = mouse_ev.pos_x;
                    drag_center.y = mouse_ev.pos_y;

                    drag_start = start;

                    set_drag(true);
                }

                if (_is_dragging)
                {
                    start.x = drag_start.x + mouse_ev.pos_x - drag_center.x;
                    start.y = drag_start.y + mouse_ev.pos_y - drag_center.y;

                    end.x = start.x + width;
                    end.y = start.y + height;

                    _updated = true;
                }
            }
            else if (_is_dragging)
            {
                set_drag(false);
            }
        }
        return _is_dragging;
    }
    
    void Control::render(canvas& c)
    {
        if (_needs_update)
        {
            if (_is_dragging)
            {
                fill = color_drag;
            }
            else if (_is_focused)
            {
                fill = color_focus;
            }
            else if (_is_hovered)
            {
                fill = color_hover;
            }
            else
            {
                fill = color_normal;
            }

            int b = border_thickness;
            rendered << move_to(0, 0) << border << box(width, height)
                    << move_to(b, b) << fill << box(width - 2*b, height - 2*b);
            _needs_update = false;
        }

        // TODO miert nem mukodsz
        int x = std::min(std::max(start.x, 0), ENV_WIDTH - (int)width);
        int y = std::min(std::max(start.y, 0), ENV_HEIGHT - (int)height);

        c << stamp(rendered, x, y);
        _updated = false;
    }

    // Scene
    Scene::Scene(int width, int height)
        : clear_screen(width, height)
    {}

    bool Scene::on_mouse_event(const event& ev)
    {
        click_buf += ev.button;

        // something is being dragged -> ignore others
        if (dragged == nullptr) 
        {
            for (int i = controls.size() - 1; i >= 0; i--)
            {
                Control& c = controls[i];
                if (c.intersects(ev.pos_x, ev.pos_y))
                {
                    // check highest hover
                    if (hovered != nullptr  && hovered != &c)
                    {
                        hovered->set_hover(false);
                    }
                    hovered = &c;
                    c.set_hover(true);

                    // check to assign focus
                    if (ev.button == btn_left && focused != &c)
                    {
                        if (focused != nullptr)
                        {
                            focused->set_focus(false);
                        }
                        focused = hovered;
                        c.set_focus(true);
                    }
                }
                else
                {
                    c.set_hover(false);
                    if (ev.button == btn_left && focused == &c)
                    {
                        focused->set_focus(false);
                        focused = nullptr;
                    }
                }   
            }
        }
        
        if (focused != nullptr && focused->check_drag(ev, click_buf))
        {
            dragged = focused;
        }
        else
        {
            dragged = nullptr;
        }
        
        
        for (const Control& f : controls)
        {
            if (f.updated())
            {
                return true;
            }
        }
        return false;
    }

    void Scene::render(canvas& c)
    {
        c << stamp(clear_screen, 0, 0);
        for (int i = controls.size() - 1; i >= 0; i--)
        {
            controls[i].render(c);
        }
    }

    void Scene::add_control(const Control& c)
    {
        controls.push_back(c);
    }
}