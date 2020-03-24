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
        bool is_hovered_, is_focused_, is_held_;
        bool is_resizable_, is_resizing_, size_changed_;
        bool needs_visual_update_;

        bool is_dragging_;

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

        virtual void set_resizable(const bool val) { is_resizable_ = val; }
        
        virtual void on_mouse_ev(const genv::event& mouse_ev, const bool btn_held = false) = 0;
        virtual void on_key_ev(const genv::event& key_ev, const int key_held = 0) = 0;
        // virtual void on_timer_ev(const genv::event& timer_ev) = 0;

        virtual void render() = 0;
        virtual void draw(genv::canvas& c) = 0;
    };
}

#endif