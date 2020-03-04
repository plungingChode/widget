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

void style_btn(Button*& btn)
{
    btn->set_border_color("E5D96E");
    btn->set_text_fill_normal("E5D96E");
    btn->set_normal_bg("6c6c6c");
    btn->set_hover_bg("7c7c7c");
    btn->set_focus_bg("7c7c7c");
    btn->set_drag_bg("8c8c8c");
    btn->set_font("LiberationSans-Regular.ttf");
}


int main(int argc, char const *argv[])
{
    Scene s(470, 300);
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            Point start = Point(60 + y*110, 50 + x*40);
            std::string text = "Btn " + std::to_string(x+1) + ':' + std::to_string(y+1);
            Button* btn1 = new Button(start, text, 100, 30, print_one);
            style_btn(btn1);
            s.add_control(btn1);
        }
        
    }
    s.run();
}
