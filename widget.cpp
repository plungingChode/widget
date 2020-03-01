#include "pch.hpp"
#include "controls.cpp"

using namespace genv;
using namespace Controls;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int CANVAS_WIDTH = 600;

void print_one()
{
    std::cout << 1 << '\n';
}

Frame* MENU_BOX1 = new Frame(Point(CANVAS_WIDTH + 1, 0), Point(SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2 - 1));
// Control MENU_BOX2 = Control(Point(0, SCREEN_HEIGHT / 2 + 3), CANVAS_WIDTH / 2, SCREEN_HEIGHT / 2);
Frame* MENU_BOX3 = new Frame(Point(50, SCREEN_HEIGHT / 2 - 50), CANVAS_WIDTH / 2, SCREEN_HEIGHT / 2);
Frame* MENU_BOX4 = new Frame(Point(0, SCREEN_HEIGHT / 2 + 3), CANVAS_WIDTH / 2, SCREEN_HEIGHT / 2);
Label* lbl1 = new Label(Point(0, 0), "Sample text", Margin(25, 15));
Label* lbl2 = new Label(Point(10, 50), "LUL", Margin(50, 18));
Button* btn1 = new Button(Point(50, 50), 100, 100, print_one);

int main(int argc, char const *argv[])
{
    gout.open(900, 600);
    Scene s(900, 600);
 
    MENU_BOX1->is_draggable = false;
    MENU_BOX3->set_border_thickness(15);
    lbl1->set_border_thickness(3);
    lbl1->set_border_color("CFCFCF");
    lbl2->set_border_thickness(1);

    s.add_control(lbl1);
    s.add_control(lbl2);
    s.add_control(MENU_BOX1);
    s.add_control(MENU_BOX3);
    s.add_control(MENU_BOX4);
    s.add_control(btn1);

    event ev;
    while (gin >> ev)
    {
        if (ev.type == ev_key)
        {
            // if (ev.keycode >= 97 && ev.keycode <= 122)
            // {
            //     std::cout << char(ev.keycode) << '\n';
            // }
            
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
