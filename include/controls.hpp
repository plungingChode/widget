#ifndef CONTROLS_INCLUDED
#define CONTROLS_INCLUDED

#include "graphics.hpp"
#include <sstream>
#include <vector>

using namespace genv;

namespace Controls
{
    // declare static here, define in .cpp??


    static color hex_to_color(const std::string& h)
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

    const static color DEFAULT_BORDER = hex_to_color("718EA4");
    const static color DEFAULT_NORMAL = hex_to_color("FFFFFF");
    const static color DEFAULT_HOVER = hex_to_color("D4BA6A");
    const static color DEFAULT_FOCUS = hex_to_color("AA8E39");
    const static color DEFAULT_MOUSEDOWN = hex_to_color("AA5939");
    const static color DEFAULT_TEXT_NORMAL = hex_to_color("100000");
    const static color DEFAULT_TEXT_FOCUS = hex_to_color("FFFFFF");

    static int ENV_WIDTH  = 999999;
    static int ENV_HEIGHT = 999999;
    static color BACKGROUND_COLOR = color(60, 60, 60);

    struct Point
    {
        int x, y;
        Point(int x, int y);
        Point();
        
        void operator+=(const Point& rhs);
        void operator-=(const Point& rhs);
        friend Point operator-(const Point& lhs, const Point& rhs);
        friend Point operator+(const Point& lhs, const Point& rhs);
    };

    struct Margin
    {
        int top, left, bottom, right;
        Margin(int top, int left, int bottom, int right);
        Margin(int all);
        Margin(int horizontal, int vertical);
        Margin();
    };

    struct Rect
    {
    public:
        Point start, end;
        unsigned int width, height;

        Rect(Point start, Point end);
        Rect(Point start, int width, int height);
        Rect(int width, int height);
        Rect();

        Point get_start();
        Point get_end();
        unsigned int get_width();
        unsigned int get_height();

        bool intersects(Point p) const;
        bool intersects(int x, int y) const;
    };

// TODO move drag handling (is_draggable, drag_center, drag_start) to Frame?
    struct Control
    {
    friend class Scene;
    protected:
        bool _is_hovered, _is_focused, _is_held;
        bool _is_resizable, _is_resizing;
        bool _needs_visual_update;

        bool _is_dragging;

        // Coordinates of the mouse event that started the drag
        Point drag_center;

        // Coordinates of the 'start' point when the drag begins
        Point drag_start;

        Rect resize_hitbox;

        Control(Point drag_center, Point drag_start);

    public:
        bool is_hittest_visible;
        bool is_draggable;

        bool is_focused() const;
        bool is_hovered() const;
        bool is_held() const;

        void update_visuals();
        bool updated() const;

        virtual void set_resizable(const bool val) { _is_resizable = val; }
        
        virtual void on_mouse_ev(const event& mouse_ev, const bool btn_held = false) = 0;
        virtual void on_key_ev(const event& key_ev, const bool key_held = false) = 0;

        virtual void render() = 0;
        virtual void draw(canvas& c) = 0;
    };

    struct Frame : public Control, public Rect
    {
    protected:
        color normal_bg, hover_bg, focus_bg, hold_bg;
        color fill, border;
        unsigned int border_thickness;
        unsigned int min_width, min_height;

        canvas rendered;

        inline void set_color(color& target, const std::string& hex);

    public:
        Frame(Point start, Point end);
        Frame(Point start, int width, int height);

        void set_resizable(const bool val) override;
        void reset_resize_hitbox();
        void set_normal_bg(const std::string& hex);
        void set_focus_bg(const std::string& hex);
        void set_hover_bg(const std::string& hex);
        void set_drag_bg(const std::string& hex);
        void set_border_color(const std::string& hex);
        void set_border_thickness(const unsigned thickness);

        virtual void on_mouse_ev(const event& mouse_ev, const bool btn_held = false) override;
        virtual void on_key_ev(const event& key_ev, const bool key_held = false) override {}
        virtual void render() override;
        virtual void draw(canvas& c) override;
    };

    struct Label : public Frame
    {
    protected:
        color text_fill_normal, text_fill_focused;
        Margin padding;

        std::string text, font_src;
        int text_width, char_ascent, char_descent;
        int text_x, text_y;

    public:
        Label(Point start, const std::string& text,int width, int height);
        Label(Point start, const std::string& text, int padding);
        Label(Point start, const std::string& text, Margin padding);

        void set_text_fill_normal(const std::string& hex);
        void set_font(const std::string& font_src, int font_size = 16);
        virtual void render() override;
    };

    struct Button : public Label
    {
    protected:
        void (*action)();
        canvas content;
        // Point content_offset;

    public:
        Button(Point start, const std::string& text, Margin padding, void (*action)());
        Button(Point start, const std::string& text, int width, int height, void (*action)());

        void on_mouse_ev(const event& mouse_ev, const bool btn_held = false) override;
        void render() override;
    };

    // struct TextBox : public Label
    // {
    // public:
    //     TextBox(Point start, const std::string& text, Margin padding);
    //     TextBox(Point start, const std::string& text, int width, int height);
    //     // TextBox(Point start, Margin padding);
    //     // TextBox(Point start, int width, int height);

    //     void on_key_ev(const event& key_ev) override;
    //     void render() override;
    // };

    // struct Spinner : public Label
    // {
    // protected:
    //     void (*spin_up)(int& value);
    //     void (*spin_dn)(int& value);
    //     void (*spin_up_big)(int& value);
    //     void (*spin_dn_big)(int& value);


    // };

    // struct ComboBox
    // {};

    struct Scene
    {
    private:
        canvas background;

        std::vector<Control*> controls;
        int click_buffer = 0; 
        bool mouse_held = false;
        bool needs_update = true;
        Control* hovered = nullptr;
        Control* focused = nullptr;
        Control* held = nullptr;

        void render_background();
        bool on_mouse_event(const event& mev);
        bool on_key_event(const event& kev);
        void render(canvas& c);

    public:
        Scene(int width, int height);
        ~Scene();

        void add_control(Control* c);

        int run(bool fullscreen = false);
    };
}

#endif