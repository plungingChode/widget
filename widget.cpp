#include "pch.hpp"
#include "controls.hpp"

using namespace genv;
using namespace Controls;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int CANVAS_WIDTH = 600;



Control MENU_BOX1 = Control(Point(CANVAS_WIDTH + 1, 0), Point(SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2 - 1));
// Control MENU_BOX2 = Control(Point(0, SCREEN_HEIGHT / 2 + 3), CANVAS_WIDTH / 2, SCREEN_HEIGHT / 2);
Control MENU_BOX3 = Control(Point(50, SCREEN_HEIGHT / 2 - 50), CANVAS_WIDTH / 2, SCREEN_HEIGHT / 2);
Control MENU_BOX4 = Control(Point(0, SCREEN_HEIGHT / 2 + 3), CANVAS_WIDTH / 2, SCREEN_HEIGHT / 2);

int main(int argc, char const *argv[])
{
    gout.open(900, 600);
    Scene s(900, 600);

    MENU_BOX1.is_draggable = false;
    MENU_BOX3.set_border_thickness(15);

    s.add_control(MENU_BOX1);
    s.add_control(MENU_BOX3);
    s.add_control(MENU_BOX4);

    event ev;
    while (gin >> ev)
    {
        // std::cout << ev.type << '\n';

        if (ev.type == ev_key)
        {
            if (ev.keycode >= 97 && ev.keycode <= 122)
            {
                std::cout << char(ev.keycode) << '\n';
            }
            
            if (ev.keycode == key_escape)
            {
                return 0;
            }
        }

        if (ev.type == ev_mouse)
        {
            if (s.on_mouse_event(ev))
            {
                s.render(gout);
                gout << refresh;
            }
            
        }
    }
    return 0;
}
