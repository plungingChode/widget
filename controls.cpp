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

    Point Rect::get_start() { return start; }
    Point Rect::get_end() { return end; }
    unsigned int Rect::get_width() { return width; }
    unsigned int Rect::get_height() { return height; }

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

    // Control (base)
    Control::Control(Point drag_center, Point drag_start)
        : drag_center(drag_center),
          drag_start(drag_start),
          _is_hovered(false), 
          _is_focused(false), 
          _is_held(false),
          _needs_visual_update(true),
          is_hittest_visible(true),
          is_draggable(true)
    {
    }

    void Control::update_visuals()
    {
        _needs_visual_update = true;
    }

    bool Control::is_focused() const
    {
        return _is_focused;
    }

    bool Control::is_hovered() const
    {
        return _is_hovered;
    }

    bool Control::is_held() const
    {
        return _is_held;
    }

    bool Control::updated() const
    {
        return _needs_visual_update;
    }
    
    // Frame
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
          border_thickness(10)
    {
        // std::cout << &rendered << '\n';
    }

    Frame::Frame(Point start, Point end)
        : Frame(start, end.x - start.x, end.y - start.y)
    {
    }

    inline void Frame::set_color(color& target, const std::string& hex)
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

    void Frame::set_border_thickness(const int thickness)
    {
        border_thickness = thickness;
        _needs_visual_update = true;
    }

    void Frame::on_mouse_ev(const event& m, const bool btn_held)
    {
        if (!is_hittest_visible) return;

        _is_hovered = intersects(m.pos_x, m.pos_y);

        if (m.button == btn_left && !btn_held)
        {
            _is_focused = _is_hovered;
        }

        _is_held =  _is_focused && (m.button == btn_left || btn_held);

        if (!is_draggable) return;

        if (_is_held)
        {
            if (drag_center.x == start.x)
            {
                drag_center.x = m.pos_x;
                drag_center.y = m.pos_y;

                drag_start = start;
            }

            start.x = drag_start.x + m.pos_x - drag_center.x;
            start.y = drag_start.y + m.pos_y - drag_center.y;

            start.x = std::min(std::max(start.x, 0), ENV_WIDTH - (int)width);
            start.y = std::min(std::max(start.y, 0), ENV_HEIGHT - (int)height);
            
            end.x = start.x + width;
            end.y = start.y + height;
        }
        else
        {
            _is_held = false;
            drag_center = start;
        }
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
    }

    void Frame::draw(canvas& c)
    {
        if (_needs_visual_update)
        {
            render();
        }
        c << stamp(rendered, start.x, start.y);
        _needs_visual_update = false;
    }

    // Label
    // default border thickness = 1
    Label::Label(Point start, const std::string& text, Margin padding)
        : text_fill_normal(DEFAULT_TEXT_NORMAL),
          text_fill_focused(DEFAULT_TEXT_FOCUS),
          text(text),
          text_width(rendered.twidth(text)),
          char_ascent(rendered.cascent()),
          char_descent(rendered.cdescent()),
          text_x(width  / 2 - rendered.twidth(text) / 2),
          text_y(height / 2 + rendered.cdescent() - rendered.cascent()),
          padding(padding),
          Frame(start,
            Point(start.x 
                    + padding.left + padding.right 
                    + rendered.twidth(text) 
                    + 2*2,
                  start.y 
                    + padding.top  + padding.bottom 
                    + rendered.cdescent() + rendered.cascent() 
                    + 2*2))
    {
        Frame::border_thickness = 1;
        Control::is_hittest_visible = false;
    }

    Label::Label(Point start, const std::string& text, int width, int height)
        : Label(start, text, 
            Margin((width  - rendered.twidth(text)) / 2, 
                   (height - (rendered.cdescent() + rendered.cascent())) / 2))
    {
    }

    Label::Label(Point start, const std::string& text, int padding)
        : Label(start, text, Margin(padding))
    {
    }

    void Label::set_text_fill_normal(const std::string& hex)
    {
        set_color(text_fill_normal, hex);
    }

    void Label::set_font(const std::string& font_src, int font_size)
    {
        rendered.load_font(font_src, font_size);
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
        rendered << move_to(width - 8, height - 8)
                 << color(0, 0, 0) << box(8, 8);
    }

    // void Label::on_mouse_ev(const event& m)
    // {
    //     // if ()
    // }


    // Button
    // button is not draggable by default
    Button::Button(Point start, const std::string& text, Margin padding, void (*action)())
        : Label(start, text, padding), action(action)
    {
        Frame::rendered.transparent(true);
        Control::is_draggable = false;
        Control::is_hittest_visible = true;
    }

    Button::Button(Point start, const std::string& text, int width, int height, void (*action)())
        : Label(start, text, width, height), action(action)
    {
        Frame::rendered.transparent(true);
        Control::is_draggable = false;
        Control::is_hittest_visible = true;
    }

    void Button::on_mouse_ev(const event& m, const bool btn_held)
    {
        if (m.button == -btn_left && _is_held && _is_hovered)
        {
            if (_is_hovered)
            {
                action();
            }
        }
        Frame::on_mouse_ev(m, btn_held);
    }

    // TODO replace color(0,0,0) with static BLACK
    void Button::render()
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

        // leave gap for bevel effect
        rendered 
            << move_to(0, 0) << color(0, 0, 0) << box(width, height)
            << move_to(0, 0) << fill << box(width - b, height - b);

        if (_is_held)
        {
            // bevel on the bottom right, push in text
            rendered 
                << move_to(1, height-b) << border << box(width-1, b)
                << move_to(width-b, 1) << border << box(b, height-1)
                << move_to(text_x + b, text_y + b) << text_fill_normal << genv::text(text);
        }
        else
        {
            // bevel on the top left
            rendered 
                << move_to(0, 0) << border << box(width-b, b)
                << move_to(0, 0) << border << box(b, height-b)
                << move_to(text_x, text_y) << text_fill_normal << genv::text(text);
        } 
    }

    // // TextBox
    // TextBox::TextBox(Point start, const std::string& text, Margin padding)
    //     : Label(start, text, padding)
    // {
    // }

    // TextBox::TextBox(Point start, const std::string& text, int width, int height)
    //     : Label(start, text, width, height)
    // {
    // }

    // void TextBox::on_key_ev(const event& kev)
    // {
    //     // visible char: 32 - 255
    // }

    // Scene
    // TODO share common background color
    void Scene::render_background()
    {
        background 
            << move_to(0, 0) 
            << BACKGROUND_COLOR
            << box(ENV_WIDTH, ENV_HEIGHT);
    }

    Scene::Scene(int width, int height)
        : background(width, height)
    {
        ENV_WIDTH = width;
        ENV_HEIGHT = height;
        render_background();
    }

    Scene::~Scene()
    {
        for (Control*& c : controls)
        {
            delete c;
        }
    }

    bool Scene::on_mouse_event(const event& m)
    {
        click_buffer += m.button;
        mouse_held = (click_buffer != 0 && m.button == 0);

        // something is being held -> ignore others
        // hover unchanged -> ignore others
        if (held == nullptr)
        {
            for (Control*& c : controls)
            {
                c->on_mouse_ev(m, mouse_held);

                if (c->is_hittest_visible && c->is_hovered())
                {
                    // check first hover
                    if (hovered != c)
                    {
                        if (hovered != nullptr)
                        {
                            hovered->_is_hovered = false;
                            hovered->update_visuals();
                        }
                        hovered = c;
                        c->update_visuals();
                    }

                    // check to assign focus
                    if (focused != c && c->is_focused())
                    {
                        if (focused != nullptr)
                        {
                            focused->_is_focused = false;
                            focused->update_visuals();
                        }
                        focused = hovered;
                        c->update_visuals();
                    }
                    break;
                }
            }
        }
        else
        {
            // something held -> update hold state
            held->on_mouse_ev(m, mouse_held);
        }
        
        if (hovered != nullptr && !hovered->is_hovered())
        {
            hovered->_is_hovered = false;
            hovered->update_visuals();
            hovered = nullptr;
        }

        // check for click outside of control
        if (m.button == btn_left && focused != nullptr && hovered == nullptr)
        {
            focused->_is_focused = false;
            focused->update_visuals();
            focused = nullptr;
        }
    
// TODO on drag end: check for hover!
        // check for drag
        if (focused != nullptr)
        {
            if (focused->is_held())
            {
                held = focused;
                held->update_visuals();
            }
            else if (held != nullptr)
            {
                held->update_visuals();
                held = nullptr;
            }
        }
    
// TODO set local variable to avoid another loop?
        for (Control*& c : controls)
        {
            if (c->updated())
            {
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
        c << stamp(background, 0, 0);
        for (int i = controls.size() - 1; i >= 0; i--)
        {
            controls[i]->draw(c);
        }
    }

    void Scene::add_control(Control* c)
    {
        controls.push_back(c);
    }

    int Scene::run(bool fullscreen)
    {
        gout.open(ENV_WIDTH, ENV_HEIGHT, fullscreen);

        event ev;
        while (gin >> ev)
        {
            if (ev.type == ev_key)
            {
                on_key_event(ev);
                
                if (ev.keycode == key_escape)
                {
                    return 0;
                }
            }

            if (ev.type == ev_mouse)
            {
                if (on_mouse_event(ev))
                {
                    render(gout);
                    gout << refresh;
                }
            }
        }
        return 0;
    }
}