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
        bool _is_hovered, _is_focused, _is_held;
        bool _is_resizable, _is_resizing, _size_changed;
        bool _needs_visual_update;

        bool _is_dragging;

        // Coordinates of the mouse event that started the drag
        vec2 drag_center;

        rect resize_hitbox;

        Control(vec2 drag_center);

    public:
        bool is_hittest_visible;
        bool is_draggable;

        bool is_focused() const;
        bool is_hovered() const;
        bool is_held() const;

        void update_visuals();
        bool updated() const;

        virtual void set_resizable(const bool val) { _is_resizable = val; }
        
        virtual void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) = 0;
        virtual void on_key_ev(const genv::event& key_ev, const int key_held = 0) = 0;
        // virtual void on_timer_ev(const genv::event& timer_ev) = 0;

        virtual void render() = 0;
        virtual void draw(genv::canvas& c) = 0;
    };
}

#endif