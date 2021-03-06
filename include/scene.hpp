#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "control.hpp"
#include <vector>
#include <functional>

class Scene
{
protected:
    const int KEY_DELAY = 7;
    const int REFRESH_RATE = 40;

    std::vector<Control*> controls;

    int click_buffer = 0; 
    bool mouse_held = false;

    int key_held = 0;
    int key_hold_delay = KEY_DELAY;

    Control* hovered = nullptr;
    Control* focused = nullptr;
    Control* held = nullptr;
    size_t focused_index = 0;

    bool needs_update = false;

    const genv::font *global_font = nullptr;

    bool on_mouse_event(const genv::event &mev);
    bool on_key_event(const genv::event &kev);
    void render(genv::canvas& c);

public:
    const int ENV_WIDTH;
    const int ENV_HEIGHT;
    genv::color background_color;

    Scene(int width, int height);
    virtual ~Scene();

    void add_control(Control *c);
    void focus(Control *c);
    void focus(int index);

    void set_global_font(const genv::font *f);
    const genv::font* get_global_font() const;

    int run(bool fullscreen = false);
};

#endif
