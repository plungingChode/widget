#ifndef CONTROL_HPP_INCLUDED
#define CONTROL_HPP_INCLUDED

#include "vec2.hpp"
#include "rect.hpp"
#include "control_common.hpp"

namespace Controls
{
    struct Control
    {
    friend class Scene;
    protected:
        bool hovered, focused, held;
        bool resizable, resizing, size_changed;
        bool needs_update;

        bool is_dragged;

        // Coordinates of the mouse event that started the drag
        vec2 drag_center;

        rect resize_hitbox;

        Control(vec2 drag_center);

    public:
        virtual ~Control() = default;

        bool is_hittest_visible;
        bool is_draggable;

        bool is_focused() const { return focused; };
        bool is_hovered() const { return hovered; };
        bool is_held() const { return held; };

        void schedule_update() { needs_update = true; };
        bool updated() const { return needs_update; };

        virtual void set_resizable(const bool val) { resizable = val; }
        
        virtual void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) = 0;
        virtual void on_key_ev(const genv::event& key_ev, const int key_held = 0) = 0;

        virtual void render() = 0;
        virtual void draw(genv::canvas& c) = 0;
    };
}

#endif