#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "control.hpp"
#include <vector>

namespace Controls
{
   struct Scene
    {
    private:
        const int KEY_DELAY = 7;
        const int REFRESH_RATE = 40;

        genv::canvas background;

        std::vector<Control*> controls;
        std::vector<void(*)(genv::event)> listeners;

        int click_buffer = 0; 
        bool mouse_held = false;

        int key_held = 0;
        int key_hold_delay = KEY_DELAY;

        Control* hovered = nullptr;
        Control* focused = nullptr;
        Control* held = nullptr;
        size_t focused_index = -1;

        void render_background();
        bool on_mouse_event(const genv::event& mev);
        bool on_key_event(const genv::event& kev);
        void render(genv::canvas& c);

    public:
        Scene(int width, int height);
        ~Scene();

        void add_control(Control* c);
        void add_listener(void(*listener)(genv::event));

        int run(bool fullscreen = false);
    };
}

#endif