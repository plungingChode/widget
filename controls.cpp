#include "controls.hpp"
#include <iostream>
using namespace genv;

namespace Controls
{    
    // Point
    Point::Point(int x, int y) : x(x), y(y) {};
    Point::Point() : x(0), y(0) {};

    // Margin
    Margin::Margin(int top, int left, int bottom, int right)
        : top(top), left(left), bottom(bottom), right(right)
    {}
    Margin::Margin(int all) 
        : Margin(all, all, all, all) 
    {}
    Margin::Margin(int horizontal, int vertical)
        : Margin(vertical, horizontal, vertical, horizontal)
    {} 
    Margin::Margin() 
        : Margin(0, 0, 0, 0)
    {}

    
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
    Control::Control(Point drag_center, Point drag_start)
        : drag_center(drag_center),
          drag_start(drag_start),
          _is_hovered(false), 
          _is_focused(false), 
          _is_dragging(false),
          _needs_update(true),
          _updated(true),
          is_draggable(true)
    {
    }

    void Control::set_hover(bool val)
    {
        _is_hovered = val;
        _needs_update = true;
        _updated = true;
        // std::cout << "Control @ " << this << " - hover changed\n";
    }

    void Control::set_focus(bool val)
    {
        _is_focused = val;
        _needs_update = true;
        _updated = true;
        // std::cout << "Control @ " << this << " - focus changed\n";
    }

    inline void Control::set_drag(bool val)
    {
        _is_dragging = val;
        _needs_update = true;
        _updated = true;
        // std::cout << "Control @ " << this << " - drag changed\n";
    }   

    bool Control::is_focused() const
    {
        return _is_focused;
    }

    bool Control::updated() const
    {
        return _updated;
    }
    
    // Frame
    Frame::Frame(Point start, int width, int height)
        : Rect(start, width, height),
          Control(start, start),
          rendered(width, height),
          normal_bg(DEFAULT_NORMAL), 
          hover_bg(DEFAULT_HOVER),
          drag_bg(DEFAULT_MOUSEDOWN), 
          focus_bg(DEFAULT_FOCUS),
          fill(DEFAULT_NORMAL), 
          border(DEFAULT_BORDER),
          border_thickness(10)
    {
        std::cout << &rendered << '\n';
    }

    Frame::Frame(Point start, Point end)
        : Frame(start, end.x - start.x, end.y - start.y)
    {
    }

        inline void Frame::set_color(color& target, const std::string& hex)
    {
        target = hex_to_color(hex);
    }


    void Frame::set_normal_color(const std::string& hex)
    {
        set_color(normal_bg, hex);
    }

    void Frame::set_focus_color(const std::string& hex)
    {
        set_color(focus_bg, hex);
    }

    void Frame::set_hover_color(const std::string& hex)
    {
        set_color(hover_bg, hex);
    }

    void Frame::set_border_color(const std::string& hex)
    {
        set_color(border, hex);
    }

    void Frame::set_border_thickness(const int thickness)
    {
        border_thickness = thickness;
        _needs_update = true;
    }

    bool Frame::check_hover(const event& mouse_ev)
    {
        return intersects(mouse_ev.pos_x, mouse_ev.pos_y);
    }

    bool Frame::check_drag(const event& mouse_ev, const int btn)
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

                    start.x = std::min(std::max(start.x, 0), ENV_WIDTH - (int)width);
                    start.y = std::min(std::max(start.y, 0), ENV_HEIGHT - (int)height);
                    
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

    void Frame::render()
    {
        // std::cout << "Calling Frame::render()\n"; 
        if (_is_dragging)
        {
            fill = drag_bg;
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
    }

    void Frame::draw(canvas& c)
    {
        if (_needs_update)
        {
            render();
            _needs_update = false;
        }
        c << stamp(rendered, start.x, start.y);
        _updated = false;
    }

    //Label
    Label::Label(Point start, const std::string& text, Margin padding)
        : text_fill_normal(DEFAULT_TEXT_NORMAL),
          text_fill_focused(DEFAULT_TEXT_FOCUS),
          text(text),
          text_width(rendered.twidth(text)),
          char_ascent(rendered.cascent()),
          char_descent(rendered.cdescent()),
          text_x(width  / 2 - rendered.twidth(text) / 2),
          text_y(height / 2 + rendered.cdescent()),
          padding(padding),
          Frame(start,
            Point(start.x 
                    + padding.left + padding.right 
                    + rendered.twidth(text) 
                    + 2*border_thickness,
                  start.y 
                    + padding.top  + padding.bottom 
                    + rendered.cdescent() + rendered.cascent() 
                    + 2*border_thickness))
    {
    }

    Label::Label(Point start, int width, int height, const std::string& text)
        : Label(start, text, 
            Margin((width - start.x) / 2, 
                   (height - start.x) / 2))
    {
    }

    Label::Label(Point start, const std::string& text, int padding)
        : Label(start, text, Margin(padding))
    {
    }

    void Label::render()
    {
        Frame::render();
        if (_is_focused)
        {   
            rendered << move_to(text_x, text_y)
                    << text_fill_focused << genv::text(text);
        }
        else
        {
            rendered << move_to(text_x, text_y)
                    << text_fill_normal << genv::text(text);
        }
    }

    // Button
    Button::Button(
        Point start, int width, int height, 
        canvas content, Point content_offset, 
        void (*action)())
        :
        Frame(start, width, height), 
        content(content), 
        content_offset(content_offset), 
        action(action),
        is_held(false)
    {
        this->is_draggable = false;
    }

    Button::Button(
        Point start, int width, int height,
        canvas content, void (*action)())
        :
        Button(start, width, height, content, Point(0, 0), action)
    {
    }

    inline void Button::set_held(bool val)
    {
        is_held = val;
        _needs_update = true;
        _updated = true;
    }

    void Button::on_mouse_ev(const event& mev)
    {
        if (mev.button == btn_left)
        {
            set_held(true);
        }
        if (mev.button == -btn_left)
        {
            if (intersects(mev.pos_x, mev.pos_y))
            {
                action();
            }
            set_held(false);
        }
    }

    void Button::render()
    {
        if (is_held)
        {
            fill = drag_bg;
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
                 << move_to(b, b) << fill << box(width - 2*b, height - 2*b)
                 << stamp(content, content_offset.x, content_offset.y);
    }

    // Scene
    Scene::Scene(int width, int height)
        : clear_screen(width, height)
    {
        ENV_WIDTH = width;
        ENV_HEIGHT = height;
    }

    Scene::~Scene()
    {
        for (Control*& c : controls)
        {
            delete c;
        }
    }

    bool Scene::on_mouse_event(const event& ev)
    {
        click_buf += ev.button;

        // something is being dragged -> ignore others
        // hover unchanged -> ignore others
        if (dragged == nullptr)
        {
            for (Control*& c : controls)
            {
                // Control*& c = controls[i];
                if (c->check_hover(ev))
                {
                    // check highest hover
                    if (hovered != c)
                    {
                        if (hovered != nullptr)
                        {
                            hovered->set_hover(false);
                        }
                        hovered = c;
                        c->set_hover(true);
                    }

                    // check to assign focus
                    if (ev.button == btn_left && focused != c)
                    {
                        // std::cout << "something was focused!\n";
                        if (focused != nullptr)
                        {
                            focused->set_focus(false);
                        }
                        focused = hovered;
                        c->set_focus(true);
                    }
                    break;
                }
                else
                {
                    if (hovered == c)
                    {
                        hovered->set_hover(false);
                        hovered = nullptr;
                    }
                    if (ev.button == btn_left && focused == c)
                    {
                        focused->set_focus(false);
                        focused = nullptr;
                    }
                }   
            }
        }
        
        if (focused != nullptr)
        {
            focused->on_mouse_ev(ev);
            if (focused->check_drag(ev, click_buf))
            {
                dragged = focused;
            }
        }
        else
        {
            dragged = nullptr;
        }
        
        
        for (Control*& c : controls)
        {
            if (c->updated())
            {
                // std::cout << "Button updated\n";
                return true;
            }
        }
        return false;
    }

    bool Scene::on_key_event(const event& kev)
    {
        if (focused != nullptr)
        {
            focused->on_key_ev(kev);
            return focused->updated();
        }
        return false;
    }

    void Scene::render(canvas& c)
    {
        c << stamp(clear_screen, 0, 0);
        for (int i = controls.size() - 1; i >= 0; i--)
        {
            controls[i]->draw(c);
        }
    }

    void Scene::add_control(Control* c)
    {
        controls.push_back(c);
    }
}