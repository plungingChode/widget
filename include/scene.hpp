#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "control.hpp"
#include <vector>
#include <functional>

namespace Controls
{
    typedef std::function<void(const genv::event&)> listener_t;

    class Scene
    {
    protected:
        const int KEY_DELAY = 7;
        const int REFRESH_RATE = 40;

        std::vector<Control*> controls;
        std::vector<listener_t> listeners;

        int click_buffer = 0; 
        bool mouse_held = false;

        int key_held = 0;
        int key_hold_delay = KEY_DELAY;

        Control* hovered = nullptr;
        Control* focused = nullptr;
        Control* held = nullptr;
        size_t focused_index = 0;

        bool needs_update = false;

        virtual bool on_mouse_event(const genv::event &mev);
        virtual bool on_key_event(const genv::event &kev);
        void render(genv::canvas& c);

    public:
        Scene(int width, int height);
        ~Scene();

        void add_control(Control *c);
        void add_listener(listener_t f);  
        void focus(Control *c);
        void focus(int index);

        template<typename T>
        void add_listener(void(T::*f)(const genv::event&), T *owner)
        {
            listeners.push_back(std::bind(f, owner, std::placeholders::_1));
        }

        int run(bool fullscreen = false);
    };
}

#endif