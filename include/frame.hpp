#ifndef FRAME_HPP_INCLUDED
#define FRAME_HPP_INCLUDED

#include "control.hpp"
#include "control_common.hpp"

class Frame : public Control
{
protected:
    genv::color normal_bg = DEFAULT_BACKGROUND_NORMAL;
    genv::color hover_bg  = DEFAULT_BACKGROUND_HOVER;
    genv::color focus_bg  = DEFAULT_BACKGROUND_FOCUS;
    genv::color hold_bg   = DEFAULT_BACKGROUND_HOLD;
    genv::color border    = DEFAULT_BORDER;
    int border_thickness;

    void set_color(genv::color &target, int hex);        
    virtual void render_resize_area();
    virtual void update() override;

public:
    Frame(Scene *owner, int x, int y, int width, int height, const genv::font *font = nullptr);

    void set_resizable(bool val) override;
    void set_background_color(int hex) { set_color(normal_bg, hex); }
    void set_focus_color(int hex) { set_color(focus_bg, hex); }
    void set_hover_color(int hex) { set_color(hover_bg, hex); }
    void set_hold_color(int hex) { set_color(hold_bg, hex); }
    void set_border_color(int hex) { set_color(border, hex); }

    virtual void set_border_thickness(int thickness);

    virtual void on_key_ev(const genv::event &key_ev, int key_held) override {}
    virtual void render(genv::canvas &c) override;
};

#endif