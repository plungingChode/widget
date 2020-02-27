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

    static int ENV_WIDTH  = 999999;
    static int ENV_HEIGHT = 999999;

    struct Point
    {
        int x, y;
        Point(int x, int y);
        Point();
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

    struct Control : public Rect
    {
    protected:
        color color_normal, color_hover, color_focus, color_drag;
        color fill, border;

        bool _is_hovered, _is_focused;
        bool _needs_update, _updated;

        bool _is_dragging;

        // Coordinates of the mouse event that started the drag1
        Point drag_center;

        // Coordinates of the 'start' point when the drag begins
        Point drag_start;

        int border_thickness;
        canvas rendered;

        Control();
        void set_defaults() const;
        inline void set_drag(bool val);
        inline void set_color(color& target, const std::string& hex);
    
    public:
        bool is_draggable;

        Control(Point start, Point end);
        Control(Point start, int width, int height);

        bool is_focused() const;
        bool updated() const;

        void set_normal_color(const std::string& hex);
        void set_focus_color(const std::string& hex);
        void set_hover_color(const std::string& hex);
        void set_border_color(const std::string& hex);
        void set_border_thickness(const int thickness);

        void set_hover(bool val);
        void set_focus(bool val);
        bool check_drag(const event& mouse_ev, const int btn);
        
        void render(canvas& c);
    };

    struct Scene
    {
    private:
        canvas clear_screen = canvas(ENV_HEIGHT, ENV_WIDTH);

        std::vector<Control> controls;
        int click_buf = 0; 
        bool needs_update = true;
        Control* hovered = nullptr;
        Control* focused = nullptr;
        Control* dragged = nullptr;

    public:
        Scene(int width, int height);

        bool on_mouse_event(const event& mev);
        void render(canvas& c);
        void add_control(const Control& c);
    };
}

#endif