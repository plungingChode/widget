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
    const static color DEFAULT_DRAG = hex_to_color("AA5939");
    const static color DEFAULT_TEXT_NORMAL = hex_to_color("000000");
    const static color DEFAULT_TEXT_FOCUS = hex_to_color("FFFFFF");

    static int ENV_WIDTH  = 999999;
    static int ENV_HEIGHT = 999999;

    struct Point
    {
        int x, y;
        Point(int x, int y);
        Point();
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
    protected:
        Point start, end;
        unsigned int width, height;

    public:
        Rect(Point start, Point end);
        Rect(Point start, int width, int height);
        Rect(int width, int height);

        bool intersects(Point p) const;
        bool intersects(int x, int y) const;
    };

    struct Control
    {
    protected:
        bool _is_hovered, _is_focused;
        bool _needs_update, _updated;

        bool _is_dragging;

        // Coordinates of the mouse event that started the drag
        Point drag_center;

        // Coordinates of the 'start' point when the drag begins
        Point drag_start;

        Control(Point drag_center, Point drag_start);

        inline void set_drag(bool val);
    
    public:
        bool is_draggable;

        bool is_focused() const;
        bool updated() const;

        virtual void set_hover(bool val);
        virtual void set_focus(bool val);

        virtual bool check_hover(const event& mouse_ev) {}
        virtual bool check_drag(const event& mouse_ev, const int btn) {}
        virtual bool on_mouse_ev(const event& mouse_ev) {}
        virtual bool on_key_ev(const event& key_ev) {}

        virtual void render() {}
        virtual void draw(canvas& c) {}
    };

    struct Frame : public Control, public Rect
    {
    protected:
        color normal_bg, hover_bg, focus_bg, drag_bg;
        color fill, border;
        int border_thickness;

        canvas rendered;

        inline void set_color(color& target, const std::string& hex);

    public:
        Frame(Point start, Point end);
        Frame(Point start, int width, int height);

        void set_normal_color(const std::string& hex);
        void set_focus_color(const std::string& hex);
        void set_hover_color(const std::string& hex);
        void set_border_color(const std::string& hex);
        void set_border_thickness(const int thickness);

        // allow override
        bool check_hover(const event& mouse_ev) override;
        bool check_drag(const event& mouse_ev, const int btn) override;
        virtual void render() override;
        virtual void draw(canvas& c) override;
    };

    struct Label : public Frame
    {
    protected:
        color text_fill_normal, text_fill_focused;
        Margin padding;

        std::string text;
        int text_width, char_ascent, char_descent;
        int text_x, text_y;

    public:
        Label(Point start, int width, int height, const std::string& text);
        Label(Point start, const std::string& text, int padding);
        Label(Point start, const std::string& text, Margin padding);

        void render() override;
        void set_text(const std::string& text);
    };

    struct Scene
    {
    private:
        canvas clear_screen = canvas(ENV_HEIGHT, ENV_WIDTH);

        std::vector<Control*> controls;
        int click_buf = 0; 
        bool needs_update = true;
        Control* hovered = nullptr;
        Control* focused = nullptr;
        Control* dragged = nullptr;

    public:
        Scene(int width, int height);
        ~Scene();

        bool on_mouse_event(const event& mev);
        bool on_key_event(const event& kev);
        void render(canvas& c);
        void add_control(Control* c);
    };
}

#endif