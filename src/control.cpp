#include "control.hpp"
#include "scene.hpp"

using namespace genv;

bool Control::FORCE_GLOBAL_FONT = false;

Control::Control(Scene *s, int x_, int y_, int w_, int h_, const genv::font *f)
    : rect(x_, y_, w_, h_),
        rendered(w_, h_),
        hovered(false), 
        focused(false), 
        held(false),
        resizable(false),
        resizing(false),
        size_changed(false),
        needs_update(true),
        dragged(false),
        hittest_visible(true),
        draggable(true),
        drag_center(vec2(0, 0)),
        min_width(20),
        min_height(20),
        owner(s),
        font(nullptr)
{
    set_font(f);
    s->add_control(this);
}

void Control::set_font(const genv::font *f)
{
    if (FORCE_GLOBAL_FONT && owner)
    {
        f = owner->get_global_font();
    }

    if (f && rendered.load_font(f->font_name, f->font_size))
    {
        this->font = f;
    }
    else
    {
        this->font = nullptr;
    }
    schedule_update();
}

void Control::reset_resize_hitbox()
{
    resize_hitbox = rect(w-8, h-8, 8, 8);
}

void Control::on_mouse_ev(const event& m, bool btn_held)
{
    if (!hittest_visible) return;
    size_changed = false; // assume change was handled

    hovered = intersects(m.pos_x, m.pos_y);

    if (m.button == btn_left && !btn_held)
    {
        focused = hovered;
    }

    held = focused && (m.button == btn_left || btn_held);

    if (held && resizable)
    {
        vec2 m_rel(m.pos_x - x, m.pos_y - y);
        bool resize_hit = resize_hitbox.intersects(m_rel);

        resizing = resizing || (m.button == btn_left && resize_hit);
    }
    
    if (resizing && held)
    {
        vec2 m_limit
        (
            std::max(m.pos_x, x + min_width),
            std::max(m.pos_y, y + min_height)
        );
        
        w += m_limit.x - x - w;
        h += m_limit.y - y - h;
    }
    else if (draggable && held)
    {
        if (!dragged)
        {
            drag_center.x = m.pos_x - x;
            drag_center.y = m.pos_y - y;

            dragged = true;
        }
        
        x = std::min(std::max(m.pos_x - drag_center.x, 0), owner->ENV_WIDTH - w);
        y = std::min(std::max(m.pos_y - drag_center.y, 0), owner->ENV_HEIGHT - h);
    }
    else
    {
        if (resizing)
        {
            reset_resize_hitbox();

            size_changed = true;
            resizing = false;
            held = false;
        }
        if (dragged)
        {
            dragged = false;
            held = false;
        }
    }
}

void Control::on_key_ev(const genv::event& key_ev, int key_held)
{
}

void Control::render(genv::canvas &c)
{
    if (needs_update)
    {
        update();
        needs_update = false;
    }
    c << stamp(rendered, x, y);
}