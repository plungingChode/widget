#include "scene.hpp"

using namespace genv;

namespace Controls
{
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
                            hovered->hovered = false;
                            hovered->schedule_update();
                        }
                        hovered = c;
                        c->schedule_update();
                    }

                    // check to assign focus
                    if (focused != c && c->is_focused())
                    {
                        if (focused != nullptr)
                        {
                            focused->focused = false;
                            focused->schedule_update();
                        }
                        focused = hovered;
                        c->schedule_update();
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
            hovered->hovered = false;
            hovered->schedule_update();
            hovered = nullptr;
        }

        // check for click outside of control
        if (m.button == btn_left && focused != nullptr && hovered == nullptr)
        {
            focused->focused = false;
            focused->schedule_update();
            focused = nullptr;
        }
    
// TODO on drag end: check for hover!
        // check for drag
        if (focused != nullptr)
        {
            if (focused->is_held())
            {
                held = focused;
                held->schedule_update();
            }
            else if (held != nullptr)
            {
                held->schedule_update();
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
        int kc = kev.keycode;
        if (kc >= 0)
        {
            key_held = kc;
        }
        else
        {
            key_held = 0;
            key_hold_delay = KEY_DELAY;
        }
        
        if (focused != nullptr)
        {
            focused->on_key_ev(kev, key_held);
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

        gin.timer(70);

        event ev;
        while (gin >> ev)
        {
            if (ev.type == ev_key)
            {
                // needs_update = needs_update || on_key_event(ev);
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
                // needs_update = needs_update || on_mouse_event(ev);
                // std::cout << held << '\n';
                if (on_mouse_event(ev))
                {
                    render(gout);
                    gout << refresh;
                }
            }

            if (ev.type == ev_timer && key_held)
            {
                if (key_hold_delay) key_hold_delay--;

                if (focused && !key_hold_delay)
                {
                    if (key_held) focused->on_key_ev(ev, key_held);
                    // if (mouse_held) focused->on_mouse_ev(ev, true);
                }
                render(gout);
                gout << refresh;
                // needs_update = false;
            }
        }
        return 0;
    }
}