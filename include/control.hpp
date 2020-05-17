#ifndef CONTROL_HPP_INCLUDED
#define CONTROL_HPP_INCLUDED

#include "vec2.hpp"
#include "rect.hpp"
#include "control_common.hpp"

class Scene;

class Control : public rect
{
protected:
    genv::canvas rendered;

    bool hovered, focused, held;
    bool resizable, resizing, size_changed;
    bool needs_update;
    bool dragged;
    bool hittest_visible;
    bool draggable;

    // Coordinates of the mouse event that started the drag
    vec2 drag_center;

    Scene *owner;
    const genv::font *font;

    Control(Scene *owner, int x, int y, int width, int height, const genv::font *font = nullptr);

    virtual void update() = 0;

public:
    static bool FORCE_GLOBAL_FONT;

    virtual ~Control() = default; 

    void set_focus(bool val) { focused = val; schedule_update(); }
    void set_hover(bool val) { hovered = val; schedule_update(); }
    void set_owner(Scene *s) { owner = s; }

    bool is_focused() const { return focused; }
    bool is_hovered() const { return hovered; }
    bool is_held() const { return held; }
    bool is_resizable() const { return resizable; }
    bool is_draggable() const { return draggable; }
    bool is_hittest_visible() const { return hittest_visible; }

    virtual void set_resizable(bool val) { resizable = val; }
    void set_draggable(bool val) { draggable = val; }
    void set_hittest_visible(bool val) { hittest_visible = val; }
    virtual void set_font(const genv::font *font);

    virtual void on_mouse_ev(const genv::event& mouse_ev, bool btn_held) = 0;
    virtual void on_key_ev(const genv::event& key_ev, int key_held) = 0;

    void schedule_update() { needs_update = true; }
    bool updated() const { return needs_update; }
    virtual void render(genv::canvas& c) = 0;
};

#endif