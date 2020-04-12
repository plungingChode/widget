#ifndef CONTROL_HPP_INCLUDED
#define CONTROL_HPP_INCLUDED

#include "vec2.hpp"
#include "rect.hpp"
#include "control_common.hpp"

namespace Controls
{
    class Control
    {
    protected:
        bool hovered, focused, held;
        bool resizable, resizing, size_changed;
        bool needs_update;
        bool dragged;

        // Coordinates of the mouse event that started the drag
        vec2 drag_center;

        rect resize_hitbox;

        Control(vec2 drag_center);

        virtual void update() = 0;

    public:
        bool hittest_visible;
        bool draggable;

        void set_focus(bool val) { focused = val; schedule_update(); }
        void set_hover(bool val) { hovered = val; schedule_update(); }

        bool is_focused() const { return focused; }
        bool is_hovered() const { return hovered; }
        bool is_held() const { return held; }
        bool is_resizable() const { return resizable; }

        virtual void set_resizable(bool val) { resizable = val; }
        
        virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held = false) = 0;
        virtual void on_key_ev(const genv::event& key_ev, int key_held = 0) = 0;

        void schedule_update() { needs_update = true; }
        bool updated() const { return needs_update; }
        virtual void render(genv::canvas& c) = 0;
    };
}

#endif