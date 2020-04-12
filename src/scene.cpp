#include "scene.hpp"
#include <algorithm>

using namespace genv;

namespace Controls
{
    Scene::Scene(int width, int height)
    {
        ENV_WIDTH = width;
        ENV_HEIGHT = height;
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

        // something is held -> ignore others
        // hover unchanged -> ignore others
        if (held == nullptr)
        {
            for (size_t i = 0; i < controls.size(); i++)
            {
                Control *c = controls[i];

                c->on_mouse_ev(m, mouse_held);

                if (c->hittest_visible && c->is_hovered())
                {
                    // check first hover
                    if (hovered != c)
                    {
                        if (hovered != nullptr)
                        {
                            hovered->set_hover(false);
                        }
                        hovered = c;
                        c->schedule_update();
                    }

                    // check to assign focus
                    if (focused != c && c->is_focused())
                    {
                        if (focused != nullptr)
                        {
                            focused->set_focus(false);
                        }
                        focused = hovered;
                        focused_index = i;
                        c->schedule_update();
                    }
                    break;
                }
            }
        }
        else
        {
            // something is held --> update hold state
            held->on_mouse_ev(m, mouse_held);
        }
        
        if (hovered != nullptr && !hovered->is_hovered())
        {
            hovered->set_hover(false);
            hovered = nullptr;
        }

        // check for click outside of control
        if (m.button == btn_left && focused != nullptr && hovered == nullptr)
        {
            focused->set_focus(false);
            focused = nullptr;
            focused_index = -1;
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

        if (key_held == key_tab && !held)
        {
            ++focused_index;
            if (focused_index > controls.size()-1)
            {
                focused_index = 0;
            }
            focus(focused_index);
            return true;
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
        c << move_to(0, 0) 
          << BACKGROUND_COLOR 
          << box(ENV_WIDTH, ENV_HEIGHT);

        for (int i = controls.size() - 1; i >= 0; i--)
        {
            controls[i]->render(c);
        }
    }

    void Scene::add_control(Control *c)
    {
        controls.push_back(c);
        needs_update = true;
    }

    void Scene::add_listener(void(*listener)(event))
    {
        listeners.push_back(listener);
    }

    void Scene::focus(Control *c)
    {
        if (focused)
        {
            focused->set_focus(false);
        }

        focused = c;
        focused_index = std::distance(std::find(controls.begin(), controls.end(), c), controls.begin());
        focused_index = std::min(focused_index, controls.size()-1);
        focused->set_focus(true);
    }

    void Scene::focus(int index)
    {
        if (focused)
        {
            focused->set_focus(false);
        }

        focused = controls[index];
        focused_index = index;
        focused->set_focus(true);
    }

    int Scene::run(bool fullscreen)
    {
        gout.open(ENV_WIDTH, ENV_HEIGHT, fullscreen);
        render(gout);
        gout << refresh;

        gin.timer(70);

        event ev;
        while (gin >> ev && ev.keycode != key_escape)
        {
            for (void(*l)(event) : listeners)
            {
                l(ev);
            }

            if (ev.type == ev_key && on_key_event(ev))
            {
                render(gout);              
                gout << refresh;
            } 
            else if (ev.type == ev_mouse && on_mouse_event(ev))
            {
                render(gout);
                gout << refresh;
            }
            else if (ev.type == ev_timer && key_held)
            {
                if (key_hold_delay) key_hold_delay--;

                if (focused && !key_hold_delay)
                {
                    if (key_held) focused->on_key_ev(ev, key_held);
                }
                render(gout);
                gout << refresh;
            }
        }
        return 0;
    }
}