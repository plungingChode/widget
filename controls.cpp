#include "controls.hpp"
#include <iostream>
using namespace genv;

namespace Controls
{    
    // static
    color hex_to_color(const std::string& h)
    {
        int n;
        std::istringstream(h) >> std::hex >> n;
        int b = n % 256;
        n/= 256;
        int g = n % 256;
        n /= 256;
        int r = n % 256;
        return color(r, g, b);
    }

    canvas read_kep(const std::string& fname)
    {
        std::ifstream f(fname);
        int width, height;
        f >> width >> std::ws;
        f >> height >> std::ws;

        canvas c(width, height); 

        int x, y;
        int r, g, b;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                f >> r >> g >> b;

                c << move_to(x, y) 
                << color(r, g, b) 
                << dot;
            }
        }
        c.transparent(true);
        return c;
    }

    // Point
    Point::Point(int x, int y) : x(x), y(y) {};
    Point::Point() : x(0), y(0) {};

    void Point::operator+=(const Point& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
    }
    void Point::operator-=(const Point& rhs)
    {
        this->x -= rhs.x;
        this->y += rhs.y;
    }
    Point operator+(const Point& lhs, const Point& rhs)
    {
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    Point operator-(const Point& lhs, const Point& rhs)
    {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }

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

    Rect::Rect() : Rect(0, 0)
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
          is_draggable(true),
          _is_dragging(false),
          _is_resizable(false),
          _is_resizing(false),
          _size_changed(false)
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
                drag_center.x = m.pos_x;
                drag_center.y = m.pos_y;

                drag_start = start;
                _is_dragging = true;
            }

            start.x = drag_start.x + m.pos_x - drag_center.x;
            start.y = drag_start.y + m.pos_y - drag_center.y;

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

    // Label
    // default border thickness = 1
    Label::Label(Point start, const std::string& text, Margin padding, TextAlign align)
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
                    + rendered.twidth(text),
                  start.y 
                    + padding.top  + padding.bottom 
                    + rendered.cdescent() + rendered.cascent()))
    {
        Frame::border_thickness = 1;
        Control::is_hittest_visible = false;
    }

    Label::Label(Point start, const std::string& text, int width, int height, TextAlign align)
        : Label(start, text, 
            Margin((width  - rendered.twidth(text)) / 2, 
                   (height - (rendered.cdescent() + rendered.cascent())) / 2))
    {
    }

    Label::Label(Point start, const std::string& text, int padding, TextAlign align)
        : Label(start, text, Margin(padding))
    {
    }

    void Label::set_text(const std::string& text)
    {
        this->text = text;
        update_visuals();
    }

    void Label::set_text_fill_normal(const std::string& hex)
    {
        set_color(text_fill_normal, hex);
    }

    void Label::set_font(const std::string& font_src)
    {
        rendered.load_font(font_src);
        this->font_src = font_src;
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

    void Label::on_mouse_ev(const event& m, const bool btn_held)
    {
        Frame::on_mouse_ev(m, btn_held);
        if (_size_changed)
        {
            // std::cout << "Reload font\n";
            rendered.load_font(font_src);
        }
    }

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
        // std::cout << "held: " << _is_held << "btn: " << m.button <<  '\n';
        if (m.button == -btn_left && _is_held && _is_hovered)
        {
            action();
        }
        Label::on_mouse_ev(m, btn_held);
        if (_size_changed)
        {
            rendered.transparent(true);
        }
    }

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
            << move_to(0, 0) << BLACK << box(width, height)
            << move_to(0, 0) << fill << box(width - b, height - b);

        if (_is_held)
        {
            // bevel on the bottom right, push in text
            rendered 
                << move_to(1, height-b) << border << box(width-1, b)
                << move_to(width-b, 1) << border << box(b, height-1)
                << move_to(text_x + b+1, text_y + b+1) << text_fill_normal << genv::text(text);
        }
        else
        {
            // bevel on the top left
            rendered 
                << move_to(0, 0) << border << box(width-b, b)
                << move_to(0, 0) << border << box(b, height-b)
                << move_to(text_x, text_y) << text_fill_normal << genv::text(text);
        }
        if(_is_resizable)
        {
            render_resize_area();
        }
    }

    // Spinner
    Spinner::Spinner(Point start, int value, int width, int height)
        : Label(start, std::to_string(value), width, height),
          min_value(INT_MIN),
          max_value(INT_MAX),
          value(value),
          spin_color(DEFAULT_MOUSEDOWN)
    {
        Control::is_draggable = false;
        Frame::hold_bg = DEFAULT_FOCUS;
        set_spinner_hitboxes();
    }

    Spinner::Spinner(Point start, int value, Margin padding)
        : Label(start, std::to_string(value), padding),
          min_value(INT_MIN),
          max_value(INT_MAX),
          value(value),
          spin_color(DEFAULT_MOUSEDOWN)
    {
        Control::is_draggable = false;
        Frame::hold_bg = DEFAULT_FOCUS;
        set_spinner_hitboxes();
    }

    void Spinner::set_spinner_hitboxes()
    {
        unsigned int& b = border_thickness;
        spin_up_hitbox = Rect(Point(width - 17 - b, b), Point(width - b, height / 2));
        spin_dn_hitbox = Rect(Point(width - 17 - b, height / 2), Point(width - b, height - b));
        spin_up_icon = read_kep("uarrow.kep");
        spin_dn_icon = read_kep("dnarrow.kep");
    }

    void Spinner::set_spin_color(const std::string& hex)
    {
        set_color(spin_color, hex);
    }

    void Spinner::set_value(const int val)
    {     
        value = std::max(std::min(val, max_value), min_value);
        set_text(std::to_string(value));
    }

    int Spinner::get_value() const
    {
        return value;
    }
    
    void Spinner::on_mouse_ev(const event& m, const bool btn_held)
    {
        Label::on_mouse_ev(m, btn_held);

        spin = NONE;
        if (_is_focused)
        {
            int value_change = 0;
            if (m.button == btn_wheelup)
            {
                value_change = 1;
            }
            else if (m.button == btn_wheeldown)
            {
                value_change = -1;
            }
            else if (m.button == btn_left)
            {
                // std::cout << "mbutton released\n";
                Point mouse = Point(m.pos_x, m.pos_y) - start;
                if (spin_up_hitbox.intersects(mouse))
                {
                    value_change = 1;
                    spin = BTN_UP;
                }
                else if (spin_dn_hitbox.intersects(mouse))
                {
                    value_change = -1;
                    spin = BTN_DOWN;
                }
            }
            set_value(value+value_change);
        }
    }

    void Spinner::on_key_ev(const event& k, const bool key_held)
    {
        // std::cout << "Spin w/ key\n";
        if (_is_focused)
        {
            switch (k.keycode)
            {
            case key_up:
                set_value(value+1);
                break;

            case key_down:
                set_value(value-1);
                break;

            case key_pgup:
                set_value(value+10);
                break;

            case key_pgdn:
                set_value(value-10);
                break;

            default:
                break;
            }
        }
    }

    void Spinner::render()
    {
        Label::render();
        color btn_border = text_fill_normal;
        color btn_up_bg = normal_bg;
        color btn_dn_bg = normal_bg;

        if (spin == BTN_DOWN)
        {
            btn_dn_bg = spin_color;
        }
        else if (spin == BTN_UP)
        {
            btn_up_bg = spin_color;
        }

        Rect& r1 = spin_up_hitbox;
        rendered << move_to(r1.start.x, r1.start.y)
                 << btn_border
                 << box(r1.width, r1.height)
                 << move_to(r1.start.x + 1, r1.start.y + 1)
                 << btn_up_bg
                 << box(r1.width - 2, r1.height - 2)
                 << stamp(spin_up_icon, r1.start.x + 3, r1.start.y + r1.height/2 - 3);

        Rect& r2 = spin_dn_hitbox;
        rendered << move_to(r2.start.x, r2.start.y)
                 << btn_border
                 << box(r2.width, r2.height)
                 << move_to(r2.start.x + 1, r2.start.y + 1)
                 << btn_dn_bg
                 << box(r2.width - 2, r2.height - 2)
                 << stamp(spin_dn_icon, r2.start.x + 3, r2.start.y + r2.height/2 - 3);
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
    //     // visible charcodes: 32 - 255
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
            focused->on_key_ev(kev, false);
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
        render(gout);
        gout << refresh;

        event ev;
        while (gin >> ev)
        {
            if (ev.type == ev_key)
            {
                if(on_key_event(ev))
                {
                    render(gout);
                    gout << refresh;
                }
                
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