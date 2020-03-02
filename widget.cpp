#include "pch.hpp"
#include "controls.cpp"

using namespace genv;
using namespace Controls;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int CANVAS_WIDTH = 600;

void print_one()
{
    std::cout << "+1\n";
}

canvas read_kep(const std::string& fname)
{
    std::ifstream f(fname);
    int width, height;
    f >> width >> std::ws;
    f >> height >> std::ws;

    canvas c(width, height); 

    int x, y;
    int r, g, b;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            f >> r >> g >> b;

            c << move_to(x, y) 
              << color(r, g, b) 
              << dot;
        }
    }
    c.transparent(true);
    return c;
}

// Button* btn1 = new Button(Point(50, 60), "Test button", 120, 30, print_one);
// Button* btn2 = new Button(Point(50+btn1->get_width()+10, 60), "Test button 2", 120, 30, print_one);

void style_btn(Button*& btn)
{
    btn->set_border_color("E5D96E");
    btn->set_text_fill_normal("E5D96E");
    btn->set_normal_bg("7c7c7c");
    btn->set_hover_bg("8c8c8c");
    btn->set_focus_bg("8c8c8c");
    btn->set_drag_bg("999999");
    btn->set_font("LiberationSans-Regular.ttf");
}

void style_label(Label*& lbl)
{
    lbl->is_hittest_visible = true;
    lbl->set_font("LiberationSans-Regular.ttf");
    lbl->set_border_thickness(3);
}

int main(int argc, char const *argv[])
{
    Scene s(500, 300);
    for (int i = 0; i < 10; i++)
    {
        Label* lbl1 = new Label(Point(std::rand() % 400, std::rand() % 200), "0", Margin(25, 10));
        style_label(lbl1);
        s.add_control(lbl1);
    }
    s.run();
}
